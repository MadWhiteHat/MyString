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
class AssignTests : public TestingHelper::StringTestingBase<_Tuple> {};

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


TYPED_TEST_SUITE(AssignTests, MyParamTypes);

TYPED_TEST(AssignTests, AssignOperatorMyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __other(__cStr,
       TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignOperatorMyStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignOperatorSTLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  std::basic_string<value_type> __other(__cStr,
       TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignOperatorSTLStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  std::basic_string<value_type> __other(__cStr);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __other(__cStr,
       TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;
  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);

}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString __str;
  auto __prevDataPtr = __other.data();
  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __pos = (__cStrLen > TestFixture::_localBufferLenThreshold) ?
    __cStrLen - TestFixture::_localBufferLenThreshold : 0;
  typename TestFixture::MyTestingString __other(__cStr + __pos);
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringDyncamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __reqPos = 4;
  const size_type __pos = (__cStrLen - __reqPos >
    TestFixture::_localBufferLenThreshold) ? __reqPos : 0;
  typename TestFixture::MyTestingString __other(__cStr + __pos);
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str = std::move(__str);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, std::char_traits<value_type>::length(__cStr)), 0);

}

TYPED_TEST(AssignTests, AssignOperatorCStrLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __pos = (__cStrLen > TestFixture::_localBufferLenThreshold) ?
    __cStrLen - TestFixture::_localBufferLenThreshold : 0;

  //Act
  __str = __cStr + __pos;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr +
    __pos));
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, std::char_traits<value_type>::length(__cStr + __pos)), 0);
}

TYPED_TEST(AssignTests, AssignOperatorCStrLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();
  auto __prevCap = __str.capacity();
  const size_type __pos = (__cStrLen > TestFixture::_localBufferLenThreshold) ?
    __cStrLen - TestFixture::_localBufferLenThreshold : 0;

  //Act
  __str = __cStr + __pos;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr +
    __pos));
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(), __cStr +
    __pos, std::char_traits<value_type>::length(__cStr + __pos)), 0);
}

TYPED_TEST(AssignTests, AssignOperatorCStrDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);

  //Act
  __str = __cStr;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __cStrLen), 0);
}

TYPED_TEST(AssignTests, AssignOperatorCStrDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  typename TestFixture::MyTestingString __str(__cStr + 2);
  auto __prevDataPtr = __str.data();

  //Act
  __str = __cStr;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __cStrLen), 0);
}

TYPED_TEST(AssignTests, AssignOperatorCStrLocalSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();

  //Act
  __str = __str.data() + 1;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen - 1);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + 1, __prevLen - 1), 0);
}

TYPED_TEST(AssignTests, AssignOperatorCStrDynamicSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __reqPos  = 1;
  const size_type __pos = (__reqPos + TestFixture::_localBufferCapThreshold >
    __cStrLen) ? (__cStrLen - TestFixture::_localBufferLenThreshold) : __reqPos;
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();

  //Act
  __str = __str.data() + __pos;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr +
    __pos));
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(), __cStr +
    __pos, std::char_traits<value_type>::length(__cStr + __pos)), 0);
}

TYPED_TEST(AssignTests, AssignOperatorCharToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  typename TestFixture::MyTestingString __str;
  constexpr const value_type __ch = 'a';

  //Act
  __str = __ch;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), 1);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, AssignOperatorCharToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();
  auto __prevCap = __str.capacity();
  value_type __ch = 'a';

  //Act
  __str = __ch;

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), 1);
  EXPECT_EQ(__str.capacity(), __prevCap);

}

TYPED_TEST(AssignTests, AssignOperatorListLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  std::initializer_list<value_type> __ilist = {'G', 'o'};
  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str = __ilist;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignOperatorListLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  std::initializer_list<value_type> __ilist = {'G', 'o'};
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevCap = __str.capacity();

  //Act
  __str = __ilist;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignOperatorListDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str = __ilist;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignOperatorListDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  __str = __ilist;

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignCharsLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  value_type __ch = 'a';
  typename TestFixture::MyTestingString __cmp(
    TestFixture::_localBufferLenThreshold - 2, __ch);

  //Act
  __str.assign(TestFixture::_localBufferLenThreshold - 2, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cmp.data(), __cmp.length()), 0);
}

TYPED_TEST(AssignTests, AssignCharsDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  value_type __ch = 'a';
  typename TestFixture::MyTestingString __cmp(
    TestFixture::_localBufferLenThreshold + 2, __ch);

  //Act
  __str.assign(TestFixture::_localBufferLenThreshold + 2, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cmp.data(), __cmp.length()), 0);
}

