#ifndef ECS_HPP
#define ECS_HPP

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

using namespace std;
using ComponentID = size_t;
using Group = size_t;

// we get the last used ID and then increment it
inline ComponentID getNewComponentTypeID() {
    static ComponentID lastID = 0u;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

//  whether an entity has a component or not
using ComponentBitSet = bitset<maxComponents>;

// whether an entity is in a group or not
using GroupBitSet = bitset<maxGroups>;

// an array of pointers to components that an enity has
using ComponentArray = array<Component*, maxComponents>;


class Component 
{
public:
    Entity* entity; // component has a pointer to the entity it belongs to
    // virtual so that they can be overriden by derived classes
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity
{
private:
    Manager& manager; // reference to the manager
    bool active = true; // whether the entity is active or not
    vector<unique_ptr<Component>> components; // list of all the components that the entity has

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet; // whether the entity is in a group or not

public:
    // constructor
    Entity(Manager& mManager) : manager(mManager) {} // member initialization

    void update() {
        for (auto& c: components) c->update();    
    }

    void draw() {
        for (auto& c: components) c->draw();
    }

    bool isActive() const { return active; }

    // we can call the entity destroy function from any of our
    // components
    void destroy() { active = false; }

    // check if the entity has a certain group
    bool hasGroup(Group mGroup) {
        return groupBitSet[mGroup];
    }

    // add the entity to a group
    void addGroup(Group mGroup);

    // remove the entity from a group
    void delGroup(Group mGroup) {
        groupBitSet[mGroup] = false;
    }

    // if the entity has a certain component
    template <typename T> bool hasComponent() const {
        return componentBitSet[getComponentTypeID<T>()];
    }

    // add a component to the entity
    template <typename T, typename... TArgs> T& addComponent(TArgs&&... mArgs) {
        T* c(new T(forward<TArgs>(mArgs)...));
        c->entity = this;
        unique_ptr<Component> uPtr{ c };
        components.emplace_back(move(uPtr));

        componentArray[getComponentTypeID<T>()] = c;
        componentBitSet[getComponentTypeID<T>()] = true;

        c->init();
        return *c;
    }

    // get a component from the entity
    template <typename T> T& getComponent() const {
        // set a pointer to a position in the array
        auto ptr(componentArray[getComponentTypeID<T>()]);
        return *static_cast<T*>(ptr);
    }
    
};

class Manager 
{
private:
    // a vector of pointers to entities
    vector<unique_ptr<Entity>> entities;

    // an array of vectors of pointers to entities in each 32 `groups`
    array<vector<Entity*>, maxGroups> groupedEntities;

public:
    void update() {
        for (auto& e: entities) e->update();
    }
    void draw() {
        for (auto& e: entities) e->draw();
    }

    // move through the vector and remove any entities that are not active
    void refresh() {
        // remove the entities from the groups before updating them
        for (auto i(0u); i < maxGroups; i++) {
            // we have a reference for each group (vector) in the array which allows
            // direct access and modification of the entities in each group
            auto& vec(groupedEntities[i]);
            // we make sure that only active entities that belong to the current group
            // remain in the vector
            vec.erase(remove_if(begin(vec), end(vec),
                [i](Entity* mEntity) {
                    return !mEntity->isActive() || !mEntity->hasGroup(i);
                }),
                end(vec));
        }

        entities.erase(remove_if(begin(entities), end(entities),
            [](const unique_ptr<Entity> &mEntity) {
                return !mEntity->isActive();
            }),
            end(entities));
    }

    void addToGroup(Entity* mEntity, Group mGroup) {
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    // move through a single group
    vector<Entity*>& getGroup(Group mGroup) {
        return groupedEntities[mGroup];
    }

    // add an entity to the vector
    Entity& addEntity() {
        Entity* e = new Entity(*this);
        unique_ptr<Entity> uPtr{ e }; // unique pointer to the entity
        /* unique_ptr is a smart pointer that takes ownership of the dynamically 
        allocated object and ensures that the object is properly deallocated when
        the ptr goes out of scope */
        /* when uPtr is moved into the entities container it means that the ownership
        of the dynamically allocated Entity object is transferred to the entities 
        container, and uPtr no longer owns it */
        entities.emplace_back(move(uPtr));
        /* when uPtr goes out of scope (the entities container is destroyed) it will
        automatically release the memory allocated for the Entity object */
        return *e;
    }
};

#endif /* ECS_HPP */