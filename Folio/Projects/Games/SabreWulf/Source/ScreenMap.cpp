// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "ScreenMap.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// The screen map layout (256 screens).
// There are 48 (0x00-0x2f) screen types in total.
const   ScreenMap::ScreenNumbersList    ScreenMap::m_screenMap
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
};

//{
//    0x00, 0x14, 0x14, 0x1a, 0x16, 0x14, 0x14, 0x16, 0x14, 0x1a, 0x1b, 0x14, 0x1a, 0x14, 0x16, 0x02,
//    0x26, 0x21, 0x1d, 0x1c, 0x11, 0x0c, 0x0d, 0x17, 0x1d, 0x17, 0x1d, 0x21, 0x11, 0x1f, 0x0b, 0x03,
//    0x25, 0x15, 0x15, 0x0d, 0x0b, 0x0c, 0x12, 0x18, 0x15, 0x11, 0x17, 0x18, 0x18, 0x12, 0x11, 0x1e,
//    0x25, 0x18, 0x11, 0x0c, 0x05, 0x12, 0x15, 0x20, 0x1c, 0x19, 0x11, 0x0b, 0x0b, 0x2d, 0x11, 0x03,
//    0x27, 0x1c, 0x15, 0x12, 0x08, 0x18, 0x15, 0x0d, 0x1f, 0x1f, 0x1c, 0x18, 0x15, 0x08, 0x11, 0x1e,
//    0x27, 0x21, 0x05, 0x11, 0x1f, 0x1c, 0x11, 0x0c, 0x12, 0x12, 0x0d, 0x17, 0x18, 0x0d, 0x0b, 0x03,
//    0x27, 0x17, 0x11, 0x0b, 0x1f, 0x0c, 0x11, 0x2e, 0x0b, 0x11, 0x0c, 0x15, 0x11, 0x1f, 0x17, 0x1e,
//    0x25, 0x11, 0x17, 0x08, 0x12, 0x0d, 0x0b, 0x0a, 0x0f, 0x0a, 0x0c, 0x11, 0x17, 0x0d, 0x17, 0x22,
//    0x28, 0x0b, 0x0b, 0x1f, 0x2d, 0x12, 0x15, 0x10, 0x07, 0x10, 0x12, 0x15, 0x20, 0x1f, 0x1c, 0x23,
//    0x25, 0x05, 0x18, 0x1d, 0x0b, 0x17, 0x11, 0x0e, 0x06, 0x0e, 0x2f, 0x11, 0x0c, 0x12, 0x1d, 0x03,
//    0x25, 0x20, 0x1c, 0x19, 0x15, 0x18, 0x15, 0x12, 0x08, 0x12, 0x11, 0x17, 0x12, 0x15, 0x20, 0x1e,
//    0x28, 0x21, 0x1d, 0x1f, 0x1c, 0x08, 0x20, 0x17, 0x1d, 0x1c, 0x15, 0x0b, 0x17, 0x0b, 0x1f, 0x22,
//    0x27, 0x0b, 0x2d, 0x12, 0x1d, 0x1f, 0x21, 0x11, 0x1c, 0x0d, 0x17, 0x08, 0x18, 0x18, 0x1d, 0x22,
//    0x25, 0x18, 0x05, 0x05, 0x20, 0x21, 0x20, 0x0b, 0x1f, 0x0c, 0x11, 0x1f, 0x1c, 0x15, 0x18, 0x23,
//    0x29, 0x08, 0x19, 0x15, 0x12, 0x20, 0x21, 0x19, 0x1d, 0x21, 0x15, 0x1d, 0x1f, 0x1c, 0x15, 0x23,
//    0x04, 0x2a, 0x2c, 0x2b, 0x2b, 0x2a, 0x2b, 0x2a, 0x2b, 0x2b, 0x2b, 0x2b, 0x2a, 0x2a, 0x2b, 0x09,
//};

