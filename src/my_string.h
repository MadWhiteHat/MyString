#ifndef _MY_STRING_H
#define _MY_STRING_H
#define LOCAL_CAPACITY (1 << 4)
#define _AHO_CORASICK_SEARCH

#if __cplusplus > 201703L
#define _CXX20_CONSTEXPR constexpr
#else
#define _CXX20_CONSTEXPR
#endif


// 1. Related headers
//------------------------------------None------------------------------------//

// 2. C system headers
//------------------------------------None------------------------------------//

// 3. C++ standard library headers
#include <iostream>
#include <string>
#include <initializer_list>
// char_traits
#include <type_traits>
// iterator_traits
#include <iterator>
// allocator, allcoator_traits
#include <memory>
// polymorphic_allocator
#include <memory_resource>
// less
#include <functional>
// numeric_limits
#include <limits>

// 4. Other libraries' .h files.
//------------------------------------None------------------------------------//

// 5. Your project's .h files.
#include "custom_traits.h"
#include "my_exception.h"
#include "my_iterator.h"
#include "search_trie.h"

// Variables: lowerCamelCase
// Custom types: UpperCamelCsse
// New names/aliases to builtin types: snake_case
// Custom functions: UpperCamelCase

namespace MyTypes {

template <typename _CharT,
          typename _Traits = std::char_traits<_CharT>,
          typename _Alloc = std::allocator<_CharT> >
class MyBasicString {

 private:
  static_assert(__custom_traits::_StringValidTypeV<_CharT>,
    "Invalid template parameter _CharT." 
    " Valid types: char, wchar_t, char16_t, char32_t"
#if __cplusplus > 201703L
     ", char8_t"
#endif
  );

  static_assert(LOCAL_CAPACITY % 4 == 0,
                "LOCAL_CAPACITY must be divisible by 4");

  using _AllocatorTraits = std::allocator_traits<_Alloc>;

 public:
  using traits_type = _Traits;
  using value_type = _CharT;
  using allocator_type = _Alloc;
  using size_type = typename _AllocatorTraits::size_type;
  using difference_type = typename _AllocatorTraits::difference_type;
  using reference =  value_type&;
  using const_reference = const value_type&;
  using pointer = typename _AllocatorTraits::pointer;
  using const_pointer = typename _AllocatorTraits::const_pointer;
  using iterator = _MyIterator<pointer, MyBasicString>;
  using const_iterator = _MyIterator<const_pointer, MyBasicString>;
  using reverse_iterator = MyReverseIterator<iterator>;
  using const_reverse_iterator = MyReverseIterator<const_iterator>;

  static const size_type npos = static_cast<size_type>(-1);

//--------------------------------Constructors--------------------------------//

  _CXX20_CONSTEXPR
  MyBasicString() noexcept(std::is_nothrow_default_constructible_v<_Alloc>);
  explicit
  _CXX20_CONSTEXPR
  MyBasicString(const _Alloc& __alloc) noexcept;
  template <typename = __custom_traits::_RequireAllocator<_Alloc>>
  _CXX20_CONSTEXPR
  MyBasicString(const size_type __count, value_type __ch,
                const _Alloc& __alloc = _Alloc());
  template <typename = __custom_traits::_RequireAllocator<_Alloc>>
  explicit
  _CXX20_CONSTEXPR
  MyBasicString(value_type __ch, const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const std::basic_string<value_type>& __other,
                size_type __pos, const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const MyBasicString& __other, size_type __pos,
                const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const std::basic_string<value_type>& __other, size_type __pos,
                size_type __count, const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const MyBasicString& __other, size_type __pos,
                size_type __count, const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const_pointer __cStr, size_type __count,
                const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const_pointer __cStr, const _Alloc& __alloc = _Alloc());
  template <typename _InputIter,
            typename = __custom_traits::_RequireInputIter<_InputIter> >
  _CXX20_CONSTEXPR
  MyBasicString(_InputIter __first, _InputIter __last,
                const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(const std::basic_string<value_type>& __other);
  _CXX20_CONSTEXPR
  MyBasicString(const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString(const std::basic_string<value_type>& __other,
                const _Alloc& __alloc);
  _CXX20_CONSTEXPR
  MyBasicString(const MyBasicString& __other,
                const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(MyBasicString&& __other) noexcept;
  _CXX20_CONSTEXPR
  MyBasicString(MyBasicString&& __other, const _Alloc& __alloc)
  noexcept(_AllocatorTraits::is_always_equal);
  _CXX20_CONSTEXPR
  MyBasicString(std::initializer_list<value_type> __ilist,
                const _Alloc& __alloc = _Alloc());
  _CXX20_CONSTEXPR
  MyBasicString(std::nullptr_t) = delete;

//---------------------------------Destructor---------------------------------//

  _CXX20_CONSTEXPR
  ~MyBasicString() noexcept;

//----------------------------Assignment operator-----------------------------//

  _CXX20_CONSTEXPR
  MyBasicString& operator=(const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& operator=(const std::basic_string<value_type>& __other);

  _CXX20_CONSTEXPR
  MyBasicString& operator=(MyBasicString&& __other)
  noexcept(_AllocatorTraits::propagate_on_container_move_assignment::value
           || _AllocatorTraits::is_always_equal::value);

  _CXX20_CONSTEXPR
  MyBasicString& operator=(const_pointer __cStr);

  _CXX20_CONSTEXPR
  MyBasicString& operator=(value_type __ch);

  _CXX20_CONSTEXPR
  MyBasicString& operator=(std::initializer_list<value_type> __ilist);

  _CXX20_CONSTEXPR
  MyBasicString& operator=(std::nullptr_t) = delete;

//-----------------------------------Assign-----------------------------------//

  _CXX20_CONSTEXPR
  MyBasicString& assign(size_type __count, value_type __ch);

  _CXX20_CONSTEXPR
  MyBasicString& assign(const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& assign(const std::basic_string<value_type>& __other);

  _CXX20_CONSTEXPR
  MyBasicString& assign(const MyBasicString& __other, size_type __pos,
                        size_type __count = npos);
  _CXX20_CONSTEXPR
   MyBasicString& assign(const std::basic_string<value_type>& __other,
       size_type __pos, size_type __count = npos);

  _CXX20_CONSTEXPR
  MyBasicString& assign(MyBasicString&& __other) noexcept(
    _AllocatorTraits::propagate_on_container_move_assignment::value
    || _AllocatorTraits::is_always_equal::value);

  _CXX20_CONSTEXPR
  MyBasicString& assign(const_pointer __cStr, size_type __count);

  _CXX20_CONSTEXPR
  MyBasicString& assign(const_pointer __cStr);

  template <typename _InputIter,
            typename = __custom_traits::_RequireInputIter<_InputIter>>
  _CXX20_CONSTEXPR
  MyBasicString& assign(_InputIter __first, _InputIter __last);

  _CXX20_CONSTEXPR
  MyBasicString& assign(std::initializer_list<value_type> __ilist);

//---------------------------------Allocator----------------------------------//
  _CXX20_CONSTEXPR
  allocator_type get_allocator() const noexcept;

//-------------------------------Element access-------------------------------//

  _CXX20_CONSTEXPR
  reference at(size_type __pos);
  _CXX20_CONSTEXPR
  const_reference at(size_type __pos) const;

  _CXX20_CONSTEXPR
  reference operator[](size_type __pos) noexcept;
  _CXX20_CONSTEXPR
  const_reference operator[](size_type __pos) const noexcept;

  _CXX20_CONSTEXPR
  reference front() noexcept;
  _CXX20_CONSTEXPR
  const_reference front() const noexcept;

  _CXX20_CONSTEXPR
  reference back() noexcept;
  _CXX20_CONSTEXPR
  const_reference back() const noexcept;

  _CXX20_CONSTEXPR
  pointer data() noexcept;
  _CXX20_CONSTEXPR
  const_pointer data() const noexcept;

  _CXX20_CONSTEXPR
  pointer c_str() noexcept;
  _CXX20_CONSTEXPR
  const_pointer c_str() const noexcept;

//---------------------------------Iterators----------------------------------//

  _CXX20_CONSTEXPR
  iterator begin() noexcept;
  _CXX20_CONSTEXPR
  const_iterator begin() const noexcept;
  _CXX20_CONSTEXPR
  const_iterator cbegin() const noexcept;

  _CXX20_CONSTEXPR
  iterator end() noexcept;
  _CXX20_CONSTEXPR
  const_iterator end() const noexcept;
  _CXX20_CONSTEXPR
  const_iterator cend() const noexcept;

  _CXX20_CONSTEXPR
  reverse_iterator rbegin() noexcept;
  _CXX20_CONSTEXPR
  const_reverse_iterator rbegin() const noexcept;
  _CXX20_CONSTEXPR
  const_reverse_iterator crbegin() const noexcept;

  _CXX20_CONSTEXPR
  reverse_iterator rend() noexcept;
  _CXX20_CONSTEXPR
  const_reverse_iterator rend() const noexcept;
  _CXX20_CONSTEXPR
  const_reverse_iterator crend() const noexcept;

//----------------------------------Capacity----------------------------------//

  [[nodiscard]]
  _CXX20_CONSTEXPR
  bool empty() const noexcept;

  _CXX20_CONSTEXPR
  size_type size() const noexcept;
  _CXX20_CONSTEXPR
  size_type length() const noexcept;

  _CXX20_CONSTEXPR
  size_type max_size() const noexcept;

  _CXX20_CONSTEXPR
  void reserve(size_type __newCap);

#if __cplusplus > 201703L
  [[deprecated]]
#endif
  void reserve();

  _CXX20_CONSTEXPR
  size_type capacity() const noexcept;

  _CXX20_CONSTEXPR
  void shrink_to_fit();

//---------------------------------Operations---------------------------------//

  _CXX20_CONSTEXPR
  void clear() noexcept;

  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx, size_type __count, value_type __ch);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx, value_type __ch);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx, const_pointer __cStr);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx, const_pointer __cStr,
                        size_type __count);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx,
                        const std::basic_string<value_type>& __other);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx, const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx,
                        const std::basic_string<value_type>& __other,
                        size_type __idxStr, size_type __count = npos);
  _CXX20_CONSTEXPR
  MyBasicString& insert(size_type __idx, const MyBasicString& __other,
                        size_type __idxStr, size_type __count = npos);
  _CXX20_CONSTEXPR
  iterator insert(const_iterator __pos, value_type __ch);
  _CXX20_CONSTEXPR
  iterator insert(const_iterator __pos, size_type __count, value_type __ch);
  template <typename _InputIter,
            typename = __custom_traits::_RequireInputIter<_InputIter>>
  _CXX20_CONSTEXPR
  iterator insert(const_iterator __pos, _InputIter __beg, _InputIter __end);
  _CXX20_CONSTEXPR
  iterator insert(const_iterator __pos,
                  std::initializer_list<value_type> __ilist);

