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
    typedef FolioString OwnerId;

    // Owner identifiers.
    static  const   OwnerId OWNER_ID_MAIN_PLAYER_SPRITE;    // Main player sprite owner identifier.   
    static  const   OwnerId OWNER_ID_BOSS_SPRITE;           // Boss sprite owner identifier.
    static  const   OwnerId OWNER_ID_NASTY_SPRITE;          // Nasty sprite owner identifier.
    static  const   OwnerId OWNER_ID_WEAPON_SPRITE;         // Weapon sprite owner identifier.
    static  const   OwnerId OWNER_ID_INFORMATION_PANEL;     // Information panel owner identifier.

    ResourceGraphicsCache ();
    ~ResourceGraphicsCache ();

    FolioStatus Add (const ResourceGraphicPtr& resourceGraphicPtr);
    FolioStatus Remove (const ResourceGraphicPtr& resourceGraphicPtr);

    FolioStatus GainResourceGraphic (const OwnerId&                             ownerId,
                                     const DrawingElement::DrawingElementId&    drawingElementId,
                                     UInt16                                     bitmapResourceId,
                                     ResourceGraphicPtr&                        resourceGraphicPtr);
    FolioStatus GainResourceGraphic (const OwnerId&             ownerId,
                                     const ResourceGraphicPtr&  resourceGraphicPtr);
    FolioStatus ReleaseResourceGraphic (const ResourceGraphicPtr& resourceGraphicPtr);
    FolioStatus ReleaseResourceGraphics (const OwnerId& ownerId);

    void    Dump (bool ownedOnly = true) const;
    void    DumpNumUsedBitmaps (bool ownedOnly = true) const;

    static  OwnerId MakeOwnerId (UInt32 ownerId);

private:
    struct Cache
    {
        Cache ()
        {} // Endproc.

        Cache (const ResourceGraphicPtr& resourceGraphicPtr)
        :   m_resourceGraphicPtr(resourceGraphicPtr)
        {} // Endproc.

        ~Cache ()
        {} // Endproc.

        bool    IsOwned () const
        {
            return (!m_ownerId.empty ());
        } // Endproc.

        FolioString Describe () const
        {
            FolioOStringStream  str;

            if (IsOwned ())
            {
                str << TXT('\'') <<m_ownerId << TXT("' ");
            } // Endif.

            str << m_resourceGraphicPtr->Describe ();

            return (str.str ());
        } // Endproc.

        OwnerId             m_ownerId;                  // The identifier of the owner that owns the resource graphic.
        ResourceGraphicPtr  m_resourceGraphicPtr;       // The resource graphic.
    }; // Endstruct.
    
    // Resource graphics list.
    typedef std::vector<Cache>  ResourceGraphicsList;
    ResourceGraphicsList    m_resourceGraphicsList;

    ResourceGraphicsList::iterator  Find (const DrawingElement::DrawingElementId&   drawingElementId,
                                          UInt16                                    bitmapResourceId);
    ResourceGraphicsList::iterator  Find (const ResourceGraphicPtr& resourceGraphicPtr);
    ResourceGraphicsList::iterator  Find (const ResourceGraphicPtr& resourceGraphicPtr, 
                                          bool                      findOwnedResourceGraphic);
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
