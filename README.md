HOW TO MAKE A 2D GAME WITH SDL2
===
## Setup
- install SDL2
- install SDL2_image

# How to compile and run the game
- make
- ./game

## The main function
- limiting frame rate (for smoother performace hehe)

## Game class
- create the game window
- create the game loop
  - handle events
  - update game state
  - render

## TextureManager class
- drawing textures/sprites to the screen: the birth of **Gorge Gorgeous** 

## GameObject class
- create player objects

## Map class
- create the map of the game

- create an entity component system

## Entity Component System (ECS) design pattern
- we have created 3 classes for this pattern: 
  - Entity: which can have more components
  - Component: which can be added to an entity, and have a reference to the entity
  - Manager: which can manage entities and components
- we have created the PositionComponent class, which derives from Component class and implements the update and init functions -> which will be used to update the position of the player
