#pragma once

// "Home-made" includes.
#include    <Base.h>
#include    "StaticMap.h"

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/**
 * Template class that is used to hold a map that allows mapping from an 
 * integral value of type to its descriptions.
 */
template<typename T>
class ValueDescriptor
{
public:
    /// The value to description map type.
    typedef Folio::Core::Util::StaticMap<typename T, FolioString>   DescriptionMap;

    /// Single value to description map element type.
    typedef typename DescriptionMap::MapElement DescriptionMapElement;

    /**
     * Constructor that will create a value to description map from the 
     * specified array of value descriptions.
     *
     * @param [in] numDescriptions
     * The number of value descriptions in the array of value descriptions.
     *
     * @param [in] descriptions
     * The array of value descriptions.
     */
    ValueDescriptor (UInt32                         numDescriptions,
                     const DescriptionMapElement    descriptions [])
    :   m_descriptionMap (descriptions,
                          numDescriptions,
                          TXT(""))
    {} // Endproc.

    /**
     * The class destructor.
     */
    ~ValueDescriptor ()
    {} // Endproc.

    /**
     * Method that returns the description of a specified value.
     *
     * @param [in] value
     * The value.
     *
     * @return
     * The value description.
     */
    FolioString ToString (const T& value)
    {
        FolioOStringStream  description;

        if (m_descriptionMap [value].empty ())
        {
            description << value << FOLIO_UNKNOWN;
        } // Endif.

        else
        {
            description << m_descriptionMap [value];
        } // Endelse.

        return (description.str ());
    } // Endproc.

private:
    DescriptionMap  m_descriptionMap;   ///< The value to description map.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
