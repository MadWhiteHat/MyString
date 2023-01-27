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
using TestingHelper::MyParamTypes;

TYPED_TEST_SUITE(FindTests, MyParamTypes);

TYPED_TEST(FindTests, STLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other, __pos);

  //Act
  auto __posStr = __str.find(__other, __pos);

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
  const typename TestFixture::STLString __other(__str.data() + __pos);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, STLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other);

  //Act
  auto __posStr = __str.find(__other);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos1);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other, __pos2);

  //Act
  auto __posStr = __str.find(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, MyStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos);

  //Act
  auto __posStr = __str.find(__other, __pos);

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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos2, __other.length());

  //Act
  auto __posStr = __str.find(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), size_type(0), __other.length());

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0), __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos, __other.length());

  //Act
  auto __posStr = __str.find(__other.data(), __pos, __other.length());

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
  const typename TestFixture::STLString __other(__str.data() + __pos);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Act
  auto __posStr = __str.find(__other.data(), size_type(0),
    __other.length() / 2);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos1);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos2, __other.length() / 2);

  //Act
  auto __posStr = __str.find(__other.data(), __pos2, __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos, __other.length());

  //Act
  auto __posStr = __str.find(__other.data(), __pos, __other.length());

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
  const typename TestFixture::STLString __other(__str.data() + __pos);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find(__other.data());

  //Act
  auto __posStr = __str.find(__other.data());

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos1);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__other.data(), __pos2);

  //Act
  auto __posStr = __str.find(__other.data(), __pos2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__ch);

  //Act
  auto __posStr = __str.find(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, CharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = 0xff;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__ch);

  //Act
  auto __posStr = __str.find(__ch);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find(__ch, __pos);

  //Act
  auto __posStr = __str.find(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
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

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other, __pos);

  //Act
  auto __posStr = __str.rfind(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__str.data(),
    __str.length() / 2);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other);

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(), __pos);

  //Act
  auto __posStr = __str.rfind(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other(__str.data(),
    __str.length() / 2);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrPosCountEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrPosCountEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrPosCountEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(), __pos, __other.length());

  //Act
  auto __posStr = __str.rfind(__other.data(), __pos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_OUT(1, __pos);
  ADJUST_IN(__str.length() - 1, __pos);
  const typename TestFixture::STLString __other(__str.data() + __pos);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length() / 2);

  //Act
  auto __posStr = __str.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other.data(), size_type(0),
    __other.length() / 2);

  //Act
  auto __posStr = __str.rfind(__other.data(), size_type(0),
    __other.length() / 2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.rfind(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data(), __pos);

  //Act
  auto __posStr = __str.rfind(__other.data(), __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__str.data());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__other.data());

  //Act
  auto __posStr = __str.rfind(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.rfind(__ch);

  //Act
  auto __posStr = __str.rfind(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.rfind(__ch);

  //Act
  auto __posStr = __str.rfind(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, ReverseCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const value_type __ch = 0xFF;

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.rfind(__ch);

  //Act
  auto __posStr = __str.rfind(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other, __pos);

  //Act
  auto __posStr = __str.find_first_of(__other, __pos);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos, __count);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other);

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos1);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other, __pos2);

  //Act
  auto __posStr = __str.find_first_of(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfMyStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_of(__other, __pos);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist1);
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos2);

  //Act
  auto __posStr = __str.find_first_of(__other, __pos2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosCountEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosCountEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrPosCountEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos, __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), __pos, __other.length());

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos, __count);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
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


  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), size_type(0),
    __other.length());

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos1);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos2, __str.length());

  //Act
  auto __posStr = __str.find_first_of(__other.data(), __pos2, __str.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCStrEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_of(__other.data(), __pos);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos, __count);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
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


  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_of(__other.data());

  //Act
  auto __posStr = __str.find_first_of(__other.data());

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos1);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__other.data(), __pos2);

  //Act
  auto __posStr = __str.find_first_of(__other.data(), __pos2);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);

}

