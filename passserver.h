#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <iostream>
#include <string>
#include <utility>

#include "hashtable.h"

namespace cop4530 {
    class PassServer {
        public:
            // Constructors and Destructors
            PassServer(size_t size = 101);
            ~PassServer();

            // Public member functions
            bool load(const char *filename);
            bool addUser(std::pair<string, string> &kv);
            bool addUser(std::pair<string, string> &&kv);
            bool removeUser(const string &k);
            bool changePassword(const std::pair<string, string> &p, const string & newpassword);
            bool find(const string & user) const;
            void dump() const;
            size_t size() const;
            bool write_to_file(const char *filename) const;

        private:
            // Private member functions
            string encrypt(const string &str);
            
            // Private member data
            HashTable<string, string> table;
        };
    #include "passserver.cpp"
}

#endif
