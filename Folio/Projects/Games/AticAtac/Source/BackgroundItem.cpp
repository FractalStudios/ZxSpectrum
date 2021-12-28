// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItem.h"
#include    "Screen.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Background items table.
static  const   BackgroundItem  g_backgroundItemsTable [] =
{
//      m_backgroundItemId                        m_screenNumber  m_screenXLeft m_screenYBottom     m_backgroundItemflags                                                   m_drawingFlags
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            7,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            0,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           25,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            0,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,      1,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,      0,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            2,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            1,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            3,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            2,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            4,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            3,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           25,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            4,            128,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            5,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            4,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            6,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            5,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,              26,             72,        182,                BackgroundItem::FLAGS_OPEN_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            6,             80,         63,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,     8,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,     6,             80,        151,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            7,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            6,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            9,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            8,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           10,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            9,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           11,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           10,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           12,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           11,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           13,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           12,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           14,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           13,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           15,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           14,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           16,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           15,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      17,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      16,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           18,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           17,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           19,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           18,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           20,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           19,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           21,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           20,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           22,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           21,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      23,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      22,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    24,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    23,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           24,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            2,             80,         63,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           26,             80,         40,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           27,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           27,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,              28,             10,        119,                BackgroundItem::FLAGS_OPEN_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           28,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             29,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           30,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           31,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           31,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           32,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           32,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           33,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           33,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           34,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           34,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           35,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           35,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           36,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           36,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           37,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     37,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     30,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           36,             80,         63,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,              38,             72,        182,                BackgroundItem::FLAGS_OPEN_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            2,             80,        151,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           38,             80,         40,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           39,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           40,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     40,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     41,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           41,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           42,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           42,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           43,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           43,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           44,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           44,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           45,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    45,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    46,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           46,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           39,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           39,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,              47,             72,        182,                BackgroundItem::FLAGS_OPEN_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   32,             80,        151,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   47,             80,         40,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             48,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             49,             80,         39,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             49,             80,        175,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             50,             80,         39,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             50,             80,        175,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             51,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             51,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             52,             80,         39,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             52,             80,        175,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             53,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             51,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             54,             16,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             54,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             55,             16,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             55,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             56,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             56,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             57,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,      56,            144,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,      58,             24,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             57,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             59,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             58,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             59,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,      59,             80,        167,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,      60,             80,         47,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             59,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             61,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             60,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             62,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             61,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             62,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,       61,            144,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,       63,             16,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             63,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             64,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             64,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             65,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             64,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             66,             80,        175,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             66,             80,         39,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             67,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             67,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             68,             16,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,        68,            152,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,        69,             24,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             67,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             70,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             70,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             71,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,        71,             16,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,        72,            144,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             72,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             73,             80,         39,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,       72,             24,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR,       74,            152,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             74,             16,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             75,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             75,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             76,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             72,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             77,             80,        175,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,        77,             80,         39,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR,        78,             80,        167,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             78,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             79,             16,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             79,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             80,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             80,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             81,             80,         39,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,      80,            144,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR,      82,             16,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             82,            152,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             83,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             29,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             67,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             70,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             81,             80,        175,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             76,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             85,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             84,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             85,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             84,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             48,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           45,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          117,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          117,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          118,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          118,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          119,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          119,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          120,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          120,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          121,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          121,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          122,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          122,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          123,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  123,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  124,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  124,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  125,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          125,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          118,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,     122,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,     126,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          126,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           41,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           33,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          136,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   127,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   128,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          128,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          130,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          130,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          129,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          129,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          127,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,    130,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,    135,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          135,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          136,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          135,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          139,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          139,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          140,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   140,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   141,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,     131,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,     132,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          132,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          134,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          134,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          133,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          133,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          131,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  132,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  137,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          137,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          141,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          137,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          138,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   138,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    35,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           19,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          115,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           17,            128,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          107,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          107,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          108,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,    108,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,      3,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    15,            128,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   109,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          109,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          110,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          110,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,            5,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     13,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,    111,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          111,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          112,            112,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          112,             48,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,             113,             72,        182,                BackgroundItem::FLAGS_OPEN_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          113,             80,         40,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BIG_DOOR_FRAME,             114,             72,        182,                BackgroundItem::FLAGS_OPEN_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          114,             80,         40,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             53,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             48,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            116,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           86,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           87,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    87,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    88,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           88,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           89,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           90,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           91,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      91,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      92,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    92,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    93,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      94,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      95,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      95,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      96,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           96,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           97,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           98,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           99,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           99,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          100,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  100,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  101,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           86,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           90,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     90,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     94,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           94,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           98,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           87,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           91,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    91,             48,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    95,             48,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     95,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     99,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           88,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           92,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      92,            112,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      96,            112,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     96,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,    100,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   89,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   93,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           93,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           97,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           97,             80,        183,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          101,             80,         31,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,    103,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR,     86,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,     104,             80,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR,      89,             80,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  105,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   86,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,   106,            160,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR,    98,              8,        111,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  102,             48,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   91,            112,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  102,            112,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   92,             48,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  102,             48,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   95,            112,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,  102,            112,        183,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR,   96,             48,         31,                BackgroundItem::FLAGS_LOCKED_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,          101,            160,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_NORMAL_DOOR_FRAME,           27,              8,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             64,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            143,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             84,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            144,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            144,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            145,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            145,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            146,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            146,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            147,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            147,            144,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90     | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            148,             24,        111,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,             58,             80,         47,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CAVE_DOOR_FRAME,            148,             80,        167,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM                                                                  | Folio::Core::Game::ResourceGraphic::FLIP_VERTICAL,    },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,             115,             80,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        116,             72,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,               3,             48,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        101,             56,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,              97,             80,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                         75,             72,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,              45,             80,        144,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        141,             72,        148,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,             118,             80,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        132,             72,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,             139,             80,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        108,             72,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,             141,             80,         80,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        110,             72,         84,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,              33,            112,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                          3,            104,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,              21,             80,        124,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        102,             72,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,             120,            112,        112,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                        138,            104,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_OPEN_TRAP_DOOR,              41,             80,        128,                BackgroundItem::FLAGS_OPEN_DOOR | BackgroundItem::FLAGS_CAN_BE_CLOSED,  Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_RUG,                          9,             72,        116,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_PICTURE,                     11,             80,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_PICTURE,                     12,             80,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BARRELS,                    145,             80,        143,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      31,            152,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      33,              8,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                      37,            152,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      35,              8,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                       0,            152,         63,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       6,             56,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BARRELS,                     61,             95,         95,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       0,            152,        143,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       6,            120,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       1,             88,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       3,             88,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       5,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_KNIGHT,                       7,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_KNIGHT,                      23,             88,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      21,            120,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_KNIGHT,                      21,             56,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_KNIGHT,                      19,             88,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                     136,              8,         63,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                     138,              8,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                     136,              8,        143,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                     138,              8,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                      39,             56,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      43,             56,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      39,            120,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      43,            120,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      86,             56,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      36,             56,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      86,            120,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                      36,            120,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                     124,             56,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                     122,             56,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                     124,            120,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                     122,            120,         39,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_KNIGHT,                       9,              8,         63,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                     127,             56,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_KNIGHT,                       9,              8,        143,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_KNIGHT,                     127,            120,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_TABLE,                       13,             56,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       19,            112,        144,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       99,             56,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       93,            112,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       24,             72,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      136,            112,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      122,             56,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      129,            112,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       24,             88,        128,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      109,             48,        144,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       91,             56,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       92,            112,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      106,            120,        152,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       27,            112,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       46,             56,         87,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      125,             72,         80,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       46,             96,        127,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                      125,             88,        128,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       42,             56,         87,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       45,             48,        128,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       42,             96,        127,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_TABLE,                       45,            112,        128,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_NONE,                                                                                                                           },
    {   BACKGROUND_ITEM_ACG_SHIELD,                 141,             40,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SHIELD,                     140,             40,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              139,            136,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_TROPHY,                     140,            136,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ACG_SHIELD,                  22,             88,         55,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_SHIELD,                      20,             88,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,               14,             40,         87,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_TROPHY,                      18,            136,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ACG_SHIELD,                  15,             40,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SHIELD,                      17,             40,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,               16,            136,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_TROPHY,                     115,             88,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ACG_SHIELD,                   8,            136,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_SHIELD,                      24,            136,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              111,             40,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_TROPHY,                      14,             40,        119,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_PICTURE_2,                    0,             40,         23,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_SHIELD,                      25,             88,         55,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_PICTURE,                      0,            120,         28,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_TROPHY,                      11,             88,         55,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_ACG_SHIELD,                   0,             56,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_SHIELD,                      25,             88,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,                0,            120,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_TROPHY,                      11,             40,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_PICTURE,                      4,             40,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,               21,             88,         55,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_TROPHY,                       4,             40,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_PICTURE_2,                   20,             88,         55,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_PICTURE,                    115,             88,         60,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_TROPHY,                     110,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ACG_SHIELD,                 109,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_PICTURE_2,                   14,            136,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_PICTURE_2,                    7,            168,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ACG_SHIELD,                   6,             56,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ACG_SHIELD,                   6,            120,        151,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_SHIELD,                       1,            168,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_PICTURE,                     24,             40,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SHIELD,                      23,            168,        103,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              135,             56,         23,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_TROPHY,                     137,             56,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_TROPHY,                     135,            120,         23,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              137,            120,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_SHIELD,                       0,              8,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_TROPHY,                     130,             56,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_TROPHY,                       0,              8,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              130,            120,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_PICTURE,                    102,            164,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_SHIELD,                      97,            168,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              102,            168,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_PICTURE_2,                   93,            168,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_TROPHY,                     102,              8,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SHIELD,                     101,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ACG_SHIELD,                 102,              8,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_TROPHY,                     100,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_PICTURE,                     99,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,               98,             80,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_TROPHY,                     112,             56,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,               13,              8,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SHIELD,                     112,            120,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_TROPHY,                      12,             88,         55,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_TROPHY,                       9,            168,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              127,              8,         96,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_PICTURE,                      9,            164,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_SHIELD,                     127,             88,         23,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,               90,              8,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_PICTURE_2,                   39,            168,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_TROPHY,                      90,              8,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SHIELD,                      39,            168,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ACG_SHIELD,                  41,            168,         71,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_TROPHY,                     126,            168,         96,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_PICTURE,                     41,            164,        135,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ANTLER_TROPHY,              126,             88,        183,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_CLOCK,                       13,             48,         39,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CLOCK,                       19,             48,        183,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_CLOCK,                        9,             48,         39,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CLOCK,                       23,             48,        183,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_CLOCK,                       53,            136,        111,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_CLOCK,                      143,             24,        111,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CLOCK,                      103,            152,        111,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_CLOCK,                      104,              8,        111,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CLOCK,                      141,            120,         79,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_CLOCK,                       34,             40,        111,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_CLOCK,                      118,             48,         39,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_CLOCK,                      117,             48,        183,                BackgroundItem::FLAGS_KNIGHT_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BOOKCASE,                    10,             64,         71,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BOOKCASE,                    22,             64,        151,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BOOKCASE,                    61,             76,         54,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BOOKCASE,                    73,             76,        177,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BOOKCASE,                   105,             64,        183,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BOOKCASE,                   106,             64,         39,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BOOKCASE,                   108,             64,        183,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BOOKCASE,                   110,             64,         39,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BOOKCASE,                    62,            137,        115,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_BOOKCASE,                    65,             76,        168,                BackgroundItem::FLAGS_WIZARD_DOOR,                                      Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BARREL,                      69,             80,         55,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BARREL,                      83,             80,        164,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BARREL,                      76,            136,        111,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_BARREL,                      78,             24,        111,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_BARREL,                      56,             80,         55,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BARREL,                      75,             80,        167,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BARREL,                     107,             80,        183,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
    {   BACKGROUND_ITEM_BARREL,                     109,             80,         39,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP,                                                                                                                            },
    {   BACKGROUND_ITEM_BARREL,                     138,            152,        111,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_BARREL,                       8,             40,        111,                BackgroundItem::FLAGS_SERF_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_ACG_EXIT_DOOR,                0,            152,        127,                BackgroundItem::FLAGS_EXIT_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_ACG_EXIT_DOOR,              142,              0,        127,                BackgroundItem::FLAGS_EXIT_DOOR,                                        Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SKELETON,                    83,            128,        119,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_SKELETON,                   143,            128,        119,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT       | Folio::Core::Game::ResourceGraphic::ROTATION_RIGHT_90,                                                            },
    {   BACKGROUND_ITEM_SKELETON,                    51,             24,        111,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT        | Folio::Core::Game::ResourceGraphic::ROTATION_LEFT_90,                                                             },
    {   BACKGROUND_ITEM_SKELETON,                    85,             70,        167,                BackgroundItem::FLAGS_NONE,                                             Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM      | Folio::Core::Game::ResourceGraphic::ROTATION_180,                                                                 },
};


