
/*
Maze Game

using ncurses in linux os

last edit: 14/07/2023 v3.4
*/

#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <ncurses.h>  
#include <unistd.h>

using namespace std;

//get maze width to init maze array
int get_maze_width(string filename)
{
    int width = 0;
    fstream file;
    file.open(filename, ios::in);
    while (file.get() != '\n')
    {
        width++;//increase width one time for every character that is not \n
    }
    file.close();
    return width;
}

//classes and methods 
class Entity
{

public:
    char name;
    int user;
    int x;
    int y;
    int pos_x;
    int pos_y;

    //methods prototypes
    int go_up();
    int go_down();
    int go_left();
    int go_right();
    int stay();
    int set_init_coordinates(int max);
};

int Entity::go_up()
{

    pos_x = x - 1;
    return pos_x;
}

int Entity::go_down()
{

    pos_x = x + 1;
    return pos_x;
}

int Entity::go_left()
{

    pos_y = y - 1;
    return pos_y;
}

int Entity::go_right()
{

    pos_y = y + 1;
    return pos_y;
}

int Entity::stay()
{
    pos_x = x;
    pos_y = y;
    return 0;
}

class User : public Entity//class User inherits all features from Entity
{

public:

    char name = 'M';
};

class Cpu : public Entity
{

public:

    char name = 'L';

};

class Diamond
{

public:

    int pos_x;
    int pos_y;
    char name = 'D';

};

class Engine
{

public:

    //method prototype
    int start_game(string filename);
};

