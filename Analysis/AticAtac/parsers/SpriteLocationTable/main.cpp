#include "stdafx.h"
#include "File.h"


static  const   WORD    START_ADDRESS = 0x6025;

struct AddressDetails
{
    AddressDetails ()
    :   m_wAddress(0),
        m_byByte(0),
        m_bKnown(false)
    {} // Endproc.

    AddressDetails (WORD    wAddress,
                    BYTE    byByte)
    :   m_wAddress(wAddress),
        m_byByte(byByte),
        m_bKnown(false)
    {} // Endproc.

    WORD    m_wAddress;
    BYTE    m_byByte;
    bool    m_bKnown;
}; // Endstruct.

typedef std::map<WORD, AddressDetails> AddressMap;

typedef std::vector<BYTE>   DataList;

DWORD   ReadFile (const std::wstring    &filePath,
                  DataList              &fileData)
{
    // Open the file for reading.

    Utils::File    file;

    DWORD   dwWin32Error = file.Create (filePath, 
                                        GENERIC_READ,
                                        FILE_SHARE_READ,
                                        OPEN_EXISTING);

    if (dwWin32Error == ERROR_SUCCESS)
    {
        // Get the file's size.

        UINT    uiLowOrderSize  = 0;    // Initialise!
        UINT    uiHighOrderSize = 0;

        dwWin32Error = file.QuerySize (uiLowOrderSize, uiHighOrderSize);

        if (dwWin32Error == ERROR_SUCCESS)
        {
            // Read from the file.

            fileData.resize (uiLowOrderSize);

            UINT    uiNumOfBytes = uiLowOrderSize;

            dwWin32Error = file.Read (&(fileData [0]), uiNumOfBytes);

            if (dwWin32Error == ERROR_SUCCESS)
            {
                fileData.resize (uiNumOfBytes);
            } // Endif.

            else
            {
                ::wprintf (L"Read file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s.",
                           dwWin32Error, dwWin32Error,
                           filePath.c_str ());
            } // Endelse.

        } // Endif.

        else
        {
            ::wprintf (L"Query file size failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s.",
                       dwWin32Error, dwWin32Error,
                       filePath.c_str ());
        } // Endelse.

    } // Endif.

    else
    {
        ::wprintf (L"Create file failed, dwWin32Error=%u(0x%08.08x), szFolderPath=%s, uiDesiredAccess=0x%08.08x, uiShareMode=0x%08.08x, uiCreationDisposition=0x%08.08x, uiAttributes=0x%08.08x.",
                   dwWin32Error, dwWin32Error,
                   filePath.c_str (),
                   GENERIC_READ,
                   FILE_SHARE_READ,
                   OPEN_EXISTING,
                   FILE_ATTRIBUTE_NORMAL);
    } // Endelse.

    return (dwWin32Error);
} // Endproc.


std::wstring    DescribeAttribute (BYTE byAttribute)
{
    static  const   BYTE    ATTRIBUTE_MASK = 0xf0;

    static  const   BYTE    FLASH   = 0x80;
    static  const   BYTE    BRIGHT  = 0x40;

    std::wostringstream str;

    if (byAttribute & FLASH)
    {
        str << L"Flash ";
    } // Endif.

    if (byAttribute & BRIGHT)
    {
        str << L"Bright ";
    } // Endif.

    return (str.str ());
} // Endproc.


std::wstring    DescribeColour (BYTE byColour)
{
    static  const   BYTE    COLOUR_MASK = 0x0f;

    static  const   BYTE    BLACK   = 0;  
    static  const   BYTE    BLUE    = 1;  
    static  const   BYTE    RED     = 2;  
    static  const   BYTE    MAGENTA = 3;  
    static  const   BYTE    GREEN   = 4;  
    static  const   BYTE    CYAN    = 5;  
    static  const   BYTE    YELLOW  = 6;  
    static  const   BYTE    WHITE   = 7;

    switch (byColour & COLOUR_MASK)
    {
    case BLACK:
        return (L"Black");
        break;
    case BLUE:
        return (L"Blue");
        break;
    case RED:
        return (L"Red");
        break;
    case MAGENTA:
        return (L"Magenta");
        break;
    case GREEN:
        return (L"Green");
        break;
    case CYAN:
        return (L"Cyan");
        break;
    case YELLOW:
        return (L"Yellow");
        break;
    case WHITE:
        return (L"White");
        break;
    default:
        {
            std::wostringstream str;
            str << static_cast<int> (byColour);
            return (str.str ());
        } // Endscope.
        break;
    } // Endswitch.

} // Endproc.


