#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    "CollisionGrid.h"
#include    "ResourceOwnerIds.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// The minimum number of nasty sprites that can be displayed on a screen.
const   UInt32  MIN_NASTY_SPRITES_PER_SCREEN = 0;

// The maximum number of nasty sprites that can be displayed on a screen.
const   UInt32  MAX_NASTY_SPRITES_PER_SCREEN = MAX_NASTY_SPRITE_DRAWING_ELEMENTS / 2;


// Nasty sprite identifier enumeration.
enum NASTY_SPRITE_ID
{
    NASTY_SPRITE_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    NASTY_SPRITE_SPIDER,
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
    NastySprite ();
    ~NastySprite ();

    FolioStatus Create (FolioHandle             dcHandle,
                        NASTY_SPRITE_ID         nastySpriteId,
                        UInt32                  screenMapIndex,
                        const CollisionGrid&    collisionGrid);
    FolioStatus CheckNastySprite (Folio::Core::Game::DrawingElementPtr& drawingElement,
                                  Gdiplus::Graphics&                    graphics,
                                  CollisionGrid&                        collisionGrid);

    NASTY_SPRITE_ID GetNastySpriteId () const;
    UInt32          GetNastySpriteScreenMapIndex () const;

    static  NASTY_SPRITE_ID GetNastySpriteToCreate (UInt32 numFoundAmuletPieces);

private:  
    NASTY_SPRITE_ID m_nastySpriteId;                // The identifier of the nasty sprite.
    UInt32          m_nastySpriteScreenMapIndex;    // The screen map index of the nasty sprite.
    UInt32          m_nastySpriteSpeed;             // The speed of the nasty sprite.

    FolioStatus SetInitialisingMode (FolioHandle                            dcHandle,
                                     Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour);
    FolioStatus SetTerminatingMode (FolioHandle                             dcHandle,
                                    Folio::Core::Game::ZxSpectrum::COLOUR   nastySpriteColour);

    FolioStatus Move (Gdiplus::Graphics&    graphics,
                      CollisionGrid&        collisionGrid);

    bool    IsUpdateNastySpriteDirectionRqd (const CollisionGrid& collisionGrid);
    Folio::Core::Game::Direction    GetNastySpriteDirection (const CollisionGrid& collisionGrid);
    
    static  void    QueryInitialScreenTopLeft (const CollisionGrid& collisionGrid,
                                               Int32&               initialScreenXLeft,
                                               Int32&               initialScreenYTop);
    static  Int32   GetInitialScreenXLeft (Int32                maxNastySpriteScreenWidth,
                                           const CollisionGrid& collisionGrid);
    static  Int32   GetInitialScreenYTop (Int32                 maxNastySpriteScreenHeight,
                                          const CollisionGrid&  collisionGrid);
    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetNastySpriteColour (NASTY_SPRITE_ID nastySpriteId);
    static  UInt32  GetNastySpriteSpeed (NASTY_SPRITE_ID nastySpriteId);

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

extern  FolioStatus CheckScreenNastySprites (FolioHandle        dcHandle,
                                             Gdiplus::Graphics& graphics,
                                             CollisionGrid&     collisionGrid,
                                             UInt32&            screenAddNastySpriteTickCount);
extern  FolioStatus RemoveScreenNastySprites (CollisionGrid& collisionGrid);
extern  FolioStatus StoreScreenNastySpriteBackgrounds (Gdiplus::Graphics& graphics);
extern  FolioStatus RestoreScreenNastySpriteBackgrounds (Gdiplus::Graphics& graphics);
extern  FolioStatus DrawScreenNastySprites (Gdiplus::Graphics& graphics);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
