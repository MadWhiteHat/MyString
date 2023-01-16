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
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist.begin(),
       TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignOperatorMyStringDynamic) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  const typename TestFixture::MyTestingString __other(__ilist);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignOperatorSTLStringLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const std::basic_string<value_type> __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignOperatorSTLStringDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  const std::basic_string<value_type> __other(__ilist);
  typename TestFixture::MyTestingString __str;

  //Act
  __str = __other;

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringLocalToLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;

  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);

}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringDynamicToLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist);
  typename TestFixture::MyTestingString __str;

  auto __prevDataPtr = __other.data();
  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringLocalToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringDyncamicToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;


  typename TestFixture::MyTestingString __str(__ilist1);
  typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevLen = __other.length();

  //Act
  __str = std::move(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignOperatorMyStringSelf) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str = std::move(__str);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());

}

TYPED_TEST(AssignTests, AssignOperatorCStrLocalToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str = __other.data();

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignOperatorCStrLocalToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  //Act
  __str = __other.data();

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignOperatorCStrDynamicToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str = __ilist2.begin();

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __str.length());
}

TYPED_TEST(AssignTests, AssignOperatorCStrDynamicToDynamicWORealloc) {
  //Arrange
  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il1 : __il2;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevDataPtr = __str.data();

  //Act
  __str = __ilist2.begin();

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignOperatorCStrLocalSelf) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __pos = 1;
  ADJUST_POS_LOCAL(__str.length(), __pos);

  const typename TestFixture::MyTestingString __cmp(__str.data() + __pos);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();

  //Act
  __str = __str.data() + __pos;

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignOperatorCStrDynamicSelf) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_POS_DYNAMIC(__str.length(), __pos);

  const typename TestFixture::MyTestingString __cmp(__str.data() + __pos);

  auto __prevDataPtr = __str.data();

  //Act
  __str = __str.data() + __pos;

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignOperatorCharToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  typename TestFixture::MyTestingString __str;
  const value_type __ch = *(TestFixture::_str1.begin());

  //Act
  __str = __ch;

  //Assert
  EXPECT_EQ(__str.length(), 1);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, AssignOperatorCharToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevDataPtr = __str.data();
  auto __prevCap = __str.capacity();
  const value_type __ch = 'a';

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

  const auto __ilist1 = TestFixture::_str1;
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};
  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str = __ilist2;

  //Assert
  EXPECT_EQ(__str.length(), __ilist2.size());
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignOperatorListLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  std::initializer_list<value_type> __ilist2 = {'G', 'o'};
  typename TestFixture::MyTestingString __str(__ilist1);

  auto __prevCap = __str.capacity();

  //Act
  __str = __ilist2;

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignOperatorListDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str = __ilist2;

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignOperatorListDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  //Act
  __str = __ilist2;

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignCharsLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;
  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  const value_type __ch = *(__ilist.begin());

  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_IN(TestFixture::_localBufferLenThreshold, __count);

  const typename TestFixture::MyTestingString __cmp(__count, __ch);

  //Act
  __str.assign(__count, __ch);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignCharsDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  const value_type __ch = *(__ilist.begin());

  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold + 1, __count);

  const typename TestFixture::MyTestingString __cmp(__count, __ch);

  //Act
  __str.assign(__count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignCharsLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);
  const value_type __ch = *(__ilist.begin());

  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_IN(TestFixture::_localBufferLenThreshold, __count);

  const typename TestFixture::MyTestingString __cmp(__count, __ch);

  //Act
  __str.assign(__count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignCharsDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);
  const value_type __ch = *(__ilist.begin());

  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_OUT(TestFixture::_localBufferLenThreshold + 1, __count);

  const typename TestFixture::MyTestingString __cmp(__count, __ch);

  //Act
  __str.assign(__count, __ch);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignMyStringLocalToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringDynamicToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringLocalToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringDynamicToDynamicWORealloc) {
  //Arrange
  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il1 : __il2;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringDynamicToDynamicRealloc) {
  //Arrange
  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il2 : __il1;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringSelf) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__str);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
}

