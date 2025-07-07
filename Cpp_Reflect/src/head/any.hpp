#pragma once

#include"Log/Log.h"
#include"Traits/field_trait.hpp"
#include"type.hpp"

namespace Reflect
{
    enum Variant
    {
        NullType,
        ValueType,
        PointerType,
        ReferenceType
    };

    template<typename T>
    const Type* GetType();

    struct type_operations final {
        using destroy_fn = void(*)(void*);
        using copy_construct_fn = void* (*) (void*);
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
            delete (T*)(elem);

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

    // 对指针类型进行特化
    template <typename T>
    struct type_operation_traits<T*> {
        static void destroy(void* elem) {
            T* ptr = *static_cast<T**>(elem);
            delete ptr;  // 删除实际对象
            delete static_cast<T**>(elem);  // 删除存储指针的内存

        }

        static void* copy_construct(void* elem) {
            T* original = *static_cast<T**>(elem);
            return new T*(new T(*original));  // 深拷贝
        }

        static void* steal_construct(void* elem) {
            return new T{ std::move(*(T*)elem) };

        }

        static auto& get_operations() {
            using traits = type_operation_traits<T*>;

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

        friend std::ostream& operator<<(std::ostream& os, const any& elem);

        enum type_access
        {
            Copy,
            Ref,
            Move,
            CRef,
            Null,
        };



        void print() {
            //
            //LOG_INFO(*str);
        }

        any(void* payload, const Type* typeinfo, type_access store, type_operations* ops, Variant v);
        any() = default;
        any(const any&);
        any(any&&) noexcept;
        ~any() 
        {
            if (store == Copy && payload != nullptr && ops != nullptr)
            {
                ops->destroy(payload);
            }
            payload = nullptr;
        }

        const Type* getTypeInfo() const
        {
            return typeinfo;
        }

        void* getPayload() const
        {
            return payload;
        }

        Variant getVariant() const
        {
            return variant;
        }
    private:
        void* payload;
        type_access store;
        type_operations* ops;
        const Type* typeinfo{};
        Variant variant;

        
    };

    // 获取类型函数
    template<typename T>
    Variant detectVariant()
    {
        Variant v = Variant::ValueType;
        if (std::is_pointer_v<T>) {
            v = Variant::PointerType;
        }
        else if constexpr (std::is_reference_v<T>) {
            v = Variant::ReferenceType;
        }
        return v;
    }

    // 声明友元函数实现
    template<typename T> any make_any_copy(const T& value)
    {
        LOG_INFO("拷贝生成any");
        void* elem = nullptr;

        elem = new T{ value };

        static type_operations ops = type_operation_traits<T>::get_operations();
        return { elem, GetType<T>(),any::Copy, &ops,  detectVariant<T>()};
    }
    template<typename T> any make_any_ref(T& value)
    {
        LOG_INFO("引用生成any");
        void* elem = nullptr;
        elem = (void*)&value;

        static type_operations ops = type_operation_traits<T>::get_operations();
        return { elem,GetType<T>(), any::Ref, &ops , detectVariant<T>() };
    }
    template<typename T> const any make_any_cref(const T& value)
    {
        LOG_INFO("常量引用生成any");
        void* elem = nullptr;
        elem = (void*)&value;

        static type_operations ops = type_operation_traits<T>::get_operations();
        return { elem,GetType<T>(), any::CRef, &ops , detectVariant<T>() };
    }
    template<typename T> T* cast_any(any& a)
    {
        // 如果能转换的判定

        return  static_cast<T*>(a.payload);
    }
    template<typename T> T* cast_any_const(const any& a)
    {
        return  static_cast<T*>(a.payload);

    }

}


