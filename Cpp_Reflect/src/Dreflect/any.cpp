#include "head/any.hpp"


namespace Reflect
{
	any::any(void* payload, const Type* typeinfo, type_access store, type_operations* ops)
		:payload(payload), typeinfo(typeinfo), store(store), ops(ops)
	{

	}

	any::any(const any& other)
		:payload(other.payload),typeinfo(other.typeinfo),store(other.store),ops(other.ops)
	{

	}

	any::any(any&& other) noexcept
		:payload(std::move(other.payload)), typeinfo(std::move(other.typeinfo)),
		store(std::move(other.store)),ops(std::move(other.ops))
	{
		other.store = any::Null;
		other.payload = nullptr;
		other.ops = nullptr;
		other.typeinfo = nullptr;
	}
}
