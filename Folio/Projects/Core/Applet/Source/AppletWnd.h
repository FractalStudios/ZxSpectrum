#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    <Util.h>
#include    <Graphic.h>
#include    "ACanvasMsgHandler.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

/// The applet window class.
/**
 * This class provides for an applet window.
 *
 * This class does not support copy construction or assignment.
 */
class AppletWnd : public Folio::Core::Util::ProcessSingleton<AppletWnd>
{
public:    
    ~AppletWnd ();

    FolioStatus Process (FolioHandle        instanceHandle,
                         const FolioString& commandLine);

    FolioHandle     GetAppletInstanceHandle () const;
    FolioHandle     GetAppletWndHandle () const;
    FolioHandle     GetAppletWndDCHandle () const;
    Gdiplus::Rect   GetAppletWndRect () const;
    Gdiplus::Color  GetAppletWndBackgroundColour () const;

    Gdiplus::Graphics*          GetAppletWndGraphics () const;
    Folio::Core::Game::Gamepad* GetAppletWndGamepad () const;

    void    SetReady ();

protected:    
    // As this is a process singleton, don't allow direct construction.

    AppletWnd ();

private:
    static  const   FolioCString    APPLET_WND_CLASS_NAME;  ///< The name of the applet window class.
    static  const   FolioCString    APPLET_WND_NAME;        ///< The name of the applet window.

    static  const   UInt32  APPLET_WND_WIDTH    = 1024; ///< The width of the applet window.
    static  const   UInt32  APPLET_WND_HEIGHT   = 768;  ///< The height of the applet window.

    static  const   Gdiplus::ARGB   APPLET_WND_BACKGROUND_COLOUR = Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR; //< The background colour of the applet window.

    static  const   UInt32  APPLET_WND_OBJECT_INDEX = 0;    ///< The data index to the applet window object in the applet window.
    
    FolioHandle m_instanceHandle;   ///< The application instance handle.
    FolioString m_commandLine;      ///< The application command line.
    FolioHandle m_wndHandle;        ///< The window handle of the applet window.
    FolioHandle m_wndDCHandle;      ///< The device context handle of the applet window.
    bool        m_appletWndReady;   ///< <b>true</b> if the applet window is ready, <b>false</b> otherwise.

    std::unique_ptr<ACanvasMsgHandler>  m_canvasMsgHandler;  ///< Our canvas message handler.

    FolioHandle m_gdiHandle;    ///< The GDI+ handle;

    std::unique_ptr<Gdiplus::Graphics>  m_graphics;  ///< The graphics object of the applet window.

    std::unique_ptr<Folio::Core::Game::Gamepad>  m_gamepad;  ///< The gamepad of the applet window.

    FolioStatus Initialise ();
    FolioStatus Terminate ();

    FolioStatus RegisterGraphics ();
    FolioStatus DeregisterGraphics ();

    FolioStatus RegisterAppletWndClass () const;
    FolioStatus DeregisterAppletWndClass () const;

    FolioStatus CreateAppletWnd ();

    FolioStatus CreateCanvasMsgHandler ();
    void        DestroyCanvasMsgHandler ();
    ACanvasMsgHandler*  GetCanvasMsgHandler ();
    bool    IsCanvasMsgHandler () const;

    FolioStatus CreateGraphics ();
    void        DestroyGraphics ();
    bool    IsGraphics () const;

    FolioStatus CreateGamepad ();
    void    DestroyGamepad ();
    bool    IsGamepad () const;

    FolioStatus HandleProcessFrame (HWND      wndHandle,
                                    UInt32&   frameRateIncrement);

    static  FolioStatus SetAppletWnd (HWND          wndHandle,
                                      AppletWnd*    appletWnd);
    static  AppletWnd*  GetAppletWnd (HWND wndHandle);

    static  LRESULT CALLBACK    AppletWndProc (HWND    wndHandle,
                                               UINT    msg,
                                               WPARAM  wParam,
                                               LPARAM  lParam);

    static  FolioStatus HandleCreateWndMsg (HWND    wndHandle,
                                            WPARAM  wParam,
                                            LPARAM  lParam);
    static  FolioStatus HandleDestroyWndMsg (HWND   wndHandle,
                                             WPARAM wParam,
                                             LPARAM lParam);
    static  FolioStatus HandleSizeMsg (HWND     wndHandle,
                                       WPARAM   wParam,
                                       LPARAM   lParam);
    static  FolioStatus HandlePaintWndMsg (HWND     wndHandle,
                                           WPARAM   wParam,
                                           LPARAM   lParam);
    static  FolioStatus HandleKeyboardMsg (HWND     wndHandle,
                                           WPARAM   wParam,
                                           LPARAM   lParam,
                                           bool     keyDown);
    static  FolioStatus HandleMouseMoveMsg (HWND    wndHandle,
                                            WPARAM  wParam,
                                            LPARAM  lParam);
    static  FolioStatus HandleMouseButtonMsg (HWND      wndHandle,
                                              WPARAM    wParam,
                                              LPARAM    lParam);
    static  FolioStatus HandleTimerMsg (HWND    wndHandle,
                                        WPARAM  wParam,
                                        LPARAM  lParam);

    /// Private copy constructor to prevent copying.
    AppletWnd (const AppletWnd& rhs);

    /// Private assignment operator to prevent copying.
    AppletWnd& operator= (const AppletWnd& rhs);

    /// Allow the process singleton to construct.
    friend class Folio::Core::Util::ProcessSingleton<AppletWnd>;
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
