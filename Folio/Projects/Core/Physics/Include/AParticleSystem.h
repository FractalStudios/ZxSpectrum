#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Trace.h>
#include    "AParticle.h"
#include    "IGraphicElement.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Physics
{

/// The abstract particle system template class.
/**
 * This class provides a template for abstract particle systems.
 *
 * This class does not support copy construction or assignment.
 */
template <typename T>
class AParticleSystem : public IGraphicElement
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

    virtual ~AParticleSystem ();

    FolioStatus Initialise (FolioHandle     dcHandle,
                            Gdiplus::Rect&  boundingRect,
                            UInt32          maxNumParticles);
    FolioStatus Terminate ();
    FolioStatus Update (Gdiplus::Graphics&  graphics,
                        RectList*           rects = 0);
    FolioStatus Redraw (Gdiplus::Graphics&  graphics,
                        RectList*           rects = 0);

    // IGraphicElement method(s).
    virtual FolioStatus Draw (Gdiplus::Graphics&    graphics,
                              RectList*             rects = 0);

    bool    IsActive () const;

protected:
    FolioHandle     m_dcHandle;             ///< The device context handle to be used by the particle system.
    Gdiplus::Rect   m_boundingRect;         ///< The bounding rect of the particle system.
    UInt32          m_maxNumParticles;      ///< The maximum number of particles supported by the particle system.
    bool            m_recreateParticles;    ///< Indicates if particles in the particle system are recreated.

    /// The particle list.
    typedef std::vector<AParticle<T> *> ParticleList;
    ParticleList    m_particles;    ///< The particles in the system.

    virtual FolioStatus HandleInitialize ();
    virtual FolioStatus HandleTerminate ();
    virtual FolioStatus HandleUpdate ();
    virtual FolioStatus HandleRedraw ();

    virtual FolioStatus CreateParticle (AParticle<T>*& particle);
    virtual FolioStatus CreateParticles ();

    AParticleSystem ();

private:
    bool    m_initialized;  ///< Indicates if the particle system has been initialized.

    void        DestroyParticles ();
    FolioStatus UpdateParticles (Gdiplus::Graphics& graphics,
                                 RectList*          rects);
    FolioStatus BeginUpdateParticles (Gdiplus::Graphics&    graphics,
                                      RectList*             rects);
    FolioStatus EndUpdateParticles (Gdiplus::Graphics& graphics);
    FolioStatus RedrawParticles (Gdiplus::Graphics& graphics,
                                 RectList*          rects);
    FolioStatus BeginRedrawParticles (Gdiplus::Graphics&    graphics,
                                      RectList*             rects);
    FolioStatus EndRedrawParticles (Gdiplus::Graphics& graphics);
    FolioStatus DrawParticles (Gdiplus::Graphics&   graphics,
                               RectList*            rects);

    bool    IsInitialized () const;

    /// Private copy constructor to prevent copying.
    AParticleSystem (const AParticleSystem<T>& rhs);

    /// Private assignment operator to prevent copying.
    AParticleSystem& operator= (const AParticleSystem<T>& rhs);
}; // Endclass.


/**
 * The default class constructor.
 */
template <typename T>
inline  AParticleSystem<T>::AParticleSystem ()
:   m_dcHandle(FOLIO_INVALID_HANDLE),
    m_maxNumParticles(0),
    m_recreateParticles(false),
    m_initialized(false)
{
} // Endproc.


/**
 * The class destructor.
 */
template <typename T>
inline  AParticleSystem<T>::~AParticleSystem ()
{
    // Destroy the particles.

    DestroyParticles ();
} // Endproc.


