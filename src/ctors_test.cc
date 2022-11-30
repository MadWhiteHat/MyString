#include <gtest/gtest.h>
#include <initializer_list>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class ConstructorsTests : public TestingHelper::TestingBase<_Tuple> {
  public:
// Instantiation different string type depending on provided tuple 
  using typename TestingHelper::TestingBase<_Tuple>::MyTestingString;
  using TestingHelper::_localBufferThreshold;
};

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
 std::tuple<char, std::char_traits<char>, std::pmr::polymorphic_allocator<char>>
>;


TYPED_TEST_SUITE(ConstructorsTests, MyParamTypes);

TYPED_TEST(ConstructorsTests, Default) {
  //Arrange
  
  //Act
  typename TestFixture::MyTestingString __str; 

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
}

TYPED_TEST(ConstructorsTests, Allocator) {
  //Arrange
  typename TestFixture::MyTestingString::allocator_type __alloc;

  //Act
  typename TestFixture::MyTestingString __str(__alloc);

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
}

TYPED_TEST(ConstructorsTests, SingleChar) {
  //Arrange
  typename TestFixture::MyTestingString::value_type __ch = 'a';

  //Act
  typename TestFixture::MyTestingString __str(__ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), 1);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
}

TYPED_TEST(ConstructorsTests, CharsInLocal) {
  //Arrangei
  typename TestFixture::MyTestingString::value_type __ch = 'a';
  typename TestFixture::MyTestingString::size_type __count =
    0x8e % TestFixture::_localBufferThreshold;

  //Act
  typename TestFixture::MyTestingString __str(__count, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
}

TYPED_TEST(ConstructorsTests, CharsOutLocal) {
  //Arrangei
  typename TestFixture::MyTestingString::value_type __ch = 'a';
  typename TestFixture::MyTestingString::size_type __count =
    0x8e % TestFixture::_localBufferThreshold +
    TestFixture::_localBufferThreshold;

  //Act
  typename TestFixture::MyTestingString __str(__count, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  // Local buffer guarantee
  typename TestFixture::MyTestingString::size_type __reqPos = 6;
  typename TestFixture::MyTestingString::size_type __pos =
    (__other.length() > TestFixture::_localBufferThreshold) ?
    __other.length() - TestFixture::_localBufferThreshold + 1 : __reqPos;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringOutLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 6; 

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringPosOutside) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString::size_type __pos = 1000; 

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  // Local buffer guarantee
  typename TestFixture::MyTestingString::size_type __reqPos = 6;
  typename TestFixture::MyTestingString::size_type __pos =
    (__other.length() > TestFixture::_localBufferThreshold) ?
    __other.length() - TestFixture::_localBufferThreshold + 1 : __reqPos;
  typename TestFixture::MyTestingString::size_type __count = 
    (__other.size() - __pos > TestFixture::_localBufferThreshold) ?
    TestFixture :: _localBufferThreshold : __other.size() - __pos - 1;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  // Local buffer guarantee
  typename TestFixture::MyTestingString::size_type __reqPos = 6;
  typename TestFixture::MyTestingString::size_type __pos =
    (__other.length() > TestFixture::_localBufferThreshold) ?
    __other.length() - TestFixture::_localBufferThreshold + 1 : __reqPos;
  typename TestFixture::MyTestingString::size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringOutLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 6;
  typename TestFixture::MyTestingString::size_type __count =
    TestFixture::_localBufferThreshold + 1;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringOutLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 6;
  typename TestFixture::MyTestingString::size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
      std::char_traits<value_type>::length(__other.data()+ __pos),
      __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringPosOutsideCounted) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 1000;
  typename TestFixture::MyTestingString::size_type __count = 6;
  //Act

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos, __count);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  // Local buffer guarantee
  typename TestFixture::MyTestingString::size_type __reqPos = 6;
  typename TestFixture::MyTestingString::size_type __pos =
    (__other.length() > TestFixture::_localBufferThreshold) ?
    __other.length() - TestFixture::_localBufferThreshold + 1 : __reqPos;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringOutLocalPosInside) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 6; 

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringPosOutside) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);

  //Act
  typename TestFixture::MyTestingString::size_type __pos = 1000; 

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  // Local buffer guarantee
  typename TestFixture::MyTestingString::size_type __reqPos = 6;
  typename TestFixture::MyTestingString::size_type __pos =
    (__other.length() > TestFixture::_localBufferThreshold) ?
    __other.length() - TestFixture::_localBufferThreshold + 1 : __reqPos;
  typename TestFixture::MyTestingString::size_type __count = 
    (__other.size() - __pos > TestFixture::_localBufferThreshold) ?
    TestFixture :: _localBufferThreshold : __other.size() - __pos - 1;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  // Local buffer guarantee
  typename TestFixture::MyTestingString::size_type __reqPos = 6;
  typename TestFixture::MyTestingString::size_type __pos =
    (__other.length() > TestFixture::_localBufferThreshold) ?
    __other.length() - TestFixture::_localBufferThreshold + 1 : __reqPos;
  typename TestFixture::MyTestingString::size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
        std::char_traits<value_type>::length(__other.data() + __pos),
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringOutLocalPosInsideCountValid) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 6;
  typename TestFixture::MyTestingString::size_type __count =
    TestFixture::_localBufferThreshold + 1;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos, __count,
        __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringOutLocalPosInsideCountOver) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 6;
  typename TestFixture::MyTestingString::size_type __count = 1000;

  //Act
  typename TestFixture::MyTestingString __str(__other, __pos, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), __other.length() - __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(
      TestingHelper::CustomStrCmp(__other.data() + __pos,
      std::char_traits<value_type>::length(__other.data()+ __pos),
      __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringPosOutsideCounted) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString::size_type __pos = 1000;
  typename TestFixture::MyTestingString::size_type __count = 6;
  //Act

  //Assert
  EXPECT_THROW( {
    typename TestFixture::MyTestingString __str(__other, __pos, __count);
  }, MyTypes::MyException );
}

