#include "head/any.hpp"


namespace Reflect
{
	any::any(void* payload, const Type* typeinfo, type_access store, type_operations* ops, Variant v)
		:payload(payload), typeinfo(typeinfo), store(store), ops(ops), variant(v)
	{

	}

	any::any(const any& other)
		:typeinfo(other.typeinfo),store(other.store),ops(other.ops),variant(other.variant)
	{
		if (other.payload != nullptr)
		{
			if (store == Copy)
			{
				payload = ops->copy_construct(other.payload);
			}
			else
			{
				payload = other.payload;
			}
		}
		else
		{
			payload = nullptr;
		}
	}

	any::any(any&& other) noexcept
		:payload(std::move(other.payload)), typeinfo(std::move(other.typeinfo)),
		store(std::move(other.store)),ops(std::move(other.ops)),variant(std::move(other.variant))
	{
		other.store = any::Null;
		other.payload = nullptr;
		other.ops = nullptr;
		other.typeinfo = nullptr;
		other.variant = NullType;
	}
}