/**
 * Method that is used to initialize the particle system.
 *
 * @param [in] dcHandle
 * The handle to the device context to be used by the particle system.
 *
 * @param [in] boundingRect
 * The bounding rect of the particle system.
 *
 * @param [in] maxNumParticles
 * The maximum number of particles that are supported by the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the particle system was successfully initialized.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the particle system has been previously 
 *      initialized using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::Initialise (FolioHandle     dcHandle,
                                            Gdiplus::Rect&  boundingRect,
                                            UInt32          maxNumParticles)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we initialized the particle system already?

    if (IsInitialized ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // Set random seed.
    
        Folio::Core::Util::Random::SetRandomSeed ();
    
        // Set the particle system's attributes.
    
        m_dcHandle          = dcHandle;
        m_boundingRect      = boundingRect;
        m_maxNumParticles   = maxNumParticles;
    
        // Create the particles.
    
        status = CreateParticles ();
    
        if (status == ERR_SUCCESS)
        {
            // Let our sub-class handle the initialization.
    
            status = HandleInitialize ();
    
            if (status == ERR_SUCCESS)
            {   
                // We have been initialized.
    
                m_initialized = true;
            } // Endif.
    
            else
            {
                // Log an error.
    
                FOLIO_LOG_CALL_ERROR (TXT("HandleInitialize"), 
                                      status);
            } // Endelse.
    
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to terminate the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the particle system was successfully terminated.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the particle system has not been 
 *     previously initialized using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::Terminate ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we initialized the particle system?

    if (IsInitialized ())
    {
        // Yes. Let our sub-class handle the termination.

        status = HandleTerminate ();

        if (status == ERR_SUCCESS)
        {
            // Destroy the particles.
    
            DestroyParticles ();

            // We are no longer initialized.

            m_initialized = false;
        } // Endif.
    
        else
        {
            // Log an error.
    
            FOLIO_LOG_CALL_ERROR (TXT("HandleTerminate"), 
                                  status);
        } // Endelse.

    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to update the particle system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle system, if successful. If 
 * this method fails then this parameter is undefined. May be zero if not 
 * required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the particle system has not been 
 *     previously initialized using this object.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::Update (Gdiplus::Graphics&  graphics,
                                        RectList*           rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we initialized the particle system?

    if (IsInitialized ())
    {
        // Yes. Is the particle system active?
        
        if (IsActive ())
        {
            // Yes. Let our sub-class handle the update.

            status = HandleUpdate ();
    
            if (status == ERR_SUCCESS)
            {
                // Update the particles.
    
                status = UpdateParticles (graphics, rects);

                if (status == ERR_SUCCESS)
                {
                    // Draw the particles.

                    status = DrawParticles (graphics, rects);
                } // Endif.

            } // Endif.
    
            else
            {
                // Log an error.
        
                FOLIO_LOG_CALL_ERROR (TXT("HandleUpdate"), 
                                      status);
            } // Endelse.

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
 * Method that is used to redraw the particle system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle system, if successful. If 
 * this method fails then this parameter is undefined. May be zero if not 
 * required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the particle system has not been 
 *     previously initialized using this object.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::Redraw (Gdiplus::Graphics&  graphics,
                                        RectList*           rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we initialized the particle system?

    if (IsInitialized ())
    {
        // Yes. Is the particle system active?
        
        if (IsActive ())
        {
            // Yes. Let our sub-class handle the redraw.

            status = HandleRedraw ();
    
            if (status == ERR_SUCCESS)
            {
                // Redraw the particles.

                status = RedrawParticles (graphics, rects);
            } // Endif.
    
            else
            {
                // Log an error.
        
                FOLIO_LOG_CALL_ERROR (TXT("HandleRedraw"), 
                                      status);
            } // Endelse.

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
 * Method that is used to draw the particle system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle system, if successful. If 
 * this method fails then this parameter is undefined. May be zero if not 
 * required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the particle system has not been 
 *     previously initialized using this object.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::Draw (Gdiplus::Graphics&    graphics,
                                      RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we initialized the particle system?

    if (IsInitialized ())
    {
        // Yes. Is the particle system active?
        
        if (IsActive ())
        {
            // Draw the particles.

            status = DrawParticles (graphics, rects);
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
 * Method that is used to determine if the particle system is active.
 *
 * @return
 * <b>true</b> if the particle system is active, <b>false</b> otherwise.
 */
template <typename T>
inline  bool    AParticleSystem<T>::IsActive () const
{
    // If there is at least one particle in the particle system, then the 
    // particle system is active.

    return (!m_particles.empty ());
} // Endproc.


