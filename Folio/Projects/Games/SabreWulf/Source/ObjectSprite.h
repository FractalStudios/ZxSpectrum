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

namespace SabreWulf
{

// Object sprite identifier enumeration.
enum OBJECT_SPRITE_ID
{
    OBJECT_SPRITE_UNDEFINED = Folio::Core::Game::AItem::ITEM_ID_UNDEFINED,
    OBJECT_SPRITE_BOX,
    OBJECT_SPRITE_RING,
    OBJECT_SPRITE_APPLE,
    OBJECT_SPRITE_CHARM,
    OBJECT_SPRITE_AMULET,
    OBJECT_SPRITE_EXTRA_LIFE,
    OBJECT_SPRITE_MONEY_BAG,
    OBJECT_SPRITE_SPEAR,   
    OBJECT_SPRITE_CHALICE,
    OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT,
    OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT,
    OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT,
    OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT,
}; // Endenum.


// Object sprite.
class ObjectSprite : public Folio::Core::Game::AStaticSprite
{
public:
    ObjectSprite ();
    ~ObjectSprite ();

    FolioStatus Create (FolioHandle         dcHandle,
                        OBJECT_SPRITE_ID    objectSpriteId,
                        UInt32              currentScreenMapIndex,
                        Int32               screenXLeft,
                        Int32               screenYBottom);
    FolioStatus ChangeObjectSpriteColour ();
    FolioStatus HandlePlayerCollision (bool& foundAmuletPiece);

    OBJECT_SPRITE_ID    GetObjectSpriteId () const;

private:
    OBJECT_SPRITE_ID    m_objectSpriteId;   // The identifier of the object sprite.

    UInt32  m_colourChangeCounter;  // The colour change counter of the object sprite (if the object sprite supports colour change).
    UInt32  m_colourChangeIndex;    // The colour change index of the object sprite (if the object sprite supports colour change).

    static  Folio::Core::Util::Sound::SoundSample   m_objectCollectedSoundSample;   // The object collected sound sample.

    FolioStatus ChangeAmuletPieceColour ();

    static  Folio::Core::Game::ZxSpectrum::COLOUR   GetObjectSpriteColour (OBJECT_SPRITE_ID objectSpriteId);

    // Private copy constructor to prevent copying.
    ObjectSprite (const ObjectSprite& rhs);

    // Private assignment operator to prevent copying.
    ObjectSprite& operator= (const ObjectSprite& rhs);
}; // Endclass.                         

// Object sprite pointer.
typedef std::shared_ptr<ObjectSprite>   ObjectSpritePtr;

// Object sprites list.
typedef std::vector<ObjectSpritePtr>    ObjectSpritesList;

// Object sprite drawing element.
typedef Folio::Core::Game::SpriteDrawingElement<ObjectSpritePtr>    ObjectSpriteDrawingElement;

// Object sprite drawing elements list.
typedef std::vector<ObjectSpriteDrawingElement> ObjectSpriteDrawingElementsList;


// Routines.

extern  FolioStatus InitialiseScreenObjectSprites (FolioHandle                      dcHandle,
                                                   ObjectSpriteDrawingElementsList& objectSpriteDrawingElementsList,
                                                   CollisionGrid&                   collisionGrid);
extern  FolioStatus CheckScreenObjectSprites (Gdiplus::Graphics&                graphics, 
                                              ObjectSpriteDrawingElementsList&  objectSpriteDrawingElementsList);
extern  FolioStatus StoreScreenObjectSpriteBackgrounds (Gdiplus::Graphics&                  graphics,
                                                        ObjectSpriteDrawingElementsList&    objectSpriteDrawingElementsList);
extern  FolioStatus RestoreScreenObjectSpriteBackgrounds (Gdiplus::Graphics&                graphics,
                                                          ObjectSpriteDrawingElementsList&  objectSpriteDrawingElementsList);
extern  FolioStatus DrawScreenObjectSprites (Gdiplus::Graphics&                 graphics,
                                             ObjectSpriteDrawingElementsList&   objectSpriteDrawingElementsList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
