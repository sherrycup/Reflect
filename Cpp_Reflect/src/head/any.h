#pragma once
//#include"../Log/Log.h"

namespace Reflect
{
	class any final
	{
	public:
		template<typename T>
		friend any make_any_copy(T&&);

		template<typename T>
		friend any make_any_ref(T&);

		template<typename T>
		friend const any make_any_cref(const T&);

		template<typename T>
		friend T* cast_any(any&);

		template<typename T>
		friend T* cast_any_const(const any&);

		enum type_access
		{
			Copy,
			Ref,
			Move,
			CRef,

		};
		struct type_operations
		{
			any(*copy)(const any&);
			any(*move)(any&&);
			any& (*ref)(const any&);
			const any& (*cref)(const any&);
			void(*release)();
		};

		any() = default;
		any(const any&);
		any(any&&);
		~any() {
			ops.release();
		}
	private:
		void* payload;
		type_access store;
		type_operations ops;

	};


}