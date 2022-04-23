FLAGS = -pedantic-errors -std=c++11

player.o: player.cpp player.h
	g++ $(FLAGS) -c $<

tile.o: tile.cpp tile.h
	g++ $(FLAGS) -c $<

game.o: game.cpp tile.h player.h
	g++ $(FLAGS) -c $<

game: game.o tile.o player.o
	g++ $(FLAGS) $^ -o $@

clean:
	rm -f game game.o player.o tile.o playerdata.txt

.PHONY: clean
