#include "worm.hpp"
#include "getChar.hpp"

//Constructor 
entireWorm::entireWorm() {}

//Constructor for STUCT used for body
wormbody::wormbody()
{
    x = 0;
    y = 0;
}

wormbody::wormbody(int col, int row)
{
    x = col;
    y = row;
}

// This BOOL is named OK because it only returns TRUE when
// things are going OK otherwise it returns false which 
// will terminate the program. It will only return false 
// for collision detections whether itself or the border
bool entireWorm::ok() {
    return _ok;
}

entireWorm::entireWorm(int y, int x)
{
    maxwidth = x;
    maxheight = y;

    // Initialize Variables
    munchie.x = 0;
    munchie.y = 0;
    score = 0;
    munchCounter = 0;
    direction = 'l';
    eatMunchie = false;
    _ok = false;

    // This push_back is used to push the WORM to the middle of the screen 
    // so it can start for there
    worm.push_back(wormbody(x/2, y/2));
    placeMunchie();
}

// Deconstructor
entireWorm::~entireWorm()
{
    getChar();
    endwin();
}

// **NOTE TO PROF**
// Professor, this could be done better than using a while loop, and I understand we want to limits the loops for this project
// for intializng. However, I was overcome with bugs at the end so this was the simplest way to get it to work.
void entireWorm::begin()
{
    createFreePool();
     while (true)
    {
        if (detectCollision())
        {
            break;
        } else
        moveworm();  
    }
}

void entireWorm::createFreePool() {
     //*********************
     // CREATE FREEPOOL
     //*********************   
     int lastIdx;
     for(int i = 1; i < (maxheight); i++) {
          for(int k = 1; k < (maxwidth); k++) {
               cell newScreenCell(i, k);
               freePool.push_back(newScreenCell); //FreePool
               lastIdx++;
        }
      }

}

// **NOTE TO PROF**
// Professor, this could be done better than using a while loop, and I understand we want to limits the loops for this project
// for intializng. However, I was overcome with bugs at the end so this was the simplest way to get it to work.
void entireWorm::placeMunchie()
{
    while (1)
    {
        int randomMunchieX = rand() % maxwidth + 1; 
        int randomMunchieY = rand() % maxheight + 1;
        
         //*********************
         // Keeps from generating munchie onto worm
         //*********************
        for (int i = 0; i < worm.size(); i++)
        {
            if (worm[i].x == randomMunchieX && worm[i].y == randomMunchieY)
            {
                continue;
            }
        }

        //*********************
         // Keeps from generating munchie outside of boundaries 
         //*********************
        if (randomMunchieX >= maxwidth - 2 || randomMunchieY >= maxheight - 3)
        {
            continue;
        }

        // This will give a NEW random position to the munchie
        munchie.x = randomMunchieX;
        munchie.y = randomMunchieY;

        break;
    }
    //*********************
    //Prints munchie onto screen
    //*********************
    //mvprintw first MOVES to the position (munchie.y,munchie.x) and then it prints onto the window randomFoodNum
    randomFoodNum = rand() % 10;
    munchieValue = randomFoodNum;
    mvprintw(munchie.y,munchie.x,"%d",randomFoodNum);
    refresh();
}

bool entireWorm::detectCollision()
{
    //*********************
    // Detect if worm runs into ITSELF
    //*********************
    for (int i = 2; i < worm.size(); i++)
    {
        if (worm[0].x == worm[i].x && worm[0].y == worm[i].y) {
            _ok = true;
            return true;
        }
        
    }
    //*********************
    // Detect if worm runs into BORDERS
    //*********************
    if (worm[0].x == 1 || worm[0].x == maxwidth - 1 || worm[0].y == 1 || worm[0].y == maxheight - 1 ) {
         _ok = true;
     return true;
    }
    
    //*********************
    // Detect if worm runs into MUNCHIE
    //*********************
    if (worm[0].x == munchie.x && worm[0].y == munchie.y)
    {
        eatMunchie = true;
        // The addscore function updates the score to be score = score + munchieValue
        addScore(munchieValue);
        // Next we start a counter that will allow us to add a exact number of body
        // segments to the worm that matches the number from the munchie we just ate
        munchCounter = munchieValue;
        // Then we want to place down a NEW munchie
        placeMunchie();
        // Once the munchie is eaten, we now print the UPDATED 
        // score onto the screen. If we do NOT print the updated
        // score from here the score will stay at zero. This is the best
        // way to update score without any loops
        move(0, maxwidth - 2);
        // printw is used so we dont have do do any char conversions we can
        // instead print the integer directly onto the screen which is more efficent 
        // printw("%d", getScore());
        printw("%d", getScore());
        move(1, 0);  
        refresh();  
    }
    else
        eatMunchie = false;
    return false;
}

// Setter - Used to update score from detectCollision function 
void entireWorm::addScore(int val) {
     score = score + val;
}
// Getter - Used to get the score
int entireWorm::getScore() {
    return score;
}

void entireWorm::moveworm()
{

    //*********************************
    // Make sure DIRECTIONS dont counter
    //*********************************
    char c = getChar();
    switch(c)
    {   
    // It is important to make sure each direction does not counter its opposite 
    // in order to keep the worm from eating itself
    // **EXAMPLE**    
    // It is important to make sure if we want to go left we arnt going right because then
    // we will automatically backtrack, eat ourselves, and lose
    // so we put in these checks to avoid that
        case 'h':
            if (direction != 'r') direction = 'l'; break;
        case 'k':
            if (direction != 'd') direction = 'u'; break;
        case 'l':
            if (direction != 'l') direction = 'r'; break;
        case 'j':
            if (direction != 'u') direction = 'd'; break;
    }
  
    //*********************************
    // Moving the worm
    //*********************************
    // In order to move the worm around we grab the starting element
    // of the vector based circular queue with .begin()
    // we can do these operations because its vector based.
    // Next we insert a new value for either the X or Y at the head position.
    // If we are moving left or right we change the X either positive or negative
    // if we are moving up and down then we change the Y value either positive or negative.
    // It is important to know that Y = 0 is up around the top so we decrease Y in order to
    // go upward with the snake and increase the Y in order to go downward.
    if (direction == 'l')
    {
        worm.insert(worm.begin(), wormbody(worm[0].x - 1, worm[0].y));
    }
    else if (direction == 'r')
    {
        worm.insert(worm.begin(), wormbody(worm[0].x + 1, worm[0].y));
    }
    else if (direction == 'u')
    {
        worm.insert(worm.begin(), wormbody(worm[0].x, worm[0].y - 1));
    }
    else if (direction == 'd')
    {
        worm.insert(worm.begin(), wormbody(worm[0].x, worm[0].y + 1));
    }

    //******************************************************
    // Translating Worm movement to be visible on the screen
    //******************************************************
    move(worm[0].y, worm[0].x);
    addch('@');
    move(worm[1].y, worm[1].x);
    addch('o');
    int last = worm.size() - 1;
    if (!eatMunchie)
    {
        //*********************
        // Removing tail of worm 
        //*********************
        // If NOT eating a munchie, the simply remove the TAIL of the worm by adding a space character
        // TAIL = worm.size() - 1
        move(worm[worm.size() - 1].y, worm[worm.size() - 1].x);
        addch(' ');
        refresh();
        worm.pop_back();
    }
    //***************************************
    // Adding correct number of body segments
    //***************************************
    if(worm.size() > 1 && munchCounter > 0) {
    worm.push_back(wormbody(last++, last++));
    munchCounter--;
    }

    refresh();
}


