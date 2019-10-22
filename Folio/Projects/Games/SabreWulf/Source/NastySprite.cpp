// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "NastySprite.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Nasty sprite graphic attributes.
static  const   Folio::Core::Game::SpriteGraphicsAttributesList<NASTY_SPRITE_ID, SPRITE_ID> g_nastySpriteGraphicAttributes =
{
//      m_spriteId                  m_direction                             m_spriteGraphicIdsList
    {   NASTY_SPRITE_SPIDER,        Folio::Core::Game::ANastySprite::E,     {   SPRITE_SPIDER_RIGHT_1, SPRITE_SPIDER_RIGHT_2,       },  },
    {   NASTY_SPRITE_SPIDER,        Folio::Core::Game::ANastySprite::W,     {   SPRITE_SPIDER_LEFT_1, SPRITE_SPIDER_LEFT_2,         },  },

    {   NASTY_SPRITE_SCORPION,      Folio::Core::Game::ANastySprite::E,     {   SPRITE_SCORPION_RIGHT_1, SPRITE_SCORPION_RIGHT_2,   },  },
    {   NASTY_SPRITE_SCORPION,      Folio::Core::Game::ANastySprite::W,     {   SPRITE_SCORPION_LEFT_1, SPRITE_SCORPION_LEFT_2,     },  },

    {   NASTY_SPRITE_BAT,           Folio::Core::Game::ANastySprite::E,     {   SPRITE_BAT_RIGHT_1, SPRITE_BAT_RIGHT_2,             },  },
    {   NASTY_SPRITE_BAT,           Folio::Core::Game::ANastySprite::W,     {   SPRITE_BAT_LEFT_1, SPRITE_BAT_LEFT_2,               },  },

    {   NASTY_SPRITE_PARROT,        Folio::Core::Game::ANastySprite::E,     {   SPRITE_PARROT_RIGHT_1, SPRITE_PARROT_RIGHT_2,       },  },
    {   NASTY_SPRITE_PARROT,        Folio::Core::Game::ANastySprite::W,     {   SPRITE_PARROT_LEFT_1, SPRITE_PARROT_LEFT_2,         },  },

    {   NASTY_SPRITE_MONKEY,        Folio::Core::Game::ANastySprite::E,     {   SPRITE_MONKEY_RIGHT_1, SPRITE_MONKEY_RIGHT_2,       },  },
    {   NASTY_SPRITE_MONKEY,        Folio::Core::Game::ANastySprite::W,     {   SPRITE_MONKEY_LEFT_1, SPRITE_MONKEY_LEFT_2,         },  },

    {   NASTY_SPRITE_LIZARD,        Folio::Core::Game::ANastySprite::E,     {   SPRITE_LIZARD_RIGHT_1, SPRITE_LIZARD_RIGHT_2,       },  },
    {   NASTY_SPRITE_LIZARD,        Folio::Core::Game::ANastySprite::W,     {   SPRITE_LIZARD_LEFT_1, SPRITE_LIZARD_LEFT_2,         },  },

    {   NASTY_SPRITE_SNAKE,         Folio::Core::Game::ANastySprite::E,     {   SPRITE_SNAKE_RIGHT_1, SPRITE_SNAKE_RIGHT_2,         },  },
    {   NASTY_SPRITE_SNAKE,         Folio::Core::Game::ANastySprite::W,     {   SPRITE_SNAKE_LEFT_1, SPRITE_SNAKE_LEFT_2,           },  },

    {   NASTY_SPRITE_RAT,           Folio::Core::Game::ANastySprite::E,     {   SPRITE_RAT_RIGHT_1, SPRITE_RAT_RIGHT_2,             },  },
    {   NASTY_SPRITE_RAT,           Folio::Core::Game::ANastySprite::W,     {   SPRITE_RAT_LEFT_1, SPRITE_RAT_LEFT_2,               },  },

    {   NASTY_SPRITE_BIRD,          Folio::Core::Game::ANastySprite::E,     {   SPRITE_BIRD_RIGHT_1, SPRITE_BIRD_RIGHT_2,           },  },
    {   NASTY_SPRITE_BIRD,          Folio::Core::Game::ANastySprite::W,     {   SPRITE_BIRD_LEFT_1, SPRITE_BIRD_LEFT_2,             },  },

    {   NASTY_SPRITE_FLY,           Folio::Core::Game::ANastySprite::E,     {   SPRITE_FLY_RIGHT_1, SPRITE_FLY_RIGHT_2,             },  },
    {   NASTY_SPRITE_FLY,           Folio::Core::Game::ANastySprite::W,     {   SPRITE_FLY_LEFT_1, SPRITE_FLY_LEFT_2,               },  },

    {   NASTY_SPRITE_FROG,          Folio::Core::Game::ANastySprite::E,     {   SPRITE_FROG_RIGHT_1, SPRITE_FROG_RIGHT_2,           },  },
    {   NASTY_SPRITE_FROG,          Folio::Core::Game::ANastySprite::W,     {   SPRITE_FROG_LEFT_1, SPRITE_FROG_LEFT_2,             },  },

    {   NASTY_SPRITE_BUG,           Folio::Core::Game::ANastySprite::E,     {   SPRITE_BUG_RIGHT_1, SPRITE_BUG_RIGHT_2,             },  },
    {   NASTY_SPRITE_BUG,           Folio::Core::Game::ANastySprite::W,     {   SPRITE_BUG_LEFT_1, SPRITE_BUG_LEFT_2,               },  },

    {   NASTY_SPRITE_SKUNK,         Folio::Core::Game::ANastySprite::E,     {   SPRITE_SKUNK_RIGHT_1, SPRITE_SKUNK_RIGHT_2,         },  },
    {   NASTY_SPRITE_SKUNK,         Folio::Core::Game::ANastySprite::W,     {   SPRITE_SKUNK_LEFT_1, SPRITE_SKUNK_LEFT_2,           },  },

    {   NASTY_SPRITE_EARWIG,        Folio::Core::Game::ANastySprite::E,     {   SPRITE_EARWIG_RIGHT_1, SPRITE_EARWIG_RIGHT_2,       },  },
    {   NASTY_SPRITE_EARWIG,        Folio::Core::Game::ANastySprite::W,     {   SPRITE_EARWIG_LEFT_1, SPRITE_EARWIG_LEFT_2,         },  },
};


