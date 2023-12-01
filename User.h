#pragma once
#include <iostream>
#include <vector>
#include "sha1.h"

class User
{
private:
	const std::string _login;
	uint* _shaPas;
	std::string _name;
	int count = 0;
	User* usData;
public:
	User(const std::string& login, const std::string& name, uint* shaPas) :_login(login), _name(name), _shaPas(shaPas) {
		
	}
	
	const std::string GetLogin()const { return _login; }

	//void SetPassword(const std::string& password) { _password = password; }
	uint* get_sha_pas() { return _shaPas; }
	const std::string GetName()const { return _name; }
	void setName(const std::string& name) { _name = name; }
};

