// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Globals.h"
#include    "PlayerSprite.h"
#include    "ResourceOwnerId.h"
#include    "SpriteGraphics.h"
#include    "Ultimate.h"
#include    "WeaponSprite.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Weapon sprite attributes.
struct WeaponSpriteAttributes
{
    WEAPON_SPRITE_ID                        m_weaponSpriteId;       // The identifier of the weapon sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_weaponSpriteColour;   // The colour of the weapon sprite.
}; // Endstruct.

// Weapon sprite attributes table.
static  const   WeaponSpriteAttributes  g_weaponSpriteAttributesTable [] =
{
//      m_weaponSpriteId                m_weaponSpriteColour
    {   WEAPON_SPRITE_KNIGHT_AXE,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     },
    {   WEAPON_SPRITE_WIZARD_POTION,    Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
};


// Weapon sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<WEAPON_SPRITE_ID, SPRITE_ID>    g_weaponSpriteGraphicCharacteristics =
{
//      m_spriteId                      m_direction                         m_spriteGraphicIdsList
    {   WEAPON_SPRITE_KNIGHT_AXE,       Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_KNIGHT_AXE_1, SPRITE_KNIGHT_AXE_2, SPRITE_KNIGHT_AXE_3, SPRITE_KNIGHT_AXE_4, SPRITE_KNIGHT_AXE_5, SPRITE_KNIGHT_AXE_6, SPRITE_KNIGHT_AXE_7, SPRITE_KNIGHT_AXE_8, },  },    

    {   WEAPON_SPRITE_WIZARD_POTION,    Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_WIZARD_POTION_1, SPRITE_WIZARD_POTION_2, SPRITE_WIZARD_POTION_3,                                                                                                 },  },    

    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::N,               {   SPRITE_SERF_SWORD_5,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::S,               {   SPRITE_SERF_SWORD_1,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::E,               {   SPRITE_SERF_SWORD_3,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::W,               {   SPRITE_SERF_SWORD_7,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::NE,              {   SPRITE_SERF_SWORD_6,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::NW,              {   SPRITE_SERF_SWORD_4,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::SE,              {   SPRITE_SERF_SWORD_2,                                                                                                                                                    },  },
    {   WEAPON_SPRITE_SERF_SWORD,       Folio::Core::Game::SW,              {   SPRITE_SERF_SWORD_8,                                                                                                                                                    },  },
};


// Weapon sprite static members.
Folio::Core::Util::Sound::SoundSample   WeaponSprite::m_knightWeaponSpriteInitialisedSoundSample;   // The knight weapon sprite initialised sound sample.
Folio::Core::Util::Sound::SoundSample   WeaponSprite::m_wizardWeaponSpriteInitialisedSoundSample;   // The wizard weapon sprite initialised sound sample.
Folio::Core::Util::Sound::SoundSample   WeaponSprite::m_serfWeaponSpriteInitialisedSoundSample;     // The serf weapon sprite initialised sound sample.
Folio::Core::Util::Sound::SoundSample   WeaponSprite::m_weaponSpriteTerminatedSoundSample;          // The weapon sprite terminated sound sample.
Folio::Core::Util::Sound::SoundSample   WeaponSprite::m_weaponSpriteReboundSoundSample;             // The weapon sprite rebound sound sample.

WeaponSprite::WeaponSprite ()
:   m_weaponSpriteId(WEAPON_SPRITE_UNDEFINED)
{
} // Endproc.


WeaponSprite::~WeaponSprite ()
{
} // Endproc.


FolioStatus WeaponSprite::Create (FolioHandle                           dcHandle,
                                  WEAPON_SPRITE_ID                      weaponSpriteId,
                                  Folio::Core::Game::ZxSpectrum::COLOUR weaponSpriteColour)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 25;
    
    // Query the weapon sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<WEAPON_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       OWNER_ID_WEAPON_SPRITE,
                                                                                                       DRAWING_ELEMENT_WEAPON_SPRITE,
                                                                                                       weaponSpriteId,
                                                                                                       weaponSpriteColour,
                                                                                                       g_weaponSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Create the weapon sprite.

        status = Folio::Core::Game::AWeaponSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           Folio::Core::Game::ZxSpectrum::UNDEFINED,
                                                           Folio::Core::Game::ZxSpectrum::UNDEFINED,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (weaponSpriteColour),
                                                           Folio::Core::Game::E,
                                                           &(g_resourceGraphicsCache),
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERR_SUCCESS)
        {
            // Set the weapon sprite's sound samples.

            SetWeaponSpriteSoundSamples (weaponSpriteId);

            // Note the weapon sprite's attributes.

            m_weaponSpriteId = weaponSpriteId;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus WeaponSprite::Start ()
{
    // Get the main player rect.

    Gdiplus::Rect   mainPlayerRect(g_mainPlayer->GetScreenRect ());

    // Recreate the weapon sprite.

    FolioStatus status = Recreate (GetInitialScreenXLeft (mainPlayerRect), 
                                   GetInitialScreenYTop (mainPlayerRect),
                                   g_mainPlayer->GetDirection ());  // Direction is the same as the main player.

    if (status == ERR_SUCCESS)
    {
        // The weapon sprite is initialised.

        SetState (STATE_INITIALISED);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus WeaponSprite::Stop (bool bPlayTerminatedSound)
{
    // The weapon sprite is terminated.

    SetState (STATE_TERMINATED, bPlayTerminatedSound);

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus WeaponSprite::Move (Gdiplus::Graphics   &graphics,
                                CollisionGrid       &collisionGrid)
{
    // Move the weapon sprite.

    return (Folio::Core::Game::AWeaponSprite::Move (graphics, 
                                                    WEAPON_SPRITE_SPEED, 
                                                    collisionGrid));
} // Endproc.


void    WeaponSprite::PlayWeaponSpriteInitialisedSound () const
{
    PlaySpriteInitialisedSound ();
} // Endproc.


void    WeaponSprite::PlayWeaponSpriteTerminatedSound () const
{
    PlaySpriteTerminatedSound ();
} // Endproc.


WEAPON_SPRITE_ID   WeaponSprite::GetWeaponSpriteId () const
{
    return (m_weaponSpriteId);
} // Endproc.


WEAPON_SPRITE_ID    WeaponSprite::GetMainPlayerWeaponSpriteId ()
{
    // The weapon is dependent on the main player.

    switch (g_mainPlayer->GetPlayerSpriteId ())
    {
    case PLAYER_SPRITE_WIZARD:
        return (WEAPON_SPRITE_WIZARD_POTION);

    case PLAYER_SPRITE_SERF:
        return (WEAPON_SPRITE_SERF_SWORD);

    case PLAYER_SPRITE_KNIGHT:
        return (WEAPON_SPRITE_KNIGHT_AXE);

    default:
        return (WEAPON_SPRITE_UNDEFINED);
    } // Endswitch.

} // Endproc.


Int32   WeaponSprite::GetInitialScreenXLeft (const Gdiplus::Rect &mainPlayerRect) const
{
    return (mainPlayerRect.X + (mainPlayerRect.Width - GetCurrentSpriteGraphicWidth ()) / 2);
} // Endproc.


Int32   WeaponSprite::GetInitialScreenYTop (const Gdiplus::Rect &mainPlayerRect) const
{
    return (mainPlayerRect.Y + (mainPlayerRect.Height - GetCurrentSpriteGraphicHeight ()) / 2);
} // Endproc.


void    WeaponSprite::SetWeaponSpriteSoundSamples (WEAPON_SPRITE_ID weaponSpriteId)
{
    // Create the weapon sprite's sound samples.

    CreateWeaponSpriteSoundSamples (weaponSpriteId);

    // Set the weapon sprite's initialised sound sample.

    SetWeaponSpriteInitialisedSoundSample (weaponSpriteId);

    // Set the weapon sprite's terminated sound sample.

    SetWeaponSpriteTerminatedSoundSample (weaponSpriteId);

    // Set the weapon sprite's rebound sound sample.

    SetWeaponSpriteReboundSoundSample (weaponSpriteId);
} // Endproc.


void    WeaponSprite::SetWeaponSpriteInitialisedSoundSample (WEAPON_SPRITE_ID weaponSpriteId)
{
    switch (weaponSpriteId)
    {
    case WEAPON_SPRITE_WIZARD_POTION:
        SetSpriteInitialisedSoundSample (Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(m_wizardWeaponSpriteInitialisedSoundSample)));
        break;

    case WEAPON_SPRITE_SERF_SWORD:
        SetSpriteInitialisedSoundSample (Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(m_serfWeaponSpriteInitialisedSoundSample)));
        break;

    case WEAPON_SPRITE_KNIGHT_AXE:
        SetSpriteInitialisedSoundSample (Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(m_knightWeaponSpriteInitialisedSoundSample)));
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


void    WeaponSprite::SetWeaponSpriteTerminatedSoundSample (WEAPON_SPRITE_ID weaponSpriteId)
{
    SetSpriteTerminatedSoundSample (Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(m_weaponSpriteTerminatedSoundSample)));
} // Endproc.


void    WeaponSprite::SetWeaponSpriteReboundSoundSample (WEAPON_SPRITE_ID weaponSpriteId)
{
    SetSpriteReboundSoundSample (Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(m_weaponSpriteReboundSoundSample)));
} // Endproc.


void    WeaponSprite::CreateWeaponSpriteSoundSamples (WEAPON_SPRITE_ID weaponSpriteId)
{
    switch (weaponSpriteId)
    {
    case WEAPON_SPRITE_WIZARD_POTION:
        // Create the wizard weapon sprite initialised sound sample.

        CreateWizardWeaponSpriteInitialisedSoundSample ();
        break;

    case WEAPON_SPRITE_SERF_SWORD:
        // Create the serf weapon sprite initialised sound sample.

        CreateSerfWeaponSpriteInitialisedSoundSample ();
        break;

    case WEAPON_SPRITE_KNIGHT_AXE:
        // Create the knight weapon sprite initialised sound sample.

        CreateKnightWeaponSpriteInitialisedSoundSample ();
        break;

    default:
        break;
    } // Endswitch.

    // Create the weapon sprite terminated sound sample.

    CreateWeaponSpriteTerminatedSoundSample ();

    // Create the weapon sprite rebound sound sample.

    CreateWeaponSpriteReboundSoundSample ();
} // Endproc.


void    WeaponSprite::CreateKnightWeaponSpriteInitialisedSoundSample ()
{
    // Has the knight weapon sprite initialised sound sample been created?

    if (!m_knightWeaponSpriteInitialisedSoundSample.IsSoundSampleGenerated ())
    {
        // No. Create the sound sample representing the required sound.
    
        Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x06;

        for (UInt32 count = 0; count < 12; ++count)
        {
            m_knightWeaponSpriteInitialisedSoundSample.AddSoundSample (Ultimate::CreateSoundSample (frequency, 0x01));

            if (frequency & 0x80)
            {
                frequency &= ~0x80;
            } // Endif.

            else
            {
                frequency--;
                frequency |= 0x80;
            } // Endelse.

        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::CreateWizardWeaponSpriteInitialisedSoundSample ()
{
    // Has the wizard weapon sprite initialised sound sample been created?

    if (!m_wizardWeaponSpriteInitialisedSoundSample.IsSoundSampleGenerated ())
    {
        // No. Create the sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0xef; frequency <= 0xfd; frequency += 0x02)
        {
            m_wizardWeaponSpriteInitialisedSoundSample.AddSoundSample (Ultimate::CreateSoundSample (frequency, 0x01));
        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::CreateSerfWeaponSpriteInitialisedSoundSample ()
{
    // Has the serf weapon sprite initialised sound sample been created?
    
    if (!m_serfWeaponSpriteInitialisedSoundSample.IsSoundSampleGenerated ())
    {
        // No. Create the sound sample representing the required sound.
    
        Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x1d;

        for (UInt32 count = 0; count < 16; ++count)
        {
            m_serfWeaponSpriteInitialisedSoundSample.AddSoundSample (Ultimate::CreateSoundSample (frequency, 0x01));

            if (frequency == 0x1d)
            {
                frequency = 0xec;
            } // Endif.

            else
            if ((count % 2) == 0)
            {
                frequency -= 0x30;
            } // Endelseif.

            else
            {
                frequency += 0x10;
            } // Endelse.

        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::CreateWeaponSpriteTerminatedSoundSample ()
{
    // Has the weapon sprite terminated sound sample been created?

    if (!m_weaponSpriteTerminatedSoundSample.IsSoundSampleGenerated ())
    {
        // No. Create the sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x3f; frequency >= 0x21; frequency -= 2)
        {
            m_weaponSpriteTerminatedSoundSample.AddSoundSample (Ultimate::CreateSoundSample (frequency, 0x01));
        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::CreateWeaponSpriteReboundSoundSample ()
{
    // Has the weapon sprite rebound sound sample been created?

    if (!m_weaponSpriteReboundSoundSample.IsSoundSampleGenerated ())
    {
        // No. Create the sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x21; frequency <= 0x3f; frequency += 2)
        {
            m_weaponSpriteReboundSoundSample.AddSoundSample (Ultimate::CreateSoundSample (frequency, 0x01));
        } // Endfor.

    } // Endif.

} // Endproc.


FolioStatus CreateWeaponSprites (FolioHandle        dcHandle,
                                 WeaponSpritesMap   &weaponSpritesMap)
{
    FolioStatus status = ERR_SUCCESS;

    weaponSpritesMap.clear ();   // Initialise!

    // Build the weapon sprites map.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_weaponSpriteAttributesTable) / sizeof (WeaponSpriteAttributes)));
         ++index)
    {              
        // Create a weapon sprite.

        WeaponSpritePtr weaponSprite(new WeaponSprite);

        status = weaponSprite->Create (dcHandle,
                                       g_weaponSpriteAttributesTable [index].m_weaponSpriteId,
                                       g_weaponSpriteAttributesTable [index].m_weaponSpriteColour);

        if (status == ERR_SUCCESS)
        {
            // Store the weapon sprite in the weapon sprites map.
        
            weaponSpritesMap.insert (WeaponSpritesMap::value_type(g_weaponSpriteAttributesTable [index].m_weaponSpriteId, 
                                                                  weaponSprite));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        weaponSpritesMap.clear ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
