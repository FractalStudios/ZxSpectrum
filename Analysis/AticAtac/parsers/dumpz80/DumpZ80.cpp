#include "stdafx.h"
#include "Utils.h"

static  Utils::File     g_dumpFile;
static  Utils::DataList g_dumpFileData;

static  bool    s_bVerbose = false;

struct Z80_V1
{
    BYTE    m_A;            // A register
    BYTE    m_F;            // F register
    WORD    m_BC;           // BC register pair (LSB, i.e. C, first)
    WORD    m_HL;           // HL register pair
    WORD    m_PC;           // Program counter
    WORD    m_SP;           // Stack pointer
    BYTE    m_I;            // Interrupt register
    BYTE    m_R;            // Refresh register (Bit 7 is not significant!)
    BYTE    m_flags;        // Bit 0  : Bit 7 of the R-register
                            // Bit 1-3: Border colour
                            // Bit 4  : 1=Basic SamRom switched in
                            // Bit 5  : 1=Block of data is compressed
                            // Bit 6-7: No meaning
    WORD    m_DE;           // DE register pair
    WORD    m_BCdash;       // BC' register pair
    WORD    m_DEdash;       // DE' register pair
    WORD    m_HLdash;       // HL' register pair
    BYTE    m_Adash;        // A' register
    BYTE    m_Fdash;        // F' register
    WORD    m_IY;           // IY register (Again LSB first)
    WORD    m_IX;           // IX register
    BYTE    m_IFF1;         // Interrupt flipflop, 0=DI, otherwise EI
    BYTE    m_IFF2;         // IFF2 (not particularly important...)
    BYTE    m_flags2;       // Bit 0-1: Interrupt mode (0, 1 or 2)
                            // Bit 2  : 1=Issue 2 emulation
                            // Bit 3  : 1=Double interrupt frequency
                            // Bit 4-5: 1=High video synchronisation
                            //          3=Low video synchronisation
                            //          0,2=Normal
                            // Bit 6-7: 0=Cursor/Protek/AGF joystick
                            //          1=Kempston joystick
                            //          2=Sinclair 2 Left joystick (or user
                            //            defined, for version 3 .z80 files)
                            //          3=Sinclair 2 Right joystick
}; // Endstruct.


struct Z80
{
    Z80_V1  m_z80;                          
    WORD    m_addLength;                     // Length of additional header block (see below)
    WORD    m_PC;                            // Program counter
    BYTE    m_hwMode;                        // Hardware mode (see below)
    BYTE    m_state;                         // If in SamRam mode, bitwise state of 74ls259.
                                             // For example, bit 6=1 after an OUT 31,13 (=2*6+1)
                                             // If in 128 mode, contains last OUT to 0x7ffd
                                             // If in Timex mode, contains last OUT to 0xf4
    BYTE    m_byte1;                         // Contains 0xff if Interface I rom paged
                                             // If in Timex mode, contains last OUT to 0xff
    BYTE    m_byte2;                         // Bit 0: 1 if R register emulation on
                                             // Bit 1: 1 if LDIR emulation on
                                             // Bit 2: AY sound in use, even on 48K machines
                                             // Bit 6: (if bit 2 set) Fuller Audio Box emulation
                                             // Bit 7: Modify hardware (see below)
    BYTE    m_portFFFD;                      // Last OUT to port 0xfffd (soundchip register number)
    BYTE    m_soundChip [16];                // Contents of the sound chip registers
    WORD    m_loTStateCounter;               // Low T state counter
    BYTE    m_hiTStateCounter;               // Hi T state counter
    BYTE    m_speculatorFlag;                // Flag byte used by Spectator (QL spec. emulator)
                                             // Ignored by Z80 when loading, zero when saving
    BYTE    m_mgtFlag;                       // 0xff if MGT Rom paged
    BYTE    m_multifaceFlag;                 // 0xff if Multiface Rom paged. Should always be 0.
    BYTE    m_loROMFlag;                     // 0xff if 0-8191 is ROM, 0 if RAM
    BYTE    m_hiROMFlag;                     // 0xff if 8192-16383 is ROM, 0 if RAM
    BYTE    m_keyboardMapping [10];          // 5 x keyboard mappings for user defined joystick
    BYTE    m_keyboardMappingASCII [10];     // 5 x ASCII word: keys corresponding to mappings above
    BYTE    m_mgtType;                       // MGT type: 0=Disciple+Epson,1=Disciple+HP,16=Plus D
    BYTE    m_discipleInhibitButtonFlag;     // Disciple inhibit button status: 0=out, 0ff=in
    BYTE    m_discipleInhibitFlag;           // Disciple inhibit flag: 0=rom pageable, 0ff=not
    BYTE    m_port1FFD;                      // Last OUT to port 0x1ffd
}; // Endstruct.