// Orchid screen positions (1 per screen type. { 0x00, 0x00, } - means no orchid).
const   ScreenMap::ScreenPositionsList  ScreenMap::m_orchidScreenPositions =
{
    { 0x38, 0x3f, },    // Screen 0x00. 
    { 0x00, 0x00, },    // Screen 0x01.
    { 0x50, 0x77, },    // Screen 0x02.
    { 0x30, 0x7f, },    // Screen 0x03.
    { 0x50, 0x7f, },    // Screen 0x04.
    { 0xa8, 0x7f, },    // Screen 0x05.
    { 0xd8, 0x7f, },    // Screen 0x06.
    { 0x30, 0x47, },    // Screen 0x07.
    { 0x78, 0x5f, },    // Screen 0x08.
    { 0x58, 0x3f, },    // Screen 0x09.
    { 0x78, 0x7f, },    // Screen 0x0a.
    { 0xb0, 0x7f, },    // Screen 0x0b.
    { 0x80, 0x7f, },    // Screen 0x0c.
    { 0x68, 0x7f, },    // Screen 0x0d.
    { 0x38, 0x3f, },    // Screen 0x0e.
    { 0x80, 0x7f, },    // Screen 0x0f.
    { 0xc0, 0x7f, },    // Screen 0x10.
    { 0xc0, 0x7f, },    // Screen 0x11.
    { 0x78, 0x5f, },    // Screen 0x12.
    { 0x00, 0x00, },    // Screen 0x13.
    { 0xc8, 0x3f, },    // Screen 0x14.
    { 0x20, 0x3f, },    // Screen 0x15.
    { 0x48, 0x3f, },    // Screen 0x16.
    { 0xd8, 0x7f, },    // Screen 0x17.
    { 0xb0, 0x7f, },    // Screen 0x18.
    { 0x78, 0x3f, },    // Screen 0x19.
    { 0x20, 0x7f, },    // Screen 0x1a.
    { 0x80, 0x7f, },    // Screen 0x1b.
    { 0x48, 0x3f, },    // Screen 0x1c.
    { 0xc0, 0x7f, },    // Screen 0x1d.
    { 0x20, 0x7f, },    // Screen 0x1e.
    { 0xb8, 0x3f, },    // Screen 0x1f.
    { 0xc8, 0x7f, },    // Screen 0x20.
    { 0x60, 0x7f, },    // Screen 0x21.
    { 0x70, 0x7f, },    // Screen 0x22.
    { 0x10, 0x7f, },    // Screen 0x23.
    { 0x90, 0x3f, },    // Screen 0x24.
    { 0xd8, 0x7f, },    // Screen 0x25.
    { 0x58, 0x4f, },    // Screen 0x26.
    { 0x98, 0x7f, },    // Screen 0x27.
    { 0x40, 0x7f, },    // Screen 0x28.
    { 0xa0, 0x7f, },    // Screen 0x29.
    { 0xc0, 0x7f, },    // Screen 0x2a.
    { 0xc8, 0x7f, },    // Screen 0x2b.
    { 0x48, 0x3f, },    // Screen 0x2c.
    { 0x50, 0x7f, },    // Screen 0x2d.
    { 0x78, 0x3f, },    // Screen 0x2e.
    { 0x40, 0x3f, },    // Screen 0x2f.
};


