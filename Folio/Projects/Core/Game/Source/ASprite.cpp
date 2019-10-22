// "Home-made" includes.
#include    "ASprite.h"

namespace Folio
{

namespace Core
{

namespace Game
{

ASprite::ASprite ()
:   m_state(STATE_UNKNOWN),
    m_spriteInkColour(Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR),
    m_direction(NO_DIRECTION),
    m_previousHorizontalDirection(DEFAULT_DIRECTION),
    m_previousVerticalDirection(NO_DIRECTION),
    m_action(DEFAULT_ACTION),
    m_speed(STATIC_SPEED),
    m_maxNumAutoMoves(0),
    m_remainingNumAutoMoves(0),
    m_initialisingDrawingMode(DM_NONE),
    m_terminatingDrawingMode(DM_NONE),
    m_isAtWall(false),
    m_drawingElementId(DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED),
    m_collisionGridCellValue(ACollisionGrid::CELL_VALUE_EMPTY),
    m_initialisingMaxSequenceCount(0),
    m_initialisingCurrentSequenceCount(0),
    m_terminatingMaxSequenceCount(0),
    m_terminatingCurrentSequenceCount(0),
    m_playSpriteInitialisingSound(false),
    m_initialisingCurrentSoundSamplesListIndex(0),
    m_playSpriteTerminatingSound(false),
    m_terminatingCurrentSoundSamplesListIndex(0),
    m_isAtLockedScreenExit(false),
    m_isInScreenExit(false),
    m_isExitedScreen(false),
    m_isEnteringScreen(false),
    m_currentSpriteDrawingAttributes(0),
    m_spriteMovementAudioCount(0),
    m_currentSpriteMovementAudioAttributes(0)
{
} // Endproc.


ASprite::~ASprite ()
{
} // Endproc.


FolioStatus ASprite::Create (FolioHandle                        dcHandle,
                             const SpriteGraphicAttributesList& spriteGraphicAttributesList,
                             Int32                              initialScreenXLeft,
                             Int32                              initialScreenYTop,
                             UInt32                             screenScale,
                             Gdiplus::ARGB                      spriteInkColour,
                             Direction                          initialDirection,
                             UInt32                             maxNumAutoMoves)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite already?

    if (IsCreated ())
    {
        // Yes.

        status = ERR_INVALID_SEQUENCE;
    } // Endif.

