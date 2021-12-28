// "Home-made" includes.
#include    "ResourceGraphicsCache.h"

//#define _OUTPUT_RESOURCE_GRAPHICS_CACHE_

namespace Folio
{

namespace Core
{

namespace Game
{

// Owner identifiers.
const   ResourceGraphicsCache::OwnerId  ResourceGraphicsCache::OWNER_ID_MAIN_PLAYER_SPRITE = TXT("Main Player Sprite"); // Main player sprite owner.   
const   ResourceGraphicsCache::OwnerId  ResourceGraphicsCache::OWNER_ID_BOSS_SPRITE        = TXT("Boss Sprite");        // Boss sprite owner.
const   ResourceGraphicsCache::OwnerId  ResourceGraphicsCache::OWNER_ID_NASTY_SPRITE       = TXT("Nasty Sprite");       // Nasty sprite owner.
const   ResourceGraphicsCache::OwnerId  ResourceGraphicsCache::OWNER_ID_WEAPON_SPRITE      = TXT("Weapon Sprite");      // Weapon sprite owner.
const   ResourceGraphicsCache::OwnerId  ResourceGraphicsCache::OWNER_ID_INFORMATION_PANEL  = TXT("Information Panel");  // Information panel owner.

ResourceGraphicsCache::ResourceGraphicsCache ()
{
} // Endproc.


ResourceGraphicsCache::~ResourceGraphicsCache ()
{
} // Endproc.


FolioStatus ResourceGraphicsCache::Add (const ResourceGraphicPtr& resourceGraphicPtr)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the resource graphic in the resource graphics list?

    if (Find (resourceGraphicPtr) != m_resourceGraphicsList.end ())
    {
        // Yes.

        status = ERR_ALREADY_EXISTS;
    } // Endif.