// Object screen positions (4 per screen type { 0x00, 0x00, } - means no object).
const   ScreenMap::ScreenPositionsList  ScreenMap::m_objectScreenPositions = 
{
    { 0x50, 0x3f, }, { 0x40, 0x7f, }, { 0x88, 0x7f, }, { 0xd0, 0x7f, }, // Screen 0x00.
    { 0x00, 0x00, }, { 0x00, 0x00, }, { 0x00, 0x00, }, { 0x00, 0x00, }, // Screen 0x01.
    { 0xb8, 0x3f, }, { 0xb8, 0x7f, }, { 0x20, 0x7f, }, { 0x70, 0x87, }, // Screen 0x02.
    { 0x20, 0x3f, }, { 0x50, 0x7f, }, { 0x70, 0x3f, }, { 0xb0, 0x7f, }, // Screen 0x03.
    { 0x50, 0x3f, }, { 0x78, 0x7f, }, { 0xb8, 0x7f, }, { 0xd8, 0x3f, }, // Screen 0x04.
    { 0x20, 0x5f, }, { 0x58, 0x57, }, { 0x78, 0x77, }, { 0xd0, 0x67, }, // Screen 0x05.
    { 0x08, 0x7f, }, { 0x58, 0x3f, }, { 0x78, 0x7f, }, { 0xb0, 0x3f, }, // Screen 0x06.
    { 0x30, 0x7f, }, { 0x48, 0x3f, }, { 0xa0, 0x3f, }, { 0xc8, 0x5f, }, // Screen 0x07.
    { 0x20, 0x67, }, { 0x68, 0x3f, }, { 0x88, 0x7f, }, { 0xc8, 0x57, }, // Screen 0x08.
    { 0x28, 0x7f, }, { 0x70, 0x7f, }, { 0x98, 0x3f, }, { 0xb0, 0x7f, }, // Screen 0x09.
    { 0x10, 0x7f, }, { 0x48, 0x3f, }, { 0xa8, 0x77, }, { 0xc8, 0x77, }, // Screen 0x0a.
    { 0x38, 0x7f, }, { 0x40, 0x3f, }, { 0x58, 0x77, }, { 0xb0, 0x3f, }, // Screen 0x0b.
    { 0x28, 0x3f, }, { 0x60, 0x7f, }, { 0xb0, 0x7f, }, { 0xb8, 0x3f, }, // Screen 0x0c.
    { 0x48, 0x7f, }, { 0x60, 0x3f, }, { 0x98, 0x7f, }, { 0xc8, 0x3f, }, // Screen 0x0d.
    { 0x70, 0x7f, }, { 0x90, 0x3f, }, { 0xc8, 0x3f, }, { 0xc8, 0x7f, }, // Screen 0x0e.
    { 0x30, 0x4f, }, { 0x58, 0x7f, }, { 0xa0, 0x3f, }, { 0xd8, 0x7f, }, // Screen 0x0f.
    { 0x20, 0x3f, }, { 0x30, 0x7f, }, { 0x60, 0x47, }, { 0xc8, 0x47, }, // Screen 0x10.
    { 0x90, 0x87, }, { 0x98, 0x3f, }, { 0xd0, 0x3f, }, { 0xe0, 0x7f, }, // Screen 0x11.
    { 0x40, 0x87, }, { 0x50, 0x4f, }, { 0x90, 0x3f, }, { 0xd0, 0x57, }, // Screen 0x12.
    { 0x40, 0x47, }, { 0x50, 0x7f, }, { 0xa8, 0x3f, }, { 0xa8, 0x7f, }, // Screen 0x13.
    { 0x18, 0x7f, }, { 0x40, 0x3f, }, { 0x80, 0x3f, }, { 0xd0, 0x7f, }, // Screen 0x14.
    { 0x28, 0x7f, }, { 0x58, 0x3f, }, { 0x78, 0x7f, }, { 0xd0, 0x7f, }, // Screen 0x15.
    { 0x20, 0x3f, }, { 0x60, 0x67, }, { 0x78, 0x5f, }, { 0xa0, 0x3f, }, // Screen 0x16.
    { 0x20, 0x3f, }, { 0x28, 0x7f, }, { 0x78, 0x7f, }, { 0xc8, 0x3f, }, // Screen 0x17.
    { 0x70, 0x7f, }, { 0x90, 0x7f, }, { 0xc0, 0x3f, }, { 0xd0, 0x7f, }, // Screen 0x18.
    { 0x28, 0x5f, }, { 0x38, 0x7f, }, { 0xb0, 0x7f, }, { 0xd0, 0x6f, }, // Screen 0x19.
    { 0x48, 0x7f, }, { 0x58, 0x3f, }, { 0x78, 0x7f, }, { 0xd0, 0x3f, }, // Screen 0x1a.
    { 0x80, 0x3f, }, { 0xb0, 0x7f, }, { 0xc8, 0x7f, }, { 0xe0, 0x3f, }, // Screen 0x1b.
    { 0x28, 0x7f, }, { 0x80, 0x4f, }, { 0xd8, 0x3f, }, { 0xd0, 0x7f, }, // Screen 0x1c.
    { 0x18, 0x3f, }, { 0x20, 0x7f, }, { 0xa0, 0x7f, }, { 0xd8, 0x7f, }, // Screen 0x1d.
    { 0x30, 0x3f, }, { 0x60, 0x3f, }, { 0x70, 0x7f, }, { 0x70, 0xa7, }, // Screen 0x1e.
    { 0x48, 0x3f, }, { 0x28, 0x7f, }, { 0xa0, 0x3f, }, { 0xa0, 0x87, }, // Screen 0x1f.
    { 0x20, 0x7f, }, { 0x28, 0x3f, }, { 0x70, 0x87, }, { 0xa8, 0x87, }, // Screen 0x20.
    { 0x20, 0x87, }, { 0x48, 0x3f, }, { 0x78, 0x7f, }, { 0xd0, 0x7f, }, // Screen 0x21.
    { 0x20, 0x3f, }, { 0x28, 0x7f, }, { 0x58, 0x7f, }, { 0x70, 0x97, }, // Screen 0x22.
    { 0x70, 0x87, }, { 0xb8, 0x3f, }, { 0xb8, 0x77, }, { 0xb8, 0x87, }, // Screen 0x23.
    { 0x20, 0x3f, }, { 0x78, 0x3f, }, { 0x78, 0x7f, }, { 0xd0, 0x7f, }, // Screen 0x24.
    { 0x68, 0x57, }, { 0x68, 0x7f, }, { 0x68, 0x3f, }, { 0x68, 0x97, }, // Screen 0x25.
    { 0x38, 0x7f, }, { 0x70, 0x7f, }, { 0x90, 0x3f, }, { 0xc0, 0x7f, }, // Screen 0x26.
    { 0x40, 0x5f, }, { 0x68, 0x3f, }, { 0xc8, 0x7f, }, { 0xd0, 0x3f, }, // Screen 0x27.
    { 0x48, 0x3f, }, { 0x88, 0x7f, }, { 0xb8, 0x3f, }, { 0xd8, 0x7f, }, // Screen 0x28.
    { 0x38, 0x3f, }, { 0x58, 0x7f, }, { 0x88, 0x7f, }, { 0xa8, 0x97, }, // Screen 0x29.
    { 0x40, 0x3f, }, { 0x60, 0x7f, }, { 0xa0, 0x7f, }, { 0xc8, 0x3f, }, // Screen 0x2a.
    { 0x20, 0x77, }, { 0x68, 0x3f, }, { 0xa0, 0x7f, }, { 0xd0, 0x3f, }, // Screen 0x2b.
    { 0x28, 0x3f, }, { 0x70, 0x77, }, { 0x98, 0x77, }, { 0xb0, 0x3f, }, // Screen 0x2c.
    { 0x28, 0x3f, }, { 0x78, 0x7f, }, { 0xc0, 0x7f, }, { 0xd0, 0x4f, }, // Screen 0x2d.
    { 0x48, 0x3f, }, { 0x28, 0x7f, }, { 0xa0, 0x3f, }, { 0xa0, 0x87, }, // Screen 0x2e.
    { 0x48, 0x87, }, { 0xc0, 0x3f, }, { 0xd0, 0x4f, }, { 0xd0, 0x87, }, // Screen 0x2f.
};


