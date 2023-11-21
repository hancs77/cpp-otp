#include "gtest/gtest.h"
#include "../main/AuthenticationService.h"
#include "../main/ProfileDao.h"
#include "../main/RsaTokenDao.h"

class ProfileDaoStub : public ProfileDao {
public:
    ProfileDaoStub(std::string passwd) {
        _passwd = passwd;
    }
    std::string getPassword(std::string userName) {
        return _passwd;
    }
    std::string _passwd;
};

class RsaTokenDaoStub : public RsaTokenDao {
public:
    RsaTokenDaoStub(std::string token) {
        _token = token;
    }
    std::string getRandom(std::string userName) {
        return _token;
    }
    std::string _token;
};

class LoggerMock : public Logger {
public:
    void show(const std::string msg) {
        _lastMsg = msg;
    }
    std::string _lastMsg;
};

namespace {

    TEST(AuthenticationService, IsValid) {

        ProfileDaoStub* pProfileStub = new ProfileDaoStub("91");
        RsaTokenDaoStub* pTokenStub = new RsaTokenDaoStub("000000");
        LoggerMock* pLoggerMock = new LoggerMock();

        AuthenticationService target(pProfileStub, pTokenStub, pLoggerMock);

        bool actual = target.isValid("joey", "91000000");
        ASSERT_TRUE(actual);
    }

    TEST(AuthenticationService, NotValid) {

        ProfileDaoStub* pProfileStub = new ProfileDaoStub("91");
        RsaTokenDaoStub* pTokenStub = new RsaTokenDaoStub("000000");
        LoggerMock* pLoggerMock = new LoggerMock();

        AuthenticationService target(pProfileStub, pTokenStub, pLoggerMock);

        bool actual = target.isValid("joey", "91000001");

        ASSERT_TRUE(actual == false);
        ASSERT_TRUE(pLoggerMock->_lastMsg == "valid failed");
    }
}