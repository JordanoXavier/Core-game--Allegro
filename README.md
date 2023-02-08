# Final Work of the Programming Laboratory I discipline of the Computer Science course at UFSM.

  Developed with the Allegro 5 library, it is a version of the "Core" Game, recreated in C with additional functionalities.


## Help:

### Commands:
  Mouse: controls the defense circle.
  Click: shoot with the cannon, destroying the orbs.
  Esc: enable pause, when available

### Life:
  When hit by a red orb, the player's radius is reduced.
  When hit by a blue orb, the player's radius is increased.
 
### Levels:
  Every 15 points you reach a new level.
  With each level the speed increases by 1.05x.
  One pause per level is allowed.
  The shield can be used every 3 levels.
  Every 5 levels an extra orb will appear on the screen.
  Every 10 levels the player gains a life.
  Every 50 points the special missile is activated.


## Run the game:

  To run the game, unzip the file "Allegro.c", open it in the IDE and put the code in the terminal: gcc Allegro.c -o main -lallegro -lallegro_font -lallegro_primitives -Wall