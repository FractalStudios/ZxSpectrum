#pragma once

// STL includes.
#include    <memory>

// "Home-made" includes.
#include    "GraphicConstsAndTypes.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Graphic
{

/// The GDI raster font class.
/**
 * This class provides for GDI raster font.
 *
 * This class does not support copy construction or assignment.
 */
class GdiRasterFont
{
public:    
    // The character map.
    typedef std::map<FolioNarrowString::value_type, FolioByteBuffer> CharacterMap;

    GdiRasterFont ();
    GdiRasterFont (UInt32               characterWidth,
                   Int32                characterHeightInPixels,
                   const CharacterMap&  characterMap);
    ~GdiRasterFont ();

    FolioStatus Create (UInt32              characterWidth,
                        Int32               characterHeightInPixels,
                        const CharacterMap& characterMap);

    UInt32  GetCharacterWidth () const;
    Int32   GetCharacterWidthInPixels () const;
    Int32   GetCharacterHeightInPixels () const;

    FolioByteBuffer GetTextStringBitBuffer (const FolioNarrowString& textString) const;

private:
    UInt32  m_characterWidth;           ///< The width (in bytes) of a raster font character.
    Int32   m_characterHeightInPixels;  ///< The height in pixels of a raster font character.

    CharacterMap    m_characterMap; ///< The font character map.

    FolioByteBuffer GetCharacterBitBuffer (const FolioNarrowString::value_type& character) const;

    bool    IsCreated () const;

    /// Private copy constructor to prevent copying.
    GdiRasterFont (const GdiRasterFont& rhs);

    /// Private assignment operator to prevent copying.
    GdiRasterFont& operator= (const GdiRasterFont& rhs);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
