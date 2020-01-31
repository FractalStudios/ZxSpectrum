// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Font.h"
#include    "Globals.h"
#include    "InformationPanel.h"
#include    "ResourceOwnerId.h"
#include    "Ultimate.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Information panel item attributes.
typedef Folio::Core::Game::ItemAttributes<INFORMATION_PANEL_ITEM_ID>    InformationPanelItemAttributes;

// Information panel item attributes table.
static  const   InformationPanelItemAttributes  g_informationPanelAttributesTable [] =
{
//      m_itemId                                    m_bitmapResourceId                  m_screenXLeft   m_screenYTop    m_colour
    {   INFORMATION_PANEL_ITEM_SCROLL,              IDB_BITMAP_SCROLL,                   0,               0,            Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       },
    {   INFORMATION_PANEL_ITEM_SCROLL_SEAL,         IDB_BITMAP_SCROLL_SEAL,              8,             144,            Folio::Core::Game::ZxSpectrum::UNDEFINED,                                       },
    {   INFORMATION_PANEL_ITEM_TIME_TEXT,           0,                                  16,              56,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, },
    {   INFORMATION_PANEL_ITEM_TIME_VALUE,          0,                                   8,              64,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   INFORMATION_PANEL_ITEM_SCORE_TEXT,          0,                                  12,              72,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    },
    {   INFORMATION_PANEL_ITEM_SCORE_VALUE,         0,                                   8,              80,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   INFORMATION_PANEL_ITEM_TURKEY_CARCASS,      IDB_BITMAP_TURKEY_CARCASS,           8,              90,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   INFORMATION_PANEL_ITEM_TURKEY,              IDB_BITMAP_FULL_TURKEY,              8,              90,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  },
    {   INFORMATION_PANEL_ITEM_PLAYER_LIFE_1,       IDB_BITMAP_KNIGHT_WALKING_LEFT_1,    8,             122,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   INFORMATION_PANEL_ITEM_PLAYER_LIFE_2,       IDB_BITMAP_KNIGHT_WALKING_LEFT_1,   24,             122,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
    {   INFORMATION_PANEL_ITEM_PLAYER_LIFE_3,       IDB_BITMAP_KNIGHT_WALKING_LEFT_1,   40,             122,            Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   },
};


// Information panel static members.
Folio::Core::Util::Sound::SoundSample   InformationPanel::m_startingSoundSample(Ultimate::CreateSoundSample (0x80, 0x60));      // Starting sound sample.
Folio::Core::Util::Sound::SoundSample   InformationPanel::m_collectedItemSoundSample(Ultimate::CreateSoundSample (0x40, 0x40)); // Collected item sound sample.
Folio::Core::Util::Sound::SoundSample   InformationPanel::m_droppedItemSoundSample(Ultimate::CreateSoundSample (0x20, 0x80));   // Dropped item sound sample.

bool    InformationPanel::m_playIncrementMainPlayerHealthSound                  = false;    // Indicates if the increment main player health sound should be played.
UInt32  InformationPanel::m_currentIncrementMainPlayerHealthSoundSampleIndex    = 0;        // The current increment main player health sound sample index.
Folio::Core::Util::Sound::SoundSamplesList  InformationPanel::m_incrementMainPlayerHealthSoundSamplesList;  // The increment main player health sound samples.

bool    InformationPanel::m_playDecrementMainPlayerHealthSound                  = false;    // Indicates if the decrement main player health sound should be played.
UInt32  InformationPanel::m_currentDecrementMainPlayerHealthSoundSampleIndex    = 0;        // The current decrement main player health sound sample index.
Folio::Core::Util::Sound::SoundSamplesList  InformationPanel::m_decrementMainPlayerHealthSoundSamplesList;  // The decrement main player health sound samples.

InformationPanel::InformationPanel ()
:   m_canvas(0),
    m_startingCounter(0),
    m_previousScoreFrameTickCount(0),
    m_previousTimeFrameTickCount(0),
    m_timeInSeconds(0),
    m_score(0),
    m_health(MAX_HEALTH),
    m_lives(MAX_NUM_LIVES),
    m_totalNumRooms(0),
    m_numRoomsVisited(0),
    m_invertScoreColours(false)
{
} // Endproc.


InformationPanel::~InformationPanel ()
{
    // Release the information panel's resource graphics.

    ReleaseResourceGraphics ();
} // Endproc.


FolioStatus InformationPanel::Create (Folio::Core::Applet::Canvas   &canvas,
                                      UInt32                        totalNumRooms,
                                      UInt16                        mainPlayerBitmapResourceId)
{
    // Note the information panel attributes.

    m_canvas                        = &(canvas);
    m_startingCounter               = 0;
    m_previousScoreFrameTickCount   = 0;
    m_previousTimeFrameTickCount    = 0;
    m_timeInSeconds                 = 0;
    m_score                         = 0;
    m_health                        = MAX_HEALTH;
    m_lives                         = MAX_NUM_LIVES;
    m_totalNumRooms                 = totalNumRooms;
    m_numRoomsVisited               = 0;
    m_invertScoreColours            = false;

    // Release the information panel's resource graphics.

    ReleaseResourceGraphics ();

    m_heldItemsList.clear ();   // Initialise!

    // Create the information panel sound samples.

    CreateInformationPanelSoundSamples ();

    // Build the information panel items.

    return (BuildItems (canvas.GetCanvasDcHandle (), 
                        canvas.GetAppletInstanceHandle (), 
                        mainPlayerBitmapResourceId));
} // Endproc.


FolioStatus InformationPanel::QueryDrawingElements (FolioHandle                             dcHandle,
                                                    Folio::Core::Game::ZxSpectrum::COLOUR   roomColour,
                                                    Folio::Core::Game::DrawingElementsList  &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Query the drawing elements of the information panel items.

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Query the information panel item's drawing elements.

        Folio::Core::Game::DrawingElementsList  itemDrawingElementsList;

        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case INFORMATION_PANEL_ITEM_SCROLL:
        case INFORMATION_PANEL_ITEM_SCROLL_SEAL:
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

                // Query the information panel item's drawing elements.

                status = item->QueryDrawingElements (dcHandle,
                                                     Folio::Core::Game::ZxSpectrum::MapInkColour (GetScrollItemColour (itemId, roomColour)), 
                                                     itemDrawingElementsList);
            } // Endscope.
            break;
        
        case INFORMATION_PANEL_ITEM_TIME_TEXT:
        case INFORMATION_PANEL_ITEM_TIME_VALUE:
        case INFORMATION_PANEL_ITEM_SCORE_TEXT:
        case INFORMATION_PANEL_ITEM_SCORE_VALUE:
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Get the information panel item's drawing elements.
                
                itemDrawingElementsList = item->GetDrawingElementsList ();
            } // Endscope.
            break;

        case INFORMATION_PANEL_ITEM_HELD_ITEM_1:
        case INFORMATION_PANEL_ITEM_HELD_ITEM_2:
        case INFORMATION_PANEL_ITEM_HELD_ITEM_3:
        case INFORMATION_PANEL_ITEM_TURKEY_CARCASS:
        case INFORMATION_PANEL_ITEM_TURKEY:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_1:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_2:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_3:
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

                // Get the information panel item's drawing elements.
                
                itemDrawingElementsList = item->GetDrawingElementsList ();

                if (itemId == INFORMATION_PANEL_ITEM_TURKEY)
                {
                    // Set the information panel graphic item's height.

                    SetGraphicItemHeight (*item);
                } // Endif.

            } // Endscope.
            break;
        
        default:
            break;
        } // Endswitch.

        // Add the information panel item's drawing elements to the drawing elements list.

        drawingElementsList.insert (drawingElementsList.end (), 
                                    itemDrawingElementsList.begin (),
                                    itemDrawingElementsList.end ()); 
    } // Endfor.

    if (status != ERR_SUCCESS)
    {
        drawingElementsList.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::HandleProcessFrame (bool  &isStarting,
                                                  bool  &mainPlayerIsDead)
{
    // Play the information panel sounds.

    PlayInformationPanelSounds ();

    // Get the current tick count

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    // Check time.

    FolioStatus status = CheckTime (currentTickCount, isStarting, mainPlayerIsDead);

    if (status == ERR_SUCCESS)
    {
        // Are we starting?

        if (isStarting)
        {
            // Yes. Check score.

            status = CheckScore (currentTickCount, isStarting);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::AddCollectedItem (const HeldItem  &heldItem,
                                                DroppedItem     &droppedItem)
{
    // Add the collected (held) item to the information panel.

    FolioStatus status = AddHeldItem (heldItem, droppedItem);

    if (status == ERR_SUCCESS)
    {
         // Play the collected item sound sample.

        status = Folio::Core::Util::Sound::PlaySoundSample (m_collectedItemSoundSample);
        
        // Is an item dropped?

        if ((status == ERR_SUCCESS) && droppedItem.IsPopulated ())
        {
            // Yes. Play the dropped item sound sample.

            status = Folio::Core::Util::Sound::PlaySoundSample (m_droppedItemSoundSample);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::CycleCollectedItems (DroppedItem &droppedItem)
{
    // Cycle the collected (held) items in the information panel.

    FolioStatus status = CycleHeldItems (droppedItem);

    // Is an item dropped?

    if ((status == ERR_SUCCESS) && droppedItem.IsPopulated ())
    {
        // Yes. Play the dropped item sound sample.

        status = Folio::Core::Util::Sound::PlaySoundSample (m_droppedItemSoundSample);
    } // Endif.

    return (status);
} // Endproc.


bool    InformationPanel::IsAnyCollectedItem () const
{
    return (IsAnyHeldItem ());
} // Endproc.


bool    InformationPanel::IsRedKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsGreenKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsCyanKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsYellowKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsAcgKeyCollected () const
{
    UInt32  acgKeyCount = 0;    // Initialise!

    for (HeldItemsList::const_iterator itr = m_heldItemsList.begin ();
         (itr != m_heldItemsList.end ());
         ++itr)
    {
        if (itr->IsPopulated () && 
            (itr->m_staticSprite->GetStaticSpriteId () == (STATIC_SPRITE_ACG_KEY_LEFT + acgKeyCount)))
        {
            acgKeyCount++;
        } // Endif.

        else
        {
            break;
        } // Endelse.

    } // Endfor.

    return (acgKeyCount == MAX_NUM_HELD_ITEMS);
} // Endproc.


bool    InformationPanel::IsCrucifixCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_CRUCIFIX, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsSpannerCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_SPANNER, Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN) != m_heldItemsList.end ());
} // Endproc.


FolioStatus InformationPanel::IncrementScore (UInt32 scoreIncrement)
{
    // Increment the current score.

    m_score += scoreIncrement;

    if (m_score > MAX_SCORE)
    {
        m_score = 0;
    } // Endif.

    // Update the score.

    return (Update (UPDATE_SCORE));
} // Endproc.
    

void    InformationPanel::IncrementNumRoomsVisited ()
{
    m_numRoomsVisited++;
} // Endproc.


FolioStatus InformationPanel::IncrementMainPlayerHealth (UInt32 healthIncrement,
                                                         bool   playSound)
{
    FolioStatus status = ERR_SUCCESS;

    if (m_health < MAX_HEALTH)
    {
        // Increment the main player's current health.

        m_health += healthIncrement;

        if (m_health > MAX_HEALTH)
        {
            m_health = MAX_HEALTH;
        } // Endif.

        // Update the main player's health.

        status = Update (UPDATE_HEALTH);
    } // Endif.

    if (!m_playIncrementMainPlayerHealthSound && 
        (status == ERR_SUCCESS))
    {
        // Start playing the increment main player health sound.

        m_playIncrementMainPlayerHealthSound                = true;
        m_currentIncrementMainPlayerHealthSoundSampleIndex  = 0;

        // Stop playing the decrement main player health sound.

        m_playDecrementMainPlayerHealthSound                = false;
        m_currentDecrementMainPlayerHealthSoundSampleIndex  = 0;
    } // Endif.

    return (status);
} // Endproc.
    

FolioStatus InformationPanel::DecrementMainPlayerHealth (UInt32 healthDecrement, 
                                                         bool   &mainPlayerIsDead,
                                                         bool   playSound)
{
    FolioStatus status = ERR_SUCCESS;
   
    mainPlayerIsDead = false;    // Initialise!

    if (m_health >= MIN_HEALTH)
    {
        // Decrement the main player's current health.

        m_health -= healthDecrement;

        // Is the main player dead?

        mainPlayerIsDead = (m_health < MIN_HEALTH);

        if (mainPlayerIsDead)
        {
            // Yes. 
               
            // Stop playing the increment main player health sound.

            m_playIncrementMainPlayerHealthSound                = false;
            m_currentIncrementMainPlayerHealthSoundSampleIndex  = 0;

            // Stop playing the decrement main player health sound.

            m_playDecrementMainPlayerHealthSound                = false;
            m_currentDecrementMainPlayerHealthSoundSampleIndex  = 0;
        } // Endif.

        else
        {
            // No. Update the main player's health.

            status = Update (UPDATE_HEALTH);

            if (playSound && !m_playDecrementMainPlayerHealthSound && 
                (status == ERR_SUCCESS))
            {
                // Start playing the decrement main player health sound.

                m_playDecrementMainPlayerHealthSound                = true;
                m_currentDecrementMainPlayerHealthSoundSampleIndex  = 0;

                // Stop playing the increment main player health sound.

                m_playIncrementMainPlayerHealthSound                = false;
                m_currentIncrementMainPlayerHealthSoundSampleIndex  = 0;
            } // Endif.

        } // Endelse.

    } // Endif.

    return (status);
} // Endproc.
    

FolioStatus InformationPanel::DecrementMainPlayerLife (bool &gameOver)
{
    FolioStatus status = ERR_SUCCESS;

    gameOver = false;   // Initialise!

    // Decrement the number of player's lives.

    m_lives--;

    // Update player's lives.

    switch (m_lives)
    {
    case 0:
        gameOver = true;
        break;
    case 1:
        status = Update (UPDATE_LIFE_1);
        break;
    case 2:
        status = Update (UPDATE_LIFE_2);
        break;
    case 3:
        status = Update (UPDATE_LIFE_3);
        break;
    default:
        break;
    } // Endswitch.

    if ((status == ERR_SUCCESS) && !gameOver)
    {
        // Reset the main player's health.

        status = ResetMainPlayerHealth ();
    } // Endif.

    return (status);
} // Endproc.
    

UInt32  InformationPanel::GetTimeInSeconds () const
{
    return (m_timeInSeconds);
} // Endproc.

    
UInt32  InformationPanel::GetScore () const
{
    return (m_score);
} // Endproc.

    
UInt32  InformationPanel::GetPercentageCompleted () const
{
    return (100 * m_numRoomsVisited / m_totalNumRooms);
} // Endproc.


Int32   InformationPanel::GetCurrentHealth () const
{
    return (m_health);
} // Endproc.


FolioNarrowString   InformationPanel::DescribeTime (UInt32 timeInSeconds)
{
    FolioNarrowOStringStream    str;

    str << std::setfill('0') << std::setw(3) << (timeInSeconds / 60)
        << ':' << std::setw(2) << (timeInSeconds % 60);

    return (str.str ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribeScore (UInt32 score)
{
    FolioNarrowOStringStream    str;

    str << std::setfill('0') << std::setw(6) << score;

    return (str.str ());
} // Endproc.


FolioNarrowString   InformationPanel::DescribePercentage (UInt32 percentage)
{
    FolioNarrowOStringStream    str;

    str << percentage;

    return (str.str ());
} // Endproc.


FolioStatus InformationPanel::BuildItems (FolioHandle   dcHandle, 
                                          FolioHandle   instanceHandle,
                                          UInt16        mainPlayerBitmapResourceId)
{
    FolioStatus status = ERR_SUCCESS;

    m_itemsList.clear ();   // Initialise!

    // Build the information panel items. 

    for (UInt32 index = 0; 
         (status == ERR_SUCCESS) && (index < (sizeof (g_informationPanelAttributesTable) / sizeof (InformationPanelItemAttributes)));
         ++index)
    {              
        // Build the information panel item.

        switch (g_informationPanelAttributesTable [index].m_itemId)
        {
        case INFORMATION_PANEL_ITEM_SCROLL:
        case INFORMATION_PANEL_ITEM_SCROLL_SEAL:
            {
                // Create an information panel graphic item.

                Folio::Core::Game::GraphicItemPtr    item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
                                       g_informationPanelAttributesTable [index].m_bitmapResourceId,
                                       g_informationPanelAttributesTable [index].m_itemId,
                                       g_informationPanelAttributesTable [index].m_screenXLeft + ORIGIN_X_LEFT, 
                                       g_informationPanelAttributesTable [index].m_screenYTop + ORIGIN_Y_TOP,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour (),
                                       Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR,
                                       Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR,
                                       g_informationPanelAttributesTable [index].m_itemId == INFORMATION_PANEL_ITEM_SCROLL_SEAL);   // Mask required.

                if (status == ERR_SUCCESS)
                {
                    // Store the information panel item in the information panel items list.

                    m_itemsList.push_back (item);
                } // Endif.
            
            } // Endscope.
            break;

        case INFORMATION_PANEL_ITEM_TIME_TEXT:
        case INFORMATION_PANEL_ITEM_TIME_VALUE:
        case INFORMATION_PANEL_ITEM_SCORE_TEXT:
        case INFORMATION_PANEL_ITEM_SCORE_VALUE:
            { 
                // Create an information panel text item.

                Folio::Core::Game::TextItemPtr   item(new Folio::Core::Game::TextItemPtr::element_type);
                
                status = item->Create (dcHandle,
                                       DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
                                       *GetFont (),
                                       g_informationPanelAttributesTable [index].m_itemId,
                                       g_informationPanelAttributesTable [index].m_screenXLeft + ORIGIN_X_LEFT, 
                                       g_informationPanelAttributesTable [index].m_screenYTop + ORIGIN_Y_TOP,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (g_informationPanelAttributesTable [index].m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Set the information panel item's text.

                    SetItemText (*item.get ());
            
                    // Store the information panel item in the information panel items list.

                    m_itemsList.push_back (item);
                } // Endif.
            
            } // Endscope.
            break;

        case INFORMATION_PANEL_ITEM_TURKEY_CARCASS:
        case INFORMATION_PANEL_ITEM_TURKEY:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_1:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_2:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_3:
            {
                // Need to set the bitmap resource identifer of the main player.

                UInt16  bitmapResourceId = g_informationPanelAttributesTable [index].m_bitmapResourceId;

                if ((g_informationPanelAttributesTable [index].m_itemId == INFORMATION_PANEL_ITEM_PLAYER_LIFE_1) ||
                    (g_informationPanelAttributesTable [index].m_itemId == INFORMATION_PANEL_ITEM_PLAYER_LIFE_2) ||
                    (g_informationPanelAttributesTable [index].m_itemId == INFORMATION_PANEL_ITEM_PLAYER_LIFE_3))
                {
                    bitmapResourceId = mainPlayerBitmapResourceId;
                } // Endif.

                // Create an information panel graphic item.
            
                Folio::Core::Game::GraphicItemPtr    item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
                status = item->Create (dcHandle,
                                       instanceHandle,
                                       DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
                                       bitmapResourceId,
                                       g_informationPanelAttributesTable [index].m_itemId,
                                       g_informationPanelAttributesTable [index].m_screenXLeft + ORIGIN_X_LEFT, 
                                       g_informationPanelAttributesTable [index].m_screenYTop + ORIGIN_Y_TOP,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::GetBitmapChangeColour (),
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (g_informationPanelAttributesTable [index].m_colour));

                if (status == ERR_SUCCESS)
                {
                    // Store the information panel item in the information panel items list.

                    m_itemsList.push_back (item);
                } // Endif.
            
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    return (status);
} // Endproc.


FolioStatus InformationPanel::CheckTime (UInt32 currentTickCount,
                                         bool   isStarting,
                                         bool   &mainPlayerIsDead)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_previousTimeFrameTickCount)
    {
        m_previousTimeFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
    } // Endif.

    else
    if (currentTickCount >= (m_previousTimeFrameTickCount + 1000))
    {
        // Increment the time in seconds.

        status = IncrementTimeInSeconds (currentTickCount, isStarting, mainPlayerIsDead);

        if (status == ERR_SUCCESS)
        {
            // Note the previous time frame tick count.

            m_previousTimeFrameTickCount = currentTickCount;
        } // Endif.

    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::CheckScore (UInt32    currentTickCount, 
                                          bool      &isStarting)
{                                                            
    FolioStatus status = ERR_SUCCESS;

    // Have we initialised the starting counter?

    if (!m_startingCounter)
    {
        // No. Initialise the starting counter.

        m_startingCounter = 1;

        // Note the previous score frame tick count.

        m_previousScoreFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
    } // Endif.

    // Should we update (flash) the score?

    else
    if (currentTickCount >= (m_previousScoreFrameTickCount + Folio::Core::Game::ZxSpectrum::FLASH_MILLISECONDS))
    {
        // Yes. Update the information panel.

        status = Update (UPDATE_SCORE_COLOURS);

        if (status == ERR_SUCCESS)
        {
            // Play the starting sound sample.

            status = Folio::Core::Util::Sound::PlaySoundSample (m_startingSoundSample, 
                                                                false); // Play synchronously.

            if (status == ERR_SUCCESS)
            {
                // Are we still starting?

                if (++m_startingCounter >= 7)
                {
                    // No. We are no longer starting.

                    isStarting = false;

                    m_startingCounter = 0;   // Reset starting counter.

                    // Reset the information panel.

                    status = Reset ();
                } // Endif.
        
                else
                {
                    // Yes. Note the previous score frame tick count.

                    m_previousScoreFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
                } // Endelse.

            } // Endif.

        } // Endif.

    } // Endelseif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::IncrementTimeInSeconds (UInt32    currentTickCount,
                                                      bool      isStarting,
                                                      bool      &mainPlayerIsDead)
{
    // Increment the time in seconds.

    m_timeInSeconds++;

    if (m_timeInSeconds > MAX_TIME_IN_SECONDS)
    {   
        m_timeInSeconds = 0;
    } // Endif.

    // We periodically reduce the main player's health.

    if (!isStarting && (m_timeInSeconds % PLAYER_HEALTH_TIME_DECREMENT) == 0)
    {
        DecrementMainPlayerHealth (PLAYER_HEALTH_TIME_DECREMENT, mainPlayerIsDead, false);
    } // Endif.

    // Update the time.

    return (Update (UPDATE_TIME));
} // Endproc.
    

FolioStatus InformationPanel::ResetMainPlayerHealth ()
{
    // Reset the main player's current health.

    m_health = MAX_HEALTH;

    // Update the main player's health.

    return (Update (UPDATE_HEALTH));
} // Endproc.


Int32   InformationPanel::GetLossOfHealth () const
{
    return ((m_health >= MIN_HEALTH) ? MAX_HEALTH - m_health : m_health);
} // Endproc.


FolioStatus InformationPanel::Update (UPDATE update)
{
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Update the information panel items (depending on the type of update required).

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case INFORMATION_PANEL_ITEM_HELD_ITEM_1:
        case INFORMATION_PANEL_ITEM_HELD_ITEM_2:
        case INFORMATION_PANEL_ITEM_HELD_ITEM_3:
            if (update == UPDATE_HELD_ITEMS)          
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));
 
                // Update the held item.

                status = UpdateHeldItem (*item);

                if (status == ERR_SUCCESS)
                {
                    // Draw the held item.

                    status = item->Draw (*graphics);

                    redrawCanvas = true;
                } // Endif.

                finished = (itemId == m_heldItemsList.front ().m_itemId);
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_TIME_VALUE:
            if (update == UPDATE_TIME)
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Set the information panel text item's text.

                SetItemText (*item);

                // Draw the information panel text item.

                status = item->Draw (*graphics);

                redrawCanvas    = true;
                finished        = true;
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_SCORE_VALUE:
            if (update == UPDATE_SCORE)
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Set the information panel text item's text.

                SetItemText (*item);

                // Draw the information panel text item.

                status = item->Draw (*graphics);

                redrawCanvas    = true;
                finished        = true;
            } // Endif.

            else
            if (update == UPDATE_SCORE_COLOURS)
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Update the information panel text item.

                m_invertScoreColours = !m_invertScoreColours;

                status = UpdateTextItem (*item,
                                         m_invertScoreColours,
                                         *graphics, 
                                         redrawCanvas);

                finished = true;
            } // Endelse.
            break;

        case INFORMATION_PANEL_ITEM_TURKEY_CARCASS:
            if (update == UPDATE_HEALTH)
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

                // Draw the information panel graphic item.

                status = item->Draw (*graphics);

                redrawCanvas = true;
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_TURKEY:
            if (update == UPDATE_HEALTH)
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

                // Set the information panel graphic item's height.

                if (SetGraphicItemHeight (*item))
                {
                    // Draw the information panel graphic item.

                    status = item->Draw (*graphics);
                    
                    redrawCanvas = true;
                } // Endif.

                finished = true;
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_1:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_2:
        case INFORMATION_PANEL_ITEM_PLAYER_LIFE_3:
            if ((itemId - INFORMATION_PANEL_ITEM_PLAYER_LIFE_1) == (update - UPDATE_LIFE_1))
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

                // Clear the information panel graphic item.

                status = item->GetGdiBitmap ()->Clear ();

                if (status == ERR_SUCCESS)
                {
                    // Draw the information panel graphic item.

                    status = item->Draw (*graphics);
                    
                    redrawCanvas = true;
                } // Endif.

                finished = true;
            } // Endif.
            break;

        case INFORMATION_PANEL_ITEM_SCROLL:
        case INFORMATION_PANEL_ITEM_SCROLL_SEAL:
        case INFORMATION_PANEL_ITEM_TIME_TEXT:
        case INFORMATION_PANEL_ITEM_SCORE_TEXT:
        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::Reset ()
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas graphics.

    Gdiplus::Graphics   *graphics = m_canvas->GetCanvasGraphics ();

    // Reset the information panel items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvas    = false;

    for (Folio::Core::Game::ItemsList::iterator itr = m_itemsList.begin ();
         !finished && (status == ERR_SUCCESS) && (itr != m_itemsList.end ());
         ++itr)
    {
        // Get the information panel item's identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (itr->get ()->GetItemId ());
         
        switch (itemId)
        {
        case INFORMATION_PANEL_ITEM_SCORE_VALUE:
            {
                // Get the information panel text item.

                Folio::Core::Game::TextItemPtr  item(std::dynamic_pointer_cast<Folio::Core::Game::TextItem> (*itr));

                // Update the information panel text item.
            
                status = UpdateTextItem (*item,
                                         false, // Don't invert colours.
                                         *graphics, 
                                         redrawCanvas);

                // Finished?
            
                finished = (itemId == INFORMATION_PANEL_ITEM_TURKEY_CARCASS);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvas && (status == ERR_SUCCESS))
    {
        // The canvas should be redrawn on the next draw.

        m_canvas->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


INFORMATION_PANEL_ITEM_ID   InformationPanel::GetNextHeldItemId () const
{
    // Get the next held item information panel identifier.

    INFORMATION_PANEL_ITEM_ID   itemId = INFORMATION_PANEL_ITEM_HELD_ITEM_1;

    if (!m_heldItemsList.empty ())
    {
        itemId = static_cast<INFORMATION_PANEL_ITEM_ID> (m_heldItemsList.front ().m_itemId + 1);

        if (itemId >= (INFORMATION_PANEL_ITEM_HELD_ITEM_1 + MAX_NUM_HELD_ITEMS))
        {
            itemId = INFORMATION_PANEL_ITEM_HELD_ITEM_1;
        } // Endif.

    } // Endif.

    return (itemId);
} // Endproc.


FolioStatus InformationPanel::AddHeldItem  (const HeldItem  &heldItem,
                                            DroppedItem     &droppedItem)
{
    FolioStatus status = ERR_SUCCESS;

    // Is there a spare slot for the held item?

    if (m_heldItemsList.size () >= MAX_NUM_HELD_ITEMS)
    {
        // No. Remove the last held item.

        status = RemoveLastHeldItem (droppedItem);
    } // Endif.

    if (status == ERR_SUCCESS)
    {
        // Get the held item's information panel identifier.

        INFORMATION_PANEL_ITEM_ID   itemId = GetNextHeldItemId ();

        // Add the held item to the front of the list of held items.
        
        m_heldItemsList.push_front (heldItem);
        m_heldItemsList.front ().m_itemId = itemId; // Note its information panel identifier.

        // Gain the sprite's graphic resource.

        status = heldItem.m_staticSprite->GainResourceGraphics (OWNER_ID_INFORMATION_PANEL);

        if (status == ERR_SUCCESS)
        {
            // Create an information panel graphic item representing the held item.

            Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);

            status = item->Create (m_canvas->GetCanvasDcHandle (),
                                   heldItem.m_staticSprite->GetCurrentSpriteGraphic (),
                                   DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
                                   itemId,
                                   HELD_ITEM_ORIGIN_X_LEFT, 
                                   HELD_ITEM_ORIGIN_Y_TOP,
                                   Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE);

            if (status == ERR_SUCCESS)
            {
                // Store the information panel item in the information panel items list.

                m_itemsList.push_back (item);

                // Clear the held items rectangle in the information panel.

                status = ClearHeldItemsRectangle ();

                if (status == ERR_SUCCESS)
                {
                    // Update the held items.

                    status = Update (UPDATE_HELD_ITEMS);
                } // Endif.

            } // Endif.

        } // Endif.
  
    } // Endif.
            
    return (status);
} // Endproc.


FolioStatus InformationPanel::CycleHeldItems  (DroppedItem &droppedItem)
{
    FolioStatus status = ERR_SUCCESS;

    // Is there a spare slot for an empty held item?

    if (m_heldItemsList.size () >= MAX_NUM_HELD_ITEMS)
    {
        // No. Remove the last held item.

        status = RemoveLastHeldItem (droppedItem);
    } // Endif.

    // Are there any held items in the information panel?

    if ((status == ERR_SUCCESS) && IsAnyHeldItem ()) 
    {
        // Yes. Add an empty held item to the front of the list of held items.
        
        m_heldItemsList.push_front (HeldItem(GetNextHeldItemId ()));

        // Clear the held items rectangle in the information panel.

        status = ClearHeldItemsRectangle ();

        if (status == ERR_SUCCESS)
        {
            // Yes. Update the held items.

            status = Update (UPDATE_HELD_ITEMS);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::RemoveLastHeldItem (DroppedItem &droppedItem)
{
    FolioStatus status = ERR_SUCCESS;

    if (!m_heldItemsList.empty ())
    {
        // Note the dropped item.

        droppedItem = m_heldItemsList.back ();

        // Remove the dropped item from the list of held items.

        m_heldItemsList.pop_back ();

        // Are there any held items in the information panel?

        if (!IsAnyHeldItem ())
        {
            // No. Clear the list of held items.

            m_heldItemsList.clear ();

            // Clear the held items rectangle in the information panel.

            status = ClearHeldItemsRectangle ();
        } // Endif.

        // Is the dropped item populated?

        if ((status == ERR_SUCCESS) && droppedItem.IsPopulated ())
        {
            // Yes. Find the information panel graphic item.

            Folio::Core::Game::ItemsList::iterator  itr = FindItem (droppedItem.m_itemId);

            if (itr != m_itemsList.end ())
            {
                // Remove the information panel item from the information panel items list.

                m_itemsList.erase (itr);
            } // Endif.
        
            // Release the sprite's graphic resource.

            status = droppedItem.m_staticSprite->ReleaseResourceGraphics ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::ClearHeldItemsRectangle ()
{
    return (m_canvas->ClearCanvasRectangle (Gdiplus::Rect(HELD_ITEM_ORIGIN_X_LEFT, 
                                                          HELD_ITEM_ORIGIN_Y_TOP, 
                                                          MAX_NUM_HELD_ITEMS * MAX_HELD_ITEM_WIDTH,
                                                          MAX_HELD_ITEM_HEIGHT)));
} // Endproc.


FolioStatus InformationPanel::UpdateHeldItem (Folio::Core::Game::GraphicItemPtr::element_type &item)
{
    FolioStatus status = ERR_NOT_FOUND;

    // Find the held item.

    HeldItemsList::iterator itr = FindHeldItem (static_cast<INFORMATION_PANEL_ITEM_ID> (item.GetItemId ()));

    if (itr != m_heldItemsList.end ())
    {
        // Set the held item's position.

        status = item.SetScreenTopLeft (HELD_ITEM_ORIGIN_X_LEFT + MAX_HELD_ITEM_WIDTH * std::distance (m_heldItemsList.begin (), itr),
                                        HELD_ITEM_ORIGIN_Y_BOTTOM - item.GetScreenHeight ());
    } // Endif.

    return (status);
} // Endproc.


bool    InformationPanel::IsAnyHeldItem () const
{
    bool    isAnyHeldItem = false;  // Initialise!

    for (HeldItemsList::const_iterator itr = m_heldItemsList.begin ();
         !isAnyHeldItem && (itr != m_heldItemsList.end ());
         ++itr)
    {
        // A held item is populated.

        isAnyHeldItem = itr->IsPopulated ();
    } // Endfor.

    return (isAnyHeldItem);
} // Endproc.


InformationPanel::HeldItemsList::iterator InformationPanel::FindHeldItem (INFORMATION_PANEL_ITEM_ID itemId)
{
    return (std::find_if (m_heldItemsList.begin (), m_heldItemsList.end (), 
                          [&itemId](const HeldItem& arg) {return (arg.m_itemId == itemId);}));
} // Endproc.


InformationPanel::HeldItemsList::const_iterator InformationPanel::FindHeldItem (STATIC_SPRITE_ID                        staticSpriteId,
                                                                                Folio::Core::Game::ZxSpectrum::COLOUR   colour) const
{
    return (std::find_if (m_heldItemsList.begin (), m_heldItemsList.end (), 
                          [&staticSpriteId, colour](const HeldItem& arg) 
                          {return (arg.m_staticSprite                                               &&
                                  (arg.m_staticSprite->GetStaticSpriteId ()     == staticSpriteId)  && 
                                  (arg.m_staticSprite->GetStaticSpriteColour () == colour));}));
} // Endproc.


FolioStatus InformationPanel::UpdateTextItem (Folio::Core::Game::TextItemPtr::element_type  &item,
                                              bool                                          invertColours,
                                              Gdiplus::Graphics                             &graphics, 
                                              bool                                          &redrawCanvas)
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the text item's GDI raster text.

    Folio::Core::Graphic::GdiRasterTextPtr  gdiRasterText(item.GetGdiRasterText ());

    // Invert the text item's colours?

    if (invertColours)
    {
        // Yes. Toggle text item's inverted state.

        gdiRasterText->ToggleInverted ();

        // Draw it.

        status = gdiRasterText->Draw (item.GetScreenXLeft (), 
                                      item.GetScreenYTop (), 
                                      graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvas = true;
        } // Endif.

    } // Endif.

    // No. Is the text item inverted?

    else
    if (gdiRasterText->IsInverted ())
    {
        // Yes.

        gdiRasterText->SetNonInverted ();

        // Draw it.

        status = gdiRasterText->Draw (item.GetScreenXLeft (), 
                                      item.GetScreenYTop (), 
                                      graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvas = true;
        } // Endif.

    } // Endelseif.

    return (status);
} // Endproc.


void    InformationPanel::SetItemText (Folio::Core::Game::TextItemPtr::element_type &item)
{
    switch (item.GetItemId ())
    {
    case INFORMATION_PANEL_ITEM_TIME_TEXT:
        // Set the time text string.

        item.GetGdiRasterText ()->SetTextString ("TIME");
        break;

    case INFORMATION_PANEL_ITEM_TIME_VALUE:
        // Set the time value text string.

        item.GetGdiRasterText ()->SetTextString (DescribeTime (m_timeInSeconds));
        break;

    case INFORMATION_PANEL_ITEM_SCORE_TEXT:
        // Set the score text string.

        item.GetGdiRasterText ()->SetTextString ("SCORE");
        break;

    case INFORMATION_PANEL_ITEM_SCORE_VALUE:
        // Set the score value text string.

        item.GetGdiRasterText ()->SetTextString (DescribeScore (m_score));
        break;

    default:
        break;
    } // Endswitch.

} // Endproc.


bool    InformationPanel::SetGraphicItemHeight (Folio::Core::Game::GraphicItemPtr::element_type &item)
{
    // Set the drawing height of the full chicken's GDI bitmap.

    Int32   drawingHeight = GetLossOfHealth () / PLAYER_HEALTH_DECREMENT;

    if (drawingHeight >= 0)
    {
       item.GetGdiBitmap ()->SetDrawingHeight (-1 * drawingHeight);
    } // Endif.

    return (drawingHeight >= 0);
} // Endproc.


Folio::Core::Game::ItemsList::iterator  InformationPanel::FindItem (INFORMATION_PANEL_ITEM_ID itemId)
{
    return (std::find_if (m_itemsList.begin (), m_itemsList.end (), 
                          [&itemId](const Folio::Core::Game::ItemPtr& arg) {return (arg->GetItemId () == itemId);}));
} // Endproc.


Folio::Core::Game::ZxSpectrum::COLOUR   InformationPanel::GetScrollItemColour (INFORMATION_PANEL_ITEM_ID                itemId,
                                                                               Folio::Core::Game::ZxSpectrum::COLOUR    roomColour) const
{
    // The colour map type.
    typedef std::map<Folio::Core::Game::ZxSpectrum::COLOUR, Folio::Core::Game::ZxSpectrum::COLOUR>  ColourMap;

    // The scroll colour map.
    static  ColourMap   s_scrollColourMap =
    {
    //      roomColour                                                                      scrollColour
        {   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::RED,     Folio::Core::Game::ZxSpectrum::CYAN,                                            },
        {   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::MAGENTA, Folio::Core::Game::ZxSpectrum::GREEN,                                           },
        {   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   Folio::Core::Game::ZxSpectrum::MAGENTA,                                         },
        {   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::CYAN,    Folio::Core::Game::ZxSpectrum::RED,                                             },
        {   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::YELLOW,  Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
        {   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::WHITE,   Folio::Core::Game::ZxSpectrum::BRIGHT | Folio::Core::Game::ZxSpectrum::GREEN,   },
    };

    Folio::Core::Game::ZxSpectrum::COLOUR   itemColour = Folio::Core::Game::ZxSpectrum::WHITE; // Initialise!

    // Get the item's colour.

    switch (itemId)
    {
    case INFORMATION_PANEL_ITEM_SCROLL:
        itemColour = s_scrollColourMap [roomColour];
        break;

    case INFORMATION_PANEL_ITEM_SCROLL_SEAL:
        itemColour = roomColour;
        break;

    default:
        itemColour = Folio::Core::Game::ZxSpectrum::WHITE;
        break;
    } // Endswitch.

    return (itemColour);
} // Endproc.


FolioStatus InformationPanel::ReleaseResourceGraphics ()
{
    // Release the information panel's resource graphics.

    return (g_resourceGraphicsCache.ReleaseResourceGraphics (OWNER_ID_INFORMATION_PANEL));
} // Endproc.


void    InformationPanel::CreateInformationPanelSoundSamples ()
{
    // Create the increment main player health sound samples.
    
    CreateIncrementMainPlayerHealthSoundSamples ();

    // Create the decrement main player health sound samples.
    
    CreateDecrementMainPlayerHealthSoundSamples ();
} // Endproc.


void    InformationPanel::CreateIncrementMainPlayerHealthSoundSamples ()
{
    if (m_incrementMainPlayerHealthSoundSamplesList.empty ())
    {
        // Create each sound sample representing the required sound.
    
        for (Folio::Core::Game::ZxSpectrum::BYTE frequency = 0x10; frequency <= 0x90; frequency += 0x10)
        {
            m_incrementMainPlayerHealthSoundSamplesList.push_back (Ultimate::CreateSoundSample (frequency, 0x08));
        } // Endfor.
        
        for (UInt32 count = 0; count < 3; ++count)
        {
            m_incrementMainPlayerHealthSoundSamplesList.push_back (Ultimate::CreateSoundSample (0x80, 0x08));
            m_incrementMainPlayerHealthSoundSamplesList.push_back (Ultimate::CreateSoundSample (0x90, 0x08));
        } // Endfor.

        m_incrementMainPlayerHealthSoundSamplesList.push_back (Ultimate::CreateSoundSample (0x80, 0x08));
    } // Endif.

} // Endproc.


void    InformationPanel::CreateDecrementMainPlayerHealthSoundSamples ()
{
    if (m_decrementMainPlayerHealthSoundSamplesList.empty ())
    {
        // Create each sound sample representing the required sound.

        Folio::Core::Game::ZxSpectrum::BYTE    frequency = 0x4c;

        for (Folio::Core::Game::ZxSpectrum::BYTE numLoops = 0x0f; numLoops >= 0x01; --numLoops)
        {
            m_decrementMainPlayerHealthSoundSamplesList.push_back (Ultimate::CreateSoundSample (frequency, numLoops));

            frequency++;

            if ((frequency % 0x04) == 0)
            {
                frequency -= 0x08;
            } // Endif.

        } // Endfor.

    } // Endif.

} // Endproc.


void    InformationPanel::PlayInformationPanelSounds ()
{
    // Play the increment main player health sound.

    if (!PlayIncrementMainPlayerHealthSound ())
    {
        // Play the decrement main player health sound.

        PlayDecrementMainPlayerHealthSound ();
    } // Endif.

} // Endproc.


bool    InformationPanel::PlayIncrementMainPlayerHealthSound ()
{
    bool    playedIncrementMainPlayerHealthSound = false;   // Initialise!

    // Should an increment main player health sound be played?

    if (m_playIncrementMainPlayerHealthSound)
    {
        // Yes. Play the increment main player health sound sample.

        FolioStatus status = 
            Folio::Core::Util::Sound::PlaySoundSample (m_incrementMainPlayerHealthSoundSamplesList [m_currentIncrementMainPlayerHealthSoundSampleIndex]);

        if (status == ERR_SUCCESS)
        {
            // All increment main player health sound samples played?

            if (++m_currentIncrementMainPlayerHealthSoundSampleIndex >= m_incrementMainPlayerHealthSoundSamplesList.size ())
            {
                // Yes.

                m_playIncrementMainPlayerHealthSound                = false;
                m_currentIncrementMainPlayerHealthSoundSampleIndex  = 0;
            } // Endif.

            playedIncrementMainPlayerHealthSound = true;
        } // Endif.

    } // Endif.

    return (playedIncrementMainPlayerHealthSound);
} // Endproc.


bool    InformationPanel::PlayDecrementMainPlayerHealthSound ()
{
    bool    playedDecrementMainPlayerHealthSound = false;   // Initialise!

    // Should a decrement main player health sound be played?

    if (m_playDecrementMainPlayerHealthSound)
    {
        // Yes. Play the decrement main player health sound sample.

        FolioStatus status = 
            Folio::Core::Util::Sound::PlaySoundSample (m_decrementMainPlayerHealthSoundSamplesList [m_currentDecrementMainPlayerHealthSoundSampleIndex]);

        if (status == ERR_SUCCESS)
        {
            // All decrement main player health sound samples played?

            if (++m_currentDecrementMainPlayerHealthSoundSampleIndex >= m_decrementMainPlayerHealthSoundSamplesList.size ())
            {
                // Yes.

                m_playDecrementMainPlayerHealthSound                = false;
                m_currentDecrementMainPlayerHealthSoundSampleIndex  = 0;
            } // Endif.

            playedDecrementMainPlayerHealthSound = true;
        } // Endif.

    } // Endif.

    return (playedDecrementMainPlayerHealthSound);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
