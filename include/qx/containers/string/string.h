/**

    @file      string.h
    @brief     Contains qx::string class
    @author    Khrapov
    @date      4.09.2019
    @copyright © Nick Khrapov, 2021. All right reserved.

**/
#pragma once

#include <qx/containers/container.h>
#include <qx/containers/string/string_data.h>
#include <qx/containers/string/string_hash.h>
#include <qx/containers/string/string_setup.h>
#include <qx/macros/static_assert.h>
#include <qx/meta/type_traits.h>

#include <iostream>
#include <optional>
#include <string_view>
#include <vector>

namespace qx
{

template<class char_t, class traits_t = char_traits<char_t>>
class basic_string;

namespace detail
{

template<class char_t>
using ostream = std::basic_ostream<char_t>;

template<class char_t>
using istream = std::basic_istream<char_t>;

} // namespace detail

} // namespace qx

template<class char_t, class traits_t>
qx::detail::istream<char_t>& operator>>(qx::detail::istream<char_t>& is, qx::basic_string<char_t, traits_t>& str);

namespace qx
{

/**

    @class   basic_string
    @brief   String class
    @details A class containing a null-terminated character sequence.
             Supports small strings optimization, almost completely supports
             the std::string interface (except for some overloads),
             has many additional methods for convenient working with strings.
    @tparam  char_t   - char type (char, wchar_t, etc)
    @tparam  traits_t - char traits. \see string_traits.h
    @author  Khrapov
    @date    20.10.2019

**/
template<class char_t, class traits_t>
class basic_string
{
    template<class _char_t, class _traits_t>
    friend qx::detail::istream<_char_t>& ::operator>>(
        qx::detail::istream<_char_t>&     is,
        basic_string<_char_t, _traits_t>& str);

public:
    using traits_type     = traits_t;
    using value_type      = typename traits_type::value_type;
    using pointer         = typename traits_type::pointer;
    using const_pointer   = typename traits_type::const_pointer;
    using reference       = typename traits_type::reference;
    using const_reference = typename traits_type::const_reference;
    using difference_type = typename traits_type::difference_type;
    using size_type       = typename traits_type::size_type;
    using string_view     = std::basic_string_view<value_type>;
    using sstream_type    = std::basic_stringstream<value_type>;
    using views           = std::vector<string_view>;

    static constexpr size_type npos = std::numeric_limits<size_type>::max();

    QX_IMPL_CONTAINER(basic_string);

public:
    /**
        @brief basic_string object constructor
    **/
    basic_string() noexcept = default;

    /**
        @brief basic_string object constructor
        @param nSymbols - number of same chars
        @param chSymbol - char to assign
    **/
    basic_string(size_type nSymbols, value_type chSymbol) noexcept;

    /**
        @brief basic_string object constructor
        @param pszSource - source string pointer
        @param nSymbols  - source string size
    **/
    basic_string(const_pointer pszSource, size_type nSymbols) noexcept;

    /**
        @brief basic_string object constructor
        @param pszSource - source string pointer
    **/
    basic_string(const_pointer pszSource) noexcept;

    /**
        @brief basic_string object constructor
        @param sAnother - another string rvalue ref
    **/
    basic_string(basic_string&& sAnother) noexcept;

    /**
        @brief basic_string object constructor
        @param sAnother - another string
    **/
    basic_string(const basic_string& sAnother) noexcept;

    /**
        @brief  basic_string object constructor
        @tparam fwd_it_t - forward iterator type
        @param  itFirst  - first source iterator
        @param  itLast   - last source iterator
    **/
    template<class fwd_it_t>
    basic_string(fwd_it_t itFirst, fwd_it_t itLast) noexcept;

    /**
        @brief  basic_string object constructor
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sAnother - string-ish container
    **/
    template<string_convertable string_t>
    basic_string(const string_t& sAnother) noexcept;

    /**
        @brief basic_string object destructor
    **/
    ~basic_string() noexcept;

    /**
        @brief  Assign by filling 
        @param  nSymbols - number of same chars
        @param  chSymbol - char to assign
    **/
    void assign(size_type nSymbols, value_type chSymbol) noexcept;

    /**
        @brief  Assign by char sequence
        @param  pszSource - pointer to char sequence
        @param  nSymbols  - num of chars
    **/
    void assign(const_pointer pszSource, size_type nSymbols) noexcept;

    /**
        @brief  Assign by psz
        @param  pszSource - pointer to zero terminated char sequence
    **/
    void assign(const_pointer pszSource) noexcept;

    /**
        @brief  Assign by moving from another string
        @param  sAnother - another string
    **/
    void assign(basic_string&& sAnother) noexcept;

    /**
        @brief  Assign by another string
        @param  sAnother - another string
    **/
    void assign(const basic_string& sAnother) noexcept;

    /**
        @brief  Assign by iterators
        @tparam fwd_it_t - forward iterator type
        @param  itFirst  - first iterator of source
        @param  itLast   - last iterator of source
    **/
    template<class fwd_it_t>
    void assign(fwd_it_t itFirst, fwd_it_t itLast) noexcept;

    /**
        @brief  Assign by char container
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  str      - char container
    **/
    template<string_convertable string_t>
    void assign(const string_t& str) noexcept;

    /**
        @brief  Format string (c-style printf)
        @param  pszFormat - format pattern. this str as pszFormat is UB
        @param  ...       - format arguments
    **/
    void sprintf(const_pointer pszFormat, ...) noexcept;

    /**
        @brief  Format string with given va_args (c-style printf)
        @param  pszFormat - format pattern. this str as pszFormat is UB
        @param  args      - args pack
    **/
    void vsprintf(const_pointer pszFormat, va_list args) noexcept;

    /**
        @brief  Static format string (c-style printf)
        @tparam args_t    - template parameter pack type
        @param  pszFormat - format pattern
        @param  args      - format arguments
        @retval           - formatted string
    **/
    template<class... args_t>
    static basic_string static_sprintf(const_pointer pszFormat, args_t... args) noexcept;

    /**
        @brief  Format string (c-style printf) and append to the current string
        @param  pszFormat - format pattern
        @param  ...       - format arguments
    **/
    void append_sprintf(const_pointer pszFormat, ...) noexcept;

    /**
        @brief  Format string (c-style printf) and append to the current string
        @param  pszFormat - format pattern
        @param  args      - format arguments
    **/
    void append_vsprintf(const_pointer pszFormat, va_list args) noexcept;

    /**
        @brief  Swap this str and other
        @param  sOther - other str
    **/
    void swap(basic_string& sOther) noexcept;

    /**
        @brief  Reserve memory for the string
        @param  nCapacity - required capacity
        @retval           - new string capacity
    **/
    size_type reserve(size_type nCapacity) noexcept;

    /**
        @brief Fit allocated size to string's actual size
    **/
    void shrink_to_fit() noexcept;

