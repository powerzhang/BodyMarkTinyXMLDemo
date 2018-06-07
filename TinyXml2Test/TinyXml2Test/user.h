#ifndef USER_H
#define USER_H
#include<string>
using namespace std;
//用户类
class User
{
public:
    User(){
        gender=0;
    };

    User(const string& userName, const string& password, int gender, const string& mobile, const string& email){
        this->userName=userName;
        this->password=password;
        this->gender=gender;
        this->mobile=mobile;
        this->email=email;
    };

    string userName;
    string password;
    int gender;
    string mobile;
    string email;
};

#endif // USER_H
