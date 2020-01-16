// "Home-made" includes.
#include    "StdAfx.h"
#include    "Globals.h"
#include    "OrchidSprite.h"
#include    "ResourceOwnerId.h"
#include    "SpriteGraphics.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Orchid sprite graphic characteristics.
static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<ORCHID_SPRITE_ID, SPRITE_ID>    g_orchidSpriteGraphicCharacteristics =
{
//      m_spriteId      m_direction             spriteGraphicIdsList
    {   ORCHID_SPRITE,  Folio::Core::Game::N,   {   SPRITE_ORCHID_8,    },  },  
    {   ORCHID_SPRITE,  Folio::Core::Game::S,   {   SPRITE_ORCHID_1,    },  },  
};


OrchidSprite::OrchidSprite ()
:   m_orchidSpriteColour(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_transitionTickCount(0),
    m_colourChangeIndex(FOLIO_INVALID_INDEX),
    m_infectedPlayer(false)
{
} // Endproc.


OrchidSprite::~OrchidSprite ()
{
} // Endproc.


FolioStatus OrchidSprite::Create (FolioHandle dcHandle)
{
    // Get the orchid sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR   orchidSpriteColour = GetOrchidSpriteColour ();

    // Query the orchid sprite's graphic attributes.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<ORCHID_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       OWNER_ID_ORCHID_SPRITE,
                                                                                                       DRAWING_ELEMENT_ORCHID_SPRITE,
                                                                                                       ORCHID_SPRITE,
                                                                                                       orchidSpriteColour,
                                                                                                       g_orchidSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Create the orchid sprite.

        status = Folio::Core::Game::AStaticSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           INITIAL_SCREEN_X_LEFT,
                                                           INITIAL_SCREEN_Y_TOP,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (orchidSpriteColour),
                                                           Folio::Core::Game::S,    // The orchid sprite is shrunk.
                                                           &(g_resourceGraphicsCache));

        if (status == ERR_SUCCESS)
        {
            // Set the orchid sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, orchidSpriteColour);

            if (status == ERR_SUCCESS)
            {
                // Set the orchid sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, orchidSpriteColour); 

                if (status == ERR_SUCCESS)
                {
                    // The orchid sprite is static.

                    SetState (STATE_STATIC);

                    // Note the orchid sprite's attributes.

                    m_orchidSpriteColour = orchidSpriteColour;
                } // Endif.

            } // Endif.

       } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus OrchidSprite::SetScreenBottomLeft (Int32    screenXLeft,
                                               Int32    screenYBottom)
{
    // Calculate the orchid sprite's screen Y top.

    Int32   screenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (screenYBottom, 
                                                                             m_screenWidth,
                                                                             m_screenHeight);

    // Set the orchid sprite's screen position.

    return (Folio::Core::Game::AStaticSprite::SetScreenTopLeft (screenXLeft, screenYTop));
} // Endproc.


void    OrchidSprite::StartTransitionTickCount (bool newScreen)
{
    // Is the orchid sprite sprite grown?

    if (IsOrchidSpriteGrown ())
    {
        // Yes. Is this a new screen?

        if (newScreen)
        {
            // Yes. Should the orchid sprite's colour be changed?

            if (Folio::Core::Util::Random::GetRandomNumber (4) == 0)
            {
                // Yes. Leave the orchid sprite grown but change its colour.

                ChangeOrchidSpriteColour ();
            } // Endif.

            else
            {
                // The orchid sprite should shrink.

                SetOrchidSpriteShrinking ();
            } // Endelse.

        } // Endif.

        else
        {
            // No. Set the transition tick count at which time orchid sprite 
            // should start to shrink.

            m_transitionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                    1000 * Folio::Core::Util::Random::GetRandomNumber (1, 4);
        } // Endelse.

    } // Endif.

    // Is the orchid sprite sprite shrunk?

    else
    if (IsOrchidSpriteShrunk ())
    {
        // Yes. Set the transition tick count at which time the orchid sprite 
        // should start to grow.

        m_transitionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                1000 * Folio::Core::Util::Random::GetRandomNumber (5, 10);
    } // Endelseif.

} // Endproc.


void    OrchidSprite::CheckTransition ()
{
    switch (m_state)
    {
    case STATE_INITIALISED:
        // The orchid sprite is initialised. This means that the orchid sprite 
        // has now grown.

        SetOrchidSpriteGrown ();

        // Start the transition tick count; to transition from grown to shrinking.

        StartTransitionTickCount (false);   // Not a new screen.
        break;

    case STATE_TERMINATED:
        // The orchid sprite is terminated. This means that the orchid sprite 
        // has now shrunk.

        SetOrchidSpriteShrunk ();

        // Start the transition tick count; to transition from shrunk to growing.

        StartTransitionTickCount (false);   // Not a new screen.
        break;

    case STATE_STATIC:
        // The orchid sprite is static. This means that the orchid sprite 
        // has either grown or shrunk.

        // Should the orchid sprite transition?

        if (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_transitionTickCount)
        {
            // Yes. Is the orchid sprite grown?

            if (IsOrchidSpriteGrown ())
            {
                // Yes. The orchid sprite should shrink.

                SetOrchidSpriteShrinking ();
            } // Endif.

            else
            {
                // No. The orchid sprite should grow.

                SetOrchidSpriteGrowing ();
            } // Endelse.
            
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


FolioStatus OrchidSprite::HandlePlayerCollision (ORCHID_SPRITE_TYPE                     &orchidSpriteType,
                                                 Folio::Core::Game::ZxSpectrum::COLOUR  &orchidSpriteColour)
{
    orchidSpriteType    = UNDEFINED_ORCHID_TYPE; // Initialise!
    orchidSpriteColour  = Folio::Core::Game::ZxSpectrum::UNDEFINED;

    FolioStatus status = ERR_SUCCESS;

    // The player has collided with an orchide sprite.

    // Is the orchid sprite infectious?

    if (IsOrchidSpriteInfectious ())
    {
        // Yes. Get the orchid sprite type.

        orchidSpriteType = GetOrchidSpriteType (m_orchidSpriteColour);
            
        // Note the orchid sprite's colour.

        orchidSpriteColour = m_orchidSpriteColour;
            
        // The orchid sprite has infected the player.

        m_infectedPlayer = true;

        // The orchid sprite should shrink.

        SetOrchidSpriteShrinking ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus OrchidSprite::SetInitialisingMode (FolioHandle                           dcHandle,
                                               Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Orchid sprite initialising sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<ORCHID_SPRITE_ID, SPRITE_ID>    s_initialisingSpriteGraphicCharacteristics = 
    {
    //      m_spriteId                  m_direction                         m_spriteGraphicIdsList
        {   ORCHID_SPRITE_UNDEFINED,    Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_ORCHID_2, SPRITE_ORCHID_3, SPRITE_ORCHID_4, SPRITE_ORCHID_5, SPRITE_ORCHID_6, SPRITE_ORCHID_7,   },  },
    };

    // Query the orchid sprite's initialising graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<ORCHID_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       OWNER_ID_ORCHID_SPRITE,
                                                                                                       DRAWING_ELEMENT_ORCHID_SPRITE,
                                                                                                       orchidSpriteColour,
                                                                                                       s_initialisingSpriteGraphicCharacteristics,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERR_SUCCESS)
    {
        // Set graphic initialising mode.

        status = SetGraphicInitialisingMode (dcHandle,
                                             spriteGraphicAttributesList,
                                             MAX_SEQUENCE_COUNT);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus OrchidSprite::SetTerminatingMode (FolioHandle                           dcHandle,
                                              Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Orchid sprite terminating sprite characteristics.
    static  const   Folio::Core::Game::SpriteGraphicCharacteristicsList<ORCHID_SPRITE_ID, SPRITE_ID>    s_terminatingSpriteGraphicCharacteristics = 
    {
    //      m_spriteId                  m_direction                         m_spriteGraphicIdsList
        {   ORCHID_SPRITE_UNDEFINED,    Folio::Core::Game::ALL_DIRECTIONS,  {   SPRITE_ORCHID_7, SPRITE_ORCHID_6, SPRITE_ORCHID_5, SPRITE_ORCHID_4, SPRITE_ORCHID_3, SPRITE_ORCHID_2,   },  },
    };

    // Query the orchid sprite's terminating graphics.

    Folio::Core::Game::SpriteGraphicAttributesList  spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<ORCHID_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       g_resourceGraphicsCache,
                                                                                                       OWNER_ID_ORCHID_SPRITE,
                                                                                                       DRAWING_ELEMENT_ORCHID_SPRITE,
                                                                                                       orchidSpriteColour,
                                                                                                       s_terminatingSpriteGraphicCharacteristics,
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


FolioStatus OrchidSprite::ChangeOrchidSpriteColour ()
{
    // Get the orchid sprite's colour.

    m_orchidSpriteColour = GetOrchidSpriteColour ();

    // Change the orchid sprite's colour.

    return (ChangeSpriteInkColour (Folio::Core::Game::ZxSpectrum::MapInkColour (m_orchidSpriteColour)));
} // Endproc.


void    OrchidSprite::SetOrchidSpriteGrowing ()
{
    // Set the orchid sprite's direction.

    SetDirection (Folio::Core::Game::N);

    // The orchid sprite is initialising.

    SetState (STATE_INITIALISE_RQD);
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteGrowing () const
{
    return ((m_direction == Folio::Core::Game::N) && (m_state != STATE_STATIC));
} // Endproc.


void    OrchidSprite::SetOrchidSpriteGrown ()
{
    // Set the orchid sprite's direction.

    SetDirection (Folio::Core::Game::N);

    // The orchid sprite is static.

    SetState (STATE_STATIC);
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteGrown () const
{
    return ((m_direction == Folio::Core::Game::N) && (m_state == STATE_STATIC));
} // Endproc.


void    OrchidSprite::SetOrchidSpriteShrinking ()
{
    // Set the orchid sprite's direction.

    SetDirection (Folio::Core::Game::S);

    // The orchid sprite is terminating.

    SetState (STATE_TERMINATE_RQD);
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteShrinking () const
{
    return ((m_direction == Folio::Core::Game::S) && (m_state != STATE_STATIC));
} // Endproc.


void    OrchidSprite::SetOrchidSpriteShrunk ()
{
    // Set the orchid sprite's direction.

    SetDirection (Folio::Core::Game::S);

    // The orchid sprite is static.

    SetState (STATE_STATIC);

    // Change the orchid sprite colour.

    ChangeOrchidSpriteColour ();

    // The orchid sprite has no longer infected the player.

    m_infectedPlayer = false;
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteShrunk () const
{
    return ((m_direction == Folio::Core::Game::S) && (m_state == STATE_STATIC));
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteInfectious () const
{
    // The orchid sprite is infectious if it is has not already infected the 
    // player, and it is grown.

    return (!m_infectedPlayer && IsOrchidSpriteGrown ());
} // Endproc.


OrchidSprite::ORCHID_SPRITE_TYPE    OrchidSprite::GetOrchidSpriteType (Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour)
{
    // The orchid sprite's type is based on it's colour.

    switch (GET_INK_COLOUR(orchidSpriteColour))
    {
    case Folio::Core::Game::ZxSpectrum::RED:
        return (IMMUNITY);

    case Folio::Core::Game::ZxSpectrum::MAGENTA:
        return (CONFUSION);

    case Folio::Core::Game::ZxSpectrum::CYAN:
        return (SPEED);

    case Folio::Core::Game::ZxSpectrum::YELLOW:
        return (SICKNESS);

    case Folio::Core::Game::ZxSpectrum::WHITE:
    default:
        return (CURE);
    } // Endswitch.

} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   OrchidSprite::GetOrchidSpriteColour ()
{
    // Orchid sprite colours.
    static  const   std::vector<Folio::Core::Game::ZxSpectrum::COLOUR>  s_orchidSpriteColours = 
    {
        Folio::Core::Game::ZxSpectrum::RED, 
        Folio::Core::Game::ZxSpectrum::MAGENTA, 
        Folio::Core::Game::ZxSpectrum::CYAN, 
        Folio::Core::Game::ZxSpectrum::YELLOW, 
        Folio::Core::Game::ZxSpectrum::WHITE,
    };

    return (Folio::Core::Game::ZxSpectrum::BRIGHT | SET_INK_COLOUR(s_orchidSpriteColours [Folio::Core::Util::Random::GetRandomNumber (s_orchidSpriteColours.size () - 1)]));
} // Endproc.


FolioStatus CreateOrchidSpriteDrawingElement (FolioHandle                   dcHandle,
                                              OrchidSpriteDrawingElement    &orchidSpriteDrawingElement)
{
    // Before creating an orchid sprite drawing element, make sure that the 
    // current orchid sprite drawing element is destroyed.

    orchidSpriteDrawingElement.Destroy ();

    // Create an orchid sprite.

    OrchidSpritePtr orchidSprite(new OrchidSpritePtr::element_type);

    FolioStatus status = orchidSprite->Create (dcHandle);

    if (status == ERR_SUCCESS)
    {
        // Create an orchid sprite drawing element.
    
        status = orchidSpriteDrawingElement.Create (DRAWING_ELEMENT_ORCHID_SPRITE, 
                                                    orchidSprite,
                                                    orchidSprite->GetCollisionGridCellValue ());
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InitialiseScreenOrchidSprite (CollisionGrid &collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the orchid sprite drawing element created and does the current screen
    // support an orchid sprite?

    if (g_orchidSpriteDrawingElement.IsCreated () && 
        g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Get the orchid sprite.

        OrchidSpritePtr &orchidSprite(g_orchidSpriteDrawingElement.m_sprite);

        // Set the orchid sprite's screen position.

        status = orchidSprite->SetScreenBottomLeft (g_screenMap.GetScreenOrchidSpriteScreenXLeft (), 
                                                    g_screenMap.GetScreenOrchidSpriteScreenYBottom ());

        if (status == ERR_SUCCESS)
        {
            // Add the orchid sprite to the current screen's collision grid.

            status = collisionGrid.AddCellElement (*(g_orchidSpriteDrawingElement.m_drawingElement));
            
            if (status == ERR_SUCCESS)
            {
                // Start the orchid sprite's transition tick count.

                orchidSprite->StartTransitionTickCount ();
            } // Endif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus UpdateScreenOrchidSprite ()
{
    FolioStatus status = ERR_SUCCESS;
    
    // Is the orchid sprite drawing element created and does the current screen
    // support an orchid sprite?

    if (g_orchidSpriteDrawingElement.IsCreated () && 
        g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Get the orchid sprite.

        OrchidSpritePtr &orchidSprite(g_orchidSpriteDrawingElement.m_sprite);

        // Start the orchid sprite's transition tick count.

        orchidSprite->StartTransitionTickCount ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus CheckScreenOrchidSprite (Gdiplus::Graphics &graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the orchid sprite drawing element created and does the current screen
    // support an orchid sprite?

    if (g_orchidSpriteDrawingElement.IsCreated () && 
        g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Get the orchid sprite.

        OrchidSpritePtr &orchidSprite(g_orchidSpriteDrawingElement.m_sprite);

        // Check the orchid sprite's transition.

        orchidSprite->CheckTransition ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus StoreScreenOrchidSpriteBackground (Gdiplus::Graphics &graphics)
{
    return (g_orchidSpriteDrawingElement.StoreSpriteBackground (graphics));
} // Endproc.


FolioStatus RestoreScreenOrchidSpriteBackground (Gdiplus::Graphics &graphics)
{
    return (g_orchidSpriteDrawingElement.RestoreSpriteBackground (graphics));
} // Endproc.


FolioStatus DrawScreenOrchidSprite (Gdiplus::Graphics &graphics)
{
    return (g_orchidSpriteDrawingElement.DrawSprite (graphics));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