// Nasty sprite static members.
//IAC NastySprite::SpriteTerminatingSoundSamplesList  NastySprite::m_nastySpriteTerminatingSoundSamplesList;  // The nasty sprite's terminating sound samples.

NastySprite::NastySprite (const PlayerSpritePtr &playerSprite)
:   m_playerSprite(playerSprite),
    m_nastySpriteId(NASTY_SPRITE_UNDEFINED),
    m_nastySpriteSpeed(STATIC_SPEED)
{
} // Endproc.


NastySprite::~NastySprite ()
{
} // Endproc.


FolioStatus NastySprite::Create (FolioHandle                dcHandle,
                                 const SpriteGraphicsMapPtr &spriteGraphicsMap,
                                 NASTY_SPRITE_ID            nastySpriteId,
                                 const CollisionGrid        &collisionGrid)
{
    // Get the nasty sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour = GetNastySpriteColour (nastySpriteId);

    // Query the nasty sprite's graphics.

    SpriteGraphicAttributesList spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      nastySpriteId,
                                                                                                      *spriteGraphicsMap,
                                                                                                      nastySpriteColour,
                                                                                                      g_nastySpriteGraphicAttributes,
                                                                                                      spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Get the nasty sprite's initial screen position.

        Int32   initialScreenXLeft  = FOLIO_UNDEFINED;  // Initialise!
        Int32   initialScreenYTop   = FOLIO_UNDEFINED;

        QueryInitialScreenTopLeft (collisionGrid, initialScreenXLeft, initialScreenYTop);

        // Create the nasty sprite.

        status = Folio::Core::Game::ANastySprite::Create (dcHandle,
                                                          spriteGraphicAttributesList,
                                                          initialScreenXLeft,
                                                          initialScreenYTop,
                                                          Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                          Folio::Core::Game::ZxSpectrum::MapInkColour (nastySpriteColour),
                                                          GetNastySpriteDirection (collisionGrid));

        if (status == ERROR_SUCCESS)
        {
            // Set the nasty sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, 
                                          spriteGraphicsMap, 
                                          nastySpriteColour);

            if (status == ERROR_SUCCESS)
            {
                // Set the nasty sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, 
                                             spriteGraphicsMap, 
                                             nastySpriteColour); 

                if (status == ERROR_SUCCESS)
                {
                    // The nasty sprite is alive.

                    SetAlive ();

                    // Note the nasty sprite's attributes.

                    m_nastySpriteId     = nastySpriteId;
                    m_nastySpriteSpeed  = GetNastySpriteSpeed (nastySpriteId);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus NastySprite::CheckNasty (Folio::Core::Game::DrawingElementPtr   &drawingElement,
                                     Gdiplus::Graphics                      &graphics,
                                     CollisionGrid                          &collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_INITIALISED:
        // Set the nasty sprite's drawing element's collision grid cell value.

        drawingElement->SetCollisionGridCellValue (CollisionGrid::CELL_VALUE_NASTY_SPRITE);

        // The nasty sprite is static.

        status = Static (graphics, collisionGrid);
        break;

    case NastySprite::STATE_STATIC:
    case NastySprite::STATE_MOVING:
        // Move the nasty sprite.

        status = Move (graphics, collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Set the nasty sprite's drawing element's top-left screen position.

            drawingElement->SetScreenTopLeft (m_collisionRect.X, m_collisionRect.Y);

            // Update the nasty sprite in the screen's collision grid.

            status = collisionGrid.UpdateCellElement (*(drawingElement));
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


UInt32  NastySprite::GetCreateNastySpriteTickCount ()
{
    return (Folio::Core::Util::DateTime::GetCurrentTickCount () +
            1000 * Folio::Core::Util::Random::GetRandomNumber (1, 4));
} // Endproc.


NASTY_SPRITE_ID NastySprite::GetNastySpriteToCreate (UInt32 numFoundAmuletPieces)
{
    switch (numFoundAmuletPieces)
    {
    case 1:
        return (static_cast<NASTY_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (NASTY_SPRITE_SPIDER, NASTY_SPRITE_BIRD)));
    
    case 2:
        return (static_cast<NASTY_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (NASTY_SPRITE_SPIDER, NASTY_SPRITE_FROG)));
    
    case 3:
        return (static_cast<NASTY_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (NASTY_SPRITE_SPIDER, NASTY_SPRITE_SKUNK)));
    
    case 4:
        return (static_cast<NASTY_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (NASTY_SPRITE_SPIDER, NASTY_SPRITE_EARWIG)));

    case 0:
    default:
        return (static_cast<NASTY_SPRITE_ID> (Folio::Core::Util::Random::GetRandomNumber (NASTY_SPRITE_SPIDER, NASTY_SPRITE_SNAKE)));
    } // Endswitch.

} // Endproc.