TYPED_TEST(FindTests, FirstOfCharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_of(__ch);

  //Act
  auto __posStr = __str.find_first_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__ch);

  //Act
  auto __posStr = __str.find_first_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = 0xff;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__ch);

  //Act
  auto __posStr = __str.find_first_of(__ch);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_of(__ch, __pos);

  //Act
  auto __posStr = __str.find_first_of(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other, __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other);

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfSTLStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other, __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfMyStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos,
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), __pos,
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), size_type(0),
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosCountPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos,
    __other.length());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), __pos,
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data());

  //Act
  auto __posStr = __str.find_first_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCStrPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__other.data(), __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_first_not_of(__ch);

  //Act
  auto __posStr = __str.find_first_not_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__ch);

  //Act
  auto __posStr = __str.find_first_not_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, FirstNotOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type __ch = 'a';

  const typename TestFixture::MyTestingString __str(size_type(17), __ch);

  const typename TestFixture::STLString __cmp(size_type(17), __ch);
  auto __posCmp = __cmp.find_first_not_of(__ch);

  //Act
  auto __posStr = __str.find_first_not_of(__ch);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_first_not_of(__ch, __pos);

  //Act
  auto __posStr = __str.find_first_not_of(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other, __pos);

  //Act
  auto __posStr = __str.find_last_of(__other, __pos);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos, __count);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other);

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfMyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfMyStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfMyStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfMyStringEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_last_of(__other, __pos);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
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

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data(), __pos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(), __pos, __other.length());

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos, __count);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrEmptyStrPosLast) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length();
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_last_of(__other.data(), __pos);

  //Assert
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
  const typename TestFixture::STLString __other(__str.data() + __pos, __count);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {0x01, 0x02, 0x03, 0x04,
    0x05, 0x06, 0x07, 0x08}; 

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_of(__other.data());

  //Act
  auto __posStr = __str.find_last_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_of(__ch);

  //Act
  auto __posStr = __str.find_last_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__ch);

  //Act
  auto __posStr = __str.find_last_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = 0xff;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_of(__ch);

  //Act
  auto __posStr = __str.find_last_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other);

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other);

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other);

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other, __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_not_of(__other);

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other);

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfSTLStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other, __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::MyTestingString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfMyStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::MyTestingString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__other, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(), __pos,
    __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(), __pos,
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(),
    TestFixture::MyTestingString::npos, __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosCountPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(), __pos,
    __other.length());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(), __pos,
    __other.length());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrEmptyEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrEmptyStr) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrEmptyStrPosFirst) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = 0;
  const typename TestFixture::STLString __other;

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(), __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __other(__ilist2);

  const typename TestFixture::STLString __cmp(__ilist1);
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data());

  //Act
  auto __posStr = __str.find_last_not_of(__other.data());

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCStrPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const typename TestFixture::STLString __other(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__other.data(), __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__other.data(), __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCharEmpty) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str;

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp;
  auto __posCmp = __cmp.find_last_not_of(__ch);

  //Act
  auto __posStr = __str.find_last_not_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCharFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__ch);

  //Act
  auto __posStr = __str.find_last_not_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCharNotFound) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const value_type __ch = 'a';

  const typename TestFixture::MyTestingString __str(size_type(17), __ch);

  const typename TestFixture::STLString __cmp(size_type(17), __ch);
  auto __posCmp = __cmp.find_last_not_of(__ch);

  //Act
  auto __posStr = __str.find_last_not_of(__ch);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}

TYPED_TEST(FindTests, LastNotOfCharPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const size_type __pos = __str.length() + 2;
  const value_type __ch = *(__ilist.begin());

  const typename TestFixture::STLString __cmp(__ilist);
  auto __posCmp = __cmp.find_last_not_of(__ch, __pos);

  //Act
  auto __posStr = __str.find_last_not_of(__ch, __pos);

  //Assert
  EXPECT_EQ(__posStr, __posCmp);
}
