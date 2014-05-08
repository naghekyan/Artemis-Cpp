#include "Artemis/EntitySystem.h"
#include "Artemis/World.h"
#include "Artemis/Entity.h"

using namespace std;

namespace artemis {
  
	EntitySystem::~EntitySystem() {
		world = NULL;
	}
  
	int EntitySystem::getEntityCount(){
		return actives.getCount();
	}
  
	void EntitySystem::change(Entity& e) {
		bool contains = (systemBit & e.getSystemBits()) == systemBit;
		bool interest = (typeFlags & e.getTypeBits()) == typeFlags;
    
		if(interest && !contains && typeFlags.any()) {
			actives.add(&e);
			e.addSystemBit(systemBit);
			added(e);
		} else if(!interest && contains && typeFlags.any()) {
			this->remove(e);
		}
	}
  
	void EntitySystem::process() {
		if(checkProcessing()) {
			begin();
			processEntities(actives);
			end();
		}
	};
  
	void EntitySystem::setWorld(World *world) {
		this->world = world;
	};
  
	void EntitySystem::remove(Entity &e) {
		actives.remove(&e);
		e.removeSystemBit(systemBit);
		removed(e);
		// TODO Maybe it's better to actually delete the component from memory here by using typeFlags; e.getTypeBits()
		// TODO and e.getId() so that in `EntitySystem::removed` function the user could access the "removed" component
		// TODO in order to be able to stop rendering by calling removeChild, or to be able to stop physics simulation,
		// TODO by removing it from the physics world or such other tasks? But on the other hand user can perform this
		// TODO kind of tasks in the destructor of the component, and we can leave this functionality as is.
	};
  
	void  EntitySystem::setSystemBit(bitset<BITSIZE> bit) {
		systemBit = bit;
	}
  
};
