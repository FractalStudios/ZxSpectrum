// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Globals.h"
#include    "PlayerSprite.h"
#include    "ResourceOwnerId.h"
#include    "SpriteGraphics.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Player sprite attributes.
struct PlayerSpriteAttributes
{
    PLAYER_SPRITE_ID                        m_playerSpriteId;       // The identifier of the player sprite.
    Int32                                   m_initialScreenXLeft;   // The initial screen X left (in pixels) of the player sprite.
    Int32                                   m_initialScreenYTop;    // The initial screen Y top (in pixels) of the player sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_playerSpriteColour;   // The colour of the player sprite.
    Folio::Core::Game::Direction            m_initialDirection;     // The initial direction of the player sprite.
    UInt32                                  m_playerSpriteFlags;    // The flags of the player sprite.
}; // Endstruct.

// Player sprite attributes table.
static  const   PlayerSpriteAttributes  g_playerSpriteAttributesTable [] =
{
//      m_playerSpriteId        m_initialScreenXLeft    m_initialScreenYTop     m_playerSpriteColour                                                            m_initialDirection      m_playerSpriteFlags
    {   PLAYER_SPRITE_KNIGHT,   96,                     88,                     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   Folio::Core::Game::E,   PlayerSprite::FLAGS_INITIALISED_BOTTOM_UP | PlayerSprite::FLAGS_TERMINATED_TOP_DOWN,    },
    {   PLAYER_SPRITE_WIZARD,   96,                     88,                     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   Folio::Core::Game::E,   PlayerSprite::FLAGS_INITIALISED_BOTTOM_UP | PlayerSprite::FLAGS_TERMINATED_TOP_DOWN,    },
    {   PLAYER_SPRITE_SERF,     96,                     88,                     Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   Folio::Core::Game::E,   PlayerSprite::FLAGS_INITIALISED_BOTTOM_UP | PlayerSprite::FLAGS_TERMINATED_TOP_DOWN,    },
};


// Player sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<PLAYER_SPRITE_ID, SPRITE_ID>    g_playerSpriteGraphicCharacteristics =
{
//      m_spriteId              m_direction             m_spriteGraphicIdsList
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::E,   {   SPRITE_KNIGHT_RIGHT, SPRITE_KNIGHT_RIGHT, SPRITE_KNIGHT_WALKING_RIGHT_1, SPRITE_KNIGHT_WALKING_RIGHT_1, SPRITE_KNIGHT_RIGHT, SPRITE_KNIGHT_RIGHT, SPRITE_KNIGHT_WALKING_RIGHT_2, SPRITE_KNIGHT_WALKING_RIGHT_2, },  },
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::W,   {   SPRITE_KNIGHT_LEFT, SPRITE_KNIGHT_LEFT, SPRITE_KNIGHT_WALKING_LEFT_1, SPRITE_KNIGHT_WALKING_LEFT_1, SPRITE_KNIGHT_LEFT, SPRITE_KNIGHT_LEFT, SPRITE_KNIGHT_WALKING_LEFT_2, SPRITE_KNIGHT_WALKING_LEFT_2,         },  },
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::N,   {   SPRITE_KNIGHT_UP, SPRITE_KNIGHT_UP, SPRITE_KNIGHT_WALKING_UP_1, SPRITE_KNIGHT_WALKING_UP_1, SPRITE_KNIGHT_UP, SPRITE_KNIGHT_UP, SPRITE_KNIGHT_WALKING_UP_2, SPRITE_KNIGHT_WALKING_UP_2,                         },  },
    {   PLAYER_SPRITE_KNIGHT,   Folio::Core::Game::S,   {   SPRITE_KNIGHT_DOWN, SPRITE_KNIGHT_DOWN, SPRITE_KNIGHT_WALKING_DOWN_1, SPRITE_KNIGHT_WALKING_DOWN_1, SPRITE_KNIGHT_DOWN, SPRITE_KNIGHT_DOWN, SPRITE_KNIGHT_WALKING_DOWN_2, SPRITE_KNIGHT_WALKING_DOWN_2,         },  },

    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::E,   {   SPRITE_WIZARD_RIGHT, SPRITE_WIZARD_RIGHT, SPRITE_WIZARD_WALKING_RIGHT_1, SPRITE_WIZARD_WALKING_RIGHT_1, SPRITE_WIZARD_RIGHT, SPRITE_WIZARD_RIGHT, SPRITE_WIZARD_WALKING_RIGHT_2, SPRITE_WIZARD_WALKING_RIGHT_2, },  },
    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::W,   {   SPRITE_WIZARD_LEFT, SPRITE_WIZARD_LEFT, SPRITE_WIZARD_WALKING_LEFT_1, SPRITE_WIZARD_WALKING_LEFT_1, SPRITE_WIZARD_LEFT, SPRITE_WIZARD_LEFT, SPRITE_WIZARD_WALKING_LEFT_2, SPRITE_WIZARD_WALKING_LEFT_2,         },  },
    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::N,   {   SPRITE_WIZARD_UP, SPRITE_WIZARD_UP, SPRITE_WIZARD_WALKING_UP_1, SPRITE_WIZARD_WALKING_UP_1, SPRITE_WIZARD_UP, SPRITE_WIZARD_UP, SPRITE_WIZARD_WALKING_UP_2, SPRITE_WIZARD_WALKING_UP_2,                         },  },
    {   PLAYER_SPRITE_WIZARD,   Folio::Core::Game::S,   {   SPRITE_WIZARD_DOWN, SPRITE_WIZARD_DOWN, SPRITE_WIZARD_WALKING_DOWN_1, SPRITE_WIZARD_WALKING_DOWN_1, SPRITE_WIZARD_DOWN, SPRITE_WIZARD_DOWN, SPRITE_WIZARD_WALKING_DOWN_2, SPRITE_WIZARD_WALKING_DOWN_2,         },  },

    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::E,   {   SPRITE_SERF_RIGHT, SPRITE_SERF_RIGHT, SPRITE_SERF_WALKING_RIGHT_1, SPRITE_SERF_WALKING_RIGHT_1, SPRITE_SERF_RIGHT, SPRITE_SERF_RIGHT, SPRITE_SERF_WALKING_RIGHT_2, SPRITE_SERF_WALKING_RIGHT_2,                 },  },
    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::W,   {   SPRITE_SERF_LEFT, SPRITE_SERF_LEFT, SPRITE_SERF_WALKING_LEFT_1, SPRITE_SERF_WALKING_LEFT_1, SPRITE_SERF_LEFT, SPRITE_SERF_LEFT, SPRITE_SERF_WALKING_LEFT_2, SPRITE_SERF_WALKING_LEFT_2,                         },  },
    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::N,   {   SPRITE_SERF_UP, SPRITE_SERF_UP, SPRITE_SERF_WALKING_UP_1, SPRITE_SERF_WALKING_UP_1, SPRITE_SERF_UP, SPRITE_SERF_UP, SPRITE_SERF_WALKING_UP_2, SPRITE_SERF_WALKING_UP_2,                                         },  },
    {   PLAYER_SPRITE_SERF,     Folio::Core::Game::S,   {   SPRITE_SERF_DOWN, SPRITE_SERF_DOWN, SPRITE_SERF_WALKING_DOWN_1, SPRITE_SERF_WALKING_DOWN_1, SPRITE_SERF_DOWN, SPRITE_SERF_DOWN, SPRITE_SERF_WALKING_DOWN_2, SPRITE_SERF_WALKING_DOWN_2,                         },  },
};


