#pragma once

#include <entt/entt.hpp>
#include <fmt/format.h>

class Entity
{
public:
	Entity() = default;
	Entity(entt::entity handle, entt::registry& registry);
	Entity(const Entity& other) = default;

	template<typename T, typename... Args>
	T& addComponent(Args&&... args)
	{
		if (hasComponent<T>())
		{
			throw fmt::format("{}:{}: Entity {} already has the component!", __FILE__, __LINE__, operator uint32_t());
		}

		return m_registry->emplace<T>(m_entityHandle, std::forward<Args>(args)...);
	}

	template<typename T>
	T& getComponent()
	{
		if (!hasComponent<T>())
		{
			throw fmt::format("{}:{}: Entity {} doesn't have the component!", __FILE__, __LINE__, operator uint32_t());
		}

		return m_registry->get<T>(m_entityHandle);
	}

	template<typename T>
	void removeComponent()
	{
		if (!hasComponent<T>())
		{
			throw fmt::format("{}:{}: Entity {} doesn't have the component!", __FILE__, __LINE__, operator uint32_t());
		}

		m_registry->remove<T>(m_entityHandle);
	}

	template<typename T>
	bool hasComponent() const
	{
		return m_registry->has<T>(m_entityHandle);
	}

 	operator bool() const { return m_entityHandle != entt::null; }
	operator entt::entity() const { return m_entityHandle; }
	operator std::uint32_t() const { return static_cast<std::uint32_t>(m_entityHandle); }

private:
	entt::entity m_entityHandle { entt::null };
	entt::registry* m_registry = nullptr;
};
