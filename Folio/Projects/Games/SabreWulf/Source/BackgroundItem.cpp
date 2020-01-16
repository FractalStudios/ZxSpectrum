// "Home-made" includes.
#include    "StdAfx.h"
#include    "BackgroundItem.h"

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

BackgroundItem::BackgroundItem (BACKGROUND_ITEM_ID  backgroundItemId,
                                Int32               screenXLeft,    
                                Int32               screenYTop)
:   m_backgroundItemId(backgroundItemId),
    m_screenXLeft(screenXLeft),    
    m_screenYTop(screenYTop)
{
} // Endproc.


BackgroundItem::~BackgroundItem ()
{
} // Endproc.


FolioStatus BackgroundItem::SetBackgroundItemGraphic (const BackgroundItemGraphicsMap &backgroundItemGraphicsMap)
{
    return (FindBackgroundItemGraphic (m_backgroundItemId,
                                       backgroundItemGraphicsMap,
                                       m_backgroundItemGraphic));
} // Endproc.


BackgroundItemGraphic   BackgroundItem::GetBackgroundItemGraphic () const
{
    return (m_backgroundItemGraphic);
} // Endproc.


BACKGROUND_ITEM_ID  BackgroundItem::GetBackgroundItemId () const
{
    return (m_backgroundItemId);
} // Endproc.


UInt16  BackgroundItem::GetBitmapResourceId () const
{
    return (m_backgroundItemGraphic ? m_backgroundItemGraphic->GetBitmapResourceId () : m_backgroundItemId);
} // Endproc.


Gdiplus::Rect   BackgroundItem::GetScreenRect () const
{
    return (Gdiplus::Rect(GetScreenXLeft(), 
                          GetScreenYTop (), 
                          GetScreenWidth (), 
                          GetScreenHeight ()));
} // Endproc.


Int32   BackgroundItem::GetScreenXLeft () const
{
    return (m_screenXLeft);
} // Endproc.


Int32   BackgroundItem::GetScreenYTop () const
{
    return (m_screenYTop);
} // Endproc.


Int32   BackgroundItem::GetScreenXRight () const
{
    return (m_backgroundItemGraphic ? m_screenXLeft + m_backgroundItemGraphic->GetGraphicWidth () - 1 : Folio::Core::Game::ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   BackgroundItem::GetScreenYBottom () const
{
    return (m_backgroundItemGraphic ? m_screenYTop + m_backgroundItemGraphic->GetGraphicHeight () - 1 : Folio::Core::Game::ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   BackgroundItem::GetScreenWidth () const
{
    return (m_backgroundItemGraphic ? m_backgroundItemGraphic->GetGraphicWidth () : Folio::Core::Game::ZxSpectrum::UNDEFINED);
} // Endproc.


Int32   BackgroundItem::GetScreenHeight () const
{
    return (m_backgroundItemGraphic ? m_backgroundItemGraphic->GetGraphicHeight () : Folio::Core::Game::ZxSpectrum::UNDEFINED);
} // Endproc.


FolioStatus BackgroundItem::QueryDrawingElements (FolioHandle                               dcHandle,
                                                  Folio::Core::Game::DrawingElementsList    &drawingElementsList)
{
    FolioStatus status = ERR_SUCCESS;

    drawingElementsList.clear ();   // Initialise!

    if (m_backgroundItemGraphic)
    {
        // Have the background item graphic's drawing elements been queried already?

        if (m_drawingElementsList.empty ())
        {
            // No. Query the background item graphic's drawing elements.

            status = m_backgroundItemGraphic->QueryDrawingElements (dcHandle,
                                                                    m_screenXLeft,
                                                                    m_screenYTop,
                                                                    Folio::Core::Game::ZxSpectrum::DEFAULT_SCREEN_SCALE,
                                                                    Folio::Core::Game::ResourceGraphic::NO_DRAWING_FLAGS,
                                                                    const_cast<BackgroundItem *> (this),    // Drawing element user data.
                                                                    m_drawingElementsList,
                                                                    false); // Masked drawing element not required.
        } // Endif.

        if ((status == ERR_SUCCESS) && !m_drawingElementsList.empty ())
        {
            drawingElementsList = m_drawingElementsList;
        } // Endif.

    } // Endif.

    else
    {
        status = ERR_NOT_INITIALISED;
    } // Endelse.

    return (status);
} // Endproc.


BackgroundItem::operator Folio::Core::Game::ItemAttributes<BACKGROUND_ITEM_ID> () const
{
    return (Folio::Core::Game::ItemAttributes<BACKGROUND_ITEM_ID>(m_backgroundItemId,
                                                                  GetBitmapResourceId (),
                                                                  m_screenXLeft,     
                                                                  m_screenYTop,
                                                                  Folio::Core::Game::ZxSpectrum::UNDEFINED));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
