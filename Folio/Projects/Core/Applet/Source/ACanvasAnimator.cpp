// "Home-made" includes.
#include    <Trace.h>
#include    "ACanvasAnimator.h"

namespace Folio
{

namespace Core
{
                                  
namespace Applet
{

using   namespace   Folio::Core::Util;

/**
 * The default class constructor.
 */
ACanvasAnimator::ACanvasAnimator ()
:   m_canvasMsgHandler(0)
{
} // Endproc.


/**
 * The class destructor.
 */
ACanvasAnimator::~ACanvasAnimator ()
{
    Destroy ();
} // Endproc.


/**
 * Method that is used to create the animator.
 *
 * @param [in] canvasMsgHandler
 * The canvas message handler.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an animator has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::Create (ACanvasMsgHandler& canvasMsgHandler)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we already created an animator? 

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Note the animator attributes.

        m_canvasMsgHandler = &(canvasMsgHandler);

        // Start the animator thread.

        status = StartThread ();
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to destroy the animator.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an animator has not been previously 
 *     created using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::Destroy ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created an animator? 

    if (IsCreated ())
    {
        // Yes. Stop the animator thread.

        status = StopThread ();
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to reanimate the animator.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if an animator has been previously created using 
 *     this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::Reanimate ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created an animator? 

    if (IsCreated ())
    {
        // Yes. Let our subclass redraw the animation.
    
        FolioStatus status = RedrawAnimation ();
    
        if (status != ERR_SUCCESS)
        {
            // Log the error.
    
            FOLIO_LOG_CALL_ERROR (TXT("RedrawAnimation"),
                                  status);
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to get the animator animation timeout.
 *
 * @return
 * The animator animation timeout.
 */
UInt32  ACanvasAnimator::GetAnimationTimeout () const
{
    return (DEFAULT_ANIMATION_TIMEOUT);
} // Endproc.


/**
 * Method that is used to determine if the animator has been created.
 *
 * @return
 * <b>true</b> if the animator has been created, <b>false</b> otherwise.
 */
bool    ACanvasAnimator::IsCreated () const
{
    // If the animator thread is running, then the animator has been created.

    return (m_thread.IsRunning ());
} // Endproc.


/**
 * Method that will start the animator thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERROR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::StartThread ()
{
    // Create the animator thread initialized pulse (unset).

    FolioStatus status = m_threadInitializedPulse.Create ();

    if (status == ERR_SUCCESS)
    {
        // Create the animator thread exit pulse (unset).

        status = m_exitThreadPulse.Create ();

        if (status == ERR_SUCCESS)
        {
            // Start the animator thread.

            status = m_thread.Start (reinterpret_cast<Thread::ThreadCallback> (ThreadEntry),
                                     this); // Pass in this object.

            if (status == ERR_SUCCESS)
            {
                // Wait a finite time for the animator thread to initialize.

                status = m_threadInitializedPulse.Wait (FOLIO_FINITE);
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will stop the animator thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERROR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::StopThread ()
{
    // Signal the animator thread to exit.

    FolioStatus status = m_exitThreadPulse.Set ();

    if (status == ERR_SUCCESS)
    {
        // Wait a finite time for the animator thread to exit.

        m_thread.Wait (FOLIO_FINITE);
    } // Endif.

    return (status);
} // Endproc.


/**
 * The entry point of the animator thread.
 *
 * @param [in] args
 * Pointer to the <i>ACanvasAnimator</i> object that created the thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERROR_SUCCESS</b> if successful.
 * <li><b>ERR_INTERNAL_ERROR</b> if there is no <b>ACanvasAnimator</b> object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus FOLIO_CALL  ACanvasAnimator::ThreadEntry (void* args)
{
    FolioStatus status = ERROR_SUCCESS;

    // Set our thread name.
                                            
    ProcessInfo::SetThreadName (ProcessInfo::GetCurrentThreadId (), "ACanvasAnimator Thread");

    // Pick up the animator object.

    ACanvasAnimator*   animator = reinterpret_cast<ACanvasAnimator*> (args);

    // Do we have a valid object?

    if (animator)
    {
        // Yes. Initialise the animator thread.

        status = animator->ThreadInitialize ();

        if (status == ERR_SUCCESS)
        {
            // Let's go.

            status = animator->Thread ();
        } // Endif.

        // Terminate the animator thread.

        animator->ThreadTerminate ();
    } // Endif.

    else
    {
        // No. Something bad has happened.

        status = ERR_INTERNAL_ERROR;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that will initialize the animator thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERROR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::ThreadInitialize ()
{
    // Let our subclass initialize the animation.

    FolioStatus status = InitializeAnimation ();

    if (status != ERR_SUCCESS)
    {
        // Log the error.
    
        FOLIO_LOG_CALL_ERROR (TXT("InitializeAnimation"),
                              status);
    } // Endif.

    // Irrespective of success or failure, we must signal that we have 
    // initialized.

    m_threadInitializedPulse.Set ();

    return (status);
} // Endproc.


/**
 * Method that will terminate the animator thread.
 */
void    ACanvasAnimator::ThreadTerminate ()
{
    // Let our subclass terminate the animation.

    FolioStatus status = TerminateAnimation ();

    if (status != ERR_SUCCESS)
    {
        // Log the error.
    
        FOLIO_LOG_CALL_ERROR (TXT("TerminateAnimation"),
                              status);
    } // Endif.

} // Endproc.


/**
 * This method is THE animator thread.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERROR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::Thread ()
{
    FolioStatus status = ERR_SUCCESS;

    // Loop until we are told to exit.

    bool    exit = false;   // Initialise!

    do
    {
        // Wait a finite time on exit.

        status = m_exitThreadPulse.Wait (GetAnimationTimeout ());

        switch (status)
        {
        case ERR_TIMEOUT:
            // Animate.

            exit = Animate ();
            break;

        default:
            // Get-outta-here.

            exit = true;
            break;
        } // Endswitch.

    } // Enddo.
    while (!exit);

    return (status);
} // Endproc.


/**
 * Method that is used to animate.
 *
 * @return
 * <<b>true</b> if the animator thread should exit, <b>false</b> otherwise.
 */
bool    ACanvasAnimator::Animate ()
{
    // Let our subclass perform the animation.

    bool    stopAnimation = false;  // Initialise!

    FolioStatus status = PerformAnimation (stopAnimation);

    if (status != ERR_SUCCESS)
    {
        // Log the error.

        FOLIO_LOG_CALL_ERROR (TXT("PerformAnimation"),
                              status);
    } // Endif.

    return (stopAnimation || (status != ERR_SUCCESS));
} // Endproc.


#ifdef  FOLIO_DOXYGEN

/**
 * Method that is used to begin the animation.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::InitializeAnimation () = 0;


/**
 * Method that is used to perform the animation.
 *
 * @param [out] stopAnimation
 * On return, will indicate if the animation should be stopped, if successful. 
 * If this method fails then this parameter is undefined.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the animation has already stopped.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::PerformAnimation (bool& stopAnimation) = 0;


/**
 * Method that is used to redraw the animation.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if the animation has stopped.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus ACanvasAnimator::RedrawAnimation () = 0;

#endif

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
