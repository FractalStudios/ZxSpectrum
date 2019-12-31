// "Home-made" includes.
#include    "SpriteGraphicsAttributes.h"

namespace Folio        
{

namespace Core
{

namespace Game
{

FolioStatus ReleaseSpriteGraphicsAttributes (const Folio::Core::Game::ASprite::SpriteGraphicAttributesList  &spriteGraphicAttributesList,
                                             Folio::Core::Game::ResourceGraphicsCache                       &resourceGraphicsCache)
{
    FolioStatus status = ERR_SUCCESS;

    for (Folio::Core::Game::ASprite::SpriteGraphicAttributesList::const_iterator itrSpriteGraphicAttributesList = spriteGraphicAttributesList.begin ();
         (status == ERR_SUCCESS) && (itrSpriteGraphicAttributesList != spriteGraphicAttributesList.end ());
         ++itrSpriteGraphicAttributesList)
    {
        for (Folio::Core::Game::ASprite::SpriteGraphicsList::const_iterator itrSpriteGraphicsList = itrSpriteGraphicAttributesList->m_spriteGraphics.begin ();
             (status == ERR_SUCCESS) && (itrSpriteGraphicsList != itrSpriteGraphicAttributesList->m_spriteGraphics.end ());
             ++itrSpriteGraphicsList)
        {
            status = resourceGraphicsCache.ReleaseResourceGraphic (*itrSpriteGraphicsList);
        } // Endfor.

    } // Endfor.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
