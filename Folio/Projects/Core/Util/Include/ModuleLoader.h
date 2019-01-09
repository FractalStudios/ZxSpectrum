#pragma once

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The module load implementation class.
/**
 * This class allows a module (Dynamic-link Library or <i>DLL</i>) to be
 * loaded/unloaded and for procedure addresses within the module to be
 * retrieved.
 *
 * This class does not support copy construction or assignment.
 */
class ModuleLoader
{
public:
    ModuleLoader ();
    ~ModuleLoader ();

    FolioStatus LoadLibrary (const FolioString& moduleName);
    FolioStatus UnloadLibrary ();

    FolioStatus QueryProcedureAddress (const FolioString&   procedureName,
                                       void*&               procedureAddress);

    FolioHandle GetModuleHandle () const;

private:
    FolioString m_moduleName;   ///< The module (library) name.
    FolioHandle m_moduleHandle; ///< The module (library) handle.

    /// Private copy constructor to prevent copying.
    ModuleLoader (const ModuleLoader& rhs);

    /// Private assignment operator to prevent copying.
    ModuleLoader& operator= (const ModuleLoader& rhs);

    // The stream operator is our friend.
    friend  FolioOStream&   operator<< (FolioOStream&       outputStream, 
                                        const ModuleLoader& rhs);
}; // Endclass.

// The stream operator.
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const ModuleLoader&     rhs);

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
