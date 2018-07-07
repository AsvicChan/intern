#pragma once
#include <memory>
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
		
	};

	~SmartCache()
	{
		
	};

	std::shared_ptr<T> getPtr(ID id)
	{
		auto ptr = map[id].lock();
		if (ptr==nullptr)
		{
			ptr = loader_(id);
			map[id] = ptr;
		}
		return ptr;
	};
};

