#pragma once
#include "head/type.hpp"
#include"Numeric.hpp"
#include"Enum.hpp"
#include"Class.hpp" 
#include"Bool.hpp"
#include"Void.hpp"
#include"String.hpp"

namespace Reflect
{
	template <typename T>
	class NumericFactory
	{
	public:
		static NumericFactory& GetInstance()
		{
			static NumericFactory inst{Numeric::Create<T>()};
			static bool is_register = false;
			if (!is_register) {
				TypenameList::GetInstance().add(&inst.info_);
				is_register = true;
			}
			return inst;
		}
		NumericFactory& setName(const std::string& name)
		{
			info_.name_ = name;
			return *this;
		}
		const Numeric* getInfo() const { return &info_; }
	protected:

	private:
		Numeric info_;
		NumericFactory(Numeric&& info): info_(std::move(info)) {}

	};


	class EnumFactory
	{
	public:
		static EnumFactory& GetInstance()
		{
			static EnumFactory inst{Enum::Create()};
			static bool is_register = false;
			if (!is_register) {
				TypenameList::GetInstance().add(&inst.info_);
				is_register = true;
			}
			return inst;
		}

		const Enum* getInfo() const { return &info_; }

		EnumFactory& setName(const std::string& name)
		{
			info_.name_ = name;
			return *this;
		}
	protected:

	private:
		Enum info_;
		EnumFactory(Enum&& info) :info_(std::move(info)){}
	};


	class BoolFactory
	{
	public:
		static BoolFactory& GetInstance()
		{
			static BoolFactory inst{ Bool::Create() };
			static bool is_register = false;
			if (!is_register) {
				TypenameList::GetInstance().add(&inst.info_);
				is_register = true;
			}
			return inst;
		}

		BoolFactory& setName(const std::string& name)
		{
			info_.name_ = name;
			return *this;
		}



		const Bool* getInfo() const { return &info_; }

	private:
		Bool info_;
		BoolFactory(Bool&& info) : info_(std::move(info)) {}
	};

	class VoidFactory
	{
	public:
		static VoidFactory& GetInstance()
		{
			static VoidFactory inst{ Void::Create() };
			static bool is_register = false;
			if (!is_register) {
				TypenameList::GetInstance().add(&inst.info_);
				is_register = true;
			}
			return inst;
		}

		VoidFactory& setName(const std::string& name)
		{
			info_.name_ = name;
			return *this;
		}

		const Void* getInfo() const { return &info_; }
	private:
		Void info_;
		VoidFactory(Void&& info) : info_(std::move(info)) {}
	};

	class ClassFactory
	{
	public:
		static ClassFactory& GetInstace()
		{
			static ClassFactory inst{ Class::Create() };
			static bool is_register = false;
			if (!is_register) {
				TypenameList::GetInstance().add(&inst.info_);
				is_register = true;
			}
			return inst;
		}

		ClassFactory& setName(const std::string& name)
		{
			info_.name_ = name;
			return *this;
		}

		template<typename U>
		ClassFactory& addVariable(const std::string& name,U ptr)
		{
			using temp = typename field_trait<U>::trait;
			using T = typename temp::type;
			using Clazz = typename temp::clazz_type;
			info_.addVariable(MemberVariable<T, Clazz>::Create(name,ptr));
			return *this;
		}

		template<typename U>
		ClassFactory& addFunction(const std::string& name, U ptr)
		{
			using temp = typename field_trait<U>::trait;
			using Ret = typename temp::ret_type;
			using Clazz = typename temp::clazz_type;
			using Tuple = typename temp::args;

			std::apply([&](auto... args) {
				info_.addFunction(MemberFunction<Ret, Clazz, decltype(args)...>::Create(name,ptr));
				}, Tuple{});

			
			return *this;
		}

		const Class* getInfo() const { return &info_; }
	protected:

	private:
		Class info_;
		ClassFactory(Class&& info) : info_(std::move(info)) {}
	};

	class StringFactory
	{
	public:
		static StringFactory& GetInstance()
		{
			static StringFactory inst{ String::Create() };
			static bool is_register = false;
			if (!is_register) {
				TypenameList::GetInstance().add(&inst.info_);
				is_register = true;
			}
			return inst;
		}

		StringFactory& setName(const std::string& name)
		{
			info_.name_ = name;
			return *this;
		}

		const String* getInfo() const { return &info_; }
	protected:

	private:
		String info_;
		StringFactory(String&& info) : info_(std::move(info)) {}
	};
}