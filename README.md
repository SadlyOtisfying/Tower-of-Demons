# Tower of Demons
Team members:

Kong Man Min (3035929217), Ng Tsz Hin (3035855571)

Description:
This is a text-based adventure game.
Once upon a time, Princess Lily was captured by some demons and was locked in the top of a tower. The player will need to enter the tower from level 1 and find a path to reach the next level, until he reaches the top, where he will save Princess Lily.

Game Rules:
1) Each level will be represented by 6 x 6 tiles
2) The player will start from the top left tile (0, 0) and need to arrive at the bottom right tile (5, 5)
3) The player can only see tiles which x-coordinate or y-coordinate are within a distance of 2
4) Each tile could be one of the following: empty space, demon, potion, sword, armor
5) If the player's x-coordinate or y-coordinate is within 1 tile of the demon, he will enter into a fight
6) If the player lose, game is over, and he will need to restart the level
7) Potions will recover the health point of the player
8) Sword will increase the attack damage of the player
9) Armor will reduce the damage from demons taken by the player
10) There will be 2, 4, or 6 levels depending on the difficulty chosen

Compilation and execution instructions:
Change to the game directory.
To compile, type "make game".
To run the game, type "./game".
To completely reset data, remove the file "playerdata.txt".

List of features:
1(Generation of random game sets or events):
Demon, potion, sword and armor will be spawned randomly. The map will also be regenerated every game.

2(Data structures for storing game status):
The position, health point, attack damage and player's armor are stored in a struct.
Each tile of the map is stored in a Tile struct
The map of each level is stored in a 2D Tile vector 

3(Dynamic memory management):
The difficulty of the game can be inputted by the player when the game is start, which will determine the number of levels stored in the map vector.

4(File input/output):
After each level, information about the player will be written on a text file.
If player dies or closes and reopens the game, the previous save will be loaded and the player will need to start at (0, 0) of the level.

5(Program codes in multiple files):
Codes of player, Tile, and game logic are seperated into files and can be reused during coding.



