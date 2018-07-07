// SmartCash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include "SmartCache.h"

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

