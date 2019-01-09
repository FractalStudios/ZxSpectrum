// "Home-made" includes.
#include    "StdAfx.h"
#include    "DrawingElement.h"
#include    "Font.h"
#include    "InformationPanel.h"

namespace Folio
{

namespace Games
{

namespace AticAtac
{

// Information panel item attributes.
struct InformationPanelItemAttributes
{
    INFORMATION_PANEL_ITEM_ID   m_itemId;               // The identifier of the information panel item.
    UInt16                      m_bitmapResourceId;     // The information panel item's bitmap resource identifier (if it's a graphic item).
    Int32                       m_screenXLeft;          // The screen X left of the information panel item.
    Int32                       m_screenYTop;           // The screen Y top of the information panel item.
    ZxSpectrum::COLOUR          m_colour;               // The colour of the information panel item.
 }; // Endstruct.

// Information panel item attributes table.
static  const   InformationPanelItemAttributes  g_informationPanelAttributesTable [] =
{
//      m_itemId                                m_bitmapResourceId                  m_screenXLeft   m_screenYTop    m_colour
    {   INFORMATION_PANEL_ITEM_SCROLL,          IDB_BITMAP_SCROLL,                   0,               0,            0,                                          },
    {   INFORMATION_PANEL_ITEM_SCROLL_SEAL,     IDB_BITMAP_SCROLL_SEAL,              8,             144,            0,                                          },
    {   INFORMATION_PANEL_ITEM_TIME_TEXT,       0,                                  16,              56,            ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   },
    {   INFORMATION_PANEL_ITEM_TIME_VALUE,      0,                                   8,              64,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   INFORMATION_PANEL_ITEM_SCORE_TEXT,      0,                                  12,              72,            ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      },
    {   INFORMATION_PANEL_ITEM_SCORE_VALUE,     0,                                   8,              80,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   INFORMATION_PANEL_ITEM_TURKEY_CARCASS,  IDB_BITMAP_TURKEY_CARCASS,           8,              90,            ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   INFORMATION_PANEL_ITEM_TURKEY,          IDB_BITMAP_FULL_TURKEY,              8,              90,            ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    },
    {   INFORMATION_PANEL_ITEM_PLAYER_LIFE_1,   IDB_BITMAP_KNIGHT_WALKING_LEFT_1,    8,             122,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   INFORMATION_PANEL_ITEM_PLAYER_LIFE_2,   IDB_BITMAP_KNIGHT_WALKING_LEFT_1,   24,             122,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
    {   INFORMATION_PANEL_ITEM_PLAYER_LIFE_3,   IDB_BITMAP_KNIGHT_WALKING_LEFT_1,   40,             122,            ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     },
};


InformationPanel::InformationPanel ()
:   m_canvasBag(0),
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
} // Endproc.


FolioStatus InformationPanel::Create (Folio::Core::Applet::CanvasBag    &canvasBag,
                                      UInt32                            totalNumRooms,
                                      UInt16                            mainPlayerBitmapResourceId)
{
    // Note the information panel attributes.

    m_canvasBag             = &(canvasBag);
    m_timeInSeconds         = 0;
    m_score                 = 0;
    m_health                = MAX_HEALTH;
    m_lives                 = MAX_NUM_LIVES;
    m_totalNumRooms         = totalNumRooms;
    m_numRoomsVisited       = 0;
    m_invertScoreColours    = false;

    m_heldItemsList.clear ();   // Initialise!

    // Build the information panel items.

    return (BuildItems (canvasBag.GetCanvasDcHandle (), 
                        canvasBag.GetAppletInstanceHandle (), 
                        mainPlayerBitmapResourceId));
} // Endproc.


FolioStatus InformationPanel::QueryDrawingElements (FolioHandle                             dcHandle,
                                                    ZxSpectrum::COLOUR                      roomColour,
                                                    Folio::Core::Game::DrawingElementsList  &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    // Query the drawing elements of the information panel items.

    for (ItemsList::iterator itr = m_itemsList.begin ();
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
                                                     ZxSpectrum::MapInkColour (GetScrollItemColour (itemId, roomColour)), 
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

    return (status);
} // Endproc.


FolioStatus InformationPanel::HandleProcessFrame (bool  &isStarting,
                                                  bool  &mainPlayerIsDead)
{
    // Note if we were (ar) starting.

    bool    wasStarting = isStarting;

    // Check time per frame.

    FolioStatus status = CheckTimePerFrame (isStarting, mainPlayerIsDead);

    if (status == ERR_SUCCESS)
    {
        // Are we starting?

        if (isStarting)
        {
            // Yes. Check score.

            status = CheckScorePerFrame ();
        } // Endif.

        // Were we starting?

        else
        if (wasStarting)
        {
            // Yes. Reset the information panel.

            status = Reset ();
        } // Endelseif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::AddCollectedItem (const HeldItem  &heldItem,
                                                DroppedItem     &droppedItem)
{
    // Add the collected (held) item to the information panel.

    return (AddHeldItem (heldItem, droppedItem));
} // Endproc.


FolioStatus InformationPanel::CycleCollectedItems (DroppedItem &droppedItem)
{
    // Cycle the collected (held) items in the information panel.

    return (CycleHeldItems (droppedItem));
} // Endproc.


bool    InformationPanel::IsAnyCollectedItem () const
{
    return (IsAnyHeldItem ());
} // Endproc.


bool    InformationPanel::IsRedKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, ZxSpectrum::BRIGHT | ZxSpectrum::RED) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsGreenKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, ZxSpectrum::BRIGHT | ZxSpectrum::GREEN) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsCyanKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, ZxSpectrum::BRIGHT | ZxSpectrum::CYAN) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsYellowKeyCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_KEY, ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW) != m_heldItemsList.end ());
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
    return (FindHeldItem (STATIC_SPRITE_CRUCIFIX, ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW) != m_heldItemsList.end ());
} // Endproc.


