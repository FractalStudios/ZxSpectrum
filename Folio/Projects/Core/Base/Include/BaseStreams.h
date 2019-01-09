#pragma once

// STL includes.
#include    <fstream>
#include    <iostream>
#include    <iomanip>
#include    <istream>
#include    <ostream>
#include    <sstream>

// "Home-made" includes.
#include    "BaseTypes.h"

#pragma pack(push, 1)

namespace Folio
{

typedef std::basic_istream<Char>    FolioIStream;   ///< Folio input stream.
typedef std::basic_ostream<Char>    FolioOStream;   ///< Folio output stream.
typedef std::basic_iostream<Char>   FolioIOStream;  ///< Folio input/output stream.

typedef std::basic_fstream<Char>    FolioFStream;   ///< Folio file stream.
typedef std::basic_ifstream<Char>   FolioIFStream;  ///< Folio input file stream.
typedef std::basic_ofstream<Char>   FolioOFStream;  ///< Folio output file stream.

typedef std::basic_stringstream<Char, std::char_traits<Char> >  FolioStringStream;  ///< Folio string stream.
typedef std::basic_istringstream<Char, std::char_traits<Char> > FolioIStringStream; ///< Folio input string stream.
typedef std::basic_ostringstream<Char, std::char_traits<Char> > FolioOStringStream; ///< Folio output string stream.

typedef std::basic_istream<char>    FolioNarrowIStream;   ///< Folio narrow input stream.
typedef std::basic_ostream<char>    FolioNarrowOStream;   ///< Folio narrow output stream.
typedef std::basic_iostream<char>   FolioNarrowIOStream;  ///< Folio narrow input/output stream.

typedef std::basic_fstream<char>    FolioNarrowFStream;   ///< Folio narrow file stream.
typedef std::basic_ifstream<char>   FolioNarrowIFStream;  ///< Folio narrow input file stream.
typedef std::basic_ofstream<char>   FolioNarrowOFStream;  ///< Folio narrow output file stream.

typedef std::basic_stringstream<char, std::char_traits<char> >  FolioNarrowStringStream;  ///< Folio narrow string stream.
typedef std::basic_istringstream<char, std::char_traits<char> > FolioNarrowIStringStream; ///< Folio narrow input string stream.
typedef std::basic_ostringstream<char, std::char_traits<char> > FolioNarrowOStringStream; ///< Folio narrow output string stream.

typedef std::basic_istream<wchar_t>     FolioWideIStream;   ///< Folio wide input stream.
typedef std::basic_ostream<wchar_t>     FolioWideOStream;   ///< Folio wide output stream.
typedef std::basic_iostream<wchar_t>    FolioWideIOStream;  ///< Folio wide input/output stream.

typedef std::basic_fstream<wchar_t>     FolioWideFStream;   ///< Folio wide file stream.
typedef std::basic_ifstream<wchar_t>    FolioWideIFStream;  ///< Folio wide input file stream.
typedef std::basic_ofstream<wchar_t>    FolioWideOFStream;  ///< Folio wide output file stream.

typedef std::basic_stringstream<wchar_t, std::char_traits<wchar_t> >    FolioWideStringStream;  ///< Folio wide string stream.
typedef std::basic_istringstream<wchar_t, std::char_traits<wchar_t> >   FolioWideIStringStream; ///< Folio wide input string stream.
typedef std::basic_ostringstream<wchar_t, std::char_traits<wchar_t> >   FolioWideOStringStream; ///< Folio wide output string stream.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
