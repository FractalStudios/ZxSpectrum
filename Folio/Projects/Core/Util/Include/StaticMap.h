#pragma once

// STL includes.
#include    <map>

// "Home-made" includes.
#include    <Base.h>

#pragma pack(push, 1)

namespace Folio
{

namespace Core
{

namespace Util
{

/// The mapped array template class.
/**
 * This class provides a simple template wrapper for holding static array data.
 */
template <typename T, typename U>
class StaticMap
{
public:
    /// The map element structure.
    struct  MapElement
    {
        T   m_key;      ///< The index of this element in the map.
        U   m_value;    ///< The value of this element in the map.
    }; // Endstruct.

    /**
     * Constructor that initialises the <b>StaticMap</b> object from a static array.
     *
     * @param [in] mapData
     * A (potientally static) array of <b>MapElements</b>.
     *
     * @param [in] numMapRows
     * The number of array elements in the <i>mapData</i> parameter.
     *
     * @param [in] defaultValue
     * The value to be returned by operator [] in the case where the key is not found.
     */
    StaticMap (const MapElement mapData [],
               UInt32           numMapRows,
               U                defaultValue) : m_defaultValue(defaultValue)
    {
        for (UInt32 index = 0; index < numMapRows; ++index)
        {
            m_dataMap [mapData [index].m_key] = mapData [index].m_value;
        } // Endfor.

    } // Endproc.

    /**
     * operator [] returns the value data associated with any given key.
     *
     * @param [in] key
     * The key to be used to find a value.
     *
     * @return
     * The value associated with the provided key, or the default value
     * if the key entry does not exist.
     */
    const U& operator [] (const T& key)
    {
        typename    std::map<T, U>::iterator itr;

        if ((itr = m_dataMap.find (key)) != m_dataMap.end())
        {
            return (itr->second);
        } // Endif.

        else
        {
            return (m_defaultValue);
        } // Endelse.

    } // Endproc.

private:
    std::map<T, U>  m_dataMap;      ///< The map data.
    U               m_defaultValue; ///< The default map value.
}; // Endclass.

} // Endnamespace.

} // Endnamespace.

} // Endnamespace.

#pragma pack(pop)

/******************************* End of File *******************************/
