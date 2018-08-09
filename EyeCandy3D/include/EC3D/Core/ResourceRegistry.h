#pragma once
#include "EC3D/Core/Texture.h"
#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Material.h"
#include "EC3D/Core/Drawable.h"

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

		bool RegisterResource(Resource_Ptr resource, const std::string& key);
		Resource* UnregisterResource(const std::string& key);

		Resource* GetResource(const std::string& key);
		bool IsRegistered(const std::string& key);
		bool IsRegistered(Resource_Ptr);

	private:
		Resource_Container m_resources;
	};
}

#include "ResourceRegistry.inl"