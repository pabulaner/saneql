#include <string>
#include <vector>

#include "Stream.hpp"

struct Account {
    struct Key {
        int id;
    };

    std::string name;
    std::string email;
    int age;
};

int main(int argc, char** argv) {
    std::vector<std::pair<Account::Key, Account>> db{
        {{1}, {"Paul", "p.hayder@example.com", 23}},
        {{2}, {"Marc", "m.hayder@example.com", 21}},
        {{3}, {"Sophie", "s.b@yahoo.de", 24}}
    };

    
    
    return 0;
}