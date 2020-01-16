// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Globals.h"
#include    "NastySprite.h"
#include    "ResourceOwnerId.h"
#include    "Screen.h"
#include    "SpriteGraphics.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Nasty sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<NASTY_SPRITE_ID, SPRITE_ID> g_nastySpriteGraphicCharacteristics =
{
//      m_spriteId                  m_direction                         m_spriteGraphicIdsList
    {   NASTY_SPRITE_PUMPKIN,       Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_PUMPKIN_1, SPRITE_PUMPKIN_2,                         },  },    
    {   NASTY_SPRITE_SPIDER,        Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_SPIDER_1, SPRITE_SPIDER_2,                           },  },    
    {   NASTY_SPRITE_GHOST,         Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_GHOST_1, SPRITE_GHOST_2,                             },  },    
    {   NASTY_SPRITE_BOUNCY,        Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_BOUNCY_1, SPRITE_BOUNCY_2,                           },  },    
    {   NASTY_SPRITE_SMORPH,        Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_SMORPH_1, SPRITE_SMORPH_2,                           },  },    
    {   NASTY_SPRITE_JELLY_GHOUL,   Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_JELLY_GHOUL_1, SPRITE_JELLY_GHOUL_2,                 },  },    
    {   NASTY_SPRITE_BAT,           Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_BAT_1, SPRITE_BAT_2,                                 },  },    
    {   NASTY_SPRITE_GHOUL,         Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_GHOUL_1, SPRITE_GHOUL_2,                             },  },    

    {   NASTY_SPRITE_WITCH_FLYING,  Folio::Core::Game::E,               {   SPRITE_WITCH_FLYING_RIGHT_1, SPRITE_WITCH_FLYING_RIGHT_2,   },  },
    {   NASTY_SPRITE_WITCH_FLYING,  Folio::Core::Game::W,               {   SPRITE_WITCH_FLYING_LEFT_1, SPRITE_WITCH_FLYING_LEFT_2,     },  },

    {   NASTY_SPRITE_GHOUL_FLYING,  Folio::Core::Game::E,               {   SPRITE_GHOUL_FLYING_RIGHT_1, SPRITE_GHOUL_FLYING_RIGHT_2,   },  },
    {   NASTY_SPRITE_GHOUL_FLYING,  Folio::Core::Game::W,               {   SPRITE_GHOUL_FLYING_LEFT_1, SPRITE_GHOUL_FLYING_LEFT_2,     },  },

    {   NASTY_SPRITE_BAT_FLYING,    Folio::Core::Game::E,               {   SPRITE_BAT_FLYING_RIGHT_1, SPRITE_BAT_FLYING_RIGHT_2,       },  },
    {   NASTY_SPRITE_BAT_FLYING,    Folio::Core::Game::W,               {   SPRITE_BAT_FLYING_LEFT_1, SPRITE_BAT_FLYING_LEFT_2,         },  },
};


// Nasty sprite static members.
Folio::Core::Game::SpriteStationarySoundSamplesList NastySprite::m_nastySpriteTerminatingSoundSamplesList;  // The nasty sprite's terminating sound samples.

NastySprite::NastySprite ()
:   m_nastySpriteId(NASTY_SPRITE_UNDEFINED),
    m_nastySpriteScreenNumber(SCREEN_NUMBER_UNDEFINED),
    m_nastySpriteFlags(FLAGS_NONE),
    m_nastySpriteSpeed(STATIC_SPEED)
{
} // Endproc.


NastySprite::~NastySprite ()
{
} // Endproc.


