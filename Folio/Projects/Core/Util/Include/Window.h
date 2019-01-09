#pragma once

// Windows includes.
#include    <Windows.h>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

namespace Wnd
{

// Routines.
FolioStatus RegisterWndClass (WNDCLASSEX& wndClassEx);
FolioStatus DeregisterWndClass (const FolioString&  wndClassName,
                                FolioHandle         instanceHandle);
FolioStatus CreateWnd (const FolioString&   wndClassName,
                       const FolioString&   wndName,
                       UInt32               style,
                       UInt32               styleEx,
                       UInt32               xPos,
                       UInt32               yPos,
                       UInt32               width,
                       UInt32               height,
                       FolioHandle          instanceHandle,
                       void*                param,
                       FolioHandle&         wndHandle);
FolioStatus DestroyWnd (FolioHandle wndHandle);
FolioStatus ShowWnd (FolioHandle    wndHandle, 
                     Int32          cmdShow);
FolioStatus UpdateWnd (FolioHandle wndHandle);
bool        IsValidWnd (FolioHandle wndHandle,
                        bool        nullAllowed = false);
FolioStatus GetWndMessage (FolioHandle  wndHandle,
                           UInt32       minMsgFilter,
                           UInt32       maxMsgFilter,
                           MSG&         msg);
void        TranslateWndMessage (MSG& msg);
void        DispatchWndMessage (MSG& msg);
FolioStatus PeekWndMessage (FolioHandle wndHandle,
                            UInt32      minMsgFilter,
                            UInt32      maxMsgFilter,
                            UInt32      removeMsg,
                            MSG&        msg);
FolioStatus PostWndMessage (FolioHandle wndHandle,
                            UInt32      msg,
                            WPARAM      wParam,
                            LPARAM      lParam);
FolioStatus SendWndMessage (FolioHandle wndHandle,
                            UInt32      msg,
                            WPARAM      wParam,
                            LPARAM      lParam);
FolioStatus DefWindowProc (FolioHandle  wndHandle,
                           UInt32       msg,
                           WPARAM       wParam,
                           LPARAM       lParam);
FolioStatus SetWndText (FolioHandle         wndHandle,
                        const FolioString&  wndText);
FolioStatus SetWndData (FolioHandle wndHandle,
                        UInt32      dataIndex,
                        void*       data);
FolioStatus QueryWndData (FolioHandle   wndHandle,
                          UInt32        dataIndex,
                          void*&        data);
FolioStatus QueryWndRect (FolioHandle   wndHandle,
                          RECT&         rect);
FolioStatus QueryClientRect (FolioHandle    wndHandle,
                             RECT&          rect);
FolioStatus InvalidateClientRect (FolioHandle   wndHandle,
                                  RECT*         rect = 0,
                                  bool          eraseBackground = false);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