bool    NastySprite::IsRemoveScreenNastySprites (UInt32 exitScreenTickCount)
{
    static  const   UInt32  MAX_REMOVE_NASTY_SPRITES_TICK_COUNT = 10 * 1000;    // The maximum tick count to remove the nasty sprites.

    return (Folio::Core::Util::DateTime::GetCurrentTickCount () > (exitScreenTickCount + MAX_REMOVE_NASTY_SPRITES_TICK_COUNT));
} // Endproc.


FolioStatus NastySprite::SetInitialisingMode (FolioHandle                           dcHandle,
                                              const SpriteGraphicsMapPtr            &spriteGraphicsMap,
                                              Folio::Core::Game::ZxSpectrum::COLOUR nastySpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Nasty sprite initialising sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<NASTY_SPRITE_ID, SPRITE_ID> s_initialisingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::APlayerSprite::ALL_DIRECTIONS,   {   SPRITE_NASTY_ALIVE_1, SPRITE_NASTY_ALIVE_2, SPRITE_NASTY_ALIVE_3, SPRITE_NASTY_ALIVE_4, SPRITE_NASTY_ALIVE_5, SPRITE_NASTY_ALIVE_6, },  },
    };

    // Query the nasty sprite's initialising graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      *spriteGraphicsMap,
                                                                                                      nastySpriteColour,
                                                                                                      s_initialisingSpriteGraphicAttributes,
                                                                                                      spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Set graphic initialising mode.

        status = SetGraphicInitialisingMode (dcHandle,
                                             spriteGraphicAttributesList,
                                             MAX_SEQUENCE_COUNT);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus NastySprite::SetTerminatingMode (FolioHandle                            dcHandle,
                                             const SpriteGraphicsMapPtr             &spriteGraphicsMap,
                                             Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Nasty sprite terminating sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<NASTY_SPRITE_ID, SPRITE_ID> s_terminatingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::APlayerSprite::ALL_DIRECTIONS,   {   SPRITE_NASTY_DEAD_1, SPRITE_NASTY_DEAD_2, SPRITE_NASTY_DEAD_3, SPRITE_NASTY_DEAD_2, SPRITE_NASTY_DEAD_1, SPRITE_NASTY_DEAD_4,   },  },
    };

    // Query the nasty sprite's terminating graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      *spriteGraphicsMap,
                                                                                                      nastySpriteColour,
                                                                                                      s_terminatingSpriteGraphicAttributes,
                                                                                                      spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Set graphic terminating mode.

        status = SetGraphicTerminatingMode (dcHandle,
                                            spriteGraphicAttributesList,
                                            MAX_SEQUENCE_COUNT);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus NastySprite::Move (Gdiplus::Graphics    &graphics,
                               CollisionGrid        &collisionGrid)
{
    // Should the nasty sprite's direction be updated?

    if (IsUpdateNastySpriteDirectionRqd (collisionGrid))
    {
        // Yes. Update the nasty sprite's direction.

        UpdateDirection (GetNastySpriteDirection (collisionGrid));
    } // Endif.

    // Move the nasty sprite.

    return (Folio::Core::Game::ANastySprite::Move (graphics, m_nastySpriteSpeed, collisionGrid));
} // Endproc.