    else
    {
        // No. Create the sprite's drawing attributes list.

        status = CreateSpriteDrawingAttributesList (dcHandle, 
                                                    spriteGraphicAttributesList,
                                                    screenScale,
                                                    initialDirection,
                                                    m_spriteDrawingAttributesList);

        if (status == ERR_SUCCESS)
        {
            // Set the graphic element's width and height.

            Int32   screenWidth = m_currentSpriteDrawingAttributes->GetCurrentSpriteDrawingBitmap ()->GetScreenWidth ();
            SetScreenWidth (screenWidth);
            m_collisionRect.Width = screenWidth;

            Int32   screenHeight = m_currentSpriteDrawingAttributes->GetCurrentSpriteDrawingBitmap ()->GetScreenHeight ();
            SetScreenHeight (screenHeight);
            m_collisionRect.Height = screenHeight;

            // Set the sprite's top-left position.

            status = SetScreenTopLeft (initialScreenXLeft, initialScreenYTop);
            
            if (status == ERR_SUCCESS)
            {
                // Scale the sprite.

                SetScreenScale (screenScale);
            
                // Create the sprite's underlying background.

                status = m_underlyingBackground.Create (dcHandle, GetScaledRect (m_screenRect.X, m_screenRect.Y));

                if (status == ERR_SUCCESS)
                {
                    // Note the sprite attributes.

                    m_spriteInkColour       = spriteInkColour;
                    m_direction             = initialDirection;
                    m_maxNumAutoMoves       = maxNumAutoMoves;
                    m_remainingNumAutoMoves = maxNumAutoMoves;

                    // Set the sprite's previous direction.

                    SetPreviousSpriteDirection (m_direction);

                    // We're good to go.

                    m_state = STATE_CREATED;
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::SetScreenTopLeft (Int32    screenXLeft,
                                       Int32    screenYTop)
{
    m_screenRect = Gdiplus::Rect(screenXLeft, 
                                 screenYTop,
                                 m_screenWidth,
                                 m_screenHeight);

    m_collisionRect.X = CalculateCollisionXLeft ();
    m_collisionRect.Y = CalculateCollisionYTop ();

    return (ERR_SUCCESS);
} // Endproc.


Gdiplus::Rect   ASprite::GetScreenRect () const
{
    return (m_screenRect);
} // Endproc.


Int32   ASprite::GetScreenXLeft () const
{
    return (m_screenRect.X);
} // Endproc.


Int32   ASprite::GetScreenYTop () const
{
    return (m_screenRect.Y);
} // Endproc.


Int32   ASprite::GetScreenXRight () const
{
    return (m_screenRect.X + m_screenRect.Width - 1);
} // Endproc.


Int32   ASprite::GetScreenYBottom () const
{
    return (m_screenRect.Y + m_screenRect.Height - 1);
} // Endproc.


Int32   ASprite::GetScreenWidth () const
{
    return (m_screenRect.Width);
} // Endproc.


Int32   ASprite::GetScreenHeight () const
{
    return (m_screenRect.Height);
} // Endproc.


Gdiplus::Rect   ASprite::GetCollisionRect () const
{
    return (m_collisionRect);
} // Endproc.


Int32   ASprite::GetCollisionXLeft () const
{
    return (m_collisionRect.X);
} // Endproc.


Int32   ASprite::GetCollisionYTop () const
{
    return (m_collisionRect.Y);
} // Endproc.


Int32   ASprite::GetCollisionXRight () const
{
    return (m_collisionRect.X + m_collisionRect.Width - 1);
} // Endproc.


Int32   ASprite::GetCollisionYBottom () const
{
    return (m_collisionRect.Y + m_collisionRect.Height - 1);
} // Endproc.


Int32   ASprite::GetCollisionWidth () const
{
    return (m_collisionRect.Width);
} // Endproc.


Int32   ASprite::GetCollisionHeight () const
{
    return (m_collisionRect.Height);
} // Endproc.


FolioStatus ASprite::SetSpriteMovementSoundSamples (const SpriteMovementSoundAttributesList& spriteMovementSoundSamplesAttributesList)
{
    // Create the sprite's movement audio attributes.

    return (CreateSpriteMovementAudioAttributes (spriteMovementSoundSamplesAttributesList, m_direction));
} // Endproc.


FolioStatus ASprite::SetSpriteReboundSoundSamples (const SpriteReboundSoundAttributesList& spriteReboundSoundSamplesAttributesList)
{
    m_spriteReboundAudioAttributesList = spriteReboundSoundSamplesAttributesList;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::ChangeSpriteInkColour (Gdiplus::ARGB   spriteInkColour,
                                            bool            includeInitialisingGraphics,
                                            bool            includeTerminatingGraphics)

{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. Has the sprite's colour changed?

        if (spriteInkColour != m_spriteInkColour)
        {
            // Yes. Change the colour of the sprite's drawing bitmaps.

            for (SpriteDrawingAttributesList::iterator itr = m_spriteDrawingAttributesList.begin ();
                 (status == ERR_SUCCESS) && (itr != m_spriteDrawingAttributesList.end ());
                 ++itr)
            {
                if (itr->m_action == m_action)
                {
                    status = ChangeSpriteDrawingBitmapsColour (spriteInkColour, itr->m_spriteDrawingBitmaps);
                } // Endif.

            } // Endfor.

            if (includeInitialisingGraphics && (status == ERR_SUCCESS) && !m_initialisingSpriteDrawingAttributesList.empty ())
            {
                // Change the colour of the sprite's initialising bitmaps.

                for (SpriteDrawingAttributesList::iterator itr = m_initialisingSpriteDrawingAttributesList.begin ();
                    (status == ERR_SUCCESS) && (itr != m_initialisingSpriteDrawingAttributesList.end ());
                    ++itr)
                {
                    status = ChangeSpriteDrawingBitmapsColour (spriteInkColour, itr->m_spriteDrawingBitmaps);
                } // Endfor.

            } // Endif.

            if (includeTerminatingGraphics && (status == ERR_SUCCESS) && !m_terminatingSpriteDrawingAttributesList.empty ())
            {
                // Change the colour of the sprite's terminating bitmaps.

                for (SpriteDrawingAttributesList::iterator itr = m_terminatingSpriteDrawingAttributesList.begin ();
                    (status == ERR_SUCCESS) && (itr != m_terminatingSpriteDrawingAttributesList.end ());
                    ++itr)
                {
                    status = ChangeSpriteDrawingBitmapsColour (spriteInkColour, itr->m_spriteDrawingBitmaps);
                } // Endfor.

            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // Note the sprite's new colour. 
        
                m_spriteInkColour = spriteInkColour;
            } // Endif.

        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


void    ASprite::SetState (STATE state)
{ 
    m_state = state;
   
    switch (m_state)
    {
    case STATE_FALLING:
        // Always exit south.

        SetCurrentSpriteBitmaps (S, m_spriteDrawingAttributesList, true);
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


ACollisionGrid::CellValue   ASprite::GetCollisionGridCellValue () const
{
    return (m_collisionGridCellValue);
} // Endproc.


UInt32  ASprite::GetMaxNumAutoMoves () const
{
    return (m_maxNumAutoMoves);
} // Endproc.
    

UInt32  ASprite::GetRemainingNumAutoMoves () const
{
    return (m_remainingNumAutoMoves);
} // Endproc.


ASprite::STATE  ASprite::GetState () const
{
    return (m_state);
} // Endproc.


void    ASprite::SetAlive (bool playSpriteInitialisingSound)
{
    m_playSpriteInitialisingSound = playSpriteInitialisingSound;
   
    SetState (STATE_INITIALISE_RQD);
} // Endproc.


bool    ASprite::IsAlive () const
{
    switch (m_state)
    {
    case STATE_INITIALISE_RQD:
    case STATE_INITIALISING:
    case STATE_INITIALISED:
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        return (true);

    default:
        return (false);
    } // Endswitch.

} // Endproc.


void    ASprite::SetDead (bool playSpriteTerminatingSound)
{
    m_playSpriteTerminatingSound = playSpriteTerminatingSound;

    SetState (STATE_TERMINATE_RQD);
} // Endproc.


bool    ASprite::IsDying () const
{
    switch (m_state)
    {
    case STATE_TERMINATE_RQD:
    case STATE_TERMINATING:
        return (true);

    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    ASprite::IsDead () const
{
    return (m_state == STATE_TERMINATED);
} // Endproc.


bool    ASprite::IsReady () const
{
    switch (m_state)
    {
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        return (true);

    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    ASprite::IsInitialiseRqd () const
{
    return (m_state == STATE_INITIALISE_RQD);
} // Endproc.


bool    ASprite::IsInitialising () const
{
    switch (m_state)
    {
    case STATE_INITIALISE_RQD:
    case STATE_INITIALISING:
        return (true);

    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    ASprite::IsInitialised () const
{
    return (m_state == STATE_INITIALISED);
} // Endproc.


bool    ASprite::IsTerminateRqd () const
{
    return (m_state == STATE_TERMINATE_RQD);
} // Endproc.


bool    ASprite::IsTerminating () const
{
    switch (m_state)
    {
    case STATE_TERMINATE_RQD:
    case STATE_TERMINATING:
        return (true);

    default:
        return (false);
    } // Endswitch.

} // Endproc.


bool    ASprite::IsTerminated () const
{
    return (m_state == STATE_TERMINATED);
} // Endproc.


bool    ASprite::IsStatic () const
{
    return (m_state == STATE_STATIC);
} // Endproc.


bool    ASprite::IsMoving () const
{
    return (m_state == STATE_MOVING);
} // Endproc.


bool    ASprite::IsFalling () const
{
    return (m_state == STATE_FALLING);
} // Endproc.


FolioStatus ASprite::SetGraphicInitialisingMode (FolioHandle                                dcHandle,
                                                 const SpriteGraphicAttributesList&         initialisingSpriteGraphicAttributesList,
                                                 UInt32                                     initialisingMaxSequenceCount,
                                                 const SpriteInitialisingSoundSamplesList&  initialisingSoundSamplesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the initialising mode if the current state is created or initialise required.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Create the sprite's initialising drawing attributes list.

        status = CreateSpriteDrawingAttributesList (dcHandle, 
                                                    initialisingSpriteGraphicAttributesList,
                                                    m_screenScale,
                                                    m_initialisingSpriteDrawingAttributesList);

        if (status == ERR_SUCCESS)
        {
            // Note the sprite's initialising attributes.

            m_initialisingDrawingMode                   = DM_GRAPHIC;
            m_initialisingMaxSequenceCount              = initialisingMaxSequenceCount * m_initialisingSpriteDrawingAttributesList.front ().m_maxNumSpriteBitmaps;
            m_initialisingCurrentSequenceCount          = 0;
            m_initialisingSoundSamplesList              = initialisingSoundSamplesList;
            m_initialisingCurrentSoundSamplesListIndex  = 0;
            m_playSpriteInitialisingSound               = true;
        } // Endif.
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::SetGraphicTerminatingMode (FolioHandle                                 dcHandle,
                                                const SpriteGraphicAttributesList&          terminatingSpriteGraphicAttributesList,
                                                UInt32                                      terminatingMaxSequenceCount,
                                                const SpriteTerminatingSoundSamplesList&    terminatingSoundSamplesList)
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
        // Create the sprite's terminating drawing attributes list.

        status = CreateSpriteDrawingAttributesList (dcHandle, 
                                                    terminatingSpriteGraphicAttributesList, 
                                                    m_screenScale,
                                                    m_terminatingSpriteDrawingAttributesList);

        if (status == ERR_SUCCESS)
        {
            // Note the sprite's terminating attributes.

            m_terminatingDrawingMode                    = DM_GRAPHIC;
            m_terminatingMaxSequenceCount               = terminatingMaxSequenceCount * m_terminatingSpriteDrawingAttributesList.front ().m_maxNumSpriteBitmaps;
            m_terminatingCurrentSequenceCount           = 0;
            m_terminatingSoundSamplesList               = terminatingSoundSamplesList;
            m_terminatingCurrentSoundSamplesListIndex   = 0;
            m_playSpriteTerminatingSound                = true;
        } // Endif.
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


void    ASprite::SetPlaySpriteInitialisingSound (bool playSpriteInitialisingSound)
{
    m_playSpriteInitialisingSound = playSpriteInitialisingSound;
} // Endproc.


void    ASprite::SetPlaySpriteTerminatingSound (bool playSpriteTerminatingSound)
{
    m_playSpriteTerminatingSound = playSpriteTerminatingSound;
} // Endproc.


ASprite::Direction  ASprite::UpdateDirection (Direction direction)
{
    Direction   orgDirection = m_direction; // Note original direction.

    // New direction.

    m_direction = direction;

    // Has the character sprite's direction changed?

    if (orgDirection != m_direction)
    {
        // Yes. Set the sprite's previous direction.

        SetPreviousSpriteDirection (orgDirection);

        // Set the current sprite drawing bitmaps.

        SetCurrentSpriteBitmaps (m_direction, m_spriteDrawingAttributesList);
    } // Endif.

    return (m_direction);
} // Endproc.


void    ASprite::SetDirection (Direction direction)
{
    if (direction != m_direction)
    {
        // Set the sprite's previous direction.

        SetPreviousSpriteDirection (m_direction);

        m_direction = direction;
    } // Endif.

} // Endproc.


ASprite::Direction  ASprite::GetDirection () const
{
    return (m_direction);
} // Endproc.


bool    ASprite::IsDirection () const
{
    return (m_direction != NO_DIRECTION);
} // Endproc.


void    ASprite::SetAction (Action action)
{
    if (action != m_action)
    {
        m_action = action;
    
        // Set the current sprite bitmaps.

        SetCurrentSpriteBitmaps (m_direction, m_spriteDrawingAttributesList, true);
    } // Endif.

} // Endproc.


ASprite::Action  ASprite::GetAction () const
{
    return (m_action);
} // Endproc.


bool    ASprite::IsAction () const
{
    return (m_action != DEFAULT_ACTION);
} // Endproc.


bool    ASprite::IsAtLockedScreenExit () const
{
    return (m_isAtLockedScreenExit);
} // Endproc.


bool    ASprite::IsInScreenExit () const
{
    return (m_isInScreenExit);
} // Endproc.


bool    ASprite::IsInScreenExit (const Gdiplus::Rect& screenRect) const
{
    return (m_isInScreenExit && m_screenExit.m_screenRect.Contains (static_cast<Gdiplus::Rect> (screenRect)));
} // Endproc.


bool    ASprite::IsExitedScreen () const
{
    return (m_isExitedScreen);
} // Endproc.


void    ASprite::SetScreenEntrance (ACollisionGrid::ScreenEntrance& screenEntrance) 
{
    // Only set the screen entrance attributes if the sprite is entering the screen.

    if (m_isEnteringScreen)
    {
        m_screenExit = screenEntrance;

        switch (screenEntrance.m_orientation)
        {
        case ACollisionGrid::ScreenEntrance::TOP:
        case ACollisionGrid::ScreenEntrance::FLOOR:
            m_direction = UpdateDirection (S);
            break;

        case ACollisionGrid::ScreenEntrance::BOTTOM:
            m_direction = UpdateDirection (N);
            break;
        
        case ACollisionGrid::ScreenEntrance::LEFT:
            m_direction = UpdateDirection (E);
            break;
        
        case ACollisionGrid::ScreenEntrance::RIGHT:
            m_direction = UpdateDirection (W);
            break;
        
        default:
            break;
        } // Endswitch.

    } // Endif.

} // Endproc.


void    ASprite::ResetScreenEntrance () 
{
    m_isAtLockedScreenExit  = false;
    m_isInScreenExit        = false;
    m_isExitedScreen        = false;
    m_isEnteringScreen      = false;
} // Endproc.


bool    ASprite::IsEnteringScreen () const
{
    return (m_isEnteringScreen);
} // Endproc.


ACollisionGrid::ScreenExit  ASprite::GetScreenExit () const
{
    return (m_screenExit);
} // Endproc.


ACollisionGrid::ScreenEntrance  ASprite::GetScreenEntrance () const
{
    return (m_screenExit);
} // Endproc.


FolioStatus ASprite::SetScreenEntranceTopLeft (const Gdiplus::Rect&     screenScreenRect,
                                               const ACollisionGrid&    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_screenExit.m_orientation)
    {
    case ACollisionGrid::ScreenExit::TOP:
        {
            // Calculate the sprite's new collision rect.

            m_collisionRect.Y = screenScreenRect.Y + screenScreenRect.Height - m_collisionRect.Height; 

            // Check for a collision with a wall.

            collisionGrid.IsWallCollision (ACollisionGrid::UP, m_collisionRect, true);

            // Set the player sprite's position.

            status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::UP), 
                                       CalculateScreenYTop (ACollisionGrid::UP));
        } // Endscope.
        break;

    case ACollisionGrid::ScreenExit::BOTTOM:
        {
            // Calculate the player sprite's new collision rect.
 
            m_collisionRect.Y = screenScreenRect.Y;

            // Check for a collision with a wall.

            collisionGrid.IsWallCollision (ACollisionGrid::DOWN, m_collisionRect, true);

            // Set the player sprite's position.

            status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::DOWN), 
                                       CalculateScreenYTop (ACollisionGrid::DOWN));
        } // Endscope.
        break;

    case ACollisionGrid::ScreenExit::LEFT:
        {
            // Calculate the player sprite's new collision rect.

            m_collisionRect.X = screenScreenRect.X + screenScreenRect.Width - m_collisionRect.Width; 

            // Check for a collision with a wall.

            collisionGrid.IsWallCollision (ACollisionGrid::LEFT, m_collisionRect, true);

            // Set the player sprite's position.

            status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::LEFT), 
                                       CalculateScreenYTop (ACollisionGrid::LEFT));
        } // Endscope.
        break;                                                                                             

    case ACollisionGrid::ScreenExit::RIGHT:
        {
            // Calculate the player sprite's new collision rect.

            m_collisionRect.X = screenScreenRect.X;

            // Check for a collision with a wall.

            collisionGrid.IsWallCollision (ACollisionGrid::RIGHT, m_collisionRect, true);

            // Set the player sprite's position.

            status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::RIGHT), 
                                       CalculateScreenYTop (ACollisionGrid::RIGHT));
        } // Endscope.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


void    ASprite::SetPreviousSpriteDirection (Direction direction)
{
    switch (direction)
    {
    case N:
    case S:
        m_previousVerticalDirection = direction;
        break;

    case E:
    case W:
        m_previousHorizontalDirection = direction;
        break;

    case NE:
        m_previousVerticalDirection     = N;
        m_previousHorizontalDirection   = E;
        break;

    case NW:
        m_previousVerticalDirection     = N;
        m_previousHorizontalDirection   = W;
        break;

    case SE:
        m_previousVerticalDirection     = S;
        m_previousHorizontalDirection   = E;
        break;

    case SW:
        m_previousVerticalDirection     = S;
        m_previousHorizontalDirection   = W;
        break;

    default:
        m_previousVerticalDirection     = NO_DIRECTION;
        m_previousHorizontalDirection   = DEFAULT_DIRECTION;
        break;
    } // Endswitch.

} // Endproc.


ASprite::Direction   ASprite::GetPreviousSpriteDirection () const
{
    return (m_previousHorizontalDirection | m_previousVerticalDirection);
} // Endproc.


ASprite::Direction  ASprite::GetDirectionToScreenTopLeft (Int32                 initialScreenXLeft,
                                                          Int32                 initialScreenYTop,
                                                          const ACollisionGrid& collisionGrid,
                                                          bool                  toScreenTopLeft) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    if (toScreenTopLeft)
    {
        direction  = (m_collisionRect.X <= initialScreenXLeft) ? E : W;
        direction |= (m_collisionRect.Y <= initialScreenYTop) ? S : N;
    } // Endif.

    else
    {
        direction  = (initialScreenXLeft <= (collisionGrid.GetFloorLeftBound () + collisionGrid.GetFloorWidth () / 2)) ? E : W;
        direction |= (initialScreenYTop <= (collisionGrid.GetFloorTopBound () + collisionGrid.GetFloorHeight () / 2)) ? S : N;
    } // Endelse.

    return (direction);
} // Endproc.


bool    ASprite::IsAtScreenTopLeft (Int32   initialScreenXLeft,
                                    Int32   initialScreenYTop) const
{
    return ((m_collisionRect.X == initialScreenXLeft) &&
            (m_collisionRect.Y == initialScreenYTop));
} // Endproc.


ASprite::Direction  ASprite::GetDirectionToScreenRect (const Gdiplus::Rect&     screenRect,
                                                       const ACollisionGrid&    collisionGrid,
                                                       bool                     toScreenRect) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    if (toScreenRect)
    {
        direction  = (m_collisionRect.X <= screenRect.X) ? E : W;
        direction |= ((m_collisionRect.Y + m_collisionRect.Height - 1) <= (screenRect.Y + screenRect.Height - 1)) ? S : N;
    } // Endif.

    else
    {
        direction  = (screenRect.X <= (collisionGrid.GetFloorLeftBound () + collisionGrid.GetFloorWidth () / 2)) ? E : W;
        direction |= (screenRect.Y <= (collisionGrid.GetFloorTopBound () + collisionGrid.GetFloorHeight () / 2)) ? S : N;
    } // Endelse.

    return (direction);
} // Endproc.


bool    ASprite::IsAtScreenRect (const Gdiplus::Rect& screenRect) const
{
    return ((m_collisionRect.X == screenRect.X) &&
           ((m_collisionRect.Y + m_collisionRect.Height) == (screenRect.Y + screenRect.Height)));
} // Endproc.


ASprite::Direction  ASprite::GetDirectionToNearestCorner (const ACollisionGrid &collisionGrid) const
{
    Direction   direction = ((m_collisionRect.X + m_collisionRect.Width / 2) <= (collisionGrid.GetFloorLeftBound () + collisionGrid.GetFloorWidth () / 2)) ? W : E;
    direction |= ((m_collisionRect.Y + m_collisionRect.Height / 2) <= (collisionGrid.GetFloorTopBound () + collisionGrid.GetFloorHeight () / 2)) ? N : S;

    return (direction);
} // Endproc.


ASprite::Direction  ASprite::GetFloorBoundDirection (ACollisionGrid::DIRECTION collisionGridDirection) const
{
    Direction   direction = m_direction;    // Note the sprite's current direction.

    switch (collisionGridDirection)
    {
    case ACollisionGrid::UP:
        direction &= ~N;
        direction |= S;
        break;

    case ACollisionGrid::DOWN:
        direction &= ~S;
        direction |= N;
        break;

    case ACollisionGrid::LEFT:
        direction &= ~W;
        direction |= E;
        break;

    case ACollisionGrid::RIGHT:
        direction &= ~E;
        direction |= W;
        break;

    default:
        break;
    } // Endswitch.

    return (direction);
} // Endproc.


FolioStatus ASprite::StoreUnderlyingBackground (Gdiplus::Graphics&  graphics,
                                                Gdiplus::Rect*      rect)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_UNKNOWN:
        status = ERR_INVALID_SEQUENCE;
        break;
 
    case STATE_INITIALISE_RQD:
        if (m_initialisingDrawingMode == DM_GRAPHIC)
        {
            // Set the sprite's screen attributes.

            SetSpriteScreenAttributes (m_initialisingSpriteDrawingAttributesList.front ().GetCurrentSpriteDrawingBitmap ());
        } // Endif.

        // Buffer the underlying background.
    
        status = m_underlyingBackground.Buffer (graphics, GetScaledRect (m_screenRect.X, m_screenRect.Y));  
        break;

    case STATE_TERMINATE_RQD:
        if (m_terminatingDrawingMode == DM_GRAPHIC)
        {
            // Set the sprite's screen attributes.

            SetSpriteScreenAttributes (m_terminatingSpriteDrawingAttributesList.front ().GetCurrentSpriteDrawingBitmap ());
        } // Endif.

        // Buffer the underlying background.
    
        status = m_underlyingBackground.Buffer (graphics, GetScaledRect (m_screenRect.X, m_screenRect.Y));
        break;

    case STATE_INITIALISING:
    case STATE_INITIALISED:
    case STATE_TERMINATING:
    case STATE_TERMINATED:
    case STATE_STATIC:
    case STATE_MOVING:
        // Buffer the underlying background.
    
        status = m_underlyingBackground.Buffer (graphics, rect ? *rect : GetScaledRect (m_screenRect.X, m_screenRect.Y));
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::RestoreUnderlyingBackground (Gdiplus::Graphics&    graphics,
                                                  RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_UNKNOWN:
        status = ERR_INVALID_SEQUENCE;
        break;

    case STATE_INITIALISING:
    case STATE_INITIALISED:
    case STATE_TERMINATE_RQD:
    case STATE_TERMINATING:
    case STATE_TERMINATED:
    case STATE_STATIC:
    case STATE_MOVING:
        // Draw the underlying background.

        status = m_underlyingBackground.Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::Move (Gdiplus::Graphics&       graphics,
                           UInt32                   speed, 
                           const ACollisionGrid&    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. The sprite is moving.
        
        m_state = STATE_MOVING;
        m_speed = speed;
        
        // Let our sub-class handle it.

        status = HandleMoveSprite (graphics, speed, collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Play sprite movement sound.

            PlaySpriteMovementSound ();
        } // Endif.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::Static (Gdiplus::Graphics&     graphics,
                             const ACollisionGrid&  collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. The sprite is static.
        
        m_state = STATE_STATIC; 
        m_speed = STATIC_SPEED;
        
        // Let our sub-class handle it.

        status = HandleStaticSprite (graphics, collisionGrid);
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::Draw (Gdiplus::Graphics&   graphics,
                           RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_state)
    {
    case STATE_UNKNOWN:
        status = ERR_INVALID_SEQUENCE;
        break;

    case STATE_INITIALISE_RQD:
        if (m_initialisingDrawingMode == DM_GRAPHIC)
        {
            // Set the initialising sprite bitmaps.

            status = SetCurrentSpriteBitmaps (m_direction, m_initialisingSpriteDrawingAttributesList, false, true);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            status = InitialiseSprite (graphics, rects);
        } // Endif.
        break;

    case STATE_INITIALISING:
        status = InitialiseSprite (graphics, rects);
        break;

    case STATE_TERMINATE_RQD:
        if (m_terminatingDrawingMode == DM_GRAPHIC)
        {
            // Set the terminating sprite bitmaps.

            status = SetCurrentSpriteBitmaps (m_direction, m_terminatingSpriteDrawingAttributesList, false, true);
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            status = TerminateSprite (graphics, rects);
        } // Endif.
        break;

    case STATE_TERMINATING:
        status = TerminateSprite (graphics, rects);
        break;

    case STATE_INITIALISED:
    case STATE_TERMINATED:
    case STATE_STATIC:
    case STATE_MOVING:
    case STATE_FALLING:
        status = DrawSprite (graphics, rects);
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::Draw (Int32                                                screenXLeft, 
                           Int32                                                screenYTop,
                           Gdiplus::Graphics&                                   graphics,
                           Folio::Core::Graphic::AGdiGraphicElement::RectList*  rects)
{
    // Set the sprite's top-left position.

    FolioStatus status = SetScreenTopLeft (screenXLeft, screenYTop);

    if (status == ERR_SUCCESS)
    {
        // Draw it.

        status = Draw (graphics, rects);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingAttributes (FolioHandle                 dcHandle,
                                                    const SpriteGraphicsList&   spriteGraphics,
                                                    UInt32                      screenScale,
                                                    SpriteDrawingAttributes&    spriteDrawingAttributes)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the sprite's graphics.

    for (SpriteGraphicsList::const_iterator spriteGraphicsItr = spriteGraphics.begin ();
            (status == ERR_SUCCESS) && (spriteGraphicsItr != spriteGraphics.end ());
            ++spriteGraphicsItr)
    {
        // Get the sprite graphic.

        SpriteGraphic::element_type&    spriteGraphic(*spriteGraphicsItr->get ());

        // Create a sprite drawing bitmap from the sprite graphic GDI device-independent bitmap.

        SpriteDrawingBitmap spriteDrawingBitmap(new SpriteDrawingBitmap::element_type);

        status = spriteDrawingBitmap->Create (dcHandle, *(spriteGraphic.GetGdiDiBitmap ()));

        if (status == ERR_SUCCESS)
        {
            // Create a sprite masked drawing bitmap from the sprite drawing bitmap.

            SpriteDrawingBitmap spriteMaskedDrawingBitmap;

            status = ResourceGraphic::CreateMaskedGdiBitmap (dcHandle,
                                                                spriteGraphic.GetMaskColour (),
                                                                screenScale, 
                                                                ResourceGraphic::NO_DRAWING_FLAGS,
                                                                spriteDrawingBitmap,
                                                                spriteMaskedDrawingBitmap);

            if (status == ERR_SUCCESS)
            {
                // Scale the sprite's drawing bitmap.

                spriteDrawingBitmap->SetScreenScale (screenScale);

                // Add to the sprite's drawing attributes.

                spriteDrawingAttributes.AddSpriteDrawingBitmaps (spriteDrawingBitmap,
                                                                 spriteMaskedDrawingBitmap);
            } // Endif.

        } // Endif.

    } // Endfor.

    // Note the maximum number of sprite drawing bitmaps.

    spriteDrawingAttributes.m_maxNumSpriteBitmaps = spriteDrawingAttributes.m_spriteDrawingBitmaps.size ();

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingAttributesList (FolioHandle                         dcHandle,
                                                        const SpriteGraphicAttributesList&  spriteGraphicAttributesList,
                                                        UInt32                              screenScale,
                                                        SpriteDrawingAttributesList&        spriteDrawingAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the sprite's drawing attributes.

    for (SpriteGraphicAttributesList::const_iterator spriteGraphicAttributesItr = spriteGraphicAttributesList.begin ();
         (status == ERR_SUCCESS) && (spriteGraphicAttributesItr != spriteGraphicAttributesList.end ());
         ++spriteGraphicAttributesItr)
    {
        // Get the sprite's graphics.

        for (SpriteGraphicsList::const_iterator spriteGraphicsItr = spriteGraphicAttributesItr->m_spriteGraphics.begin ();
             (status == ERR_SUCCESS) && (spriteGraphicsItr != spriteGraphicAttributesItr->m_spriteGraphics.end ());
             ++spriteGraphicsItr)
        {
            // Get the sprite graphic.

            SpriteGraphic::element_type&    spriteGraphic(*spriteGraphicsItr->get ());

            // Create a sprite drawing bitmap from the sprite graphic GDI device-independent bitmap.

            SpriteDrawingBitmap spriteDrawingBitmap(new SpriteDrawingBitmap::element_type);

            status = spriteDrawingBitmap->Create (dcHandle, *(spriteGraphic.GetGdiDiBitmap ()));

            if (status == ERR_SUCCESS)
            {
                // Create a sprite masked drawing bitmap from the sprite drawing bitmap.

                SpriteDrawingBitmap spriteMaskedDrawingBitmap;

                status = ResourceGraphic::CreateMaskedGdiBitmap (dcHandle,
                                                                 spriteGraphic.GetMaskColour (),
                                                                 screenScale, 
                                                                 ResourceGraphic::NO_DRAWING_FLAGS,
                                                                 spriteDrawingBitmap,
                                                                 spriteMaskedDrawingBitmap);

                if (status == ERR_SUCCESS)
                {
                    // Scale the sprite's drawing bitmap.

                    spriteDrawingBitmap->SetScreenScale (screenScale);

                    // Add to the sprite's drawing attributes.

                    AddSpriteDrawingAttributes (spriteGraphicAttributesItr->m_direction, 
                                                spriteGraphicAttributesItr->m_action,
                                                spriteDrawingBitmap,
                                                spriteMaskedDrawingBitmap,
                                                spriteDrawingAttributesList);
                } // Endif.

            } // Endif.

        } // Endfor.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingAttributesList (FolioHandle                         dcHandle,
                                                        const SpriteGraphicAttributesList&  spriteGraphicAttributesList,
                                                        UInt32                              screenScale,
                                                        Direction                           direction,
                                                        SpriteDrawingAttributesList&        spriteDrawingAttributesList)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the sprite's drawing attributes.

    for (SpriteGraphicAttributesList::const_iterator spriteGraphicAttributesItr = spriteGraphicAttributesList.begin ();
         (status == ERR_SUCCESS) && (spriteGraphicAttributesItr != spriteGraphicAttributesList.end ());
         ++spriteGraphicAttributesItr)
    {
        // Get the sprite's graphics.

        for (SpriteGraphicsList::const_iterator spriteGraphicsItr = spriteGraphicAttributesItr->m_spriteGraphics.begin ();
             (status == ERR_SUCCESS) && (spriteGraphicsItr != spriteGraphicAttributesItr->m_spriteGraphics.end ());
             ++spriteGraphicsItr)
        {
            // Get the sprite graphic.

            SpriteGraphic::element_type&    spriteGraphic(*spriteGraphicsItr->get ());

            // Create a sprite drawing bitmap from the sprite graphic GDI device-independent bitmap.

            SpriteDrawingBitmap spriteDrawingBitmap(new SpriteDrawingBitmap::element_type);

            status = spriteDrawingBitmap->Create (dcHandle, *(spriteGraphic.GetGdiDiBitmap ()));

            if (status == ERR_SUCCESS)
            {
                // Create a sprite masked drawing bitmap from the sprite drawing bitmap.

                SpriteDrawingBitmap spriteMaskedDrawingBitmap;

                status = ResourceGraphic::CreateMaskedGdiBitmap (dcHandle,
                                                                 spriteGraphic.GetMaskColour (),
                                                                 screenScale, 
                                                                 ResourceGraphic::NO_DRAWING_FLAGS,
                                                                 spriteDrawingBitmap,
                                                                 spriteMaskedDrawingBitmap);

                if (status == ERR_SUCCESS)
                {
                    // Scale the sprite's drawing bitmap.

                    spriteDrawingBitmap->SetScreenScale (screenScale);

                    // Add to the sprite's drawing attributes.

                    AddSpriteDrawingAttributes (spriteGraphicAttributesItr->m_direction,
                                                spriteGraphicAttributesItr->m_action,
                                                spriteDrawingBitmap,
                                                spriteMaskedDrawingBitmap,
                                                spriteDrawingAttributesList);

                    if (m_drawingElementId == DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED)
                    {
                        m_drawingElementId          = spriteGraphic.GetDrawingElementId ();
                        m_collisionGridCellValue    = spriteGraphic.GetCollisionGridCellValue ();
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endfor.

    } // Endfor.

    if ((status == ERR_SUCCESS) && !spriteDrawingAttributesList.empty ())
    {
        // Set the initial sprite bitmaps.

        status = SetCurrentSpriteBitmaps (direction, spriteDrawingAttributesList);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::SetCurrentSpriteBitmaps (Direction                     direction,
                                              SpriteDrawingAttributesList&  spriteDrawingAttributesList,
                                              bool                          isSetSpriteScreenAttributes,
                                              bool                          ignoreAction)
{
    FolioStatus status = ERR_NOT_FOUND;

    if (spriteDrawingAttributesList.size () == 1)
    {
        m_currentSpriteDrawingAttributes = &(spriteDrawingAttributesList [0]);

        status = ERR_SUCCESS;
    } // Endif.

    else
    {
        // Find the sprite bitmaps that relate to the sprite bitmap index and direction.

        for (SpriteDrawingAttributesList::iterator itr = spriteDrawingAttributesList.begin ();
             itr != spriteDrawingAttributesList.end ();
             ++itr)
        {
            if (((itr->m_direction & direction) == itr->m_direction) &&
                 (ignoreAction || (itr->m_action == m_action)))
            {
                m_currentSpriteDrawingAttributes = &(*itr);

                status = ERR_SUCCESS;

                break;  // Get-outta-here!
            } // Endif.

        } // Endfor.

        if (status == ERR_NOT_FOUND)
        {
            Direction   previousDirection = GetPreviousSpriteDirection ();

            for (SpriteDrawingAttributesList::iterator itr = spriteDrawingAttributesList.begin ();
                 itr != spriteDrawingAttributesList.end ();
                 ++itr)
            {
                if (((itr->m_direction & previousDirection) == itr->m_direction) &&
                     (ignoreAction || (itr->m_action == m_action)))
                {
                    m_currentSpriteDrawingAttributes = &(*itr);

                    status = ERR_SUCCESS;

                    break;  // Get-outta-here!
                } // Endif.

            } // Endfor.

        } // Endfor.
    
    } // Endelse.

    if (isSetSpriteScreenAttributes && (status == ERR_SUCCESS))
    {
        // Set the sprite's screen attributes.

        SetSpriteScreenAttributes (m_currentSpriteDrawingAttributes->GetCurrentSpriteDrawingBitmap ());
    } // Endif.

    //iac
    if (status == ERR_NOT_FOUND)
        FOLIO_DEBUG_BREAK;

    return (status);
} // Endproc.


FolioStatus ASprite::QueryCurrentSpriteBitmaps (SpriteDrawingBitmap&    spriteDrawingBitmap,
                                                SpriteDrawingBitmap&    spriteMaskedDrawingBitmap,
                                                bool                    incrementSpriteBitmapIndex)
{
    FolioStatus status = ERR_NOT_FOUND;

    if (m_currentSpriteDrawingAttributes)
    {
        // Query the current sprite drawing attributes' current sprite drawing bitmaps.

        m_currentSpriteDrawingAttributes->QueryCurrentSpriteDrawingBitmaps (m_state,
                                                                            spriteDrawingBitmap,
                                                                            spriteMaskedDrawingBitmap,
                                                                            incrementSpriteBitmapIndex);

        status = ERR_SUCCESS;
    } // Endif.

    return (status);
} // Endproc.


void    ASprite::SetSpriteScreenAttributes (const SpriteDrawingBitmap& spriteDrawingBitmap)
{
    // Get the sprite drawing bitmap's width.

    Int32   bitmapScreenWidth = spriteDrawingBitmap->GetScreenWidth ();

    if (bitmapScreenWidth != m_screenWidth)
    {
        m_screenRect.X      = CalculateScreenXLeft (bitmapScreenWidth);
        m_screenRect.Width  = bitmapScreenWidth;

        SetScreenWidth (bitmapScreenWidth);

        m_collisionRect.X = CalculateCollisionXLeft ();
    } // Endif.

    // Get the sprite drawing bitmap's height.

    Int32   bitmapScreenHeight = spriteDrawingBitmap->GetScreenHeight ();
    
    if (bitmapScreenHeight != m_screenHeight)
    {
        m_screenRect.Y      = CalculateScreenYTop (bitmapScreenHeight);
        m_screenRect.Height = bitmapScreenHeight;

        SetScreenHeight (bitmapScreenHeight);
        
        m_collisionRect.Y = CalculateCollisionYTop ();
    } // Endif.

} // Endproc.


void    ASprite::PlaySpriteInitialisingSound (UInt32 initialisingSoundSamplesListIndex) const
{
    if (m_playSpriteInitialisingSound && 
        (initialisingSoundSamplesListIndex < m_initialisingSoundSamplesList.size ())) 
    {
        // Play the sound samples.

        for (UInt32 index = 0; 
             index < m_initialisingSoundSamplesList [initialisingSoundSamplesListIndex].m_numSoundSamplesPerFrame;
             ++index)
        {
            Folio::Core::Util::Sound::PlayAsyncSoundSample (m_initialisingSoundSamplesList [initialisingSoundSamplesListIndex].m_soundSample);
        } // Endfor.

    } // Endif.

} // Endproc.


void    ASprite::PlaySpriteTerminatingSound (UInt32 terminatingSoundSamplesListIndex) const
{
    if (m_playSpriteTerminatingSound && 
        (terminatingSoundSamplesListIndex < m_terminatingSoundSamplesList.size ()))
     {
        // Play the sound samples.
        
         for (UInt32 index = 0; 
             index < m_terminatingSoundSamplesList [terminatingSoundSamplesListIndex].m_numSoundSamplesPerFrame;
             ++index)
        {
            Folio::Core::Util::Sound::PlayAsyncSoundSample (m_terminatingSoundSamplesList [terminatingSoundSamplesListIndex].m_soundSample);
        } // Endfor.

    } // Endif.

} // Endproc.


FolioStatus ASprite::PlaySpriteMovementSound ()
{
    FolioStatus status = ERR_SUCCESS;
    
    switch (m_state)
    {
    case STATE_MOVING:
        // Does the sprite support sound when moving?

        if (IsSpriteMovementSoundSupported ())
        {
            // Yes.

            SpriteMovementSoundSample   spriteMovementSoundSample;
            
            if (QueryCurrentSpriteMovementSoundSample (spriteMovementSoundSample) == ERR_SUCCESS)
            {
                status = Folio::Core::Util::Sound::PlayAsyncSoundSample (*spriteMovementSoundSample);
            } // Endif.

        } // Endif.
        break;

    default:
        break;
    } // Endif.

    return (status);
} // Endproc.


bool    ASprite::IsSpriteMovementSoundSupported ()
{
    return (m_speed && ((++m_spriteMovementAudioCount % m_speed) == 0) && !m_spriteMovementAudioAttributesList.empty ());
} // Endproc.


FolioStatus ASprite::SetCurrentSpriteMovementSoundSample (Direction direction)
{
    FolioStatus status = ERR_NOT_FOUND;

    // Find the sprite movement audio samples that relate to the initial sprite sound sample index and direction.

    for (SpriteMovementAudioAttributesList::iterator itr = m_spriteMovementAudioAttributesList.begin ();
         itr != m_spriteMovementAudioAttributesList.end ();
         ++itr)
    {
        if ((itr->m_direction & direction) == direction)
        {
            itr->m_currentSpriteSoundSampleIndex = 0;

            m_currentSpriteMovementAudioAttributes = &(*itr);

            status = ERR_SUCCESS;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus ASprite::QueryCurrentSpriteMovementSoundSample (SpriteMovementSoundSample& spriteMovementSoundSample)
{

    FolioStatus status = ERR_NOT_FOUND;

    if (m_currentSpriteMovementAudioAttributes)
    {
        if (m_currentSpriteMovementAudioAttributes->m_currentSpriteSoundSampleIndex >= m_currentSpriteMovementAudioAttributes->m_maxNumSpriteSoundSamples)
        {
            m_currentSpriteMovementAudioAttributes->m_currentSpriteSoundSampleIndex = 0;
        } // Endif.

        spriteMovementSoundSample = m_currentSpriteMovementAudioAttributes->m_spriteMovementSoundSamples [m_currentSpriteMovementAudioAttributes->m_currentSpriteSoundSampleIndex];

        switch (m_state)
        {
        case STATE_MOVING:
            m_currentSpriteMovementAudioAttributes->m_currentSpriteSoundSampleIndex++; // Next.
            break;

        default:
            break;
        } // Endswitch.

        status = ERR_SUCCESS;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::UpdateSpriteMovementAudioAttributes (Direction direction)
{
    FolioStatus status = ERR_NOT_FOUND;

    // Find the sprite's movement audio attributes that relate to the direction.

    for (SpriteMovementAudioAttributesList::iterator itr = m_spriteMovementAudioAttributesList.begin ();
         itr != m_spriteMovementAudioAttributesList.end ();
         ++itr)
    {
        if ((itr->m_direction & direction) == direction)
        {
            m_currentSpriteMovementAudioAttributes = &(*itr);

            status = ERR_SUCCESS;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


Int32   ASprite::CalculateCollisionXLeft () const
{
    return (m_screenRect.X);
} // Endproc.


Int32   ASprite::CalculateCollisionYTop () const
{
    return (m_screenRect.Y);
} // Endproc.


Int32   ASprite::CalculateScreenXLeft (ACollisionGrid::DIRECTION collisionGridDirection) const
{
    return (m_collisionRect.X);
} // Endproc.


Int32   ASprite::CalculateScreenYTop (ACollisionGrid::DIRECTION collisionGridDirection) const
{
    return (m_collisionRect.Y);
} // Endproc.


Int32   ASprite::CalculateScreenXLeft (Int32 bitmapScreenWidth) const
{
    return (m_screenRect.X + (m_screenWidth - bitmapScreenWidth) / 2);
} // Endproc.


Int32   ASprite::CalculateScreenYTop (Int32 bitmapScreenHeight) const
{
    return (m_screenRect.Y + (m_screenHeight - bitmapScreenHeight) / 2);
} // Endproc.


FolioStatus ASprite::HandleInitialiseSprite (Gdiplus::Graphics& graphics,
                                             RectList*          rects)
{
    // Sprite is initialised.

    m_state = STATE_INITIALISED;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::HandleTerminateSprite (Gdiplus::Graphics&  graphics,
                                            RectList*           rects)
{
    // Sprite is terminated.

    m_state = STATE_TERMINATED;

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::HandleMoveSprite (Gdiplus::Graphics&       graphics,
                                       UInt32                   speed, 
                                       const ACollisionGrid&    collisionGrid)
{
    // Calculate the sprite's screen rect.

    CalculateScreenRect (speed, collisionGrid);

    // Is the sprite being auto-moved?

    if (m_remainingNumAutoMoves)
    {
        // Yes. Still moving? 

        if (--m_remainingNumAutoMoves == 0)
        {
            // No. Sprite is terminated.

            m_state = STATE_TERMINATED;
        } // Endif.

    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::HandleStaticSprite (Gdiplus::Graphics&     graphics,
                                         const ACollisionGrid&  collisionGrid)
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::InitialiseSprite (Gdiplus::Graphics&   graphics,
                                       RectList*            rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Initialisation is dependent on the drawing mode.
        
    switch (m_initialisingDrawingMode)
    {
    case DM_GRAPHIC:
        status = PerformGraphicInitialising (graphics, rects);
        break;

    default:
        // Let our sub-class handle initialise.

        status = HandleInitialiseSprite (graphics, rects);
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::TerminateSprite (Gdiplus::Graphics&    graphics,
                                      RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Termination is dependent on the drawing mode.
        
    switch (m_terminatingDrawingMode)
    {
    case DM_GRAPHIC:
        status = PerformGraphicTerminating (graphics, rects);
        break;

    default:
        // Let our sub-class handle terminate.

        status = HandleTerminateSprite (graphics, rects);
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::DrawSprite (Gdiplus::Graphics& graphics,
                                 RectList*          rects)
{
    // Obtain the sprite's current bitmaps.

    SpriteDrawingBitmap spriteDrawingBitmap;
    SpriteDrawingBitmap spriteMaskedDrawingBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteDrawingBitmap,
                                                    spriteMaskedDrawingBitmap);

    if (status == ERR_SUCCESS)
    {
        // Draw the sprite's masked drawing bitmap.

        status = spriteMaskedDrawingBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's drawing bitmap.

            status = spriteDrawingBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


void    ASprite::AddSpriteDrawingAttributes (Direction                      direction,
                                             Action                         action,
                                             const SpriteDrawingBitmap&     spriteDrawingBitmap,
                                             const SpriteDrawingBitmap&     spriteMaskedDrawingBitmap,
                                             SpriteDrawingAttributesList&   spriteDrawingAttributesList)
{
    bool    found = false;  // Initialise!

    // Find the sprite's drawing attributes for the specified direction.

    for (SpriteDrawingAttributesList::iterator itr = spriteDrawingAttributesList.begin ();
         itr != spriteDrawingAttributesList.end ();
         ++itr)
    {
        if (((itr->m_direction & direction) == itr->m_direction) &&
             (itr->m_action                 == action))
        {
            // Add to the sprite's drawing attributes.
            
            itr->AddSpriteDrawingBitmaps (spriteDrawingBitmap,
                                          spriteMaskedDrawingBitmap);

            found = true;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    // If we didn't find the sprite's drawing attributes for the specified 
    // direction, then add a new one.
 
    if (!found)
    {
        spriteDrawingAttributesList.push_back (SpriteDrawingAttributes(direction, 
                                                                       action,
                                                                       spriteDrawingBitmap, 
                                                                       spriteMaskedDrawingBitmap));
    } // Endif.

} // Endproc.


FolioStatus     ASprite::ChangeSpriteDrawingBitmapsColour (Gdiplus::ARGB                spriteInkColour,
                                                           SpriteDrawingBitmapsList&    spriteDrawingBitmaps)
{
    FolioStatus status = ERR_SUCCESS;
    
    // Change the colour of the sprite's drawing bitmaps.

    for (SpriteDrawingBitmapsList::iterator itr = spriteDrawingBitmaps.begin ();
         itr != spriteDrawingBitmaps.end ();
         ++itr)
    {
        status = itr->get ()->ChangeColour (m_spriteInkColour, spriteInkColour);
    } // Endfor.

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteMovementAudioAttributes (const SpriteMovementSoundSamplesList& spriteMovementSoundSamples,
                                                          SpriteMovementAudioAttributes&        spriteMovementAudioAttributes)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the sprite's movement sound sample.

    for (SpriteMovementSoundSamplesList::const_iterator spriteMovementSoundSamplesItr = spriteMovementSoundSamples.begin ();
        (status == ERR_SUCCESS) && (spriteMovementSoundSamplesItr != spriteMovementSoundSamples.end ());
        ++spriteMovementSoundSamplesItr)
    {
        // Add to the sprite's movement audio attributes.

        spriteMovementAudioAttributes.m_spriteMovementSoundSamples.push_back (*spriteMovementSoundSamplesItr);
    } // Endfor.

    // Note the maximum number of sprite movement audio samples.

    spriteMovementAudioAttributes.m_maxNumSpriteSoundSamples = spriteMovementAudioAttributes.m_spriteMovementSoundSamples.size ();

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteMovementAudioAttributes (const SpriteMovementSoundAttributesList&  spriteMovementSoundSamplesAttributesList,
                                                          Direction                                 direction)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the sprite's movement audio attributes.

    for (SpriteMovementSoundAttributesList::const_iterator spriteMovementSoundSamplesAttributesItr = spriteMovementSoundSamplesAttributesList.begin ();
         (status == ERR_SUCCESS) && (spriteMovementSoundSamplesAttributesItr != spriteMovementSoundSamplesAttributesList.end ());
         ++spriteMovementSoundSamplesAttributesItr)
    {
        // Get the sprite's movement sound samples.

        for (SpriteMovementSoundSamplesList::const_iterator spriteMovementSoundSamplesItr = spriteMovementSoundSamplesAttributesItr->m_spriteMovementSoundSamples.begin ();
             (status == ERR_SUCCESS) && (spriteMovementSoundSamplesItr != spriteMovementSoundSamplesAttributesItr->m_spriteMovementSoundSamples.end ());
             ++spriteMovementSoundSamplesItr)
        {
            // Add to the sprite's movement audio attributes.

            AddSpriteMovementAudioAttributes (spriteMovementSoundSamplesAttributesItr->m_direction, *spriteMovementSoundSamplesItr);
        } // Endfor.

    } // Endfor.

    if ((status == ERR_SUCCESS) && !m_spriteMovementAudioAttributesList.empty ())
    {
        // Set the initial sprite movement audio sound samples.

        status = SetCurrentSpriteMovementSoundSample (direction);
    } // Endif.

    return (status);
} // Endproc.


void    ASprite::AddSpriteMovementAudioAttributes (Direction                        direction,
                                                   const SpriteMovementSoundSample& spriteMovementSoundSample)
{
    bool    found = false;  // Initialise!

    // Find the sprite's movement audio attributes for the specified direction.

    for (SpriteMovementAudioAttributesList::iterator itr = m_spriteMovementAudioAttributesList.begin ();
         itr != m_spriteMovementAudioAttributesList.end ();
         ++itr)
    {
        if ((itr->m_direction & direction) == direction)
        {
            // Store the sprite movement audio sound samples.

            itr->m_spriteMovementSoundSamples.push_back (spriteMovementSoundSample);
            
            itr->m_maxNumSpriteSoundSamples++;

            found = true;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    // If we didn't find the sprite's movement audio attributes for the specified 
    // direction, then add a new one.
 
    if (!found)
    {
        m_spriteMovementAudioAttributesList.push_back (SpriteMovementAudioAttributes(direction, spriteMovementSoundSample));
    } // Endif.

} // Endproc.


FolioStatus ASprite::PerformGraphicInitialising (Gdiplus::Graphics& graphics,
                                                 RectList*          rects)
{
    // Get the sprite's initialising drawing bitmaps.

    SpriteDrawingBitmap spriteDrawingBitmap;
    SpriteDrawingBitmap spriteMaskedDrawingBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteDrawingBitmap,
                                                    spriteMaskedDrawingBitmap);

    if (status == ERR_SUCCESS)
    {
        // Draw the sprite's masked drawing bitmap.

        status = spriteMaskedDrawingBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's drawing bitmap.

            status = spriteDrawingBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
                            
            if (status == ERR_SUCCESS)
            {
                // Play the sprite's initialising sound.

                PlaySpriteInitialisingSound (m_initialisingCurrentSoundSamplesListIndex);

                if (++m_initialisingCurrentSoundSamplesListIndex >= m_initialisingSoundSamplesList.size ())
                {
                    m_initialisingCurrentSoundSamplesListIndex = 0;
                } // Endif.

                // We are initialising until the maximum sequence count is reached.

                m_state = (++m_initialisingCurrentSequenceCount < m_initialisingMaxSequenceCount)
                          ? STATE_INITIALISING 
                          : STATE_INITIALISED;

                if (m_state == STATE_INITIALISED)
                {
                    m_initialisingCurrentSequenceCount = 0; // Reset.

                    // Set the current sprite bitmaps.

                    SetCurrentSpriteBitmaps (m_direction, m_spriteDrawingAttributesList, true);
                } // Endif.

            } // Endif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::PerformGraphicTerminating (Gdiplus::Graphics&  graphics,
                                                RectList*           rects)
{
    // Get the sprite's terminating drawing bitmaps.

    SpriteDrawingBitmap spriteDrawingBitmap;
    SpriteDrawingBitmap spriteMaskedDrawingBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteDrawingBitmap,
                                                    spriteMaskedDrawingBitmap);

    if (status == ERR_SUCCESS)
    {
        // Draw the sprite's masked drawing bitmap.

        status = spriteMaskedDrawingBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's drawing bitmap.

            status = spriteDrawingBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
                            
            if (status == ERR_SUCCESS)
            {
                // Play the sprite's terminating sound.

                PlaySpriteTerminatingSound (m_terminatingCurrentSoundSamplesListIndex);

                if (++m_terminatingCurrentSoundSamplesListIndex >= m_terminatingSoundSamplesList.size ())
                {
                    m_terminatingCurrentSoundSamplesListIndex = 0;
                } // Endif.
                    
                // We are terminating until the maximum sequence count is reached.

                m_state = (++m_terminatingCurrentSequenceCount < m_terminatingMaxSequenceCount)
                          ? STATE_TERMINATING 
                          : STATE_TERMINATED;

                if (m_state == STATE_TERMINATED)
                {
                    m_terminatingCurrentSequenceCount = 0;  // Reset.

                    // Set the current sprite bitmaps.

                    SetCurrentSpriteBitmaps (m_direction, m_spriteDrawingAttributesList, true);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


void    ASprite::CalculateScreenRect (UInt32                speed,
                                      const ACollisionGrid& collisionGrid)
{
    // Calculate the sprite's screen rect based on its direction.

    switch (m_direction)
    {
    case N:
        MoveUp (speed, collisionGrid);
        break;

    case S:
        MoveDown (speed, collisionGrid);
        break;

    case E:
        MoveRight (speed, collisionGrid);
        break;

    case W:
        MoveLeft (speed, collisionGrid);
        break;

    case NE:
        MoveUp (speed, collisionGrid);
        MoveRight (speed, collisionGrid);
        break;

    case NW:
        MoveUp (speed, collisionGrid);
        MoveLeft (speed, collisionGrid);
        break;

    case SE:
        MoveDown (speed, collisionGrid);
        MoveRight (speed, collisionGrid);
        break;

    case SW:
        MoveDown (speed, collisionGrid);
        MoveLeft (speed, collisionGrid);
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


void    ASprite::MoveUp (UInt32                 speed,
                         const ACollisionGrid&  collisionGrid)
{
    m_collisionRect.Y -= speed; // Move up.

    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::UP);

    m_screenRect.Y = CalculateScreenYTop (ACollisionGrid::UP);
} // Endproc.


void    ASprite::MoveDown (UInt32                   speed,
                           const ACollisionGrid&    collisionGrid)
{
    m_collisionRect.Y += speed; // Move down.

    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::DOWN);

    m_screenRect.Y = CalculateScreenYTop (ACollisionGrid::DOWN);
} // Endproc.


void    ASprite::MoveLeft (UInt32                   speed,
                           const ACollisionGrid&    collisionGrid)
{
    m_collisionRect.X -= speed; // Move left.
    
    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::LEFT);
    
    m_screenRect.X = CalculateScreenXLeft (ACollisionGrid::LEFT);
} // Endproc.


void    ASprite::MoveRight (UInt32                  speed,
                            const ACollisionGrid&   collisionGrid)
{
    m_collisionRect.X += speed; // Move right.

    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::RIGHT);
    
    m_screenRect.X = CalculateScreenXLeft (ACollisionGrid::RIGHT);
} // Endproc.


void    ASprite::CheckSpritePosition (const ACollisionGrid&     collisionGrid,
                                      ACollisionGrid::DIRECTION collisionGridDirection)
{
    // Check for wall collision.

    collisionGrid.IsWallCollision (collisionGridDirection, m_collisionRect);

    // Is the sprite outwith the floor bound?

    if (collisionGrid.IsOutwithFloorBound (collisionGridDirection, m_collisionRect))
    {
        // Yes. Play the rebound sound

        PlayReboundSound (m_direction);

        // Update the sprite's m_direction.

        m_direction = UpdateDirection (GetFloorBoundDirection (collisionGridDirection));
    } // Endif.

} // Endproc.


void    ASprite::PlayReboundSound (Direction& direction) const
{
    if (!m_spriteReboundAudioAttributesList.empty ())
    {
        // Find the sprite's rebound audio attributes that relate to the direction.

        for (SpriteReboundAudioAttributesList::const_iterator itr = m_spriteReboundAudioAttributesList.begin ();
             itr != m_spriteReboundAudioAttributesList.end ();
             ++itr)
        {
            if ((itr->m_direction & direction) == direction)
            {
                Folio::Core::Util::Sound::PlayAsyncSoundSample (*(itr->m_spriteReboundSoundSample));

                break;  // Get-outta-here!
            } // Endif.

        } // Endfor.
    
    } // Endif.

} // Endproc.


bool    ASprite::IsCreated () const
{
    return (m_state != STATE_UNKNOWN);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