FolioStatus NastySprite::Create (FolioHandle            dcHandle,
                                 NASTY_SPRITE_ID        nastySpriteId,
                                 UInt32                 screenNumber,
                                 const CollisionGrid    &collisionGrid,
                                 UInt32                 nastySpriteFlags)
{
    // Get the nasty sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR   nastySpriteColour = GetColour (nastySpriteId);

    // Query the nasty sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      g_resourceGraphicsCache,
                                                                                                      OWNER_ID_NASTY_SPRITE,
                                                                                                      DRAWING_ELEMENT_NASTY_SPRITE,
                                                                                                      nastySpriteId,
                                                                                                      nastySpriteColour,
                                                                                                      g_nastySpriteGraphicCharacteristics,
                                                                                                      spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Create the nasty sprite.

        status = Folio::Core::Game::ANastySprite::Create (dcHandle,
                                                          spriteGraphicAttributesList,
                                                          GetInitialScreenXLeft (collisionGrid),
                                                          GetInitialScreenYTop (collisionGrid),
                                                          Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                          Folio::Core::Game::ZxSpectrum::MapInkColour (nastySpriteColour),
                                                          Folio::Core::Game::E,
                                                          &(g_resourceGraphicsCache));

        if (status == ERR_SUCCESS)
        {
            // Set the nasty sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, 
                                          Folio::Core::Game::ZxSpectrum::GREEN, // Always green.
                                          nastySpriteFlags);

            if (status == ERR_SUCCESS)
            {
                // Set the nasty sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, 
                                             nastySpriteColour,
                                             nastySpriteFlags); 

                if (status == ERR_SUCCESS)
                {
                    // Note the nasty sprite's attributes.

                    m_nastySpriteId             = nastySpriteId;
                    m_nastySpriteScreenNumber   = screenNumber;
                    m_nastySpriteFlags          = nastySpriteFlags;
                    m_nastySpriteSpeed          = GetSpeed (nastySpriteId);

                    // The nasty sprite is alive.

                    SetAlive ();
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus NastySprite::Move (Gdiplus::Graphics    &graphics,
                               CollisionGrid        &collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Should the nasty sprite's direction be updated?

    if (IsUpdateDirectionRqd (m_nastySpriteId))
    {
        // Yes. Set the nasty sprite's direction.

        status = SetDirection (GetDirection (m_nastySpriteId));
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Move the nasty sprite.

        status = Folio::Core::Game::ANastySprite::Move (graphics, m_nastySpriteSpeed, collisionGrid);
    } // Endif.

    return (status);
} // Endproc.


NASTY_SPRITE_ID   NastySprite::GetNastySpriteId () const
{
    return (m_nastySpriteId);
} // Endproc.


UInt32  NastySprite::GetNastySpriteFlags () const
{
    return (m_nastySpriteFlags);
} // Endproc.
       

UInt32  NastySprite::GetNastySpriteScreenNumber () const
{
    return (m_nastySpriteScreenNumber);
} // Endproc.


bool    NastySprite::IsInitialisedByGraphic (UInt32 nastySpriteflags)
{
    return ((nastySpriteflags & FLAGS_INITIALISED_BY_GRAPHIC) == FLAGS_INITIALISED_BY_GRAPHIC);
} // Endproc.
       

bool    NastySprite::IsTerminatedByGraphic (UInt32 nastySpriteflags)
{
    return ((nastySpriteflags & FLAGS_TERMINATED_BY_GRAPHIC) == FLAGS_TERMINATED_BY_GRAPHIC);
} // Endproc.
      

FolioStatus NastySprite::QueryInitialisingGraphics (FolioHandle                                         dcHandle,
                                                    Folio::Core::Game::ResourceGraphicsCache::OwnerId   ownerId,
                                                    Folio::Core::Game::ZxSpectrum::COLOUR               spriteColour,
                                                    Folio::Core::Game::SpriteGraphicAttributesList      &spriteGraphicAttributesList)
{
    // Nasty sprite initialising sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<NASTY_SPRITE_ID, SPRITE_ID> s_initialisingSpriteGraphicCharacteristics = 
    {
    //      m_spriteId                  m_direction                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_NASTY_ALIVE_1, SPRITE_NASTY_ALIVE_2, SPRITE_NASTY_ALIVE_3, SPRITE_NASTY_ALIVE_4, },  },
    };

    spriteGraphicAttributesList.clear ();   // Initialise!

    return (Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                         g_resourceGraphicsCache,
                                                                                         ownerId,
                                                                                         DRAWING_ELEMENT_NASTY_SPRITE,
                                                                                         spriteColour,
                                                                                         s_initialisingSpriteGraphicCharacteristics,
                                                                                         spriteGraphicAttributesList));
} // Endproc.


FolioStatus NastySprite::QueryTerminatingGraphics (FolioHandle                                          dcHandle,
                                                   Folio::Core::Game::ResourceGraphicsCache::OwnerId    ownerId,
                                                   Folio::Core::Game::ZxSpectrum::COLOUR                spriteColour,
                                                   Folio::Core::Game::SpriteGraphicAttributesList       &spriteGraphicAttributesList)
{
    // Nasty sprite terminating sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<NASTY_SPRITE_ID, SPRITE_ID> s_terminatingSpriteGraphicCharacteristics = 
    {
    //      m_spriteId                  m_direction                         m_spriteGraphicIdsList
        {   NASTY_SPRITE_UNDEFINED,     Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_NASTY_DEAD_1, SPRITE_NASTY_DEAD_2, SPRITE_NASTY_DEAD_3, SPRITE_NASTY_DEAD_4, },  },
    };

    spriteGraphicAttributesList.clear ();   // Initialise!

    return (Folio::Core::Game::QuerySpriteGraphicAttributes<NASTY_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                         g_resourceGraphicsCache,
                                                                                         ownerId,
                                                                                         DRAWING_ELEMENT_NASTY_SPRITE,
                                                                                         spriteColour,
                                                                                         s_terminatingSpriteGraphicCharacteristics,
                                                                                         spriteGraphicAttributesList));
} // Endproc.