TYPED_TEST(AssignTests, AssignCharsLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r','l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);
  value_type __ch = 'a';
  typename TestFixture::MyTestingString __cmp(
    TestFixture::_localBufferLenThreshold - 2, __ch);

  //Act
  __str.assign(TestFixture::_localBufferLenThreshold - 2, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cmp.data(), __cmp.length()), 0);
}

TYPED_TEST(AssignTests, AssignCharsDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r','l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);
  value_type __ch = 'a';
  typename TestFixture::MyTestingString __cmp(
    TestFixture::_localBufferLenThreshold + 2, __ch);

  //Act
  __str.assign(TestFixture::_localBufferLenThreshold + 2, __ch);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cmp.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cmp.data(), __cmp.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i','n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __other(__cStr2,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __other(__cStr2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);
  typename TestFixture::MyTestingString __other(__cStr2,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee no realloc

  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr1 : __cStr2;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  typename TestFixture::MyTestingString __other(__assignData);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee realloc

  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr2 : __cStr1;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  typename TestFixture::MyTestingString __other(__assignData);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__str);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(AssignTests, AssignSTLStringLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  std::basic_string<value_type> __other(__cStr2,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  std::basic_string<value_type> __other(__cStr2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);
  std::basic_string<value_type> __other(__cStr2,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee no realloc
  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr1 : __cStr2;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  std::basic_string<value_type> __other(__assignData);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee realloc
  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr2 : __cStr1;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  std::basic_string<value_type> __other(__assignData);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringPosCountLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __other(__cStr2);

  const size_type __reqLength = TestFixture::_localBufferLenThreshold;
  const size_type __reqPos = 1;

  const size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    TestFixture::_localBufferLenThreshold : __reqLength;
  const size_type __pos = (__reqPos + __length > __other.length()) ? 0 :
    __reqPos;

  //Act
  __str.assign(__other, __pos, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data() + __pos, (__other.length() > __length + __pos) ?
    __length : __other.length() - __pos), 0);

}

TYPED_TEST(AssignTests, AssignMyStringPosCountDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __other(__cStr2);

  const size_type __reqLength = TestFixture::_localBufferLenThreshold + 1;
  const size_type __reqPos = 1;

  const size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    __reqLength : TestFixture::_localBufferLenThreshold + 1;
  const size_type __pos = (__reqPos + __length > __other.length()) ? 0 :
    __reqPos;

  //Act
  __str.assign(__other, __pos, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data() + __pos, (__other.length() > __length + __pos) ?
    __length : __other.length() - __pos), 0);
}

TYPED_TEST(AssignTests, AssignMyStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);
  typename TestFixture::MyTestingString __other(__cStr2);

  const size_type __reqLength = TestFixture::_localBufferLenThreshold;
  const size_type __reqPos = 1;

  const size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    TestFixture::_localBufferLenThreshold : __reqLength;
  const size_type __pos = (__reqPos + __length > __other.length()) ? 0 :
    __reqPos;

  //Act
  __str.assign(__other, __pos, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data() + __pos, (__other.length() > __length + __pos) ?
    __length : __other.length() - __pos), 0);

}

TYPED_TEST(AssignTests, AssignMyStringPosCountDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr1 : __cStr2;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  typename TestFixture::MyTestingString __other(__assignData);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringPosCountDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee realloc
  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr2 : __cStr1;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  typename TestFixture::MyTestingString __other(__assignData);

  const size_type __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringPosCountPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);
  typename TestFixture::MyTestingString __other(__cStr2);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  EXPECT_THROW({
    __str.assign(__other, __other.length() + 1);
  }, MyTypes::MyException);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_NE(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignMyStringPosCountSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  const size_type __reqPos = 1;
  const size_type __pos = (__reqPos  > __str.length()) ? 0 : __reqPos;


  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__str, __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen - __pos);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, std::char_traits<value_type>::length(__cStr + __pos)), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  std::basic_string<value_type> __other(__cStr2);

  const size_type __reqLength =
    TestFixture::_localBufferLenThreshold;
  const size_type __reqPos = 1;

  const size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    TestFixture::_localBufferLenThreshold : __reqLength;
  const size_type __pos = (__reqPos + __length > __other.length()) ? 0 :
    __reqPos;

  //Act
  __str.assign(__other, __pos, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data() + __pos, (__other.length() > __length + __pos) ?
    __length : __other.length() - __pos), 0);

}

