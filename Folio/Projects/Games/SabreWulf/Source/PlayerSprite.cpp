// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
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
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_RIGHT, SPRITE_SABRE_MAN_WALKING_RIGHT_1, SPRITE_SABRE_MAN_RIGHT, SPRITE_SABRE_MAN_WALKING_RIGHT_2,                                                                                                                                             },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_LEFT, SPRITE_SABRE_MAN_WALKING_LEFT_1, SPRITE_SABRE_MAN_LEFT, SPRITE_SABRE_MAN_WALKING_LEFT_2,                                                                                                                                                 },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::N,   {   SPRITE_SABRE_MAN_UP, SPRITE_SABRE_MAN_WALKING_UP_1, SPRITE_SABRE_MAN_UP, SPRITE_SABRE_MAN_WALKING_UP_2,                                                                                                                                                         },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::S,   {   SPRITE_SABRE_MAN_DOWN, SPRITE_SABRE_MAN_WALKING_DOWN_1, SPRITE_SABRE_MAN_DOWN, SPRITE_SABRE_MAN_WALKING_DOWN_2,                                                                                                                                                 },                                      },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_SWORD_RIGHT_1, SPRITE_SABRE_MAN_SWORD_RIGHT_2, SPRITE_SABRE_MAN_SWORD_RIGHT_3, SPRITE_SABRE_MAN_SWORD_RIGHT_4, SPRITE_SABRE_MAN_SWORD_RIGHT_5, SPRITE_SABRE_MAN_SWORD_RIGHT_4, SPRITE_SABRE_MAN_SWORD_RIGHT_6, SPRITE_SABRE_MAN_SWORD_RIGHT_2, },  PlayerSprite::ACTION_SWIPE_SWORD,   },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_SWORD_LEFT_1, SPRITE_SABRE_MAN_SWORD_LEFT_2, SPRITE_SABRE_MAN_SWORD_LEFT_3, SPRITE_SABRE_MAN_SWORD_LEFT_4, SPRITE_SABRE_MAN_SWORD_LEFT_5, SPRITE_SABRE_MAN_SWORD_LEFT_4, SPRITE_SABRE_MAN_SWORD_LEFT_6, SPRITE_SABRE_MAN_SWORD_LEFT_2,         },  PlayerSprite::ACTION_SWIPE_SWORD,   },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_FALLING_RIGHT,                                                                                                                                                                                                                                 },  PlayerSprite::ACTION_FALLING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_FALLING_LEFT,                                                                                                                                                                                                                                  },  PlayerSprite::ACTION_FALLING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_SITTING_RIGHT,                                                                                                                                                                                                                                 },  PlayerSprite::ACTION_SITTING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_SITTING_LEFT,                                                                                                                                                                                                                                  },  PlayerSprite::ACTION_SITTING,       },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_GAME_OVER_RIGHT,                                                                                                                                                                                                                               },  PlayerSprite::ACTION_GAME_OVER,     },
    {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_GAME_OVER_LEFT,                                                                                                                                                                                                                                },  PlayerSprite::ACTION_GAME_OVER,     },
};


PlayerSprite::PlayerSprite ()
:   m_playerSpriteSpeed(DEFAULT_SPEED),
    m_infection(NO_INFECTION),
    m_infectionTickCount(0),
    m_justFoundAmuletPiece(false)
{
} // Endproc.


PlayerSprite::~PlayerSprite ()
{
} // Endproc.


