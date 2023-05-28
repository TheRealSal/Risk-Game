# COMP-345-Assignment

<p align="center">
  <a href="https://github.com/CSG48-TZ/comp-345-project">
  <img src="./Assets/C++logo.png" height="128">
  </a>
</p>

## Team Members 

<div align="center">
<table>
  <tr>
    <td align="center"><a href="https://github.com/CSG48-TZ"><img src="https://avatars.githubusercontent.com/u/82446800?v=4" width="100px;" alt=""/><br /><sub><b> Tongwei Zhang</b></sub></a></td>
    <td align="center"><a href="https://github.com/DaxInvader"><img src="https://avatars.githubusercontent.com/u/24554538?v=4" width="100px;" alt=""/><br /><sub><b>Dario Cimmino</b></sub></a></td>
    <td align="center"><a href="https://github.com/junkokie"><img src="https://avatars.githubusercontent.com/u/76203567?v=4" width="100px;" alt=""/><br /><sub><b>Wanjun Gong</b></sub></a></td>
    <td align="center"><a href="https://github.com/therealsal"><img src="https://avatars.githubusercontent.com/u/75696327?v=4" width="100px;" alt=""/><br /><sub><b>Salman Hussain Ali</b></sub></a></td> 
    <td align="center"><a href="https://github.com/jvobuu"><img src="https://avatars.githubusercontent.com/u/61026480?v=4" width="100px;" alt=""/><br /><sub><b>Jeremy Vo Buu</b></sub></a></td> 
  </tr>
</table>
</div>
<br>

Concordia University 2023


# Risk Game (Console)

Welcome to the Risk Game! This is a console-based implementation of the popular strategy board game, Risk, created using C++. In this game, you will engage in a battle for global domination by strategically deploying your armies and conquering territories.

## Gameplay

1. **Objective**: The objective of the game is to conquer the entire world by eliminating all other players or by successfully occupying all territories on the game board.

2. **Setup**: At the beginning of the game, each player will be assigned territories randomly. The number of territories each player receives depends on the total number of players. Players take turns in clockwise order.

3. **Game Flow**: The game consists of multiple rounds, each divided into three phases: reinforcement, issue orders, and execution.

![Screen Shot 2023-05-28 at 3 40 18 PM](https://github.com/TheRealSal/Risk-Game/assets/75696327/3172d2e5-f791-4370-a2b2-70b4f6d5b29a)

   - **Reinforcement Phase**: In this phase, players receive additional armies based on the number of territories they occupy and the continents they control. Players can strategically place their newly acquired armies on their territories.

   - **Issue Orders Phase**: In this phase, players can issue orders to their armies. They can choose to attack neighboring territories, reinforce their own territories, or make other strategic moves. Each player takes turns issuing orders.

   - **Execution Phase**: In this phase, the orders issued by the players are executed. Attacks are resolved, reinforcements are deployed, and the game board is updated accordingly.

4. **Game Progression**: Players continue to take turns, going through the reinforcement, issue orders, and execution phases until one player conquers the entire world or the game reaches a predefined number of rounds.

5. **Winning the Game**: The game ends when one player controls all the territories on the game board or when the maximum number of rounds is reached. The player who achieves this goal is declared the winner.

6. **Player AI**: The game features an AI implementation using the strategy pattern. Each AI player has a specific strategy that determines its decision-making during the game. The AI players will make strategic moves based on their assigned strategies.

7. **Game Options**: The game may offer additional options such as saving and loading game states, displaying game statistics, or enabling different rule variations. These options can be accessed through the game's menu system.

## Controls

![Screen Shot 2023-05-28 at 3 40 09 PM](https://github.com/TheRealSal/Risk-Game/assets/75696327/17a22b2f-8d06-43cb-910a-974f3166dbb1)

The game is played entirely using the console. You will be presented with menu options and prompts to enter your choices and commands. The specific controls and commands will be displayed on the screen during gameplay.

## Limitations and Future Enhancements

- The current implementation is limited to a console-based version of the Risk Game. A graphical user interface (GUI) could be developed to enhance the gameplay experience.

- The game could be expanded to include additional features, such as multiplayer support or online gameplay.

- The current version may have some limitations and bugs. Your feedback and contributions are welcome to improve the game.

- The current version may have some limitations and bugs. Your feedback and contributions are welcome
