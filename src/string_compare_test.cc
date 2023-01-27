#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class CompareTests : public TestingHelper::StringTestingBase<_Tuple> {};
using TestingHelper::MyParamTypes;

TYPED_TEST_SUITE(CompareTests, MyParamTypes);

TYPED_TEST(CompareTests, STLStringEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);

  //Act
  auto __cmpRes = __str.compare(__cmp);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __cmp(__ilist2);

  //Act
  auto __cmpRes = __str.compare(__cmp);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);

  //Act
  auto __cmpRes = __str.compare(__cmp);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::MyTestingString __cmp(__ilist2);

  //Act
  auto __cmpRes = __str.compare(__cmp);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosCountEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosCountLessThanLengthNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length() / 2;

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosShiftedCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 1;
  const size_type __count1 = __str.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosOutCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, MyStringPosCountEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringPosCountLessThanLengthNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length() / 2;

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringPosShiftedCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 1;
  const size_type __count1 = __str.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringPosOutCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, STLStringPosCountStrPosStrCountEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 5;
  const size_type __count1 = __str.length();
  const size_type __pos2 = __pos1;
  const size_type __count2 = __count1;

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosCountLessThanLengthStrPosStrCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length() / 2;
  const size_type __pos2 = __pos1;
  const size_type __count2 = __cmp.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosShiftedCountStrPosStrCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 1;
  const size_type __count1 = __str.length();
  const size_type __pos2 = 0;
  const size_type __count2 = __cmp.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, STLStringPosOutCountStrPosStrCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();
  const size_type __pos2 = 0;
  const size_type __count2 = __cmp.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, STLStringPosCountStrPosOutStrCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length();
  const size_type __pos2 = __cmp.length() + 1;
  const size_type __count2 = __cmp.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, MyStringPosCountStrPosStrCountEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 5;
  const size_type __count1 = __str.length();
  const size_type __pos2 = __pos1;
  const size_type __count2 = __count1;

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringPosCountLessThanLengthStrPosStrCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length() / 2;
  const size_type __pos2 = __pos1;
  const size_type __count2 = __cmp.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringPosShiftedCountStrPosStrCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 1;
  const size_type __count1 = __str.length();
  const size_type __pos2 = 0;
  const size_type __count2 = __cmp.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, MyStringPosOutCountStrPosStrCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();
  const size_type __pos2 = 0;
  const size_type __count2 = __cmp.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, MyStringPosCountStrPosOutStrCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::MyTestingString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length();
  const size_type __pos2 = __cmp.length() + 1;
  const size_type __count2 = __cmp.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp, __pos2, __count2);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, CStrEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);

  //Act
  auto __cmpRes = __str.compare(__cmp.data());

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str(__ilist1);

  const typename TestFixture::STLString __cmp(__ilist2);

  //Act
  auto __cmpRes = __str.compare(__cmp.data());

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosCountStrCountEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 5;
  const size_type __count1 = __str.length();
  const size_type __pos2 = __pos1;
  const size_type __count2 = __count1;

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data() + __pos2,
    __cmp.length() - __pos2);

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosCountLessThanLengthStrStrCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length() / 2;
  const size_type __pos2 = __pos1;
  const size_type __count2 = __cmp.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data() + __pos2,
    __count2);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosShiftedCountStrCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 1;
  const size_type __count1 = __str.length();
  const size_type __pos2 = 0;
  const size_type __count2 = __cmp.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data() +  __pos2,
    __count2);

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosOutCountStrPosStrCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();
  const size_type __pos2 = 0;
  const size_type __count2 = __cmp.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data() +  __pos2,
      __count2);
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, CStrPosCountEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data());

  //Assert
  EXPECT_TRUE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosCountLessThanLengthNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 0;
  const size_type __count1 = __str.length() / 2;

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data());

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosShiftedCountNE) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = 1;
  const size_type __count1 = __str.length();

  //Act
  auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data());

  //Assert
  EXPECT_FALSE(!bool(__cmpRes));
}

TYPED_TEST(CompareTests, CStrPosOutCount) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const typename TestFixture::STLString __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data());
  }, MyTypes::MyException);
}

