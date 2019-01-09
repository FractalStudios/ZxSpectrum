#pragma once

// STL includes.
#include    <deque>
#include    <list>
#include    <map>
#include    <set>
#include    <vector>

// "Home-made" includes.
#include    "BaseStrings.h"
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

typedef std::vector<Byte>           FolioByteBuffer;    ///< Folio vector of bytes.
typedef std::vector<FolioString>    FolioStringList;    ///< Folio vector of strings.

// Type descriptions.
FolioString GetTypeDescription (const FolioByteBuffer&);
FolioString GetTypeDescription (const FolioStringList&);


/**
 * Method that is used to obtain a description of a <b>std::deque</b> type.
 *
 * @return
 * The description of a <b>std::deque</b> type.
 */
template <typename T, typename Allocator>
FolioString GetTypeDescription (const std::deque<T, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::deque<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::list</b> type.
 *
 * @return
 * The description of a <b>std::list</b> type.
 */
template <typename T, typename Allocator>
FolioString GetTypeDescription (const std::list<T, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::list<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::map</b> type.
 *
 * @return
 * The description of a <b>std::map</b> type.
 */
template <typename T, typename U, typename Traits, typename Allocator>
FolioString GetTypeDescription (const std::map<T, U, Traits, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::map<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::multimap</b> type.
 *
 * @return
 * The description of a <b>std::multimap</b> type.
 */
template <typename T, typename U, typename Traits, typename Allocator>
FolioString GetTypeDescription (const std::multimap<T, U, Traits, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::multimap<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::set</b> type.
 *
 * @return
 * The description of a <b>std::set</b> type.
 */
template <typename T, typename Traits, typename Allocator>
FolioString GetTypeDescription (const std::set<T, Traits, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::set<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::multiset</b> type.
 *
 * @return
 * The description of a <b>std::multiset</b> type.
 */
template <typename T, typename Traits, typename Allocator>
FolioString GetTypeDescription (const std::multiset<T, Traits, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::multiset<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::vector</b> type.
 *
 * @return
 * The description of a <b>std::vector</b> type.
 */
template <typename T, typename Allocator>
FolioString GetTypeDescription (const std::vector<T, Allocator>&)
{
    FolioOStringStream  outputStringStream;

    typename T  value;

    outputStringStream << TXT("std::vector<")
                       << GetTypeDescription (value)
                       << TXT(">");

    return (outputStringStream.str ());
} // Endproc.


// Stream operators.
FolioOStream&   operator<< (FolioOStream&           outputStream,
                            const FolioByteBuffer&  rhs);
FolioOStream&   operator<< (FolioOStream&           outputStream,
                            const FolioStringList&  rhs);


/**
 * <b>std::deque</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::deque</b> to.
 *
 * @param [in] rhs
 * The <b>std::deque</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::deque</b>.
 */
template <typename T, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                   outputStream,
                            const std::deque<T, Allocator>& rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::deque<T, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::deque<T, Allocator>::const_iterator itr = rhs.begin ();
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


/**
 * <b>std::list</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::list</b> to.
 *
 * @param [in] rhs
 * The <b>std::list</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::list</b>.
 */
template <typename T, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                   outputStream,
                            const std::list<T, Allocator>&  rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::list<T, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::list<T, Allocator>::const_iterator itr = rhs.begin ();
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


/**
 * <b>std::map</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::map</b> to.
 *
 * @param [in] rhs
 * The <b>std::map</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::map</b>.
 */
template <typename T, typename U, typename Traits, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                           outputStream,
                            const std::map<T, U, Traits, Allocator>&rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::map<T, U, Traits, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::map<T, U, Traits, Allocator>::const_iterator itr = rhs.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != rhs.begin ())
        {
            outputStream << FOLIO_MID_VARIABLE_PREFIX;
        } // Endif.
                      
        outputStream << itr->first
                     << FOLIO_VARIABLE_NAME_TO_VALUE
                     << itr->second;
    } // Endfor.
 
    outputStream << FOLIO_CONTAINER_SUFFIX;

    return (outputStream);
} // Endproc.


/**
 * <b>std::multimap</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::multimap</b> to.
 *
 * @param [in] rhs
 * The <b>std::multimap</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::multimap</b>.
 */
template <typename T, typename U, typename Traits, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                                   outputStream,
                            const std::multimap<T, U, Traits, Allocator>&   rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::multimap<T, U, Traits, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::multimap<T, U, Traits, Allocator>::const_iterator itr = rhs.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != rhs.begin ())
        {
            outputStream << FOLIO_MID_VARIABLE_PREFIX;
        } // Endif.
                      
        outputStream << itr->first
                     << FOLIO_VARIABLE_NAME_TO_VALUE
                     << itr->second;
    } // Endfor.
 
    outputStream << FOLIO_CONTAINER_SUFFIX;

    return (outputStream);
} // Endproc.


/**
 * <b>std::set</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::set</b> to.
 *
 * @param [in] rhs
 * The <b>std::set</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::set</b>.
 */
template <typename T, typename Traits, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                           outputStream,
                            const std::set<T, Traits, Allocator>&   rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::set<T, Traits, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::set<T, Traits, Allocator>::const_iterator itr = rhs.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != rhs.begin ())
        {
            outputStream << FOLIO_MID_VARIABLE_PREFIX;
        } // Endif.
                      
        outputStream << itr->first
                     << FOLIO_VARIABLE_NAME_TO_VALUE
                     << itr->second;
    } // Endfor.
 
    outputStream << FOLIO_CONTAINER_SUFFIX;

    return (outputStream);
} // Endproc.


/**
 * <b>std::multiset</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::multiset</b> to.
 *
 * @param [in] rhs
 * The <b>std::multiset</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::multiset</b>.
 */
template <typename T, typename Traits, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                               outputStream,
                            const std::multiset<T, Traits, Allocator>&  rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::multiset<T, Traits, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::multiset<T, Traits, Allocator>::const_iterator itr = rhs.begin ();
         itr != itrEnd;
         ++itr)
    {
        if (itr != rhs.begin ())
        {
            outputStream << FOLIO_MID_VARIABLE_PREFIX;
        } // Endif.
                      
        outputStream << itr->first
                     << FOLIO_VARIABLE_NAME_TO_VALUE
                     << itr->second;
    } // Endfor.
 
    outputStream << FOLIO_CONTAINER_SUFFIX;

    return (outputStream);
} // Endproc.


/**
 * <b>std::vector</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>std::vector</b> to.
 *
 * @param [in] rhs
 * The <b>std::vector</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>std::vector</b>.
 */
template <typename T, typename Allocator>
FolioOStream&   operator<< (FolioOStream&                       outputStream,
                            const std::vector<T, Allocator>&    rhs)
{
    outputStream << rhs.size () << FOLIO_CONTAINER_PREFIX;

    typename std::vector<T, Allocator>::const_iterator itrEnd = rhs.end ();

    for (typename std::vector<T, Allocator>::const_iterator itr = rhs.begin ();
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

#pragma pack(pop)

//****************************** End of File *******************************/
