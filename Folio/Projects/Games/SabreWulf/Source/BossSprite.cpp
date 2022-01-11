// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "BossSprite.h"
#include    "SpriteGraphics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Boss sprite attributes.
struct BossSpriteAttributes
{
    BOSS_SPRITE_ID                          m_bossSpriteId;             // The identifier of the boss sprite.
    UInt32                                  m_initialScreenMapIndex;    // The initial screen map index of the boss sprite.
    Int32                                   m_initialScreenXLeft;       // The initial screen X left (in pixels) of the boss sprite.
    Int32                                   m_initialScreenYBottom;     // The initial screen Y bottom (in pixels) of the boss sprite.
    Folio::Core::Game::Direction            m_initialDirection;         // The initial direction of the boss sprite.
    UInt32                                  m_initialSpeed;             // The initial speed of the boss sprite.
    Folio::Core::Game::ZxSpectrum::COLOUR   m_bossSpriteColour;         // The colour of the boss sprite.
}; // Endstruct.

// Boss sprite attributes table.
static  const   BossSpriteAttributes  g_bossSpriteAttributesTable [] =
{
//      m_bossSpriteId              m_initialScreenMapIndex m_initialScreenXLeft    m_initialScreenYBottom  m_initialDirection      m_initialSpeed                              m_bossSpriteColour                                                              
    {   BOSS_SPRITE_RHINOCEROS_1,   152,                    112,                    131,                    Folio::Core::Game::E,   BossSprite::DEFAULT_SPEED,                  Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   BOSS_SPRITE_RHINOCEROS_2,     7,                    112,                     63,                    Folio::Core::Game::W,   BossSprite::DEFAULT_SPEED,                  Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   BOSS_SPRITE_RHINOCEROS_3,   243,                    112,                    131,                    Folio::Core::Game::E,   BossSprite::DEFAULT_SPEED,                  Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   BOSS_SPRITE_RHINOCEROS_4,   152,                    112,                     63,                    Folio::Core::Game::W,   BossSprite::DEFAULT_SPEED,                  Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   BOSS_SPRITE_GUARDIAN,       136,                    112,                    135,                    Folio::Core::Game::E,   Folio::Core::Game::ASprite::STATIC_SPEED,   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
};


// Boss sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<BOSS_SPRITE_ID, SPRITE_ID> g_bossSpriteGraphicCharacteristics =
{
//      m_spriteId                  m_direction                         m_spriteGraphicIdsList
    {   BOSS_SPRITE_RHINOCEROS_1,   Folio::Core::Game::E,               {   SPRITE_RHINOCEROS_RUNNING_RIGHT_1, SPRITE_RHINOCEROS_RUNNING_RIGHT_2,   },  },
    {   BOSS_SPRITE_RHINOCEROS_1,   Folio::Core::Game::W,               {   SPRITE_RHINOCEROS_RUNNING_LEFT_1, SPRITE_RHINOCEROS_RUNNING_LEFT_2,     },  },

    {   BOSS_SPRITE_RHINOCEROS_2,   Folio::Core::Game::E,               {   SPRITE_RHINOCEROS_RUNNING_RIGHT_1, SPRITE_RHINOCEROS_RUNNING_RIGHT_2,   },  },
    {   BOSS_SPRITE_RHINOCEROS_2,   Folio::Core::Game::W,               {   SPRITE_RHINOCEROS_RUNNING_LEFT_1, SPRITE_RHINOCEROS_RUNNING_LEFT_2,     },  },

    {   BOSS_SPRITE_RHINOCEROS_3,   Folio::Core::Game::E,               {   SPRITE_RHINOCEROS_RUNNING_RIGHT_1, SPRITE_RHINOCEROS_RUNNING_RIGHT_2,   },  },
    {   BOSS_SPRITE_RHINOCEROS_3,   Folio::Core::Game::W,               {   SPRITE_RHINOCEROS_RUNNING_LEFT_1, SPRITE_RHINOCEROS_RUNNING_LEFT_2,     },  },

    {   BOSS_SPRITE_RHINOCEROS_4,   Folio::Core::Game::E,               {   SPRITE_RHINOCEROS_RUNNING_RIGHT_1, SPRITE_RHINOCEROS_RUNNING_RIGHT_2,   },  },
    {   BOSS_SPRITE_RHINOCEROS_4,   Folio::Core::Game::W,               {   SPRITE_RHINOCEROS_RUNNING_LEFT_1, SPRITE_RHINOCEROS_RUNNING_LEFT_2,     },  },

    {   BOSS_SPRITE_GUARDIAN,       Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_GUARDIAN_1, SPRITE_GUARDIAN_2,                                   },  },
};


