#pragma once
#include <condition_variable>
#include <mutex>
#include <thread>
#include <queue>

template <typename Message, typename Function>
class Notificator
{
private:
	bool alive_;
	std::mutex mutex_;
	std::condition_variable cv_;
	std::queue<Message> queue_;
	std::thread thread_;
	const bool eraseable_;
	bool needscall_;
	const Function *f;

	void send()
	{
		while (alive_)
		{
			std::queue<Message> copyqueue;
			{
				std::unique_lock<std::mutex> lck(mutex_);
				cv_.wait(lck, [this]() {return (needscall_ || !alive_); });
				needscall_ = false;
				if (!queue_.empty()) queue_.swap(copyqueue); 
			}
			while (!copyqueue.empty())
			{
				f(std::move(copyqueue.front()));
				copyqueue.pop();
			}
		}
		while (!queue_.empty())
		{
			f(std::move(queue_.front()));
			queue_.pop();
		}
	};

public:

	Notificator()
	{
		
	};

	Notificator(Function func, bool eraseable)
	: alive_(true), thread_(&Notificator::send, this), f(func), eraseable_(eraseable)
	{

	};

	~Notificator()
	{
		alive_ = false;
		cv_.notify_all();
		thread_.join();
	};

	void notify(Message message)
	{
		std::lock_guard<std::mutex> lock(mutex_);
		if (eraseable_ && !queue_.empty()) queue_.pop();
		queue_.push(message);
		needscall_ = true;
		cv_.notify_all();
	};

};