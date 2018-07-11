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
	bool needscall_;
	void(*func_)(Message);

	void send()
	{
		alive_ = true;
		std::unique_lock<std::mutex> lck(mutex_);
		while (alive_)
		{
			while (!needscall_) cv_.wait(lck);
			if (!queue_.empty())
			{
				Message post = queue_.front();
				queue_.pop();
				lck.unlock();
				func_(post);
				lck.lock();
			}
			else needscall_ = false;
		}
		while (!queue_.empty())
		{
			Message post = queue_.front();
			queue_.pop();
			lck.unlock();
			func_(post);
			lck.lock();
		}
		return;
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
		//std::lock_guard<std::mutex> lock(mutex_);
		alive_ = false;
		needscall_ = true;
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