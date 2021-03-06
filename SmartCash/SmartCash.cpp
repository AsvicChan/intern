// SmartCash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include "SmartCache.h"
#include <boost/test/minimal.hpp>

class Shouter
{
public:
	Shouter(int id) : id_(id)
	{
		std::cout <<id_<<" BORN; ";
	};

	~Shouter()
	{
		std::cout <<id_<<" DEAD; ";
	};

private:
	int id_;
};

Shouter a[10];

std::shared_ptr<Shouter> load(int id)
{
	//return std::make_shared<Shouter>(a[id](id));
};

/*
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
*/

int add(int i, int j)
{
	return i + j;
}

int test_main(int, char *[]) // note the name! 
{

	SmartCache<int, Shouter> cache(load);
	BOOST_CHECK(cache.getPtr(0).get()==load(0).get()); // #1 continues on error 
	return cache.getPtr(0).get() == load(0).get() ? 0 : 1;
	
}