bool    NastySprite::IsUpdateNastySpriteDirectionRqd (const CollisionGrid &collisionGrid)
{
    bool    isUpdateDirectionRqd = true;    // Initialise!

    switch (m_nastySpriteId)
    {
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_LIZARD:             
    case NASTY_SPRITE_SNAKE:             
    case NASTY_SPRITE_BUG: 
        // Move nasty sprite to the main player.

        isUpdateDirectionRqd = true;
        break;
    
    case NASTY_SPRITE_SPIDER:            
    case NASTY_SPRITE_SCORPION:            
    case NASTY_SPRITE_PARROT:            
    case NASTY_SPRITE_MONKEY:             
    case NASTY_SPRITE_RAT:             
    case NASTY_SPRITE_BIRD:             
    case NASTY_SPRITE_FLY:             
    case NASTY_SPRITE_FROG:             
    case NASTY_SPRITE_SKUNK:
    case NASTY_SPRITE_EARWIG: 
    default:
        // The nasty sprite can randomly change direction.
    
        isUpdateDirectionRqd = (Folio::Core::Util::Random::GetRandomNumber (20) == 0);
        break;
    } // Endswitch.

    return (isUpdateDirectionRqd);
} // Endproc.


NastySprite::Direction  NastySprite::GetNastySpriteDirection (const CollisionGrid &collisionGrid)
{  
    Direction  direction = NO_DIRECTION;    // Initialise!

    switch (m_nastySpriteId)
    {
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_LIZARD:             
    case NASTY_SPRITE_SNAKE:             
    case NASTY_SPRITE_BUG: 
        // Move nasty sprite to the player.

        direction = GetDirectionToScreenRect (m_playerSprite->GetCollisionRect (), collisionGrid); 
        break;
    
    case NASTY_SPRITE_SPIDER:            
    case NASTY_SPRITE_SCORPION:            
    case NASTY_SPRITE_PARROT:            
    case NASTY_SPRITE_MONKEY:             
    case NASTY_SPRITE_RAT:             
    case NASTY_SPRITE_BIRD:             
    case NASTY_SPRITE_FLY:             
    case NASTY_SPRITE_FROG:             
    case NASTY_SPRITE_SKUNK:
    case NASTY_SPRITE_EARWIG: 
    default:
        // The nasty sprite can randomly change direction (but NEVER move North or 
        // South - as the player's sword algorithm cannot manage a nasty sprite 
        // hitting the player from either North or South).
    
        switch (Folio::Core::Util::Random::GetRandomNumber (5))
        {
        case 0:
            direction = E;
            break;
    
        case 1:
            direction = W;
            break;
    
        case 2:
            direction = NE;
            break;
    
        case 3:
            direction = NW;
            break;
    
        case 4:
            direction = SE;
            break;
    
        case 5:
            direction = SW;
            break;
    
        default:
            direction = NO_DIRECTION;
            break;
        } // Endswitch.
        break;
    } // Endswitch.

    return (direction);
} // Endproc.


