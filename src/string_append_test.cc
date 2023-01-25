#include <gtest/gtest.h>
#include <memory_resource>
#include <string>
#include <memory>
#include <tuple>
#include <type_traits>

#include "test_utils.h"
#include "my_exception.h"

template <typename _Tuple>
class AppendTests : public TestingHelper::StringTestingBase<_Tuple> {};

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

TYPED_TEST_SUITE(AppendTests, MyParamTypes);

TYPED_TEST(AppendTests, CharCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());
  size_type __count = TestFixture::_localBufferLenThreshold - __initLen;
  ADJUST_OUT(1, __count);
  ADJUST_IN(TestFixture::_localBufferLenThreshold - __initLen, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(), __initLen);
  __cmp.append(__count, __ch);

  //Act
  __str.append(__count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CharCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__count, __ch);

  //Act
  __str.append(__count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CharCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());
  size_type __count = 1;
  ADJUST_OUT(1, __count);

  std::basic_string<value_type> __cmp(__ilist);
  __cmp.append(__count, __ch);

  //Act
  __str.append(__count, __ch);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__other);

  //Act
  __str.append(__other);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__other);

  //Act
  __str.append(__other);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__other);

  //Act
  __str.append(__other);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, MyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__other.data());

  //Act
  __str.append(__other);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, MyStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__other.data());

  //Act
  __str.append(__other);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, MyStringDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__other.data());

  //Act
  __str.append(__other);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringPosCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__other, __pos, __count);

  //Act
  __str.append(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__other, __pos, __count);

  //Act
  __str.append(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringPosCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;


  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__other, __pos, __count);

  //Act
  __str.append(__other, __pos, __count);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, STLStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;


  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = __other.length() + 1;
  size_type __count = __other.length();

  //Act

  //Assert
  EXPECT_THROW({
    __str.append(__other, __pos, __count);
  }, MyTypes::MyException);
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(AppendTests, MyStringPosCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  const std::basic_string<value_type> __otherCmp(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__otherCmp, __pos, __count);

  //Act
  __str.append(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, MyStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__otherCmp, __pos, __count);

  //Act
  __str.append(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, MyStringPosCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;


  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);
  const std::basic_string<value_type> __otherCmp(__ilist2);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__otherCmp, __pos, __count);

  //Act
  __str.append(__other, __pos, __count);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, MyStringPosOut) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;


  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevData = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);
  size_type __pos = __other.length() + 1;
  size_type __count = __other.length();

  //Act

  //Assert
  EXPECT_THROW({
    __str.append(__other, __pos, __count);
  }, MyTypes::MyException);
  EXPECT_EQ(__str.data(), __prevData);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(AppendTests, CStrLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__other.data());

  //Act
  __str.append(__other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CStrLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__other.data());

  //Act
  __str.append(__other.data());

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CStrDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__other.data());

  //Act
  __str.append(__other.data());

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CStrCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__other.data() + __pos, __count);

  //Act
  __str.append(__other.data() + __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CStrCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__other.data() + __pos, __count);

  //Act
  __str.append(__other.data() + __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, CStrCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;


  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);
  size_type __pos = 1;
  size_type __count = __other.length();
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__other.data() + __pos, __count);

  //Act
  __str.append(__other.data() + __pos, __count);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, ItersRangeLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__other.begin(), __other.end());

  //Act
  __str.append(__other.begin(), __other.end());

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, ItersRangeLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__other.begin(), __other.end());

  //Act
  __str.append(__other.begin(), __other.end());

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, ItersRangeDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__other.begin(), __other.end());

  //Act
  __str.append(__other.begin(), __other.end());

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, ListLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp.append(__ilist2);

  //Act
  __str.append(__ilist2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, ListLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp.append(__ilist2);

  //Act
  __str.append(__ilist2);

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, ListDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp.append(__ilist2);

  //Act
  __str.append(__ilist2);

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorCharCountLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold - 1);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold - 1);
  __cmp += __ch;

  //Act
  __str += __ch;

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorCharCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp += __ch;

  //Act
  __str += __ch;

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorCharCountDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevCap = __str.capacity();

  const value_type __ch = *(__ilist.begin());

  std::basic_string<value_type> __cmp(__ilist);
  __cmp += __ch;

  //Act
  __str += __ch;

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorSTLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp += __other;

  //Act
  __str += __other;

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorSTLStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp += __other;

  //Act
  __str += __other;

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorSTLStringDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp += __other;

  //Act
  __str += __other;

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorMyStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp += __other.data();

  //Act
  __str += __other;

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorMyStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp += __other.data();

  //Act
  __str += __other;

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorMyStringDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const typename TestFixture::MyTestingString __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp += __other.data();

  //Act
  __str += __other;

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorCStrLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold - __initLen);

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp += __other.data();

  //Act
  __str += __other.data();

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorCStrLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp += __other.data();

  //Act
  __str += __other.data();

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorCStrDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  const std::basic_string<value_type> __other(__ilist2);

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp += __other.data();

  //Act
  __str += __other.data();

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorListLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  const size_type __initLen = TestFixture::_localBufferLenThreshold / 2;
  typename TestFixture::MyTestingString __str(__ilist1.begin(), __initLen);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist1.begin(), __initLen);
  __cmp += __ilist2;

  //Act
  __str += __ilist2;

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorListLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  __cmp += __ilist2;

  //Act
  __str += __ilist2;

  //Assert
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AppendTests, OperatorListDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  std::basic_string<value_type> __cmp(__ilist1);
  __cmp += __ilist2;

  //Act
  __str += __ilist2;

  //Assert
  EXPECT_GE(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}
