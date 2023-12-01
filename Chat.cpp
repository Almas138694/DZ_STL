#include "Chat.h"
#include "User.h"
#include "Message.h"
#include <iostream>
#include <string>


std::shared_ptr<User> Chat::Get_Login(const std::string& _login)const
{
	for (auto& user : users)
	{
		if (_login == user.GetLogin())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::get_name(const std::string& _name)const
{
	
	return std::shared_ptr<User>();
}

std::shared_ptr<User> Chat::get_sha_pas(uint* _shaPas)
{
	for (auto& user : users)
	{
		if (_shaPas == user.get_sha_pas())
			return std::make_shared<User>(user);
	}
	return nullptr;
}

std::shared_ptr<User> Chat::getByPassword(const std::string& _password) const
{
	
	return std::shared_ptr<User>();
}

bool Chat::pas_sha1(uint* pas_sha)
{
	for (auto& user : users)
	{
		if (!memcmp(pas_sha, user.get_sha_pas(), SHA1HASHLENGTHBYTES))
			return true;
	}
	return false;
}

bool Chat::start()
{
	return chat_worc = true;
}

void Chat::autoriz()
{	
	std::string login, password;

		std::cout << "Ввидите логин" << std::endl;
		std::cin >> login;
		std::cout << "Ввидите пароль" << std::endl;
		std::cin >> password;

		currentUser = Get_Login(login);

		int size = password.size() + 1;
		char* Password = new char[size];
		memcpy(Password, password.c_str(), size);

		uint* sha1_pas = sha1(Password, size);
		
		if (currentUser == nullptr)
		{
			currentUser = nullptr;
			std::cout << "Не верный логин" << std::endl;
			return;
		} 
		else
		{
			if (!pas_sha1(sha1_pas))
			{
				currentUser = nullptr;
				std::cout << "Не верный пароль" << std::endl;
				return;
			}
		}
}

void Chat::regis()
{
	std::string _name, _login, password;	

		std::cout << "Ввидите имя" << std::endl;
		std::cin >> _name;
		std::cout << "Bвидите логин" << std::endl;
		std::cin >> _login;
		std::cout << "Ввидите пароль" << std::endl;
		std::cin >> password;

		if (Get_Login(_login))
		{
			throw LoginEx();
		}
		int size = password.size() + 1;
		char* Password = new char[size];
		memcpy(Password, password.c_str(), size);

		uint* sha1_pas = sha1(Password, size);
	
		User user = User(_login, _name, sha1_pas);
		currentUser = std::make_shared<User>(user);
		users.push_back(user);	
		delete[]Password;
}

void Chat::ChatMenu()
{
		char oper;
		std::cout << "Нажмите 1 для входа. Нажмите 2 для регистрации. Нажмите 0 для выхода." << std::endl;
		std::cin >> oper;
		switch (oper)
		{
		case '1':
		{
			autoriz();
			break;
		}
		case '2':
		{
			try {
				regis();
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}
			break;
		}
		case '0':
		{
			chat_worc = false;
			break;
		}
		default:
		{
			std::cout << "Выберети значения 1, 2, 0" << std::endl;
			break;
		}
		}
}

void Chat::All_Users_Name()
{
	std::cout << "<<<<Пользователи>>>>" << std::endl;
	for (auto& user : users)
	{
		std::cout << user.GetLogin();
		if (currentUser->GetLogin() == user.GetLogin())
		{
			std::cout << " <- Вы ";
		}
		std::cout << std::endl;
		std::cout << "------------------------" << std::endl;
	}
}

void Chat::add_Messange()
{
	std::string to, text;
	std::cout << "Написать всем или логин: ";
	std::cin >> to;
	std::cout << "ТЕКСТ: " << to <<" >>> ";
	std::cin.ignore();

	std::getline(std::cin, text);


	if (!(to == "всем" || Get_Login(to)))
	{
		std::cout << "пользователь с таким логином не существует: " << to << std::endl;// не удалось найти пользователя
			return;
	}

	if (to == "всем")
		messages.push_back(Message{ currentUser->GetLogin(), "всем", text });
	else
		messages.push_back(Message{ currentUser->GetLogin(), Get_Login(to)->GetLogin(), text });
		
	
}

void Chat::show_user()
{		
		std::cout << "Ас-саляму алейкум: " << currentUser->GetLogin();
		std::cout << std::endl << "---------------------------" << std::endl;
 while (chat_worc && currentUser) {
		std::cout << "Ввидите значение 1 прочитать сообщения, 2 написать сообщения, 3 посмотреть кто есть в чате, 0 выход" << std::endl;
		int oper = 0;
		std::cin.ignore( oper);
		std::cin >> oper;
		switch (oper)
		{
		case 1:
		{
			show_messages();
			break;
		}
		case 2:
		{
			add_Messange();
			break;
		}
		case 3:
		{
			All_Users_Name();
			break;
		}
		case 0:
		{
			currentUser = nullptr;
			break;
		}
		default:
		{
			std::cout << "Ввидите значение 1 прочитать сообщения, 2 написать сообщения, 3 посмотреть кто есть в чате, 0 выход" << std::endl;
			break;
		}
		}
	}
		
}

void Chat::show_messages()
{
	std::string general;
	std::string from;

	std::cout << ">>>>>>>Chat<<<<<<<" << std::endl;
	 
	//Показываем сообщения
	for (auto& mess : messages)
	{
		if (currentUser->GetLogin() == mess.getFrom() || currentUser->GetLogin() == mess.getWhom() || mess.getWhom() == "всем")
		{
			from = (currentUser->GetLogin() == mess.getFrom()) ? "меня" : Get_Login(mess.getFrom())->GetName();

			if (mess.getWhom() == "всем")
			{
				general = "(всем)";
			}
			else
			{
				general = (currentUser->GetLogin() == mess.getWhom()) ? "мне" : Get_Login(mess.getWhom())->GetName();
			}

			std::cout << "Сообщение от " << from << " >>> " << general << std::endl;
			std::cout << "text: " << mess.getText() << std::endl;
		}
	}
	std::cout << "==========================" << std::endl;
}
