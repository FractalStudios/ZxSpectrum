// "Home-made" includes.
#include    "StdAfx.h"
#include    "NastySprite.h"
#include    "PlayerSprite.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Player sprite graphic attributes.
static  const   Folio::Core::Game::SpriteGraphicsAttributesList<PLAYER_SPRITE_ID, SPRITE_ID>    g_playerSpriteGraphicAttributes =
{
//      m_spriteId                  m_direction                             m_spriteGraphicIdsList                                                                                                                                                                                                                                                  m_action
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::E,    {   SPRITE_SABRE_MAN_RIGHT, SPRITE_SABRE_MAN_WALKING_RIGHT_1, SPRITE_SABRE_MAN_RIGHT, SPRITE_SABRE_MAN_WALKING_RIGHT_2,                                                                                                                                             },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::W,    {   SPRITE_SABRE_MAN_LEFT, SPRITE_SABRE_MAN_WALKING_LEFT_1, SPRITE_SABRE_MAN_LEFT, SPRITE_SABRE_MAN_WALKING_LEFT_2,                                                                                                                                                 },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::N,    {   SPRITE_SABRE_MAN_UP, SPRITE_SABRE_MAN_WALKING_UP_1, SPRITE_SABRE_MAN_UP, SPRITE_SABRE_MAN_WALKING_UP_2,                                                                                                                                                         },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::S,    {   SPRITE_SABRE_MAN_DOWN, SPRITE_SABRE_MAN_WALKING_DOWN_1, SPRITE_SABRE_MAN_DOWN, SPRITE_SABRE_MAN_WALKING_DOWN_2,                                                                                                                                                 },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::E,    {   SPRITE_SABRE_MAN_SWORD_RIGHT_1, SPRITE_SABRE_MAN_SWORD_RIGHT_2, SPRITE_SABRE_MAN_SWORD_RIGHT_3, SPRITE_SABRE_MAN_SWORD_RIGHT_4, SPRITE_SABRE_MAN_SWORD_RIGHT_5, SPRITE_SABRE_MAN_SWORD_RIGHT_4, SPRITE_SABRE_MAN_SWORD_RIGHT_6, SPRITE_SABRE_MAN_SWORD_RIGHT_2, },  PlayerSprite::ACTION_SWIPE_SWORD,   },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::W,    {   SPRITE_SABRE_MAN_SWORD_LEFT_1, SPRITE_SABRE_MAN_SWORD_LEFT_2, SPRITE_SABRE_MAN_SWORD_LEFT_3, SPRITE_SABRE_MAN_SWORD_LEFT_4, SPRITE_SABRE_MAN_SWORD_LEFT_5, SPRITE_SABRE_MAN_SWORD_LEFT_4, SPRITE_SABRE_MAN_SWORD_LEFT_6, SPRITE_SABRE_MAN_SWORD_LEFT_2,         },  PlayerSprite::ACTION_SWIPE_SWORD,   },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::E,    {   SPRITE_SABRE_MAN_FALLING_RIGHT,                                                                                                                                                                                                                                 },  PlayerSprite::ACTION_FALLING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::W,    {   SPRITE_SABRE_MAN_FALLING_LEFT,                                                                                                                                                                                                                                  },  PlayerSprite::ACTION_FALLING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::E,    {   SPRITE_SABRE_MAN_SITTING_RIGHT,                                                                                                                                                                                                                                 },  PlayerSprite::ACTION_SITTING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::W,    {   SPRITE_SABRE_MAN_SITTING_LEFT,                                                                                                                                                                                                                                  },  PlayerSprite::ACTION_SITTING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::E,    {   SPRITE_SABRE_MAN_GAME_OVER_RIGHT,                                                                                                                                                                                                                               },  PlayerSprite::ACTION_GAME_OVER,     },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::W,    {   SPRITE_SABRE_MAN_GAME_OVER_LEFT,                                                                                                                                                                                                                                },  PlayerSprite::ACTION_GAME_OVER,     },
};


PlayerSprite::PlayerSprite ()
:   m_playerSpriteSpeed(DEFAULT_SPEED),
    m_temporaryState(NO_TEMPORARY_STATE),
    m_temporaryStateTickCount(0),
    m_foundAmuletPiece(false)
{
} // Endproc.


PlayerSprite::~PlayerSprite ()
{
} // Endproc.