std::wstring    DescribeGraphic (BYTE byGraphicType)
{
    std::wostringstream str;
    str << static_cast<int> (byGraphicType) << L' ';

    switch (byGraphicType - 1)
    {  
    case 0	 : str << "Knight Walking Left 1"; break;
    case 1	 : str << "Knight Left"; break;
    case 2	 : str << "Knight Walking Left 2"; break;
    case 4	 : str << "Knight Walking Right 1"; break;
    case 5	 : str << "Knight Right"; break;
    case 6	 : str << "Knight Walking Right 2"; break;
    case 8	 : str << "Knight Walking Up 1"; break;
    case 9	 : str << "Knight Up"; break;
    case 10	 : str << "Knight Walking Up 2"; break;
    case 12	 : str << "Knight Walking Down 1"; break;
    case 13	 : str << "Knight Down"; break;
    case 14	 : str << "Knight Walking Down 2"; break;
    case 16	 : str << "Wizard Walking Left 1"; break;
    case 17	 : str << "Wizard Left"; break;
    case 18	 : str << "Wizard Walking Left 2"; break;
    case 20	 : str << "Wizard Walking Right 1"; break;
    case 21	 : str << "Wizard Right"; break;
    case 22	 : str << "Wizard Walking Right 2"; break;
    case 24	 : str << "Wizard Walking Up 1"; break;
    case 25	 : str << "Wizard Up"; break;
    case 26	 : str << "Wizard Walking Up 2"; break;
    case 28	 : str << "Wizard Walking Down 1"; break;
    case 29	 : str << "Wizard Down"; break;
    case 30	 : str << "Wizard Walking Down 2"; break;
    case 32	 : str << "Serf Walking Left 1"; break;
    case 33	 : str << "Serf Left"; break;
    case 34	 : str << "Serf Walking Left 2"; break;
    case 36	 : str << "Serf Walking Right 1"; break;
    case 37	 : str << "Serf Right"; break;
    case 38	 : str << "Serf Walking Right 2"; break;
    case 40	 : str << "Serf Walking Up 1"; break;
    case 41	 : str << "Serf Up"; break;
    case 42	 : str << "Serf Walking Up 2"; break;
    case 44	 : str << "Serf Walking Down 1"; break;
    case 45	 : str << "Serf Down"; break;
    case 46	 : str << "Serf Walking Down 2"; break;
    case 48	 : str << "Unknown"; break;
    case 49	 : str << "Cursor Directions Left Pane"; break;
    case 50	 : str << "Cursor Directions Right Pane"; break;
    case 51	 : str << "Wizard Potion 1"; break;
    case 52	 : str << "Wizard Potion 2"; break;
    case 54	 : str << "Wizard Potion 3"; break;
    case 55	 : str << "Knight Sword 1"; break;
    case 56	 : str << "Knight Sword 2"; break;
    case 57	 : str << "Knight Sword 3"; break;
    case 58	 : str << "Knight Sword 4"; break;
    case 59	 : str << "Knight Sword 5"; break;
    case 60	 : str << "Knight Sword 6"; break;
    case 61	 : str << "Knight Sword 7"; break;
    case 62	 : str << "Knight Sword 8"; break;
    case 63	 : str << "Serf Axe 1"; break;
    case 64	 : str << "Serf Axe 2"; break;
    case 65	 : str << "Serf Axe 3"; break;
    case 66	 : str << "Serf Axe 4"; break;
    case 67	 : str << "Serf Axe 5"; break;
    case 68	 : str << "Serf Axe 6"; break;
    case 69	 : str << "Serf Axe 7"; break;
    case 70	 : str << "Serf Axe 8"; break;
    case 71	 : str << "Keyboard Left Pane"; break;
    case 72	 : str << "Keyboard Right Pane"; break;
    case 73	 : str << "Joystick Left Pane"; break;
    case 74	 : str << "Joystick Right Pane"; break;
    case 75	 : str << "Pumpkin 1"; break;
    case 76	 : str << "Pumpkin 2"; break;
    case 77	 : str << "Ghoul 1"; break;
    case 78	 : str << "Ghoul 2"; break;
    case 79	 : str << "Can"; break;
    case 80	 : str << "Candy Bar"; break;
    case 81	 : str << "Ham"; break;
    case 82	 : str << "Lollipop"; break;
    case 83	 : str << "Ice Cream Cone"; break;
    case 84	 : str << "Bowl"; break;
    case 85	 : str << "Apple"; break;
    case 86	 : str << "Bottle"; break;
    case 88	 : str << "Character Appear 2"; break;
    case 89	 : str << "Character Appear 3"; break;
    case 90	 : str << "Character Appear 4"; break;
    case 91	 : str << "Spider 1"; break;
    case 92	 : str << "Spider 2"; break;
    case 93	 : str << "Ghost 1"; break;
    case 94	 : str << "Ghost 2"; break;
    case 95	 : str << "Bouncy 1"; break;
    case 96	 : str << "Bouncy 2"; break;
    case 97	 : str << "Smorph 1"; break;
    case 98	 : str << "Smorph 2"; break;
    case 99 : str << "Unknown"; break;
    case 103: str << "Jelly Ghoul 1"; break;
    case 104: str << "Jelly Ghoul 2"; break;
    case 105: str << "Bat 1"; break;
    case 106: str << "Bat 2"; break;
    case 107: str << "Character Dead 1"; break;
    case 108: str << "Character Dead 2"; break;
    case 109: str << "Character Dead 3"; break;
    case 110: str << "Character Dead 4"; break;
    case 111: str << "Mummy 1"; break;
    case 112: str << "Mummy 2"; break;
    case 113: str << "Mummy 3"; break;
    case 115: str << "Frankenstien 1"; break;
    case 116: str << "Frankenstien 2"; break;
    case 117: str << "Frankenstien 3"; break;
    case 119: str << "Devil 1"; break;
    case 120: str << "Devil 2"; break;
    case 121: str << "Devil 3"; break;
    case 123: str << "Dracula 1"; break;
    case 124: str << "Dracula 2"; break;
    case 125: str << "Dracula 3"; break;
    case 127: str << "Leaf"; break;
    case 128: str << "Key"; break;
    case 129: str << "Medicine Bottle"; break;
    case 130: str << "Gobstopper"; break;
    case 131: str << "Broken"; break;
    case 132: str << "Rope"; break;
    case 133: str << "Arm"; break;
    case 134: str << "Amulet"; break;
    case 135: str << "Money Bag"; break;
    case 136: str << "Skeleton Head"; break;
    case 137: str << "Cross"; break;
    case 138: str << "Spanner"; break;
    case 139: str << "ACG Key Left"; break;
    case 140: str << "ACG Key Middle"; break;
    case 141: str << "ACG Key Right"; break;
    case 142: str << "Gravestone"; break;
    case 143: str << "Witch Flying Left 1"; break;
    case 144: str << "Witch Flying Left 2"; break;
    case 145: str << "Witch Flying Right 1"; break;
    case 146: str << "Witch Flying Right 2"; break;
    case 147: str << "Ghoul Flying Left 1"; break;
    case 148: str << "Ghoul Flying Left 2"; break;
    case 149: str << "Ghoul Flying Right 1"; break;
    case 150: str << "Ghoul Flying Right 2"; break;
    case 151: str << "Bat Flying Left 1"; break;
    case 152: str << "Bat Flying Left 2"; break;
    case 153: str << "Bat Flying Right 1"; break;
    case 154: str << "Bat Flying Right 2"; break;
    case 155: str << "Hunchback 1"; break;
    case 156: str << "Hunchback 2"; break;
    case 157: str << "Hunchback 3"; break;
    case 160: str << "Mushroom"; break;
    default: str << "Unknown"; break;
    } // Endswitch.

    return (str.str ());
} // Endproc.


