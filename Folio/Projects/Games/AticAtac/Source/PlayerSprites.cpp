// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "PlayerSprites.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Player sprite attributes.
struct PlayerSpriteAttributes
{
    PLAYER_SPRITE_ID                            m_playerSpriteId;       // The identifier of the player sprite.
    Int32                                       m_initialScreenXLeft;   // The initial screen X left (in pixels) of the player sprite.
    Int32                                       m_initialScreenYTop;    // The initial screen Y top (in pixels) of the player sprite.
    ZxSpectrum::COLOUR                          m_playerSpriteColour;   // The colour of the player sprite.
    Folio::Core::Game::APlayerSprite::Direction m_initialDirection;     // The initial direction of the player sprite.
    UInt32                                      m_playerSpriteFlags;    // The flags of the player sprite.
}; // Endstruct.

// Player sprite attributes table.
static  const   PlayerSpriteAttributes  g_playerSpriteAttributesTable [] =
{
//      m_playerSpriteId        m_initialScreenXLeft    m_initialScreenYTop     m_playerSpriteColour                        m_initialDirection  m_playerSpriteFlags
    {   PLAYER_SPRITE_KNIGHT,   96,                     88,                     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     PlayerSprite::E,    PlayerSprite::FLAGS_INITIALISED_BOTTOM_UP | PlayerSprite::FLAGS_TERMINATED_TOP_DOWN,    },
    {   PLAYER_SPRITE_WIZARD,   96,                     88,                     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     PlayerSprite::E,    PlayerSprite::FLAGS_INITIALISED_BOTTOM_UP | PlayerSprite::FLAGS_TERMINATED_TOP_DOWN,    },
    {   PLAYER_SPRITE_SERF,     96,                     88,                     ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     PlayerSprite::E,    PlayerSprite::FLAGS_INITIALISED_BOTTOM_UP | PlayerSprite::FLAGS_TERMINATED_TOP_DOWN,    },
};


// Player sprite graphic attributes.
typedef Folio::Core::Game::SpriteGraphicsAttributes<PLAYER_SPRITE_ID, SPRITE_ID> PlayerSpriteGraphicAttributes;

// Player sprite graphic attributes table.
static  const   PlayerSpriteGraphicAttributes   g_playerSpriteGraphicAttributesTable [] =
{
//      m_spriteId              m_direction                                                                                                         m_spriteGraphicIdsList
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::APlayerSprite::N,                                                                                {   SPRITE_KNIGHT_UP, SPRITE_KNIGHT_WALKING_UP_1, SPRITE_KNIGHT_UP, SPRITE_KNIGHT_WALKING_UP_2,             },  },
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::APlayerSprite::S,                                                                                {   SPRITE_KNIGHT_DOWN, SPRITE_KNIGHT_WALKING_DOWN_1, SPRITE_KNIGHT_DOWN, SPRITE_KNIGHT_WALKING_DOWN_2,     },  },
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::APlayerSprite::E | Folio::Core::Game::APlayerSprite::NE | Folio::Core::Game::APlayerSprite::SE,  {   SPRITE_KNIGHT_RIGHT, SPRITE_KNIGHT_WALKING_RIGHT_1, SPRITE_KNIGHT_RIGHT, SPRITE_KNIGHT_WALKING_RIGHT_2, },  },
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::APlayerSprite::W | Folio::Core::Game::APlayerSprite::NW | Folio::Core::Game::APlayerSprite::SW,  {   SPRITE_KNIGHT_LEFT, SPRITE_KNIGHT_WALKING_LEFT_1, SPRITE_KNIGHT_LEFT, SPRITE_KNIGHT_WALKING_LEFT_2,     },  },

    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::APlayerSprite::N,                                                                                {   SPRITE_WIZARD_UP, SPRITE_WIZARD_WALKING_UP_1, SPRITE_WIZARD_UP, SPRITE_WIZARD_WALKING_UP_2,             },  },
    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::APlayerSprite::S,                                                                                {   SPRITE_WIZARD_DOWN, SPRITE_WIZARD_WALKING_DOWN_1, SPRITE_WIZARD_DOWN, SPRITE_WIZARD_WALKING_DOWN_2,     },  },
    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::APlayerSprite::E | Folio::Core::Game::APlayerSprite::NE | Folio::Core::Game::APlayerSprite::SE,  {   SPRITE_WIZARD_RIGHT, SPRITE_WIZARD_WALKING_RIGHT_1, SPRITE_WIZARD_RIGHT, SPRITE_WIZARD_WALKING_RIGHT_2, },  },
    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::APlayerSprite::W | Folio::Core::Game::APlayerSprite::NW | Folio::Core::Game::APlayerSprite::SW,  {   SPRITE_WIZARD_LEFT, SPRITE_WIZARD_WALKING_LEFT_1, SPRITE_WIZARD_LEFT, SPRITE_WIZARD_WALKING_LEFT_2,     },  },

    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::APlayerSprite::N,                                                                                {   SPRITE_SERF_UP, SPRITE_SERF_WALKING_UP_1, SPRITE_SERF_UP, SPRITE_SERF_WALKING_UP_2,                     },  },
    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::APlayerSprite::S,                                                                                {   SPRITE_SERF_DOWN, SPRITE_SERF_WALKING_DOWN_1, SPRITE_SERF_DOWN, SPRITE_SERF_WALKING_DOWN_2,             },  },
    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::APlayerSprite::E | Folio::Core::Game::APlayerSprite::NE | Folio::Core::Game::APlayerSprite::SE,  {   SPRITE_SERF_RIGHT, SPRITE_SERF_WALKING_RIGHT_1, SPRITE_SERF_RIGHT, SPRITE_SERF_WALKING_RIGHT_2,         },  },
    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::APlayerSprite::W | Folio::Core::Game::APlayerSprite::NW | Folio::Core::Game::APlayerSprite::SW,  {   SPRITE_SERF_LEFT, SPRITE_SERF_WALKING_LEFT_1, SPRITE_SERF_LEFT, SPRITE_SERF_WALKING_LEFT_2,             },  },
};


