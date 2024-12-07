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
            PassServer(size_t size = 101);  // Constructor
            ~PassServer();  // Destructor

            // Public member functions
            bool load(const char *filename);    // Load a password file into the HashTable object
            bool addUser(std::pair<string, string> &kv);    // Add a new username and password
            bool addUser(std::pair<string, string> &&kv);   // Move version of addUser
            bool removeUser(const string &k);   // Delete an existing user with username k
            bool changePassword(const std::pair<string, string> &p, const string & newpassword);    // Change an existing user's password
            bool find(const string & user) const;   // Check if a user exists
            void dump() const;  // Show the structure and contents of the HashTable object to the screen
            size_t size() const;    // Return the size of the HashTable
            bool write_to_file(const char *filename) const; // Save the username and password combination into a file

        private:
            // Private member functions
            string encrypt(const string &str);  // Encrypt the parameter str and return the encrypted string
            
            // Private member data
            HashTable<string, string> table;
        };
}

#endif
