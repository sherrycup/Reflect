#pragma once
#include "head/type.hpp"
#include "head/any.hpp"
#include<vector> 
#include<memory>

namespace Reflect
{
	class Member
	{
		virtual ~Member() = default;
		virtual any call(std::vector<any>& args) = 0;
	};

	template<typename T, typename Clazz>
	class MemberVariable : public Member
	{
	public:
		any call(std::vector<any>& args) override
		{

		}
		static MemberVariable Create();
	protected:

	private:
		T Clazz::* ptr;
	};

	template<typename Ret,typename Clazz,typename... Args>
	class MemberFunction : public Member
	{
	public:
		any call(std::vector<any>& args) override
		{

		}
		static MemberFunction Create();
	protected:

	private:
		Ret(Clazz::* ptr)(Args...);
	};

	class Class : public Type
	{
	public:
		Class(std::string name)
			:Type{ name, Type::Class }
		{

		}
	protected:

	private:
		std::vector<std::unique_ptr<Member>> vars_;
		std::vector<std::unique_ptr<Member>> funcs_;
	};
}