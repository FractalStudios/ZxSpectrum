// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "BossSprite.h"
#include    "NastySprite.h"
#include    "PlayerSprite.h"
#include    "SpriteGraphics.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Player sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<PLAYER_SPRITE_ID, SPRITE_ID>    g_playerSpriteGraphicCharacteristics =
{
//      m_spriteId                  m_direction             m_spriteGraphicIdsList                                                                                                                                                                                                                                                  m_action
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_WALKING_RIGHT_1, SPRITE_SABRE_MAN_RIGHT, SPRITE_SABRE_MAN_WALKING_RIGHT_2, SPRITE_SABRE_MAN_RIGHT,                                                                                                                                             },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_WALKING_LEFT_1, SPRITE_SABRE_MAN_LEFT, SPRITE_SABRE_MAN_WALKING_LEFT_2, SPRITE_SABRE_MAN_LEFT,                                                                                                                                                 },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::N,   {   SPRITE_SABRE_MAN_WALKING_UP_1, SPRITE_SABRE_MAN_UP, SPRITE_SABRE_MAN_WALKING_UP_2, SPRITE_SABRE_MAN_UP,                                                                                                                                                         },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::S,   {   SPRITE_SABRE_MAN_WALKING_DOWN_1, SPRITE_SABRE_MAN_DOWN, SPRITE_SABRE_MAN_WALKING_DOWN_2, SPRITE_SABRE_MAN_DOWN,                                                                                                                                                 },                                      },

    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_SWORD_RIGHT_1, SPRITE_SABRE_MAN_SWORD_RIGHT_2, SPRITE_SABRE_MAN_SWORD_RIGHT_3, SPRITE_SABRE_MAN_SWORD_RIGHT_4, SPRITE_SABRE_MAN_SWORD_RIGHT_5, SPRITE_SABRE_MAN_SWORD_RIGHT_4, SPRITE_SABRE_MAN_SWORD_RIGHT_6, SPRITE_SABRE_MAN_SWORD_RIGHT_2, },  PlayerSprite::ACTION_SWIPE_SWORD,   },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_SWORD_LEFT_1, SPRITE_SABRE_MAN_SWORD_LEFT_2, SPRITE_SABRE_MAN_SWORD_LEFT_3, SPRITE_SABRE_MAN_SWORD_LEFT_4, SPRITE_SABRE_MAN_SWORD_LEFT_5, SPRITE_SABRE_MAN_SWORD_LEFT_4, SPRITE_SABRE_MAN_SWORD_LEFT_6, SPRITE_SABRE_MAN_SWORD_LEFT_2,         },  PlayerSprite::ACTION_SWIPE_SWORD,   },

    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_FALLING_RIGHT,                                                                                                                                                                                                                                 },  PlayerSprite::ACTION_FALLING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_FALLING_LEFT,                                                                                                                                                                                                                                  },  PlayerSprite::ACTION_FALLING,       },

    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_SITTING_RIGHT,                                                                                                                                                                                                                                 },  PlayerSprite::ACTION_SITTING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_SITTING_LEFT,                                                                                                                                                                                                                                  },  PlayerSprite::ACTION_SITTING,       },

    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_LYING_DEAD_RIGHT,                                                                                                                                                                                                                              },  PlayerSprite::ACTION_LYING_DEAD,    },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_LYING_DEAD_LEFT,                                                                                                                                                                                                                               },  PlayerSprite::ACTION_LYING_DEAD,    },
};


PlayerSprite::PlayerSprite ()
:   m_playerSpriteSpeed(DEFAULT_SPEED),
    m_infection(NO_INFECTION),
    m_infectionColour(INITIAL_COLOUR),
    m_infectionColourSet(false),
    m_infectionTickCount(0),
    m_infectionCountdown(INFECTION_COUNTDOWN),
    m_justFoundAmuletPiece(false)
{
} // Endproc.


PlayerSprite::~PlayerSprite ()
{
} // Endproc.


