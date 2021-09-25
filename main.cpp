#include <curses.h>
#include "getChar.hpp"
#include <iostream>
#include "worm.hpp"
#include "getChar.hpp"
#include <vector>
#include <string>

void startup( void );
void terminate( void );

//*************************
//main( integer, array of char *)
//Integer = int argc = number of arguements that are passed
//array of strings = char *argv[] = represents those arguments 
//*************************

int main(int argc, char *argv[])
{
     //stoi, or string to integer, converts the users input into a int
     int numberOfRows = std::stoi(argv[1]); //Height
     int numberOfColumns = std::stoi(argv[2]); //Width

     //***********************************************************
     // Check that the user provides valid values for the inputs
     //***********************************************************
     if (numberOfRows < 9 || numberOfRows > 25) {
          std::cout << "The number of rows can be between 9 and 25, inclusive" <<std::endl;
          exit(1);
     }
      if (numberOfColumns < 9 || numberOfColumns > 80) {
          std::cout << "the number of columns can be between 9 and 80, inclusive" <<std::endl;
          exit(1);
     }
     int totalRows = numberOfRows + 3;
     int totalColumns = numberOfColumns + 2;
     WINDOW *window = newwin(totalRows, totalColumns, 0, 0);

     //*********************
     // Creation of Scoreboard
     //*********************
     startup();
     move(0, 3);  
     addstr("Worm");
     move(0, totalColumns - 11);
     addstr("Score");
     // Start by printing 0 onto the screen for score
     // Then in the worm class, when we eat the munchie, we will print a new number
     // in that postion that is equivalent to the current score + munchie value
     move(0, totalColumns - 4);
     printw("%d", 0);
     move(1, 0);  
     refresh();  
    
     
    //*********************
    // Generate the borders
    //*********************
    // Creates (*******) for the TOP
    for (int i = 0; i < numberOfColumns; i++ ) {
        mvaddch(1, i , '*');

    }
     //Creates (*******) for the BOTTOM
    for (int i = 0; i < numberOfColumns; i++ ) {
          mvaddch(numberOfRows - 1, i, '*');
    }
    //Creates (*******) for the RIGHT
     for (int i = 1; i < numberOfRows - 1; i++ ) {
          mvaddch(i, numberOfColumns -1, '*');
    }
     // Creates (*******) for the LEFT
     for (int i = 1; i < numberOfRows - 1; i++ ) {
          mvaddch(i, 0, '*');
    }

     //*********************
     // Here is the call to startup the worm class that controls the worm.
     //*********************
     // Must pass rows and columns 
     entireWorm *s = new entireWorm(numberOfRows ,numberOfColumns);
     s->begin();
     
     // If we detect a collision then we terminate the program
    if (s->ok() == true) {
     terminate();
     std::cout << std::endl << "The worm died since it ran into something!" << std::endl;
     std::cout << "Your final score was: " << s->getScore() << std::endl;
    } 
}

void startup( void )
{
     initscr();	 
     curs_set(0); 
     clear();	 
     noecho();	
     cbreak();	
  
}

void terminate( void )
{
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}