TYPED_TEST(CompareTests, OperatorLessMyStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 < __cmp2;

  //Act
  auto __resStr = __str1 < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessMyStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 < __cmp2;

  //Act
  auto __resStr = __str1 < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterMyStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 > __cmp2;

  //Act
  auto __resStr = __str1 > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterMyStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 > __cmp2;

  //Act
  auto __resStr = __str1 > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualMyStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 != __cmp2;

  //Act
  auto __resStr = __str1 != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualMyStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 != __cmp2;

  //Act
  auto __resStr = __str1 != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualMyStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 == __cmp2;

  //Act
  auto __resStr = __str1 == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualMyStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 == __cmp2;

  //Act
  auto __resStr = __str1 == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualMyStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 <= __cmp2;

  //Act
  auto __resStr = __str1 <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualMyStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 <= __cmp2;

  //Act
  auto __resStr = __str1 <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualMyStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 >= __cmp2;

  //Act
  auto __resStr = __str1 >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualMyStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 >= __cmp2;

  //Act
  auto __resStr = __str1 >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessMyStringSTLStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 < __cmp2;

  //Act
  auto __resStr = __str1 < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessMyStringSTLStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 < __cmp2;

  //Act
  auto __resStr = __str1 < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterMyStringSTLStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 > __cmp2;

  //Act
  auto __resStr = __str1 > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterMyStringSTLStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 > __cmp2;

  //Act
  auto __resStr = __str1 > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualMyStringSTLStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 != __cmp2;

  //Act
  auto __resStr = __str1 != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualMyStringSTLStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 != __cmp2;

  //Act
  auto __resStr = __str1 != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualMyStringSTLStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 == __cmp2;

  //Act
  auto __resStr = __str1 == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualMyStringSTLStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 == __cmp2;

  //Act
  auto __resStr = __str1 == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualMyStringSTLStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 <= __cmp2;

  //Act
  auto __resStr = __str1 <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualMyStringSTLStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 <= __cmp2;

  //Act
  auto __resStr = __str1 <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualMyStringSTLStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 >= __cmp2;

  //Act
  auto __resStr = __str1 >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualMyStringSTLStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 >= __cmp2;

  //Act
  auto __resStr = __str1 >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessSTLStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 < __cmp2;

  //Act
  auto __resStr = __str1 < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessSTLStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 < __cmp2;

  //Act
  auto __resStr = __str1 < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterSTLStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 > __cmp2;

  //Act
  auto __resStr = __str1 > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterSTLStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 > __cmp2;

  //Act
  auto __resStr = __str1 > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualSTLStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 != __cmp2;

  //Act
  auto __resStr = __str1 != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualSTLStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 != __cmp2;

  //Act
  auto __resStr = __str1 != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualSTLStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 == __cmp2;

  //Act
  auto __resStr = __str1 == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualSTLStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 == __cmp2;

  //Act
  auto __resStr = __str1 == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualSTLStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 <= __cmp2;

  //Act
  auto __resStr = __str1 <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualSTLStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 <= __cmp2;

  //Act
  auto __resStr = __str1 <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualSTLStringMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 >= __cmp2;

  //Act
  auto __resStr = __str1 >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualSTLStringMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 >= __cmp2;

  //Act
  auto __resStr = __str1 >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessMyStringCStrSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 < __cmp2.data();

  //Act
  auto __resStr = __str1 < __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessMyStringCStrDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 < __cmp2.data();

  //Act
  auto __resStr = __str1 < __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterMyStringCStrSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 > __cmp2.data();

  //Act
  auto __resStr = __str1 > __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterMyStringCStrDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 > __cmp2.data();

  //Act
  auto __resStr = __str1 > __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualMyStringCStrSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 != __cmp2.data();

  //Act
  auto __resStr = __str1 != __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualMyStringCStrDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 != __cmp2.data();

  //Act
  auto __resStr = __str1 != __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualMyStringCStrSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 == __cmp2.data();

  //Act
  auto __resStr = __str1 == __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualMyStringCStrDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 == __cmp2.data();

  //Act
  auto __resStr = __str1 == __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualMyStringCStrSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 <= __cmp2.data();

  //Act
  auto __resStr = __str1 <= __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualMyStringCStrDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 <= __cmp2.data();

  //Act
  auto __resStr = __str1 <= __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualMyStringCStrSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str1(__ilist);
  const typename TestFixture::STLString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1 >= __cmp2.data();

  //Act
  auto __resStr = __str1 >= __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualMyStringCStrDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::MyTestingString __str1(__ilist1);
  const typename TestFixture::STLString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1 >= __cmp2.data();

  //Act
  auto __resStr = __str1 >= __str2.data();

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessCStrMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1.data() < __cmp2;

  //Act
  auto __resStr = __str1.data() < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessCStrMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1.data() < __cmp2;

  //Act
  auto __resStr = __str1.data() < __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterCStrMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1.data() > __cmp2;

  //Act
  auto __resStr = __str1.data() > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterCStrMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1.data() > __cmp2;

  //Act
  auto __resStr = __str1.data() > __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualCStrMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1.data() != __cmp2;

  //Act
  auto __resStr = __str1.data() != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorNotEqualCStrMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1.data() != __cmp2;

  //Act
  auto __resStr = __str1.data() != __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualCStrMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1.data() == __cmp2;

  //Act
  auto __resStr = __str1.data() == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorEqualCStrMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1.data() == __cmp2;

  //Act
  auto __resStr = __str1.data() == __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualCStrMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1.data() <= __cmp2;

  //Act
  auto __resStr = __str1.data() <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorLessEqualCStrMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1.data() <= __cmp2;

  //Act
  auto __resStr = __str1.data() <= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualCStrMyStringSameStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::STLString __str1(__ilist);
  const typename TestFixture::MyTestingString __str2(__ilist);

  const typename TestFixture::STLString __cmp1(__ilist);
  const typename TestFixture::STLString __cmp2(__ilist);
  auto __resCmp = __cmp1.data() >= __cmp2;

  //Act
  auto __resStr = __str1.data() >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}

TYPED_TEST(CompareTests, OperatorGreaterEqualCStrMyStringDiffStr) {
  //Arrange
  using value_type = typename  TestFixture::value_type;
  
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const typename TestFixture::STLString __str1(__ilist1);
  const typename TestFixture::MyTestingString __str2(__ilist2);

  const typename TestFixture::STLString __cmp1(__ilist1);
  const typename TestFixture::STLString __cmp2(__ilist2);
  auto __resCmp = __cmp1.data() >= __cmp2;

  //Act
  auto __resStr = __str1.data() >= __str2;

  //Assert
  EXPECT_EQ(__resStr, __resCmp);
}