// Player sprite static members.
PlayerSprite::SpriteInitialisingSoundSamplesList    PlayerSprite::m_playerSpriteInitialisingSoundSamplesList;   // The player sprite's initialising sound samples.
PlayerSprite::SpriteTerminatingSoundSamplesList     PlayerSprite::m_playerSpriteTerminatingSoundSamplesList;    // The player sprite's terminating sound samples.

PlayerSprite::PlayerSprite ()
:   m_playerSpriteId(PLAYER_SPRITE_UNDEFINED),
    m_initialScreenXLeft(ZxSpectrum::UNDEFINED),
    m_initialScreenYTop(ZxSpectrum::UNDEFINED),
    m_playerSpriteColour(ZxSpectrum::UNDEFINED),
    m_initialDirection(NO_DIRECTION),
    m_playerSpriteFlags(FLAGS_NONE)
{
} // Endproc.


PlayerSprite::~PlayerSprite ()
{
} // Endproc.


FolioStatus PlayerSprite::Create (FolioHandle               dcHandle, 
                                  PLAYER_SPRITE_ID          playerSpriteId,
                                  const SpriteGraphicsMap   &spriteGraphicsMap,
                                  Int32                     initialScreenXLeft,
                                  Int32                     initialScreenYTop,
                                  ZxSpectrum::COLOUR        playerSpriteColour,
                                  Direction                 initialDirection,
                                  UInt32                    playerSpriteFlags)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 3;

    // Query the player sprite's graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = QuerySpriteGraphics<PLAYER_SPRITE_ID, PlayerSpriteGraphicAttributes> (dcHandle,
                                                                                               playerSpriteId,
                                                                                               spriteGraphicsMap,
                                                                                               playerSpriteColour,
                                                                                               sizeof (g_playerSpriteGraphicAttributesTable) / sizeof (PlayerSpriteGraphicAttributes),
                                                                                               g_playerSpriteGraphicAttributesTable,
                                                                                               spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Create the player sprite.

        status = Folio::Core::Game::APlayerSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           initialScreenXLeft,
                                                           initialScreenYTop,
                                                           ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           ZxSpectrum::MapInkColour (playerSpriteColour),
                                                           initialDirection,
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERROR_SUCCESS)
        {
            // Set the player sprite's movement sound samples.

            status = SetMovementSoundSamples (playerSpriteId);

            if (status == ERROR_SUCCESS)
            {
                // Set the player sprite's initialising mode.
            
                status = SetInitialisingMode (playerSpriteFlags);

                if (status == ERROR_SUCCESS)
                {
                    // Set the player sprite's terminating mode.

                    status = SetTerminatingMode (playerSpriteFlags);

                    if (status == ERROR_SUCCESS)
                    {
                        // Note the player sprite's attributes.

                        m_playerSpriteId        = playerSpriteId;
                        m_initialScreenXLeft    = initialScreenXLeft;
                        m_initialScreenYTop     = initialScreenYTop;
                        m_playerSpriteColour    = playerSpriteColour;
                        m_initialDirection      = initialDirection;
                        m_playerSpriteFlags     = playerSpriteFlags;
                    } // Endif.
            
                } // Endif.

            } // Endif.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::Restart ()
{
    // Recreate the player sprite.

    return (Recreate (m_initialScreenXLeft, m_initialScreenYTop, m_initialDirection));
} // Endproc.


PLAYER_SPRITE_ID   PlayerSprite::GetPlayerSpriteId () const
{
    return (m_playerSpriteId);
} // Endproc.


ZxSpectrum::COLOUR  PlayerSprite::GetPlayerSpriteColour () const
{
    return (m_playerSpriteColour);
} // Endproc.


UInt32  PlayerSprite::GetPlayerSpriteFlags () const
{
    return (m_playerSpriteFlags);
} // Endproc.
       

bool    PlayerSprite::IsInitialisedBottomUp (UInt32 playerSpriteflags)
{
    return ((playerSpriteflags & FLAGS_INITIALISED_BOTTOM_UP) == FLAGS_INITIALISED_BOTTOM_UP);
} // Endproc.
       

bool    PlayerSprite::IsInitialisedTopDown (UInt32 playerSpriteflags)
{
    return ((playerSpriteflags & FLAGS_INITIALISED_TOP_DOWN) == FLAGS_INITIALISED_TOP_DOWN);
} // Endproc.


bool    PlayerSprite::IsTerminatedBottomUp (UInt32 playerSpriteflags)
{
    return ((playerSpriteflags & FLAGS_TERMINATED_BOTTOM_UP) == FLAGS_TERMINATED_BOTTOM_UP);
} // Endproc.
       

bool    PlayerSprite::IsTerminatedTopDown (UInt32 playerSpriteflags)
{
    return ((playerSpriteflags & FLAGS_TERMINATED_TOP_DOWN) == FLAGS_TERMINATED_TOP_DOWN);
} // Endproc.


FolioStatus PlayerSprite::SetMovementSoundSamples (PLAYER_SPRITE_ID playerSpriteId)
{
    // Player sprite movement sound sample list.
    static  const   SpriteMovementSoundSamplesList  s_playerSpriteMovementSoundSampleList =
    {
        {   SpriteMovementSoundSample(new SpriteMovementSoundSample::element_type(ZxSpectrum::MapUltimateMakeSound (0x30, 0x08))),  },
        {   SpriteMovementSoundSample(new SpriteMovementSoundSample::element_type(ZxSpectrum::MapUltimateMakeSound (0x40, 0x08))),  },
    };

    // Set the player sprite's movement sound samples.

    return (SetSpriteMovementSoundSamples (SpriteMovementSoundAttributesList(1, 
                                                                             SpriteMovementSoundAttributes(ALL_DIRECTIONS, s_playerSpriteMovementSoundSampleList))));
} // Endproc.


FolioStatus PlayerSprite::SetInitialisingMode (UInt32 playerSpriteFlags)
{
    // The initialising colour list.
    static  const   PlayerSprite::ColourList  s_initialisingColourList =
    {
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::BLUE),       }, 
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::RED),        },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA),    },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::GREEN),      },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::CYAN),       },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW),     },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::WHITE),      },
    };

    FolioStatus status = ERR_SUCCESS;

    // Is the player sprite initialised from the bottom up?

    if (IsInitialisedBottomUp (playerSpriteFlags))
    {
        // Yes. Set bottom up initialising mode.

        status = SetBottomUpInitialisingMode (s_initialisingColourList,     
                                              GetPlayerSpriteInitialisingSoundSamples (true));
    } // Endif.

    // Is the player sprite initialised from the top down?
            
    else
    if (IsInitialisedTopDown (playerSpriteFlags))
    {
        // Yes. Set to down initialising mode.
              
        status = SetTopDownInitialisingMode (s_initialisingColourList,
                                             GetPlayerSpriteInitialisingSoundSamples (false));
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::SetTerminatingMode (UInt32 playerSpriteFlags)
{
    // The terminating colour list.
    static  const   PlayerSprite::ColourList  s_terminatingColourList =
    {
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::WHITE),      },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW),     },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::CYAN),       },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::GREEN),      },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA),    },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::RED),        },
        {   ZxSpectrum::MapInkColour (ZxSpectrum::BRIGHT | ZxSpectrum::BLUE),       }, 
    };

    FolioStatus status = ERR_SUCCESS;

    // Is the player sprite terminated from the bottom up?

    if (IsTerminatedBottomUp (playerSpriteFlags))
    {
        // Yes. Set bottom up terminating mode.

        status = SetBottomUpTerminatingMode (s_terminatingColourList,
                                             GetPlayerSpriteTerminatingSoundSamples (true));
    } // Endif.

    // Is the player sprite terminated from the top down?
            
    else
    if (IsTerminatedTopDown (playerSpriteFlags))
    {
        // Yes. Set top down terminating mode.
              
        status = SetTopDownTerminatingMode (s_terminatingColourList,
                                            GetPlayerSpriteTerminatingSoundSamples (false));
    } // Endelseif.

    return (status);
} // Endproc.


