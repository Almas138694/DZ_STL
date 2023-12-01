#include "Chat.h"
#include <Windows.h>

int main()
{
	SetConsoleCP(1251);
	setlocale(0, "rus");
		Chat chat;
		chat.start();

		do{
			chat.ChatMenu();
			
			while (chat.get_current_user())
			{
				chat.show_user();
			}

		} while (chat.chat_worc);
		return 0;
}