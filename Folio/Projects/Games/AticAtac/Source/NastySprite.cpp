// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "NastySprite.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Nasty sprite graphic attributes.
static  const   Folio::Core::Game::SpriteGraphicsAttributesList<NASTY_SPRITE_ID, SPRITE_ID> g_nastySpriteGraphicAttributes =
{
//      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
    {   NASTY_SPRITE_PUMPKIN,       Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_PUMPKIN_1, SPRITE_PUMPKIN_2,                         },  },    
    {   NASTY_SPRITE_SPIDER,        Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_SPIDER_1, SPRITE_SPIDER_2,                           },  },    
    {   NASTY_SPRITE_GHOST,         Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_GHOST_1, SPRITE_GHOST_2,                             },  },    
    {   NASTY_SPRITE_BOUNCY,        Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_BOUNCY_1, SPRITE_BOUNCY_2,                           },  },    
    {   NASTY_SPRITE_SMORPH,        Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_SMORPH_1, SPRITE_SMORPH_2,                           },  },    
    {   NASTY_SPRITE_JELLY_GHOUL,   Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_JELLY_GHOUL_1, SPRITE_JELLY_GHOUL_2,                 },  },    
    {   NASTY_SPRITE_BAT,           Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_BAT_1, SPRITE_BAT_2,                                 },  },    
    {   NASTY_SPRITE_GHOUL,         Folio::Core::Game::ANastySprite::ALL_DIRECTIONS,    {   SPRITE_GHOUL_1, SPRITE_GHOUL_2,                             },  },    

    {   NASTY_SPRITE_WITCH_FLYING,  Folio::Core::Game::ANastySprite::E,                 {   SPRITE_WITCH_FLYING_RIGHT_1, SPRITE_WITCH_FLYING_RIGHT_2,   },  },
    {   NASTY_SPRITE_WITCH_FLYING,  Folio::Core::Game::ANastySprite::W,                 {   SPRITE_WITCH_FLYING_LEFT_1, SPRITE_WITCH_FLYING_LEFT_2,     },  },

    {   NASTY_SPRITE_GHOUL_FLYING,  Folio::Core::Game::ANastySprite::E,                 {   SPRITE_GHOUL_FLYING_RIGHT_1, SPRITE_GHOUL_FLYING_RIGHT_2,   },  },
    {   NASTY_SPRITE_GHOUL_FLYING,  Folio::Core::Game::ANastySprite::W,                 {   SPRITE_GHOUL_FLYING_LEFT_1, SPRITE_GHOUL_FLYING_LEFT_2,     },  },

    {   NASTY_SPRITE_BAT_FLYING,    Folio::Core::Game::ANastySprite::E,                 {   SPRITE_BAT_FLYING_RIGHT_1, SPRITE_BAT_FLYING_RIGHT_2,       },  },
    {   NASTY_SPRITE_BAT_FLYING,    Folio::Core::Game::ANastySprite::W,                 {   SPRITE_BAT_FLYING_LEFT_1, SPRITE_BAT_FLYING_LEFT_2,         },  },
};


// Nasty sprite static members.
NastySprite::SpriteTerminatingSoundSamplesList  NastySprite::m_nastySpriteTerminatingSoundSamplesList;  // The nasty sprite's terminating sound samples.

NastySprite::NastySprite ()
:   m_nastySpriteId(NASTY_SPRITE_UNDEFINED),
    m_nastySpriteFlags(FLAGS_NONE),
    m_nastySpriteSpeed(STATIC_SPEED)
{
} // Endproc.


NastySprite::~NastySprite ()
{
} // Endproc.


