#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
private:
    int userID;
    std::string username;
    std::string email;
    std::string password;
    std::vector<int> reservations;

public:
    User(int id, const std::string& name, const std::string& email, const std::string& password);
    User(const std::string& name);

    int getUserID() const;
    std::string getEmail() const;
    std::string getUsername() const;
    std::string getPassword() const;

    bool verifyPassword(const std::string& inputPassword) const;
    void registerUser(std::vector<User>& users);
    void saveToFile(const std::vector<User>& users);
    static std::vector<User> loadFromFile();
    static bool checkUserExists(const std::string& email);
    void addReservation(int trainID);
    void cancelReservation(int trainID);
    std::vector<int> getReservations() const;
    std::string getName() const;

    static User* loginUser(std::vector<User>& users, const std::string& email, const std::string& password);
};

#endif