TYPED_TEST(AssignTests, AssignSTLStringLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignSTLStringDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __other(__ilist2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignSTLStringLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignSTLStringDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il1 : __il2;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignSTLStringDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il2 : __il1;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  //Act
  __str.assign(__other);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountLocalToLocal) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold;
  size_type __pos = 1;

  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  const typename TestFixture::MyTestingString __cmp(__other, __pos, __count);

  //Act
  __str.assign(__other, __pos, __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountDynamicToLocal) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  size_type __pos = 1;

  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  const typename TestFixture::MyTestingString __cmp(__other, __pos, __count);

  //Act
  __str.assign(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountLocalToDynamic) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  typename TestFixture::MyTestingString __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold;
  size_type __pos = 1;

  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  const typename TestFixture::MyTestingString __cmp(__other, __pos, __count);

  //Act
  __str.assign(__other, __pos, __count);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountDynamicToDynamicWORealloc) {
  //Arrange
  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il1 : __il2;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountDynamicToDynamicRealloc) {
  //Arrange
  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il2 : __il1;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountPosOutside) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);

  size_type __pos = __other.length() + 1;
  ADJUST_OUT(__other.length() + 1, __pos);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  EXPECT_THROW({
    __str.assign(__other, __pos);
  }, MyTypes::MyException);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(AssignTests, AssignMyStringPosCountSelf) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_POS_DYNAMIC(__str.length(), __pos);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  typename TestFixture::MyTestingString __cmp(__str, __pos);

  //Act
  __str.assign(__str, __pos);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold;
  size_type __pos = 1;
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  const std::basic_string<value_type> __cmp(__other, __pos, __count);

  //Act
  __str.assign(__other, __pos, __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  size_type __pos = 1;
  ADJUST_POS_COUNT_DYNAMIC(__other.length(), __pos, __count);

  const std::basic_string<value_type> __cmp(__other, __pos, __count);

  //Act
  __str.assign(__other, __pos, __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold;
  size_type __pos = 1;
  ADJUST_POS_COUNT_LOCAL(__other.length(), __pos, __count);

  const std::basic_string<value_type> __cmp(__other, __pos, __count);

  //Act
  __str.assign(__other, __pos, __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data() + __pos);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountDynamicToDynamicWORealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il1 : __il2;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountDynamicToDynamicRealloc) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il2 : __il1;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other, 0);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignSTLStringPosCountPosOutside) {
  //Arrange
  using value_type = typename TestFixture::value_type;
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  size_type __pos = __other.length() + 1;
  ADJUST_OUT(__other.length() + 1, __pos);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  EXPECT_THROW({
    __str.assign(__other, __pos);
  }, MyTypes::MyException);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist1.begin(),
    __ilist1.size());
}

TYPED_TEST(AssignTests, MoveAssignMyStringLocalToLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);
  typename TestFixture::MyTestingString __str;

  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __str.length());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);

}

TYPED_TEST(AssignTests, MoveAssignMyStringDynamicToLocal) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __other(__ilist);
  typename TestFixture::MyTestingString __str;

  auto __prevDataPtr = __other.data();
  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignMyStringLocalToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __str.length());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignMyStringDyncamicToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist2);
  typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevLen = __other.length();

  //Act
  __str.assign(std::move(__other));

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());

  EXPECT_TRUE(__other.empty());
  EXPECT_EQ(__other.capacity(), TestFixture::_localBufferCapThreshold);
}

TYPED_TEST(AssignTests, MoveAssignMyStringSelf) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(std::move(__str));

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(AssignTests, AssignCStrLocalToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignCStrLocalToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other.data());

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignCStrDynamicToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2);

  //Act
  __str.assign(__other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignCStrDynamicToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);

  auto __prevDataPtr = __str.data();

  //Act
  __str.assign(__other.data());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignCStrLocalSelf) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __pos = 1;
  ADJUST_POS_LOCAL(__str.length(), __pos);

  const typename TestFixture::MyTestingString __cmp(__str.data() + __pos);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();

  //Act
  __str.assign(__str.data() + __pos);

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignCStrDynamicSelf) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  size_type __pos = 1;
  ADJUST_POS_DYNAMIC(__str.length(), __pos);

  const typename TestFixture::MyTestingString __cmp(__str.data() + __pos);

  //Act
  __str.assign(__str.data() + __pos);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __cmp.data(),
    __cmp.length());
}

