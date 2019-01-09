#pragma once

#include <vector>
#include "Main.h"
#include "Utils.h"

#pragma pack(push, 1)

// Definitions and Types.

struct BackgroundItemAttrib
{
    BackgroundItemAttrib ()
    :   m_byGraphicType(0),
        m_wAddress(0),
        m_byWidth(0),
        m_byHeight(0)
    {} // Endproc.

    void    Reset ()
    {
        m_byGraphicType     = 0;
        m_wAddress          = 0;
        m_byWidth           = 0;
        m_byHeight          = 0;
        m_colourData.clear ();
    } // Endproc.

    bool    IsStarted () const
    {
        return (m_wAddress != 0);
    } // Endproc.

    bool    IsFinished () const
    {
        return (m_colourData.size () == (m_byWidth * m_byHeight));
    } // Endproc.

    void    ReorderColourData ()
    {
        Utils::DataList tempColourData;

        for (Utils::DataList::reverse_iterator ritr = m_colourData.rbegin ();
             ritr != m_colourData.rend ();
             ritr += m_byWidth)
        {
            Utils::DataList::iterator   itr = (ritr + m_byWidth).base ();

            tempColourData.insert (tempColourData.end (),
                                   itr,
                                   itr + m_byWidth);
        } // Endfor.

        m_colourData = tempColourData;
    } // Endproc.

    bool    operator < (const BackgroundItemAttrib &rhs) const
    {
        return (m_byGraphicType < rhs.m_byGraphicType);
    } // Endproc.

    BYTE            m_byGraphicType;
    WORD            m_wAddress;
    BYTE            m_byWidth;
    BYTE            m_byHeight;
    Utils::DataList m_colourData;
};

typedef std::vector<BackgroundItemAttrib> BackgroundItemAttribList;


// Routines.

extern  void    ParseBackgroundItemAttribs (const Utils::DataList       &fileData,
                                            BackgroundItemAttribList    &backgroundItemAttribList,
                                            AddressMap                  &addressMap);
extern  BackgroundItemAttrib    GetBackgroundItemAttrib (BYTE                           byGraphicType,
                                                         const BackgroundItemAttribList &backgroundItemAttribList);

#pragma pack(pop)

/******************************* End of File *******************************/
