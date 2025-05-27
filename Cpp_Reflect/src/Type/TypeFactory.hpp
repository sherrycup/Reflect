#pragma once
#include "head/type.hpp"
#include"Numeric.hpp"
#include"Enum.hpp"
#include"Bool.hpp"
#include"Void.hpp"

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
			info_.setName(name);
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
			info_.setName(name);
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
			info_.setName(name);
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
	private:
		Void info_;
		VoidFactory(Void&& info) : info_(std::move(info)) {}
	};
}