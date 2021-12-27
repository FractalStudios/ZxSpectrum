// "Home-made" includes.
#include    "StdAfx.h"
#include    "BossSprite.h"
#include    "Globals.h"
#include    "SpriteGraphics.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Boss sprite attributes.
struct BossSpriteAttributes
{
    BOSS_SPRITE_ID                          m_bossSpriteId;         // The identifier of the boss sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_bossSpriteColour;     // The colour of the boss sprite.
    UInt32                                  m_bossSpriteFlags;      // The flags of the boss sprite.
}; // Endstruct.

// Boss sprite attributes table.
static  const   BossSpriteAttributes  g_bossSpriteAttributesTable [] =
{
//      m_bossSpriteId              m_bossSpriteColour                                                              m_bossSpriteFlags
    {   BOSS_SPRITE_MUMMY,          Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   BossSprite::FLAGS_NONE,                     },
    {   BOSS_SPRITE_HUNCHBACK,      Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     BossSprite::FLAGS_NONE,                     },
    {   BOSS_SPRITE_DRACULA,        Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   BossSprite::FLAGS_NONE,                     },
    {   BOSS_SPRITE_FRANKENSTEIN,   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     BossSprite::FLAGS_TERMINATED_BY_GRAPHIC,    },
    {   BOSS_SPRITE_DEVIL,          Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, BossSprite::FLAGS_NONE,                     },
};


// Boss sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<BOSS_SPRITE_ID, SPRITE_ID>  g_bossSpriteGraphicCharacteristics =
{
//      m_spriteId                  m_direction                         m_spriteGraphicIdsList
    {   BOSS_SPRITE_MUMMY,          Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_MUMMY_1, SPRITE_MUMMY_2, SPRITE_MUMMY_3, SPRITE_MUMMY_2,                             },  },    
    {   BOSS_SPRITE_HUNCHBACK,      Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_HUNCHBACK_1, SPRITE_HUNCHBACK_2, SPRITE_HUNCHBACK_3, SPRITE_HUNCHBACK_2,             },  },    
    {   BOSS_SPRITE_DRACULA,        Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_DRACULA_1, SPRITE_DRACULA_2, SPRITE_DRACULA_3, SPRITE_DRACULA_2,                     },  },    
    {   BOSS_SPRITE_FRANKENSTEIN,   Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_FRANKENSTEIN_1, SPRITE_FRANKENSTEIN_2, SPRITE_FRANKENSTEIN_3, SPRITE_FRANKENSTEIN_2, },  },    
    {   BOSS_SPRITE_DEVIL,          Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_DEVIL_1, SPRITE_DEVIL_2, SPRITE_DEVIL_3, SPRITE_DEVIL_2,                             },  },    
};


// Boss sprite static members.
Folio::Core::Util::Sound::SoundSample   BossSprite::m_bossSpriteTerminatedSoundSample;  // The boss sprite terminated sound sample.

BossSprite::BossSprite ()
:   m_bossSpriteId(BOSS_SPRITE_UNDEFINED),
    m_bossSpriteFlags(FLAGS_NONE)
{
} // Endproc.


BossSprite::~BossSprite ()
{
} // Endproc.


FolioStatus BossSprite::Create (FolioHandle                             dcHandle,
                                BOSS_SPRITE_ID                          bossSpriteId,
                                Folio::Core::Game::ZxSpectrum::COLOUR   bossSpriteColour,
                                UInt32                                  bossSpriteFlags)
{
    // Query the boss sprite's graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<BOSS_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                     g_resourceGraphicsCache,
                                                                                                     Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_BOSS_SPRITE,
                                                                                                     Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE,
                                                                                                     bossSpriteId,
                                                                                                     bossSpriteColour,
                                                                                                     g_bossSpriteGraphicCharacteristics,
                                                                                                     spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Create the boss sprite.

        status = Folio::Core::Game::ABossSprite::Create (dcHandle,
                                                         spriteGraphicAttributesList,
                                                         Folio::Core::Game::ZxSpectrum::UNDEFINED,
                                                         Folio::Core::Game::ZxSpectrum::UNDEFINED,
                                                         Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                         Folio::Core::Game::ZxSpectrum::MapInkColour (bossSpriteColour),
                                                         Folio::Core::Game::E,
                                                         &(g_resourceGraphicsCache));

        if (status == ERR_SUCCESS)
        {
            // Set the boss sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, 
                                          bossSpriteColour,
                                          bossSpriteFlags); 

            if (status == ERR_SUCCESS)
            {
                // Set the boss sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, 
                                             bossSpriteColour,
                                             bossSpriteFlags); 

                if (status == ERR_SUCCESS)
                {
                    // Set the boss sprite's sound samples.

                    SetBossSpriteSoundSamples (bossSpriteId);

                    // Note the boss sprite's attributes.

                    m_bossSpriteId      = bossSpriteId;
                    m_bossSpriteFlags   = bossSpriteFlags;
                } // Endif.

            } // Endif.

        } // Endif.

    } // Endif.
    
    return (status);
} // Endproc.


