// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "ObjectSprite.h"
#include    "Screen.h"
#include    "SpriteGraphics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Object sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<OBJECT_SPRITE_ID, SPRITE_ID>    g_objectSpriteGraphicCharacteristics =
{
//      m_spriteId                                  m_direction                         spriteGraphicIdsList
    {   OBJECT_SPRITE_BOX,                          Folio::Core::Game::NO_DIRECTION,    {   SPRITE_BOX,                         },  },  
    {   OBJECT_SPRITE_RING,                         Folio::Core::Game::NO_DIRECTION,    {   SPRITE_RING,                        },  },
    {   OBJECT_SPRITE_APPLE,                        Folio::Core::Game::NO_DIRECTION,    {   SPRITE_APPLE,                       },  },
    {   OBJECT_SPRITE_CHARM,                        Folio::Core::Game::NO_DIRECTION,    {   SPRITE_CHARM,                       },  },
    {   OBJECT_SPRITE_AMULET,                       Folio::Core::Game::NO_DIRECTION,    {   SPRITE_AMULET,                      },  },
    {   OBJECT_SPRITE_EXTRA_LIFE,                   Folio::Core::Game::NO_DIRECTION,    {   SPRITE_EXTRA_LIFE,                  },  },
    {   OBJECT_SPRITE_MONEY_BAG,                    Folio::Core::Game::NO_DIRECTION,    {   SPRITE_MONEY_BAG,                   },  },
    {   OBJECT_SPRITE_SPEAR,                        Folio::Core::Game::NO_DIRECTION,    {   SPRITE_SPEAR,                       },  },
    {   OBJECT_SPRITE_CHALICE,                      Folio::Core::Game::NO_DIRECTION,    {   SPRITE_CHALICE,                     },  },
    {   OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT,        Folio::Core::Game::NO_DIRECTION,    {   SPRITE_AMULET_PIECE_TOP_LEFT,       },  },
    {   OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT,       Folio::Core::Game::NO_DIRECTION,    {   SPRITE_AMULET_PIECE_TOP_RIGHT,      },  },
    {   OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT,     Folio::Core::Game::NO_DIRECTION,    {   SPRITE_AMULET_PIECE_BOTTOM_LEFT,    },  },
    {   OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT,    Folio::Core::Game::NO_DIRECTION,    {   SPRITE_AMULET_PIECE_BOTTOM_RIGHT,   },  },
};


ObjectSprite::ObjectSprite ()
:   m_objectSpriteId(OBJECT_SPRITE_UNDEFINED),
    m_colourChangeCounter(0),
    m_colourChangeIndex(FOLIO_INVALID_INDEX)
{
} // Endproc.


ObjectSprite::~ObjectSprite ()
{
} // Endproc.