struct DATA_BLOCK
{
    WORD    m_length;   // Length of compressed data (without this 3-byte header)
                        // If length=0xffff, data is 16384 bytes long and not compressed
    BYTE    m_page;     // Page number of block
}; // Endstruct.


static  const   UINT    VERSION_1 = 1;
static  const   UINT    VERSION_2 = 2;
static  const   UINT    VERSION_3 = 3;

static  UINT    GetZ80Version (const Z80 &z80)
{
    UINT    version = VERSION_1;

    if (z80.m_z80.m_PC == 0)
    {
        if (z80.m_addLength == 23)
        {
            version = VERSION_2;
        } // Endif.

        else
        {
            version = VERSION_3;
        } // Endelse.

    } // Endif.

    return (version);
} // Endproc.


static  void    PrintUsage (int argc, _TCHAR *argv [], bool bInvalidCommandLine = true)
{
    if (bInvalidCommandLine)
    {
        std::cout << "  Invalid Command Line :" << std::endl;
        std::cout << std::endl;
    
        ::_tprintf (Utils::GetCommandLine (argc, argv).c_str ());
        std::cout << std::endl << std::endl;
    } // Endif.
    
    std::cout << "  Usage :" << std::endl;
    std::cout << std::endl;

    std::cout << "DumpZ80 [/V]" << std::endl;
    std::cout << std::endl;
    std::cout << "  Where :" << std::endl;
    std::cout << std::endl;
    std::cout << "  /V - Verbose." << std::endl;
    std::cout << std::endl;

    std::cout << "  i.e. :" << std::endl;
    std::cout << std::endl;
    std::cout << "DumpZ80.exe" << std::endl;
    std::cout << std::endl;
} // Endproc.


static  bool    ProcessCommandLineOptions (int argc, _TCHAR *argv [])
{
    bool    bSuccess = true;

    s_bVerbose  = false;

    bool    bObtainedVerbose = false;

    // Look for the command line options.

    for (int nArgIndex = 1; 
         bSuccess && (nArgIndex < argc); 
         ++nArgIndex)
    {
        // Help.

        if (::_tcscmp (TEXT("/?"), argv [nArgIndex]) == 0)
        {
            PrintUsage (argc, argv);

            bSuccess = false;
        } // Endif.

        else
        if ((::_tcscmp (TEXT("/V"), argv [nArgIndex]) == 0) ||
            (::_tcscmp (TEXT("/v"), argv [nArgIndex]) == 0))
        {
            // Verbose.

            if (!bObtainedVerbose)
            {
                s_bVerbose = true;

                bObtainedVerbose = true;
            } // Endif.

            else
            {
                // Invalid verbose - user needs help.

                PrintUsage (argc, argv);

                bSuccess = false;
            } // Endelse.

        } // Endif.

        else
        {
            // Invalid command line - user needs help.

            PrintUsage (argc, argv);

            bSuccess = false;
        } // Endif.

    } // Endfor.

    return (bSuccess);
} // Endproc.


static  bool    Open (const std::wstring &dumpFileName)
{
    bool    bOkay = false;

    if (!dumpFileName.empty ())
    {
        // Open the dump file.

        g_dumpFile.SetFilePath (dumpFileName);

        if (g_dumpFile.Open (true,     // Read access required.
                             false))   // Write access NOT required.
        {
            // Get the file size of the dump file.
        
            UINT    uiFileSize = g_dumpFile.GetFileSize ();
        
            if (uiFileSize > 0)
            {
                // Resize the device recovery logdata.

                g_dumpFileData.resize (uiFileSize);

                // Read the device recovery log.
        
                DWORD   dwNumBytesRead = 0; // Initialise

                if (g_dumpFile.Read (0,   // Offset to read from.
                                      uiFileSize, 
                                      reinterpret_cast<BYTE &> (*(&(g_dumpFileData [0]))), 
                                      dwNumBytesRead))
                {
                    bOkay = true;
                } // Endif.

            } // Endif.

            if (!bOkay)
            {
                // Close the dump file.

                g_dumpFile.Close ();
            } // Endif.
        
        } // Endif.

    } // Endif.

    return (bOkay);
} // Endproc.


static  std::string DescribeHex (UINT uiValue, UINT uiSizeof = sizeof (UINT))
{
    std::ostringstream  str;

    str << std::setw (2 * uiSizeof) << std::setfill ('0') << std::hex << std::uppercase << uiValue;
    
    return (str.str ());
} // Endproc.