// The amulet piece screen index list (4 pieces, 8 separate combinations).
const   ScreenMap::ScreenIndexList  ScreenMap::m_amuletPieceScreenIndexList =
{
//  Top-left piece      Top-right Piece     Bottom-left piece   Bottom-right Piece
    0x43,               0x91,               0x4d,               0xcb,    
    0x9d,               0xac,               0x2d,               0x26,
    0xe1,               0x73,               0x44,               0x2d,
    0x35,               0xc3,               0x4d,               0xa9,
    0x8a,               0x4d,               0xe1,               0x52,
    0x43,               0x58,               0x39,               0xe7,
    0x59,               0xa7,               0xe2,               0x91,
    0x26,               0x35,               0xcb,               0xa3,
};

UInt32  ScreenMap::m_amuletPieceScreenIndexListIndex = 0;   // The current index into the amulet piece screen index list.


ScreenMap::ScreenMap ()
:   m_currentScreenMapIndex(INITIAL_SCREEN_INDEX)
{
} // Endproc.


ScreenMap::~ScreenMap ()
{
} // Endproc.


void    ScreenMap::ScatterObjects ()
{
    // Get the random index into the amulet piece screen index list.

    m_amuletPieceScreenIndexListIndex = 
        Folio::Core::Util::Random::GetRandomNumber (m_amuletPieceScreenIndexList.size () / MAX_AMULET_PIECES - 1) * MAX_AMULET_PIECES;
} // Endproc.


