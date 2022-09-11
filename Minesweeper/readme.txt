INSTALLATION
- Make sure you have the most recent Visual Studio Redistributables downloaded

GAME
- Click the smiley to reset the board at any time.
- The three test buttons on the bottom right will load prewritten boards from the .brd files in boards/.
- The button with the eye on it is the toggle debug button, which will allow you to see the positions of the hidden mines.
- First line of boards/config.cfg is the width.
- Second line is the height.
- Third is the mine count for randomized boards.
- If you change the config dimensions, the test boards will not work unless you manually 
	change them to have the same dimensions. This will not close the program, but the 
	buttons themselves will seemingly do nothing.
- If you remove a directory or change the names of any files in boards/ or images/, the program will likely not run.
	You should, hypothetically, be allowed to change the files themselves though, just with the same name and format.
	The outcome will be unpredicatable, but the program should still run.
- Don't try to change the window size...