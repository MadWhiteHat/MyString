#ifndef _MY_STRING_H
#define _MY_STRING_H

#include <iostream>
#include <string>

#include "my_type_traits.h"

// Variables: lowerCamelCase
// Custom types: UpperCamelCsse
// New names/aliases to builtin types: snake_case
// Custom functions: UpperCamelCase

namespace MyTypes {

template <typename CharT>
class MyBasicString {

  static_assert(string_valid_type_v<CharT>);

 public:
  typedef CharT value_type;
  typedef size_t size_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;

  static constexpr size_type npos = static_cast<size_type>(-1);

  // 1. Constructs empty string
  MyBasicString() noexcept;
  
  // 2. Constructs the string explicitly from char.
  explicit MyBasicString(value_type ch) noexcept;

  // 3. Constructs the string with count copies of character ch.
  MyBasicString(const size_type count, value_type ch) noexcept;

  // 4. Constructs the string with substring [pos, pos+count) of
  // other. If count == npos, if count is not specified, or if the
  // requested substring lasts past the end of the string, the
  // resulting substring is [pos, other.size()).
  // Strong exception guarantee: if pos > other.size()
  MyBasicString(const std::basic_string<CharT>& other, size_type pos,
                size_type count) noexcept;
  MyBasicString(const MyBasicString<CharT>& other, size_type pos,
                size_type count) noexcept;

  MyBasicString(const std::basic_string<CharT>& other, size_type pos) noexcept;
  MyBasicString(const MyBasicString<CharT>& other, size_type pos) noexcept;

  // 5. Construct the sting with the first count characters of character string
  // pointed by str. str can contain null characters.
  // Range validation: [str, str + min(count, len(str)).
  MyBasicString(const_pointer str, size_type count) noexcept;

  // 6. Constructs a string with the content initialized with a copy
  // of the null-terminated characted string pointed by str. The
  // length of the string is determined by the first null character.
  // Range validation: if str == nullptr, object won't be changed.
  MyBasicString(const_pointer str) noexcept;

  // 7. Copy constructor. Constructs the string with a copy of the
  // content of other.
  MyBasicString(const std::basic_string<CharT>& other) noexcept;
  MyBasicString(const MyBasicString<CharT>& other) noexcept;

  // 8. Move constructor. Constructs the string with the contents of
  // other using move semantics. After moving other state is
  // other == MyBasicString()
  MyBasicString(MyBasicString<CharT>&& other) noexcept;

  // 9. Constructs the string with the content of the initializer list
  MyBasicString(std::initializer_list<CharT> lst) noexcept;

  // Last(10). Cannot be constructed from nullptr
  MyBasicString(nullptr_t) = delete;

//----------------------------Assignment operators----------------------------//

  // 1. Deep copy of str content
  MyBasicString<CharT>& operator=(const MyBasicString<CharT>& str) noexcept;
  
  // 2. Behave like default copy operator
  // Affter operation str == MyBasicString() is true
  MyBasicString<CharT>& operator=(MyBasicString<CharT>&& str) noexcept;

  // 3. Deep copy of str.c_str()
  MyBasicString<CharT>& operator=(const std::basic_string<CharT>& str) noexcept;
  MyBasicString<CharT>& operator=(std::basic_string<CharT>&& str) noexcept;
  
  // 4. Deep copy of str
  MyBasicString<CharT>& operator=(const_pointer str) noexcept;
  
  // 5. Deep copy of CharT array {ch, '\0'}
  MyBasicString<CharT>& operator=(value_type ch) noexcept;

//---------------------------------Destructor---------------------------------//
  
  // Destructs object by deallocating memory (explcitly declared as noexcept)
  ~MyBasicString() noexcept;

//-------------------------------Element access-------------------------------//

  reference at(size_type pos);
  const_reference at(size_type pos) const;

  reference operator[](size_type pos) noexcept;
  const_reference operator[](size_type pos) const noexcept;

  reference front() noexcept;
  const_reference front() const noexcept;

  reference back() noexcept;
  const_reference back() const noexcept;

  const_pointer data() const noexcept;
  const_pointer c_str() const noexcept;

//----------------------------------Capacity----------------------------------//

  bool empty() const noexcept;

  size_type size() const noexcept;
  size_type length() const noexcept;

  void reserve(size_type new_cap) noexcept;
  void reserve() noexcept;

  size_type capacity() const noexcept;

  void shrink_to_fit() noexcept;

//---------------------------------Operations---------------------------------//

  void clear() noexcept;

  MyBasicString<CharT>& insert(size_type index, size_type count,
                               value_type ch) noexcept;
  MyBasicString<CharT>& insert(size_type index, const_pointer str) noexcept;
  MyBasicString<CharT>& insert(size_type index, const_pointer str,
                               size_type count) noexcept;
  MyBasicString<CharT>& insert(size_type index, 
                               const std::basic_string<CharT>& str) noexcept;
  MyBasicString<CharT>& insert(size_type index,
                               const std::basic_string<CharT>& str,
                               size_type index_str,
                               size_type count = npos) noexcept;
  MyBasicString<CharT>& insert(size_type index, 
                               const MyBasicString<CharT>& str) noexcept;
  MyBasicString<CharT>& insert(size_type index,
                               const MyBasicString<CharT>& str,
                               size_type index_str,
                               size_type count = npos) noexcept;

  void erase(size_type index = 0, size_type count = npos) noexcept;

  void push_back(value_type ch) noexcept;

  void pop_back() noexcept;

