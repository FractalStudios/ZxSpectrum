#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "BackgroundItemGraphics.h"
#include    "CollisionGrid.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Background item.
class BackgroundItem
{
public:
    // Background item flags.
    static  const   UInt32    FLAGS_NONE            = 0x00000000;
    static  const   UInt32    FLAGS_DOOR            = 0x00000001;               // Background item is a door.
    static  const   UInt32    FLAGS_OPEN_DOOR       = FLAGS_DOOR | 0x00010000;  // Background item is an open door.
    static  const   UInt32    FLAGS_CLOSED_DOOR     = FLAGS_DOOR | 0x00020000;  // Background item is a closed door.
    static  const   UInt32    FLAGS_LOCKED_DOOR     = FLAGS_DOOR | 0x00040000;  // Background item is a locked door.
    static  const   UInt32    FLAGS_EXIT_DOOR       = FLAGS_DOOR | 0x00080000;  // Background item is an exit door.
    static  const   UInt32    FLAGS_KNIGHT_DOOR     = FLAGS_DOOR | 0x01000000;  // Background item is a knight door.
    static  const   UInt32    FLAGS_WIZARD_DOOR     = FLAGS_DOOR | 0x02000000;  // Background item is a wizard door.
    static  const   UInt32    FLAGS_SERF_DOOR       = FLAGS_DOOR | 0x04000000;  // Background item is a serf door.
    static  const   UInt32    FLAGS_CAN_BE_CLOSED   = 0x80000000;               // Background item is a door that can be closed.

    BackgroundItem ();
    BackgroundItem (BACKGROUND_ITEM_ID  backgroundItemId,
                    UInt32              screenNumber,
                    Int32               screenXLeft,
                    Int32               screenYBottom,
                    UInt32              backgroundItemflags = FLAGS_NONE,
                    UInt32              drawingFlags = Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS);
    ~BackgroundItem ();

    FolioStatus             SetBackgroundItemGraphic ();
    BackgroundItemGraphic   GetBackgroundItemGraphic () const;

    BACKGROUND_ITEM_ID  GetBackgroundItemId () const;
    UInt32              GetScreenNumber () const;
    UInt32              GetBackgroundItemFlags () const;
    UInt32              GetDrawingFlags () const;

    FolioStatus SetScreenTopLeft (Int32 screenXLeft,
                                  Int32 screenYTop);

    Gdiplus::Rect   GetScreenRect () const;
    Int32           GetScreenXLeft () const;
    Int32           GetScreenYTop () const;
    Int32           GetScreenXRight () const;
    Int32           GetScreenYBottom () const;
    Int32           GetScreenWidth () const;
    Int32           GetScreenHeight () const;

    FolioStatus QueryDrawingElements (FolioHandle                               dcHandle,
                                      Folio::Core::Game::ZxSpectrum::COLOUR     roomColour,
                                      Folio::Core::Game::DrawingElementsList&   drawingElementsList,
                                      bool                                      maskedDrawingElementRqd = true) const;

    CollisionGrid::ScreenExit::ORIENTATION  GetDoorOrientation () const;

    void    SetDoorTransitionTickCount (UInt32 currentTickCount);
    UInt32  GetDoorTransitionTickCount () const;
    bool    IsDoorTransition (UInt32 currentTickCount) const;

    FolioStatus SetDoorOpen (bool setBackgroundItemGraphic = false);
    FolioStatus SetDoorClosed (bool setBackgroundItemGraphic = false);
    FolioStatus SetDoorUnlocked (bool setBackgroundItemGraphic = false);

    bool    operator == (const BackgroundItem& rhs) const;

    static  bool    IsDoor (UInt32 backgroundItemflags);
    static  bool    IsOpenDoor (UInt32 backgroundItemflags);
    static  bool    IsClosedDoor (UInt32 backgroundItemflags);
    static  bool    IsLockedDoor (UInt32 backgroundItemflags);
    static  bool    IsExitDoor (UInt32 backgroundItemflags);
    static  bool    IsKnightDoor (UInt32 backgroundItemflags);
    static  bool    IsWizardDoor (UInt32 backgroundItemflags);
    static  bool    IsSerfDoor (UInt32 backgroundItemflags);
    static  bool    CanDoorBeClosed (UInt32 backgroundItemflags);

    static  bool    IsCaveDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsNormalDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsBigDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsTrapDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsLockedRedDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsLockedGreenDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsLockedCyanDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsLockedYellowDoor (BACKGROUND_ITEM_ID backgroundItemId);
    static  bool    IsLockedExitDoor (BACKGROUND_ITEM_ID backgroundItemId);

private:
    BACKGROUND_ITEM_ID  m_backgroundItemId;         // The identifier of the background item.
    UInt32              m_screenNumber;             // The screen number the background item belongs to.
    Int32               m_screenXLeft;              // The screen X left (in pixels) of the background item.
    Int32               m_screenYBottom;            // The screen Y bottom (in pixels) of the background item.
    UInt32              m_backgroundItemflags;      // The flags of the background item.
    UInt32              m_drawingFlags;             // The drawing flags of the background item.
    UInt32              m_doorTransitionTickCount;  // The door timing (in milliseconds) of the background item (if it's a door).

    BackgroundItemGraphic   m_backgroundItemGraphic;    // The background item's graphic.

    BACKGROUND_ITEM_ID  GetNewBackgroundItemId () const;
}; // Endclass.

// Background item pointer.
typedef std::shared_ptr<BackgroundItem> BackgroundItemPtr;

// Background items list.
typedef std::vector<BackgroundItemPtr>  BackgroundItemsList;
             

// Routines.

extern  UInt32  GetMaxBackgroundItemsOnScreen (BACKGROUND_ITEM_ID backgroundItemId);
extern  FolioStatus CreateBackgroundItems (BackgroundItemsList& backgroundItemsList);
extern  BackgroundItemsList GetScreenBackgroundItemsList (UInt32                        screenNumber,
                                                          const BackgroundItemsList&    backgroundItemsList);
extern  BackgroundItemPtr   GetOppositeDoor (const BackgroundItem*      currentDoorBackgroundItem,
                                             const BackgroundItemsList& backgroundItemsList,
                                             bool                       setBackgroundItemGraphic = false);
extern  UInt32  GetNewScreenNumber (const BackgroundItem*       currentDoorBackgroundItem,
                                    const BackgroundItemsList&  backgroundItemsList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
