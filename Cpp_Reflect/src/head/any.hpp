#pragma once
#include"Log/Log.h"

namespace Reflect
{

    struct type_operations final {
        using destroy_fn = void(*)(void*);
        using copy_construct_fn = void*(*) (void*);
        using steal_construct_fn = void* (*)(void*);


        destroy_fn destroy = empty_destroy;
        copy_construct_fn copy_construct = empty_copy;
        steal_construct_fn steal_construct = empty_steal;


        static type_operations null;

    private:
        static void empty_destroy(void*) {}
        static void* empty_copy(void*) { return nullptr; }
        static void* empty_steal(void*) { return nullptr; }

    };

    template <typename T>
    struct type_operation_traits {
        static void destroy(void* elem) {
            delete[](T*)(elem);

        }

        static void* copy_construct(void* elem) {
            return new T{ *(const T*)elem };

        }

        static void* steal_construct(void* elem) {
            return new T{ std::move(*(T*)elem) };

        }

        static auto& get_operations() {
            using traits = type_operation_traits<T>;

            static type_operations operations = {
                traits::destroy,
                traits::copy_construct,
                traits::steal_construct
            };
            return operations;
        }
    };

	class any final
	{
	public:
		template<typename T>
		friend any make_any_copy(const T&);

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

        void print() {
            LOG_INFO(*(int*)payload);
        }

		any(void* payload, type_access store, type_operations* ops);
        any() = default;
		any(const any&);
		any(any&&);
        ~any() {}
	private:
		void* payload;
		type_access store;
		type_operations* ops;

	};

    // 声明友元函数，在make_any中实现
    template<typename T> any make_any_copy(const T& value)
    {
        LOG_INFO("拷贝生成any");
        void* elem = nullptr;

        elem = new T{ value };

        type_operations ops = type_operation_traits<T>::get_operations();
        return { elem,any::Copy, &ops };
    }
    template<typename T> any make_any_ref(T& value);
    template<typename T> const any make_any_cref(const T& value);
    template<typename T> T* cast_any(any& a);
    template<typename T> T* cast_any_const(const any& a);

}