#ifndef EntityState_h__
#define EntityState_h__

#include <vector>

namespace artemis 
{

	class Component;

	class EntityState
	{
		std::vector<Component*>		m_stateComponents;

	public:
		EntityState& addComponent(Component*);
		Component* operator[](unsigned index);
		int size();
	};
}

#endif // EntityState_h__