FolioStatus PlayerSprite::Create (FolioHandle dcHandle)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 8;

    // Query the player sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<PLAYER_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_MAIN_PLAYER_SPRITE,
                                                                                                       Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,
                                                                                                       PLAYER_SPRITE_SABRE_MAN,
                                                                                                       INITIAL_COLOUR,
                                                                                                       g_playerSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Create the player sprite.

        status = Folio::Core::Game::APlayerSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           INITIAL_SCREEN_X_LEFT,
                                                           INITIAL_SCREEN_Y_TOP,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (INITIAL_COLOUR),
                                                           INITIAL_DIRECTION,
                                                           &(g_resourceGraphicsCache),
                                                           MAX_NUM_AUTO_MOVES);

        if (status == ERR_SUCCESS)
        {
            // Set the player sprite's terminating mode.
                
            status = SetTerminatingMode (dcHandle); 

            if (status == ERR_SUCCESS)
            {
                // Set the player sprite's movement sound samples.

                SetMovementSoundSamples ();
            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::Start ()
{
    // Restart the player sprite.

    FolioStatus status = Folio::Core::Game::APlayerSprite::Restart (INITIAL_SCREEN_X_LEFT, 
                                                                    INITIAL_SCREEN_Y_TOP, 
                                                                    INITIAL_DIRECTION);

    if (status == ERR_SUCCESS)
    {
        // Clear any infection the player sprite may have.

        status = ClearInfection ();
        
        if (status == ERR_SUCCESS)
        {
            // The player sprite has not just found an amulet piece.

            ResetJustFoundAmuletPiece ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::UpdateDirection (Folio::Core::Game::Direction direction, 
                                           bool                         keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the player sprite ready?

    if (IsReady ())
    {
        // Yes. Is a key down?

        if (keyDown)
        {
            // Yes. Is the player sprite confused? 
        
            if (IsInfectionConfusion ())
            {
                // Yes. Direction is opposite to that specified.

                switch (direction)
                {
                case Folio::Core::Game::N:
                    direction = Folio::Core::Game::S;
                    break;

                case Folio::Core::Game::S:
                    direction = Folio::Core::Game::N;
                    break;
            
                case Folio::Core::Game::E:
                    direction = Folio::Core::Game::W;
                    break;
            
                case Folio::Core::Game::W:
                    direction = Folio::Core::Game::E;
                    break;
            
                case Folio::Core::Game::NE:
                    direction = Folio::Core::Game::SW;
                    break;
            
                case Folio::Core::Game::NW:
                    direction = Folio::Core::Game::SE;
                    break;
            
                case Folio::Core::Game::SE:
                    direction = Folio::Core::Game::NW;
                    break;
            
                case Folio::Core::Game::SW:
                    direction = Folio::Core::Game::NE;
                    break;
            
                default:
                    break;
                } // Endswitch.

            } // Endif.

        } // Endif.

        // Update the player sprite's direction.

        status = Folio::Core::Game::APlayerSprite::UpdateDirection (direction, keyDown);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::CheckPlayerSprite (Gdiplus::Graphics&                 graphics,
                                             CollisionGrid&                     collisionGrid,
                                             ObjectSpriteDrawingElementsList&   screenObjectSpriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_INITIALISED:
        status = Folio::Core::Game::APlayerSprite::Static (graphics, collisionGrid);
        break;

    case STATE_TERMINATED:
        // Decrement the player sprite's life.

        status = g_informationPanel->DecrementPlayerLife (&(g_playerSprite));
        break;

    case STATE_STATIC:
    case STATE_MOVING:
        // Is the player sprite falling?
        
        if (IsAction (ACTION_FALLING)) 
        {
            // Yes. Move the player sprite.

            status = Folio::Core::Game::APlayerSprite::Move (graphics, 
                                                             m_playerSpriteSpeed, 
                                                             collisionGrid);

            // Is the player sprite at a wall or screen edge?

            if ((status == ERR_SUCCESS) && 
                (IsAtWall () || IsExitedScreen ()))
            {
                // Yes. Reset the player sprite's falling action.

                status = ResetFalling ();

                if (status == ERR_SUCCESS)
                {
                    // Player sprite is not exiting or entering a screen.
                
                    ResetScreenExit ();

                    // The player sprite is now dead.

                    SetDead ();
                } // Endif.

            } // Endif.

        } // Endif.

        // Is the player sprite lying dead?
        
        else
        if (IsAction (ACTION_LYING_DEAD)) 
        {
            // Yes. Is the player sprite's lying dead action complete?

            if (IsActionComplete (ACTION_LYING_DEAD))
            {
                // Yes. The game is over.

                SetGameOver ();
            } // Endif.

        } // Endelseif.

        else
        {
            // Is the player sprite's infection finished?

            if (IsInfectionFinished ())
            {
                // Yes. Clear the player sprite's infection.

                status = ClearInfection ();
            } // Endif.

            // Is the player sprite's infection finishing?
        
            else
            if (IsInfectionFinishing ())
            {
                // Yes.

                status = InfectionFinishing ();
            } // Endelseif.

            if (status == ERR_SUCCESS)
            {
                status = (m_state == STATE_MOVING)
                         ? Folio::Core::Game::APlayerSprite::Move (graphics, m_playerSpriteSpeed, collisionGrid)
                         : Folio::Core::Game::APlayerSprite::Static (graphics, collisionGrid);

                // Has the player sprite not exited the screen?

                if ((status == ERR_SUCCESS) && !IsExitedScreen ())
                {
                    // Yes. Has the player sprite collided with something?

                    CollisionGrid::CellElements cellElements;

                    if (collisionGrid.IsCollision (IsAction (ACTION_SWIPE_SWORD) ? g_playerSprite->GetScreenRect () : g_playerSprite->GetMovingRect (), 
                                                   cellElements))
                    {
                        // Yes. Handle the collision.

                        status = HandleCollision (cellElements, 
                                                  collisionGrid, 
                                                  screenObjectSpriteDrawingElementsList);
                    } // Endif.
            
                } // Endif.
        
            } // Endif.
        
        } // Endelse.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::SetFireKeyDown (bool fireKeyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the player sprite ready and not infected?

    if (IsReady () && !IsInfection ())
    {
        // Yes. Is the fire key down?

        if (fireKeyDown)
        {
            // Yes. Set the player sprite's swipe sword action.

            status = SetSwipeSword ();
        } // Endif.
    
        // Is the player sprite performing the swipe sword action?

        else
        if (IsAction (ACTION_SWIPE_SWORD))
        {
            // Yes. Reset the player sprite's swipe sword action.

            status = ResetSwipeSword ();
        } // Endelseif.
    
    } // Endif.
       
    return (status);
} // Endproc.


FolioStatus PlayerSprite::Alive ()
{   
    // The player sprite is static.

    SetState (STATE_STATIC);

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus PlayerSprite::Dead ()
{
    static  const   UInt32  LYING_DEAD_TICK_COUNT = 2 * 1000;   // Tick count the player sprite can be lying dead.

    // Set the player sprite's lying dead action.

    FolioStatus status = SetAction (ACTION_LYING_DEAD, LYING_DEAD_TICK_COUNT);

    if (status == ERR_SUCCESS)
    {
        // Reset the number of remaining auto-mode moves.

        ResetNumRemainingAutoModeMoves ();

        // The player sprite is static.

        SetState (STATE_STATIC);
    } // Endif.

    return (status);
} // Endproc.


void    PlayerSprite::ResetJustFoundAmuletPiece ()
{
    m_justFoundAmuletPiece = false;
} // Endproc.


bool    PlayerSprite::IsJustFoundAmuletPiece () const
{
    return (m_justFoundAmuletPiece);
} // Endproc.


bool    PlayerSprite::IsReady () const
{
    // Is the player sprite ready and not sick, falling or lying dead?

    return (ASprite::IsReady ()         &&
            !IsInfectionSickness ()     &&
            !IsAction (ACTION_FALLING)  &&
            !IsAction (ACTION_LYING_DEAD));
} // Endproc.


FolioStatus PlayerSprite::SetTerminatingMode (FolioHandle dcHandle)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = MAX_PLAYER_SPRITE_SITTING_DRAWING_ELEMENTS;

    // Player sprite terminating sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<PLAYER_SPRITE_ID, SPRITE_ID>    s_terminatingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction             m_spriteGraphicIdsList                  m_action
        {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_SITTING_RIGHT, },                                  },
        {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_SITTING_LEFT,  },                                  },
    };

    // Query the player sprite's terminating graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<PLAYER_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_MAIN_PLAYER_SPRITE,
                                                                                                       Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_MAIN_PLAYER_SPRITE,
                                                                                                       INITIAL_COLOUR,
                                                                                                       s_terminatingSpriteGraphicAttributes,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Set graphic terminating mode.

        status = SetGraphicTerminatingMode (dcHandle,
                                            spriteGraphicAttributesList,
                                            MAX_SEQUENCE_COUNT,
                                            g_soundResources.GetPlayerTerminatingSound ());
    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleCollision (const CollisionGrid::CellElements&   cellElements,
                                            CollisionGrid&                      collisionGrid,
                                            ObjectSpriteDrawingElementsList&    screenObjectSpriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // Handle any player sprite collision.

    for (CollisionGrid::CellElements::const_iterator itr = cellElements.begin ();
         (status == ERR_SUCCESS) && (itr != cellElements.end ());
         ++itr)
    {
        switch (itr->m_cellValue)
        {
        case CollisionGrid::CELL_VALUE_ITEM:
            // Handle the player sprite's collision with an item.

            status = HandleItemCollision (*itr, collisionGrid);
            break;

        case CollisionGrid::CELL_VALUE_SOLID_ITEM:
            // Handle the player sprite's collision with a solid item.

            status = HandleSolidItemCollision (*itr, collisionGrid);
            break;

        case CollisionGrid::CELL_VALUE_COLLECTABLE_ITEM:
            // Handle the player sprite's collision with a collectable item.

            status = HandleCollectableItemCollision (*itr, collisionGrid, screenObjectSpriteDrawingElementsList);
            break;

        case CollisionGrid::CELL_VALUE_NASTY_SPRITE:
            // Handle the player sprite's collision with a nasty sprite.

            status = HandleNastySpriteCollision (*itr, collisionGrid);
            break;

        case CollisionGrid::CELL_VALUE_BOSS_SPRITE:
            // Handle the player sprite's collision with a boss sprite.

            status = HandleBossSpriteCollision (*itr, collisionGrid);
            break;

         case CollisionGrid::CELL_VALUE_GAME_COMPLETE:
            // Handle the player sprite's collision with the game complete.

            status = HandleGameCompleteCollision (*itr, collisionGrid);
            break;

       default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleItemCollision (const CollisionGrid::CellElement&    cellElement,
                                               CollisionGrid&                       collisionGrid)
{
    // The player sprite has collided with a non-solid item. The only non-solid 
    // item on a screen is an orchid sprite.

    // Handle the player sprite's collision with the orchid sprite.

    OrchidSprite::ORCHID_SPRITE_TYPE        orchidSpriteType    = OrchidSprite::ORCHID_TYPE_UNDEFINED;
    Folio::Core::Game::ZxSpectrum::COLOUR   orchidSpriteColour  = Folio::Core::Game::ZxSpectrum::UNDEFINED;

    FolioStatus status = g_orchidSpriteDrawingElement.m_sprite->HandlePlayerCollision (orchidSpriteType, 
                                                                                       orchidSpriteColour);

    if (status == ERR_SUCCESS)
    {            
        // Set the player sprite's infection.

        switch (orchidSpriteType)
        {
        case OrchidSprite::IMMUNITY:
            status = SetInfection (IMMUNITY, orchidSpriteColour);
            break;

        case OrchidSprite::CONFUSION:
            status = SetInfection (CONFUSION, orchidSpriteColour);
            break;
    
        case OrchidSprite::SPEED: 
            status = SetInfection (SPEED, orchidSpriteColour);
            break;
    
        case OrchidSprite::SICKNESS:
            status = SetInfection (SICKNESS, orchidSpriteColour);

            if (status == ERR_SUCCESS)
            {
                // Remove all the screen's nasty sprites.

                status = RemoveScreenNastySprites (collisionGrid);
            } // Endif.
            break;
    
        case OrchidSprite::CURE:
            status = ClearInfection ();
            break;

        case OrchidSprite::ORCHID_TYPE_UNDEFINED:
        default:
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleSolidItemCollision (const CollisionGrid::CellElement&   cellElement,
                                                    CollisionGrid&                      collisionGrid)
{
    // The player sprite has collided with a solid item.
    
    // Get the player sprite's screen rect.

    Gdiplus::Rect   playerScreenRect(GetScreenRect ());

    // The player sprite is bound to the solid item.

    collisionGrid.ToScreenRectBound (GetDirection (), 
                                     cellElement.m_collisionGridRect,
                                     playerScreenRect);

    // Set the player sprite's screen position.

    return (SetScreenTopLeft (playerScreenRect.X, playerScreenRect.Y));
} // Endproc.


FolioStatus PlayerSprite::HandleCollectableItemCollision (const CollisionGrid::CellElement& cellElement,
                                                          CollisionGrid&                    collisionGrid,
                                                          ObjectSpriteDrawingElementsList&  screenObjectSpriteDrawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    // The player sprite has collided with a collectable item. The only 
    // collectable item on a screen is an object sprite.

    // Find the collectable object sprite that the player sprite has 
    // collided with.

    bool    found = false;  // Initialise!

    ObjectSpriteDrawingElementsList::iterator itr = screenObjectSpriteDrawingElementsList.begin ();

    do
    {
        // Get the object sprite.

        ObjectSpritePtr &objectSprite(itr->m_sprite);

        // Is this the collectable object sprite that the player sprite 
        // has collided with?

        if (objectSprite.get () == cellElement.m_userData)
        {
            // Yes. 
                
            found = true;   // Found the collectable object sprite.
                
            // Handle the player sprite's collision with the object sprite.

            status = objectSprite->HandlePlayerCollision (m_justFoundAmuletPiece);
                    
            if (status == ERR_SUCCESS)
            {
                // Remove the object sprite from the screen's collision grid.

                status = collisionGrid.RemoveCellElement (cellElement);

                if (status == ERR_SUCCESS)
                {
                    // Remove the object sprite from the screen's object sprite 
                    // drawing elements list.

                    itr = screenObjectSpriteDrawingElementsList.erase (itr);
                } // Endif.

            } // Endif.

        } // Endif.

        else
        {
            ++itr;  // Next.
        } // Endelse.

    } // Enddo.
    while (!found                   &&
           (status == ERR_SUCCESS)  &&        
           (itr != screenObjectSpriteDrawingElementsList.end ()));

    // Did we find the collectable object sprite that the player sprite has 
    // collided with?

    if (!found && (status == ERR_SUCCESS))
    {
        // No.

        status = ERR_INTERNAL_ERROR;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleNastySpriteCollision (const CollisionGrid::CellElement& cellElement,
                                                      CollisionGrid&                    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // The player sprite has collided with a nasty sprite.

    // Is the player sprite NOT immune?

    if (!IsImmune ())
    {
        // Yes. Get the current screen map index.

        UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

        // Find the nasty sprite that the player sprite has collided with.

        bool    found = false;  // Initialise!

        for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
             !found && (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
             ++itr)
        {              
            // Get the nasty sprite.

            NastySpritePtr  &nastySprite(itr->m_sprite);

            // Is the nasty sprite on the current screen that the player sprite 
            // has collided with?

            if ((nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex) && 
                (nastySprite.get () == cellElement.m_userData))
            {
                // Yes. 
            
                found = true;   // Found the nasty sprite.
            
                // Check if the player sprite is dead.

                if (CheckPlayerSpriteDead (*nastySprite))
                {
                    // Yes. Remove all the screen's nasty sprites.

                    status = RemoveScreenNastySprites (collisionGrid);
                } // Endif.

                else
                {
                    // No. Remove the nasty sprite from the screen's collision grid.

                    status = collisionGrid.RemoveCellElement (cellElement);

                    if (status == ERR_SUCCESS)
                    {
                        // The nasty sprite is dead.

                        nastySprite->SetDead ();
                    } // Endif.

                } // Endelse.

                if (status == ERR_SUCCESS)
                {
                    // Add to the player's score.

                    g_informationPanel->AddPlayerScore (InformationPanel::SCORE_NASTY_SPRITE_DEAD);
                } // Endif.

            } // Endif.

        } // Endfor.
    
        // Did we find the nasty sprite that the player sprite has collided with?

        if (!found && (status == ERR_SUCCESS))
        {
            // No.

            status = ERR_INTERNAL_ERROR;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleBossSpriteCollision (const CollisionGrid::CellElement&  cellElement,
                                                     CollisionGrid&                     collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // The player sprite has collided with a boss sprite.

    // Is the player sprite NOT immune?

    if (!IsImmune ())
    {
        // Yes. Get the current screen map index.

        UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

        // Find the boss sprite that the player sprite has collided with.

        bool    found = false;  // Initialise!

        for (BossSpriteDrawingElementsList::iterator itr = g_bossSpriteDrawingElementsList.begin ();
             !found && (status == ERR_SUCCESS) && (itr != g_bossSpriteDrawingElementsList.end ());
             ++itr)
        {              
            // Get the boss sprite.

            BossSpritePtr  &bossSprite(itr->m_sprite);

            // Is the boss sprite on the current screen that the player sprite 
            // has collided with?

            if ((bossSprite->GetBossSpriteScreenMapIndex () == currentScreenMapIndex) && 
                (bossSprite.get () == cellElement.m_userData))
            {
                // Yes. 
            
                found = true;   // Found the boss sprite.
            
                // Check if the player sprite is dead.

                bool    changeDirection = false;    // Initialise!

                if (CheckPlayerSpriteDead (*bossSprite, &(changeDirection)))
                {
                    // Yes. Remove all the screen's nasty sprites.

                    status = RemoveScreenNastySprites (collisionGrid);

                    if (changeDirection && (status == ERR_SUCCESS))
                    {
                        // Yes. Change the direction of the boss sprite.

                        status = bossSprite->ChangeDirection ();
                    } // Endif.

                } // Endif.

                // Should the boss sprite change direction?.

                else
                if (changeDirection)
                {
                    // Yes. Play the player striking boss sound.

                    status = g_soundResources.PlayPlayerStrikingBossSound ();

                    if (status == ERR_SUCCESS)
                    {
                        // Change the direction of the boss sprite.

                        status = bossSprite->ChangeDirection ();
                    } // Endif.

                } // Endelseif.

                else
                {
                    // No. Play the player striking boss sound.

                    status = g_soundResources.PlayPlayerStrikingBossSound ();

                    if (status == ERR_SUCCESS)
                    {
                        // Change the speed of the boss sprite.

                           status = bossSprite->ChangeSpeed ();
                    } // Endif.
                
                } // Endelse.

            } // Endif.

        } // Endfor.
    
        // Did we find the boss sprite that the player sprite has collided with?

        if (!found && (status == ERR_SUCCESS))
        {
            // No.

            status = ERR_INTERNAL_ERROR;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleGameCompleteCollision (const CollisionGrid::CellElement&    cellElement,
                                                       CollisionGrid&                       collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // The player sprite has collided with the game complete.

    // Is the player sprite entering the game complete?

    if (m_direction & Folio::Core::Game::N)
    {
        // Yes. The player has completed the game!!

        SetGameCompleted ();
    } // Endif.

    else
    {
        // Treat the game complete as a solid item.

        status = HandleSolidItemCollision (cellElement, collisionGrid);
    } // Endelse.

    return (status);
} // Endproc.


bool    PlayerSprite::CheckPlayerSpriteDead (const Folio::Core::Game::ASprite&  nastySprite, 
                                             bool*                              changeDirection)
{
    if (changeDirection)
    {
        *changeDirection = false;
    } // Endif.

    bool    isDead = false; // Initialise!

    // The player sprite cannot be dead if the player sprite is immune.

    if (!IsImmune ())
    {
        // Get the direction of the nasty (or boss) sprite.
        
        Folio::Core::Game::Direction    nastySpirteDirection = nastySprite.GetDirection ();

        // Get the screen rect of the nasty (or boss) sprite.
        
        Gdiplus::Rect   nastySpriteCollisionRect = nastySprite.GetScreenRect ();

        // The player sprite may be dead, depending on the player sprite's action.

        switch (m_action)
        {
        case ACTION_SWIPE_SWORD:
            // Depending on the orientation of the player sprite to the nasty 
            // (or boss) sprite, the player sprite may or may not be dead.
            //              
            // If the player sprite is moving in the same direction to the 
            // nasty (or boss) sprite, and the nasty (or boss) sprite is behind 
            // the player sprite, then the player sprite is dead.

            switch (nastySpirteDirection)
            {
            case Folio::Core::Game::E:
            case Folio::Core::Game::NE:
            case Folio::Core::Game::SE:
                isDead = ((nastySpriteCollisionRect.X <= m_screenRect.X) &&
                         ((m_direction & Folio::Core::Game::E) || 
                        (((m_previousHorizontalDirection & Folio::Core::Game::E)) &&
                         ((m_direction == Folio::Core::Game::N) || (m_direction == Folio::Core::Game::S)))));

                // If the player sprite is not dead, should the nasty (or 
                // bosss) sprite change direction?
                //              
                // If the player sprite is moving in the opposite direction to 
                // the nasty (or boss) sprite, then the nasty (or boss) sprite 
                // should change direction.

                if (!isDead && changeDirection)
                {
                    *changeDirection = (m_direction & Folio::Core::Game::W) || 
                                     (((m_previousHorizontalDirection & Folio::Core::Game::W)) &&
                                      ((m_direction == Folio::Core::Game::N) || (m_direction == Folio::Core::Game::S)));
                } // Endif.
                break;
            
            case Folio::Core::Game::W:
            case Folio::Core::Game::NW:
            case Folio::Core::Game::SW:
                isDead = ((nastySpriteCollisionRect.X >= m_screenRect.X) &&
                         ((m_direction & Folio::Core::Game::W) || 
                        (((m_previousHorizontalDirection & Folio::Core::Game::W)) &&
                         ((m_direction == Folio::Core::Game::N) || (m_direction == Folio::Core::Game::S)))));

                // If the player sprite is not dead, should the nasty (or 
                // bosss) sprite change direction?
                //              
                // If the player sprite is moving in the opposite direction to 
                // the nasty (or boss) sprite, then the nasty (or boss) sprite 
                // should change direction.

                if (!isDead && changeDirection)
                {
                    *changeDirection = (m_direction & Folio::Core::Game::E) || 
                                     (((m_previousHorizontalDirection & Folio::Core::Game::E)) &&
                                      ((m_direction == Folio::Core::Game::N) || (m_direction == Folio::Core::Game::S)));
                } // Endif.
                break;

            case Folio::Core::Game::N:
            case Folio::Core::Game::S:
            default:
                isDead = true;
                break;
            } // Endswitch.
            break;

        case ACTION_FALLING:    
        case ACTION_SITTING:    
        case ACTION_LYING_DEAD:  
            // The player sprite cannot be dead if already dead or dying.

            isDead = false;
            break;

        case Folio::Core::Game::NO_ACTION:
        default:
            isDead = true;

            // If the player sprite is moving in the opposite direction to 
            // the nasty (or boss) sprite, then the nasty (or boss) sprite 
            // should change direction.

            switch (nastySpirteDirection)
            {
            case Folio::Core::Game::E:
            case Folio::Core::Game::NE:
            case Folio::Core::Game::SE:
                if (changeDirection)
                {
                    *changeDirection = !(m_direction & Folio::Core::Game::E);
                } // Endif.
                break;
            
            case Folio::Core::Game::W:
            case Folio::Core::Game::NW:
            case Folio::Core::Game::SW:
                if (changeDirection)
                {
                    *changeDirection = !(m_direction & Folio::Core::Game::W);
                } // Endif.
                break;

            case Folio::Core::Game::N:
                if (changeDirection)
                {
                    *changeDirection = !(m_direction & Folio::Core::Game::N);
                } // Endif.
                break;

            case Folio::Core::Game::S:
                if (changeDirection)
                {
                    *changeDirection = !(m_direction & Folio::Core::Game::S);
                } // Endif.
                break;

            default:
                break;
            } // Endswitch.

            break;
        } // Endswitch.

        if (isDead)
        {
            // The player sprite is dead. Based on the direction of the nasty 
            // (or boss sprite), determine if the player sprite should be 
            // falling.

            switch (nastySpirteDirection)
            {
            case Folio::Core::Game::E:
            case Folio::Core::Game::NE:
            case Folio::Core::Game::SE:
                // The player sprite is falling.

                SetFalling (Folio::Core::Game::E);
                break;

            case Folio::Core::Game::W:
            case Folio::Core::Game::NW:
            case Folio::Core::Game::SW:
                // The player sprite is falling.

                SetFalling (Folio::Core::Game::W);
                break;

            case Folio::Core::Game::N:
            case Folio::Core::Game::S:
            default:
                // The player sprite is dead.

                SetDead ();
                break;
            } // Endswitch.

        } // Endif.

    } // Endif.

    return (isDead);
} // Endproc.


FolioStatus PlayerSprite::SetInfection (INFECTION                               infection,
                                        Folio::Core::Game::ZxSpectrum::COLOUR   playerSpriteColour)
{
    FolioStatus status = ERR_SUCCESS;
    
    // Set the player sprite's action depending on the infection.

    if (infection == SICKNESS)
    {
        // The player sprite is sitting.

        status = SetSitting ();
    } // Endif.
    
    else
    if (IsAction (ACTION_SITTING))
    {
        status = ResetSitting ();
    } // Endelseif.

    if (status == ERR_SUCCESS)
    {
        // Reset the number of remaining auto-mode moves.

        ResetNumRemainingAutoModeMoves ();

        // Change the player sprite's colour.

        status = ChangeSpriteInkColour (Folio::Core::Game::ZxSpectrum::MapInkColour (playerSpriteColour),   
                                        false,  // Don't change the player sprite's initialising graphics. 
                                        false); // Don't change the player sprite's terminating graphics.

        if (status == ERR_SUCCESS)
        {
            // Set the player sprite's infection colour.

            m_infectionColour       = playerSpriteColour; 
            m_infectionColourSet    = true;
            
            // Set the player sprite's state.

            switch (infection)
            {
            case NO_INFECTION:
                break;

            case SICKNESS:
                SetState (STATE_STATIC);
                break;

            case IMMUNITY:
            case CONFUSION:
            case SPEED:
            default:
                SetState (STATE_MOVING);
                break;
            } // Endswitch.

            // Set the player sprite's speed.

            switch (infection)
            {
            case SPEED:
                m_playerSpriteSpeed = FAST_SPEED;
                break;

            case SICKNESS:
                m_playerSpriteSpeed = STATIC_SPEED;
                break;

            case NO_INFECTION:
            case IMMUNITY:
            case CONFUSION:
            default:
                m_playerSpriteSpeed = DEFAULT_SPEED;
                break;
            } // Endswitch.

            // Set the player sprite's infection.

            m_infection = infection;

            if (infection == NO_INFECTION)
            {
                // Reset the infection tick count.

                ResetInfectionTickCount ();
            } // Endif.

            else
            {
                // Start the infection tick count.

                StartInfectionTickCount ();
            } // Endelse.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::ClearInfection ()
{
    return (SetInfection (NO_INFECTION, INITIAL_COLOUR));   
} // Endproc.


FolioStatus PlayerSprite::InfectionFinishing ()
{
    // Play the player infection finishing sound.

    FolioStatus status = g_soundResources.PlayPlayerInfectionFinishingSound ();

    if (status == ERR_SUCCESS)
    {
        // Toggle the player sprite's colour.

        status = ChangeSpriteInkColour (Folio::Core::Game::ZxSpectrum::MapInkColour (m_infectionColourSet ? INITIAL_COLOUR : m_infectionColour),   
                                                                                     false,  // Don't change the player sprite's initialising graphics. 
                                                                                     false); // Don't change the player sprite's terminating graphics.

        if (status == ERR_SUCCESS)
        {
            m_infectionColourSet = !m_infectionColourSet;
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


void    PlayerSprite::StartInfectionTickCount ()
{
    m_infectionTickCount    = Folio::Core::Util::DateTime::GetCurrentTickCount () + INFECTION_TICK_COUNT;
    m_infectionCountdown    = INFECTION_COUNTDOWN;
} // Endproc.


void    PlayerSprite::ResetInfectionTickCount ()
{
    m_infectionTickCount    = 0;
    m_infectionCountdown    = INFECTION_COUNTDOWN;
} // Endproc.


bool    PlayerSprite::IsImmune () const
{
    // If the player sprite has any infection then it is immune.

    return (IsInfection ());
} // Endproc.


bool    PlayerSprite::IsInfection () const
{
    return (m_infection != NO_INFECTION);
} // Endproc.


bool    PlayerSprite::IsInfectionFinishing () const
{
    bool    isInfectionFinishing = (IsInfection () && 
                                    (static_cast<Int32> ((m_infectionTickCount - Folio::Core::Util::DateTime::GetCurrentTickCount ()) / 500) <= m_infectionCountdown));

    if (isInfectionFinishing)
    {
        m_infectionCountdown--; // Decrement the infection countdown.
    } // Endif.

    return (isInfectionFinishing);
} // Endproc.


bool    PlayerSprite::IsInfectionFinished () const
{
    return (IsInfection () &&
            (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_infectionTickCount));
} // Endproc.


bool    PlayerSprite::IsInfectionImmunity () const
{
    return (m_infection == IMMUNITY);
} // Endproc.


bool    PlayerSprite::IsInfectionConfusion () const
{
    return (m_infection == CONFUSION);
} // Endproc.


bool    PlayerSprite::IsInfectionSickness () const
{
    return (m_infection == SICKNESS);
} // Endproc.


FolioStatus PlayerSprite::SetSwipeSword ()
{
    // Set the player sprite's swipe sword action.

    FolioStatus status = SetAction (ACTION_SWIPE_SWORD);

    if (status == ERR_SUCCESS)
    {
        // Set the player sprite's speed.

        m_playerSpriteSpeed = SWIPE_SWORD_SPEED;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::ResetSwipeSword ()
{
    // Reset the player sprite's action.

    FolioStatus status = ResetAction ();

    if (status == ERR_SUCCESS)
    {
        // Set the player sprite's speed.
        
        m_playerSpriteSpeed = DEFAULT_SPEED;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::SetSitting ()
{
    // Set the player sprite's sitting action.

    return (SetAction (ACTION_SITTING));
} // Endproc.


FolioStatus PlayerSprite::ResetSitting ()
{
    // Reset the player sprite's action.

    return (ResetAction ());
} // Endproc.


FolioStatus PlayerSprite::SetFalling (Folio::Core::Game::Direction direction)
{
    // Set the player sprite's direction.
    
    FolioStatus status = SetDirection (direction);

    if (status == ERR_SUCCESS)
    {
        // The player sprite is falling.
    
        status = SetAction (ACTION_FALLING);

        if (status == ERR_SUCCESS)
        {
            // Reset the number of remaining auto-mode moves.

            ResetNumRemainingAutoModeMoves ();

            // The player sprite is moving.

            SetState (STATE_MOVING);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::ResetFalling ()
{
    // Toggle the player sprite's direction.
    
    FolioStatus status = SetDirection ((GetDirection () == Folio::Core::Game::E) 
                                       ? Folio::Core::Game::W 
                                       : Folio::Core::Game::E);
                
    if (status == ERR_SUCCESS)
    {
        // Reset the player sprite's action.

        status = ResetAction ();

        if (status == ERR_SUCCESS)
        {
            // The player sprite is static.

            SetState (STATE_STATIC);
        } // Endif.

    } // Endif.

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


Int32   PlayerSprite::CalculateMovingXLeft (Int32 bitmapScreenWidth) const
{
    // Is the player sprite performing the swipe sword action?

    if (IsAction (ACTION_SWIPE_SWORD))
    {
        switch (m_direction)
        {
        case Folio::Core::Game::N:
        case Folio::Core::Game::S:
            if (m_previousHorizontalDirection == Folio::Core::Game::W)
            {
                return (m_screenRect.X + m_screenRect.Width - m_movingRect.Width);
            } // Endif.
            break;

        case Folio::Core::Game::W:
        case Folio::Core::Game::NW:
        case Folio::Core::Game::SW:
            return (m_screenRect.X + m_screenRect.Width - m_movingRect.Width);

        case Folio::Core::Game::E:
        case Folio::Core::Game::NE:
        case Folio::Core::Game::SE:
        default:
            break;
        } // Endswitch.

    } // Endif.

    return (APlayerSprite::CalculateMovingXLeft (bitmapScreenWidth));
} // Endproc.


Int32   PlayerSprite::CalculateScreenXLeft (Folio::Core::Game::ACollisionGrid::DIRECTION collisionGridDirection) const
{
    return (CalculateScreenXLeft (m_screenRect.Width));
} // Endproc.


Int32   PlayerSprite::CalculateScreenXLeft (Int32 bitmapScreenWidth) const
{
    switch (m_direction)
    {
    case Folio::Core::Game::N:
    case Folio::Core::Game::S:
        if (m_previousHorizontalDirection == Folio::Core::Game::W)
        {
            return (m_movingRect.X + m_movingRect.Width - bitmapScreenWidth);
        } // Endif.
        break;

    case Folio::Core::Game::W:
    case Folio::Core::Game::NW:
    case Folio::Core::Game::SW:
        return (m_movingRect.X + m_movingRect.Width - bitmapScreenWidth);

    case Folio::Core::Game::E:
    case Folio::Core::Game::NE:
    case Folio::Core::Game::SE:
    default:
        break;
    } // Endswitch.

    return (GetMovingXLeft ());
} // Endproc.


FolioStatus CreatePlayerSprite (FolioHandle         dcHandle, 
                                PlayerSpritePtr&    playerSprite)
{
    // Create the player sprite.

    playerSprite.reset (new PlayerSpritePtr::element_type);

    return (playerSprite->Create (dcHandle));
} // Endproc.


FolioStatus StorePlayerSpriteBackground (Gdiplus::Graphics& graphics)
{
    return (g_playerSprite->StoreUnderlyingBackground (graphics));
} // Endproc.


FolioStatus RestorePlayerSpriteBackground (Gdiplus::Graphics& graphics)
{
    return (g_playerSprite->RestoreUnderlyingBackground (graphics));
} // Endproc.


FolioStatus DrawPlayerSprite (Gdiplus::Graphics& graphics)
{
    return (g_playerSprite->Draw (graphics));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
