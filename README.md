# Flow-Solver
An AI written in C to solve the puzzle game "Flow Free"
Flow Free is a puzzle game where the player is given a grid with coloured dots. The aim of the game is to connect all dots of the same colour with lines that never intersect and fill the whole grid. See the below image for an example of an initial board and said board in a solved state.
![Example of an initial and solved flow game](images/example.png)
The AI is implemented using Dijkstra's algorithm. In this implementation a vertex is a state in the game as such the total number of vertices could expand factorially with the game size. Since Dijkstra's algorithm usually has a performance of O(V^2), the performance of the program is heavily reliant on the algorithm choosing the best paths and stopping when a path cannot lead to a solution using color selection and dead end detection.

## How to run
Compile the files from the main directory using the command
`make`
Then run on an example puzzle using the command 
`./flow puzzles/jumbo_11x11_01.txt -d`
The `-d` flag enables dead end detection, significantly optimising the performance of the AI.

