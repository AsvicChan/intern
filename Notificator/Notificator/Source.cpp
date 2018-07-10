#include <iostream>
#include "Notificator.h"
#include <string>

void func(std::string str)
{
	std::cout << str;
}

int main()
{
	Notificator<std::string> notificator(func,false);
	notificator.notify("Message 1 ");
	notificator.notify("Message 2 ");
	notificator.notify("Message 3 ");
	notificator.notify("Message 4 ");
	system("pause");
	return 0;
}