/**
 * Method that is used to handle the initialization of the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
inline  FolioStatus AParticleSystem<T>::HandleInitialize ()
{
    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to handle the termination of the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
inline  FolioStatus AParticleSystem<T>::HandleTerminate ()
{
    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to handle the updating of the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
inline  FolioStatus AParticleSystem<T>::HandleUpdate ()
{
    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to handle the redrawing of the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
inline  FolioStatus AParticleSystem<T>::HandleRedraw ()
{
    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to create a particle in the particle system.
 *
 * @param [in, out] particle
 * On return, will hold the created particle, if successful. If this method 
 * fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
inline  FolioStatus AParticleSystem<T>::CreateParticle (AParticle<T>*& particle)
{
    // Generically we don't know how to create a particle.

    return (ERR_PROGRAMMING_LOGIC);

    FOLIO_UNREFERENCED(particle);
} // Endproc.


/**
 * Method that is used to create the particles in the particle system.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
inline  FolioStatus AParticleSystem<T>::CreateParticles ()
{
    // Generically we don't know how to create particles.

    return (ERR_PROGRAMMING_LOGIC);
} // Endproc.


/**
 * Method that is used to destroy the particles in the particle system.
 */
template <typename T>
void    AParticleSystem<T>::DestroyParticles ()
{
    // Destroy the particles in the particle system.

    ParticleList::iterator  itrEnd = m_particles.end ();

    for (ParticleList::iterator itr = m_particles.begin ();
         itr != itrEnd;
         ++itr)
    {
        // Destroy the particle.

        delete *itr;
    } // Endfor.

    m_particles.clear ();   // All gone!
} // Endproc.