// Player sprite static members.
Folio::Core::Game::SpriteStationarySoundSamplesList PlayerSprite::m_playerSpriteInitialisingSoundSamplesList;   // The player sprite's initialising sound samples.
Folio::Core::Game::SpriteStationarySoundSamplesList PlayerSprite::m_playerSpriteTerminatingSoundSamplesList;    // The player sprite's terminating sound samples.

PlayerSprite::PlayerSprite ()
:   m_playerSpriteId(PLAYER_SPRITE_UNDEFINED),
    m_initialScreenXLeft(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_initialScreenYTop(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_initialDirection(Folio::Core::Game::NO_DIRECTION),
    m_playerSpriteFlags(FLAGS_NONE),
    m_canFireWeapon(false),
    m_canCollectItems(false)
{
} // Endproc.


PlayerSprite::~PlayerSprite ()
{
} // Endproc.


FolioStatus PlayerSprite::Create (FolioHandle                           dcHandle, 
                                  PLAYER_SPRITE_ID                      playerSpriteId,
                                  Int32                                 initialScreenXLeft,
                                  Int32                                 initialScreenYTop,
                                  Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour,
                                  Folio::Core::Game::Direction          initialDirection,
                                  UInt32                                playerSpriteFlags)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 3;

    // Query the player sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<PLAYER_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       OWNER_ID_MAIN_PLAYER_SPRITE,
                                                                                                       DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,
                                                                                                       playerSpriteId,
                                                                                                       playerSpriteColour,
                                                                                                       g_playerSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Create the player sprite.

        status = Folio::Core::Game::APlayerSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           initialScreenXLeft,
                                                           initialScreenYTop,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (playerSpriteColour),
                                                           initialDirection,
                                                           &(g_resourceGraphicsCache),
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERR_SUCCESS)
        {
            // Set the player sprite's initialising mode.
            
            status = SetInitialisingMode (playerSpriteFlags);

            if (status == ERR_SUCCESS)
            {
                // Set the player sprite's terminating mode.

                status = SetTerminatingMode (playerSpriteFlags);

                if (status == ERR_SUCCESS)
                {
                    // Set the player sprite's movement sound samples.

                    SetMovementSoundSamples ();

                    // Note the player sprite's attributes.

                    m_playerSpriteId        = playerSpriteId;
                    m_initialScreenXLeft    = initialScreenXLeft;
                    m_initialScreenYTop     = initialScreenYTop;
                    m_initialDirection      = initialDirection;
                    m_playerSpriteFlags     = playerSpriteFlags;
                } // Endif.
            
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::Restart ()
{
    // Restart the player sprite.

    FolioStatus status = Folio::Core::Game::APlayerSprite::Restart (m_initialScreenXLeft, 
                                                                    m_initialScreenYTop, 
                                                                    m_initialDirection);

    if (status == ERR_SUCCESS)
    {
        m_canFireWeapon     = false;
        m_canCollectItems   = false;
    } // Endif.

    return (status);
} // Endproc.


PLAYER_SPRITE_ID   PlayerSprite::GetPlayerSpriteId () const
{
    return (m_playerSpriteId);
} // Endproc.


UInt32  PlayerSprite::GetPlayerSpriteFlags () const
{
    return (m_playerSpriteFlags);
} // Endproc.
     

void    PlayerSprite::SetCanFireWeapon (bool canFireWeapon)
{
    m_canFireWeapon = canFireWeapon;
} // Endproc.


bool    PlayerSprite::CanFireWeapon () const
{
    // Cannot fire a weapon if in screen exit.

    return (m_canFireWeapon && !IsInScreenExit ());
} // Endproc.


void    PlayerSprite::SetCanCollectItems (bool canCollectItems)
{
    m_canCollectItems = canCollectItems;
} // Endproc.


bool    PlayerSprite::CanCollectItems () const
{
    return (m_canCollectItems);
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


FolioStatus PlayerSprite::SetInitialisingMode (UInt32 playerSpriteFlags)
{
    // The initialising colour list.
    static  const   PlayerSprite::ColourList  s_initialisingColourList =
    {
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::BLUE),      }, 
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED),       },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA),   },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN),      },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW),    },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE),     },
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
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW),    },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN),      },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN),     },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA),   },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED),       },
        {   Folio::Core::Game::ZxSpectrum::MapInkColour (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::BLUE),      }, 
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


