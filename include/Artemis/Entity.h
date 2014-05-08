#ifndef ENTITY_H
#define ENTITY_H

#include <bitset>
#include <string>
#include <cstddef>
#include <typeinfo>
#include "BitSize.h"
#include "ImmutableBag.h"
#include "ComponentTypeManager.h"

namespace artemis {
  
	class Component;
	class ComponentType;
	class World;
	class EntityManager;
	class EntityStateMachine;
  
	/**
   * The entity class. Cannot be instantiated outside the framework, you must
   * create new entities using World.
   */
  class Entity {
    
  private:
    int						id;
    long int				uniqueId;
    std::bitset<BITSIZE>	typeBits;
    std::bitset<BITSIZE>	systemBits;
    World*					world;
    EntityManager*			entityManager;
	EntityStateMachine*		fsm;		
    
    // No copy constructor
    Entity(const Entity&);
    // No assign operator
    Entity& operator=(const Entity&);
    
  protected:
    
  public:
    Entity(World * world, int id);
    ~Entity();
    int getId();
    void setUniqueId(long int uniqueId);
    long int getUniqueId();
    
    std::bitset<BITSIZE> getTypeBits();
    void addTypeBit(std::bitset<BITSIZE> bit);
    void removeTypeBit(std::bitset<BITSIZE> bit);
    std::bitset<BITSIZE> getSystemBits();
    void addSystemBit(std::bitset<BITSIZE> bit);
    void removeSystemBit(std::bitset<BITSIZE> bit);
    void setSystemBits(std::bitset<BITSIZE> systemBits);
    void setTypeBits(std::bitset<BITSIZE> typeBits);
    void reset();
    
    std::string toString();
    
    void addComponent(Component * c);
    
    //Might change to non template
    template<typename c>
    void deleteComponent() {
      entityManager->deleteComponent(*this,ComponentTypeManager::getTypeFor<c>());
    }
    
	template<typename c>
	void reomveComponent() {
		entityManager->removeComponent(*this,ComponentTypeManager::getTypeFor<c>());
	}

    void deleteComponent(ComponentType & type);
    
	void removeComponent(ComponentType & type);

	void deleteComponent(Component* c);

	void removeComponent(Component* c);
    
    Component * getComponent(ComponentType & type);
    
    template<typename c>
    Component * getComponent() {
      return (c*)entityManager->getComponent(*this,ComponentTypeManager::getTypeFor<c>());
    }
    
    ImmutableBag<Component*> & getComponents();
    
    bool isActive();
    void remove();
    void setGroup(const std::string& group);
    void setTag(const std::string& tag);
    
	EntityStateMachine* createStateMachine();
	EntityStateMachine* getStateMachine();
	void changeStateTo(const std::string& newState);
    
  };
};
#endif // $(Guard token)
