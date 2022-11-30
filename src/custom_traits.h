#ifndef _CUSTOM_TRAITS_H
#define _CUSTOM_TRAITS_H

#include <iterator>
#include <type_traits>
#include <memory>

namespace MyTypes {
namespace __custom_traits {

// String traits
template <typename _CharT>
struct _StringValidType : std::false_type {};
template<>
struct _StringValidType<char> : std::true_type {};
template<>
struct _StringValidType<wchar_t> : std::true_type {};
template<>
struct _StringValidType<char16_t> : std::true_type {};
template<>
struct _StringValidType<char32_t> : std::true_type {};
#if __cplusplus > 201703L
template<>
struct _StringValidType<char8_t> : std::true_type {};
#endif

// Type presence resolution

template <typename _CharT>
inline constexpr bool _StringValidTypeV = _StringValidType<_CharT>::value;

template <typename _Alloc>
constexpr inline void _alloc_on_copy(_Alloc& __first, _Alloc& __second) {
  using __traits = std::allocator_traits<_Alloc>;
  using __pocca =  typename __traits::propagate_on_container_copy_assignment;

  if constexpr (__pocca::value) {
    __first = __second;
  }
}

template <typename _Alloc>
constexpr inline void _alloc_on_move(_Alloc& __first, _Alloc& __second) {

  using __traits = std::allocator_traits<_Alloc>;
  using __pocma =  typename __traits::propagate_on_container_move_assignment;
  if constexpr (__pocma::value) {
    __first = std::move(__second);
  }
}

template <typename _Alloc>
constexpr inline void _alloc_on_swap(_Alloc& __first, _Alloc& __second) {

  using __traits = std::allocator_traits<_Alloc>;
  using __pocs =  typename __traits::propagate_on_container_move_assignment;
  if constexpr (__pocs::value) {
    std::swap(__first, __second);
  }
}

// Requirements traits
template <typename _Alloc, typename = void>
struct _IsAllocator : std::false_type {};

// class _Alloc has method allocate
template <typename _Alloc>
struct _IsAllocator <_Alloc, std::void_t< typename _Alloc::value_type,
  decltype(std::declval<_Alloc&>().allocate(size_t{}))> > : std::true_type {};

template <typename _Alloc>
using _RequireAllocator = std::enable_if_t<
                            _IsAllocator<_Alloc>::value, _Alloc>;

template<typename _InputIter>
using _IterCategoryT = typename std::iterator_traits<
  _InputIter>::iterator_category;

template <typename _InputIter>
using _RequireInputIter = std::enable_if_t<
                            std::is_convertible_v<
                             _IterCategoryT<_InputIter>,
                             std::input_iterator_tag> >;

template <typename _From, typename _To>
using _ConvertibleFrom = std::enable_if_t< std::is_convertible_v<_From, _To> >;

} // namespace __custom_traits
} // namespace MyTypes

#endif // _CUSTOM_TRAITS_H
