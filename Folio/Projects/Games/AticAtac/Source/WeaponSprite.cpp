// "Home-made" includes.
#include    "StdAfx.h"
#include    "WeaponSprite.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Weapon sprite graphic attributes.
static  const   Folio::Core::Game::SpriteGraphicsAttributesList<WEAPON_SPRITE_ID, SPRITE_ID>    g_weaponSpriteGraphicAttributes =
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


FolioStatus WeaponSprite::Create (FolioHandle               dcHandle,
                                  WEAPON_SPRITE_ID          weaponSpriteId,
                                  const SpriteGraphicsMap   &spriteGraphicsMap,
                                  const Gdiplus::Rect       &mainPlayerRect,      
                                  Direction                 initialDirection)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 25;

    // Get the weapon sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR   weaponSpriteColour = GetColour (weaponSpriteId);

    // Query the weapon sprite's graphics.

    SpriteGraphicAttributesList spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<WEAPON_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       weaponSpriteId,
                                                                                                       spriteGraphicsMap,
                                                                                                       weaponSpriteColour,
                                                                                                       g_weaponSpriteGraphicAttributes,
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
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           weaponSpriteColour,
                                                           initialDirection,
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERROR_SUCCESS)
        {
            // Create the weapon sprite sound samples.

            CreateWeaponSpriteSoundSamples (weaponSpriteId);

            // Set the weapon sprite's rebound sound samples.

            status = SetReboundSoundSamples (weaponSpriteId);

            if (status == ERROR_SUCCESS)
            {
                // Note the weapon sprite's attributes.

                m_weaponSpriteId = weaponSpriteId;
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus WeaponSprite::Move (Gdiplus::Graphics   &graphics,
                                CollisionGrid       &collisionGrid)
{
    // Move the weapon sprite.

    return (Folio::Core::Game::AWeaponSprite::Move (graphics, WEAPON_SPRITE_SPEED, collisionGrid));
} // Endproc.


void    WeaponSprite::PlayWeaponsSpriteSound () const
{
    switch (m_state)
    {
    case STATE_INITIALISED:
        PlayWeaponSpriteInitialisedSound (m_weaponSpriteId);
        break;

    case STATE_TERMINATED:
        PlayWeaponSpriteTerminatedSound (m_weaponSpriteId);
        break;
    
    default:
        break;
    } // Endswitch.

} // Endif.


WEAPON_SPRITE_ID   WeaponSprite::GetWeaponSpriteId () const
{
    return (m_weaponSpriteId);
} // Endproc.


FolioStatus WeaponSprite::SetReboundSoundSamples (WEAPON_SPRITE_ID weaponSpriteId)
{
    // Set the weapon sprite's rebound sound samples.

    return (SetSpriteReboundSoundSamples (SpriteReboundSoundAttributesList(1, 
                                                                           SpriteReboundSoundAttributes(ALL_DIRECTIONS, SpriteReboundSoundSample(new SpriteReboundSoundSample::element_type(m_weaponSpriteReboundSoundSample))))));
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


Folio::Core::Game::ZxSpectrum::COLOUR   WeaponSprite::GetColour (WEAPON_SPRITE_ID weaponSpriteId)
{
    switch (weaponSpriteId)
    {
    case WEAPON_SPRITE_WIZARD_POTION:             
        return (Folio::Core::Game::ZxSpectrum::UNDEFINED);
                                                 
    case WEAPON_SPRITE_SERF_SWORD:              
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW);
    
    case WEAPON_SPRITE_KNIGHT_AXE:            
    default:
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED);
    } // Endswitch.

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
    default:
        // Create the knight weapon sprite initialised sound sample.

        CreateKnightWeaponSpriteInitialisedSoundSample ();
        break;
    } // Endswitch.

    // Create the weapon sprite terminated sound sample.

    CreateWeaponSpriteTerminatedSoundSample ();

    // Create the weapon sprite rebound sound sample.

    CreateWeaponSpriteReboundSoundSample ();
} // Endproc.


void    WeaponSprite::CreateKnightWeaponSpriteInitialisedSoundSample ()
{
    if (!m_knightWeaponSpriteInitialisedSoundSample.IsSoundSampleGenerated ())
    {
        // Create the sound sample representing the required sound.
    
        Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x06;

        for (UInt32 count = 0; count < 12; ++count)
        {
            m_knightWeaponSpriteInitialisedSoundSample.AddSoundSample (Ultimate::MapMakeSound (frequency, 0x01));

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
    if (!m_wizardWeaponSpriteInitialisedSoundSample.IsSoundSampleGenerated ())
    {
        // Create the sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0xef; frequency <= 0xfd; frequency += 0x02)
        {
            m_wizardWeaponSpriteInitialisedSoundSample.AddSoundSample (Ultimate::MapMakeSound (frequency, 0x01));
        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::CreateSerfWeaponSpriteInitialisedSoundSample ()
{
    if (!m_serfWeaponSpriteInitialisedSoundSample.IsSoundSampleGenerated ())
    {
        // Create the sound sample representing the required sound.
    
        Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x1d;

        for (UInt32 count = 0; count < 16; ++count)
        {
            m_serfWeaponSpriteInitialisedSoundSample.AddSoundSample (Ultimate::MapMakeSound (frequency, 0x01));

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
    if (!m_weaponSpriteTerminatedSoundSample.IsSoundSampleGenerated ())
    {
        // Create the sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x3f; frequency >= 0x21; frequency -= 2)
        {
           m_weaponSpriteTerminatedSoundSample.AddSoundSample (Ultimate::MapMakeSound (frequency, 0x01));
        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::CreateWeaponSpriteReboundSoundSample ()
{
    if (!m_weaponSpriteReboundSoundSample.IsSoundSampleGenerated ())
    {
        // Create the sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x21; frequency <= 0x3f; frequency += 2)
        {
           m_weaponSpriteReboundSoundSample.AddSoundSample (Ultimate::MapMakeSound (frequency, 0x01));
        } // Endfor.

    } // Endif.

} // Endproc.


void    WeaponSprite::PlayWeaponSpriteInitialisedSound (WEAPON_SPRITE_ID weaponSpriteId)
{
    switch (weaponSpriteId)
    {
    case WEAPON_SPRITE_WIZARD_POTION:
        Folio::Core::Util::Sound::PlaySoundSample (m_wizardWeaponSpriteInitialisedSoundSample);
        break;

    case WEAPON_SPRITE_SERF_SWORD:
        Folio::Core::Util::Sound::PlaySoundSample (m_serfWeaponSpriteInitialisedSoundSample);
        break;

    case WEAPON_SPRITE_KNIGHT_AXE:
    default:
        Folio::Core::Util::Sound::PlaySoundSample (m_knightWeaponSpriteInitialisedSoundSample);
        break;
    } // Endswitch.

} // Endproc.


void    WeaponSprite::PlayWeaponSpriteTerminatedSound (WEAPON_SPRITE_ID weaponSpriteId)
{
    Folio::Core::Util::Sound::PlaySoundSample (m_weaponSpriteTerminatedSoundSample);
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
