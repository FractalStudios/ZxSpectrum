#pragma once

// STL includes.
#include    <vector>

// "Home-made" includes.
#include    <Util.h>
#include    "DrawingElement.h"
#include    "ResourceGraphic.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Game
{

class ResourceGraphicsCache
{
public:
    // Owner identifier.
    typedef UInt32  OwnerId;

    static  const   OwnerId OWNER_ID_UNDEFINED  = -1;  // Undefined owner identifier.

    ResourceGraphicsCache ();
    ~ResourceGraphicsCache ();

    FolioStatus Add (DrawingElement::Id         drawingElementId,
                     const ResourceGraphicPtr   &resourceGraphicPtr);
    FolioStatus Remove (const ResourceGraphicPtr &resourceGraphicPtr);

    FolioStatus GainResourceGraphic (OwnerId            ownerId,
                                     DrawingElement::Id drawingElementId,
                                     UInt16             bitmapResourceId,
                                     ResourceGraphicPtr &resourceGraphicPtr);
    FolioStatus GainResourceGraphic (OwnerId                    ownerId,
                                     const ResourceGraphicPtr   &resourceGraphicPtr);
    FolioStatus ReleaseResourceGraphic (const ResourceGraphicPtr &resourceGraphicPtr);
    FolioStatus ReleaseResourceGraphics (OwnerId ownerId);

    void    Dump (bool ownedOnly = true) const;
    void    DumpNumUsedBitmaps (bool ownedOnly = true) const;

private:
    struct Cache
    {
        Cache ()
        :   m_ownerId(OWNER_ID_UNDEFINED),
            m_drawingElementId(DrawingElement::DRAWING_ELEMENT_ID_UNDEFINED)
        {} // Endproc.

        Cache (DrawingElement::Id       drawingElementId,
               const ResourceGraphicPtr &resourceGraphicPtr)
        :   m_ownerId(OWNER_ID_UNDEFINED),
            m_drawingElementId(drawingElementId),
            m_resourceGraphicPtr(resourceGraphicPtr)
        {} // Endproc.

        ~Cache ()
        {} // Endproc.

        bool    IsOwned () const
        {
            return (m_ownerId != OWNER_ID_UNDEFINED);
        } // Endproc.

        FolioString Describe () const
        {
            FolioOStringStream  str;
            str << std::setw(2) << std::dec << static_cast<int> (m_ownerId)
                << TXT(' ') << std::dec << m_drawingElementId
                << TXT(' ') << std::dec << Folio::Core::Util::DescribeId (m_resourceGraphicPtr->GetBitmapResourceId ())
                << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << m_resourceGraphicPtr
                << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << m_resourceGraphicPtr->GetGdiBitmap ()
                << TXT(" 0x") << std::setw(8) << std::setfill(TXT('0')) << std::hex << m_resourceGraphicPtr->GetMaskedGdiBitmap ();

            return (str.str ());
        } // Endproc.

        OwnerId             m_ownerId;              // The identifier of the owner that owns the resource graphic.
        DrawingElement::Id  m_drawingElementId;     // The drawing element identifier of the resource graphic.
        ResourceGraphicPtr  m_resourceGraphicPtr;   // The resource graphic.
    }; // Endstruct.
    
    // Resource graphics list.
    typedef std::vector<Cache>  ResourceGraphicsList;
    ResourceGraphicsList    m_resourceGraphicsList;

    ResourceGraphicsList::iterator  Find (DrawingElement::Id    drawingElementId,
                                          UInt16                bitmapResourceId);
    ResourceGraphicsList::iterator  Find (const ResourceGraphicPtr &resourceGraphicPtr);
    ResourceGraphicsList::iterator  Find (const ResourceGraphicPtr  &resourceGraphicPtr, 
                                          bool                      findOwnedResourceGraphic);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
