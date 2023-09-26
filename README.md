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
- _failure in using Gimp to create the map_, so we have a simple text file ("assets/tiles16x16.map") in which we **"designed"** the map with the help of 0, 1, 2 characters
- 0 is for dirt
- 1 is for grass
- 2 is for water
- the size of the map is 16x16 tiles, each tile being 32x32 pixels

## Rendering Layers and Grouping entities together
- in order to solve the rendering problem (the map was drawn over the player), we
add each entity to a **specific** group, and then we render the groups in the preferred 
order

# Making my first sprite sheet
- we have created a **sprite sheet** for Fernando, red-haired daddy
- the sprite sheet has **4 frames**
- each frame has 32x32 pixels and it was done in Gimp
- we put all the frames together in Paint
- because Paint makes the background white, _we made it transparent using_
_a python script: alpha.py (see the script in the assets folder)_

# Making multiple animations
- we have created a **Animation struct** which holds the information about the animation
- we have a sprite sheet for idle and walking animations, each on different rows
- we use _RenderCopyEx_ instead of RenderCopy in order to flip the texture horizontally when the player is moving left

# Tile Map
- we have a sprite sheet with all the tiles used for the map; it has a width of
10 tiles and a height of 3 tiles, each tile being 32x32 pixels
- the width was made 10 in order to identify the tiles easier, based on their
row and column indexes and create the map in a text file

# Camera
- we create a camera object which will be a SDL_Rect object the size of our screen
- the tile map is scaled up 2 times

