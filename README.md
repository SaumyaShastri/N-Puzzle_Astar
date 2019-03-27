# N-Puzzle_Astar
Solving the N-tile puzzle using the A* search 


N-Puzzle or sliding puzzle is a popular puzzle that consists of N tiles where N can be 8, 15, 24 and so on. The puzzle is divided into √(N+1) rows and √(N+1) columns eg. 15-Puzzle will have 4 rows and 4 columns, an 8-Puzzle will have 3 rows and 3 columns and so on. The puzzle consists of one empty space where the tiles can be moved and thus the puzzle is solved when a particular goal pattern is formed like the following is one of the variant goal patterns.
In computer science, A* (pronounced "A star") is a computer algorithm that is widely used in pathfinding and graph traversal, which is the process of finding a path between multiple points, called "nodes". It enjoys widespread use due to its performance and accuracy. However, in practical travel-routing systems, it is generally outperformed by algorithms which can pre-process the graph to attain better performance, although other work has found A* to be superior to other approaches.
A* is an informed search algorithm, or a best-first search, meaning that it is formulated in terms of weighted graphs: starting from a specific starting node of a graph, it aims to find a path to the given goal node having the smallest cost (least distance travelled, shortest time, etc.). It does this by maintaining a tree of paths originating at the start node and extending those paths one edge at a time until its termination criterion is satisfied.

At each iteration of its main loop, A* needs to determine which of its paths to extend. It does so based on the cost of the path and an estimate of the cost required to extend the path all the way to the goal. Specifically, A* selects the path that minimizes
f(n)=g(n)+h(n)
where n is the next node on the path, g(n) is the cost of the path from the start node to n, and h(n) is a heuristic function that estimates the cost of the cheapest path from n to the goal. A* terminates when the path it chooses to extend is a path from start to goal or if there are no paths eligible to be extended. The heuristic function is problem-specific. If the heuristic function is admissible, meaning that it never overestimates the actual cost to get to the goal, A* is guaranteed to return a least-cost path from start to goal.
This implementation checks for the solvability of the initial state (which must be unique). The Manhattan Distance heuristic is used in this implementation along with priority queues. It outputs at every step - the state of the problem, and the f,g,h values. The final output shows the final state, the total number of steps taken, and the number of total optimal steps taken.
NOTE: A* can only be used to solve 8-Puzzle it uses much more memory for solving higher N as the memory consumption is exponential in A* because of the closed and the open lists that are to be maintained, for higher N we use memory constrained version of the A* algorithm like the IDA* algorithm. The basic algorithms change but rest everything remains as it is. Make sure you go through my post on IDA* algorithm. IDA* algorithm can be used for higher values of N since it uses memory linearly. If used with proper heuristics it can solve 15-Puzzle in a few seconds.