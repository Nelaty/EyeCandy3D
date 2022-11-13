#pragma once
#include "ec3/common/common.h"

#include <string>
#include <map>
#include <memory>

namespace ec
{
	/**
	 * \brief Templated registry that stores key value pairs.
	 * \tparam Resource_Type The type of the resources to store.
	 * \tparam Key_Type The resource key, used to retrieve a 
	 * resource.
	 */
	template<class Resource_Type, class Key_Type = ::std::string>
	class EC3D_DECLSPEC ResourceRegistry
	{
	public:
		using Resource_Ptr = Resource_Type*;
		using Resource_Container = std::map<Key_Type, Resource_Ptr>;

		explicit ResourceRegistry();
		~ResourceRegistry();

		/**
		 * \brief Register a new key-value pair.
		 * \param resource The resource to save.
		 * \param key The key to bind with the resource.
		 * \return The resource if it was found, nullptr otherwise.
		 */
		Resource_Type* registerResource(Resource_Ptr resource,
										const Key_Type& key);

		/**
		 * \brief Unregister an already registered resource.
		 * \param key The key of the resource to unregister.
		 * \return The resource if it was found, nullptr otherwise.
		 */
		Resource_Ptr unregisterResource(const Key_Type& key);

		/**
		 * \brief Get a reference to a registered resource.
		 * \param key The key of the resource to retrieve.
		 * \return A reference to the resource if it was found,
		 * nullptr otherwise.
		 */
		Resource_Type* getResource(const Key_Type& key) const;
		/**
		 * \brief Check if a resource is registered.
		 * \param key The key associated with the resource.
		 * \return True if it is registered, false otherwise.
		 */
		bool isRegistered(const Key_Type& key) const;
		/**
		 * \brief Check if a resource is registered.
		 * \param resource The resource to check against.
		 * \return True if it is registered, false otherwise.
		 */
		bool isRegistered(Resource_Type* resource) const;

	private:
		Resource_Container m_resources;
	};
}

#include "ec3/resource-registry.inl"