int Engine::start_game(string filename)
{
    srand(time(NULL));
    WINDOW *win;
    User user;
    Cpu cpu;
    Diamond diamond;
    int width = get_maze_width(filename);
    int height = width / 2;

    char maze[height][width]; // init maze array
    char buffer[width];       // init buffer array

    //file handling
    fstream file;
    file.open(filename, ios::in | ios::out);

    // maze parsing from file
    for (int i = 0; i < height; i++)
    {
        file.getline(buffer, 100);
        for (int j = 0; j < width; j++)
        {
            maze[i][j] = buffer[j]; 
        }
    }

    //randomise starting position

    //random int number from 1 to border -1
    user.x = rand() % height;
    user.y = rand() % width;
    cpu.x = rand() % height;
    cpu.y = rand() % width;
    diamond.pos_x = rand() % height;
    diamond.pos_y = rand() % width;

    //init character coordinates
    while (maze[user.x][user.y] == '*')
    {
        user.x = rand() % height;
        user.y = rand() % width;
    }

    while (maze[cpu.x][cpu.y] == '*')
    {
        cpu.x = rand() % height;
        cpu.y = rand() % width;
    }

    while (maze[diamond.pos_x][diamond.pos_y] == '*')
    {
        diamond.pos_x = rand() % height;
        diamond.pos_y = rand() % width;
    }

    //init screen
    initscr();
    cbreak();

    //check if terminal supports color 
    if (has_colors() == FALSE)
    {
        endwin();
        cout << "Terminal does not support color!" << endl;
        return 1;
    }

    char username[30];

    //create the window
    win = newwin(50, 30, 25, 15);

    printw("Enter username:  ");
    scanw("%19s", username);
    printw("Welcome %s\n", username);
    printw("Press any key to continue");
    getch();

    endwin();

    initscr();
    noecho();
    cbreak();
    win = newwin(50, 30, 25, 15);

    //current pos = last pos 
    user.pos_x = user.x;
    user.pos_y = user.y;
    cpu.pos_x = cpu.x;
    cpu.pos_y = cpu.y;
    int counter = 0;

    //color pair init
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_GREEN);
    init_pair(2, COLOR_YELLOW, COLOR_YELLOW);
    init_pair(3, COLOR_RED, COLOR_RED);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);
    init_pair(5, COLOR_WHITE, COLOR_BLUE);

    keypad(stdscr, true);

    //game runs while flag = TRUE
    bool flag = TRUE;
    while (flag)
    {

        clear();//clear the screen
        
        //place user, cpu and diamond on the map
        maze[cpu.pos_x][cpu.pos_y] = 'L';
        maze[user.pos_x][user.pos_y] = 'M';
        maze[diamond.pos_x][diamond.pos_y] = 'D';

        printw("\t");
        attron(COLOR_PAIR(5));
        printw("Good Luck Player!!\n");
        attroff(COLOR_PAIR(5));

        //create colored map from the array
        for (int i = 0; i < height; ++i)
        {
            for (int j = 0; j < width; ++j)
            {
                if (maze[i][j] == 'M')
                {
                    attron(COLOR_PAIR(1));
                    printw("%c", maze[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                if (maze[i][j] == 'L')
                {
                    attron(COLOR_PAIR(2));
                    printw("%c", maze[i][j]);
                    attroff(COLOR_PAIR(2));
                }
                if (maze[i][j] == 'D')
                {
                    attron(COLOR_PAIR(3));
                    printw("%c", maze[i][j]);
                    attroff(COLOR_PAIR(3));
                }
                if (maze[i][j] == '*')
                {
                    attron(COLOR_PAIR(4));
                    printw("%c", maze[i][j]);
                    attroff(COLOR_PAIR(4));
                }
                if (maze[i][j] == '.')
                {
                    printw("%c", ' ');
                } 
            }
            printw("%c", '\n');
        }

        //wait for user input
        int c = getch();
        switch (c)
        {
            case KEY_UP:
                user.go_up();
                break;
            case KEY_DOWN:
                user.go_down();
                break;
            case KEY_LEFT:
                user.go_left();
                break;
            case KEY_RIGHT:
                user.go_right();
                break;
            case ' ':
                user.stay();
                break;
            case 'q':
                endwin();
                printw("Player Quited!!\n");
                printw("Press any key to continue (NOT power button)");
                getch();
                flag = !flag;//end game when q is pressed
                break;
            case 27:
                flag = !flag;//end game when Esc is pressed
                cout<<"EXIT"<<endl;
                break;
        }

        //move cpu player
        
        int Lmove = rand() % 4;//random int from 0 to 3

        if (Lmove == 0)
        {
            cpu.go_up();
        }
        if (Lmove == 1)
        {
            cpu.go_down();
        }
        if (Lmove == 2)
        {
            cpu.go_left();
        }
        if (Lmove == 3)
        {
            cpu.go_right();
        }

        //move user in the map
        if (maze[user.pos_x][user.pos_y] == '.' || maze[user.pos_x][user.pos_y] == 'L' || maze[user.pos_x][user.pos_y] == 'D')
        {
            maze[user.pos_x][user.pos_y] = 'M';
            maze[user.x][user.y] = '.';
            user.x = user.pos_x;
            user.y = user.pos_y;
        }
        else
        {
            user.pos_x = user.x;
            user.pos_y = user.y;
        }

        //move cpu in the map
        if (maze[cpu.pos_x][cpu.pos_y] == '.' || maze[cpu.pos_x][cpu.pos_y] == 'M' || maze[cpu.pos_x][cpu.pos_y] == 'D')
        {
            maze[cpu.pos_x][cpu.pos_y] = 'L';
            maze[cpu.x][cpu.y] = '.';
            cpu.x = cpu.pos_x;
            cpu.y = cpu.pos_y;
        }
        else
        {
            cpu.pos_x = cpu.x;
            cpu.pos_y = cpu.y;
        }

        //check if user found the diamond
        if (user.pos_x == diamond.pos_x && user.pos_y == diamond.pos_y)
        {
            printw("%s Won!!\n", username);
            printw("Press any key to continue (NOT power button)");
            getch();
            flag = !flag;
        }

        //check if cpu found the diamond
        if (cpu.pos_x == diamond.pos_x && cpu.pos_y == diamond.pos_y)
        {
            printw("Cpu Won!!\n");
            printw("Press any key to continue (NOT power button)");
            getch();
            flag = !flag;
        }
    }
    endwin();//end the window
    return 0;
}

int main(int argc, char *argv[])
{

    string filename = argv[1];//get level filename

    Engine game;//create the game

    cout<<"GAME STARTING..."<<endl;

    try{
        int error = 0;
        if (game.start_game(filename) == 0){//start the game
            cout<<"GAME FINISHED SUCCESSFULLY!"<<endl;
        }else{
            error = 1;
            throw(error);
        }
        }catch(int er){
            cout<<"GAME ENDED UNEXPECTEDLY"<<endl;
        }   
    return 0;
}
