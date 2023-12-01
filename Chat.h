#pragma once
#include <iostream>
#include "Message.h"
#include <memory> 
#include <exception>
#include <vector>

class LoginEx :public std::exception
{
public:
	const char* what() const noexcept override { return "Такой логин существует"; }
};

class Chat
{
private:
	std::vector<User>users;
	std::vector<Message>messages;
	std::shared_ptr<User>currentUser = nullptr;

	void autoriz(); //авторизация
	void regis(); // регистрация
	void All_Users_Name();
	void add_Messange();
	std::vector<User>& Get_users() { return users;}
	std::vector<Message>& Get_messags() { return messages; }
	std::shared_ptr<User>Get_Login(const std::string& _login)const;
	std::shared_ptr<User>get_name(const std::string& _name)const;
	std::shared_ptr<User>get_sha_pas(uint* _shaPas);
	std::shared_ptr<User>getByPassword(const std::string& _password)const;
	bool pas_sha1(uint* pas_sha);
public:
	bool chat_worc = false;
	bool start();
	std::shared_ptr<User> get_current_user() const { return currentUser; } 
	void ChatMenu(); // меню чата
	void show_user();
	void show_messages();
};