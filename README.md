# Ohjelmointi 2 projekti, matopeli

Ohjelmointi 2 kurssin viimeisenä projektina oli suunnitella graafinen käyttöliittymä matopeliin. 
Pohjakoodiksi oli annettu symbolinen matopeli(gameboard.hh, point.hh, gameboard.cpp ja point.cpp). 





![Symbolin matopeli](https://user-images.githubusercontent.com/30124819/216674800-b2cc4cb9-d4d0-402a-87de-997d836b376b.png)
Symbolinen matopeli


![Aloitusnäkymä](https://user-images.githubusercontent.com/30124819/216680779-a2bbe990-045f-452e-b36f-16fbdf3a3420.png)

Aloitusnäkymä




![Pelinäkymä](https://user-images.githubusercontent.com/30124819/216681181-7e72de51-c523-458b-ba69-81ff89948c56.png)

Pelinäkymä



![TUlos](https://user-images.githubusercontent.com/30124819/216680888-d16599b2-6e16-4d82-a7e5-7bf00b9ff7ce.png)

Tulostaulu


Alla vielä ohjeet, jotka on projektin tekemisen ohessa kirjoitettu.

#### Instructions to snake game.

You can specify the width, heigth and seed value that gameboard uses.
Width can be selected from range (5,40) and Height (5,30), semen value doesnt have range.
You have to enter your name for the game, otherwise it doesn't start.
After entering name and clicking play, tab changes to gametab where snake game starts.

the snake head is snakehead.png picture.
Last part of snake is blue.
Snake food is picture of orange.
All other parts of snake are red.

On top left corner there is pause, main and reset buttons.

Main button goes back to start screen.

Pause button pauses the game and prompts message box where you can choose to either
continue or go gack to main.

Reset button resets the score, time and snake position.

Score is shown on top right, it tells the length of snake minus head and updates everytime
food is eaten.

In the middle is your playername you entered before starting game.
on the right is timer, which updates every 100 milliseconds.

if you it lose or win it prompts message box saying game either lost or win.
Messagebox asks if you want to play again or not.
It will restart the game or go back to main window.
Also the background will flash red and green.

In the main window you also have scores button, which takes you to scores tab.
In there you can see all the players that have played the game in aplhabetical order.
Only the highest score of the player is saved in scoreboard.
Score is the lenght of your snake body, no matter in what size of field you were playing.
You can also clear scoreboard which also clears scores.txt file which saves all scores across
startups. scores.txt is read everytime program starts. If it doesn't open it wont alert user or crash
program.Note scores are saved even if you reset or go back to mainwindow by buttons

Additional features:
-You can change the width and height of the map between set ranges.

-Program tells the snake size whichis same as score

-Food and parts of snake are shown as photos

-Game has a timer

-Game has a scoreboard

-Background color changes when game is either lost or won Flashing red and green

-Game has an pause