  _CXX20_CONSTEXPR
  MyBasicString& erase(size_type __idx = 0, size_type __count = npos);
  _CXX20_CONSTEXPR
  iterator erase(const_iterator __pos);
  _CXX20_CONSTEXPR
  iterator erase(const_iterator __beg, const_iterator __end);

  _CXX20_CONSTEXPR
  void push_back(value_type __ch);

  _CXX20_CONSTEXPR
  void pop_back();

  _CXX20_CONSTEXPR
  MyBasicString& append(size_type __count, value_type __ch);
  _CXX20_CONSTEXPR
  MyBasicString& append(const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& append(const std::basic_string<value_type>& __other);
  _CXX20_CONSTEXPR
  MyBasicString& append(const MyBasicString& __other, size_type __pos,
                        size_type __count = npos);
  _CXX20_CONSTEXPR
  MyBasicString& append(const std::basic_string<value_type>& __other,
                        size_type __pos, size_type __count = npos);
  _CXX20_CONSTEXPR
  MyBasicString& append(const_pointer __cStr, size_type __count);
  _CXX20_CONSTEXPR
  MyBasicString& append(const_pointer __cStr);
  template <typename _InputIter,
            typename = __custom_traits::_RequireInputIter<_InputIter>>
  _CXX20_CONSTEXPR
  MyBasicString& append(_InputIter __beg, _InputIter __end);
  _CXX20_CONSTEXPR
  MyBasicString& append(std::initializer_list<value_type> __ilist);

  _CXX20_CONSTEXPR
  MyBasicString& operator+=(const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& operator+=(const std::basic_string<value_type>& __other);
  _CXX20_CONSTEXPR
  MyBasicString& operator+=(value_type __ch);
  _CXX20_CONSTEXPR
  MyBasicString& operator+=(const_pointer __cStr);
  _CXX20_CONSTEXPR
  MyBasicString& operator+=(std::initializer_list<value_type> __ilist);

  _CXX20_CONSTEXPR
  int32_t compare(const MyBasicString& __other) const noexcept;
  _CXX20_CONSTEXPR
  int32_t compare(const std::basic_string<value_type> __other) const noexcept;
  _CXX20_CONSTEXPR
  int32_t compare(size_type __pos1, size_type __count1,
                  const MyBasicString& __other) const;
  _CXX20_CONSTEXPR
  int32_t compare(size_type __pos1, size_type __count1,
                  const std::basic_string<value_type>& __other) const;
  _CXX20_CONSTEXPR
  int32_t compare(size_type __pos1, size_type __count1,
                  const MyBasicString& __other, size_type __pos2,
                  size_type __count2 = npos) const;
  _CXX20_CONSTEXPR
  int32_t compare(size_type __pos1, size_type __count1,
                  const std::basic_string<value_type>& __other, size_type __pos2,
                  size_type __count2 = npos) const;
  _CXX20_CONSTEXPR
  int32_t compare(const_pointer __cStr) const;
  _CXX20_CONSTEXPR
  int32_t compare(size_type __pos1, size_type __count1, const_pointer __cStr)
  const;
  _CXX20_CONSTEXPR
  int32_t compare(size_type __pos1, size_type __count1, const_pointer __cStr,
                  size_type __count2) const;

  _CXX20_CONSTEXPR
  bool starts_with(value_type __ch) const noexcept;
  _CXX20_CONSTEXPR
  bool starts_with(const_pointer __cStr) const;

  _CXX20_CONSTEXPR
  bool ends_with(value_type __ch) const noexcept;
  _CXX20_CONSTEXPR
  bool ends_with(const_pointer __cStr)const;

  _CXX20_CONSTEXPR
  bool contains(value_type __ch) const noexcept;
  _CXX20_CONSTEXPR
  bool contains(const_pointer __cStr) const;

  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos, size_type __count,
                         const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos, size_type __count,
                         const std::basic_string<value_type>& __other);
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg, const_iterator __end,
                         const MyBasicString& __other);
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg, const_iterator __end,
                         const std::basic_string<value_type>& __other);
  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos1, size_type __count1,
                         const MyBasicString& __other, size_type __pos2,
                         size_type __count2 = npos);
  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos1, size_type __count1,
                         const std::basic_string<value_type>& __other,
                         size_type __pos2, size_type __count2 = npos);
  template <typename _InputIter,
            typename = __custom_traits::_RequireInputIter<_InputIter>>
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg1, const_iterator __end1,
                         _InputIter __beg2, _InputIter __end2);
  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos, size_type __count1,
                         const_pointer __cStr, size_type __count2);
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg, const_iterator __end,
                         const_pointer __cStr, size_type __count);
  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos, size_type __count,
                         const_pointer __cStr);
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg, const_iterator __end,
                         const_pointer __cStr);
  _CXX20_CONSTEXPR
  MyBasicString& replace(size_type __pos, size_type __count1,
                         size_type __count2, value_type __ch);
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg, const_iterator __end,
                         size_type __count, value_type __ch);
  _CXX20_CONSTEXPR
  MyBasicString& replace(const_iterator __beg, const_iterator __end,
                         std::initializer_list<value_type> __ilist);

  _CXX20_CONSTEXPR
  MyBasicString substr(size_type __pos = 0, size_type __count = npos) const;

  _CXX20_CONSTEXPR
  size_type copy(pointer __dest, size_type __count, size_type __pos = 0) const;

  _CXX20_CONSTEXPR
  void resize(size_type __count);
  _CXX20_CONSTEXPR
  void resize(size_type __count, value_type __ch);

  _CXX20_CONSTEXPR
  void swap(MyBasicString& __other) noexcept(
    _AllocatorTraits::propagate_on_container_swap::value
   || _AllocatorTraits::is_always_equal::value);



  _CXX20_CONSTEXPR
  size_type find(const MyBasicString& __other, size_type __pos = 0)
  const noexcept;
  _CXX20_CONSTEXPR
  size_type find(const std::basic_string<value_type>& __other,
                 size_type __pos = 0)
  const noexcept;
  _CXX20_CONSTEXPR
  size_type find(const_pointer __cStr, size_type __pos, size_type __count)
  const;
  _CXX20_CONSTEXPR
  size_type find(const_pointer __cStr, size_type __pos = 0) const;
  _CXX20_CONSTEXPR
  size_type find(value_type __ch, size_type __pos = 0) const noexcept;

  _CXX20_CONSTEXPR
  size_type rfind(const MyBasicString& __other, size_type __pos = npos)
  const noexcept;
  _CXX20_CONSTEXPR
  size_type rfind(const std::basic_string<value_type>& __other,
                  size_type __pos = npos) const noexcept;
  _CXX20_CONSTEXPR
  size_type rfind(const_pointer __cStr, size_type __pos, size_type __count)
  const;
  _CXX20_CONSTEXPR
  size_type rfind(const_pointer __cStr, size_type __pos = npos) const;
  _CXX20_CONSTEXPR
  size_type rfind(value_type __ch, size_type __pos = npos) const noexcept;

  _CXX20_CONSTEXPR
  size_type find_first_of(const MyBasicString& __other, size_type __pos = 0)
  const noexcept;
  _CXX20_CONSTEXPR
  size_type find_first_of(const std::basic_string<value_type>& __other,
                          size_type __pos = 0) const noexcept;
  _CXX20_CONSTEXPR
  size_type find_first_of(const_pointer __cStr, size_type __pos,
                          size_type __count) const;
  _CXX20_CONSTEXPR
  size_type find_first_of(const_pointer __cStr, size_type __pos = 0) const;
  _CXX20_CONSTEXPR
  size_type find_first_of(value_type __ch, size_type __pos = 0) const noexcept;

  _CXX20_CONSTEXPR
  size_type find_first_not_of(const MyBasicString& __other, size_type __pos = 0)
  const noexcept;
  _CXX20_CONSTEXPR
  size_type find_first_not_of(const std::basic_string<value_type>& __other,
                              size_type __pos = 0) const noexcept;
  _CXX20_CONSTEXPR
  size_type find_first_not_of(const_pointer __cStr, size_type __pos,
                              size_type __count) const;
  _CXX20_CONSTEXPR
  size_type find_first_not_of(const_pointer __cStr, size_type __pos = 0) const;
  _CXX20_CONSTEXPR
  size_type find_first_not_of(value_type __ch, size_type __pos = 0) const
  noexcept;

  _CXX20_CONSTEXPR
  size_type find_last_of(const MyBasicString& __other, size_type __pos = npos)
  const noexcept;
  _CXX20_CONSTEXPR
  size_type find_last_of(const std::basic_string<value_type>& __other,
                         size_type __pos = npos) const noexcept;
  _CXX20_CONSTEXPR
  size_type find_last_of(const_pointer __cStr, size_type __pos,
                         size_type __count) const;
  _CXX20_CONSTEXPR
  size_type find_last_of(const_pointer __cStr, size_type __pos = npos) const;
  _CXX20_CONSTEXPR
  size_type find_last_of(value_type __ch, size_type __pos = npos) const
  noexcept;

  _CXX20_CONSTEXPR
  size_type find_last_not_of(const MyBasicString& __other,
                             size_type __pos = npos) const noexcept;
  _CXX20_CONSTEXPR
  size_type find_last_not_of(const std::basic_string<value_type>& __other,
                             size_type __pos = npos) const noexcept;
  _CXX20_CONSTEXPR
  size_type find_last_not_of(const_pointer __cStr, size_type __pos,
                             size_type __count) const;
  _CXX20_CONSTEXPR
  size_type find_last_not_of(const_pointer __cStr, size_type __pos = npos)
  const;
  _CXX20_CONSTEXPR
  size_type find_last_not_of(value_type __ch, size_type __pos = npos) const
  noexcept;

 private:

  struct _Alloc_hider : allocator_type {
    _Alloc_hider(pointer __data, const _Alloc& __alloc)
      : allocator_type(__alloc), _data(__data) {}
    _Alloc_hider(pointer __data, _Alloc&& __alloc = _Alloc())
      : allocator_type(std::move(__alloc)), _data(__data) {}

    pointer _data;
  };

  inline void _Data(pointer __data) noexcept { _dataPlus._data = __data; }

  inline void _Length(size_type __len) noexcept { _stringLength = __len; }

  inline pointer _Data() const noexcept { return _dataPlus._data; }

  inline pointer _LocalData() {
    return std::pointer_traits<pointer>::pointer_to(*_localData);
  }

  inline const_pointer _LocalData() const noexcept {
    return std::pointer_traits<const_pointer>::pointer_to(*_localData);
  }

  inline void _Capacity(size_type __cap) noexcept {
    _allocatedCapacity = __cap;
  }

  inline void _SetLength(size_type __len) {
    this->_Length(__len);
    traits_type::assign(this->_Data()[__len], value_type(0));
  }

  inline bool _IsLocal() const noexcept {
    return this->_Data() == this->_LocalData();
  }

  inline void _Dispose() {
    if (!this->_IsLocal()) { this->_Destroy(_allocatedCapacity); }
  }

  template <typename _InputIter>
  void _Construct(_InputIter __beg, _InputIter __end, std::input_iterator_tag) {
    size_type __len = 0;
    size_type __capacity = size_type(_localCapacity);

    pointer __p = this->_LocalData();

    while(__beg != __end && __len < __capacity) {
      __p[__len++] = *__beg;
      ++__beg;
    }

    struct _Guard {
      explicit _Guard(MyBasicString* __s) : _guarded(__s) { }
      ~_Guard() { if (_guarded) _guarded->_Dispose(); }

      MyBasicString* _guarded;
    } __guard(this);

    while (__beg != __end) {
      if (__len == __capacity + 1) {
        __capacity = __len + 1;
        pointer __another = this->_Create(__capacity, __len);
        this->_Copy(__another, this->_Data(), __len);
        this->_Dispose();
        this->_Data(__another);
        this->_Capacity(__capacity);
      }
      traits_type::assign(this->_Data()[__len++], *__beg);
      ++__beg;
    }

    __guard._guarded = nullptr;
    this->_SetLength(__len);
  }

  template <typename _ForwardIter>
  void _Construct(_ForwardIter __beg, _ForwardIter __end,
                  std::forward_iterator_tag) {
    size_type __dnew = static_cast<size_type>(std::distance(__beg, __end)) + 1;
    if (__dnew > size_type(_localCapacity)) {
      this->_Data(this->_Create(__dnew, size_type(0)));
      this->_Capacity(__dnew);
    } else {
      this->_Data(this->_LocalData());
    }

    struct _Guard {
      explicit _Guard(MyBasicString* __s) : _guarded(__s) { }
      ~_Guard() { if (_guarded) _guarded->_Dispose(); }

      MyBasicString* _guarded;
    } __guard(this);
    this->_CopyChars(_Data(), __beg, __end);

    __guard._guarded = nullptr;
    this->_SetLength(__dnew);
  }

  void _Construct(size_type __count, value_type __ch) {
    if (__count >= size_type(_localCapacity)) {
      this->_Data(this->_Create(++__count, size_type(0)));
      this->_Capacity(__count);
    } else {
      if (__count) {
        this->_Assign(_Data(), __count, __ch);
      }
    }
    this->_SetLength(this->capacity());
  }

  pointer _Create(size_type& __cap, size_type __oldCapacity) {
    if (__cap > this->max_size()) {
      __ThrowMyExceptionFmt<MyLengthError>("MyBasicString::_Create");
    }
    if (__cap > __oldCapacity && __cap < 2 * __oldCapacity) {
      __cap = 2 * __oldCapacity;
    }
    if (__cap > this->max_size()) {
      __cap = this->max_size();
    }
    return _AllocatorTraits::allocate(this->_GetAllocator(), __cap);
  }

  inline void _Destroy(size_type __size) noexcept {
    _AllocatorTraits::deallocate(this->_GetAllocator(), this->_Data(), __size);
  }

  inline allocator_type& _GetAllocator() noexcept { return _dataPlus; }
  inline const allocator_type& _GetAllocator() const noexcept {
    return _dataPlus;
  }

  size_type _Check(size_type __pos, const char* __methodName) const {
    if (__pos > this->length()) {
      __ThrowMyExceptionFmt<MyOutOfRange>(
        ("Out of range in %s: __pos (which is %zu) > "
         " this->length() (which is %zu)"),
        __methodName, __pos, this->length());
    }
    return __pos;
  }

  template<typename _BasicCharT, typename _BasicTraits, typename _BasicAlloc>
  static size_type _Check(
    std::basic_string<_BasicCharT, _BasicTraits, _BasicAlloc>& __other,
    size_type __pos, const char* __methodName) {
    if (__pos > __other.length()) {
      __ThrowMyExceptionFmt<MyOutOfRange>(
        ("Out of range in %s: __pos (which is %zu) > __other.length()" 
         " [decltype(__other) = basic_string] (which is %zu)"),
        __methodName, __pos, __other->length());
    }
    return __pos;
  }

  void _CheckLength(size_type __n1, size_type __n2, const char* __msg) const {
    if (this->max_size() - this->length() - __n1 < __n2) {
      __ThrowMyExceptionFmt<MyLengthError>("%s", __msg);
    }
  }

  size_type _Limit(size_type __pos, size_type __offset) const noexcept{
    const bool __testoff = __offset < this->length() - __pos;
    return __testoff ? __offset : this->length() - __pos;
  }

  bool _Disjunct(const_pointer __cStr) {
    return std::less<const_pointer>()(__cStr, this->_Data())
      || std::less<const_pointer>()(this->_Data() + this->length(), __cStr);
  }

  void _Mutate(size_type __pos, size_type __len1, const_pointer __cStr,
               size_type __len2) {
    const size_type __count = this->length() - __pos - __len1;

    size_type __newCap = this->length() + __len2 - __len1;
    pointer __another = _Create(__newCap, this->capacity());

    if (__pos) {
      this->_Copy(__another, _Data(), __pos);
    }
    if (__cStr && __len2) {
      this->_Copy(__another + __pos, __cStr, __len2);
    }
    if (__count) {
      this->_Copy(__another + __pos + __len2, this->_Data() + __pos + __len1,
        __count);
    }
    this->_Dispose();
    this->_Data(__another);
    this->_Capacity(__newCap);
  }

  MyBasicString& _ReplaceAux(size_type __pos1, size_type __count1,
                             size_type __count2, value_type __ch) {
    this->_CheckLength(__count1, __count2, "MyBasicString::_ReplaceAux");

    const size_type __oldLen = this->length();
    const size_type __newLen = __oldLen + __count2 - __count1;

    if (__newLen < this->capacity()) {
      pointer __inner = this->_Data() + __pos1;

      const size_type __replCount = __oldLen - __pos1 - __count1;
      if (__replCount && __count1 != __count2) {
        this->_Move(__inner + __count2, __inner + __count1, __replCount);
      }
    } else {
      this->_Mutate(__pos1, __count1, 0, __count2);
    }
    if (__count2) {
      this->_Assign(this->_Data() + __pos1, __count2, __ch);
    }
    this->_SetLength(__newLen + 1);
    return *this;
  }

  template <typename _InputIter,
            typename = __custom_traits::_RequireInputIter<_InputIter> >
  MyBasicString& __Replace(const_iterator __beg1, const_iterator __end1,
    _InputIter __beg2, _InputIter __end2) {
    const MyBasicString __str(__beg2, __end2, this->_GetAllocator());
    const size_type __count = __end1 - __beg1;
    return this->_Replace(__beg1 - this->cbegin(), __count, __str._Data(),
      __str.length());
  }

  MyBasicString& _Replace(size_type __pos, size_type __len1,
                          const_pointer __cStr, const size_type __len2) {
    this->_CheckLength(__len1, __len2, "MyBasicString::_Replace");

    const size_type __oldLen = this->length();
    const size_type __newLen = __oldLen + __len2 - __len1;

    if(__newLen < this->capacity()) {
      pointer __inner = this->_Data() + __pos;
      const size_type __replCount = __oldLen - __pos - __len1;
      if (this->_Disjunct(__cStr)) {
        if (__replCount && __len1 != __len2) {
          this->_Move(__inner + __len2, __inner + __len1, __replCount);
        }
        if (__len2) {
          this->_Copy(__inner, __cStr, __len2);
        }
      } else {
        if (__len2 && __len2 <= __len1) {
          this->_Move(__inner, __cStr, __len2);
        }
        if (__replCount && __len1 != __len2) {
          this->_Move(__inner + __len2, __inner + __len1, __replCount);
        }
        if (__len2 > __len1) {
          const size_type __innerOff= (__cStr - __inner) + (__len2 - __len1);
          if (__cStr + __len2 <= __inner + __len1) {
            this->_Move(__inner, __cStr, __len2);
          } else if (__cStr >= __inner + __len1) {
            this->_Copy(__inner, __inner + __innerOff, __len2);
          } else {
            const size_type __numLeft = (__inner + __len1) - __cStr;
            this->_Move(__inner, __cStr, __numLeft);
            this->_Copy(__inner + __innerOff, __inner + __len2,
              __len2 - __numLeft);
          }
        }
      }
    } else {
      this->_Mutate(__pos, __len1, __cStr, __len2);
    }
    this->_SetLength(__newLen);
    return *this;
  }

  void _Erase(size_type __idx, size_type __count) {
    const size_type __pastCnt = this->length() - __idx - __count;
    if (__pastCnt && __count) {
      this->_Move(this->_Data() + __idx, this->_Data() + __idx + __count,
        __pastCnt);
    }
    this->_SetLength(this->length() - __count);
  }

  MyBasicString& _Append(const_pointer __cStr, size_type __count) {
    const size_type __length = __count + this->length();

    if (__length < this->capacity()) {
      this->_Copy(this->_Data() + this->length(), __cStr, __count);
    } else {
      this->_Mutate(this->length(), size_type(0), __cStr, __count);
    }
    this->_SetLength(__length);
    return *this;
  }

  template<typename _BasicCharT, typename _BasicTraits, typename _BasicAlloc>
  static size_type _Limit(
    std::basic_string<_BasicCharT, _BasicTraits, _BasicAlloc>& __other,
    size_type __pos, size_type __offset) noexcept{
    const bool __testoff = __offset < __other->length() - __pos;
    return __testoff ? __offset : __other->length() - __pos;
  }

  static void _Copy(pointer __dest, const_pointer __src, size_type __count) {
    if (__count == 1) { traits_type::assign(*__dest, *__src); }
    else { traits_type::copy(__dest, __src, __count); }
  }

  static void _Move(pointer __dest, const_pointer __src, size_type __count) {
    if (__count == 1) { traits_type::assign(*__dest, *__src); }
    else { traits_type::move(__dest, __src, __count); }
  }

  static void _Assign(pointer __dest, const_pointer __src, size_type __count) {
    if (__count == 1) { traits_type::assign(*__dest, *__src); }
    else { traits_type::assign(__dest, __src, __count); }
  }

  template <typename _Iter>
  static void _CopyChars(pointer __p, _Iter __beg, _Iter __end) {
    for (; __beg != __end; ++__beg, ++__p) {
      traits_type::assign(*__p, *__beg);
    }
  }

  static void _CopyChars(pointer __p, iterator __it1, iterator __it2) {
    _CopyChars(__p, __it1.base(), __it2.base());
  }

  static void _CopyChars(pointer __p, const_iterator __it1,
                         const_iterator __it2) {
    _CopyChars(__p, __it1.base(), __it2.base());
  }

  static void _CopyChars(pointer __p, pointer __beg, pointer __end) {
    _Copy(__p, __beg, __end - __beg);
  }

  static void _CopyChars(pointer* __p, const_pointer* __beg,
                         const_pointer* __end) {
    _Copy(__p, __beg, __end - __beg);
  }

  static inline int _CompareHelper(size_type __count1, size_type __count2) {
    using __limits = std::numeric_limits<int>;
    const difference_type __diff= __count1 - __count2;
    if (__diff > __limits::max()) {
      return __limits::max();
    } else if (__diff < __limits::min()) {
      return __limits::min();
    }
    return static_cast<int>(__diff);
  }

  static int _Compare(const_pointer __cStr1, const size_type __len1,
    const_pointer __cStr2, const size_type __len2) {
    const size_type __minLength = std::min(__len1, __len2);

    int __res = traits_type::compare(__cStr1, __cStr2, __minLength);

    if (__res == 0) {
      __res = _CompareHelper(__len1, __len2);
    }
    return __res;
  }

  _Alloc_hider _dataPlus{this->_LocalData()};
  size_type _stringLength{0};

  enum { _localCapacity = ((LOCAL_CAPACITY - 1)/ sizeof(value_type)) + 1};

  union {
    value_type _localData[_localCapacity] = {0};
    size_type _allocatedCapacity;
  };
};

