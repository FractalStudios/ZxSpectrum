// "Home-made" includes.
#include    "StdAfx.h"
#include    "Screens.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Screens table.
static  const   Screen  g_screensTable [] =
{
//      m_screenNumber  m_roomId    m_roomColour        
    {     0,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {     1,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {     2,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {     3,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {     4,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {     5,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {     6,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {     7,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {     8,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {     9,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    10,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    11,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    12,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    13,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    14,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    15,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    16,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    17,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    18,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    19,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    20,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    21,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    22,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    23,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    24,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    25,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    26,            ROOM_5,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    27,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    28,            ROOM_8,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    29,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    30,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    31,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    32,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    33,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    34,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    35,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    36,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    37,            ROOM_2,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    38,            ROOM_5,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    39,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    40,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    41,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    42,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    43,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    44,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    45,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    46,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    47,            ROOM_5,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    48,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    49,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    50,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    51,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    52,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    53,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    54,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    55,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    56,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    57,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    58,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    59,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    60,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    61,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    62,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    63,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    64,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    65,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    66,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    67,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    68,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    69,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    70,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    71,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    72,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    73,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    74,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    75,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    76,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    77,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    78,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    79,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    80,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    81,            ROOM_10,    ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    82,            ROOM_9,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    83,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    84,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    85,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    86,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    87,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    88,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    89,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    90,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {    91,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    92,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {    93,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {    94,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    95,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    96,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {    97,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {    98,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {    99,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   100,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   101,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {   102,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   103,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   104,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   105,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   106,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   107,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   108,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   109,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   110,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   111,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {   112,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   113,            ROOM_5,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   114,            ROOM_5,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   115,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   116,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   117,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   118,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   119,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   120,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   121,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {   122,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   123,            ROOM_3,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   124,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   125,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   126,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   127,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   128,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   129,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   130,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   131,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {   132,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   133,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   134,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   135,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   136,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   137,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   138,            ROOM_0,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   139,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   140,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   141,            ROOM_4,     ZxSpectrum::BRIGHT | ZxSpectrum::RED,       },
    {   142,            ROOM_11,    ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   143,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   144,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     },
    {   145,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   146,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   147,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   148,            ROOM_1,     ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
};
  

// Screen static members.
bool    Screen::m_playEnteredScreenSound                = false;    // Indicates if the entered screen sound should be played.
UInt32  Screen::m_currentEnteredScreenSoundSampleIndex  = 0;        // The current entered screen sound sample index.
Folio::Core::Util::Sound::SoundSamplesList  Screen::m_enteredScreenSoundSamples;    // The entered screen sound samples.

Folio::Core::Util::Sound::SoundSample   Screen::m_openDoorSoundSample(16, 8883.25f); // The open door sound sample.
Folio::Core::Util::Sound::SoundSample   Screen::m_closeDoorSoundSample(16, 8883.25f); // The close door sound sample.

Screen::Screen ()
:   m_canvas(0),
    m_informationPanel(0),
    m_spriteGraphicsMap(0),
    m_screenNumber(SCREEN_NUMBER_UNDEFINED),
    m_roomId(ROOM_UNDEFINED),
    m_roomColour(ZxSpectrum::UNDEFINED),
    m_exitScreenTickCount(0),
    m_createNastySpriteTickCount(0)
{         
} // Endproc.
          

Screen::Screen (UInt32              screenNumber,
                ROOM_ID             roomId,
                ZxSpectrum::COLOUR  roomColour)
:   m_canvas(0),
    m_spriteGraphicsMap(0),
    m_informationPanel(0),
    m_screenNumber(screenNumber),
    m_roomId(roomId),
    m_roomColour(roomColour),
    m_exitScreenTickCount(0),       
    m_createNastySpriteTickCount(0)
{
} // Endproc.


Screen::~Screen ()
{
} // Endproc.


void    Screen::SetCanvas (Folio::Core::Applet::Canvas &canvas)
{
    m_canvas = &(canvas);
} // Endproc.


void    Screen::SetRoomGraphic (const RoomGraphicsMap &roomGraphicsMap)
{
    // Find the room in the room graphics map.

    RoomGraphicsMap::const_iterator itr = roomGraphicsMap.find (m_roomId);

    if (itr != roomGraphicsMap.end ())
    {
        // Note the room graphic.

        m_roomGraphic = itr->second;

        // Get the room's collision grid.

        m_collisionGrid = m_roomGraphic->GetCollisionGrid ();
    } // Endif.

} // Endproc.


void    Screen::SetSpriteGraphicsMap (const SpriteGraphicsMap &spriteGraphicsMap)
{
    m_spriteGraphicsMap = const_cast<SpriteGraphicsMap *> (&(spriteGraphicsMap));
} // Endproc.


void    Screen::SetInformationPanel (const InformationPanel &informationPanel)
{
    m_informationPanel = const_cast<InformationPanel *> (&(informationPanel));
} // Endproc.


UInt32  Screen::GetScreenNumber () const
{
    return (m_screenNumber);
} // Endproc.


ROOM_ID Screen::GetRoomId () const
{
    return (m_roomId);
} // Endproc.


ZxSpectrum::COLOUR  Screen::GetRoomColour () const
{
    return (m_roomColour);
} // Endproc.


void    Screen::SetBackgroundItemsList (const BackgroundItemsList &backgroundItemsList)
{
    m_backgroundItemsList = backgroundItemsList;
} // Endproc.


void    Screen::SetStaticSpritesList (const StaticSpritesList &staticSpritesList)
{
    m_staticSpritesList = staticSpritesList;
} // Endproc.


FolioStatus Screen::QueryDrawingElements (const PlayerSpritePtr                     &mainPlayer,
                                          Folio::Core::Game::DrawingElementsList    &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear();    // Initialise!

    // Has the screen's drawing elements been set?

    if (m_drawingElementsSet.empty ())
    {
        // No. Note the main player.

        m_mainPlayer = mainPlayer;

        // Initialise the screen.

        status = InitialiseScreen ();

        if (status == ERR_SUCCESS)
        {
            // Increment the number of rooms visited.

            m_informationPanel->IncrementNumRoomsVisited ();
        } // Endif.

    } // Endif.

    else
    {
        m_createNastySpriteTickCount = 0;   // Reset the create nasty sprite tick count.

        // Update the screen.

        status = UpdateScreen ();
    } // Endelse.

    if (status == ERR_SUCCESS)
    {
        if (!m_drawingElementsSet.empty ())
        {
            // Add the drawing elements of the screen.

            std::copy (m_drawingElementsSet.begin (), 
                       m_drawingElementsSet.end (), 
                       std::back_inserter (drawingElementsList));
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Start any screen boss sprite.
                                    
            status = StartBossSprite ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleProcessFrame (bool    &isStarting,
                                        UInt32  *frameRateIncrement)
{
    // Play the screen sounds.

    PlayScreenSounds ();

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Restore the sprite backgrounds.

    FolioStatus status = RestoreSpriteBackgrounds (*graphics);

    if (status == ERR_SUCCESS)
    {
        // Open or close the screen's doors.

        status = CheckDoors ();

        if (status == ERR_SUCCESS)
        {
            // Check the sprites.

            status = CheckSprites (*graphics);

            if (status == ERR_SUCCESS)
            {
                // Let the information panel process the frame.

                bool    mainPlayerIsDead = false;    // Initialise!

                status = m_informationPanel->HandleProcessFrame (isStarting, mainPlayerIsDead);

                // Is the main player dead?

                if (mainPlayerIsDead && (status == ERR_SUCCESS))
                {
                    // Yes. Kill the nasty sprites.

                    status = KillNastySprites ();

                    if (status == ERR_SUCCESS)
                    {
                        // Remove the weapon sprite.

                        status = RemoveWeaponSprite ();

                        if (status == ERR_SUCCESS)
                        {
                            // The main player is dead.

                            m_mainPlayer->SetDead ();
                        } // Endif.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


UInt32  Screen::MoveToNewScreen (const BackgroundItemsList &backgroundItemsList)
{
    // Get the current screen exit.

    Folio::Core::Game::CollisionGrid::ScreenExit    screenExit(m_mainPlayer->GetScreenExit ());

    // Get the new screen.

    BackgroundItemPtr   screenEntranceBackgroundItem;

    UInt32  screenNumber = GetNewScreenNumber (reinterpret_cast<BackgroundItem *> (screenExit.m_userData), 
                                               backgroundItemsList, 
                                               screenEntranceBackgroundItem);

    // Is the screen entrance locked?

    if (BackgroundItem::IsLockedDoor (screenEntranceBackgroundItem->GetBackgroundItemFlags ()))
    {
        // Yes. Unlock it.

        screenEntranceBackgroundItem->SetDoorUnlocked ();
    } // Endif.

    // Set the main player's position.

    switch (screenEntranceBackgroundItem->GetDoorOrientation ())
    {
    case Folio::Core::Game::CollisionGrid::ScreenExit::TOP:
    case Folio::Core::Game::CollisionGrid::ScreenExit::FLOOR:
        m_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft () + (screenEntranceBackgroundItem->GetScreenWidth () - m_mainPlayer->GetScreenWidth ()) / 2,
                                        screenEntranceBackgroundItem->GetScreenYTop ());
        break;

    case Folio::Core::Game::CollisionGrid::ScreenExit::BOTTOM:
        m_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft () + (screenEntranceBackgroundItem->GetScreenWidth () - m_mainPlayer->GetScreenWidth ()) / 2,
                                        screenEntranceBackgroundItem->GetScreenYTop () + screenEntranceBackgroundItem->GetScreenHeight () - m_mainPlayer->GetScreenHeight ());
        break;

    case Folio::Core::Game::CollisionGrid::ScreenExit::LEFT:
        m_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft (),
                                        screenEntranceBackgroundItem->GetScreenYTop () + (screenEntranceBackgroundItem->GetScreenHeight () - m_mainPlayer->GetScreenHeight ()) / 2);
        break;

    case Folio::Core::Game::CollisionGrid::ScreenExit::RIGHT:
        m_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft (),
                                        screenEntranceBackgroundItem->GetScreenYTop () + (screenEntranceBackgroundItem->GetScreenHeight () - m_mainPlayer->GetScreenHeight ()) / 2);
        break;

    default:
        break;
    } // Endswitch.

    // The main player is at a screen entrance.

    m_mainPlayer->SetScreenEntrance (Folio::Core::Game::CollisionGrid::ScreenEntrance(screenEntranceBackgroundItem->GetDoorOrientation (),
                                                                                      screenEntranceBackgroundItem->GetScreenRect (),
                                                                                      Folio::Core::Game::CollisionGrid::ScreenEntrance::OPEN,
                                                                                      screenEntranceBackgroundItem.get ()));

    // Note the exit screen tick count for the old screen.

    m_exitScreenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    // Start playing the entered screen sound.

    m_playEnteredScreenSound                = true;
    m_currentEnteredScreenSoundSampleIndex  = 0;
    
    return (screenNumber);
} // Endproc.


FolioStatus Screen::StoreSpriteBackgrounds (Gdiplus::Graphics &graphics)
{
    // Store the static sprites' underlying backgrounds.
    
    FolioStatus status = Folio::Core::Game::StoreSpriteBackgrounds<StaticSpriteDrawingElementsList> (graphics, 
                                                                                                     m_staticSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Store the nasty sprites' underlying backgrounds.
    
        status = Folio::Core::Game::StoreSpriteBackgrounds<NastySpriteDrawingElementsList> (graphics, 
                                                                                            m_nastySpriteDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Store the boss sprite's underlying background.
    
            status = m_bossSpriteDrawingElement.StoreSpriteBackground (graphics);

            if (status == ERR_SUCCESS)
            {
                // Store the weapon sprite's underlying background.
    
                status = m_weaponSpriteDrawingElement.StoreSpriteBackground (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Store the main player's underlying background.

                    status = m_mainPlayer->StoreUnderlyingBackground (graphics);
                } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RestoreSpriteBackgrounds (Gdiplus::Graphics &graphics)
{
    // Restore the static sprites' underlying backgrounds.
    
    FolioStatus status = Folio::Core::Game::RestoreSpriteBackgrounds<StaticSpriteDrawingElementsList> (graphics, 
                                                                                                       m_staticSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Restore the nasty sprites' underlying backgrounds.
    
        status = Folio::Core::Game::RestoreSpriteBackgrounds<NastySpriteDrawingElementsList> (graphics, 
                                                                                              m_nastySpriteDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Restore the boss sprite's underlying background.
    
            status = m_bossSpriteDrawingElement.RestoreSpriteBackground (graphics);

            if (status == ERR_SUCCESS)
            {
                // Restore the weapon sprite's underlying background.
    
                status = m_weaponSpriteDrawingElement.RestoreSpriteBackground (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Restore the main player's underlying background.
        
                    status = m_mainPlayer->RestoreUnderlyingBackground (graphics);
                } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawSprites (Gdiplus::Graphics &graphics)
{
    // Draw the static sprites.
    
    FolioStatus status = Folio::Core::Game::DrawSprites<StaticSpriteDrawingElementsList> (graphics, 
                                                                                          m_staticSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the nasty sprites.
    
        status = Folio::Core::Game::DrawSprites<NastySpriteDrawingElementsList> (graphics, 
                                                                                 m_nastySpriteDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Draw the boss sprite.
    
            status = m_bossSpriteDrawingElement.DrawSprite (graphics);

            if (status == ERR_SUCCESS)
            {
                // Draw the weapon sprite.
    
                status = m_weaponSpriteDrawingElement.DrawSprite (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Draw the main player.

                    status = m_mainPlayer->Draw (graphics);

                    if (status == ERR_SUCCESS)
                    {
                        // The canvas should be redrawn on the next draw.

                        m_canvas->SetRedrawRqd ();
                    } // Endif.
    
                } // Endif.
    
            } // Endif.
    
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::AddGravestone ()
{
    // Add a gravestone to the screen.

    return (AddStaticSprite (STATIC_SPRITE_GRAVESTONE, m_mainPlayer->GetScreenRect ()));
} // Endproc.


UInt32  Screen::GetTotalNumRooms ()
{
    return (sizeof (g_screensTable) / sizeof (Screen));
} // Endproc.


FolioStatus Screen::InitialiseScreen ()
{                      
    // Create the screen's sound samples.

    CreateScreenSoundSamples ();

    // Initialise the screen's doors.

    FolioStatus status = InitialiseDoors ();

    if (status == ERR_SUCCESS)
    {
        // Build the screen's drawing elements.

        status = BuildScreenDrawingElements ();

        if (status == ERR_SUCCESS)
        {
            // Initialise the screen's collision grid.

            status = InitialiseCollisionGrid ();

            if (status == ERR_SUCCESS)
            {
                // Initialise the screen's static sprites.

                status = InitialiseStaticSprites ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::UpdateScreen ()
{
    FolioStatus status = ERR_SUCCESS;

    // Should the nasty sprites be removed?

    if (Folio::Core::Util::DateTime::GetCurrentTickCount () > (m_exitScreenTickCount + MAX_REMOVE_NASTY_SPRITES_TICK_COUNT))
    {
        // Yes.

        status = RemoveNastySprites ();
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Remove the weapon sprite.

        status = RemoveWeaponSprite ();

        if (status == ERR_SUCCESS)
        {
            // Reset the weapon sprite

            m_weaponSpriteDrawingElement.Reset ();
        
            // Remove the information panel's drawing elements from the screen's drawing elements.

            status = RemoveScreenDrawingElements (DRAWING_ELEMENT_INFORMATION_PANEL_ITEM);

            if (status == ERR_SUCCESS)
            {
                // Get the information panel's drawing elements.

                Folio::Core::Game::DrawingElementsList  informationPanelDrawingElementsList;

                status = m_informationPanel->QueryDrawingElements (m_canvas->GetCanvasDcHandle (),
                                                                   m_roomColour, 
                                                                   informationPanelDrawingElementsList);

                if (status == ERR_SUCCESS)
                {
                    // Add the information panel's drawing elements to the screen's drawing elements.

                    m_drawingElementsSet.insert (informationPanelDrawingElementsList.begin (),
                                                 informationPanelDrawingElementsList.end ());

                    // Open or close the screen's doors.

                    status = CheckDoors (true); // We're building the screen.
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::InitialiseDoors ()
{
    static  const   UInt32  DEFAULT_DOOR_TRANSITION = 5;    // Default door transition.

    FolioStatus status = ERR_SUCCESS;
    
    // Initialise the screen's doors.

    for (BackgroundItemsList::iterator itr = m_backgroundItemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_backgroundItemsList.end ());
         ++itr)
    {
        // Get the background item.

        BackgroundItem  &backgroundItem(*itr->get ());

        // Get the background item's flags.

        UInt32  backgroundItemflags = backgroundItem.GetBackgroundItemFlags ();

        // Is this a door?

        if (BackgroundItem::IsDoor (backgroundItemflags))
        {
            // Yes. Is this a door that can be closed?

            if (BackgroundItem::CanDoorBeClosed (backgroundItemflags))
            {
                // Yes. The door cannot be closed if the main player is in it.

                if (!m_mainPlayer->IsInScreenExit (backgroundItem.GetScreenRect ()) &&
                    (Folio::Core::Util::Random::GetRandomNumber (DEFAULT_DOOR_TRANSITION) == 0))
                {
                    // Force the door to be closed once the screen has been drawn.

                    backgroundItem.SetDoorTransitionTickCount (0);
                } // Endif.

                else
                {
                    // Set the door transition tick count.

                    backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());
                } // Endelse.

            } // Endif.

            // Is this an unlocked door?

            else
            if (BackgroundItem::IsUnlockedDoor (backgroundItemflags))
            {
                // Yes. Open the door.

                backgroundItem.SetDoorOpen ();
            } // Endelseif.
        
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::CheckDoors (bool buildingScreen)
{
    FolioStatus status = ERR_SUCCESS;

    // Check the screen's doors.

    for (BackgroundItemsList::iterator itr = m_backgroundItemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_backgroundItemsList.end ());
         ++itr)
    {
        // Get the background item.

        BackgroundItem  &backgroundItem(*itr->get ());

        // Get the background item's flags.

        UInt32  backgroundItemflags = backgroundItem.GetBackgroundItemFlags ();

        // Is this a door?

        if (BackgroundItem::IsDoor (backgroundItemflags))
        {
            // Is this a door that can be closed?

            if (BackgroundItem::CanDoorBeClosed (backgroundItemflags))
            {
                // Yes. Is the screen being built?

                if (buildingScreen)
                {
                    // Yes. Just restart the door transition.

                    backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());
                } // Endif.
                
                // Should the door be closed? 

                else
                if (backgroundItem.IsDoorTransition (Folio::Core::Util::DateTime::GetCurrentTickCount ()))
                {
                    // Yes. The door cannot be closed if the main player is in it.

                    if (m_mainPlayer->IsInScreenExit (backgroundItem.GetScreenRect ()))
                    {
                        // Just restart the door transition.

                        backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());
                    } // Endif.

                    else
                    {
                        // Close the door.
                
                       status = CloseDoor (backgroundItem, buildingScreen);
                    } // Endelse.

                } // Endelseif.

            } // Endif.

            // Is this a closed door?

            else
            if (BackgroundItem::IsClosedDoor (backgroundItemflags))
            {
                // Yes. Is the screen being built?

                if (buildingScreen)
                {
                    // Yes. Close the door.
                
                    status = CloseDoor (backgroundItem, buildingScreen);
                } // Endif.

                // The door cannot be closed if the main player is in it.

                else
                if (m_mainPlayer->IsInScreenExit (backgroundItem.GetScreenRect ()))
                {
                    backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());
                } // Endelseif.

                else
                if (backgroundItem.IsDoorTransition (Folio::Core::Util::DateTime::GetCurrentTickCount ()))
                {
                    // Open the door.
                
                    status = OpenDoor (backgroundItem, buildingScreen);
                } // Endelseif.

            } // Endelseif.
        
            // Is this an unlocked door?

            else
            if (BackgroundItem::IsUnlockedDoor (backgroundItemflags))
            {
                // Yes. Open the door.
                
                status = OpenDoor (backgroundItem, buildingScreen);
            } // Endelseif.
        
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::OpenDoor (BackgroundItem    &backgroundItem, 
                              bool              buildingScreen)
{
    // Open the door.

    return (UpdateDoor (backgroundItem, true, buildingScreen));
} // Endproc.


FolioStatus Screen::CloseDoor (BackgroundItem   &backgroundItem, 
                               bool             buildingScreen)
{
    // Close the door.

    return (UpdateDoor (backgroundItem, false, buildingScreen));
} // Endproc.


FolioStatus Screen::UpdateDoor (BackgroundItem  &backgroundItem,
                                bool            openDoor,
                                bool            buildingScreen)
{
    // Remove the background item's drawing elements from the screen's drawing elements.

    FolioStatus status = RemoveBackgroundItemDrawingElements (FindScreenDrawingElements (&(backgroundItem))); 

    if (status == ERR_SUCCESS)
    {
        if (openDoor)
        {
            // Open the door.

            backgroundItem.SetDoorOpen ();

            // Open the screen exit.

            status = m_collisionGrid.OpenScreenExit (&(backgroundItem));
        } // Endif.

        else
        {
            // Close the door.

            backgroundItem.SetDoorClosed ();

            // Close the screen exit.

            status = m_collisionGrid.CloseScreenExit (&(backgroundItem));
        } // Endelse.

        if (status == ERR_SUCCESS)
        {
            // Get the background item's drawing elements.

            Folio::Core::Game::DrawingElementsList  drawingElementsList;

            FolioStatus status = backgroundItem.QueryDrawingElements (m_canvas->GetCanvasDcHandle (),
                                                                      m_roomColour,
                                                                      drawingElementsList,
                                                                      openDoor || !buildingScreen ? true : false);  // If the door is closed and the screen is being built, the mask is not required.

            if ((status == ERR_SUCCESS) && !drawingElementsList.empty ())
            {
                // Add the background item's drawing elements.

                status = AddBackgroundItemDrawingElements (drawingElementsList);

                if (status == ERR_SUCCESS)
                {
                    // Set the door transition tick count.

                    backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());

                    if (openDoor)
                    {
                        // Play the open door sound.

                        Folio::Core::Util::Sound::PlaySoundSample (m_openDoorSoundSample);
                    } // Endif.

                    else
                    {
                        // Play the close door sound.

                        Folio::Core::Util::Sound::PlaySoundSample (m_closeDoorSoundSample);
                    } // Endelse.

                } // Endif.

            } // Endif.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    Screen::IsDoor(const BackgroundItem  &backgroundItem) const
{
    bool    isDoor = false; // Initialise!

    // Get the background item's flags.

    UInt32  backgroundItemflags = backgroundItem.GetBackgroundItemFlags ();

    // Depending on the main player, certain background items are secret doors.

    switch (m_mainPlayer->GetPlayerSpriteId ())
    {
    case PLAYER_SPRITE_WIZARD:
        isDoor = BackgroundItem::IsDoor (backgroundItemflags) && 
                 (!BackgroundItem::IsKnightDoor (backgroundItemflags) ||
                  !BackgroundItem::IsSerfDoor (backgroundItemflags));
        break;

    case PLAYER_SPRITE_SERF:
        isDoor = BackgroundItem::IsDoor (backgroundItemflags) && 
                 (!BackgroundItem::IsKnightDoor (backgroundItemflags) ||
                  !BackgroundItem::IsWizardDoor (backgroundItemflags));
        break;

    case PLAYER_SPRITE_KNIGHT:
    default:
        isDoor = BackgroundItem::IsDoor (backgroundItemflags) && 
                 (!BackgroundItem::IsWizardDoor (backgroundItemflags) ||
                  !BackgroundItem::IsSerfDoor (backgroundItemflags));
        break;
    } // Endswitch.

    return (isDoor);
} // Endproc.


Folio::Core::Game::CollisionGrid::ScreenExit::STATE Screen::GetDoorState (const BackgroundItem &backgroundItem) const
{
    Folio::Core::Game::CollisionGrid::ScreenExit::STATE doorState = 
        Folio::Core::Game::CollisionGrid::ScreenExit::CLOSED;   // Initialise!

    // Get the background item's flags.

    UInt32  backgroundItemflags = backgroundItem.GetBackgroundItemFlags ();

    // Get the background item's identifier.

    BACKGROUND_ITEM_ID  backgroundItemId = backgroundItem.GetBackgroundItemId ();

    // Is the door open?

    if (BackgroundItem::IsOpenDoor (backgroundItemflags))
    {
        // Yes.

        doorState = Folio::Core::Game::CollisionGrid::ScreenExit::OPEN;
    } // Endif.

    // Is the door locked?

    else
    if (BackgroundItem::IsLockedDoor (backgroundItemflags) ||
        BackgroundItem::IsExitDoor (backgroundItemflags))
    {
        // Yes.

        doorState = Folio::Core::Game::CollisionGrid::ScreenExit::LOCKED;
    } // Endelseif.

    else
    {
        // Depending on the main player, certain background items are secret doors.

        switch (m_mainPlayer->GetPlayerSpriteId ())
        {
        case PLAYER_SPRITE_WIZARD:
            if (BackgroundItem::IsWizardDoor (backgroundItemflags))
            {
                doorState = Folio::Core::Game::CollisionGrid::ScreenExit::OPEN;
            } // Endif.
            break;

        case PLAYER_SPRITE_SERF:
            if (BackgroundItem::IsSerfDoor (backgroundItemflags))
            {
                doorState = Folio::Core::Game::CollisionGrid::ScreenExit::OPEN;
            } // Endif.
            break;

        case PLAYER_SPRITE_KNIGHT:
        default:
            if (BackgroundItem::IsKnightDoor (backgroundItemflags))
            {
                doorState = Folio::Core::Game::CollisionGrid::ScreenExit::OPEN;
            } // Endif.
            break;
        } // Endswitch.

    } // Endelse.

    return (doorState);
} // Endproc.


bool    Screen::CanDoorBeUnlocked (const BackgroundItem &backgroundItem) const
{
    // Get the background item's identifier.

    BACKGROUND_ITEM_ID  backgroundItemId = backgroundItem.GetBackgroundItemId ();

    // Is this a door that can now be unlocked?

    return ((BackgroundItem::IsLockedRedDoor (backgroundItemId)     && m_informationPanel->IsRedKeyCollected ())    ||
            (BackgroundItem::IsLockedGreenDoor (backgroundItemId)   && m_informationPanel->IsGreenKeyCollected ())  ||
            (BackgroundItem::IsLockedCyanDoor (backgroundItemId)    && m_informationPanel->IsCyanKeyCollected ())   ||
            (BackgroundItem::IsLockedYellowDoor (backgroundItemId)  && m_informationPanel->IsYellowKeyCollected ()) ||
            (BackgroundItem::IsLockedExitDoor (backgroundItemId)    && m_informationPanel->IsAcgKeyCollected ()));
} // Endproc.


FolioStatus Screen::CheckSprites (Gdiplus::Graphics &graphics)
{
    // Check the static sprites.

    FolioStatus status = CheckStaticSprites (graphics);

    if (status == ERR_SUCCESS)
    {
        // Check the nasty sprites.

        status = CheckNastySprites (graphics);

        if (status == ERR_SUCCESS)
        {
            // Check the boss sprite.

            status = CheckBossSprite (graphics);

            if (status == ERR_SUCCESS)
            {
                // Check the weapon sprite.

                status = CheckWeaponSprite (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Check the main player.

                    status = CheckMainPlayer (graphics);

                    if (status == ERR_SUCCESS)
                    {
                        // Store the sprite backgrounds.

                        status = StoreSpriteBackgrounds (graphics);

                        if (status == ERR_SUCCESS)
                        {            
                            // Draw the sprites.

                            status = DrawSprites (graphics);
                        } // Endif.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus Screen::InitialiseStaticSprites ()
{
    FolioStatus status = ERR_SUCCESS;

    m_staticSpriteDrawingElementsList.clear (); // Initialise!

    if (!m_staticSpritesList.empty ())
    {
        // Add each static sprite to the screen.

        for (StaticSpritesList::const_iterator itr = m_staticSpritesList.begin ();
             (status == ERR_SUCCESS) && (itr != m_staticSpritesList.end ());
             ++itr)
        {
            // Add the static sprite to the screen.

            status = AddStaticSprite (*itr);
        } // Endfor.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckStaticSprites (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Any screen static sprites?

    if (!m_staticSpriteDrawingElementsList.empty ())
    {
        // Yes. Change the static sprite's colours.

        for (StaticSpriteDrawingElementsList::iterator itr = m_staticSpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != m_staticSpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            StaticSpritePtr &staticSprite(itr->m_sprite);

            // Can the static sprite's colour be changed?

            if (StaticSprite::SupportsColourChange (staticSprite->GetStaticSpriteFlags ()))
            {
                // Yes. Change the colour of the static sprite.

                status = staticSprite->ChangeStaticSpriteColour ();
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::AddStaticSprite (const StaticSpritePtr &staticSprite)
{
    // Create a static sprite drawing element.

    StaticSpriteDrawingElement  staticSpriteDrawingElement(staticSprite, 
                                                           DRAWING_ELEMENT_STATIC_SPRITE, 
                                                           staticSprite->GetCollisionGridCellValue ());

    // Add to the screen's static sprite drawing elements list.

    m_staticSpriteDrawingElementsList.push_back (staticSpriteDrawingElement);

    // Add the static sprite to the screen's collision grid.

    return (AddCollisionGridDrawingElement (*(staticSpriteDrawingElement.m_drawingElement)));
} // Endproc.


FolioStatus Screen::AddStaticSprite (STATIC_SPRITE_ID       staticSpriteId,
                                     const Gdiplus::Rect    &screenRect)
{
    // Create the static sprite.

    StaticSpritePtr staticSprite(new StaticSpritePtr::element_type);
    
    FolioStatus status = staticSprite->Create (m_canvas->GetCanvasDcHandle (),
                                               staticSpriteId,
                                               *m_spriteGraphicsMap,
                                               m_screenNumber,
                                               screenRect.X,
                                               screenRect.Y + screenRect.Height - 1, // Screen Y bottom.
                                               GetStaticSpriteColour (staticSpriteId));

    if (status == ERR_SUCCESS)
    {
        // Get the canvas graphics.

        Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

        // Restore the static sprites' underlying backgrounds.
    
        status = Folio::Core::Game::RestoreSpriteBackgrounds<StaticSpriteDrawingElementsList> (*graphics, 
                                                                                               m_staticSpriteDrawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Restore the boss sprite's underlying background.
    
            status = m_bossSpriteDrawingElement.RestoreSpriteBackground (*graphics);

            if (status == ERR_SUCCESS)
            {
                // Add the static sprite to the screen.

                status = AddStaticSprite (staticSprite);

                if (status == ERR_SUCCESS)
                {
                    // Store the static sprites' underlying backgrounds.
    
                    status = Folio::Core::Game::StoreSpriteBackgrounds<StaticSpriteDrawingElementsList> (*graphics, 
                                                                                                         m_staticSpriteDrawingElementsList);

                    if (status == ERR_SUCCESS)
                    {
                        // Store the boss sprite's underlying background.
        
                        status = m_bossSpriteDrawingElement.StoreSpriteBackground (*graphics);
                    } // Endif.
 
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveStaticSprite (const StaticSpritePtr &staticSprite)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the static sprite in the screen's static sprite drawing elements list.

    StaticSpriteDrawingElementsList::iterator   itr = FindStaticSprite (staticSprite);

    if (itr != m_staticSpriteDrawingElementsList.end ())
    {
        // Remove the static sprite from the screen's collision grid.

        status = RemoveCollisionGridDrawingElement (*(itr->m_drawingElement));

        if (status == ERR_SUCCESS)
        {
            // Remove from the screen's static sprite drawing elements list.

            m_staticSpriteDrawingElementsList.erase (itr);
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


StaticSpriteDrawingElementsList::iterator   Screen::FindStaticSprite (const StaticSpritePtr &staticSprite)
{
    return (std::find_if (m_staticSpriteDrawingElementsList.begin (), m_staticSpriteDrawingElementsList.end (), 
                          [&staticSprite](const StaticSpriteDrawingElement& arg) {return (arg.m_sprite == staticSprite);}));
} // Endproc.


FolioStatus Screen::CheckNastySprites (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the main player ready or dying?

    bool    isMainPlayerReady   = m_mainPlayer->IsReady ();
    bool    isMainPlayerDying   = m_mainPlayer->IsDying ();

    if (isMainPlayerReady || isMainPlayerDying)
    {
        // Yes. Have we created all the nasty sprites?

        if (isMainPlayerReady && 
            (m_nastySpriteDrawingElementsList.size () < MAX_NUM_NASTY_SPRITES))
        {
            // No. Start any nasty sprites.

            status = StartNastySprites (graphics);
        } // Endif.

        if ((status == ERR_SUCCESS) && !m_nastySpriteDrawingElementsList.empty ())
        {
            // Process the nasty sprites.

            NastySpriteDrawingElementsList::iterator    itr = m_nastySpriteDrawingElementsList.begin ();

            do
            {
                // Get the nasty sprite.

                NastySpritePtr  &nastySprite(itr->m_sprite);

                // Get the state of the nasty sprite.

                switch (nastySprite->GetState ())
                {
                case NastySprite::STATE_INITIALISED:
                    // The nasty sprite is initialised.

                    // Set the nasty sprite's drawing element's collision grid cell value.

                    itr->m_drawingElement->SetCollisionGridCellValue (Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE);

                    status = nastySprite->Static (graphics, m_collisionGrid);
                    break;

                case NastySprite::STATE_TERMINATED:
                    // The nasty sprite is terminated.
                    break;

                case NastySprite::STATE_STATIC:
                case NastySprite::STATE_MOVING:
                    // Move the nasty sprite.

                    status = nastySprite->Move (graphics, m_collisionGrid);

                    if (status == ERR_SUCCESS)
                    {
                        // Set the nasty sprite's drawing element's top-left screen position.

                        itr->m_drawingElement->SetScreenTopLeft (nastySprite->GetScreenXLeft (), nastySprite->GetScreenYTop ());

                        // Update the nasty sprite in the screen's collision grid.

                        status = UpdateCollisionGridDrawingElement (*(itr->m_drawingElement));
                    } // Endif.
                    break;

                default:
                    break;
                } // Endswitch.

                // Is the nasty sprite dead?

                if (nastySprite->IsDead ())
                {
                    // Yes. Remove it from the the screen's nasty sprites list.

                    itr = m_nastySpriteDrawingElementsList.erase (itr);
                } // Endif.
                
                else
                {
                    ++itr;  // Next nasty sprite.
                } // Endelse.

            } // Enddo.
            while ((status == ERR_SUCCESS) && (itr != m_nastySpriteDrawingElementsList.end ()));
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StartNastySprites (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current tick count.

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    // Have we already started the create nasty tick count.

    if (m_createNastySpriteTickCount)
    {
        // Yes. Should we create a nasty sprite?

        if (currentTickCount >= m_createNastySpriteTickCount)
        {
            // Yes. Calculate the number of nasty sprites to create.

            UInt32  numNastySpritesToCreate = Folio::Core::Util::Random::GetRandomNumber(1, MAX_NUM_NASTY_SPRITES - m_nastySpriteDrawingElementsList.size ());

            for (UInt32 nastySpriteCount = 0; 
                 (status == ERR_SUCCESS) && (nastySpriteCount < numNastySpritesToCreate); 
                 ++nastySpriteCount)
            {
                // Add a nasty sprite to the screen.

                status = AddNastySprite (static_cast<NASTY_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (MAX_NASTY_SPRITE)));
            } // Endfor.

            if (status == ERR_SUCCESS)
            {
                // Restart the create nasty sprite tick count.

                SetCreateNastySpriteTickCount (currentTickCount, 1, 4);
            } // Endif.

        } // Endif.

    } // Endif.

    else
    {
        // No. Start the create nasty sprite tick count.

        SetCreateNastySpriteTickCount (currentTickCount, 1, 4);
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus Screen::AddNastySprite (NASTY_SPRITE_ID nastySpriteId)
{
    // Create the nasty sprite.

    NastySpritePtr  nastySprite(new NastySpritePtr::element_type);
    
    FolioStatus status = nastySprite->Create (m_canvas->GetCanvasDcHandle (),
                                              nastySpriteId,
                                              *m_spriteGraphicsMap,
                                              m_collisionGrid);

    if (status == ERR_SUCCESS)
    {
        // The nasty sprite is alive.

        nastySprite->SetAlive ();

        // Create a nasty sprite drawing element.

        NastySpriteDrawingElement   nastySpriteDrawingElement(nastySprite, DRAWING_ELEMENT_NASTY_SPRITE);

        // Add to the screen's nasty sprite drawing elements list.

        m_nastySpriteDrawingElementsList.push_back (nastySpriteDrawingElement);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveNastySprites ()
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_nastySpriteDrawingElementsList.empty ())
    {
        // Remove all the nasty sprites.

        NastySpriteDrawingElementsList::iterator    itr = m_nastySpriteDrawingElementsList.begin ();

        do
        {
            // Remove the nasty sprite from the screen's collision grid.

            status = RemoveCollisionGridDrawingElement (*(itr->m_drawingElement));

            if (status == ERR_SUCCESS)
            {
                // Remove from the screen's nasty sprite drawing elements list.

                itr = m_nastySpriteDrawingElementsList.erase (itr);
            } // Endif.

        } // Enddo.
        while ((status == ERR_SUCCESS) && (itr != m_nastySpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::KillNastySprites ()
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_nastySpriteDrawingElementsList.empty ())
    {
        // Kill all the nasty sprites.

        for (NastySpriteDrawingElementsList::iterator itr = m_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != m_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Remove the nasty sprite from the screen's collision grid.

            status = RemoveCollisionGridDrawingElement (*(itr->m_drawingElement));

            if (status == ERR_SUCCESS)
            {
                // The nasty sprite is dead.

                itr->m_sprite->SetDead (false); // Don't play its terminating sound.
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


void    Screen::SetCreateNastySpriteTickCount (UInt32   currentTickCount,
                                               UInt32   minNumSeconds, 
                                               UInt32   maxNumSeconds)

{
    m_createNastySpriteTickCount = currentTickCount + 
                                   500 * Folio::Core::Util::Random::GetRandomNumber (minNumSeconds, maxNumSeconds);
} // Endproc.


FolioStatus Screen::CheckBossSprite (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the boss sprite been created?

    if (m_bossSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the boss sprite.

        BossSpritePtr   &bossSprite(m_bossSpriteDrawingElement.m_sprite);

        // Get the state of the boss sprite.

        switch (bossSprite->GetState ())
        {
        case NastySprite::STATE_INITIALISED:
            // The boss sprite is initialised.

            status = bossSprite->Static (graphics, m_collisionGrid);
            break;

        case BossSprite::STATE_TERMINATED:
            // The boss sprite is terminated.

            // Kill the boss sprite

            m_bossSpriteDrawingElement.Kill ();
            break;

        case BossSprite::STATE_STATIC:
        case BossSprite::STATE_MOVING:
            // Move the boss sprite.

            status = bossSprite->Move (graphics, *m_informationPanel, m_collisionGrid);

            if (status == ERR_SUCCESS)
            {
                // Set the boss sprite's drawing element's top-left screen position.

                m_bossSpriteDrawingElement.m_drawingElement->SetScreenTopLeft (bossSprite->GetScreenXLeft (), 
                                                                               bossSprite->GetScreenYTop ());

                // Update the boss sprite in the screen's collision grid.

                status = UpdateCollisionGridDrawingElement (*(m_bossSpriteDrawingElement.m_drawingElement));
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StartBossSprite ()
{
    FolioStatus status = ERR_SUCCESS;

    // Has the boss sprite been created?

    if (m_bossSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the boss sprite.

        BossSpritePtr   &bossSprite(m_bossSpriteDrawingElement.m_sprite);

        // Reset the boss sprite.

        bool    removeBossSprite = false;   // Initialise!

        status = bossSprite->Reset (m_collisionGrid, removeBossSprite);

        if (removeBossSprite && (status == ERR_SUCCESS))
        {
            // Remove the boss sprite from the screen's collision grid.

            status = RemoveCollisionGridDrawingElement (*(m_bossSpriteDrawingElement.m_drawingElement));

            if (status == ERR_SUCCESS)
            {
                // Kill the boss sprite

                m_bossSpriteDrawingElement.Kill ();
            } // Endif.

        } // Endif.

    } // Endif.

    // Has the boss sprite been killed?

    else
    if (!m_bossSpriteDrawingElement.IsKilled ())
    {
        // No. Is there a boss sprite on the screen?

        BOSS_SPRITE_ID  bossSpriteId = GetScreenBossSpriteId (m_screenNumber, GetTotalNumRooms ());

        if (bossSpriteId != BOSS_SPRITE_UNDEFINED)
        {
            // Yes. Add it.

            status = AddBossSprite (bossSpriteId);
        } // Endif.
    
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus Screen::AddBossSprite (BOSS_SPRITE_ID bossSpriteId)
{
    // Create the boss sprite.

    BossSpritePtr   bossSprite(new BossSpritePtr::element_type);
    
    FolioStatus status = bossSprite->Create (m_canvas->GetCanvasDcHandle (),
                                             bossSpriteId,
                                             *m_spriteGraphicsMap,
                                             m_mainPlayer,
                                             *m_informationPanel,
                                             m_collisionGrid);

    if (status == ERR_SUCCESS)
    {
        // The boss sprite is alive.

        bossSprite->SetAlive ();

        // Create a boss sprite drawing element.

        status = m_bossSpriteDrawingElement.Create (bossSprite, 
                                                    DRAWING_ELEMENT_BOSS_SPRITE, 
                                                    bossSprite->GetCollisionGridCellValue ());
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckWeaponSprite (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the weapon sprite been created?

    if (m_weaponSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the weapon sprite.

        WeaponSpritePtr &weaponSprite(m_weaponSpriteDrawingElement.m_sprite);

        // Get the state of the weapon sprite.

        switch (weaponSprite->GetState ())
        {
        case WeaponSprite::STATE_TERMINATED:
            // The weapon sprite is terminated.

            // Play the weapon sprite terminated sound.

            weaponSprite->PlayWeaponsSpriteSound ();
          
            // Reset the weapon sprite

            m_weaponSpriteDrawingElement.Reset ();
            break;

        case WeaponSprite::STATE_INITIALISED:
            // The weapon sprite is initialised.

            // Play the weapon sprite initialised sound.

            weaponSprite->PlayWeaponsSpriteSound ();
            
            // Carefull.
            //          .
            //          .

        case WeaponSprite::STATE_STATIC:
        case WeaponSprite::STATE_MOVING:
            // Move the weapon sprite.

            status = weaponSprite->Move (graphics, m_collisionGrid);

            if (status == ERR_SUCCESS)
            {
                // Set the weapon sprite's drawing element's top-left screen position.

                m_weaponSpriteDrawingElement.m_drawingElement->SetScreenTopLeft (weaponSprite->GetScreenXLeft (), 
                                                                                 weaponSprite->GetScreenYTop ());

                // Has the weapon sprite collided with a nasty sprite?

                Folio::Core::Game::CollisionGrid::CellElements  cellCollisionElements;

                if (m_collisionGrid.IsCollision (m_weaponSpriteDrawingElement.m_drawingElement->GetScreenRect (),
                                                 Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE,
                                                 cellCollisionElements))
                {
                    // Yes. Handle the collision.

                    status = HandleCollision (cellCollisionElements, false);    // Weapon collision.
                } // Endif.

            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StartWeaponSprite ()
{
    // If a weapon sprites has not been created, then add add a weapon sprite to the screen.

    return (m_weaponSpriteDrawingElement.IsCreated () ? ERR_SUCCESS : AddWeaponSprite (GetMainPlayerWeaponSpriteId (m_mainPlayer)));
} // Endproc.


FolioStatus Screen::AddWeaponSprite (WEAPON_SPRITE_ID weaponSpriteId)
{
    // Create the weapon sprite.

    WeaponSpritePtr   weaponSprite(new WeaponSpritePtr::element_type);
    
    FolioStatus status = weaponSprite->Create (m_canvas->GetCanvasDcHandle (),
                                               weaponSpriteId,
                                               *m_spriteGraphicsMap,
                                               m_mainPlayer->GetScreenRect (),
                                               m_mainPlayer->GetDirection ());

    if (status == ERR_SUCCESS)
    {
        // The weapon sprite is initialised.

        weaponSprite->SetState (WeaponSprite::STATE_INITIALISED);

        // Create a weapon sprite drawing element.

        status = m_weaponSpriteDrawingElement.Create (weaponSprite, 
                                                      DRAWING_ELEMENT_WEAPON_SPRITE, 
                                                      weaponSprite->GetCollisionGridCellValue ());
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveWeaponSprite ()
{
    FolioStatus status = ERR_SUCCESS;

    // Has the weapon sprite been created?

    if (m_weaponSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the weapon sprite.

        WeaponSpritePtr &weaponSprite(m_weaponSpriteDrawingElement.m_sprite);

        // The weapon sprite should be terminated,

        weaponSprite->SetState (WeaponSprite::STATE_TERMINATE_RQD);
    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus Screen::CheckMainPlayer (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the state of the main player.

    switch (m_mainPlayer->GetState ())
    {
    case PlayerSprite::STATE_INITIALISED:
    case PlayerSprite::STATE_STATIC:
        // The main player is static.

        status = m_mainPlayer->Static (graphics, m_collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Process the main player.

            status = ProcessMainPlayer (graphics);
        } // Endif.
        break;

    case PlayerSprite::STATE_MOVING:
        // Move the main player.

        status = m_mainPlayer->Move (graphics, PlayerSprite::MAIN_PLAYER_SPEED, m_collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Process the main player.
            
            status = ProcessMainPlayer (graphics);
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus Screen::ProcessMainPlayer (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the main player exited a screen?

    if (m_mainPlayer->IsExitedScreen ())
    {
        // Yes. Did the main player exit the screen though a trap door?

        if (BackgroundItem::IsTrapDoor (reinterpret_cast<BackgroundItem *> (m_mainPlayer->GetScreenExit ().m_userData)->GetBackgroundItemId ()))
        {
            // Yes. The main player is falling.

            m_mainPlayer->SetState (PlayerSprite::STATE_FALLING);
        } // Endif.

    } // Endif.

    else
    {
        // No. Is the main player at a locked exit?

        if (m_mainPlayer->IsAtLockedScreenExit ()) 
        {
            // Yes. Get the background item.

            BackgroundItem  &backgroundItem(*reinterpret_cast<BackgroundItem *> (m_mainPlayer->GetScreenExit ().m_userData));

            // Can the door be unlocked?

            if (CanDoorBeUnlocked (backgroundItem))
            {
                // Yes. Is this the exit door?

                if (BackgroundItem::IsExitDoor (backgroundItem.GetBackgroundItemFlags ()))
                {   
                    // Yes. The main player has completed the game.

                    m_mainPlayer->SetCompletedGame ();
                } // Endif.

                else
                {
                    // No. Open the door

                    status = OpenDoor (backgroundItem);
                } // Endelse.

            } // Endif.

        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Has the main player collided with another object?

            Folio::Core::Game::CollisionGrid::CellElements  cellCollisionElements;

            if (m_collisionGrid.IsCollision (m_mainPlayer->GetScreenRect (), cellCollisionElements))
            {
                // Yes. Handle the collision.

                status = HandleCollision (cellCollisionElements, true); // Main player collision.
            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // Can the main player fire a weapon?

                if (m_mainPlayer->CanFireWeapon ())
                {
                    // Yes. Start it.

                    status = StartWeaponSprite ();
                } // Endif.

                // Can the main player collect items, and are there any collected 
                // items in the information panel?

                else
                if (m_mainPlayer->CanCollectItems () && 
                    m_informationPanel->IsAnyCollectedItem ())
                {
                    // Yes. We need to cycle the collected items in the information panel.

                    InformationPanel::DroppedItem   droppedItem;

                    status = m_informationPanel->CycleCollectedItems (droppedItem);

                    // Has an item been dropped?

                    if ((status == ERR_SUCCESS) && droppedItem.IsPopulated ())
                    {
                        // Yes. Add it.

                        status = AddDroppedItem (droppedItem);
                    } // Endif.

                } // Endif.

            } // Endif.
        
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus Screen::HandleCollision (const Folio::Core::Game::CollisionGrid::CellElements   &cellCollisionElements,
                                     bool                                                   mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Handle any collision.

    for (Folio::Core::Game::CollisionGrid::CellElements::const_iterator itr = cellCollisionElements.begin ();
         (status == ERR_SUCCESS) && (itr != cellCollisionElements.end ());
         ++itr)
    {
        switch (itr->GetCollisionGridCellValue ())
        {
        case Folio::Core::Game::CollisionGrid::CELL_VALUE_SOLID_ITEM:
            // Handle the collision with a solid item.

            status = HandleSolidItemCollision (*itr, mainPlayer);
            break;

        case Folio::Core::Game::CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM:
            // Can the main player collect items?

            if (m_mainPlayer->CanCollectItems ())
            {
                // Yes. Handle the collision with a collectable item.

                status = HandleCollectableItemCollision (*itr, mainPlayer);

                // The main player can no longer collect items.

                m_mainPlayer->SetCanCollectItems (false);
            } // Endif.
            break;

        case Folio::Core::Game::CollisionGrid::CELL_VALUE_HEALTH_ITEM:
            // Handle the collision with a health item.

            status = HandleHealthItemCollision (*itr, mainPlayer);
            break;

        case Folio::Core::Game::CollisionGrid::CELL_VALUE_HARMFUL_ITEM:
            // Handle the collision with a harmful item.

            status = HandleHarmfulItemCollision (*itr, mainPlayer);
            break;

        case Folio::Core::Game::CollisionGrid::CELL_VALUE_NASTY_SPRITE:
            // Handle the collision with a nasty sprite.

            status = HandleNastySpriteCollision (*itr, mainPlayer);
            break;

        case Folio::Core::Game::CollisionGrid::CELL_VALUE_BOSS_SPRITE:
            // Handle the collision with a boss sprite.

            status = HandleBossSpriteCollision (*itr, mainPlayer);
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::HandleSolidItemCollision (const Folio::Core::Game::DrawingElement   &drawingElement,
                                              bool                                      mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Get the drawing element's user data.

        Folio::Core::Game::DrawingElement::UserData userData = drawingElement.GetUserData ();

        // Find the solid item that has been collided with.

        Folio::Core::Game::DrawingElementsSet::iterator itr = m_drawingElementsSet.begin ();

        bool    found = false;  // Initialise!

        do
        {
            // Is this the solid item that has been collided with?

            if (itr->GetUserData () == userData)
            {
                // Yes. Get the main player's position.

                Int32   mainPlayerXLeft     = m_mainPlayer->GetScreenXLeft ();
                Int32   mainPlayerYTop      = m_mainPlayer->GetScreenYTop ();
                Int32   mainPlayerXRight    = m_mainPlayer->GetScreenXRight ();
                Int32   mainPlayerYBottom   = m_mainPlayer->GetScreenYBottom ();
                Int32   mainPlayerWidth     = m_mainPlayer->GetScreenWidth ();
                Int32   mainPlayerHeight    = m_mainPlayer->GetScreenHeight ();

                // Get the solid item's position.

                Int32   solidItemXLeft      = itr->GetScreenXLeft ();
                Int32   solidItemYTop       = itr->GetScreenYTop ();
                Int32   solidItemXRight     = itr->GetScreenXRight ();
                Int32   solidItemYBottom    = itr->GetScreenYBottom ();

                // Get the main player's direction.

                PlayerSprite::Direction  direction = m_mainPlayer->GetDirection ();

                switch (direction)
                {
                case PlayerSprite::N:
                    mainPlayerYTop = solidItemYBottom + 1; 
                    break;

                case PlayerSprite::S:
                    mainPlayerYTop = solidItemYTop - mainPlayerHeight; 
                    break;

                case PlayerSprite::E:
                    mainPlayerXLeft = solidItemXLeft - mainPlayerWidth; 
                    break;
 
                case PlayerSprite::W:
                    mainPlayerXLeft = solidItemXRight + 1; 
                    break;
            
                case PlayerSprite::NE:
                case PlayerSprite::NW:
                case PlayerSprite::SE:
                case PlayerSprite::SW:
                    if ((direction == PlayerSprite::NE) ||
                        (direction == PlayerSprite::NW))
                    {
                        if ((mainPlayerYTop < solidItemYBottom) &&
                            (mainPlayerYBottom > solidItemYBottom))
                        {
                            // Check floor bound.

                            Int32   floorBottomBound = m_collisionGrid.GetFloorBottomBound ();

                            if ((solidItemYBottom + 1 + mainPlayerHeight) < floorBottomBound)
                            {
                                mainPlayerYTop = solidItemYBottom + 1;
                            } // Endif.

                            else
                            {
                                mainPlayerYTop = floorBottomBound - mainPlayerHeight + 1;
                            } // Endelse.

                        } // Endif.
                 
                    } // Endif.
                
                    else
                    if ((mainPlayerYTop < solidItemYTop) &&
                        (mainPlayerYBottom > solidItemYTop))
                    {
                        // Check floor bound.

                        Int32   floorTopBound = m_collisionGrid.GetFloorTopBound ();

                        if ((solidItemYTop - mainPlayerHeight) > floorTopBound)
                        {
                            mainPlayerYTop = solidItemYTop - mainPlayerHeight; 
                        } // Endif.

                        else
                        {
                            mainPlayerYTop = floorTopBound; 
                        } // Endelse.

                    } // Endelseif.

                    if ((direction == PlayerSprite::NE) ||
                        (direction == PlayerSprite::SE))
                    {
                        if ((mainPlayerXLeft < solidItemXLeft)  &&
                            (mainPlayerXRight > solidItemXLeft))
                        {
                            // Check floor bound.

                            Int32   floorLeftBound = m_collisionGrid.GetFloorLeftBound ();

                            if ((solidItemXLeft - mainPlayerWidth) > floorLeftBound)
                            {
                                mainPlayerXLeft = solidItemXLeft - mainPlayerWidth; 
                            } // Endif.

                            else
                            {
                                mainPlayerXLeft = floorLeftBound; 
                            } // Endelse.

                        } // Endif.

                    } // Endif.

                    else
                    if ((mainPlayerXLeft < solidItemXRight) &&
                        (mainPlayerXRight > solidItemXRight))
                    {
                        // Check floor bound.

                        Int32   floorRightBound = m_collisionGrid.GetFloorRightBound ();

                        if ((solidItemXRight + 1 + mainPlayerWidth) < floorRightBound)
                        {
                            mainPlayerXLeft = solidItemXRight + 1;
                        } // Endif.

                        else
                        {
                            mainPlayerXLeft = floorRightBound - mainPlayerWidth + 1;
                        } // Endelse.
                
                    } // Endelseif.
                    break;

                default:
                    break;
                } // Endswitch.

                // Set the main player's position.

                m_mainPlayer->SetScreenTopLeft (mainPlayerXLeft, mainPlayerYTop);

                found = true;   // Found the solid item.
            } // Endif.

            else
            {
                ++itr;
            } // Endelse.

        } // Enddo.
        while (!found                   && 
               (status == ERR_SUCCESS)  && 
               (itr != m_drawingElementsSet.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleCollectableItemCollision (const Folio::Core::Game::DrawingElement &drawingElement,
                                                    bool                                    mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Get the drawing element's user data.

        Folio::Core::Game::DrawingElement::UserData userData = drawingElement.GetUserData ();

        // Find the collectable item that has been collided with.

        StaticSpriteDrawingElementsList::iterator   itr = m_staticSpriteDrawingElementsList.begin ();

        bool    found = false;  // Initialise!

        do
        {              
            // Is this the collectable item that has been collided with?

            if (itr->m_sprite.get () == userData)
            {
                // Yes. Get the static sprite.

                StaticSpritePtr staticSprite = itr->m_sprite;

                // Remove it.

                status = RemoveStaticSprite (staticSprite);

                if (status == ERR_SUCCESS)
                {
                    // An item has been collected.

                    InformationPanel::DroppedItem   droppedItem;

                    status = m_informationPanel->AddCollectedItem (staticSprite, droppedItem);

                    // Has an item been dropped?

                    if ((status == ERR_SUCCESS) && droppedItem.IsPopulated ())
                    {
                        // Yes. Add it to the screen.

                        status = AddDroppedItem (droppedItem);
                    } // Endif.

                } // Endif.

                found = true;   // Found the collectable item.
            } // Endif.

            else
            {
                ++itr;
            } // Endelse.

        } // Enddo.
        while (!found                   && 
               (status == ERR_SUCCESS)  && 
               (itr != m_staticSpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleHealthItemCollision (const Folio::Core::Game::DrawingElement  &drawingElement,
                                               bool                                     mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Get the drawing element's user data.

        Folio::Core::Game::DrawingElement::UserData userData = drawingElement.GetUserData ();

        // Find the health item that has been collided with.

        StaticSpriteDrawingElementsList::iterator   itr = m_staticSpriteDrawingElementsList.begin ();

        bool    found = false;  // Initialise!

        do
        {              
            // Is this the health item that has been collided with?

            if (itr->m_sprite.get () == userData)
            {
                // Yes. Get the static sprite.

                StaticSpritePtr staticSprite = itr->m_sprite;

                // Remove it.

                status = RemoveStaticSprite (staticSprite);

                if (status == ERR_SUCCESS)
                {
                    // Increment the main player's health.

                    status = IncrementMainPlayerHealth (InformationPanel::PLAYER_HEALTH_HEALTH_ITEM_INCREMENT);
                } // Endif.

                found = true;   // Found the health item.
            } // Endif.

            else
            {
                ++itr;
            } // Endelse.

        } // Enddo.
        while (!found                   && 
               (status == ERR_SUCCESS)  && 
               (itr != m_staticSpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleHarmfulItemCollision (const Folio::Core::Game::DrawingElement &drawingElement,
                                                bool                                    mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Decrement the main player's health.

        status = DecrementMainPlayerHealth (InformationPanel::PLAYER_HEALTH_HARMFUL_ITEM_DECREMENT);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleNastySpriteCollision (const Folio::Core::Game::DrawingElement &drawingElement,
                                                bool                                    mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the drawing element's user data.

    Folio::Core::Game::DrawingElement::UserData userData = drawingElement.GetUserData ();

    // Find the nasty sprite that has been collided with.

    bool    found = false;  // Initialise!

    for (NastySpriteDrawingElementsList::iterator itr = m_nastySpriteDrawingElementsList.begin ();
         !found && (status == ERR_SUCCESS) && (itr != m_nastySpriteDrawingElementsList.end ());
         ++itr)
    {              
        // Is this the nasty sprite that has been collided with?

        if (itr->m_sprite.get () == userData)
        {
            // Yes. Is the nasty sprite ready?
            
            if (itr->m_sprite->IsReady ())
            {
                // Yes. Remove the nasty sprite from the screen's collision grid.

                status = RemoveCollisionGridDrawingElement (*(itr->m_drawingElement));

                if (status == ERR_SUCCESS)
                {
                    // Has the main player collided with the nasty sprite?

                    if (mainPlayer)
                    {
                        // Yes. Decrement the main player's health.
        
                        status = DecrementMainPlayerHealth (InformationPanel::PLAYER_HEALTH_NASTY_SPRITE_DECREMENT);
                    } // Endif.

                    else
                    {
                        // No. Remove the weapon sprite.

                        status = RemoveWeaponSprite ();
                    } // Endelse.

                    if (status == ERR_SUCCESS)
                    {
                        // The nasty sprite is dead.

                        itr->m_sprite->SetDead ();

                        // Increment the score.

                        m_informationPanel->IncrementScore (InformationPanel::SCORE_NASTY_SPRITE_DEAD);
                    } // Endif.
                    
                } // Endif.

            } // Endif.

            found = true;   // Found the nasty sprite.
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleBossSpriteCollision (const Folio::Core::Game::DrawingElement  &drawingElement,
                                               bool                                     mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Get the boss sprite.

        BossSpritePtr   &bossSprite(m_bossSpriteDrawingElement.m_sprite);

        // Is the boss sprite ready?
            
        if (bossSprite->IsReady ())
        {
            // Can the boss sprite be killed?

            if (bossSprite->CanBeKilled (*m_informationPanel))
            {
                // Yes. Remove the boss sprite from the screen's collision grid.

                status = RemoveCollisionGridDrawingElement (*(m_bossSpriteDrawingElement.m_drawingElement));

                if (status == ERR_SUCCESS)
                {
                    // The boss sprite is dead.

                    bossSprite->SetDead ();

                    // Increment the score.

                    m_informationPanel->IncrementScore (InformationPanel::SCORE_BOSS_SPRITE_DEAD);
                } // Endif.

            } // Endif.
            
            else
            {
                // No. Decrement the main player's health.
        
                status = DecrementMainPlayerHealth (InformationPanel::PLAYER_HEALTH_BOSS_SPRITE_DECREMENT);
            } // Endelse.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DecrementMainPlayerHealth (UInt32 healthDecrement)
{
    // Decrement the main player's health.

    bool    mainPlayerIsDead = false;    // Initialise!

    FolioStatus status = m_informationPanel->DecrementMainPlayerHealth (healthDecrement,
                                                                        mainPlayerIsDead);

    // Is the main player dead?

    if (mainPlayerIsDead && (status == ERR_SUCCESS))
    {
        // Yes. Kill the nasty sprites.

        status = KillNastySprites ();

        if (status == ERR_SUCCESS)
        {
            // Remove the weapon sprite.

            status = RemoveWeaponSprite ();

            if (status == ERR_SUCCESS)
            {
                // The main player is dead.

                m_mainPlayer->SetDead ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::IncrementMainPlayerHealth (UInt32 healthIncrement)
{
    return (m_informationPanel->IncrementMainPlayerHealth (healthIncrement));
} // Endproc.


FolioStatus Screen::AddDroppedItem (InformationPanel::DroppedItem &droppedItem)
{
    // Set the dropped item's static sprite position.

    droppedItem.m_staticSprite->SetScreenTopLeft (m_mainPlayer->GetScreenXLeft (),
                                                  m_mainPlayer->GetScreenYBottom () - droppedItem.m_staticSprite->GetScreenHeight () + 1);

    // Add the dropped item's static sprite.

    return (AddStaticSprite (droppedItem.m_staticSprite));
} // Endproc.


FolioStatus Screen::InitialiseCollisionGrid ()
{
    FolioStatus status = ERR_SUCCESS;

    // Initialise the screen's collision grid.

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::DrawingElementsSet::iterator itr = m_drawingElementsSet.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_drawingElementsSet.end ());
         ++itr)
    {
        switch (itr->GetDrawingElementId ())
        {
        case DRAWING_ELEMENT_BACKGROUND_ITEM:
            // Add the background item to the collision grid.

            status = AddCollisionGridDrawingElement (*itr);
            break;                            

        case DRAWING_ELEMENT_INFORMATION_PANEL_ITEM:
            // No more drawing elements to add to the collision grid.

            finished = true;
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::AddCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the drawing elements to the screen's collision grid.

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
         ++itr)
    {
        switch (itr->GetDrawingElementId ())
        {
        case DRAWING_ELEMENT_BACKGROUND_ITEM:
            // Is the background item's collision grid cell value empty?

            if (!Folio::Core::Game::CollisionGrid::IsEmpty (itr->GetCollisionGridCellValue ()))
            {
                // No. Add the background item to the collision grid.

                status = AddCollisionGridDrawingElement (*itr);
            } // Endif.
            break;                            

        case DRAWING_ELEMENT_INFORMATION_PANEL_ITEM:
            // No more drawing elements to add to the collision grid.
            
            finished = true;
            break;                            

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::AddCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement)
{
    FolioStatus status = ERR_SUCCESS;

    switch (drawingElement.GetDrawingElementId ())
    {
    case DRAWING_ELEMENT_BACKGROUND_ITEM:
        {
            Folio::Core::Game::CollisionGrid::CellValue collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

            // Is this an exit?

            if (Folio::Core::Game::CollisionGrid::IsExit (collisionGridCellValue))
            {
                // Get the background item.

                BackgroundItem  *backgroundItem = reinterpret_cast<BackgroundItem *> (drawingElement.GetUserData ());

                // Is the exit a door and not already in the collision grid?

                if (IsDoor (*backgroundItem) && 
                    !m_collisionGrid.IsScreenExit (backgroundItem))
                {
                    // Yes. Add the screen exit to the collision grid.
                    
                    status = m_collisionGrid.AddScreenExit (Folio::Core::Game::CollisionGrid::ScreenExit(backgroundItem->GetDoorOrientation (),
                                                                                                         drawingElement.GetScreenRect (),
                                                                                                         GetDoorState (*backgroundItem),
                                                                                                         backgroundItem));
                } // Endif.

            } // Endif.

            // Is the background item's collision grid cell value empty?

            else
            if (!Folio::Core::Game::CollisionGrid::IsEmpty (collisionGridCellValue))
            {
                // No. Add the background item's drawing elements to the collision grid.

                status = m_collisionGrid.AddDrawingElement (drawingElement);
            } // Endelseif.

        } // Endscope.
        break;

    case DRAWING_ELEMENT_STATIC_SPRITE:
        {
            UInt32  collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

            // Is the static sprite's collision grid cell value empty?

            if (!Folio::Core::Game::CollisionGrid::IsEmpty (collisionGridCellValue))
            {
                // No. Add the static sprite's drawing element to the collision grid.

                status = m_collisionGrid.AddDrawingElement (drawingElement);
            } // Endif.

        } // Endscope.
        break;                            

    case DRAWING_ELEMENT_NASTY_SPRITE:
    case DRAWING_ELEMENT_BOSS_SPRITE:
    case DRAWING_ELEMENT_WEAPON_SPRITE:
        // Always add this sprite's drawing element to the collision grid.

        status = m_collisionGrid.AddDrawingElement (drawingElement);
        break;                            

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Remove the drawing elements from the screen's collision grid.

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
         ++itr)
    {
        switch (itr->GetDrawingElementId ())
        {
        case DRAWING_ELEMENT_BACKGROUND_ITEM:
            // Is the background item's collision grid cell value empty?

            if (!Folio::Core::Game::CollisionGrid::IsEmpty (itr->GetCollisionGridCellValue ()))
            {
                // No. Remove the background item from the collision grid.

                status = RemoveCollisionGridDrawingElement (*itr);
            } // Endif.
            break;                            

        case DRAWING_ELEMENT_INFORMATION_PANEL_ITEM:
            // No more drawing elements to remove from the collision grid.
            
            finished = true;
            break;                            

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement)
{
    FolioStatus status = ERR_SUCCESS;

    switch (drawingElement.GetDrawingElementId ())
    {
    case DRAWING_ELEMENT_BACKGROUND_ITEM:
        {
            Folio::Core::Game::CollisionGrid::CellValue collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

            // Is this an exit?

            if (Folio::Core::Game::CollisionGrid::IsExit (collisionGridCellValue))
            {
                // Get the background item.

                BackgroundItem  *backgroundItem = reinterpret_cast<BackgroundItem *> (drawingElement.GetUserData ());

                // Is the exit in the collision grid?

                if (m_collisionGrid.IsScreenExit (backgroundItem))
                {
                    // Yes. Remove the screen exit from the collision grid.

                    status = m_collisionGrid.RemoveScreenExit (Folio::Core::Game::CollisionGrid::ScreenExit(backgroundItem->GetDoorOrientation (),
                                                                                                            drawingElement.GetScreenRect (),
                                                                                                            Folio::Core::Game::CollisionGrid::ScreenExit::CLOSED,
                                                                                                            backgroundItem));
                } // Endif.

            } // Endif.

            // Is the background item's collision grid cell value empty?

            else
            if (!Folio::Core::Game::CollisionGrid::IsEmpty (collisionGridCellValue))
            {
                // No. Remove the background item's drawing element from the collision grid.

                status = m_collisionGrid.RemoveDrawingElement (drawingElement);
            } // Endelseif.

        } // Endscope.
        break;

    case DRAWING_ELEMENT_STATIC_SPRITE:
        {
            UInt32  collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

            // Is the static sprite's collision grid cell value empty?

            if (!Folio::Core::Game::CollisionGrid::IsEmpty (collisionGridCellValue))
            {
                // No. Remove the static sprite's drawing element from the collision grid.

                status = m_collisionGrid.RemoveDrawingElement (drawingElement);
            } // Endif.

        } // Endscope.
        break;                            

    case DRAWING_ELEMENT_NASTY_SPRITE:
    case DRAWING_ELEMENT_BOSS_SPRITE:
    case DRAWING_ELEMENT_WEAPON_SPRITE:
        // Always remove this sprite's drawing element from the collision grid.

        status = m_collisionGrid.RemoveDrawingElement (drawingElement);
        break;                            

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus Screen::UpdateCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement &drawingElement)
{
    FolioStatus status = ERR_SUCCESS;

    switch (drawingElement.GetDrawingElementId ())
    {
    case DRAWING_ELEMENT_NASTY_SPRITE:
    case DRAWING_ELEMENT_BOSS_SPRITE:
    case DRAWING_ELEMENT_WEAPON_SPRITE:
        // Always update this sprite's drawing element in the collision grid.

        status = m_collisionGrid.UpdateDrawingElement (drawingElement);
        break;                            

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus Screen::AddBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList)
{
    // Add the drawing elements to the screen's drawing elements.

    m_drawingElementsSet.insert (drawingElementsList.begin (),
                                 drawingElementsList.end ());

    // Add the drawing elements to the screen's collision grid.

    FolioStatus status = AddCollisionGridDrawingElements (drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the drawing elements in the canvas.

        status = m_canvas->DrawDrawingElements (drawingElementsList);
    } // Endif.

    return (status);
} // Endif.


FolioStatus Screen::RemoveBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList)
{
    // Remove the background item's drawing elements from the screen's drawing elements.
    // But don't remove from the screen's collision grid.

    return (RemoveScreenDrawingElements (drawingElementsList, false)); 
} // Endif.


FolioStatus Screen::BuildScreenDrawingElements ()
{
    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas->GetCanvasDcHandle ();

    // Query the room's drawing elements.

    Folio::Core::Game::DrawingElementsList  roomDrawingElementsList;

    FolioStatus status = m_roomGraphic->QueryDrawingElements (dcHandle,
                                                              m_roomColour,
                                                              roomDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Add the room's drawing element to the screen's drawing elements.

        m_drawingElementsSet.insert (roomDrawingElementsList.begin (),
                                     roomDrawingElementsList.end ());

        // Add the screen's background items to the screen's drawing elements.

        for (BackgroundItemsList::const_iterator itr = m_backgroundItemsList.begin ();
             (status == ERR_SUCCESS) && (itr != m_backgroundItemsList.end ());
             ++itr)
        {
            // Get the background item's drawing elements.

            Folio::Core::Game::DrawingElementsList  backgroundItemDrawingElementsList;

            status = itr->get ()->QueryDrawingElements (dcHandle,
                                                        m_roomColour,
                                                        backgroundItemDrawingElementsList);

            if (status == ERR_SUCCESS)
            {
                // Add the background item's drawing elements to the screen's 
                // drawing elements.

                m_drawingElementsSet.insert (backgroundItemDrawingElementsList.begin (),
                                             backgroundItemDrawingElementsList.end ());
            } // Endif.

        } // Endfor.

        if (status == ERR_SUCCESS)
        {
            // Get the information panel's drawing elements.

            Folio::Core::Game::DrawingElementsList  informationPanelDrawingElementsList;

            status = m_informationPanel->QueryDrawingElements (dcHandle,
                                                               m_roomColour, 
                                                               informationPanelDrawingElementsList);

            if (status == ERR_SUCCESS)
            {
                // Add the information panel's drawing elements to the screen's drawing elements.

                m_drawingElementsSet.insert (informationPanelDrawingElementsList.begin (),
                                             informationPanelDrawingElementsList.end ());
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveScreenDrawingElements (const Folio::Core::Game::DrawingElementsList &drawingElementsList, 
                                                 bool                                         removeFromCollisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Remove the drawing elements from the screen's collision grid?

    if (removeFromCollisionGrid)
    {
        // Yes.

        status = RemoveCollisionGridDrawingElements (drawingElementsList);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Remove the drawing elements from the screen's drawing elements.

        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
             ++itr)
        {
            // Remove the drawing elements that match the user data.

            status = RemoveScreenDrawingElements (itr->GetUserData ());
        } // Endfor.

    } // Endif.

    return (status);
} // Endif.


FolioStatus Screen::RemoveScreenDrawingElements (Folio::Core::Game::DrawingElement::UserData userData)
{
    // Remove the drawing elements that match the user data.

    Folio::Core::Game::DrawingElementsSet::iterator itr = m_drawingElementsSet.begin ();

    while (itr != m_drawingElementsSet.end ())
    {
        if (itr->GetUserData () == userData)
        {
            // Remove the drawing element from the screen's drawing elements set.

            itr = m_drawingElementsSet.erase (itr);
        } // Endif.

        else
        {
            ++itr;
        } // Endelse.

    } // Endwhile.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus Screen::RemoveScreenDrawingElements (DRAWING_ELEMENT_ID drawingElementId)
{
    // Remove the drawing elements that match the drawing element identifier.

    Folio::Core::Game::DrawingElementsSet::iterator itr = m_drawingElementsSet.begin ();

    while (itr != m_drawingElementsSet.end ())
    {
        if (itr->GetDrawingElementId () == drawingElementId)
        {
            // Remove the drawing element from the screen's drawing elements set.

            itr = m_drawingElementsSet.erase (itr);
        } // Endif.

        else
        {
            ++itr;
        } // Endelse.

    } // Endwhile.

    return (ERR_SUCCESS);
} // Endproc.


Folio::Core::Game::DrawingElementsList  Screen::FindScreenDrawingElements (Folio::Core::Game::DrawingElement::UserData userData) const
{
    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    for (Folio::Core::Game::DrawingElementsSet::iterator itr = m_drawingElementsSet.begin ();
         itr != m_drawingElementsSet.end ();
         ++itr)
    {
        if (itr->GetUserData () == userData)
        {
            drawingElementsList.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (drawingElementsList);
} // Endfor.


Folio::Core::Game::DrawingElementsList  Screen::FindScreenDrawingElements (DRAWING_ELEMENT_ID drawingElementId) const
{
    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    for (Folio::Core::Game::DrawingElementsSet::iterator itr = m_drawingElementsSet.begin ();
         itr != m_drawingElementsSet.end ();
         ++itr)
    {
        if (itr->GetDrawingElementId () == drawingElementId)
        {
            drawingElementsList.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (drawingElementsList);
} // Endfor.


void    Screen::CreateScreenSoundSamples ()
{
    // Create the screen's entered screen sound samples.

    CreateEnteredScreenSoundSamples ();
} // Endproc.


void    Screen::CreateEnteredScreenSoundSamples ()
{
    if (m_enteredScreenSoundSamples.empty ())
    {
        // Create each sound sample representing the required sound.
    
        ZxSpectrum::BYTE    frequency = 0xf7;

        for (ZxSpectrum::BYTE numLoops = 0x09; numLoops >= 0x01; --numLoops)
        {
            m_enteredScreenSoundSamples.push_back (ZxSpectrum::MapUltimateMakeSound (frequency, numLoops));

            if (frequency == 0xff)
            {
                frequency = 0x87;
            } // Endif.

            else
            {
                frequency += 0x8;
            } // Endelse.

        } // Endfor.

    } // Endif.

} // Endproc.


void    Screen::PlayScreenSounds ()
{
    // Play the entered screen sound.

    PlayEnteredScreenSound ();
} // Endproc.


bool    Screen::PlayEnteredScreenSound ()
{
    bool    playedEnteredScreenSound = false;   // Initialise!

    // Should an entered screen sound be played?

    if (m_playEnteredScreenSound)
    {
        // Yes. Play the entered screen sound.

        Folio::Core::Util::Sound::PlaySoundSample (m_enteredScreenSoundSamples [m_currentEnteredScreenSoundSampleIndex]);

        // All entered screen sounds played?

        if (++m_currentEnteredScreenSoundSampleIndex >= m_enteredScreenSoundSamples.size ())
        {
            // Yes.

            m_playEnteredScreenSound                = false;
            m_currentEnteredScreenSoundSampleIndex  = 0;
        } // Endif.

        playedEnteredScreenSound = true;
    } // Endif.

    return (playedEnteredScreenSound);
} // Endproc.


FolioStatus BuildScreens (Folio::Core::Applet::Canvas       &canvas,
                          const RoomGraphicsMap             &roomGraphicsMap,
                          const BackgroundItemGraphicsMap   &backgroundItemGraphicsMap,
                          const SpriteGraphicsMap           &spriteGraphicsMap,
                          const BackgroundItemsList         &backgroundItemsList,
                          const StaticSpritesList           &staticSpritesList,
                          const InformationPanel            &informationPanel,
                          ScreensList                       &screensList)
{
    FolioStatus status = ERR_SUCCESS;

    screensList.clear ();   // Initialise!

    // Build the screens list.

    screensList.insert (screensList.end (),
                        g_screensTable,
                        g_screensTable  + (sizeof (g_screensTable) / sizeof (Screen)));

    for (ScreensList::iterator itr = screensList.begin ();
         itr != screensList.end ();
         ++itr)
    {
        // Set the canvas.

        itr->SetCanvas (canvas);

        // Set the screen's room graphic.

        itr->SetRoomGraphic (roomGraphicsMap);

        // Set the sprite graphics map.

        itr->SetSpriteGraphicsMap (spriteGraphicsMap);

        // Set the information panel.

        itr->SetInformationPanel (informationPanel);

        // Set the screen's background items.

        itr->SetBackgroundItemsList (GetScreenBackgroundItemsList (itr->GetScreenNumber (), backgroundItemsList));

        // Set the screen's static sprites.

        itr->SetStaticSpritesList (GetScreenStaticSpritesList (itr->GetScreenNumber (), staticSpritesList));
    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
