#pragma once

// STL includes.
#include    <string>

// "Home-made" includes.
#include    "BaseStreams.h"
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

// Routines.
extern  char*       WideStringToMultiByteString (const wchar_t* wideString);
extern  wchar_t*    MultiByteStringToWideString (const char* multiByteString);

class FolioNarrowString;    // Declare class prototypes.
class FolioWideString;

/**
 * The <b>FolioString</b> class is a class that inherits from
 * <b>std::basic_string&lt;Char&gt;</b>.
 */
class FolioString : public std::basic_string<Char, std::char_traits<Char> >
{
public:
    FolioString ();
    FolioString (const value_type*  ptr,
                 size_type          count);
    FolioString (const value_type* ptr);
    FolioString (size_type  count,
                 value_type val);

    /**
     * Class constructor that constructs a <b>FolioString</b> from a range of
     * characters.
     *
     * @param [in] first
     * The position of the first element in the range of characters to be
     * copied.
     *
     * @param [in] last
     * The position of the first element beyond the range of characters to be
     * copied.
     */
    template <typename InputIterator>
    FolioString (InputIterator  first,
                 InputIterator  last)
    : std::basic_string<Char, std::char_traits<Char> >(first, last)
    {
    } // Endproc.

    FolioString (const_pointer  first,
                 const_pointer  last);
    FolioString (const_iterator first,
                 const_iterator last);

    FolioString (const FolioString& var,
                 size_type          index,
                 size_type          count = std::basic_string<Char, std::char_traits<Char> >::npos);