void    PlayerSprite::SetMovementSoundSamples ()
{
    // Player sprite sound sample list.
    static  const   Folio::Core::Game::SpriteSoundSamplesList   s_playerSpriteMovementSoundSampleList =
    {
        {   Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(Ultimate::CreateSoundSample (0x40, 0x04))),  },
        {   Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(Ultimate::CreateSoundSample (0x60, 0x04))),  },
    };

    // Set the player sprite's movement sound samples.

    SetSpriteMovementSoundSamples (Folio::Core::Game::SpriteMovementSoundSamplesList(1, 
                                                                                     Folio::Core::Game::SpriteMovementSoundSample(Folio::Core::Game::ALL_DIRECTIONS, s_playerSpriteMovementSoundSampleList)));
} // Endproc.


Folio::Core::Game::SpriteStationarySoundSamplesList PlayerSprite::GetPlayerSpriteInitialisingSoundSamples (bool isBottomUpMode)
{
    // Has the player sprite's initialising sound samples been created?

    if (m_playerSpriteInitialisingSoundSamplesList.empty ())
    {
        // No. Create each sound sample representing the required sound.

        if (isBottomUpMode)
        {
            for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x7f; frequency >= 0x5d; frequency -= 0x02)
            {
                m_playerSpriteInitialisingSoundSamplesList.push_back (Folio::Core::Game::SpriteStationarySoundSample(Ultimate::CreateSoundSample (frequency, 0x10), 2));
            } // Endfor.
    
        } // Endif.
    
        else
        {
            for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x5d; frequency <= 0x7f; frequency += 0x02)
            {
                m_playerSpriteInitialisingSoundSamplesList.push_back (Folio::Core::Game::SpriteStationarySoundSample(Ultimate::CreateSoundSample (frequency, 0x10), 2));
            } // Endfor.
    
        } // Endelse.
    
    } // Endif.
    
    return (m_playerSpriteInitialisingSoundSamplesList);
} // Endproc.


Folio::Core::Game::SpriteStationarySoundSamplesList PlayerSprite::GetPlayerSpriteTerminatingSoundSamples (bool isBottomUpMode)
{
    // Has the player sprite's terminating sound samples been created?
    
    if (m_playerSpriteTerminatingSoundSamplesList.empty ())
    {
        // No. Create each sound sample representing the required sound.

        UInt32  count = 0;  // Initialise!

        if (isBottomUpMode)
        {
            for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x7f; frequency >= 0x5d; frequency -= 0x02)
            {
                UInt32  numFrames = ((++count % 3) == 0) ? 2 : 1;

                m_playerSpriteTerminatingSoundSamplesList.push_back (Folio::Core::Game::SpriteStationarySoundSample(Ultimate::CreateSoundSample (frequency, 0x10), numFrames));
            } // Endfor.
    
        } // Endif.
    
        else
        {
            for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x5d; frequency <= 0x7f; frequency += 0x02)
            {
                UInt32  numFrames = ((++count % 3) == 0) ? 2 : 1;

                m_playerSpriteTerminatingSoundSamplesList.push_back (Folio::Core::Game::SpriteStationarySoundSample(Ultimate::CreateSoundSample (frequency, 0x10), numFrames));
            } // Endfor.
    
        } // Endelse.
    
    } // Endif.
    
    return (m_playerSpriteTerminatingSoundSamplesList);
} // Endproc.


FolioStatus CreatePlayerSprites (FolioHandle        dcHandle,
                                 PlayerSpritesMap   &playerSpritesMap)
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
