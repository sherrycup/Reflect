#pragma once

namespace Reflect
{
	class JsonLoader final
	{
	public:
		static JsonLoader GetInstance()
		{
			static JsonLoader inst;
			return inst;
		}
	private:

	};
}