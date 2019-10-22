#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "PlayerSprite.h"
#include    "SpriteGraphics.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Weapon sprite identifier enumeration.
enum WEAPON_SPRITE_ID
{
    WEAPON_SPRITE_UNDEFINED = Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED,
    WEAPON_SPRITE_KNIGHT_AXE = 0,            
    WEAPON_SPRITE_WIZARD_POTION,             
    WEAPON_SPRITE_SERF_SWORD,
    MAX_WEAPON_SPRITE = WEAPON_SPRITE_SERF_SWORD, 
}; // Endenum.


// Weapon sprite.
class WeaponSprite : public Folio::Core::Game::AWeaponSprite
{
public:
    WeaponSprite ();
    ~WeaponSprite ();

    FolioStatus Create (FolioHandle             dcHandle,
                        WEAPON_SPRITE_ID        weaponSpriteId,
                        const SpriteGraphicsMap &spriteGraphicsMap,
                        const Gdiplus::Rect     &mainPlayerRect,      
                        Direction               initialDirection = E);
    FolioStatus Move (Gdiplus::Graphics &graphics,
                      CollisionGrid     &collisionGrid);

    void    PlayWeaponsSpriteSound () const;

    WEAPON_SPRITE_ID    GetWeaponSpriteId () const;

private:
    static  const   UInt32  WEAPON_SPRITE_SPEED = 8;    // Weapon sprite speed.

    WEAPON_SPRITE_ID    m_weaponSpriteId;   // The identifier of the weapon sprite.

    FolioStatus SetReboundSoundSamples (WEAPON_SPRITE_ID weaponSpriteId);

    static  Folio::Core::Util::Sound::SoundSample   m_knightWeaponSpriteInitialisedSoundSample; // The knight weapon sprite initialised sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_wizardWeaponSpriteInitialisedSoundSample; // The wizard weapon sprite initialised sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_serfWeaponSpriteInitialisedSoundSample;   // The serf weapon sprite initialised sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_weaponSpriteTerminatedSoundSample;        // The weapon sprite terminated sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_weaponSpriteReboundSoundSample;           // The weapon sprite rebound sound sample.

    static  Int32                                   GetInitialScreenXLeft (const Gdiplus::Rect    &mainPlayerRect,
                                                                           Int32                  weaponSpriteWidth);
    static  Int32                                   GetInitialScreenYTop (const Gdiplus::Rect &mainPlayerRect,
                                                                          Int32               weaponSpriteHeight);
    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetColour (WEAPON_SPRITE_ID weaponSpriteId);

    static  void    CreateWeaponSpriteSoundSamples (WEAPON_SPRITE_ID weaponSpriteId);
    static  void    CreateKnightWeaponSpriteInitialisedSoundSample ();
    static  void    CreateWizardWeaponSpriteInitialisedSoundSample ();
    static  void    CreateSerfWeaponSpriteInitialisedSoundSample ();
    static  void    CreateWeaponSpriteTerminatedSoundSample ();
    static  void    CreateWeaponSpriteReboundSoundSample ();

    static  void    PlayWeaponSpriteInitialisedSound (WEAPON_SPRITE_ID weaponSpriteId);
    static  void    PlayWeaponSpriteTerminatedSound (WEAPON_SPRITE_ID weaponSpriteId);

    // Private copy constructor to prevent copying.
    WeaponSprite (const WeaponSprite& rhs);

    // Private assignment operator to prevent copying.
    WeaponSprite& operator= (const WeaponSprite& rhs);
}; // Endclass.                         

// Weapon sprite pointer.
typedef std::shared_ptr<WeaponSprite>   WeaponSpritePtr;

// Weapon sprites list.
typedef std::vector<WeaponSpritePtr>    WeaponSpritesList;

// Weapon sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<WeaponSpritePtr> WeaponSpriteDrawingElement;

// Weapon sprite drawing elements list.
typedef std::vector<WeaponSpriteDrawingElement> WeaponSpriteDrawingElementsList;


// Routines.

WEAPON_SPRITE_ID    GetMainPlayerWeaponSpriteId (const PlayerSpritePtr &mainPlayer);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
