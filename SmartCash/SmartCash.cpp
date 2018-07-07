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
	BOOST_CHECK(add(2, 2) == 4); // #1 continues on error 
	BOOST_REQUIRE(add(2, 2) == 4); // #2 throws on error 

	if (add(2, 2) != 4)
		BOOST_ERROR("Ouch..."); // #3 continues on error 
	if (add(2, 2) != 4)
		BOOST_FAIL("Ouch..."); // #4 throws on error 
	if (add(2, 2) != 4)
		throw "Oops..."; // #5 throws on error 

	return add(2, 2) == 4 ? 0 : 1; // #6 returns error code 
}
