#include "head/any.hpp"


namespace Reflect
{
	any::any(void* payload, const Type* typeinfo, type_access store, type_operations* ops)
		:payload(payload), typeinfo(typeinfo), store(store), ops(ops)
	{

	}

	any::any(const any& other)
		:payload()
	{

	}
}
