#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include "hashtable.h"

using namespace std;
using namespace cop4530;

//------------------------------------------------
// ========== Constructors & Destructors =========
//------------------------------------------------

// Constructor. Create a hash table, where the size of the vector is set to prime_below(size) 
// (where size is default  to 101), where prime_below() is a private member function of the 
// HashTable and provided to you.
template <typename K, typename V>
  HashTable<K, V>::HashTable(size_t size) : table(prime_below(size)), currentSize(0) {}

// Destructor. Delete all elements in hash table.
template <typename K, typename V>
  HashTable<K, V>::~HashTable() {
      clear();
  }

//------------------------------------------------
// =========== Public Member functions ===========
//------------------------------------------------

// Check if key k is in the hash table.
template <typename K, typename V>
  bool HashTable<K, V>::contains(const K &k) const {
      auto &list = table[myhash(k)];
      return std::any_of(list.begin(), list.end(), [&k](const auto &item) {
          return item.first == k;
      });
  }

// Check if key-value pair is in the hash table.
template <typename K, typename V>
  bool HashTable<K, V>::match(const std::pair<K, V> &kv) const {
      auto &list = table[myhash(kv.first)];
      return std::any_of(list.begin(), list.end(), [&kv](const auto &item) {
          return item == kv;
      });
  }

// Add the key-value pair kv into the hash table. Don't add if kv is already in the hash table. 
// If the key is the hash table but with a different value, the value should be updated to the 
// new one with kv. Return true if kv is inserted or the value is updated; return false otherwise 
// (i.e., if kv is in the hash table).
template <typename K, typename V>
  bool HashTable<K, V>::insert(const std::pair<K, V> &kv) {
      auto &list = table[myhash(kv.first)];
      for (auto &item : list) {
          if (item.first == kv.first) {
              item.second = kv.second;
              return true;
          }
      }
      list.push_back(kv);
      if (++currentSize > table.size()) {
          rehash();
      }
      return true;
  }

// Move version of insert
template <typename K, typename V>
  bool HashTable<K, V>::insert(std::pair<K, V> &&kv) {
      return insert(kv);
  }

// Delete the key k and the corresponding value if it is in the hash table. Return true if k is deleted, 
// return false otherwise (i.e., if key k is not in the hash table).
template <typename K, typename V>
  bool HashTable<K, V>::remove(const K &k) {
      auto &list = table[myhash(k)];
      auto it = std::find_if(list.begin(), list.end(), [&k](const auto &item) {
          return item.first == k;
      });
      if (it != list.end()) {
          list.erase(it);
          --currentSize;
          return true;
      }
      return false;
  }

// Delete all elements in the hash table
template <typename K, typename V>
  void HashTable<K, V>::clear() {
      makeEmpty();
  }

// Load the content of the file with name filename into the hash table. In the file, each line contains a 
// single pair of key and value, separated by a white space.
template <typename K, typename V>
  bool HashTable<K, V>::load(const char *filename) {
      std::ifstream infile(filename);
      if (!infile) return false;

      K key;
      V value;
      while (infile >> key >> value) {
          insert({key, value});
      }
      return true;
  }

// Display all entries in the hash table. If an entry contains multiple key-value pairs, separate them by a 
// semicolon character (:) (see the provided executable for the exact output format).
template <typename K, typename V>
  void HashTable<K, V>::dump() const {
      for (size_t i = 0; i < table.size(); ++i) {
          std::cout << "Bucket " << i << ": ";
          for (const auto &kv : table[i]) {
              std::cout << kv.first << ":" << kv.second << " ";
          }
          std::cout << std::endl;
      }
  }

// Return the number of elements in the hash table.
template <typename K, typename V>
  size_t HashTable<K, V>::size() const {
      return currentSize;
  }

// Write all elements in the hash table into a file with name filename. Similar to the file format in the 
// load function, each line contains a pair of key-value pair, separated by a white space.
template <typename K, typename V>
  bool HashTable<K, V>::write_to_file(const char *filename) const {
      std::ofstream outfile(filename);
      if (!outfile) return false;

      for (const auto &list : table) {
          for (const auto &kv : list) {
              outfile << kv.first << " " << kv.second << std::endl;
          }
      }
      return true;
  }

//------------------------------------------------
// =========== Private Member functions ==========
//------------------------------------------------

// Delete all elements in the hash table. The public interface clear() will call this function.
template <typename K, typename V>
  void HashTable<K, V>::makeEmpty() {
      for (auto &list : table) {
          list.clear();
      }
      currentSize = 0;
  }

// Rehash function. Called when the number of elements in the hash table is greater than the 
// size of the vector.
template <typename K, typename V>
  void HashTable<K, V>::rehash() {
      auto oldTable = table;
      table.resize(prime_below(2 * table.size()));
      for (auto &list : table) {
          list.clear();
      }
      currentSize = 0;
      for (const auto &list : oldTable) {
          for (const auto &kv : list) {
              insert(kv);
          }
      }
  }

// Return the index of the vector entry where k should be stored.
template <typename K, typename V>
  size_t HashTable<K, V>::myhash(const K &k) const {
      static std::hash<K> hashFunc;
      return hashFunc(k) % table.size();
  }


// Returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
  unsigned long HashTable<K, V>::prime_below (unsigned long n)
  {
    if (n > max_prime){
        cerr << "** input too large for prime_below()\n";
        return 0;
    }
    if (n == max_prime){
        return max_prime;
    }
    if (n <= 1){
      cerr << "** input too small \n";
      return 0;
    }

    // now: 2 <= n < max_prime
    vector <unsigned long> v (n+1);
    setPrimes(v);
    while (n > 2)
      {
        if (v[n] == 1)
    return n;
        --n;
      }

    return 2;
  }

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
  void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
  {
    int i = 0;
    int j = 0;

    vprimes[0] = 0;
    vprimes[1] = 0;
    int n = vprimes.capacity();

    for (i = 2; i < n; ++i)
      vprimes[i] = 1;

    for( i = 2; i*i < n; ++i)
      {
        if (vprimes[i] == 1)
          for(j = i + i ; j < n; j += i)
            vprimes[j] = 0;
      }
  }

#endif