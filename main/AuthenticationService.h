#ifndef CPP_OTP_AUTHENTICATIONSERVICE_H
#define CPP_OTP_AUTHENTICATIONSERVICE_H

#include <string>

#include "ProfileDao.h"
#include "RsaTokenDao.h"

class Logger {

public:
    virtual void show(const std::string msg) {
        std::cout << msg << std::endl;
    }
};

class AuthenticationService {

public:
    AuthenticationService(ProfileDao* p1, RsaTokenDao* p2, Logger* p3) {
        _pProfileDao = p1;
        _pTokenDao = p2;
        _pLogger = p3;
    }
    bool isValid(const std::string userName, const std::string password);

private:
    ProfileDao* _pProfileDao;
    RsaTokenDao* _pTokenDao;
    Logger* _pLogger;
};


#endif //CPP_OTP_AUTHENTICATIONSERVICE_H
