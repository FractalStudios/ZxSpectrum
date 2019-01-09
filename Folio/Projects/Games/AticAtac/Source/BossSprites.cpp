// "Home-made" includes.
#include    "StdAfx.h"
#include    "BossSprites.h"
#include    "DrawingElement.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Boss sprite graphic attributes.
typedef Folio::Core::Game::SpriteGraphicsAttributes<BOSS_SPRITE_ID, SPRITE_ID> BossSpriteGraphicAttributes;

// Boss sprite graphic attributes table.
static  const   BossSpriteGraphicAttributes g_bossSpriteGraphicAttributesTable [] =
{
//      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
    {   BOSS_SPRITE_MUMMY,          Folio::Core::Game::ABossSprite::ALL_DIRECTIONS,     {   SPRITE_MUMMY_1, SPRITE_MUMMY_2, SPRITE_MUMMY_3, SPRITE_MUMMY_2,                             },  },    
    {   BOSS_SPRITE_HUNCHBACK,      Folio::Core::Game::ABossSprite::ALL_DIRECTIONS,     {   SPRITE_HUNCHBACK_1, SPRITE_HUNCHBACK_2, SPRITE_HUNCHBACK_3, SPRITE_HUNCHBACK_2,             },  },    
    {   BOSS_SPRITE_DRACULA,        Folio::Core::Game::ABossSprite::ALL_DIRECTIONS,     {   SPRITE_DRACULA_1, SPRITE_DRACULA_2, SPRITE_DRACULA_3, SPRITE_DRACULA_2,                     },  },    
    {   BOSS_SPRITE_FRANKENSTEIN,   Folio::Core::Game::ABossSprite::ALL_DIRECTIONS,     {   SPRITE_FRANKENSTEIN_1, SPRITE_FRANKENSTEIN_2, SPRITE_FRANKENSTEIN_3, SPRITE_FRANKENSTEIN_2, },  },    
    {   BOSS_SPRITE_DEVIL,          Folio::Core::Game::ABossSprite::ALL_DIRECTIONS,     {   SPRITE_DEVIL_1, SPRITE_DEVIL_2, SPRITE_DEVIL_3, SPRITE_DEVIL_2,                             },  },    
};


BossSprite::BossSprite ()
:   m_bossSpriteId(BOSS_SPRITE_UNDEFINED),
    m_bossSpriteFlags(NastySprite::FLAGS_NONE)
{
} // Endproc.


BossSprite::~BossSprite ()
{
} // Endproc.