    /**
        @brief Clear string and free allocated memory
    **/
    void free() noexcept;

    /**
        @brief  Get substring
        @param  nPos     - start index
        @param  nSymbols - string size (npos - to the end)
        @retval          - substring view
    **/
    string_view substr(size_type nPos, size_type nSymbols = npos) const noexcept;

    /**
        @brief Convert string to lowercase
    **/
    void to_lower() noexcept;

    /**
        @brief Convert string to uppercase
    **/
    void to_upper() noexcept;

    /**
        @brief  Get first char of the string
        @retval - first char of the string
    **/
    value_type front() const noexcept;

    /**
        @brief  Get last char of the string
        @retval - last char of the string
    **/
    value_type back() const noexcept;

    /**
        @brief  Get string length
        @brief  Same as size()
        @retval - string length
    **/
    size_type length() const noexcept;

    /**
        @brief  Get pointer to string zero terminated
        @retval - pointer to string zero terminated
    **/
    const_pointer c_str() const noexcept;

    /**
        @brief  Get allocated memory size (including null terminator)
        @retval - allocated memory size
    **/
    size_type capacity() const noexcept;

    /**
        @brief  Get the theoretical maximum of string size
        @retval - theoretical maximum of string size
    **/
    static constexpr size_type max_size() noexcept;

    /**
        @brief  Convert string to specified type
        @tparam to_t      - type to convert
        @param  pszFormat - format string
        @retval           - converted value or std::nullopt
    **/
    template<class to_t>
    std::optional<to_t> to(const_pointer pszFormat = nullptr) const noexcept;

    /**
        @brief  Copies a substring [nPos, nPos + nCount) to character string pointed to by pDest
        @param  pDest  - pointer to the destination character string 
        @param  nCount - length of the substring 
        @param  nPos   - position of the first character to include 
        @retval        - number of characters copied
    **/
    size_type copy(pointer pDest, size_type nCount, size_type nPos = 0) const noexcept;

    /**
        @brief  Construct string from custom type
        @tparam from_t    - type to convert from
        @param  data      - data of type from_type
        @param  pszFormat - format string if default is not enough
    **/
    template<class from_t>
    void from(const from_t& data, const_pointer pszFormat = nullptr) noexcept;

    /**
        @brief  Construct string from custom type and get it
        @tparam from_t    - type to convert from
        @param  data      - data of type from_type
        @param  pszFormat - format string if default is not enough
        @retval           - constructed string
    **/
    template<class from_t>
    static basic_string static_from(const from_t& data, const_pointer pszFormat = nullptr) noexcept;

    /**
        @brief  Append char
        @param  chSymbol - char to append
    **/
    void append(value_type chSymbol) noexcept;

    /**
        @brief  Append string
        @param  pszStr   - source string
        @param  nStrSize - source string size
    **/
    void append(const_pointer pszStr, size_type nStrSize = npos) noexcept;

    /**
        @brief  Append string
        @param  sStr - source string
    **/
    void append(const basic_string& sStr) noexcept;

    /**
        @brief  Append string
        @tparam fwd_it_t - forward iterator type
        @param  itBegin     - other string begin iterator
        @param  itEnd       - other end begin iterator
    **/
    template<class fwd_it_t>
    void append(fwd_it_t itBegin, fwd_it_t itEnd) noexcept;

    /**
        @brief  Append string
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - source char container
    **/
    template<string_convertable string_t>
    void append(const string_t& sStr) noexcept;

    /**
        @brief  Insert substring
        @param  nPos     - first char index
        @param  chSymbol - symbol to insert
        @retval          - pos of char after last char of inserted string or npos
    **/
    size_type insert(size_type nPos, value_type chSymbol) noexcept;

    /**
        @brief  Insert substring
        @param  nPos     - first char index 
        @param  pszWhat  - source string 
        @param  nSymbols - number of symbols to insert 
        @retval          - pos of char after last char of inserted string or npos
    **/
    size_type insert(size_type nPos, const_pointer pszWhat, size_type nSymbols = npos) noexcept;

    /**
        @brief  Insert substring
        @param  nPos  - first char index
        @param  sWhat - string to insert
        @retval       - pos of char after last char of inserted string or npos
    **/
    size_type insert(size_type nPos, const basic_string& sWhat) noexcept;

    /**
        @brief  Insert substring
        @tparam fwd_it_t    - forward iterator type
        @param  nPos        - first char index
        @param  itWhatBegin - source first iterator
        @param  itWhatEnd   - source last iterator
        @retval             - pos of char after last char of inserted string or npos
    **/
    template<class fwd_it_t>
    size_type insert(size_type nPos, fwd_it_t itWhatBegin, fwd_it_t itWhatEnd) noexcept;

    /**
        @brief  Insert substring
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  nPos     - first char index
        @param  sWhat    - source string
        @retval          - pos of char after last char of inserted string or npos
    **/
    template<string_convertable string_t>
    size_type insert(size_type nPos, string_t sWhat) noexcept;

    /**
        @brief  Insert char
        @param  itPos    - first char iterator
        @param  chSymbol - char to insert
        @retval          - pos of char after last char of inserted string or npos
    **/
    size_type insert(const_iterator itPos, value_type chSymbol) noexcept;

    /**
        @brief  Insert substring
        @param  itPos    - first char iterator
        @param  pszWhat  - source string
        @param  nSymbols - number of symbols to insert
        @retval          - pos of char after last char of inserted string or npos
    **/
    size_type insert(const_iterator itPos, const_pointer pszWhat, size_type nSymbols = npos) noexcept;

    /**
        @brief  Insert substring
        @param  itPos - first char iterator
        @param  sWhat - string to insert
        @retval       - pos of char after last char of inserted string or npos
    **/
    size_type insert(const_iterator itPos, const basic_string& sWhat) noexcept;

    /**
        @brief  Insert substring
        @tparam fwd_it_t    - forward iterator type
        @param  itPos       - first char iterator 
        @param  itWhatBegin - source string first iterator 
        @param  itWhatEnd   - source string last iterator 
        @retval             - pos of char after last char of inserted string or npos
    **/
    template<class fwd_it_t>
    size_type insert(const_iterator itPos, fwd_it_t itWhatBegin, fwd_it_t itWhatEnd) noexcept;

    /**
        @brief  Insert substring
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  itPos    - first char iterator
        @param  sWhat    - source string
        @retval          - pos of char after last char of inserted string or npos
    **/
    template<string_convertable string_t>
    size_type insert(const_iterator itPos, string_t sWhat) noexcept;

    /**
        @brief  Insert char in the end of the string
        @param  chSymbol - char to insert
    **/
    void push_back(value_type chSymbol) noexcept;

    /**
        @brief  Insert char in the beginning of the string
        @param  chSymbol - char to insert
    **/
    void push_front(value_type chSymbol) noexcept;

