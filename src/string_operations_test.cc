#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class OperationsTests : public TestingHelper::StringTestingBase<_Tuple> {};

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

TYPED_TEST_SUITE(OperationsTests, MyParamTypes);

TYPED_TEST(OperationsTests, ReserveInLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve(TestFixture::_localBufferCapThreshold - 1);

  //Assert
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}

TYPED_TEST(OperationsTests, ReserveLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve(__prevCap + 1);

  //Assert
  EXPECT_NE(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_LE(__str.capacity(), __prevCap * 2);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}

TYPED_TEST(OperationsTests, ReserveDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve(__prevCap + 1);

  //Assert
  EXPECT_NE(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_LE(__str.capacity(), __prevCap * 2);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}

#if __cplusplus <= 201703L
TYPED_TEST(OperationsTests, ReserveAsShrinkToFit) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.reserve();

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_LE(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}
#endif

TYPED_TEST(OperationsTests, ShrinkToFitLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold - 1);

  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  // Going to use allocated storage
  __str.reserve(TestFixture::_localBufferCapThreshold + 1);
  // Moving back to local storage
  __str.shrink_to_fit();

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}

TYPED_TEST(OperationsTests, ShrinkToFitDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();
  //Act
  __str.shrink_to_fit();

  //Assert
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_LE(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}

TYPED_TEST(OperationsTests, ClearLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  auto __prevData = __str.data();
  auto __prevCap = __str.capacity();

  //Act
  __str.clear();

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(OperationsTests, ClearDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  auto __prevData = __str.data();
  auto __prevCap = __str.capacity();

  //Act
  __str.clear();

  //Assert
  EXPECT_TRUE(__str.empty());
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(OperationsTests, InsertCntCharLocal) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  const size_type __pos = 0;
  const size_type __cnt = TestFixture::_localBufferLenThreshold - __initLen;
  value_type __ch = 'a';
  typename TestFixture::MyTestingString __str(__cStr, __initLen);

  auto __prevData = __str.data();
  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __other(__cStr, __initLen);
  __other.insert(__pos, __cnt, __ch);

  //Act
  __str.insert(__pos, __cnt, __ch);

  //Assert
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.capacity(), __prevCap);
}
