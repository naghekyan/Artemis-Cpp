#ifndef EntityStateMachine_h__
#define EntityStateMachine_h__

#include <string>
#include <map>
#include <cassert>
#include "EntityState.h"


namespace artemis 
{
	class Entity;
	class World;
	class EntityManager;

	class EntityStateMachine
	{
		typedef	std::map<std::string, EntityState>	StateNameToComponentsMap;
		typedef std::vector<std::string>	StatesContainer;

		World*							m_world;
		EntityManager*					m_entityManager;
		Entity*							m_entity;
		std::string						m_currentStateName;
		StateNameToComponentsMap		m_stateNameToComponentsMap;
		StatesContainer					m_states;

		// World and only World should actually change the state
		friend class World;
		void changeStateTo(const std::string& newStateName);
	public:
		EntityStateMachine(World*, Entity* entity);
		EntityState& createState(const std::string& stateName);

		bool isStateDefined(const std::string& state);

		EntityStateMachine& addPermanentComponent(Component*);

		~EntityStateMachine();
	};
}


#endif // EntityStateMachine_h__
