#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <unordered_map>

class User {
    private:
        int userID;
        std::string username; 
        std::string password;
        std::string email;
    
    public: 
        // Constructor
        User(int id, const std::string& name, const std::string& email, const std::string& password);
        
        // Methods in order of implementation
        int getUserID() const;
        std::string getEmail() const;
        std::string getUsername() const;
        std::string getPassword() const;
        bool verifyPassword(const std::string& inputPassword) const;
        static void registerUser(std::vector<User>& users);
        static void saveToFile(const std::vector<User>& users);
        static bool loginUser(std::vector<User>& users, const std::string& email, const std::string& password);
        static std::vector<User> loadFromFile();
        static bool checkUserExists(const std::string& email);
};   

#endif // USER_H
