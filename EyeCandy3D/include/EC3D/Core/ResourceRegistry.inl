
namespace ec
{
	template<class Resource, class Key_Type>
	ResourceRegistry<Resource, Key_Type>
	::ResourceRegistry()
	= default;

	template<class Resource, class Key_Type>
	ResourceRegistry<Resource, Key_Type>
	::~ResourceRegistry()
	= default;

	template<class Resource, class Key_Type>
	Resource* ResourceRegistry<Resource, Key_Type>
	::registerResource(Resource_Ptr resource, const Key_Type& key)
	{
		auto foundResource = getResource(key);
		if(foundResource != nullptr)
		{
			return foundResource;
		}

		m_resources[key] = resource;
		return getResource(key);
	}

	template<class Resource, class Key_Type>
	typename ResourceRegistry<Resource, Key_Type>::Resource_Ptr ResourceRegistry<Resource, Key_Type>
	::unregisterResource(const Key_Type& key)
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

	template<class Resource, class Key_Type>
	Resource* ResourceRegistry<Resource, Key_Type>
	::getResource(const Key_Type& key) const
	{
		auto foundResource = m_resources.find(key);
		if(foundResource == m_resources.end())
		{
			return nullptr;
		}
		return foundResource->second;
	}	

	template<class Resource, class Key_Type>
	bool ResourceRegistry<Resource, Key_Type>
	::isRegistered(const Key_Type& key) const
	{
		return getResource(key) != nullptr;
	}


	template<class Resource, class Key_Type>
	bool ResourceRegistry<Resource, Key_Type>
	::isRegistered(Resource* resource) const
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