TYPED_TEST(ConstructorsTests, CStringLocalCounted) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString::size_type __count =
    TestFixture::_localBufferThreshold - 2;

  //Act
  typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __count, __str.data(), 
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringOutLocalCounted) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString::size_type __reqCount = 
    TestFixture::_localBufferThreshold + 2;
  typename TestFixture::MyTestingString::size_type __count =
    (std::char_traits<value_type>::length(__cStr) > __reqCount) ?
    __reqCount : std::char_traits<value_type>::length(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __count, __str.data(), 
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringNullptrCountGTZero) {
  //Arrange
  using const_pointer = typename TestFixture::MyTestingString::const_pointer;
  const_pointer __cStr = nullptr;
  typename TestFixture::MyTestingString::size_type __count = 1;
  //Act

  //Assert
  EXPECT_THROW({
    typename TestFixture::MyTestingString __str(__cStr, __count);
  }, MyTypes::MyException);
 
}

TYPED_TEST(ConstructorsTests, CStringNullptrCountEQZero) {
  //Arrange
  using const_pointer = typename TestFixture::MyTestingString::const_pointer;
  const_pointer __cStr = nullptr;
  typename TestFixture::MyTestingString::size_type __count = 0;

  //Act
  typename TestFixture::MyTestingString __str(__cStr, __count);

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold); 
}

TYPED_TEST(ConstructorsTests, CStringLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  typename TestFixture::MyTestingString::size_type __pos =
    (__cStrLen > TestFixture::_localBufferThreshold) ? 
     __cStrLen - TestFixture::_localBufferThreshold + 1 : 0;

  //Act
  typename TestFixture::MyTestingString __str(__cStr + __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen - __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr + __pos, __cStrLen - __pos,
     __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringOutLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__cStr);
  
  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __cStrLen, __str.data(), 
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, CStringNullptr) {
  //Arrange
  using const_pointer = typename TestFixture::MyTestingString::const_pointer;
  const_pointer __cStr = nullptr;
  //Act

  //Assert
  EXPECT_THROW({
    typename TestFixture::MyTestingString __str(__cStr);
  }, MyTypes::MyException);
 
}

TYPED_TEST(ConstructorsTests, InputIterLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr,
      TestFixture::_localBufferThreshold - 1);

  //Act
  typename TestFixture::MyTestingString __str(__other.begin(), __other.end());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, InputIterOutLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other.begin(), __other.end());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferThreshold - 1);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringOutLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr,
    TestFixture::_localBufferThreshold - 1);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, STLStringOutLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::basic_string<value_type> __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferThreshold - 1);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringOutLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferThreshold - 1);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MyStringOutLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);

  //Act
  typename TestFixture::MyTestingString __str(__other, allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__other.data(), __other.length(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferThreshold - 1);
  typename TestFixture::MyTestingString::size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other));

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringOutLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString::size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other));

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_GT(__str.capacity(), __prevLen);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr,
    TestFixture::_localBufferThreshold - 1);
  typename TestFixture::MyTestingString::size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other),
    allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, MoveMyStringOutLocalAlloc) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;
  value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l', 
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString::size_type __prevLen = __other.length();

  //Act
  typename TestFixture::MyTestingString __str(std::move(__other),
    allocator_type());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_GT(__str.capacity(), __prevLen);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__cStr, __prevLen, __str.data(),
    __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, InitaiazierListLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  std::initializer_list<value_type> __ilist =
    {'H', 'e', 'l'};

  //Act
  typename TestFixture::MyTestingString __str(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__ilist.begin(), __ilist.size(),
    __str.data(), __str.length()), 0);
}

TYPED_TEST(ConstructorsTests, InitaiazierListOutLocal) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  using allocator_type = typename TestFixture::MyTestingString::allocator_type;

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
