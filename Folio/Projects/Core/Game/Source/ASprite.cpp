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
    m_action(NO_ACTION),
    m_speed(STATIC_SPEED),
    m_currentSpriteDrawingList(0),
    m_currentSpriteDrawingListIndex(FOLIO_INVALID_INDEX),
    m_previousHorizontalDirection(NO_DIRECTION),
    m_previousVerticalDirection(NO_DIRECTION),
    m_maxNumAutoMoves(0),
    m_remainingNumAutoMoves(0),
    m_initialisingDrawingMode(DM_NONE),
    m_terminatingDrawingMode(DM_NONE),
    m_isAtLockedScreenExit(false),
    m_isInScreenExit(false),
    m_isExitedScreen(false),
    m_isEnteringScreen(false),
    m_initialisingMaxSequenceCount(0),
    m_currentInitialisingSequenceCount(0),
    m_terminatingMaxSequenceCount(0),
    m_currentTerminatingSequenceCount(0),
    m_playSpriteInitialisingSoundResource (false),
    m_initialisingSpriteSoundResource(0),
    m_playSpriteInitialisingSoundSamples(false),
    m_currentInitialisingSpriteSoundSamplesListIndex(FOLIO_INVALID_INDEX),
    m_playSpriteTerminatingSoundResource(false),
    m_terminatingSpriteSoundResource(0),
    m_playSpriteTerminatingSoundSamples(false),
    m_currentTerminatingSpriteSoundSamplesListIndex(FOLIO_INVALID_INDEX),
    m_isAtWall(false),
    m_reboundFlags(NO_REBOUND),
    m_resourceGraphicsCache(0),
    m_dcHandle(FOLIO_INVALID_HANDLE),
    m_spriteMovementAudioCount(0),
    m_currentMovementSoundSamplesListIndex(FOLIO_INVALID_INDEX),
    m_playSpriteInitialisedSound(false),
    m_playSpriteTerminatedSound(false), 
    m_playSpriteReboundSound(false), 
    m_actionTickCount(0)
{
} // Endproc.


ASprite::~ASprite ()
{
    // Destroy the sprite.

    Destroy ();
} // Endproc.


