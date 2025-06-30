#pragma once
#include <fstream>
#include <filesystem>
#include "nlohmann/json.hpp"
#include "sref_method.hpp"

namespace Reflect
{
	class JsonGenerator final
	{
	public:
		static JsonGenerator GetInstance()
		{
			static JsonGenerator inst;
			return inst;
		}

		template<typename T>
		void CreatJson(TypeInfo<T>& typeinfo)
		{
			// 如果不存在文件夹就创建一个
			std::filesystem::create_directories("Asset");
			// 路径构建
			std::filesystem::path filepath = std::filesystem::path("Asset") / (std::string(typeinfo.name) + ".json");
			std::string filename = filepath.string();

			nlohmann::json file = generateJson(typeinfo);
			// 检查文件是否存在相同内容
			if (std::filesystem::exists(filepath))
			{
				try
				{
					// 判断文件是否相同
					std::ifstream inFile(filename);
					nlohmann::json currentJson = nlohmann::json::parse(inFile);

					if (file == currentJson)
					{
						LOG_INFO("文件内容相同，不覆盖" + filename);
						return;
					}
				}
				catch(const std::exception& e)
				{
					LOG_WARN("读取JSON文件失败，重新创建JSON" + std::string(e.what()));
				}
			}

			//std::string json_str = file.dump(4);

			std::ofstream outFile(filename);
			if (!outFile.is_open())
			{
				LOG_ERROR("无法打开 JSON 文件！");
			}
			// 输出json
			outFile << file.dump(4);
			outFile.close();
			LOG_INFO("JSON文件已写入！");
		}
	private:
		JsonGenerator() {}

		std::string access2string(Access acc)
		{
			switch (acc)
			{
			case Reflect::Public:
				return "Public";
			case Reflect::Private:
				return "Private";
			case Reflect::Protected:
				return "Protected";
			default:
				return "Unknown";
			}
		}

		template<typename T>
		nlohmann::json generateJson(const TypeInfo<T>& typeinfo)
		{
			//创建json文件
			nlohmann::json file;
			nlohmann::json vars, funcs;
			std::vector<Access> acc;

			// 装配类名
			file["class_name"] = typeinfo.name;

			// 装配字段
			std::vector<std::string> names = getDeclearedField(typeinfo, acc);
			for (int i = 0; i < names.size(); i++) {
				std::string_view temp = names[i];
				size_t type_pos = temp.find_first_of(" ");
				if (type_pos == std::string_view::npos) continue;

				vars.push_back({
					{"Type", temp.substr(0, type_pos)},
					{"Name", temp.substr(type_pos + 1)},
					{"Access", access2string(acc[i])}
					});
			}
			acc.clear();

			// 装配方法
			names = getDeclearedMethod(typeinfo, acc);
			for (int i = 0; i < names.size(); i++) {
				std::string_view temp = names[i];
				size_t type_pos = temp.find_first_of(" ");
				size_t left_paren = temp.find_first_of("(");

				if (type_pos == std::string_view::npos || left_paren == std::string_view::npos)
					continue;

				funcs.push_back({
					{"RetType", temp.substr(0, type_pos)},
					{"Name", temp.substr(type_pos + 1, left_paren - type_pos - 1)},
					{"Param", temp.substr(left_paren)},
					{"Access", access2string(acc[i])}
					});
			}

			// 组装json
			file["functions"] = funcs;
			file["variables"] = vars;

			return file;
		}
	};
}