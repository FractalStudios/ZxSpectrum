#pragma once

// STL includes.
#include    <map>
#include    <memory>

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
    ScreenBackground (const BackgroundItemsList         &backgroundItemsList,
                      const BackgroundItemGraphicsMap   &backgroundItemGraphicsMap);
    ~ScreenBackground ();

    BackgroundItemsList GetBackgroundItemsList () const;

private:
    BackgroundItemsList m_backgroundItemsList;  // The screen's background items list.

    FolioStatus SetBackgroundItemGraphics (const BackgroundItemGraphicsMap &backgroundItemGraphicsMap);

    // Private copy constructor to prevent copying.
    ScreenBackground (const ScreenBackground& rhs);

    // Private assignment operator to prevent copying.
    ScreenBackground& operator= (const ScreenBackground& rhs);
}; // Endclass.

// Screen background pointer.
typedef std::shared_ptr<ScreenBackground>   ScreenBackgroundPtr;

// Screen backgrounds map.
typedef std::map<ScreenMap::ScreenNumber, ScreenBackgroundPtr>  ScreenBackgroundsMap;
             

// Routines.

extern  FolioStatus CreateScreenBackgrounds (const BackgroundItemGraphicsMap    &backgroundItemGraphicsMap,
                                             ScreenBackgroundsMap               &screenBackgroundsMap);
extern  FolioStatus QueryScreenBackgroundList (ScreenMap::ScreenNumber  screenNumber,
                                               BackgroundItemsList      &backgroundItemsList);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