PlayerSprite::SpriteInitialisingSoundSamplesList    PlayerSprite::GetPlayerSpriteInitialisingSoundSamples (bool isBottomUpMode)
{
    if (m_playerSpriteInitialisingSoundSamplesList.empty ())
    {
        // Create each sound sample representing the required sound.

        if (isBottomUpMode)
        {
            for (ZxSpectrum::BYTE frequency = 0x7f; frequency >= 0x5d; frequency -= 0x02)
            {
                m_playerSpriteInitialisingSoundSamplesList.push_back (SpriteInitialisingSoundSample(ZxSpectrum::MapUltimateMakeSound (frequency, 0x10), 4));
            } // Endfor.
    
        } // Endif.
    
        else
        {
            for (ZxSpectrum::BYTE frequency = 0x5d; frequency <= 0x7f; frequency += 0x02)
            {
                m_playerSpriteInitialisingSoundSamplesList.push_back (SpriteInitialisingSoundSample(ZxSpectrum::MapUltimateMakeSound (frequency, 0x10), 4));
            } // Endfor.
    
        } // Endelse.
    
    } // Endif.
    
    return (m_playerSpriteInitialisingSoundSamplesList);
} // Endproc.


PlayerSprite::SpriteTerminatingSoundSamplesList PlayerSprite::GetPlayerSpriteTerminatingSoundSamples (bool isBottomUpMode)
{
    if (m_playerSpriteTerminatingSoundSamplesList.empty ())
    {
        // Create each sound sample representing the required sound.

        if (isBottomUpMode)
        {
            for (ZxSpectrum::BYTE frequency = 0x7f; frequency >= 0x5d; frequency -= 0x02)
            {
                m_playerSpriteTerminatingSoundSamplesList.push_back (SpriteTerminatingSoundSample(ZxSpectrum::MapUltimateMakeSound (frequency, 0x10)));
            } // Endfor.
    
        } // Endif.
    
        else
        {
            for (ZxSpectrum::BYTE frequency = 0x5d; frequency <= 0x7f; frequency += 0x02)
            {
                m_playerSpriteTerminatingSoundSamplesList.push_back (SpriteTerminatingSoundSample(ZxSpectrum::MapUltimateMakeSound (frequency, 0x10)));
            } // Endfor.
    
        } // Endelse.
    
    } // Endif.
    
    return (m_playerSpriteTerminatingSoundSamplesList);
} // Endproc.