static  std::string  ByteBufferToAsciiLine (const std::vector<BYTE>             &buffer,
                                            UINT                                uiNumColumns,
                                            std::vector<BYTE>::const_iterator   &itr)
{
    static  const   char    ASCII_MIN_PRINTABLE = 0x20;
    static  const   char    ASCII_MAX_PRINTABLE = 0x7e;


    std::ostringstream   str;
    std::ostringstream  strAscii;

    str << std::uppercase;
                
    UINT    uiColumn = 0;   // Initialise!

    for (;
         (uiColumn < uiNumColumns) && (itr != buffer.end ());
         ++itr, ++uiColumn)
    {
        if (uiColumn == 0)
        {
            str << std::setfill('0') << std::setw(4) << std::hex
                << std::distance<std::vector<BYTE>::const_iterator> (buffer.begin (), itr)
                << "  ";
        } // Endif.

        else
        {
            str << ' ';
        } // Endelse.

        int n = *itr;

        str << std::setfill('0') << std::setw(2) << std::hex << n;

        if ((*itr >= ASCII_MIN_PRINTABLE) &&
            (*itr <= ASCII_MAX_PRINTABLE))
        {
            strAscii << *itr;
        } // Endif.

        else
        {
            strAscii << '.';
        } // Endelse.

    } // Endfor.

    // Pad if required.

    while (uiColumn != uiNumColumns)
    {
        str << "   ";

        uiColumn++;
    } // Endwhile.

    str << "  " << strAscii.str ();

    return (str.str ());
} // Endproc.


static  std::string ByteBufferToAsciiString (const std::vector<BYTE>    &buffer,
                                             UINT                       uiNumColumns)
{
    std::ostringstream   str;

    std::vector<BYTE>::const_iterator   itr = buffer.begin ();

    while (itr != buffer.end ())
    {
        str << ByteBufferToAsciiLine (buffer, uiNumColumns, itr) << std::endl;
    } // Endwhile.

    return (str.str ());
} // Endproc.


static  std::string DescribeFlags (BYTE flags)
{
    std::ostringstream  str;

    str << DescribeHex (flags, sizeof (flags))
        << " ("
        << "R (bit7):" << (flags & 0x01)
        << ", Border:" << ((flags >> 1) & 0x07);

    if (flags & 0x10)
    {
        str << ", Basic SamRom switched in";
    } // Endif.

    if (flags & 0x20)
    {
        str << ", Block data compressed";
    } // Endif.

    str << ")";

    return (str.str ());
} // Endproc.


static  std::string DescribeFlags2 (BYTE flags)
{
    std::ostringstream  str;

    str << DescribeHex (flags, sizeof (flags))
        << " ("
        << "Interrupt mode:" << (flags & 0x03);

    if (flags & 0x04)
    {
        str << ", Issue 2 emulation";
    } // Endif.

    if (flags & 0x08)
    {
        str << ", Double interrupt frequency";
    } // Endif.

    switch ((flags >> 4) & 0x03)
    {
    case 1:
        str << ", High video sync";
        break;
    case 3:
        str << ", Low video sync";
        break;
    default:
        str << ", Normal video sync";
        break;
    } // Endif.

    switch ((flags >> 6) & 0x03)
    {
    case 0:
        str << ", Cursor/Protek/AGF joystick";
        break;
    case 1:
        str << ", Kempston joystick";
        break;
    case 2:
        str << ", Sinclair 2 Left joystick";
        break;
    case 3:
        str << ", Sinclair 3 Left joystick";
        break;
    } // Endif.

    str << ")";

    return (str.str ());
} // Endproc.


