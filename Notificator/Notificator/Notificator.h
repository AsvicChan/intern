#pragma once
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

template <typename Message>
class Notificator
{
private:
	std::mutex mutex_;
	std::condition_variable cv_;
	std::queue<Message> queue_;
	std::thread thread_;
	bool eraseable_;
	bool alive_;
	bool hasdata_;
	void(*func_)(Message);

	void send()
	{
		alive_ = true;
		std::unique_lock<std::mutex> lck(mutex_);
		while (alive_)
		{
			while (!hasdata_) cv_.wait(lck);
			//mutex_.lock();
			if (!queue_.empty())
			{
				func_(queue_.front());
				queue_.pop();
			}
			else hasdata_ = false;
			//mutex_.unlock();
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
		hasdata_ = true;
		cv_.notify_all();
		mutex_.unlock();
	};

};