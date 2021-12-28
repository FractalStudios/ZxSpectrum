// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "NastySprite.h"
#include    "ResourceOwnerIds.h"
#include    "ScreenMap.h"
#include    "SpriteGraphics.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Nasty sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<NASTY_SPRITE_ID, SPRITE_ID> g_nastySpriteGraphicCharacteristics =
{
//      m_spriteId                  m_direction             m_spriteGraphicIdsList
    {   NASTY_SPRITE_SPIDER,        Folio::Core::Game::E,   {   SPRITE_SPIDER_RIGHT_1, SPRITE_SPIDER_RIGHT_2,       },  },
    {   NASTY_SPRITE_SPIDER,        Folio::Core::Game::W,   {   SPRITE_SPIDER_LEFT_1, SPRITE_SPIDER_LEFT_2,         },  },

    {   NASTY_SPRITE_SCORPION,      Folio::Core::Game::E,   {   SPRITE_SCORPION_RIGHT_1, SPRITE_SCORPION_RIGHT_2,   },  },
    {   NASTY_SPRITE_SCORPION,      Folio::Core::Game::W,   {   SPRITE_SCORPION_LEFT_1, SPRITE_SCORPION_LEFT_2,     },  },

    {   NASTY_SPRITE_BAT,           Folio::Core::Game::E,   {   SPRITE_BAT_RIGHT_1, SPRITE_BAT_RIGHT_2,             },  },
    {   NASTY_SPRITE_BAT,           Folio::Core::Game::W,   {   SPRITE_BAT_LEFT_1, SPRITE_BAT_LEFT_2,               },  },

    {   NASTY_SPRITE_PARROT,        Folio::Core::Game::E,   {   SPRITE_PARROT_RIGHT_1, SPRITE_PARROT_RIGHT_2,       },  },
    {   NASTY_SPRITE_PARROT,        Folio::Core::Game::W,   {   SPRITE_PARROT_LEFT_1, SPRITE_PARROT_LEFT_2,         },  },

    {   NASTY_SPRITE_MONKEY,        Folio::Core::Game::E,   {   SPRITE_MONKEY_RIGHT_1, SPRITE_MONKEY_RIGHT_2,       },  },
    {   NASTY_SPRITE_MONKEY,        Folio::Core::Game::W,   {   SPRITE_MONKEY_LEFT_1, SPRITE_MONKEY_LEFT_2,         },  },

    {   NASTY_SPRITE_LIZARD,        Folio::Core::Game::E,   {   SPRITE_LIZARD_RIGHT_1, SPRITE_LIZARD_RIGHT_2,       },  },
    {   NASTY_SPRITE_LIZARD,        Folio::Core::Game::W,   {   SPRITE_LIZARD_LEFT_1, SPRITE_LIZARD_LEFT_2,         },  },

    {   NASTY_SPRITE_SNAKE,         Folio::Core::Game::E,   {   SPRITE_SNAKE_RIGHT_1, SPRITE_SNAKE_RIGHT_2,         },  },
    {   NASTY_SPRITE_SNAKE,         Folio::Core::Game::W,   {   SPRITE_SNAKE_LEFT_1, SPRITE_SNAKE_LEFT_2,           },  },

    {   NASTY_SPRITE_RAT,           Folio::Core::Game::E,   {   SPRITE_RAT_RIGHT_1, SPRITE_RAT_RIGHT_2,             },  },
    {   NASTY_SPRITE_RAT,           Folio::Core::Game::W,   {   SPRITE_RAT_LEFT_1, SPRITE_RAT_LEFT_2,               },  },

    {   NASTY_SPRITE_BIRD,          Folio::Core::Game::E,   {   SPRITE_BIRD_RIGHT_1, SPRITE_BIRD_RIGHT_2,           },  },
    {   NASTY_SPRITE_BIRD,          Folio::Core::Game::W,   {   SPRITE_BIRD_LEFT_1, SPRITE_BIRD_LEFT_2,             },  },

    {   NASTY_SPRITE_FLY,           Folio::Core::Game::E,   {   SPRITE_FLY_RIGHT_1, SPRITE_FLY_RIGHT_2,             },  },
    {   NASTY_SPRITE_FLY,           Folio::Core::Game::W,   {   SPRITE_FLY_LEFT_1, SPRITE_FLY_LEFT_2,               },  },

    {   NASTY_SPRITE_FROG,          Folio::Core::Game::E,   {   SPRITE_FROG_RIGHT_1, SPRITE_FROG_RIGHT_2,           },  },
    {   NASTY_SPRITE_FROG,          Folio::Core::Game::W,   {   SPRITE_FROG_LEFT_1, SPRITE_FROG_LEFT_2,             },  },

    {   NASTY_SPRITE_BUG,           Folio::Core::Game::E,   {   SPRITE_BUG_RIGHT_1, SPRITE_BUG_RIGHT_2,             },  },
    {   NASTY_SPRITE_BUG,           Folio::Core::Game::W,   {   SPRITE_BUG_LEFT_1, SPRITE_BUG_LEFT_2,               },  },

    {   NASTY_SPRITE_SKUNK,         Folio::Core::Game::E,   {   SPRITE_SKUNK_RIGHT_1, SPRITE_SKUNK_RIGHT_2,         },  },
    {   NASTY_SPRITE_SKUNK,         Folio::Core::Game::W,   {   SPRITE_SKUNK_LEFT_1, SPRITE_SKUNK_LEFT_2,           },  },

    {   NASTY_SPRITE_EARWIG,        Folio::Core::Game::E,   {   SPRITE_EARWIG_RIGHT_1, SPRITE_EARWIG_RIGHT_2,       },  },
    {   NASTY_SPRITE_EARWIG,        Folio::Core::Game::W,   {   SPRITE_EARWIG_LEFT_1, SPRITE_EARWIG_LEFT_2,         },  },
};