UInt32  ScreenMap::GetCurrentScreenMapIndex () const
{
    return (m_currentScreenMapIndex);
} // Endproc.


UInt32  ScreenMap::MoveToNewScreen (CollisionGrid::ScreenExit::ORIENTATION orientation)
{
    m_currentScreenMapIndex++;
    if (m_currentScreenMapIndex >= 48)
    //if (m_currentScreenMapIndex >= (MAX_SCREEN_MAP_COLUMNS * MAX_SCREEN_MAP_ROWS))
        m_currentScreenMapIndex = 0;

    //switch (orientation)
    //{
    //case CollisionGrid::ScreenExit::TOP:
    //    if (m_currentScreenMapIndex >= MAX_SCREEN_MAP_COLUMNS)
    //    {
    //        m_currentScreenMapIndex -= MAX_SCREEN_MAP_COLUMNS;
    //    } // Endif.

    //    else
    //    {
    //        m_currentScreenMapIndex += (MAX_SCREEN_MAP_COLUMNS * (MAX_SCREEN_MAP_ROWS - 1));
    //    } // Endelse.
    //    break;

    //case CollisionGrid::ScreenExit::BOTTOM:
    //    if (m_currentScreenMapIndex <= (MAX_SCREEN_MAP_COLUMNS * (MAX_SCREEN_MAP_ROWS - 1)))
    //    {
    //        m_currentScreenMapIndex += MAX_SCREEN_MAP_COLUMNS;
    //    } // Endif.

    //    else
    //    {
    //        m_currentScreenMapIndex -= (MAX_SCREEN_MAP_COLUMNS * (MAX_SCREEN_MAP_ROWS - 1));
    //    } // Endelse.
    //    break;

    //case CollisionGrid::ScreenExit::LEFT:
    //    if ((m_currentScreenMapIndex % MAX_SCREEN_MAP_COLUMNS) == 0)
    //    {
    //        m_currentScreenMapIndex += MAX_SCREEN_MAP_COLUMNS;
    //    } // Endif.

    //    else
    //    {
    //        m_currentScreenMapIndex--;
    //    } // Endelse.
    //    break;

    //case CollisionGrid::ScreenExit::RIGHT:
    //    if ((m_currentScreenMapIndex + 1) % MAX_SCREEN_MAP_COLUMNS)
    //    {
    //        m_currentScreenMapIndex++;
    //    } // Endif.

    //    else
    //    {
    //        m_currentScreenMapIndex -= MAX_SCREEN_MAP_COLUMNS;
    //    } // Endelse.
    //    break;

    //default:
    //    break;
    //} // Endswitch.

    return (m_currentScreenMapIndex);
} // Endproc.


ScreenMap::ScreenNumber ScreenMap::GetCurrentScreenNumber () const
{
    return (m_screenMap [m_currentScreenMapIndex]);
} // Endproc.


ScreenMap::ScreenNumber ScreenMap::GetScreenNumber (UInt32 screenMapIndex) const
{
    return (m_screenMap [screenMapIndex]);
} // Endproc.


