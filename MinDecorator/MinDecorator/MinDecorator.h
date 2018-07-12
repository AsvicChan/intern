#pragma once
#include <algorithm>

template <typename Obj, typename Filter>
class DecoratorComparator
{
private:
	Filter filter_;
public:

	DecoratorComparator(Filter f) : filter_(f)
	{

	};

	~DecoratorComparator()
	{

	};

	bool operator()(Obj first, Obj second)
	{
		if (filter_(first) && filter_(second)) return first < second;
		if (filter_(first)) return true;
		return false;
	};
};

template <class ForwardIt, typename Filter>
ForwardIt min_element_if(ForwardIt first, ForwardIt last, Filter filter)
{
	DecoratorComparator<decltype(*first),Filter> comparator(filter);
	return std::min_element(first, last, comparator);
};