NastySprite::NastySprite ()
:   m_nastySpriteId(NASTY_SPRITE_UNDEFINED),
    m_nastySpriteScreenMapIndex(ScreenMap::UNDEFINED_SCREEN_INDEX),
    m_nastySpriteSpeed(STATIC_SPEED)
{
} // Endproc.


NastySprite::~NastySprite ()
{
} // Endproc.


FolioStatus NastySprite::Create (FolioHandle            dcHandle,
                                 NASTY_SPRITE_ID        nastySpriteId,
                                 UInt32                 currentScreenMapIndex,
                                 const CollisionGrid&   collisionGrid)
{
    // Get the nasty sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour = GetNastySpriteColour (nastySpriteId);

    // Query the nasty sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      g_resourceGraphicsCache,
                                                                                                      Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_NASTY_SPRITE,
                                                                                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,
                                                                                                      nastySpriteId,
                                                                                                      nastySpriteColour,
                                                                                                      g_nastySpriteGraphicCharacteristics,
                                                                                                      spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
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
                                                          GetNastySpriteDirection (collisionGrid),
                                                          &(g_resourceGraphicsCache));

        if (status == ERR_SUCCESS)
        {
            // Set the nasty sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, nastySpriteColour);

            if (status == ERR_SUCCESS)
            {
                // Set the nasty sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, nastySpriteColour); 

                if (status == ERR_SUCCESS)
                {
                    // Note the nasty sprite's attributes.

                    m_nastySpriteId             = nastySpriteId;
                    m_nastySpriteScreenMapIndex = currentScreenMapIndex;
                    m_nastySpriteSpeed          = GetNastySpriteSpeed (nastySpriteId);

                    // The nasty sprite is alive.

                    SetAlive ();
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus NastySprite::CheckNastySprite (Folio::Core::Game::DrawingElementPtr&    drawingElement,
                                           Gdiplus::Graphics&                       graphics,
                                           CollisionGrid&                           collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_INITIALISED:
        // The nasty sprite is initialised.

        // Set the nasty sprite's drawing element's collision grid cell value.

        drawingElement->SetCollisionGridCellValue (CollisionGrid::CELL_VALUE_NASTY_SPRITE);

        // The nasty sprite is static.

        status = Static (graphics, collisionGrid);
        break;

    case STATE_TERMINATED:
        // The nasty sprite is terminated.
        break;

    case STATE_STATIC:
    case STATE_MOVING:
        // Move the nasty sprite.

        status = Move (graphics, collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Set the nasty sprite's drawing element's top-left screen position.

            status = drawingElement->SetScreenTopLeft (m_collisionRect.X, m_collisionRect.Y);

            if (status == ERR_SUCCESS)
            {
                // Update the nasty sprite in the current screen's collision grid.

                status = collisionGrid.UpdateCellElement (*(drawingElement));
            } // Endif.

        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


NASTY_SPRITE_ID   NastySprite::GetNastySpriteId () const
{
    return (m_nastySpriteId);
} // Endproc.


UInt32  NastySprite::GetNastySpriteScreenMapIndex () const
{
    return (m_nastySpriteScreenMapIndex);
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


FolioStatus NastySprite::SetInitialisingMode (FolioHandle                           dcHandle,
                                              Folio::Core::Game::ZxSpectrum::COLOUR nastySpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Nasty sprite initialising sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<NASTY_SPRITE_ID, SPRITE_ID> s_initialisingSpriteGraphicCharacteristics = 
    {
    //      m_spriteId                  m_direction                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_NASTY_ALIVE_1, SPRITE_NASTY_ALIVE_2, SPRITE_NASTY_ALIVE_3, SPRITE_NASTY_ALIVE_4, SPRITE_NASTY_ALIVE_5, SPRITE_NASTY_ALIVE_6, },  },
    };

    // Query the nasty sprite's initialising graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      g_resourceGraphicsCache,
                                                                                                      Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_NASTY_SPRITE,
                                                                                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,
                                                                                                      nastySpriteColour,
                                                                                                      s_initialisingSpriteGraphicCharacteristics,
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
                                             Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Nasty sprite terminating sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<NASTY_SPRITE_ID, SPRITE_ID> s_terminatingSpriteGraphicCharacteristics = 
    {
    //      m_spriteId                  m_direction                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_NASTY_DEAD_1, SPRITE_NASTY_DEAD_2, SPRITE_NASTY_DEAD_3, SPRITE_NASTY_DEAD_2, SPRITE_NASTY_DEAD_1, SPRITE_NASTY_DEAD_4,   },  },
    };

    // Query the nasty sprite's terminating graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      g_resourceGraphicsCache,
                                                                                                      Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_NASTY_SPRITE,
                                                                                                      Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE,
                                                                                                      nastySpriteColour,
                                                                                                      s_terminatingSpriteGraphicCharacteristics,
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


FolioStatus NastySprite::Move (Gdiplus::Graphics&   graphics,
                               CollisionGrid&       collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Should the nasty sprite's direction be updated?

    if (IsUpdateNastySpriteDirectionRqd (collisionGrid))
    {
        // Yes. Set the nasty sprite's direction.

        status = SetDirection (GetNastySpriteDirection (collisionGrid));
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Move the nasty sprite.

        status = Folio::Core::Game::ANastySprite::Move (graphics, m_nastySpriteSpeed, collisionGrid);
    } // Endif.

    return (status);
} // Endproc.


bool    NastySprite::IsUpdateNastySpriteDirectionRqd (const CollisionGrid& collisionGrid)
{
    bool    isUpdateDirectionRqd = true;    // Initialise!

    switch (m_nastySpriteId)
    {
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_LIZARD:             
    case NASTY_SPRITE_SNAKE:             
    case NASTY_SPRITE_BUG: 
        // Move nasty sprite to the player.

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


Folio::Core::Game::Direction    NastySprite::GetNastySpriteDirection (const CollisionGrid& collisionGrid)
{  
    Folio::Core::Game::Direction    direction = Folio::Core::Game::NO_DIRECTION;    // Initialise!

    switch (m_nastySpriteId)
    {
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_LIZARD:             
    case NASTY_SPRITE_SNAKE:             
    case NASTY_SPRITE_BUG: 
        // Move nasty sprite to the player.

        direction = GetDirectionToScreenRect (g_playerSprite->GetCollisionRect (), 
                                              collisionGrid); 
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
        // The nasty sprite can randomly change direction (but NEVER move north or 
        // south - as the player sprite's sword algorithm cannot manage a nasty sprite 
        // hitting the player from either north or south).
    
        switch (Folio::Core::Util::Random::GetRandomNumber (5))
        {
        case 0:
            direction = Folio::Core::Game::E;
            break;
    
        case 1:
            direction = Folio::Core::Game::W;
            break;
    
        case 2:
            direction = Folio::Core::Game::NE;
            break;
    
        case 3:
            direction = Folio::Core::Game::NW;
            break;
    
        case 4:
            direction = Folio::Core::Game::SE;
            break;
    
        case 5:
            direction = Folio::Core::Game::SW;
            break;
    
        default:
            direction = Folio::Core::Game::NO_DIRECTION;
            break;
        } // Endswitch.
        break;
    } // Endswitch.

    return (direction);
} // Endproc.


void    NastySprite::QueryInitialScreenTopLeft (const CollisionGrid&    collisionGrid,
                                                Int32&                  initialScreenXLeft,
                                                Int32&                  initialScreenYTop)
{
    static  const   Int32   MAX_NASTY_SPRITE_WIDTH  = 24;
    static  const   Int32   MAX_NASTY_SPRITE_HEIGHT = 24;

    // Make sure the nasty sprite starts on the floor.

    Gdiplus::Rect   spriteScreenRect(0, 0, MAX_NASTY_SPRITE_WIDTH, MAX_NASTY_SPRITE_HEIGHT);

    do
    {
        spriteScreenRect.X = GetInitialScreenXLeft (spriteScreenRect.Width, collisionGrid);
        spriteScreenRect.Y = GetInitialScreenYTop (spriteScreenRect.Height, collisionGrid);
    } // Enddo.
    while (collisionGrid.IsWallCollision (CollisionGrid::UP, spriteScreenRect));

    initialScreenXLeft  = spriteScreenRect.X;
    initialScreenYTop   = spriteScreenRect.Y;
} // Endproc.


Int32   NastySprite::GetInitialScreenXLeft (Int32                   maxNastySpriteScreenWidth,
                                            const CollisionGrid&    collisionGrid)
{
    // Get random initial screen X left position for the nasty sprite.

    return (Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorLeftBound (), 
                                                        collisionGrid.GetFloorRightBound () - maxNastySpriteScreenWidth));
} // Endproc.


Int32   NastySprite::GetInitialScreenYTop (Int32                maxNastySpriteScreenHeight,
                                           const CollisionGrid& collisionGrid)
{
    // Get random initial screen Y top position for the nasty sprite.

    return (Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorTopBound (), 
                                                        collisionGrid.GetFloorBottomBound () - maxNastySpriteScreenHeight));
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   NastySprite::GetNastySpriteColour (NASTY_SPRITE_ID nastySpriteId)
{
    Folio::Core::Game::ZxSpectrum::COLOUR   nastySpriteColour = Folio::Core::Game::ZxSpectrum::UNDEFINED;   // Initialise!

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


static  void    SetScreenAddNastySpriteTickCount (UInt32    currentTickCount,
                                                  UInt32&   screenAddNastySpriteTickCount)
{
    screenAddNastySpriteTickCount = currentTickCount + 
                                    500 * Folio::Core::Util::Random::GetRandomNumber (1, 4);
} // Endproc.


static  FolioStatus CheckRemoveNastySpriteDrawingElement (UInt32 currentScreenMapIndex)
{
    FolioStatus status = ERR_SUCCESS;

    // Have the maximum number of nasty sprite drawing elements been added to 
    // the nasty sprite drawing elements list?

    if (g_nastySpriteDrawingElementsList.size () >= MAX_NASTY_SPRITE_DRAWING_ELEMENTS)
    {
        // Yes. Find the oldest nasty sprite drawing element that is not on the 
        // current screen.

        NastySpriteDrawingElementsList::iterator    oldestDrawingElementItr = g_nastySpriteDrawingElementsList.begin ();

        UInt32  oldestTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();  // Initialise!

        bool    found = false; // Initialise!

        for (NastySpriteDrawingElementsList::iterator itr = oldestDrawingElementItr;
             itr != g_nastySpriteDrawingElementsList.end ();
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is this nasty sprite NOT on the current screen and older than 
            // the current oldest nasty sprite?

            if ((nastySprite->GetNastySpriteScreenMapIndex () != currentScreenMapIndex) && 
                (itr->m_createdTickCount < oldestTickCount))
            {
                // Yes. Note the nasty sprite drawing element.

                oldestDrawingElementItr = itr;

                found = true;
            } // Endif.

        } // Endfor.

        if (found)
        {
            // Remove the oldest nasty sprite drawing element from the nasty 
            // sprite drawing elements list.
    
            g_nastySpriteDrawingElementsList.erase (oldestDrawingElementItr);
        } // Endif.

        else
        {
            status = ERR_IN_USE;
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.


static  FolioStatus AddScreenNastySprite (FolioHandle       dcHandle,
                                          NASTY_SPRITE_ID   nastySpriteId,
                                          UInt32            currentScreenMapIndex,
                                          CollisionGrid&    collisionGrid)
{
    // Check if a nasty sprite drawing element should be removed from the nasty 
    // sprite drawing elements list.

    FolioStatus status = CheckRemoveNastySpriteDrawingElement (currentScreenMapIndex);

    if (status == ERR_SUCCESS)
    {
        // Create the nasty sprite.

        NastySpritePtr  nastySprite(new NastySpritePtr::element_type);
    
        status = nastySprite->Create (dcHandle, 
                                      nastySpriteId, 
                                      currentScreenMapIndex,
                                      collisionGrid);
       
        if (status == ERR_SUCCESS)
        {
            // Create a nasty sprite drawing element.

            NastySpriteDrawingElement   nastySpriteDrawingElement(Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_NASTY_SPRITE, 
                                                                  nastySprite,
                                                                  nastySprite->GetCollisionGridCellValue ());

            // Add the nasty sprite to the current screen's collision grid.

            status = collisionGrid.AddCellElement (*(nastySpriteDrawingElement.m_drawingElement));

            if (status == ERR_SUCCESS)
            {
                // Add the nasty sprite drawing element to the nasty sprite drawing 
                // elements list.

                g_nastySpriteDrawingElementsList.push_back (nastySpriteDrawingElement);
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


static  bool    IsRemoveScreenNastySprites (UInt32 exitScreenTickCount)
{
    static  const   UInt32  MAX_REMOVE_NASTY_SPRITES_TICK_COUNT = 10 * 1000;    // The maximum tick count to remove the nasty sprites.

    return (exitScreenTickCount &&
            (Folio::Core::Util::DateTime::GetCurrentTickCount () > (exitScreenTickCount + MAX_REMOVE_NASTY_SPRITES_TICK_COUNT)));
} // Endproc.


static  FolioStatus RemoveScreenNastySprites (UInt32            currentScreenMapIndex,
                                              bool              onScreenEntry, 
                                              CollisionGrid&    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Are there any created nasty sprite drawing elements?

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Yes. Remove all the nasty sprites on the current screen.

        NastySpriteDrawingElementsList::iterator    itr = g_nastySpriteDrawingElementsList.begin ();

        do
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on the current screen?

            if (nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex)
            {
                // Yes. Remove the nasty sprite from the current screen's 
                // collision grid.

                status = collisionGrid.RemoveCellElement (*(itr->m_drawingElement));

                if (status == ERR_SUCCESS)
                {
                    if (onScreenEntry)
                    {
                        // Remove the nasty sprite from the nasty sprite drawing 
                        // elements list.

                        itr = g_nastySpriteDrawingElementsList.erase (itr);
                    } // Endif.

                    else
                    {
                        // The nasty sprite is dead.

                        nastySprite->SetDead (false); // Don't play its terminating sound.
                        
                        ++itr;  // Next nasty sprite.
                    } // Endelse.

                } // Endif.
            
            } // Endif.

            else
            {
                // No.

                ++itr;  // Next nasty sprite.
            } // Endelse.

        } // Enddo.
        while ((status == ERR_SUCCESS) && 
               (itr != g_nastySpriteDrawingElementsList.end ()));
    } // Endif.

    return (status);
} // Endproc.


static  UInt32  GetNumNastySpritesOnScreen (UInt32 currentScreenMapIndex)
{
    UInt32  numNastySpritesOnScreen = 0;    // Initialise!

    // Are there any created nasty sprite drawing elements?

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Yes. Count all the nasty sprites on the current screen.

        for (NastySpriteDrawingElementsList::const_iterator itr = g_nastySpriteDrawingElementsList.begin ();
             itr != g_nastySpriteDrawingElementsList.end ();
             ++itr)
        {
            // Get the nasty sprite.

            const NastySpritePtr    &nastySprite(itr->m_sprite);

            // Is the nasty sprite on the current screen?

            if (nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex)
            {
                // Yes.

                numNastySpritesOnScreen++;
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (numNastySpritesOnScreen);
} // Endproc.


static  FolioStatus StartScreenNastySprites (FolioHandle        dcHandle,
                                             Gdiplus::Graphics& graphics,
                                             UInt32             currentScreenMapIndex,
                                             UInt32             numNastySpritesOnScreen,
                                             CollisionGrid&     collisionGrid,
                                             UInt32&            screenAddNastySpriteTickCount)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current tick count.

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    // Have we already started the add nasty tick count for the current screen.

    if (screenAddNastySpriteTickCount)
    {
        // Yes. Should we add a nasty sprite to the current screen?

        //if (currentTickCount >= screenAddNastySpriteTickCount)
        {
            // Yes. Calculate the number of nasty sprites to add to the current 
            // screen.

            UInt32  numNastySpritesToAdd =MAX_NASTY_SPRITES_PER_SCREEN - numNastySpritesOnScreen; 
                //Folio::Core::Util::Random::GetRandomNumber(1, MAX_NASTY_SPRITES_PER_SCREEN - numNastySpritesOnScreen);

            for (UInt32 nastySpriteCount = 0; 
                 (status == ERR_SUCCESS) && (nastySpriteCount < numNastySpritesToAdd); 
                 ++nastySpriteCount)
            {
                // Add a nasty sprite to the screen.

                status = AddScreenNastySprite (dcHandle,
                                               NastySprite::GetNastySpriteToCreate (g_informationPanel->GetNumFoundAmuletPieces ()), 
                                               currentScreenMapIndex,
                                               collisionGrid);
            } // Endfor.

            //if (status == ERR_SUCCESS)
            //{
            //    // Restart the add nasty sprite tick count for the current 
            //    // screen.

            //    SetScreenAddNastySpriteTickCount (currentTickCount, 
            //                                      screenAddNastySpriteTickCount);
            //} // Endif.

        } // Endif.

    } // Endif.

    else
    {
        // No. Start the add nasty sprite tick count for the current screen.

        SetScreenAddNastySpriteTickCount (currentTickCount, 
                                          screenAddNastySpriteTickCount);
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus UpdateScreenNastySprites (UInt32            exitScreenTickCount,
                                      CollisionGrid&    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;
  
    // Are there any created nasty sprite drawing elements?

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Yes. Should the current screen's nasty sprites be removed?

        if (IsRemoveScreenNastySprites (exitScreenTickCount))
        {
            // Yes. Remove the current screen's nasty sprites.

            status = RemoveScreenNastySprites (g_screenMap.GetCurrentScreenMapIndex (),
                                               true,    // On screen entry. 
                                               collisionGrid);
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus CheckScreenNastySprites (FolioHandle        dcHandle,
                                     Gdiplus::Graphics& graphics,
                                     CollisionGrid&     collisionGrid,
                                     UInt32&            screenAddNastySpriteTickCount)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the player ready and not sick?

    if (g_playerSprite->IsReady () &&  
        !g_playerSprite->IsSick ())
    {
        // Yes. Get the current screen map index.

        UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

        // Have we created all the nasty sprites for the current screen?

        UInt32  numNastySpritesOnScreen = GetNumNastySpritesOnScreen (currentScreenMapIndex);

        if (numNastySpritesOnScreen < MAX_NASTY_SPRITES_PER_SCREEN)
        {
            // No. Start any nasty sprites.

            status = StartScreenNastySprites (dcHandle,
                                              graphics, 
                                              currentScreenMapIndex,
                                              numNastySpritesOnScreen, 
                                              collisionGrid,
                                              screenAddNastySpriteTickCount);
        } // Endif.

        // Are there any created nasty sprite drawing elements?
    
        if ((status == ERR_SUCCESS) && 
            !g_nastySpriteDrawingElementsList.empty ())
        {
            // Yes. Check all the nasty sprites for the current screen.

            NastySpriteDrawingElementsList::iterator    itr = g_nastySpriteDrawingElementsList.begin ();

            do
            {
                // Get the nasty sprite.

                const NastySpritePtr    &nastySprite(itr->m_sprite);

                // Is the nasty sprite on the current screen?

                if (nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex)
                {
                    // Yes. Check the nasty sprite.

                    status = nastySprite->CheckNastySprite (itr->m_drawingElement, 
                                                            graphics, 
                                                            collisionGrid);

                    // Is the nasty sprite dead?

                    if (nastySprite->IsDead ())
                    {
                        // Yes. Remove it from the nasty sprites drawing elements list.

                        itr = g_nastySpriteDrawingElementsList.erase (itr);
                    } // Endif.
                
                    else
                    {
                        ++itr;  // Next nasty sprite.
                    } // Endelse.
                
                } // Endif.

                else
                {
                    ++itr;  // Next nasty sprite.
                } // Endelse.
                
            } // Enddo.
            while ((status == ERR_SUCCESS) && 
                   (itr != g_nastySpriteDrawingElementsList.end ()));
        } // Endif.
 
    } // Endif.

    return (status);
} // Endproc.


FolioStatus RemoveScreenNastySprites (CollisionGrid& collisionGrid)
{
    // Remove the current screen's nasty sprites.

    return (RemoveScreenNastySprites (g_screenMap.GetCurrentScreenMapIndex (), 
                                      false,    // Not on screen entry. 
                                      collisionGrid));
} // Endproc.


FolioStatus StoreNastySpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Are there any created nasty sprite drawing elements?

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Yes. Get the current screen map index.

        UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

        // Store all the nasty sprites' backgrounds for the current screen.

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on the current screen?

            if (nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex)
            {
                // Yes. Store the nasty sprite's background.

                status = nastySprite->StoreUnderlyingBackground (graphics);
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus RestoreNastySpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Are there any created nasty sprite drawing elements?

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Yes. Get the current screen map index.

        UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

        // Restore all the nasty sprites' backgrounds for the current screen.

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on the current screen?

            if (nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex)
            {
                // Yes. Restore the nasty sprite's background.

                status = nastySprite->RestoreUnderlyingBackground (graphics);
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus DrawNastySprites (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Are there any created nasty sprite drawing elements?

    if (!g_nastySpriteDrawingElementsList.empty ())
    {
        // Yes. Get the current screen map index.

        UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

        // Draw all the nasty sprites for the current screen.

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on the current screen?

            if (nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex)
            {
                // Yes. Draw the nasty sprite.

                status = nastySprite->Draw (graphics);
            } // Endif.

        } // Endfor.
    
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