void    NastySprite::QueryInitialScreenTopLeft (const CollisionGrid &collisionGrid,
                                                Int32               &initialScreenXLeft,
                                                Int32               &initialScreenYTop)
{
    static  const   Int32   MAX_NASTY_SPRITE_WIDTH  = 24;
    static  const   Int32   MAX_NASTY_SPRITE_HEIGHT = 24;

    // Make sure the nasty sprite starts on the floor.

    Gdiplus::Rect   spriteScreenRect;
    spriteScreenRect.Width  = MAX_NASTY_SPRITE_WIDTH; 
    spriteScreenRect.Height = MAX_NASTY_SPRITE_HEIGHT; 

    do
    {
        spriteScreenRect.X = GetInitialScreenXLeft (spriteScreenRect.Width, collisionGrid);
        spriteScreenRect.Y = GetInitialScreenYTop (spriteScreenRect.Height, collisionGrid);
    } // Enddo.
    while (collisionGrid.IsWallCollision (CollisionGrid::UP, spriteScreenRect));

    initialScreenXLeft  = spriteScreenRect.X;
    initialScreenYTop   = spriteScreenRect.Y;
} // Endproc.


Int32   NastySprite::GetInitialScreenXLeft (Int32               maxNastySpriteScreenWidth,
                                            const CollisionGrid &collisionGrid)
{
    // Get random initial screen X left position for the nasty sprite.

    return (Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorLeftBound (), 
                                                        collisionGrid.GetFloorRightBound () - maxNastySpriteScreenWidth));
} // Endproc.


