// "Home-made" includes.
#include    <Trace.h>
#include    "AppletConstsAndTypes.h"
#include    "AppletWnd.h"

namespace Folio
{

namespace Core
{

namespace Applet
{

using   namespace   Folio::Core::Util;

// Define the class's statics.
const   FolioCString    AppletWnd::APPLET_WND_CLASS_NAME    = TXT("FolioAppletWndClass");   ///< The name of the applet window class.
const   FolioCString    AppletWnd::APPLET_WND_NAME          = TXT("FolioAppletWnd");        ///< The name of the applet window.

/**
 * The default class constructor.
 */
AppletWnd::AppletWnd ()
:   m_instanceHandle(FOLIO_INVALID_HANDLE),
    m_wndHandle(FOLIO_INVALID_HANDLE),
    m_wndDCHandle(FOLIO_INVALID_HANDLE),
    m_gdiHandle(FOLIO_INVALID_HANDLE),
    m_appletWndReady(false)
{
} // Endproc.


/**
 * The class destructor.
 */
AppletWnd::~AppletWnd ()
{
} // Endproc.


/**
 * Method that is used to process the applet.
 *
 * @param [in] instanceHandle
 * The application instance handle.
 *
 * @param [in] commandLine
 * The application command line.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::Process (FolioHandle         instanceHandle,
                                const FolioString&  commandLine)
{
    FolioStatus status = ERR_SUCCESS;

    m_instanceHandle    = instanceHandle;
    m_commandLine       = commandLine;

    // Initialise the applet.

    status = Initialise ();

    if (status == ERR_SUCCESS)
    {
        // Get the first connected controller.

        Folio::Core::Game::Gamepad::CONTROLLER_ID   controllerId = m_gamepad->GetFirstConnectedController ();

        static  const   UInt32  FRAMES_PER_SECOND   = 50;
        static  const   UInt32  TICK_COUNT_DELTA    = (1000 / FRAMES_PER_SECOND);

        MSG msg = {0};  // Initialise!

        UInt32  currentTickCount    = 0;    // Initialise!
        UInt32  previousTickCount   = 0;

        UInt32  frameRateIncrement = 0; // Initialise!

        do 
        {
            Thread::Sleep (frameRateIncrement); // Pause.

            do
            {
                // Peek for a message to any window.

                status = Wnd::PeekWndMessage (0, 0, 0, PM_REMOVE, msg);
                
                switch (status)
                {
                case ERR_SUCCESS: 
                    Wnd::TranslateWndMessage (msg);
                    Wnd::DispatchWndMessage (msg);
                    break;

                case ERR_NO_MSG: 
                case ERR_STOPPED: 
                default:
                    break;
                } // Endswitch.

                // Get current tick count.

                currentTickCount = DateTime::GetCurrentTickCount ();

                if (!previousTickCount) 
                {
                    previousTickCount = currentTickCount;
                } // Endif.

            } // Enddo.
            while ((status != ERR_STOPPED) && 
                   ((currentTickCount - previousTickCount) < TICK_COUNT_DELTA));

            if (status != ERR_STOPPED)
            {
                // Note previous frame tick count.

                previousTickCount = currentTickCount;
            
                // Check gamepad.

                if (m_gamepad)
                {
                    m_gamepad->CheckController (controllerId);
                } // Endif.

                // Process a frame.

                frameRateIncrement = 0; // Reset.

                status = HandleProcessFrame (static_cast<HWND> (m_wndHandle), frameRateIncrement);
            } // Endif.

        } // Enddo.
        while (status != ERR_STOPPED); 

        status = ERR_SUCCESS;
    } // Endif.

    // Terminate the applet.

    Terminate ();

    return (status);
} // Endproc.


/**
 * Method that is used to get the applet instance handle.
 *
 * @return
 * The applet instance handle.
 */
FolioHandle AppletWnd::GetAppletInstanceHandle () const
{
    return (m_instanceHandle);
} // Endproc.


/**
 * Method that is used to get the applet window handle.
 *
 * @return
 * The applet window handle.
 */
FolioHandle AppletWnd::GetAppletWndHandle () const
{
    return (m_wndHandle);
} // Endproc.


/**
 * Method that is used to get the applet window device context handle.
 *
 * @return
 * The applet window device context handle.
 */
FolioHandle AppletWnd::GetAppletWndDCHandle () const
{
    return (m_wndDCHandle);
} // Endproc.


/**
 * Method that is used to get the applet window rect.
 *
 * @return
 * The applet window rect.
 */
Gdiplus::Rect   AppletWnd::GetAppletWndRect () const
{
    // The applet window rect is the client rect.

    RECT    clientRect;
    Wnd::QueryClientRect (m_wndHandle, clientRect);

    return (Gdiplus::Rect(clientRect.left, 
                          clientRect.top, 
                          clientRect.right - clientRect.left, 
                          clientRect.bottom - clientRect.top));
} // Endproc.


/**
 * Method that is used to get the applet window background colour.
 *
 * @return
 * The applet window background colour.
 */
Gdiplus::Color  AppletWnd::GetAppletWndBackgroundColour () const
{
    return (Gdiplus::Color (APPLET_WND_BACKGROUND_COLOUR));
} // Endproc.


/**
 * Method that is used to get the applet window graphics object.
 *
 * @return
 * The applet window graphics object.
 */
Gdiplus::Graphics*  AppletWnd::GetAppletWndGraphics () const
{
    return (m_graphics.get ());
} // Endproc.


/**
 * Method that is used to get the applet window gamepad object.
 *
 * @return
 * The applet window ggamepad object.
 */
Folio::Core::Game::Gamepad*  AppletWnd::GetAppletWndGamepad () const
{
    return (m_gamepad.get ());
} // Endproc.


/**
 * Method that is used to set the applet window ready.
 */
void    AppletWnd::SetReady ()
{
    m_appletWndReady = true;
} // Endproc.


/**
 * Method that is used to initialize the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the applet window was successfully initialized.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::Initialise ()
{
    FolioStatus status = ERR_SUCCESS;

#ifndef _DEBUG
    Folio::Core::Util::Wnd::ShowCursor (false);
#endif

    // Register with GDI+.

    status = RegisterGraphics ();

    if (status == ERR_SUCCESS)
    {
        // Register the applet window class.

        status = RegisterAppletWndClass ();

        if (status == ERR_SUCCESS)
        {
            // Create the applet window.

            status = CreateAppletWnd ();
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_INTERNAL_ERROR;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to terminate the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the applet window was successfully terminated.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::Terminate()
{
    // Deregister the applet window class.

    DeregisterAppletWndClass ();

    // Deregister from GDI+.

    DeregisterGraphics ();

    Folio::Core::Util::Wnd::ShowCursor (true);

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to register with the GDI+ subsystem.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successfull.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::RegisterGraphics ()
{
    // Register with GDI+.

    return (Folio::Core::Graphic::Gdi::RegisterGdi (m_gdiHandle));
} // Endproc.


/**
 * Method that is used to deregister from the GDI+ subsystem.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successfull.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::DeregisterGraphics ()
{
    // Deregister from GDI+.

    return (Folio::Core::Graphic::Gdi::DeregisterGdi (m_gdiHandle));
} // Endproc.


/**
 * Method that will register the applet window class.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the applet window class was successfully 
 *     registered.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::RegisterAppletWndClass () const
{
    // Fill in the window class structure with parameters that describe
    // the applet window.

    WNDCLASSEX  wndClassEx;
    ::memset (&(wndClassEx), 0, sizeof (wndClassEx));

    wndClassEx.cbSize        = sizeof (wndClassEx);
    wndClassEx.style         = 0;
    wndClassEx.lpfnWndProc   = AppletWndProc;
    wndClassEx.cbClsExtra    = 0;
    wndClassEx.cbWndExtra    = sizeof (AppletWnd);   // We will put a pointer to the object in here.
    wndClassEx.hInstance     = reinterpret_cast<HINSTANCE> (m_instanceHandle);
    wndClassEx.hIcon         = 0;
    wndClassEx.hCursor       = ::LoadCursor (0, IDC_ARROW);
    wndClassEx.hbrBackground = ::CreateSolidBrush (ARGB_TO_RGB(APPLET_WND_BACKGROUND_COLOUR));
    wndClassEx.lpszMenuName  = 0;
    wndClassEx.lpszClassName = APPLET_WND_CLASS_NAME;
    wndClassEx.hIconSm       = 0;

    // Register the applet window class.

    FolioStatus status = Wnd::RegisterWndClass (wndClassEx);

    // If the applet window class already existed, then this is okay.

    if (status == ERR_ALREADY_EXISTS)
    {
        status = ERR_SUCCESS;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will deregister the applet window class.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the applet window class was successfully 
 *     deregistered.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::DeregisterAppletWndClass () const
{
    // Deregister the applet window class.

    FolioStatus status = Wnd::DeregisterWndClass (APPLET_WND_CLASS_NAME,
                                                  m_instanceHandle);

    // If the applet window class is in use, then this is okay.

    if (status == ERR_IN_USE)
    {
        status = ERR_SUCCESS;
    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that will create the applet window.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if the applet window class was successfully 
 *     created.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::CreateAppletWnd ()
{
    // Calculate the position of the applet window. We position in the middle
    // of the desktop.

    // As we support an overlapped window our total width and height includes its 
    // size frame border. The height also includes a title bar.

    UInt32  width   = APPLET_WND_WIDTH  + 4 * ::GetSystemMetrics (SM_CXSIZEFRAME);
    UInt32  height  = APPLET_WND_HEIGHT + 4 * ::GetSystemMetrics (SM_CYSIZEFRAME) + ::GetSystemMetrics (SM_CYSIZE) + 1;

    UInt32  xPos    = (::GetSystemMetrics (SM_CXFULLSCREEN) - width) / 2;
    UInt32  yPos    = (::GetSystemMetrics (SM_CYFULLSCREEN) - height) / 2;
    
    // Create the applet window.

    FolioStatus status = Wnd::CreateWnd (APPLET_WND_CLASS_NAME,
                                         APPLET_WND_NAME,
                                         WS_VISIBLE | WS_OVERLAPPEDWINDOW,
                                         0,
                                         xPos,
                                         yPos,
                                         width,
                                         height,
                                         m_instanceHandle,
                                         this,
                                         m_wndHandle);

    if (status == ERR_SUCCESS)
    {
        // Show the applet window.

        Wnd::ShowWnd (m_wndHandle, SW_NORMAL);
        Wnd::UpdateWnd (m_wndHandle);
    } // Endif.

    return (status);        
} // Endproc.


/**
 * Method that is used to create the canvas message handler.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::CreateCanvasMsgHandler ()
{
    m_canvasMsgHandler.reset (Folio::Core::Applet::CreateCanvasMsgHandler ());

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to destroy the canvas message handler.
 */
void    AppletWnd::DestroyCanvasMsgHandler ()
{
    m_canvasMsgHandler.reset ();
} // Endproc.


/**
 * Method that is used to get the canvas message handler.
 *
 * @return
 * The canvas message handler.
 */
ACanvasMsgHandler*  AppletWnd::GetCanvasMsgHandler ()
{
    return (m_canvasMsgHandler.get ());
} // Endproc.


/**
 * Method that is used to indicate if the canvas message handler has been 
 * created.
 * 
 * @return
 * <b>true</b> if the canvas message handler has been created, <b>false</b> 
 * otherwise.
 */
bool    AppletWnd::IsCanvasMsgHandler () const
{
    return (m_canvasMsgHandler.get () != 0);
} // Endproc.


/**
 * Method that is used to create the graphics object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::CreateGraphics ()
{
    m_graphics.reset (new Gdiplus::Graphics(reinterpret_cast<HWND> (m_wndHandle)));

    return (Folio::Core::Graphic::Gdi::InitializeGraphics (*m_graphics.get ()));
} // Endproc.


/**
 * Method that is used to destroy the graphics object.
 */
void    AppletWnd::DestroyGraphics ()
{
    m_graphics.reset ();
} // Endproc.


/**
 * Method that is used to indicate if the graphics object has been created.
 * 
 * @return
 * <b>true</b> if the graphics object has been created, <b>false</b> otherwise.
 */
bool    AppletWnd::IsGraphics () const
{
    return (m_graphics.get () != 0);
} // Endproc.


/**
 * Method that is used to create the gamepad object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::CreateGamepad ()
{
    m_gamepad.reset (new Folio::Core::Game::Gamepad(m_wndHandle));

    return (ERR_SUCCESS);
} // Endproc.


/**
 * Method that is used to destroy the gamepad object.
 */
void    AppletWnd::DestroyGamepad ()
{
    m_gamepad.reset ();
} // Endproc.


/**
 * Method that is used to indicate if the gamepad object has been created.
 * 
 * @return
 * <b>true</b> if the gamepad object has been created, <b>false</b> otherwise.
 */
bool    AppletWnd::IsGamepad () const
{
    return (m_gamepad.get () != 0);
} // Endproc.


/**
 * Method that is used process a frame in the applet window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [out] frameRateIncrement
 * The frame rate increment.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::HandleProcessFrame (HWND     wndHandle,
                                           UInt32&  frameRateIncrement)
{
    FolioStatus status = ERR_SUCCESS;

    if (m_appletWndReady && m_canvasMsgHandler)
    {
        // Let the canvas message handler process a frame.

        status = m_canvasMsgHandler->HandleProcessFrame (wndHandle, frameRateIncrement);

        if (status != ERR_SUCCESS)
        {
            FOLIO_LOG_CALL_ERROR_2 (TXT("HandleProcessFrame"),
                                    status,
                                    wndHandle,
                                    frameRateIncrement);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to set the applet window object into the applet 
 * window's extra data.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] appletWnd
 * The applet window object.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successfull.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::SetAppletWnd (HWND       wndHandle,
                                     AppletWnd* appletWnd)
{
    // Store the applet window object in the applet window's extra data.

    return (Wnd::SetWndData (wndHandle,
                             APPLET_WND_OBJECT_INDEX,
                             appletWnd));
} // Endproc.


/**
 * Method that is used to get the applet window object from the applet 
 * window's extra data.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @return
 * The applet window object.
 */
AppletWnd*  AppletWnd::GetAppletWnd (HWND wndHandle)
{
    // Obtain the applet window object from the applet window's extra data.

    AppletWnd*  appletWnd = 0;  // Initialise!

    Wnd::QueryWndData (wndHandle,
                       APPLET_WND_OBJECT_INDEX,
                       reinterpret_cast<void*&> (appletWnd));

    return (appletWnd);
} // Endproc.


/**
 * The applet window procedure.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] msg
 * The message sent to the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The result of processing the message.
 */
LRESULT CALLBACK    AppletWnd::AppletWndProc (HWND      wndHandle,
                                              UINT      msg,
                                              WPARAM    wParam,
                                              LPARAM    lParam)
{
    // Switch on the message received.

    switch (msg)
    {
    case WM_CREATE:
        if (HandleCreateWndMsg (wndHandle, wParam, lParam) != ERR_SUCCESS)
        {
            return (-1);    // Fail the window creation.
        } // Endif.
        break;

    case WM_DESTROY:
        HandleDestroyWndMsg (wndHandle, wParam, lParam);
        break;

    case WM_SIZE:
		HandleSizeMsg (wndHandle, wParam, lParam);
        break;

    case WM_PAINT:
        HandlePaintWndMsg (wndHandle, wParam, lParam);
        break;

    default:
        break;
    } // Endswitch.

    return (DefWindowProc (wndHandle, msg, wParam, lParam));
} // Endproc.


/**
 * Method that is used to handle a WM_CREATE message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::HandleCreateWndMsg (HWND     wndHandle,
                                           WPARAM   wParam,
                                           LPARAM   lParam)
{
    // lParam holds details about the window created. We want the creation 
    // parameters - that is the pointer to the object that created the window.

    AppletWnd*  appletWnd = 
        reinterpret_cast<AppletWnd*> ((reinterpret_cast<LPCREATESTRUCT> (lParam))->lpCreateParams);

    // Store the applet window object in the window's extra data.

    FolioStatus status = SetAppletWnd (wndHandle, appletWnd);

    if (status == ERR_SUCCESS)
    {
        appletWnd->m_wndHandle = wndHandle;    // Note the applet window handle.

        // Get the applet window device context.

        appletWnd->m_wndDCHandle = ::GetDC (wndHandle);

        // Create the graphics object.

        status = appletWnd->CreateGraphics ();

        if (status == ERR_SUCCESS)
        {
            // Create the gamepad object.

            status = appletWnd->CreateGamepad ();

            if (status == ERR_SUCCESS)
            {
                // Create the canvas message handler.
            
                status = appletWnd->CreateCanvasMsgHandler ();

                if (status == ERR_SUCCESS)
                {
                    // Let the canvas message handler deal with the message.

                    status = appletWnd->GetCanvasMsgHandler ()->HandleCreateCanvasMsg (wndHandle, 
                                                                                       wParam, 
                                                                                       lParam);

                    if (status == ERR_SUCCESS)
                    {
                        appletWnd->SetReady ();
                    } // Endif.

                    else
                    {
                        FOLIO_LOG_CALL_ERROR_3 (TXT("HandleCreateCanvasMsg"),
                                                status,
                                                wndHandle, 
                                                wParam, 
                                                lParam);
                    } // Endelse.

                } // Endif.

            } // Endif.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


/**
 * Method that is used to handle a WM_DESTROY message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::HandleDestroyWndMsg (HWND    wndHandle,
                                            WPARAM  wParam,
                                            LPARAM  lParam)
{
    FolioStatus status = ERR_SUCCESS;

    // Obtain the applet window object from the window's extra data.

    AppletWnd*  appletWnd = GetAppletWnd (wndHandle);

    if (appletWnd == 0)
    {
        status = ERR_INTERNAL_ERROR;
    } // Endif.

    else
    {
        // Get the canvas message handler.

        ACanvasMsgHandler*  canvasMsgHandler = appletWnd->GetCanvasMsgHandler ();

        if (canvasMsgHandler == 0)
        {
            status = ERR_INTERNAL_ERROR;
        } // Endif.

        else
        {
            // Let the canvas message handler deal with the message.

            status = canvasMsgHandler->HandleDestroyCanvasMsg (wndHandle, 
                                                               wParam, 
                                                               lParam);

            if (status != ERR_SUCCESS)
            {
                FOLIO_LOG_CALL_ERROR_3 (TXT("HandleDestroyCanvasMsg"),
                                        status,
                                        wndHandle, 
                                        wParam, 
                                        lParam);
            } // Endif.

        } // Endelse.

        // Destroy the canvas message handler.

        appletWnd->DestroyCanvasMsgHandler ();

        // Destroy the gamepad.

        appletWnd->DestroyGamepad ();

        // Destroy the graphics.

        appletWnd->DestroyGraphics ();

        // Release the applet window device context.

        ::ReleaseDC (wndHandle, reinterpret_cast<HDC> (appletWnd->m_wndDCHandle));
    } // Endelse.

    // Always quit.

    ::PostQuitMessage (ERR_SUCCESS);

    return (status);
} // Endproc.


/**
 * Method that is used to handle a WM_SIZE message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::HandleSizeMsg (HWND      wndHandle,
                                      WPARAM    wParam,
                                      LPARAM    lParam)
{
    FolioStatus status = ERR_SUCCESS;

    // Obtain the applet window object from the window's extra data.

    AppletWnd*  appletWnd = GetAppletWnd (wndHandle);

    if (appletWnd == 0)
    {
        status = ERR_INTERNAL_ERROR;
    } // Endif.

    else
    {
        // Get the canvas message handler.

        ACanvasMsgHandler*  canvasMsgHandler = appletWnd->GetCanvasMsgHandler ();

        if (canvasMsgHandler == 0)
        {
            status = ERR_INTERNAL_ERROR;
        } // Endif.

        else
        {
            // Let the canvas message handler deal with the message.

            status = canvasMsgHandler->HandleSizeMsg (wndHandle, 
                                                      wParam, 
                                                      lParam);

            if (status != ERR_SUCCESS)
            {
                FOLIO_LOG_CALL_ERROR_3 (TXT("HandleSizeMsg"),
                                        status,
                                        wndHandle, 
                                        wParam, 
                                        lParam);
            } // Endif.

        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to handle a WM_PAINT message received by the applet 
 * window.
 *
 * @param [in] wndHandle
 * The handle of the applet window.
 *
 * @param [in] wParam
 * Contains additional data relevant to the message.
 *
 * @param [in] lParam
 * Contains additional data relevant to the message.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus AppletWnd::HandlePaintWndMsg (HWND      wndHandle,
                                          WPARAM    wParam,
                                          LPARAM    lParam)
{
    FolioStatus status = ERR_SUCCESS;

    // Obtain the applet window object from the window's extra data.

    AppletWnd*  appletWnd = GetAppletWnd (wndHandle);

    if (appletWnd == 0)
    {
        status = ERR_INTERNAL_ERROR;
    } // Endif.

    else
    {
        // Get the canvas message handler.

        ACanvasMsgHandler*  canvasMsgHandler = appletWnd->GetCanvasMsgHandler ();

        if (canvasMsgHandler == 0)
        {
            status = ERR_INTERNAL_ERROR;
        } // Endif.

        else
        {
            // Let the canvas message handler deal with the message.

            status = canvasMsgHandler->HandlePaintCanvasMsg (wndHandle, 
                                                             wParam, 
                                                             lParam);

            if (status != ERR_SUCCESS)
            {
                FOLIO_LOG_CALL_ERROR_3 (TXT("HandlePaintCanvasMsg"),
                                        status,
                                        wndHandle, 
                                        wParam, 
                                        lParam);
            } // Endif.

        } // Endelse.

    } // Endelse.

    return (status);
} // Endproc.

}  // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
