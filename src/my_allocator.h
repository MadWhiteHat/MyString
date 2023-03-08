#ifndef _MY_ALLOCATOR_H
#define _MY_ALLOCATOR_H

#if __cplusplus > 201703L
#define _CXX20_CONSTEXPR constexpr
#else
#define _CXX20_CONSTEXPR
#endif

#include <iostream>
#include <type_traits>
#include <memory>
#include <utility>
#include <limits>

#include "my_exception.h"

namespace MyTypes {

template <typename _Tp>
struct MyAllocator {
  using value_type = _Tp;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using propagate_on_container_move_assignment = std::true_type;
  using is_always_equal = std::true_type;
#if __cplusplus < 201703L
  using pointer = _Tp*;
  using const_pointer = const _Tp*;
  using reference = _Tp&;
  using const_reference = const _Tp&;
  template <typename _Up>
  struct rebind {
    using other = MyTypes::MyAllocator<U>;
  };
#elif __cplusplus == 201703L
  using pointer [[deprecated]] = _Tp*;
  using const_pointer [[deprecated]] = const _Tp*;
  using reference [[deprecated]] = _Tp&;
  using const_reference [[deprecated]] = const _Tp&;
  template <typename _Up>
  struct rebind {
    using other = MyTypes::MyAllocator<_Up>;
  };
#endif
  _CXX20_CONSTEXPR
  MyAllocator() noexcept {}
  _CXX20_CONSTEXPR
  MyAllocator(const MyAllocator&) noexcept {}
  template <typename _Up>
  _CXX20_CONSTEXPR
  MyAllocator(const MyAllocator<_Up>&) noexcept {}
  _CXX20_CONSTEXPR
  ~MyAllocator() = default;

#if __cplusplus <= 201703L
#if __cplusplus == 201703L
  [[deprecated]]
#endif
  pointer address(reference __x) const noexcept {
    return std::addressof(__x);
  }
#if __cplusplus == 201703L
  [[deprecated]]
#endif
  const_pointer address(const_reference __x) const noexcept {
    return std::addressof(__x);
  }
#endif
#if __cplusplus == 201703L
  [[deprecated]]
#endif
  size_type max_size() const noexcept {
    return std::numeric_limits<size_type>::max() / sizeof(_Tp);
  }
#if __cplusplus > 201703L
[[nodiscard]] _CXX20_CONSTEXPR
#endif
#if __cplusplus == 201703L
  _Tp*
#else
  pointer
#endif
  allocate(size_t __count) {
    static_assert(sizeof(_Tp) != 0, "Cannot allocate incomplete types");
    if (__count > (size_t(-1) / sizeof(_Tp))) {
      __ThrowMyExceptionFmt<MyBadArrayLength>("bad array length");
    }
    return static_cast<_Tp*>(::operator new(__count * sizeof(_Tp)));
  }
  _CXX20_CONSTEXPR
  void deallocate (_Tp* __ptr, size_t __count __attribute__((unused))) {
    ::operator delete(__ptr, __count * sizeof(_Tp));
  }
#if __cplusplus <= 201703L
  template <typename _Up, typename... _Args>
#if __cplusplus == 201703L
  [[deprecated]]
#endif
  void construct(_Up* __ptr, _Args&&... __args) {
    ::new(reinterpret_cast<void*>(__ptr)) _Up(std::forward<_Args>(__args)...);
  }
#endif
#if __cplusplus <= 201703L
  template <typename _Up>
#if __cplusplus == 201703L
  [[deprecated]]
#endif
  void construct(_Up* __ptr) { __ptr->~_Up(); }
#endif
};

template<>
struct MyAllocator<void>;

_CXX20_CONSTEXPR
template <typename _T1, typename _T2>
bool operator==(
    const MyAllocator<_T1>& __lhs __attribute__((unused)),
    const MyAllocator<_T2>& __rhs __attribute__((unused)))
noexcept { return true; }
_CXX20_CONSTEXPR
template <typename _T1, typename _T2>
bool operator!=(
    const MyAllocator<_T1>& __lhs __attribute__((unused)),
    const MyAllocator<_T2>& __rhs __attribute__((unused)))
noexcept { return false; }

} // namespace MyTypes

#endif //_MY_ALLOCATOR_H
