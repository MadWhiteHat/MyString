#ifndef _MY_ITERATOR_H
#define _MY_ITERATOR_H

#include <iterator>
#include <type_traits>

#include "custom_traits.h"

namespace MyTypes {

template <typename _Iterator, typename _Container>
class _MyIterator {

 protected:
  using _TraitsType = std::iterator_traits<_Iterator>;

 public:

  using iterator_type = _Iterator;
  using difference_type = typename _TraitsType::difference_type;
  using value_type = typename _TraitsType::value_type;
  using pointer = typename _TraitsType::pointer;
  using reference = typename _TraitsType::reference;
  using iterator_category = typename _TraitsType::iterator_category;

  constexpr _MyIterator() noexcept : _MyIterator(_Iterator()) {}

  constexpr explicit _MyIterator(const _Iterator& __it) noexcept
    : _curr(__it) {}

  template <typename _Iter,
            typename = __custom_traits::_ConvertibleFrom<_Iter, _Iterator> >
  constexpr _MyIterator(const _MyIterator<_Iter, _Container>& __it) noexcept
    : _curr(__it.base()) {}

  constexpr reference operator*() const noexcept {
    return *_curr;
  }

  constexpr pointer operator->() const noexcept{
    return _curr;
  }

  constexpr _MyIterator& operator++() noexcept {
    ++_curr;
    return *this;
  }

  constexpr _MyIterator operator++(int) noexcept {
    return _MyIterator(_curr++);
  }

  constexpr _MyIterator& operator--() noexcept {
    --_curr;
    return *this;
  }

  constexpr _MyIterator operator--(int) noexcept {
    return _MyIterator(_curr--);
  }

  constexpr reference operator[](difference_type __pos) const noexcept {
    return _curr[__pos];
  }

  constexpr _MyIterator& operator+=(difference_type __n) noexcept {
    _curr += __n;
    return *this;
  }

  constexpr _MyIterator operator+(difference_type __n) const noexcept {
    return _MyIterator(_curr + __n);
  }

  constexpr _MyIterator& operator-=(difference_type __n) noexcept {
    _curr -= __n;
    return *this;
  }

  constexpr _MyIterator operator-(difference_type __n) const noexcept {
    return _MyIterator(_curr - __n);
  }

  constexpr const _Iterator& base() const noexcept {
    return _curr;
  }

 protected:

  _Iterator _curr;
};

} // namespace MyTypes

