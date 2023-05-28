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

## Getting Started

To run the Risk Game on your local machine, follow the instructions below:

1. **Clone the repository**: Begin by cloning this repository to your local machine using the following command:
   ```
   git clone <repository-url>
   ```

2. **Compile the code**: Navigate to the cloned directory and compile the C++ code using a C++ compiler. For example, if you have GCC installed, you can compile the code using the following command:
   ```
   g++ risk.cpp -o risk
   ```

3. **Run the game**: Once the code is compiled successfully, run the game by executing the generated executable. Use the following command:
   ```
   ./risk
   ```

## Gameplay

1. **Objective**: The objective of the game is to conquer the entire world by eliminating all other players or by successfully occupying all territories on the game board.

2. **Setup**: At the beginning of the game, each player will be assigned territories equally. The number of territories each player receives depends on the total number of players. Players take turns in clockwise order.

3. **Game Flow**: The game consists of multiple rounds, each divided into three phases: reinforcement, attack, and fortification.


   - **Reinforcement Phase**: In this phase, players receive additional armies based on the number of territories they occupy and the continents they control. Players can strategically place their newly acquired armies on their territories.

   - **Attack Phase**: Players can choose to attack neighboring territories held by other players. The attacking player must have at least two armies on the attacking territory and can roll dice to determine the outcome of the battle. The number of dice rolled depends on the number of armies on the attacking and defending territories.

   - **Fortification Phase**: Players can choose to move armies between their territories to reinforce their positions. This phase allows players to strengthen their defenses or prepare for an attack.

4. **Game Progression**: Players continue to take turns, going through the reinforcement, attack, and fortification phases until one player conquers the entire world or the game reaches a predefined number of rounds.

5. **Winning the Game**: The game ends when one player controls all the territories on the game board or when the maximum number of rounds is reached. The player who achieves this goal is declared the winner.

6. **Player AI**: The game features an AI implementation using the strategy pattern. Each AI player has a specific strategy that determines its decision-making during the game. The AI players will make strategic moves based on their assigned strategies.

7. **Game Options**: The game may offer additional options such as saving and loading game states, displaying game statistics, or enabling different rule variations. These options can be accessed through the game's menu system.

## Controls

The game is played entirely using the console. You will be presented with menu options and prompts to enter your choices and commands. The specific controls and commands will be displayed on the screen during gameplay.

## Limitations and Future Enhancements

- The current implementation is limited to a console-based version of the Risk Game. A graphical user interface (GUI) could be developed to enhance the gameplay experience.

- The game could be expanded to include additional features such as online gameplay.

- The current version may have some limitations and bugs. Your feedback and contributions are welcome
