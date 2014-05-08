#ifndef EntityStateMachine_h__
#define EntityStateMachine_h__

#include <string>
#include <map>
#include <cassert>
#include "EntityState.h"


namespace artemis 
{
	class Entity;

	class EntityStateMachine
	{
		typedef	std::map<std::string, EntityState>	StateNameToComponentsMap;

		Entity*							m_entity;
		std::string						m_currentStateName;
		StateNameToComponentsMap		m_stateNameToComponentsMap;

		// World and only World should actually change the state
		friend class World;
		void changeStateTo(const std::string& newStateName);
	public:
		EntityStateMachine(Entity* entity);
		EntityState& createState(const std::string& stateName);

		EntityStateMachine& addPermanentComponent(Component*);

		~EntityStateMachine();
	};
}


#endif // EntityStateMachine_h__