template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline bool operator==(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept {
  return __lhs.base() == __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline bool operator==(
  const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
  const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() == __rhs.base();
}


template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline bool operator!=(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept {
  return __lhs.base() != __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline bool operator!=(
  const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
  const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() != __rhs.base();
}


template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline bool operator>(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept {
  return __lhs.base() > __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline bool operator>(
  const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
  const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() > __rhs.base();
}


template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline bool operator<(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept {
  return __lhs.base() < __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline bool operator<(
  const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
  const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() < __rhs.base();
}


template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline bool operator>=(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept {
  return __lhs.base() >= __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline bool operator>=(
  const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
  const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() >= __rhs.base();
}


template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline bool operator<=(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept {
  return __lhs.base() <= __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline bool operator<=(
  const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
  const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() <= __rhs.base();
}

template <typename _IteratorR, typename _IteratorL, typename _Container>
[[nodiscard]]
inline auto operator-(
  const MyTypes::_MyIterator<_IteratorR, _Container>& __rhs,
  const MyTypes::_MyIterator<_IteratorL, _Container>& __lhs) noexcept
  -> decltype(__lhs.base() - __rhs.base()) {
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline typename MyTypes::_MyIterator<_Iterator, _Container>::difference_type
operator-(const MyTypes::_MyIterator<_Iterator, _Container>& __rhs,
          const MyTypes::_MyIterator<_Iterator, _Container>& __lhs) noexcept {
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator, typename _Container>
[[nodiscard]]
inline MyTypes::_MyIterator<_Iterator, _Container>
operator+(
  typename MyTypes::_MyIterator<_Iterator, _Container>::difference_type __n,
  const MyTypes::_MyIterator<_Iterator, _Container>& __it) noexcept {
  return MyTypes::_MyIterator<_Iterator, _Container>(__it.base() + __n);
}

namespace MyTypes {

template <typename _Iterator>
class MyReverseIterator {

protected:
  using _TraitsType = std::iterator_traits<_Iterator>;
 public:

  using iterator_type = _Iterator;
  using difference_type = typename _TraitsType::difference_type;
  using value_type = typename _TraitsType::value_type;
  using pointer = typename _TraitsType::pointer;
  using reference = typename _TraitsType::reference;
  using iterator_category = typename _TraitsType::iterator_category;

  constexpr MyReverseIterator()
    noexcept(std::is_nothrow_default_constructible_v<iterator_type>)
    : _curr(iterator_type()) {}

  constexpr explicit MyReverseIterator(iterator_type __it)
    noexcept(std::is_nothrow_copy_constructible_v<iterator_type>)
    : _curr(__it) {}

  constexpr MyReverseIterator(const MyReverseIterator& __it)
    noexcept(std::is_nothrow_copy_constructible_v<iterator_type>)
    : _curr(__it._curr) {}

  template <typename _Iter>
  constexpr MyReverseIterator(
    const MyReverseIterator<_Iter>& __other)
    noexcept(std::is_nothrow_constructible_v<iterator_type, _Iter>)
    : _curr(__other._curr) {}

  constexpr MyReverseIterator& operator=(const MyReverseIterator&) = default;

  template <typename _Iter>
  constexpr MyReverseIterator& operator=(
    const MyReverseIterator<_Iter>& __other)
    noexcept(std::is_nothrow_assignable_v<iterator_type, _Iter>) {
    _curr = __other._curr;
    return *this;
  }

  [[nodiscard]]
  constexpr reference operator*() const {
    iterator_type tmp(_curr);
    return *--tmp;
  }

  [[nodiscard]]
  constexpr pointer operator->() const {
    return std::addressof(operator*());
  }

  [[nodiscard]]
  constexpr reference operator[](difference_type __pos) const {
    return *(*this + __pos);
  }

  constexpr MyReverseIterator& operator++() {
    --_curr;
    return *this;
  }

  constexpr MyReverseIterator operator++(int) {
    MyReverseIterator __tmp;
    --_curr;
    return __tmp;
  }

  constexpr MyReverseIterator& operator--() {
    ++_curr;
    return *this;
  }

  constexpr MyReverseIterator operator--(int) {
    MyReverseIterator __tmp;
    ++_curr;
    return __tmp;
  }


  constexpr MyReverseIterator& operator+=(difference_type __n) {
    _curr -= __n;
    return *this;
  }

  [[nodiscard]]
  constexpr MyReverseIterator operator+(difference_type __n) const {
    return iterator_type(_curr - __n);
  }

  constexpr MyReverseIterator& operator-=(difference_type __n) {
    _curr += __n;
    return *this;
  }

  [[nodiscard]]
  constexpr MyReverseIterator operator-(difference_type __n) const {
    return iterator_type(_curr + __n);
  }

  [[nodiscard]]
  constexpr const iterator_type base() const {
    return _curr;
  }

 protected:

  _Iterator _curr;
};

template <typename _Iterator>
constexpr MyReverseIterator<_Iterator> MakeMyReverseIterator(_Iterator __it) {
  return MyReverseIterator<_Iterator>(__it);
}

} // namespace MyTypes

template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr bool operator==(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs) {
  return __lhs.base() == __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr bool operator==(
  const MyTypes::MyReverseIterator<_Iterator>& __rhs,
  const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() == __rhs.base();
}


template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr bool operator!=(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs) {
  return __lhs.base() != __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr bool operator!=(
  const MyTypes::MyReverseIterator<_Iterator>& __rhs,
  const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() != __rhs.base();
}


template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr bool operator>(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs) {
  return __lhs.base() > __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr bool operator>(
  const MyTypes::MyReverseIterator<_Iterator>& __rhs,
  const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() > __rhs.base();
}


template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr bool operator<(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs) {
  return __lhs.base() < __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr bool operator<(
  const MyTypes::MyReverseIterator<_Iterator>& __rhs,
  const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() < __rhs.base();
}


template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr bool operator>=(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs) {
  return __lhs.base() >= __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr bool operator>=(
  const MyTypes::MyReverseIterator<_Iterator>& __rhs,
  const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() >= __rhs.base();
}


template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr bool operator<=(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs) {
  return __lhs.base() <= __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr bool operator<=(
  const MyTypes::MyReverseIterator<_Iterator>& __rhs,
  const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() <= __rhs.base();
}

template <typename _IteratorR, typename _IteratorL>
[[nodiscard]]
inline constexpr auto operator-(
  const MyTypes::MyReverseIterator<_IteratorR>& __rhs,
  const MyTypes::MyReverseIterator<_IteratorL>& __lhs)
  -> decltype(__lhs.base() - __rhs.base()) {
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr typename MyTypes::MyReverseIterator<_Iterator>::difference_type
operator-(const MyTypes::MyReverseIterator<_Iterator>& __rhs,
          const MyTypes::MyReverseIterator<_Iterator>& __lhs) {
  return __lhs.base() - __rhs.base();
}

template <typename _Iterator>
[[nodiscard]]
inline constexpr MyTypes::MyReverseIterator<_Iterator>
operator+(typename MyTypes::MyReverseIterator<_Iterator>::difference_type __n,
          const MyTypes::MyReverseIterator<_Iterator>& __it) {
  return MyTypes::MyReverseIterator<_Iterator>(__it.base() + __n);
}

#endif // _MY_ITERATOR_H