TYPED_TEST(AssignTests, AssignCStrCountLocalToLocal) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_IN(__other.length(), __count);

  //Act
  __str.assign(__other.data(), __count);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __str.length());
}

TYPED_TEST(AssignTests, AssignCStrCountDynamicToLocal) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const typename TestFixture::MyTestingString __other(__ilist2);

  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_IN(__other.length(), __count);

  //Act
  __str.assign(__other.data(), __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.length(), __count);
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __str.length());
}

TYPED_TEST(AssignTests, AssignCStrCountLocalToDynamic) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  size_type __count = TestFixture::_localBufferLenThreshold;
  ADJUST_IN(__other.length(), __count);

  //Act
  __str.assign(__other.data(), __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignCStrCountDynamicToDynamicWORealloc) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  // guarantee no realloc
  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il1 : __il2;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);
  
  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_IN(__other.length(), __count);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other.data(), __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(), __count);
}

TYPED_TEST(AssignTests, AssignCStrCountDynamicToDynamicRealloc) {
  //Arrange
  using size_type = typename TestFixture::size_type;

  const auto __il1 = TestFixture::_str1;
  const auto __il2 = TestFixture::_str2;

  const auto __ilist1 = (__il1.size() > __il2.size()) ? __il2 : __il1;
  const auto __ilist2 = (__il1.begin() == __ilist1.begin()) ? __il2 : __il1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const typename TestFixture::MyTestingString __other(__ilist2);
  
  size_type __count = TestFixture::_localBufferLenThreshold + 1;
  ADJUST_IN(__other.length(), __count);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other.data(), __count);

  //Assert
  EXPECT_NE(__str.data(), __other.data());
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(), __count);
}

TYPED_TEST(AssignTests, AssignCStrCountSelf) {
  //Arrange
  const auto __ilist = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist);

  auto __prevDataPtr = __str.data();
  auto __prevLen = __str.length();
  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__str.data(), __str.length());

  //Assert
  EXPECT_EQ(__str.data(), __prevDataPtr);
  EXPECT_EQ(__str.length(), __prevLen);
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist.begin(),
    __ilist.size());
}

TYPED_TEST(AssignTests, AssignIteratorsLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__other.begin(), __other.end());

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignIteratorsLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2.begin(),
    TestFixture::_localBufferLenThreshold);

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__other.begin(), __other.end());

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignIteratorsDynamicToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::basic_string<value_type> __other(__ilist2);

  //Act
  __str.assign(__other.begin(), __other.end());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignIteratorsDynamicToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::basic_string<value_type> __other(__ilist2);

  //Act
  __str.assign(__other.begin(), __other.end());

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __other.data(),
    __other.length());
}

TYPED_TEST(AssignTests, AssignListLocalToLocal) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  //Act
  __str.assign(__ilist2);

  //Assert
  EXPECT_EQ(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignListLocalToDynamic) {
  //Arrange
  using value_type = typename TestFixture::value_type;

  const auto __ilist1 = TestFixture::_str1;

  typename TestFixture::MyTestingString __str(__ilist1);
  const std::initializer_list<value_type> __ilist2 = {'G', 'o'};

  auto __prevCap = __str.capacity();

  //Act
  __str.assign(__ilist2);

  //Assert
  EXPECT_EQ(__str.capacity(), __prevCap);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignListDynamicToLocal) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1.begin(),
    TestFixture::_localBufferLenThreshold);

  //Act
  __str.assign(__ilist2);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}

TYPED_TEST(AssignTests, AssignListDynamicToDynamic) {
  //Arrange
  const auto __ilist1 = TestFixture::_str1;
  const auto __ilist2 = TestFixture::_str2;

  typename TestFixture::MyTestingString __str(__ilist1);

  //Act
  __str.assign(__ilist2);

  //Assert
  EXPECT_GT(__str.capacity(), TestFixture::_localBufferCapThreshold);
  EXPECT_STREQ_CUSTOM(__str.data(), __str.length(), __ilist2.begin(),
    __ilist2.size());
}
