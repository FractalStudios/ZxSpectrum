// "Home-made" includes.
#include    "StdAfx.h"

// "Home-made" includes.
#include    <Util.h>

namespace Folio
{

namespace Core
{

namespace Util
{

FolioString DescribeBitmapResourceId (UInt16 bitmapResourceId)
{
    switch (bitmapResourceId)
    {
    case 102: return (TXT("IDB_BITMAP_CAVE_DOOR_FRAME"));
    case 103: return (TXT("IDB_BITMAP_NORMAL_DOOR_FRAME"));
    case 104: return (TXT("IDB_BITMAP_BIG_DOOR_FRAME"));
    case 105: return (TXT("IDB_BITMAP_RED_LOCKED_NORMAL_DOOR"));
    case 106: return (TXT("IDB_BITMAP_GREEN_LOCKED_NORMAL_DOOR"));
    case 107: return (TXT("IDB_BITMAP_CYAN_LOCKED_NORMAL_DOOR"));
    case 108: return (TXT("IDB_BITMAP_YELLOW_LOCKED_NORMAL_DOOR"));
    case 109: return (TXT("IDB_BITMAP_RED_LOCKED_CAVE_DOOR"));
    case 110: return (TXT("IDB_BITMAP_GREEN_LOCKED_CAVE_DOOR"));
    case 111: return (TXT("IDB_BITMAP_CYAN_LOCKED_CAVE_DOOR"));
    case 112: return (TXT("IDB_BITMAP_YELLOW_LOCKED_CAVE_DOOR"));
    case 113: return (TXT("IDB_BITMAP_CLOCK"));
    case 114: return (TXT("IDB_BITMAP_PICTURE"));
    case 115: return (TXT("IDB_BITMAP_TABLE"));
    case 116: return (TXT("IDB_BITMAP_FULL_TURKEY"));
    case 117: return (TXT("IDB_BITMAP_TURKEY_CARCASS"));
    case 118: return (TXT("IDB_BITMAP_ANTLER_TROPHY"));
    case 119: return (TXT("IDB_BITMAP_TROPHY"));
    case 120: return (TXT("IDB_BITMAP_BOOKCASE"));
    case 121: return (TXT("IDB_BITMAP_CLOSED_TRAP_DOOR"));
    case 122: return (TXT("IDB_BITMAP_OPEN_TRAP_DOOR"));
    case 123: return (TXT("IDB_BITMAP_BARREL"));
    case 124: return (TXT("IDB_BITMAP_RUG"));
    case 125: return (TXT("IDB_BITMAP_ACG_SHIELD"));
    case 126: return (TXT("IDB_BITMAP_SHIELD"));
    case 127: return (TXT("IDB_BITMAP_KNIGHT"));
    case 128: return (TXT("IDB_BITMAP_CLOSED_NORMAL_DOOR"));
    case 129: return (TXT("IDB_BITMAP_OPEN_NORMAL_DOOR"));
    case 130: return (TXT("IDB_BITMAP_CLOSED_CAVE_DOOR"));
    case 131: return (TXT("IDB_BITMAP_OPEN_CAVE_DOOR"));
    case 132: return (TXT("IDB_BITMAP_ACG_EXIT_DOOR"));
    case 133: return (TXT("IDB_BITMAP_PICTURE_2"));
    case 134: return (TXT("IDB_BITMAP_SKELETON"));
    case 135: return (TXT("IDB_BITMAP_BARRELS"));
    case 136: return (TXT("IDB_BITMAP_ROOM_0"));
    case 137: return (TXT("IDB_BITMAP_ROOM_1"));
    case 138: return (TXT("IDB_BITMAP_ROOM_2"));
    case 139: return (TXT("IDB_BITMAP_ROOM_3"));
    case 140: return (TXT("IDB_BITMAP_ROOM_4"));
    case 141: return (TXT("IDB_BITMAP_ROOM_5"));
    case 142: return (TXT("IDB_BITMAP_ROOM_6"));
    case 143: return (TXT("IDB_BITMAP_ROOM_7"));
    case 144: return (TXT("IDB_BITMAP_ROOM_8"));
    case 145: return (TXT("IDB_BITMAP_ROOM_9"));
    case 146: return (TXT("IDB_BITMAP_ROOM_10"));
    case 147: return (TXT("IDB_BITMAP_ROOM_11"));
    case 148: return (TXT("IDB_BITMAP_SCROLL"));
    case 149: return (TXT("IDB_BITMAP_SCROLL_SEAL"));
    case 150: return (TXT("IDB_BITMAP_LEAF"));
    case 151: return (TXT("IDB_BITMAP_KEY"));
    case 152: return (TXT("IDB_BITMAP_BOTTLE"));
    case 153: return (TXT("IDB_BITMAP_MEDICINE_BOTTLE"));
    case 154: return (TXT("IDB_BITMAP_BROKEN"));
    case 155: return (TXT("IDB_BITMAP_ROPE"));
    case 156: return (TXT("IDB_BITMAP_ARM"));
    case 157: return (TXT("IDB_BITMAP_BOWL"));
    case 158: return (TXT("IDB_BITMAP_APPLE"));
    case 159: return (TXT("IDB_BITMAP_CANDY_BAR"));
    case 160: return (TXT("IDB_BITMAP_HAM"));
    case 161: return (TXT("IDB_BITMAP_LOLLIPOP"));
    case 162: return (TXT("IDB_BITMAP_MONEY_BAG"));
    case 163: return (TXT("IDB_BITMAP_GOBSTOPPER"));
    case 164: return (TXT("IDB_BITMAP_AMULET"));
    case 165: return (TXT("IDB_BITMAP_CAN"));
    case 166: return (TXT("IDB_BITMAP_ICE_CREAM_CONE"));
    case 167: return (TXT("IDB_BITMAP_CRUCIFIX"));
    case 168: return (TXT("IDB_BITMAP_SKULL"));
    case 169: return (TXT("IDB_BITMAP_SPANNER"));
    case 170: return (TXT("IDB_BITMAP_MUSHROOM"));
    case 171: return (TXT("IDB_BITMAP_GRAVESTONE"));
    case 172: return (TXT("IDB_BITMAP_ACG_KEY_LEFT"));
    case 173: return (TXT("IDB_BITMAP_ACG_KEY_MIDDLE"));
    case 174: return (TXT("IDB_BITMAP_ACG_KEY_RIGHT"));
    case 175: return (TXT("IDB_BITMAP_KEYBOARD_LEFT_PANE"));
    case 176: return (TXT("IDB_BITMAP_KEYBOARD_RIGHT_PANE"));
    case 177: return (TXT("IDB_BITMAP_CURSOR_DIRECTIONS_LEFT_PANE"));
    case 178: return (TXT("IDB_BITMAP_CURSOR_DIRECTIONS_RIGHT_PANE"));
    case 179: return (TXT("IDB_BITMAP_JOYSTICK_LEFT_PANE"));
    case 180: return (TXT("IDB_BITMAP_JOYSTICK_RIGHT_PANE"));
    case 186: return (TXT("IDB_BITMAP_KNIGHT_WALKING_DOWN_1"));
    case 187: return (TXT("IDB_BITMAP_KNIGHT_WALKING_UP_1")); 
    case 188: return (TXT("IDB_BITMAP_KNIGHT_DOWN")); 
    case 189: return (TXT("IDB_BITMAP_KNIGHT_WALKING_DOWN_2")); 
    case 190: return (TXT("IDB_BITMAP_KNIGHT_UP"));
    case 191: return (TXT("IDB_BITMAP_KNIGHT_WALKING_UP_2"));
    case 192: return (TXT("IDB_BITMAP_KNIGHT_WALKING_LEFT_1"));
    case 193: return (TXT("IDB_BITMAP_KNIGHT_WALKING_RIGHT_1"));
    case 194: return (TXT("IDB_BITMAP_KNIGHT_LEFT"));
    case 195: return (TXT("IDB_BITMAP_KNIGHT_WALKING_LEFT_2")); 
    case 196: return (TXT("IDB_BITMAP_KNIGHT_RIGHT"));
    case 197: return (TXT("IDB_BITMAP_KNIGHT_WALKING_RIGHT_2"));
    case 198: return (TXT("IDB_BITMAP_WIZARD_WALKING_DOWN_1"));
    case 199: return (TXT("IDB_BITMAP_WIZARD_WALKING_UP_1")); 
    case 200: return (TXT("IDB_BITMAP_WIZARD_DOWN")); 
    case 201: return (TXT("IDB_BITMAP_WIZARD_WALKING_DOWN_2")); 
    case 202: return (TXT("IDB_BITMAP_WIZARD_UP"));
    case 203: return (TXT("IDB_BITMAP_WIZARD_WALKING_UP_2"));
    case 204: return (TXT("IDB_BITMAP_WIZARD_WALKING_LEFT_1"));
    case 205: return (TXT("IDB_BITMAP_WIZARD_WALKING_RIGHT_1"));
    case 206: return (TXT("IDB_BITMAP_WIZARD_LEFT"));
    case 207: return (TXT("IDB_BITMAP_WIZARD_WALKING_LEFT_2"));
    case 208: return (TXT("IDB_BITMAP_WIZARD_RIGHT"));
    case 209: return (TXT("IDB_BITMAP_WIZARD_WALKING_RIGHT_2"));
    case 210: return (TXT("IDB_BITMAP_SERF_WALKING_DOWN_1"));
    case 211: return (TXT("IDB_BITMAP_SERF_WALKING_UP_1"));
    case 212: return (TXT("IDB_BITMAP_SERF_DOWN"));
    case 213: return (TXT("IDB_BITMAP_SERF_WALKING_DOWN_2"));
    case 214: return (TXT("IDB_BITMAP_SERF_UP"));
    case 215: return (TXT("IDB_BITMAP_SERF_WALKING_UP_2"));
    case 216: return (TXT("IDB_BITMAP_SERF_WALKING_LEFT_1"));
    case 217: return (TXT("IDB_BITMAP_SERF_WALKING_RIGHT_1"));
    case 218: return (TXT("IDB_BITMAP_SERF_LEFT"));
    case 219: return (TXT("IDB_BITMAP_SERF_WALKING_LEFT_2"));
    case 220: return (TXT("IDB_BITMAP_SERF_RIGHT"));
    case 221: return (TXT("IDB_BITMAP_SERF_WALKING_RIGHT_2"));
    case 222: return (TXT("IDB_BITMAP_FALLING_SIMULATION_01"));
    case 223: return (TXT("IDB_BITMAP_FALLING_SIMULATION_02"));
    case 224: return (TXT("IDB_BITMAP_FALLING_SIMULATION_03"));
    case 225: return (TXT("IDB_BITMAP_FALLING_SIMULATION_04"));
    case 226: return (TXT("IDB_BITMAP_FALLING_SIMULATION_05"));
    case 227: return (TXT("IDB_BITMAP_FALLING_SIMULATION_06"));
    case 228: return (TXT("IDB_BITMAP_PUMPKIN_1"));
    case 229: return (TXT("IDB_BITMAP_PUMPKIN_2"));
    case 230: return (TXT("IDB_BITMAP_SPIDER_1"));
    case 231: return (TXT("IDB_BITMAP_SPIDER_2"));
    case 232: return (TXT("IDB_BITMAP_GHOST_1"));
    case 233: return (TXT("IDB_BITMAP_GHOST_2"));
    case 234: return (TXT("IDB_BITMAP_BOUNCY_1"));
    case 235: return (TXT("IDB_BITMAP_BOUNCY_2"));
    case 236: return (TXT("IDB_BITMAP_SMORPH_1"));
    case 237: return (TXT("IDB_BITMAP_SMORPH_2"));
    case 238: return (TXT("IDB_BITMAP_JELLY_GHOUL_1"));
    case 239: return (TXT("IDB_BITMAP_JELLY_GHOUL_2"));
    case 240: return (TXT("IDB_BITMAP_BAT_1"));
    case 241: return (TXT("IDB_BITMAP_BAT_2"));
    case 242: return (TXT("IDB_BITMAP_WITCH_FLYING_LEFT_1"));
    case 243: return (TXT("IDB_BITMAP_WITCH_FLYING_LEFT_2"));
    case 244: return (TXT("IDB_BITMAP_WITCH_FLYING_RIGHT_1"));
    case 245: return (TXT("IDB_BITMAP_WITCH_FLYING_RIGHT_2"));
    case 246: return (TXT("IDB_BITMAP_GHOUL_FLYING_LEFT_1"));
    case 247: return (TXT("IDB_BITMAP_GHOUL_FLYING_LEFT_2"));
    case 248: return (TXT("IDB_BITMAP_GHOUL_FLYING_RIGHT_1"));
    case 249: return (TXT("IDB_BITMAP_GHOUL_FLYING_RIGHT_2"));
    case 250: return (TXT("IDB_BITMAP_BAT_FLYING_LEFT_1"));
    case 251: return (TXT("IDB_BITMAP_BAT_FLYING_LEFT_2"));
    case 252: return (TXT("IDB_BITMAP_BAT_FLYING_RIGHT_1"));
    case 253: return (TXT("IDB_BITMAP_BAT_FLYING_RIGHT_2"));
    case 254: return (TXT("IDB_BITMAP_GHOUL_1"));
    case 255: return (TXT("IDB_BITMAP_GHOUL_2"));
    case 256: return (TXT("IDB_BITMAP_NASTY_ALIVE_1"));
    case 257: return (TXT("IDB_BITMAP_NASTY_ALIVE_2"));
    case 258: return (TXT("IDB_BITMAP_NASTY_ALIVE_3"));
    case 259: return (TXT("IDB_BITMAP_NASTY_ALIVE_4"));
    case 260: return (TXT("IDB_BITMAP_NASTY_DEAD_1"));
    case 261: return (TXT("IDB_BITMAP_NASTY_DEAD_2"));
    case 262: return (TXT("IDB_BITMAP_NASTY_DEAD_3"));
    case 263: return (TXT("IDB_BITMAP_NASTY_DEAD_4"));
    case 264: return (TXT("IDB_BITMAP_KNIGHT_AXE_1"));
    case 265: return (TXT("IDB_BITMAP_KNIGHT_AXE_2"));
    case 266: return (TXT("IDB_BITMAP_KNIGHT_AXE_3"));
    case 267: return (TXT("IDB_BITMAP_KNIGHT_AXE_4"));
    case 268: return (TXT("IDB_BITMAP_KNIGHT_AXE_5"));
    case 269: return (TXT("IDB_BITMAP_KNIGHT_AXE_6"));
    case 270: return (TXT("IDB_BITMAP_KNIGHT_AXE_7"));
    case 271: return (TXT("IDB_BITMAP_KNIGHT_AXE_8"));
    case 272: return (TXT("IDB_BITMAP_WIZARD_POTION_1"));
    case 273: return (TXT("IDB_BITMAP_WIZARD_POTION_2"));
    case 274: return (TXT("IDB_BITMAP_WIZARD_POTION_3"));
    case 275: return (TXT("IDB_BITMAP_SERF_SWORD_1"));
    case 276: return (TXT("IDB_BITMAP_SERF_SWORD_2"));
    case 277: return (TXT("IDB_BITMAP_SERF_SWORD_3"));
    case 278: return (TXT("IDB_BITMAP_SERF_SWORD_4"));
    case 279: return (TXT("IDB_BITMAP_SERF_SWORD_5"));
    case 280: return (TXT("IDB_BITMAP_SERF_SWORD_6"));
    case 281: return (TXT("IDB_BITMAP_SERF_SWORD_7"));
    case 282: return (TXT("IDB_BITMAP_SERF_SWORD_8"));
    case 283: return (TXT("IDB_BITMAP_MUMMY_1"));
    case 284: return (TXT("IDB_BITMAP_MUMMY_2"));
    case 285: return (TXT("IDB_BITMAP_MUMMY_3"));
    case 286: return (TXT("IDB_BITMAP_DRACULA_1"));
    case 287: return (TXT("IDB_BITMAP_DRACULA_2"));
    case 288: return (TXT("IDB_BITMAP_DRACULA_3"));
    case 289: return (TXT("IDB_BITMAP_FRANKENSTEIN_1"));
    case 290: return (TXT("IDB_BITMAP_FRANKENSTEIN_2"));
    case 291: return (TXT("IDB_BITMAP_FRANKENSTEIN_3"));
    case 292: return (TXT("IDB_BITMAP_HUNCHBACK_1"));
    case 293: return (TXT("IDB_BITMAP_HUNCHBACK_2"));
    case 294: return (TXT("IDB_BITMAP_HUNCHBACK_3"));
    case 295: return (TXT("IDB_BITMAP_DEVIL_1"));
    case 296: return (TXT("IDB_BITMAP_DEVIL_2"));
    case 297: return (TXT("IDB_BITMAP_DEVIL_3"));
    case 298: return (TXT("IDB_BITMAP_LOADING_SCREEN"));
    default:
        {
            FolioOStringStream  str;

            str << std::dec << bitmapResourceId;

            return (str.str ());
        } // Endscope.

    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
