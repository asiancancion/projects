# Shannon Switching Game Implementation

**Author**: Caleb Song  
**Section**: M3 De Freitas  
**Project**: PEX5  
**Purpose**: The purpose of this project is to implement the necessary functions to create a Shannon Switching Game. This game involves two players: **Cut** and **Short**. One player attempts to cut edges to prevent a connection between two vertices, while the other player tries to protect the edges to maintain the connection.

## Game Overview

- **Cut Player**: The goal is to cut edges and disconnect the starting and ending vertices.
- **Short Player**: The goal is to protect edges and ensure that there is a continuous path from the starting vertex to the ending vertex.
- **AI or Human Players**: Players can either be human or AI-controlled. The AI follows a decision-making process based on Dijkstra’s shortest path algorithm.

## Functionality

### `setPlayerType()`
This function sets the type of player, either **human** or **AI**, for both the Cut and Short players.

### `setActivePlayer()`
This function is called at the start of the game to determine which player will take the first turn.

### `createVertices()`
This function randomly generates vertices for the game graph within specific constraints, ensuring that vertices are within the window's borders and are not too close to one another.

### `createEdges()`
This function creates random edges between vertices within a certain range. The edges represent the connections between vertices, which can either be cut or protected by the players.

### `runDjikstras()`
This function runs Dijkstra’s algorithm to calculate the shortest path from the starting vertex to the ending vertex. It generates a table that shows the cost of reaching each vertex and helps determine the next move for the AI.

### `checkWinner()`
This function checks if either the **Cut** or **Short** player has won the game by analyzing the graph and the Dijkstra table. If the **Cut** player successfully disconnects the graph, they win. If the **Short** player manages to keep a connection, they win.

### `doTurn()`
This is the main game loop that handles a player's turn. It checks whether the player is a human or AI and performs the appropriate action (cutting or protecting edges). After each turn, the function checks if there is a winner.

## Key Functions

### `humanPlayer()`
This function processes a turn for a human player. The human player uses mouse clicks to select edges to either cut or protect.

### `aiPlayer()`
This function handles the AI player’s turn. The AI player uses Dijkstra's algorithm to determine the most strategic move (cutting or protecting an edge) based on the current state of the graph.

### `drawGraph()`
This function visually renders the graph on the screen, showing the vertices and edges. It also displays the game's current state, including which player is currently taking a turn.
