#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "DrawingElement.h"
#include    "PlayerSprite.h"
#include    "SpriteGraphics.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Nasty sprite identifier enumeration.
enum NASTY_SPRITE_ID
{
    NASTY_SPRITE_UNDEFINED = DRAWING_ELEMENT_UNDEFINED,
    NASTY_SPRITE_SPIDER = DRAWING_ELEMENT_NASTY_SPRITE * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,
    NASTY_SPRITE_SCORPION,
    NASTY_SPRITE_BAT,                
    NASTY_SPRITE_PARROT,            
    NASTY_SPRITE_MONKEY,             
    NASTY_SPRITE_LIZARD,              
    NASTY_SPRITE_SNAKE,             
    NASTY_SPRITE_RAT,             
    NASTY_SPRITE_BIRD,             
    NASTY_SPRITE_FLY,             
    NASTY_SPRITE_FROG,             
    NASTY_SPRITE_BUG, 
    NASTY_SPRITE_SKUNK,   
    NASTY_SPRITE_EARWIG, 
}; // Endenum.


// Nasty sprite.
class NastySprite : public Folio::Core::Game::ANastySprite
{
public:
    NastySprite (const PlayerSpritePtr &playerSprite);
    ~NastySprite ();

    FolioStatus Create (FolioHandle                 dcHandle,
                        const SpriteGraphicsMapPtr  &spriteGraphicsMap,
                        NASTY_SPRITE_ID             nastySpriteId,
                        const CollisionGrid         &collisionGrid);

    FolioStatus CheckNasty (Folio::Core::Game::DrawingElementPtr    &drawingElement,
                            Gdiplus::Graphics                       &graphics,
                            CollisionGrid                           &collisionGrid);

    static  UInt32          GetCreateNastySpriteTickCount ();
    static  NASTY_SPRITE_ID GetNastySpriteToCreate (UInt32 numFoundAmuletPieces);
    static  bool            IsRemoveScreenNastySprites (UInt32 exitScreenTickCount);

private:  
    PlayerSpritePtr m_playerSprite;     // The player sprite.
    NASTY_SPRITE_ID m_nastySpriteId;    // The identifier of the nasty sprite.
    UInt32          m_nastySpriteSpeed; // The speed of the nasty sprite.

    static  Folio::Core::Game::SpriteStationarySoundSamplesList m_nastySpriteTerminatingSoundSamplesList;   // The nasty sprite's terminating sound samples.

    FolioStatus SetInitialisingMode (FolioHandle                            dcHandle,
                                     const SpriteGraphicsMapPtr             &spriteGraphicsMap,
                                     Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour);
    FolioStatus SetTerminatingMode (FolioHandle                             dcHandle,
                                    const SpriteGraphicsMapPtr              &spriteGraphicsMap,
                                    Folio::Core::Game::ZxSpectrum::COLOUR   nastySpriteColour);

    FolioStatus Move (Gdiplus::Graphics &graphics,
                      CollisionGrid     &collisionGrid);

    bool    IsUpdateNastySpriteDirectionRqd (const CollisionGrid &collisionGrid);
    Folio::Core::Game::Direction    GetNastySpriteDirection (const CollisionGrid &collisionGrid);
    
    static  void    QueryInitialScreenTopLeft (const CollisionGrid  &collisionGrid,
                                               Int32                &initialScreenXLeft,
                                               Int32                &initialScreenYTop);
    static  Int32   GetInitialScreenXLeft (Int32                maxNastySpriteScreenWidth,
                                           const CollisionGrid  &collisionGrid);
    static  Int32   GetInitialScreenYTop (Int32                 maxNastySpriteScreenHeight,
                                          const CollisionGrid   &collisionGrid);
    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetNastySpriteColour (NASTY_SPRITE_ID nastySpriteId);
    static  UInt32  GetNastySpriteSpeed (NASTY_SPRITE_ID nastySpriteId);

    static  Folio::Core::Game::SpriteStationarySoundSamplesList GetNastySpriteTerminatingSoundSamples ();

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

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