FolioStatus ObjectSprite::Create (FolioHandle       dcHandle, 
                                  OBJECT_SPRITE_ID  objectSpriteId,
                                  UInt32            currentScreenMapIndex,
                                  Int32             screenXLeft,
                                  Int32             screenYBottom)
{
    // Get the object sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR   objectSpriteColour = GetObjectSpriteColour (objectSpriteId);

    // Query the object sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<OBJECT_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       Screen::MakeOwnerId (currentScreenMapIndex),
                                                                                                       Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE,
                                                                                                       objectSpriteId,
                                                                                                       objectSpriteColour,
                                                                                                       g_objectSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Get the object sprite's graphic.

        const   Folio::Core::Game::SpriteGraphic    &spriteGraphic(spriteGraphicAttributesList.front ().m_spriteGraphicsList.front ());

        // Calculate the object sprite's screen Y top.

        Int32   screenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (screenYBottom, 
                                                                                 spriteGraphic->GetGraphicWidth (),
                                                                                 spriteGraphic->GetGraphicHeight ());

        // Create the object sprite.

        status = Folio::Core::Game::AStaticSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           screenXLeft,
                                                           screenYTop,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (objectSpriteColour),
                                                           Folio::Core::Game::NO_DIRECTION,
                                                           &(g_resourceGraphicsCache));

        if (status == ERR_SUCCESS)
        {
            // Object sprite is static.

            SetState (STATE_STATIC);

            // Note the object sprite's attributes.

            m_objectSpriteId = objectSpriteId;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ObjectSprite::ChangeObjectSpriteColour ()
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_objectSpriteId)
    {
    case OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT:
        // Change the amulet piece's colour.

        status = ChangeAmuletPieceColour ();
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ObjectSprite::HandlePlayerCollision (bool& foundAmuletPiece)
{
    foundAmuletPiece = false;   // Initialise!

    // The player has collided with an object sprite.

    // Play the player collected item sound.

    FolioStatus status = g_soundResources.PlayPlayerCollectedItemSound ();

    if (status == ERR_SUCCESS)
    {
        // Add to the player's score.

        g_informationPanel->AddPlayerScore (InformationPanel::SCORE_OBJECT_COLLECTED);

        switch (m_objectSpriteId)
        {
        case OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT:
        case OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT:
        case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT:
        case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT:
            // The player has just found an amulet piece.

            foundAmuletPiece = true;

            g_informationPanel->SetFoundAmuletPiece (m_objectSpriteId);
            break;
    
        case OBJECT_SPRITE_EXTRA_LIFE:
            // The player has just found an extra life.

            // Increment the player's life.

            status = g_informationPanel->IncrementPlayerLife ();
            break;

        default:
            break;
        } // Endswitch.
    
    } // Endif.

    return (status);
} // Endproc.


OBJECT_SPRITE_ID    ObjectSprite::GetObjectSpriteId () const
{
    return (m_objectSpriteId);
} // Endproc.


FolioStatus ObjectSprite::ChangeAmuletPieceColour ()
{
    // The amulet piece colour list.
    static  const   std::vector<Gdiplus::ARGB>  s_amuletPieceColourList =
    {
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW)),    },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::WHITE)),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::GREEN)),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN)),      },
    };

    FolioStatus status = ERR_SUCCESS;

    // Should the amulet piece's colour be changed?

    if (++m_colourChangeCounter >= 4)
    {
        // Yes.

        m_colourChangeCounter = 0;  // Reset.

        if (++m_colourChangeIndex >= s_amuletPieceColourList.size ()) 
        {
            m_colourChangeIndex = 0;
        } // Endif.

        // Change the object sprite's colour.

        status = ChangeSpriteInkColour (s_amuletPieceColourList [m_colourChangeIndex]);
    } // Endif.

    return (status);
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   ObjectSprite::GetObjectSpriteColour (OBJECT_SPRITE_ID objectSpriteId)
{
    Folio::Core::Game::ZxSpectrum::COLOUR   objectSpriteColour = Folio::Core::Game::ZxSpectrum::UNDEFINED;

    switch (objectSpriteId)
    {
    case OBJECT_SPRITE_BOX:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::RED
                             : Folio::Core::Game::ZxSpectrum::CYAN;
        break;

    case OBJECT_SPRITE_RING:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::MAGENTA
                             : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case OBJECT_SPRITE_APPLE:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::RED
                             : Folio::Core::Game::ZxSpectrum::GREEN;
        break;

    case OBJECT_SPRITE_CHARM:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::MAGENTA
                             : Folio::Core::Game::ZxSpectrum::CYAN;
        break;

    case OBJECT_SPRITE_AMULET:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (Folio::Core::Game::ZxSpectrum::MAGENTA, 
                                                                         Folio::Core::Game::ZxSpectrum::YELLOW);
        break;

    case OBJECT_SPRITE_EXTRA_LIFE:
        objectSpriteColour = Folio::Core::Game::ZxSpectrum::RED;
        break;

    case OBJECT_SPRITE_MONEY_BAG:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::MAGENTA
                             : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case OBJECT_SPRITE_SPEAR:   
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::RED
                             : Folio::Core::Game::ZxSpectrum::GREEN;
        break;

    case OBJECT_SPRITE_CHALICE:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? Folio::Core::Game::ZxSpectrum::CYAN
                             : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT:
        objectSpriteColour = Folio::Core::Game::ZxSpectrum::YELLOW; 
        break;

    default:
        break;
    } // Endswitch.

    return (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(objectSpriteColour));
} // Endproc.


