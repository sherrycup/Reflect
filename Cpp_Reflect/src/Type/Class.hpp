#pragma once
#include "head/type.hpp"
#include "head/any.hpp"
#include<vector> 
#include<memory>
#include<variant>

namespace Reflect
{

	template<typename T>
	T unwrap(const any& value)
	{
		return *(T*)value.getPayload();
	}

	template<typename Ret,typename Clazz, typename... Args, size_t... Idx>
	any inner_call(Ret(Clazz::*ptr)(Args...), const std::vector<any>& params,std::index_sequence<Idx...>)
	{
		Variant variant = params[0].getVariant();
		Ret return_value;
		if (variant == Variant::ValueType || variant == Variant::ReferenceType)
		{
			return_value = ((Clazz*)params[0].getPayload()->*ptr)(unwrap<Args>(params[Idx + 1])...);
		}
		else
		{
			return_value = (*(Clazz**)params[0].getPayload()->*ptr)(unwrap<Args>(params[Idx + 1])...);
		}
		
		return make_any_copy(return_value);
	}
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
			Variant variant = anies[0].getVariant();
			Clazz* instance;
			if (variant == Variant::ValueType || variant == Variant::ReferenceType)
			{
				// 此时void*储存的是指向类对象的指针
				instance = (Clazz*)anies[0].getPayload();	// 强转
			}
			else
			{
				// 此时void*储存的是指向类指针的指针
				instance = *(Clazz**)anies[0].getPayload(); // 解引强转
			}
			
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
		/*
			直接调用函数 第一个参数是类实例 后面的参数是所需要的参数
		*/
		any call(const std::vector<any>& anies) override
		{
			assert(anies.size() == paramTypes_.size() + 1);
			for (int i = 0;i < paramTypes_.size();i++)
			{
				assert(paramTypes_[i] == anies[i + 1].getTypeInfo());
			}
			return inner_call(ptr_, anies, std::make_index_sequence<sizeof...(Args)>());
		}
		MemberFunction(const std::string& name, const Type* ret,const std::vector<const Type*>& params, Ret(Clazz::* ptr)(Args...))
			:name_(name), retType_(ret),paramTypes_(std::move(params)),ptr_(ptr)
		{

		}
		static MemberFunction Create(const std::string& name, Ret(Clazz::* ptr)(Args...))
		{
			using args = typename std::tuple<Args...>;
			//bool tag = (std::is_same_v<int, Args> || ...);
			//std::cout << tag << std::endl;
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

	class Ctor
	{
	public:
		Ctor() {}
		virtual any createInstance(const std::vector<any>& anies) const = 0;
		virtual Access getAccess() const = 0;
		virtual std::vector<const Type*> getParam() const = 0;
	private:
		
		
	protected:

	};

	template<typename Class,typename... Args>
	class CtorFunc : public Ctor
	{
	public:
		
		CtorFunc(const std::vector<const Type*>& param, std::function <Class* (const std::vector<any>&)> invoke,Access acc)
			:paramType_(param), invoker(invoke), access(acc)
		{

		}

		/*
			生成构造函数包装
		*/
		static CtorFunc Create(Access access)
		{
			std::vector<const Type*> param = { GetType<Args>()... };
			auto invoke = [](const std::vector<any>& anies) -> Class*
				{
					// 检查参数数量是否匹配
					assert(anies.size() == sizeof...(Args), "构造参数数量不匹配");

					// 
					return createClass2Any<Class, Args...>(anies);
				};

			return {param, invoke, access};
		}

		/*
			生成实例
		*/
		any createInstance(const std::vector<any>& anies) const override
		{
			Class* obj = invoker(anies);
			return make_any_copy(obj);
		}

		/*
			返回变量
		*/
		Access getAccess() const override { return access; }
		std::vector<const Type*> getParam() const override{ return paramType_; }

		/*
			输出字符
		*/
		std::string to_string() const
		{

		}
	private:
		std::function <Class*(const std::vector<any>&)> invoker;
		std::vector<const Type*> paramType_;
		Access access;

		template<typename Class, typename... Args>
		static Class* createClass2Any(const std::vector<any>& anies)
		{
			return cvtParam2TypeParam<Class, Args...>(
				anies,
				std::make_index_sequence<sizeof...(Args)>{}
			);
		}

		template<typename Class, typename... Args, size_t... I>
		static Class* cvtParam2TypeParam(const std::vector<any>& anies, std::index_sequence<I...>)
		{
			Class* obj = new Class(*cast_any_const<Args>(anies[I])...);
			return obj;
		}
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

		template<typename Class,typename... Args>
		void addCtor(CtorFunc<Class,Args...>&& ctor)
		{
			ctors_.emplace_back(std::make_unique<CtorFunc<Class,Args...>>(std::move(ctor)));
			LOG_INFO("注册构造函数结束");
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

		any getVariable(const std::string& name, const std::vector<any>& anies)
		{
			for (const auto& ptr : vars_)
			{
				if (ptr->getName() == name)
				{
					return ptr.get()->call(anies);
				}
			}
			//return nullptr;
		}

		Member* getFunction(const std::string& name)
		{
			for (const auto& ptr : funcs_)
			{
				if(ptr->getName() == name)
				{
					return ptr.get();
				}
			}
			return nullptr;
		}

		any getFunction(const std::string& name, const std::vector<any>& anies)
		{
			for (const auto& ptr : vars_)
			{
				if (ptr->getName() == name)
				{
					return ptr.get()->call(anies);
				}
			}
			//return nullptr;
		}

		any createInstance(const std::vector<any>& anies)
		{
			try {
				bool findctor = true;
				// 找到符合参数列表的构造函数
				for (const auto& ptr : ctors_)
				{
					findctor = true;
					if (ptr->getAccess() != Access::Public || ptr->getParam().size() != anies.size())
					{
						// 不是public构造函数无法调用
						findctor = false;
					}
					else
					{
						std::vector<const Type*> types = ptr->getParam();
						// 对比函数参数和现有参数一一对应的关系
						for (int i = 0;i < types.size();i++)
						{
							if (types[i] != anies[i].getTypeInfo())
							{
								findctor = false;
								break;
							}
						}
					}
					if (findctor)
					{
						return ptr->createInstance(anies);
					}
				}
				throw std::runtime_error("没有合适的实例");
			}
			catch(const std::exception e)
			{
				LOG_ERROR("无法生成实例");
				
			}
			
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
		std::vector<std::unique_ptr<Ctor>> ctors_;
	};
}