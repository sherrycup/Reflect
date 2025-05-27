#pragma once

#include"head/type.hpp"
#include<vector>

namespace Reflect
{
	// 类型列表
	class TypenameList final
	{
	public:
		static TypenameList& GetInstance()
		{
			static TypenameList inst;
			return inst;
		}
		void add(const Type* info) {
			list.push_back(info);
		}
		std::vector<const Type*>& getVector() { return list; }
	private:
		std::vector<const Type*> list;
		TypenameList() {}
	};

	const Type* GetType(const std::string& name)
	{
		std::vector<const Type*> v = TypenameList::GetInstance().getVector();
		for (auto typeinfo : v)
		{
			if (typeinfo->getName() == name) {
				return typeinfo;
			}
		}
		return nullptr;
	}
	
}