BackgroundItem::BackgroundItem ()
:   m_backgroundItemId(BACKGROUND_ITEM_UNDEFINED),
    m_screenNumber(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_screenXLeft(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_screenYBottom(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_backgroundItemflags(FLAGS_NONE),
    m_drawingFlags(Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS),
    m_doorTransitionTickCount(0)
{
} // Endproc.


BackgroundItem::BackgroundItem (BACKGROUND_ITEM_ID  backgroundItemId,
                                UInt32              screenNumber,
                                Int32               screenXLeft,
                                Int32               screenYBottom,
                                UInt32              backgroundItemflags,
                                UInt32              drawingFlags)
:   m_backgroundItemId(backgroundItemId),
    m_screenNumber(screenNumber),
    m_screenXLeft(screenXLeft),
    m_screenYBottom(screenYBottom),
    m_backgroundItemflags(backgroundItemflags),
    m_drawingFlags(drawingFlags),
    m_doorTransitionTickCount(0)
{
} // Endproc.


BackgroundItem::~BackgroundItem ()
{
} // Endproc.


FolioStatus BackgroundItem::SetBackgroundItemGraphic ()
{
    FolioStatus status = ERR_SUCCESS;

    if (m_backgroundItemGraphic)
    {
        // Release the background item's graphic from the resource graphics cache.

        status = ReleaseBackgroundItemGraphic (m_backgroundItemGraphic);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Query the background item's graphic.

        status = QueryBackgroundItemGraphic (Screen::MakeOwnerId (m_screenNumber),
                                             m_backgroundItemId,
                                             m_backgroundItemGraphic);
    } // Endif.

    return (status);
} // Endproc.


BackgroundItemGraphic   BackgroundItem::GetBackgroundItemGraphic () const
{
    return (m_backgroundItemGraphic);
} // Endproc.


BACKGROUND_ITEM_ID  BackgroundItem::GetBackgroundItemId () const
{
    return (m_backgroundItemId);
} // Endproc.


UInt32  BackgroundItem::GetScreenNumber () const
{
    return (m_screenNumber);
} // Endproc.


UInt32    BackgroundItem::GetBackgroundItemFlags () const
{
    return (m_backgroundItemflags);
} // Endproc.


UInt32    BackgroundItem::GetDrawingFlags () const
{
    return (m_drawingFlags);
} // Endproc.


FolioStatus BackgroundItem::SetScreenTopLeft (Int32 screenXLeft,
                                              Int32 screenYTop)
{
    FolioStatus status = ERR_SUCCESS;

    if (m_backgroundItemGraphic)
    {
        m_screenXLeft   = screenXLeft;
        m_screenYBottom = Folio::Core::Game::ZxSpectrum::CalculateScreenYBottom (screenYTop, 
                                                                                 m_backgroundItemGraphic->GetGraphicWidth (),
                                                                                 m_backgroundItemGraphic->GetGraphicHeight ());
    } // Endif.

    return (status);
} // Endproc.


Gdiplus::Rect   BackgroundItem::GetScreenRect () const
{
    return (Gdiplus::Rect(GetScreenXLeft(), 
                          GetScreenYTop (), 
                          GetScreenWidth (), 
                          GetScreenHeight ()));
} // Endproc.


Int32   BackgroundItem::GetScreenXLeft () const
{
    return (m_backgroundItemGraphic ? m_screenXLeft : Folio::Core::Game::ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   BackgroundItem::GetScreenYTop () const
{
    Int32   screenYTop = Folio::Core::Game::ZxSpectrum::UNDEFINED;   

    if (m_backgroundItemGraphic)
    {
        screenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (m_screenYBottom, 
                                                                         m_backgroundItemGraphic->GetGraphicWidth (),
                                                                         m_backgroundItemGraphic->GetGraphicHeight (),
                                                                         m_drawingFlags);
    } // Endif.

    return (screenYTop);
} // Endproc.


Int32   BackgroundItem::GetScreenXRight () const
{
    return (m_backgroundItemGraphic ? m_screenXLeft + m_backgroundItemGraphic->GetGraphicWidth () - 1 : Folio::Core::Game::ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   BackgroundItem::GetScreenYBottom () const
{
    return (m_screenYBottom);
} // Endproc.


Int32   BackgroundItem::GetScreenWidth () const
{
    Int32   screenWidth = Folio::Core::Game::ZxSpectrum::UNDEFINED;   

    if (m_backgroundItemGraphic)
    {
        // A background item can be rotated left 90 or right 90 degrees, meaning that 
        // the width is the height, and the height the width.

        if (!Folio::Core::Game::ResourceGraphic::IsRotated (m_drawingFlags) ||
             Folio::Core::Game::ResourceGraphic::IsRotation180 (m_drawingFlags))
        {
            screenWidth = m_backgroundItemGraphic->GetGraphicWidth ();
        } // Endif.

        else
        {
            screenWidth = m_backgroundItemGraphic->GetGraphicHeight ();
        } // Endelse.

    } // Endif.

    return (screenWidth);
} // Endproc.


Int32   BackgroundItem::GetScreenHeight () const
{
    Int32   screenHeight = Folio::Core::Game::ZxSpectrum::UNDEFINED;   

    if (m_backgroundItemGraphic)
    {
        // A background item can be rotated left 90 or right 90 degrees, meaning that 
        // the width is the height, and the height the width.

        if (!Folio::Core::Game::ResourceGraphic::IsRotated (m_drawingFlags) ||
             Folio::Core::Game::ResourceGraphic::IsRotation180 (m_drawingFlags))
        {
            screenHeight = m_backgroundItemGraphic->GetGraphicHeight ();
        } // Endif.

        else
        {
            screenHeight = m_backgroundItemGraphic->GetGraphicWidth ();
        } // Endelse.

    } // Endif.

    return (screenHeight);
} // Endproc.


FolioStatus BackgroundItem::QueryDrawingElements (FolioHandle                               dcHandle,
                                                  Folio::Core::Game::ZxSpectrum::COLOUR     roomColour,
                                                  Folio::Core::Game::DrawingElementsList    &drawingElementsList,
                                                  bool                                      maskedDrawingElementRqd) const
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    if (m_backgroundItemGraphic)
    {
        // Query the background item graphic's drawing elements.

        Int32   screenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (m_screenYBottom, 
                                                                                 m_backgroundItemGraphic->GetGraphicWidth (),
                                                                                 m_backgroundItemGraphic->GetGraphicHeight (),
                                                                                 m_drawingFlags);

        status = m_backgroundItemGraphic->QueryDrawingElements (dcHandle,
                                                                m_screenXLeft,
                                                                screenYTop,
                                                                Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                                Folio::Core::Game::ZxSpectrum::MapInkColour (roomColour),
                                                                m_drawingFlags,
                                                                const_cast<BackgroundItem *> (this),    // Drawing element user data.
                                                                drawingElementsList,
                                                                maskedDrawingElementRqd);

        if (status != ERR_SUCCESS)
        {
            drawingElementsList.clear ();
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_NOT_INITIALISED;
    } // Endelse.

    return (status);
} // Endproc.


CollisionGrid::ScreenExit::ORIENTATION  BackgroundItem::GetDoorOrientation () const
{
    switch (Folio::Core::Game::ResourceGraphic::GetOrientation (m_drawingFlags))
    {
    case Folio::Core::Game::ResourceGraphic::ORIENTATION_TOP:
        return (((m_backgroundItemId == BACKGROUND_ITEM_OPEN_TRAP_DOOR)      || 
                 (m_backgroundItemId == BACKGROUND_ITEM_CLOSED_TRAP_DOOR)    || 
                 (m_backgroundItemId == BACKGROUND_ITEM_RUG))
                ? CollisionGrid::ScreenExit::FLOOR 
                : CollisionGrid::ScreenExit::TOP);

    case Folio::Core::Game::ResourceGraphic::ORIENTATION_BOTTOM:
        return (CollisionGrid::ScreenExit::BOTTOM);
    
    case Folio::Core::Game::ResourceGraphic::ORIENTATION_LEFT:
        return (CollisionGrid::ScreenExit::LEFT);
    
    case Folio::Core::Game::ResourceGraphic::ORIENTATION_RIGHT:
        return (CollisionGrid::ScreenExit::RIGHT);
    
    default:
        return (CollisionGrid::ScreenExit::NONE);
    } // Endswitch.

} // Endproc.


void    BackgroundItem::SetDoorTransitionTickCount (UInt32 currentTickCount)
{
    if (currentTickCount)
    {
        m_doorTransitionTickCount = currentTickCount + 1000 * Folio::Core::Util::Random::GetRandomNumber (5, 25);
    } // Endif.

    else
    {
        m_doorTransitionTickCount = 0;
    } // Endelse.

} // Endproc.


UInt32    BackgroundItem::GetDoorTransitionTickCount () const
{
    return (m_doorTransitionTickCount);
} // Endproc.


bool    BackgroundItem::IsDoorTransition (UInt32 currentTickCount) const
{
    return (currentTickCount >= m_doorTransitionTickCount);
} // Endproc.


FolioStatus BackgroundItem::SetDoorOpen (bool setBackgroundItemGraphic)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the door closed?

    if (IsClosedDoor (m_backgroundItemflags))
    {
        // Yes. The door is now open and can be closed.

        m_backgroundItemflags = FLAGS_OPEN_DOOR | FLAGS_CAN_BE_CLOSED;

        // Get the new background item identifier.

        m_backgroundItemId = GetNewBackgroundItemId ();

        if (setBackgroundItemGraphic)
        {
            // Set the background item's new graphic.

            status = SetBackgroundItemGraphic ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus BackgroundItem::SetDoorClosed (bool setBackgroundItemGraphic)
{
    FolioStatus status = ERR_SUCCESS;

    // If the door is open then can the door be closed?

    if (IsOpenDoor (m_backgroundItemflags) && 
        CanDoorBeClosed (m_backgroundItemflags))
    {
        // Yes. The door is now closed.

        m_backgroundItemflags = FLAGS_CLOSED_DOOR;

        // Get the new background item identifier.

        m_backgroundItemId = GetNewBackgroundItemId ();

        if (setBackgroundItemGraphic)
        {
            // Set the background item's new graphic.

            status = SetBackgroundItemGraphic ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus BackgroundItem::SetDoorUnlocked (bool setBackgroundItemGraphic)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the door locked?

    if (IsLockedDoor (m_backgroundItemflags))
    {
        // Yes. The door is now open and it cannot be closed.

        m_backgroundItemflags = FLAGS_OPEN_DOOR;

        // Get the new background item identifier.

        m_backgroundItemId = GetNewBackgroundItemId ();

        if (setBackgroundItemGraphic)
        {
            // Set the background item's new graphic.

            status = SetBackgroundItemGraphic ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    BackgroundItem::operator == (const BackgroundItem& rhs) const
{
    return ((m_screenNumber     == rhs.m_screenNumber)      &&
            (m_backgroundItemId == rhs.m_backgroundItemId)  &&
            (m_screenXLeft      == rhs.m_screenXLeft)       &&
            (m_screenYBottom    == rhs.m_screenYBottom));
} // Endproc.


bool    BackgroundItem::IsDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_DOOR) == BackgroundItem::FLAGS_DOOR);
} // Endproc.


bool    BackgroundItem::IsOpenDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_OPEN_DOOR) == BackgroundItem::FLAGS_OPEN_DOOR);
} // Endproc.


bool    BackgroundItem::IsClosedDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_CLOSED_DOOR) == BackgroundItem::FLAGS_CLOSED_DOOR);
} // Endproc.


bool    BackgroundItem::IsLockedDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_LOCKED_DOOR) == BackgroundItem::FLAGS_LOCKED_DOOR);
} // Endproc.


bool    BackgroundItem::IsExitDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_EXIT_DOOR) == BackgroundItem::FLAGS_EXIT_DOOR);
} // Endproc.