FolioStatus NastySprite::Create (FolioHandle                dcHandle,
                                 NASTY_SPRITE_ID            nastySpriteId,
                                 const SpriteGraphicsMap    &spriteGraphicsMap,
                                 const CollisionGrid        &collisionGrid,
                                 UInt32                     nastySpriteFlags)
{
    // Get the nasty sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour = GetColour (nastySpriteId);

    // Query the nasty sprite's graphics.

    SpriteGraphicAttributesList spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      nastySpriteId,
                                                                                                      spriteGraphicsMap,
                                                                                                      nastySpriteColour,
                                                                                                      g_nastySpriteGraphicAttributes,
                                                                                                      spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Create the nasty sprite.

        status = Folio::Core::Game::ANastySprite::Create (dcHandle,
                                                          spriteGraphicAttributesList,
                                                          GetInitialScreenXLeft (collisionGrid),
                                                          GetInitialScreenYTop (collisionGrid),
                                                          Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                          Folio::Core::Game::ZxSpectrum::MapInkColour (nastySpriteColour),
                                                          GetDirection (nastySpriteId));

        if (status == ERROR_SUCCESS)
        {
            // Set the nasty sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, 
                                          spriteGraphicsMap, 
                                          nastySpriteColour,
                                          nastySpriteFlags);

            if (status == ERROR_SUCCESS)
            {
                // Set the nasty sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, 
                                             spriteGraphicsMap, 
                                             nastySpriteColour,
                                             nastySpriteFlags); 

                if (status == ERROR_SUCCESS)
                {
                    // Note the nasty sprite's attributes.

                    m_nastySpriteId     = nastySpriteId;
                    m_nastySpriteFlags  = nastySpriteFlags;
                    m_nastySpriteSpeed  = GetSpeed (nastySpriteId);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus NastySprite::Move (Gdiplus::Graphics    &graphics,
                               CollisionGrid        &collisionGrid)
{
    // Should the nasty sprite's direction be updated?

    if (IsUpdateDirectionRqd (m_nastySpriteId))
    {
        // Yes. Update the nasty sprite's direction.

        UpdateDirection (GetDirection (m_nastySpriteId));
    } // Endif.

    // Move the nasty sprite.

    return (Folio::Core::Game::ANastySprite::Move (graphics, m_nastySpriteSpeed, collisionGrid));
} // Endproc.


NASTY_SPRITE_ID   NastySprite::GetNastySpriteId () const
{
    return (m_nastySpriteId);
} // Endproc.


UInt32  NastySprite::GetNastySpriteFlags () const
{
    return (m_nastySpriteFlags);
} // Endproc.
       

bool    NastySprite::IsInitialisedByGraphic (UInt32 nastySpriteflags)
{
    return ((nastySpriteflags & FLAGS_INITIALISED_BY_GRAPHIC) == FLAGS_INITIALISED_BY_GRAPHIC);
} // Endproc.
       

bool    NastySprite::IsTerminatedByGraphic (UInt32 nastySpriteflags)
{
    return ((nastySpriteflags & FLAGS_TERMINATED_BY_GRAPHIC) == FLAGS_TERMINATED_BY_GRAPHIC);
} // Endproc.
      

FolioStatus NastySprite::QueryNastySpriteInitialisingGraphics (FolioHandle                              dcHandle,
                                                               const SpriteGraphicsMap                  &spriteGraphicsMap,
                                                               Folio::Core::Game::ZxSpectrum::COLOUR    nastySpriteColour,
                                                               SpriteGraphicAttributesList              &spriteGraphicAttributesList)
{
    // Nasty sprite initialising sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<NASTY_SPRITE_ID, SPRITE_ID> s_initialisingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::APlayerSprite::ALL_DIRECTIONS,   {   SPRITE_NASTY_ALIVE_1, SPRITE_NASTY_ALIVE_2, SPRITE_NASTY_ALIVE_3, SPRITE_NASTY_ALIVE_4, },  },
    };

    return (Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                         spriteGraphicsMap,
                                                                                         nastySpriteColour,
                                                                                         s_initialisingSpriteGraphicAttributes,
                                                                                         spriteGraphicAttributesList));
} // Endproc.


FolioStatus NastySprite::QueryNastySpriteTerminatingGraphics (FolioHandle                           dcHandle,
                                                              const SpriteGraphicsMap               &spriteGraphicsMap,
                                                              Folio::Core::Game::ZxSpectrum::COLOUR nastySpriteColour,
                                                              SpriteGraphicAttributesList           &spriteGraphicAttributesList)
{
    // Nasty sprite terminating sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<NASTY_SPRITE_ID, SPRITE_ID> s_terminatingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::APlayerSprite::ALL_DIRECTIONS,   {   SPRITE_NASTY_DEAD_1, SPRITE_NASTY_DEAD_2, SPRITE_NASTY_DEAD_3, SPRITE_NASTY_DEAD_4, },  },
    };

    return (Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                         spriteGraphicsMap,
                                                                                         nastySpriteColour,
                                                                                         s_terminatingSpriteGraphicAttributes,
                                                                                         spriteGraphicAttributesList));
} // Endproc.


