#pragma once
#include <map>
#include <unordered_map>
#include <vector>
#include <set>
#include <unordered_set>
#include <list>
#include <queue>

template<typename K, typename V>
using map = std::map<K, V, std::less<K>>;

template<typename K, typename V>
using multi_map = std::multimap<K, V, std::less<K>>;

template<typename K, typename V>
using unordered_map = std::unordered_map<K, V>;

template<typename K, typename V>
using unordered_multimap = std::unordered_multimap<K, V>;

template<typename K>
using set = std::set<K, std::less<K>>;

template<typename K>
using multi_set = std::multiset<K, std::less<K>>;

template<typename K>
using unordered_set = std::unordered_set<K>;

template<typename K>
using unordered_multiset = std::unordered_multiset<K>;

template<typename T>
using vector = std::vector<T>;

template<typename T>
using list = std::list<T>;

template<typename T>
using queue = std::queue<T>;