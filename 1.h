// To do:
// 2. check Check func correctness
// 3. impl call methods


#ifndef _SEARCH_H
#define _SEARCH_H

// 1. Related headers
//------------------------------------None------------------------------------//

// 2. C system headers
//------------------------------------None------------------------------------//

// 3. C++ standard library headers
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>
// 4. Other libraries' .h files.
//------------------------------------None------------------------------------//

// 5. Your project's .h files.
#include "custom_traits.h"

// Variables: lowerCamelCase
// Custom types: UpperCamelCsse
// New namess to builtin types: snake_case
// Custom function names: UpperCamelCase

namespace MyTypes {

template <typename _String,
          typename _EqComparator = std::equal_to<typename _String::value_type>>
class PatternSearcher {
  using value_type = typename _String::value_type;
  static_assert(__custom_traits::_StringValidTypeV<value_type>,
    "Invalid template parameter _CharT." 
    " Valid types: char, wchar_t, char16_t, char32_t"
#if __cplusplus > 201703L
     ", char8_t"
#endif
  );

  using string_type = _String;
  using const_pointer = typename _String::const_pointer;
  using size_type = size_t;
  using pos_type = typename _String::size_type;

  const size_type npos = static_cast<size_type>(-1);

 public:
  PatternSearcher();
  PatternSearcher(const std::vector<string_type>& __patterns);

  void AddToTrie(const string_type& __pattern);

  // std::pair<pattern_num, pos>
  std::vector<std::pair<size_type, pos_type>> operator()(
    const string_type& __word);

  std::vector<std::pair<size_type, pos_type>> operator()(const_pointer __word)
  const;

 private:

  bool _IsStringInTrie(const string_type& __pattern) const noexcept {
    size_type __vertex = 0;
    for (pos_type i = 0; i < __pattern.length(); ++i) {
      value_type __ch = __pattern[i];
      if (!_trie[__vertex]._nextVertex.count(__ch)) {
        return false;
      }
      __vertex = _trie[__vertex]._nextVertex.at(__ch);
    }
    return true;
  }

  size_type _GetAutoMove(size_type __vertex, value_type __ch) {
    
    if (!_trie[__vertex]._autoMove.count(__ch)) {
      if (_trie[__vertex]._nextVertex.count(__ch)) {
        _trie[__vertex]._autoMove[__ch] = _trie[__vertex]._nextVertex[__ch];
      } else if (__vertex == 0) {
        _trie[__vertex]._autoMove[__ch] = 0;
      } else {
        _trie[__vertex]._autoMove[__ch] = _GetAutoMove(_GetSuffLink(__vertex),
          __ch);
      }
    }
    return _trie[__vertex]._autoMove[__ch]; 
  }

  size_type _GetSuffLink(size_type __vertex) {
    if (_trie[__vertex]._suffLink == size_type(-1)) {
      if (__vertex == 0 || _trie[__vertex]._parent == 0) {
        _trie[__vertex]._suffLink = 0;
      } else {
        _trie[__vertex]._suffLink = _GetAutoMove(
          _GetSuffLink(_trie[__vertex]._parent),
          _trie[__vertex]._sym);
      }
    }
    return _trie[__vertex]._suffLink;
  }

  size_type _GetSuffFlink(size_type __vertex) {
    if (_trie[__vertex]._suffFlink == size_type(-1)) {
      size_type __u = _GetSuffLink(__vertex);
      if (__u == 0) { _trie[__vertex]._suffFlink = 0; }
      else {
        _trie[__vertex]._suffFlink = _trie[__vertex]._isLeaf ?
        __u :
        _GetSuffFlink(__u);
      }
    }
    return _trie[__vertex]._suffFlink;
  }

  std::pair<size_type, pos_type>
  _Check(size_type __vertex, size_type __idx) {
    for (size_type __u = __vertex; __u != 0; __u = _GetSuffFlink(__u)) {
      if (_trie[__u]._isLeaf) {
        return std::pair<size_type, pos_type>(
          _trie[__u]._patternNum,
          __idx - _patterns[_trie[__u]._patternNum].get().length());
      }
    }
    return std::pair<size_type, pos_type>(npos, npos);
  }

  struct SortCompare {
    bool operator()(const std::pair<size_type, pos_type>& __lhs,
      const std::pair<size_type, pos_type>& __rhs) {
      return __lhs.second < __rhs.second;
    }
  };

  struct _Vertex {

    _Vertex(size_type __parent = -1, value_type __sym = 0)
      : _nextVertex(),
        _autoMove(),
        _parent(__parent),
        _patternNum(-1),
        _suffLink(-1),
        _suffFlink(-1),
        _sym(__sym),
        _isLeaf(false) {} 

    // For custom equality checker; e.g case-insensive check
    std::unordered_map<value_type, size_type,
      std::hash<value_type>, _EqComparator> _nextVertex;
    std::unordered_map<value_type, size_type,
      std::hash<value_type>, _EqComparator> _autoMove;
    size_type _parent;
    size_type _patternNum;
    size_type _suffLink;
    size_type _suffFlink;
    value_type _sym;
    bool _isLeaf;
  };

  std::vector<_Vertex> _trie;
  std::vector<std::reference_wrapper<const string_type>> _patterns;
};

template <typename _String, typename _EqComparator>
PatternSearcher<_String, _EqComparator>::
PatternSearcher() {
  _trie.push_back(_Vertex());
}

template <typename _String, typename _EqComparator>
PatternSearcher<_String, _EqComparator>::
PatternSearcher(const std::vector<string_type>& __patterns)
    : PatternSearcher() {
  for (const auto& __pattern : __patterns) { AddToTrie(__pattern); }
}

template <typename _String, typename _EqComparator>
void
PatternSearcher<_String, _EqComparator>::
AddToTrie(const string_type& __pattern) {
  if(_IsStringInTrie(__pattern)) { return; }
  size_type __pos = 0;
  for (pos_type i = 0; i < __pattern.length(); ++i) {
   value_type __ch = __pattern[i];
    if (!_trie[__pos]._nextVertex.count(__ch)) {
      _trie[__pos]._nextVertex[__ch] = _trie.size();
      _trie.push_back(_Vertex(__pos, __ch));
    }
    __pos = _trie[__pos]._nextVertex[__ch];
  }
  _patterns.push_back(__pattern);
  _trie[__pos]._isLeaf = true;
  _trie[__pos]._patternNum = _patterns.size() - 1;
}

template <typename _String, typename _EqComparator>
std::vector<std::pair<
  typename PatternSearcher<_String, _EqComparator>::size_type,
  typename PatternSearcher<_String, _EqComparator>::pos_type>>
PatternSearcher<_String, _EqComparator>::
operator()(const string_type&__word) {
  std::vector<std::pair<size_type, pos_type>> __res;
  size_type __u = 0;
  for (pos_type __idx = 0; __idx < __word.length(); ++__idx) {
    __u = _GetAutoMove(__u, __word[__idx]);
    auto __resPair = _Check(__u, __idx + 1);
    if (__resPair.second != npos) {
      __res.push_back(std::move(__resPair));
    }
  }
  std::sort(__res.begin(), __res.end(), SortCompare{});
  return __res;
}

} // namespace MyTypes

#endif // _SEARCH_H