bool    InformationPanel::IsSpannerCollected () const
{
    return (FindHeldItem (STATIC_SPRITE_SPANNER, ZxSpectrum::BRIGHT | ZxSpectrum::CYAN) != m_heldItemsList.end ());
} // Endproc.


FolioStatus InformationPanel::IncrementScore (UInt32 scoreIncrement)
{
    // Increment the current score.

    m_score += scoreIncrement;

    // Update the score.

    return (Update (UPDATE_SCORE));
} // Endproc.
    

void    InformationPanel::IncrementNumRoomsVisited ()
{
    m_numRoomsVisited++;
} // Endproc.


FolioStatus InformationPanel::DecrementMainPlayerHealth (UInt32 healthDecrement, 
                                                         bool   &mainPlayerIsDead)
{
    FolioStatus status = ERR_SUCCESS;

    mainPlayerIsDead = false;    // Initialise!

    if (m_health >= MIN_HEALTH)
    {
        // Decrement the main player's current health.

        m_health -= healthDecrement;

        // Is the main player dead?

        mainPlayerIsDead = (m_health < MIN_HEALTH);

        if (!mainPlayerIsDead)
        {
            // No. Update the main player's health.

            status = Update (UPDATE_HEALTH);
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.
    

FolioStatus InformationPanel::IncrementMainPlayerHealth (UInt32 healthIncrement)
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
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       ZxSpectrum::GetBitmapChangeColour (),
                                       Folio::Core::Graphic::DEFAULT_FOREGROUND_COLOUR,
                                       Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR,
                                       true);   // Mask required.

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
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       ZxSpectrum::MapInkColour (g_informationPanelAttributesTable [index].m_colour));

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
                                       ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       ZxSpectrum::GetBitmapChangeColour (),
                                       ZxSpectrum::MapInkColour (g_informationPanelAttributesTable [index].m_colour));

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


