# Connect-n
Do you ever miss the days where you and your friend would spend hours on end playing Connect-4 under your about-to-collapse blanket fort? Time  passed by so quickly when we played this simple game. It was addicting really, to play over and over again to see if placing a piece here instead of _**there**_ could change the fate of the game. 

In this game of Connect-n, we play with different variations of board sizes and target connected number of pieces. In main.cpp, you can decide the number of columns, number of levels and number of connections, respectively, with a maximum of 5. In this example, we'll be playing on a 3 by 3 board with a target connection of 3. 

<p float="left">

<img width="350" alt="Screen Shot 2022-01-04 at 1 50 11 PM" src="https://user-images.githubusercontent.com/81529754/148109687-a834c75d-e133-452c-8787-f06544e5c367.png">

<img width="350" alt="Screen Shot 2022-01-04 at 1 50 14 PM" src="https://user-images.githubusercontent.com/81529754/148109706-86fb66d0-cc53-4319-a035-3bf1bc828360.png">
</p>


# The Player 
There are three kind of player types in Connect-N: HumanPlayer, BadPlayer, SmartPlayer.

**HumanPlayer**
Pretty self explanatory I hope.

**BadPlayer**
This is a computer player that will place a piece at the first empty column it identifies. 

**Smart Player**
This is where the gold is. The SmartPlayer is a computer player that will calculate the most optimal move each round by playing through every possible outcome of the game. Well of course, there's the limitation of time since we don't want to wait forever. You can change the time in the provided.h file. I used recursion here to play through every move and assigned 0, -1, and 1 to the move if it would result in a tie, loss or a win respectively. The SmartPlayer would place its piece in the column that would result in the quickest win. If it isn't able to win (humans can be smarter than computers sometime!), it will place its piece in the column that would result in the quickest tie. 