    /**
        @brief  Erase substring
        @param  itFirst - first substr char iterator
        @param  itLast  - last substr char iterator (excluded)
    **/
    void erase(iterator itFirst, iterator itLast) noexcept;

    /**
        @brief  Erase on iterator
        @param  itPos - iterator where to erase
    **/
    void erase(iterator itPos) noexcept;

    /**
        @brief  Erase on position
        @param  nPos - index where to erase
    **/
    void erase(size_type nPos) noexcept;

    /**
        @brief  Erase substring
        @param  nPos     - start position
        @param  nSymbols - number of symbols
    **/
    void erase(size_type nPos, size_type nSymbols) noexcept;

    /**
        @brief  Erase last char and return it
        @retval - last char
    **/
    value_type pop_back() noexcept;

    /**
        @brief  Erase first char and return it
        @retval - first char
    **/
    value_type pop_front() noexcept;

    /**
        @brief  Trim the string to the left (whitespace characters)
        @retval - number of deleted symbols
    **/
    size_type trim_left() noexcept;

    /**
        @brief  Trim the string to the left
        @param  chSymbol - symbol to delete
        @retval          - number of deleted symbols
    **/
    size_type trim_left(value_type chSymbol) noexcept;

    /**
        @brief  Trim the string to the left
        @param  pszStr - string with symbols to delete 
        @retval        - number of deleted symbols
    **/
    size_type trim_left(const_pointer pszStr) noexcept;

    /**
        @brief  Trim the string to the left
        @param  pszStr   - string with symbols to delete
        @param  nStrSize - string size
        @retval          - number of deleted symbols
    **/
    size_type trim_left(const_pointer pszStr, size_type nStrSize) noexcept;

    /**
        @brief  Trim the string to the left
        @param  sStr - string with symbols to delete
        @retval      - number of deleted symbols
    **/
    size_type trim_left(const basic_string& sStr) noexcept;

    /**
        @brief  Trim the string to the left
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - begin it of string with symbols to delete
        @param  itEnd    - begin it of string with symbols to delete
        @retval          - number of deleted symbols
    **/
    template<class fwd_it_t>
    size_type trim_left(fwd_it_t itBegin, fwd_it_t itEnd) noexcept;

    /**
        @brief  Trim the string to the left
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string with symbols to delete 
        @retval          - number of deleted symbols
    **/
    template<string_convertable string_t>
    size_type trim_left(const string_t& sStr) noexcept;

    /**
        @brief  Trim the string to the right (whitespace characters)
        @retval - number of deleted symbols
    **/
    size_type trim_right() noexcept;

    /**
        @brief  Trim the string to the right
        @param  chSymbol - symbol to delete
        @retval          - number of deleted symbols
    **/
    size_type trim_right(value_type chSymbol) noexcept;

    /**
        @brief  Trim the string to the right
        @param  pszStr - string with symbols to delete
        @retval        - number of deleted symbols
    **/
    size_type trim_right(const_pointer pszStr) noexcept;

    /**
        @brief  Trim the string to the right
        @param  pszStr   - string with symbols to delete
        @param  nStrSize - string size
        @retval          - number of deleted symbols
    **/
    size_type trim_right(const_pointer pszStr, size_type nStrSize) noexcept;

    /**
        @brief  Trim the string to the right
        @param  sStr - string with symbols to delete
        @retval      - number of deleted symbols
    **/
    size_type trim_right(const basic_string& sStr) noexcept;

    /**
        @brief  Trim the string to the right
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - begin it of string with symbols to delete
        @param  itEnd    - begin it of string with symbols to delete
        @retval          - number of deleted symbols
    **/
    template<class fwd_it_t>
    size_type trim_right(fwd_it_t itBegin, fwd_it_t itEnd) noexcept;

    /**
        @brief  Trim the string to the right
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string with symbols to delete
        @retval          - number of deleted symbols
    **/
    template<string_convertable string_t>
    size_type trim_right(const string_t& sStr) noexcept;

    /**
        @brief  Trim the string to the both sides (whitespace characters)
        @retval - number of deleted symbols
    **/
    size_type trim() noexcept;

    /**
        @brief  Trim the string to the both sides
        @param  chSymbol - symbol to delete
        @retval          - number of deleted symbols
    **/
    size_type trim(value_type chSymbol) noexcept;

    /**
        @brief  Trim the string to the both sides
        @param  pszStr - string with symbols to delete 
        @retval        - number of deleted symbols
    **/
    size_type trim(const_pointer pszStr) noexcept;

    /**
        @brief  Trim the string to the both sides
        @param  pszStr   - string with symbols to delete
        @param  nStrSize - string size
        @retval          - number of deleted symbols
    **/
    size_type trim(const_pointer pszStr, size_type nStrSize) noexcept;

    /**
        @brief  Trim the string to the both sides
        @param  sStr - string with symbols to delete
        @retval      - number of deleted symbols
    **/
    size_type trim(const basic_string& sStr) noexcept;

    /**
        @brief  Trim the string to the both sides
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - begin it of string with symbols to delete
        @param  itEnd    - begin it of string with symbols to delete
        @retval          - number of deleted symbols
    **/
    template<class fwd_it_t>
    size_type trim(fwd_it_t itBegin, fwd_it_t itEnd) noexcept;

    /**
        @brief  Trim the string to the both sides
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string with symbols to delete
        @retval          - number of deleted symbols
    **/
    template<string_convertable string_t>
    size_type trim(const string_t& sStr) noexcept;