BossSprite::BossSprite ()
:   m_bossSpriteId(BOSS_SPRITE_UNDEFINED),
    m_bossSpriteScreenMapIndex(ScreenMap::UNDEFINED_SCREEN_INDEX),
    m_bossSpriteSpeed(DEFAULT_SPEED)
{
} // Endproc.


BossSprite::~BossSprite ()
{
} // Endproc.


FolioStatus BossSprite::Create (FolioHandle                             dcHandle,
                                BOSS_SPRITE_ID                          bossSpriteId,
                                UInt32                                  initialScreenMapIndex,
                                Int32                                   initialScreenXLeft,
                                Int32                                   initialScreenYBottom,
                                Folio::Core::Game::Direction            initialDirection,
                                UInt32                                  initialSpeed,
                                Folio::Core::Game::ZxSpectrum::COLOUR   bossSpriteColour)
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
        // Get the current sprite graphic.

        Folio::Core::Game::SpriteGraphic    spriteGraphic(spriteGraphicAttributesList.front ().m_spriteGraphicsList.front ());

        // Calculate the initial screen Y top.

        Int32   initialScreenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (initialScreenYBottom, 
                                                                                        spriteGraphic->GetGraphicWidth (),
                                                                                        spriteGraphic->GetGraphicHeight ());

        // Create the boss sprite.

        status = Folio::Core::Game::ABossSprite::Create (dcHandle,
                                                         spriteGraphicAttributesList,
                                                         initialScreenXLeft,
                                                         initialScreenYTop,
                                                         Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                         Folio::Core::Game::ZxSpectrum::MapInkColour (bossSpriteColour),
                                                         initialDirection,
                                                         &(g_resourceGraphicsCache),
                                                         0, // No auto-mode moves.
                                                         NO_REBOUND);

        if (status == ERR_SUCCESS)
        {
            // Note the boss sprite's attributes.

            m_bossSpriteId              = bossSpriteId;
            m_bossSpriteScreenMapIndex  = initialScreenMapIndex;
            m_bossSpriteSpeed           = initialSpeed;

            // The boss sprite is alive.

            SetAlive ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus BossSprite::CheckBossSprite (Folio::Core::Game::DrawingElementPtr&  drawingElement,
                                         Gdiplus::Graphics&                     graphics,
                                         bool&                                  onCurrentScreen,
                                         CollisionGrid&                         collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    //FolioOStringStream  str;
    //str << m_bossSpriteScreenMapIndex 
    //    << TXT(" ") << Describe () 
    //    << TXT(" ") << m_currentNumSteps
    //    << std::endl;
    //OutputDebugString (str.str ().c_str ());

    switch (m_state)
    {
    case STATE_INITIALISE_RQD:
        // Initialise the boss sprite.

        status = InitialiseSprite (graphics);
        break;

    case STATE_INITIALISED:
        // The boss sprite is initialised.

        // The boss sprite is static.

        status = Static (graphics, collisionGrid);
        break;

    case STATE_TERMINATED:
        // The boss sprite is terminated.
        break;

    case STATE_STATIC:
        // Is the boss sprite on the current screen?

        if (onCurrentScreen)
        {
            // Yes. Add the boss sprite to the current screen's collision grid.

            status = collisionGrid.AddCellElement (*(drawingElement));
        } // Endif.

        if (status == ERR_SUCCESS)
        {
            // The boss sprite is moving.

            SetState (STATE_MOVING);
        } // Endif.
        break;

    case STATE_MOVING:
        // Move the boss sprite.

        status = Move (drawingElement, graphics, onCurrentScreen, collisionGrid);

        if (status == ERR_SUCCESS)
        {
            // Set the boss sprite's drawing element's top-left screen position.

            status = drawingElement->SetScreenTopLeft (m_screenRect.X, m_screenRect.Y);

            // Is the boss sprite on the current screen?

            if (onCurrentScreen && (status == ERR_SUCCESS))
            {
                // Yes. Update the boss sprite in the current screen's collision 
                // grid.

                status = collisionGrid.UpdateCellElement (*(drawingElement));
            } // Endif.

        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

    return (status);
} // Endproc.


FolioStatus BossSprite::ChangeDirection ()
{
    // Set the boss sprite's opposite direction.

    FolioStatus status = SetDirection (GetFloorBoundDirection (ToCollisionGridDirection (m_direction)));

    if (status == ERR_SUCCESS)
    {
        // Make sure boss sprite speed is default.

        m_bossSpriteSpeed = DEFAULT_SPEED;
    } // Endif.

    return (status);
} // Endproc.


FolioStatus BossSprite::ChangeSpeed ()
{
    // Always set to fast speed.

    m_bossSpriteSpeed = FAST_SPEED;

    return (ERR_SUCCESS);
} // Endproc.


BOSS_SPRITE_ID   BossSprite::GetBossSpriteId () const
{
    return (m_bossSpriteId);
} // Endproc.


UInt32  BossSprite::GetBossSpriteScreenMapIndex () const
{
    return (m_bossSpriteScreenMapIndex);
} // Endproc.


FolioStatus BossSprite::Move (Folio::Core::Game::DrawingElementPtr& drawingElement,
                              Gdiplus::Graphics&                    graphics,
                              bool&                                 onCurrentScreen,
                              CollisionGrid&                        collisionGrid)
{
    // Move the boss sprite.

    FolioStatus status = Folio::Core::Game::ABossSprite::Move (graphics, 
                                                               m_bossSpriteSpeed, 
                                                               collisionGrid);

    if (status == ERR_SUCCESS)
    {
        // Has the boss sprite hit a wall?

        if (m_isAtWall)
        {
            // Yes. Change the boss sprite's direction.

            status = ChangeDirection ();
        } // Endif.

        // Has the boss sprite exited the screen?

        else
        if (m_isExitedScreen)
        {
            // Yes. Is the boss sprite on the current screen?
            
            if (onCurrentScreen)
            {
                // Yes. Remove the boss sprite from the current screen's collision 
                // grid.

                status = collisionGrid.RemoveCellElement (*(drawingElement));
            } // Endif.

            if (status == ERR_SUCCESS)
            {
                // Set the boss sprite's position at the screen's entrance.

                status = SetScreenEntranceTopLeft (collisionGrid.GetFloorRect ());

                if (status == ERR_SUCCESS)
                {
                    // Get the boss sprite's new screen.

                    m_bossSpriteScreenMapIndex = g_screenMap.GetNewScreenMapIndex (m_screenExit.m_orientation, 
                                                                                   m_bossSpriteScreenMapIndex);

                    // Boss sprite is no longer on the current screen,

                    onCurrentScreen = false;
                } // Endif.

            } // Endif.
    
        } // Endelseif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus CreateBossSpriteDrawingElements (FolioHandle dcHandle)
{
    FolioStatus status = ERR_SUCCESS;

    // Clear the boss sprite drawing elements list.

    g_bossSpriteDrawingElementsList.clear ();

    // Build the boss sprite drawing elements list.

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_bossSpriteAttributesTable) / sizeof (BossSpriteAttributes)));
         ++index)
    {              
        // Create the boss sprite.

        BossSpritePtr   bossSprite(new BossSpritePtr::element_type);

        status = bossSprite->Create (dcHandle,
                                     g_bossSpriteAttributesTable [index].m_bossSpriteId,
                                     g_bossSpriteAttributesTable [index].m_initialScreenMapIndex,
                                     g_bossSpriteAttributesTable [index].m_initialScreenXLeft,
                                     g_bossSpriteAttributesTable [index].m_initialScreenYBottom,
                                     g_bossSpriteAttributesTable [index].m_initialDirection,
                                     g_bossSpriteAttributesTable [index].m_initialSpeed,
                                     g_bossSpriteAttributesTable [index].m_bossSpriteColour);

        if (status == ERR_SUCCESS)
        {
            // Add the boss sprite drawing element to the boss sprite drawing 
            // elements list.

            g_bossSpriteDrawingElementsList.push_back (BossSpriteDrawingElement(Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE, 
                                                                                bossSprite));
        } // Endif.

    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        g_bossSpriteDrawingElementsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus CheckBossSprites (FolioHandle           dcHandle,
                              Gdiplus::Graphics&    graphics,
                              CollisionGrid&        collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current screen map index.

    UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

    // Check all the boss sprites for the current screen.

    for (BossSpriteDrawingElementsList::iterator itr = g_bossSpriteDrawingElementsList.begin ();
         (status == ERR_SUCCESS) && (itr != g_bossSpriteDrawingElementsList.end ());
         ++itr)
    {
        // Get the boss sprite.

        BossSpritePtr   &bossSprite(itr->m_sprite);

        // On the current screen?

        bool    onCurrentScreen = (bossSprite->GetBossSpriteScreenMapIndex () == currentScreenMapIndex);

        // Check the boss sprite.

        status = bossSprite->CheckBossSprite (itr->m_drawingElement, 
                                              graphics, 
                                              onCurrentScreen,
                                              *g_screenCollisionGridMap [g_screenMap.GetCurrentScreenNumber ()]);
    } // Endfor.

    return (status);
} // Endproc.


FolioStatus RemoveScreenBossSprites (CollisionGrid& collisionGrid)
{
    // Remove all boss sprites from the current screen's collision grid.

    return (collisionGrid.RemoveCellElements (Folio::Core::Game::DrawingElement::DRAWING_ELEMENT_BOSS_SPRITE));
} // Endproc.


FolioStatus StoreScreenBossSpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current screen map index.

    UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

    // Store all the boss sprites' backgrounds for the current screen.

    for (BossSpriteDrawingElementsList::iterator itr = g_bossSpriteDrawingElementsList.begin ();
         (status == ERR_SUCCESS) && (itr != g_bossSpriteDrawingElementsList.end ());
         ++itr)
    {
        // Get the boss sprite.

        BossSpritePtr   &bossSprite(itr->m_sprite);

        // Is the boss sprite on the current screen?

        if (bossSprite->GetBossSpriteScreenMapIndex () == currentScreenMapIndex)
        {
            // Yes. Store the boss sprite's background.

            status = bossSprite->StoreUnderlyingBackground (graphics);
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus RestoreScreenBossSpriteBackgrounds (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current screen map index.

    UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

    // Restore all the boss sprites' backgrounds for the current screen.

    for (BossSpriteDrawingElementsList::iterator itr = g_bossSpriteDrawingElementsList.begin ();
         (status == ERR_SUCCESS) && (itr != g_bossSpriteDrawingElementsList.end ());
         ++itr)
    {
        // Get the boss sprite.

        BossSpritePtr  &bossSprite(itr->m_sprite);

        // Is the boss sprite on the current screen?

        if (bossSprite->GetBossSpriteScreenMapIndex () == currentScreenMapIndex)
        {
            // Yes. Restore the boss sprite's background.

            status = bossSprite->RestoreUnderlyingBackground (graphics);
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus DrawScreenBossSprites (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the current screen map index.

    UInt32  currentScreenMapIndex = g_screenMap.GetCurrentScreenMapIndex ();

    // Draw all the boss sprites for the current screen.

    for (BossSpriteDrawingElementsList::iterator itr = g_bossSpriteDrawingElementsList.begin ();
         (status == ERR_SUCCESS) && (itr != g_bossSpriteDrawingElementsList.end ());
         ++itr)
    {
        // Get the boss sprite.

        BossSpritePtr  &bossSprite(itr->m_sprite);

        // Is the boss sprite on the current screen?

        if (bossSprite->GetBossSpriteScreenMapIndex () == currentScreenMapIndex)
        {
            // Yes. Draw the boss sprite.

            status = bossSprite->Draw (graphics);
        } // Endif.

    } // Endfor.
    
    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
