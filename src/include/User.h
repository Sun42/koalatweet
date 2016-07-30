#ifndef USER_H
#define USER_H

#include "Status.h"
#include <list>
#include <iostream>

class User
{

public:
       User(std::string name, std::string screenName, std::string location, std::string profileImageUrl);
       User(const User& rt);
       ~User();
       User& operator=(const User &rt);

       void setName(std::string& name);
       void setScreenName(std::string& screenName);
       void setLocation(std::string& location);
       void setProfile(std::string& profile);
        void setStatus(Status* status);
       std::string  getName() const;
       std::string getScreenName() const;
       std::string getLocation() const ;
       std::string getProfile() const;
       Status* getStatus() const ;

   private:
    // http://twitter.com/users/57691423.xml
    // void    ParseCommon::getInfoUser(std::map<std::string, std::string> & infoUser)
    std::string _name;
    // [name]
    std::string _screenName;
    // [screen_name]
    std::string _location;
    // [time_zone] 
    std::string _profileImageUrl;
    // [profile_image_url]
    Status* _currentStatus;
    std::list<Status*> _listStatus;
    std::string _nbFriends;
    // [friends_count]
    std::string _nbFollowers;
    // [followers_count]
};

#endif // USER_H
