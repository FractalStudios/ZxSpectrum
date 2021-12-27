#pragma once

// STL includes.
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

// Nasty sprite identifier enumeration.
enum NASTY_SPRITE_ID
{
    NASTY_SPRITE_UNDEFINED = -1,
    NASTY_SPRITE_PUMPKIN = 0,            
    NASTY_SPRITE_SPIDER,             
    NASTY_SPRITE_GHOST,              
    NASTY_SPRITE_BOUNCY,             
    NASTY_SPRITE_SMORPH,             
    NASTY_SPRITE_JELLY_GHOUL,        
    NASTY_SPRITE_BAT,                
    NASTY_SPRITE_GHOUL,
    NASTY_SPRITE_WITCH_FLYING, 
    NASTY_SPRITE_GHOUL_FLYING, 
    NASTY_SPRITE_BAT_FLYING,   
    MAX_NASTY_SPRITE = NASTY_SPRITE_BAT_FLYING,
}; // Endenum.


// Nasty sprite.
class NastySprite : public Folio::Core::Game::ANastySprite
{
public:
    // Nasty sprite flags.
    static  const   UInt32  FLAGS_NONE                      = 0x00000000;
    static  const   UInt32  FLAGS_INITIALISED_BY_GRAPHIC    = 0x00000001;
    static  const   UInt32  FLAGS_TERMINATED_BY_GRAPHIC     = 0x00000002;
    
    NastySprite ();
    ~NastySprite ();

    FolioStatus Create (FolioHandle             dcHandle,
                        NASTY_SPRITE_ID         nastySpriteId,
                        UInt32                  screenNumber,
                        const CollisionGrid&    collisionGrid,
                        UInt32                  nastySpriteFlags = FLAGS_INITIALISED_BY_GRAPHIC | FLAGS_TERMINATED_BY_GRAPHIC);
    FolioStatus Move (Gdiplus::Graphics&    graphics,
                      CollisionGrid&        collisionGrid);

    NASTY_SPRITE_ID GetNastySpriteId () const;
    UInt32          GetNastySpriteFlags () const;
    UInt32          GetNastySpriteScreenNumber () const;

    static  bool    IsInitialisedByGraphic (UInt32 nastySpriteFlags);
    static  bool    IsTerminatedByGraphic (UInt32 nastySpriteFlags);

    static  FolioStatus QueryInitialisingGraphics (FolioHandle                                              dcHandle,
                                                   const Folio::Core::Game::ResourceGraphicsCache::OwnerId& ownerId,
                                                   Folio::Core::Game::ZxSpectrum::COLOUR                    spriteColour,
                                                   Folio::Core::Game::SpriteGraphicAttributesList&          spriteGraphicAttributesList);
    static  FolioStatus QueryTerminatingGraphics (FolioHandle                                               dcHandle,
                                                  const Folio::Core::Game::ResourceGraphicsCache::OwnerId&  ownerId,
                                                  Folio::Core::Game::ZxSpectrum::COLOUR                     spriteColour,
                                                  Folio::Core::Game::SpriteGraphicAttributesList&           spriteGraphicAttributesList);

private:
    NASTY_SPRITE_ID m_nastySpriteId;            // The identifier of the nasty sprite.
    UInt32          m_nastySpriteScreenNumber;  // The screen number of the nasty sprite.
    UInt32          m_nastySpriteFlags;         // The flags of the nasty sprite.
    UInt32          m_nastySpriteSpeed;         // The speed of the nasty sprite.

    static  Folio::Core::Util::Sound::SoundSample   m_nastySpriteTerminatedSoundSample; // The nasty sprite terminated sound sample.

    FolioStatus SetInitialisingMode (FolioHandle                            dcHandle,
                                     Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour,
                                     UInt32                                 nastySpriteFlags);
    FolioStatus SetTerminatingMode (FolioHandle                             dcHandle,
                                    Folio::Core::Game::ZxSpectrum::COLOUR   nastySpriteColour,
                                    UInt32                                  nastySpriteFlags);

    void    SetNastySpriteSoundSamples (NASTY_SPRITE_ID nastySpriteId);
    void    SetNastySpriteTerminatedSoundSample (NASTY_SPRITE_ID nastySpriteId);

    static  Int32   GetInitialScreenXLeft (const CollisionGrid& collisionGrid);
    static  Int32   GetInitialScreenYTop (const CollisionGrid& collisionGrid);
    
    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetColour (NASTY_SPRITE_ID nastySpriteId);
    
    static  bool    IsUpdateDirectionRqd (NASTY_SPRITE_ID nastySpriteId);
    static  Folio::Core::Game::Direction    GetDirection (NASTY_SPRITE_ID nastySpriteId);
    
    static  UInt32  GetSpeed (NASTY_SPRITE_ID nastySpriteId);

    static  void    CreateNastySpriteSoundSamples (NASTY_SPRITE_ID nastySpriteId);
    static  void    CreateNastySpriteTerminatedSoundSample ();

    // Private copy constructor to prevent copying.
    NastySprite (const NastySprite& rhs);

    // Private assignment operator to prevent copying.
    NastySprite& operator= (const NastySprite& rhs);
}; // Endclass.                         

// Nasty sprite pointer.
typedef std::shared_ptr<NastySprite>    NastySpritePtr;

// Nasty sprites list.
typedef std::vector<NastySpritePtr>     NastySpritesList;

// Nasty sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<NastySpritePtr> NastySpriteDrawingElement;

// Nasty sprite drawing elements list.
typedef std::vector<NastySpriteDrawingElement> NastySpriteDrawingElementsList;


// Routines.

extern  FolioStatus AddNastySpriteDrawingElement (const NastySpriteDrawingElement&  nastySpriteDrawingElement,
                                                  NastySpriteDrawingElementsList&   nastySpriteDrawingElementsList);
extern  FolioStatus RemoveNastySpriteDrawingElement (UInt32                             screenNumber,  
                                                     UInt32                             maxNastySpriteDrawingElements,
                                                     NastySpriteDrawingElementsList&    nastySpriteDrawingElementsList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