FolioStatus PlayerSprite::Create (FolioHandle dcHandle)
{
    static  const   UInt32  MAX_NUM_AUTO_MOVES = 3;

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

    // Is the player sprite sick?

    if (!IsInfectionSickness ())
    {
        // No. Is a key down?

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
    case STATE_TERMINATED:
        // Decrement the player sprite's life.

        status = g_informationPanel->DecrementPlayerLife (&(g_playerSprite));
        break;

    case STATE_INITIALISED:
    case STATE_STATIC:
    case STATE_MOVING:
        // Is the player sprite's infection finished?

        if (IsInfectionFinished ())
        {
            // Yes. Clear the player sprite's infection.

            status = ClearInfection ();
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            status = (m_state == STATE_MOVING) && (m_playerSpriteSpeed != STATIC_SPEED) 
                     ? Folio::Core::Game::APlayerSprite::Move (graphics, m_playerSpriteSpeed, collisionGrid)
                     : Folio::Core::Game::APlayerSprite::Static (graphics, collisionGrid);

            // Has the player sprite exited the screen?

            if ((status == ERR_SUCCESS) && !IsExitedScreen ())
            {
                // No. Has the player sprite collided with something?

                CollisionGrid::CellElements cellElements;

                if (collisionGrid.IsCollision (g_playerSprite->GetCollisionRect (), 
                                               cellElements))
                {
                    // Yes. Handle the collision.

                    status = HandleCollision (cellElements, 
                                              collisionGrid, 
                                              screenObjectSpriteDrawingElementsList);
                } // Endif.
            
            } // Endif.
        
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::SetFireKeyDown (bool fireKeyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the player sprite NOT infected and ready?

    if (!IsInfection () && IsReady ())
    {
        // Yes. Is the fire key down?

        if (fireKeyDown)
        {
            // Yes. Set the player sprite's swipe sword action.

            status = SetAction (ACTION_SWIPE_SWORD);

            if (status == ERR_SUCCESS)
            {
                m_playerSpriteSpeed = SWIPE_SWORD_SPEED;
            } // Endif.

        } // Endif.
    
        // Is the player sprite performing an action?

        else
        if (IsAction ())
        {
            // Yes. Reset the player sprite's action.

            status = SetAction (Folio::Core::Game::NO_ACTION);

            if (status == ERR_SUCCESS)
            {
                m_playerSpriteSpeed = DEFAULT_SPEED;
            } // Endif.

        } // Endelseif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::SetGameOver ()
{
    // Set the player sprite's game over action.

    FolioStatus status = SetAction (ACTION_GAME_OVER);

    if (status == ERR_SUCCESS)
    {
        // The player sprite's game is over.

        APlayerSprite::SetGameOver ();
    } // Endif.

    return (status);
} // Endproc.


bool    PlayerSprite::IsImmune () const
{
    // If the player sprite has any infection then it is immune.

    return (IsInfection ());
} // Endproc.


bool    PlayerSprite::IsSick () const
{
    return (IsInfectionSickness ());
} // Endproc.


void    PlayerSprite::ResetJustFoundAmuletPiece ()
{
    m_justFoundAmuletPiece = false;
} // Endproc.


bool    PlayerSprite::IsJustFoundAmuletPiece () const
{
    return (m_justFoundAmuletPiece);
} // Endproc.


FolioStatus PlayerSprite::SetTerminatingMode (FolioHandle dcHandle)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 6;

    // Player sprite terminating sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<PLAYER_SPRITE_ID, SPRITE_ID>    s_terminatingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction             m_spriteGraphicIdsList
        {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::W,   {   SPRITE_SABRE_MAN_SITTING_LEFT,  },  },
        {   PLAYER_SPRITE_SABRE_MAN,    Folio::Core::Game::E,   {   SPRITE_SABRE_MAN_SITTING_RIGHT, },  },
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
                                            MAX_SEQUENCE_COUNT);
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

            //status = HandleBossSpriteCollision (*itr, collisionGrid);
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
    FolioStatus status = ERR_SUCCESS;

    // The player sprite has collided with a non-solid item. The only non-solid 
    // item on a screen is an orchid sprite.

    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Get the orchid sprite.

        OrchidSpritePtr &orchidSprite(g_orchidSpriteDrawingElement.m_sprite);

        // Handle the player sprite's collision with the orchid sprite.

        OrchidSprite::ORCHID_SPRITE_TYPE        orchidSpriteType    = OrchidSprite::ORCHID_TYPE_UNDEFINED;
        Folio::Core::Game::ZxSpectrum::COLOUR   orchidSpriteColour  = Folio::Core::Game::ZxSpectrum::UNDEFINED;

        status = orchidSprite->HandlePlayerCollision (orchidSpriteType, orchidSpriteColour);

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

    } // Endif.

    else
    {
        status = ERR_INTERNAL_ERROR;
    } // Endelse.

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
                                     cellElement.m_screenRect,
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

    // Any current screen object sprites?

    if (!screenObjectSpriteDrawingElementsList.empty ())
    {
        // Find the collectable object sprite that the player sprite has 
        // collided with.

        ObjectSpriteDrawingElementsList::iterator   itr = screenObjectSpriteDrawingElementsList.begin ();

        bool    found = false;  // Initialise!

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
                        // Remove the object sprite from the screen's object 
                        // sprite drawing elements list.

                        screenObjectSpriteDrawingElementsList.erase (itr);
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

    } // Endif.

    else
    {
        status = ERR_INTERNAL_ERROR;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus PlayerSprite::HandleNastySpriteCollision (const CollisionGrid::CellElement& cellElement,
                                                      CollisionGrid&                    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // The player sprite has collided with a nasty sprite.

    // Get the current screen map index.

    UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

    // Find the nasty sprite that the player sprite has collided with.

    bool    found = false;  // Initialise!

    for (NastySpriteDrawingElementsList::iterator itr = g_nastySpriteDrawingElementsList.begin ();
         !found && (status == ERR_SUCCESS) && (itr != g_nastySpriteDrawingElementsList.end ());
         ++itr)
    {              
        // Get the nasty sprite.

        NastySpritePtr  &nastySprite(itr->m_sprite);

        // Is the nasty sprite on the current screen that the player sprite has 
        // collided with?

        if ((nastySprite->GetNastySpriteScreenMapIndex () == currentScreenMapIndex) && 
            (nastySprite.get () == cellElement.m_userData))
        {
            // Yes. 
            
            found = true;   // Found the nasty sprite.
            
            // Is the nasty sprite ready and the player sprite 
            // NOT immune?
            
            if (nastySprite->IsReady () && !IsImmune ())
            {
                // Yes. Is the player sprite dead?

                if (IsDead (cellElement))
                {
                    // Yes. Remove all the screen's nasty sprites.

                    status = RemoveScreenNastySprites (collisionGrid);
                } // Endif.

                if (status == ERR_SUCCESS)
                {
                    // Add to the player's score.

                    g_informationPanel->AddPlayerScore (InformationPanel::SCORE_NASTY_SPRITE_DEAD);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


bool    PlayerSprite::IsDead (const CollisionGrid::CellElement& cellElement)
{
    //ia 
    return (true);

    // The player sprite cannot be dead if the player sprite is immune.

    bool    isDead = !IsImmune ();

    if (isDead)
    {
        // The player sprite is dead depending on the player sprite's action.

        switch (m_action)
        {
        case ACTION_SWIPE_SWORD:
            // Depending on the orientation of the player sprite to the nasty 
            // sprite, the player sprite may or may not be dead.
                
            // Get the direction of the nasty sprite.

            switch (reinterpret_cast<NastySprite *> (cellElement.m_userData)->GetDirection ())
            {
            case Folio::Core::Game::E:
            case Folio::Core::Game::NE:
            case Folio::Core::Game::SE:
                isDead = (m_direction & Folio::Core::Game::E) || 
                       (((m_direction == Folio::Core::Game::N) || (m_direction == Folio::Core::Game::S)) && 
                         (m_previousHorizontalDirection & Folio::Core::Game::E));
                break;
            
            case Folio::Core::Game::W:
            case Folio::Core::Game::NW:
            case Folio::Core::Game::SW:
                isDead = (m_direction & Folio::Core::Game::W) || 
                       (((m_direction == Folio::Core::Game::N )|| (m_direction == Folio::Core::Game::S)) && 
                         (m_previousHorizontalDirection & Folio::Core::Game::W));
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
        case ACTION_GAME_OVER:  
            // The player sprite cannot be dead if already dead or dying.

            isDead = false;
            break;

        case Folio::Core::Game::NO_ACTION:
        default:
            isDead = true;
            break;
        } // Endswitch.

    } // Endif.

    if (isDead)
    {
        // The player sprite is dead.

        SetDead ();
    } // Endif.

    return (isDead);
} // Endproc.


FolioStatus PlayerSprite::SetInfection (INFECTION                               infection,
                                        Folio::Core::Game::ZxSpectrum::COLOUR   playerSpriteColour)
{
    // Set the player sprite's action depending on the infection.

    FolioStatus status = SetAction ((infection == SICKNESS) 
                         ? ACTION_SITTING 
                         : Folio::Core::Game::NO_ACTION);

    if (status == ERR_SUCCESS)
    {
        // Change the player sprite's colour.

        status = ChangeSpriteInkColour (Folio::Core::Game::ZxSpectrum::MapInkColour (playerSpriteColour),   
                                        false,  // Don't change the player sprite's initialising graphics. 
                                        false); // Don't change the player sprite's terminating graphics.

        if (status == ERR_SUCCESS)
        {
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
                m_infectionTickCount = 0;   // Reset.
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


void    PlayerSprite::StartInfectionTickCount ()
{
    m_infectionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                           1000 * Folio::Core::Util::Random::GetRandomNumber (5, 8);
} // Endproc.


bool    PlayerSprite::IsInfection () const
{
    return (m_infection != NO_INFECTION);
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


Int32   PlayerSprite::CalculateCollisionXLeft () const
{
    if (m_action == ACTION_SWIPE_SWORD)
    {
        switch (m_direction)
        {
        case Folio::Core::Game::N:
        case Folio::Core::Game::S:
            if (m_previousHorizontalDirection == Folio::Core::Game::W)
            {
                return (m_screenRect.X + m_screenRect.Width - m_collisionRect.Width);
            } // Endif.
            break;

        case Folio::Core::Game::W:
        case Folio::Core::Game::NW:
        case Folio::Core::Game::SW:
            return (m_screenRect.X + m_screenRect.Width - m_collisionRect.Width);

        case Folio::Core::Game::E:
        case Folio::Core::Game::NE:
        case Folio::Core::Game::SE:
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
    case Folio::Core::Game::N:
    case Folio::Core::Game::S:
        if (m_previousHorizontalDirection == Folio::Core::Game::W)
        {
            return (m_collisionRect.X + m_collisionRect.Width - m_screenRect.Width);
        } // Endif.
        break;

    case Folio::Core::Game::W:
    case Folio::Core::Game::NW:
    case Folio::Core::Game::SW:
        return (m_collisionRect.X + m_collisionRect.Width - m_screenRect.Width);

    case Folio::Core::Game::E:
    case Folio::Core::Game::NE:
    case Folio::Core::Game::SE:
    default:
        break;
    } // Endswitch.

    return (m_collisionRect.X);
} // Endproc.


Int32   PlayerSprite::CalculateScreenXLeft (Int32 bitmapScreenWidth) const
{
    switch (m_direction)
    {
    case Folio::Core::Game::N:
    case Folio::Core::Game::S:
        if (m_previousHorizontalDirection == Folio::Core::Game::W)
        {
            return (m_collisionRect.X + m_collisionRect.Width - bitmapScreenWidth);
        } // Endif.
        break;

    case Folio::Core::Game::W:
    case Folio::Core::Game::NW:
    case Folio::Core::Game::SW:
        return (m_collisionRect.X + m_collisionRect.Width - bitmapScreenWidth);

    case Folio::Core::Game::E:
    case Folio::Core::Game::NE:
    case Folio::Core::Game::SE:
    default:
        break;
    } // Endswitch.

    return (m_collisionRect.X);
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
