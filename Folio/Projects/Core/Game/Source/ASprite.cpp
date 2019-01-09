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
    m_spriteWidth(FOLIO_UNDEFINED),
    m_spriteHeight(FOLIO_UNDEFINED),
    m_direction(NO_DIRECTION),
    m_spriteInkColour(Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR),
    m_maxNumAutoMoves(0),
    m_remainingNumAutoMoves(0),
    m_initialisingDrawingMode(DM_NONE),
    m_terminatingDrawingMode(DM_NONE),
    m_drawingElementId(DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED),
    m_collisionGridCellValue(CollisionGrid::CELL_VALUE_EMPTY),
    m_initialisingMaxSequenceCount(0),
    m_initialisingCurrentSequenceCount(0),
    m_terminatingMaxSequenceCount(0),
    m_terminatingCurrentSequenceCount(0),
    m_isAtLockedScreenExit(false),
    m_isInScreenExit(false),
    m_isExitedScreen(false),
    m_isEnteringScreen(false),
    m_currentSpriteDrawingAttributes(0)
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
                             UInt32                             maxNumAutoMoves,
                             UInt32                             initialSpriteBitmapIndex)
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
        // No. Create the sprite's drawing attributes.

        status = CreateSpriteDrawingAttributes (dcHandle, 
                                                spriteGraphicAttributesList,
                                                initialScreenXLeft,
                                                initialScreenYTop,
                                                screenScale,
                                                initialDirection,
                                                initialSpriteBitmapIndex);

        if (status == ERR_SUCCESS)
        {
            // We're good to go.

            m_state = STATE_CREATED;

            // Note the sprite attributes.

            m_spriteInkColour       = spriteInkColour;
            m_maxNumAutoMoves       = maxNumAutoMoves;
            m_remainingNumAutoMoves = maxNumAutoMoves;
            
            m_spriteWidth  = m_currentSpriteDrawingAttributes->m_spriteDrawingBitmaps [0]->GetBitmapWidth ();
            m_spriteHeight = m_currentSpriteDrawingAttributes->m_spriteDrawingBitmaps [0]->GetBitmapHeight ();

            // Set the sprite's top-left screen position.

            SetScreenTopLeft (initialScreenXLeft, initialScreenYTop);

            // Scale the sprite.

            SetScreenScale (screenScale);

            // Set the sprite's direction.

            m_direction = initialDirection;

            // Create the sprite's underlying background.

            status = m_underlyingBackground.Create (dcHandle, m_scaledRect);
        } // Endif.

    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::ChangeSpriteInkColour (Gdiplus::ARGB spriteInkColour)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. Has the sprite's colour changed?

        if (spriteInkColour != m_spriteInkColour)
        {
            // Yes. Change the colour of the sprite's graphics.

            for (SpriteDrawingAttributesList::iterator spriteDrawingAttributesItr = m_spriteDrawingAttributesList.begin ();
                 spriteDrawingAttributesItr != m_spriteDrawingAttributesList.end ();
                 ++spriteDrawingAttributesItr)
            {
                for (SpriteDrawingBitmapsList::iterator spriteDrawingBitmapsItr = spriteDrawingAttributesItr->m_spriteDrawingBitmaps.begin ();
                     spriteDrawingBitmapsItr != spriteDrawingAttributesItr->m_spriteDrawingBitmaps.end ();
                     ++spriteDrawingBitmapsItr)
                {
                    // Change the colour of the sprites graphic.

                    status = spriteDrawingBitmapsItr->get ()->ChangeColour (m_spriteInkColour, spriteInkColour);
                } // Endfor.

            } // Endfor.

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

        UpdateSpriteDrawingAttributes (S);
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


CollisionGrid::CellValue    ASprite::GetCollisionGridCellValue () const
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


void    ASprite::SetAlive ()
{
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


void    ASprite::SetDead ()
{
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


FolioStatus ASprite::SetGraphicInitialisingMode (FolioHandle                dcHandle,
                                                 const SpriteGraphicsList&  initialisingSpriteGraphics,
                                                 UInt32                     initialisingMaxSequenceCount)
{
    FolioStatus status = ERR_SUCCESS;

    // Only set the initialising mode if the current state is created or initialise required.

    switch (m_state)
    {
    case STATE_CREATED:
    case STATE_INITIALISE_RQD:
        // Create the sprite's drawing attributes.

        status = CreateSpriteDrawingAttributes (dcHandle, 
                                                initialisingSpriteGraphics, 
                                                m_initialisingSpriteDrawingAttributes);

        if (status == ERR_SUCCESS)
        {
            // Note the sprite's initialising attributes.

            m_initialisingDrawingMode           = DM_GRAPHIC;
            m_initialisingMaxSequenceCount      = initialisingMaxSequenceCount * m_initialisingSpriteDrawingAttributes.m_maxNumSpriteBitmaps;
            m_initialisingCurrentSequenceCount  = 0;
        } // Endif.
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::SetGraphicTerminatingMode (FolioHandle                 dcHandle,
                                                const SpriteGraphicsList&   terminatingSpriteGraphics,
                                                UInt32                      terminatingMaxSequenceCount)
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
        // Create the sprite's terminating drawing attributes.

        status = CreateSpriteDrawingAttributes (dcHandle, 
                                                terminatingSpriteGraphics, 
                                                m_terminatingSpriteDrawingAttributes);

        if (status == ERR_SUCCESS)
        {
            // Note the sprite's terminating attributes.

            m_terminatingDrawingMode            = DM_GRAPHIC;
            m_terminatingMaxSequenceCount       = terminatingMaxSequenceCount * m_terminatingSpriteDrawingAttributes.m_maxNumSpriteBitmaps;
            m_terminatingCurrentSequenceCount   = 0;
        } // Endif.
        break;

    default:
        status = ERR_INVALID_SEQUENCE;
        break;
    } // Endswitch.

    return (status);
} // Endproc.


ASprite::Direction  ASprite::UpdateDirection (Direction direction)
{
    Direction   orgDirection = m_direction; // Note original direction.

    // New direction.

    m_direction = direction;

    // Has the character sprite's direction changed?

    if (orgDirection != m_direction)
    {
        // Yes. Update the current sprite drawing attributes.

        UpdateSpriteDrawingAttributes (m_direction);
    } // Endif.

    return (m_direction);
} // Endproc.


void    ASprite::SetDirection (Direction direction)
{
    m_direction = direction;
} // Endproc.


ASprite::Direction  ASprite::GetDirection () const
{
    return (m_direction);
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


void    ASprite::SetScreenEntrance (CollisionGrid::ScreenEntrance& screenEntrance) 
{
    // Only set the screen entrance attributes if the sprite is entering the screen.

    if (m_isEnteringScreen)
    {
        m_screenExit = screenEntrance;

        switch (screenEntrance.m_orientation)
        {
        case CollisionGrid::ScreenEntrance::TOP:
        case CollisionGrid::ScreenEntrance::FLOOR:
            m_direction = UpdateDirection (S);
            break;

        case CollisionGrid::ScreenEntrance::BOTTOM:
            m_direction = UpdateDirection (N);
            break;
        
        case CollisionGrid::ScreenEntrance::LEFT:
            m_direction = UpdateDirection (E);
            break;
        
        case CollisionGrid::ScreenEntrance::RIGHT:
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


CollisionGrid::ScreenExit   ASprite::GetScreenExit () const
{
    return (m_screenExit);
} // Endproc.


CollisionGrid::ScreenEntrance   ASprite::GetScreenEntrance () const
{
    return (m_screenExit);
} // Endproc.


ASprite::Direction  ASprite::GetDirectionToScreenTopLeft (Int32                 initialScreenXLeft,
                                                          Int32                 initialScreenYTop,
                                                          const CollisionGrid&  collisionGrid,
                                                          bool                  toScreenTopLeft) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    if (toScreenTopLeft)
    {
        direction  = (m_screenRect.X <= initialScreenXLeft) ? E : W;
        direction |= (m_screenRect.Y <= initialScreenYTop) ? S : N;
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
    return ((m_screenRect.X == initialScreenXLeft) &&
            (m_screenRect.Y == initialScreenYTop));
} // Endproc.


ASprite::Direction  ASprite::GetDirectionToScreenRect (const Gdiplus::Rect& screenRect,
                                                       const CollisionGrid& collisionGrid,
                                                       bool                 toScreenRect) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    if (toScreenRect)
    {
        direction  = (m_screenRect.X <= screenRect.X) ? E : W;
        direction |= ((m_screenRect.Y + m_screenRect.Height - 1) <= (screenRect.Y + screenRect.Height - 1)) ? S : N;
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
    return ((m_screenRect.X == screenRect.X) &&
           ((m_screenRect.Y + m_screenRect.Height) == (screenRect.Y + screenRect.Height)));
} // Endproc.


ASprite::Direction  ASprite::GetDirectionToNearestCorner (const Folio::Core::Game::CollisionGrid &collisionGrid) const
{
    Direction   direction = ((m_screenRect.X + m_screenRect.Width / 2) <= (collisionGrid.GetFloorLeftBound () + collisionGrid.GetFloorWidth () / 2)) ? W : E;
    direction |= ((m_screenRect.Y + m_screenRect.Height / 2) <= (collisionGrid.GetFloorTopBound () + collisionGrid.GetFloorHeight () / 2)) ? N : S;

    return (direction);
} // Endproc.


ASprite::Direction  ASprite::GetFloorBoundDirection (CollisionGrid::DIRECTION collisionGridDirection) const
{
    Direction   direction = m_direction;    // Note the sprite's current direction.

    switch (collisionGridDirection)
    {
    case CollisionGrid::UP:
        direction &= ~N;
        direction |= S;
        break;

    case CollisionGrid::DOWN:
        direction &= ~S;
        direction |= N;
        break;

    case CollisionGrid::LEFT:
        direction &= ~W;
        direction |= E;
        break;

    case CollisionGrid::RIGHT:
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
            // Get the sprite drawing bitmap.

            const SpriteDrawingBitmap& spriteDrawingBitmap(m_initialisingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex]);

            // Set the sprite's top-left position.

            m_screenRect.X += (m_spriteWidth - spriteDrawingBitmap->GetBitmapWidth ()) / 2;
            m_screenRect.Y += (m_spriteHeight - spriteDrawingBitmap->GetBitmapHeight ()) / 2;

            SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
        } // Endif.

        // Buffer the underlying background.
    
        status = m_underlyingBackground.Buffer (graphics, m_scaledRect);
        break;

    case STATE_TERMINATE_RQD:
        if (m_terminatingDrawingMode == DM_GRAPHIC)
        {
            // Get the sprite drawing bitmap.

            const SpriteDrawingBitmap& spriteDrawingBitmap(m_terminatingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex]);

            // Set the sprite's top-left position.

            m_screenRect.X += (m_spriteWidth - spriteDrawingBitmap->GetBitmapWidth ()) / 2;
            m_screenRect.Y += (m_spriteHeight - spriteDrawingBitmap->GetBitmapHeight ()) / 2;

            SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
        } // Endif.

        // Buffer the underlying background.
    
        status = m_underlyingBackground.Buffer (graphics, m_scaledRect);
        break;

    case STATE_INITIALISING:
    case STATE_INITIALISED:
    case STATE_TERMINATING:
    case STATE_TERMINATED:
    case STATE_STATIC:
    case STATE_MOVING:
        // Buffer the underlying background.
    
        status = m_underlyingBackground.Buffer (graphics, rect ? *rect : m_scaledRect);
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

        status = m_underlyingBackground.Draw (graphics, rects);
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus ASprite::Move (Gdiplus::Graphics&   graphics,
                           UInt32               speed, 
                           const CollisionGrid& collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. The sprite is moving.
        
        m_state = STATE_MOVING; 
        
        // Let our sub-class handle it.

        status = HandleMoveSprite (graphics, speed, collisionGrid);
    } // Endif.

    else
    {
        // No.

        status = ERR_INVALID_SEQUENCE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ASprite::Static (Gdiplus::Graphics&     graphics,
                             const CollisionGrid&   collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Have we created a sprite?

    if (IsCreated ())
    {
        // Yes. The sprite is static.
        
        m_state = STATE_STATIC; 
        
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


FolioStatus ASprite::SetScreenTopLeft (Int32    screenXLeft,
                                       Int32    screenYTop)
{
    // Set the screen rect.

    SetScreenRect (Gdiplus::Rect(screenXLeft, 
                                 screenYTop,
                                 GetSpriteWidth (),
                                 GetSpriteHeight ()));

    return (ERR_SUCCESS);
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
    case STATE_INITIALISING:
        status = InitialiseSprite (graphics, rects);
        break;

    case STATE_TERMINATE_RQD:
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


FolioStatus ASprite::HandleMoveSprite (Gdiplus::Graphics&   graphics,
                                       UInt32               speed, 
                                       const CollisionGrid& collisionGrid)
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
                                         const CollisionGrid&   collisionGrid)
{
    return (ERR_SUCCESS);
} // Endproc.


FolioStatus ASprite::SetInitialSpriteBitmaps (Direction initialDirection,
                                              UInt32    initialSpriteBitmapIndex)
{
    FolioStatus status = ERR_NOT_FOUND;

    // Find the sprite bitmaps that relate to the initial sprite bitmap index and direction.

    for (SpriteDrawingAttributesList::iterator itr = m_spriteDrawingAttributesList.begin ();
         itr != m_spriteDrawingAttributesList.end ();
         ++itr)
    {
        if ((itr->m_direction & initialDirection) == initialDirection)
        {
            if (initialSpriteBitmapIndex < itr->m_maxNumSpriteBitmaps)
            {
                itr->m_currentSpriteBitmapIndex = initialSpriteBitmapIndex;
            } // Endif.

            m_currentSpriteDrawingAttributes = &(*itr);

            status = ERR_SUCCESS;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus ASprite::QueryCurrentSpriteBitmaps (SpriteDrawingBitmap&    spriteDrawingBitmap,
                                                SpriteDrawingBitmap&    spriteMaskedDrawingBitmap)
{
    FolioStatus status = ERR_NOT_FOUND;

    if (m_currentSpriteDrawingAttributes)
    {
        if (m_currentSpriteDrawingAttributes->m_currentSpriteBitmapIndex >= m_currentSpriteDrawingAttributes->m_maxNumSpriteBitmaps)
        {
            m_currentSpriteDrawingAttributes->m_currentSpriteBitmapIndex = 0;
        } // Endif.

        spriteDrawingBitmap         = m_currentSpriteDrawingAttributes->m_spriteDrawingBitmaps [m_currentSpriteDrawingAttributes->m_currentSpriteBitmapIndex];
        spriteMaskedDrawingBitmap   = m_currentSpriteDrawingAttributes->m_spriteMaskedDrawingBitmaps [m_currentSpriteDrawingAttributes->m_currentSpriteBitmapIndex];

        switch (m_state)
        {
        case STATE_INITIALISED: 
        case STATE_TERMINATED: 
        case STATE_MOVING:
            m_currentSpriteDrawingAttributes->m_currentSpriteBitmapIndex++; // Next.
            break;

        default:
            break;
        } // Endswitch.

        status = ERR_SUCCESS;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::UpdateSpriteDrawingAttributes (Direction direction)
{
    FolioStatus status = ERR_NOT_FOUND;

    // Find the sprite's drawing attributes that relate to the direction.

    for (SpriteDrawingAttributesList::iterator itr = m_spriteDrawingAttributesList.begin ();
         itr != m_spriteDrawingAttributesList.end ();
         ++itr)
    {
        if ((itr->m_direction & direction) == direction)
        {
            m_currentSpriteDrawingAttributes = &(*itr);

            status = ERR_SUCCESS;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    return (status);
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
        // Set the sprite's masked drawing bitmap top-left screen position.

        status = spriteMaskedDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's masked drawing bitmap.

            status = spriteMaskedDrawingBitmap->Draw (graphics);

            if (status == ERR_SUCCESS)
            {
                // Set the sprite's drawing bitmap top-left screen position.

                status = spriteDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

                if (status == ERR_SUCCESS)
                {
                    // Draw the sprite's drawing bitmap.

                    status = spriteDrawingBitmap->Draw (graphics, rects);
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingAttributes (FolioHandle                 dcHandle,
                                                    const SpriteGraphicsList&   spriteGraphics,
                                                    SpriteDrawingAttributes&    spriteDrawingAttributes)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the sprite's graphics.

    for (SpriteGraphicsList::const_iterator spriteGraphicsItr = spriteGraphics.begin ();
        (status == ERR_SUCCESS) && (spriteGraphicsItr != spriteGraphics.end ());
        ++spriteGraphicsItr)
    {
        // Create a sprite drawing bitmap from the sprite graphic GDI device-independent bitmap.

        SpriteDrawingBitmap spriteDrawingBitmap(new SpriteDrawingBitmap::element_type);

        status = spriteDrawingBitmap->Create (dcHandle, *(spriteGraphicsItr->get ()->GetGdiDiBitmap ()));

        if (status == ERR_SUCCESS)
        {
            // Create a sprite masked drawing bitmap from the sprite drawing bitmap.

            SpriteDrawingBitmap spriteMaskedDrawingBitmap;

            status = ResourceGraphic::CreateMaskedBitmapDrawingElement (dcHandle,
                                                                        spriteDrawingBitmap,
                                                                        spriteGraphicsItr->get ()->GetMaskColour (),
                                                                        m_screenRect.X,
                                                                        m_screenRect.Y,
                                                                        m_screenScale, 
                                                                        ResourceGraphic::NO_DRAWING_FLAGS,
                                                                        spriteMaskedDrawingBitmap);

            if (status == ERR_SUCCESS)
            {
                // Set the sprite's drawing bitmap drawing mode.

                spriteDrawingBitmap->SetDrawingMode (SRCPAINT);

                // Scale the sprite's drawing bitmap.

                spriteDrawingBitmap->SetScreenScale (m_screenScale);

                // Add to the sprite's drawing attributes.

                spriteDrawingAttributes.m_spriteDrawingBitmaps.push_back (spriteDrawingBitmap);
                spriteDrawingAttributes.m_spriteMaskedDrawingBitmaps.push_back (spriteMaskedDrawingBitmap);
            } // Endif.

        } // Endif.

    } // Endfor.

    // Note the maximum number of sprite drawing bitmaps.

    spriteDrawingAttributes.m_maxNumSpriteBitmaps = spriteDrawingAttributes.m_spriteDrawingBitmaps.size ();

    return (status);
} // Endproc.


FolioStatus ASprite::CreateSpriteDrawingAttributes (FolioHandle                         dcHandle,
                                                    const SpriteGraphicAttributesList&  spriteGraphicAttributesList,
                                                    Int32                               initialScreenXLeft,
                                                    Int32                               initialScreenYTop,
                                                    UInt32                              screenScale,
                                                    Direction                           initialDirection,
                                                    UInt32                              initialSpriteBitmapIndex)
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

                status = ResourceGraphic::CreateMaskedBitmapDrawingElement (dcHandle,
                                                                            spriteDrawingBitmap,
                                                                            spriteGraphic.GetMaskColour (),
                                                                            initialScreenXLeft, 
                                                                            initialScreenYTop,
                                                                            screenScale, 
                                                                            ResourceGraphic::NO_DRAWING_FLAGS,
                                                                            spriteMaskedDrawingBitmap);

                if (status == ERR_SUCCESS)
                {
                    // Set the sprite's drawing bitmap drawing mode.

                    spriteDrawingBitmap->SetDrawingMode (SRCPAINT);

                    // Scale the sprite's drawing bitmap.

                    spriteDrawingBitmap->SetScreenScale (screenScale);

                    // Add to the sprite's drawing attributes.

                    AddSpriteDrawingAttributes (spriteGraphicAttributesItr->m_direction, 
                                                spriteDrawingBitmap,
                                                spriteMaskedDrawingBitmap);

                    if (m_drawingElementId == DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED)
                    {
                        m_drawingElementId          = spriteGraphic.GetDrawingElementId ();
                        m_collisionGridCellValue    = spriteGraphic.GetCollisionGridCellValue ();
                    } // Endif.

                } // Endif.

            } // Endif.

        } // Endfor.

    } // Endfor.

    if ((status == ERR_SUCCESS) && !m_spriteDrawingAttributesList.empty ())
    {
        // Set the initial sprite bitmap.

        status = SetInitialSpriteBitmaps (initialDirection, initialSpriteBitmapIndex);
    } // Endif.

    return (status);
} // Endproc.


void    ASprite::AddSpriteDrawingAttributes (Direction                  direction,
                                             const SpriteDrawingBitmap& spriteDrawingBitmap,
                                             const SpriteDrawingBitmap& spriteMaskedDrawingBitmap)
{
    bool    found = false;  // Initialise!

    // Find the sprite's drawing attributes for the specified direction.

    for (SpriteDrawingAttributesList::iterator itr = m_spriteDrawingAttributesList.begin ();
         itr != m_spriteDrawingAttributesList.end ();
         ++itr)
    {
        if ((itr->m_direction & direction) == direction)
        {
            // Store the sprite drawing bitmaps.

            itr->m_spriteDrawingBitmaps.push_back (spriteDrawingBitmap);
            itr->m_spriteMaskedDrawingBitmaps.push_back (spriteMaskedDrawingBitmap);
            
            itr->m_maxNumSpriteBitmaps++;

            found = true;

            break;  // Get-outta-here!
        } // Endif.

    } // Endfor.

    // If we didn't find the sprite's drawing attributes for the specified 
    // direction, then add a new one.
 
    if (!found)
    {
        m_spriteDrawingAttributesList.push_back (SpriteDrawingAttributes(direction, 
                                                                         spriteDrawingBitmap, 
                                                                         spriteMaskedDrawingBitmap));
    } // Endif.

} // Endproc.


FolioStatus ASprite::PerformGraphicInitialising (Gdiplus::Graphics& graphics,
                                                 RectList*          rects)
{
    // Get the sprite's initialising drawing bitmaps.

    SpriteDrawingBitmap spriteDrawingBitmap         = m_initialisingSpriteDrawingAttributes.m_spriteDrawingBitmaps [m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex];
    SpriteDrawingBitmap spriteMaskedDrawingBitmap   = m_initialisingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex];

    m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex++; // Next.

    if (m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex >= m_initialisingSpriteDrawingAttributes.m_maxNumSpriteBitmaps)
    {
        m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex = 0;
    } // Endif.

    // Set the sprite's masked drawing bitmap top-left screen position.

    FolioStatus status = spriteMaskedDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

    if (status == ERR_SUCCESS)
    {
        // Set the sprite's drawing bitmap top-left screen position.

        status = spriteDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's masked drawing bitmap.

            status = spriteMaskedDrawingBitmap->Draw (graphics);

            if (status == ERR_SUCCESS)
            {
                // Draw the sprite's drawing bitmap.

                status = spriteDrawingBitmap->Draw (graphics, rects);
                            
                if (status == ERR_SUCCESS)
                {
                    // We are initialising until the maximum sequence count is reached.

                    m_state = (++m_initialisingCurrentSequenceCount < m_initialisingMaxSequenceCount)
                              ? STATE_INITIALISING 
                              : STATE_INITIALISED;

                    if (m_state == STATE_INITIALISED)
                    {
                        m_initialisingCurrentSequenceCount = 0; // Reset.

                        // Set the sprite top-left position.

                        m_screenRect.X += (spriteDrawingBitmap->GetBitmapWidth () - m_spriteWidth) / 2;
                        m_screenRect.Y += (spriteDrawingBitmap->GetBitmapHeight () - m_spriteHeight) / 2;

                        SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
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
    // Get the sprite's terminating drawing bitmaps.

    SpriteDrawingBitmap spriteDrawingBitmap         = m_terminatingSpriteDrawingAttributes.m_spriteDrawingBitmaps [m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex];
    SpriteDrawingBitmap spriteMaskedDrawingBitmap   = m_terminatingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex];

    m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex++; // Next.

    if (m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex >= m_terminatingSpriteDrawingAttributes.m_maxNumSpriteBitmaps)
    {
        m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex = 0;
    } // Endif.

    // Set the sprite's masked drawing bitmap top-left screen position.
    
    FolioStatus status = spriteMaskedDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

    if (status == ERR_SUCCESS)
    {
        // Set the sprite's drawing bitmap top-left screen position.

        status = spriteDrawingBitmap->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

        if (status == ERR_SUCCESS)
        {
            // Draw the sprite's masked drawing bitmap.

            status = spriteMaskedDrawingBitmap->Draw (graphics);

            if (status == ERR_SUCCESS)
            {
                // Draw the sprite's drawing bitmap.

                status = spriteDrawingBitmap->Draw (graphics, rects);
                            
                if (status == ERR_SUCCESS)
                {
                    // We are terminating until the maximum sequence count is reached.

                    m_state = (++m_terminatingCurrentSequenceCount < m_terminatingMaxSequenceCount)
                              ? STATE_TERMINATING 
                              : STATE_TERMINATED;

                    if (m_state == STATE_TERMINATED)
                    {
                        m_terminatingCurrentSequenceCount = 0;  // Reset.

                        // Set the sprite top-left position.

                        m_screenRect.X += (spriteDrawingBitmap->GetBitmapWidth () - m_spriteWidth) / 2;
                        m_screenRect.Y += (spriteDrawingBitmap->GetBitmapHeight () - m_spriteHeight) / 2;

                        SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
                    } // Endif.

                } // Endif.

            } // Endif.
    
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


Int32   ASprite::GetSpriteWidth () const
{
    switch (m_state)
    {
    case STATE_INITIALISE_RQD:
    case STATE_INITIALISING:
        if (m_initialisingDrawingMode == DM_GRAPHIC)
        {
            return (m_initialisingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex]->GetBitmapWidth ());
        } // Endif.
        break;

    case STATE_TERMINATE_RQD:
    case STATE_TERMINATING:
    case STATE_TERMINATED:
        if (m_terminatingDrawingMode == DM_GRAPHIC)
        {
            return (m_terminatingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex]->GetBitmapWidth ());
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (m_spriteWidth);
} // Endproc.


Int32   ASprite::GetSpriteHeight () const
{
    switch (m_state)
    {
    case STATE_INITIALISE_RQD:
    case STATE_INITIALISING:
        if (m_initialisingDrawingMode == DM_GRAPHIC)
        {
            return (m_initialisingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_initialisingSpriteDrawingAttributes.m_currentSpriteBitmapIndex]->GetBitmapHeight ());
        } // Endif.
        break;

    case STATE_TERMINATE_RQD:
    case STATE_TERMINATING:
    case STATE_TERMINATED:
        if (m_terminatingDrawingMode == DM_GRAPHIC)
        {
            return (m_terminatingSpriteDrawingAttributes.m_spriteMaskedDrawingBitmaps [m_terminatingSpriteDrawingAttributes.m_currentSpriteBitmapIndex]->GetBitmapHeight ());
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (m_spriteHeight);
} // Endproc.


void    ASprite::CalculateScreenRect (UInt32                speed,
                                      const CollisionGrid&  collisionGrid)
{
    // Calculate the sprite's screen rect based on its direction.

    switch (m_direction)
    {
    case N:
        MoveUp (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case S:
        MoveDown (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case E:
        MoveRight (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case W:
        MoveLeft (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case NE:
        MoveUp (speed, collisionGrid, m_direction, m_screenRect);
        MoveRight (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case NW:
        MoveUp (speed, collisionGrid, m_direction, m_screenRect);
        MoveLeft (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case SE:
        MoveDown (speed, collisionGrid, m_direction, m_screenRect);
        MoveRight (speed, collisionGrid, m_direction, m_screenRect);
        break;

    case SW:
        MoveDown (speed, collisionGrid, m_direction, m_screenRect);
        MoveLeft (speed, collisionGrid, m_direction, m_screenRect);
        break;

    default:
        break;
    } // Endswitch.

    // Set the sprite's top-left screen position.

    SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);
} // Endproc.


void    ASprite::MoveUp (UInt32                 speed,
                         const CollisionGrid&   collisionGrid,
                         Direction&             direction,
                         Gdiplus::Rect&         spriteScreenRect)
{
    spriteScreenRect.Y -= speed;    // Move up.

    // Check floor bounds.

    CheckFloorBound (collisionGrid,
                     CollisionGrid::UP,
                     direction,
                     spriteScreenRect);
} // Endproc.


void    ASprite::MoveDown (UInt32               speed,
                           const CollisionGrid& collisionGrid,
                           Direction&           direction,
                           Gdiplus::Rect&       spriteScreenRect)
{
    spriteScreenRect.Y += speed;    // Move down.

    // Check floor bounds.

    CheckFloorBound (collisionGrid,
                     CollisionGrid::DOWN,
                     direction,
                     spriteScreenRect);
} // Endproc.


void    ASprite::MoveLeft (UInt32               speed,
                           const CollisionGrid& collisionGrid,
                           Direction&           direction,
                           Gdiplus::Rect&       spriteScreenRect)
{
    spriteScreenRect.X -= speed;    // Move left.
    
    // Check floor bounds.

    CheckFloorBound (collisionGrid,
                     CollisionGrid::LEFT,
                     direction,
                     spriteScreenRect);
} // Endproc.


void    ASprite::MoveRight (UInt32                  speed,
                            const CollisionGrid&    collisionGrid,
                            Direction&              direction,
                            Gdiplus::Rect&          spriteScreenRect)
{
    spriteScreenRect.X += speed;    // Move right.

    // Check floor bounds.

    CheckFloorBound (collisionGrid,
                     CollisionGrid::RIGHT,
                     direction,
                     spriteScreenRect);
} // Endproc.


void    ASprite::CheckFloorBound (const CollisionGrid&      collisionGrid,
                                  CollisionGrid::DIRECTION  collisionGridDirection,
                                  Direction&                direction,
                                  Gdiplus::Rect&            spriteScreenRect)
{
    // Is the sprite outwith the floor bound?

    if (collisionGrid.IsOutwithFloorBound (collisionGridDirection, spriteScreenRect))
    {
        // Yes. Update the sprite's direction.

        direction = UpdateDirection (GetFloorBoundDirection (collisionGridDirection));
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