  MyBasicString<CharT>& append(size_type count, value_type ch) noexcept;
  MyBasicString<CharT>& append(const std::basic_string<CharT>& str) noexcept;
  MyBasicString<CharT>& append(const MyBasicString<CharT>& str) noexcept;
  MyBasicString<CharT>& append(const std::basic_string<CharT>& str,
                               size_type pos,
                               size_type count = npos) noexcept;
  MyBasicString<CharT>& append(const MyBasicString<CharT>& str,
                               size_type pos,
                               size_type count = npos) noexcept;
  MyBasicString<CharT>& append(const_pointer str, size_type count) noexcept;
  MyBasicString<CharT>& append(const_pointer str) noexcept;
  MyBasicString<CharT>& append(std::initializer_list<CharT> lst) noexcept;

  MyBasicString<CharT>& operator+=(const MyBasicString<CharT>& str) noexcept;
  MyBasicString<CharT>& operator+=(
      const std::basic_string<CharT>& str) noexcept;
  MyBasicString<CharT>& operator+=(const_pointer str) noexcept;
  MyBasicString<CharT>& operator+=(value_type ch) noexcept;
  MyBasicString<CharT>& operator+=(std::initializer_list<CharT> str) noexcept;

  int compare(const std::basic_string<CharT>& str) const noexcept;
  int compare(const MyBasicString<CharT>& str) const noexcept;
  int compare(size_type pos1, size_type count1,
              std::basic_string<CharT>& str) const noexcept;
  int compare(size_type pos1, size_type count1,
              std::basic_string<CharT>& str,
              size_type pos2, size_type count2 = npos) const noexcept;
  int compare(size_type pos1, size_type count1,
              MyBasicString<CharT>& str,
              size_type pos2, size_type count2 = npos) const noexcept;
  int compare(const_pointer str) const noexcept;
  int compare(size_type pos1, size_type count1,
              const_pointer str) const noexcept;
  int compare(size_type pos1, size_type count1,
              const_pointer str, size_type count2) const noexcept;

  MyBasicString<CharT>& replace(size_type pos, size_type count,
                                const std::basic_string<CharT>& str) noexcept;
  MyBasicString<CharT>& replace(size_type pos, size_type count,
                               const MyBasicString<CharT>& str) noexcept;
  MyBasicString<CharT>& replace(size_type pos1, size_type count1,
                                const std::basic_string<CharT>& str,
                                size_type pos2,
                                size_type count2 = npos) noexcept;
  MyBasicString<CharT>& replace(size_type pos1, size_type count1,
                               const MyBasicString<CharT>& str, size_type pos2,
                               size_type count2 = npos) noexcept;
  MyBasicString<CharT>& replace(size_type pos1, size_type count1,
                                const_pointer cStr, size_type count2) noexcept;
  MyBasicString<CharT>& replace(size_type pos, size_type count,
                                const_pointer cStr) noexcept;
  MyBasicString<CharT>& replace(size_type pos, size_type count,
                                size_type count2, value_type ch) noexcept;

  MyBasicString<CharT> substr(size_type pos = 0,
                              size_type count = npos) const noexcept;

  size_type copy(pointer dest, size_type count,
                 size_type pos = 0) const noexcept;

//---------------------------------Not sorted---------------------------------//
  
  inline void swap(MyBasicString<CharT>& other) noexcept;

 protected:
  inline static size_type Min(size_type num1, size_type num2);

  inline static size_type CapCalc(size_type size);
  inline static size_type LenCalc(size_type len, size_type pos,
                                  size_type count);
  inline static pointer MemAlloc(size_type size);
  static size_type StrLen(const_pointer str);

  // Custom strcpy for template CharT
  static void StrCpy(pointer dst, const_pointer src, size_type count);
  // Custom memset for template CharT
  static void StrSet(pointer dst, value_type value, size_type count);
  static int StrCmp(const_pointer str1, const_pointer str2);

  template <typename T>
  inline static void Swap(T& lhs, T& rhs) noexcept;

  size_type length_;
  size_type capacity_;
  pointer str_;
};


  typedef MyBasicString<char> MyString;
  typedef MyBasicString<wchar_t> MyWideString;
  typedef MyBasicString<char16_t> MyU16String;
  typedef MyBasicString<char32_t> MyU32String;

} // namespace MyTypes

// std::fstream& operator<<(std::fstream&, const MyTypes::MyBasicString&) noexcept;
// std::fstream& operator>>(std::fstream&, MyTypes::MyBasicString&) noexcept;

template <typename CharT>
std::basic_ostream<CharT>& operator<<(
    std::basic_ostream<CharT>& out,
    const MyTypes::MyBasicString<CharT>& str) noexcept;
// std::istream& operator>>(std::istream&, MyTypes::MyBasicString&) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    typename MyTypes::MyBasicString<CharT>::const_pointer rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    typename MyTypes::MyBasicString<CharT>::value_type rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    std::initializer_list<CharT> rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    const std::basic_string<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    std::basic_string<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    typename MyTypes::MyBasicString<CharT>::const_pointer rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    typename MyTypes::MyBasicString<CharT>::value_type rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    std::initializer_list<CharT> rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    const std::basic_string<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>&& lhs,
    std::basic_string<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::const_pointer lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::const_pointer lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::value_type lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::value_type lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::initializer_list<CharT> lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::initializer_list<CharT> lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const std::basic_string<CharT>& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const std::basic_string<CharT>& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::basic_string<CharT>&& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept;

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::basic_string<CharT>&& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept;

#endif //_MY_STRING_H