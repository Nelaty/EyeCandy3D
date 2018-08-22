#pragma once
#include <string>
#include <map>

namespace ec
{
	template<class Resource>
	class ResourceRegistry
	{
	public:
		using Resource_Ptr = Resource*;
		using Resource_Container = std::map<std::string, Resource_Ptr>;

	public:
		explicit ResourceRegistry();
		~ResourceRegistry();

		bool registerResource(Resource_Ptr resource, const std::string& key);
		Resource* unregisterResource(const std::string& key);

		Resource* getResource(const std::string& key);
		bool isRegistered(const std::string& key);
		bool isRegistered(Resource_Ptr);

	private:
		Resource_Container m_resources;
	};
}

#include "ResourceRegistry.inl"