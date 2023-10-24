# Conway_Game_Of_Life
C++ Code based on Conway's Game of Life
This is my first coding project in C++.

The game must follow the rules of:

1. Randomly generated seed with 40% chance to live (size should be entered in by user) or read in a board from a bpm file (file specify by user).
2. Program should evolve over a 1000 iterations and at each iteration, the current board should be saved as a pbm file.
3. If <=1 Neighbor, cell dies of lonliness.
4. If = 2 Neighbors, cell survives
5. If = 3 Neighbors, cell will make a new occupied cell if unoccupied and if occupied, remain occupied.
6. If >=4 Neighbors, cell dies by over crowding.
