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

TYPED_TEST_SUITE(CompareTests, MyParamTypes);

TYPED_TEST(CompareTests, STLStringEQ) {
  //Arrange
  using value_type = typename  TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __str(__ilist);

  const std::basic_string<value_type> __cmp(__ilist);

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

  const std::basic_string<value_type> __cmp(__ilist2);

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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);

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

  const std::basic_string<value_type> __cmp(__ilist2);

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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
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

  const std::basic_string<value_type> __cmp(__ilist);
  const size_type __pos1 = __str.length() + 1;
  const size_type __count1 = __str.length();

  //Act

  //Assert
  EXPECT_THROW({
    auto __cmpRes = __str.compare(__pos1, __count1, __cmp.data());
  }, MyTypes::MyException);
}
