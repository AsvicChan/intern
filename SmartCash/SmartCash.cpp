// SmartCash.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <unordered_map>
#include "SmartCache.h"
#include <boost/test/minimal.hpp>

int a[10];

std::shared_ptr<int> load(int id)
{
	std::cout << "LOADER: " << a[id] << " LOADED... ";
	return std::make_shared<int>(a[id]);
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

	for (int i = 0; i < 10; i++)
	{
		a[i] = 10 - i;
	}
	SmartCache<int, int> cache(load);
	BOOST_CHECK(cache.getPtr(0).get()==load(0).get()); // #1 continues on error 
	return cache.getPtr(0).get() == load(0).get() ? 0 : 1;
	
}
