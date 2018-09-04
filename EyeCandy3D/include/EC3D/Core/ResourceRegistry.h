#pragma once
#include <string>
#include <map>
#include <memory>

namespace ec
{
	template<class Resource>
	class ResourceRegistry
	{
	public:
		using Resource_Ptr = Resource*;
		using Resource_Container = std::map<std::string, Resource_Ptr>;

		explicit ResourceRegistry();
		~ResourceRegistry();

		Resource* registerResource(Resource_Ptr resource, const std::string& key);
		Resource_Ptr unregisterResource(const std::string& key);

		Resource* getResource(const std::string& key);
		bool isRegistered(const std::string& key);
		bool isRegistered(Resource* resource);

	private:
		Resource_Container m_resources;
	};
}

#include "ResourceRegistry.inl"