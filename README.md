# TheMazeGame
This is a game programmed in C++ Programming Language

Programming techniques used:
1.  file handling
2.  ncurses library (on linux os)
3.  Object Oriented Programming
4.  arrays
5.  many more...

   
version 3.4 last edit 15/07/2023

In this game the user (green character) tries to find the red diamond located in the maze before his oponent (orange character)

-Important:

1.  The source code comes with two .txt files <<easy.txt>> and <<hard.txt>>. Depending on the file the user selects, the dificulty of the game is set. To select file, run command ./main <level name>
2.  The user controls the green character using cursor keys to move up, down, left or right and space to stay in the same position
3.  For every move the user decides, the computer responds by making one move
4.  During the game, the user can 'surrender' by pressing Esc, this option, however, gives the victory to the oponent.
5.  For the game to work properly, a terminal that supports color must be used. If not, the program terminates and exits with a message and an error code 1
6.  Starting positions of all characters and the diamond on the game board are randomly generated each time the game starts.

Feel free to improve the game as long as you keep the source code free for everyone to see and use! 

Potential updates:
1.  second player using wasd keys
2.    better cpu algorithm
