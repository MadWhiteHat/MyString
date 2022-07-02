// 1. Related headers
//------------------------------------None------------------------------------//

// 2. C system headers
//------------------------------------None------------------------------------//

// 3. C++ standard library headers
// #include <cmath>
#include <iostream>
#include <string>
#include <cassert>

// 4. Other libraries' .h files.
//------------------------------------None------------------------------------//

// 5. Your project's .h files.
#include "my_string.h"

namespace MyTypes {

//------------------------------Constructors----------------------------------//

template <typename CharT>
MyBasicString<CharT>::MyBasicString() noexcept
    : length_(0), capacity_(0),str_(nullptr) {}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    MyBasicString<CharT>::value_type ch) noexcept
    : MyBasicString<CharT>(1, ch) {}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    const size_type count,
    MyBasicString<CharT>::value_type ch) noexcept
    : length_(count),
      capacity_(CapCalc(size())),
      str_(MemAlloc(capacity())) {
  if (c_str()) {
    StrSet(str_, ch, size());
    StrSet(str_ + size(), 0x00, capacity() - size());
  } else { length_ = capacity_ = 0; }
}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    const std::basic_string<CharT>& other,
    MyBasicString<CharT>::size_type pos,
    MyBasicString<CharT>::size_type count) noexcept
    : length_(LenCalc(other.size(), pos, count)),
      capacity_(CapCalc(size())),
      str_(MemAlloc(capacity())) {
  if (c_str()) {
    StrCpy(str_, other.c_str() + pos, size());
    StrSet(str_ + size(), 0x00, capacity() - size());
  } else { length_ = capacity_ = 0; }
}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    const MyBasicString<CharT>& other,
    MyBasicString<CharT>::size_type pos,
    MyBasicString<CharT>::size_type count) noexcept
    : length_(LenCalc(other.size(), pos, count)),
      capacity_(CapCalc(size())),
      str_(MemAlloc(capacity())) {
  if (c_str()) {
    StrCpy(str_, other.c_str() + pos, size());
    StrSet(str_ + size(), 0x00, capacity() - size());
  } else { length_ = capacity_ = 0; }
}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    const std::basic_string<CharT>& other,
    MyBasicString<CharT>::size_type pos) noexcept
    : MyBasicString(other, pos, other.size()) {}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    const MyBasicString<CharT>& other,
    MyBasicString<CharT>::size_type pos) noexcept
    : MyBasicString(other, pos, other.size()) {}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    MyBasicString<CharT>::const_pointer cStr,
    MyBasicString<CharT>::size_type count) noexcept
    : length_(LenCalc(StrLen(cStr), 0, count)),
      capacity_(CapCalc(size())),
      str_(MemAlloc(capacity())) {
    if (c_str()) {
      StrCpy(str_, cStr, size());
      StrSet(str_ + length_, 0x00, capacity() - size());
    } else {length_ = capacity_ = 0;}
}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    const std::basic_string<CharT>& other) noexcept
    : MyBasicString(other, 0, other.size()) {}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(const MyBasicString<CharT>& other) noexcept
    : MyBasicString(other, 0, other.size()) {}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(MyBasicString<CharT>&& other) noexcept
    : length_(other.size()),
      capacity_(other.capacity()),
      str_(other.c_str()) {
  other.str_ = nullptr;
  other.length_ = other.capacity_ = 0;
}

template <typename CharT>
MyBasicString<CharT>::MyBasicString(std::initializer_list<CharT> lst) noexcept
    : length_(lst.size()),
      capacity_(CapCalc(size())),
      str_(MemAlloc(capacity())) {
  if (c_str()) {
    size_type idx = static_cast<size_type>(-1);
    for (auto &el : lst) { str_[++idx] = el; }
  }
}
template <typename CharT>
MyBasicString<CharT>::MyBasicString(
    typename MyBasicString<CharT>::const_pointer cStr) noexcept
    : MyBasicString(cStr, StrLen(cStr)) {}

