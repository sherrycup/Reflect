#pragma once
#include "head/type.hpp"
#include "head/any.hpp"
#include<vector> 
#include<memory>
#include<variant>

namespace Reflect
{
	// 先行声明函数
	template<typename T>
	const Type* GetType();

	class Member
	{
	public:
		virtual ~Member() = default;

		/*	关于call函数
		*	参数形式为(class& obj, param...)
		*	第一个参数为实例对象，后面的参数为函数所需的参数
		*/
		virtual any call(const std::vector<any>& args) = 0;
		virtual std::string to_string() const = 0;

		virtual std::string getName() const
		{
			return  "No name";
		}

	};

	template<typename T, typename Clazz>
	class MemberVariable : public Member
	{
	public:
		/*
			目前只实现call函数的get和set
			get 一个实例参数  size = 1
			set 一个实例参数 一个赋值参数 size = 2
		*/
		any call(const std::vector<any>& anies) override
		{
			// 判定大小在1-2之间 且第一个参数是类实例
			assert(anies.size()!=0 && anies.size()<=2 && anies[0].getTypeInfo() == GetType<Clazz>());
			Clazz* instance = (Clazz*)anies[0].getPayload();	// 强转
			if (anies.size() == 1) {	// 执行get操作
				auto value = instance->*ptr_;
				return make_any_copy(value);
			}
			else	// 执行set操作
			{
				assert(type_->getKind() == anies[1].getTypeInfo()->getKind());
				std::variant<char,unsigned char,short,unsigned short,int ,unsigned int,long, unsigned long,
							long long,unsigned long long,float ,double> value;
				switch (anies[1].getTypeInfo()->getKind())
				{
				case Type::Numeric:
					switch (anies[1].getTypeInfo()->asNumeric()->getKind())
					{
					case Numeric::Char:
						if (anies[1].getTypeInfo()->asNumeric()->getIsSigned())
						{
							value = *static_cast<char*>(anies[1].getPayload());
						}
						else
						{
							value = *static_cast<unsigned char*>(anies[1].getPayload());
						}
						break;
					case Numeric::Short:
						if (anies[1].getTypeInfo()->asNumeric()->getIsSigned())
						{
							value = *static_cast<short*>(anies[1].getPayload());
						}
						else
						{
							value = *static_cast<unsigned short*>(anies[1].getPayload());
						}
						break;
					case Numeric::Int:
						if (anies[1].getTypeInfo()->asNumeric()->getIsSigned())
						{
							value = *static_cast<int*>(anies[1].getPayload());
						}
						else
						{
							value = *static_cast<unsigned int*>(anies[1].getPayload());
						}
						break;
					case Numeric::Long:
						if (anies[1].getTypeInfo()->asNumeric()->getIsSigned())
						{
							value = *static_cast<long*>(anies[1].getPayload());
						}
						else
						{
							value = *static_cast<unsigned long*>(anies[1].getPayload());
						}
						break;
					case Numeric::LongLong:
						if (anies[1].getTypeInfo()->asNumeric()->getIsSigned())
						{
							value = *static_cast<long long*>(anies[1].getPayload());
						}
						else
						{
							value = *static_cast<unsigned long long*>(anies[1].getPayload());
						}
						break;
					case Numeric::Float:
						value = *static_cast<float*>(anies[1].getPayload());
						break;
					case Numeric::Double:
						value = *static_cast<double*>(anies[1].getPayload());
						break;
					default:
						LOG_ERROR("非法的Numeric类型");
						break;
					}
				default:
					break;
				}

				switch (type_->getKind())
				{
				case Type::Numeric:
					switch (type_->asNumeric()->getKind())
					{
					case Numeric::Char:
						if (type_->asNumeric()->getIsSigned())
						{
							instance->*ptr_ = std::get<char>(value);
						}
						else
						{
							instance->*ptr_ = std::get<unsigned char>(value);
						}
						break;
					case Numeric::Short:
						if (type_->asNumeric()->getIsSigned())
						{
							instance->*ptr_ = std::get<short>(value);
						}
						else
						{
							instance->*ptr_ = std::get<unsigned short>(value);
						}
						break;
					case Numeric::Int:
						if (type_->asNumeric()->getIsSigned())
						{
							instance->*ptr_ = std::get<int>(value);
						}
						else
						{
							instance->*ptr_ = std::get<unsigned int>(value);
						}
						break;
					case Numeric::Long:
						if (type_->asNumeric()->getIsSigned())
						{
							instance->*ptr_ = std::get<long>(value);
						}
						else
						{
							instance->*ptr_ = std::get<unsigned long>(value);
						}
						break;
					case Numeric::LongLong:
						if (type_->asNumeric()->getIsSigned())
						{
							instance->*ptr_ = std::get<long long>(value);
						}
						else
						{
							instance->*ptr_ = std::get<unsigned long long>(value);
						}
						break;
					case Numeric::Float:
						instance->*ptr_ = std::get<float>(value);
						break;
					case Numeric::Double:
						instance->*ptr_ = std::get<double>(value);
						break;
					default:
						LOG_ERROR("非法的Numeric类型");
						break;
					}
				default:
					break;
				}

				return make_any_copy(instance->*ptr_);
			}
		
			
		}

		MemberVariable(const std::string& name,const Type* type, T Clazz::* ptr)
			:type_(type), name_(name),ptr_(ptr)
		{

		}

		static MemberVariable Create(const std::string& name, T Clazz::* ptr)
		{

			return { name , GetType<T>() , ptr};
		}

		std::string getName() const override
		{
			return name_;
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
		any call(const std::vector<any>& args) override
		{
			return make_any_copy<int>(1);
		}
		MemberFunction(const std::string& name, const Type* ret,const std::vector<const Type*>& params, Ret(Clazz::* ptr)(Args...))
			:name_(name), retType_(ret),paramTypes_(std::move(params)),ptr_(ptr)
		{

		}
		static MemberFunction Create(const std::string& name, Ret(Clazz::* ptr)(Args...))
		{
			using args = typename std::tuple<Args...>;
			bool tag = (std::is_same_v<int, Args> || ...);
			std::cout << tag << std::endl;
			std::vector<const Type*> paramTypes = { GetType<Args>()... };
			return { name, GetType<Ret>(), paramTypes, ptr};
		}

		std::string getName() const override
		{
			return name_;
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

		Member* getVariable(const std::string& name)
		{
			for (const auto& ptr : vars_)
			{
				if (ptr->getName() == name)
				{
					return ptr.get();
				}
			}
			return nullptr;
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