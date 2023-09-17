HOW TO MAKE A 2D GAME WITH SDL2
===
## Overview
Implementing a 2D game in C++ using the SDL2 library.

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
- drawing textures/sprites to the screen: the birth of **Gorge Gorgeous**, our main player for now

<!-- ## GameObject class
- create player objects -->

## Map class
- loads the map from a file

## Entity Component System (ECS) design pattern
- we have created 3 classes for this pattern: 
  - Entity: which can have more components
  - Component: which can be added to an entity, and have a reference to the entity
  - Manager: which can manage entities and components
- we have created the **PositionComponent class**, which derives from the Component class and handles the position of the sprite
- we have created the **SpriteComponent class**, which derives from the Compnent class and is responsible for drawing the sprite to the screen and updating the sprite's position
- we have created the **KeyboardController class**, which derives from the Component class and handles the keyboard input -> OUR PLAYER CAN MOVE NOW!
- we have created the **ColliderComponent class**, which derives from the Component class and handles the collision between entities -> OUR PLAYER CAN'T GO THROUGH THE WALLS NOW! (especially the youShallNotPassWall)
- we have created the **TileComponent class**, which derives from the Component class and handles the tiles of the map (tiles for grass, water, dirt)

## Collision detection
- we have created the **Collision class**, which handles the collision between entities
- we have used the simple AABB collision detection algorithm (Axis-Aligned Bounding Box)

We have used to concept of _forward declaration_ in order to avoid _circular dependencies between classes_.

## Parsing external Map/Level files
- _failure in using Gimp to create the map_, so we have a simple text file
in which we **"designed"** the map with the help of 0, 1, 2 characters
- 0 is for dirt
- 1 is for grass
- 2 is for water
- the size of the map is 16x16 tiles, each tile being 32x32 pixels

## Rendering Layers and Grouping entities together