FolioStatus BossSprite::Start (const InformationPanel&  informationPanel,
                               const CollisionGrid&     collisionGrid)
{
    // Recreate the boss sprite.

    FolioStatus status = Recreate (GetInitialScreenXLeft (m_bossSpriteId, collisionGrid),
                                   GetInitialScreenYTop (m_bossSpriteId, collisionGrid),
                                   GetDirection (informationPanel, collisionGrid));

    if (status == ERR_SUCCESS)
    {
        // The boss sprite is initialised.

        SetState (STATE_INITIALISED);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus BossSprite::Move (Gdiplus::Graphics&        graphics,
                              const InformationPanel&   informationPanel,
                              CollisionGrid&            collisionGrid)
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
            // Yes. Set the boss sprite's direction.

            status = SetDirection (GetDirection (informationPanel, collisionGrid));
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // Move the boss sprite.

            status = Folio::Core::Game::ABossSprite::Move (graphics, speed, collisionGrid);
        } // Endif.

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


bool    BossSprite::CanBeKilled (const InformationPanel& informationPanel) const
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


BOSS_SPRITE_ID  BossSprite::GetScreenBossSpriteId (UInt32   screenNumber, 
                                                   UInt32   totalNumRooms)
{
    switch (screenNumber)
    {
    case 86: 
        return (BOSS_SPRITE_HUNCHBACK);
        break;

    case 85: 
        return (BOSS_SPRITE_FRANKENSTEIN);
        break;

    case 67: 
        return (BOSS_SPRITE_DEVIL);
        break;

    default:
        if (IsRedKeyLocation (screenNumber))
        {
            return (BOSS_SPRITE_MUMMY);
        } // Endif.

        else
        {
            return ((Folio::Core::Util::Random::GetRandomNumber (totalNumRooms) == 0) ? BOSS_SPRITE_DRACULA : BOSS_SPRITE_UNDEFINED);
        } // Endelse.
        break;
    } // Endswitch.

} // Endproc.


FolioStatus BossSprite::SetInitialisingMode (FolioHandle                            dcHandle,
                                             Folio::Core::Game::ZxSpectrum::COLOUR  bossSpriteColour,
                                             UInt32                                 bossSpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 7;

    FolioStatus status = ERR_SUCCESS;

    // Is the boss sprite initialised by graphic?

    if (NastySprite::IsInitialisedByGraphic (bossSpriteFlags))
    {
        // Yes. Query the boss sprite's initialising graphics.

        Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

        status = NastySprite::QueryInitialisingGraphics (dcHandle,
                                                         Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_BOSS_SPRITE,
                                                         bossSpriteColour, 
                                                         spriteGraphicAttributesList);

        if (status == ERR_SUCCESS)
        {
            // Set graphic initialising mode.

            status = SetGraphicInitialisingMode (dcHandle,
                                                 spriteGraphicAttributesList,
                                                 MAX_SEQUENCE_COUNT);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus BossSprite::SetTerminatingMode (FolioHandle                             dcHandle,
                                            Folio::Core::Game::ZxSpectrum::COLOUR   bossSpriteColour,
                                            UInt32                                  bossSpriteFlags)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 4;

    FolioStatus status = ERR_SUCCESS;

    // Is the boss sprite terminated by graphic?

    if (NastySprite::IsTerminatedByGraphic (bossSpriteFlags))
    {
        // Yes. Query the boss sprite's terminating graphics.

        Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

        status = NastySprite::QueryTerminatingGraphics (dcHandle,
                                                        Folio::Core::Game::ResourceGraphicsCache::OWNER_ID_BOSS_SPRITE,
                                                        bossSpriteColour, 
                                                        spriteGraphicAttributesList);
        
        if (status == ERR_SUCCESS)
        {
            // Set graphic terminating mode.

            status = SetGraphicTerminatingMode (dcHandle,
                                                spriteGraphicAttributesList,
                                                MAX_SEQUENCE_COUNT);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


void    BossSprite::SetBossSpriteSoundSamples (BOSS_SPRITE_ID bossSpriteId)
{
    switch (bossSpriteId)
    {
    case BOSS_SPRITE_FRANKENSTEIN:
        // Create the boss sprite's sound samples.

        CreateBossSpriteSoundSamples (bossSpriteId);

        // Set the boss sprite's terminated sound sample.

        SetBossSpriteTerminatedSoundSample (bossSpriteId);
        break;

    case BOSS_SPRITE_MUMMY:            
    case BOSS_SPRITE_HUNCHBACK:
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_DEVIL:                
    default:
        break;
    } // Endswitch.

} // Endproc.


void    BossSprite::SetBossSpriteTerminatedSoundSample (BOSS_SPRITE_ID bossSpriteId)
{
    switch (bossSpriteId)
    {
    case BOSS_SPRITE_FRANKENSTEIN:
        SetSpriteTerminatedSoundSample (Folio::Core::Game::SpriteSoundSample(new Folio::Core::Game::SpriteSoundSample::element_type(m_bossSpriteTerminatedSoundSample)));
        break;

    case BOSS_SPRITE_MUMMY:            
    case BOSS_SPRITE_HUNCHBACK:
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_DEVIL:                
    default:
        break;
    } // Endswitch.

} // Endproc.


bool    BossSprite::IsUpdateDirectionRqd (const CollisionGrid& collisionGrid) const
{
    bool    isUpdateDirectionRqd = true;    // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
        // Is the main player ready?

        if (g_mainPlayer->IsReady ())
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


Folio::Core::Game::Direction    BossSprite::GetDirection (const InformationPanel&   informationPanel,
                                                          const CollisionGrid&      collisionGrid) const
{
    Folio::Core::Game::Direction    direction = Folio::Core::Game::NO_DIRECTION;    // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
        {
            // The direction of the mummy is dependent on whether or not a static sprite 
            // it is attracted to is on the screen.
            
            bool    staticSpriteFound = false;  // Initialise!

            direction = GetDirectionToAttractedStaticSprite (collisionGrid, staticSpriteFound);

            // Was a static sprite the mummy is attracted to found?

            if (!staticSpriteFound && 
                (direction == Folio::Core::Game::NO_DIRECTION))
            {
                // No. Move the mummy to the main player if ready. Otherwise move to 
                // the nearest corner of the screen.
                
                direction = g_mainPlayer->IsReady ()
                            ? Folio::Core::Game::ABossSprite::GetDirectionToScreenRect (g_mainPlayer->GetScreenRect (), collisionGrid)
                            : Folio::Core::Game::ABossSprite::GetDirectionToNearestCorner (collisionGrid);
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

            if (!staticSpriteFound && 
                (direction == Folio::Core::Game::NO_DIRECTION))
            {
                // No. Move the hunchback to its initial position.

                direction = Folio::Core::Game::ABossSprite::GetDirectionToScreenTopLeft (GetInitialScreenXLeft (m_bossSpriteId, collisionGrid),
                                                                                         GetInitialScreenYTop (m_bossSpriteId, collisionGrid),
                                                                                         collisionGrid);
            } // Endif.

        } // Endscope.
        break;     

    case BOSS_SPRITE_DRACULA:
        // Move dracula to or from the main player if ready and depending on whether 
        // or not the crucifix is collected. Otherwise move to the nearest corner of 
        // the screen.

        direction = g_mainPlayer->IsReady () 
                    ? Folio::Core::Game::ABossSprite::GetDirectionToScreenRect (g_mainPlayer->GetScreenRect (), 
                                                                                collisionGrid, 
                                                                                !informationPanel.IsCrucifixCollected ())
                    : Folio::Core::Game::ABossSprite::GetDirectionToNearestCorner (collisionGrid);
        break;            

    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:
        // Move the boss sprite to the main player if ready. Otherwise move to 
        // the nearest corner of the screen.

        direction = g_mainPlayer->IsReady () 
                    ? Folio::Core::Game::ABossSprite::GetDirectionToScreenRect (g_mainPlayer->GetScreenRect (), 
                                                                                collisionGrid)
                    : Folio::Core::Game::ABossSprite::GetDirectionToNearestCorner (collisionGrid);
        break;            

    default:
        direction = Folio::Core::Game::NO_DIRECTION;
        break;            
    } // Endswitch.

    return (direction);
} // Endproc.


Folio::Core::Game::Direction    BossSprite::GetDirectionToAttractedStaticSprite (const CollisionGrid&   collisionGrid,
                                                                                 bool&                  staticSpriteFound) const
{
    staticSpriteFound = false;  // Initialise!

    Folio::Core::Game::Direction    direction = Folio::Core::Game::NO_DIRECTION;    // Initialise!

    // Find the static sprites in the collision grid.

    CollisionGrid::CellElements cellElementsList;

    if (collisionGrid.FindCellElements (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE, cellElementsList))
    {
        // Are any of the static sprites one that the boss sprite is attracted to?

        bool    previousStaticSpriteFound = false;  // Initialise!

        for (CollisionGrid::CellElements::const_iterator itr = cellElementsList.begin ();
             !staticSpriteFound && (itr != cellElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            const   StaticSprite   &staticSprite(*reinterpret_cast<StaticSprite *> (itr->m_userData));

            // Is the static sprite one that the boss sprite is attracted to?

            if (IsAttractedToStaticSprite (m_bossSpriteId, staticSprite))
            {
                // Yes. Move the boss sprite to the static sprite.

                direction = Folio::Core::Game::ABossSprite::GetDirectionToScreenRect (staticSprite.GetScreenRect (), 
                                                                                      collisionGrid);

                if ((m_bossSpriteId == BOSS_SPRITE_MUMMY) && 
                    (staticSprite.GetStaticSpriteId () == STATIC_SPRITE_KEY))
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


UInt32  BossSprite::GetSpeed (const InformationPanel&   informationPanel,
                              const CollisionGrid&      collisionGrid) const
{
    UInt32  speed = STATIC_SPEED;  // Initialise!

    switch (m_bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
    case BOSS_SPRITE_FRANKENSTEIN:            
    case BOSS_SPRITE_DEVIL:
        // The speed of the boss sprite is dependent on whether or not the main 
        // player is ready and the boss sprite is at the main player.
        
        speed = g_mainPlayer->IsReady () && Folio::Core::Game::ABossSprite::IsAtScreenRect (g_mainPlayer->GetScreenRect ()) 
                ? STATIC_SPEED 
                : BOSS_SPRITE_SPEED;
        break;

    case BOSS_SPRITE_HUNCHBACK:                
        {
            // The speed of the hunchback is dependent on whether or not a static sprite 
            // it is attracted to is on the screen.
            
            bool    staticSpriteFound = false;  // Initialise!

            speed = GetSpeedToAttractedStaticSprite (collisionGrid, staticSpriteFound);

            if (!staticSpriteFound && (speed == STATIC_SPEED))
            {
                speed = Folio::Core::Game::ABossSprite::IsAtScreenTopLeft (GetInitialScreenXLeft (m_bossSpriteId, collisionGrid),
                                                                           GetInitialScreenYTop (m_bossSpriteId, collisionGrid)) 
                        ? STATIC_SPEED 
                        : BOSS_SPRITE_SPEED;

            } // Endif.
        
        } // Endscope.
        break;     

    case BOSS_SPRITE_DRACULA:            
        // The speed of dracula is dependent on whether or not the crucifix is 
        // collected, and on whether or not the main player is ready and 
        // dracula is at the main player.

        if (informationPanel.IsCrucifixCollected ())
        {
            speed = BOSS_SPRITE_SPEED;
        } // Endif.

        else
        {
            // The speed of the boss sprite.
        
            speed = g_mainPlayer->IsReady () && Folio::Core::Game::ABossSprite::IsAtScreenRect (g_mainPlayer->GetScreenRect ()) 
                    ? STATIC_SPEED 
                    : BOSS_SPRITE_SPEED;
        } // Endelse.
        break;

    default:
        speed = STATIC_SPEED;
        break;
    } // Endswitch.

    return (speed);
} // Endproc.


UInt32  BossSprite::GetSpeedToAttractedStaticSprite (const CollisionGrid&   collisionGrid, 
                                                     bool&                  staticSpriteFound) const
{
    staticSpriteFound = false;  // Initialise!

    UInt32  speed = STATIC_SPEED;  // Initialise!

    // Find the static sprites in the collision grid.

    CollisionGrid::CellElements cellElementsList;

    if (collisionGrid.FindCellElements (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE, cellElementsList))
    {
        // Are any of the static sprites one that the boss sprite is attracted to?

        bool    previousStaticSpriteFound = false;  // Initialise!

        for (CollisionGrid::CellElements::const_iterator itr = cellElementsList.begin ();
             !staticSpriteFound && (itr != cellElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            const   StaticSprite    &staticSprite(*reinterpret_cast<StaticSprite *> (itr->m_userData));

            // Is the static sprite one that the boss sprite is attracted to?

            if (IsAttractedToStaticSprite (m_bossSpriteId, staticSprite))
            {
                // Yes. The speed of the boss sprite is dependent on whether or not it is at the static sprite.

                speed = Folio::Core::Game::ABossSprite::IsAtScreenRect (staticSprite.GetScreenRect ()) 
                        ? STATIC_SPEED 
                        : BOSS_SPRITE_SPEED;

                if ((m_bossSpriteId == BOSS_SPRITE_MUMMY) && 
                    (staticSprite.GetStaticSpriteId () == STATIC_SPRITE_KEY))
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


bool    BossSprite::IsAnyAttractedStaticSprite (const CollisionGrid& collisionGrid) const
{
    bool    isAnyAttractedStaticSprite = false; // Initialise!

    // Find the static sprites in the collision grid.

    CollisionGrid::CellElements cellElementsList;

    if (collisionGrid.FindCellElements (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_STATIC_SPRITE, cellElementsList))
    {
        // Are any of the static sprites one that the boss sprite is attracted to?

        for (CollisionGrid::CellElements::const_iterator itr = cellElementsList.begin ();
             !isAnyAttractedStaticSprite && (itr != cellElementsList.end ());
             ++itr)
        {
            // Get the static sprite.

            const   StaticSprite    &staticSprite(*reinterpret_cast<StaticSprite *> (itr->m_userData));

            // Is the static sprite one that the boss sprite is attracted to?

            isAnyAttractedStaticSprite = IsAttractedToStaticSprite (m_bossSpriteId, staticSprite);
        } // Endfor.

    } // Endif.

    return (isAnyAttractedStaticSprite);
} // Endproc.


Int32   BossSprite::GetInitialScreenXLeft (BOSS_SPRITE_ID       bossSpriteId,
                                           const CollisionGrid& collisionGrid)
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

            CollisionGrid::ScreenEntrance   screenEntrance(g_mainPlayer->GetScreenEntrance ());

            // Calculate the initial screen X left position of the boss sprite.

            switch (screenEntrance.m_orientation)
            {
            case CollisionGrid::ScreenExit::TOP:
            case CollisionGrid::ScreenExit::BOTTOM:
                initialScreenXLeft = screenEntrance.m_screenRect.X + (screenEntrance.m_screenRect.Width - MAX_BOSS_SPRITE_WIDTH) / 2;
                break;

            case CollisionGrid::ScreenExit::LEFT:
                initialScreenXLeft = collisionGrid.GetFloorRightBound () - MAX_BOSS_SPRITE_WIDTH;
                break;
            
            case CollisionGrid::ScreenExit::RIGHT:
                initialScreenXLeft = collisionGrid.GetFloorLeftBound ();
                break;

            case CollisionGrid::ScreenExit::FLOOR:
            default:
                initialScreenXLeft = collisionGrid.GetFloorLeftBound () + (collisionGrid.GetFloorWidth () - MAX_BOSS_SPRITE_WIDTH) / 2;
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case BOSS_SPRITE_DRACULA:            
        initialScreenXLeft = Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorLeftBound () + 8, 
                                                                         collisionGrid.GetFloorRightBound () - MAX_BOSS_SPRITE_WIDTH);
        break;

    default:
        break;
    } // Endswitch.

    return (initialScreenXLeft);
} // Endproc.


Int32   BossSprite::GetInitialScreenYTop (BOSS_SPRITE_ID        bossSpriteId,
                                          const CollisionGrid&  collisionGrid)
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

            CollisionGrid::ScreenEntrance   screenEntrance(g_mainPlayer->GetScreenEntrance ());

            // Calculate the initial screen Y top position of the boss sprite.

            switch (screenEntrance.m_orientation)
            {
            case CollisionGrid::ScreenExit::TOP:
                initialScreenYTop = collisionGrid.GetFloorBottomBound () - MAX_BOSS_SPRITE_HEIGHT;
                break;

            case CollisionGrid::ScreenExit::BOTTOM:
                initialScreenYTop = collisionGrid.GetFloorTopBound ();
                break;

            case CollisionGrid::ScreenExit::LEFT:
            case CollisionGrid::ScreenExit::RIGHT:
                initialScreenYTop = screenEntrance.m_screenRect.Y + (screenEntrance.m_screenRect.Height - MAX_BOSS_SPRITE_HEIGHT) / 2;
                break;

            case CollisionGrid::ScreenExit::FLOOR:
            default:
                initialScreenYTop = collisionGrid.GetFloorTopBound () + (collisionGrid.GetFloorHeight () - MAX_BOSS_SPRITE_HEIGHT) / 2;
                break;
            } // Endswitch.

        } // Endscope.
        break;

    case BOSS_SPRITE_DRACULA:            
        initialScreenYTop = Folio::Core::Util::Random::GetRandomNumber (collisionGrid.GetFloorTopBound () + 8, 
                                                                        collisionGrid.GetFloorBottomBound () - MAX_BOSS_SPRITE_HEIGHT);
        break;

    default:
        break;
    } // Endswitch.

    return (initialScreenYTop);
} // Endproc.


bool    BossSprite::IsAttractedToStaticSprite (BOSS_SPRITE_ID       bossSpriteId,
                                               const StaticSprite&  staticSprite)
{
    bool    isAttractedToStaticSprite = false;  // Initialise!

    switch (bossSpriteId)
    {
    case BOSS_SPRITE_MUMMY:
        // The mummy is attracted to the leaf and the red key.

        isAttractedToStaticSprite = ((staticSprite.GetStaticSpriteId () == STATIC_SPRITE_LEAF) || 
                                    ((staticSprite.GetStaticSpriteId () == STATIC_SPRITE_KEY) && (staticSprite.GetStaticSpriteColour () == (Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED))));  
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


void    BossSprite::CreateBossSpriteSoundSamples (BOSS_SPRITE_ID bossSpriteId)
{
    switch (bossSpriteId)
    {
    case BOSS_SPRITE_FRANKENSTEIN:
        // Create the boss sprite terminated sound sample.

        CreateBossSpriteTerminatedSoundSample ();
        break;

    case BOSS_SPRITE_MUMMY:            
    case BOSS_SPRITE_HUNCHBACK:
    case BOSS_SPRITE_DRACULA:            
    case BOSS_SPRITE_DEVIL:                
    default:
        break;
    } // Endswitch.

} // Endproc.


void    BossSprite::CreateBossSpriteTerminatedSoundSample ()
{
    // Has the boss sprite terminated sound sample been created?

    if (!m_bossSpriteTerminatedSoundSample.IsSoundSampleGenerated ())
    {
        // No. Create each sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x3f; frequency >= 0x21; frequency -= 2)
        {
            m_bossSpriteTerminatedSoundSample.AddSoundSample (Ultimate::CreateSoundSample (frequency, 0x01));
        } // Endfor.

    } // Endif.
    
} // Endproc.


FolioStatus CreateBossSprites (FolioHandle      dcHandle,
                               BossSpritesMap&  bossSpritesMap)
{
    FolioStatus status = ERR_SUCCESS;

    bossSpritesMap.clear ();   // Initialise!

    // Build the boss sprites map.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_bossSpriteAttributesTable) / sizeof (BossSpriteAttributes)));
         ++index)
    {              
        // Create a boss sprite.

        BossSpritePtr bossSprite(new BossSprite);

        status = bossSprite->Create (dcHandle,
                                     g_bossSpriteAttributesTable [index].m_bossSpriteId,
                                     g_bossSpriteAttributesTable [index].m_bossSpriteColour,
                                     g_bossSpriteAttributesTable [index].m_bossSpriteFlags);

        if (status == ERR_SUCCESS)
        {
            // Store the boss sprite in the boss sprites map.
        
            bossSpritesMap.insert (BossSpritesMap::value_type(g_bossSpriteAttributesTable [index].m_bossSpriteId, 
                                                              bossSprite));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        bossSpritesMap.clear ();
    } // Endif.

    return (status);
} // Endproc.


void    SetBossSpritesAlive (BossSpritesMap& bossSpritesMap)
{
    // All the boss sprite's are alive.

    for (BossSpritesMap::iterator itr = bossSpritesMap.begin ();
         itr != bossSpritesMap.end ();
         ++itr)
    {
        // The boss sprite is alive.

        itr->second->SetAlive ();
    } // Endfor.

} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
