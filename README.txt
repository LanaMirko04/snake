SNAKE
=====

Descrizione
-----------
Avevo la polmonite, ero annoiato e non sapevo cosa fare. 
Per il resto, è un semplicissimo gioco di "snake" scritto in C.

Features
--------
- Un serpente che si muove (non è scontato)
- Mele da mangiare
- L'effetto più amato dai terrapiattisti (Pacman)
- Sistema di punteggio (inutile)

Installazione
-------------
1. Clona la repository ed entra nella cartella:
   git clone https://github.com/LanaMirko04/snake.git && cd snake

2. Compila il progetto (potrebbe essere necessario cambiare "gcc-14" in "gcc"):
   make

3. Esegui il programma:
   ./bin/snake

Come si usa
-----------
Esegui './bin/snake -h' per visualizzare le opzioni di utilizzo. 
Per i più pigri, ecco una copia dell'output:

Usage: snake [OPTIONS]

Options:
  -h           Show this help message and exit.
  -d           Specify the difficulty of the game (easy, normal,
               hard). Default is normal.

Controls:
  Arrow keys   Move the snake (Up, Down, Left, Right).
  W            Move Up.
  A            Move Left.
  S            Move Down.
  D            Move Right.
  Q            Quit the game.

Description:
  A classic arcade Snake game with a twist: when you hit the
  wall you don't die; instead, you lose points.


Usage: snake [OPTIONS]

Options:
  -h           Show this help message and exit.
  -d           Specify the difficulty of the game (easy, normal,
               hard). Default is normal.

Controls:
  Arrow keys   Move the snake (Up, Down, Left, Right).
  W            Move Up.
  A            Move Left.
  S            Move Down.
  D            Move Right.
  Q            Quit the game.

Description:
  A classic arcade Snake game with a twist: when you hit the
  wall you don't die; instead, you lose points.
