#include "search_trie.h"

#include <unordered_map>
#include <vector>

#include "my_string.h"

namespace MyTypes {
// Search Trie part

template <typename CharT, typename StringClass>
SearchTrie<CharT, StringClass>::SearchTrie() noexcept {
  trie_.push_back(Vertex());
}

template <typename CharT, typename StringClass>
SearchTrie<CharT, StringClass>::SearchTrie(
    std::vector<const StringClass>& patterns) noexcept : SearchTrie() {
  for (auto &pattern : patterns) { AddToTrie(pattern); }
}

template <typename CharT, typename StringClass>
void SearchTrie<CharT, StringClass>::AddToTrie(
    const StringClass& pattern) noexcept {
  if(IsStringInTrie(pattern)) { return; }
  size_t pos = 0;
  for (size_t i = 0; i < pattern.length(); ++i) {
    value_type key = pattern[i];
    if (!trie_[pos].nextVertex.count(key)) {
      trie_[pos].nextVertex[key] = trie_.size();
      trie_.push_back(Vertex());
    }
    pos = trie_[pos].nextVertex[key];
  }
  trie_[pos].bLeaf = true;
  patterns.push_back(std::move(pattern));
}

template <typename CharT, typename StringClass>
size_t SearchTrie<CharT, StringClass>::GetAutoMove(
    size_t vertex,
    typename SearchTrie::value_type ch) noexcept {
  if (!trie_[vertex].autoMove.count(ch)) {
    if (trie_[vertex].nextVertex.count(ch)) {
      trie_[vertex].autoMove[ch] = trie_[vertex].nextVertex[ch];
    } else if (vertex == 0) {
      trie_[vertex].autoMove[ch] = 0;
    } else {
      trie_[vertex].autoMove[ch] = GetAutoMove(GetSuffLink(vertex), ch);
    }
  }
  return trie_[vertex].autoMove[ch];
}

template <typename CharT, typename StringClass>
size_t SearchTrie<CharT, StringClass>::GetSuffLink(size_t vertex) noexcept {
  if (trie_[vertex].suff_link == -1) {
    trie_[vertex].suff_link = (vertex == 0 || trie_[vertex].parent == 0) ? 0 :
      GetAutoMove(GetSuffLink(trie_[vertex].parent), trie_[vertex].symb);
  }
  return trie_[vertex].suff_link;
}

template <typename CharT, typename StringClass>
size_t SearchTrie<CharT, StringClass>::GetSuffFlink(size_t vertex) noexcept {
  if (trie_[vertex].suff_flink == -1) {
    size_t u = GetSuffLink(vertex);
    if (u == 0) { trie_[vertex].suff_flink = 0; }
    else {
      trie_[vertex].suff_flink = trie_[vertex].bLeaf ? u : GetSuffFlink(u);
    }
  }
  return trie_[vertex].suff_flink;
}

template <typename CharT, typename StringClass>
void SearchTrie<CharT, StringClass>::Check(std::vector<size_t>& pos,
                              size_t vertex, size_t idx) const noexcept {
  for (int u = vertex; u != 0; u = GetSuffFlink(u)) {
    if (trie_[u].flag) {
      pos.push_back(idx - patterns[trie_[u].patternNum].length() + 1);
    }
  }
}

// Vertex part

template <typename CharT, typename StringClass>
SearchTrie<CharT, StringClass>::Vertex::Vertex(
    size_t parent,
    typename SearchTrie<CharT, StringClass>::value_type ch) noexcept
    : symb(ch),
      parent(parent),
      patternNum(-1),
      suff_link(-1),
      suff_link(-1),
      bLeaf(false) {}

}; // namespace MyTypes