// "Home-made" includes.
#include    "StdAfx.h"
#include    "WeaponSprites.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Weapon sprite graphic attributes.
typedef Folio::Core::Game::SpriteGraphicsAttributes<WEAPON_SPRITE_ID, SPRITE_ID> WeaponSpriteGraphicAttributes;

// Weapon sprite graphic attributes table.
static  const   WeaponSpriteGraphicAttributes   g_weaponSpriteGraphicAttributesTable [] =
{
//      m_spriteId                      m_direction                                         m_spriteGraphicIdsList
    {   WEAPON_SPRITE_KNIGHT_AXE,       Folio::Core::Game::AWeaponSprite::ALL_DIRECTIONS,   {   SPRITE_KNIGHT_AXE_1, SPRITE_KNIGHT_AXE_2, SPRITE_KNIGHT_AXE_3, SPRITE_KNIGHT_AXE_4, SPRITE_KNIGHT_AXE_5, SPRITE_KNIGHT_AXE_6, SPRITE_KNIGHT_AXE_7, SPRITE_KNIGHT_AXE_8, },  },    

    {   WEAPON_SPRITE_WIZARD_POTION,    Folio::Core::Game::AWeaponSprite::ALL_DIRECTIONS,   {   SPRITE_WIZARD_POTION_1, SPRITE_WIZARD_POTION_2, SPRITE_WIZARD_POTION_3,                                                                                                 },  },    

    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::N,                {   SPRITE_SERF_SWORD_5,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::S,                {   SPRITE_SERF_SWORD_1,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::E,                {   SPRITE_SERF_SWORD_3,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::W,                {   SPRITE_SERF_SWORD_7,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::NE,               {   SPRITE_SERF_SWORD_6,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::NW,               {   SPRITE_SERF_SWORD_4,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::SE,               {   SPRITE_SERF_SWORD_2,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::AWeaponSprite::SW,               {   SPRITE_SERF_SWORD_8,                                                                                                                                                    },  },
};


WeaponSprite::WeaponSprite ()
:   m_weaponSpriteId(WEAPON_SPRITE_UNDEFINED)
{
} // Endproc.


WeaponSprite::~WeaponSprite ()
{
} // Endproc.


FolioStatus WeaponSprite::Create (FolioHandle               dcHandle,
                                  WEAPON_SPRITE_ID          weaponSpriteId,
                                  const SpriteGraphicsMap   &spriteGraphicsMap,
                                  const Gdiplus::Rect       &mainPlayerRect,      
                                  Direction                 initialDirection)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 25;

    // Get the weapon sprite's colour.

    ZxSpectrum::COLOUR  weaponSpriteColour = GetColour (weaponSpriteId);

    // Query the weapon sprite's graphics.

    SpriteGraphicAttributesList spriteGraphicAttributesList;

    FolioStatus status = QuerySpriteGraphics<WEAPON_SPRITE_ID, WeaponSpriteGraphicAttributes> (dcHandle,
                                                                                               weaponSpriteId,
                                                                                               spriteGraphicsMap,
                                                                                               weaponSpriteColour,
                                                                                               sizeof (g_weaponSpriteGraphicAttributesTable) / sizeof (WeaponSpriteGraphicAttributes),
                                                                                               g_weaponSpriteGraphicAttributesTable,
                                                                                               spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Get the weapon sprite's graphic.

        const SpriteGraphic &spriteGraphic(spriteGraphicAttributesList.front ().m_spriteGraphics.front ());

        // Create the weapon sprite.

        status = Folio::Core::Game::AWeaponSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           GetInitialScreenXLeft (mainPlayerRect, spriteGraphic->GetGraphicWidth ()),
                                                           GetInitialScreenYTop (mainPlayerRect, spriteGraphic->GetGraphicHeight ()),
                                                           ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           weaponSpriteColour,
                                                           initialDirection,
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERROR_SUCCESS)
        {
            // Note the weapon sprite's attributes.

            m_weaponSpriteId = weaponSpriteId;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus WeaponSprite::Move (Gdiplus::Graphics                   &graphics,
                                Folio::Core::Game::CollisionGrid    &collisionGrid)
{
    // Move the weapon sprite.

    return (Folio::Core::Game::AWeaponSprite::Move (graphics, WEAPON_SPRITE_SPEED, collisionGrid));
} // Endproc.


WEAPON_SPRITE_ID   WeaponSprite::GetWeaponSpriteId () const
{
    return (m_weaponSpriteId);
} // Endproc.


Int32   WeaponSprite::GetInitialScreenXLeft (const Gdiplus::Rect    &mainPlayerRect,
                                             Int32                  weaponSpriteWidth)
{
    return (mainPlayerRect.X + (mainPlayerRect.Width - weaponSpriteWidth) / 2);
} // Endproc.


Int32   WeaponSprite::GetInitialScreenYTop (const Gdiplus::Rect &mainPlayerRect,
                                            Int32               weaponSpriteHeight)
{
    return (mainPlayerRect.Y + (mainPlayerRect.Height - weaponSpriteHeight) / 2);
} // Endproc.


ZxSpectrum::COLOUR  WeaponSprite::GetColour (WEAPON_SPRITE_ID weaponSpriteId)
{
    switch (weaponSpriteId)
    {
    case WEAPON_SPRITE_WIZARD_POTION:             
        return (ZxSpectrum::BRIGHT | ZxSpectrum::CYAN);
    
    case WEAPON_SPRITE_SERF_SWORD:              
        return (ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW);
    
    case WEAPON_SPRITE_KNIGHT_AXE:            
    default:
        return (ZxSpectrum::BRIGHT | ZxSpectrum::RED);
    } // Endswitch.

} // Endproc.


WEAPON_SPRITE_ID    GetMainPlayerWeaponSpriteId (const PlayerSpritePtr &mainPlayer)
{
    // Weapon is dependent on the main player

    switch (mainPlayer->GetPlayerSpriteId ())
    {
    case PLAYER_SPRITE_WIZARD:
        return (WEAPON_SPRITE_WIZARD_POTION);

    case PLAYER_SPRITE_SERF:
        return (WEAPON_SPRITE_SERF_SWORD);

    case PLAYER_SPRITE_KNIGHT:
    default:
        return (WEAPON_SPRITE_KNIGHT_AXE);
    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
