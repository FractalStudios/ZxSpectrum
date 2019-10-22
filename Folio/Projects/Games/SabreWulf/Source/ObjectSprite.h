#pragma once

// STL includes.
#include    <memory>
#include    <vector>

// "Home-made" includes.
#include    <Applet.h>
#include    <Game.h>
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

class   InformationPanel;    // Pre-declare class
using   InformationPanelPtr = std::shared_ptr<InformationPanel>;


// Object sprite identifier enumeration.
enum OBJECT_SPRITE_ID
{
    OBJECT_SPRITE_UNDEFINED = DRAWING_ELEMENT_UNDEFINED,
    OBJECT_SPRITE_BOX = DRAWING_ELEMENT_OBJECT_SPRITE * MAX_NUM_DRAWING_ELEMENTS_PER_ITEM,                              
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

    FolioStatus Create (FolioHandle                             dcHandle,
                        const SpriteGraphicsMapPtr              &spriteGraphicsMap,
                        OBJECT_SPRITE_ID                        objectSpriteId,
                        Int32                                   screenXLeft,
                        Int32                                   screenYBottom);

    FolioStatus ChangeObjectSpriteColour ();
    FolioStatus HandlePlayerCollision (PlayerSpritePtr      &playerSprite, 
                                       InformationPanelPtr  &informationPanel);

private:
    OBJECT_SPRITE_ID                        m_objectSpriteId;       // The identifier of the object sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_objectSpriteColour;   // The colour of the object sprite.

    UInt32  m_colourChangeCount;    // The colour change count.
    UInt32  m_colourChangeIndex;    // The colour change index.

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

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