FolioStatus InformationPanel::CheckTimePerFrame (bool   &isStarting,
                                                 bool   &mainPlayerIsDead)
{
    static  UInt32  previousFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    FolioStatus status = ERR_SUCCESS;

    UInt32  currentTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    if (currentTickCount >= (previousFrameTickCount + 1000))
    {
        // Increment the time in seconds.

        status = IncrementTimeInSeconds (currentTickCount, isStarting, mainPlayerIsDead);

        if (status == ERR_SUCCESS)
        {
            // Note the previous tick count.

            previousFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::CheckScorePerFrame ()
{
    static  UInt32  previousFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();

    FolioStatus status = ERR_SUCCESS;

    if (Folio::Core::Util::DateTime::GetCurrentTickCount () >= (previousFrameTickCount  + ZxSpectrum::FLASH_MS))
    {
        // Update the information panel.

        status = Update (UPDATE_SCORE_COLOURS);

        if (status == ERR_SUCCESS)
        {
            // Note the previous tick count.

            previousFrameTickCount = Folio::Core::Util::DateTime::GetCurrentTickCount ();
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::IncrementTimeInSeconds (UInt32    currentTickCount,
                                                      bool      &isStarting,
                                                      bool      &mainPlayerIsDead)
{
    static  bool    s_isStarting                = false;
    static  UInt32  s_previousStartingTickCount = 0;

    static  const   UInt32  DEFAULT_START_TIME = 3 * 1000;  // 3 seconds.

    // Starting?

    if (isStarting)
    {
        if (!s_isStarting)
        {
            s_isStarting                = true;
            s_previousStartingTickCount = currentTickCount;
        } // Endif.

        else
        {
            s_isStarting = (currentTickCount < (s_previousStartingTickCount + DEFAULT_START_TIME));
        } // Endelse.

        isStarting = s_isStarting;
    } // Endif.

    // Increment the time in seconds.

    m_timeInSeconds++;

    // We periodically reduce the main player's health.

    if (!isStarting && (m_timeInSeconds % PLAYER_HEALTH_TIME_DECREMENT) == 0)
    {
        DecrementMainPlayerHealth (PLAYER_HEALTH_TIME_DECREMENT, mainPlayerIsDead);
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

    // Get the canvas bag graphics.

    Gdiplus::Graphics   *graphics = m_canvasBag->GetCanvasGraphics ();

    // Update the information panel items (depending on the type of update required).

    bool    finished        = false;   // Initialise!
    bool    redrawCanvasBag = false;

    for (ItemsList::iterator itr = m_itemsList.begin ();
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

                    redrawCanvasBag = true;
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

                redrawCanvasBag = true;
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

                redrawCanvasBag = true;
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
                                         redrawCanvasBag);
            } // Endelse.
            break;

        case INFORMATION_PANEL_ITEM_TURKEY_CARCASS:
            if (update == UPDATE_HEALTH)
            {
                // Get the information panel graphic item.

                Folio::Core::Game::GraphicItemPtr   item(std::dynamic_pointer_cast<Folio::Core::Game::GraphicItem> (*itr));

                // Draw the information panel graphic item.

                status = item->Draw (*graphics);

                redrawCanvasBag = true;
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
                    
                    redrawCanvasBag = true;
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
                    
                    redrawCanvasBag = true;
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

    if (redrawCanvasBag && (status == ERR_SUCCESS))
    {
        // The canvas bag should be redrawn on the next draw.

        m_canvasBag->SetRedrawRqd ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::Reset ()
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the canvas bag graphics.

    Gdiplus::Graphics   *graphics = m_canvasBag->GetCanvasGraphics ();

    // Reset the information panel items.

    bool    finished        = false;   // Initialise!
    bool    redrawCanvasBag = false;

    for (ItemsList::iterator itr = m_itemsList.begin ();
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
                                         redrawCanvasBag);

                // Finished?
            
                finished = (itemId == INFORMATION_PANEL_ITEM_TURKEY_CARCASS);
            } // Endscope.
            break;

        default:
            break;
        } // Endswitch.

    } // Endfor.

    if (redrawCanvasBag && (status == ERR_SUCCESS))
    {
        // The canvas bag should be redrawn on the next draw.

        m_canvasBag->SetRedrawRqd ();
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

        // Create an information panel graphic item representing the held item.

        Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
        status = item->Create (m_canvasBag->GetCanvasDcHandle (),
                               m_canvasBag->GetAppletInstanceHandle (),
                               DRAWING_ELEMENT_INFORMATION_PANEL_ITEM,
                               heldItem.m_staticSprite->GetSpriteGraphic ()->GetBitmapResourceId (),
                               itemId,
                               HELD_ITEM_ORIGIN_X_LEFT, 
                               HELD_ITEM_ORIGIN_Y_TOP,
                               ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                               ZxSpectrum::GetBitmapChangeColour (),
                               ZxSpectrum::MapInkColour (heldItem.m_staticSprite->GetStaticSpriteColour ()));

        if (status == ERR_SUCCESS)
        {
            // Store the information panel item in the information panel items list.

            m_itemsList.push_back (item);

            // Add the information panel graphic item's drawing elements to the canvas bag.

            status = m_canvasBag->AddDrawingElements (item->GetDrawingElementsList ());

            if (status == ERR_SUCCESS)
            {
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

            InformationPanel::ItemsList::iterator   itr = FindItem (droppedItem.m_itemId);

            if (itr != m_itemsList.end ())
            {
                // Remove the dropped item's drawing elements from the canvas bag.

                status = m_canvasBag->RemoveDrawingElements (itr->get ()->GetDrawingElementsList ());

                if (status == ERR_SUCCESS)
                {
                    // Remove the information panel item from the information panel items list.

                    m_itemsList.erase (itr);
                } // Endif.

            } // Endif.
        
        } // Endif.

    } // Endif.

    return (status);
} // Endproc.


FolioStatus InformationPanel::ClearHeldItemsRectangle ()
{
    return (m_canvasBag->ClearCanvasRectangle (Gdiplus::Rect(HELD_ITEM_ORIGIN_X_LEFT, 
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


InformationPanel::HeldItemsList::const_iterator InformationPanel::FindHeldItem (STATIC_SPRITE_ID    staticSpriteId,
                                                                                ZxSpectrum::COLOUR  colour) const
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
                                              bool                                          &redrawCanvasBag)
{                   
    FolioStatus status = ERR_SUCCESS;

    // Get the text item's GDI raster text.

    Folio::Core::Graphic::GdiRasterTextPtr  gdiRasterText(item.GetGdiRasterText ());

    // Invert the text item's colours?

    if (invertColours)
    {
        // Yes. Invert the text item's colours

        gdiRasterText->InvertColours ();

        // Draw it.

        status = gdiRasterText->Draw (graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvasBag = true;
        } // Endif.

    } // Endif.

    else
    if (!invertColours && gdiRasterText->IsInvertedColours ())
    {
        // No. Reset the text item's colours

        gdiRasterText->ResetColours ();

        // Draw it.

        status = gdiRasterText->Draw (graphics);

        if (status == ERR_SUCCESS)
        {
            redrawCanvasBag = true;
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


InformationPanel::ItemsList::iterator   InformationPanel::FindItem (INFORMATION_PANEL_ITEM_ID itemId)
{
    return (std::find_if (m_itemsList.begin (), m_itemsList.end (), 
                          [&itemId](const Item& arg) {return (arg->GetItemId () == itemId);}));
} // Endproc.


ZxSpectrum::COLOUR  InformationPanel::GetScrollItemColour (INFORMATION_PANEL_ITEM_ID    itemId,
                                                           ZxSpectrum::COLOUR           roomColour) const
{
    // The colour map type.
    typedef std::map<ZxSpectrum::COLOUR, ZxSpectrum::COLOUR>    ColourMap;

    // The scroll colour map.
    static  ColourMap   s_scrollColourMap =
    {
    //      roomColour                                  scrollColour
        {   ZxSpectrum::BRIGHT | ZxSpectrum::RED,       ZxSpectrum::CYAN,                       },
        {   ZxSpectrum::BRIGHT | ZxSpectrum::MAGENTA,   ZxSpectrum::GREEN,                      },
        {   ZxSpectrum::BRIGHT | ZxSpectrum::GREEN,     ZxSpectrum::MAGENTA,                    },
        {   ZxSpectrum::BRIGHT | ZxSpectrum::CYAN,      ZxSpectrum::RED,                        },
        {   ZxSpectrum::BRIGHT | ZxSpectrum::YELLOW,    ZxSpectrum::BRIGHT | ZxSpectrum::GREEN, },
        {   ZxSpectrum::BRIGHT | ZxSpectrum::WHITE,     ZxSpectrum::BRIGHT | ZxSpectrum::GREEN, },
    };

    ZxSpectrum::COLOUR  itemColour = ZxSpectrum::WHITE; // Initialise!

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
        itemColour = ZxSpectrum::WHITE;
        break;
    } // Endswitch.

    return (itemColour);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
