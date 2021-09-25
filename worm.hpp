#include <cstdlib>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <vector>
#include "cell.hpp"

#ifndef WORM_HPP
#define WORM_HPP

//*************************************************************
// Creating a vector-based circular queue for the worm segments
//*************************************************************
// This is the structure that hold the components of the worm
// we create a vector and the datatype of that vector becomes this struct
// that vector becomes the vector based circular queue to represent the worm.
// A circular queue always has a fixed length, our worms length will NEVER be
// greater than the size of (totalRows - 1) * (totalColumns - 1) - 1
struct wormbody {
    int x, y;
    wormbody(int col, int row);
    wormbody();
};

class entireWorm {
    public:
        //Constructors and Deconstructor
        entireWorm();
        entireWorm(int y, int x);
        ~entireWorm();

        // The begin function starts up the worm class 
        // and keeps a eye out for collisions 
        void begin();
        void createFreePool();
        bool beginBool();
        // Setter and Getter
        void addScore(int val);
        int getScore();

        // These must reside in PUBLIC or else we would not be able to access them properly
        // from the main.cpp
        bool detectCollision();
        bool ok();
        void moveworm(); 
    private:
        void placeMunchie();
        ///***************************
        // vector-based circular queue
        //****************************
        std::vector<wormbody> worm;
        //***************************
        // Private variables to be used throughout the classes functions
        //****************************
        char direction, border, foodSymbol;
        int munchieValue, maxwidth, maxheight, randomFoodNum, score, munchCounter;
        bool eatMunchie, _ok;
        // Create munchie out of the same struct used for worm, this allows
        // each Munchie to hold a X and a Y postion on the board
        wormbody munchie;
        std::vector<cell> freePool; 
};

#endif