Int32   NastySprite::GetInitialScreenYTop (Int32                maxNastySpriteScreenHeight,
                                           const CollisionGrid  &collisionGrid)
{
    // Get random initial screen Y top position for the nasty sprite.

    return (Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorTopBound (), 
                                                        collisionGrid.GetFloorBottomBound () - maxNastySpriteScreenHeight));
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   NastySprite::GetNastySpriteColour (NASTY_SPRITE_ID nastySpriteId)
{
    Folio::Core::Game::ZxSpectrum::COLOUR   nastySpriteColour = Folio::Core::Game::ZxSpectrum::UNDEFINED;

    switch (nastySpriteId)
    {
    case NASTY_SPRITE_SPIDER:            
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::CYAN
                            : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case NASTY_SPRITE_SCORPION:            
        nastySpriteColour = Folio::Core::Game::ZxSpectrum::RED;
        break;

    case NASTY_SPRITE_BAT:                
        nastySpriteColour = Folio::Core::Game::ZxSpectrum::MAGENTA;
        break;

    case NASTY_SPRITE_PARROT:            
        nastySpriteColour = Folio::Core::Game::ZxSpectrum::CYAN;
        break;

    case NASTY_SPRITE_MONKEY:             
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::CYAN
                            : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case NASTY_SPRITE_LIZARD:             
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::RED
                            : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case NASTY_SPRITE_SNAKE:             
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::RED
                            : Folio::Core::Game::ZxSpectrum::MAGENTA;
        break;

    case NASTY_SPRITE_RAT:             
        nastySpriteColour = Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case NASTY_SPRITE_BIRD:             
        nastySpriteColour = Folio::Core::Game::ZxSpectrum::RED;
        break;

    case NASTY_SPRITE_FLY:             
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::RED
                            : Folio::Core::Game::ZxSpectrum::CYAN;
        break;

    case NASTY_SPRITE_FROG:             
        nastySpriteColour = Folio::Core::Game::ZxSpectrum::MAGENTA;
        break;

    case NASTY_SPRITE_BUG: 
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::RED
                            : Folio::Core::Game::ZxSpectrum::MAGENTA;
        break;

    case NASTY_SPRITE_SKUNK:
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::MAGENTA
                            : Folio::Core::Game::ZxSpectrum::YELLOW;
        break;

    case NASTY_SPRITE_EARWIG: 
        nastySpriteColour = Folio::Core::Util::Random::GetRandomNumber (1)
                            ? Folio::Core::Game::ZxSpectrum::MAGENTA
                            : Folio::Core::Game::ZxSpectrum::CYAN;
        break;

    default:
        break;
    } // Endswitch.

    return (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(nastySpriteColour));
} // Endproc.


UInt32  NastySprite::GetNastySpriteSpeed (NASTY_SPRITE_ID nastySpriteId)
{
    // Get random speed for the nasty sprite.

    switch (nastySpriteId)
    {
    case NASTY_SPRITE_SPIDER:            
    case NASTY_SPRITE_SCORPION:            
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_PARROT:            
    case NASTY_SPRITE_MONKEY:             
    case NASTY_SPRITE_LIZARD:             
    case NASTY_SPRITE_SNAKE:             
    case NASTY_SPRITE_RAT:             
    case NASTY_SPRITE_BIRD:             
    case NASTY_SPRITE_FLY:             
    case NASTY_SPRITE_FROG:             
    case NASTY_SPRITE_BUG: 
    case NASTY_SPRITE_SKUNK:
    case NASTY_SPRITE_EARWIG: 
        return (Folio::Core::Util::Random::GetRandomNumber (1, 3));
    
    default:
        return (STATIC_SPEED);
    } // Endswitch.

} // Endproc.


//IAC
//NastySprite::SpriteTerminatingSoundSamplesList  NastySprite::GetNastySpriteTerminatingSoundSamples ()
//{
//    if (m_nastySpriteTerminatingSoundSamplesList.empty ())
//    {
//        // Create each sound sample representing the required sound.
//    
//        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x3f; frequency >= 0x21; frequency -= 2)
//        {
//            m_nastySpriteTerminatingSoundSamplesList.push_back (Ultimate::MapMakeSound (frequency, 0x01));
//        } // Endfor.
//
//    } // Endif.
//    
//    return (m_nastySpriteTerminatingSoundSamplesList);
//} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
