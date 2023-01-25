#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class PropertiesTests : public TestingHelper::StringTestingBase<_Tuple> {};

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

TYPED_TEST_SUITE(PropertiesTests, MyParamTypes);

TYPED_TEST(PropertiesTests, AtInnerPos) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);
  typename TestFixture::MyTestingString::size_type __reqPos = 1;

  typename TestFixture::MyTestingString::size_type __pos =
    (__reqPos > __str.length()) ? 0 : __reqPos;

  //Act
  decltype(auto) __ch = __str.at(__pos);

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), value_type&>::value));
  EXPECT_EQ(__cStr[__pos], __ch);
}

TYPED_TEST(PropertiesTests, AtConstInnerPos) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);
  typename TestFixture::MyTestingString::size_type __reqPos = 1;

  typename TestFixture::MyTestingString::size_type __pos =
    (__reqPos > __str.length()) ? 0 : __reqPos;

  //Act
  decltype(auto) __ch = __str.at(__pos);

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), const value_type&>::value));
  EXPECT_EQ(__cStr[__pos], __ch);
}

TYPED_TEST(PropertiesTests, AtOuterPos) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);
  typename TestFixture::MyTestingString::size_type __reqPos = 1;

  typename TestFixture::MyTestingString::size_type __pos =
    (__reqPos >= __str.length()) ? __reqPos : __str.length();

  //Act

  EXPECT_THROW({
    decltype(auto) __ch = __str.at(__pos);
  }, MyTypes::MyException);

  //Assert
}

TYPED_TEST(PropertiesTests, AtConstOuterPos) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);
  typename TestFixture::MyTestingString::size_type __reqPos = 1;

  typename TestFixture::MyTestingString::size_type __pos =
    (__reqPos >= __str.length()) ? __reqPos : __str.length();

  //Act

  EXPECT_THROW({
    decltype(auto) __ch = __str.at(__pos);
  }, MyTypes::MyException);

  //Assert
}

TYPED_TEST(PropertiesTests, IndexOperator) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);
  typename TestFixture::MyTestingString::size_type __reqPos = 1;

  typename TestFixture::MyTestingString::size_type __pos =
    (__reqPos > __str.length()) ? 0 : __reqPos;

  //Act
  decltype(auto) __ch = __str[__pos];

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), value_type&>::value));
  EXPECT_EQ(__cStr[__pos], __ch);
}

TYPED_TEST(PropertiesTests, ConstIndexOperator) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);
  typename TestFixture::MyTestingString::size_type __reqPos = 1;

  typename TestFixture::MyTestingString::size_type __pos =
    (__reqPos > __str.length()) ? 0 : __reqPos;

  //Act
  decltype(auto) __ch = __str[__pos];

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), const value_type&>::value));
  EXPECT_EQ(__cStr[__pos], __ch);
}

TYPED_TEST(PropertiesTests, Front) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ch = __str.front();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), value_type&>::value));
  EXPECT_EQ(__cStr[0], __ch);
}

TYPED_TEST(PropertiesTests, ConstFront) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ch = __str.front();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), const value_type&>::value));
  EXPECT_EQ(__cStr[0], __ch);
}

TYPED_TEST(PropertiesTests, Back) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ch = __str.back();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), value_type&>::value));
  EXPECT_EQ(__cStr[std::char_traits<value_type>::length(__cStr) - 1], __ch);
}

TYPED_TEST(PropertiesTests, ConstBack) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ch = __str.back();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ch), const value_type&>::value));
  EXPECT_EQ(__cStr[std::char_traits<value_type>::length(__cStr) - 1], __ch);
}

TYPED_TEST(PropertiesTests, Data) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ptr = __str.data();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ptr), value_type*>::value));
  EXPECT_EQ(__ptr, std::addressof(__str[0]));
}

TYPED_TEST(PropertiesTests, ConstData) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ptr = __str.data();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ptr), const value_type*>::value));
  EXPECT_EQ(__ptr, std::addressof(__str[0]));
}

TYPED_TEST(PropertiesTests, CStr) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ptr = __str.c_str();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ptr), value_type*>::value));
  EXPECT_EQ(__ptr, std::addressof(__str[0]));
}

TYPED_TEST(PropertiesTests, ConstCStr) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act
  decltype(auto) __ptr = __str.c_str();

  //Assert
  EXPECT_TRUE((std::is_same<decltype(__ptr), const value_type*>::value));
  EXPECT_EQ(__ptr, std::addressof(__str[0]));
}

TYPED_TEST(PropertiesTests, Empty) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str1(__cStr);
  const typename TestFixture::MyTestingString __str2;

  //Act

  //Assert
  EXPECT_FALSE(__str1.empty());
  EXPECT_TRUE(__str2.empty());
}

TYPED_TEST(PropertiesTests, Length) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act

  //Assert
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr));
}

TYPED_TEST(PropertiesTests, Size) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act

  //Assert
  EXPECT_EQ(__str.size(), std::char_traits<value_type>::length(__cStr));
}

TYPED_TEST(PropertiesTests, LocalCapacity) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold - 1);

  //Act

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(PropertiesTests, DynamicCapacity) {
  //Arrange
  using value_type = typename TestFixture::MyTestingString::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  const typename TestFixture::MyTestingString __str(__cStr);

  //Act

  //Assert
  EXPECT_GT(__str.capacity(), std::char_traits<value_type>::length(__cStr));
}