TYPED_TEST(AssignTests, AssignSTLStringPosCountDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);
  std::basic_string<value_type> __other(__cStr2);

  const size_type __reqLength =
    TestFixture::_localBufferLenThreshold + 1;
  const size_type __reqPos = 1;

  const size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    __reqLength : TestFixture::_localBufferLenThreshold + 1;
  const size_type __pos = (__reqPos + __length > __other.length()) ? 0 :
    __reqPos;

  //Act
  __str.assign(__other, __pos, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data() + __pos, (__other.length() > __length + __pos) ?
    __length : __other.length() - __pos), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);
  std::basic_string<value_type> __other(__cStr2);

  const size_type __reqLength =
    TestFixture::_localBufferLenThreshold;
  const size_type __reqPos = 1;

  const size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    TestFixture::_localBufferLenThreshold : __reqLength;
  const size_type __pos = (__reqPos + __length > __other.length()) ? 0 :
    __reqPos;

  //Act
  __str.assign(__other, __pos, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data() + __pos, (__other.length() > __length + __pos) ?
    __length : __other.length() - __pos), 0);

}

TYPED_TEST(AssignTests, AssignSTLStringPosCountDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr1 : __cStr2;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  std::basic_string<value_type> __other(__assignData);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee realloc
  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr2 : __cStr1;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  std::basic_string<value_type> __other(__assignData);

  const size_type __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __other.length());
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);
  std::basic_string<value_type> __other(__cStr2);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  EXPECT_THROW({
    __str.assign(__other, __other.length() + 1);
  }, MyTypes::MyException);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_NE(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __other.data(), __other.length()), 0);
}

TYPED_TEST(AssignTests, MoveAssignMyStringLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __other(__cStr,
       TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;
  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);

}

TYPED_TEST(AssignTests, MoveAssignMyStringDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __other(__cStr);
  typename TestFixture::MyTestingString __str;
  auto __prevDataPtr = __other.data();
  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignMyStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __pos = (__cStrLen > TestFixture::_localBufferLenThreshold) ?
    __cStrLen - TestFixture::_localBufferLenThreshold : 0;
  typename TestFixture::MyTestingString __other(__cStr + __pos);
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignMyStringDyncamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __reqPos = 4;
  const size_type __pos =
    (__cStrLen - __reqPos > TestFixture::_localBufferLenThreshold) ?
    __reqPos : 0;
  typename TestFixture::MyTestingString __other(__cStr + __pos);
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, __prevLen), 0);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignMyStringSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(std::move(__str));

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, std::char_traits<value_type>::length(__cStr)), 0);
}

TYPED_TEST(AssignTests, AssignCStrLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  const size_type __pos = (__cStrLen > TestFixture::_localBufferLenThreshold) ?
    __cStrLen - TestFixture::_localBufferLenThreshold : 0;

  //Act
  __str.assign(__cStr + __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr +
    __pos));
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, std::char_traits<value_type>::length(__cStr + __pos)), 0);
}

TYPED_TEST(AssignTests, AssignCStrLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();
  auto __prevCap = __str.capacity();
  const size_type __pos = (__cStrLen > TestFixture::_localBufferLenThreshold) ?
    __cStrLen - TestFixture::_localBufferLenThreshold : 0;

  //Act
  __str.assign(__cStr + __pos);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr +
    __pos));
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + __pos, std::char_traits<value_type>::length(__cStr + __pos)), 0);
}

TYPED_TEST(AssignTests, AssignCStrDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __cStrLen = std::char_traits<value_type>::length(__cStr);

  //Act
  __str.assign(__cStr);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __cStrLen), 0);
}

TYPED_TEST(AssignTests, AssignCStrDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  auto __cStrLen = std::char_traits<value_type>::length(__cStr);
  typename TestFixture::MyTestingString __str(__cStr + 2);
  auto __prevDataPtr = __str.data();

  //Act
  __str.assign(__cStr);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __cStrLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __cStrLen), 0);
}

TYPED_TEST(AssignTests, AssignCStrLocalSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r','l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();

  //Act
  __str.assign(__str.data() + 1);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen - 1);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + 1, __prevLen - 1), 0);
}

TYPED_TEST(AssignTests, AssignCStrDynamicSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r','l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevDataPtr = __str.data();

  //Act
  __str.assign(__str.data() + 1);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), std::char_traits<value_type>::length(__cStr + 1));
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr + 1, std::char_traits<value_type>::length(__cStr + 1)), 0);
}

TYPED_TEST(AssignTests, AssignCStrCountLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);

  const size_type __cStr2Len = std::char_traits<value_type>::length(__cStr2);

  const size_type __reqLength = TestFixture::_localBufferLenThreshold;
  size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    TestFixture::_localBufferLenThreshold : __reqLength;
  __length = (__length > __cStr2Len) ? __cStr2Len : __length;

  //Act
  __str.assign(__cStr2, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __cStr2);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(), __cStr2,
    __length), 0);
}

