#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class FindTests : public TestingHelper::StringTestingBase<_Tuple> {};

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

TYPED_TEST_SUITE(FindTests, MyParamTypes);

TYPED_TEST(FindTests, STLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const std::basic_string<value_type> __other;

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const std::basic_string<value_type> __other(__str.data() + __pos);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other, __pos2);

  //Act
  auto __posStr = __str.find(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const typename TestFixture::MyTestingString __other(__str.data() + __pos);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const typename TestFixture::MyTestingString __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const typename TestFixture::MyTestingString __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos2, __other.length());

  //Act
  auto __posStr = __str.find(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other.data(), size_type(0), __other.length());

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0), __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other.data(), size_type(0), __other.length());

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0), __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), size_type(0), __other.length());

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0), __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const std::basic_string<value_type> __other(__str.data() + __pos);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos2, __other.length() / 2);

  //Act
  auto __posStr = __str.find(__other.data(), __pos2, __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const std::basic_string<value_type> __other(__str.data() + __pos);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos2);

  //Act
  auto __posStr = __str.find(__other.data(), __pos2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.find(__ch);

  //Act
  auto __posStr = __str.find(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__ch);

  //Act
  auto __posStr = __str.find(__ch);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = 0xff;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__ch);

  //Act
  auto __posStr = __str.find(__ch);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CharPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find(__ch, __pos);

  //Act
  auto __posStr = __str.find(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const std::basic_string<value_type> __other;

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp;
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other(__str.data(), __str.length() / 2);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other(__str.data(),
    __str.length() / 2);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const std::basic_string<value_type> __other(__str.data() + __pos);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length() / 2);

  //Act
  auto __posStr = __str.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length() / 2);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other.data(), size_type(0),
    __other.length() / 2);

  //Act
  auto __posStr = __str.rfind(__other.data(), size_type(0),
    __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other(__str.data());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other.data());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other.data());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__ch);

  //Act
  auto __posStr = __str.rfind(__ch);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const value_type __ch = 0xFF;

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__ch);

  //Act
  auto __posStr = __str.rfind(__ch);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const std::basic_string<value_type> __other(__str.data() + __pos, __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other, __pos2);

  //Act
  auto __posStr = __str.find_first_of(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const typename TestFixture::MyTestingString __other(__str.data() + __pos,
    __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);


  const typename TestFixture::MyTestingString __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const typename TestFixture::MyTestingString __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos2);

  //Act
  auto __posStr = __str.find_first_of(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const std::basic_string<value_type> __other(__str.data() + __pos, __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);


  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosOutCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos2, __str.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), __pos2, __str.length());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const std::basic_string<value_type> __other(__str.data() + __pos, __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);


  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos2);

  //Act
  auto __posStr = __str.find_first_of(__other.data(), __pos2);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);

}

TYPED_TEST(FindTests, FirstOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__ch);

  //Act
  auto __posStr = __str.find_first_of(__ch);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = 0xff;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__ch);

  //Act
  auto __posStr = __str.find_first_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCharPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__ch, __pos);

  //Act
  auto __posStr = __str.find_first_of(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other, __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const std::basic_string<value_type> __other(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosOutCount) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos1 = 1;
  ADJUST_OUT(1, __pos1);
  ADJUST_IN(__str.length() - 1, __pos1);
  const size_type __pos2 = __str.length() + 2;
  const std::basic_string<value_type> __other(__str.data() + __pos1);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos2,
    __str.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), __pos2,
    __str.length());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const std::basic_string<value_type> __other(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), __pos);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__ch);

  //Act
  auto __posStr = __str.find_first_not_of(__ch);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type __ch = 'a';

  const typename TestFixture::MyTestingString __str(size_type(17), __ch);

  const std::basic_string<value_type> __cmp(size_type(17), __ch);
  auto __posCmp = __cmp.find_first_not_of(__ch);

  //Act
  auto __posStr = __str.find_first_not_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCharPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__ch, __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const std::basic_string<value_type> __other(__str.data() + __pos, __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const typename TestFixture::MyTestingString __other(__str.data() + __pos,
    __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const std::basic_string<value_type> __other(__str.data() + __pos, __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data(), 
   TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(), 
   TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other.data(), 
   TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(), 
   TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  size_type __count = 2;
  ADJUST_IN(__str.length() - __pos, __count);
  const std::basic_string<value_type> __other(__str.data() + __pos, __count);

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const std::basic_string<value_type> __other(__ilist2);

  const std::basic_string<value_type> __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__ch);

  //Act
  auto __posStr = __str.find_last_of(__ch);

  //Assert
  EXPECT_NE(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = 0xff;

  const std::basic_string<value_type> __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__ch);

  //Act
  auto __posStr = __str.find_last_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, TestFixture::MyTestingString::npos);
  EXPECT_EQ(__posStr, __posCmp);
}
