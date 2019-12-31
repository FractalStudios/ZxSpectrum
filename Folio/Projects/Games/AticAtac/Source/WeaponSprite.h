#pragma once

// STL includes.
#include    <map>
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"

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

    FolioStatus Create (FolioHandle                             dcHandle,
                        WEAPON_SPRITE_ID                        weaponSpriteId,
                        Folio::Core::Game::ZxSpectrum::COLOUR   weaponSpriteColour);
    FolioStatus Start ();
    FolioStatus Stop (bool bPlayTerminatedSound);
    FolioStatus Move (Gdiplus::Graphics &graphics,
                      CollisionGrid     &collisionGrid);

    void    PlayWeaponSpriteInitialisedSound () const;
    void    PlayWeaponSpriteTerminatedSound () const;

    WEAPON_SPRITE_ID    GetWeaponSpriteId () const;

    static  WEAPON_SPRITE_ID    GetMainPlayerWeaponSpriteId ();

private:
    static  const   UInt32  WEAPON_SPRITE_SPEED = 8;    // Weapon sprite speed.

    WEAPON_SPRITE_ID    m_weaponSpriteId;   // The identifier of the weapon sprite.

    Int32   GetInitialScreenXLeft (const Gdiplus::Rect &mainPlayerRect) const;
    Int32   GetInitialScreenYTop (const Gdiplus::Rect &mainPlayerRect) const;

    void    SetSoundSamples (WEAPON_SPRITE_ID weaponSpriteId);
    void    SetInitialisedSoundSample (WEAPON_SPRITE_ID weaponSpriteId);
    void    SetTerminatedSoundSample (WEAPON_SPRITE_ID weaponSpriteId);
    void    SetReboundSoundSample (WEAPON_SPRITE_ID weaponSpriteId);

    static  Folio::Core::Util::Sound::SoundSample   m_knightWeaponSpriteInitialisedSoundSample; // The knight weapon sprite initialised sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_wizardWeaponSpriteInitialisedSoundSample; // The wizard weapon sprite initialised sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_serfWeaponSpriteInitialisedSoundSample;   // The serf weapon sprite initialised sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_weaponSpriteTerminatedSoundSample;        // The weapon sprite terminated sound sample.
    static  Folio::Core::Util::Sound::SoundSample   m_weaponSpriteReboundSoundSample;           // The weapon sprite rebound sound sample.

    static  void    CreateWeaponSpriteSoundSamples (WEAPON_SPRITE_ID weaponSpriteId);
    static  void    CreateKnightWeaponSpriteInitialisedSoundSample ();
    static  void    CreateWizardWeaponSpriteInitialisedSoundSample ();
    static  void    CreateSerfWeaponSpriteInitialisedSoundSample ();
    static  void    CreateWeaponSpriteTerminatedSoundSample ();
    static  void    CreateWeaponSpriteReboundSoundSample ();

    // Private copy constructor to prevent copying.
    WeaponSprite (const WeaponSprite& rhs);

    // Private assignment operator to prevent copying.
    WeaponSprite& operator= (const WeaponSprite& rhs);
}; // Endclass.                         

// Weapon sprite pointer.
typedef std::shared_ptr<WeaponSprite>   WeaponSpritePtr;

// Weapon sprites map.
typedef std::map<WEAPON_SPRITE_ID, WeaponSpritePtr> WeaponSpritesMap;

// Weapon sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<WeaponSpritePtr> WeaponSpriteDrawingElement;

// Weapon sprite drawing elements list.
typedef std::vector<WeaponSpriteDrawingElement> WeaponSpriteDrawingElementsList;


// Routines.

FolioStatus CreateWeaponSprites (FolioHandle        dcHandle,
                                 WeaponSpritesMap   &weaponSpritesMap);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
