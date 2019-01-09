// STL includes.
#include    <algorithm>
#include    <iterator>

// "Home-made" includes.
#include    "BaseStrings.h"

namespace Folio
{

/// Maximum number of characters that can be translated.
static  const   size_t  MAX_OUTPUT_BUFFER_SIZE = INT_MAX;

/**
 * This function attempts to convert the supplied wide character string to a
 * multibyte character string.
 *
 * @param [in] wideString
 * The wide character string to be converted.
 *
 * @return
 * Pointer to the multibyte character string, if successful. Zero
 * otherwise.
 */
char*   WideStringToMultiByteString (const wchar_t* wideString)
{
    char*   multiByteString = 0;    // Initialise!

    // Check if the wide character string is empty.

    if ((wideString == 0) || (*wideString == L'\0'))
    {
        // Conversion is simple - there's nothing to do.
    } // Endif.

    else
    {
        // Get the size of the required buffer by passing a NULL buffer.

        size_t  bufferSize = ::wcstombs (0,
                                         wideString,
                                         MAX_OUTPUT_BUFFER_SIZE);

        if (bufferSize != static_cast<size_t> (-1))
        {
            bufferSize++;   // Increment for NULL.

            multiByteString = new char [bufferSize];

            // Convert the wide character string.

            if ((bufferSize = ::wcstombs (multiByteString,
                                          wideString,
                                          bufferSize)) != static_cast<size_t> (-1))
            {
                // Add a trailing NULL.

                multiByteString [bufferSize] = '\0';
            } // Endif.

            else
            {
                // Failed to convert the wide character string.

                delete [] multiByteString;
                multiByteString = 0;
            } // Endelse.

        } // Endif.

    } // Endelse.

    return (multiByteString);
} // Endproc.


/**
 * This function attempts to convert the supplied multibyte character string to
 * a wide character string.
 *
 * @param [in] multiByteString
 * The multibyte character string to be converted.
 *
 * @return
 * Pointer to the wide character string, if successful. Zero otherwise.
 */
wchar_t*    MultiByteStringToWideString (const char* multiByteString)
{
    wchar_t*    wideString = 0;    // Initialise!

    // Check if the multibyte character string is empty.

    if ((multiByteString == 0) || (*multiByteString == '\0'))
    {
        // Conversion is simple - there's nothing to do.
    } // Endif.

    else
    {
        // Get the size of the required buffer by passing a NULL buffer.

        size_t  bufferSize = ::mbstowcs (0,
                                         multiByteString,
                                         MAX_OUTPUT_BUFFER_SIZE);

        if (bufferSize != static_cast<size_t> (-1))
        {
            bufferSize++;   // Increment for NULL.

            wideString = new wchar_t [bufferSize];

            // Convert the multibyte character string.

            if ((bufferSize = ::mbstowcs (wideString,
                                          multiByteString,
                                          bufferSize)) != static_cast<size_t> (-1))
            {
                // Add a trailing NULL.

                wideString [bufferSize] = L'\0';
            } // Endif.

            else
            {
                // Failed to convert the multibyte character string.

                delete [] wideString;
                wideString = 0;
            } // Endelse.

        } // Endif.

    } // Endelse.

    return (wideString);
} // Endproc.


/**
 * Class constructor that constructs an empty <b>FolioString</b>.
 */
FolioString::FolioString ()
: std::basic_string<Char, std::char_traits<Char> >()
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioString</b> from a specified full
 * or partial C-string with a specified number of characters.
 *
 * @param [in] ptr
 * The C-string whose characters are to be used to initialize the string
 * being constructed. This value cannot be a NULL pointer.
 *
 * @param [in] count
 * The number of characters to be copied into the string being constructed.
 */
FolioString::FolioString (const value_type* ptr,
                          size_type         count)
: std::basic_string<Char, std::char_traits<Char> >(ptr, count)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioString</b> from a specified
 * C-string.
 *
 * @param [in] ptr
 * The C-string whose characters are to be used to initialize the string
 * being constructed. This value cannot be a NULL pointer.
 */
FolioString::FolioString (const value_type* ptr)
: std::basic_string<Char, std::char_traits<Char> >(ptr)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioString</b> with a specified number
 * of characters with a specific value.
 *
 * @param [in] count
 * The number of characters in the <b>FolioString</b>.
 *
 * @param [in] val
 * The value of the characters in the <b>FolioString</b>.
 */
FolioString::FolioString (size_type     count,
                          value_type    val)
: std::basic_string<Char, std::char_traits<Char> >(count, val)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioString</b> from a range of
 * characters.
 *
 * @param [in] first
 * The pointer to the first element in the range of characters to be
 * copied.
 *
 * @param [in] last
 * The pointer to the first element beyond the range of characters to be
 * copied.
 */
FolioString::FolioString (const_pointer first,
                          const_pointer last)
: std::basic_string<Char, std::char_traits<Char> >(first, last)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioString</b> from a range of
 * characters.
 *
 * @param [in] first
 * The iterator to the first element in the range of characters to be
 * copied.
 *
 * @param [in] last
 * The iterator to the first element beyond the range of characters to be
 * copied.
 */
FolioString::FolioString (const_iterator    first,
                          const_iterator    last)
: std::basic_string<Char, std::char_traits<Char> >(first, last)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioString</b> from all or part of an
 * object of type <b>FolioString</b>.
 *
 * @param [in] var
 * The <b>FolioString</b>.
 *
 * @param [in] index
 * The index of a character in the specified string that is the first to
 * be used to initialize character values for the strint being constructed.
 *
 * @param [in] count
 * The number of characters to be copied into the string being constructed.
 */
FolioString::FolioString (const FolioString&   var,
                          size_type            index,
                          size_type            count)
: std::basic_string<Char, std::char_traits<Char> >(var, index, count)
{
} // Endproc.


#ifdef FOLIO_ANSI
/**
 * Class constructor that constructs a <b>FolioString</b> from a
 * <b>FolioWideString</b>.
 *
 * @param [in] var
 * The <b>FolioWideString</b>.
 */
FolioString::FolioString (const FolioWideString& var)
{
    // Convert the FolioWideString to a FolioString.

    char*   multiByteString = WideStringToMultiByteString (var.c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        this->assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioWideString</b> to a
 * <b>FolioString</b>.
 *
 * @param [in] rhs
 * The <b>FolioWideString</b>.
 */
FolioString& FolioString::operator= (const FolioWideString& rhs)
{
    // Convert the FolioWideString to a FolioString.

    char*   multiByteString = WideStringToMultiByteString (rhs.c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        this->assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioString</b> to a
 * <b>FolioWideString</b>.
 */
FolioString::operator FolioWideString () const
{
    FolioWideString folioWideString;

    // Convert the FolioString to a FolioWideString.

    wchar_t*    wideString = MultiByteStringToWideString (this->c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        folioWideString.assign (wideString);

        delete [] wideString;
    } // Endif.

    return (folioWideString);
} // Endproc.
#else
/**
 * Class constructor that constructs a <b>FolioString</b> from a 
 * <b>FolioNarrowString</b>.
 *
 * @param [in] var
 * The <b>FolioNarrowString</b>.
 */
FolioString::FolioString (const FolioNarrowString& var)
{
    // Convert the FolioNarrowString to a FolioString.

    wchar_t*    wideString = MultiByteStringToWideString (var.c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        this->assign (wideString);

        delete [] wideString;
    } // Endif.

} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioNarrowString</b> to a
 * <b>FolioString</b>.
 *
 * @param [in] rhs
 * The <b>FolioNarrowString</b>.
 */
FolioString& FolioString::operator= (const FolioNarrowString& rhs)
{
    // Convert the FolioNarrowString to a FolioString.

    wchar_t*    wideString = MultiByteStringToWideString (rhs.c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        this->assign (wideString);

        delete [] wideString;
    } // Endif.

    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioString</b> to a
 * <b>FolioNarrowString</b>.
 */
FolioString::operator FolioNarrowString () const
{
    FolioNarrowString folioNarrowString;

    // Convert the FolioString to a FolioNarrowString.

    char*   multiByteString = WideStringToMultiByteString (this->c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        folioNarrowString.assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

    return (folioNarrowString);
} // Endproc.
#endif


/**
 * Class constructor that constructs a <b>FolioString</b> from a
 * <b>FolioCString</b>.
 *
 * @param [in] var
 * The <b>FolioCString</b>.
 */
FolioString::FolioString (const FolioCString& var)
: std::basic_string<Char, std::char_traits<Char> >(var)
{
} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioCString</b> to a 
 * <b>FolioString</b>.
 *
 * @param [in] rhs
 * The <b>FolioCString</b>.
 */
FolioString& FolioString::operator= (const FolioCString& rhs)
{
    this->assign (rhs);

    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioString</b> to a 
 * <b>FolioCString</b>.
 */
FolioString::operator const FolioCString () const
{
    return (const_cast<FolioCString> (this->c_str ()));
} // Endproc.


/**
 * Class destructor.
 */
FolioString::~FolioString ()
{
} // Endproc.


/**
 * Method that will convert the <b>FolioString</b> to uppercase.
 */
void    FolioString::ConvertToUpperCase ()
{
    std::transform (this->begin (),
                    this->end (),
                    this->begin (),
                    ::toupper);
} // Endproc.


/**
 * Method that will return an uppercase copy of the <b>FolioString</b>.
 *
 * @return
 * An uppercase copy of the <b>FolioString</b>.
 */
FolioString FolioString::ToUpperCase () const
{
    FolioString folioString;

    std::transform (this->begin (),
                    this->end (),
                    std::back_inserter(folioString),
                    ::toupper);

    return (folioString);
} // Endproc.


/**
 * Method that will convert the <b>FolioString</b> to lowercase.
 */
void    FolioString::ConvertToLowerCase ()
{
    std::transform (this->begin (),
                    this->end (),
                    this->begin (),
                    ::tolower);
} // Endproc.


/**
 * Method that will return a lowercase copy of the <b>FolioString</b>.
 *
 * @return
 * A lowercase copy of the <b>FolioString</b>.
 */
FolioString FolioString::ToLowerCase () const
{
    FolioString folioString;

    std::transform (this->begin (),
                    this->end (),
                    std::back_inserter(folioString),
                    ::tolower);

    return (folioString);
} // Endproc.


/**
 * Method that will perform a case insensitive comparison with a specified
 * string to determine if the two strings are equal or if one is
 * lexicographically less than the other.
 *
 * @param [in] folioString
 * The <b>FolioString</b> that is to be compared to the operands string.
 *
 * @return
 * The possible return values are:<ul>
 * <li>A negative value if the operand string is less than the parameter
 *     string.
 * <li>Zero if the two strings are equal
 * <li>A positive value if the operand string is greater than the parameter
 *     string.
 * </ul>
 */
int     FolioString::InsensitiveCompare (const FolioString& folioString) const
{
    return (STRICMP(this->c_str (), folioString.c_str ()));
} // Endproc.


/**
 * Class constructor that constructs an empty <b>FolioNarrowString</b>.
 */
FolioNarrowString::FolioNarrowString ()
: std::basic_string<char, std::char_traits<char> >()
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from a 
 * specified full or partial C-string with a specified number of characters.
 *
 * @param [in] ptr
 * The C-string whose characters are to be used to initialize the string
 * being constructed. This value cannot be a NULL pointer.
 *
 * @param [in] count
 * The number of characters to be copied into the string being constructed.
 */
FolioNarrowString::FolioNarrowString (const value_type* ptr,
                                      size_type         count)
: std::basic_string<char, std::char_traits<char> >(ptr, count)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from a 
 * specified C-string.
 *
 * @param [in] ptr
 * The C-string whose characters are to be used to initialize the string
 * being constructed. This value cannot be a NULL pointer.
 */
FolioNarrowString::FolioNarrowString (const value_type* ptr)
: std::basic_string<char, std::char_traits<char> >(ptr)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> with a 
 * specified number of characters with a specific value.
 *
 * @param [in] count
 * The number of characters in the <b>FolioNarrowString</b>.
 *
 * @param [in] val
 * The value of the characters in the <b>FolioNarrowString</b>.
 */
FolioNarrowString::FolioNarrowString (size_type     count,
                                      value_type    val)
: std::basic_string<char, std::char_traits<char> >(count, val)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from a range of
 * characters.
 *
 * @param [in] first
 * The pointer to the first element in the range of characters to be
 * copied.
 *
 * @param [in] last
 * The pointer to the first element beyond the range of characters to be
 * copied.
 */
FolioNarrowString::FolioNarrowString (const_pointer first,
                                      const_pointer last)
: std::basic_string<char, std::char_traits<char> >(first, last)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from a range of
 * characters.
 *
 * @param [in] first
 * The iterator to the first element in the range of characters to be
 * copied.
 *
 * @param [in] last
 * The iterator to the first element beyond the range of characters to be
 * copied.
 */
FolioNarrowString::FolioNarrowString (const_iterator    first,
                                      const_iterator    last)
: std::basic_string<char, std::char_traits<char> >(first, last)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from all or 
 * part of an object of type <b>FolioNarrowString</b>.
 *
 * @param [in] var
 * The <b>FolioNarrowString</b>.
 *
 * @param [in] index
 * The index of a character in the specified string that is the first to
 * be used to initialize character values for the strint being constructed.
 *
 * @param [in] count
 * The number of characters to be copied into the string being constructed.
 */
FolioNarrowString::FolioNarrowString (const FolioNarrowString&  var,
                                      size_type                 index,
                                      size_type                 count)
: std::basic_string<char, std::char_traits<char> >(var, index, count)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from a
 * <b>FolioString</b>.
 *
 * @param [in] var
 * The <b>FolioString</b>.
 */
FolioNarrowString::FolioNarrowString (const FolioString& var)
{
#ifdef FOLIO_ANSI    
    this->assign (var.begin (), var.end ());
#else
    // Convert the FolioString to a FolioNarrowString.

    char*   multiByteString = WideStringToMultiByteString (var.c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        this->assign (multiByteString);

        delete [] multiByteString;
    } // Endif.
#endif
} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioString</b> to a
 * <b>FolioNarrowString</b>.
 *
 * @param [in] rhs
 * The <b>FolioString</b>.
 */
FolioNarrowString& FolioNarrowString::operator= (const FolioString& rhs)
{
#ifdef FOLIO_ANSI    
    this->assign (rhs.begin (), rhs.end ());
#else
    // Convert the FolioString to a FolioNarrowString.

    char*   multiByteString = WideStringToMultiByteString (rhs.c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        this->assign (multiByteString);

        delete [] multiByteString;
    } // Endif.
#endif
    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioNarrowString</b> to a
 * <b>FolioString</b>.
 */
FolioNarrowString::operator FolioString () const
{
#ifdef FOLIO_ANSI    
    return (*this);
#else
    FolioString folioString;

    // Convert the FolioNarrowString to a FolioString.

    wchar_t*    wideString = MultiByteStringToWideString (this->c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        folioString.assign (wideString);

        delete [] wideString;
    } // Endif.

    return (folioString);
#endif
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioNarrowString</b> from a
 * <b>FolioWideString</b>.
 *
 * @param [in] var
 * The <b>FolioWideString</b>.
 */
FolioNarrowString::FolioNarrowString (const FolioWideString& var)
{
    // Convert the FolioWideString to a FolioNarrowString.

    char*   multiByteString = WideStringToMultiByteString (var.c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        this->assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioWideString</b> to a
 * <b>FolioNarrowString</b>.
 *
 * @param [in] rhs
 * The <b>FolioWideString</b>.
 */
FolioNarrowString& FolioNarrowString::operator= (const FolioWideString& rhs)
{
    // Convert the FolioWideString to a FolioNarrowString.

    char*   multiByteString = WideStringToMultiByteString (rhs.c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        this->assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioNarrowString</b> to a
 * <b>FolioWideString</b>.
 */
FolioNarrowString::operator FolioWideString () const
{
    FolioWideString folioWideString;

    // Convert the FolioNarrowString to a FolioWideString.

    wchar_t*    wideString = MultiByteStringToWideString (this->c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        folioWideString.assign (wideString);

        delete [] wideString;
    } // Endif.

    return (folioWideString);
} // Endproc.


/**
 * Class destructor.
 */
FolioNarrowString::~FolioNarrowString ()
{
} // Endproc.


/**
 * Class constructor that constructs an empty <b>FolioWideString</b>.
 */
FolioWideString::FolioWideString ()
: std::basic_string<wchar_t, std::char_traits<wchar_t> >()
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from a specified
 * full or partial C-string with a specified number of characters.
 *
 * @param [in] ptr
 * The C-string whose characters are to be used to initialize the string
 * being constructed. This value cannot be a NULL pointer.
 *
 * @param [in] count
 * The number of characters to be copied into the string being constructed.
 */
FolioWideString::FolioWideString (const value_type* ptr,
                                  size_type         count)
: std::basic_string<wchar_t, std::char_traits<wchar_t> >(ptr, count)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from a specified
 * C-string.
 *
 * @param [in] ptr
 * The C-string whose characters are to be used to initialize the string
 * being constructed. This value cannot be a NULL pointer.
 */
FolioWideString::FolioWideString (const value_type* ptr)
: std::basic_string<wchar_t, std::char_traits<wchar_t> >(ptr)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> with a specified
 * number of characters with a specific value.
 *
 * @param [in] count
 * The number of characters in the <b>FolioWideString</b>.
 *
 * @param [in] val
 * The value of the characters in the <b>FolioWideString</b>.
 */
FolioWideString::FolioWideString (size_type     count,
                                  value_type    val)
: std::basic_string<wchar_t, std::char_traits<wchar_t> >(count, val)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from a range of
 * characters.
 *
 * @param [in] first
 * The pointer to the first element in the range of characters to be
 * copied.
 *
 * @param [in] last
 * The pointer to the first element beyond the range of characters to be
 * copied.
 */
FolioWideString::FolioWideString (const_pointer first,
                                  const_pointer last)
: std::basic_string<wchar_t, std::char_traits<wchar_t> >(first, last)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from a range of
 * characters.
 *
 * @param [in] first
 * The iterator to the first element in the range of characters to be
 * copied.
 *
 * @param [in] last
 * The iterator to the first element beyond the range of characters to be
 * copied.
 */
FolioWideString::FolioWideString (const_iterator    first,
                                  const_iterator    last)
: std::basic_string<wchar_t, std::char_traits<wchar_t> >(first, last)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from all or part 
 * of an object of type <b>FolioWideString</b>.
 *
 * @param [in] var
 * The <b>FolioWideString</b>.
 *
 * @param [in] index
 * The index of a character in the specified string that is the first to
 * be used to initialize character values for the strint being constructed.
 *
 * @param [in] count
 * The number of characters to be copied into the string being constructed.
 */
FolioWideString::FolioWideString (const FolioWideString&    var,
                                  size_type                 index,
                                  size_type                 count)
: std::basic_string<wchar_t, std::char_traits<wchar_t> >(var, index, count)
{
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from a
 * <b>FolioString</b>.
 *
 * @param [in] var
 * The <b>FolioString</b>.
 */
FolioWideString::FolioWideString (const FolioString& var)
{
#ifdef FOLIO_ANSI    
    // Convert the FolioString to a FolioWideString.

    wchar_t*    wideString = MultiByteStringToWideString (var.c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        this->assign (wideString);

        delete [] wideString;
    } // Endif.
#else
    this->assign (var.begin (), var.end ());
#endif
} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioString</b> to a
 * <b>FolioWideString</b>.
 *
 * @param [in] rhs
 * The <b>FolioString</b>.
 */
FolioWideString& FolioWideString::operator= (const FolioString& rhs)
{
#ifdef FOLIO_ANSI    
    // Convert the FolioString to a FolioWideString.

    wchar_t*    wideString = MultiByteStringToWideString (rhs.c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        this->assign (wideString);

        delete [] wideString;
    } // Endif.
#else
    this->assign (rhs.begin (), rhs.end ());
#endif
    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioWideString</b> to a
 * <b>FolioString</b>.
 */
FolioWideString::operator FolioString () const
{
#ifdef FOLIO_ANSI    
    FolioString folioString;

    // Convert the FolioWideString to a FolioString.

    char*   multiByteString = WideStringToMultiByteString (this->c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        folioString.assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

    return (folioString);
#else
    return (*this);
#endif
} // Endproc.


/**
 * Class constructor that constructs a <b>FolioWideString</b> from a
 * <b>FolioNarrowString</b>.
 *
 * @param [in] var
 * The <b>FolioNarrowString</b>.
 */
FolioWideString::FolioWideString (const FolioNarrowString& var)
{
    // Convert the FolioNarrowString to a FolioWideString.

    wchar_t*    wideString = MultiByteStringToWideString (var.c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        this->assign (wideString);

        delete [] wideString;
    } // Endif.

} // Endproc.


/**
 * Assignment operator that assigns a specified <b>FolioNarrowString</b> to a
 * <b>FolioWideString</b>.
 *
 * @param [in] rhs
 * The <b>FolioNarrowString</b>.
 */
FolioWideString& FolioWideString::operator= (const FolioNarrowString& rhs)
{
    // Convert the FolioNarrowString to a FolioWideString.

    wchar_t*    wideString = MultiByteStringToWideString (rhs.c_str ());

    if (wideString)
    {
        // Copy the converted string (and then delete it).

        this->assign (wideString);

        delete [] wideString;
    } // Endif.

    return (*this);
} // Endproc.


/**
 * Cast operator that implicitly converts a <b>FolioWideString</b> to a
 * <b>FolioNarrowString</b>.
 */
FolioWideString::operator FolioNarrowString () const
{
    FolioNarrowString folioNarrowString;

    // Convert the FolioWideString to a FolioNarrowString.

    char*   multiByteString = WideStringToMultiByteString (this->c_str ());

    if (multiByteString)
    {
        // Copy the converted string (and then delete it).

        folioNarrowString.assign (multiByteString);

        delete [] multiByteString;
    } // Endif.

    return (folioNarrowString);
} // Endproc.


/**
 * Class destructor.
 */
FolioWideString::~FolioWideString ()
{
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::string</b> type.
 *
 * @return
 * The description of a <b>std::string</b> type.
 */
FolioString GetTypeDescription (const std::string&)
{
    return (TXT("std::string"));
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>std::wstring</b> type.
 *
 * @return
 * The description of a <b>std::wstring</b> type.
 */
FolioString GetTypeDescription (const std::wstring&)
{
    return (TXT("std::wstring"));
} // Endproc.


/**
 * Method that is used to obtain a description of a <b>FolioString</b> type.
 *
 * @return
 * The description of a <b>FolioString</b> type.
 */
FolioString GetTypeDescription (const FolioString&)
{
    return (TXT("FolioString"));
} // Endproc.


#ifdef FOLIO_ANSI    
/**
 * Method that is used to obtain a description of a <b>FolioWideString</b> type.
 *
 * @return
 * The description of a <b>FolioWideString</b> type.
 */
FolioString GetTypeDescription (const FolioWideString&)
{
    return (TXT("FolioWideString"));
} // Endproc.
#else
/**
 * Method that is used to obtain a description of a <b>FolioNarrowString</b> type.
 *
 * @return
 * The description of a <b>FolioNarrowString</b> type.
 */
FolioString GetTypeDescription (const FolioNarrowString&)
{
    return (TXT("FolioNarrowString"));
} // Endproc.
#endif


/**
 * <b>FolioString</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>FolioString</b> to.
 *
 * @param [in] rhs
 * The <b>FolioString</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>FolioString</b>.
 */
FolioOStream&   operator<< (FolioOStream&       outputStream, 
                            const FolioString&  rhs)
{
    outputStream << rhs.c_str ();

    return (outputStream);
} // Endproc.


#ifdef FOLIO_ANSI    
/**
 * <b>FolioWideString</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>FolioWideString</b> to.
 *
 * @param [in] rhs
 * The <b>FolioWideString</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>FolioWideString</b>.
 */
FolioOStream&   operator<< (FolioOStream&           outputStream, 
                            const FolioWideString&  rhs)
{
    outputStream << rhs.c_str ();

    return (outputStream);
} // Endproc.

#else

/**
 * <b>FolioNarrowString</b> output stream operator.
 *
 * @param [in, out] outputStream
 * The output stream to add the <b>FolioNarrowString</b> to.
 *
 * @param [in] rhs
 * The <b>FolioNarrowString</b> to add to the output stream.
 *
 * @return
 * The output stream with added <b>FolioNarrowString</b>.
 */
FolioOStream&   operator<< (FolioOStream&               outputStream, 
                            const FolioNarrowString&    rhs)
{
    outputStream << rhs.c_str ();

    return (outputStream);
} // Endproc.
#endif

} // Endnamespace.

/******************************* End of File *******************************/