FolioStatus BuildPlayerSprites (FolioHandle             dcHandle,
                                const SpriteGraphicsMap &spriteGraphicsMap,
                                PlayerSpritesMap        &playerSpritesMap)
{
    FolioStatus status = ERR_SUCCESS;

    playerSpritesMap.clear ();   // Initialise!

    // Build the player sprites map.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_playerSpriteAttributesTable) / sizeof (PlayerSpriteAttributes)));
         ++index)
    {              
        // Create a player sprite.

        PlayerSpritePtr playerSprite(new PlayerSprite);

        status = playerSprite->Create (dcHandle,
                                       g_playerSpriteAttributesTable [index].m_playerSpriteId,
                                       spriteGraphicsMap,
                                       g_playerSpriteAttributesTable [index].m_initialScreenXLeft,
                                       g_playerSpriteAttributesTable [index].m_initialScreenYTop,
                                       g_playerSpriteAttributesTable [index].m_playerSpriteColour,
                                       g_playerSpriteAttributesTable [index].m_initialDirection,
                                       g_playerSpriteAttributesTable [index].m_playerSpriteFlags);

        if (status == ERR_SUCCESS)
        {
            // Store the player sprite in the player sprites map.
        
            playerSpritesMap.insert (PlayerSpritesMap::value_type(g_playerSpriteAttributesTable [index].m_playerSpriteId, 
                                                                  playerSprite));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        playerSpritesMap.clear ();
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
