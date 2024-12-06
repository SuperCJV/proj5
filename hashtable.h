#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>

// Each entry in the hash table is a list inside a vector
#include <vector>
#include <list>

// Provides the std::pair<K, V> class template to pass the pairs as parameter types
#include <utility>

// Provides the std::has class template to compute hash value for the key
#include <functional>

// max_prime is used by the helpful functions provided to you.
static const unsigned int max_prime = 1301081;
// the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero. 
static const unsigned int default_capacity = 101;

namespace cop4530{
    template <typename K, typename V>   // K = Key, V = Value
        class HashTable{
            public:
                // Constructors and Destructor
                HashTable(size_t size = 101);   // Constructor
                ~HashTable();   // Destructor

                // Public Member functions
                bool contains(const K &k) const;   // Check if key k is in the hash table 
                bool match(const std::pair<K,V> &kv) const;  // check if key-value pair is in the hash table
                bool insert(const std::pair<K,V> &kv);   // Add the key-value pair kv into the hash table
                bool insert(std::pair<K, V> &&kv);   // Move version of insert
                bool remove(const K &k);   // delete the key k and the corresponding value
                void clear();   // delete all elements in the hash table
                bool load(const char *filename);    // load the content of the file with name filename into the hash table
                void dump() const;  //  display all entries in the hash table
                size_t size() const;    //  return the number of elements in the hash table
                bool write_to_file(const char *filename) const;  //  write all elements in the hash table into a file with name filename
            private:
                // Private Member functions
                void makeEmpty();   // delete all elements in the hash table
                void rehash();  // Rehash function
                size_t myhash(const K &k) const;    // return the index of the vector entry where k should be stored
                unsigned long prime_below(unsigned long);   // help function to determine the proper prime numbers used in setting up the vector size
                void setPrimes(std::vector<unsigned long>& vprimes); // help function to determine the proper prime numbers used in setting up the vector size
        
                // Private Member data
                vector<list<std::pair<K, V>>> table;
                size_t currentSize;
        };
    #include "hashtable.hpp"
}

#endif
