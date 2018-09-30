
namespace ec
{
	template<class Resource>
	ResourceRegistry<Resource>::ResourceRegistry()
	= default;

	template<class Resource>
	ResourceRegistry<Resource>::~ResourceRegistry()
	= default;

	template<class Resource>
	Resource* ResourceRegistry<Resource>::registerResource(Resource_Ptr resource, const std::string& key)
	{
		auto foundResource = getResource(key);
		if(foundResource != nullptr)
		{
			return foundResource;
		}

		m_resources[key] = resource;
		return getResource(key);
	}

	template<class Resource>
	typename ResourceRegistry<Resource>::Resource_Ptr ResourceRegistry<Resource>::unregisterResource(const std::string& key)
	{
		auto foundResource = getResource(key);
		if(foundResource == nullptr)
		{
			return nullptr;
		}

		auto retVal = foundResource->second;
		m_resources.erase(foundResource);
		return retVal;
	}

	template<class Resource>
	Resource* ResourceRegistry<Resource>::getResource(const std::string& key) const
	{
		auto foundResource = m_resources.find(key);
		if(foundResource == m_resources.end())
		{
			return nullptr;
		}
		return foundResource->second;
	}	

	template<class Resource>
	bool ResourceRegistry<Resource>::isRegistered(const std::string& key) const
	{
		return getResource(key) != nullptr;
	}


	template<class Resource>
	bool ResourceRegistry<Resource>::isRegistered(Resource* resource) const
	{
		for(const auto& it : m_resources)
		{
			if(it.second == resource)
			{
				return true;
			}
		}
		return false;
	}
}