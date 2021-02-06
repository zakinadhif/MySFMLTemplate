#include "Engine/Entity.hpp"

Entity::Entity(entt::entity handle, entt::registry& registry)
	: m_entityHandle(handle)
	, m_registry(&registry)
{

}