FolioStatus NastySprite::SetInitialisingMode (FolioHandle                           dcHandle,
                                              const SpriteGraphicsMap               &spriteGraphicsMap,
                                              Folio::Core::Game::ZxSpectrum::COLOUR nastySpriteColour,
                                              UInt32                                nastySpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 7;

    FolioStatus status = ERR_SUCCESS;

    // Is the nasty sprite initialised by graphic?

    if (IsInitialisedByGraphic (nastySpriteFlags))
    {
        // Yes. Query the nasty sprite's initialising graphics.

        SpriteGraphicAttributesList    spriteGraphicAttributesList;

        status = QueryNastySpriteInitialisingGraphics (dcHandle,
                                                       spriteGraphicsMap,
                                                       nastySpriteColour, 
                                                       spriteGraphicAttributesList);

        if (status == ERR_SUCCESS)
        {
            // Set graphic initialising mode.

            status = SetGraphicInitialisingMode (dcHandle,
                                                 spriteGraphicAttributesList,
                                                 MAX_SEQUENCE_COUNT);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus NastySprite::SetTerminatingMode (FolioHandle                            dcHandle,
                                             const SpriteGraphicsMap                &spriteGraphicsMap,
                                             Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour,
                                             UInt32                                 nastySpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 4;

    FolioStatus status = ERR_SUCCESS;

    // Is the nasty sprite terminated by graphic?

    if (IsTerminatedByGraphic (nastySpriteFlags))
    {
        // Yes. Query the nasty sprite's terminating graphics.

        SpriteGraphicAttributesList    spriteGraphicAttributesList;

        status = QueryNastySpriteTerminatingGraphics (dcHandle,
                                                      spriteGraphicsMap,
                                                      nastySpriteColour, 
                                                      spriteGraphicAttributesList);
        
        if (status == ERR_SUCCESS)
        {
            // Set graphic terminating mode.

            status = SetGraphicTerminatingMode (dcHandle,
                                                spriteGraphicAttributesList,
                                                MAX_SEQUENCE_COUNT,
                                                GetNastySpriteTerminatingSoundSamples ());
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


Int32   NastySprite::GetInitialScreenXLeft (const CollisionGrid &collisionGrid)
{
    static  const   Int32   MAX_NASTY_SPRITE_WIDTH = 16;

    // Get random initial screen X left position for the nasty sprite.

    return (Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorLeftBound () + 8, 
                                                        collisionGrid.GetFloorRightBound () - MAX_NASTY_SPRITE_WIDTH));
} // Endproc.


Int32   NastySprite::GetInitialScreenYTop (const CollisionGrid &collisionGrid)
{
    static  const   Int32   MAX_NASTY_SPRITE_HEIGHT = 22;

    // Get random initial screen Y top position for the nasty sprite.

    return (Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorTopBound () + 8, 
                                                        collisionGrid.GetFloorBottomBound () - MAX_NASTY_SPRITE_HEIGHT));
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   NastySprite::GetColour (NASTY_SPRITE_ID nastySpriteId)
{
    switch (nastySpriteId)
    {
    case NASTY_SPRITE_PUMPKIN:            
    case NASTY_SPRITE_SPIDER:             
    case NASTY_SPRITE_SMORPH:             
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW);

    case NASTY_SPRITE_GHOST:              
    case NASTY_SPRITE_BOUNCY:             
    case NASTY_SPRITE_JELLY_GHOUL:        
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN);
    
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_WITCH_FLYING: 
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA);
    
    case NASTY_SPRITE_GHOUL:
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN);
    
    case NASTY_SPRITE_GHOUL_FLYING: 
    case NASTY_SPRITE_BAT_FLYING:
        return (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED);
    
    default:
        return (Folio::Core::Game::ZxSpectrum::UNDEFINED);
    } // Endswitch.

} // Endproc.


bool    NastySprite::IsUpdateDirectionRqd (NASTY_SPRITE_ID nastySpriteId)
{
    // The nasty sprite can randomly change direction.

    switch (nastySpriteId)
    {
    case NASTY_SPRITE_PUMPKIN:            
    case NASTY_SPRITE_SPIDER:             
    case NASTY_SPRITE_SMORPH:             
    case NASTY_SPRITE_GHOST:              
    case NASTY_SPRITE_BOUNCY:             
    case NASTY_SPRITE_JELLY_GHOUL:        
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_GHOUL:
        return (Folio::Core::Util::Random::GetRandomNumber (8) == 0);
    
    case NASTY_SPRITE_WITCH_FLYING: 
    case NASTY_SPRITE_GHOUL_FLYING: 
    case NASTY_SPRITE_BAT_FLYING:
        return (Folio::Core::Util::Random::GetRandomNumber (4) == 0);

    default:
        return (false);
    } // Endswitch.

} // Endproc.


NastySprite::Direction  NastySprite::GetDirection (NASTY_SPRITE_ID nastySpriteId)
{
    // Get random direction for the nasty sprite.

    switch (nastySpriteId)
    {
    case NASTY_SPRITE_PUMPKIN:            
    case NASTY_SPRITE_SPIDER:             
    case NASTY_SPRITE_SMORPH:             
    case NASTY_SPRITE_GHOST:              
    case NASTY_SPRITE_BOUNCY:             
    case NASTY_SPRITE_JELLY_GHOUL:        
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_GHOUL:
        switch (Folio::Core::Util::Random::GetRandomNumber (7))
        {
        case 0:
            return (N);

        case 1:
            return (S);
    
        case 2:
            return (E);
    
        case 3:
            return (W);
    
        case 4:
            return (NE);
    
        case 5:
            return (NW);
    
        case 6:
            return (SE);
    
        case 7:
            return (SW);
    
        default:
            return (NO_DIRECTION);
        } // Endswitch.
    
    case NASTY_SPRITE_WITCH_FLYING: 
    case NASTY_SPRITE_GHOUL_FLYING: 
    case NASTY_SPRITE_BAT_FLYING:
        switch (Folio::Core::Util::Random::GetRandomNumber (5))
        {
        case 0:
            return (E);
    
        case 1:
            return (W);
    
        case 2:
            return (NE);
    
        case 3:
            return (NW);
    
        case 4:
            return (SE);
    
        case 5:
            return (SW);
    
        default:
            return (NO_DIRECTION);
        } // Endswitch.

    default:
        return (false);
    } // Endswitch.

} // Endproc.


UInt32  NastySprite::GetSpeed (NASTY_SPRITE_ID nastySpriteId)
{
    // Get random speed for the nasty sprite.

    switch (nastySpriteId)
    {
    case NASTY_SPRITE_PUMPKIN:            
    case NASTY_SPRITE_SPIDER:             
    case NASTY_SPRITE_SMORPH:             
    case NASTY_SPRITE_GHOST:              
    case NASTY_SPRITE_BOUNCY:             
    case NASTY_SPRITE_JELLY_GHOUL:        
    case NASTY_SPRITE_BAT:                
    case NASTY_SPRITE_GHOUL:
        return (Folio::Core::Util::Random::GetRandomNumber (1, 4));

    case NASTY_SPRITE_WITCH_FLYING: 
    case NASTY_SPRITE_GHOUL_FLYING: 
    case NASTY_SPRITE_BAT_FLYING:
        return (Folio::Core::Util::Random::GetRandomNumber (1, 6));
    
    default:
        return (STATIC_SPEED);
    } // Endswitch.

} // Endproc.


NastySprite::SpriteTerminatingSoundSamplesList  NastySprite::GetNastySpriteTerminatingSoundSamples ()
{
    if (m_nastySpriteTerminatingSoundSamplesList.empty ())
    {
        // Create each sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x3f; frequency >= 0x21; frequency -= 2)
        {
            m_nastySpriteTerminatingSoundSamplesList.push_back (Ultimate::MapMakeSound (frequency, 0x01));
        } // Endfor.

    } // Endif.
    
    return (m_nastySpriteTerminatingSoundSamplesList);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
