// 1. Related headers
//------------------------------------None------------------------------------//

// 2. C system headers
//------------------------------------None------------------------------------//

// 3. C++ standard library headers
#include <iostream>
#include <vector>
#include <string>
// 4. Other libraries' .h files.
//------------------------------------None------------------------------------//

#define _AHO_CORASICK_SEARCH

// 5. Your project's .h files.
#include "my_string.h"
#include "search_trie.h"
// Variables: lowerCamelCase
// Custom types: UpperCamelCsse
// New namess to builtin types: snake_case
// Custom function names: UpperCamelCasd

int main(const int32_t, const char**) {
  std::string ms("hello worlod");
  std::vector<std::string> vs;
  vs.emplace_back("lo");
  MyTypes::PatternSearcher<std::string> pat(vs);
  auto res = pat(ms);
  std::cout << res.size();
  return 0;
}
