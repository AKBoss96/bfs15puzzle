# bfs15puzzle
This is the C++ implementation of the 15-puzzle using breadth-first search.

Execution instructions:
1. The initial tile configuration is passed as a 16-character string in the command line, where the numbers 1 through 9 are entered as is, the numbers 10 through 15 are represented as their hexadecimal equivalents A through F, and the empty tile is denoted by 0.

2. The goal state is represented as 123456789ABCDEF0.

3. The chrono header file and the std:chrono library require C++ 11 support.

4. Compile the program using g++ command.
	E.g., $ g++ bfs_15.cpp

5. Run the executable file a.out followed by the initial state on the command line.
	E.g., $ ./a.out 134852069A7BDEFC
