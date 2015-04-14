#include "Artemis/Entity.h"
#include <sstream>
#include "Artemis/Component.h"
#include "Artemis/World.h"
#include "Artemis/EntityManager.h"

namespace artemis {
  
  Entity::Entity(World * world, int id) {
    this->world = world;
    this->entityManager = world->getEntityManager();
    this->id = id;
  }
  
  Entity::~Entity() {
    world = NULL;
    entityManager = NULL;
  }
  
  
  void Entity::addSystemBit(std::bitset<BITSIZE> bit) {
    systemBits |= bit;
  }
  
  void Entity::addTypeBit(std::bitset<BITSIZE> bit) {
    typeBits |= bit;
  }
  
  Component* Entity::getComponent(ComponentType & type) {
    return entityManager->getComponent(*this, type);
  }
  
  ImmutableBag<Component*> & Entity::getComponents() {
    return entityManager->getComponents(*this);
  }
  
  int Entity::getId() {
    return id;
  }
  
  std::bitset<BITSIZE> Entity::getSystemBits() {
    return systemBits;
  }
  
  std::bitset<BITSIZE> Entity::getTypeBits() {
    return typeBits;
  }
  
  long int Entity::getUniqueId() {
    return uniqueId;
  }
  
  bool Entity::isActive() {
    return entityManager->isActive(this->getId());
  }
  
  
  void Entity::addComponent(Component * c){
    entityManager->addComponent(*this,c);
  }
  
  void Entity::removeComponent(ComponentType & type) {
    entityManager->removeComponent(*this, type);
  }

  void Entity::removeComponent(Component* c)
  {
      ComponentType type = ComponentTypeManager::getTypeFor(typeid(*c));
      removeComponent(type);
  }

  void Entity::removeSystemBit(std::bitset<BITSIZE> bit) {
    systemBits &= ~bit;
  }
  
  void Entity::removeTypeBit(std::bitset<BITSIZE> bit) {
    typeBits &= ~bit;
  }
  
  void Entity::reset() {
    typeBits = 0;
    systemBits = 0;
  }
  
  void Entity::setGroup(const std::string& group)
  {    
    world->getGroupManager()->set(group, *this);
  }
  
  void Entity::setSystemBits(std::bitset<BITSIZE> systemBits) {
    this->systemBits = systemBits;
  }
  
  void Entity::setTag(const std::string& tag)
  {
    world->getTagManager()->subscribe(tag, *this);
  }
  
  void Entity::setTypeBits(std::bitset<BITSIZE> typeBits) {
    this->typeBits = typeBits;
  }
  
  void Entity::setUniqueId(long int uniqueId) {
    this->uniqueId = uniqueId;
  }
  
  std::string Entity::toString() {
    std::ostringstream oss;
    oss << "Entity[" << id << "]\n";
    return  oss.str();
  }
  
  void Entity::remove() {
    world->deleteEntity(*this);
  }

};
