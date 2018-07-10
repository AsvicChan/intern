#pragma once
#include <thread>
#include <queue>
#include <mutex>

template <typename Message>
class Notificator
{
private:
	std::mutex mutex_;
	std::queue<Message> queue_;
	std::thread thread_;
	bool eraseable_;
	bool alive_;
	void(*func_)(Message);

	void send()
	{
		alive_ = true;
		while (alive_)
		{
			mutex_.lock();
			if (!queue_.empty())
			{
				func_(queue_.front());
				queue_.pop();
			}
			mutex_.unlock();
		}
	};

public:

	Notificator()
	{
		
	};

	template <typename F>
	Notificator(F func, bool eraseable)
	: thread_(&Notificator::send, this), func_(func), eraseable_(eraseable)
	{

	};

	~Notificator()
	{
		alive_ = false;
		thread_.join();
	};

	void notify(Message message)
	{
		mutex_.lock();
		if (eraseable_ && !queue_.empty()) queue_.pop();
		queue_.push(message);
		mutex_.unlock();
	};

};