struct SpriteLocation
{
    SpriteLocation ()
    :   m_wAddress(0),
        m_byGraphicType(0),
        m_byRoom(0),
        m_byUnknown1(0),
        m_byXPosition(0),
        m_byYPosition(0),
        m_byColour(0),
        m_byUnknown2(0),
        m_byUnknown3(0)
    {} // Endproc.

    void    Reset ()
    {
        m_wAddress      = 0;
        m_byGraphicType = 0;
        m_byRoom        = 0;
        m_byUnknown1    = 0;
        m_byXPosition   = 0;
        m_byYPosition   = 0;
        m_byColour      = 0;
        m_byUnknown2    = 0;
        m_byUnknown3    = 0;
    } // Endproc.

    WORD    m_wAddress;
    BYTE    m_byGraphicType;
    BYTE    m_byRoom;
    BYTE    m_byUnknown1;
    BYTE    m_byXPosition;
    BYTE    m_byYPosition;
    BYTE    m_byColour;
    BYTE    m_byUnknown2;
    BYTE    m_byUnknown3;
};

typedef std::vector<SpriteLocation> SpriteLocationList;

int wmain (int argc, WCHAR* argv[])
{
    int nReturnCode = 0;

    if (argc == 2)
    {
        DataList    fileData;
        DWORD   dwin32Error = ReadFile (argv [1], fileData);

        if (dwin32Error == ERROR_SUCCESS)
        {
            SpriteLocationList  backgroundList;
            SpriteLocation  currentSpriteLocation;

            enum PARSE
            {
                GRAPHIC_TYPE = 0,
                ROOM,
                UNKNOWN1,
                X_POSITION,
                Y_POSITION,
                COLOUR,
                UNKNOWN2,
                UNKNOWN3,
            }; // Endenum.

            PARSE   currentParse = GRAPHIC_TYPE;

            bool    bFinished   = false;    // Initialise!
            bool    bFoundData  = false;
            BYTE    byByte      = 0;

            WORD    wAddress = START_ADDRESS;

            AddressMap  addressMap;

            DataList::const_iterator itr = fileData.begin ();

            while (!bFinished && (itr != fileData.end ()))
            {
                if (bFoundData)
                {
                    switch (*itr)
                    {
                    case '0': 
                    case '1': 
                    case '2': 
                    case '3': 
                    case '4': 
                    case '5': 
                    case '6': 
                    case '7': 
                    case '8': 
                    case '9': 
                        byByte *= 16;
                        byByte += *itr - '0';
                        ++itr;
                        break;

                    case 'a':
                    case 'b':
                    case 'c':
                    case 'd':
                    case 'e':
                    case 'f':
                        byByte *= 16;
                        byByte += *itr - 'a' + 10;
                        ++itr;
                        break;

                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                    case 'E':
                    case 'F':
                        byByte *= 16;
                        byByte += *itr - 'A' + 10;
                        ++itr;
                       break;

                    case 'h':
                    case 'H':
                        addressMap [wAddress] = AddressDetails(wAddress, byByte);

                        switch (currentParse)
                        {
                        case GRAPHIC_TYPE:
                            addressMap [wAddress].m_bKnown = true;

                            currentSpriteLocation.m_wAddress      = wAddress;
                            currentSpriteLocation.m_byGraphicType = byByte;
                            currentParse = ROOM;
                            break;

                        case ROOM:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byRoom = byByte;
                            currentParse = UNKNOWN1;
                            break;

                        case UNKNOWN1:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byUnknown1 = byByte;
                            currentParse = X_POSITION;
                            break;

                        case X_POSITION:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byXPosition = byByte;
                            currentParse = Y_POSITION;
                            break;

                        case Y_POSITION:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byYPosition = byByte;
                            currentParse = COLOUR;
                            break;

                        case COLOUR:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byColour = byByte;
                            currentParse = UNKNOWN2;
                            break;

                        case UNKNOWN2:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byUnknown2 = byByte;
                            currentParse = UNKNOWN3;
                            break;

                        case UNKNOWN3:
                            addressMap [wAddress].m_bKnown = true;
                            
                            currentSpriteLocation.m_byUnknown3 = byByte;
                            currentParse = GRAPHIC_TYPE;

                            backgroundList.push_back (currentSpriteLocation);
                            currentSpriteLocation.Reset ();
                            break;

                        default:
                            _asm {int 3};
                            break;
                        } // Endswitch.

                        wAddress++;

                        byByte = 0;
                        ++itr;
                        break;

                    case ' ':
                    case ',':
                        ++itr;
                        break;

                    case '\r':
                    case '\n':
                    case '\t':
                    default:
                        bFoundData  = false;
                        byByte      = 0;
                        break;                                
                    } // Endswitch.

                } // Endif.

                else
                if (((*itr == 'D') || (*itr == 'd')) &&
                   (((itr + 1) != fileData.end ()) && ((*(itr + 1) == 'B') || (*(itr + 1) == 'b'))) &&
                   (((itr + 2) != fileData.end ()) && ((*(itr + 2) == ' '))))
                {
                    bFoundData = true;

                    itr += 3;
                } // Endelseif.

                else
                {
                    ++itr;
                } // Endelse.

            } // Endwhile.

            for (SpriteLocationList::const_iterator itr = backgroundList.begin ();
                 itr != backgroundList.end ();
                 ++itr)
            {
                ::wprintf (L"SpriteLocation Item %03.03u, Address = 0x%04.04x, GraphicType = %s, Room=%03.03u, Unknown1=0x%02.02x, X=%u, Y=%u, Colour=%s, Unknown2=0x%02.02x, Unknown3=0x%02.02x, \n", 
                           itr - backgroundList.begin (),
                           itr->m_wAddress,
                           DescribeGraphic (itr->m_byGraphicType).c_str (),
                           itr->m_byRoom,
                           itr->m_byUnknown1,
                           itr->m_byXPosition,
                           itr->m_byYPosition,
                           DescribeColour (itr->m_byColour).c_str (),
                           itr->m_byUnknown1,
                           itr->m_byUnknown2);
            } // Endfor.

            std::ostringstream  str;

            for (AddressMap::const_iterator itr = addressMap.begin ();
                 itr != addressMap.end ();
                 ++itr)
            {
                if (!itr->second.m_bKnown)
                {
                    std::cout << "0x" << std::hex << std::setfill('0') << std::setw(4) << static_cast<int> (itr->first) << ',' 
                              << "0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<int> (itr->second.m_byByte)
                              << std::endl;
                } // Endif.

            } // Endfor.

        } // Endif.
    
    } // Endif.

    else
    {
        printf ("Feed me a file name to parse.\n");

        nReturnCode = 1;
    } // Endelse.

    return (nReturnCode);
} // Endproc.

/******************************* End of File *******************************/
