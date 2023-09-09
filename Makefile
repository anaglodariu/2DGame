CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lSDL2 -lSDL2_image

game: main.o Game.o TextureManager.o Map.o 
	$(CC) $(CFLAGS) -o game main.o Game.o TextureManager.o Map.o $(LDFLAGS)

main.o: main.cpp Game.hpp TextureManager.hpp Map.hpp ECS/Components.hpp ECS/ECS.hpp ECS/PositionComponent.hpp ECS/SpriteComponent.hpp
	$(CC) $(CFLAGS) -c main.cpp

Game.o: Game.cpp Game.hpp

TextureManager.o: TextureManager.cpp TextureManager.hpp

Map.o: Map.cpp Map.hpp

clean:
	rm -f *.o game

