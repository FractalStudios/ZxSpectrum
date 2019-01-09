// "Home-made" includes.
#include    "BaseContainers.h"

namespace Folio
{

/**
 * Method that is used to obtain a description of a <b>FolioByteBuffer</b> type.
 *
 * @return
 * The description of a <b>FolioByteBuffer</b> type.
 */
FolioString GetTypeDescription (const FolioByteBuffer&)
{
    return (TXT("FolioByteBuffer"));
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>FolioStringList</b> type.
 *
 * @return
 * The description of a <b>FolioStringList</b> type.
 */
FolioString GetTypeDescription (const FolioStringList&)
{
    return (TXT("FolioStringList"));
} // Endproc.


/**
 * <b>FolioByteBuffer</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>FolioByteBuffer</b> to.
 *
 * @param [in] rhs
 * The <b>FolioByteBuffer</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>FolioByteBuffer</b>.
 */
FolioOStream&   operator<< (FolioOStream&           outputStream,
                            const FolioByteBuffer&  rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;
 
    outputStream << std::setbase(16)
                 << std::setfill(TXT('0'));

    FolioByteBuffer::const_iterator itrEnd = rhs.end ();

    for (FolioByteBuffer::const_iterator itr = rhs.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != rhs.begin ())
        {
            outputStream << FOLIO_MID_VARIABLE_PREFIX;
        } // Endif.
 
        outputStream << std::setw(2) << *itr;
    } // Endfor.
 
    outputStream << FOLIO_CONTAINER_SUFFIX;

    outputStream << std::setbase(10);

    return (outputStream);
} // Endproc.


/**
 * <b>FolioStringList</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>FolioStringList</b> to.
 *
 * @param [in] rhs
 * The <b>FolioStringList</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>FolioStringList</b>.
 */
FolioOStream&   operator<< (FolioOStream&           outputStream, 
                            const FolioStringList&  rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;
 
    FolioStringList::const_iterator itrEnd = rhs.end ();

    for (FolioStringList::const_iterator itr = rhs.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != rhs.begin ())
        {
            outputStream << FOLIO_MID_VARIABLE_PREFIX;
        } // Endif.
 
        outputStream << *itr;
    } // Endfor.
 
    outputStream << FOLIO_CONTAINER_SUFFIX;

    return (outputStream);
} // Endproc.

} // Endnamespace.

/******************************* End of File *******************************/
