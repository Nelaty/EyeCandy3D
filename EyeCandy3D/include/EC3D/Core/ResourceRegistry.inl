#include <algorithm>

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
	bool ResourceRegistry<Resource>::RegisterResource(Resource_Ptr resource, const std::string& key)
	{
		if(IsRegistered(key)) return false;

		m_resources.insert(std::make_pair(key, resource));
		return true;
	}

	template<class Resource>
	Resource* ResourceRegistry<Resource>::UnregisterResource(const std::string& key)
	{
		auto foundResource = m_resources.find(key);
		if(foundResource == m_resources.end())
		{
			return nullptr;
		}
		else
		{
			m_resources.erase(foundResource);
			return foundResource->second;
		}
	}

	template<class Resource>
	Resource* ResourceRegistry<Resource>::GetResource(const std::string& key)
	{
		auto foundResource = m_resources.find(key);
		if(foundResource == m_resources.end())
		{
			return nullptr;
		}
		else
		{
			return foundResource->second;
		}
	}	

	template<class Resource>
	bool ResourceRegistry<Resource>::IsRegistered(const std::string& key)
	{
		return GetResource(key) == nullptr;
	}


	template<class Resource>
	bool ResourceRegistry<Resource>::IsRegistered(Resource_Ptr)
	{
		return false;
	}
}