//--------------------------------Constructors--------------------------------//
template <typename _CharT, typename _Traits, typename _Alloc>
MyBasicString<_CharT, _Traits, _Alloc>::
_CXX20_CONSTEXPR
MyBasicString() noexcept(std::is_nothrow_default_constructible_v<_Alloc>)
    : _dataPlus(this->_LocalData()) {
  this->_SetLength(0);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const _Alloc& __alloc) noexcept
    : _dataPlus(this->_LocalData(), __alloc) {
  this->_SetLength(0);
}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const size_type __count, value_type __ch, const _Alloc& __alloc)
    : _dataPlus(this->_LocalData(), __alloc) {
  this->_Construct(__count, __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(value_type __ch, const _Alloc& __alloc)
    : MyBasicString(size_type(1), __ch, __alloc) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const std::basic_string<value_type>& __other, size_type __pos,
              const _Alloc& __alloc)
    : MyBasicString(__other, __pos, npos, __alloc) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const MyBasicString& __other, size_type __pos,
              const _Alloc& __alloc)
    : MyBasicString(__other, __pos, npos, __alloc) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const std::basic_string<value_type>& __other, size_type __pos,
              size_type __count, const _Alloc& __alloc)
    : _dataPlus(this->_LocalData(), __alloc) {

  const_pointer __start = __other.data() +
  this->_Check(__other, __pos, "MyBasicString::MyBasicString");
  this->_Construct(__start, __start + this->_Limit(__other, __pos, __count),
    std::forward_iterator_tag());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const MyBasicString& __other, size_type __pos, size_type __count,
              const _Alloc& __alloc)
    : _dataPlus(this->_LocalData(), __alloc) {

  const_pointer __start = __other._Data() +
    __other._Check(__pos, "MyBasicString::MyBasicString");
  this->_Construct(__start, __start + __other._Limit(__pos, __count),
    std::forward_iterator_tag());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const_pointer __cStr, size_type __count, const _Alloc& __alloc)
    : _dataPlus(this->_LocalData(), __alloc) {

  if (__cStr == nullptr && __count > 0) {
    __ThrowMyExceptionFmt<MyLogicError>(
      "MyBasicString: construction from nullptr is not valid");
  }
  this->_Construct(__cStr,
    __cStr +  std::min(__count, traits_type::length(__cStr)),
    std::forward_iterator_tag());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const_pointer __cStr, const _Alloc& __alloc)
  : MyBasicString(__cStr, traits_type::length(__cStr), __alloc) {}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename _InputIter, typename>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(_InputIter __first, _InputIter __last, const _Alloc& __alloc)
    : _dataPlus(this->_LocalData(), __alloc) {
  this->_Construct(__first, __last,
    std::iterator_traits<_InputIter>::iterator_category());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const std::basic_string<value_type>& __other)
    : MyBasicString(__other, size_type(0), __other.size()) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const MyBasicString& __other)
    : MyBasicString(__other, size_type(0), __other.size()) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const std::basic_string<value_type>& __other,
              const _Alloc& __alloc)
    : MyBasicString(__other, size_type(0), __other.size(), __alloc) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(const MyBasicString& __other, const _Alloc& __alloc)
    : MyBasicString(__other, size_type(0), __other.size(), __alloc) {}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(MyBasicString&& __other) noexcept
    : MyBasicString(this->_LocalData(), std::move(__other._GetAllocator())) {

  if (__other._IsLocal()) {
    traits_type::copy(_localData, __other._localData, __other.length() + 1);
  } else {
    this->_Data(__other._Data());
    this->_Capacity(__other._allocatedCapacity);
  }

  this->_Length(__other.length());
  __other._Data(__other._LocalData());
  __other._SetLength(0);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(MyBasicString&& __other, const _Alloc& __alloc)
noexcept(_AllocatorTraits::is_always_equal)
    : _dataPlus(this->_LocalData(), __alloc) {

  if (__other._IsLocal()) {
    traits_type::copy(_localData, __other._localData, __other.length() + 1);
    this->_Length(__other.length());
    __other._SetLength(0);
  } else if (_AllocatorTraits::is_always_equal() ||
    __alloc == __other._GetAllocator()) {
    this->_Data(__other._Data());
    this->_Length(__other.length());
    this->_Capacity(__other._allocatedCapacity);
    __other._Data(__other._LocalData());
    __other._SetLength(0);
  } else {
    this->_Construct(__other.begin(), __other.end(),
      std::forward_iterator_tag());
  }
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>::
MyBasicString(std::initializer_list<value_type> __ilist, const _Alloc& __alloc)
    : _dataPlus(this->_LocalData(), __alloc) {
  this->_Construct(__ilist.begin(), __ilist.end(), std::forward_iterator_tag());
}

//---------------------------------Destructor---------------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
MyBasicString<_CharT, _Traits, _Alloc>::
~MyBasicString() noexcept {
  this->_Dispose();
}

//----------------------------Assignment operator-----------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator=(const MyBasicString& __other) {
  return *this->assign(__other);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator=(const std::basic_string<value_type>& __other) {
  return *this->assign(__other);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator=(MyBasicString&& __other)
noexcept(_AllocatorTraits::propagate_on_container_move_assignment::value
         || _AllocatorTraits::is_always_equal::value) {
  if (!this->_IsLocal()
      && !_AllocatorTraits::propagate_on_container_move_assignment::value
      && !_AllocatorTraits::is_always_equal::value
      && this->_GetAllocator() != __other._GetAllocator()) {
    this->_Destroy(_allocatedCapacity);
    this->_Data(_LocalData());
    this->_Length(0);
  }

  // move allocator if propagate_on_container_move_assignment::value = true
  __custom_traits::_alloc_on_move(this->_GetAllocator(),
    __other._GetAllocator());

  if (__other._IsLocal()) {
    if (this == std::addressof(__other)) { return *this; }
    if (__other.length()) {
      this->_Copy(this->_Data(), __other._Data(), __other.length());
      this->_SetLength(__other.length());
    }
  } else if (_AllocatorTraits::propagate_on_container_move_assignment::value 
           || _AllocatorTraits::is_always_equal::value
           || this->_GetAllocator() == __other._GetAllocator()) {
    pointer __data = nullptr;
    size_type __capacity;
    if (!this->_IsLocal()) {
      // Can be freed by __other
      if (_AllocatorTraits::is_always_equal::value) {
        __data = this->_Data();
        __capacity = _allocatedCapacity;
      } else {
        this->_Destroy(_allocatedCapacity);
      }
    }
    this->_Data(__other._Data());
    this->_Length(__other.length());
    this->_Capacity(__other._allocatedCapacity);
    if (__data) {
      __other._Data(__data);
      __other._Capacity(__capacity);
    } else {
      __other._Data(__other._LocalData());
    }
  } else {
    this->assign(__other);
  }
  __other.clear();
  return *this;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator=(const_pointer __cStr) {
  return this->assign(__cStr);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator=(value_type __ch) {
  return this->assign(size_type(1), __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator=(std::initializer_list<value_type> __ilist) {
  return this->assign(__ilist.begin(), __ilist.end());
}

//-----------------------------------Assign-----------------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(size_type __count, value_type __ch) {
  return _ReplaceAux(size_type(0), this->length(), __count, __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(const MyBasicString& __other) {
  if (_AllocatorTraits::propagate_on_container_copy_assignment::value) {
    if (!_AllocatorTraits::is_always_equal::value && !this->_IsLocal()
      && this->_GetAllocator() != __other._GetAllocator()) {

      if (__other.length() < _localCapacity) {
        this->_Destroy(_allocatedCapacity);
        this->_Data(this->_LocalData());
        this->_SetLength(0);
      } else {
        const size_type __len = __other.length();
        pointer __another = _AllocatorTraits::allocate(__other._GetAllocator(),
          __len + 1);
        this->_Destroy(_allocatedCapacity);
        this->_Data(__another);
        this->_Capacity(__len + 1);
        this->_SetLength(__len);
      }
    }
  __custom_traits::_alloc_on_copy(this->_GetAllocator(),
    __other._GetAllocator());
  }
  this->_Assign(__other);
  return *this;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(const std::basic_string<value_type>& __other) {
  return this->_Replace(size_type(0), __other.length(), __other.data(), 
    _Limit(__other, size_type(0), npos));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(const MyBasicString& __other, size_type __pos, size_type __count) {
  return this->_Replace(size_type(0), __other.length(), __other._Data() +  
    this->_Check(__pos, "MyBasicString::assign"), this->_Limit(__pos, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(const std::basic_string<value_type>& __other,
                      size_type __pos, size_type __count) {
  return this->_Replace(size_type(0), __other.length(), __other.data() +  
    this->_Check(__other, __pos, "MyBasicString::assign"),
    this->_Limit(__other, __pos, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(MyBasicString&& __other) noexcept(
  _AllocatorTraits::propagate_on_container_move_assignment::value
  || _AllocatorTraits::is_always_equal::value) {
  return *this = std::move(__other);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(const_pointer __cStr, size_type __count) {
  return this->_Replace(size_type(0), this->length(), __cStr, __count);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(const_pointer __cStr) {
  return this->_Replace(size_type(0), this->length(), __cStr,
    traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename _InputIter, typename>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(_InputIter __first, _InputIter __last) {
  return this->replace(this->begin(), this->end(), __first, __last);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
assign(std::initializer_list<value_type> __ilist) {
  return this->assign(__ilist.begin(), __ilist.size());
}

//---------------------------------Allocator----------------------------------//
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::allocator_type
MyBasicString<_CharT, _Traits, _Alloc>::
get_allocator() const noexcept {
  return _GetAllocator();
}

//-------------------------------Element access-------------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::reference
MyBasicString<_CharT, _Traits, _Alloc>::
at(size_type __pos) {
  return this->_Data() + this->_Check(__pos, "MyBasicString::at");
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reference
MyBasicString<_CharT, _Traits, _Alloc>::
at(size_type __pos) const {
  return this->_Data() + this->_Check(__pos, "MyBasicString::at");
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::reference
MyBasicString<_CharT, _Traits, _Alloc>::
operator[](size_type __pos) noexcept {
  return this->_Data()[__pos];
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reference 
MyBasicString<_CharT, _Traits, _Alloc>::
operator[](size_type __pos) const noexcept {
  return this->_Data()[__pos];
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::reference
MyBasicString<_CharT, _Traits, _Alloc>::
front() noexcept {
  return this->_Data[0];
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reference
MyBasicString<_CharT, _Traits, _Alloc>::
front() const noexcept {
  return this->_Data[0];
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::reference
MyBasicString<_CharT, _Traits, _Alloc>::back() noexcept {
  return this->_Data()[this->length() - 1];
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reference
MyBasicString<_CharT, _Traits, _Alloc>::
back() const noexcept {
  return this->_Data()[this->length() - 1];
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::pointer
MyBasicString<_CharT, _Traits, _Alloc>::
data() noexcept {
  return _Data();
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_pointer
MyBasicString<_CharT, _Traits, _Alloc>::
data() const noexcept {
  return _Data();
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::pointer
MyBasicString<_CharT, _Traits, _Alloc>::
c_str() noexcept {
  return _Data();
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_pointer
MyBasicString<_CharT, _Traits, _Alloc>::
c_str() const noexcept {
  return _Data();
}

//---------------------------------Iterators----------------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
begin() noexcept { return iterator(this->_Data()); }
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
begin() const noexcept { return this->cbegin(); }
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
cbegin() const noexcept { return const_iterator(this->_Data()); }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
end() noexcept {
  return iterator(this->_Data() + this->length());
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
end() const noexcept { return this->cend(); }
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
cend() const noexcept {
  return cosnt_iterator(this->_Data() + this->length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::reverse_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
rbegin() noexcept { return reverse_iterator(this->end()); }
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reverse_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
rbegin() const noexcept { this->crbegin(); }
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reverse_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
crbegin() const noexcept {
  return const_reverse_iterator(this->cend());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::reverse_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
rend() noexcept {
  return reverse_iterator(this->begin());
}
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reverse_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
rend() const noexcept { return this->crend(); }
template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::const_reverse_iterator
MyBasicString<_CharT, _Traits, _Alloc>::
crend() const noexcept {
  return const_reverse_iterator(this->cbegin());
}

//----------------------------------Capacity----------------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
[[nodiscard]]
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
empty() const noexcept { return this->length() == size_type(0); }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::size_type
MyBasicString<_CharT, _Traits, _Alloc>::
size() const noexcept { return _stringLength; }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::size_type
MyBasicString<_CharT, _Traits, _Alloc>::
length() const noexcept { return _stringLength; }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::size_type
MyBasicString<_CharT, _Traits, _Alloc>::
max_size() const noexcept { 
  return (_AllocatorTraits::max_size(this->_GetAllocator()) - 1) / 2;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
reserve(size_type __newCap) {
  size_type __capacity = this->capacity();

  // Reallocation is not required
  if (__newCap <= __capacity) { return; }

  pointer __another = _Create(__newCap, __capacity);
  this->_Copy(__another, _Data(), this->length() + 1);
  _Dispose();
  _Data(__another);
  _Capacity(__newCap);
  _SetLength(this->length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
#if __cplusplus > 201703L
[[deprecated]]
#endif
void
MyBasicString<_CharT, _Traits, _Alloc>::
reserve() { shrink_to_fit(); }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::size_type
MyBasicString<_CharT, _Traits, _Alloc>::
capacity() const noexcept {
  return this->_IsLocal() ? _localCapacity : _allocatedCapacity;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
shrink_to_fit() {
  if (_IsLocal()) { return; }

  const size_type __length = this->length();
  const size_type __capacity = _allocatedCapacity;

  if (__length < size_type(_localCapacity)) {
    this->_Copy(_LocalData(), _Data(), __length + 1);
    _Destroy(__capacity);
    _Data(_LocalData());
  } else if (__length < __capacity - 1) {
    pointer __another =
      _AllocatorTraits::allocate(this->_GetAllocator(), __length + 1);
    this->_Copy(__another, _Data(), __length + 1);
    _Dispose();
    _Data(__another);
    _Capacity(__length + 1);
  }
}

//---------------------------------Operations---------------------------------//

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
clear() noexcept { this->_SetLength(0); }


template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, size_type __count, value_type __ch) {
  return this->_ReplaceAux(_Check(__idx, "MyBasicString::insert"), size_type(0),
    __count, __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, value_type __ch) {
  return this->insert(__idx, size_type(1), __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, const_pointer __cStr) {
  return this->replace(__idx, size_type(0), __cStr,
    traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, const_pointer __cStr, size_type __count) {
  return this->replace(__idx, size_type(0), __cStr, __count);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, const std::basic_string<value_type>& __other) {
  return this->replace(__idx, size_type(0), __other.data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, const MyBasicString& __other) {
  return this->replace(__idx, size_type(0), __other.data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, const std::basic_string<value_type>& __other,
       size_type __idxStr, size_type __count) {
  return this->replace(__idx, size_type(0), __other.data() + 
    this->_Check(__other,__idxStr, "MyBasicString::insert"),
    this->_Limit(__other, __idxStr, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
insert(size_type __idx, const MyBasicString& __other, size_type __idxStr,
       size_type __count) {
  return this->replace(__idx, size_type(0), __other._Data() + 
    this->_Check(__idxStr, "MyBasicString::insert"),
    this->_Limit(__idxStr, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
insert(const_iterator __pos, value_type __ch) {
  return this->insert(__pos, size_type(1), __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
insert(const_iterator __pos, size_type __count, value_type __ch) {
  const size_type __position = __pos - this->begin();
  this->replace(__pos, __pos, __count, __ch);
  return iterator(this->_Data() + __position);
}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename _InputIter, typename>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
insert(const_iterator __pos, _InputIter __beg, _InputIter __end) {
  const size_type __position = __pos - this->begin();
  this->replace(__pos, __pos, __beg, __end);
  return iterator(this->_Data() + __position);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
insert(const_iterator __pos, std::initializer_list<value_type> __ilist) {
  return this->insert(__pos, __ilist.begin(), __ilist.end());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
erase(size_type __idx, size_type __count) {
  this->_Check(__idx, "MyBasicString::erase");
  if (__count == npos) {
    this->_SetLength(__idx);
  } else if (__count != 0) {
    this->_Erase(__idx, __count);
  }
  return *this;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
erase(const_iterator __pos) {
  size_type __position = __pos - this->begin();
  this->_Erase(__position, size_type(1));
  return iterator(this->_Data() + __position);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::iterator
MyBasicString<_CharT, _Traits, _Alloc>::
erase(const_iterator __beg, const_iterator __end) {
  const size_type __position = __beg - this->begin();
  if (__end == this->end()) {
    this->_SetLength(__position);
  } else {
    this->_Erase(__position, __end - __beg);
  }
  return iterator(this->_Data() + __position);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
push_back(value_type __ch) { this->append(size_type(1), __ch); }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
pop_back() { this->_SetLength(this->length() - 1);}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(size_type __count, value_type __ch) {
  return this->_ReplaceAux(size_type(0), this->length(), __count, __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(const MyBasicString& __other) {
  return this->append(__other._Data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(const std::basic_string<value_type>& __other) {
  return this->append(__other.data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(const MyBasicString& __other, size_type __pos, size_type __count) {
  return this->append(__other._Data() +
    __other._Check(__pos, "MyBasicString::append"),
    __other._Limit(__pos, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(const std::basic_string<value_type>& __other, size_type __pos,
       size_type __count) {
  return this->append(__other.data() +
    this->_Check(__other, __pos, "MyBasicString::append"),
    this->_Limit(__other, __pos, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(const_pointer __cStr, size_type __count) {
  this->_CheckLength(size_type(0), __count, "MyBasicString::append");
  return this->_Append(__cStr, __count);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(const_pointer __cStr) {
  this->_CheckLength(size_type(0), traits_type::length(__cStr),
    "MyBasicString::append");
  return this->_Append(__cStr, traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename _InputIter, typename>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(_InputIter __beg, _InputIter __end) {
  return this->replace(this->end(), this->end(), __beg, __end);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
append(std::initializer_list<value_type> __ilist) {
  return this->append(__ilist.begin(), __ilist.end());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator+=(const MyBasicString& __other) {
  return this->append(__other._Data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator+=(const std::basic_string<value_type>& __other) {
  return this->append(__other.data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator+=(value_type __ch) {
  return this->append(size_type(1), __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator+=(const_pointer __cStr) {
  return this->append(__cStr, traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
operator+=(std::initializer_list<value_type> __ilist) {
  return this->append(__ilist.begin(), __ilist.end());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(const MyBasicString& __other) const noexcept {
  return this->_Compare(this->_Data(), this->length(), __other._Data(),
    __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(const std::basic_string<value_type> __other) const noexcept {
  return this->_Compare(this->_Data(), this->length(), __other.data(),
    __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(size_type __pos1, size_type __count1, const MyBasicString& __other)
const {
  return this->compare(__pos1, __count1, __other, __other.length(), npos);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(size_type __pos1, size_type __count1,
        const std::basic_string<value_type>& __other) const {
  return this->compare(__pos1, __count1, __other, __other.length(), npos);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(size_type __pos1, size_type __count1, const MyBasicString& __other,
        size_type __pos2, size_type __count2) const {
  return this->_Compare(
    this->_Data() + this->_Check(__pos1, "MyBasicString::compare"),
    _Limit(__pos1, __count1), __other._Data() +
    __other._Check(__pos2, "MyBasicString::compare"),
    __other._Limit(__pos2, __count2));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(size_type __pos1, size_type __count1,
         const std::basic_string<value_type>& __other, size_type __pos2,
         size_type __count2) const {
  return this->_Compare(
    this->_Data() + this->_Check(__pos1, "MyBasicString::compare"),
    this->_Limit(__pos1, __count1), __other.data() +
    this->_Check(__other, __pos2, "MyBasicString::compare"),
    this->_Limit(__other, __pos2, __count2));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(const_pointer __cStr) const {
  return this->_Compare(this->_Data(), this->length(), __cStr,
    traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(size_type __pos1, size_type __count1, const_pointer __cStr) const {
  return this->_Compare(
    this->_Data() + this->_Check(__pos1, "MyBasicString::compare"),
    this->_Limit(__pos1, __count1), __cStr, traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
int32_t
MyBasicString<_CharT, _Traits, _Alloc>::
compare(size_type __pos1, size_type __count1, const_pointer __cStr,
                size_type __count2) const {
  return this->_Compare(
    this->_Data() + this->_Check(__pos1, "MyBasicString::compare"),
    this->_Limit(__pos1, __count1), __cStr, __count2);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
starts_with(value_type __ch) const noexcept {
  return !this->empty() && traits_type(this->front() == __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
starts_with(const_pointer __cStr) const {
  return this->_Compare(this->_Data(), this->length(), __cStr,
    traits_type::length(__cStr)) == 0;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
ends_with(value_type __ch) const noexcept {
  return !this->empty() && traits_type(this->back() == __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
ends_with(const_pointer __cStr)const {
  if (this->length() < traits_type::length(__cStr)) { return false; }
  const size_type __length = traits_type::length(__cStr);
  const size_type __offset = this->length() - __length;
  return this->_Compare(this->_Data() + __offset,
    traits_type::length(this->_Data() + __offset), __cStr, __length) == 0;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
contains(value_type __ch) const noexcept {
  return this-> find(__ch) != npos;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
bool
MyBasicString<_CharT, _Traits, _Alloc>::
contains(const_pointer __cStr) const {
  return this->find(__cStr) != npos;
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos, size_type __count, const MyBasicString& __other) {
  return this->_Replace(this->_Check(__pos, "MyBasicString::replace"),
    this->_Limit(__pos, __count), __other._Data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos, size_type __count,
        const std::basic_string<value_type>& __other) {
  return this->_Replace(this->_Check(__pos, "MyBasicString::replace"),
    this->_Limit(__pos, __count), __other.data(), __other.length());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg, const_iterator __end,
        const MyBasicString& __other) {
  return this->replace(__beg, __end, __other.cbegin(), __other.cend());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg, const_iterator __end,
        const std::basic_string<value_type>& __other) {
  return this->replace(__beg, __end, __other.cbegin(), __other.cend());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos1, size_type __count1, const MyBasicString& __other,
        size_type __pos2, size_type __count2) {
  return this->_Replace(this->_Check(__pos1, "MyBasicString::replace"),
    this->_Limit(__pos1, __count1),
    __other._Data() + __other._Check(__pos2, "MyBasicString::replace"),
    __other._Limit(__pos2, __count2));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos1, size_type __count1,
        const std::basic_string<value_type>& __other, size_type __pos2,
        size_type __count2) {
  return this->_Replace(this->_Check(__pos1, "MyBasicString::replace"),
    this->_Limit(__pos1, __count1, "MyBasicString::replace"),
    __other.data() + this->_Check(__other, __pos2, "MyBasicString::replace"),
    this->_Limit(__other, __pos2, __count2));
}

template <typename _CharT, typename _Traits, typename _Alloc>
template <typename _InputIter, typename>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg1, const_iterator __end1, _InputIter __beg2,
        _InputIter __end2) {
  return this->_Replace(__beg1, __end1, __beg2, __end2);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos, size_type __count1, const_pointer __cStr,
        size_type __count2) {
  this->_Check(__pos, "MyBasicString::replace");
  return this->_Replace(__pos, __count1, __cStr, __count2);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg, const_iterator __end, const_pointer __cStr,
    size_type __count) {
  return this->replace(__beg - this->cbegin(), __end - __beg, __cStr, __count);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos, size_type __count, const_pointer __cStr) {
  this->_Check(__pos, "MyBasicString::replace");
  return this->_Replace(__pos, __count, __cStr, traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg, const_iterator __end, const_pointer __cStr) {
  return this->replace(__beg, __end, __cStr, traits_type::length(__cStr));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(size_type __pos, size_type __count1, size_type __count2,
    value_type __ch) {
  this->_Check(__pos, "MyBasicString::replace");
  return this->_ReplaceAux(__pos, __count1, __count2, __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg, const_iterator __end, size_type __count,
    value_type __ch) {
  return this->_ReplaceAux(__beg - this->cbegin(), __end - __beg, __count,
      __ch);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>&
MyBasicString<_CharT, _Traits, _Alloc>::
replace(const_iterator __beg, const_iterator __end,
        std::initializer_list<value_type> __ilist) {
  return this->replace(__beg, __end, __ilist.begin(), __ilist.end());
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
MyBasicString<_CharT, _Traits, _Alloc>
MyBasicString<_CharT, _Traits, _Alloc>::
substr(size_type __pos, size_type __count) const {
  return MyBasicString(*this, this->_Check(__pos, "MyBasicString::substr"),
    __count);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::size_type
MyBasicString<_CharT, _Traits, _Alloc>::
copy(pointer __dest, size_type __count, size_type __pos) const {
  this->_Copy(__dest, this->_Data() + _Check(__pos, "MyBasicString::copy"),
    this->_Limit(__pos, __count));
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
resize(size_type __count) { this->resize(__count, value_type()); }

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
resize(size_type __count, value_type __ch) {
  const size_type __length = this->length();
  if (__length < __count) {
    this->append(__length - __count, __ch);
  } else if (__length > __count) {
    this->_SetLength(__count);
  }
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
void
MyBasicString<_CharT, _Traits, _Alloc>::
swap(MyBasicString& __other) noexcept(
  _AllocatorTraits::propagate_on_container_swap::value
 || _AllocatorTraits::is_always_equal::value) {

  if (this == std::addressof(__other)) { return; }

  // Potentially can throw exception
  __custom_traits::_alloc_on_swap(this->_GetAllocator(),
    __other._GetAllocator());

  if (this->_IsLocal()) {
    if (__other._IsLocal()) {
      if (this->length() && __other.length()) {
        value_type __tmpStr[_localCapacity] = {0};
        traits_type::copy(__tmpStr, __other._Data(), __other.length() + 1);
        traits_type::copy(__other._localData, this->_Data(), this->length() + 1);
        traits_type::copy(_localData, __tmpStr, __other.length() + 1);
      } else if (__other.length()) {
        traits_type::copy(_localData, __other._Data(), __other.length());
        _Length(__other.length());
        __other._SetLength(0);
        return;
      } else if (this->length()) {
        traits_type::copy(__other._localData, this->_Data(), this->length());
        __other._Length(this->length());
        this->_SetLength(0);
        return;
      }
    } else {
      //   __other._Data() has been allocated by allocator
      const size_type __tmpCap = __other.capacity();
      traits_type::copy(__other._localData,this->_LocalData(),
        this->length() + 1);
      this->_Data(__other._Data());
      __other._Data(__other._LocalData());
      this->_Capacity(__tmpCap);
    }
  } else {
    // this->_Data() has been allocated by allocator
    const size_type __tmpCap = this->capacity();
    if (__other._IsLocal()) {
      traits_type::copy(_localData, __other._LocalData(), __other.length() + 1);
      __other._Data(this->_Data());
      this->_Data(this->_LocalData());
    } else {
      pointer __tmpStr = this->_Data();
      this->_Data(__other._Data());
      __other._Data(__tmpStr);
      this->_Capacity(__other.capacity());
    }
    __other._Capacity(__tmpCap);
  }
  const size_type __tmpLen = this->length();
  _Length(__other.length());
  __other._Length(__tmpLen);
}

template <typename _CharT, typename _Traits, typename _Alloc>
_CXX20_CONSTEXPR
typename MyBasicString<_CharT, _Traits, _Alloc>::size_type
MyBasicString<_CharT, _Traits, _Alloc>::
find(const MyBasicString& __other, size_type __pos) const noexcept {
  std::vector<MyBasicString<_CharT, _Traits, _Alloc>> __vs;
  __vs.push_back(__other.data());
  MyTypes::PatternSearcher<MyBasicString> __search(__vs);
  auto __res = __search(*this);
  std::cout << __res.size() << std::endl;
  for (auto& __el : __res) {
    if (__el.second > __pos) { return __el.second; }
  }
  return npos;
}

namespace PMR {

template <typename _CharT, typename _Traits = std::char_traits<_CharT>>
using MyBasicString = MyTypes::MyBasicString<
                        _CharT, _Traits,
                        std::pmr::polymorphic_allocator<_CharT> >;

using MyString = MyBasicString<char>;
using MyWideString = MyBasicString<wchar_t>;
using MyU16String = MyBasicString<char16_t>;
using MyU32String = MyBasicString<char32_t>;

} // namespace PMR

using MyString = MyBasicString<char>;
using MyWideString = MyBasicString<wchar_t>;
using MyU16String = MyBasicString<char16_t>;
using MyU32String = MyBasicString<char32_t>;


} // namespace MyTypes

template <typename _CharT, typename _Traits, typename _Alloc>
std::basic_ostream<_CharT, _Traits>& operator<<(
    std::basic_ostream<_CharT, _Traits>& out,
    const MyTypes::MyBasicString<_CharT, _Traits, _Alloc>& str) noexcept {
  out << str.data();
  return out;
}

#endif //_MY_STRING_H