static  void    DumpZ80_V1 (const Z80 &z80, WORD PC)
{
    std::cout << "Z80" << std::endl;
    std::cout << "---" << std::endl;
    std::cout << "PC:" << DescribeHex (PC, sizeof (PC)) << "    ";
    std::cout << "SP:" << DescribeHex (z80.m_z80.m_SP, sizeof (z80.m_z80.m_SP)) << std::endl;
    std::cout << "A:" << DescribeHex (z80.m_z80.m_A, sizeof (z80.m_z80.m_A)) << "       ";
    std::cout << "A':" << DescribeHex (z80.m_z80.m_Adash, sizeof (z80.m_z80.m_Adash)) << std::endl;
    std::cout << "F:" << DescribeHex (z80.m_z80.m_F, sizeof (z80.m_z80.m_F)) << "       ";;
    std::cout << "F':" << DescribeHex (z80.m_z80.m_Fdash, sizeof (z80.m_z80.m_Fdash)) << std::endl;
    std::cout << "BC:" << DescribeHex (z80.m_z80.m_BC, sizeof (z80.m_z80.m_BC)) << "    ";
    std::cout << "BC':" << DescribeHex (z80.m_z80.m_BCdash, sizeof (z80.m_z80.m_BCdash)) << std::endl;
    std::cout << "DE:" << DescribeHex (z80.m_z80.m_DE, sizeof (z80.m_z80.m_DE)) << "    ";
    std::cout << "DE':" << DescribeHex (z80.m_z80.m_DEdash, sizeof (z80.m_z80.m_DEdash)) << std::endl;
    std::cout << "HL:" << DescribeHex (z80.m_z80.m_HL, sizeof (z80.m_z80.m_HL)) << "    ";
    std::cout << "HL':" << DescribeHex (z80.m_z80.m_HLdash, sizeof (z80.m_z80.m_HLdash)) << std::endl;
    std::cout << "IX:" << DescribeHex (z80.m_z80.m_IX, sizeof (z80.m_z80.m_IX)) << "    ";
    std::cout << "IY:" << DescribeHex (z80.m_z80.m_IY, sizeof (z80.m_z80.m_IY)) << std::endl;
    std::cout << "I:" << DescribeHex (z80.m_z80.m_I, sizeof (z80.m_z80.m_I)) << "       ";
    std::cout << "R:" << DescribeHex (z80.m_z80.m_R, sizeof (z80.m_z80.m_R)) << std::endl;
    std::cout << "IFF1:" << DescribeHex (z80.m_z80.m_IFF1, sizeof (z80.m_z80.m_IFF1)) << "    ";
    std::cout << "IFF2:" << DescribeHex (z80.m_z80.m_IFF2, sizeof (z80.m_z80.m_IFF2)) << std::endl;
    std::cout << std::endl;

    std::cout << "flags:" << DescribeFlags (z80.m_z80.m_flags) << std::endl;
    std::cout << "flags2:" << DescribeFlags2 (z80.m_z80.m_flags2) << std::endl;
    std::cout << std::endl;
} // Endproc.


static  void    DumpZ80 (const Z80 &z80)
{
    std::cout << "Version:" << GetZ80Version (z80) << ".x" << std::endl;
    std::cout << std::endl;

    bool    bV2 = (z80.m_z80.m_PC == 0);

    WORD    PC = bV2 ? z80.m_PC : z80.m_z80.m_PC;
                  
    DumpZ80_V1 (z80, PC);

    if (bV2)
    {
        std::cout << "Length:" << z80.m_addLength << std::endl;
        std::cout << std::endl;
    } // Endif.

} // Endproc.


static  void    DumpDataBlock (const DATA_BLOCK &dataBlock)
{
    std::cout << "DATA BLOCK" << std::endl;
    std::cout << "----------" << std::endl;

    std::cout << "Length:" << dataBlock.m_length << std::endl;
    std::cout << "Page:" << static_cast<UINT> (dataBlock.m_page) << std::endl;
    std::cout << std::endl;
} // Endproc.


static  bool    ProcessZ80 ()
{
    // Open the Z80 file.

    bool    bOkay = Open (L"jetpac.z80");

    if (bOkay)
    {
        // Get the Z80 header.

        Z80*    lpZ80 = reinterpret_cast<Z80*> (&(g_dumpFileData [0]));

        // Dump the Z80 header.

        DumpZ80 (*lpZ80);

        // Get the 1st data block.

        DATA_BLOCK* lpDataBlock = reinterpret_cast<DATA_BLOCK*> (&(g_dumpFileData [sizeof (Z80_V1) + sizeof (WORD) + lpZ80->m_addLength]));

        while (reinterpret_cast<LPBYTE> (lpDataBlock) < &(g_dumpFileData [g_dumpFileData.size () - 1]))
        {
            // Dump the data block.

            DumpDataBlock (*lpDataBlock);

            // Get the next data block.

            lpDataBlock = reinterpret_cast<DATA_BLOCK*> (reinterpret_cast<LPBYTE> (lpDataBlock) + sizeof (DATA_BLOCK) + lpDataBlock->m_length);
        } // Endwhile.

    } // Endif.

    return (bOkay);
} // Endproc.


int _cdecl _tmain (int argc, _TCHAR *argv [])
{
    int nSuccess = 1;
    
    std::cout << std::endl;
    std::cout << "DumpZ80 01.00" << std::endl;
    std::cout << "=============" << std::endl;
    std::cout << std::endl;

    if (ProcessCommandLineOptions (argc, argv))
    {
        if (ProcessZ80 ())
        {
            nSuccess = 0;
        } // Endif.

    } // Endif.

    return (nSuccess);
} // Endproc.

/******************************* End of File *******************************/