FolioStatus PlayerSprite::Create (FolioHandle                   dcHandle, 
                                  const SpriteGraphicsMapPtr    &spriteGraphicsMap)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 0; //iac.

    // Query the player sprite's graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<PLAYER_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       PLAYER_SPRITE_SABRE_MAN,
                                                                                                       *spriteGraphicsMap,
                                                                                                       INITIAL_COLOUR,
                                                                                                       g_playerSpriteGraphicAttributes,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Create the player sprite.

        status = Folio::Core::Game::APlayerSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           INITIAL_SCREEN_X_LEFT,
                                                           INITIAL_SCREEN_Y_TOP,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (INITIAL_COLOUR),
                                                           INITIAL_DIRECTION,
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERROR_SUCCESS)
        {
            // Set the player sprite's terminating mode.
                
            status = SetTerminatingMode (dcHandle, 
                                         spriteGraphicsMap); 

            if (status == ERROR_SUCCESS)
            {
                // Set the player sprite's movement sound samples.

                status = SetMovementSoundSamples ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::Start ()
{
    // Recreate the player sprite.

    FolioStatus status = Recreate (INITIAL_SCREEN_X_LEFT, INITIAL_SCREEN_Y_TOP, INITIAL_DIRECTION);

    if (status == ERR_SUCCESS)
    {
        // Reset the temporary state.

        status = ResetTemporaryState ();
    } // Endif.

    return (status);
} // Endproc.


PlayerSprite::Direction PlayerSprite::UpdateDirection (Direction    direction, 
                                                       bool         keyDown)
{
    if (!IsTemporarySickness ())
    {
        // Is a key down?

        if (keyDown)
        {
            // Yes. Is the player sprite temporary confused? 
        
            if (IsTemporaryConfusion ())
            {
                // Yes. Direction is opposite.

                switch (direction)
                {
                case N:
                    direction = S;
                    break;

                case S:
                    direction = N;
                    break;
            
                case E:
                    direction = W;
                    break;
            
                case W:
                    direction = E;
                    break;
            
                case NE:
                    direction = SW;
                    break;
            
                case NW:
                    direction = SE;
                    break;
            
                case SE:
                    direction = NW;
                    break;
            
                case SW:
                    direction = NE;
                    break;
            
                default:
                    break;
                } // Endswitch.

            } // Endif.
        
            // Has the player sprite's direction changed?

            if (direction != m_direction)
            {
                // Yes. Set the previous sprite direction. 
        
                SetPreviousSpriteDirection (m_direction);

                // Set the current sprite bitmaps.

                SetCurrentSpriteBitmaps (direction, m_spriteDrawingAttributesList);
            } // Endif.

            // The player sprite is moving in the direction.
        
            m_direction = direction;
            m_state     = STATE_MOVING; 
        } // Endif.

        // All keys are up. In auto-move mode?

        else
        if (!m_inAutoMoveMode)
        {
            // No. Get the auto-move state.
        
            m_state = GetAutoMoveState ();
        } // Endelseif.
    
    } // Endif.

    return (m_direction);
} // Endproc.


FolioStatus PlayerSprite::CheckPlayer (Gdiplus::Graphics    &graphics,
                                       const CollisionGrid  &collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_INITIALISED:
    case STATE_STATIC:
    case STATE_MOVING:
        // If in a temporary state, is it finished?

        if (IsTemporaryState () &&
            IsTemporaryStateFinished ())
        {
            // Yes. Reset the temporary state.

            status = ResetTemporaryState ();
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            status = (m_state == STATE_MOVING) && (m_playerSpriteSpeed != STATIC_SPEED) 
                     ? Folio::Core::Game::APlayerSprite::Move (graphics, m_playerSpriteSpeed, collisionGrid)
                     : Folio::Core::Game::APlayerSprite::Static (graphics, collisionGrid);
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::SetTemporaryImmunity (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour)
{
    return (SetTemporaryState (IMMUNITY, playerSpriteColour));
} // Endproc.


FolioStatus PlayerSprite::SetTemporaryConfusion (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour)
{
    return (SetTemporaryState (CONFUSION, playerSpriteColour));
} // Endproc.


FolioStatus PlayerSprite::SetTemporarySpeed (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour)
{
    return (SetTemporaryState (SPEED, playerSpriteColour));
} // Endproc.


FolioStatus PlayerSprite::SetTemporarySickness (Folio::Core::Game::ZxSpectrum::COLOUR playerSpriteColour)
{
    return (SetTemporaryState (SICKNESS, playerSpriteColour));
} // Endproc.


FolioStatus PlayerSprite::ResetTemporaryState ()
{
    return (SetTemporaryState (NO_TEMPORARY_STATE, INITIAL_COLOUR));
} // Endproc.


void    PlayerSprite::SetFireKeyDown (bool fireKeyDown)
{
    if (!IsTemporaryState () && IsReady ())
    {
        if (fireKeyDown)
        {
            // Set the player sprite's swipe sword action.

            SetAction (ACTION_SWIPE_SWORD);

            m_playerSpriteSpeed = SWIPE_SWORD_SPEED;
        } // Endif.
    
        else
        if (m_action != DEFAULT_ACTION)
        {
            // Reset the player sprite's action.

            SetAction (DEFAULT_ACTION);

            m_playerSpriteSpeed = DEFAULT_SPEED;
        } // Endelseif.
    
    } // Endif.

} // Endproc.


void    PlayerSprite::SetGameOver ()
{
    // Set the player sprite's game over action.

    SetAction (ACTION_GAME_OVER);

    APlayerSprite::SetGameOver ();
} // Endproc.


bool    PlayerSprite::IsImmune () const
{
    return (IsTemporaryImmunity ());
} // Endproc.


bool    PlayerSprite::IsSick () const
{
    return (IsTemporarySickness ());
} // Endproc.


bool    PlayerSprite::IsDead (const CollisionGrid::CellElement& cellElement)
{
    // Cannot be dead if the player sprite is immune.

    bool    isDead = !IsImmune ();

    if (isDead)
    {
        switch (m_action)
        {
        case ACTION_SWIPE_SWORD:
            // Depending on the orientation of the payer sprite to the nasty sprite, 
            // the player sprite may or may not be dead.
                
            switch (reinterpret_cast<NastySprite *> (cellElement.m_userData)->GetDirection ())
            {
            case E:
            case NE:
            case SE:
                isDead = (m_direction & E) || 
                       (((m_direction == N )|| (m_direction == S)) && (m_previousHorizontalDirection & E));
                break;
            
            case W:
            case NW:
            case SW:
                isDead = (m_direction & W) || 
                       (((m_direction == N )|| (m_direction == S)) && (m_previousHorizontalDirection & W));
                break;

            case N:
            case S:
            default:
                isDead = true;
                break;
            } // Endswitch.
            break;

        case ACTION_FALLING:    
        case ACTION_SITTING:    
        case ACTION_GAME_OVER:  
            // Cannot be dead if already dead or dying.

            isDead = false;
            break;

        case DEFAULT_ACTION:
        default:
            isDead = true;
            break;
        } // Endswitch.

    } // Endif.

    if (isDead)
    {
        // The player is dead.

        SetDead ();
    } // Endif.

    return (isDead);
} // Endif.


void    PlayerSprite::SetFoundAmuletPiece (bool foundAmuletPiece)
{
    m_foundAmuletPiece = foundAmuletPiece;
} // Endproc.


bool    PlayerSprite::FoundAmuletPiece () const
{
    return (m_foundAmuletPiece);
} // Endproc.


FolioStatus PlayerSprite::SetTerminatingMode (FolioHandle                   dcHandle,
                                              const SpriteGraphicsMapPtr    &spriteGraphicsMap)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 6;

    // Player sprite terminating sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<PLAYER_SPRITE_ID, SPRITE_ID>    s_terminatingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                             m_spriteGraphicIdsList
        {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::W,    {   SPRITE_SABRE_MAN_SITTING_LEFT,  },  },
        {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::APlayerSprite::E,    {   SPRITE_SABRE_MAN_SITTING_RIGHT, },  },
    };

    // Query the player sprite's terminating graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<PLAYER_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       *spriteGraphicsMap,
                                                                                                       INITIAL_COLOUR,
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


FolioStatus PlayerSprite::SetTemporaryState (TEMPORARY_STATE                        temporaryState,
                                             Folio::Core::Game::ZxSpectrum::COLOUR  playerSpriteColour)
{
    // Set the player sprite's action.

    SetAction (temporaryState == SICKNESS ? ACTION_SITTING : DEFAULT_ACTION);

    // Change the player sprite's colour.

    FolioStatus status = ChangeSpriteInkColour (Folio::Core::Game::ZxSpectrum::MapInkColour (playerSpriteColour),   
                                                false, 
                                                false);

    if (status == ERR_SUCCESS)
    {
        // Set the player sprite's speed.

        switch (temporaryState)
        {
        case SPEED:
            m_playerSpriteSpeed = FAST_SPEED;
            break;

        case SICKNESS:
            m_playerSpriteSpeed = STATIC_SPEED;
            break;

        case NO_TEMPORARY_STATE:
        case IMMUNITY:
        case CONFUSION:
        default:
            m_playerSpriteSpeed = DEFAULT_SPEED;
            break;
        } // Endswitch.

        // Set the player sprite's temporary state.

        m_temporaryState = temporaryState;

        // Start the temporary state tick count.

        StartTemporaryStateTickCount ();
    } // Endif.

    return (status);
} // Endproc.


void    PlayerSprite::StartTemporaryStateTickCount ()
{
    m_temporaryStateTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                1000 * Folio::Core::Util::Random::GetRandomNumber (5, 8);
} // Endproc.


bool    PlayerSprite::IsTemporaryState () const
{
    return (m_temporaryState != NO_TEMPORARY_STATE);
} // Endproc.


bool    PlayerSprite::IsTemporaryStateFinished () const
{
    return (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_temporaryStateTickCount);
} // Endproc.


bool    PlayerSprite::IsTemporaryImmunity () const
{
    return (m_temporaryState != NO_TEMPORARY_STATE);
} // Endproc.


bool    PlayerSprite::IsTemporaryConfusion () const
{
    return (m_temporaryState == CONFUSION);
} // Endproc.


bool    PlayerSprite::IsTemporarySickness () const
{
    return (m_temporaryState == SICKNESS);
} // Endproc.


FolioStatus PlayerSprite::SetMovementSoundSamples ()
{
    // Player sprite movement sound sample list.
    static  const   SpriteMovementSoundSamplesList  s_playerSpriteMovementSoundSampleList =
    {
        {   SpriteMovementSoundSample(new SpriteMovementSoundSample::element_type(Ultimate::MapMakeSound (0x30, 0x08))),  },
        {   SpriteMovementSoundSample(new SpriteMovementSoundSample::element_type(Ultimate::MapMakeSound (0x40, 0x08))),  },
    };

    // Set the player sprite's movement sound samples.

    return (SetSpriteMovementSoundSamples (SpriteMovementSoundAttributesList(1, 
                                                                             SpriteMovementSoundAttributes(ALL_DIRECTIONS, s_playerSpriteMovementSoundSampleList))));
} // Endproc.


Int32   PlayerSprite::CalculateCollisionXLeft () const
{
    if (m_action == ACTION_SWIPE_SWORD)
    {
        switch (m_direction)
        {
        case N:
        case S:
            if (m_previousHorizontalDirection == W)
            {
                return (m_screenRect.X + m_screenRect.Width - m_collisionRect.Width);
            } // Endif.
            break;

        case W:
        case NW:
        case SW:
            return (m_screenRect.X + m_screenRect.Width - m_collisionRect.Width);

        case E:
        case NE:
        case SE:
        default:
            break;
        } // Endswitch.

    } // Endif.

    return (APlayerSprite::CalculateCollisionXLeft ());
} // Endproc.


Int32   PlayerSprite::CalculateScreenXLeft (CollisionGrid::DIRECTION collisionGridDirection) const
{
    switch (m_direction)
    {
    case N:
    case S:
        if (m_previousHorizontalDirection == W)
        {
            return (m_collisionRect.X + m_collisionRect.Width - m_screenRect.Width);
        } // Endif.
        break;

    case W:
    case NW:
    case SW:
        return (m_collisionRect.X + m_collisionRect.Width - m_screenRect.Width);

    case E:
    case NE:
    case SE:
    default:
        break;
    } // Endswitch.

    return (m_collisionRect.X);
} // Endproc.


Int32   PlayerSprite::CalculateScreenXLeft (Int32 bitmapScreenWidth) const
{
    switch (m_direction)
    {
    case N:
    case S:
        if (m_previousHorizontalDirection == W)
        {
            return (m_collisionRect.X + m_collisionRect.Width - bitmapScreenWidth);
        } // Endif.
        break;

    case W:
    case NW:
    case SW:
        return (m_collisionRect.X + m_collisionRect.Width - bitmapScreenWidth);

    case E:
    case NE:
    case SE:
    default:
        break;
    } // Endswitch.

    return (m_collisionRect.X);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
