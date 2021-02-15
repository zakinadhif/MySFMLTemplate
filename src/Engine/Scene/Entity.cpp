#include "Engine/Scene/Entity.hpp"

namespace zfge
{

Entity::Entity(entt::entity handle, entt::registry& registry)
	: m_entityHandle(handle)
	, m_registry(&registry)
{

}

}
