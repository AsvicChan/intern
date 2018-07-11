#pragma once
#include <algorithm>

template <class ForwardIt, typename Filter>
class MinDecorator
{
private:

public:

	MinDecorator()
	{

	};

	~MinDecorator()
	{

	};

	ForwardIt operator()(ForwardIt first, ForwardIt last, Filter filter)
	{
		return std::min_element(first, last, Comparator);
	};

};