bool    BackgroundItem::IsKnightDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_KNIGHT_DOOR) == BackgroundItem::FLAGS_KNIGHT_DOOR);
} // Endproc.


bool    BackgroundItem::IsWizardDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_WIZARD_DOOR) == BackgroundItem::FLAGS_WIZARD_DOOR);
} // Endproc.


bool    BackgroundItem::IsSerfDoor (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_SERF_DOOR) == BackgroundItem::FLAGS_SERF_DOOR);
} // Endproc.


bool    BackgroundItem::CanDoorBeClosed (UInt32 backgroundItemflags)
{
    return ((backgroundItemflags & BackgroundItem::FLAGS_CAN_BE_CLOSED) == BackgroundItem::FLAGS_CAN_BE_CLOSED);
} // Endproc.


bool    BackgroundItem::IsCaveDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_CAVE_DOOR_FRAME:
    case BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_CLOSED_CAVE_DOOR:
    case BACKGROUND_ITEM_OPEN_CAVE_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsNormalDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_NORMAL_DOOR_FRAME:
    case BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_CLOSED_NORMAL_DOOR:
    case BACKGROUND_ITEM_OPEN_NORMAL_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsBigDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_BIG_DOOR_FRAME:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsTrapDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_CLOSED_TRAP_DOOR:
    case BACKGROUND_ITEM_OPEN_TRAP_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsLockedRedDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsLockedGreenDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsLockedCyanDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsLockedYellowDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    BackgroundItem::IsLockedExitDoor (BACKGROUND_ITEM_ID backgroundItemId)
{
    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_ACG_EXIT_DOOR:
        return (true);
    default:
        return (false);
    } // Endswitch.

} // Endproc.


