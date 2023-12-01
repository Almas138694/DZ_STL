#pragma once
#include "User.h"
#include <iostream>

class Message
{
private:
	const std::string _from;

	const std::string _whom;
	std::string _text;

public:
	Message(const std::string& from, const std::string& whom, const std::string& text):_from(from), _whom(whom), _text(text){}
	const std::string& getFrom()const { return _from; }
	const std::string& getWhom()const { return _whom; }
	const std::string& getText() const { return _text; }

};