#pragma once
#include <thread>
#include <queue>

template <typename Message, typename Function>
class Notificator
{
private:
	std::queue<Message> queue_;
	std::thread thread_;
	bool eraseable_;
	Function func_;

	void sender()
	{
		while (true)
		{
			if (queue_.empty != true)
			{
				func_(queue_.front());
				queue_.pop();
			}
		}
	};

public:

	Notificator()
	{
		thread_(&Notificator.sender); //NOT YET READY DO NOT COMPILE
	};

	~Notificator()
	{

	};

	void notify(Message message)
	{
		queue_.push(m);
	};

};