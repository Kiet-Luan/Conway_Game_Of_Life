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

Here's a randomly generated seed.

![GameOfLife](https://github.com/Kiet-Luan/Conway_Game_Of_Life/assets/143954671/254db2c6-ca92-444d-8cff-fc202fd74140)

There are two files uploaded. The new version has been updated by:

1. Removing unnecessary #include
2. Removed pointers
3. Simplified input and output operations
4. Combined and condensed conditions into loop
5. Added Comments