    /**
        @brief  Remove the first occurrence of a substring in a string
        @param  chSymbol - char to remove
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @retval          - position where the first occurrence was or npos
    **/
    size_type remove(value_type chSymbol, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove the first occurrence of a substring in a string
        @param  pszStr   - c-string to remove
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @param  nStrSize - c-string size
        @retval          - position where the first occurrence was or npos
    **/
    size_type remove(
        const_pointer pszStr,
        size_type     nBegin   = 0,
        size_type     nEnd     = npos,
        size_type     nStrSize = npos) noexcept;

    /**
        @brief  Remove the first occurrence of a substring in a string
        @param  sStr   - string to remove
        @param  nBegin - start searching index
        @param  nEnd   - end searching index
        @retval        - position where the first occurrence was or npos
    **/
    size_type remove(const basic_string& sStr, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove the first occurrence of a substring in a string
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - string begin iterator
        @param  itEnd    - string end iterator
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @retval          - position where the first occurrence was or npos
    **/
    template<class fwd_it_t>
    size_type remove(fwd_it_t itBegin, fwd_it_t itEnd, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove the first occurrence of a substring in a string
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to remove
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @retval          - position where the first occurrence was or npos
    **/
    template<string_convertable string_t>
    size_type remove(const string_t& sStr, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove string prefix if matches
        @param  chSymbol - char to remove
        @retval          - true if removed
    **/
    bool remove_prefix(value_type chSymbol) noexcept;

    /**
        @brief  Remove string prefix if matches
        @param  pszStr   - string to remove
        @param  nStrSize - string size
        @retval          - true if removed
    **/
    bool remove_prefix(const_pointer pszStr, size_type nStrSize = npos) noexcept;

    /**
        @brief  Remove string prefix if matches
        @param  sStr - string to remove
        @retval      - true if removed
    **/
    bool remove_prefix(const basic_string& sStr) noexcept;

    /**
        @brief  Remove string prefix if matches
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - string to remove begin iterator
        @param  itEnd    - string to remove end iterator
        @retval          - true if removed
    **/
    template<class fwd_it_t>
    bool remove_prefix(fwd_it_t itBegin, fwd_it_t itEnd) noexcept;

    /**
        @brief  Remove string prefix if matches
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to remove
        @retval          - true if removed
    **/
    template<string_convertable string_t>
    bool remove_prefix(const string_t& sStr) noexcept;

    /**
        @brief  Remove string suffix if matches
        @param  chSymbol - char to remove 
        @retval          - true if removed
    **/
    bool remove_suffix(value_type chSymbol) noexcept;

    /**
        @brief  Remove string suffix if matches
        @param  pszStr   - string to remove
        @param  nStrSize - string size
        @retval          - true if removed
    **/
    bool remove_suffix(const_pointer pszStr, size_type nStrSize = npos) noexcept;

    /**
        @brief  Remove string suffix if matches
        @param  sStr   - string to remove
        @retval        - true if removed
    **/
    bool remove_suffix(const basic_string& sStr) noexcept;

    /**
        @brief  Remove string suffix if matches
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - string to remove begin iterator
        @param  itEnd    - string to remove end iterator
        @retval          - true if removed
    **/
    template<class fwd_it_t>
    bool remove_suffix(fwd_it_t itBegin, fwd_it_t itEnd) noexcept;

    /**
        @brief  Remove string suffix if matches
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to remove
        @retval          - true if removed
    **/
    template<string_convertable string_t>
    bool remove_suffix(const string_t& sStr) noexcept;

    /**
        @brief  Remove all occurrences of a substring in a string
        @param  chSymbol - char to remove 
        @param  nBegin   - start searching index 
        @param  nEnd     - end searching index 
        @retval          - number of deleted occurrences
    **/
    size_type remove_all(value_type chSymbol, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove all occurrences of a substring in a string
        @param  pszStr   - string to remove
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @param  nStrSize - string size
        @retval          - number of deleted occurrences
    **/
    size_type remove_all(
        const_pointer pszStr,
        size_type     nBegin   = 0,
        size_type     nEnd     = npos,
        size_type     nStrSize = npos) noexcept;

    /**
        @brief  Remove all occurrences of a substring in a string
        @param  sStr   - string to remove
        @param  nBegin - start searching index
        @param  nEnd   - end searching index
        @retval        - number of deleted occurrences
    **/
    size_type remove_all(const basic_string& sStr, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove all occurrences of a substring in a string
        @tparam fwd_it_t - forward iterator type
        @param  itFirst  - string begin iterator
        @param  itLast   - string end iterator
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @retval          - number of deleted occurrences
    **/
    template<class fwd_it_t>
    size_type remove_all(fwd_it_t itFirst, fwd_it_t itLast, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Remove all occurrences of a substring in a string
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to remove
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @retval          - number of deleted occurrences
    **/
    template<string_convertable string_t>
    size_type remove_all(const string_t& sStr, size_type nBegin = 0, size_type nEnd = npos) noexcept;

    /**
        @brief  Replace first occurrence of sFind with sReplace
        @tparam find_string_t    - find string type
        @tparam replace_string_t - replace string type
        @param  sFind            - string to find and replace
        @param  sReplace         - string to replace with
        @param  nBegin           - start searching index
        @param  nEnd             - end searching index
        @retval                  - pos of char after last char of replaced string or npos
    **/
    template<class find_string_t, class replace_string_t>
    size_type replace(
        const find_string_t&    sFind,
        const replace_string_t& sReplace,
        size_type               nBegin = 0,
        size_type               nEnd   = npos) noexcept;

    /**
        @brief  Replace all occurrences of sFind with sReplace
        @tparam find_string_t    - find string type
        @tparam replace_string_t - replace string type
        @param  sFind            - string to find and replace
        @param  sReplace         - string to replace with
        @param  nBegin           - start searching index
        @param  nEnd             - end searching index
        @retval                  - number of replaced occurrences
    **/
    template<class find_string_t, class replace_string_t>
    size_type replace_all(
        const find_string_t&    sFind,
        const replace_string_t& sReplace,
        size_type               nBegin = 0,
        size_type               nEnd   = npos) noexcept;

    /**
        @brief  Performs a binary comparison of the characters
        @param  chSymbol - symbol to compare
        @retval          - < 0 the first character that does not match has
                               a lower value in this than in chSymbol
                           = 0 the contents of both strings are equal
                           > 0 the first character that does not match has
                               a greater value in this than in chSymbol
    **/
    int compare(value_type chSymbol) const noexcept;

    /**
        @brief  Performs a binary comparison of the characters
        @param  pszStr - string to compare. must not be nullptr
        @retval        - < 0 the first character that does not match has
                             a lower value in this than in chSymbol
                         = 0 the contents of both strings are equal
                         > 0 the first character that does not match has
                             a greater value in this than in chSymbol
    **/
    int compare(const_pointer pszStr) const noexcept;

    /**
        @brief  Performs a binary comparison of the characters
        @param  pStr     - string to compare. must not be nullptr
        @param  nStrSize - number of symbols to compare
        @retval          - < 0 the first character that does not match has
                               a lower value in this than in chSymbol
                           = 0 the contents of both strings are equal
                           > 0 the first character that does not match has
                               a greater value in this than in chSymbol
    **/
    int compare(const_pointer pStr, size_type nStrSize) const noexcept;

    /**
        @brief  Performs a binary comparison of the characters
        @param  sStr - string to compare
        @retval      - < 0 the first character that does not match has
                           a lower value in this than in chSymbol
                       = 0 the contents of both strings are equal
                       > 0 the first character that does not match has
                           a greater value in this than in chSymbol
    **/
    int compare(const basic_string& sStr) const noexcept;

    /**
        @brief  Performs a binary comparison of the characters
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - string to compare begin iterator
        @param  itEnd    - string to compare end iterator
        @retval          - < 0 the first character that does not match has
                               a lower value in this than in chSymbol
                           = 0 the contents of both strings are equal
                           > 0 the first character that does not match has
                               a greater value in this than in chSymbol
    **/
    template<class fwd_it_t>
    int compare(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept;

    /**
        @brief  Performs a binary comparison of the characters
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - < 0 the first character that does not match has
                               a lower value in this than in chSymbol
                           = 0 the contents of both strings are equal
                           > 0 the first character that does not match has
                               a greater value in this than in chSymbol
    **/
    template<string_convertable string_t>
    int compare(const string_t& sStr) const noexcept;

    /**
        @brief  Find substring
        @param  chSymbol - char to find
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index (npos - to the end)
        @retval          - substring index or npos if not found
    **/
    size_type find(value_type chSymbol, size_type nBegin = 0, size_type nEnd = npos) const noexcept;

    /**
        @brief  Find substring
        @param  pszWhat   - string to find
        @param  nBegin    - start searching index
        @param  nWhatSize - string length (npos - string is zero terminated)
        @param  nEnd      - end searching index (npos - to the end).
        @retval           - substring index
    **/
    size_type find(const_pointer pszWhat, size_type nBegin = 0, size_type nWhatSize = npos, size_type nEnd = npos)
        const noexcept;

    /**
        @brief  Find substring
        @param  sWhat  - string to find
        @param  nBegin - start searching index
        @param  nEnd   - end searching index
        @retval        - substring index or npos if not found
    **/
    size_type find(const basic_string& sWhat, size_type nBegin = 0, size_type nEnd = npos) const noexcept;

    /**
        @brief  Find substring
        @tparam fwd_it_t    - forward iterator type
        @param  itWhatBegin - substring begin iterator
        @param  itWhatEnd   - substring end iterator
        @param  nBegin      - start searching index
        @param  nEnd        - end searching index
        @retval             - substring index or npos if not found
    **/
    template<class fwd_it_t>
    size_type find(fwd_it_t itWhatBegin, fwd_it_t itWhatEnd, size_type nBegin = 0, size_type nEnd = npos)
        const noexcept;

    /**
        @brief  Find substring
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sWhat    - substring
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
        @retval          - substring index or npos if not found
    **/
    template<string_convertable string_t>
    size_type find(string_t sWhat, size_type nBegin = 0, size_type nEnd = npos) const noexcept;

    /**
        @brief  Find substring (reverse direction)
        @param  chSymbol - char to find
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
                           (if nBegin < end, result is equivalent of find(...))
        @retval          - substring index or npos if not found
    **/
    size_type rfind(value_type chSymbol, size_type nBegin = npos, size_type nEnd = 0) const noexcept;

    /**
        @brief  Find substring (reverse direction)
        @param  pszWhat   - c-string to find
        @param  nBegin    - start searching index
        @param  nWhatSize - c-string length
        @param  nEnd      - end searching index
                            (if nBegin < end, result is equivalent of find(...))
        @retval           - substring index or npos if not found
    **/
    size_type rfind(const_pointer pszWhat, size_type nBegin = npos, size_type nWhatSize = npos, size_type nEnd = 0)
        const noexcept;

    /**
        @brief  Find substring (reverse direction)
        @param  sWhat  - string to find
        @param  nBegin - start searching index
        @param  nEnd   - end searching index
                         (if nBegin < end, result is equivalent of find(...))
        @retval        - substring index or npos if not found
    **/
    size_type rfind(const basic_string& sWhat, size_type nBegin = npos, size_type nEnd = 0) const noexcept;

    /**
        @brief  Find substring (reverse direction)
        @tparam fwd_it_t    - forward iterator type
        @param  itWhatBegin - substring begin iterator
        @param  itWhatEnd   - substring end iterator
        @param  nBegin      - start searching index
        @param  nEnd        - end searching index
                              (if nBegin < end, result is equivalent of find(...))
        @retval             - substring index or npos if not found
    **/
    template<class fwd_it_t>
    size_type rfind(fwd_it_t itWhatBegin, fwd_it_t itWhatEnd, size_type nBegin = npos, size_type nEnd = 0)
        const noexcept;

    /**
        @brief  Find substring (reverse direction)
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sWhat    - substring
        @param  nBegin   - start searching index
        @param  nEnd     - end searching index
                           (if nBegin < end, result is equivalent of find(...))
        @retval          - substring index or npos if not found
    **/
    template<string_convertable string_t>
    size_type rfind(string_t sWhat, size_type nBegin = npos, size_type nEnd = 0) const noexcept;

    /**
        @brief  Find first position of character
        @param  chSymbol - char to find
        @param  nBegin   - position at which the search is to begin
        @retval          - symbol index or npos
    **/
    size_type find_first_of(value_type chSymbol, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to one of characters in the given character sequence
        @param  pszWhat   - string identifying characters to search for
        @param  nBegin    - position at which the search is to begin
        @param  nWhatSize - length of character string identifying characters to search for
        @retval           - symbol index or npos
    **/
    size_type find_first_of(const_pointer pszWhat, size_type nBegin, size_type nWhatSize) const noexcept;

    /**
        @brief  Finds the first character equal to one of characters in the given character sequence
        @param  pszWhat - null terminated string identifying characters to search for
        @param  nBegin  - position at which the search is to begin
        @retval         - symbol index or npos
    **/
    size_type find_first_of(const_pointer pszWhat, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to one of characters in the given character sequence
        @param  sWhat  - string identifying characters to search for
        @param  nBegin - position at which the search is to begin
        @retval        - symbol index or npos
    **/
    size_type find_first_of(const basic_string& sWhat, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to one of characters in the given character sequence
        @tparam fwd_it_t    - forward iterator type
        @param  itWhatBegin - begin it of string identifying characters to search for
        @param  itWhatEnd   - end it of string identifying characters to search for
        @param  nBegin      - position at which the search is to begin
        @retval             - symbol index or npos
    **/
    template<class fwd_it_t>
    size_type find_first_of(fwd_it_t itWhatBegin, fwd_it_t itWhatEnd, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to one of characters in the given character sequence
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sWhat    - string identifying characters to search for
        @param  nBegin   - position at which the search is to begin
        @retval          - symbol index or npos
    **/
    template<string_convertable string_t>
    size_type find_first_of(string_t sWhat, size_type nBegin = 0) const noexcept;

    /**
        @brief  Find last position of character
        @param  chSymbol - char to find
        @param  nEnd     - position at which the search is to finish
        @retval          - symbol index or npos
    **/
    size_type find_last_of(value_type chSymbol, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to one of characters in the given character sequence
        @param  pszWhat   - string identifying characters to search for
        @param  nEnd      - position at which the search is to finish
        @param  nWhatSize - length of character string identifying characters to search for
        @retval           - symbol index or npos
    **/
    size_type find_last_of(const_pointer pszWhat, size_type nEnd, size_type nWhatSize) const noexcept;

    /**
        @brief  Finds the last character equal to one of characters in the given character sequence
        @param  pszWhat - null terminated string identifying characters to search for
        @param  nEnd    - position at which the search is to finish
        @retval         - symbol index or npos
    **/
    size_type find_last_of(const_pointer pszWhat, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to one of characters in the given character sequence
        @param  sWhat - string identifying characters to search for 
        @param  nEnd  - position at which the search is to finish 
        @retval       - symbol index or npos
    **/
    size_type find_last_of(const basic_string& sWhat, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to one of characters in the given character sequence
        @tparam fwd_it_t    - forward iterator type
        @param  itWhatBegin - begin it of string identifying characters to search for 
        @param  itWhatEnd   - end it of string identifying characters to search for 
        @param  nEnd        - position at which the search is to finish 
        @retval             - symbol index or npos
    **/
    template<class fwd_it_t>
    size_type find_last_of(fwd_it_t itWhatBegin, fwd_it_t itWhatEnd, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to one of characters in the given character sequence
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sWhat    - string identifying characters to search for
        @param  nEnd     - position at which the search is to finish
        @retval          - symbol index or npos
    **/
    template<string_convertable string_t>
    size_type find_last_of(string_t sWhat, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the first character not equal to chSymbol
        @param  chSymbol - char to find
        @param  nBegin   - position at which the search is to begin
        @retval          - symbol index or npos
    **/
    size_type find_first_not_of(value_type chSymbol, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to none of the characters in the given character sequence
        @param  pszWhat   - string identifying characters to search for
        @param  nBegin    - position at which the search is to begin
        @param  nWhatSize - length of character string identifying characters to search for
        @retval           - symbol index or npos
    **/
    size_type find_first_not_of(const_pointer pszWhat, size_type nBegin, size_type nWhatSize) const noexcept;

    /**
        @brief  Finds the first character equal to none of the characters in the given character sequence
        @param  pszWhat - null terminated string identifying characters to search for
        @param  nBegin  - position at which the search is to begin
        @retval         - symbol index or npos
    **/
    size_type find_first_not_of(const_pointer pszWhat, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to none of the characters in the given character sequence
        @param  sWhat  - string identifying characters to search for
        @param  nBegin - position at which the search is to begin
        @retval        - symbol index or npos
    **/
    size_type find_first_not_of(const basic_string& sWhat, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to none of the characters in the given character sequence
        @tparam fwd_it_t    - forward iterator type
        @param  itWhatBegin - begin it of string identifying characters to search for
        @param  itWhatEnd   - end it of string identifying characters to search for
        @param  nBegin      - position at which the search is to begin
        @retval             - symbol index or npos
    **/
    template<class fwd_it_t>
    size_type find_first_not_of(fwd_it_t itWhatBegin, fwd_it_t itWhatEnd, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the first character equal to none of the characters in the given character sequence
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sWhat    - string identifying characters to search for 
        @param  nBegin   - position at which the search is to begin 
        @retval          - symbol index or npos
    **/
    template<string_convertable string_t>
    size_type find_first_not_of(string_t sWhat, size_type nBegin = 0) const noexcept;

    /**
        @brief  Finds the last character not equal to chSymbol
        @param  chSymbol - char to find 
        @param  nEnd     - position at which the search is to finish 
        @retval          - symbol index or npos
    **/
    size_type find_last_not_of(value_type chSymbol, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to none of the characters in the given character sequence
        @param  pszWhat   - string identifying characters to search for
        @param  nEnd      - position at which the search is to finish
        @param  nWhatSize - length of character string identifying characters to search for
        @retval           - symbol index or npos
    **/
    size_type find_last_not_of(const_pointer pszWhat, size_type nEnd, size_type nWhatSize) const noexcept;

    /**
        @brief  Finds the last character equal to none of the characters in the given character sequence
        @param  pszWhat - null terminated string identifying characters to search for
        @param  nEnd    - position at which the search is to finish
        @retval         - symbol index or npos
    **/
    size_type find_last_not_of(const_pointer pszWhat, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to none of the characters in the given character sequence
        @param  sWhat - string identifying characters to search for
        @param  nEnd  - position at which the search is to finish
        @retval       - symbol index or npos
    **/
    size_type find_last_not_of(const basic_string& sWhat, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to none of the characters in the given character sequence
        @tparam fwd_it_t    - forward iterator type
        @param  itWhatBegin - begin it of string identifying characters to search for
        @param  itWhatEnd   - end it of string identifying characters to search for
        @param  nEnd        - position at which the search is to finish
        @retval             - symbol index or npos
    **/
    template<class fwd_it_t>
    size_type find_last_not_of(fwd_it_t itWhatBegin, fwd_it_t itWhatEnd, size_type nEnd = 0) const noexcept;

    /**
        @brief  Finds the last character equal to none of the characters in the given character sequence
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sWhat    - string identifying characters to search for 
        @param  nEnd     - position at which the search is to finish 
        @retval          - symbol index or npos
    **/
    template<string_convertable string_t>
    size_type find_last_not_of(string_t sWhat, size_type nEnd = 0) const noexcept;

    /**
        @brief  Split string by separator
        @param  chSeparator - char separator
        @retval             - string_view container 
    **/
    views split(const value_type chSeparator) const noexcept;

    /**
        @brief  Split string by separator
        @param  pszSeparator - separator string
        @param  nSepLen      - separator string length (npos if str is null terminated)
        @retval              - string_view container
    **/
    views split(const_pointer pszSeparator, size_type nSepLen = npos) const noexcept;

    /**
        @brief  Split string by separator
        @param  sSeparator - separator string
        @retval            - string_view container
    **/
    views split(const basic_string& sSeparator) const noexcept;

    /**
        @brief  Split string by separator
        @tparam fwd_it_t    - forward iterator type
        @param  itSepFirst - separator begin iterator 
        @param  itSepLast  - separator end iterator 
        @retval            - string_view container
    **/
    template<class fwd_it_t>
    views split(fwd_it_t itSepFirst, fwd_it_t itSepLast) const noexcept;

    /**
        @brief  Split string by separator
        @tparam string_t    - string-ish type, satisfying the "string_convertable" concept
        @param  sSeparator  - separator string
        @retval             - string_view container
    **/
    template<string_convertable string_t>
    views split(const string_t& sSeparator) const noexcept;

    /**
        @brief  Check if current string starts with char
        @param  chSymbol - char for comparison
        @retval          - true if starts with char
    **/
    bool starts_with(value_type chSymbol) const noexcept;

    /**
        @brief  Check if current string starts with string
        @param  pszStr   - const pointer to string
        @param  nStrSize - string length
        @retval          - true if starts with string
    **/
    bool starts_with(const_pointer pszStr, size_type nStrSize = npos) const noexcept;

    /**
        @brief  Check if current string starts with string
        @param  sStr - string to check 
        @retval      - true if starts with string
    **/
    bool starts_with(const basic_string& sStr) const noexcept;

    /**
        @brief  Check if current string starts with string
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - string begin iterator
        @param  itEnd    - string end iterator
        @retval          - true if starts with string
    **/
    template<class fwd_it_t>
    bool starts_with(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept;

    /**
        @brief  Check if current string starts with string
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string container to check
        @retval          - true if starts with string
    **/
    template<string_convertable string_t>
    bool starts_with(const string_t& sStr) const noexcept;

    /**
        @brief  Check if current string ends with char
        @param  chSymbol - char for comparison
        @retval          - true if ends with char
    **/
    bool ends_with(value_type chSymbol) const noexcept;

    /**
        @brief  Check if current string ends with string
        @param  pszStr   - const pointer to string
        @param  nStrSize - string length
        @retval          - true if ends with string
    **/
    bool ends_with(const_pointer pszStr, size_type nStrSize = npos) const noexcept;

    /**
        @brief  Check if current string ends with string
        @param  sStr - string to check
        @retval      - true if starts with string
    **/
    bool ends_with(const basic_string& sStr) const noexcept;

    /**
        @brief  Check if current string ends with string
        @tparam fwd_it_t - forward iterator type
        @param  itBegin  - string begin iterator
        @param  itEnd    - string end iterator
        @retval          - true if ends with string
    **/
    template<class fwd_it_t>
    bool ends_with(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept;

    /**
        @brief  Check if current string ends with string
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string container to check
        @retval          - true if starts with string
    **/
    template<string_convertable string_t>
    bool ends_with(const string_t& sStr) const noexcept;

    /**
        @brief   Check if string contains char
        @details Equal to find != npos
        @param   chSymbol - char to check
        @retval           - true if this string contains substring
    **/
    bool contains(value_type chSymbol) const noexcept;

    /**
        @brief   Check if string contains substring
        @details Equal to find != npos
        @param   pszStr   - substring to check
        @param   nStrSize - substring size 
        @retval           - true if this string contains substring
    **/
    bool contains(const_pointer pszStr, size_type nStrSize = npos) const noexcept;

    /**
        @brief   Check if string contains substring
        @details Equal to find != npos
        @param   sStr - string to check
        @retval       - true if this string contains substring
    **/
    bool contains(const basic_string& sStr) const noexcept;

    /**
        @brief   Check if string contains substring
        @details Equal to find != npos
        @tparam  fwd_it_t - forward iterator type
        @param   itBegin  - substring begin iterator 
        @param   itEnd    - substring end iterator 
        @retval           - true if this string contains substring
    **/
    template<class fwd_it_t>
    bool contains(fwd_it_t itBegin, fwd_it_t itEnd) const noexcept;

    /**
        @brief   Check if string contains substring
        @details Equal to find != npos
        @tparam  string_t - string-ish type, satisfying the "string_convertable" concept
        @param   sStr     - string to check
        @retval           - true if this string contains substring
    **/
    template<string_convertable string_t>
    bool contains(const string_t& sStr) const noexcept;

    /**
        @brief  operator=
        @param  pszSource - psz to assign
        @retval           - this object reference
    **/
    basic_string& operator=(const_pointer pszSource) noexcept;

    /**
        @brief  operator=
        @param  sStr - string to assign
        @retval      - this object reference
    **/
    basic_string& operator=(basic_string&& sStr) noexcept;

    /**
        @brief  operator=
        @param  sStr - string to assign
        @retval      - this object reference
    **/
    basic_string& operator=(const basic_string& sStr) noexcept;

    /**
        @brief  operator=
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to assign
        @retval          - this object reference
    **/
    template<string_convertable string_t>
    basic_string& operator=(const string_t& sStr) noexcept;

    /**
        @brief  operator+=
        @param  chSymbol - char to concat
        @retval          - this object reference
    **/
    basic_string& operator+=(value_type chSymbol) noexcept;

    /**
        @brief  operator+=
        @param  pszSource - psz to concat
        @retval           - this object reference
    **/
    basic_string& operator+=(const_pointer pszSource) noexcept;

    /**
        @brief  operator+=
        @param  sStr - string to concat
        @retval      - this object reference
    **/
    basic_string& operator+=(const basic_string& sStr) noexcept;

    /**
        @brief  operator+=
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to concat
        @retval          - this object reference
    **/
    template<string_convertable string_t>
    basic_string& operator+=(const string_t& sStr) noexcept;

    /**
        @brief  operator==
        @param  chSymbol - char to compare
        @retval          - true, if objects are equal
    **/
    bool operator==(value_type chSymbol) const noexcept;

    /**
        @brief  operator==
        @param  pszSource - psz to compare
        @retval           - true, if objects are equal
    **/
    bool operator==(const_pointer pszSource) const noexcept;

    /**
        @brief  operator==
        @param  sStr - string to compare
        @retval      - true, if objects are equal
    **/
    bool operator==(const basic_string& sStr) const noexcept;

    /**
        @brief  operator==
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - true, if objects are equal
    **/
    template<string_convertable string_t>
    bool operator==(const string_t& sStr) const noexcept;

    /**
        @brief  operator!=
        @param  chSymbol - char to compare
        @retval          - true, if objects are not equal
    **/
    bool operator!=(value_type chSymbol) const noexcept;

    /**
        @brief  operator!=
        @param  pszSource - psz to compare
        @retval           - true, if objects are not equal
    **/
    bool operator!=(const_pointer pszSource) const noexcept;

    /**
        @brief  operator!=
        @param  sStr - string to compare
        @retval      - true, if objects are not equal
    **/
    bool operator!=(const basic_string& sStr) const noexcept;

    /**
        @brief  operator!=
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - true, if objects are not equal
    **/
    template<string_convertable string_t>
    bool operator!=(const string_t& sStr) const noexcept;

    /**
        @brief  operator<
        @param  chSymbol - char to compare
        @retval          - true, if left object is less than right
    **/
    bool operator<(value_type chSymbol) const noexcept;

    /**
        @brief  operator<
        @param  pszSource - psz to compare
        @retval           - true, if left object is less than right
    **/
    bool operator<(const_pointer pszSource) const noexcept;

    /**
        @brief  operator<
        @param  sStr - string to compare
        @retval      - true, if left object is less than right
    **/
    bool operator<(const basic_string& sStr) const noexcept;

    /**
        @brief  operator<
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - true, if left object is less than right
    **/
    template<string_convertable string_t>
    bool operator<(const string_t& sStr) const noexcept;

    /**
        @brief  operator<=
        @param  chSymbol - char to compare
        @retval          - true, if left object is less or equal than right
    **/
    bool operator<=(value_type chSymbol) const noexcept;

    /**
        @brief  operator<=
        @param  pszSource - psz to compare
        @retval           - true, if left object is less or equal than right
    **/
    bool operator<=(const_pointer pszSource) const noexcept;

    /**
        @brief  operator<=
        @param  sStr - string to compare
        @retval      - true, if left object is less or equal than right
    **/
    bool operator<=(const basic_string& sStr) const noexcept;

    /**
        @brief  operator<=
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - true, if left object is less or equal than right
    **/
    template<string_convertable string_t>
    bool operator<=(const string_t& sStr) const noexcept;

    /**
        @brief  operator>
        @param  chSymbol - char to compare
        @retval          - true, if left object is greater than right
    **/
    bool operator>(value_type chSymbol) const noexcept;

    /**
        @brief  operator>
        @param  pszSource - psz to compare
        @retval           - true, if left object is greater than right
    **/
    bool operator>(const_pointer pszSource) const noexcept;

    /**
        @brief  operator>
        @param  sStr - string to compare
        @retval      - true, if left object is greater than right
    **/
    bool operator>(const basic_string& sStr) const noexcept;

    /**
        @brief  operator>
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - true, if left object is greater than right
    **/
    template<string_convertable string_t>
    bool operator>(const string_t& sStr) const noexcept;

    /**
        @brief  operator>=
        @param  chSymbol - char to compare
        @retval          - true, if left object is greater or equal than right
    **/
    bool operator>=(value_type chSymbol) const noexcept;

    /**
        @brief  operator>=
        @param  pszSource - psz to compare
        @retval           - true, if left object is greater or equal than right
    **/
    bool operator>=(const_pointer pszSource) const noexcept;

    /**
        @brief  operator>=
        @param  sStr - string to compare
        @retval      - true, if left object is greater or equal than right
    **/
    bool operator>=(const basic_string& sStr) const noexcept;

    /**
        @brief  operator>=
        @tparam string_t - string-ish type, satisfying the "string_convertable" concept
        @param  sStr     - string to compare
        @retval          - true, if left object is greater or equal than right
    **/
    template<string_convertable string_t>
    bool operator>=(const string_t& sStr) const noexcept;

    /**
        @brief  operator[]
        @param  nSymbol - number of char in the string
        @retval         - char on nSymbol position
    **/
    reference operator[](size_type nSymbol) noexcept;

    /**
        @brief  operator[]
        @param  nSymbol - number of char in the string
        @retval         - char on nSymbol position
    **/
    const_reference operator[](size_type nSymbol) const noexcept;

    /**
        @brief  operator string_view
        @retval string_view of this string
    **/
    operator string_view() const noexcept;

    /**
        @brief  operator bool
        @retval  - true if string is not empty
    **/
    explicit operator bool() const noexcept;

private:
    /**
        @brief   Resize string
        @details If new size is smaller, string will be truncated
        @param   nSymbols - new size
        @param   eType    - resize type
        @retval           - true if memory alloc is successful
    **/
    bool _resize(size_type nSymbols, string_resize_type eType = string_resize_type::common) noexcept;

    /**
        @brief  Common algorithm for trimming string to the left
        @tparam searcher_t - "searcher" type
        @param  searcher   - function that returns true if symbol has to be deleted
        @retval            - number of deleted symbols
    **/
    template<class searcher_t>
    size_type _trim_left(const searcher_t& searcher) noexcept;

    /**
        @brief  Common algorithm for trimming string to the right
        @tparam searcher_t - "searcher" type
        @param  searcher   - function that returns true if symbol has to be deleted
        @retval            - number of deleted symbols
    **/
    template<class searcher_t>
    size_type _trim_right(const searcher_t& searcher) noexcept;

    /**
        @brief  Common algorithm for trimming string to the both sides
        @tparam searcher_t - "searcher" type
        @param  searcher   - function that returns true if symbol has to be deleted
        @retval            - number of deleted symbols
    **/
    template<class searcher_t>
    size_type _trim(const searcher_t& searcher) noexcept;

    /**
        @brief  Common algorithm for finding substring
        @tparam comparator_t - "comparator" type
        @param  nBegin       - start searching index 
        @param  nEnd         - end searching index (npos - to the end) 
        @param  comparator   - comparator function 
        @retval              - substring index or npos if not found
    **/
    template<class comparator_t>
    size_type _find(size_type nBegin, size_type nEnd, const comparator_t& comparator) const noexcept;

    /**
        @brief  
        @tparam comparator_t - "comparator" type
        @param  nBegin       - start searching index 
        @param  nEnd         - end searching index 
        @param  comparator   - comparator function 
        @retval              - substring index or npos if not found
    **/
    template<class comparator_t>
    size_type _rfind(size_type nBegin, size_type nEnd, const comparator_t& comparator) const noexcept;

    /**
        @brief  Common algorithm for find_first_of
        @tparam incrementer_t - "incrementer" type
        @tparam fwd_it_t      - forward iterator type
        @param  itBegin       - begin it of "of" string
        @param  itEnd         - end it of "of" string
        @param  nBegin        - position at which the search is to begin
        @param  incrementer   - function that increments iterator and returns itEnd when string is over
        @retval               - symbol index or npos
    **/
    template<class incrementer_t, class fwd_it_t>
    size_type _find_first_of(fwd_it_t itBegin, fwd_it_t itEnd, size_type nBegin, const incrementer_t& incrementer)
        const noexcept;

    /**
        @brief  Common algorithm for find_last_of
        @tparam incrementer_t - "incrementer" type
        @tparam fwd_it_t      - forward iterator type
        @param  itBegin       - begin it of "of" string
        @param  itEnd         - end it of "of" string
        @param  nEnd          - position at which the search is to finish
        @param  incrementer   - function that increments iterator and returns itEnd when string is over
        @retval               - symbol index or npos
    **/
    template<class incrementer_t, class fwd_it_t>
    size_type _find_last_of(fwd_it_t itBegin, fwd_it_t itEnd, size_type nEnd, const incrementer_t& incrementer)
        const noexcept;

    /**
        @brief  Common algorithm for find_first_not_of
        @tparam incrementer_t - "incrementer" type
        @tparam fwd_it_t      - forward iterator type
        @param  itBegin       - begin it of "of" string
        @param  itEnd         - end it of "of" string
        @param  nBegin        - position at which the search is to begin
        @param  incrementer   - function that increments iterator and returns itEnd when string is over
        @retval               - symbol index or npos
    **/
    template<class incrementer_t, class fwd_it_t>
    size_type _find_first_not_of(fwd_it_t itBegin, fwd_it_t itEnd, size_type nBegin, const incrementer_t& incrementer)
        const noexcept;

    /**
        @brief  Common algorithm for find_last_not_of
        @tparam incrementer_t - "incrementer" type
        @tparam fwd_it_t      - forward iterator type
        @param  itBegin       - begin it of "of" string
        @param  itEnd         - end it of "of" string
        @param  nEnd          - position at which the search is to finish
        @param  incrementer   - function that increments iterator and returns itEnd when string is over
        @retval               - symbol index or npos
    **/
    template<class incrementer_t, class fwd_it_t>
    size_type _find_last_not_of(fwd_it_t itBegin, fwd_it_t itEnd, size_type nEnd, const incrementer_t& incrementer)
        const noexcept;

private:
    string_data<traits_t> m_Data;
};

using cstring = basic_string<char>;
using wstring = basic_string<wchar_t>;
using string  = basic_string<char_type>;

} // namespace qx

#include <qx/containers/string/string.inl>
