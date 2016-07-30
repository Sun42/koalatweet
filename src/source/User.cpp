#include "User.h"

User::User(std::string name, std::string screenName, std::string location, std::string profileImageUrl)
  :_name(name), _screenName(screenName), _location(location), _profileImageUrl(profileImageUrl)
{
}

User::User(const User& rt)
{
  this->_name = rt._name;
  this->_screenName = rt._screenName;
  this->_location = rt._location;
  this->_profileImageUrl = rt._profileImageUrl;
}

User::~User()
{
}
       User& User::operator=(const User &rt)
       {
            if (this != &rt)
               {
                   this->_name = rt._name;
                   this->_screenName = rt._screenName;
                   this->_location = rt._location;
                   this->_profileImageUrl = rt._profileImageUrl;
                }
	    return (*this);
       }

       void User::setStatus(Status* status)
       {
           this->_currentStatus = status;
       }

              void User::setName(std::string& name)
              {
                  this->_name = name;
              }
       void User::setScreenName(std::string& screenName)
       {
           this->_screenName = screenName;
       }
       void User::setLocation(std::string& location)
       {
            this->_location = location;
       }
       void User::setProfile(std::string& profile)
       {
           this->_profileImageUrl = profile;
       }

       std::string  User::getName() const
       {
            return (this->_name);
       }

       std::string User::getScreenName() const
       {
           return (this->_screenName);
       }
       std::string User::getLocation() const
       {
           return (this->_location);
       }
       std::string User::getProfile() const
       {
           return (this->_profileImageUrl);
       }
  Status* User::getStatus() const
  {
      return (this->_currentStatus);
  }

/*
    std::string _name;
    std::string _screenName;
    std::string _location;
    std::string _profileImageUrl;
   Status* _currentStatus;
    std::list<Status*> _listStatus;
    std::string _nbFriends;
    std::string _nbFollowers;
*/
