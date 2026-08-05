#pragma once
#include "Resource.h"
#include <map>
#include <string>
#include <iostream>

namespace nu {
	class ResourceManager {
	public:
		template<typename T, typename ... Args>
		res_t<T> Get(const std::string& name, Args&& ... args);

	private:
		std::map<std::string, res_t<Resource>> m_resources;
	};


	template<typename T, typename ...Args>
	inline res_t<T> ResourceManager::Get(const std::string& name, Args && ...args)
	{
		auto iter = m_resources.find(name);
		//check if resource exists
		if (iter != m_resources.end()) {
			auto base = iter->second;
			auto resource = std::dynamic_pointer_cast<T>();

			if (resource == nullptr) {
				std::cerr << "Resource type mismatch: " << name << std::end;
				return res_t<T>();
			}

			return resource;
		}

		//resource deosnt exist, create and load
		res_t<T> resource = std::make_shared<T>();
		if (!resource->Load(name, std::forward<Args>(args)...)) {
			std::cerr << "Could not load resource: " << name << std::end;
			return res_t<T>();
		}




		return resource;
	}
}