TYPED_TEST(AssignTests, AssignCStrCountDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1,
    TestFixture::_localBufferLenThreshold);

  const size_type __cStr2Len = std::char_traits<value_type>::length(__cStr2);

  const size_type __reqLength = TestFixture::_localBufferLenThreshold + 1;
  size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    __reqLength : TestFixture::_localBufferLenThreshold + 1;
  __length = (__length > __cStr2Len) ? __cStr2Len : __length;

  //Act
  __str.assign(__cStr2, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __cStr2);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(), __cStr2,
    __length), 0);
}

TYPED_TEST(AssignTests, AssignCStrCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  typename TestFixture::MyTestingString __str(__cStr1);

  const size_type __cStr2Len = std::char_traits<value_type>::length(__cStr2);

  const size_type __reqLength = TestFixture::_localBufferLenThreshold;
  size_type __length =
    (__reqLength > TestFixture::_localBufferLenThreshold) ?
    TestFixture::_localBufferLenThreshold : __reqLength;
  __length = (__length > __cStr2Len) ? __cStr2Len : __length;

  //Act
  __str.assign(__cStr2, __length);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __cStr2);
  EXPECT_EQ(__str.length(), __length);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(), __cStr2,
    __length), 0);
}

TYPED_TEST(AssignTests, AssignCStrCountDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr1 : __cStr2;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;

  typename TestFixture::MyTestingString __str(__initData);
  const size_type __assignDataLen = std::char_traits<value_type>::length(
    __assignData);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__assignData, __assignDataLen);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __assignData);
  EXPECT_EQ(__str.length(), __assignDataLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __assignData, __assignDataLen), 0);
}

TYPED_TEST(AssignTests, AssignCStrCountDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr1[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  constexpr const value_type __cStr2[] =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
     'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n', '\0' };

  TestFixture::LengthTest(__cStr1);
  TestFixture::LengthTest(__cStr2);

  // guarantee realloc
  const value_type* __initData = (
      std::char_traits<value_type>::length(__cStr1) >
      std::char_traits<value_type>::length(__cStr2)) ? __cStr2 : __cStr1;
  const value_type* __assignData = (__initData == __cStr1) ?
    __cStr2 : __cStr1;
  typename TestFixture::MyTestingString __str(__initData);
  const size_type __assignDataLen = std::char_traits<value_type>::length(
    __assignData);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__assignData, __assignDataLen);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_NE(__str.data(), __assignData);
  EXPECT_EQ(__str.length(), __assignDataLen);
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __assignData, __assignDataLen), 0);
}

TYPED_TEST(AssignTests, AssignCStrCountSelf) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  typename TestFixture::MyTestingString __str(__cStr);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();


  //Act
  __str.assign(__str.data(), __str.length());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __cStr, __str.length()), 0);
}

TYPED_TEST(AssignTests, AssignIteratorsLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__ilist.begin(), __ilist.begin() +
    TestFixture::_localBufferLenThreshold);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), TestFixture::_localBufferLenThreshold);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), TestFixture::_localBufferLenThreshold), 0);
}

TYPED_TEST(AssignTests, AssignIteratorsLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__ilist.begin(), __ilist.begin() +
    TestFixture::_localBufferLenThreshold);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), TestFixture::_localBufferLenThreshold);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), TestFixture::_localBufferLenThreshold), 0);
}

TYPED_TEST(AssignTests, AssignIteratorsDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__ilist.begin(), __ilist.end());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignIteratorsDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  __str.assign(__ilist.begin(), __ilist.end());

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignListLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  std::initializer_list<value_type> __ilist = {'G', 'o'};
  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignListLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  TestFixture::LengthTest(__cStr);

  std::initializer_list<value_type> __ilist = {'G', 'o'};
  typename TestFixture::MyTestingString __str(__cStr);
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignListDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};

  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr,
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}

TYPED_TEST(AssignTests, AssignListDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;
  constexpr const value_type __cStr[] =
    {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', ' ', 'H', 'e', 'l',
     'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '\0'};
  std::initializer_list<value_type> __ilist =
    {'T', 'h', 'e', ' ', 'h', 'o', 'u', 's', 'e', ' ', 'o', 'f', ' ', 't', 'h',
      'e', ' ', 'r', 'i', 's', 'i', 'n', 'g', ' ', 's', 'u', 'n' };

  TestFixture::LengthTest(__cStr);
  TestFixture::LengthTest(__ilist.begin());

  typename TestFixture::MyTestingString __str(__cStr);

  //Act
  __str.assign(__ilist);

  //Assert
  EXPECT_FALSE(__str.empty());
  EXPECT_EQ(__str.length(), __ilist.size());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_EQ(TestingHelper::CustomStrCmp(__str.data(), __str.length(),
    __ilist.begin(), __ilist.size()), 0);
}
