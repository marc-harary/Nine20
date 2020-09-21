# Nine20

The `Nine20.c` program solves the original [sliding tile game](https://www.google.com/search?q=sliding+tiles+board+puzzle&tbm=isch&ved=2ahUKEwjKtPHZifnrAhUxZN8KHfgkBgoQ2-cCegQIABAA&oq=sliding+tiles+board+puzzle&gs_lcp=CgNpbWcQAzoECCMQJzoCCAA6BQgAELEDOggIABCxAxCDAToECAAQQzoHCAAQsQMQQzoGCAAQCBAeOgQIABAYOgQIABAeUPAdWMY4YJU5aABwAHgAgAF-iAGsEpIBBDE5LjaYAQCgAQGqAQtnd3Mtd2l6LWltZ8ABAQ&sclient=img&ei=CP9nX8qQErHI_Qb4yZhQ&bih=821&biw=1440#imgrc=WszK9huczZpHPM). The usage is as follows: 

`Nine20 [HEIGHT WIDTH] MAXSTEPS INITIAL GOAL`

,where `INITIAL` is the board represented as a linear string of alphanumeric characters with exactly one `-` representing the gap in the board. Likewise, `GOAL` represents the final desired output. Additionally, the dimensions of the `INITIAL` may be specified.

The algorithm employed uses a depth-first graph search algorithm to determine the shortest sequence of moves needed to reach the `GOAL` state from the initial `INITIAL` state. These moves are stored as nodes both in a queue and a hash table (hashed using the `loselose` function). If the goal state is encountered in the queue, the algorithm uses the hash table to backtrack through the sequence of moves used to reach the current board in the tree and prints the moves in reverse order, i.e., in order of states in the tree used to search the graph. If the goal state is not reached in `MAXSTEPS` number of steps, then the program prints nothing.

`Nine20` is fairly robust and will check to ensure that the user input is valid.
