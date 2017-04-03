#ifndef CONSTITEM
#define CONSTITEM

#include <mutex>
#include <functional>


template<class Data>
class ConstItem
{
public:

	Data GetCopy() { return Item; }

	ConstItem(Data Data) : Item{ Data } {}

	using value_type = typename Data;

private:
	Data Item;
};


#endif
