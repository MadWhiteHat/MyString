#ifndef _MY_TYPE_TRAITS_H
#define _MY_TYPE_TRAITS_H

namespace MyTypes {

template <typename CharT>
struct string_valid_type { static constexpr bool value = false; };
template<>
struct string_valid_type<char> { static constexpr bool value = true; };
template<>
struct string_valid_type<wchar_t> { static constexpr bool value = true; };
template<>
struct string_valid_type<char16_t> { static constexpr bool value = true; };
template<>
struct string_valid_type<char32_t> { static constexpr bool value = true; };

template <typename CharT>
inline constexpr bool string_valid_type_v = string_valid_type<CharT>::value;

} // namespace MyTypes

#endif // _MY_TYPE_TRAITS_H