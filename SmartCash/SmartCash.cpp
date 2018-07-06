// SmartCash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>

template <class ID, class T> class SmartCache
{
private:
	std::unordered_map<ID, std::weak_ptr<T>> map;
	std::shared_ptr<T> (*loader_)(ID);
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

int a[10];

std::shared_ptr<int> load(int id)
{
	std::cout << "LOADER: " << a[id] << " LOADED... ";
	return std::make_shared<int>(a[id]);
};

int main()
{
	for (int i = 0; i < 10; i++)
	{
		a[i] = 10 - i;
	}
	SmartCache<int, int> cache(load);
	auto ptr1 = cache.getPtr(0);
	auto ptr = cache.getPtr(1);
	ptr = cache.getPtr(0);
    return 0;
}

