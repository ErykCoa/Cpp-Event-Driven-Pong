#ifndef PRIORITYQUEUEELEMENT
#define PRIORITYQUEUEELEMENT

#include <type_traits>

#include "enums.h"

template<class Type, typename PriorityType = int>
struct QueueElement : public Type
{
	using TruePriorityType = typename std::conditional<std::is_enum<PriorityType>::value, typename std::underlying_type<PriorityType>::type, PriorityType >::type;

	static_assert(std::is_arithmetic< TruePriorityType >::value, "PriorityType must be an arithmetic type!");

	// std::underlying_type<Type>, typename PriorityType

	using value_type = typename Type;

	TruePriorityType Priority;

	QueueElement(Type Item, PriorityType Priority) : Type{ Item }, Priority{ static_cast<TruePriorityType>(Priority) } {};


	friend bool operator<(const QueueElement<Type, PriorityType>& First, const QueueElement<Type, PriorityType>& Second)
	{
		return First.Priority < Second.Priority;
	}
};



#endif