/**
 * Method that is used to update the particles in the particle system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particles in the particle system, if 
 * successful. If this method fails then this parameter is undefined. May be 
 * zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::UpdateParticles (Gdiplus::Graphics& graphics,
                                                 RectList*          rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the particle system still active?

    if (IsActive ())
    {
        // Begin the update of the particles in the particle system.

        status = BeginUpdateParticles (graphics, rects);

        if (status == ERR_SUCCESS)
        {
            // End the update of the particles in the particle system.

            status = EndUpdateParticles (graphics);
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_NOT_ACTIVE;
    } // Endelse.

    return (status);
} // Endproc.
    

/**
 * Method that is used to begin the update of the particles in the particle 
 * system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particles in the particle system, if 
 * successful. If this method fails then this parameter is undefined. May be 
 * zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::BeginUpdateParticles (Gdiplus::Graphics&    graphics,
                                                      RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Begin the update of the particles in the particle system.

    ParticleList::iterator  itrEnd  = m_particles.end ();
    ParticleList::iterator  itr     = m_particles.begin ();

    while ((status == ERR_SUCCESS) && (itr != itrEnd))
    {
        // Begin the update of the particle. 

        status = (*itr)->BeginUpdate (graphics, rects);

        switch (status)
        {
        case ERR_SUCCESS:
            ++itr;  // Next particle.
            break;

        case ERR_NOT_ACTIVE:
            // The particle is dead. Should we create a new particle?

            if (m_recreateParticles)
            {
                // Yes. Create a new particle.

                typename AParticle<T>*  particle = 0;    // Initialise!

                status = CreateParticle (particle);

                if (status == ERR_SUCCESS)
                {
                     // Destroy the dead particle.

                    delete *itr;

                    // Store the new particle.

                    *itr = particle;
                } // Endif.

                else
                {
                    // Failed to create a new particle, remove the dead 
                    // particle from the particle system.

                    itr = m_particles.erase (itr);

                    itrEnd = m_particles.end ();

                    status = ERR_SUCCESS;
                } // Endelse.

            } // Endif.

            else
            {
                // No. Remove the particle from the particle system.

                itr = m_particles.erase (itr);

                itrEnd = m_particles.end ();

                status = ERR_SUCCESS;
            } // Endelse.
            break;

        default:
            // Log an error.

            FOLIO_LOG_CALL_ERROR (TXT("BeginUpdate"), 
                                  status);
            break;
        } // Endswitch.

    } // Endwhile.

    return (status);
} // Endproc.
    

/**
 * Method that is used to end the update of the particles in the particle 
 * system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::EndUpdateParticles (Gdiplus::Graphics&  graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the particle system still active?

    if (IsActive ())
    {
        // End the update of the particles in the particle system.
    
        ParticleList::iterator  itrEnd  = m_particles.end ();

        for (ParticleList::iterator itr = m_particles.begin ();
             (status == ERR_SUCCESS) && (itr != itrEnd);
             ++itr)
        {
            // End the update of the particle.
    
            status = (*itr)->EndUpdate (graphics);
        } // Endfor.

    } // Endif.

    else
    {
        status = ERR_NOT_ACTIVE;
    } // Endelse.

    return (status);
} // Endproc.
    

/**
 * Method that is used to redraw the particles in the particle system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle system, if successful. If 
 * this method fails then this parameter is undefined. May be zero if not 
 * required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::RedrawParticles (Gdiplus::Graphics& graphics,
                                                 RectList*          rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the particle system still active?

    if (IsActive ())
    {
        // Begin the redraw of the particles in the particle system.

        status = BeginRedrawParticles (graphics, rects);

        if (status == ERR_SUCCESS)
        {
            // End the redraw of the particles in the particle system.

            status = EndRedrawParticles (graphics);
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_NOT_ACTIVE;
    } // Endelse.

    return (status);
} // Endproc.
    

/**
 * Method that is used to begin the redraw of the particles in the particle 
 * system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particles in the particle system, if 
 * successful. If this method fails then this parameter is undefined. May be 
 * zero if not required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::BeginRedrawParticles (Gdiplus::Graphics&    graphics,
                                                      RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Begin the redraw of the particles in the particle system.

    ParticleList::iterator  itrEnd  = m_particles.end ();

    for (ParticleList::iterator itr = m_particles.begin ();
         (status == ERR_SUCCESS) && (itr != itrEnd);
         ++itr)
    {
        // Begin the redraw of the particle.

        status = (*itr)->BeginRedraw (graphics, rects);
    } // Endfor.

    return (status);
} // Endproc.
    

/**
 * Method that is used to end the redraw of the particles in the particle 
 * system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_NOT_ACTIVE</b> if all the particles in the particle system are 
 *     dead, and so the partice system is inactive.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::EndRedrawParticles (Gdiplus::Graphics&  graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // End the redraw of the particles in the particle system.

    ParticleList::iterator  itrEnd  = m_particles.end ();

    for (ParticleList::iterator itr = m_particles.begin ();
         (status == ERR_SUCCESS) && (itr != itrEnd);
         ++itr)
    {
        // End the redraw of the particle.

        status = (*itr)->EndRedraw (graphics);
    } // Endfor.

    return (status);
} // Endproc.


/**
 * Method that is used to draw the particles in the particle system.
 *
 * @param [in, out] graphics
 * The graphics object to draw to.
 *
 * @param [out] rects
 * On return, will hold the rects of the particle system, if successful. If 
 * this method fails then this parameter is undefined. May be zero if not 
 * required.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
template <typename T>
FolioStatus AParticleSystem<T>::DrawParticles (Gdiplus::Graphics&   graphics,
                                               RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Draw the particles in the particle system.

    ParticleList::iterator  itrEnd = m_particles.end ();

    for (ParticleList::iterator itr = m_particles.begin ();
         (status == ERR_SUCCESS) && (itr != itrEnd);
         ++itr)
    {
        // Draw the particle. 

        status = (*itr)->Draw (graphics, rects);

        if (status != ERR_SUCCESS)
        {
            // Log an error.

            FOLIO_LOG_CALL_ERROR (TXT("Draw"), 
                                  status);
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


/**
 * Method that is used to determine if the particle system has been initialized.
 *
 * @return
 * <b>true</b> if the particle system has been initialized, <b>false</b> 
 * otherwise.
 */
template <typename T>
inline  bool    AParticleSystem<T>::IsInitialized () const
{
    return (m_initialized);
} // Endproc.


/// 2D particle system.
typedef AParticleSystem<Vector2>    AParticleSystem2;


/// 3D particle system.
typedef AParticleSystem<Vector3>    AParticleSystem3;

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
