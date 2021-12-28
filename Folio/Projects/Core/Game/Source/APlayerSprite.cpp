// "Home-made" includes.
#include    "APlayerSprite.h"

namespace Folio
{

namespace Core
{

namespace Game
{

APlayerSprite::APlayerSprite ()
:   m_inAutoMoveMode(false),
    m_isGameOver(false),
    m_isGameCompleted(false)
{
} // Endproc.


APlayerSprite::~APlayerSprite ()
{
} // Endproc.


FolioStatus APlayerSprite::UpdateDirection (Direction   direction, 
                                            bool        keyDown)
{
    FolioStatus status = ERR_SUCCESS;

    // Is a key down?

    if (keyDown)
    {
        // Yes. Is the player sprite currently static?

        if (m_state == STATE_STATIC)
        {
            // Yes. Reset the remaining number of auto-moves.

            m_remainingNumAutoMoves = 0;
        } // Endif.
        
        // Has the player sprite's direction changed?

        if (direction != m_direction)
        {                    
            // Yes. Reset the remaining number of auto-moves.

            m_remainingNumAutoMoves = 0;

            // Set the player sprite's direction.
    
            status = SetDirection (direction);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // The player sprite is not in auto-move mode.

            m_inAutoMoveMode = false;

            // Increment the number of remaining of auto-moves.

            IncNumRemainingAutoModeMoves ();

            // The player sprite is moving in the direction.
        
            m_state = STATE_MOVING; 
        } // Endif.

    } // Endif.

    // All keys are up.

    else
    {
        // Get the auto-move state.
        
        m_state = GetAutoMoveState ();
    } // Endelse.

    return (status);
} // Endproc.


void    APlayerSprite::SetGameOver ()
{
    m_isGameOver = true;
} // Endproc.


bool    APlayerSprite::IsGameOver () const
{
    return (m_isGameOver);
} // Endproc.


void    APlayerSprite::SetGameCompleted ()
{
    m_isGameCompleted = true;
} // Endproc.


bool    APlayerSprite::IsGameCompleted () const
{
    return (m_isGameCompleted);
} // Endproc.


FolioStatus APlayerSprite::Restart (Int32       screenXLeft,
                                    Int32       screenYTop,
                                    Direction   direction)
{
    // Restart the player sprite.

    m_inAutoMoveMode    = false;    // Initialise!
    m_isGameOver        = false;
    m_isGameCompleted   = false;

    // Recreate the player sprite.

    return (Recreate (screenXLeft, screenYTop, direction));
} // Endproc.


APlayerSprite::STATE    APlayerSprite::GetAutoMoveState ()
{
    STATE   state = STATE_STATIC;   // Initialise!

    // Does the player sprite support auto-move mode?

    if (IsAutoMoveModeSupported ())
    {
        // Yes. The player sprite is in auto-move mode if there is a remaining 
        // number of auto-moves.

        if (m_remainingNumAutoMoves)
        {
            // The player sprite is moving in auto-move mode.

            m_inAutoMoveMode = true;

            state = STATE_MOVING; 
        } // Endif.

        else
        {
            // The player sprite is not in auto-move mode.

            m_inAutoMoveMode = false;
        } // Endelse.

    } // Endif.

    return (state);
} // Endproc.


void    APlayerSprite::CheckAutoMoveState ()
{
    // Is the player sprite moving in auto-move mode?

    if (m_inAutoMoveMode && m_remainingNumAutoMoves)
    {
        // Yes. Still in auto-move mode?

        if (--m_remainingNumAutoMoves == 0)
        {
            // No. No longer entering the screen.

            m_isEnteringScreen = false;

            // The player sprite is static.

            m_state = STATE_STATIC;
            m_speed = STATIC_SPEED;
        } // Endif.

        else
        {
            // Yes. The player sprite is moving.

            m_state = STATE_MOVING;
        } // Endelse.
    
    } // Endif.

} // Endproc.


FolioStatus APlayerSprite::SetBottomUpInitialisingMode (const ColourList&                       initialisingColourList,
                                                        const SpriteStationarySoundSamplesList& initialisingSpriteSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Note the player sprite's initialising attributes.

        m_initialisingDrawingMode                           = DM_BOTTOM_UP;
        m_initialisingMaxSequenceCount                      = 1;
        m_currentInitialisingSequenceCount                  = 0;
        m_initialisingColourList                            = initialisingColourList;
        m_initialisingSpriteSoundSamplesList                = initialisingSpriteSoundSamplesList;
        m_currentInitialisingSpriteSoundSamplesListIndex    = 0;
        m_playSpriteInitialisingSound                       = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::SetTopDownInitialisingMode (const ColourList&                        initialisingColourList,
                                                       const SpriteStationarySoundSamplesList&  initialisingSpriteSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Note the player sprite's initialising attributes.
        
        m_initialisingDrawingMode                           = DM_TOP_DOWN;
        m_initialisingMaxSequenceCount                      = 1;
        m_currentInitialisingSequenceCount                  = 0;
        m_initialisingColourList                            = initialisingColourList;
        m_initialisingSpriteSoundSamplesList                = initialisingSpriteSoundSamplesList;
        m_currentInitialisingSpriteSoundSamplesListIndex    = 0;
        m_playSpriteInitialisingSound                       = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::SetBottomUpTerminatingMode (const ColourList&                        terminatingColourList,
                                                       const SpriteStationarySoundSamplesList&  terminatingSpriteSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
    case STATE_TERMINATE_RQD:
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        // Note the player sprite's terminating attributes.
        
        m_terminatingDrawingMode                        = DM_BOTTOM_UP;
        m_terminatingMaxSequenceCount                   = 1;
        m_currentTerminatingSequenceCount               = 0;
        m_terminatingColourList                         = terminatingColourList;
        m_terminatingSpriteSoundSamplesList             = terminatingSpriteSoundSamplesList;
        m_currentTerminatingSpriteSoundSamplesListIndex = 0;
        m_playSpriteTerminatingSound                    = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::SetTopDownTerminatingMode (const ColourList&                         terminatingColourList,
                                                      const SpriteStationarySoundSamplesList&   terminatingSpriteSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
    case STATE_TERMINATE_RQD:
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        // Note the player sprite's terminating attributes.

        m_terminatingDrawingMode                        = DM_TOP_DOWN;
        m_terminatingMaxSequenceCount                   = 1;
        m_currentTerminatingSequenceCount               = 0;
        m_terminatingColourList                         = terminatingColourList;
        m_terminatingSpriteSoundSamplesList             = terminatingSpriteSoundSamplesList;
        m_currentTerminatingSpriteSoundSamplesListIndex = 0;
        m_playSpriteTerminatingSound                    = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::HandleInitialiseSprite (Gdiplus::Graphics&   graphics,
                                                   RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Initialisation is dependent on the drawing mode.
        
    switch (m_initialisingDrawingMode)
    {
    case DM_BOTTOM_UP:
    case DM_TOP_DOWN:
        status = PerformBottomUpOrTopDownInitialising (graphics, rects);
        break;

    default:
        status = ASprite::HandleInitialiseSprite (graphics, rects);
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::HandleTerminateSprite (Gdiplus::Graphics&    graphics,
                                                  RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Termination is dependent on the drawing mode.
        
    switch (m_terminatingDrawingMode)
    {
    case DM_BOTTOM_UP:
    case DM_TOP_DOWN:
        status = PerformBottomUpOrTopDownTerminating (graphics, rects);
        break;

    default:
        status = ASprite::HandleTerminateSprite (graphics, rects);
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::HandleMoveSprite (Gdiplus::Graphics&     graphics,
                                             UInt32                 speed, 
                                             const ACollisionGrid&  collisionGrid)
{
    // Calculate the player sprite's screen rect.

    m_isExitedScreen = CalculateScreenRect (speed, collisionGrid);

    // Has the player sprite exited the screen?

    if (m_isExitedScreen)
    {
        // Yes.

        m_isEnteringScreen = true;  // We're entering the next screen.
    } // Endif.

    // Is the player sprite at a wall?

    else
    if (m_isAtWall)
    {
        // Yes. Is this the same wall the player sprite was at previously?

        if ((m_action == NO_ACTION)                     &&
            (m_wallBound.m_direction == m_direction)    &&
             m_wallBound.m_screenRect.Equals (m_collisionRect))
        {
            // Yes. The player sprite is static.

            m_state = STATE_STATIC;
            m_speed = STATIC_SPEED;
        } // Endif.

        else
        {
            // No. Note the player sprite's wall bound.

            m_wallBound.m_direction     = m_direction;
            m_wallBound.m_screenRect    = m_collisionRect;

            // Check auto-move mode. 

            CheckAutoMoveState ();
        } // Endelse.

    } // Endelseif.

    else
    {
        // Yes. Check auto-move mode. 

        CheckAutoMoveState ();
    } // Endelseif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus APlayerSprite::HandleStaticSprite (Gdiplus::Graphics&       graphics,
                                               const ACollisionGrid&    collisionGrid)
{
    // Check if the player sprite has exited the screen.

    m_isExitedScreen = collisionGrid.IsExitedScreen (m_collisionRect, 
                                                     m_isInScreenExit, 
                                                     m_screenExit);

    // Has the player sprite exited the screen?

    if (m_isExitedScreen)
    {
        // Yes.

        m_isEnteringScreen = true;  // We're entering the next screen.
    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus APlayerSprite::PerformBottomUpOrTopDownInitialising (Gdiplus::Graphics& graphics,
                                                                 RectList*          rects)
{
    // Obtain the player sprite's current bitmaps.

    SpriteDrawing::SpriteBitmap spriteBitmap;
    SpriteDrawing::SpriteBitmap spriteMaskedBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteBitmap,
                                                    spriteMaskedBitmap, 
                                                    false);

    if (status == ERR_SUCCESS)
    {
        // Increment the player sprite's masked bitmap height.

        status = spriteMaskedBitmap->IncrementDrawingHeight (m_initialisingDrawingMode);

        if (status == ERR_SUCCESS)
        {
            // Draw the player sprite's masked bitmap.

            status = spriteMaskedBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

            if (status == ERR_SUCCESS)
            {
                // Get the player sprite's bitmap height adjustment.

                Int32   drawingHeightAdjustment = spriteBitmap->GetDrawingHeightAdjustment ();

                // Increment the player sprite's bitmap height.

                status = spriteBitmap->IncrementDrawingHeight (m_initialisingDrawingMode);

                if (status == ERR_SUCCESS)
                {
                    // We are initialising until the player sprite is fully drawn.

                    m_state = spriteBitmap->IsBitmapFullyDrawn () ? STATE_INITIALISED : STATE_INITIALISING;
                            
                    // Change the player sprite's bitmap colour.

                    Gdiplus::ARGB   currentColour   = m_spriteInkColour;   // Initialise!
                    Gdiplus::ARGB   newColour       = GetNewInitialisingColour (currentColour);

                    status = spriteBitmap->ChangeColour (currentColour, 
                                                         (m_state == STATE_INITIALISING) ? newColour : m_spriteInkColour);

                    if (status == ERR_SUCCESS)
                    {
                        // Draw the player sprite's bitmap.

                        status = spriteBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);

                        if (status == ERR_SUCCESS) 
                        {
                            // Play the player sprite's initialising sound synchronously.

                            status = PlaySpriteInitialisingSound (std::abs (drawingHeightAdjustment), false);

                            if ((status == ERR_SUCCESS) && 
                                (m_state == STATE_INITIALISED))
                            {
                                // Important to reset the drawing adjustment mode of the 
                                // player sprite's masked bitmap.
                                    
                                spriteMaskedBitmap->ResetDrawingAdjustmentMode ();
                            } // Endif.

                        } // Endif.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


Gdiplus::ARGB   APlayerSprite::GetNewInitialisingColour (Gdiplus::ARGB& currentColour) const
{
    static  UInt32  s_initialisingColourIndex = FOLIO_INVALID_INDEX;

    if (s_initialisingColourIndex == FOLIO_INVALID_INDEX)
    {
        currentColour = m_spriteInkColour;   // Initial colour.

        s_initialisingColourIndex = 0;
    } // Endif.

    else
    {
        currentColour = m_initialisingColourList [s_initialisingColourIndex++];

        if (s_initialisingColourIndex >= m_initialisingColourList.size ()) 
        {
            s_initialisingColourIndex = 0;
        } // Endif.

    } // Endelse.

    return (m_initialisingColourList [s_initialisingColourIndex]);
} // Endproc.


FolioStatus APlayerSprite::PerformBottomUpOrTopDownTerminating (Gdiplus::Graphics&  graphics,
                                                                RectList*           rects)
{
    // Obtain the player sprite's current bitmaps.

    SpriteDrawing::SpriteBitmap spriteBitmap;
    SpriteDrawing::SpriteBitmap spriteMaskedBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteBitmap,
                                                    spriteMaskedBitmap,
                                                    false);

    if (status == ERR_SUCCESS)
    {
        // Decrement the player sprite's masked bitmap height.

        status = spriteMaskedBitmap->DecrementDrawingHeight (-m_terminatingDrawingMode);

        if (status == ERR_SUCCESS)
        {
            // Draw the player sprite's masked bitmap.

            status = spriteMaskedBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

            if (status == ERR_SUCCESS)
            {
                // Get the player sprite's bitmap height adjustment.

                Int32   drawingHeightAdjustment = spriteBitmap->GetDrawingHeightAdjustment ();

                // Decrement the player sprite's bitmap height.

                status = spriteBitmap->DecrementDrawingHeight (-m_terminatingDrawingMode);

                if (status == ERR_SUCCESS)
                {
                    // Change the player sprite's bitmap colour.

                    Gdiplus::ARGB   currentColour   = m_spriteInkColour;   // Initialise!
                    Gdiplus::ARGB   newColour       = GetNewTerminatingColour (currentColour);

                    status = spriteBitmap->ChangeColour (currentColour, newColour);

                    if (status == ERR_SUCCESS)
                    {
                        // Draw the player sprite's bitmap.

                        status = spriteBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
                            
                        if (status == ERR_SUCCESS)
                        {
                            // We are terminating until the player sprite is no longer drawn.

                            m_state = spriteBitmap->IsBitmapNoLongerDrawn () ? STATE_TERMINATED : STATE_TERMINATING;
                            
                            if (status == ERR_SUCCESS)
                            {
                                // Play the player sprite's terminating sound synchronously.

                                status = PlaySpriteTerminatingSound (std::abs (drawingHeightAdjustment), false);

                                if  ((status == ERR_SUCCESS) &&
                                     (m_state == STATE_TERMINATED))
                                {
                                    // Important to reset the drawing adjustment mode of the 
                                    // player sprite's masked bitmap.
                                    
                                    spriteMaskedBitmap->ResetDrawingAdjustmentMode ();

                                    // Set back the default player colour.

                                    status = spriteBitmap->ChangeColour (newColour, m_spriteInkColour);
                                } // Endif.

                            } // Endif.
                            
                        } // Endif.

                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


Gdiplus::ARGB   APlayerSprite::GetNewTerminatingColour (Gdiplus::ARGB& currentColour) const
{
    static  UInt32  s_terminatingColourIndex = FOLIO_INVALID_INDEX;

    if (s_terminatingColourIndex == FOLIO_INVALID_INDEX)
    {
        currentColour = m_spriteInkColour;   // Initial colour.

        s_terminatingColourIndex = 0;
    } // Endif.

    else
    {
        currentColour = m_terminatingColourList [s_terminatingColourIndex++];

        if (s_terminatingColourIndex >= m_terminatingColourList.size ()) 
        {
            s_terminatingColourIndex = 0;
        } // Endif.

    } // Endelse.

    return (m_terminatingColourList [s_terminatingColourIndex]);
} // Endproc.


bool    APlayerSprite::CalculateScreenRect (UInt32                  speed,
                                            const ACollisionGrid&   collisionGrid)
{
    bool    isExitedScreen = false; // Initialise!

    // Is the player sprite entering a screen?

    if (m_isEnteringScreen)
    {
        // Yes. Move the player sprite based on how it is entering the screen.

        switch (m_screenExit.m_orientation)
        {
        case ACollisionGrid::ScreenExit::TOP:
            // Entered the screen from the top, move up.

            MoveUp (speed, collisionGrid); 
            break;
            
        case ACollisionGrid::ScreenExit::BOTTOM:
        case ACollisionGrid::ScreenExit::FLOOR:
            // Entered the screen from the bottom, move down.
            
            MoveDown (speed, collisionGrid); 
            break;
            
        case ACollisionGrid::ScreenExit::LEFT:
            // Entered the screen from the left, move right.

            MoveRight (speed, collisionGrid); 
            break;

        case ACollisionGrid::ScreenExit::RIGHT:
            // Entered the screen from the right, move left.

            MoveLeft (speed, collisionGrid); 
            break;

        case ACollisionGrid::ScreenExit::NONE:
        default:
            // No longer entering the screen.

            m_isEnteringScreen      = false;
            m_isAtLockedScreenExit  = false;
            m_isInScreenExit        = false;
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. Calculate the player sprite's screen rect based on its direction.

        switch (m_direction)
        {
        case N:
            isExitedScreen = MoveUp (speed, collisionGrid); 
            break;

        case S:
            isExitedScreen = MoveDown (speed, collisionGrid); 
            break;

        case E:
            isExitedScreen = MoveRight (speed, collisionGrid); 
            break;

        case W:
            isExitedScreen = MoveLeft (speed, collisionGrid); 
            break;

        case NE:
            isExitedScreen = MoveUp (speed, collisionGrid); 

            if (!isExitedScreen)
            {
                isExitedScreen = MoveRight (speed, collisionGrid); 
            } // Endif.
            break;

        case NW:
            isExitedScreen = MoveUp (speed, collisionGrid); 

            if (!isExitedScreen)
            {
                isExitedScreen = MoveLeft (speed, collisionGrid); 
            } // Endif.
            break;

        case SE:
            isExitedScreen = MoveDown (speed, collisionGrid); 

            if (!isExitedScreen)
            {
                isExitedScreen = MoveRight (speed, collisionGrid); 
            } // Endif.
            break;

        case SW:
            isExitedScreen = MoveDown (speed, collisionGrid); 

            if (!isExitedScreen)
            {
                isExitedScreen = MoveLeft (speed, collisionGrid); 
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endelse.

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveUp (UInt32                   speed,
                               const ACollisionGrid&    collisionGrid)
{
    bool    isExitedScreen = false; // Initialise!

    m_collisionRect.Y -= speed; // Move up.

    // In a screen exit?

    if (m_isInScreenExit)
    {
        // Yes.

        switch (m_screenExit.m_orientation)
        {
        case ACollisionGrid::ScreenExit::BOTTOM:
        case ACollisionGrid::ScreenExit::LEFT:
        case ACollisionGrid::ScreenExit::RIGHT:
        case ACollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (ACollisionGrid::UP, 
                                                m_collisionRect,
                                                m_isEnteringScreen,
                                                m_isInScreenExit,
                                                m_screenExit);
            break;

        case ACollisionGrid::ScreenExit::NONE:
        case ACollisionGrid::ScreenExit::TOP:
        default:
            if (m_isEnteringScreen)
            {
                // Check for screen entry.

                m_isEnteringScreen = collisionGrid.IsEnteringScreen (ACollisionGrid::UP,
                                                                     m_collisionRect,
                                                                     m_isInScreenExit,
                                                                     m_screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::UP,
                                                               m_collisionRect,
                                                               m_isAtLockedScreenExit,
                                                               m_isInScreenExit,
                                                               m_screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. No longer entering the screen.
        
        m_isEnteringScreen = false;

        // Check for screen exit.

        isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::UP,
                                                       m_collisionRect,
                                                       m_isAtLockedScreenExit,
                                                       m_isInScreenExit,
                                                       m_screenExit);

        if (!isExitedScreen)
        {
            // Check for wall collision.

            m_isAtWall = collisionGrid.IsWallCollision (ACollisionGrid::UP, m_collisionRect);
        } // Endif.

    } // Endelse.

    m_screenRect.Y = CalculateScreenYTop (ACollisionGrid::UP);

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveDown (UInt32                 speed,
                                 const ACollisionGrid&  collisionGrid)
{
    bool    isExitedScreen = false; // Initialise!

    m_collisionRect.Y += speed; // Move down.

    // In a screen exit?

    if (m_isInScreenExit)
    {
        // Yes.

        switch (m_screenExit.m_orientation)
        {
        case ACollisionGrid::ScreenExit::TOP:
        case ACollisionGrid::ScreenExit::LEFT:
        case ACollisionGrid::ScreenExit::RIGHT:
        case ACollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (ACollisionGrid::DOWN, 
                                                m_collisionRect,
                                                m_isEnteringScreen,
                                                m_isInScreenExit,
                                                m_screenExit);
            break;

        case ACollisionGrid::ScreenExit::NONE:
        case ACollisionGrid::ScreenExit::BOTTOM:
        default:
            if (m_isEnteringScreen)
            {
                // Check for screen entry.

                m_isEnteringScreen = collisionGrid.IsEnteringScreen (ACollisionGrid::DOWN,
                                                                     m_collisionRect,
                                                                     m_isInScreenExit,
                                                                     m_screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::DOWN,
                                                               m_collisionRect,
                                                               m_isAtLockedScreenExit,
                                                               m_isInScreenExit,
                                                               m_screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. No longer entering the screen.
        
        m_isEnteringScreen = false;

        isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::DOWN,
                                                       m_collisionRect,
                                                       m_isAtLockedScreenExit,
                                                       m_isInScreenExit,
                                                       m_screenExit);

        if (!isExitedScreen)
        {
            // Check for wall collision.

            m_isAtWall = collisionGrid.IsWallCollision (ACollisionGrid::DOWN, m_collisionRect);
        } // Endif.

    } // Endelse.

    m_screenRect.Y = CalculateScreenYTop (ACollisionGrid::DOWN);

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveLeft (UInt32                 speed,
                                 const ACollisionGrid&  collisionGrid)
{
    bool    isExitedScreen = false; // Initialise!

    m_collisionRect.X -= speed; // Move left.

    // In a screen exit?

    if (m_isInScreenExit)
    {
        // Yes.

        switch (m_screenExit.m_orientation)
        {
        case ACollisionGrid::ScreenExit::TOP:
        case ACollisionGrid::ScreenExit::BOTTOM:
        case ACollisionGrid::ScreenExit::RIGHT:
        case ACollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (ACollisionGrid::LEFT, 
                                                m_collisionRect,
                                                m_isEnteringScreen,
                                                m_isInScreenExit,
                                                m_screenExit);
            break;

        case ACollisionGrid::ScreenExit::NONE:
        case ACollisionGrid::ScreenExit::LEFT:
        default:
            if (m_isEnteringScreen)
            {
                // Check for screen entry.

                m_isEnteringScreen = collisionGrid.IsEnteringScreen (ACollisionGrid::LEFT,
                                                                     m_collisionRect,
                                                                     m_isInScreenExit,
                                                                     m_screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::LEFT,
                                                               m_collisionRect,
                                                               m_isAtLockedScreenExit,
                                                               m_isInScreenExit,
                                                               m_screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. No longer entering the screen.
        
        m_isEnteringScreen = false;

        isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::LEFT,
                                                       m_collisionRect,
                                                       m_isAtLockedScreenExit,
                                                       m_isInScreenExit,
                                                       m_screenExit);

        if (!isExitedScreen)
        {
            // Check for wall collision.

            m_isAtWall = collisionGrid.IsWallCollision (ACollisionGrid::LEFT, m_collisionRect);
        } // Endif.

    } // Endelse.

    m_screenRect.X = CalculateScreenXLeft (ACollisionGrid::LEFT);

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveRight (UInt32                speed,
                                  const ACollisionGrid& collisionGrid)
{
    bool    isExitedScreen = false; // Initialise!

    m_collisionRect.X += speed; // Move right.

    // In a screen exit?

    if (m_isInScreenExit)
    {
        // Yes.

        switch (m_screenExit.m_orientation)
        {
        case ACollisionGrid::ScreenExit::TOP:
        case ACollisionGrid::ScreenExit::BOTTOM:
        case ACollisionGrid::ScreenExit::LEFT:
        case ACollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (ACollisionGrid::RIGHT, 
                                                m_collisionRect,
                                                m_isEnteringScreen,
                                                m_isInScreenExit,
                                                m_screenExit);
            break;

        case ACollisionGrid::ScreenExit::NONE:
        case ACollisionGrid::ScreenExit::RIGHT:
        default:
            if (m_isEnteringScreen)
            {
                // Check for screen entry.

                m_isEnteringScreen = collisionGrid.IsEnteringScreen (ACollisionGrid::RIGHT,
                                                                     m_collisionRect,
                                                                     m_isInScreenExit,
                                                                     m_screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::RIGHT,
                                                               m_collisionRect,
                                                               m_isAtLockedScreenExit,
                                                               m_isInScreenExit,
                                                               m_screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. No longer entering the screen.
        
        m_isEnteringScreen = false;

        isExitedScreen = collisionGrid.IsExitedScreen (ACollisionGrid::RIGHT,
                                                       m_collisionRect,
                                                       m_isAtLockedScreenExit,
                                                       m_isInScreenExit,
                                                       m_screenExit);

        if (!isExitedScreen)
        {
            // Check for wall collision.

            m_isAtWall = collisionGrid.IsWallCollision (ACollisionGrid::RIGHT, m_collisionRect);
        } // Endif.

    } // Endelse.

    m_screenRect.X = CalculateScreenXLeft (ACollisionGrid::RIGHT);

    return (isExitedScreen);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
