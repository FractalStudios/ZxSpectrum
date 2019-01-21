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
    m_canFireWeapon(false),
    m_canCollectItems(false),
    m_completedGame(false)
{
} // Endproc.


APlayerSprite::~APlayerSprite ()
{
} // Endproc.


FolioStatus APlayerSprite::SetBottomUpInitialisingMode (const ColourList&                           initialisingColourList,
                                                        const SpriteInitialisingSoundSamplesList&   initialisingSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the initialising mode if the current state is created or initialise required.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Note the sprite's initialising attributes.

        m_initialisingDrawingMode                   = DM_BOTTOM_UP;
        m_initialisingColourList                    = initialisingColourList;
        m_initialisingSoundSamplesList              = initialisingSoundSamplesList;
        m_initialisingCurrentSoundSamplesListIndex  = 0;
        m_playSpriteInitialisingSound               = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::SetTopDownInitialisingMode (const ColourList&                            initialisingColourList,
                                                       const SpriteInitialisingSoundSamplesList&    initialisingSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the initialising mode if the current state is created or initialise required.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Note the sprite's initialising attributes.
        
        m_initialisingDrawingMode                   = DM_TOP_DOWN;
        m_initialisingColourList                    = initialisingColourList;
        m_initialisingSoundSamplesList              = initialisingSoundSamplesList;
        m_initialisingCurrentSoundSamplesListIndex  = 0;
        m_playSpriteInitialisingSound               = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


UInt32  APlayerSprite::GetInitialisingPauseTime () const
{
    return (DEFAULT_INITIALISING_PAUSE_TIME);
} // Endproc.


FolioStatus APlayerSprite::SetBottomUpTerminatingMode (const ColourList&                        terminatingColourList,
                                                       const SpriteTerminatingSoundSamplesList& terminatingSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the terminating mode if the current state is created, initialise 
    // required, terminate required, static or moving.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
    case STATE_TERMINATE_RQD:
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        // Note the sprite's terminating attributes.
        
        m_terminatingDrawingMode                    = DM_BOTTOM_UP;
        m_terminatingColourList                     = terminatingColourList;
        m_terminatingSoundSamplesList               = terminatingSoundSamplesList;
        m_terminatingCurrentSoundSamplesListIndex   = 0;
        m_playSpriteTerminatingSound                = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus APlayerSprite::SetTopDownTerminatingMode (const ColourList&                         terminatingColourList,
                                                      const SpriteTerminatingSoundSamplesList&  terminatingSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the terminating mode if the current state is created, initialise 
    // required, terminate required, static or moving.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
    case STATE_TERMINATE_RQD:
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        // Note the sprite's terminating attributes.

        m_terminatingDrawingMode                    = DM_TOP_DOWN;
        m_terminatingColourList                     = terminatingColourList;
        m_terminatingSoundSamplesList               = terminatingSoundSamplesList;
        m_terminatingCurrentSoundSamplesListIndex   = 0;
        m_playSpriteTerminatingSound                = true;
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


UInt32  APlayerSprite::GetTerminatingPauseTime () const
{
    return (DEFAULT_TERMINATING_PAUSE_TIME);
} // Endproc.


APlayerSprite::Direction  APlayerSprite::UpdateDirection (Direction direction, 
                                                          bool      keyDown)
{
    // Is a key down?

    if (keyDown)
    {
        // Yes. Has the player sprite's direction changed?

        if (direction != m_direction)
        {
            // Yes. Update the current sprite drawing attributes.

            UpdateSpriteDrawingAttributes (direction);
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

    return (m_direction);
} // Endproc.


void    APlayerSprite::SetCanFireWeapon (bool canFireWeapon)
{
    m_canFireWeapon = canFireWeapon;
} // Endproc.


bool    APlayerSprite::CanFireWeapon () const
{
    // Cannot fire a weapon if in screen exit.

    return (m_canFireWeapon && !m_isInScreenExit);
} // Endproc.


void    APlayerSprite::SetCanCollectItems (bool canCollectItems)
{
    m_canCollectItems = canCollectItems;
} // Endproc.


bool    APlayerSprite::CanCollectItems () const
{
    return (m_canCollectItems);
} // Endproc.


void    APlayerSprite::SetCompletedGame ()
{
    m_completedGame = true;
} // Endproc.


bool    APlayerSprite::CompletedGame () const
{
    return (m_completedGame);
} // Endproc.


FolioStatus APlayerSprite::Recreate (Int32      initialScreenXLeft,
                                     Int32      initialScreenYTop,
                                     Direction  initialDirection,
                                     UInt32     initialSpriteBitmapIndex)
{
    m_state     = STATE_CREATED;
    m_direction = initialDirection;

    // Set the initial sprite bitmap.

    FolioStatus status = SetInitialSpriteBitmaps (initialDirection, initialSpriteBitmapIndex);

    if (status == ERR_SUCCESS)
    {
        // Set the player sprite's top-left screen position.

        SetScreenTopLeft (initialScreenXLeft, initialScreenYTop);

        m_isAtLockedScreenExit  = false;    // Initialise!
        m_isInScreenExit        = false;
        m_isExitedScreen        = false;
        m_isEnteringScreen      = false;

        m_inAutoMoveMode    = false;    // Initialise!
        m_canFireWeapon     = false;
        m_canCollectItems   = false;
        m_completedGame     = false;
    } // Endif.

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
                                             const CollisionGrid&   collisionGrid)
{
    // Calculate the player sprite's screen rect.

    m_isExitedScreen = CalculateScreenRect (speed, collisionGrid);

    // Has the player sprite exited the screen?

    if (m_isExitedScreen)
    {
        // Yes.

        m_isEnteringScreen = true;  // We're entering the next screen.

        // Set the auto-move mode.

        m_inAutoMoveMode        = (m_maxNumAutoMoves != 0);
        m_remainingNumAutoMoves = m_maxNumAutoMoves;
    } // Endif.

    // Is the player sprite not entering the screen and in auto-move mode?

    else
    if (!m_isEnteringScreen && m_inAutoMoveMode)
    {
        // Yes. Still moving? 

        if (--m_remainingNumAutoMoves == 0)
        {
            // No. No longer in auto-move mode.

            m_inAutoMoveMode = false;

            m_state = STATE_STATIC;
        } // Endif.

        else
        {
            // Yes.

            m_state = STATE_MOVING;
        } // Endelse.

    } // Endelseif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus APlayerSprite::HandleStaticSprite (Gdiplus::Graphics&   graphics,
                                               const CollisionGrid& collisionGrid)
{
    // Check if the player sprite has exited the screen.

    m_isExitedScreen = collisionGrid.IsExitedScreen (m_screenRect, 
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

    SpriteDrawingBitmap spriteDrawingBitmap;
    SpriteDrawingBitmap spriteMaskedDrawingBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteDrawingBitmap,
                                                    spriteMaskedDrawingBitmap);

    if (status == ERR_SUCCESS)
    {
        // Initialise required?

        if (IsInitialiseRqd ())
        {
            // Yes. Set the player sprite's masked drawing bitmap top-left screen position.

            status = spriteMaskedDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

            if (status == ERR_SUCCESS)
            {
                // Set the player sprite's drawing bitmap top-left screen position.

                status = spriteDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
            } // Endif.

        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Increment the player sprite's masked drawing bitmap height.

            status = spriteMaskedDrawingBitmap->IncrementDrawingHeight (m_initialisingDrawingMode);

            if (status == ERR_SUCCESS)
            {
                // Draw the player sprite's masked drawing bitmap.

                status = spriteMaskedDrawingBitmap->Draw (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Get the the player sprite's drawing bitmap height asjustment.

                    Int32   drawingHeightAsjustment = spriteDrawingBitmap->GetDrawingHeightAdjustment ();

                    // Increment the player sprite's drawing bitmap height.

                    status = spriteDrawingBitmap->IncrementDrawingHeight (m_initialisingDrawingMode);

                    if (status == ERR_SUCCESS)
                    {
                        // We are initialising until the player sprite is fully drawn.

                        m_state = spriteDrawingBitmap->IsBitmapFullyDrawn () ? STATE_INITIALISED : STATE_INITIALISING;
                            
                        // Change the player sprite's drawing bitmap colour.

                        Gdiplus::ARGB   currentColour   = m_spriteInkColour;   // Initialise!
                        Gdiplus::ARGB   newColour       = GetNewInitialisingColour (currentColour);

                        status = spriteDrawingBitmap->ChangeColour (currentColour, 
                                                                    (m_state == STATE_INITIALISING) ? newColour : m_spriteInkColour);

                        if (status == ERR_SUCCESS)
                        {
                            // Draw the player sprite's drawing bitmap.

                            status = spriteDrawingBitmap->Draw (graphics, rects);

                            if (status == ERR_SUCCESS) 
                            {
                                // Play the player sprite's initialising sound.

                                PlaySpriteInitialisingSound (std::abs (drawingHeightAsjustment));

                                if (m_state == STATE_INITIALISED)
                                {
                                    // Important to reset the drawing adjustment mode of the 
                                    // player sprite's masked drawing bitmap.
                                    
                                    spriteMaskedDrawingBitmap->ResetDrawingAdjustmentMode ();
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

    SpriteDrawingBitmap spriteDrawingBitmap;
    SpriteDrawingBitmap spriteMaskedDrawingBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteDrawingBitmap,
                                                    spriteMaskedDrawingBitmap);

    if (status == ERR_SUCCESS)
    {
        // Terminate required?

        if (IsTerminateRqd ())
        {
            // Yes. Set the player sprite's masked drawing bitmap top-left screen position.

            status = spriteMaskedDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

            if (status == ERR_SUCCESS)
            {
                // Set the player sprite's drawing bitmap top-left screen position.

                status = spriteDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
            } // Endif.

        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Decrement the player sprite's masked drawing bitmap height.

            status = spriteMaskedDrawingBitmap->DecrementDrawingHeight (-m_terminatingDrawingMode);

            if (status == ERR_SUCCESS)
            {
                // Draw the player sprite's masked drawing bitmap.

                status = spriteMaskedDrawingBitmap->Draw (graphics);

                if (status == ERR_SUCCESS)
                {
                    // Get the the player sprite's drawing bitmap height asjustment.

                    Int32   drawingHeightAsjustment = spriteDrawingBitmap->GetDrawingHeightAdjustment ();

                    // Decrement the player sprite's drawing bitmap height.

                    status = spriteDrawingBitmap->DecrementDrawingHeight (-m_terminatingDrawingMode);

                    if (status == ERR_SUCCESS)
                    {
                        // Change the player sprite's drawing bitmap colour.

                        Gdiplus::ARGB   currentColour   = m_spriteInkColour;   // Initialise!
                        Gdiplus::ARGB   newColour       = GetNewTerminatingColour (currentColour);

                        status = spriteDrawingBitmap->ChangeColour (currentColour, newColour);

                        if (status == ERR_SUCCESS)
                        {
                            // Draw the player sprite's drawing bitmap.

                            status = spriteDrawingBitmap->Draw (graphics, rects);
                            
                            if (status == ERR_SUCCESS)
                            {
                                // We are terminating until the player sprite is no longer drawn.

                                m_state = spriteDrawingBitmap->IsBitmapNoLongerDrawn () ? STATE_TERMINATED : STATE_TERMINATING;
                            
                                if (status == ERR_SUCCESS)
                                {
                                    // Play the player sprite's terminating sound.

                                    PlaySpriteTerminatingSound (std::abs (drawingHeightAsjustment));

                                    if (m_state == STATE_TERMINATED)
                                    {
                                        // Important to reset the drawing adjustment mode of the 
                                        // player sprite's masked drawing bitmap.
                                    
                                        spriteMaskedDrawingBitmap->ResetDrawingAdjustmentMode ();

                                        // Set back the default player colour.

                                        status = spriteDrawingBitmap->ChangeColour (newColour, m_spriteInkColour);
                                    } // Endif.

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


APlayerSprite::STATE    APlayerSprite::GetAutoMoveState (bool keyUp)
{
    APlayerSprite::STATE    state = STATE_STATIC;   // Initialise!

    // The player sprite is moving if the player sprite is entering a screen.

    if (m_isEnteringScreen)
    {
        state = STATE_MOVING;
    } // Endif.

    // The player sprite is moving if a key is up and the player sprite supports 
    // auto-move mode. 

    else
    if (keyUp && m_maxNumAutoMoves)
    {
        m_inAutoMoveMode        = true;
        m_remainingNumAutoMoves = m_maxNumAutoMoves;

        state = STATE_MOVING; 
    } // Endelseif.

    return (state);
} // Endproc.


bool    APlayerSprite::CalculateScreenRect (UInt32                  speed,
                                            const CollisionGrid&    collisionGrid)
{
    bool    isExitedScreen = false; // Initialise!

    // Is the player sprite entering a screen?

    if (m_isEnteringScreen)
    {
        // Yes. Move the player sprite based on how it is entering the screen.

        switch (m_screenExit.m_orientation)
        {
        case CollisionGrid::ScreenExit::TOP:
        case CollisionGrid::ScreenExit::FLOOR:
            isExitedScreen = MoveDown (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;
            
        case CollisionGrid::ScreenExit::BOTTOM:
            isExitedScreen = MoveUp (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;
            
        case CollisionGrid::ScreenExit::LEFT:
            isExitedScreen = MoveRight (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;

        case CollisionGrid::ScreenExit::RIGHT:
            isExitedScreen = MoveLeft (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;

        case CollisionGrid::ScreenExit::NONE:
        default:
            // No longer entering the screen.

            m_isEnteringScreen      = false;
            m_isAtLockedScreenExit  = false;
            m_isInScreenExit        = false;
            break;
        } // Endswitch.

        // Get the auto-move state.

        m_state = GetAutoMoveState (false);
    } // Endif.

    else
    {
        // No. Calculate the player sprite's screen rect based on its direction.

        switch (m_direction)
        {
        case N:
            isExitedScreen = MoveUp (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;

        case S:
            isExitedScreen = MoveDown (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;

        case E:
            isExitedScreen = MoveRight (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;

        case W:
            isExitedScreen = MoveLeft (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            break;

        case NE:
            isExitedScreen = MoveUp (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);

            if (!isExitedScreen)
            {
                isExitedScreen = MoveRight (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            } // Endif.
            break;

        case NW:
            isExitedScreen = MoveUp (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);

            if (!isExitedScreen)
            {
                isExitedScreen = MoveLeft (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            } // Endif.
            break;

        case SE:
            isExitedScreen = MoveDown (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);

            if (!isExitedScreen)
            {
                isExitedScreen = MoveRight (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            } // Endif.
            break;

        case SW:
            isExitedScreen = MoveDown (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);

            if (!isExitedScreen)
            {
                isExitedScreen = MoveLeft (speed, collisionGrid, m_screenRect, m_isEnteringScreen, m_isAtLockedScreenExit, m_isInScreenExit, m_screenExit);
            } // Endif.
            break;

        default:
            break;
        } // Endswitch.

    } // Endelse.

    // Set the player sprite's top-left screen position.

    SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveUp (UInt32                       speed,
                               const CollisionGrid&         collisionGrid,
                               Gdiplus::Rect&               spriteScreenRect,
                               bool&                        isEnteringScreen,
                               bool&                        isAtLockedScreenExit,
                               bool&                        isInScreenExit,
                               CollisionGrid::ScreenExit&   screenExit)
{
    bool    isExitedScreen = false; // Initialise!

    spriteScreenRect.Y -= speed;    // Move up.

    // In a screen exit?

    if (isInScreenExit)
    {
        // Yes.

        switch (screenExit.m_orientation)
        {
        case CollisionGrid::ScreenExit::BOTTOM:
        case CollisionGrid::ScreenExit::LEFT:
        case CollisionGrid::ScreenExit::RIGHT:
        case CollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (CollisionGrid::UP, 
                                                spriteScreenRect,
                                                isEnteringScreen,
                                                isInScreenExit,
                                                screenExit);
            break;

        case CollisionGrid::ScreenExit::NONE:
        case CollisionGrid::ScreenExit::TOP:
        default:
            if (isEnteringScreen)
            {
                // Check for screen entry.

                isEnteringScreen = collisionGrid.IsEnteringScreen (CollisionGrid::UP,
                                                                   spriteScreenRect,
                                                                   isInScreenExit,
                                                                   screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::UP,
                                                               spriteScreenRect,
                                                               isAtLockedScreenExit,
                                                               isInScreenExit,
                                                               screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. Check for screen exit.

        isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::UP,
                                                       spriteScreenRect,
                                                       isAtLockedScreenExit,
                                                       isInScreenExit,
                                                       screenExit);
    } // Endelse.

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveDown (UInt32                     speed,
                                 const CollisionGrid&       collisionGrid,
                                 Gdiplus::Rect&             spriteScreenRect,
                                 bool&                      isEnteringScreen,
                                 bool&                      isAtLockedScreenExit,
                                 bool&                      isInScreenExit,
                                 CollisionGrid::ScreenExit& screenExit)
{
    bool    isExitedScreen = false; // Initialise!

    spriteScreenRect.Y += speed;    // Move down.

    // In a screen exit?

    if (isInScreenExit)
    {
        // Yes.

        switch (screenExit.m_orientation)
        {
        case CollisionGrid::ScreenExit::TOP:
        case CollisionGrid::ScreenExit::LEFT:
        case CollisionGrid::ScreenExit::RIGHT:
        case CollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (CollisionGrid::DOWN, 
                                                spriteScreenRect,
                                                isEnteringScreen,
                                                isInScreenExit,
                                                screenExit);
            break;

        case CollisionGrid::ScreenExit::NONE:
        case CollisionGrid::ScreenExit::BOTTOM:
        default:
            if (isEnteringScreen)
            {
                // Check for screen entry.

                isEnteringScreen = collisionGrid.IsEnteringScreen (CollisionGrid::DOWN,
                                                                   spriteScreenRect,
                                                                   isInScreenExit,
                                                                   screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::DOWN,
                                                               spriteScreenRect,
                                                               isAtLockedScreenExit,
                                                               isInScreenExit,
                                                               screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. Check for screen exit.

        isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::DOWN,
                                                       spriteScreenRect,
                                                       isAtLockedScreenExit,
                                                       isInScreenExit,
                                                       screenExit);
    } // Endelse.

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveLeft (UInt32                     speed,
                                 const CollisionGrid&       collisionGrid,
                                 Gdiplus::Rect&             spriteScreenRect,
                                 bool&                      isEnteringScreen,
                                 bool&                      isAtLockedScreenExit,
                                 bool&                      isInScreenExit,
                                 CollisionGrid::ScreenExit& screenExit)
{
    bool    isExitedScreen = false; // Initialise!

    spriteScreenRect.X -= speed;    // Move left.

    // In a screen exit?

    if (isInScreenExit)
    {
        // Yes.

        switch (screenExit.m_orientation)
        {
        case CollisionGrid::ScreenExit::TOP:
        case CollisionGrid::ScreenExit::BOTTOM:
        case CollisionGrid::ScreenExit::RIGHT:
        case CollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (CollisionGrid::LEFT, 
                                                spriteScreenRect,
                                                isEnteringScreen,
                                                isInScreenExit,
                                                screenExit);
            break;

        case CollisionGrid::ScreenExit::NONE:
        case CollisionGrid::ScreenExit::LEFT:
        default:
            if (isEnteringScreen)
            {
                // Check for screen entry.

                isEnteringScreen = collisionGrid.IsEnteringScreen (CollisionGrid::LEFT,
                                                                   spriteScreenRect,
                                                                   isInScreenExit,
                                                                   screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::LEFT,
                                                               spriteScreenRect,
                                                               isAtLockedScreenExit,
                                                               isInScreenExit,
                                                               screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. Check for screen exit.

        isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::LEFT,
                                                       spriteScreenRect,
                                                       isAtLockedScreenExit,
                                                       isInScreenExit,
                                                       screenExit);
    } // Endelse.

    return (isExitedScreen);
} // Endproc.


bool    APlayerSprite::MoveRight (UInt32                        speed,
                                  const CollisionGrid&          collisionGrid,
                                  Gdiplus::Rect&                spriteScreenRect,
                                  bool&                         isEnteringScreen,
                                  bool&                         isAtLockedScreenExit,
                                  bool&                         isInScreenExit,
                                  CollisionGrid::ScreenExit&    screenExit)
{
    bool    isExitedScreen = false; // Initialise!

    spriteScreenRect.X += speed;    // Move right.

    // In a screen exit?

    if (isInScreenExit)
    {
        // Yes.

        switch (screenExit.m_orientation)
        {
        case CollisionGrid::ScreenExit::TOP:
        case CollisionGrid::ScreenExit::BOTTOM:
        case CollisionGrid::ScreenExit::LEFT:
        case CollisionGrid::ScreenExit::FLOOR:
            // Check the screen exit's bound.

            collisionGrid.CheckScreenExitBound (CollisionGrid::RIGHT, 
                                                spriteScreenRect,
                                                isEnteringScreen,
                                                isInScreenExit,
                                                screenExit);
            break;

        case CollisionGrid::ScreenExit::NONE:
        case CollisionGrid::ScreenExit::RIGHT:
        default:
            if (isEnteringScreen)
            {
                // Check for screen entry.

                isEnteringScreen = collisionGrid.IsEnteringScreen (CollisionGrid::RIGHT,
                                                                   spriteScreenRect,
                                                                   isInScreenExit,
                                                                   screenExit);
            } // Endif.

            else
            {
                // Check for screen exit.

                isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::RIGHT,
                                                               spriteScreenRect,
                                                               isAtLockedScreenExit,
                                                               isInScreenExit,
                                                               screenExit);
            } // Endelse.
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No. Check for screen exit.

        isExitedScreen = collisionGrid.IsExitedScreen (CollisionGrid::RIGHT,
                                                       spriteScreenRect,
                                                       isAtLockedScreenExit,
                                                       isInScreenExit,
                                                       screenExit);
    } // Endelse.

    return (isExitedScreen);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
