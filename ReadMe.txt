Since there were no specific technologies defined, I decided to implement the assignment in C and create a console application.
I have used Cygwin. The GCC version that I used is 9.3.0.

Instructions on how to compile and run the app (after it is downloaded to the local repo):

	1. In Cygwin, navigate to the git repo
	2. Run the following command: gcc main.c IO_handling.c -o main
	3. After the compilation is done, a main.exefile will appear
	4. Run the app using the command: ./main

Details of the implementation:

Since not all of the scenarios are defined in detail, I had to take some assumptions.

- For the max number of games, I can take either the usual number of teams in the World Cup divided by 2 or the number of countries divided by 2. I took the second option with a small buffer.
- No need to check if the countries that are added really exist (example: if a country named asdf is added, this will be allowed). Check for this can also be added but is not part of this solution.
- Only allowed characters in team names are letters (both lowercase and uppercase). If anything else is entered, it will trigger an error.
- It is not allowed to enter the same team as team A and team B (an issue will be reported).
- When removing a team or changing a score, teams need to be entered in the same order as they are on the board.
- The app will not allow adding the same team multiple times.
- The app will not allow adding the same team as team A and team B.
- There are protections for faulty inputs. There are no smarts to suggest or to correct mistakes when inputting data. (it has to be done again correctly)