static  FolioStatus AddScreenObjectSprite (const ObjectSpritePtr&           objectSprite,
                                           ObjectSpriteDrawingElementsList& objectSpriteDrawingElementsList, 
                                           CollisionGrid&                   collisionGrid)
{
    // Create an object sprite drawing element.

    ObjectSpriteDrawingElement  objectSpriteDrawingElement(Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_OBJECT_SPRITE, 
                                                           objectSprite);

    // Add the object sprite to the current screen's collision grid.

    FolioStatus status = collisionGrid.AddCellElement (*(objectSpriteDrawingElement.m_drawingElement));

    if (status == ERR_SUCCESS)
    {
        // Add the object sprite to the current screen's object sprite drawing 
        // elements list.

        objectSpriteDrawingElementsList.push_back (objectSpriteDrawingElement);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InitialiseScreenObjectSprites (FolioHandle                      dcHandle,
                                           ObjectSpriteDrawingElementsList& objectSpriteDrawingElementsList,
                                           CollisionGrid&                   collisionGrid)
{
    objectSpriteDrawingElementsList.clear ();   // Initialise!
    
    // Query the current screen's object sprites.

    ObjectSpritesList   objectSpritesList;

    FolioStatus status = g_screenMap.QueryScreenObjectSprites (dcHandle, objectSpritesList);

    if ((status == ERR_SUCCESS) && !objectSpritesList.empty ())
    {
        // Add each object sprite to the current screen.

        for (ObjectSpritesList::const_iterator itr = objectSpritesList.begin ();
             (status == ERR_SUCCESS) && (itr != objectSpritesList.end ());
             ++itr)
        {
            // Add the object sprite to the current screen.

            status = AddScreenObjectSprite (*itr,
                                            objectSpriteDrawingElementsList, 
                                            collisionGrid);
        } // Endfor.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus CheckScreenObjectSprites (Gdiplus::Graphics&                graphics,
                                      ObjectSpriteDrawingElementsList&  objectSpriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Any current screen object sprites?

    if (!objectSpriteDrawingElementsList.empty ())
    {
        // Yes. Change the current screen's object sprite colours.

        for (ObjectSpriteDrawingElementsList::iterator itr = objectSpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != objectSpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the object sprite.

            ObjectSpritePtr &objectSprite(itr->m_sprite);

            // Change the colour of the object sprite.

            status = objectSprite->ChangeObjectSpriteColour ();
        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus StoreScreenObjectSpriteBackgrounds (Gdiplus::Graphics&                  graphics,
                                                ObjectSpriteDrawingElementsList&    objectSpriteDrawingElementsList)
{
    return (Folio::Core::Game::StoreSpriteBackgrounds<ObjectSpriteDrawingElementsList> (graphics, 
                                                                                        objectSpriteDrawingElementsList));
} // Endproc.


FolioStatus RestoreScreenObjectSpriteBackgrounds (Gdiplus::Graphics&                graphics,
                                                  ObjectSpriteDrawingElementsList&  objectSpriteDrawingElementsList)
{
    return (Folio::Core::Game::RestoreSpriteBackgrounds<ObjectSpriteDrawingElementsList> (graphics, 
                                                                                          objectSpriteDrawingElementsList));
} // Endproc.


FolioStatus DrawScreenObjectSprites (Gdiplus::Graphics&                 graphics,
                                     ObjectSpriteDrawingElementsList&   objectSpriteDrawingElementsList)
{
    return (Folio::Core::Game::DrawSprites<ObjectSpriteDrawingElementsList> (graphics, 
                                                                             objectSpriteDrawingElementsList));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
