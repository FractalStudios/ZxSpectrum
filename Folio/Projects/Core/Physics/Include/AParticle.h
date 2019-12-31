#pragma once

// "Home-made" includes.
#include    <Graphic.h>
#include    <Trace.h>
#include    "IGraphicElement.h"
#include    "Vector2.h"
#include    "Vector3.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Physics
{

/// The abstract particle template class.
/**
 * This class provides a template for abstract particles.
 *
 * This class does not support copy construction or assignment.
 */
template <typename T>
class AParticle : public IGraphicElement
{
public:
    /// Type definition for a type T.
    typedef T           value_type;
    /// Type definition for a constant reference to type T.
    typedef const T&    const_reference;
    /// Type definition for a reference to type T.
    typedef       T&    reference;
    /// Type definition for a constant interator to type T.
    typedef const T*    const_iterator;
    /// Type definition for an interator to type T.
    typedef       T*    iterator;

    virtual ~AParticle ();

    FolioStatus Create (FolioHandle     dcHandle,
                        const_reference position);

    FolioStatus BeginUpdate (Gdiplus::Graphics& graphics,
                             RectList*          rects = 0,
                             const value_type*  force = 0);
    FolioStatus EndUpdate (Gdiplus::Graphics& graphics);

    FolioStatus BeginRedraw (Gdiplus::Graphics& graphics,
                             RectList*          rects = 0);
    FolioStatus EndRedraw (Gdiplus::Graphics& graphics);

    // IGraphicElement method(s).
    virtual FolioStatus Draw (Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

protected:
    value_type  m_currentPosition;      ///< The current position of the particle.
    value_type  m_previousPosition;     ///< The previous position of the particle.
    value_type  m_velocity;             ///< The direction and speed of the particle.
    UInt32      m_age;                  ///< The age of the particle.
    float       m_mass;                 ///< The mass of the particle.

    virtual FolioStatus HandleCreate (Gdiplus::Rect& cleanRect) = 0;
    virtual FolioStatus HandleBeginUpdate (const value_type* force) = 0;
    virtual FolioStatus HandleEndUpdate (Gdiplus::Rect& cleanRect) = 0;
    virtual FolioStatus HandleBeginRedraw () = 0;
    virtual FolioStatus HandleEndRedraw (Gdiplus::Graphics& graphics) = 0;
    virtual FolioStatus HandleDraw (Gdiplus::Graphics& graphics) = 0;

    AParticle ();

private:
    bool    m_created;      ///< Indicates if the particle has been created.
    bool    m_beingUpdated; ///< Indicates if the particle is in the process of being updated.
    bool    m_beingRedrawn; ///< Indicates if the particle is in the process of being redrawn.

    Folio::Core::Graphic::GdiBufferedBitmap m_cleanRectangle;   ///< The clean rectangle of the particle.

    bool    IsCreated () const;
    bool    IsBeingUpdated () const;
    bool    IsBeingRedrawn () const;
    bool    IsBusy () const;
    bool    IsAlive () const;

    FolioStatus Update (const value_type* force);

    /// Private copy constructor to prevent copying.
    AParticle (const AParticle<T>& rhs);

    /// Private assignment operator to prevent copying.
    AParticle& operator= (const AParticle<T>& rhs);
}; // Endclass.


/**
 * The default class constructor.
 */
template <typename T>
inline  AParticle<T>::AParticle ()
:   m_created(false),
    m_age(FOLIO_INFINITE),
    m_mass(0.0),
    m_beingUpdated(false),
    m_beingRedrawn(false)
{
} // Endproc.


/**
 * The class destructor.
 */
template <typename T>
inline  AParticle<T>::~AParticle ()
{
} // Endproc.


/**
 * Method that is used to create the particle.
 *
 * @param [in] dcHandle
 * The device context handle.
 *
 * @param [in] position
 * The position of the particle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a particle has been previously created 
 *     using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::Create (FolioHandle       dcHandle,
                                  const_reference   position)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a particle already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Set the particle's attributes.

        m_currentPosition   = position;
        m_previousPosition  = position;

        // Let our sub-class handle the creation.

        Gdiplus::Rect   cleanRect;

        status = HandleCreate (cleanRect);

        if (status == ERR_SUCCESS)
        {
            // Make sure that the sub-class has specified a clean rect.

            if ((cleanRect.Width == 0) ||
                (cleanRect.Height == 0))
            {
                // The clean rect is invalid.

                status = ERR_PROGRAMMING_LOGIC;
                
                // Log an error.

                FOLIO_LOG_ERROR_5 (TXT("HandleCreate returned an invalid clean rect"),
                                   status,
                                   cleanRect.X,
                                   cleanRect.Y,
                                   cleanRect.Width,
                                   cleanRect.Height);
            } // Endif.

            else
            {
                // Create the clean rectangle. 
        
                status = m_cleanRectangle.Create (dcHandle, cleanRect);
    
                if (status == ERR_SUCCESS)
                {
                    // We have been created.
    
                    m_created = true;
                } // Endif.

            } // Endelse.

        } // Endif.

        else
        {
            // Log an error.

            FOLIO_LOG_CALL_ERROR (TXT("HandleCreate"), 
                                  status);
        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to begin the update of the particle. 
 * 
 * The particle will draw its clean rectangle into the specified graphics 
 * object before updating.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle, if successful. If this 
 * method fails then this parameter is undefined. May be zero if not required.
 *
 * @param [in] force
 * The force acting on the particle. May be zero if there is no force acting on
 * the particle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a particle has not been previously 
 *     created using this object, or the particle is already being updated.
 * <li><b>ERR_NOT_ACTIVE</b> if the particle is dead.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::BeginUpdate (Gdiplus::Graphics&   graphics,
                                       RectList*            rects,
                                       const value_type*    force)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a particle and is it not busy?

    if (IsCreated () && !IsBusy ())
    {
        // Yes. Is the particle alive?

        if (IsAlive ())
        {
            // Yes. Draw the clean rectangle (and remove the particle).
      
            status = m_cleanRectangle.Draw (graphics, rects);
      
            if (status == ERR_SUCCESS)
            {
                // Update the particle.
            
                status = Update (force);

                if (status == ERR_SUCCESS)
                {
                    // Let our sub-class handle the beginning of the update.
            
                    status = HandleBeginUpdate (force);
            
                    if (status == ERR_SUCCESS)
                    {
                        // We are being updated.

                        m_beingUpdated = true;
                    } // Endif.

                    else
                    {
                        // Log an error.
            
                        FOLIO_LOG_CALL_ERROR (TXT("HandleBeginUpdate"),
                                              status);
                    } // Endelse.

                } // Endif.
    
            } // Endif.

        } // Endif.

        else
        {
            status = ERR_NOT_ACTIVE;
        } // Endelse.
    
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to end the update of the particle.
 *
 * The particle will buffer its clean rectangle from the specified graphics 
 * object.
 *
 * @param [in, out] graphics
 * The graphics object to buffer from.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a particle has not been previously 
 *     created using this object, or the particle is not being updated.
 * <li><b>ERR_NOT_ACTIVE</b> if the particle is dead.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::EndUpdate (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a particle and is it being updated?

    if (IsCreated () && IsBeingUpdated ())
    {
        // Yes. Is the particle alive?

        if (IsAlive ())
        {
            // Yes. Let our sub-class handle the end of the update.

            Gdiplus::Rect   cleanRect;
    
            status = HandleEndUpdate (cleanRect);
    
            if (status == ERR_SUCCESS)
            {
                // Make sure that the sub-class has specified a clean rect.
    
                if ((cleanRect.Width == 0) ||
                    (cleanRect.Height == 0))
                {
                    // The clean rect is invalid.
    
                    status = ERR_PROGRAMMING_LOGIC;
                    
                    // Log an error.
    
                    FOLIO_LOG_ERROR_5 (TXT("HandleEndUpdate returned an invalid clean rect"),
                                       status,
                                       cleanRect.X,
                                       cleanRect.Y,
                                       cleanRect.Width,
                                       cleanRect.Height);
                } // Endif.

                else
                {
                    // Buffer the clean rectangle. 
            
                    status = m_cleanRectangle.Buffer (graphics, cleanRect);
                } // Endelse.

            } // Endif.
    
            else
            {
                // Log an error.
    
                FOLIO_LOG_CALL_ERROR (TXT("HandleEndUpdate"), 
                                      status);
            } // Endelse.

            m_beingUpdated = (status != ERR_SUCCESS);
        } // Endif.

        else
        {
            status = ERR_NOT_ACTIVE;
        } // Endelse.
    
    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to begin the redraw of the particle.
 *
 * The particle will buffer its clean rectangle from the specified graphics 
 * object.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle, if successful. If this 
 * method fails then this parameter is undefined. May be zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a particle has not been previously 
 *     created using this object.
 * <li><b>ERR_NOT_ACTIVE</b> if the particle is dead.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::BeginRedraw (Gdiplus::Graphics&   graphics,
                                       RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a particle and is it not busy?

    if (IsCreated () && !IsBusy ())
    {
        // Yes. Is the particle alive?

        if (IsAlive ())
        {
            // Yes. Buffer the clean rectangle. 

            Gdiplus::Rect   cleanRect(m_cleanRectangle.GetBufferedBitmapRect ());
    
            status = m_cleanRectangle.Buffer (graphics, 
                                              Gdiplus::Point(cleanRect.X, 
                                                             cleanRect.Y));

            if (status == ERR_SUCCESS)
            {
                // Let our sub-class handle the beginning of the redraw.
        
                status = HandleBeginRedraw ();
        
                if (status == ERR_SUCCESS)
                {
                    // We are being redrawn.

                    m_beingRedrawn = true;

                    // Does the caller want to know the rects?
        
                    if (rects)
                    {
                        // Yes. Give them the rect of the clean rectangle.
        
                        rects->push_back (m_cleanRectangle.GetBufferedBitmapRect ());
                    } // Endif.

                } // Endif.

                else
                {
                    // Log an error.
        
                    FOLIO_LOG_CALL_ERROR (TXT("HandleBeginRedraw"),
                                          status);
                } // Endelse.

            } // Endif.

        } // Endif.

        else
        {
            status = ERR_NOT_ACTIVE;
        } // Endelse.

    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to end the redraw of the particle.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a particle has not been previously 
 *     created using this object.
 * <li><b>ERR_NOT_ACTIVE</b> if the particle is dead.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::EndRedraw (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a particle and is it being redrawn?

    if (IsCreated () && IsBeingRedrawn ())
    {
        // Yes. Is the particle alive?

        if (IsAlive ())
        {
            // Yes. Let our sub-class handle the end of the redraw.
                
            status = HandleEndRedraw (graphics);
                
            if (status != ERR_SUCCESS)
            {
                // Log an error.
    
                FOLIO_LOG_CALL_ERROR (TXT("HandleEndRedraw"), 
                                      status);
            } // Endelse.

            m_beingRedrawn = (status != ERR_SUCCESS);
        } // Endif.

        else
        {
            status = ERR_NOT_ACTIVE;
        } // Endelse.

    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the particle.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle, if successful. If this 
 * method fails then this parameter is undefined. May be zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a particle has not been previously 
 *     created using this object.
 * <li><b>ERR_NOT_ACTIVE</b> if the particle is dead.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::Draw (Gdiplus::Graphics&  graphics,
                                RectList*           rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a particle?

    if (IsCreated ())
    {
        // Yes. Is the particle alive?

        if (IsAlive ())
        {
            // Yes. Let our sub-class handle the draw.
            
            status = HandleDraw (graphics);
            
            if (status != ERR_SUCCESS)
            {
                // Log an error.
    
                FOLIO_LOG_CALL_ERROR (TXT("HandleDraw"), 
                                      status);
            } // Endif.

            // Does the caller want to know the rects?
        
            if (rects && (status == ERR_SUCCESS))
            {
                // Yes. Give them the rect of the clean rectangle.
        
                rects->push_back (m_cleanRectangle.GetBufferedBitmapRect ());
            } // Endif.

        } // Endif.

        else
        {
            status = ERR_NOT_ACTIVE;
        } // Endelse.

    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to determine if the particle has been created.
 *
 * @return
 * <b>true</b> if the particle has been created, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    AParticle<T>::IsCreated () const
{
    return (m_created);
} // Endproc.


/**
 * Method that is used to determine if the particle is being updated.
 *
 * @return
 * <b>true</b> if the particle is being updated, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    AParticle<T>::IsBeingUpdated () const
{
    return (m_beingUpdated);
} // Endproc.


/**
 * Method that is used to determine if the particle is being redrawn.
 *
 * @return
 * <b>true</b> if the particle is being redrawn, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    AParticle<T>::IsBeingRedrawn () const
{
    return (m_beingRedrawn);
} // Endproc.


/**
 * Method that is used to determine if the particle is busy (being updated or 
 * redrawn).
 *
 * @return
 * <b>true</b> if the particle is busy, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    AParticle<T>::IsBusy () const
{
    return (m_beingUpdated || m_beingRedrawn);
} // Endproc.


/**
 * Method that is used to determine if the particle is alive.
 *
 * @return
 * <b>true</b> if the particle is alive, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    AParticle<T>::IsAlive () const
{
    return (m_age != 0);
} // Endproc.


/**
 * Method that is used to update the particle.
 *
 * @param [in] force
 * The force acting on the particle. May be zero if there is no force acting on
 * the particle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_ACTIVE</b> if the particle is dead.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticle<T>::Update (const value_type* force)
{
    if (IsAlive ())
    {
        // Is there a force acting on the particle?

        if (force)
        {
            // Update the particle's velocity according to the force acting on 
            // it.
    
            m_velocity += *force;
        } // Endif.
    
        // Note the particle's previous position.
    
        m_previousPosition = m_currentPosition;

        // Update the particle's position according to its velocity.
    
        m_currentPosition += m_velocity;
    
        if (m_age != FOLIO_INFINITE)
        {
            m_age--;    // The particle is older.
        } // Endif.

    } // Endif.

    return (IsAlive () ? ERR_SUCCESS : ERR_NOT_ACTIVE);
} // Endproc.


#ifdef  FOLIO_DOXYGEN

/**
 * Method that is used to handle the creation of the particle.
 *
 * @param [out] cleanRect
 * On return, will hold the rect which defines the position and size of the 
 * particle, if successful. If this method fails then this parameter is 
 * undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus APartricle<T>::HandleCreate (Gdiplus::Rect& cleanRect) = 0;


/**
 * Method that is used to handle the beginning of the update of the particle. 
 * 
 * @param [in] force
 * The force acting on the particle. May be zero if there is no force acting on 
 * the particle.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus APartricle<T>::HandleBeginUpdate (const value_type* force) = 0;


/**
 * Method that is used to handle the end of the update of the particle.
 *
 * @param [out] cleanRect
 * On return, will hold the rect which defines the position and size of the 
 * particle, if successful. If this method fails then this parameter is 
 * undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus APartricle<T>::HandleEndUpdate (Gdiplus::Rect& cleanRect) = 0;


/**
 * Method that is used to handle the beginning of the redraw of the particle. 
 * 
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus APartricle<T>::HandleBeginRedraw () = 0;


/**
 * Method that is used to handle the end of the redraw of the particle.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus APartricle<T>::HandleEndRedraw (Gdiplus::Graphics& graphics) = 0;


/**
 * Method that is used to handle the drawing of the particle.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus APartricle<T>::HandleDraw (Gdiplus::Graphics& graphics) = 0;

#endif


/// 2D particle.
typedef AParticle<Vector2>   AParticle2;


/// 3D particle.
typedef AParticle<Vector3>   AParticle3;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
