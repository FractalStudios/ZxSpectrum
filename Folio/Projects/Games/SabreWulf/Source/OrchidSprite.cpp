// "Home-made" includes.
#include    "StdAfx.h"
#include    "OrchidSprite.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Orchid sprite graphic attributes.
static  const   Folio::Core::Game::SpriteGraphicsAttributesList<ORCHID_SPRITE_ID, SPRITE_ID>    g_orchidSpriteGraphicAttributes =
{
//      m_spriteId      m_direction                             spriteGraphicIdsList
    {   ORCHID_SPRITE,  Folio::Core::Game::AStaticSprite::N,    {   SPRITE_ORCHID_8,    },  },  
    {   ORCHID_SPRITE,  Folio::Core::Game::AStaticSprite::S,    {   SPRITE_ORCHID_1,    },  },  
};


OrchidSprite::OrchidSprite ()
:   m_orchidSpriteColour(Folio::Core::Game::ZxSpectrum::UNDEFINED),
    m_transitionTickCount(0),
    m_colourChangeIndex(0),
    m_infectedPlayer(false)
{
} // Endproc.


OrchidSprite::~OrchidSprite ()
{
} // Endproc.


FolioStatus OrchidSprite::Create (FolioHandle                   dcHandle,
                                  const SpriteGraphicsMapPtr    &spriteGraphicsMap)
{
    // Get the orchid sprite's colour.

    Folio::Core::Game::ZxSpectrum::COLOUR   orchidSpriteColour = GetOrchidSpriteColour ();

    // Query the orchid sprite's graphic attributes.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<ORCHID_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                       ORCHID_SPRITE,
                                                                                                       *spriteGraphicsMap,
                                                                                                       orchidSpriteColour,
                                                                                                       g_orchidSpriteGraphicAttributes,
                                                                                                       spriteGraphicAttributesList);

    if (status == ERROR_SUCCESS)
    {
        // Create the orchid sprite.

        status = Folio::Core::Game::AStaticSprite::Create (dcHandle,
                                                           spriteGraphicAttributesList,
                                                           INITIAL_SCREEN_X_LEFT,
                                                           INITIAL_SCREEN_Y_TOP,
                                                           Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                           Folio::Core::Game::ZxSpectrum::MapInkColour (orchidSpriteColour),
                                                           S);

        if (status == ERROR_SUCCESS)
        {
            // Set the orchid sprite's initialising mode.
            
            status = SetInitialisingMode (dcHandle, 
                                          spriteGraphicsMap, 
                                          orchidSpriteColour);

            if (status == ERROR_SUCCESS)
            {
                // Set the orchid sprite's terminating mode.
                
                status = SetTerminatingMode (dcHandle, 
                                             spriteGraphicsMap, 
                                             orchidSpriteColour); 

                if (status == ERROR_SUCCESS)
                {
                    // Orchid sprite is static.

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
    // Calculate the screen Y top.

    Int32   screenYTop = Folio::Core::Game::ZxSpectrum::CalculateScreenYTop (screenYBottom, 
                                                                             m_screenWidth,
                                                                             m_screenHeight);

    // Set the orchid sprite's screen position.

    return (Folio::Core::Game::AStaticSprite::SetScreenTopLeft (screenXLeft, screenYTop));
} // Endproc.


void    OrchidSprite::StartTransitionTickCount (bool newScreen)
{
    if (newScreen &&
       ((m_state != STATE_STATIC) ||
        (m_direction != S)))
    {
        if ((m_state == STATE_STATIC)   && 
            (m_direction == N)          && 
            (Folio::Core::Util::Random::GetRandomNumber (4) == 0))
        {
            // Change the orchid sprite colour.

            ChangeOrchidSpriteColour ();
        } // Endif.

        else
        {
            // Terminate the orchid sprite.

            SetState (STATE_TERMINATE_RQD);
        } // Endelse.

    } // Endif.

    else
    if ((m_state == STATE_STATIC) && (m_direction == N))
    {
        m_transitionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                1000 * Folio::Core::Util::Random::GetRandomNumber (1, 4);
    } // Endelseif.

    else
    {
        m_transitionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                1000 * Folio::Core::Util::Random::GetRandomNumber (5, 10);
    } // Endelse.

} // Endproc.


void    OrchidSprite::CheckTransition ()
{
    switch (m_state)
    {
    case STATE_INITIALISED:
        // The orchid sprite is initialised.

        // The orchid sprite is now static.

        SetState (STATE_STATIC);

        UpdateDirection (N);

        // Start the transition tick count.

        StartTransitionTickCount (false);   // Not a new screen.
        break;

    case STATE_TERMINATED:
        // The orchid sprite is terminated.

        // The orchid sprite is now static.

        SetState (STATE_STATIC);

        UpdateDirection (S);

        // Change the orchid sprite colour.

        ChangeOrchidSpriteColour ();

        // The orchid sprite has no longer infected the player.

        m_infectedPlayer = false;

        // Start the transition tick count.

        StartTransitionTickCount (false);   // Not a new screen.
        break;

    case STATE_STATIC:
        // Should the orchid sprite transition?

        if (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_transitionTickCount)
        {
            // Yes. Depending on direction, initialise or terminate the orchid sprite.

            SetState ((m_direction == S) ? STATE_INITIALISE_RQD : STATE_TERMINATE_RQD);
        } // Endif.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


FolioStatus OrchidSprite::HandlePlayerCollision (PlayerSpritePtr &playerSprite)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the orchid sprite infectious?

    if (IsOrchidSpriteInfectious ())
    {
        switch (GetOrchidType (m_orchidSpriteColour))
        {
        case IMMUNITY:
            playerSprite->SetTemporaryImmunity (m_orchidSpriteColour);
            break;

        case CONFUSION:
            playerSprite->SetTemporaryConfusion (m_orchidSpriteColour);
            break;
    
        case SPEED: 
            playerSprite->SetTemporarySpeed (m_orchidSpriteColour);
            break;
    
        case SICKNESS:
            playerSprite->SetTemporarySickness (m_orchidSpriteColour);
            break;
    
        case CURE:
            playerSprite->ResetTemporaryState ();
            break;
        } // Endswitch.
            
        // The orchid sprite has infected the player.

        m_infectedPlayer = true;

        // Terminate the orchid sprite.

        SetState (STATE_TERMINATE_RQD);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus OrchidSprite::SetInitialisingMode (FolioHandle                           dcHandle,
                                               const SpriteGraphicsMapPtr            &spriteGraphicsMap,
                                               Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Orchid sprite initialising sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<ORCHID_SPRITE_ID, SPRITE_ID> s_initialisingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
        {   ORCHID_SPRITE_UNDEFINED,    Folio::Core::Game::APlayerSprite::ALL_DIRECTIONS,   {   SPRITE_ORCHID_2, SPRITE_ORCHID_3, SPRITE_ORCHID_4, SPRITE_ORCHID_5, SPRITE_ORCHID_6, SPRITE_ORCHID_7,   },  },
    };

    // Query the orchid sprite's initialising graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<ORCHID_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      *spriteGraphicsMap,
                                                                                                      orchidSpriteColour,
                                                                                                      s_initialisingSpriteGraphicAttributes,
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
                                              const SpriteGraphicsMapPtr            &spriteGraphicsMap,
                                              Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour)
{
    static  const   UInt32  MAX_SEQUENCE_COUNT = 1;

    // Orchid sprite terminating sprite attributes.
    static  const   Folio::Core::Game::SpriteGraphicsAttributesList<ORCHID_SPRITE_ID, SPRITE_ID> s_terminatingSpriteGraphicAttributes = 
    {
    //      m_spriteId                  m_direction                                         m_spriteGraphicIdsList
        {   ORCHID_SPRITE_UNDEFINED,    Folio::Core::Game::APlayerSprite::ALL_DIRECTIONS,   {   SPRITE_ORCHID_7, SPRITE_ORCHID_6, SPRITE_ORCHID_5, SPRITE_ORCHID_4, SPRITE_ORCHID_3, SPRITE_ORCHID_2,   },  },
    };

    // Query the orchid sprite's terminating graphics.

    SpriteGraphicAttributesList    spriteGraphicAttributesList;

    FolioStatus status = Folio::Core::Game::QuerySpriteGraphicAttributes<ORCHID_SPRITE_ID, SPRITE_ID> (dcHandle,
                                                                                                      *spriteGraphicsMap,
                                                                                                      orchidSpriteColour,
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


OrchidSprite::ORCHID_TYPE   OrchidSprite::GetOrchidType (Folio::Core::Game::ZxSpectrum::COLOUR orchidSpriteColour)
{
    // The orchid's type is based on it's colour.

    switch (GET_INK_COLOUR (orchidSpriteColour))
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


FolioStatus OrchidSprite::ChangeOrchidSpriteColour ()
{
    // Get the orchid sprite's colour.

    m_orchidSpriteColour = GetOrchidSpriteColour ();

    // Change the orchid sprite's colour.

    return (ChangeSpriteInkColour (Folio::Core::Game::ZxSpectrum::MapInkColour (m_orchidSpriteColour)));
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteInfectious () const
{
    switch (m_state)
    {
    case STATE_STATIC:
        // Orchid is infectious if it is has not already infected the 
        // player, and it is fully grown.

        return (!m_infectedPlayer && (m_direction == N));
        break;

    default:
        return (false);
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

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
