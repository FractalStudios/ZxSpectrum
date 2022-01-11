// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElementIds.h"
#include    "Globals.h"
#include    "OrchidSprite.h"
#include    "ResourceOwnerIds.h"
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
    m_infectious(false)
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


void    OrchidSprite::EnteredNewScreen ()
{
    // Is this the first screen we've entered?

    if (!m_transitionTickCount)
    {
        // Yes. Start the transition tick count at which time the orchid sprite 
        // should start to grow.

        StartTransitionTickCount (true);
    } // Endif.

    // Is the orchid sprite grown?

    else
    if (IsOrchidSpriteGrown ())
    {
        // Yes. 
        
        switch (Folio::Core::Util::Random::GetRandomNumber (3))
        {
        case 0:
            // Leave the orchid sprite grown but change its colour.

            ChangeOrchidSpriteColour ();

            // Start the transition tick count at which time the orchid sprite 
            // should start to shrink.

            StartTransitionTickCount (false);
            break;

        case 1:
            // The orchid sprite should shrink.

            SetOrchidSpriteShrinking ();
            break;

        default:
            // The orchid sprite is shrunk.

            SetOrchidSpriteShrunk ();
            break;
        } // Endswitch.

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
        break;

    case STATE_TERMINATED:
        // The orchid sprite is terminated. This means that the orchid sprite 
        // has now shrunk.

        SetOrchidSpriteShrunk ();
        break;

    case STATE_STATIC:
        // The orchid sprite is static. This means that the orchid sprite 
        // has either grown or shrunk.

        // Is the orchid sprite transition complete?

        if (IsTransitionComplete ())
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

        // Is the orchid sprite grown and not infectious?

        else
        if (IsOrchidSpriteGrown () && !m_infectious)
        {
            // Yes. Now that it has grown, the orchid sprite is infectious.

            m_infectious = true;
        } // Endelseif.
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


FolioStatus OrchidSprite::HandlePlayerCollision (ORCHID_SPRITE_TYPE&                    orchidSpriteType,
                                                 Folio::Core::Game::ZxSpectrum::COLOUR& orchidSpriteColour)
{
    orchidSpriteType    = ORCHID_TYPE_UNDEFINED; // Initialise!
    orchidSpriteColour  = Folio::Core::Game::ZxSpectrum::UNDEFINED;

    FolioStatus status = ERR_SUCCESS;

    // The player has collided with an orchide sprite.

    // Is the orchid sprite infectious?

    if (m_infectious)
    {
        // Yes. Get the orchid sprite type.

        orchidSpriteType = GetOrchidSpriteType (m_orchidSpriteColour);
            
        // Note the orchid sprite's colour.

        orchidSpriteColour = m_orchidSpriteColour;
            
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
    // Whilst it is growing, the orchid sprite is not infectious.

    m_infectious = false;

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

    // Set the transition tick count at which time the orchid sprite should 
    // start to shrink.

    StartTransitionTickCount (false);
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteGrown () const
{
    return ((m_direction == Folio::Core::Game::N) && (m_state == STATE_STATIC));
} // Endproc.


void    OrchidSprite::SetOrchidSpriteShrinking ()
{
    // Now that it is shrinking, the orchid sprite is not infectious.

    m_infectious = false;

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
    // Now that it has shrunk, the orchid sprite is not infectious.

    m_infectious = false;

    // Set the orchid sprite's direction.

    SetDirection (Folio::Core::Game::S);

    // The orchid sprite is static.

    SetState (STATE_STATIC);

    // Change the orchid sprite colour.

    ChangeOrchidSpriteColour ();

    // Set the transition tick count at which time the orchid sprite should 
    // start to grow.

    StartTransitionTickCount (true);
} // Endproc.


bool    OrchidSprite::IsOrchidSpriteShrunk () const
{
    return ((m_direction == Folio::Core::Game::S) && (m_state == STATE_STATIC));
} // Endproc.


void    OrchidSprite::StartTransitionTickCount (bool grow)
{
    if (grow)
    {
        // Set the transition tick count at which time the orchid sprite should 
        // start to grow.

        m_transitionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                1000 * Folio::Core::Util::Random::GetRandomNumber (MIN_GROW_SECONDS, MAX_GROW_SECONDS);
    } // Endif.

    else
    {
        // Set the transition tick count at which time the orchid sprite should 
        // start to shrink.

        m_transitionTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount () + 
                                1000 * Folio::Core::Util::Random::GetRandomNumber (MIN_SHRINK_SECONDS, MAX_SHRINK_SECONDS);
    } // Endelse.

} // Endproc.


bool    OrchidSprite::IsTransitionComplete () const
{
    return (Folio::Core::Util::DateTime::GetCurrentTickCount () >= m_transitionTickCount);
} // Endproc.


Int32   OrchidSprite::CalculateCollisionHeight (Int32 bitmapScreenHeight) const
{ 
    return (bitmapScreenHeight / 2);
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


FolioStatus CreateOrchidSpriteDrawingElement (FolioHandle dcHandle)
{
    // Before creating the orchid sprite drawing element, make sure that the 
    // current orchid sprite drawing element is destroyed.

    g_orchidSpriteDrawingElement.Destroy ();

    // Create an orchid sprite.

    OrchidSpritePtr orchidSprite(new OrchidSpritePtr::element_type);

    FolioStatus status = orchidSprite->Create (dcHandle);

    if (status == ERR_SUCCESS)
    {
        // Create the orchid sprite drawing element.
    
        status = g_orchidSpriteDrawingElement.Create (DRAWING_ELEMENT_ORCHID_SPRITE, 
                                                      orchidSprite);
    } // Endif.

    if (status != ERR_SUCCESS)
    {
        g_orchidSpriteDrawingElement.Destroy ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InitialiseScreenOrchidSprite (CollisionGrid& collisionGrid)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Set the orchid sprite's screen position.

        status = g_orchidSpriteDrawingElement.SetScreenTopLeft (g_screenMap.GetScreenOrchidSpriteScreenXLeft (), 
                                                                g_screenMap.GetScreenOrchidSpriteScreenYBottom (),
                                                                false);

        if (status == ERR_SUCCESS)
        {
            // Add the orchid sprite to the current screen's collision grid.

            status = collisionGrid.AddCellElement (Folio::Core::Game::ACollisionGrid::CellElement (*(g_orchidSpriteDrawingElement.m_drawingElement)));
            
            if (status == ERR_SUCCESS)
            {
                // Entered a new screen.

                g_orchidSpriteDrawingElement.m_sprite->EnteredNewScreen ();
            } // Endif.

        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus UpdateScreenOrchidSprite ()
{
    FolioStatus status = ERR_SUCCESS;
    
    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Set the orchid sprite's screen position.

        status = g_orchidSpriteDrawingElement.SetScreenTopLeft (g_screenMap.GetScreenOrchidSpriteScreenXLeft (), 
                                                                g_screenMap.GetScreenOrchidSpriteScreenYBottom (),
                                                                false);

        if (status == ERR_SUCCESS)
        {
            // Entered a new screen.

            g_orchidSpriteDrawingElement.m_sprite->EnteredNewScreen ();
        } // Endif.
    
    } // Endif.

    return (status);
} // Endproc.


FolioStatus CheckScreenOrchidSprite (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        // Yes. Check the orchid sprite's transition.

        g_orchidSpriteDrawingElement.m_sprite->CheckTransition ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus StoreScreenOrchidSpriteBackground (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        status = g_orchidSpriteDrawingElement.StoreSpriteBackground (graphics);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus RestoreScreenOrchidSpriteBackground (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        status = g_orchidSpriteDrawingElement.RestoreSpriteBackground (graphics);
    } // Endif.

    return (status);
} // Endproc.


FolioStatus DrawScreenOrchidSprite (Gdiplus::Graphics& graphics)
{
    FolioStatus status = ERR_SUCCESS;

    // Does the current screen support an orchid sprite?

    if (g_screenMap.IsScreenOrchidSprite ())
    {
        status = g_orchidSpriteDrawingElement.DrawSprite (graphics);
    } // Endif.

    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
