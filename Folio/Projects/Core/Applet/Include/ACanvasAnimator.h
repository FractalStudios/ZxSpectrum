#pragma once

// "Home-made" includes.
#include    <Util.h>
#include    "ACanvasMsgHandler.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

/// The canvas animator abstract class.
/**
 * This class provides for an animator. It is used to animate drawing elements 
 * held within a canvas.
 *
 * This class does not support copy construction or assignment.
 */
class ACanvasAnimator
{
public:
    virtual ~ACanvasAnimator ();

    FolioStatus Create (ACanvasMsgHandler& canvasMsgHandler);
    FolioStatus Destroy ();
    FolioStatus Reanimate ();

protected:
    ACanvasMsgHandler*  m_canvasMsgHandler;    ///< The canvas message handle.

    ACanvasAnimator ();

    virtual FolioStatus InitializeAnimation () = 0;
    virtual FolioStatus TerminateAnimation () = 0;
    virtual FolioStatus PerformAnimation (bool& stopAnimation) = 0;
    virtual FolioStatus RedrawAnimation () = 0;

    virtual UInt32  GetAnimationTimeout () const;

private:
    static  const   UInt32  DEFAULT_ANIMATION_TIMEOUT   = 10;   ///< The default animation timeout.

    Folio::Core::Util::Thread   m_thread;                   ///< The animator thread.
    Folio::Core::Util::Pulse    m_threadInitializedPulse;   ///< The (instance) pulse that the animator thread has initialized.
    Folio::Core::Util::Pulse    m_exitThreadPulse;          ///< The (instance) pulse that the animator thread should exit.

    bool    IsCreated () const;

    FolioStatus StartThread ();
    FolioStatus StopThread ();

    static  FolioStatus FOLIO_CALL  ThreadEntry (void* args);

    FolioStatus ThreadInitialize ();
    void        ThreadTerminate ();
    FolioStatus Thread ();

    bool    Animate ();

    /// Private copy constructor to prevent copying.
    ACanvasAnimator (const ACanvasAnimator& rhs);

    /// Private assignment operator to prevent copying.
    ACanvasAnimator& operator= (const ACanvasAnimator& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