FolioStatus NastySprite::SetInitialisingMode (FolioHandle                           dcHandle,
                                              Folio::Core::Game::ZxSpectrum::COLOUR nastySpriteColour,
                                              UInt32                                nastySpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 7;

    FolioStatus status = ERR_SUCCESS;

    // Is the nasty sprite initialised by graphic?

    if (IsInitialisedByGraphic (nastySpriteFlags))
    {
        // Yes. Query the nasty sprite's initialising graphics.

        Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

        status = QueryInitialisingGraphics (dcHandle,
                                            OWNER_ID_NASTY_SPRITE,
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
                                             Folio::Core::Game::ZxSpectrum::COLOUR  nastySpriteColour,
                                             UInt32                                 nastySpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 4;

    FolioStatus status = ERR_SUCCESS;

    // Is the nasty sprite terminated by graphic?

    if (IsTerminatedByGraphic (nastySpriteFlags))
    {
        // Yes. Query the nasty sprite's terminating graphics.

        Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

        status = QueryTerminatingGraphics (dcHandle,
                                           OWNER_ID_NASTY_SPRITE,
                                           nastySpriteColour, 
                                           spriteGraphicAttributesList);
        
        if (status == ERR_SUCCESS)
        {
            // Set graphic terminating mode.

            status = SetGraphicTerminatingMode (dcHandle,
                                                spriteGraphicAttributesList,
                                                MAX_SEQUENCE_COUNT,
                                                &(GetNastySpriteTerminatingSoundSamples ()));
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


Folio::Core::Game::Direction    NastySprite::GetDirection (NASTY_SPRITE_ID nastySpriteId)
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
            return (Folio::Core::Game::N);

        case 1:
            return (Folio::Core::Game::S);
    
        case 2:
            return (Folio::Core::Game::E);
    
        case 3:
            return (Folio::Core::Game::W);
    
        case 4:
            return (Folio::Core::Game::NE);
    
        case 5:
            return (Folio::Core::Game::NW);
    
        case 6:
            return (Folio::Core::Game::SE);
    
        case 7:
            return (Folio::Core::Game::SW);
    
        default:
            return (Folio::Core::Game::NO_DIRECTION);
        } // Endswitch.
    
    case NASTY_SPRITE_WITCH_FLYING: 
    case NASTY_SPRITE_GHOUL_FLYING: 
    case NASTY_SPRITE_BAT_FLYING:
        switch (Folio::Core::Util::Random::GetRandomNumber (5))
        {
        case 0:
            return (Folio::Core::Game::E);
    
        case 1:
            return (Folio::Core::Game::W);
    
        case 2:
            return (Folio::Core::Game::NE);
    
        case 3:
            return (Folio::Core::Game::NW);
    
        case 4:
            return (Folio::Core::Game::SE);
    
        case 5:
            return (Folio::Core::Game::SW);
    
        default:
            return (Folio::Core::Game::NO_DIRECTION);
        } // Endswitch.

    default:
        return (Folio::Core::Game::NO_DIRECTION);
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
        return (Folio::Core::Util::Random::GetRandomNumber (1, 3));

    case NASTY_SPRITE_WITCH_FLYING: 
    case NASTY_SPRITE_GHOUL_FLYING: 
    case NASTY_SPRITE_BAT_FLYING:
        return (Folio::Core::Util::Random::GetRandomNumber (1, 5));
    
    default:
        return (STATIC_SPEED);
    } // Endswitch.

} // Endproc.


Folio::Core::Game::SpriteStationarySoundSamplesList NastySprite::GetNastySpriteTerminatingSoundSamples ()
{
    // Has the nasty sprite's terminating sound samples been created?

    if (m_nastySpriteTerminatingSoundSamplesList.empty ())
    {
        // No. Create each sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x3f; frequency >= 0x21; frequency -= 2)
        {
            m_nastySpriteTerminatingSoundSamplesList.push_back (Ultimate::CreateSoundSample (frequency, 0x01));
        } // Endfor.

    } // Endif.
    
    return (m_nastySpriteTerminatingSoundSamplesList);
} // Endproc.


FolioStatus AddNastySpriteDrawingElement (const NastySpriteDrawingElement   &nastySpriteDrawingElement,
                                          NastySpriteDrawingElementsList    &nastySpriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Store the nasty sprite drawing element in the nasty sprite drawing 
    // elements list.

    nastySpriteDrawingElementsList.push_back (nastySpriteDrawingElement);

    return (status);
} // Endproc.


FolioStatus RemoveNastySpriteDrawingElement (UInt32                         screenNumber,
                                             UInt32                         maxNastySpriteDrawingElements,
                                             NastySpriteDrawingElementsList &nastySpriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Have the maximum number of nasty sprite drawing elements been added to 
    // the nasty sprite drawing elements list?

    if (nastySpriteDrawingElementsList.size () >= maxNastySpriteDrawingElements)
    {
        // Yes. Find the oldest nasty sprite drawing element that is not on 
        // the specified screen.

        NastySpriteDrawingElementsList::iterator    itrOldestDrawingElement = nastySpriteDrawingElementsList.begin ();

        UInt32  oldestTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();  // Initialise!

        bool    found = false; // Initialise!

        for (NastySpriteDrawingElementsList::iterator itr = itrOldestDrawingElement;
             itr != nastySpriteDrawingElementsList.end ();
             ++itr)
        {
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            if ((nastySprite->GetNastySpriteScreenNumber () != screenNumber) && 
                (itr->m_createdTickCount < oldestTickCount))
            {
                itrOldestDrawingElement = itr;

                found = true;
            } // Endif.

        } // Endfor.

        if (found)
        {
            // Remove the oldest nasty sprite drawing element from the nasty 
            // sprite drawing elements list.
    
            nastySpriteDrawingElementsList.erase (itrOldestDrawingElement);
        } // Endif.

        else
        {
            status = ERR_IN_USE;
        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
