#include <gtest/gtest.h>
#include <iostream>
#include <initializer_list>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class ConstructorsTests : public TestingHelper::StringTestingBase<_Tuple> {};

using MyParamTypes = testing::Types<
// For types defined in standards after C++17
#if __cplusplus > 201703L
  std::tuple<char8_t>
#endif
  std::tuple<char>,
  std::tuple<char16_t>,
  std::tuple<char32_t>,
  std::tuple<wchar_t>,
  std::tuple<char, std::char_traits<char>>,
  std::tuple<char, std::char_traits<char>,
    std::pmr::polymorphic_allocator<char>>
>;


TYPED_TEST_SUITE(ConstructorsTests, MyParamTypes);

TYPED_TEST(ConstructorsTests, Default) {
  //Arrange

  //Act
  typename TestFixture::MyTestingString __str;

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, Allocator) {
  //Arrange
  using allocator_type = typename TestFixture::allocator_type;

  allocator_type __alloc;

  //Act
  const typename TestFixture::MyTestingString __str(__alloc);

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, SingleChar) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  constexpr const value_type __ch = *(TestFixture::_str1.begin());

  const std::basic_string<value_type> __cmp(__ch);

  //Act
  const typename TestFixture::MyTestingString __str(__ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CharsInLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type __ch = *(TestFixture::_str1.begin());
  const size_type __count = 0x8e % TestFixture::_localBufferCapThreshold;

  const std::basic_string<value_type> __cmp(__ch, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__count, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, CharsDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type __ch = *(TestFixture::_str1.begin());
  const size_type __count = 0x8e % TestFixture::_localBufferCapThreshold +
    TestFixture::_localBufferCapThreshold;

  const std::basic_string<value_type> __cmp(__count, __ch);

  //Act
  const typename TestFixture::MyTestingString __str(__count, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type* __cStr = TestFixture::_str1;

  const std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Local buffer guarantee
  const size_type __reqPos = 6;
  const size_type __pos = (__other.length() >= __reqPos) ? __reqPos : 0;

  const std::basic_string<value_type> __cmp(__other, __pos);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamicPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type* __cStr = TestFixture::_str1.begin();

  const std::basic_string<value_type> __other(__cStr);

  //Dynamic buffer guarantee
  const size_type __reqPos = 6;
  const size_type __pos = (__other.length() > __reqPos +
    TestFixture::_localBufferLenThreshold) ? __reqPos : 0;

  const std::basic_string<value_type> __cmp(__other, __pos);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type* __cStr = TestFixture::_str1.begin();

  const std::basic_string<value_type> __other(__cStr);

  //Act
  const size_type __pos = 1000;

  //Assert
  EXPECT_THROW( {
    const typename TestFixture::MyTestingString __str(__other, __pos);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type* __cStr = TestFixture::_str1.begin();

  const std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Local buffer guarantee
  const size_type __reqPos = 6;
  const size_type __reqCount = TestFixture::_localBufferLenThreshold;

  const size_type __pos = (__other.length() >= __reqPos) ? __reqPos : 0;
  size_type __count = (__reqCount > TestFixture::_localBufferLenThreshold) ? 
    TestFixture::_localBufferLenThreshold : __reqCount;
  __count = (__other.length() > __reqPos + __reqCount) ? __reqCount :
    __other.length() - __reqPos;

  const std::basic_string<value_type> __cmp(__other, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type* __cStr = TestFixture::_str1.begin(); 

  const std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Local buffer guarantee
  const size_type __reqPos = 6;
  const size_type __reqCount = 1000;

  const size_type __pos = (__other.length() >= __reqPos) ? __reqPos : 0;
  const size_type __count = (__count > __other.length()) ? __count :
    __other.length() + 1;

  const std::basic_string<value_type> __cmp(__other, __pos, __count);

  //Act
  const typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_GT(__str.capacity(), __cmp.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(ConstructorsTests, STLStringDynamicPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  constexpr const value_type* __cStr = TestFixture::_str1.begin();

  const std::basic_string<value_type> __other(__cStr);

  //Dynamic buffer guarantee
  const size_type __reqPos = 6;
  const size_type __reqCount = TestFixture::_localBufferCapThreshold;

  const size_type __pos = (__other.length() > __reqPos +
    TestFixture::_localBufferLenThreshold) ? __reqPos : 0;
  size_type __count = (__reqCount > TestFixture::_localBufferCapThreshold) ?
    __reqCount : TestFixture::_localBufferCapThreshold;
  __count = (__other.length() > __pos + __count) ? __count

  const std::basic_string<value_type> __cmp(__other, __pos);

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringDynamicPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  size_type __pos = 6;
  size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
      std::char_traits<value_type>::length(__other.data()+ __pos),
      __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringPosOutsideCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  size_type __pos = 1000;
  size_type __count = 6;
  //Act

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos, __count);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  // Local buffer guarantee
  size_type __reqPos = 6;
  size_type __pos =
    (__other.length() > TestFixture::_localBufferCapThreshold) ?
    __other.length() - TestFixture::_localBufferLenThreshold : __reqPos;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringDynamicPosInside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  size_type __pos = 6;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);

  //Act
  size_type __pos = 1000;

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  // Local buffer guarantee
  size_type __reqPos = 6;
  size_type __pos =
    (__other.length() > TestFixture::_localBufferCapThreshold) ?
    __other.length() - TestFixture::_localBufferLenThreshold : __reqPos;
  size_type __count =
    (__other.size() - __pos > TestFixture::_localBufferCapThreshold) ?
    TestFixture :: _localBufferCapThreshold : __other.size() - __pos - 1;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  // Local buffer guarantee
  size_type __reqPos = 6;
  size_type __pos =
    (__other.length() > TestFixture::_localBufferCapThreshold) ?
    __other.length() - TestFixture::_localBufferLenThreshold : __reqPos;
  size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringDynamicPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  size_type __pos = 6;
  size_type __count =
    TestFixture::_localBufferCapThreshold + 1;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringDynamicPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  size_type __pos = 6;
  size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
      std::char_traits<value_type>::length(__other.data()+ __pos),
      __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringPosOutsideCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  size_type __pos = 1000;
  size_type __count = 6;
  //Act

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos, __count);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, CStringLocalCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  size_type __count =
    TestFixture::_localBufferCapThreshold - 2;

  //Act
  typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __count, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringDynamicCounted) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  size_type __reqCount =
    TestFixture::_localBufferCapThreshold + 2;
  size_type __count =
    (std::char_traits<value_type>::length(__cStr) > __reqCount) ?
    __reqCount : std::char_traits<value_type>::length(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __count, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringNullptrCountGTZero) {
  //Arrange
  using const_pointer = typename TestFixture::const_pointer;
  const_pointer __cStr = nullptr;
  size_type __count = 1;
  //Act

  //Assert
  EXPECT_THROW({
    typename TestFixture::MyTestingString __str(__cStr, __count);
  }, MyTypes::MyException);

}

TYPED_TEST(ConstructorsTests, CStringNullptrCountEQZero) {
  //Arrange
  using const_pointer = typename TestFixture::const_pointer;
  const_pointer __cStr = nullptr;
  size_type __count = 0;

  //Act
  typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(ConstructorsTests, CStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  size_type __pos =
    (__cStrLen > TestFixture::_localBufferCapThreshold) ?
     __cStrLen - TestFixture::_localBufferLenThreshold : 0;

  //Act
  typename TestFixture::MyTestingString __str(__cStr + __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr + __pos, __cStrLen - __pos,
     __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__cStr);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __cStrLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringNullptr) {
  //Arrange
  using const_pointer = typename TestFixture::const_pointer;
  const_pointer __cStr = nullptr;
  //Act

  //Assert
  EXPECT_THROW({
    typename TestFixture::MyTestingString __str(__cStr);
  }, MyTypes::MyException);

}

TYPED_TEST(ConstructorsTests, InputIterLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr,
      TestFixture::_localBufferLenThreshold);

  //Act
  typename TestFixture::MyTestingString __str(__other.begin(), __other.end());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, InputIterDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other.begin(), __other.end());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringDynamicAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringDynamicAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferLenThreshold);
  size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other));

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other));

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_GT(__str.capacity(), __prevLen);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferLenThreshold);
  size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other),
    allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringDynamicAlloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  auto __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other),
    allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_GT(__str.capacity(), __prevLen);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, InitaiazierListLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  std::initializer_list<value_type> __ilist =
    {'H', 'e', 'l'};

  //Act
  typename TestFixture::MyTestingString __str(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__ilist.begin(), __ilist.size(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, InitaiazierListDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using allocator_type = typename TestFixture::allocator_type;

  std::initializer_list<value_type> __ilist =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  //Act
  typename TestFixture::MyTestingString __str(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), __ilist.size());
  EXPECT_EQ(TestingHelper::CustomStrCmp(__ilist.begin(), __ilist.size(),
    __str.data(), __str.length()), 0);
}