FolioStatus ASprite::GainResourceGraphics (const Folio::Core::Game::ResourceGraphicsCache::OwnerId& ownerId)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Does the sprite support resource graphics caching?

        if (m_resourceGraphicsCache)
        {
            // Yes. Gain the sprite's graphics from the resource cache.

            for (SpriteDrawingList::const_iterator itr = m_spriteDrawingList.begin ();
                 (status == ERR_SUCCESS) && (itr != m_spriteDrawingList.end ());
                 ++itr)
            {
                status = itr->GainResourceGraphics (ownerId, *m_resourceGraphicsCache);
            } // Endfor.

            if ((status == ERR_SUCCESS) && !m_initialisingSpriteDrawingList.empty ())
            {
                // Gain the sprite's initialising graphics from the resource cache.

                for (SpriteDrawingList::const_iterator itr = m_initialisingSpriteDrawingList.begin ();
                     (status == ERR_SUCCESS) && (itr != m_initialisingSpriteDrawingList.end ());
                     ++itr)
                {
                    status = itr->GainResourceGraphics (ownerId, *m_resourceGraphicsCache);
                } // Endfor.
        
            } // Endif.

            if ((status == ERR_SUCCESS) && !m_terminatingSpriteDrawingList.empty ())
            {
                // Gain the sprite's terminating graphics from the resource cache.

                for (SpriteDrawingList::const_iterator itr = m_terminatingSpriteDrawingList.begin ();
                     (status == ERR_SUCCESS) && (itr != m_terminatingSpriteDrawingList.end ());
                     ++itr)
                {
                    status = itr->GainResourceGraphics (ownerId, *m_resourceGraphicsCache);
                } // Endfor.
        
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


FolioStatus ASprite::ReleaseResourceGraphics ()
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Does the sprite support resource graphics caching?

        if (m_resourceGraphicsCache)
        {
            // Yes. Release the sprite's graphics from the resource cache.

            for (SpriteDrawingList::const_iterator itr = m_spriteDrawingList.begin ();
                 (status == ERR_SUCCESS) && (itr != m_spriteDrawingList.end ());
                 ++itr)
            {
                status = itr->ReleaseResourceGraphics (*m_resourceGraphicsCache);
            } // Endfor.

            if ((status == ERR_SUCCESS) && !m_initialisingSpriteDrawingList.empty ())
            {
                // Release the sprite's initialising graphics from the resource cache.

                for (SpriteDrawingList::const_iterator itr = m_initialisingSpriteDrawingList.begin ();
                     (status == ERR_SUCCESS) && (itr != m_initialisingSpriteDrawingList.end ());
                     ++itr)
                {
                    status = itr->ReleaseResourceGraphics (*m_resourceGraphicsCache);
                } // Endfor.

            } // Endif.

            if ((status == ERR_SUCCESS) && !m_terminatingSpriteDrawingList.empty ())
            {
                // Release the sprite's terminating graphics from the resource cache.

                for (SpriteDrawingList::const_iterator itr = m_terminatingSpriteDrawingList.begin ();
                     (status == ERR_SUCCESS) && (itr != m_terminatingSpriteDrawingList.end ());
                     ++itr)
                {
                    status = itr->ReleaseResourceGraphics (*m_resourceGraphicsCache);
                } // Endfor.

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


FolioStatus ASprite::ChangeSpriteInkColour (Gdiplus::ARGB   spriteInkColour,
                                            bool            includeInitialisingGraphics,
                                            bool            includeTerminatingGraphics,
                                            bool            forceColourChange)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. Should the colour change be forced or has the sprite's colour 
        // changed?

        if (forceColourChange || (spriteInkColour != m_spriteInkColour))
        {
            // Yes. Change the colour of the sprite's graphics.

            for (SpriteDrawingList::iterator itr = m_spriteDrawingList.begin ();
                 (status == ERR_SUCCESS) && (itr != m_spriteDrawingList.end ());
                 ++itr)
            {
                if (itr->m_action == m_action)
                {
                    // Change the colour of the sprite's graphic.

                    status = itr->ChangeSpriteGraphicColour (spriteInkColour);

                    if (status == ERR_SUCCESS)
                    {
                        // Create the sprite's bitmaps.

                        status = itr->CreateSpriteBitmaps (m_dcHandle, m_screenScale);
                    } // Endif.

                } // Endif.

            } // Endfor.

            if (includeInitialisingGraphics && (status == ERR_SUCCESS) && !m_initialisingSpriteDrawingList.empty ())
            {
                // Change the colour of the sprite's initialising graphics.

                for (SpriteDrawingList::iterator itr = m_initialisingSpriteDrawingList.begin ();
                     (status == ERR_SUCCESS) && (itr != m_initialisingSpriteDrawingList.end ());
                     ++itr)
                {
                    // Change the colour of the sprite's initialising graphic.

                    status = itr->ChangeSpriteGraphicColour (spriteInkColour);

                    if (status == ERR_SUCCESS)
                    {
                        // Create the sprite's initialising bitmaps.

                        status = itr->CreateSpriteBitmaps (m_dcHandle, m_screenScale);
                    } // Endif.

                } // Endfor.

            } // Endif.

            if (includeTerminatingGraphics && (status == ERR_SUCCESS) && !m_terminatingSpriteDrawingList.empty ())
            {
                // Change the colour of the sprite's terminating graphics.

                for (SpriteDrawingList::iterator itr = m_terminatingSpriteDrawingList.begin ();
                     (status == ERR_SUCCESS) && (itr != m_terminatingSpriteDrawingList.end ());
                     ++itr)
                {
                    // Change the colour of the sprite's terminating graphic.

                    status = itr->ChangeSpriteGraphicColour (spriteInkColour);

                    if (status == ERR_SUCCESS)
                    {
                        // Create the sprite's terminating bitmaps.

                        status = itr->CreateSpriteBitmaps (m_dcHandle, m_screenScale);
                    } // Endif.

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


FolioStatus ASprite::StoreUnderlyingBackground (Gdiplus::Graphics&  graphics,
                                                Gdiplus::Rect*      rect)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        switch (m_state)
        {
        case STATE_UNKNOWN:
            status = ERR_INVALID_SEQUENCE;
            break;
 
        case STATE_INITIALISE_RQD:
            if (m_initialisingDrawingMode == DM_GRAPHIC)
            {
                // Set the sprite's screen size, based on the sprite's initialising bitmap.

                SetSpriteScreenSize (m_initialisingSpriteDrawingList.front ().GetCurrentSpriteBitmap ());
            } // Endif.

            // Buffer the underlying background.
    
            status = m_underlyingBackground.Buffer (graphics, GetScaledRect (m_screenRect.X, m_screenRect.Y));  
            break;

        case STATE_TERMINATE_RQD:
            if (m_terminatingDrawingMode == DM_GRAPHIC)
            {
                // Set the sprite's screen size, based on the sprite's terminating bitmap.

                SetSpriteScreenSize (m_terminatingSpriteDrawingList.front ().GetCurrentSpriteBitmap ());
            } // Endif.

            // Buffer the underlying background.
    
            status = m_underlyingBackground.Buffer (graphics, GetScaledRect (m_screenRect.X, m_screenRect.Y));
            break;

        case STATE_INITIALISING:
        case STATE_INITIALISED:
        case STATE_TERMINATING:
        case STATE_STATIC:
        case STATE_MOVING:
            // Buffer the underlying background.
    
            status = m_underlyingBackground.Buffer (graphics, rect ? *rect : GetScaledRect (m_screenRect.X, m_screenRect.Y));
            break;

        case STATE_TERMINATED:
        default:
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::RestoreUnderlyingBackground (Gdiplus::Graphics&    graphics,
                                                  RectList*             rects)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
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

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

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
            // Play the sprite's movement sound.

            status = PlaySpriteMovementSound ();
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

    // Have we created a sprite?

    if (IsCreated ())
    {
        switch (m_state)
        {
        case STATE_UNKNOWN:
            status = ERR_INVALID_SEQUENCE;
            break;

        case STATE_INITIALISE_RQD:
            if (m_initialisingDrawingMode == DM_GRAPHIC)
            {
                // Set the sprite's initialising bitmaps.

                status = SetCurrentSpriteBitmaps (m_direction, 
                                                  m_initialisingSpriteDrawingList);
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
                // Set the sprite's terminating bitmaps.

                status = SetCurrentSpriteBitmaps (m_direction,
                                                  m_terminatingSpriteDrawingList);
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
        case STATE_STATIC:
        case STATE_MOVING:
        case STATE_FALLING:
            status = DrawSprite (graphics, rects);
            break;

        case STATE_TERMINATED:
        default:
            break;
        } // Endswitch.

    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::SetScreenTopLeft (Int32    screenXLeft,
                                       Int32    screenY,
                                       bool     screenYTopSpecified)
{
    FolioStatus status = ERR_SUCCESS;

    Int32   screenYTop = screenY;   // Initialise!

    // If the screen YTop is not specified, then calculate it.

    if (!screenYTopSpecified)
    {
        screenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (screenY, 
                                                                         m_screenWidth,
                                                                         m_screenHeight);
    } // Endif.

    // Set the sprite's new screen X and Y positions.

    m_screenRect.X  = screenXLeft; 
    m_screenRect.Y  = screenYTop;

    // Calculate the sprite's new moving X and Y positions.

    m_movingRect.X = CalculateMovingXLeft (m_screenWidth);
    m_movingRect.Y = CalculateMovingYTop (m_screenHeight);

    return (status);
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


Gdiplus::Rect   ASprite::GetMovingRect () const
{
    return (m_movingRect);
} // Endproc.


Int32   ASprite::GetMovingXLeft () const
{
    return (m_movingRect.X);
} // Endproc.


Int32   ASprite::GetMovingYTop () const
{
    return (m_movingRect.Y);
} // Endproc.


Int32   ASprite::GetMovingXRight () const
{
    return (m_movingRect.X + m_movingRect.Width - 1);
} // Endproc.


Int32   ASprite::GetMovingYBottom () const
{
    return (m_movingRect.Y + m_movingRect.Height - 1);
} // Endproc.


Int32   ASprite::GetMovingWidth () const
{
    return (m_movingRect.Width);
} // Endproc.


Int32   ASprite::GetMovingHeight () const
{
    return (m_movingRect.Height);
} // Endproc.


ACollisionGrid::CellValue   ASprite::GetCollisionGridCellValue () const
{
    ACollisionGrid::CellValue   collisionGridCellValue = ACollisionGrid::CELL_VALUE_EMPTY;  // Initialise!

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        collisionGridCellValue = (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].GetSpriteCollisionGridCellValue (); 
    } // Endif.

    return (collisionGridCellValue);
} // Endproc.


Gdiplus::Rect   ASprite::GetCollisionGridDeltaRect () const
{
    Gdiplus::Rect   collisionGridDeltaRect;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        collisionGridDeltaRect = (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].GetSpriteCollisionGridDeltaRect (); 
    } // Endif.

    return (collisionGridDeltaRect);
} // Endproc.


SpriteGraphic   ASprite::GetCurrentSpriteGraphic () const
{
    SpriteGraphic   spriteGraphic;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        spriteGraphic = (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].GetCurrentSpriteGraphic (); 
    } // Endif.

    return (spriteGraphic);
} // Endproc.


Int32   ASprite::GetCurrentSpriteGraphicWidth () const
{
    SpriteGraphic   spriteGraphic(GetCurrentSpriteGraphic ());
        
    return (spriteGraphic ? spriteGraphic->GetGraphicWidth () : FOLIO_UNDEFINED);
} // Endproc.


Int32   ASprite::GetCurrentSpriteGraphicHeight () const
{
    SpriteGraphic   spriteGraphic(GetCurrentSpriteGraphic ());
        
    return (spriteGraphic ? spriteGraphic->GetGraphicHeight () : FOLIO_UNDEFINED);
} // Endproc.


void    ASprite::SetState (STATE    state, 
                           bool     playSpriteStateSound)
{ 
    m_state = state;
   
    switch (m_state)
    {
    case STATE_INITIALISE_RQD:
        SetPlaySpriteInitialisingSound (playSpriteStateSound);
        break;

    case STATE_INITIALISED:
        SetPlaySpriteInitialisedSound (playSpriteStateSound);
        break;

    case STATE_TERMINATE_RQD:
        SetPlaySpriteTerminatingSound (playSpriteStateSound);
        break;

    case STATE_TERMINATED:
        SetPlaySpriteTerminatedSound (playSpriteStateSound);
        break;

    case STATE_FALLING:
        // Always exit south.

        // Set the sprite's current bitmaps, based on the new direction.

        SetCurrentSpriteBitmaps (S, m_spriteDrawingList);
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


ASprite::STATE  ASprite::GetState () const
{
    return (m_state);
} // Endproc.


FolioString ASprite::DescribeState (STATE state)
{
    switch (state)
    {
    case STATE_CREATED:
        return (TXT("Created"));
    case STATE_INITIALISE_RQD:
        return (TXT("InitialiseRqd"));
    case STATE_INITIALISING:
        return (TXT("Initialising"));
    case STATE_INITIALISED:
        return (TXT("Initialised"));
    case STATE_TERMINATE_RQD:
        return (TXT("TerminateRqd"));
    case STATE_TERMINATING:
        return (TXT("Terminating"));
    case STATE_TERMINATED:
        return (TXT("Terminated"));
    case STATE_STATIC:
        return (TXT("Static"));
    case STATE_MOVING:
        return (TXT("Moving"));
    case STATE_FALLING:
        return (TXT("Falling"));
    case STATE_UNKNOWN:
    default:
        return (TXT("Unknown"));
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


void    ASprite::SetAlive (bool playSpriteInitialisingSound)
{
    SetState (STATE_INITIALISE_RQD, playSpriteInitialisingSound);
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
    SetState (STATE_TERMINATE_RQD, playSpriteTerminatingSound);
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


Direction   ASprite::GetDirection () const
{
    return (m_direction);
} // Endproc.


Action  ASprite::GetAction () const
{
    return (m_action);
} // Endproc.


FolioStatus ASprite::SetScreenEntranceTopLeft (const Gdiplus::Rect&     screenScreenRect,
                                               const ACollisionGrid*    collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    switch (m_screenExit.m_orientation)
    {
    case ACollisionGrid::ScreenExit::TOP:
        // Calculate the sprite's new moving Y position.

        m_movingRect.Y = screenScreenRect.Y + screenScreenRect.Height - 1 - m_movingRect.Height ; 

        if (collisionGrid)
        {
            // Check for a collision with a wall.

            collisionGrid->IsWallCollision (ACollisionGrid::UP, m_movingRect, true);
        } // Endif.

        // Set the sprite's new top-left position.

        status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::UP), 
                                   CalculateScreenYTop (ACollisionGrid::UP));
        break;

    case ACollisionGrid::ScreenExit::BOTTOM:
        // Calculate the sprite's new moving Y position.
 
        m_movingRect.Y = screenScreenRect.Y;

        if (collisionGrid)
        {
            // Check for a collision with a wall.

            collisionGrid->IsWallCollision (ACollisionGrid::DOWN, m_movingRect, true);
        } // Endif.

        // Set the sprite's new top-left position.

        status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::DOWN), 
                                   CalculateScreenYTop (ACollisionGrid::DOWN));
        break;

    case ACollisionGrid::ScreenExit::LEFT:
        // Calculate the sprite's new moving X position.

        m_movingRect.X = screenScreenRect.X + screenScreenRect.Width - 1 - m_movingRect.Width; 

        if (collisionGrid)
        {
            // Check for a collision with a wall.

            collisionGrid->IsWallCollision (ACollisionGrid::LEFT, m_movingRect, true);
        } // Endif.

        // Set the sprite's new top-left position.

        status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::LEFT), 
                                   CalculateScreenYTop (ACollisionGrid::LEFT));
        break;                                                                                             

    case ACollisionGrid::ScreenExit::RIGHT:
        // Calculate the sprite's new moving X position.

        m_movingRect.X = screenScreenRect.X;

        if (collisionGrid)
        {
            // Check for a collision with a wall.

            collisionGrid->IsWallCollision (ACollisionGrid::RIGHT, m_movingRect, true);
        } // Endif.

        // Set the sprite's new top-left position.

        status = SetScreenTopLeft (CalculateScreenXLeft (ACollisionGrid::RIGHT), 
                                   CalculateScreenYTop (ACollisionGrid::RIGHT));
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::SetScreenEntrance (ACollisionGrid::ScreenEntrance& screenEntrance) 
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the screen entrance attributes if the sprite is entering the screen.

    if (m_isEnteringScreen)
    {
        m_screenExit = screenEntrance;

        // Set the sprite's direction.

        switch (screenEntrance.m_orientation)
        {
        case ACollisionGrid::ScreenEntrance::TOP:
        case ACollisionGrid::ScreenEntrance::FLOOR:
            status = SetDirection (S);
            break;

        case ACollisionGrid::ScreenEntrance::BOTTOM:
            status = SetDirection (N);
            break;
        
        case ACollisionGrid::ScreenEntrance::LEFT:
            status = SetDirection (E);
            break;
        
        case ACollisionGrid::ScreenEntrance::RIGHT:
            status = SetDirection (W);
            break;
        
        default:
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


void    ASprite::ResetScreenEntrance () 
{
    ResetScreenExit ();
} // Endproc.


void    ASprite::ResetScreenExit () 
{
    m_isAtLockedScreenExit  = false;
    m_isInScreenExit        = false;
    m_isExitedScreen        = false;
    m_isEnteringScreen      = false;

    m_screenExit.Reset ();
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


FolioString ASprite::Describe () const
{
    FolioOStringStream  str;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        // Describe the sprite's current sprite bitmaps.

        str << (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].DescribeCurrentSpriteBitmap ()
            << TXT(" ");
    } // Endif.
        
    str << TXT("s=") << DescribeState (m_state)
        << TXT(" x=") << m_screenRect.X
        << TXT(" y=") << m_screenRect.Y
        << TXT(" w=") << m_screenRect.Width
        << TXT(" h=") << m_screenRect.Height
        << TXT(" d=") << DescribeDirection (m_direction)
        << TXT(" a=") << m_action
        << TXT(" v=") << m_speed;

    return (str.str ());
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


bool    ASprite::IsCreated () const
{
    return (m_state != STATE_UNKNOWN);
} // Endproc.


FolioStatus ASprite::Create (FolioHandle                                dcHandle,
                             const SpriteGraphicAttributesList&         spriteGraphicAttributesList,
                             Int32                                      initialScreenXLeft,
                             Int32                                      initialScreenYTop,
                             UInt32                                     screenScale,
                             Gdiplus::ARGB                              spriteInkColour,
                             Direction                                  initialDirection,
                             Folio::Core::Game::ResourceGraphicsCache   *resourceGraphicsCache,
                             UInt32                                     maxNumAutoMoves,
                             UInt32                                     reboundFlags)
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
        // No. Create the sprite's drawing list.

        status = CreateSpriteDrawingList (dcHandle, 
                                          spriteGraphicAttributesList,
                                          screenScale,
                                          initialDirection,
                                          m_spriteDrawingList);

        if (status == ERR_SUCCESS)
        {
            // Set the sprite's current bitmaps.

            status = SetCurrentSpriteBitmaps (initialDirection, m_spriteDrawingList);

            if (status == ERR_SUCCESS)
            {
                // Get the sprite's current bitmap.

                SpriteDrawing::SpriteBitmap currentSpriteBitmap(GetCurrentSpriteBitmap ());

                // Set the sprite's new width.

                SetSpriteWidth (currentSpriteBitmap->GetScreenWidth ());

                // Set the sprite's new height.

                SetSpriteHeight (currentSpriteBitmap->GetScreenHeight ());

                // Set the sprite's new top-left position.

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
                        m_resourceGraphicsCache = resourceGraphicsCache;
                        m_dcHandle              = dcHandle;
                        m_reboundFlags          = reboundFlags;

                        // Set the sprite's previous direction.

                        SetPreviousDirection (m_direction);

                        // We're good to go.

                        m_state = STATE_CREATED;
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::Recreate (Int32        screenXLeft,
                               Int32        screenYTop,
                               Direction    direction)
{
    m_state     = STATE_CREATED;
    m_action    = NO_ACTION;
    m_speed     = STATIC_SPEED;

    // Set the sprite's direction.

    FolioStatus status = SetDirection (direction);

    if (status == ERR_SUCCESS)
    {
        // Set the sprite's screen size.

        SetSpriteScreenSize (ResetCurrentSpriteBitmap ());

        // Set the sprite's top-left screen position.

        status = SetScreenTopLeft (screenXLeft, screenYTop);

        if (status == ERR_SUCCESS)
        {
            m_remainingNumAutoMoves = m_maxNumAutoMoves;    // Initialise!

            m_isAtLockedScreenExit  = false;    // Initialise!
            m_isInScreenExit        = false;
            m_isExitedScreen        = false;
            m_isEnteringScreen      = false;
            
            m_currentInitialisingSpriteSoundSamplesListIndex    = 0;    // Initialise!
            m_currentTerminatingSpriteSoundSamplesListIndex     = 0;

            m_isAtWall = false; // Initialise!

            m_currentInitialisingSequenceCount = 0; // Initialise!
            m_currentTerminatingSequenceCount  = 0;

            m_spriteMovementAudioCount              = 0; // Initialise!
            m_currentMovementSoundSamplesListIndex  = 0;
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::Destroy ()
{
    return (ReleaseResourceGraphics ());
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

    SpriteDrawing::SpriteBitmap spriteBitmap;
    SpriteDrawing::SpriteBitmap spriteMaskedBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteBitmap,
                                                    spriteMaskedBitmap);

    if (status == ERR_SUCCESS)
    {
        // Draw the sprite's masked bitmap.

        status = spriteMaskedBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's bitmap.

            status = spriteBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


void    ASprite::SetSpriteMovementSoundSamples (const SpriteMovementSoundSamplesList& spriteMovementSoundSamplesList)
{
    m_spriteMovementSoundSamplesList = spriteMovementSoundSamplesList;
   
    m_currentSpriteMovementSoundSamplesList.clear ();   // Initialise!
    m_currentMovementSoundSamplesListIndex = FOLIO_INVALID_INDEX;
} // Endproc.


void    ASprite::SetSpriteInitialisedSoundSample (const SpriteSoundSample& spriteInitialisedSoundSample)
{
    m_spriteInitialisedSoundSample = spriteInitialisedSoundSample;

    SetPlaySpriteInitialisedSound (true); 
} // Endproc.


void    ASprite::SetSpriteTerminatedSoundSample (const SpriteSoundSample& spriteTerminatedSoundSample)
{
    m_spriteTerminatedSoundSample = spriteTerminatedSoundSample;

    SetPlaySpriteTerminatedSound (true); 
} // Endproc.


void    ASprite::SetSpriteReboundSoundSample (const SpriteSoundSample& spriteReboundSoundSample)
{
    m_spriteReboundSoundSample = spriteReboundSoundSample;

    SetPlaySpriteReboundSound (true); 
} // Endproc.


FolioStatus ASprite::SetGraphicInitialisingMode (FolioHandle                        dcHandle,
                                                 const SpriteGraphicAttributesList& initialisingSpriteGraphicAttributesList,
                                                 UInt32                             initialisingMaxSequenceCount,
                                                 FolioHandle                        initialisingSpriteSoundResource)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the initialising mode if the current state is created or initialise required.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Create the sprite's initialising drawing list.

        status = CreateSpriteDrawingList (dcHandle, 
                                          initialisingSpriteGraphicAttributesList,
                                          m_screenScale,
                                          m_initialisingSpriteDrawingList);

        if (status == ERR_SUCCESS)
        {
            // Note the sprite's initialising attributes.

            m_initialisingDrawingMode               = DM_GRAPHIC;
            m_initialisingMaxSequenceCount          = initialisingMaxSequenceCount * m_initialisingSpriteDrawingList.front ().m_spriteGraphicsList.size ();
            m_currentInitialisingSequenceCount      = 0;
            m_playSpriteInitialisingSoundResource   = initialisingSpriteSoundResource != 0; 
            m_initialisingSpriteSoundResource       = initialisingSpriteSoundResource;
        } // Endif.
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::SetGraphicTerminatingMode (FolioHandle                         dcHandle,
                                                const SpriteGraphicAttributesList&  terminatingSpriteGraphicAttributesList,
                                                UInt32                              terminatingMaxSequenceCount,
                                                FolioHandle                         terminatingSpriteSoundResource)
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
        // Create the sprite's terminating drawing list.

        status = CreateSpriteDrawingList (dcHandle, 
                                          terminatingSpriteGraphicAttributesList, 
                                          m_screenScale,
                                          m_terminatingSpriteDrawingList);

        if (status == ERR_SUCCESS)
        {
            // Note the sprite's terminating attributes.

            m_terminatingDrawingMode                = DM_GRAPHIC;
            m_terminatingMaxSequenceCount           = terminatingMaxSequenceCount * m_terminatingSpriteDrawingList.front ().m_spriteGraphicsList.size ();
            m_currentTerminatingSequenceCount       = 0;
            m_playSpriteTerminatingSoundResource    = terminatingSpriteSoundResource != 0; 
            m_terminatingSpriteSoundResource        = terminatingSpriteSoundResource;
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
    m_playSpriteInitialisingSoundSamples = playSpriteInitialisingSound && 
                                           !m_initialisingSpriteSoundSamplesList.empty ();

    m_playSpriteInitialisingSoundResource = playSpriteInitialisingSound && 
                                            m_initialisingSpriteSoundResource;
} // Endproc.


void    ASprite::SetPlaySpriteTerminatingSound (bool playSpriteTerminatingSound)
{
    m_playSpriteTerminatingSoundSamples = playSpriteTerminatingSound &&
                                          !m_terminatingSpriteSoundSamplesList.empty ();

    m_playSpriteTerminatingSoundResource = playSpriteTerminatingSound && 
                                           m_terminatingSpriteSoundResource;
} // Endproc.


void    ASprite::SetPlaySpriteInitialisedSound (bool playSpriteInitialisedSound)
{
    m_playSpriteInitialisedSound = playSpriteInitialisedSound &&
                                   m_spriteInitialisedSoundSample.get () != 0;
} // Endproc.


void    ASprite::SetPlaySpriteTerminatedSound (bool playSpriteTerminatedSound)
{
    m_playSpriteTerminatedSound = playSpriteTerminatedSound &&
                                  m_spriteTerminatedSoundSample.get () != 0;
} // Endproc.


void    ASprite::SetPlaySpriteReboundSound (bool playSpriteReboundSound)
{
    m_playSpriteReboundSound = playSpriteReboundSound &&
                               m_spriteReboundSoundSample.get () != 0;
} // Endproc.


FolioStatus ASprite::SetDirection (Direction direction)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the sprite's direction changed?

    if (m_direction != direction)
    {
        // Set the sprite's previous direction.

        SetPreviousDirection (m_direction);

        // Note the sprite's new direction.
        
        m_direction = direction;

        // Set the sprite's current bitmaps, based on the new direction.

        status = SetCurrentSpriteBitmaps (m_direction, m_spriteDrawingList);

        if (status == ERR_SUCCESS)
        {
            // Set the sprite's current movement sound sample based on the new 
            // direction. 

            status = SetCurrentSpriteMovementSoundSample (m_direction);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    ASprite::IsDirection (Direction direction) const
{
    return (m_direction == direction);
} // Endproc.


bool    ASprite::IsDirection () const
{
    return (m_direction != NO_DIRECTION);
} // Endproc.


FolioStatus ASprite::SetAction (Action  action,
                                UInt32  actionTickCount)
{
    FolioStatus status = ERR_SUCCESS;

    // Has the sprite's action changed?

    if (action == m_action)
    {
        // No. 
        
        if (action != NO_ACTION)
        {
            // Select the current sprite's next bitmaps.

            status = SelectNextSpriteBitmaps ();
        } // Endif.

    } // Endif.

    else
    {
        // Yes. Note the sprite's new action.

        m_action = action;
    
        // Set the sprite's current bitmaps, based on the new action.

        status = SetCurrentSpriteBitmaps (m_direction, 
                                          m_spriteDrawingList,
                                          true);    // Set the sprite's screen size.

        if (actionTickCount && (status == ERR_SUCCESS))
        {
            // Start the action tick count.

            StartActionTickCount (actionTickCount);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::ResetAction ()
{
    return (SetAction (NO_ACTION));
} // Endproc.


bool    ASprite::IsAction (Action action) const
{
    return (m_action == action);
} // Endproc.


bool    ASprite::IsAction () const
{
    return (m_action != NO_ACTION);
} // Endproc.


bool    ASprite::IsActionComplete (Action action) const
{
    return (IsAction (action) && IsActionTickCountComplete ());
} // Endproc.


bool    ASprite::IsAtWall () const
{
    return (m_isAtWall);
} // Endproc.


void    ASprite::SetPreviousDirection (Direction direction)
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
        m_previousHorizontalDirection   = NO_DIRECTION;
        break;
    } // Endswitch.

} // Endproc.


Direction   ASprite::GetPreviousDirection () const
{
    return (m_previousHorizontalDirection | m_previousVerticalDirection);
} // Endproc.


Direction   ASprite::GetPreviousHorizontalDirection () const
{
    return (m_previousHorizontalDirection);
} // Endproc.


Direction   ASprite::GetPreviousVerticalDirection () const
{
    return (m_previousVerticalDirection);
} // Endproc.


Direction   ASprite::GetDirectionToScreenTopLeft (Int32                 initialScreenXLeft,
                                                  Int32                 initialScreenYTop,
                                                  const ACollisionGrid& collisionGrid,
                                                  bool                  toScreenTopLeft) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    if (toScreenTopLeft)
    {
        direction  = (m_movingRect.X <= initialScreenXLeft) ? E : W;
        direction |= (m_movingRect.Y <= initialScreenYTop) ? S : N;
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
    return ((m_movingRect.X == initialScreenXLeft) &&
            (m_movingRect.Y == initialScreenYTop));
} // Endproc.


Direction   ASprite::GetDirectionToScreenRect (const Gdiplus::Rect&     screenRect,
                                               const ACollisionGrid&    collisionGrid,
                                               bool                     toScreenRect) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    if (toScreenRect)
    {
        direction  = (m_movingRect.X <= screenRect.X) ? E : W;
        direction |= ((m_movingRect.Y + m_movingRect.Height - 1) <= (screenRect.Y + screenRect.Height - 1)) ? S : N;
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
    return ((m_movingRect.X == screenRect.X) &&
           ((m_movingRect.Y + m_movingRect.Height) == (screenRect.Y + screenRect.Height)));
} // Endproc.


Direction  ASprite::GetDirectionToNearestCorner (const ACollisionGrid &collisionGrid) const
{
    Direction   direction = ((m_movingRect.X + m_movingRect.Width / 2) <= (collisionGrid.GetFloorLeftBound () + collisionGrid.GetFloorWidth () / 2)) ? W : E;
    direction |= ((m_movingRect.Y + m_movingRect.Height / 2) <= (collisionGrid.GetFloorTopBound () + collisionGrid.GetFloorHeight () / 2)) ? N : S;

    return (direction);
} // Endproc.


FolioStatus ASprite::SetCurrentSpriteBitmaps (Direction             direction,
                                              SpriteDrawingList&    spriteDrawingList,
                                              bool                  setSpriteScreenSize)
{
    FolioStatus status = ERR_NOT_FOUND;

    if (spriteDrawingList.size () == 1)
    {
        // Set the current sprite drawing list.

        m_currentSpriteDrawingList      = &(spriteDrawingList);
        m_currentSpriteDrawingListIndex = 0;

        status = ERR_SUCCESS;
    } // Endif.

    else
    {
        // Find the sprite bitmaps that relate to the sprite bitmap index and direction.

        bool    foundAction = false;    // Initialise!

        for (SpriteDrawingList::iterator itr = spriteDrawingList.begin ();
             itr != spriteDrawingList.end ();
             ++itr)
        {
            if (itr->m_action == m_action)
            {
                foundAction = true;

                if ((itr->m_direction & direction) == itr->m_direction)
                {
                    // Set the current sprite drawing list.
                
                    m_currentSpriteDrawingList      = &(spriteDrawingList);
                    m_currentSpriteDrawingListIndex = std::distance (spriteDrawingList.begin (), itr);

                    status = ERR_SUCCESS;

                    break;  // Get-outta-here!
                } // Endif.

            } // Endif.

            else
            if (foundAction)
            {
                break;  // Get-outta-here!
            } // Endelseif.

        } // Endfor.

        if (status == ERR_NOT_FOUND)
        {
            // Find the sprite bitmaps that relate to the sprite bitmap index and previous direction.

            Direction   previousDirection = GetPreviousDirection ();

            foundAction = false;    // Initialise!

            for (SpriteDrawingList::iterator itr = spriteDrawingList.begin ();
                 itr != spriteDrawingList.end ();
                 ++itr)
            {
                if (itr->m_action == m_action)
                {
                    foundAction = true;

                    if ((itr->m_direction & previousDirection) == itr->m_direction)
                    {
                        // Set the current sprite drawing list.
                    
                        m_currentSpriteDrawingList      = &(spriteDrawingList);
                        m_currentSpriteDrawingListIndex = std::distance (spriteDrawingList.begin (), itr);

                        status = ERR_SUCCESS;

                        break;  // Get-outta-here!
                    } // Endif.

                } // Endif.

                else
                if (foundAction)
                {
                    break;  // Get-outta-here!
                } // Endelseif.

            } // Endfor.

        } // Endfor.
    
    } // Endelse.

    if (setSpriteScreenSize && (status == ERR_SUCCESS))
    {
        // Set the sprite's screen size, based on the sprite's current bitmap.

        SetSpriteScreenSize (GetCurrentSpriteBitmap ());
    } // Endif.

    if (status == ERR_NOT_FOUND)
    {
        FOLIO_DEBUG_BREAK;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::QueryCurrentSpriteBitmaps (SpriteDrawing::SpriteBitmap&    spriteBitmap,
                                                SpriteDrawing::SpriteBitmap&    spriteMaskedBitmap,
                                                bool                            incrementCurrentSpriteGraphicsListIndex)
{
    FolioStatus status = ERR_SUCCESS;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        // Query the sprite's current sprite bitmaps.

        (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].QueryCurrentSpriteBitmaps (m_state,
                                                                                                   spriteBitmap,
                                                                                                   spriteMaskedBitmap,
                                                                                                   incrementCurrentSpriteGraphicsListIndex);
    } // Endif.

    else
    {
        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::SelectNextSpriteBitmaps ()
{
    FolioStatus status = ERR_SUCCESS;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        // Query the sprite's current sprite bitmaps.

        (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].SelectNextSpriteBitmaps ();
    } // Endif.

    else
    {
        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.


bool    ASprite::IsAutoMoveModeSupported () const
{
    return (m_maxNumAutoMoves != 0);
} // Endproc.


void    ASprite::IncNumRemainingAutoModeMoves ()
{
    // Only increment the remaining number of auto-moves if it's not reached 
    // the maximum number of auto-moves.

    if (m_remainingNumAutoMoves < m_maxNumAutoMoves)
    {
        m_remainingNumAutoMoves++;
    } // Endif.

} // Endproc.


void    ASprite::ResetNumRemainingAutoModeMoves ()
{
    m_remainingNumAutoMoves = 0;
} // Endproc.


FolioStatus ASprite::PlaySpriteInitialisingSound (UInt32    initialisingSequenceCount,
                                                  UInt32    initialisingSpriteSoundSamplesListIndex,
                                                  bool      playAsynchronously) const
{
    FolioStatus status = ERR_SUCCESS;

    if (!initialisingSequenceCount && m_playSpriteInitialisingSoundResource)
    {
        // Play the sprite's initialising sound resource.

        status = PlaySpriteSoundResource (m_initialisingSpriteSoundResource, playAsynchronously);
    } // Endif.

    else
    if (m_playSpriteInitialisingSoundSamples)
    {
        // Play the sprite's initialising sound samples.

        status = PlaySpriteStationarySoundSamples (m_initialisingSpriteSoundSamplesList,
                                                   initialisingSpriteSoundSamplesListIndex,
                                                   playAsynchronously);
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus ASprite::PlaySpriteTerminatingSound (UInt32 terminatingSequenceCount,
                                                 UInt32 terminatingSpriteSoundSamplesListIndex,
                                                 bool   playAsynchronously) const
{
    FolioStatus status = ERR_SUCCESS;

    if (!terminatingSequenceCount && m_playSpriteTerminatingSoundResource)
    {
        // Play the sprite's terminating sound resource.

        status = PlaySpriteSoundResource (m_terminatingSpriteSoundResource, playAsynchronously);
    } // Endif.

    else
    if (m_playSpriteTerminatingSoundSamples)
    {
        // Play the sprite's terminating sound samples.

        status = PlaySpriteStationarySoundSamples (m_terminatingSpriteSoundSamplesList,
                                                   terminatingSpriteSoundSamplesListIndex,
                                                   playAsynchronously);
    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus ASprite::PlaySpriteInitialisedSound (bool playAsynchronously) const
{
    FolioStatus status = ERR_SUCCESS;

    // Does the sprite support initialised sound?

    if (m_playSpriteInitialisedSound && 
        m_spriteInitialisedSoundSample) 
    {
        // Yes. Play the sprite's initialised sound sample.

        status = PlaySpriteSoundSample (m_spriteInitialisedSoundSample, playAsynchronously);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::PlaySpriteTerminatedSound (bool playAsynchronously) const
{
    FolioStatus status = ERR_SUCCESS;
    
    // Does the sprite support terminated sound?

    if (m_playSpriteTerminatedSound && 
        m_spriteTerminatedSoundSample) 
    {
        // Yes. Play the sprite's terminated sound sample.

        status = PlaySpriteSoundSample (m_spriteTerminatedSoundSample, playAsynchronously);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::PlaySpriteReboundSound (bool playAsynchronously) const
{
    FolioStatus status = ERR_SUCCESS;
    
    // Does the sprite support rebound sound?

    if (m_playSpriteReboundSound && 
        m_spriteReboundSoundSample) 
    {
        // Yes. Play the sprite's rebound sound sample.

        status = PlaySpriteSoundSample (m_spriteReboundSoundSample, playAsynchronously);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::PlaySpriteMovementSound (bool playAsynchronously)
{
    FolioStatus status = ERR_SUCCESS;
    
    switch (m_state)
    {
    case STATE_MOVING:
        // Does the sprite support sound when moving?

        if (m_speed && ((++m_spriteMovementAudioCount % m_speed) == 0) && 
            (m_currentMovementSoundSamplesListIndex < m_currentSpriteMovementSoundSamplesList.size ())) 
        {
            // Yes. Get the sprite's movement sound sample.

            SpriteSoundSample  spriteSoundSample(m_currentSpriteMovementSoundSamplesList [m_currentMovementSoundSamplesListIndex]);

            if (spriteSoundSample)
            {
                // Play the sprite's movement sound sample.

                status = PlaySpriteSoundSample (spriteSoundSample, playAsynchronously);
            } // Endif.

            if ((status == ERR_SUCCESS) &&
                (++m_currentMovementSoundSamplesListIndex >= m_currentSpriteMovementSoundSamplesList.size ()))
            {
                m_currentMovementSoundSamplesListIndex = 0; // Reset.
            } // Endif.

        } // Endif.
        break;

    default:
        break;
    } // Endif.

    return (status);
} // Endproc.


Direction  ASprite::GetFloorBoundDirection (ACollisionGrid::DIRECTION collisionGridDirection) const
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


ACollisionGrid::DIRECTION   ASprite::ToCollisionGridDirection (Folio::Core::Game::Direction direction)
{
    switch (direction)
    {
    case N:
        return (ACollisionGrid::UP);

    case S:
        return (ACollisionGrid::DOWN);
    
    case E:
    case NE:
    case SE:
        return (ACollisionGrid::RIGHT);
    
    case W:
    case NW:
    case SW:
        return (ACollisionGrid::LEFT);

    default:
        return (ACollisionGrid::UNDEFINED);
    } // Endswitch.

} // Endproc.


Int32   ASprite::CalculateScreenXLeft (ACollisionGrid::DIRECTION collisionGridDirection) const
{
    return (GetMovingXLeft ());
} // Endproc.


Int32   ASprite::CalculateScreenYTop (ACollisionGrid::DIRECTION collisionGridDirection) const
{
    return (GetMovingYTop ());
} // Endproc.


Int32   ASprite::CalculateScreenXLeft (Int32 bitmapScreenWidth) const
{
    return (m_screenRect.X + (m_screenWidth - bitmapScreenWidth) / 2);
} // Endproc.


Int32   ASprite::CalculateScreenYTop (Int32 bitmapScreenHeight) const
{
    return (m_screenRect.Y + (m_screenHeight - bitmapScreenHeight) / 2);
} // Endproc.


Int32   ASprite::CalculateMovingXLeft (Int32 bitmapScreenWidth) const
{
    return (GetScreenXLeft ());
} // Endproc.


Int32   ASprite::CalculateMovingYTop (Int32 bitmapScreenHeight) const
{
    return (GetScreenYTop ());
} // Endproc.


Int32   ASprite::CalculateMovingWidth (Int32 bitmapScreenWidth) const
{
    return (GetScreenWidth ());
} // Endproc.


Int32   ASprite::CalculateMovingHeight (Int32 bitmapScreenHeight) const
{
    return (GetScreenHeight ());
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

    m_state     = STATE_TERMINATED;
    m_action    = NO_ACTION;

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
            // No. Reset the remaining number of auto-moves.

            m_remainingNumAutoMoves = m_maxNumAutoMoves;
            
            // Sprite is terminated.

            m_state     = STATE_TERMINATED;
            m_action    = NO_ACTION;
        } // Endif.

    } // Endif.

    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::HandleStaticSprite (Gdiplus::Graphics&     graphics,
                                         const ACollisionGrid&  collisionGrid)
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingList (FolioHandle                           dcHandle,
                                              const SpriteGraphicAttributesList&    spriteGraphicAttributesList,
                                              UInt32                                screenScale,
                                              SpriteDrawingList&                    spriteDrawingList)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the sprite's drawing list.

    for (SpriteGraphicAttributesList::const_iterator itr = spriteGraphicAttributesList.begin ();
         (status == ERR_SUCCESS) && (itr != spriteGraphicAttributesList.end ());
         ++itr)
    {
        // Create the sprite drawing.

        SpriteDrawing   spriteDrawing(*itr);

        // Create the sprite bitmaps.

        status = spriteDrawing.CreateSpriteBitmaps (dcHandle, screenScale);

        if (status == ERR_SUCCESS)
        {
            // Add to the sprite drawing list.
            
            spriteDrawingList.push_back (spriteDrawing);
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingList (FolioHandle                           dcHandle,
                                              const SpriteGraphicAttributesList&    spriteGraphicAttributesList,
                                              UInt32                                screenScale,
                                              Direction                             direction,
                                              SpriteDrawingList&                    spriteDrawingList)
{
    FolioStatus status = ERR_SUCCESS;

    // Create the sprite's drawing list.

    for (SpriteGraphicAttributesList::const_iterator itr = spriteGraphicAttributesList.begin ();
         (status == ERR_SUCCESS) && (itr != spriteGraphicAttributesList.end ());
         ++itr)
    {
        // Create the sprite drawing.

        SpriteDrawing   spriteDrawing(*itr);

        // Create the sprite bitmaps.

        status = spriteDrawing.CreateSpriteBitmaps (dcHandle, screenScale);

        if (status == ERR_SUCCESS)
        {
            // Add to the sprite drawing list.
            
            spriteDrawingList.push_back (spriteDrawing);
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus ASprite::PerformGraphicInitialising (Gdiplus::Graphics& graphics,
                                                 RectList*          rects)
{
    // Get the sprite's initialising bitmaps.

    SpriteDrawing::SpriteBitmap spriteBitmap;
    SpriteDrawing::SpriteBitmap spriteMaskedBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteBitmap,
                                                    spriteMaskedBitmap);

    if (status == ERR_SUCCESS)
    {
        // Draw the sprite's masked bitmap.

        status = spriteMaskedBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's bitmap.

            status = spriteBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
                            
            if (status == ERR_SUCCESS)
            {
                // Play the sprite's initialising sound.

                status = PlaySpriteInitialisingSound (m_currentInitialisingSequenceCount,
                                                      m_currentInitialisingSpriteSoundSamplesListIndex);

                if (status == ERR_SUCCESS)
                {
                    if (++m_currentInitialisingSpriteSoundSamplesListIndex >= m_initialisingSpriteSoundSamplesList.size ())
                    {
                        m_currentInitialisingSpriteSoundSamplesListIndex = 0;   // Reset.
                    } // Endif.

                    // We are initialising until the maximum sequence count is reached.

                    m_state = (++m_currentInitialisingSequenceCount < m_initialisingMaxSequenceCount)
                              ? STATE_INITIALISING 
                              : STATE_INITIALISED;

                    if (m_state == STATE_INITIALISED)
                    {
                        m_currentInitialisingSequenceCount                  = 0;    // Reset.
                        m_currentInitialisingSpriteSoundSamplesListIndex    = 0;

                        // Set the sprite's current bitmaps.

                        SetCurrentSpriteBitmaps (m_direction, 
                                                 m_spriteDrawingList,
                                                 true); // Set the sprite's screen size.
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::PerformGraphicTerminating (Gdiplus::Graphics&  graphics,
                                                RectList*           rects)
{
    // Get the sprite's terminating bitmaps.

    SpriteDrawing::SpriteBitmap spriteBitmap;
    SpriteDrawing::SpriteBitmap spriteMaskedBitmap;

    FolioStatus status = QueryCurrentSpriteBitmaps (spriteBitmap,
                                                    spriteMaskedBitmap);

    if (status == ERR_SUCCESS)
    {
        // Draw the sprite's masked bitmap.

        status = spriteMaskedBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's bitmap.

            status = spriteBitmap->Draw (m_screenRect.X, m_screenRect.Y, graphics, rects);
                            
            if (status == ERR_SUCCESS)
            {
                // Play the sprite's terminating sound.

                status = PlaySpriteTerminatingSound (m_currentTerminatingSequenceCount,
                                                     m_currentTerminatingSpriteSoundSamplesListIndex);
                    
                if (status == ERR_SUCCESS)
                {
                    if (++m_currentTerminatingSpriteSoundSamplesListIndex >= m_terminatingSpriteSoundSamplesList.size ())
                    {
                        m_currentTerminatingSpriteSoundSamplesListIndex = 0;    // Reset.
                    } // Endif.

                    // We are terminating until the maximum sequence count is reached.

                    m_state = (++m_currentTerminatingSequenceCount < m_terminatingMaxSequenceCount)
                              ? STATE_TERMINATING 
                              : STATE_TERMINATED;

                    if (m_state == STATE_TERMINATED)
                    {
                        m_action = NO_ACTION;

                        m_currentTerminatingSequenceCount               = 0;    // Reset.
                        m_currentTerminatingSpriteSoundSamplesListIndex = 0;

                        // Set the sprite's current bitmaps.

                        SetCurrentSpriteBitmaps (m_direction, 
                                                 m_spriteDrawingList, 
                                                 true); // Set the sprite's screen size.
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


ASprite::SpriteDrawing::SpriteBitmap    ASprite::ResetCurrentSpriteBitmap ()
{
    SpriteDrawing::SpriteBitmap spriteBitmap;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        // Reset the sprite's current bitmap.

        (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].Reset ();

        // Get the sprite's current bitmap.

        spriteBitmap = (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].GetCurrentSpriteBitmap (); 
    } // Endif.

    return (spriteBitmap);
} // Endproc.


ASprite::SpriteDrawing::SpriteBitmap    ASprite::GetCurrentSpriteBitmap () const
{
    SpriteDrawing::SpriteBitmap spriteBitmap;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        // Get the sprite's current bitmap.
        
        spriteBitmap = (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].GetCurrentSpriteBitmap (); 
    } // Endif.

    return (spriteBitmap);
} // Endproc.


ASprite::SpriteDrawing::SpriteBitmap    ASprite::GetCurrentSpriteMaskedBitmap () const
{
    SpriteDrawing::SpriteBitmap spriteMaskedBitmap;

    if (m_currentSpriteDrawingList &&
        (m_currentSpriteDrawingListIndex < m_currentSpriteDrawingList->size ()))
    {
        // Get the sprite's current masked bitmap.

        spriteMaskedBitmap = (*m_currentSpriteDrawingList) [m_currentSpriteDrawingListIndex].GetCurrentSpriteMaskedBitmap (); 
    } // Endif.

    return (spriteMaskedBitmap);
} // Endproc.


void    ASprite::SetSpriteScreenSize (const SpriteDrawing::SpriteBitmap& spriteBitmap)
{
    if (spriteBitmap)
    {
        // Get the sprite's bitmap screen width.

        Int32   bitmapScreenWidth = spriteBitmap->GetScreenWidth ();

        // Has the sprite's screen width changed?

        if (bitmapScreenWidth != m_screenWidth)
        {
            // Yes. Calculate the sprite's new screen X position.

            m_screenRect.X = CalculateScreenXLeft (bitmapScreenWidth);

            // Set the sprite's new width.

            SetSpriteWidth (bitmapScreenWidth, false);

            // Calculate the sprite's new moving X position.

            m_movingRect.X = CalculateMovingXLeft (bitmapScreenWidth);
        } // Endif.

        // Get the sprite's bitmap screen height.

        Int32   bitmapScreenHeight = spriteBitmap->GetScreenHeight ();
    
        // Has the sprite's screen height changed?

        if (bitmapScreenHeight != m_screenHeight)
        {
            // Yes. Calculate the sprite's new screen Y position.

            m_screenRect.Y = CalculateScreenYTop (bitmapScreenHeight);

            // Set the sprite's new height.

            SetSpriteHeight (bitmapScreenHeight);

            // Calculate the sprite's new moving Y position.

            m_movingRect.Y = CalculateMovingYTop (bitmapScreenHeight);
        } // Endif.
    
    } // Endif.

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


void    ASprite::SetSpriteWidth (Int32  bitmapScreenWidth,
                                 bool   setMovingWidth)
{
    // Set the sprite's new screen width.

    m_screenRect.Width = bitmapScreenWidth;

    SetScreenWidth (bitmapScreenWidth);

    if (setMovingWidth)
    {
        // Calculate the sprite's new moving width.

        m_movingRect.Width = CalculateMovingWidth (bitmapScreenWidth);
    } // Endproc.

} // Endproc.


void    ASprite::SetSpriteHeight (Int32 bitmapScreenHeight,
                                  bool  setMovingHeight)
{
    // Set the sprite's new screen height.

    m_screenRect.Height = bitmapScreenHeight;

    SetScreenHeight (bitmapScreenHeight);

    if (setMovingHeight)
    {
        // Calculate the sprite's new moving height.

        m_movingRect.Height = CalculateMovingHeight (bitmapScreenHeight);
    } // Endif.

} // Endproc.


void    ASprite::MoveUp (UInt32                 speed,
                         const ACollisionGrid&  collisionGrid)
{
    m_movingRect.Y -= speed;    // Move up.

    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::UP);

    // Calculate the sprite's new screen Y position.

    m_screenRect.Y = CalculateScreenYTop (ACollisionGrid::UP);
} // Endproc.


void    ASprite::MoveDown (UInt32                   speed,
                           const ACollisionGrid&    collisionGrid)
{
    m_movingRect.Y += speed;    // Move down.

    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::DOWN);

    // Calculate the sprite's new screen Y position.

    m_screenRect.Y = CalculateScreenYTop (ACollisionGrid::DOWN);
} // Endproc.


void    ASprite::MoveLeft (UInt32                   speed,
                           const ACollisionGrid&    collisionGrid)
{
    m_movingRect.X -= speed;    // Move left.
    
    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::LEFT);
    
    // Calculate the sprite's new screen X position.

    m_screenRect.X = CalculateScreenXLeft (ACollisionGrid::LEFT);
} // Endproc.


void    ASprite::MoveRight (UInt32                  speed,
                            const ACollisionGrid&   collisionGrid)
{
    m_movingRect.X += speed;    // Move right.

    // Check the sprite's position.

    CheckSpritePosition (collisionGrid, ACollisionGrid::RIGHT);
    
    // Calculate the sprite's new screen X position.

    m_screenRect.X = CalculateScreenXLeft (ACollisionGrid::RIGHT);
} // Endproc.


FolioStatus ASprite::CheckSpritePosition (const ACollisionGrid&     collisionGrid,
                                          ACollisionGrid::DIRECTION collisionGridDirection)
{
    FolioStatus status = ERR_SUCCESS;

    // Check for wall collision.

    m_isAtWall = collisionGrid.IsWallCollision (collisionGridDirection, m_movingRect);

    if (!m_isAtWall)
    {
        // Check exited screen.

        m_isExitedScreen = collisionGrid.IsExitedScreen (collisionGridDirection, 
                                                         false,   // Not external to floor bound.
                                                         m_movingRect,
                                                         m_isAtLockedScreenExit,
                                                         m_isInScreenExit,
                                                         m_screenExit);
    } // Endif.

    // Has the sprite collided with a wall or exited the screen, and should it rebound?

    if ((m_isAtWall       && (m_reboundFlags & WALL_REBOUND)) ||
        (m_isExitedScreen && (m_reboundFlags & FLOOR_BOUND_REBOUND)))
    {
        // Yes. Play the sprite's rebound sound

        status = PlaySpriteReboundSound ();

        if (status == ERR_SUCCESS)
        {
            // Set the sprite's direction.

            status = SetDirection (GetFloorBoundDirection (collisionGridDirection));

            if (status == ERR_SUCCESS)
            {
                m_isAtWall = false;

                if (m_isExitedScreen)
                {
                    // Reset the screen exit
                
                    ResetScreenExit (); 
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::PlaySpriteSoundResource (FolioHandle    spriteSoundResource,
                                              bool           playAsynchronously) const
{
    return (Folio::Core::Util::Sound::PlaySoundResource (spriteSoundResource, playAsynchronously));
} // Endproc.


FolioStatus ASprite::PlaySpriteSoundSample (const SpriteSoundSample&    spriteSoundSample,
                                            bool                        playAsynchronously) const
{
    return (Folio::Core::Util::Sound::PlaySoundSample (*spriteSoundSample, playAsynchronously));
} // Endproc.


FolioStatus ASprite::PlaySpriteStationarySoundSamples (const SpriteStationarySoundSamplesList&  stationarySpriteSoundSamplesList,
                                                       UInt32                                   stationarySpriteSoundSamplesListIndex,
                                                       bool                                     playAsynchronously) const
{
    FolioStatus status = ERR_SUCCESS;

    if (stationarySpriteSoundSamplesListIndex < stationarySpriteSoundSamplesList.size ())
    {
        // Are there any sound samples to play?

        switch (stationarySpriteSoundSamplesList [stationarySpriteSoundSamplesListIndex].m_numSpriteSoundSamplesPerFrame)
        {
        case 0:
            // No.

            break;

        case 1:
            // Play the sound sample.

            status = Folio::Core::Util::Sound::PlaySoundSample (stationarySpriteSoundSamplesList [stationarySpriteSoundSamplesListIndex], 
                                                                playAsynchronously);
            break;

        default:
            // Play all the sound samples.

            status = Folio::Core::Util::Sound::PlaySoundSamples (stationarySpriteSoundSamplesList [stationarySpriteSoundSamplesListIndex], 
                                                                 playAsynchronously);
            break;
        } // Endswitch.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::SetCurrentSpriteMovementSoundSample (Direction direction)
{
    FolioStatus status = ERR_NOT_FOUND;

    m_currentSpriteMovementSoundSamplesList.clear ();   // Initialise!
    m_currentMovementSoundSamplesListIndex = FOLIO_INVALID_INDEX;

    // Are there any sprite movement sound samples set?

    if (m_spriteMovementSoundSamplesList.empty ())
    {
        // No.

        status = ERR_SUCCESS;
    } // Endif.

    else
    {
        // Yes. Find the current sprite movement sound sample that relates to the direction.

        for (SpriteMovementSoundSamplesList::const_iterator itr = m_spriteMovementSoundSamplesList.begin ();
             itr != m_spriteMovementSoundSamplesList.end ();
             ++itr)
        {
            if ((itr->m_direction & direction) == direction) 
            {
                if (!itr->m_spriteSoundSamplesList.empty ())
                {
                    // Note the current sprite movement sound samples list.
    
                    m_currentSpriteMovementSoundSamplesList = itr->m_spriteSoundSamplesList;
                    m_currentMovementSoundSamplesListIndex  = 0;

                    status = ERR_SUCCESS;
                } // Endif.

                break;  // Get-outta-here!
            } // Endif.

        } // Endfor.
    
    } // Endelse.

    return (status);
} // Endproc.


void    ASprite::StartActionTickCount (UInt32 actionTickCount)
{
    m_actionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + actionTickCount;
} // Endproc.


bool    ASprite::IsActionTickCountComplete () const
{
    return (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_actionTickCount);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
