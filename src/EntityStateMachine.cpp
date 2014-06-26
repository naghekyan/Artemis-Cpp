#include "Artemis/EntityStateMachine.h"
#include "Artemis/Entity.h"
#include "Artemis/EntityManager.h"
#include "Artemis/World.h"

namespace artemis
{
	EntityStateMachine::EntityStateMachine(World* world, Entity* entity)
		: m_world(world)
		, m_entityManager(m_world->getEntityManager())
		, m_entity(entity)
		, m_currentStateName(std::string(""))
	{

	}

	EntityState& EntityStateMachine::createState(const std::string& stateName)
	{
		// prevent duplicate states
		assert(m_stateNameToComponentsMap.find(stateName) == m_stateNameToComponentsMap.end()
			&& "State is already defined.");

		m_states.push_back(stateName);

		std::pair<StateNameToComponentsMap::iterator, bool> result = 
			m_stateNameToComponentsMap.insert(std::pair<std::string, EntityState>(stateName, EntityState()));

		// return inserted EntiryState to add components
		return result.first->second;
	}

	void EntityStateMachine::changeStateTo(const std::string& newStateName)
	{
		// state should exist
		assert(m_stateNameToComponentsMap.find(newStateName) != m_stateNameToComponentsMap.end()
			&& "State is not defined.");

		// if current state is defined then non-permanent components should be removed  
		if (m_stateNameToComponentsMap.find(m_currentStateName) != m_stateNameToComponentsMap.end())
		{
			EntityState& currentState = m_stateNameToComponentsMap[m_currentStateName];

			for (int i = 0; i < currentState.size(); ++i)
			{
				m_entity->removeComponent(currentState[i]);
			}
		}

		// Execute removed or added methods of corresponding systems in case
		// we remove and add the same type of component into the same entity
		m_entityManager->refresh(*m_entity);

		EntityState& newState = m_stateNameToComponentsMap[newStateName];

		for (int i = 0; i < newState.size(); ++i)
		{
			m_entity->addComponent(newState[i]->clone());
		}
		m_currentStateName = newStateName;
		
		// Execute removed or added methods of corresponding systems in case
		// we remove and add the same type of component into the same entity
		m_entityManager->refresh(*m_entity);
	}

	EntityStateMachine& EntityStateMachine::addPermanentComponent(Component* component)
	{
		m_entity->addComponent(component);
		return *this;
	}

	EntityStateMachine::~EntityStateMachine()
	{
		StateNameToComponentsMap::iterator it = m_stateNameToComponentsMap.begin();
		for (; it != m_stateNameToComponentsMap.end(); ++it)
		{
			EntityState& entityState = it->second;
			for (int i = 0; i < entityState.size(); ++i)
			{
				delete entityState[i];
			}
		}
	}

	bool EntityStateMachine::isStateDefined(const std::string& state)
	{
		StatesContainer::iterator it;
		for (it = m_states.begin(); it != m_states.end(); ++it)
		{
			if (*it == state)
			{
				return true;
			}
		}

		return false;
	}

}