//----------------------------Assignment operators----------------------------//

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator=(
    const MyBasicString<CharT>& str) noexcept {
  if (capacity() < str.capacity()) {
    MyBasicString<CharT> tmpStr(str);
    swap(tmpStr);
  } else {
    length_ = str.size();
    StrCpy(str_, str.c_str(), size());
    StrSet(str_ + size(), 0x00, capacity() - size());
  }
  return *this;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator=(
    MyBasicString<CharT>&& str) noexcept {
  if (str.c_str() == c_str()) { return *this; }

  // Deallocate existing content before assign
  if (c_str()) { delete[] str_; }
 
  length_ = str.size();
  capacity_ = str.capacity();
 
  str_ = str.str_;
  str.str_ = nullptr;

  return *this;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator=(
    const std::basic_string<CharT>& str) noexcept {
  return *this = MyBasicString(str); 
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator=(
    std::basic_string<CharT>&& str) noexcept {
  return *this = MyBasicString(str); 
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator=(
    typename MyBasicString<CharT>::const_pointer cStr) noexcept {
  return *this = MyBasicString(cStr);
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator=(
    MyBasicString<CharT>::value_type ch) noexcept {
  return *this = MyBasicString(ch);
}

//---------------------------------Destructor---------------------------------//

// Destructs object by deallocating memory
template <typename CharT>
MyBasicString<CharT>::~MyBasicString() noexcept {
  if (c_str()) { delete[] str_; }
}

//-------------------------------Element access-------------------------------//

template <typename CharT>
typename MyBasicString<CharT>::reference MyBasicString<CharT>::at(
    typename MyBasicString<CharT>::size_type pos) { 
  // Out of range
  assert(!(pos >= size())); 
  return str_[pos]; 
}

template <typename CharT>
typename MyBasicString<CharT>::const_reference MyBasicString<CharT>::at(
    typename MyBasicString<CharT>::size_type pos) const { 
  // Out of range
  assert(!(pos >= size())); 
  return str_[pos]; 
}

template <typename CharT>
typename MyBasicString<CharT>::reference MyBasicString<CharT>::operator[](
    const MyBasicString<CharT>::size_type pos) noexcept {
  return str_[pos];
}

template <typename CharT>
typename MyBasicString<CharT>::const_reference MyBasicString<CharT>::operator[](
    const MyBasicString<CharT>::size_type pos) const noexcept {
  return str_[pos];
}

template <typename CharT>
typename MyBasicString<CharT>::reference
MyBasicString<CharT>::front() noexcept {
  // Undefined behaviour if empty() == true
  assert(!empty());
  return operator[](0);
}

template <typename CharT>
typename MyBasicString<CharT>::const_reference
MyBasicString<CharT>::front() const noexcept {
  // Undefined behaviour if empty() == true
  assert(!empty());
  return operator[](0);
}

template <typename CharT>
typename MyBasicString<CharT>::reference MyBasicString<CharT>::back() noexcept {
  // Undefined behaviour if empty() == true
  assert(!empty());
  return operator[](size() - 1);
}

template <typename CharT>
typename MyBasicString<CharT>::const_reference
MyBasicString<CharT>::back() const noexcept {
  // Undefined behaviour if empty() == true
  assert(!empty());
  return operator[](size() - 1);
}

template <typename CharT>
typename MyBasicString<CharT>::const_pointer
MyBasicString<CharT>::data() const noexcept { return str_; }

template <typename CharT>
typename MyBasicString<CharT>::const_pointer
MyBasicString<CharT>::c_str() const noexcept { return str_; }

//----------------------------------Capacity----------------------------------//

template <typename CharT>
bool MyBasicString<CharT>::empty() const noexcept {
  return size() ? false : true;
}

template <typename CharT>
typename MyBasicString<CharT>::size_type
MyBasicString<CharT>::size() const noexcept { return length_; }

template <typename CharT>
void MyBasicString<CharT>::reserve(
    typename MyBasicString<CharT>::size_type newCap) noexcept {
  if (!(newCap > capacity())) { shrink_to_fit(); }
  MyBasicString<CharT> tmpStr(newCap, '\0');
  StrCpy(tmpStr.str_, c_str(), size());
  swap(tmpStr);
}

template <typename CharT>
void MyBasicString<CharT>::reserve() noexcept { shrink_to_fit(); }

template <typename CharT>
typename MyBasicString<CharT>::size_type
MyBasicString<CharT>::capacity() const noexcept { return capacity_; }

template <typename CharT>
void MyBasicString<CharT>::shrink_to_fit() noexcept {
  typename MyBasicString<CharT>::pointer tmpStr = MemAlloc(size() + 1);
  if (!tmpStr) { return; }
  StrCpy(tmpStr, c_str(), size());
  tmpStr[size()] = MyBasicString<CharT>::value_type{0};
  Swap(tmpStr, str_);
  capacity_ = size() + 1;
  delete[] tmpStr;
}

//---------------------------------Operations---------------------------------//

template <typename CharT>
void MyBasicString<CharT>::clear() noexcept { erase(); }

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    typename MyBasicString<CharT>::size_type count,
    typename MyBasicString<CharT>::value_type ch) noexcept {
  // Out of range
  assert(!(index > size()));
  return insert(index, MyBasicString(count, ch).c_str());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    typename MyBasicString<CharT>::const_pointer cStr) noexcept {
  // Out of range
  assert(!(index > size()));
  return insert(index, cStr, StrLen(cStr));
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    typename MyBasicString<CharT>::const_pointer cStr,
    typename MyBasicString<CharT>::size_type count) noexcept {
  // Out of range
  assert(!(index > size()));
  MyBasicString<CharT> tmpStr(c_str(), index);
  tmpStr += MyBasicString(cStr, count);
  tmpStr += c_str() + index;
  
  swap(tmpStr);
  return *this;

}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    const std::basic_string<CharT>& str) noexcept {
  // Out of range
  assert(!(index > size()));
  return insert(index, str.c_str(), str.size());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    const std::basic_string<CharT>& str,
    typename MyBasicString<CharT>::size_type index_str,
    typename MyBasicString<CharT>::size_type count) noexcept {
  // Out of range
  assert(!(index > size() || index_str > str.size()));
  const_pointer tmpStr = str.data() + index;
    index_str > str.size() ? nullptr : str.substr(index_str, count).c_str();
  return insert(index, tmpStr, StrLen(tmpStr));
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    const MyBasicString<CharT>& str) noexcept {
  // Out of range
  assert(!(index > size()));
  return insert(index, str.c_str(), str.size());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::insert(
    typename MyBasicString<CharT>::size_type index,
    const MyBasicString<CharT>& str,
    typename MyBasicString<CharT>::size_type index_str,
    typename MyBasicString<CharT>::size_type count) noexcept {
  // Out of range
  assert(!(index > size() || index_str > str.size()));
  const_pointer tmpStr = str.data() + index;
    index_str > str.size() ? nullptr : str.substr(index_str, count).c_str();
  return insert(index, tmpStr, StrLen(tmpStr));
}

template <typename CharT>
void MyBasicString<CharT>::erase(
    typename MyBasicString<CharT>::size_type index,
    typename MyBasicString<CharT>::size_type count) noexcept {
  // Out of range
  assert(!(index > size()));
  *this = MyBasicString(*this, 0, index) + MyBasicString(*this, index + count);
}

template <typename CharT>
void MyBasicString<CharT>::push_back(
    typename MyBasicString<CharT>::value_type ch) noexcept {
  *this += ch;
}

template <typename CharT>
void MyBasicString<CharT>::pop_back() noexcept {
  // Undefined behaviour if empty() == true
  assert(!empty());
  erase(size() - 1);
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    typename MyBasicString<CharT>::size_type count,
    typename MyBasicString<CharT>::value_type ch) noexcept {
  return *this += MyBasicString(count, ch);
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    const std::basic_string<CharT>& str) noexcept {
  return *this += str;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    const MyBasicString<CharT>& str) noexcept {
  return *this += str;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    const std::basic_string<CharT>& str,
    typename MyBasicString<CharT>::size_type pos,
    typename MyBasicString<CharT>::size_type count) noexcept {
  return *this += MyBasicString(str, pos, count);
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    const MyBasicString<CharT>& str,
    typename MyBasicString<CharT>::size_type pos,
    typename MyBasicString<CharT>::size_type count) noexcept {
  return *this += MyBasicString(str, pos, count);
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    typename MyBasicString<CharT>::const_pointer cStr,
    typename MyBasicString<CharT>::size_type count) noexcept {
  return *this += MyBasicString(cStr, count);
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    typename MyBasicString<CharT>::const_pointer cStr) noexcept {
  return *this += cStr;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::append(
    std::initializer_list<CharT> lst) noexcept {
  return *this += lst;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator+=(
    const MyBasicString<CharT>& str) noexcept {
  return *this += str.c_str();
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator+=(
    const std::basic_string<CharT>& str) noexcept {
  return *this += str.c_str();
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator+=(
    typename MyBasicString<CharT>::const_pointer cStr) noexcept {
  if (!cStr) { return *this; }
  if (size() + StrLen(cStr) < capacity()) {
    StrCpy(str_ + size(), cStr, StrLen(cStr));
    length_ += StrLen(cStr);
  } else {
    size_type tmpLen = size() + StrLen(cStr);
    size_type tmpCap = CapCalc(tmpLen);
    pointer tmoStr = MemAlloc(tmpCap);
    if (tmoStr) {
      StrCpy(tmoStr, c_str(), size());
      StrCpy(tmoStr + size(), cStr, StrLen(cStr));
      StrSet(tmoStr + tmpLen, 0x00, tmpCap - tmpLen);
      length_ = tmpLen;
      capacity_ = tmpCap;
      delete[] str_;
      str_ = tmoStr;
    }
  }
  return *this;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator+=(
    typename MyBasicString<CharT>::value_type ch) noexcept {
  CharT buff[2] = {ch, '\0'};
  return *this += buff;
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::operator+=(
    std::initializer_list<CharT> lst) noexcept {
  return *this += MyBasicString(lst).c_str();
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    const std::basic_string<CharT>& str) const noexcept {
  return compare(0, size(), str.c_str(), str.size());
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    const MyBasicString<CharT>& str) const noexcept {
  return compare(0, size(), str.c_str(), str.size());
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    std::basic_string<CharT>& str) const noexcept {
  return compare(pos1, count1, str.c_str(), str.size());
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    std::basic_string<CharT>& str,
    typename MyBasicString<CharT>::size_type pos2,
    typename MyBasicString<CharT>::size_type count2) const noexcept {
  return compare(pos1, count1, MyBasicString(str, pos2, count2).c_str());
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    MyBasicString<CharT>& str,
    typename MyBasicString<CharT>::size_type pos2,
    typename MyBasicString<CharT>::size_type count2) const noexcept {
    return compare(pos1, count1, MyBasicString(str, pos2, count2).c_str());
}
template <typename CharT>
int MyBasicString<CharT>::compare(
    typename MyBasicString<CharT>::const_pointer cStr) const noexcept {
  return compare(0, size(), cStr, StrLen(cStr));
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    typename MyBasicString<CharT>::const_pointer cStr) const noexcept {
  return compare(pos1, count1, cStr, StrLen(cStr));
}

template <typename CharT>
int MyBasicString<CharT>::compare(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    typename MyBasicString<CharT>::const_pointer cStr,
    typename MyBasicString<CharT>::size_type count2) const noexcept {
  return StrCmp(MyBasicString(*this, pos1, count1).c_str(),
                MyBasicString(cStr, count2).c_str());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos,
    typename MyBasicString<CharT>::size_type count,
    const std::basic_string<CharT>& str) noexcept {
  return replace(pos, count, str.c_str());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos,
    typename MyBasicString<CharT>::size_type count,
    const MyBasicString<CharT>& str) noexcept {
  return replace(pos, count, str.c_str());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    const std::basic_string<CharT>& str,
    typename MyBasicString<CharT>::size_type pos2,
    typename MyBasicString<CharT>::size_type count2) noexcept {
  assert(!(pos2 > str.size()));
  return replace(pos1, count1, MyBasicString(str, pos2, count2).c_str());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    const MyBasicString<CharT>& str,
    typename MyBasicString<CharT>::size_type pos2,
    typename MyBasicString<CharT>::size_type count2) noexcept {
  assert(!(pos2 > str.size()));
  return replace(pos1, count1, MyBasicString(str, pos2, count2).c_str());
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    typename MyBasicString<CharT>::const_pointer cStr,
    typename MyBasicString<CharT>::size_type count2) noexcept {
  assert(!(pos1 > size()));
  MyBasicString<CharT> tmoStr =
    MyBasicString(c_str(), pos1) + MyBasicString(cStr, count2);
  return *this =  std::move((pos1 + count1 > size()) ?
    tmoStr : tmoStr += MyBasicString(c_str() + pos1 + count1));
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos,
    typename MyBasicString<CharT>::size_type count,
    typename MyBasicString<CharT>::const_pointer cStr) noexcept {
  return replace(pos, count, cStr, StrLen(cStr));
}

template <typename CharT>
MyBasicString<CharT>& MyBasicString<CharT>::replace(
    typename MyBasicString<CharT>::size_type pos1,
    typename MyBasicString<CharT>::size_type count1,
    typename MyBasicString<CharT>::size_type count2,
    typename MyBasicString<CharT>::value_type ch) noexcept {
  return replace(pos1, count1, MyBasicString(count2, ch).c_str());
}

template <typename CharT>
MyBasicString<CharT> MyBasicString<CharT>::substr(
    typename MyBasicString<CharT>::size_type pos,
    typename MyBasicString<CharT>::size_type count) const noexcept {
  assert(!(pos > size()));
  return MyBasicString(*this, pos, count);
}

template <typename CharT>
typename MyBasicString<CharT>::size_type MyBasicString<CharT>::copy(
    typename MyBasicString<CharT>::pointer dest,
    typename MyBasicString<CharT>::size_type count,
    typename MyBasicString<CharT>::size_type pos) const noexcept {
  size_type cnt = 0;
  assert(!(pos > size()));
  for (;cnt < count; ++cnt) {
    dest[cnt] = str_[cnt + pos];
  }
  dest[cnt] = 0;
  return cnt;
}

//---------------------------------Not sorted---------------------------------//

// Similar to block allocation, each block is 8 bytes. If size == 0, return 0,
// cuz no memory allocation is required
template <typename CharT>
inline typename MyBasicString<CharT>::size_type MyBasicString<CharT>::CapCalc(
    MyBasicString<CharT>::size_type size) {
  return size ? (((size >> 3) + 1) << 3) : 0;
}

// If pos is more than len, length should be zero, return min(len - pos, cnt)
template <typename CharT>
inline typename MyBasicString<CharT>::size_type MyBasicString<CharT>::LenCalc(
    MyBasicString<CharT>::size_type len,
    MyBasicString<CharT>::size_type pos,
    MyBasicString<CharT>::size_type count) {
  return Min(((len - pos > len) ? 0 : len - pos), count);
}

// Allocate memory for size objects of sting CharT
template <typename CharT>
inline typename MyBasicString<CharT>::pointer
MyBasicString<CharT>::MemAlloc(typename MyBasicString<CharT>::size_type size) {
  return (size ?
          new(std::nothrow) MyBasicString<CharT>::value_type[size] :
          nullptr);
}

template <typename CharT>
inline typename MyBasicString<CharT>::size_type MyBasicString<CharT>::Min(
    typename MyBasicString<CharT>::size_type num1,
    typename MyBasicString<CharT>::size_type num2){
  return (num1 > num2 ? num2 : num1);
}

// For copy-and-swap implementation
template <typename CharT>
template <typename T>
inline void MyBasicString<CharT>::Swap(T& lhs, T& rhs) noexcept {
  T tmp = lhs;
  lhs = rhs;
  rhs = tmp;
}

template <typename CharT>
inline void MyBasicString<CharT>::swap(MyBasicString<CharT>& other) noexcept {
  Swap(length_, other.length_);
  Swap(capacity_, other.capacity_);
  Swap(str_, other.str_);
}

template <typename CharT>
typename MyBasicString<CharT>::size_type MyBasicString<CharT>::StrLen(
    typename MyBasicString<CharT>::const_pointer cStr) {
  if (!cStr) return MyBasicString<CharT>::size_type{0};
  size_type length = 0;
  while(*cStr) { ++cStr; ++length; }
  return length;
}

template <typename CharT>
void MyBasicString<CharT>::StrCpy(
    typename MyBasicString<CharT>::pointer dst,
    typename MyBasicString<CharT>::const_pointer src,
    typename MyBasicString<CharT>::size_type count) {
  for (size_t i = 0; i < count; ++i) { dst[i] = src[i]; }
}

template <typename CharT>
void MyBasicString<CharT>::StrSet(
  typename MyBasicString<CharT>::pointer dst,
  typename MyBasicString<CharT>::value_type value,
  typename MyBasicString<CharT>::size_type count) {
  for (size_t i = 0; i < count; ++i) { dst[i] = value; }
}

template <typename CharT>
int MyBasicString<CharT>::StrCmp(
    typename MyBasicString<CharT>::const_pointer cStr1,
    typename MyBasicString<CharT>::const_pointer cStr2) {
  if(cStr1 && cStr2) {
    while (*cStr1 && (*cStr1 == *cStr2)) { ++cStr1; ++cStr2; }
    return static_cast<uint64_t>(*cStr1) - static_cast<uint64_t>(*cStr2);
  } else {
    return reinterpret_cast<int64_t>(cStr1 ? cStr1 : cStr2);
  }
}
} // namespace MyTypes

template <typename CharT>
std::basic_ostream<CharT>& operator<<(
    std::basic_ostream<CharT>& out,
    const MyTypes::MyBasicString<CharT>& str) noexcept {
  str.c_str() ? out << str.c_str() : out;
  // dbg
  out << '\n';
  out << str.size();
  out << '\n';
  out << str.capacity();
  return out;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    typename MyTypes::MyBasicString<CharT>::const_pointer rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    typename MyTypes::MyBasicString<CharT>::value_type rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    std::initializer_list<CharT> rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    const std::basic_string<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>& lhs,
    std::basic_string<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    typename MyTypes::MyBasicString<CharT>::const_pointer rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    typename MyTypes::MyBasicString<CharT>::value_type rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    std::initializer_list<CharT> rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    MyTypes::MyBasicString<CharT>&& lhs,
    const std::basic_string<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const MyTypes::MyBasicString<CharT>&& lhs,
    std::basic_string<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::const_pointer lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::const_pointer lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::value_type lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    typename MyTypes::MyBasicString<CharT>::value_type lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::initializer_list<CharT> lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::initializer_list<CharT> lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const std::basic_string<CharT>& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    const std::basic_string<CharT>& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::basic_string<CharT>&& lhs,
    const MyTypes::MyBasicString<CharT>& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs.c_str();
}

template <typename CharT>
MyTypes::MyBasicString<CharT> operator+(
    std::basic_string<CharT>&& lhs,
    MyTypes::MyBasicString<CharT>&& rhs) noexcept {
  MyTypes::MyBasicString<CharT> lhs_copy(lhs);
  return lhs_copy += rhs;
}
