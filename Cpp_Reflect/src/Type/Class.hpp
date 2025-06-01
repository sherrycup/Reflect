#pragma once
#include "head/type.hpp"
#include "head/any.hpp"
#include<vector> 
#include<memory>

namespace Reflect
{
	// 先行声明函数
	template<typename T>
	const Type* GetType();

	class Member
	{
	public:
		virtual ~Member() = default;
		virtual any call(std::vector<any>& args) = 0;
		virtual std::string to_string() const = 0;
	};

	template<typename T, typename Clazz>
	class MemberVariable : public Member
	{
	public:
		any call(std::vector<any>& args) override
		{
			return make_any_copy<int>(1);
		}

		MemberVariable(const std::string& name,const Type* type)
			:type_(type), name_(name)
		{

		}

		static MemberVariable Create(const std::string& name)
		{

			return { name , GetType<T>() };
		}

		std::string to_string() const override
		{
			return type_->to_string();
		}

	protected:

	private:
		std::string name_;
		const Type* type_;
		T Clazz::* ptr_;
	};

	template<typename Ret,typename Clazz,typename... Args>
	class MemberFunction : public Member
	{
	public:
		any call(std::vector<any>& args) override
		{
			return make_any_copy<int>(1);
		}
		MemberFunction(const std::string& name, const Type* ret,const std::vector<const Type*>& params)
			:name_(name), retType_(ret),paramTypes_(std::move(params))
		{

		}
		static MemberFunction Create(const std::string& name)
		{
			using args = typename std::tuple<Args...>;
			bool tag = (std::is_same_v<int, Args> || ...);
			std::cout << tag << std::endl;
			std::vector<const Type*> paramTypes = { GetType<Args>()... };
			return { name, GetType<Ret>(), paramTypes};
		}

		std::string to_string() const override
		{
			std::string str = retType_->to_string() + this->name_;
			str += " ( ";
			for (int i = 0;i < paramTypes_.size();i++)
			{
				if (i == 0)
				{
					str += paramTypes_[i]->to_string();
				}
				else
				{
					str += ", " + paramTypes_[i]->to_string();
				}
			}
			str += ")";

			return str;
		}

	protected:

	private:
		template<typename Params, size_t... Idx>
		static std::vector<const Type*> cvtTpyelist2Vector(std::index_sequence<Idx...>)
		{
			return { GetType<std::tuple_element_t<Idx,Params>>() ... };
		}

		std::string name_;
		const Type* retType_;
		std::vector<const Type*> paramTypes_;
		Ret(Clazz::* ptr_)(Args...)  ;
	};

	class Class : public Type
	{
	public:
		Class(std::string name)
			:Type{ name, Type::Class }
		{

		}

		std::string getName() const
		{
			return Type::name_;
		}

		/*
		void setName(const std::string& name)
		{
			Type::name_ = name;
		}
		*/

		template<typename T,typename Clazz>
		void addVariable(MemberVariable<T, Clazz>&& var)
		{
			vars_.emplace_back(std::make_unique<MemberVariable<T,Clazz>>(std::move(var)));
		}

		template<typename Ret,typename Clazz,typename... Args>
		void addFunction(MemberFunction<Ret, Clazz, Args...>&& func)
		{
			funcs_.emplace_back(std::make_unique<MemberFunction<Ret,Clazz,Args...>>(std::move(func)));
		}

		std::string to_string() const override
		{

			// 先打印Class + 类名
			// 在打印 变量名 分割线 函数
			std::string str = "Class " + this->getName() + "\n";
			str += "Variables:\n" ;
			if (vars_.empty())
			{
				str += "  No Member Variables!\n";
			}
			else
			{
				for (const auto& var : vars_)
				{
					str += "  " + var->to_string() + "\n";
				}
			}
			str += "===================\n";
			str += "Functions:\n";
			if (funcs_.empty()) {
				str += "  No Member Functions!\n";
			}
			else
			{
				for (const auto& func : funcs_)
				{
					str += "  " + func->to_string() + "\n";
				}
			}
			str += "===================\n";
			return str;
		}

		static Class Create()
		{
			return { "" };
		}
	protected:

	private:
		std::vector<std::unique_ptr<Member>> vars_;
		std::vector<std::unique_ptr<Member>> funcs_;
	};
}