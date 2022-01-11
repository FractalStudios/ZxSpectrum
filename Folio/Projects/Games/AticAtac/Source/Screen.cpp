// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "Screen.h"
#include    "Ultimate.h"

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
    {     0,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {     1,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {     2,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {     3,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {     4,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {     5,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {     6,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {     7,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {     8,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {     9,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    10,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    11,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    12,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    13,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    14,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    15,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    16,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    17,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    18,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    19,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    20,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    21,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    22,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    23,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    24,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    25,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    26,            ROOM_5,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    27,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    28,            ROOM_8,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    29,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    30,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    31,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    32,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    33,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    34,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    35,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    36,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    37,            ROOM_2,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    38,            ROOM_5,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    39,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    40,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    41,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    42,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    43,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    44,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    45,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    46,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    47,            ROOM_5,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    48,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    49,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    50,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    51,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    52,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    53,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    54,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    55,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    56,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    57,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    58,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    59,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    60,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    61,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    62,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    63,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    64,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    65,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    66,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    67,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    68,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    69,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    70,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    71,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    72,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    73,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    74,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    75,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    76,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    77,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    78,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    79,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    80,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    81,            ROOM_10,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    82,            ROOM_9,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    83,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    84,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    85,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    86,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    87,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    88,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    89,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    90,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {    91,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    92,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {    93,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {    94,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    95,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    96,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {    97,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {    98,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {    99,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   100,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   101,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {   102,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   103,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   104,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   105,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   106,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   107,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   108,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   109,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   110,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   111,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {   112,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   113,            ROOM_5,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   114,            ROOM_5,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   115,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   116,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   117,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   118,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   119,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   120,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   121,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {   122,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   123,            ROOM_3,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   124,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   125,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   126,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   127,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   128,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   129,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   130,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   131,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {   132,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   133,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   134,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   135,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   136,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   137,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   138,            ROOM_0,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   139,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   140,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   141,            ROOM_4,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {   142,            ROOM_11,    Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   143,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   144,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    {   145,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   146,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   147,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   148,            ROOM_1,     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
};
  

// Screen static members.
bool    Screen::m_playEnteredScreenSound                = true; // Indicates if the entered screen sound should be played.
UInt32  Screen::m_currentEnteredScreenSoundSampleIndex  = 0;    // The current entered screen sound sample index.
Folio::Core::Util::Sound::SoundSamplesList  Screen::m_enteredScreenSoundSamples;    // The entered screen sound samples.

Folio::Core::Util::Sound::SoundSample   Screen::m_openDoorSoundSample(Ultimate::CreateDoorSoundSample ());  // The open door sound sample.
Folio::Core::Util::Sound::SoundSample   Screen::m_closeDoorSoundSample(Ultimate::CreateDoorSoundSample ()); // The close door sound sample.

Screen::Screen ()
:   m_canvas(0),
    m_informationPanel(0),
    m_screenInitialised(false),
    m_screenNumber(SCREEN_NUMBER_UNDEFINED),
    m_roomId(ROOM_UNDEFINED),
    m_roomColour(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_exitScreenTickCount(0),
    m_createNastySpriteTickCount(0)
{         
} // Endproc.
          

Screen::Screen (UInt32                                  screenNumber,
                ROOM_ID                                 roomId,
                Folio::Core::Game::ZxSpectrum::COLOUR   roomColour)
:   m_canvas(0),
    m_informationPanel(0),
    m_screenInitialised(false),
    m_screenNumber(screenNumber),
    m_roomId(roomId),
    m_roomColour(roomColour),
    m_exitScreenTickCount(0),       
    m_createNastySpriteTickCount(0)
{
} // Endproc.


Screen::~Screen ()
{
    // Release the screen's resource graphics.

    ReleaseResourceGraphics ();
} // Endproc.


void    Screen::SetCanvas (Folio::Core::Applet::Canvas& canvas)
{
    m_canvas = &(canvas);
} // Endproc.


void    Screen::SetBackgroundItemsList (const BackgroundItemsList& backgroundItemsList)
{
    m_backgroundItemsList = backgroundItemsList;
} // Endproc.


void    Screen::SetStaticSpritesList (const StaticSpritesList& staticSpritesList)
{
    m_staticSpritesList = staticSpritesList;
} // Endproc.


void    Screen::SetInformationPanel (const InformationPanel& informationPanel)
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


Folio::Core::Game::ZxSpectrum::COLOUR   Screen::GetRoomColour () const
{
    return (m_roomColour);
} // Endproc.


FolioStatus Screen::QueryDrawingElements (Folio::Core::Game::DrawingElementsList& drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear();    // Initialise!

    // Is the screen initialised?

    if (IsScreenInitialised ())
    {
        // Yes. Enter the screen.

        status = EnterScreen ();
    } // Endif.

    else
    {
        // No. Initialise the screen.

        status = InitialiseScreen ();
    } // Endelse.

    if (status == ERR_SUCCESS)
    {
        // Start any screen boss sprite.
                                    
        status = StartBossSprite ();

        if (status == ERR_SUCCESS)
        {
            // Any screen drawing elements?

            if (!m_drawingElementsList.empty ())
            {
                // Yes. Add the drawing elements of the screen to the drawing elements list.

                drawingElementsList = m_drawingElementsList; 
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleProcessFrame (bool& isStarting)
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
                    // Yes.

                    status = HandleMainPlayerDead ();
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::QueryNewScreen (UInt32& newScreenNumber)
{
    newScreenNumber = SCREEN_NUMBER_UNDEFINED;  // Initialise!

    // Exit the current screen.

    FolioStatus status = ExitScreen ();

    if (status == ERR_SUCCESS)
    {
        // Get the current screen exit.

        BackgroundItem  *screenExitBackgroundItem(reinterpret_cast<BackgroundItem *> (g_mainPlayer->GetScreenExit ().m_userData));
        
       // Get the new screen number.

        newScreenNumber = GetNewScreenNumber (screenExitBackgroundItem, g_backgroundItemsList);

        // Get the new screen entrance.

        BackgroundItemPtr   screenEntranceBackgroundItem(GetOppositeDoor (screenExitBackgroundItem, g_backgroundItemsList));

        // Is the new screen's entrance closed?

        if (BackgroundItem::IsClosedDoor (screenEntranceBackgroundItem->GetBackgroundItemFlags ()))
        {
            // Yes. Open it.

            status = screenEntranceBackgroundItem->SetDoorOpen ();
        } // Endif.

        // Is the new screen's entrance locked?

        else
        if (BackgroundItem::IsLockedDoor (screenEntranceBackgroundItem->GetBackgroundItemFlags ()))
        {
            // Yes. Unlock it.

            status = screenEntranceBackgroundItem->SetDoorUnlocked ();
        } // Endelseif.

        if (status == ERR_SUCCESS)
        {
            // Set the main player's position.

            switch (screenEntranceBackgroundItem->GetDoorOrientation ())
            {
            case CollisionGrid::ScreenExit::TOP:
                status = g_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft () + (screenEntranceBackgroundItem->GetScreenWidth () - g_mainPlayer->GetScreenWidth ()) / 2,
                                                         screenEntranceBackgroundItem->GetScreenYTop ());
                break;

            case CollisionGrid::ScreenExit::BOTTOM:
                status = g_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft () + (screenEntranceBackgroundItem->GetScreenWidth () - g_mainPlayer->GetScreenWidth ()) / 2,
                                                         screenEntranceBackgroundItem->GetScreenYTop () + screenEntranceBackgroundItem->GetScreenHeight () - g_mainPlayer->GetScreenHeight ());
                break;

            case CollisionGrid::ScreenExit::LEFT:
                status = g_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft (),
                                                         screenEntranceBackgroundItem->GetScreenYTop () + (screenEntranceBackgroundItem->GetScreenHeight () - g_mainPlayer->GetScreenHeight ()) / 2);
                break;

            case CollisionGrid::ScreenExit::RIGHT:
                status = g_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft (),
                                                         screenEntranceBackgroundItem->GetScreenYTop () + (screenEntranceBackgroundItem->GetScreenHeight () - g_mainPlayer->GetScreenHeight ()) / 2);
                break;

            case CollisionGrid::ScreenExit::FLOOR:
                status = g_mainPlayer->SetScreenTopLeft (screenEntranceBackgroundItem->GetScreenXLeft () + (screenEntranceBackgroundItem->GetScreenWidth () - g_mainPlayer->GetScreenWidth ()) / 3,
                                                         screenEntranceBackgroundItem->GetScreenYTop () + (screenEntranceBackgroundItem->GetScreenHeight () - g_mainPlayer->GetScreenHeight ()) / 2);
                break;

            default:
                break;
            } // Endswitch.

            if (status == ERR_SUCCESS)
            {
                // The main player is at a screen entrance.

                g_mainPlayer->SetScreenEntrance (CollisionGrid::ScreenEntrance(screenEntranceBackgroundItem->GetDoorOrientation (),
                                                                               screenEntranceBackgroundItem->GetScreenRect (),
                                                                               CollisionGrid::ScreenEntrance::OPEN,
                                                                               screenEntranceBackgroundItem.get ()));

                // Play the entered screen sound.

                m_playEnteredScreenSound                = true;
                m_currentEnteredScreenSoundSampleIndex  = 0;
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StoreSpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    // Store the static sprites' underlying backgrounds.
    
    FolioStatus status = Folio::Core::Game::StoreSpriteBackgrounds<StaticSpriteDrawingElementsList> (graphics, 
                                                                                                     m_staticSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Store the nasty sprites' underlying backgrounds.
    
        status = StoreNastySpriteBackgrounds (graphics);

        if (status == ERR_SUCCESS)
        {
            // Store the boss sprite's underlying background.
    
            status = g_bossSpriteDrawingElement.StoreSpriteBackground (graphics);

            if (status == ERR_SUCCESS)
            {
                // Store the weapon sprite's underlying background.
    
                status = g_weaponSpriteDrawingElement.StoreSpriteBackground (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Store the main player's underlying background.

                    status = g_mainPlayer->StoreUnderlyingBackground (graphics);
                } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RestoreSpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    // Restore the static sprites' underlying backgrounds.
    
    FolioStatus status = Folio::Core::Game::RestoreSpriteBackgrounds<StaticSpriteDrawingElementsList> (graphics, 
                                                                                                       m_staticSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Restore the nasty sprites' underlying backgrounds.
    
        status = RestoreNastySpriteBackgrounds (graphics);

        if (status == ERR_SUCCESS)
        {
            // Restore the boss sprite's underlying background.
    
            status = g_bossSpriteDrawingElement.RestoreSpriteBackground (graphics);

            if (status == ERR_SUCCESS)
            {
                // Restore the weapon sprite's underlying background.
    
                status = g_weaponSpriteDrawingElement.RestoreSpriteBackground (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Restore the main player's underlying background.
        
                    status = g_mainPlayer->RestoreUnderlyingBackground (graphics);
                } // Endif.
    
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawSprites (Gdiplus::Graphics& graphics)
{
    // Draw the static sprites.
    
    FolioStatus status = Folio::Core::Game::DrawSprites<StaticSpriteDrawingElementsList> (graphics, 
                                                                                          m_staticSpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Draw the nasty sprites.
    
        status = DrawNastySprites (graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the boss sprite.
    
            status = g_bossSpriteDrawingElement.DrawSprite (graphics);

            if (status == ERR_SUCCESS)
            {
                // Draw the weapon sprite.
    
                status = g_weaponSpriteDrawingElement.DrawSprite (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Draw the main player.

                    status = g_mainPlayer->Draw (graphics);

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

    return (AddStaticSprite (STATIC_SPRITE_GRAVESTONE, g_mainPlayer->GetScreenRect ()));
} // Endproc.


UInt32  Screen::GetTotalNumRooms ()
{
    return (sizeof (g_screensTable) / sizeof (Screen));
} // Endproc.


Folio::Core::Game::ResourceGraphicsCache::OwnerId   Screen::MakeOwnerId (UInt32 screenNumber)
{
    return (TXT("Screen ") + Folio::Core::Game::ResourceGraphicsCache::MakeOwnerId (screenNumber));
} // Endproc.


bool    Screen::IsScreenInitialised () const
{
    return (m_screenInitialised);
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

        status = BuildScreenDrawingElements (true);

        if (status == ERR_SUCCESS)
        {
            // Initialise the screen's collision grid.

            status = InitialiseCollisionGrid ();

            if (status == ERR_SUCCESS)
            {
                // Build the screen's static sprites.

                status = BuildStaticSprites (true);

                if (status == ERR_SUCCESS)
                {
                    // Increment the number of rooms visited.

                    m_informationPanel->IncrementNumRoomsVisited ();

                    m_playEnteredScreenSound = true;

                    m_screenInitialised = true;
                } // Endif.
        
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::EnterScreen ()
{
    FolioStatus status = ERR_SUCCESS;

    // Should the screen's nasty sprites be removed?

    if (m_exitScreenTickCount &&
        (Folio::Core::Util::DateTime::GetCurrentTickCount () > (m_exitScreenTickCount + MAX_REMOVE_NASTY_SPRITES_TICK_COUNT)))
    {
        // Yes. Remove the screen's nasty sprites.

        status = RemoveNastySprites ();
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        m_exitScreenTickCount           = 0;    // Reset the screen's exit screen tick count.
        m_createNastySpriteTickCount    = 0;    // Reset the screen's nasty sprite tick count.

        // Destroy the weapon sprite's drawing element.

        g_weaponSpriteDrawingElement.DestroyDrawingElement ();

        // Build the screen's drawing elements.

        status = BuildScreenDrawingElements (false);

        if (status == ERR_SUCCESS)
        {
            // Build the screen's static sprites.

            status = BuildStaticSprites (false);

            if (status == ERR_SUCCESS)
            {
                // Open or close the screen's doors.

                status = CheckDoors (true); // We're entering the screen.
            } // Endif.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::ExitScreen ()
{
    // Release the screen's graphics from the resource graphics cache.

    FolioStatus status = ReleaseResourceGraphics ();

    if (status == ERR_SUCCESS)
    {
        // Clear the screen's drawing elements.

        m_drawingElementsList.clear ();

        // Clear the screen's static sprite drawing elements.
        
        m_staticSpriteDrawingElementsList.clear ();

        // Remove the boss sprite.

        RemoveBossSprite ();

        // Destroy the weapon sprite's drawing element.

        g_weaponSpriteDrawingElement.DestroyDrawingElement ();

        // Note the screen's exit screen tick count.

        m_exitScreenTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
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

                if (!g_mainPlayer->IsInScreenExit (backgroundItem.GetScreenRect ()) &&
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
        
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::CheckDoors (bool enteringScreen)
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
            // Yes. Is the screen being entered?
            
            if (enteringScreen)
            {
                // Yes. Is this an open door?

                if (BackgroundItem::IsOpenDoor (backgroundItemflags))
                {
                    // Yes. Make sure the door is open.
                        
                    status = OpenDoor (backgroundItem, enteringScreen);
                } // Endif.

                // Is this a closed door?

                else
                if (BackgroundItem::IsClosedDoor (backgroundItemflags))
                {
                    // Yes. Make sure the door is closed.
                
                    status = CloseDoor (backgroundItem, enteringScreen);
                } // Endelseif.

            } // Endif.
            
            else
            {
                // Is this a door that can be closed?

                if (BackgroundItem::CanDoorBeClosed (backgroundItemflags))
                {
                    // Yes. Should the door be closed? 

                    if (backgroundItem.IsDoorTransition (Folio::Core::Util::DateTime::GetCurrentTickCount ()))
                    {
                        // Yes. The door cannot be closed if the main player is in it.

                        if (g_mainPlayer->IsInScreenExit (backgroundItem.GetScreenRect ()))
                        {
                            // Just restart the door transition.

                            backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());
                        } // Endif.

                        else
                        {
                            // Close the door.
                
                           status = CloseDoor (backgroundItem, enteringScreen);
                        } // Endelse.

                    } // Endif.

                } // Endif.

                // Is this a closed door?

                else
                if (BackgroundItem::IsClosedDoor (backgroundItemflags))
                {
                    // Yes. Should the door be opened? 
                
                    if (backgroundItem.IsDoorTransition (Folio::Core::Util::DateTime::GetCurrentTickCount ()))
                    {
                        // Yes. Open the door.
                
                        status = OpenDoor (backgroundItem, enteringScreen);
                    } // Endif.

                } // Endelseif.
        
            } // Endelse.

        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::OpenDoor (BackgroundItem&   backgroundItem, 
                              bool              enteringScreen)
{
    // Open the door.

    return (UpdateDoor (backgroundItem, true, enteringScreen));
} // Endproc.


FolioStatus Screen::CloseDoor (BackgroundItem&  backgroundItem, 
                               bool             enteringScreen)
{
    // Close the door.

    return (UpdateDoor (backgroundItem, false, enteringScreen));
} // Endproc.


FolioStatus Screen::UpdateDoor (BackgroundItem& backgroundItem,
                                bool            openDoor,
                                bool            enteringScreen)
{
    // Remove the background item's drawing elements from the screen's drawing elements.

    FolioStatus status = RemoveBackgroundItemDrawingElements (FindScreenDrawingElements (&(backgroundItem))); 

    if (status == ERR_SUCCESS)
    {
        if (openDoor)
        {
            // Open the door.

            status = backgroundItem.SetDoorOpen (true);

            if (status == ERR_SUCCESS)
            {
                // Open the screen exit.

                status = m_collisionGrid.OpenScreenExit (&(backgroundItem));
            } // Endif.

        } // Endif.

        else
        {
            // Close the door.

            status = backgroundItem.SetDoorClosed (true);

            if (status == ERR_SUCCESS)
            {
                // Close the screen exit.

                status = m_collisionGrid.CloseScreenExit (&(backgroundItem));
            } // Endif.

        } // Endelse.

        if (status == ERR_SUCCESS)
        {
            // Get the background item's drawing elements.

            Folio::Core::Game::DrawingElementsList  drawingElementsList;

            FolioStatus status = backgroundItem.QueryDrawingElements (m_canvas->GetCanvasDcHandle (),
                                                                      m_roomColour,
                                                                      drawingElementsList,
                                                                      openDoor || !enteringScreen ? true : false);  // If the door is closed and the screen is being entered, the mask is not required.

            if ((status == ERR_SUCCESS) && !drawingElementsList.empty ())
            {
                // Add the background item's drawing elements to the screen's drawing elements.

                status = AddBackgroundItemDrawingElements (drawingElementsList);

                if (status == ERR_SUCCESS)
                {
                    // Set the door transition tick count.

                    backgroundItem.SetDoorTransitionTickCount (Folio::Core::Util::DateTime::GetCurrentTickCount ());

                    if (!enteringScreen)
                    {
                        // Play the open/close door sound sample.

                        status = Folio::Core::Util::Sound::PlaySoundSample (openDoor 
                                                                            ? m_openDoorSoundSample 
                                                                            : m_closeDoorSoundSample);
                    } // Endif.

                } // Endif.

            } // Endif.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    Screen::IsDoor (const BackgroundItem& backgroundItem) const
{
    bool    isDoor = false; // Initialise!

    // Get the background item's flags.

    UInt32  backgroundItemflags = backgroundItem.GetBackgroundItemFlags ();

    // Depending on the main player, certain background items are secret doors.

    switch (g_mainPlayer->GetPlayerSpriteId ())
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


CollisionGrid::ScreenExit::STATE    Screen::GetDoorState (const BackgroundItem& backgroundItem) const
{
    CollisionGrid::ScreenExit::STATE    doorState = CollisionGrid::ScreenExit::CLOSED;  // Initialise!

    // Get the background item's flags.

    UInt32  backgroundItemflags = backgroundItem.GetBackgroundItemFlags ();

    // Get the background item's identifier.

    BACKGROUND_ITEM_ID  backgroundItemId = backgroundItem.GetBackgroundItemId ();

    // Is the door open?

    if (BackgroundItem::IsOpenDoor (backgroundItemflags))
    {
        // Yes.

        doorState = CollisionGrid::ScreenExit::OPEN;
    } // Endif.

    // Is the door locked?

    else
    if (BackgroundItem::IsLockedDoor (backgroundItemflags) ||
        BackgroundItem::IsExitDoor (backgroundItemflags))
    {
        // Yes.

        doorState = CollisionGrid::ScreenExit::LOCKED;
    } // Endelseif.

    else
    {
        // Depending on the main player, certain background items are secret doors.

        switch (g_mainPlayer->GetPlayerSpriteId ())
        {
        case PLAYER_SPRITE_WIZARD:
            if (BackgroundItem::IsWizardDoor (backgroundItemflags))
            {
                doorState = CollisionGrid::ScreenExit::OPEN;
            } // Endif.
            break;

        case PLAYER_SPRITE_SERF:
            if (BackgroundItem::IsSerfDoor (backgroundItemflags))
            {
                doorState = CollisionGrid::ScreenExit::OPEN;
            } // Endif.
            break;

        case PLAYER_SPRITE_KNIGHT:
        default:
            if (BackgroundItem::IsKnightDoor (backgroundItemflags))
            {
                doorState = CollisionGrid::ScreenExit::OPEN;
            } // Endif.
            break;
        } // Endswitch.

    } // Endelse.

    return (doorState);
} // Endproc.


bool    Screen::CanDoorBeUnlocked (const BackgroundItem& backgroundItem) const
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


FolioStatus Screen::CheckSprites (Gdiplus::Graphics& graphics)
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


FolioStatus Screen::BuildStaticSprites (bool initialise)
{
    FolioStatus status = ERR_SUCCESS;

    m_staticSpriteDrawingElementsList.clear (); // Initialise!

    if (!m_staticSpritesList.empty ())
    {
        // Get the canvas device context.

        FolioHandle dcHandle = m_canvas->GetCanvasDcHandle ();

        // Add each static sprite to the screen.

        for (StaticSpritesList::const_iterator itr = m_staticSpritesList.begin ();
             (status == ERR_SUCCESS) && (itr != m_staticSpritesList.end ());
             ++itr)
        {
            // Create the static sprite.

            status = itr->get ()->Create (dcHandle);

            if (status == ERR_SUCCESS)
            {
                // Add the static sprite to the screen.

                status = AddStaticSprite (*itr, false);
            } // Endif.

        } // Endfor.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckStaticSprites (Gdiplus::Graphics& graphics)
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


FolioStatus Screen::AddStaticSprite (const StaticSpritePtr& staticSprite,
                                     bool                   addToStaticSpritesList)
{
    if (addToStaticSpritesList)
    {
        // Add to the screen's static sprite list.

        m_staticSpritesList.push_back (staticSprite);
    } // Endif.
    
    // Create a static sprite drawing element.

    StaticSpriteDrawingElement  staticSpriteDrawingElement(Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE,
                                                           staticSprite);

    // Add to the screen's static sprite drawing elements list.

    m_staticSpriteDrawingElementsList.push_back (staticSpriteDrawingElement);

    // Add the static sprite to the screen's collision grid.

    return (AddCollisionGridDrawingElement (*(staticSpriteDrawingElement.m_drawingElement)));
} // Endproc.


FolioStatus Screen::AddStaticSprite (STATIC_SPRITE_ID       staticSpriteId,
                                     const Gdiplus::Rect&   screenRect)
{
    // Create the static sprite.

    StaticSpritePtr staticSprite(new StaticSpritePtr::element_type);
    
    FolioStatus status = staticSprite->Create (m_canvas->GetCanvasDcHandle (),
                                               staticSpriteId,
                                               m_screenNumber,
                                               screenRect.X,
                                               screenRect.Y + screenRect.Height - 1, // Screen Y bottom.
                                               StaticSprite::GetStaticSpriteColour (staticSpriteId));

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
    
            status = g_bossSpriteDrawingElement.RestoreSpriteBackground (*graphics);

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
        
                        status = g_bossSpriteDrawingElement.StoreSpriteBackground (*graphics);
                    } // Endif.
 
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveStaticSprite (const StaticSpritePtr& staticSprite)
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

    if (status == ERR_SUCCESS)
    {
        // Release the sprite's graphic resource.

        status = staticSprite->ReleaseResourceGraphics ();

        if (status == ERR_SUCCESS)
        {
            // Remove the static sprite from the screen's static sprite list.

            m_staticSpritesList.erase (std::remove(m_staticSpritesList.begin (), 
                                                   m_staticSpritesList.end (), 
                                                   staticSprite), 
                                       m_staticSpritesList.end ());
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


StaticSpriteDrawingElementsList::iterator   Screen::FindStaticSprite (const StaticSpritePtr& staticSprite)
{
    return (std::find_if (m_staticSpriteDrawingElementsList.begin (), m_staticSpriteDrawingElementsList.end (), 
                          [&staticSprite](const StaticSpriteDrawingElement& arg) {return (arg.m_sprite == staticSprite);}));
} // Endproc.


FolioStatus Screen::CheckNastySprites (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the main player ready or dying?

    bool    isMainPlayerReady   = g_mainPlayer->IsReady ();
    bool    isMainPlayerDying   = g_mainPlayer->IsDying ();

    if (isMainPlayerReady || isMainPlayerDying)
    {
        // Yes. Is the main player ready?

        if (isMainPlayerReady)
        {
            // Yes. Have we created all the nasty sprites for this screen?

            UInt32  numNastySpritesOnScreen = GetNumNastySpritesOnScreen ();

            if (numNastySpritesOnScreen < MAX_NASTY_SPRITES_PER_SCREEN)
            {
                // No. Start any nasty sprites.

                status = StartNastySprites (graphics, numNastySpritesOnScreen);
            } // Endif.

        } // Endif.

        if ((status == ERR_SUCCESS) && !g_nastySpriteDrawingElementsList.empty ())
        {
            // Process all the nasty sprites for this screen.

            NastySpriteDrawingElementsList::iterator    itr = g_nastySpriteDrawingElementsList.begin ();

            do
            {
                // Get the nasty sprite.

                NastySpritePtr  &nastySprite(itr->m_sprite);

                // Is the nasty sprite on this screen?

                if (nastySprite->GetNastySpriteScreenNumber () == m_screenNumber)
                {
                    // Yes. Get the state of the nasty sprite.

                    switch (nastySprite->GetState ())
                    {
                    case NastySprite::STATE_INITIALISED:
                        // The nasty sprite is initialised.

                        // Set the nasty sprite's drawing element's collision grid cell value.

                        itr->m_drawingElement->SetCollisionGridCellValue (CollisionGrid::CELL_VALUE_NASTY_SPRITE);

                        // The nasty sprite is static.

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

                            status = itr->m_drawingElement->SetScreenTopLeft (nastySprite->GetScreenXLeft (), 
                                                                              nastySprite->GetScreenYTop ());

                            if (status == ERR_SUCCESS)
                            {
                                // Update the nasty sprite in the screen's collision grid.

                                status = UpdateCollisionGridDrawingElement (*(itr->m_drawingElement));
                            } // Endif.

                        } // Endif.
                        break;

                    default:
                        break;
                    } // Endswitch.

                    // Is the nasty sprite dead?

                    if (nastySprite->IsDead ())
                    {
                        // Yes. Remove the nasty sprite from the nasty sprite 
                        // drawing elements list.

                        itr = g_nastySpriteDrawingElementsList.erase (itr);
                    } // Endif.
                
                    else
                    {
                        ++itr;  // Next nasty sprite.
                    } // Endelse.

                } // Endif.

                else
                {
                    // No.

                    ++itr;  // Next nasty sprite.
                } // Endelse.

            } // Enddo.
            while ((status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ()));
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StartNastySprites (Gdiplus::Graphics&   graphics,
                                       UInt32               numNastySpritesOnScreen)
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

            UInt32  numNastySpritesToCreate = Folio::Core::Util::Random::GetRandomNumber(1, MAX_NASTY_SPRITES_PER_SCREEN - numNastySpritesOnScreen);

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
    // Remove a nasty sprite drawing element from the nasty sprite drawing 
    // elements list, as required.

    FolioStatus status = RemoveNastySpriteDrawingElement (m_screenNumber,
                                                          MAX_NASTY_SPRITE_DRAWING_ELEMENTS,
                                                          g_nastySpriteDrawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Create the nasty sprite.

        NastySpritePtr  nastySprite(new NastySpritePtr::element_type);
    
        status = nastySprite->Create (m_canvas->GetCanvasDcHandle (),
                                      nastySpriteId,
                                      m_screenNumber,
                                      m_collisionGrid);
       
        if (status == ERR_SUCCESS)
        {
            // Create a nasty sprite drawing element.

            NastySpriteDrawingElement   nastySpriteDrawingElement(Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE, 
                                                                  nastySprite);

            // Add the nasty sprite drawing element to the nasty sprite drawing 
            // elements list.

            status = AddNastySpriteDrawingElement (nastySpriteDrawingElement,
                                                   g_nastySpriteDrawingElementsList);

            if (status == ERR_SUCCESS)
            {
                // Add nasty sprite to the screen's collision grid.

                status = AddCollisionGridDrawingElement (*(nastySpriteDrawingElement.m_drawingElement));
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveNastySprites (bool onScreenEntry)
{
    FolioStatus status = ERR_SUCCESS;

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Remove all the nasty sprites on the screen.

        NastySpriteDrawingElementsList::iterator    itr = g_nastySpriteDrawingElementsList.begin ();

        do
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on this screen?

            if (nastySprite->GetNastySpriteScreenNumber () == m_screenNumber)
            {
                // Yes. Remove the nasty sprite from the screen's collision grid.

                status = RemoveCollisionGridDrawingElement (*(itr->m_drawingElement));

                if (status == ERR_SUCCESS)
                {
                    if (onScreenEntry)
                    {
                        // Remove the nasty sprite from the nasty sprite drawing 
                        // elements list.

                        itr = g_nastySpriteDrawingElementsList.erase (itr);
                    } // Endif.

                    else
                    {
                        // The nasty sprite is dead.

                        nastySprite->SetDead (false); // Don't play its terminating sound.
                        
                        ++itr;  // Next nasty sprite.
                    } // Endelse.

                } // Endif.
            
            } // Endif.

            else
            {
                // No.

                ++itr;  // Next nasty sprite.
            } // Endelse.

        } // Enddo.
        while ((status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::StoreNastySpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Store all the nasty sprites' backgrounds for this screen.

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on this screen?

            if (nastySprite->GetNastySpriteScreenNumber () == m_screenNumber)
            {
                // Yes. Store the nasty sprite's background.

                status = nastySprite->StoreUnderlyingBackground (graphics);
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RestoreNastySpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Restore all the nasty sprites' backgrounds for this screen.

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on this screen?

            if (nastySprite->GetNastySpriteScreenNumber () == m_screenNumber)
            {
                // Yes. Restore the nasty sprite's background.

                status = nastySprite->RestoreUnderlyingBackground (graphics);
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::DrawNastySprites (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Draw all the nasty sprites for this screen.

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on this screen?

            if (nastySprite->GetNastySpriteScreenNumber () == m_screenNumber)
            {
                // Draw the nasty sprite.

                status = nastySprite->Draw (graphics);
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


UInt32  Screen::GetNumNastySpritesOnScreen () const
{
    UInt32  numNastySpritesOnScreen = 0;    // Initialise!

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        for (NastySpriteDrawingElementsList::const_iterator itr = g_nastySpriteDrawingElementsList.begin ();
             itr != g_nastySpriteDrawingElementsList.end ();
             ++itr)
        {
            // Get the nasty sprite.

            const NastySpritePtr    &nastySprite(itr->m_sprite);

            // Is the nasty sprite on this screen?

            if (nastySprite->GetNastySpriteScreenNumber () == m_screenNumber)
            {
                numNastySpritesOnScreen++;
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (numNastySpritesOnScreen);
} // Endproc.


void    Screen::SetCreateNastySpriteTickCount (UInt32   currentTickCount,
                                               UInt32   minNumSeconds, 
                                               UInt32   maxNumSeconds)
{
    m_createNastySpriteTickCount = currentTickCount + 
                                   500 * Folio::Core::Util::Random::GetRandomNumber (minNumSeconds, maxNumSeconds);
} // Endproc.


FolioStatus Screen::CheckBossSprite (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the boss sprite been created?

    if (g_bossSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the boss sprite.

        BossSpritePtr   &bossSprite(g_bossSpriteDrawingElement.m_sprite);

        // Get the state of the boss sprite.

        switch (bossSprite->GetState ())
        {
        case NastySprite::STATE_INITIALISED:
            // The boss sprite is initialised.

            status = bossSprite->Static (graphics, m_collisionGrid);
            break;

        case BossSprite::STATE_TERMINATED:
            // The boss sprite is terminated.

            // Destroy the boss sprite.

            g_bossSpriteDrawingElement.Destroy ();
            break;

        case BossSprite::STATE_STATIC:
        case BossSprite::STATE_MOVING:
            // Move the boss sprite.

            status = bossSprite->Move (graphics, *m_informationPanel, m_collisionGrid);

            if (status == ERR_SUCCESS)
            {
                // Set the boss sprite's drawing element's top-left screen position.

                status = g_bossSpriteDrawingElement.m_drawingElement->SetScreenTopLeft (bossSprite->GetScreenXLeft (), 
                                                                                        bossSprite->GetScreenYTop ());

                if (status == ERR_SUCCESS)
                {
                    // Update the boss sprite in the screen's collision grid.

                    status = UpdateCollisionGridDrawingElement (*(g_bossSpriteDrawingElement.m_drawingElement));
                } // Endif.

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

    // Does the screen support a boss sprite?

    if (g_bossSpriteDrawingElement.IsSprite ())
    {
        // Yes. Get the boss sprite.

        BossSpritePtr   &bossSprite(g_bossSpriteDrawingElement.m_sprite);

        // Is the boss sprite alive?

        if (bossSprite->IsAlive ())
        {
            // Yes. Add the boss sprite to the screen.

            status = AddBossSprite ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::AddBossSprite ()
{
    // Get the boss sprite.

    BossSpritePtr   &bossSprite(g_bossSpriteDrawingElement.m_sprite);

    // Start the boss sprite.

    FolioStatus status = bossSprite->Start (*m_informationPanel, m_collisionGrid);

    if (status == ERR_SUCCESS)
    {
        // Create a boss sprite drawing element.

        status = g_bossSpriteDrawingElement.CreateDrawingElement (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE, 
                                                                  bossSprite->GetCollisionGridCellValue ());

        if (status == ERR_SUCCESS)
        {
            // Add boss sprite to the screen's collision grid.

            status = AddCollisionGridDrawingElement (*(g_bossSpriteDrawingElement.m_drawingElement));
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveBossSprite (bool onScreenExit)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the boss sprite been created?

    if (g_bossSpriteDrawingElement.IsCreated ())
    {
        // Yes. Remove the boss sprite from the screen's collision grid.

        status = RemoveCollisionGridDrawingElement (*(g_bossSpriteDrawingElement.m_drawingElement));

        if (status == ERR_SUCCESS)
        {
            if (onScreenExit)
            {
                // Destroy the boss sprite.

                g_bossSpriteDrawingElement.Destroy ();
            } // Endif.

            else
            {
                // Get the boss sprite.

                BossSpritePtr   &bossSprite(g_bossSpriteDrawingElement.m_sprite);

                // The boss sprite is dead.

                bossSprite->SetDead ();
            } // Endelse.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::CheckWeaponSprite (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the weapon sprite been created?

    if (g_weaponSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the weapon sprite.

        WeaponSpritePtr &weaponSprite(g_weaponSpriteDrawingElement.m_sprite);

        // Get the state of the weapon sprite.

        switch (weaponSprite->GetState ())
        {
        case WeaponSprite::STATE_TERMINATED:
            // The weapon sprite is terminated.

            // Play the weapon sprite terminated sound.

            weaponSprite->PlayWeaponSpriteTerminatedSound ();
          
            // Destroy the weapon sprite's drawing element.

            g_weaponSpriteDrawingElement.DestroyDrawingElement ();
            break;

        case WeaponSprite::STATE_INITIALISED:
            // The weapon sprite is initialised.

            // Play the weapon sprite initialised sound.

            weaponSprite->PlayWeaponSpriteInitialisedSound ();
            
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

                status = g_weaponSpriteDrawingElement.m_drawingElement->SetScreenTopLeft (weaponSprite->GetScreenXLeft (), 
                                                                                          weaponSprite->GetScreenYTop ());

                if (status == ERR_SUCCESS)
                {
                    // Has the weapon sprite collided with a nasty sprite?

                    CollisionGrid::CellElements cellElements;

                    if (m_collisionGrid.IsCollision (g_weaponSpriteDrawingElement.m_drawingElement->GetScreenRect (),
                                                     CollisionGrid::CELL_VALUE_NASTY_SPRITE,
                                                     cellElements))
                    {
                        // Yes. Handle the collision.

                        status = HandleCollision (cellElements, false);    // Weapon collision.
                    } // Endif.

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
    // If a weapon sprite has not been created, then add add a weapon sprite to the screen.

    return (g_weaponSpriteDrawingElement.IsCreated () ? ERR_SUCCESS : AddWeaponSprite ());
} // Endproc.


FolioStatus Screen::AddWeaponSprite ()
{
    // Get the weapon sprite.

    WeaponSpritePtr &weaponSprite(g_weaponSpriteDrawingElement.m_sprite);

    // Start the weapon sprite.

    FolioStatus status = weaponSprite->Start ();

    if (status == ERR_SUCCESS)
    {
        // Create a weapon sprite drawing element.

        status = g_weaponSpriteDrawingElement.CreateDrawingElement (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_WEAPON_SPRITE, 
                                                                    weaponSprite->GetCollisionGridCellValue ());
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveWeaponSprite (bool bPlayTerminatedSound)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the weapon sprite been created?

    if (g_weaponSpriteDrawingElement.IsCreated ())
    {
        // Yes. Get the weapon sprite.

        WeaponSpritePtr &weaponSprite(g_weaponSpriteDrawingElement.m_sprite);

        // The weapon sprite is stopped,

        weaponSprite->Stop (bPlayTerminatedSound);
    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus Screen::CheckMainPlayer (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the state of the main player.

    switch (g_mainPlayer->GetState ())
    {
    case PlayerSprite::STATE_INITIALISED:
    case PlayerSprite::STATE_STATIC:
        // The main player is static.

        status = g_mainPlayer->Static (graphics, m_collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Process the main player.

            status = ProcessMainPlayer (graphics);
        } // Endif.
        break;

    case PlayerSprite::STATE_MOVING:
        // Move the main player.

        status = g_mainPlayer->Move (graphics, PlayerSprite::MAIN_PLAYER_SPEED, m_collisionGrid);

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


FolioStatus Screen::ProcessMainPlayer (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the main player exited a screen?

    if (g_mainPlayer->IsExitedScreen ())
    {
        // Yes. Did the main player exit the screen though a trap door?

        if (BackgroundItem::IsTrapDoor (reinterpret_cast<BackgroundItem *> (g_mainPlayer->GetScreenExit ().m_userData)->GetBackgroundItemId ()))
        {
            // Yes. The main player is falling.

            g_mainPlayer->SetState (PlayerSprite::STATE_FALLING);
        } // Endif.

    } // Endif.

    else
    {
        // No. Is the main player at a locked exit?

        if (g_mainPlayer->IsAtLockedScreenExit ()) 
        {
            // Yes. Get the screen exit.

            BackgroundItem  *screenExitBackgroundItem(reinterpret_cast<BackgroundItem *> (g_mainPlayer->GetScreenExit ().m_userData));

            // Can the door be unlocked?

            if (CanDoorBeUnlocked (*screenExitBackgroundItem))
            {
                // Yes. Is this the exit door?

                if (BackgroundItem::IsExitDoor (screenExitBackgroundItem->GetBackgroundItemFlags ()))
                {   
                    // Yes. The main player has completed the game.

                    g_mainPlayer->SetGameCompleted ();
                } // Endif.

                else
                {
                    // No. Unlock the door.

                    status = screenExitBackgroundItem->SetDoorUnlocked (true);

                    if (status == ERR_SUCCESS)
                    {
                        // Get the opposite door.

                        BackgroundItemPtr   oppositeExitBackgroundItem(GetOppositeDoor (screenExitBackgroundItem, g_backgroundItemsList));
                    
                        // Unlock the opposite door.

                        status = oppositeExitBackgroundItem->SetDoorUnlocked ();

                        if (status == ERR_SUCCESS)
                        {
                            // Open the door.

                            status = OpenDoor (*screenExitBackgroundItem, true);
                        } // Endif.

                    } // Endif.

                } // Endelse.

            } // Endif.

        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Has the main player collided with another object?

            CollisionGrid::CellElements cellElements;

            if (m_collisionGrid.IsCollision (g_mainPlayer->GetScreenRect (), cellElements))
            {
                // Yes. Handle the collision.

                status = HandleCollision (cellElements, true); // Main player collision.
            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // Can the main player fire a weapon?

                if (g_mainPlayer->CanFireWeapon ())
                {
                    // Yes. Start the weapon sprite.

                    status = StartWeaponSprite ();
                } // Endif.

                // Can the main player collect items, and are there any collected 
                // items in the information panel?

                else
                if (g_mainPlayer->CanCollectItems () && 
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


FolioStatus Screen::HandleCollision (const CollisionGrid::CellElements& cellElements,
                                     bool                               mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Handle any collision.

    for (CollisionGrid::CellElements::const_iterator itr = cellElements.begin ();
         (status == ERR_SUCCESS) && (itr != cellElements.end ());
         ++itr)
    {
        switch (itr->m_cellValue)
        {
        case CollisionGrid::CELL_VALUE_SOLID_ITEM:
            // Handle the collision with a solid item.

            status = HandleSolidItemCollision (*itr, mainPlayer);
            break;

        case CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM:
            // Can the main player collect items?

            if (g_mainPlayer->CanCollectItems ())
            {
                // Yes. Handle the collision with a collectable item.

                status = HandleCollectableItemCollision (*itr, mainPlayer);

                // The main player can no longer collect items.

                g_mainPlayer->SetCanCollectItems (false);
            } // Endif.
            break;

        case CollisionGrid::CELL_VALUE_HEALTH_ITEM:
            // Handle the collision with a health item.

            status = HandleHealthItemCollision (*itr, mainPlayer);
            break;

        case CollisionGrid::CELL_VALUE_HARMFUL_ITEM:
            // Handle the collision with a harmful item.

            status = HandleHarmfulItemCollision (*itr, mainPlayer);
            break;

        case CollisionGrid::CELL_VALUE_NASTY_SPRITE:
            // Handle the collision with a nasty sprite.

            status = HandleNastySpriteCollision (*itr, mainPlayer);
            break;

        case CollisionGrid::CELL_VALUE_BOSS_SPRITE:
            // Handle the collision with a boss sprite.

            status = HandleBossSpriteCollision (*itr, mainPlayer);
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::HandleSolidItemCollision (const CollisionGrid::CellElement& cellElement,
                                              bool                              mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. The main player is bound to the solid item.

        Gdiplus::Rect   mainPlayerScreenRect(g_mainPlayer->GetScreenRect ());
                
        m_collisionGrid.ToScreenRectBound (g_mainPlayer->GetDirection (), 
                                           cellElement.m_collisionGridRect,
                                           mainPlayerScreenRect);

        // Set the main player's position.

        status = g_mainPlayer->SetScreenTopLeft (mainPlayerScreenRect.X, mainPlayerScreenRect.Y);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::HandleCollectableItemCollision (const CollisionGrid::CellElement&   cellElement,
                                                    bool                                mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Find the collectable item that has been collided with.

        StaticSpriteDrawingElementsList::iterator   itr = m_staticSpriteDrawingElementsList.begin ();

        bool    found = false;  // Initialise!

        do
        {              
            // Is this the collectable item that has been collided with?

            if (itr->m_sprite.get () == cellElement.m_userData)
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


FolioStatus Screen::HandleHealthItemCollision (const CollisionGrid::CellElement&    cellElement,
                                               bool                                 mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Find the health item that has been collided with.

        StaticSpriteDrawingElementsList::iterator   itr = m_staticSpriteDrawingElementsList.begin ();

        bool    found = false;  // Initialise!

        do
        {              
            // Is this the health item that has been collided with?

            if (itr->m_sprite.get () == cellElement.m_userData)
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


FolioStatus Screen::HandleHarmfulItemCollision (const CollisionGrid::CellElement&   cellElement,
                                                bool                                mainPlayer)
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


FolioStatus Screen::HandleNastySpriteCollision (const CollisionGrid::CellElement&   cellElement,
                                                bool                                mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the nasty sprite that has been collided with.

    bool    found = false;  // Initialise!

    for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
         !found && (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
         ++itr)
    {              
        // Get the nasty sprite.

        NastySpritePtr  &nastySprite(itr->m_sprite);

        // Is the nasty sprite on this screen and has it been collided with?

        if ((nastySprite->GetNastySpriteScreenNumber () == m_screenNumber) && 
            (nastySprite.get () == cellElement.m_userData))
        {
            // Yes. Is the nasty sprite ready?
            
            if (nastySprite->IsReady ())
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
                        // No. Nasty sprite can only have collided with the 
                        // weapon sprite. Remove the screen's weapon sprite.

                        status = RemoveWeaponSprite ();
                    } // Endelse.

                    if (status == ERR_SUCCESS)
                    {
                        // The nasty sprite is dead.

                        nastySprite->SetDead ();

                        // Increment the score.

                        m_informationPanel->IncrementScore (InformationPanel::SCORE_NASTY_SPRITE_DEAD);
                    } // Endif.
                    
                } // Endif.

            } // Endif.

            found = true;   // Found the nasty sprite.
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::HandleBossSpriteCollision (const CollisionGrid::CellElement&    cellElement,
                                               bool                                 mainPlayer)
{
    FolioStatus status = ERR_SUCCESS;

    // Is this a main player collision?

    if (mainPlayer)
    {
        // Yes. Get the boss sprite.

        BossSpritePtr   &bossSprite(g_bossSpriteDrawingElement.m_sprite);

        // Is the boss sprite ready?
            
        if (bossSprite->IsReady ())
        {
            // Can the boss sprite be killed?

            if (bossSprite->CanBeKilled (*m_informationPanel))
            {
                // Yes. Remove the boss sprite.

                status = RemoveBossSprite (false);

                if (status == ERR_SUCCESS)
                {
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
        // Yes. 
        
        status = HandleMainPlayerDead ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::IncrementMainPlayerHealth (UInt32 healthIncrement)
{
    return (m_informationPanel->IncrementMainPlayerHealth (healthIncrement));
} // Endproc.


FolioStatus Screen::HandleMainPlayerDead ()
{
    // Remove the screen's nasty sprites. They should all be killed. 

    FolioStatus status = RemoveNastySprites (false);

    if (status == ERR_SUCCESS)
    {
        // Remove the screen's weapon sprite. Don't play the terminated sound.

        status = RemoveWeaponSprite (false);

        if (status == ERR_SUCCESS)
        {
            // The main player is dead.

            g_mainPlayer->SetDead ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::AddDroppedItem (InformationPanel::DroppedItem& droppedItem)
{
    // Gain the dropped item's static sprite's graphic resource.

    FolioStatus status = droppedItem.m_staticSprite->GainResourceGraphics (Screen::MakeOwnerId (m_screenNumber));

    if (status == ERR_SUCCESS)
    {
        // Set the dropped item's static sprite position.

        status = droppedItem.m_staticSprite->SetScreenTopLeft (g_mainPlayer->GetScreenXLeft (),
                                                               g_mainPlayer->GetScreenYBottom () - droppedItem.m_staticSprite->GetScreenHeight () + 1);

        if (status == ERR_SUCCESS)
        {
            // Add the dropped item's static sprite.

            status = AddStaticSprite (droppedItem.m_staticSprite);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::BuildScreenDrawingElements (bool initialise)
{
    m_drawingElementsList.clear ();  // Initialise!

    // Get the canvas device context.

    FolioHandle dcHandle = m_canvas->GetCanvasDcHandle ();

    // Build the screen's room drawing elements.

    FolioStatus status = BuildRoomDrawingElements (dcHandle, initialise);

    if (status == ERR_SUCCESS)
    {
        // Build the screen's background item drawing elements.

        status = BuildBackgroundItemDrawingElements (dcHandle, initialise);

        if (status == ERR_SUCCESS)
        {
            status = BuildInformationPanelDrawingElements (dcHandle, initialise);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::BuildRoomDrawingElements (FolioHandle   dcHandle,
                                              bool          initialise)
{
    // Query the room graphic.

    RoomGraphicPtr  roomGraphic;

    FolioStatus status = QueryRoomGraphic (Screen::MakeOwnerId (m_screenNumber),
                                           m_roomId, 
                                           roomGraphic);

    if (status == ERR_SUCCESS)
    {
        // Query the room's drawing elements.

        Folio::Core::Game::DrawingElementsList  drawingElementsList;

        status = roomGraphic->QueryDrawingElements (dcHandle,
                                                    m_roomColour,
                                                    drawingElementsList);

        if (status == ERR_SUCCESS)
        {
            // Add the room's drawing element to the screen's drawing elements.

            m_drawingElementsList.insert (m_drawingElementsList.end (),
                                          drawingElementsList.begin (),
                                          drawingElementsList.end ());

            if (initialise)
            {
                // Note the room's collision grid.

                m_collisionGrid = roomGraphic->GetCollisionGrid ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::BuildBackgroundItemDrawingElements (FolioHandle dcHandle,
                                                        bool        initialise)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the screen's background items to the screen's drawing elements.

    for (BackgroundItemsList::const_iterator itr = m_backgroundItemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_backgroundItemsList.end ());
         ++itr)
    {
        // Set the background item's graphic.

        status = itr->get ()->SetBackgroundItemGraphic ();

        if (status == ERR_SUCCESS)
        {
            // Query the background item's drawing elements.

            Folio::Core::Game::DrawingElementsList  drawingElementsList;

            status = itr->get ()->QueryDrawingElements (dcHandle,
                                                        m_roomColour,
                                                        drawingElementsList);

            if (status == ERR_SUCCESS)
            {
                // Add the background item's drawing elements to the screen's 
                // drawing elements.

                m_drawingElementsList.insert (m_drawingElementsList.end (),
                                              drawingElementsList.begin (),
                                              drawingElementsList.end ());
            } // Endif.

        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::BuildInformationPanelDrawingElements (FolioHandle   dcHandle,
                                                          bool          initialise)
{
    // Get the information panel's drawing elements.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    FolioStatus status = m_informationPanel->QueryDrawingElements (dcHandle,
                                                                   m_roomColour, 
                                                                   drawingElementsList);

    if (status == ERR_SUCCESS)
    {
        // Add the information panel's drawing elements to the screen's drawing elements.

        m_drawingElementsList.insert (m_drawingElementsList.end (),
                                      drawingElementsList.begin (),
                                      drawingElementsList.end ());
    } // Endif.

    return (status);
} // Endproc.


FolioStatus Screen::AddBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList)
{
    // Add the background item's drawing elements to the screen's drawing elements.
    // But don't remove from the screen's collision grid.

    return (AddScreenDrawingElements (drawingElementsList, false)); 
} // Endproc.


FolioStatus Screen::RemoveBackgroundItemDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList)
{
    // Remove the background item's drawing elements from the screen's drawing elements.
    // But don't remove from the screen's collision grid.

    return (RemoveScreenDrawingElements (drawingElementsList, false)); 
} // Endproc.


FolioStatus Screen::AddScreenDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList, 
                                              bool                                          addToCollisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the drawing elements to the screen's drawing elements.

    m_drawingElementsList.insert (m_drawingElementsList.end (),
                                  drawingElementsList.begin (),
                                  drawingElementsList.end ());

    // Sort the screen's drawing elements.

    std::sort (m_drawingElementsList.begin (), 
               m_drawingElementsList.end (), 
               Folio::Core::Game::DrawingElement::Sort);

    // Add the drawing elements to the screen's collision grid?

    if (addToCollisionGrid)
    {
        // Add the drawing elements to the screen's collision grid.

        status = AddCollisionGridDrawingElements (drawingElementsList);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Draw the drawing elements in the canvas.

        status = m_canvas->DrawDrawingElements (drawingElementsList);
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
} // Endproc.


FolioStatus Screen::RemoveScreenDrawingElements (Folio::Core::Game::DrawingElement::UserData userData)
{
    // Remove the drawing elements that match the user data.

    Folio::Core::Game::DrawingElementsList::iterator    itr = m_drawingElementsList.begin ();

    while (itr != m_drawingElementsList.end ())
    {
        if (itr->GetUserData () == userData)
        {
            // Remove the drawing element from the screen's drawing elements set.

            itr = m_drawingElementsList.erase (itr);
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

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = m_drawingElementsList.begin ();
         itr != m_drawingElementsList.end ();
         ++itr)
    {
        if (itr->GetUserData () == userData)
        {
            drawingElementsList.push_back (*itr);
        } // Endif.

    } // Endfor.

    return (drawingElementsList);
} // Endfor.


FolioStatus Screen::InitialiseCollisionGrid ()
{
    FolioStatus status = ERR_SUCCESS;

    // Initialise the screen's collision grid.

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = m_drawingElementsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_drawingElementsList.end ());
         ++itr)
    {
        FolioString drawingElementId(itr->GetDrawingElementId ());

        if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM)
        {
            // Add the background item to the collision grid.

            status = AddCollisionGridDrawingElement (*itr);
        } // Endif.

        else
        if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_INFORMATION_PANEL_ITEM)
        {
            // No more drawing elements to add to the collision grid.

            finished = true;
        } // Endelseif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::AddCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Add the drawing elements to the screen's collision grid.

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
         ++itr)
    {
        FolioString drawingElementId(itr->GetDrawingElementId ());

        if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM)
        {
            // Is the background item's collision grid cell value empty?

            if (!CollisionGrid::IsEmpty (itr->GetCollisionGridCellValue ()))
            {
                // No. Add the background item to the collision grid.

                status = AddCollisionGridDrawingElement (*itr);
            } // Endif.

        } // Endif.

        else
        if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_INFORMATION_PANEL_ITEM)
        {
            // No more drawing elements to add to the collision grid.

            finished = true;
        } // Endelseif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::AddCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement& drawingElement)
{
    FolioStatus status = ERR_SUCCESS;

    FolioString drawingElementId(drawingElement.GetDrawingElementId ());

    if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM)
    {
        CollisionGrid::CellValue    collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

        // Is this an exit?

        if (CollisionGrid::IsExit (collisionGridCellValue))
        {
            // Get the background item.

            BackgroundItem  *backgroundItem = reinterpret_cast<BackgroundItem *> (drawingElement.GetUserData ());

            // Is the exit a door and not already in the collision grid?

            if (IsDoor (*backgroundItem) && 
                !m_collisionGrid.IsScreenExit (backgroundItem))
            {
                // Yes. Add the screen exit to the collision grid.
                    
                status = m_collisionGrid.AddScreenExit (CollisionGrid::ScreenExit(backgroundItem->GetDoorOrientation (),
                                                                                  drawingElement.GetScreenRect (),
                                                                                  GetDoorState (*backgroundItem),
                                                                                  backgroundItem));
            } // Endif.

        } // Endif.

        // Is the background item's collision grid cell value empty?

        else
        if (!CollisionGrid::IsEmpty (collisionGridCellValue))
        {
            // No. Add the background item's drawing elements to the collision grid.

            status = m_collisionGrid.AddCellElement (drawingElement);
        } // Endelseif.
    
    } // Endif.

    else
    if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE)
    {
        UInt32  collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

        // Is the static sprite's collision grid cell value empty?

        if (!CollisionGrid::IsEmpty (collisionGridCellValue))
        {
            // No. Add the static sprite's drawing element to the collision grid.

            status = m_collisionGrid.AddCellElement (drawingElement);
        } // Endif.

    } // Endelseif.

    else
    if ((drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE) ||
        (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE)  ||
        (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_WEAPON_SPRITE))
    {
        // Always add this sprite's drawing element to the collision grid.

        status = m_collisionGrid.AddCellElement (drawingElement);
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveCollisionGridDrawingElements (const Folio::Core::Game::DrawingElementsList& drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Remove the drawing elements from the screen's collision grid.

    bool    finished = false;   // Initialise!

    for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != drawingElementsList.end ());
         ++itr)
    {
        FolioString drawingElementId(itr->GetDrawingElementId ());

        if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM)
        {
            // Is the background item's collision grid cell value empty?

            if (!CollisionGrid::IsEmpty (itr->GetCollisionGridCellValue ()))
            {
                // No. Remove the background item from the collision grid.

                status = RemoveCollisionGridDrawingElement (*itr);
            } // Endif.

        } // Endif.

        else
        if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_INFORMATION_PANEL_ITEM)
        {
            // No more drawing elements to remove from the collision grid.
            
            finished = true;
        } // Endelseif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus Screen::RemoveCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement& drawingElement)
{
    FolioStatus status = ERR_SUCCESS;

    FolioString drawingElementId(drawingElement.GetDrawingElementId ());

    if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BACKGROUND_ITEM)
    {
        CollisionGrid::CellValue    collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

        // Is this an exit?

        if (CollisionGrid::IsExit (collisionGridCellValue))
        {
            // Get the background item.

            BackgroundItem  *backgroundItem = reinterpret_cast<BackgroundItem *> (drawingElement.GetUserData ());

            // Is the exit in the collision grid?

            if (m_collisionGrid.IsScreenExit (backgroundItem))
            {
                // Yes. Remove the screen exit from the collision grid.

                status = m_collisionGrid.RemoveScreenExit (CollisionGrid::ScreenExit(backgroundItem->GetDoorOrientation (),
                                                                                     drawingElement.GetScreenRect (),
                                                                                     CollisionGrid::ScreenExit::CLOSED,
                                                                                     backgroundItem));
            } // Endif.

        } // Endif.

        // Is the background item's collision grid cell value empty?

        else
        if (!CollisionGrid::IsEmpty (collisionGridCellValue))
        {
            // No. Remove the background item's drawing element from the collision grid.

            status = m_collisionGrid.RemoveCellElement (drawingElement);
        } // Endelseif.

    } // Endif.

    else
    if (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE)
    {
        UInt32  collisionGridCellValue = drawingElement.GetCollisionGridCellValue ();

        // Is the static sprite's collision grid cell value empty?

        if (!CollisionGrid::IsEmpty (collisionGridCellValue))
        {
            // No. Remove the static sprite's drawing element from the collision grid.

            status = m_collisionGrid.RemoveCellElement (drawingElement);
        } // Endif.

    } // Endif.

    else
    if ((drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE) ||
        (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE)  ||
        (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_WEAPON_SPRITE))
    {
        // Always remove this sprite's drawing element from the collision grid.

        status = m_collisionGrid.RemoveCellElement (drawingElement);
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus Screen::UpdateCollisionGridDrawingElement (const Folio::Core::Game::DrawingElement& drawingElement)
{
    FolioStatus status = ERR_SUCCESS;

    FolioString drawingElementId(drawingElement.GetDrawingElementId ());

    if ((drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE) ||
        (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE)  ||
        (drawingElementId == Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_WEAPON_SPRITE))
    {
        // Always update this sprite's drawing element in the collision grid.

        status = m_collisionGrid.UpdateCellElement (drawingElement);
    } // Endif..

    return (status);
} // Endproc.


FolioStatus Screen::ReleaseResourceGraphics ()
{
    // Release the screen's graphics from the resource graphics cache.

    return (g_resourceGraphicsCache.ReleaseResourceGraphics (MakeOwnerId (m_screenNumber)));
} // Endproc.


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
    
        Folio::Core::Game::ZxSpectrum::BYTE frequency = 0xf7;

        for (Folio::Core::Game::ZxSpectrum::BYTE numLoops = 0x09; numLoops >= 0x01; --numLoops)
        {
            m_enteredScreenSoundSamples.push_back (Ultimate::CreateSoundSample (frequency, numLoops));

            if (frequency == 0xff)
            {
                frequency = 0x87;
            } // Endif.

            else
            {
                frequency += 0x08;
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
        // Yes. Play the entered screen sound sample.

        FolioStatus status = 
            Folio::Core::Util::Sound::PlaySoundSample (m_enteredScreenSoundSamples [m_currentEnteredScreenSoundSampleIndex]);

        if (status == ERR_SUCCESS)
        {
            // All entered screen sound samples played?

            if (++m_currentEnteredScreenSoundSampleIndex >= m_enteredScreenSoundSamples.size ())
            {
                // Yes.

                m_playEnteredScreenSound                = false;
                m_currentEnteredScreenSoundSampleIndex  = 0;
            } // Endif.

            playedEnteredScreenSound = true;
        } // Endif.

    } // Endif.

    return (playedEnteredScreenSound);
} // Endproc.


FolioStatus BuildScreens (Folio::Core::Applet::Canvas&  canvas,
                          const BackgroundItemsList&    backgroundItemsList,
                          const StaticSpritesList&      staticSpritesList,
                          const InformationPanel&       informationPanel,
                          ScreensList&                  screensList)
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
        // Set the screen's canvas.

        itr->SetCanvas (canvas);

        // Set the screen's background items.

        itr->SetBackgroundItemsList (GetScreenBackgroundItemsList (itr->GetScreenNumber (), backgroundItemsList));

        // Set the screen's static sprites.

        itr->SetStaticSpritesList (GetScreenStaticSpritesList (itr->GetScreenNumber (), staticSpritesList));

        // Set the information panel.

        itr->SetInformationPanel (informationPanel);
    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
