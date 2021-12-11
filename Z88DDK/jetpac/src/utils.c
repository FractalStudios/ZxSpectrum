#include "includes.h"
#include "utils.h"

void    ClearDisplay (UINT8 row, 
                      UINT8 column, 
                      UINT8 width, 
                      UINT8 height,
                      UINT8 colour)
{
    struct r_Rect8  rect = {column, width, row, height};

    zx_cls_wc_attr (&(rect), colour);
} // Endproc.


void    PrintAt (UINT8  row, 
                 UINT8  column, 
                 char*  text,
                 UINT8  colour)
{
    if (text && *text)
    {
        // Get the screen address.

        UINT8*  startAddr = zx_cxy2saddr (column, row);

        if (startAddr)
        {
            // Get the attribute address.

            UINT8*  aAddr = zx_saddr2aaddr (startAddr);

            if (aAddr)
            {
                // Display the string.

                while (*text)
                {
                    // Set the colour.

                    *aAddr++ = colour;

                    // Get the character glyph data.

                    UINT8*  glyphData = (UINT8*) (ADDRESS_ROM_CHARACTER_SET + *text * MAX_UDG_SIZE);

                    UINT8*  sAddr = startAddr++;

                    for (UINT8 n = 0; n < MAX_UDG_SIZE; ++n)
                    {
                        // Set the character glpyh data.

                        *sAddr = *glyphData++;
                        sAddr += MAX_NUM_PIXELS_X; // Next line.
                    } // Endfor.

                    text++;  // Next character in string.
                } // Endwhile.
    
            } // Endif.

        } // Endif.

    } // Endif.

} // Endproc.


void    PrintUDGAt (UINT8   row, 
                    UINT8   column, 
                    UDG     udgData,
                    UINT8   numUDGs,
                    UINT8   colour)
{
    if (numUDGs)
    {
        // Get the screen address.

        UINT8*  startAddr = zx_cxy2saddr (column, row);

        if (startAddr)
        {
            // Get the attribute address.

            UINT8*  aAddr = zx_saddr2aaddr (startAddr);

            if (aAddr)
            {
                // Display the UDG.

                for (UINT8 udg = 0; udg < numUDGs; ++udg)
                {
                    // Set the colour.

                    *aAddr++ = colour;

                    // Get the UDG glyph data.

                    UINT8*  glyphData = udgData;

                    UINT8*  sAddr = startAddr++;

                    for (UINT8 n = 0; n < MAX_UDG_SIZE; ++n)
                    {
                        // Set the UDG glpyh data.

                        *sAddr = *glyphData++;
                        sAddr += MAX_NUM_PIXELS_X; // Next line.
                    } // Endfor.

                } // Endwhile.
    
            } // Endif.

        } // Endif.

    } // Endif.

} // Endproc.


void    InitialiseDisplay ()
{
    // Set black border.

    zx_border (INK_BLACK);

    // Clear screen attributes to black ink and paper.
    
    zx_cls_attr (BRIGHT | INK_BLACK | PAPER_BLACK);
} // Endproc.

/******************************* End of File *******************************/
