#include "head/any.hpp"

namespace Reflect
{
	any::any(void* payload, type_access store, type_operations* ops)
		:payload(payload),store(store), ops(ops)
	{

	}

	any::any(const any& other)
		:payload()
	{

	}
}
