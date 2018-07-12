#include <iostream>
#include "MinDecorator.h"

bool filter(int n)
{
	if (n % 2 == 0) return true;
	return false;
};

int main()
{
	int a[10];
	for (int i = 0; i != 9; ++i)
	{
		a[i] = i+1;
	}
	std::cout << *min_element_if(a, a + 8, filter)<<std::endl;
	system("pause");
	return 0;
}