bool    ScreenMap::IsScreenOrchidSprite () const
{
    // Get the current screen number.
    
    ScreenNumber    currentScreenNumber = GetCurrentScreenNumber ();

    // Is there an orchid on the screen?

    return ((m_orchidScreenPositions [currentScreenNumber].X != 0x00) && 
            (m_orchidScreenPositions [currentScreenNumber].Y != 0x00));
} // Endproc.


Int32   ScreenMap::GetScreenOrchidSpriteScreenXLeft () const
{
    return (m_orchidScreenPositions [GetCurrentScreenNumber ()].X);
} // Endproc.


Int32   ScreenMap::GetScreenOrchidSpriteScreenYBottom () const
{
    return (m_orchidScreenPositions [GetCurrentScreenNumber ()].Y);
} // Endproc.


FolioStatus ScreenMap::QueryScreenObjectSprites (FolioHandle        dcHandle,
                                                 ObjectSpritesList& objectSpritesList) const
{
    FolioStatus status = ERR_SUCCESS;

    objectSpritesList.clear (); // Initialise!

    // Get the current screen number.

    ScreenNumber    currentScreenNumber = GetCurrentScreenNumber ();

    // Get the random number of the screen's object sprites.

    UInt32  numScreenObjectSprites = 4;

    for (UInt32 screenObjectSpriteCount = 0; 
         (status == ERR_SUCCESS) && (screenObjectSpriteCount < numScreenObjectSprites); 
         ++screenObjectSpriteCount)
    {
        // Calculate the object sprite's screen position index.

        UInt32  objectSpriteScreenPositionIndex = screenObjectSpriteCount + (currentScreenNumber * MAX_OBJECT_POSITIONS_PER_SCREEN);

        // Is the object sprite's screen position valid.

        if ((m_objectScreenPositions [objectSpriteScreenPositionIndex].X != 0) &&
            (m_objectScreenPositions [objectSpriteScreenPositionIndex].Y != 0))
        {
            // Yes. Create the screen's object sprite.

            ObjectSpritePtr objectSprite(new ObjectSpritePtr::element_type);

            status = objectSprite->Create (dcHandle, 
                                           static_cast<OBJECT_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (OBJECT_SPRITE_BOX, OBJECT_SPRITE_CHALICE)),
                                           m_currentScreenMapIndex,
                                           m_objectScreenPositions [objectSpriteScreenPositionIndex].X,
                                           m_objectScreenPositions [objectSpriteScreenPositionIndex].Y);

            if (status == ERR_SUCCESS)
            {
                // Add the screen's object sprite to the object sprites list.

                objectSpritesList.push_back (objectSprite);
            } // Endif.

        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        objectSpritesList.clear ();
    } // Endif.

    return (status);
} // Endproc.


