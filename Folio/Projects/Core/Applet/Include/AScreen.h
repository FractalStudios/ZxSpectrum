#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Game.h>
#include    <Graphic.h>
#include    "Canvas.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Applet
{

class AScreen
{
public:
    virtual ~AScreen ();

    FolioStatus Create (Canvas&                 canvas,
                        const Gdiplus::Rect&    clearRect,
                        UInt32                  minTimeToDisplay = 0);
    FolioStatus HandleProcessFrame (UInt32* frameRateIncrement = 0);

    bool    IsDisplaying () const;
    bool    IsComplete () const;

protected:
    Canvas*         m_canvas;           // The canvas.
    Gdiplus::Rect   m_clearScreenRect;  // The screen rect to clear when displaying the screen.

    Folio::Core::Game::Gamepad::CONTROLLER_ID   m_controllerId; // The controller identifier of the first connected controller.

    UInt32  m_minTimeToDisplay;         // The minimal time (in milliseconds) to display the screen.
    bool    m_isDisplaying;             // Indicates if the screen is being displayed.
    UInt32  m_initialFrameTickCount;    // The initial frame tick count.
    UInt32  m_previousFrameTickCount;   // The previous frame tick count.

    Folio::Core::Game::ItemsList    m_itemsList; // The screen items.

    AScreen ();

    FolioStatus Display ();
    FolioStatus StopDisplaying ();

    template <typename T>
    FolioStatus AddGraphicItem (FolioHandle                                 dcHandle, 
                                FolioHandle                                 instanceHandle,
                                Folio::Core::Game::DrawingElement::Id       drawingElementId,
                                const Folio::Core::Game::ItemAttributes<T>& itemAttributes);

    typedef void    (FOLIO_CALL *SetItemTextFunction) (Folio::Core::Game::TextItemPtr::element_type &item);

    template <typename T>
    FolioStatus AddTextItem (FolioHandle                                    dcHandle, 
                             Folio::Core::Game::DrawingElement::Id          drawingElementId,
                             Folio::Core::Graphic::GdiRasterFont&           gdiRasterFont,
                             const Folio::Core::Game::ItemAttributes<T>&    itemAttributes,
                             SetItemTextFunction                            setItemTextFunction = 0,
                             bool                                           gdiBitmapCacheRqd = false);

    virtual FolioStatus BuildScreenItems (FolioHandle   dcHandle, 
                                          FolioHandle   instanceHandle) = 0;
    virtual FolioStatus QueryScreenDrawingElements (FolioHandle                             dcHandle,
                                                    Folio::Core::Game::DrawingElementsList& drawingElementsList) const;
    virtual FolioStatus SetupGamepad (Folio::Core::Game::Gamepad& gamepad);
    virtual FolioStatus StartDisplayingScreen ();
    virtual FolioStatus ProcessScreenInput ();
    virtual FolioStatus ProcessScreenFrame (UInt32* frameRateIncrement);

private:
    FolioStatus DrawInCanvas () const;
    FolioStatus CheckInput ();
}; // Endclass.


template <typename T>
FolioStatus AScreen::AddGraphicItem (FolioHandle                                    dcHandle, 
                                     FolioHandle                                    instanceHandle ,
                                     Folio::Core::Game::DrawingElement::Id          drawingElementId,
                                     const Folio::Core::Game::ItemAttributes<T>&    itemAttributes)
{
    // Create a graphic item.
            
    Folio::Core::Game::GraphicItemPtr   item(new Folio::Core::Game::GraphicItemPtr::element_type);
            
    FolioStatus status = item->Create (dcHandle,
                                       instanceHandle,
                                       drawingElementId,
                                       itemAttributes.m_bitmapResourceId,
                                       itemAttributes.m_itemId,
                                       itemAttributes.m_screenXLeft, 
                                       itemAttributes.m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE);

    if (status == ERR_SUCCESS)
    {
        // Store the graphic item in the screen's items list.

        m_itemsList.push_back (item);
    } // Endif.

    return (status);
} // Endproc.


template <typename T>
FolioStatus AScreen::AddTextItem (FolioHandle                                   dcHandle, 
                                  Folio::Core::Game::DrawingElement::Id         drawingElementId,
                                  Folio::Core::Graphic::GdiRasterFont&          gdiRasterFont,
                                  const Folio::Core::Game::ItemAttributes<T>&   itemAttributes,
                                  SetItemTextFunction                           setItemTextFunction,
                                  bool                                          gdiBitmapCacheRqd)
{
    // Create a text item.

    Folio::Core::Game::TextItemPtr  item(new Folio::Core::Game::TextItemPtr::element_type);
                
    FolioStatus status = item->Create (dcHandle,
                                       drawingElementId,
                                       gdiRasterFont,
                                       itemAttributes.m_itemId,
                                       itemAttributes.m_screenXLeft, 
                                       itemAttributes.m_screenYTop,
                                       Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE, 
                                       Folio::Core::Game::ZxSpectrum::MapInkColour (itemAttributes.m_colour),
                                       Folio::Core::Graphic::DEFAULT_BACKGROUND_COLOUR,
                                       gdiBitmapCacheRqd);

    if (status == ERR_SUCCESS)
    {
        if (setItemTextFunction)
        {
            // Set the item's text.

            setItemTextFunction (*item.get ());
        } // Endif.

        // Store the text item in the screen's items list.

        m_itemsList.push_back (item);
    } // Endif.
            
    return (status);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
