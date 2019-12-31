// "Home-made" includes.
#include    "StdAfx.h"
#include    "InformationPanel.h"
#include    "ObjectSprite.h"

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
    m_objectSpriteColour(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_colourChangeCount(0),
    m_colourChangeIndex(0)
{
} // Endproc.


ObjectSprite::~ObjectSprite ()
{
} // Endproc.


FolioStatus ObjectSprite::Create (FolioHandle                   dcHandle, 
                                  const SpriteGraphicsMapPtr    &spriteGraphicsMap,
                                  OBJECT_SPRITE_ID              objectSpriteId,
                                  Int32                         screenXLeft,
                                  Int32                         screenYBottom)
{
    // Get the object sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR   objectSpriteColour = GetObjectSpriteColour (objectSpriteId);

    // Query the object sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<OBJECT_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       objectSpriteId,
                                                                                                       *spriteGraphicsMap,
                                                                                                       objectSpriteColour,
                                                                                                       g_objectSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Get the object sprite's graphic.

        const   Folio::Core::Game::SpriteGraphic    &spriteGraphic(spriteGraphicAttributesList.front ().m_spriteGraphicsList.front ());

        // Calculate the initial screen Y top.

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
                                                           Folio::Core::Game::NO_DIRECTION);

        if (status == ERR_SUCCESS)
        {
            // Object sprite is static.

            SetState (STATE_STATIC);

            // Note the object sprite's attributes.

            m_objectSpriteId        = objectSpriteId;
            m_objectSpriteColour    = objectSpriteColour;
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
        status = ChangeAmuletPieceColour ();
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ObjectSprite::HandlePlayerCollision (PlayerSpritePtr        &playerSprite,
                                                 InformationPanelPtr    &informationPanel)
{
    FolioStatus status = ERR_SUCCESS;

    // Increment the score.

    informationPanel->IncrementScore (InformationPanel::SCORE_OBJECT_COLLECTED);

    switch (m_objectSpriteId)
    {
    case OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT:
        // Found an amulet piece.

        playerSprite->SetFoundAmuletPiece (true);

        informationPanel->SetFoundAmuletPiece (m_objectSpriteId);
        break;
    
    case OBJECT_SPRITE_EXTRA_LIFE:
        // Increment player's life.

        status = informationPanel->IncrementPlayerLife ();
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ObjectSprite::ChangeAmuletPieceColour ()
{
    // The colour list.
    static  const   std::vector<Gdiplus::ARGB>  s_colourList =
    {
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW),    },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN),      },
    };

    FolioStatus status = ERR_SUCCESS;

    if (++m_colourChangeCount >= 4)
    {
        m_colourChangeCount = 0;    // Reset.

        if (++m_colourChangeIndex >= s_colourList.size ()) 
        {
            m_colourChangeIndex = 0;
        } // Endif.

        // Change the object sprite's colour.

        status = ChangeSpriteInkColour (s_colourList [m_colourChangeIndex]);
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
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::RED)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN);
        break;

    case OBJECT_SPRITE_RING:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW);
        break;

    case OBJECT_SPRITE_APPLE:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::RED)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::GREEN);
        break;

    case OBJECT_SPRITE_CHARM:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN);
        break;

    case OBJECT_SPRITE_AMULET:
        objectSpriteColour = SET_INK_COLOUR(Folio::Core::Util::Random::GetRandomNumber (Folio::Core::Game::ZxSpectrum::MAGENTA, 
                                                                                        Folio::Core::Game::ZxSpectrum::YELLOW));
        break;

    case OBJECT_SPRITE_EXTRA_LIFE:
        objectSpriteColour = SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::RED);
        break;

    case OBJECT_SPRITE_MONEY_BAG:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::MAGENTA)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW);
        break;

    case OBJECT_SPRITE_SPEAR:   
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::RED)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::GREEN);
        break;

    case OBJECT_SPRITE_CHALICE:
        objectSpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                             ? SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::CYAN)
                             : SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW);
        break;

    case OBJECT_SPRITE_AMULET_PIECE_TOP_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_TOP_RIGHT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_LEFT:
    case OBJECT_SPRITE_AMULET_PIECE_BOTTOM_RIGHT:
        objectSpriteColour = SET_INK_COLOUR(Folio::Core::Game::ZxSpectrum::YELLOW); 
        break;

    default:
        break;
    } // Endswitch.

    return (Folio::Core::Game::ZxSpectrum::BRIGHT | objectSpriteColour);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