//FolioStatus ScreenMap::QueryScreenObjectSprites (FolioHandle        dcHandle,
//                                                 ObjectSpritesList  &objectSpritesList) const
//{
//    FolioStatus status = ERR_SUCCESS;
//
//    objectSpritesList.clear (); // Initialise!
//
//    // Get the current screen number.
//
//    ScreenNumber    currentScreenNumber = GetCurrentScreenNumber ();
//
//    // Is there an amulet piece on the screen?
//
//    OBJECT_SPRITE_ID    amuletPieceId = OBJECT_SPRITE_UNDEFINED;    // Initialise!
//    bool    isAmuletPieceOnScreen = IsAmuletPieceOnScreen (m_currentScreenMapIndex, amuletPieceId);
//
//    // Get the random number of the screen's object sprites.
//
//    UInt32  numScreenObjectSprites = isAmuletPieceOnScreen 
//                                     ? Folio::Core::Util::Random::GetRandomNumber (MAX_SCREEN_OBJECT_SPRITES - 1) + 1 
//                                     : Folio::Core::Util::Random::GetRandomNumber (MAX_SCREEN_OBJECT_SPRITES);
//
//    bool    screenPositionFilled [MAX_OBJECT_POSITIONS_PER_SCREEN] = {false,};  // Initialise!
//
//    for (UInt32 screenObjectSpriteCount = 0; 
//         (status == ERR_SUCCESS) && (screenObjectSpriteCount < numScreenObjectSprites); 
//         ++screenObjectSpriteCount)
//    {
//        // Get the object sprite's random empty screen position index.
//
//        UInt32  objectSpriteScreenPositionIndex = Folio::Core::Util::Random::GetRandomNumber (MAX_OBJECT_POSITIONS_PER_SCREEN - 1);
//          
//        while (screenPositionFilled [objectSpriteScreenPositionIndex])
//        {
//            objectSpriteScreenPositionIndex = Folio::Core::Util::Random::GetRandomNumber (MAX_OBJECT_POSITIONS_PER_SCREEN - 1);
//        } // Endwhile.
//
//        screenPositionFilled [objectSpriteScreenPositionIndex] = true;
//
//        // Calculate the object sprite's screen position index.
//
//        objectSpriteScreenPositionIndex += (currentScreenNumber * MAX_OBJECT_POSITIONS_PER_SCREEN);
//
//        // Is the object sprite's screen position valid.
//
//        if ((m_objectScreenPositions [objectSpriteScreenPositionIndex].X != 0) &&
//            (m_objectScreenPositions [objectSpriteScreenPositionIndex].Y != 0))
//        {
//              // Yes. Create the screen's object sprite.
//      
//              ObjectSpritePtr objectSprite(new ObjectSpritePtr::element_type);
//      
//              // Is there an amulet piece on the screen?
//      
//              if (isAmuletPieceOnScreen)
//              {
//                  // Yes. Add it.
//      
//                  status = objectSprite->Create (dcHandle, 
//                                                 amuletPieceId,
//                                                 m_currentScreenMapIndex,
//                                                 m_objectScreenPositions [objectSpriteScreenPositionIndex].X,
//                                                 m_objectScreenPositions [objectSpriteScreenPositionIndex].Y);
//              
//                  isAmuletPieceOnScreen = false;
//              } // Endif.
//
//              else
//              {
//                  // No. Add a random object sprite.
//
//                  status = objectSprite->Create (dcHandle, 
//                                                 static_cast<OBJECT_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (OBJECT_SPRITE_BOX, OBJECT_SPRITE_CHALICE)),
//                                                 m_currentScreenMapIndex,
//                                                 m_objectScreenPositions [objectSpriteScreenPositionIndex].X,
//                                                 m_objectScreenPositions [objectSpriteScreenPositionIndex].Y);
//              } // Endelse.
//
//              if (status == ERR_SUCCESS)
//              {
//                  // Add the screen's object sprite to the object sprites list.
//
//                  objectSpritesList.push_back (objectSprite);
//              } // Endif.
//
//          } // Endif.
//
//    } // Endfor.
//
//    if (status != ERR_SUCCESS)
//    {
//        objectSpritesList.clear ();
//    } // Endif.
//
//    return (status);
//} // Endproc.
//

UInt32  ScreenMap::GetTotalNumScreens ()
{
    return (m_screenMap.size ());
} // Endproc.


bool    ScreenMap::IsAmuletPieceOnScreen (UInt32            screenMapIndex,
                                          OBJECT_SPRITE_ID& amuletPieceId)
{
    bool    isAmuletPieceOnScreen = false;  // Initialise!

    amuletPieceId = OBJECT_SPRITE_UNDEFINED;    // Initialise!

    for (UInt32 index = m_amuletPieceScreenIndexListIndex; 
         !isAmuletPieceOnScreen && (index < (m_amuletPieceScreenIndexListIndex + MAX_AMULET_PIECES)); 
         ++index)
    {
        // Is there an amulet piece on the screen?

        isAmuletPieceOnScreen = (m_amuletPieceScreenIndexList [index] == screenMapIndex);

        if (isAmuletPieceOnScreen)
        {
            // Yes. Get the amulet piece identifier.

            amuletPieceId = 
                static_cast<OBJECT_SPRITE_ID> (OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT + (index - m_amuletPieceScreenIndexListIndex));
        } // Endif.

    } // Endfor.

    return (isAmuletPieceOnScreen);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
