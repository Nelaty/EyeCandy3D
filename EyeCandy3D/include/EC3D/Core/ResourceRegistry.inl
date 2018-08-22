
namespace ec
{
	template<class Resource>
	ResourceRegistry<Resource>::ResourceRegistry()
	{
	}

	template<class Resource>
	ResourceRegistry<Resource>::~ResourceRegistry()
	{
	}

	template<class Resource>
	bool ResourceRegistry<Resource>::registerResource(Resource_Ptr resource, const std::string& key)
	{
		if(isRegistered(key)) return false;

		m_resources.insert(std::make_pair(key, resource));
		return true;
	}

	template<class Resource>
	Resource* ResourceRegistry<Resource>::unregisterResource(const std::string& key)
	{
		auto foundResource = m_resources.find(key);
		if(foundResource == m_resources.end())
		{
			return nullptr;
		}
		m_resources.erase(foundResource);
		return foundResource->second;
	}

	template<class Resource>
	Resource* ResourceRegistry<Resource>::getResource(const std::string& key)
	{
		auto foundResource = m_resources.find(key);
		if(foundResource == m_resources.end())
		{
			return nullptr;
		}
		return foundResource->second;
	}	

	template<class Resource>
	bool ResourceRegistry<Resource>::isRegistered(const std::string& key)
	{
		return getResource(key) == nullptr;
	}


	template<class Resource>
	bool ResourceRegistry<Resource>::isRegistered(Resource_Ptr)
	{
		return false;
	}
}