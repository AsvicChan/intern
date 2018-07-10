#include <iostream>
#include "Notificator.h"
#include <string>

void func(std::string str)
{
	std::cout << str;
}

void testNormal()
{
	std::cout << "Started testNormal; ";
	Notificator<std::string> notificator(func, false);
	notificator.notify("Message 1 normal; ");
	notificator.notify("Message 2 normal; ");
	notificator.notify("Message 3 normal; ");
	notificator.notify("Message 4 normal; ");
	std::cout << "Finished testNormal; ";
}

void testEraseable()
{
	std::cout << "Started testEraseable; ";
	Notificator<std::string> notificator(func, true);
	notificator.notify("Message 1 eraseable; ");
	notificator.notify("Message 2 eraseable; ");
	notificator.notify("Message 3 eraseable; ");
	notificator.notify("Message 4 eraseable; ");
	std::cout << "Finished testEraseable; ";
}

void simpleCycle(int id, bool eraseable)
{
	Notificator<std::string> notificator(func, eraseable);
	for (int i = 0; i != 5; ++i)
	{
		notificator.notify("Message "+std::to_string(i)+" from "+std::to_string(id)+"; ");
	}
}

void testThreads()
{
	std::cout << "Started testThreads; ";
	std::thread t1(simpleCycle, 1, true);
	std::thread t2(simpleCycle, 2, true);
	std::thread t3(simpleCycle, 3, false);
	std::thread t4(simpleCycle, 4, false);
	std::thread t5(simpleCycle, 5, false);
	std::cout << "Finished testThreads; ";
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
	t5.detach();
}

void infCycle(int id, bool eraseable)
{
	Notificator<std::string> notificator(func, eraseable);
	while (true)
	{
		notificator.notify("Message from " + std::to_string(id) + "; ");
	}
};

void testInfinity()
{
	std::cout << "Started testInfinity; ";
	std::thread t1(infCycle, 1, true);
	std::thread t2(infCycle, 2, false);
	std::thread t3(infCycle, 3, true);
	std::thread t4(infCycle, 4, false);
	t1.detach();
	t2.detach();
	t3.detach();
	t4.detach();
	std::cout << "Finished testInfinity; ";
}

int main()
{
	Notificator<std::string> notificator1(func, true);
	Notificator<std::string> notificato2(func, false);
	Notificator<std::string> notificato3(func, true);
	Notificator<std::string> notificato4(func, false);
	//testNormal();
	//testEraseable();
	//testThreads();
	testInfinity();
	system("pause");
	return 0;
}