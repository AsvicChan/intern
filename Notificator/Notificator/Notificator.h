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
	const Function *f;

	void sendqueue(std::queue<Message> &queue)
	{
		while (!queue.empty())
		{
			f(std::move(queue.front()));
			queue.pop();
		}
	};

	void send()
	{
		while (alive_)
		{
			std::queue<Message> copyqueue;
			{
				std::unique_lock<std::mutex> lck(mutex_);
				cv_.wait(lck, [this]() {return (!queue_.empty() || !alive_); });
				queue_.swap(copyqueue); 
			}
			sendqueue(copyqueue);
		}
		sendqueue(queue_);
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
		cv_.notify_all();
	};

};