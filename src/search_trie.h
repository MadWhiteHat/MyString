#ifndef _SEARCH_TRIE_H
#define _SEARCH_TRIE_H

// 1. Related headers
//------------------------------------None------------------------------------//

// 2. C system headers
//------------------------------------None------------------------------------//

// 3. C++ standard library headers
#include <unordered_map>
#include <vector>

// 4. Other libraries' .h files.
//------------------------------------None------------------------------------//

// 5. Your project's .h files.
#include "my_type_traits.h"
#include "my_string.h"

// Variables: lowerCamelCase
// Custom types: UpperCamelCsse
// New namess to builtin types: snake_case
// Custom function names: UpperCamelCase

namespace MyTypes {

template <typename CharT, typename StringClass = MyBasicString<CharT>>
class SearchTrie {
  static_assert(string_valid_type_v<CharT>);
 public:
  typedef typename StringClass::value_type value_type;

  SearchTrie() noexcept;
  SearchTrie(std::vector<const StringClass>& patterns) noexcept;

  void AddToTrie(const StringClass& str) noexcept;
  void IsStringInTrie(const StringClass& str) noexcept;

  size_t GetAutoMove(size_t v, value_type ch) noexcept;
  size_t GetSuffLink(size_t v) noexcept;
  size_t GetSuffFlink(size_t v) noexcept;

  void Check(std::vector<size_t>& pos, size_t vertex, 
             size_t idx) const noexcept;
  void FindAllPos(std::vector<size_t>& pos,
                  const StringClass& str) const noexcept;

 private:
  struct Vertex {
   public:
    Vertex(size_t pattern = -1, value_type sym = 0) noexcept;

    value_type symb;
    size_t parent;
    size_t patternNum;
    size_t suff_link;
    size_t suff_flink;
    bool bLeaf;
    std::unordered_map<CharT, size_t> nextVertex;
    std::unordered_map<CharT, size_t> autoMove;
  };

  std::vector<Vertex> trie_;
  std::vector<const StringClass> patterns;
  std::vector<size_t> pos;

};
} // namespace MyTypes

#endif // _SEARCH_TRIE_H