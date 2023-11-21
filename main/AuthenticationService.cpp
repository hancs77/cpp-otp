//
// Created by Joseph Yao on 2018/7/31.
//

#include <iostream>
#include <string>
#include "AuthenticationService.h"

// AuthenticationService::AuthenticationService(ProfileDao& pdao, RsaTokenDao& tokendao) : _pdao(pdao), _tokenDao(tokendao){
// }

bool AuthenticationService::isValid(const std::string userName, const std::string password) {

    // 根據 account 取得自訂密碼
    // ProfileDao profileDao;
    auto passwordFromDao = _pProfileDao->getPassword(userName);

    // std::cout << "debug: passwd " << passwordFromDao << std::endl;

    // 根據 account 取得 RSA token 目前的亂數
    // RsaTokenDao rsaToken;
    auto randomCode = _pTokenDao->getRandom(userName);

    // std::cout << "debug: random " << randomCode << std::endl;

    // 驗證傳入的 password 是否等於自訂密碼 + RSA token亂數
    auto validPassword = passwordFromDao + randomCode;
    auto isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        _pLogger->show("valid failed");
        return false;
    }
}
