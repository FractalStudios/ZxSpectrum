#pragma once

// STL includes.
#include    <memory>
#include    <map>

// "Home-made" includes.
#include    <Game.h>
#include    "BackgroundItem.h"
#include    "ScreenMap.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Games
{

namespace SabreWulf
{

// Screen background.
class ScreenBackground
{
public:
    ScreenBackground (const BackgroundItemsList           &backgroundItemsList,
                      const BackgroundItemGraphicsMapPtr  &backgroundItemGraphicsMap);
    ~ScreenBackground ();

    BackgroundItemsList GetBackgroundItemsList () const;

private:
    BackgroundItemsList m_backgroundItemsList;  // The screen's background items list.

    void    SetBackgroundItemGraphics (const BackgroundItemGraphicsMapPtr &backgroundItemGraphicsMap);

    // Private copy constructor to prevent copying.
    ScreenBackground (const ScreenBackground& rhs);

    // Private assignment operator to prevent copying.
    ScreenBackground& operator= (const ScreenBackground& rhs);
}; // Endclass.

// Screen backgrounds pointer.
typedef std::shared_ptr<ScreenBackground>   ScreenBackgroundPtr;

// Screen backgrounds map.
typedef std::map<ScreenMap::ScreenNumber, ScreenBackgroundPtr>  ScreenBackgroundsMap;
             

// Routines.

extern  FolioStatus BuildScreenBackgrounds (const BackgroundItemGraphicsMapPtr  &backgroundItemGraphicsMap,
                                            ScreenBackgroundsMap                &screenBackgroundsMap);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
