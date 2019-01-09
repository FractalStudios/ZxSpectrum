// "Home-made" includes.
#include    <Trace.h>
#include    "..\Include\Gdi.h"
#include    "GdiRasterFont.h"
#include    "GraphicMacros.h"

namespace Folio
{

namespace Core
{

namespace Graphic
{

using   namespace   Gdiplus;

/**
 * The defauilt class constructor.
 */
GdiRasterFont::GdiRasterFont ()
{
} // Endproc.


/**
 * A class constructor.
 *
 * @param [in] characterMap
 * The character map.
 *
 * @param [in] characterWidth
 * The width (in bytes) of a raster font character.
 *
 * @param [in] characterHeightInPixels
 * The height in pixels of a raster font character.
 */
GdiRasterFont::GdiRasterFont (UInt32                characterWidth,
                              Int32                 characterHeightInPixels,
                              const CharacterMap&   characterMap)
:   m_characterWidth(characterWidth),
    m_characterHeightInPixels(characterHeightInPixels),
    m_characterMap(characterMap)
{
} // Endproc.


/**
 * The class destructor.
 */
GdiRasterFont::~GdiRasterFont ()
{
} // Endproc.


/**
 * Method that is used to create the raster font.
 *
 * @param [in] characterMap
 * The character map.
 *
 * @param [in] characterWidth
 * The width (in bytes) of a raster font character.
 *
 * @param [in] m_characterHeightInPixels
 * The height in pixels of a raster font character.
 *
 * @return
 * The possible return values are:<ul>
 * <li><b>ERR_SUCCESS</b> if successful.
 * <li><b>ERR_INVALID_SEQUENCE</b> if a raster font has been previously created 
 *     using this object.
 * <li><b>ERR_???</b> status code otherwise.
 * </ul>
 */
FolioStatus GdiRasterFont::Create (UInt32               characterWidth,
                                   Int32                characterHeightInPixels,
                                   const CharacterMap&  characterMap)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a raster font already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create the raster font.

        m_characterWidth            = characterWidth;
        m_characterHeightInPixels   = characterHeightInPixels;

        m_characterMap = characterMap;
    } // Endelse.

    return (status);
} // Endproc.


/**
 * Method that is used to get a character width (in bytes).
 *
 * @return
 * The character width (in bytes).
 */
UInt32  GdiRasterFont::GetCharacterWidth () const
{
    return (m_characterWidth);
} // Endproc.


/**
 * Method that is used to get a character width in pixels.
 *
 * @return
 * The character width in pixels.
 */
Int32   GdiRasterFont::GetCharacterWidthInPixels () const
{
    return (m_characterWidth * 8);
} // Endproc.


/**
 * Method that is used to get a character height in pixels.
 *
 * @return
 * The character height in pixels.
 */
Int32   GdiRasterFont::GetCharacterHeightInPixels () const
{
    return (m_characterHeightInPixels);
} // Endproc.

               
/**
 * Method that is used to get a bit buffer of the characters representing the
 * specified text string.
 *
 * @param [in] textString
 * The text string.
 *
 * @return
 * The bit buffer of the characters representing the specified text string.
 */
FolioByteBuffer GdiRasterFont::GetTextStringBitBuffer (const FolioNarrowString& textString) const
{
    FolioByteBuffer textStringBitBuffer;

    for (FolioNarrowString::const_iterator itr = textString.begin ();
         itr != textString.end ();
         ++itr)
    {
        // Get the bit buffer for the character.

        FolioByteBuffer characterBitBuffer(GetCharacterBitBuffer (*itr));

        // Add to the text string bit buffer.

        textStringBitBuffer.insert (textStringBitBuffer.end (), 
                                    characterBitBuffer.begin (), 
                                    characterBitBuffer.end ());
    } // Endfor.            

    return (textStringBitBuffer);
} // Endproc.

               
/**
 * Method that is used to get a bit buffer of the character representing the
 * specified character.
 *
 * @param [in] character
 * The character.
 *
 * @return
 * The bit buffer of the character, if found. 
 */
FolioByteBuffer GdiRasterFont::GetCharacterBitBuffer (const FolioNarrowString::value_type& character) const
{
    CharacterMap::const_iterator    itr = m_characterMap.find (character);

    if (itr != m_characterMap.end ())
    {
        return (itr->second);
    } // Endif.

    return (FolioByteBuffer());
} // Endproc.


/**
 * Method that is used to determine if the raster font has been created.
 *
 * @return
 * <b>true</b> if the raster font has been created, <b>false</b> otherwise.
 */
bool    GdiRasterFont::IsCreated () const
{
    // If the raster font handle is valid, then the raster font has been created.

    return (!m_characterMap.empty ());
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