FolioStatus BossSprite::Create (FolioHandle                             dcHandle,
                                BOSS_SPRITE_ID                          bossSpriteId,
                                const SpriteGraphicsMap                 &spriteGraphicsMap,
                                const PlayerSpritePtr                   &mainPlayer,                            
                                const InformationPanel                  &informationPanel,
                                const Folio::Core::Game::CollisionGrid  &collisionGrid)
{
    // Note the main player.

    m_mainPlayer = mainPlayer;

    // Get the boss sprite's colour.

    ZxSpectrum::COLOUR  bossSpriteColour = GetColour (bossSpriteId);

    // Query the boss sprite's graphics.

    SpriteGraphicAttributesList spriteGraphicAttributesList;

    FolioStatus status = QuerySpriteGraphics<BOSS_SPRITE_ID, BossSpriteGraphicAttributes> (dcHandle,
                                                                                           bossSpriteId,
                                                                                           spriteGraphicsMap,
                                                                                           bossSpriteColour,
                                                                                           sizeof (g_bossSpriteGraphicAttributesTable) / sizeof (BossSpriteGraphicAttributes),
                                                                                           g_bossSpriteGraphicAttributesTable,
                                                                                           spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Create the boss sprite.

        status = Folio::Core::Game::ABossSprite::Create (dcHandle,
                                                         spriteGraphicAttributesList,
                                                         GetInitialScreenXLeft (bossSpriteId, mainPlayer, collisionGrid),
                                                         GetInitialScreenYTop (bossSpriteId, mainPlayer, collisionGrid),
                                                         ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                         ZxSpectrum::MapInkColour (bossSpriteColour),
                                                         GetDirection (informationPanel, collisionGrid));

        if (status == ERROR_SUCCESS)
        {
            // Get the boss sprite's flags.

            UInt32  bossSpriteFlags = GetBossSpriteFlags (bossSpriteId);

            // Set the boss sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, 
                                          spriteGraphicsMap, 
                                          bossSpriteColour,
                                          bossSpriteFlags); 

            if (status == ERROR_SUCCESS)
            {
                // Set the boss sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, 
                                             spriteGraphicsMap, 
                                             bossSpriteColour,
                                             bossSpriteFlags); 

                if (status == ERROR_SUCCESS)
                {
                    // Note the boss sprite's attributes.

                    m_bossSpriteId      = bossSpriteId;
                    m_bossSpriteFlags   = bossSpriteFlags;
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus BossSprite::Reset (const Folio::Core::Game::CollisionGrid   &collisionGrid,
                               bool                                     &removeBossSprite)
{
    FolioStatus status = ERR_SUCCESS;

    removeBossSprite = false;   // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_DRACULA:
        removeBossSprite = true;
        break;
    
    case BOSS_SPRITE_MUMMY:            
    case BOSS_SPRITE_HUNCHBACK:
        break;

    case BOSS_SPRITE_FRANKENSTEIN:
    case BOSS_SPRITE_DEVIL:                
    default:
        // Set the boss sprite's position.

        status = SetScreenTopLeft (GetInitialScreenXLeft (m_bossSpriteId, m_mainPlayer, collisionGrid),
                                   GetInitialScreenYTop (m_bossSpriteId, m_mainPlayer, collisionGrid));
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus BossSprite::Move (Gdiplus::Graphics                 &graphics,
                              const InformationPanel            &informationPanel,
                              Folio::Core::Game::CollisionGrid  &collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the boss sprite's speed.

    UInt32  speed = GetSpeed (informationPanel, collisionGrid);

    // Is the boss sprite moving?

    if (speed == STATIC_SPEED)
    {
        // No. The boss sprite is static.

        SetState (STATE_STATIC);
    } // Endif.

    else
    {
        // Yes. Should the boss sprite's direction be updated?

        if (IsUpdateDirectionRqd (collisionGrid))
        {
            // Yes. Update the boss sprite's direction.

            UpdateDirection (GetDirection (informationPanel, collisionGrid));
        } // Endif.

        // Move the boss sprite.

        status = Folio::Core::Game::ABossSprite::Move (graphics, speed, collisionGrid);
    } // Endelse.

    return (status);
} // Endproc.


BOSS_SPRITE_ID   BossSprite::GetBossSpriteId () const
{
    return (m_bossSpriteId);
} // Endproc.


UInt32  BossSprite::GetBossSpriteFlags () const
{
    return (m_bossSpriteFlags);
} // Endproc.
       

bool    BossSprite::CanBeKilled (const InformationPanel &informationPanel) const
{
    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_FRANKENSTEIN:
        // Frankenstein can be killed by the spanner.

        return (informationPanel.IsSpannerCollected ());

    case BOSS_SPRITE_MUMMY:            
    case BOSS_SPRITE_HUNCHBACK:
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_DEVIL:                
    default:
        return (false);
    } // Endswitch.

} // Endproc.


FolioStatus BossSprite::SetInitialisingMode (FolioHandle                dcHandle,
                                             const SpriteGraphicsMap    &spriteGraphicsMap,
                                             ZxSpectrum::COLOUR         bossSpriteColour,
                                             UInt32                     bossSpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 7;

    FolioStatus status = ERR_SUCCESS;

    // Is the boss sprite initialised by graphic?

    if (NastySprite::IsInitialisedByGraphic (bossSpriteFlags))
    {
        // Yes. Query the boss sprite's initialising graphics.

        status = NastySprite::QueryNastySpriteInitialisingGraphics (dcHandle,
                                                                    spriteGraphicsMap,
                                                                    bossSpriteColour, 
                                                                    m_bossSpriteInitialisingGraphics);

        if (status == ERR_SUCCESS)
        {
            // Set graphic initialising mode.

            status = SetGraphicInitialisingMode (dcHandle,
                                                 m_bossSpriteInitialisingGraphics,
                                                 MAX_SEQUENCE_COUNT);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus BossSprite::SetTerminatingMode (FolioHandle             dcHandle,
                                            const SpriteGraphicsMap &spriteGraphicsMap,
                                            ZxSpectrum::COLOUR      bossSpriteColour,
                                            UInt32                  bossSpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 4;

    FolioStatus status = ERR_SUCCESS;

    // Is the boss sprite terminated by graphic?

    if (NastySprite::IsTerminatedByGraphic (bossSpriteFlags))
    {
        // Yes. Query the boss sprite's terminating graphics.

        status = NastySprite::QueryNastySpriteTerminatingGraphics (dcHandle,
                                                                   spriteGraphicsMap,
                                                                   bossSpriteColour, 
                                                                   m_bossSpriteTerminatingGraphics);
        
        if (status == ERR_SUCCESS)
        {
            // Set graphic terminating mode.

            status = SetGraphicTerminatingMode (dcHandle,
                                                m_bossSpriteTerminatingGraphics,
                                                MAX_SEQUENCE_COUNT);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


bool    BossSprite::IsUpdateDirectionRqd (const Folio::Core::Game::CollisionGrid &collisionGrid) const
{
    bool    isUpdateDirectionRqd = true;    // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
        // Is the main player ready?

        if (m_mainPlayer->IsReady ())
        {
            // Yes. The direction of the mummy is dependent on whether or not a static sprite 
            // it is attracted to is on the screen.
            
            if (IsAnyAttractedStaticSprite (collisionGrid))
            {
                isUpdateDirectionRqd = (Folio::Core::Util::Random::GetRandomNumber (6) == 0);
            } // Endif.

            else
            {
                isUpdateDirectionRqd = true;
            } // Endelse.

        } // Endif.

        else
        {
            isUpdateDirectionRqd = true;
        } // Endelse.
        break;
    
    case BOSS_SPRITE_HUNCHBACK:                
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:                
    default:
        isUpdateDirectionRqd = true;
        break;
    } // Endswitch.

    return (isUpdateDirectionRqd);
} // Endproc.


BossSprite::Direction  BossSprite::GetDirection (const InformationPanel                 &informationPanel,
                                                 const Folio::Core::Game::CollisionGrid &collisionGrid) const
{
    Direction  direction = NO_DIRECTION;    // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
        {
            // The direction of the mummy is dependent on whether or not a static sprite 
            // it is attracted to is on the screen.
            
            bool    staticSpriteFound = false;  // Initialise!

            direction = GetDirectionToAttractedStaticSprite (collisionGrid, staticSpriteFound);

            // Was a static sprite the mummy is attracted to found?

            if (!staticSpriteFound && (direction == NO_DIRECTION))
            {
                // No. Move the munny to the main player if ready. Otherwise move to 
                // the nearest corner of the screen.
                
                direction = m_mainPlayer->IsReady ()
                            ? ASprite::GetDirectionToScreenRect (m_mainPlayer->GetScreenRect (), collisionGrid)
                            : ASprite::GetDirectionToNearestCorner (collisionGrid);
            } // Endif.

        } // Endscope.
        break;            

    case BOSS_SPRITE_HUNCHBACK:
        {
            // The direction of the hunchback is dependent on whether or not a static sprite 
            // it is attracted to is on the screen.
            
            bool    staticSpriteFound = false;  // Initialise!

            direction = GetDirectionToAttractedStaticSprite (collisionGrid, staticSpriteFound);

            // Was a static sprite the hunchback is attracted to found?

            if (!staticSpriteFound && (direction == NO_DIRECTION))
            {
                // No. Move the hunchback to its initial position.

                direction = ASprite::GetDirectionToScreenTopLeft (GetInitialScreenXLeft (m_bossSpriteId, m_mainPlayer, collisionGrid),
                                                                  GetInitialScreenYTop (m_bossSpriteId, m_mainPlayer, collisionGrid),
                                                                  collisionGrid);
            } // Endif.

        } // Endscope.
        break;     

    case BOSS_SPRITE_DRACULA:
        // Move dracula to or from the main player if ready and depending on whether 
        // or not the crucifix is collected. Otherwise move to the nearest corner of 
        // the screen.

        direction = m_mainPlayer->IsReady () 
                    ? ASprite::GetDirectionToScreenRect (m_mainPlayer->GetScreenRect (), collisionGrid, 
                                                         !informationPanel.IsCrucifixCollected ())
                    : ASprite::GetDirectionToNearestCorner (collisionGrid);
        break;            

    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:
        // Move the boss sprite to the main player if ready. Otherwise move to 
        // the nearest corner of the screen.

        direction = m_mainPlayer->IsReady () 
                    ? ASprite::GetDirectionToScreenRect (m_mainPlayer->GetScreenRect (), collisionGrid)
                    : ASprite::GetDirectionToNearestCorner (collisionGrid);
        break;            

    default:
        direction = NO_DIRECTION;
        break;            
    } // Endswitch.

    return (direction);
} // Endproc.


BossSprite::Direction   BossSprite::GetDirectionToAttractedStaticSprite (const Folio::Core::Game::CollisionGrid &collisionGrid,
                                                                         bool                                   &staticSpriteFound) const
{
    staticSpriteFound = false;  // Initialise!

    Direction   direction = NO_DIRECTION;   // Initialise!

    // Find the static sprites in the collision grid.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    if (collisionGrid.FindDrawingElements (DRAWING_ELEMENT_STATIC_SPRITE, drawingElementsList))
    {
        // Are any of the static sprites one that the boss sprite is attracted to?

        bool    previousStaticSpriteFound = false;  // Initialise!

        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             !staticSpriteFound && (itr != drawingElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            const   StaticSprite   &staticSprite(*reinterpret_cast<StaticSprite *> (itr->GetUserData ()));

            // Is the static sprite one that the boss sprite is attracted to?

            if (IsAttractedToStaticSprite (m_bossSpriteId, staticSprite))
            {
                // Yes. Move the boss sprite to the static sprite.

                direction = ASprite::GetDirectionToScreenRect (staticSprite.GetScreenRect (), collisionGrid);

                if ((m_bossSpriteId == BOSS_SPRITE_MUMMY) && (staticSprite.GetStaticSpriteId () == STATIC_SPRITE_KEY))
                {
                    previousStaticSpriteFound = true;
                } // Endif.

                else
                {
                    staticSpriteFound = true;
                } // Endelse.

            } // Endif.

        } // Endfor.

        if (previousStaticSpriteFound)
        {
            staticSpriteFound = true;
        } // Endif.

    } // Endif.

    return (direction);
} // Endproc.


UInt32  BossSprite::GetSpeed (const InformationPanel                    &informationPanel,
                              const Folio::Core::Game::CollisionGrid    &collisionGrid) const
{
    UInt32  speed = STATIC_SPEED;  // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:
        // The speed of the boss sprite is dependent on whether or not it is at the main player.
        
        speed = ASprite::IsAtScreenRect (m_mainPlayer->GetScreenRect ()) ? STATIC_SPEED : BOSS_SPRITE_SPEED;
        break;

    case BOSS_SPRITE_HUNCHBACK:                
        {
            // The speed of the hunchback is dependent on whether or not a static sprite 
            // it is attracted to is on the screen.
            
            bool    staticSpriteFound = false;  // Initialise!

            speed = GetSpeedToAttractedStaticSprite (collisionGrid, staticSpriteFound);

            if (!staticSpriteFound && (speed == STATIC_SPEED))
            {
                speed = ASprite::IsAtScreenTopLeft (GetInitialScreenXLeft (m_bossSpriteId, m_mainPlayer, collisionGrid),
                                                    GetInitialScreenYTop (m_bossSpriteId, m_mainPlayer, collisionGrid)) ? STATIC_SPEED : BOSS_SPRITE_SPEED;

            } // Endif.
        
        } // Endscope.
        break;     

    case BOSS_SPRITE_DRACULA:            
        // The speed of dracula is dependent on whether or not it is at the main 
        // player, and depending on whether or not the crucifix is collected.

        if (informationPanel.IsCrucifixCollected ())
        {
            speed = BOSS_SPRITE_SPEED;
        } // Endif.

        else
        {
            speed = ASprite::IsAtScreenRect (m_mainPlayer->GetScreenRect ()) ? STATIC_SPEED : BOSS_SPRITE_SPEED;
        } // Endelse.
        break;

    default:
        speed = STATIC_SPEED;
        break;
    } // Endswitch.

    return (speed);
} // Endproc.


UInt32  BossSprite::GetSpeedToAttractedStaticSprite (const Folio::Core::Game::CollisionGrid &collisionGrid, 
                                                     bool                                   &staticSpriteFound) const
{
    staticSpriteFound = false;  // Initialise!

    UInt32  speed = STATIC_SPEED;  // Initialise!

    // Find the static sprites in the collision grid.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    if (collisionGrid.FindDrawingElements (DRAWING_ELEMENT_STATIC_SPRITE, drawingElementsList))
    {
        // Are any of the static sprites one that the boss sprite is attracted to?

        bool    previousStaticSpriteFound = false;  // Initialise!

        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             !staticSpriteFound && (itr != drawingElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            const   StaticSprite    &staticSprite(*reinterpret_cast<StaticSprite *> (itr->GetUserData ()));

            // Is the static sprite one that the boss sprite is attracted to?

            if (IsAttractedToStaticSprite (m_bossSpriteId, staticSprite))
            {
                // Yes. The speed of the boss sprite is dependent on whether or not it is at the static sprite.

                speed = ASprite::IsAtScreenRect (staticSprite.GetScreenRect ()) ? STATIC_SPEED : BOSS_SPRITE_SPEED;

                if ((m_bossSpriteId == BOSS_SPRITE_MUMMY) && (staticSprite.GetStaticSpriteId () == STATIC_SPRITE_KEY))
                {
                    previousStaticSpriteFound = true;
                } // Endif.

                else
                {
                    staticSpriteFound = true;
                } // Endelse.

            } // Endif.

        } // Endfor.

        if (previousStaticSpriteFound)
        {
            staticSpriteFound = true;
        } // Endif.

    } // Endif.

    return (speed);
} // Endproc.


bool    BossSprite::IsAnyAttractedStaticSprite (const Folio::Core::Game::CollisionGrid &collisionGrid) const
{
    bool    isAnyAttractedStaticSprite = false; // Initialise!

    // Find the static sprites in the collision grid.

    Folio::Core::Game::DrawingElementsList  drawingElementsList;

    if (collisionGrid.FindDrawingElements (DRAWING_ELEMENT_STATIC_SPRITE, drawingElementsList))
    {
        // Are any of the static sprites one that the boss sprite is attracted to?

        for (Folio::Core::Game::DrawingElementsList::const_iterator itr = drawingElementsList.begin ();
             !isAnyAttractedStaticSprite && (itr != drawingElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            const   StaticSprite    &staticSprite(*reinterpret_cast<StaticSprite *> (itr->GetUserData ()));

            // Is the static sprite one that the boss sprite is attracted to?

            isAnyAttractedStaticSprite = IsAttractedToStaticSprite (m_bossSpriteId, staticSprite);
        } // Endfor.

    } // Endif.

    return (isAnyAttractedStaticSprite);
} // Endproc.


Int32   BossSprite::GetInitialScreenXLeft (BOSS_SPRITE_ID                           bossSpriteId,
                                           const PlayerSpritePtr                    &mainPlayer,
                                           const Folio::Core::Game::CollisionGrid   &collisionGrid)
{
    static  const   Int32   MAX_BOSS_SPRITE_WIDTH = 16;

    Int32   initialScreenXLeft = FOLIO_UNDEFINED;   // Initialise!

    switch (bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:            
        initialScreenXLeft = 104;
        break;

    case BOSS_SPRITE_HUNCHBACK:
        initialScreenXLeft = 88;
        break;

    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:
        {
            // Get the current screen entrance.

            Folio::Core::Game::CollisionGrid::ScreenEntrance    screenEntrance(mainPlayer->GetScreenEntrance ());

            // Calculate the initial screen X left position of the boss sprite.

            switch (screenEntrance.m_orientation)
            {
            case Folio::Core::Game::CollisionGrid::ScreenExit::TOP:
            case Folio::Core::Game::CollisionGrid::ScreenExit::BOTTOM:
                initialScreenXLeft = screenEntrance.m_screenRect.X + (screenEntrance.m_screenRect.Width - MAX_BOSS_SPRITE_WIDTH) / 2;
                break;

            case Folio::Core::Game::CollisionGrid::ScreenExit::LEFT:
                initialScreenXLeft = collisionGrid.GetFloorRightBound () - MAX_BOSS_SPRITE_WIDTH;
                break;
            
            case Folio::Core::Game::CollisionGrid::ScreenExit::RIGHT:
                initialScreenXLeft = collisionGrid.GetFloorLeftBound ();
                break;

            case Folio::Core::Game::CollisionGrid::ScreenExit::FLOOR:
            default:
                initialScreenXLeft = collisionGrid.GetFloorLeftBound () + (collisionGrid.GetFloorWidth () - MAX_BOSS_SPRITE_WIDTH) / 2;
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case BOSS_SPRITE_DRACULA:            
    default:
        initialScreenXLeft = Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorLeftBound () + 8, 
                                                                         collisionGrid.GetFloorRightBound () - MAX_BOSS_SPRITE_WIDTH);
        break;
    } // Endswitch.

    return (initialScreenXLeft);
} // Endproc.


Int32   BossSprite::GetInitialScreenYTop (BOSS_SPRITE_ID                            bossSpriteId,
                                          const PlayerSpritePtr                     &mainPlayer,
                                          const Folio::Core::Game::CollisionGrid    &collisionGrid)
{
    static  const   Int32   MAX_BOSS_SPRITE_HEIGHT = 24;

    Int32   initialScreenYTop = FOLIO_UNDEFINED;   // Initialise!

    switch (bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:            
        initialScreenYTop = 40;
        break;

    case BOSS_SPRITE_HUNCHBACK:
        initialScreenYTop = 32;
        break;

    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:                
        {
            // Get the current screen entrance.

            Folio::Core::Game::CollisionGrid::ScreenEntrance    screenEntrance(mainPlayer->GetScreenEntrance ());

            // Calculate the initial screen Y top position of the boss sprite.

            switch (screenEntrance.m_orientation)
            {
            case Folio::Core::Game::CollisionGrid::ScreenExit::TOP:
                initialScreenYTop = collisionGrid.GetFloorBottomBound () - MAX_BOSS_SPRITE_HEIGHT;
                break;

            case Folio::Core::Game::CollisionGrid::ScreenExit::BOTTOM:
                initialScreenYTop = collisionGrid.GetFloorTopBound ();
                break;

            case Folio::Core::Game::CollisionGrid::ScreenExit::LEFT:
            case Folio::Core::Game::CollisionGrid::ScreenExit::RIGHT:
                initialScreenYTop = screenEntrance.m_screenRect.Y + (screenEntrance.m_screenRect.Height - MAX_BOSS_SPRITE_HEIGHT) / 2;
                break;

            case Folio::Core::Game::CollisionGrid::ScreenExit::FLOOR:
            default:
                initialScreenYTop = collisionGrid.GetFloorTopBound () + (collisionGrid.GetFloorHeight () - MAX_BOSS_SPRITE_HEIGHT) / 2;
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case BOSS_SPRITE_DRACULA:            
    default:
        initialScreenYTop = Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorTopBound () + 8, 
                                                                         collisionGrid.GetFloorBottomBound () - MAX_BOSS_SPRITE_HEIGHT);
        break;
    } // Endswitch.

    return (initialScreenYTop);
} // Endproc.


ZxSpectrum::COLOUR  BossSprite::GetColour (BOSS_SPRITE_ID bossSpriteId)
{
    switch (bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:            
        return (ZxSpectrum::BRIGHT | ZxSpectrum::WHITE);

    case BOSS_SPRITE_DRACULA:            
        return (ZxSpectrum::BRIGHT | ZxSpectrum::GREEN);

    case BOSS_SPRITE_HUNCHBACK:                
    case BOSS_SPRITE_FRANKENSTEIN:            
        return (ZxSpectrum::BRIGHT | ZxSpectrum::RED);
    
    case BOSS_SPRITE_DEVIL:                
        return (ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA);

    default:
        return (ZxSpectrum::UNDEFINED);
    } // Endswitch.

} // Endproc.


UInt32  BossSprite::GetBossSpriteFlags (BOSS_SPRITE_ID bossSpriteId)
{
    switch (bossSpriteId)
    {
    case BOSS_SPRITE_FRANKENSTEIN:
        // Frankenstein can be killed.

        return (NastySprite::FLAGS_TERMINATED_BY_GRAPHIC);

    case BOSS_SPRITE_MUMMY:            
    case BOSS_SPRITE_HUNCHBACK:                
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_DEVIL:                
    default:
        return (NastySprite::FLAGS_NONE);
    } // Endswitch.

} // Endproc.


bool    BossSprite::IsAttractedToStaticSprite (BOSS_SPRITE_ID       bossSpriteId,
                                               const StaticSprite   &staticSprite)
{
    bool    isAttractedToStaticSprite = false;  // Initialise!

    switch (bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
        // The mummy is attracted to the leaf and the red key.

        isAttractedToStaticSprite = ((staticSprite.GetStaticSpriteId () == STATIC_SPRITE_LEAF) || 
                                    ((staticSprite.GetStaticSpriteId () == STATIC_SPRITE_KEY) && (staticSprite.GetStaticSpriteColour () == (ZxSpectrum::BRIGHT | ZxSpectrum::RED))));  
        break;

    case BOSS_SPRITE_HUNCHBACK:                
        // The hunchback is attracted to a number of items.

        switch (staticSprite.GetStaticSpriteId ())
        {
        case STATIC_SPRITE_MEDICINE_BOTTLE:
        case STATIC_SPRITE_BROKEN:
        case STATIC_SPRITE_ROPE:
        case STATIC_SPRITE_ARM:
        case STATIC_SPRITE_MONEY_BAG:
        case STATIC_SPRITE_GOBSTOPPER:
        case STATIC_SPRITE_AMULET:
        case STATIC_SPRITE_SKULL:
            isAttractedToStaticSprite = true;
            break;

        default:
            isAttractedToStaticSprite = false; 
            break;
        } // Endswitch.
        break;
            
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:                
    default:
        isAttractedToStaticSprite = false; 
        break;
    } // Endswitch.

    return (isAttractedToStaticSprite);
} // Endproc.


BOSS_SPRITE_ID  GetScreenBossSpriteId (UInt32   screenNumber, 
                                       UInt32   totalNumRooms)
{
    switch (screenNumber)
    {
    case 86: 
        return (BOSS_SPRITE_HUNCHBACK);

    case 85: 
        return (BOSS_SPRITE_FRANKENSTEIN);

    case 67: 
        return (BOSS_SPRITE_DEVIL);

    default:
        if (IsRedKeyLocation (screenNumber))
        {
            return (BOSS_SPRITE_MUMMY);
        } // Endif.

        else
        {
            return ((Folio::Core::Util::Random::GetRandomNumber (totalNumRooms) == 0) ? BOSS_SPRITE_DRACULA : BOSS_SPRITE_UNDEFINED);
        } // Endelse.

    } // Endswitch.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
