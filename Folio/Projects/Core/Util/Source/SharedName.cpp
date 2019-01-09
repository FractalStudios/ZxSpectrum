// "Home-made" includes.
#include    <Trace.h>
#include    "SharedName.h"

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * The default constructor.
 */
SharedName::SharedName ()
{
} // Endproc.


/**
 * The class constructor.
 *
 * @param [in] baseName
 * The base name of the shared name object.
 */
SharedName::SharedName (const FolioString& baseName)
{
    m_sharedName = TXT("Global\\");
    m_sharedName += baseName;
} // Endproc.


/**
 * The class destructor.
 */
SharedName::~SharedName ()
{
} // Endproc.


/**
 * Method that will assign a shared name based on a base name.
 *
 * @param [in] baseName
 * The base name of the shared name object.
 */
SharedName& SharedName::operator= (const FolioString& baseName)
{
    m_sharedName = TXT("Global\\");
    m_sharedName += baseName;

    return (*this);
} // Endproc.


/**
 * Method that will assign a shared name based on a raw name.
 *
 * @param [in] rawName
 * The raw name of the shared name object.
 */
void    SharedName::SetRawName (const FolioString& rawName)
{
    m_sharedName = rawName;
} // Endproc.


/**
 * Method that will return the shared name.
 *
 * @return
 * The shared name.
 */
const FolioCString  SharedName::GetSharedName () const
{
    return (m_sharedName);
} // Endproc.


/**
 * <b>SharedName</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>SharedName</b> to.
 *
 * @param [in] rhs
 * The <b>SharedName</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>SharedName</b>.
 */
FolioOStream&   operator<< (Folio::FolioOStream&    outputStream, 
                            const SharedName&       rhs)
{
    FOLIO_STREAM_ONLY_MEMBER(outputStream, rhs, m_sharedName);

    return (outputStream);
} // Endproc.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

/******************************* End of File *******************************/