    else
    {
        // No. Add the resource graphic to the resource graphics list.

        m_resourceGraphicsList.push_back (Cache(resourceGraphicPtr));

        #ifdef _OUTPUT_RESOURCE_GRAPHICS_CACHE_
        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::Add:") 
            << TXT(' ') << m_resourceGraphicsList.back ().Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphicsCache::Remove (const ResourceGraphicPtr& resourceGraphicPtr)
{
    FolioStatus status = ERR_SUCCESS;

    // Is the resource graphic in the resource graphics list?

    ResourceGraphicsList::iterator  itr = Find (resourceGraphicPtr);

    if (itr != m_resourceGraphicsList.end ())
    {
        #ifdef _OUTPUT_RESOURCE_GRAPHICS_CACHE_
        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::Remove:") 
            << TXT(' ') << itr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif

        // Yes. Remove the resource graphic from the resource graphics list.

        m_resourceGraphicsList.erase (itr);
    } // Endif.

    else
    {
        // No. 

        status = ERR_NOT_FOUND;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphicsCache::GainResourceGraphic (const OwnerId&                          ownerId,
                                                        const DrawingElement::DrawingElementId& drawingElementId,
                                                        UInt16                                  bitmapResourceId,
                                                        ResourceGraphicPtr&                     resourceGraphicPtr)
{
    FolioStatus status = ERR_SUCCESS;

    resourceGraphicPtr.reset ();    // Initialise!

    // Find an unowned resource graphic in the resource graphics list.

    ResourceGraphicsList::iterator  itr = Find (drawingElementId, bitmapResourceId);

    if (itr != m_resourceGraphicsList.end ())
    {
        // The resource graphic is now owned.

        itr->m_ownerId = ownerId;

        resourceGraphicPtr = itr->m_resourceGraphicPtr;

        #ifdef _OUTPUT_RESOURCE_GRAPHICS_CACHE_
        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::GainResourceGraphic:") 
            << TXT(' ') << itr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif
    } // Endif.

    else
    {
        // No. 

        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::GainResourceGraphic:") 
            << TXT(' ') << drawingElementId
            << TXT(' ') << Folio::Core::Util::DescribeBitmapResourceId (bitmapResourceId)
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        Dump (true);

        status = ERR_ALREADY_IN_USE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphicsCache::GainResourceGraphic (const OwnerId&              ownerId,
                                                        const ResourceGraphicPtr&   resourceGraphicPtr)
{
    FolioStatus status = ERR_SUCCESS;

    // Find an unowned resource graphic in the resource graphics list.

    ResourceGraphicsList::iterator  itr = Find (resourceGraphicPtr, false);

    if (itr != m_resourceGraphicsList.end ())
    {
        // The resource graphic is now owned.

        itr->m_ownerId = ownerId;

        #ifdef _OUTPUT_RESOURCE_GRAPHICS_CACHE_
        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::GainResourceGraphic:") 
            << TXT(' ') << itr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif
    } // Endif.

    else
    {
        // No. 

        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::GainResourceGraphic:") 
            << TXT(' ') << ownerId
            << TXT(", ") << resourceGraphicPtr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        Dump (true);

        status = ERR_ALREADY_IN_USE;
    } // Endelse.

    return (status);
} // Endproc.


FolioStatus ResourceGraphicsCache::ReleaseResourceGraphic (const ResourceGraphicPtr& resourceGraphicPtr)
{
    FolioStatus status = ERR_SUCCESS;

    // Find the owned resource graphic in the resource graphics list.

    ResourceGraphicsList::iterator  itr = Find (resourceGraphicPtr, true);

    if (itr != m_resourceGraphicsList.end ())
    {
        #ifdef _OUTPUT_RESOURCE_GRAPHICS_CACHE_
        FolioOStringStream  str;
        str << TXT("ResourceGraphicsCache::ReleaseResourceGraphic:") 
            << TXT(' ') << itr->Describe ()
            << std::endl;
        ::OutputDebugString (str.str ().c_str ());
        #endif

        // The resource graphic is now unowned.

        itr->m_ownerId.clear ();
    } // Endif.

    return (status);
} // Endproc.


FolioStatus ResourceGraphicsCache::ReleaseResourceGraphics (const OwnerId& ownerId)
{
    FolioStatus status = ERR_SUCCESS;

    for (ResourceGraphicsList::iterator itr = m_resourceGraphicsList.begin ();
         itr != m_resourceGraphicsList.end ();
         ++itr)
    {
        if (itr->m_ownerId == ownerId)
        {
            #ifdef _OUTPUT_RESOURCE_GRAPHICS_CACHE_
            FolioOStringStream  str;
            str << TXT("ResourceGraphicsCache::ReleaseResourceGraphics:") 
                << TXT(' ') << itr->Describe ()
                << std::endl;
            ::OutputDebugString (str.str ().c_str ());
            #endif

            // The resource graphic is now unowned.

            itr->m_ownerId.clear ();
        } // Endif.

    } // Endfor.

    return (status);
} // Endproc.


void    ResourceGraphicsCache::Dump (bool ownedOnly) const
{
    for (ResourceGraphicsList::const_iterator itr = m_resourceGraphicsList.begin ();
         itr != m_resourceGraphicsList.end ();
         ++itr)
    {
        if (!ownedOnly || itr->IsOwned ())
        {
            FolioOStringStream  str;
            str << Folio::Core::Util::DescribeDecimal (std::distance(m_resourceGraphicsList.begin (), itr), 8) << TXT(":")  
                << TXT(' ') << itr->Describe ()
                << std::endl;
            ::OutputDebugString (str.str ().c_str ());
        } // Endif.

    } // Endif.

} // Endproc.


void    ResourceGraphicsCache::DumpNumUsedBitmaps (bool ownedOnly) const
{
    UInt32  numGdiBitmaps       = 0;
    UInt32  numMaskedGdiBitmaps = 0;

    for (ResourceGraphicsList::const_iterator itr = m_resourceGraphicsList.begin ();
         itr != m_resourceGraphicsList.end ();
         ++itr)
    {
        if (!ownedOnly || itr->IsOwned ())
        {
            if (itr->m_resourceGraphicPtr->GetGdiBitmap ())
            {
                numGdiBitmaps++;
            } // Endif.

            if (itr->m_resourceGraphicPtr->GetMaskedGdiBitmap ())
            {
                numMaskedGdiBitmaps++;
            } // Endif.

        } // Endif.

    } // Endif.

    FolioOStringStream  str;
    str << TXT("NumGdiBitmaps: ") << numGdiBitmaps  
        << TXT(" NumGdiMaskedBitmaps: ") << numMaskedGdiBitmaps  
        << std::endl;
    ::OutputDebugString (str.str ().c_str ());
} // Endproc.


ResourceGraphicsCache::OwnerId  ResourceGraphicsCache::MakeOwnerId (UInt32 ownerId)
{
    FolioOStringStream  str;

    str << std::dec << ownerId;

    return (str.str ());
} // Endproc.


ResourceGraphicsCache::ResourceGraphicsList::iterator   ResourceGraphicsCache::Find (const DrawingElement::DrawingElementId&    drawingElementId,
                                                                                     UInt16                                     bitmapResourceId)
{
    return (std::find_if (m_resourceGraphicsList.begin (), m_resourceGraphicsList.end (), 
                          [drawingElementId, bitmapResourceId](const Cache& arg) 
                          {return (!arg.IsOwned ()                                                          &&
                                   (arg.m_resourceGraphicPtr->GetDrawingElementId () == drawingElementId)   &&
                                   (arg.m_resourceGraphicPtr->GetBitmapResourceId () == bitmapResourceId));}));
} // Endproc.


ResourceGraphicsCache::ResourceGraphicsList::iterator   ResourceGraphicsCache::Find (const ResourceGraphicPtr& resourceGraphicPtr)
{
    return (std::find_if (m_resourceGraphicsList.begin (), m_resourceGraphicsList.end (), 
                          [resourceGraphicPtr](const Cache& arg) 
                          {return (arg.m_resourceGraphicPtr == resourceGraphicPtr);}));
} // Endproc.


ResourceGraphicsCache::ResourceGraphicsList::iterator   ResourceGraphicsCache::Find (const ResourceGraphicPtr&  resourceGraphicPtr,
                                                                                     bool                       findOwnedResourceGraphic)
{
    return (std::find_if (m_resourceGraphicsList.begin (), m_resourceGraphicsList.end (), 
                          [findOwnedResourceGraphic, resourceGraphicPtr](const Cache& arg) 
                          {return ((findOwnedResourceGraphic == arg.IsOwned ()) && 
                                   (arg.m_resourceGraphicPtr == resourceGraphicPtr));}));
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/
