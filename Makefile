CC = g++
CFLAGS = -Wall -g
LDFLAGS = -lSDL2 -lSDL2_image

game: main.o Game.o TextureManager.o Map.o Vector2D.o Collision.o ECS/ECS.o
	$(CC) $(CFLAGS) -o game main.o Game.o TextureManager.o Map.o Vector2D.o Collision.o ECS/ECS.o $(LDFLAGS)

main.o: *.hpp ECS/*.hpp
	$(CC) $(CFLAGS) -c main.cpp

Game.o: Game.cpp Game.hpp

TextureManager.o: TextureManager.cpp TextureManager.hpp

Map.o: Map.cpp Map.hpp

Vector2D.o: Vector2D.cpp Vector2D.hpp

Collision.o: Collision.cpp Collision.hpp

ECS/ECS.o: ECS/ECS.cpp ECS/ECS.hpp

clean:
	rm -f *.o game ECS/*.o

