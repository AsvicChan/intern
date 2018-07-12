#pragma once
#include <algorithm>

template <typename T, typename Filter>
class DecComparator
{
private:
	Filter filter_;
public:

	DecComparator(Filter f) : filter_(f)
	{

	};

	~DecComparator()
	{

	};

	bool operator()(T first, T second)
	{
		if (filter_(first) && filter_(second)) return first < second;
		if (filter_(first)) return true;
		return false;
	};
};

template <class ForwardIt, typename Filter>
ForwardIt mindecorator(ForwardIt first, ForwardIt last, Filter filter)
{
	DecComparator<decltype(*first),Filter> comparator(filter);
	return std::min_element(first, last, comparator);
};
