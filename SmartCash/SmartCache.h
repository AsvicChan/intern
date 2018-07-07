#pragma once
#include "stdafx.h"
#include <iostream>
#include <unordered_map>

template <class ID, class T> class SmartCache
{
private:
	std::unordered_map<ID, std::weak_ptr<T>> map;
	std::shared_ptr<T>(*loader_)(ID);
public:

	template <typename F>
	SmartCache(F loader) : loader_(loader)
	{
		std::cout << "Created smartcache; ";
	};

	~SmartCache()
	{
		std::cout << "Destoyed smartcache. ";
	};

	std::shared_ptr<T> getPtr(ID id)
	{
		std::cout << "getting pointer... ";
		if (map.end() == map.find(id))
		{
			//create pointer
			map.insert(std::make_pair(id, std::weak_ptr<T>()));
			std::cout << "pointer created... ";
		}
		if (map.at(id).expired() == true)
		{
			//load object
			auto ptr = loader_(id);
			map.at(id) = ptr;
			std::cout << "object loaded and pointer sent; ";
			return map.at(id).lock();
		}
		std::cout << "pointer sent; ";
		return map.at(id).lock();
	};
};

