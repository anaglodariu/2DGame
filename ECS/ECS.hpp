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

using namespace std;
using ComponentID = size_t;

// we get the last used ID and then increment it
inline ComponentID getComponentTypeID() {
    static ComponentID lastID = 0;
    return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept {
    static ComponentID typeID = getComponentTypeID();
    return typeID;
}

constexpr size_t maxComponents = 32;

//  whether an entity has a component or not
using ComponentBitSet = bitset<maxComponents>;

// an array of pointers to components that an enity has
using ComponentArray = array<Component*, maxComponents>;

class Component 
{
public:
    Entity* entity; // component has a reference to its owner

    // virtual so that they can be overriden by derived classes
    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity
{
private:
    bool active = true; // whether the entity is active or not
    vector<unique_ptr<Component>> components; // list of all the components that the entity has

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
public:
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

public:
    void update() {
        for (auto& e: entities) e->update();
    }
    void draw() {
        for (auto& e: entities) e->draw();
    }

    // move through the vector and remove any entities that are not active
    void refresh() {
        entities.erase(remove_if(begin(entities), end(entities),
            [](const unique_ptr<Entity> &mEntity) {
                return !mEntity->isActive();
            }),
            end(entities));
    }

    // add an entity to the vector
    Entity& addEntity() {
        Entity* e = new Entity();
        unique_ptr<Entity> uPtr{ e }; // unique pointer to the entity
        entities.emplace_back(move(uPtr));
        return *e;
    }
};

#endif /* ECS_HPP */