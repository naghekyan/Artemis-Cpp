#include "Artemis/EntityState.h"
#include <cassert>

namespace artemis
{
	EntityState& EntityState::addComponent(Component* component)
	{
		m_stateComponents.push_back(component);
		return *this;
	}

	Component* EntityState::operator[](unsigned index)
	{
		assert(index < m_stateComponents.size() && "Index is out of range.");
		return m_stateComponents[index];
	}


	int EntityState::size()
	{
		return m_stateComponents.size();
	}
}
