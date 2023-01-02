#include <iostream>
#include <limits>

#include "test_utils.h"

int
TestingHelper::
_CompareHelper(size_t __count1, size_t __count2) {
  using __limits = std::numeric_limits<int>;
  const std::ptrdiff_t __diff = __count1 - __count2;
  if (__diff > __limits::max()) {
    return __limits::max();
  } else if (__diff < __limits::min()) {
    return __limits::min();
  }
  return static_cast<int>(__diff);
}