BACKGROUND_ITEM_ID  BackgroundItem::GetNewBackgroundItemId () const
{
    BACKGROUND_ITEM_ID  backgroundItemId = m_backgroundItemId;  // Initialise!

    switch (m_backgroundItemId)
    {
    case BACKGROUND_ITEM_NORMAL_DOOR_FRAME:
    case BACKGROUND_ITEM_OPEN_NORMAL_DOOR:
        if (IsClosedDoor (m_backgroundItemflags))
        {
            backgroundItemId = BACKGROUND_ITEM_CLOSED_NORMAL_DOOR;
        } // Endif.
        break;

    case BACKGROUND_ITEM_CLOSED_NORMAL_DOOR:
    case BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR:
        if (IsOpenDoor (m_backgroundItemflags))
        {
            backgroundItemId = BACKGROUND_ITEM_OPEN_NORMAL_DOOR;
        } // Endif.
        break;

    case BACKGROUND_ITEM_CAVE_DOOR_FRAME:
    case BACKGROUND_ITEM_OPEN_CAVE_DOOR:
        if (IsClosedDoor (m_backgroundItemflags))
        {
            backgroundItemId = BACKGROUND_ITEM_CLOSED_CAVE_DOOR;
        } // Endif.
        break;

    case BACKGROUND_ITEM_CLOSED_CAVE_DOOR:
    case BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR:
        if (IsOpenDoor (m_backgroundItemflags))
        {
            backgroundItemId = BACKGROUND_ITEM_OPEN_CAVE_DOOR;
        } // Endif.
        break;

    case BACKGROUND_ITEM_CLOSED_TRAP_DOOR:
        if (IsOpenDoor (m_backgroundItemflags))
        {
            backgroundItemId = BACKGROUND_ITEM_OPEN_TRAP_DOOR;
        } // Endif.
        break;

    case BACKGROUND_ITEM_OPEN_TRAP_DOOR:
        if (IsClosedDoor (m_backgroundItemflags))
        {
            backgroundItemId = BACKGROUND_ITEM_CLOSED_TRAP_DOOR;
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (backgroundItemId);
} // Endproc.


UInt32  GetMaxBackgroundItemsOnScreen (BACKGROUND_ITEM_ID backgroundItemId)
{
    UInt32  maxBackgroundItemsOnScreen = 0; // Initialise!

    switch (backgroundItemId)
    {
    case BACKGROUND_ITEM_CLOSED_TRAP_DOOR:
        // Get the maximum background items on any single screen.

        for (UInt32 screenNumber = MIN_SCREEN_NUMBER; screenNumber <= MAX_SCREEN_NUMBER; ++screenNumber)
        {
            UInt32  numOfBackgroundItemsOnScreen = 0;   // Initialise!

            for (UInt32 index = 0; 
                 index < (sizeof (g_backgroundItemsTable) / sizeof (BackgroundItem));
                 ++index)
            {              
                if (g_backgroundItemsTable [index].GetScreenNumber () == screenNumber)
                {
                    switch (g_backgroundItemsTable [index].GetBackgroundItemId ())
                    {
                    case BACKGROUND_ITEM_OPEN_TRAP_DOOR:
                        numOfBackgroundItemsOnScreen++;
                        break;
                    default:
                        break;
                    } // Endswitch.

                } // Endif.

            } // Endfor.

            if (numOfBackgroundItemsOnScreen > maxBackgroundItemsOnScreen)
            {
                maxBackgroundItemsOnScreen = numOfBackgroundItemsOnScreen;
            } // Endif.

        } // Endfor.
        break;

    case BACKGROUND_ITEM_CLOSED_NORMAL_DOOR:
    case BACKGROUND_ITEM_OPEN_NORMAL_DOOR:
        // Get the maximum background items on any single screen.

        for (UInt32 screenNumber = MIN_SCREEN_NUMBER; screenNumber <= MAX_SCREEN_NUMBER; ++screenNumber)
        {
            UInt32  numOfBackgroundItemsOnScreen = 1;   // Initialise!

            for (UInt32 index = 0; 
                 index < (sizeof (g_backgroundItemsTable) / sizeof (BackgroundItem));
                 ++index)
            {              
                if (g_backgroundItemsTable [index].GetScreenNumber () == screenNumber)
                {
                    switch (g_backgroundItemsTable [index].GetBackgroundItemId ())
                    {
                    case BACKGROUND_ITEM_NORMAL_DOOR_FRAME:
                    case BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR:      
                    case BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR:    
                    case BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR:     
                    case BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR:   
                        numOfBackgroundItemsOnScreen++;
                        break;
                    default:
                        break;
                    } // Endswitch.

                } // Endif.

            } // Endfor.

            if (numOfBackgroundItemsOnScreen > maxBackgroundItemsOnScreen)
            {
                maxBackgroundItemsOnScreen = numOfBackgroundItemsOnScreen;
            } // Endif.

        } // Endfor.
        break;

    case BACKGROUND_ITEM_CLOSED_CAVE_DOOR:
    case BACKGROUND_ITEM_OPEN_CAVE_DOOR:
        // Get the maximum background items on any single screen.

        for (UInt32 screenNumber = MIN_SCREEN_NUMBER; screenNumber <= MAX_SCREEN_NUMBER; ++screenNumber)
        {
            UInt32  numOfBackgroundItemsOnScreen = 0;   // Initialise!

            for (UInt32 index = 0; 
                 index < (sizeof (g_backgroundItemsTable) / sizeof (BackgroundItem));
                 ++index)
            {              
                if (g_backgroundItemsTable [index].GetScreenNumber () == screenNumber)
                {
                    switch (g_backgroundItemsTable [index].GetBackgroundItemId ())
                    {
                    case BACKGROUND_ITEM_CAVE_DOOR_FRAME:
                    case BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR:      
                    case BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR:    
                    case BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR:     
                    case BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR:   
                        numOfBackgroundItemsOnScreen++;
                        break;
                    default:
                        break;
                    } // Endswitch.

                } // Endif.

            } // Endfor.

            if (numOfBackgroundItemsOnScreen > maxBackgroundItemsOnScreen)
            {
                maxBackgroundItemsOnScreen = numOfBackgroundItemsOnScreen;
            } // Endif.

        } // Endfor.
        break;

    case BACKGROUND_ITEM_BIG_DOOR_FRAME:
    case BACKGROUND_ITEM_CAVE_DOOR_FRAME:
    case BACKGROUND_ITEM_NORMAL_DOOR_FRAME:
    case BACKGROUND_ITEM_RED_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_NORMAL_DOOR:
    case BACKGROUND_ITEM_RED_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_GREEN_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_CYAN_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_YELLOW_LOCKED_CAVE_DOOR:
    case BACKGROUND_ITEM_CLOCK:
    case BACKGROUND_ITEM_PICTURE:
    case BACKGROUND_ITEM_TABLE:
    case BACKGROUND_ITEM_ANTLER_TROPHY:
    case BACKGROUND_ITEM_TROPHY:
    case BACKGROUND_ITEM_BOOKCASE:
    case BACKGROUND_ITEM_OPEN_TRAP_DOOR:
    case BACKGROUND_ITEM_BARREL:
    case BACKGROUND_ITEM_RUG:
    case BACKGROUND_ITEM_ACG_SHIELD:
    case BACKGROUND_ITEM_SHIELD:
    case BACKGROUND_ITEM_KNIGHT:
    case BACKGROUND_ITEM_ACG_EXIT_DOOR:
    case BACKGROUND_ITEM_PICTURE_2:
    case BACKGROUND_ITEM_SKELETON:
    case BACKGROUND_ITEM_BARRELS:
    default:
        // Get the maximum background items on any single screen.

        for (UInt32 screenNumber = MIN_SCREEN_NUMBER; screenNumber <= MAX_SCREEN_NUMBER; ++screenNumber)
        {
            UInt32  numOfBackgroundItemsOnScreen = 0;   // Initialise!

            for (UInt32 index = 0; 
                 index < (sizeof (g_backgroundItemsTable) / sizeof (BackgroundItem));
                 ++index)
            {              
                if ((g_backgroundItemsTable [index].GetScreenNumber () == screenNumber) &&
                    (g_backgroundItemsTable [index].GetBackgroundItemId () == backgroundItemId))
                {
                    numOfBackgroundItemsOnScreen++;
                } // Endif.

            } // Endfor.

            if (numOfBackgroundItemsOnScreen > maxBackgroundItemsOnScreen)
            {
                maxBackgroundItemsOnScreen = numOfBackgroundItemsOnScreen;
            } // Endif.

        } // Endfor.
        break;
    } // Endswitch.

    return (maxBackgroundItemsOnScreen);
} // Endproc.


FolioStatus CreateBackgroundItems (BackgroundItemsList& backgroundItemsList)
{
    FolioStatus status = ERR_SUCCESS;

    backgroundItemsList.clear ();   // Initialise!

    // Build the background items list.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_backgroundItemsTable) / sizeof (BackgroundItem)));
         ++index)
    {              
        // Store the background item in the list of background items.

        backgroundItemsList.push_back (BackgroundItemPtr(new BackgroundItem(g_backgroundItemsTable [index])));
    } // Endif.

    if (status != ERR_SUCCESS)
    {
        backgroundItemsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


BackgroundItemsList GetScreenBackgroundItemsList (UInt32                        screenNumber,
                                                  const BackgroundItemsList&    backgroundItemsList)
{
    BackgroundItemsList screenBackgroundItemsList;

    // Get the background items list for the specified screen number.

    for (BackgroundItemsList::const_iterator itr = backgroundItemsList.begin ();
         itr != backgroundItemsList.end ();
         ++itr)
    {                   
        if (itr->get ()->GetScreenNumber () == screenNumber)
        {
            // Add the background item.

            screenBackgroundItemsList.push_back (*itr);
        } // Endif.


    } // Endfor.

    return (screenBackgroundItemsList);
} // Endproc.


BackgroundItemPtr   GetOppositeDoor (const BackgroundItem*      currentDoorBackgroundItem,
                                     const BackgroundItemsList& backgroundItemsList,
                                     bool                       setBackgroundItemGraphic)
{
    BackgroundItemPtr   oppositeDoorBackgroundItem;

    // Is this a door?

    if (currentDoorBackgroundItem &&
        currentDoorBackgroundItem->IsDoor (currentDoorBackgroundItem->GetBackgroundItemFlags ()))
    {
        // Yes. Find the door in the background items list.

        for (BackgroundItemsList::const_iterator itr = backgroundItemsList.begin ();
             itr != backgroundItemsList.end ();
             ++itr)
        {
            if (itr->get () == currentDoorBackgroundItem)
            {
                // Get the opposite door.

                oppositeDoorBackgroundItem = std::distance (backgroundItemsList.begin (), itr) % 2 
                                             ? *(itr - 1) 
                                             : *(itr + 1);

                if (setBackgroundItemGraphic)
                {
                    // Set the opposite door's new graphic.

                    oppositeDoorBackgroundItem->SetBackgroundItemGraphic ();
                } // Endif.

                break;  // Get-outta-here!
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (oppositeDoorBackgroundItem);
} // Endproc.


UInt32  GetNewScreenNumber (const BackgroundItem*       currentDoorBackgroundItem,
                            const BackgroundItemsList&  backgroundItemsList)
{
    // Get the door opposite to the specified current door.

    BackgroundItemPtr   oppositeDoorBackgroundItem(GetOppositeDoor (currentDoorBackgroundItem, 
                                                                    backgroundItemsList, 
                                                                    true));

    return (oppositeDoorBackgroundItem ? oppositeDoorBackgroundItem->GetScreenNumber () : SCREEN_NUMBER_UNDEFINED);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
