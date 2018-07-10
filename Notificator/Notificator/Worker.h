#pragma once
#include "Notificator.h"
#include <string>
#include <functional>

class Worker
{
private:
	Notificator <std::string, std::function<void(std::string)>>notificator_;
public:

	Worker()
	{

	};

	~Worker()
	{

	};

};