    /**
     * Class constructor that constructs a <b>FolioString</b> from a
     * std::basic_string&lt;Char&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;Char&gt;.
     */
    template <typename Allocator>
    FolioString (const std::basic_string<Char, std::char_traits<Char>, Allocator>& var)
    : std::basic_string<Char, std::char_traits<Char> >(var.begin (), var.end ())
    {
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioString</b> to a
     * std::basic_string&lt;Char&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<Char, std::char_traits<Char>, Allocator> () const
    {
        return (std::basic_string<Char, std::char_traits<Char>, Allocator> (this->begin (), this->end ()));
    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;Char&gt; to a <b>FolioString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;Char&gt;.
     */
    template <typename Allocator>
    FolioString& operator= (const std::basic_string<Char, std::char_traits<Char>, Allocator>& rhs)
    {
        this->assign (rhs.begin (), rhs.end ());
        return (*this);
    } // Endproc.

#ifdef FOLIO_ANSI    
    /**
     * Class constructor that constructs a <b>FolioString</b> from a
     * std::basic_string&lt;wchar_t&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    FolioString (const std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>& var)
    : std::basic_string<Char, std::char_traits<Char> >()
    {
        char*   multiByteString = WideStringToMultiByteString (var.c_str ());

        if (multiByteString)
        {
            this->assign (multiByteString);

            delete [] multiByteString;
        } // Endif.

    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;wchar_t&gt; to a <b>FolioString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    FolioString& operator= (const std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>& rhs)
    {
        char*   multiByteString = WideStringToMultiByteString (rhs.c_str ());

        if (multiByteString)
        {
            this->assign (multiByteString);

            delete [] multiByteString;
        } // Endif.

        return (*this);
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioString</b> to a
     * std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator> () const
    {
        std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>  string;

        wchar_t*    wideString = MultiByteStringToWideString (this->c_str ());

        if (wideString)
        {
            string.assign (wideString);

            delete [] wideString;
        } // Endif.

        return (string);
    } // Endproc.

    FolioString (const FolioWideString& var);
    FolioString& operator= (const FolioWideString& rhs);
    operator FolioWideString () const;
#else
    /**
     * Class constructor that constructs a <b>FolioString</b> from a
     * std::basic_string&lt;char&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    FolioString (const std::basic_string<char, std::char_traits<char>, Allocator>& var)
    : std::basic_string<Char, std::char_traits<Char> >()
    {
        wchar_t*    wideString = MultiByteStringToWideString (var.c_str ());

        if (wideString)
        {
            this->assign (wideString);

            delete [] wideString;
        } // Endif.

    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;char&gt; to a <b>FolioString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    FolioString& operator= (const std::basic_string<char, std::char_traits<char>, Allocator>& rhs)
    {
        wchar_t*    wideString = MultiByteStringToWideString (rhs.c_str ());

        if (wideString)
        {
            this->assign (wideString);

            delete [] wideString;
        } // Endif.

        return (*this);
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioString</b> to a
     * std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<char, std::char_traits<char>, Allocator> () const
    {
        std::basic_string<char, std::char_traits<char>, Allocator>  string;

        char*   multiByteString = WideStringToMultiByteString (this->c_str ());

        if (multiByteString)
        {
            string.assign (multiByteString);

            delete [] multiByteString;
        } // Endif.

        return (string);
    } // Endproc.

    FolioString (const FolioNarrowString& var);
    FolioString& operator= (const FolioNarrowString& rhs);
    operator FolioNarrowString () const;
#endif

    FolioString (const FolioCString& var);
    FolioString& operator= (const FolioCString& rhs);
    operator const FolioCString () const;

    virtual ~FolioString ();

    void        ConvertToUpperCase ();
    FolioString ToUpperCase () const;
    void        ConvertToLowerCase ();
    FolioString ToLowerCase () const;

    int InsensitiveCompare (const FolioString& folioString) const;
}; // Endclass.


/**
 * The <b>FolioNarrowString</b> class is a class that inherits from
 * <b>std::basic_string&lt;char&gt;</b>.
 */
class FolioNarrowString : public std::basic_string<char, std::char_traits<char> >
{
public:
    FolioNarrowString ();
    FolioNarrowString (const value_type*    ptr,
                       size_type            count);
    FolioNarrowString (const value_type* ptr);
    FolioNarrowString (size_type    count,
                       value_type   val);

    /**
     * Class constructor that constructs a <b>FolioNarrowString</b> from a range of
     * characters.
     *
     * @param [in] first
     * The position of the first element in the range of characters to be
     * copied.
     *
     * @param [in] last
     * The position of the first element beyond the range of characters to be
     * copied.
     */
    template <typename InputIterator>
    FolioNarrowString (InputIterator    first,
                       InputIterator    last)
    : std::basic_string<char, std::char_traits<char> >(first, last)
    {
    } // Endproc.

    FolioNarrowString (const_pointer    first,
                       const_pointer    last);
    FolioNarrowString (const_iterator   first,
                       const_iterator   last);

    FolioNarrowString (const FolioNarrowString& var,
                       size_type                index,
                       size_type                count = std::basic_string<char, std::char_traits<char> >::npos);

    /**
     * Class constructor that constructs a <b>FolioNarrowString</b> from a
     * std::basic_string&lt;char&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    FolioNarrowString (const std::basic_string<char, std::char_traits<char>, Allocator>& var)
    : std::basic_string<char, std::char_traits<char> >(var.begin (), var.end ())
    {
    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;char&gt; to a <b>FolioNarrowString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    FolioNarrowString& operator= (const std::basic_string<char, std::char_traits<char>, Allocator>& rhs)
    {
        this->assign (rhs.begin (), rhs.end ());
        return (*this);
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioNarrowString</b> to a
     * std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<char, std::char_traits<char>, Allocator> () const
    {
        return (std::basic_string<char, std::char_traits<char>, Allocator> (this->begin (), this->end ()));
    } // Endproc.

    /**
     * Class constructor that constructs a <b>FolioNarrowString</b> from a
     * std::basic_string&lt;wchar_t&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    FolioNarrowString (const std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>& var)
    : std::basic_string<char, std::char_traits<char> > ()
    {
        char*   multiByteString = WideStringToMultiByteString (var.c_str ());

        if (multiByteString)
        {
            this->assign (multiByteString);

            delete [] multiByteString;
        } // Endif.

    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;wchar_t&gt; to a <b>FolioNarrowString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    FolioNarrowString& operator= (const std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>& rhs)
    {
        char*   multiByteString = WideStringToMultiByteString (rhs.c_str ());

        if (multiByteString)
        {
            this->assign (multiByteString);

            delete [] multiByteString;
        } // Endif.

        return (*this);
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioNarrowString</b> to a
     * std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator> () const
    {
        std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>  string;

        wchar_t*    wideString = MultiByteStringToWideString (this->c_str ());

        if (wideString)
        {
            string.assign (wideString);

            delete [] wideString;
        } // Endif.

        return (string);
    } // Endproc.

    FolioNarrowString (const FolioString& var);
    FolioNarrowString& operator= (const FolioString& rhs);
    operator FolioString () const;

    FolioNarrowString (const FolioWideString& var);
    FolioNarrowString& operator= (const FolioWideString& rhs);
    operator FolioWideString () const;

    virtual ~FolioNarrowString ();
}; // Endclass.


/**
 * The <b>FolioWideString</b> class is a class that inherits from
 * <b>std::basic_string&lt;wchar_t&gt;</b>.
 */
class FolioWideString : public std::basic_string<wchar_t, std::char_traits<wchar_t> >
{
public:
    FolioWideString ();
    FolioWideString (const value_type*  ptr,
                     size_type          count);
    FolioWideString (const value_type* ptr);
    FolioWideString (size_type  count,
                     value_type val);

    /**
     * Class constructor that constructs a <b>FolioWideString</b> from a range 
     * of characters.
     *
     * @param [in] first
     * The position of the first element in the range of characters to be
     * copied.
     *
     * @param [in] last
     * The position of the first element beyond the range of characters to be
     * copied.
     */
    template <typename InputIterator>
    FolioWideString (InputIterator  first,
                     InputIterator  last)
    : std::basic_string<wchar_t, std::char_traits<wchar_t> >(first, last)
    {
    } // Endproc.

    FolioWideString (const_pointer  first,
                     const_pointer  last);
    FolioWideString (const_iterator first,
                     const_iterator last);

    FolioWideString (const FolioWideString& var,
                     size_type              index,
                     size_type              count = std::basic_string<wchar_t, std::char_traits<wchar_t> >::npos);

    /**
     * Class constructor that constructs a <b>FolioWideString</b> from a
     * std::basic_string&lt;wchar_t&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    FolioWideString (const std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>& var)
    : std::basic_string<wchar_t, std::char_traits<wchar_t> >(var.begin (), var.end ())
    {
    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;wchar_t&gt; to a <b>FolioWideString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    FolioWideString& operator= (const std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator>& rhs)
    {
        this->assign (rhs.begin (), rhs.end ());
        return (*this);
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioWideString</b> to a
     * std::basic_string&lt;wchar_t&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator> () const
    {
        return (std::basic_string<wchar_t, std::char_traits<wchar_t>, Allocator> (this->begin (), this->end ()));
    } // Endproc.

    /**
     * Class constructor that constructs a <b>FolioWideString</b> from a
     * std::basic_string&lt;char&gt;.
     *
     * @param [in] var
     * The std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    FolioWideString (const std::basic_string<char, std::char_traits<char>, Allocator>& var)
    : std::basic_string<wchar_t, std::char_traits<wchar_t> > ()
    {
        wchar_t*    wideString = MultiByteStringToWideString (rhs.c_str ());

        if (wideString)
        {
            this->assign (wideString);

            delete [] wideString;
        } // Endif.

    } // Endproc.

    /**
     * Assignment operator that assigns a specified
     * std::basic_string&lt;char&gt; to a <b>FolioWideString</b>.
     *
     * @param [in] rhs
     * The std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    FolioWideString& operator= (const std::basic_string<char, std::char_traits<char>, Allocator>& rhs)
    {
        wchar_t*    wideString = MultiByteStringToWideString (rhs.c_str ());

        if (wideString)
        {
            this->assign (wideString);

            delete [] wideString;
        } // Endif.

        return (*this);
    } // Endproc.

    /**
     * Cast operator that implicitly converts a <b>FolioWideString</b> to a
     * std::basic_string&lt;char&gt;.
     */
    template <typename Allocator>
    operator std::basic_string<char, std::char_traits<char>, Allocator> () const
    {
        std::basic_string<char, std::char_traits<char>, Allocator>  string;

        char*   multiByteString = WideStringToMultiByteString (this->c_str ());

        if (multiByteString)
        {
            string.assign (multiByteString);

            delete [] multiByteString;
        } // Endif.

        return (string);
    } // Endproc.

    FolioWideString (const FolioString& var);
    FolioWideString& operator= (const FolioString& rhs);
    operator FolioString () const;

    FolioWideString (const FolioNarrowString& var);
    FolioWideString& operator= (const FolioNarrowString& rhs);
    operator FolioNarrowString () const;

    virtual ~FolioWideString ();
}; // Endclass.


// Type descriptions.
FolioString GetTypeDescription (const std::string&);
FolioString GetTypeDescription (const std::wstring&);
FolioString GetTypeDescription (const FolioString&);

#ifdef FOLIO_ANSI    
    FolioString GetTypeDescription (const FolioWideString&);
#else
    FolioString GetTypeDescription (const FolioNarrowString&);
#endif


// Stream operators.
FolioOStream&   operator<< (FolioOStream&       outputStream,
                            const FolioString&  rhs);

#ifdef FOLIO_ANSI    
    FolioOStream&   operator<< (FolioOStream&           outputStream,
                                const FolioWideString&  rhs);
#else
    FolioOStream&   operator<< (FolioOStream&               outputStream,
                                const FolioNarrowString&    rhs);
#endif

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
