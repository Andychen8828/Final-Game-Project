# Final-Game-Project

# Game Rules
The game presents various light patterns, and the player must react correctly within a time limit by pressing buttons or responding to light levels to score points. The game becomes progressively more challenging as the player advances through rounds.

Push the slide switch to right, then the game starts
Viruses will show up from left or right side, or both sides
Viruses are red LEDs
Holding the left button destroys the enemies from left side one by one, and vice versa with the right button
Kill all of them in order to survive before the enemy kills you, then game over 
And if you used wrong side weapon, they will 100% catch the chance to kill you, then game over again
The game will stop when you beat it or click the wrong button
Press reset button to start over

# Scoring system:
Each virus you kill gives you a point, the goal is to get as many points as you can by beating the game.

# Inputs:
Slide Switch State: Determines if the game is turned on or off
Button Presses: The code reads the states of the left and right buttons. These inputs are used to detect player responses during certain game modes.

# Outputs:
LED Patterns: Depending on the randomly generated lightMode, the code controls the LEDs on the Circuit Playground board to create various light patterns.
Tones: A tone is played when the round is completed
Player’s Score: The serial monitor calculates and updates the player's score based on their performance during the game.
