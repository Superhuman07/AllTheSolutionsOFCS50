//
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;
    
    double velocity = drand48()*5;
    double velocityX = drand48()*5;
    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
   
       
       move(ball, velocityX, velocity);
       pause(10); 
      // check for mouse event
      
        GEvent event = getNextEvent(MOUSE_EVENT);
       
      // if we heard one
        if (event != NULL)
        {
            // if the event was movement
            
            if (getEventType(event) == MOUSE_MOVED)
            {
                // ensure follows cursor
                double x = getX(event);
                if(x <= 350&&velocityX!=0)
                setLocation(paddle, x, 550);
                
            }
        
        }
     

        GObject object = detectCollision(window, ball);
       if(object != NULL)
       {
       if (object == paddle)
       {
         velocity = -velocity;
       updateScoreboard(window,label, points);
       }
       else if (strcmp(getType(object), "GRect") == 0)
        {
	    velocity = -velocity;
        points++;
        updateScoreboard(window,label, points);
        bricks--;
        removeGWindow(window, object);
   
   
        }
        } 
      
        
    
         
       

        // bounce off bottom edge of window
       if (getY(ball) + getHeight(ball) >= getHeight(window))
        {
          velocity = 0;
          velocityX = 0;
          lives--;
        
        }

        // bounce off up edge of window
        else if (getY(ball) <= 0)
        {
            velocity = -velocity;
          
        }
        
        if (getX(ball) + getWidth(ball) >= getWidth(window))
        {
          velocityX = -velocityX;
        }

        // bounce off bottom edge of window
        else if (getX(ball) <= 0)
        {
            velocityX = -velocityX;
          
        
        }
        // linger before moving again
        pause(10);
       
    }
    if(points==50)
    {
    GLabel label = newGLabel("You bricked out the breakout!");
    setFont(label, "SansSerif-36");
    add(window, label);
    setLocation(label, 100, 200);
    pause(10);
    }
    else if(points<50)
    {
    GLabel label = newGLabel("Try again!");
    setFont(label, "SansSerif-36");
    add(window, label);
    setLocation(label, 100, 200);
    pause(10);
    }
    
    // wait for click before exiting
    if(bricks==0)
    { 
    waitForClick();
    // game over
    closeGWindow(window);
    }
    if(lives==0)
    { 
    waitForClick();
    // game over
    closeGWindow(window);
    }
    waitForClick();
    // game over
    closeGWindow(window);
    
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    int brick_y = 50; 
    int space = 20; 

    for (int i = 0; i < ROWS; i++) 
    {
        int brick_x = 2; 
        for (int j = 0; j < COLS; j++)
        {
            GRect brick = newGRect(brick_x + 5, brick_y, 35, 10);
            
            // Setting colors based on row. Not elegant.
            if (i == 0)
            {
                setColor(brick, "RED");
            }
            if (i == 1)
            {
                setColor(brick, "ORANGE");
            }
            if (i == 2)
            {
                setColor(brick, "YELLOW");
            }
            if (i == 3)
            {
                setColor(brick, "GREEN");
            }
            if (i == 4)
            {
                setColor(brick, "00FFFF"); //CYAN
            }
            
            setFilled(brick, true);
            add(window, brick);
            brick_x = brick_x + 39; 
        }
        brick_y = brick_y + 15;
    }
    
}

/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
    // TODO
    GOval ball = newGOval(300, 200, 20 ,20);
    setFilled(ball, true);
    setColor(ball, "BLACK");
    add(window, ball);
    return ball;
}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    // creats a paddle
    GRect paddle = newGRect(0,0,80,10);
    setColor(paddle,"GREY");
    setFilled(paddle, true);
    add(window, paddle);
    addToRegion(window, paddle, "SOUTH");
    return paddle;
}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    // TODO
    GLabel label = newGLabel("");
    setFont(label, "SansSerif-36");
    add(window, label);
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object ;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
