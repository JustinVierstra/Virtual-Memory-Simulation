# Virtual-Memory-Simulation

Simulating a virtual memory system using two page replacement algorithms. Least Recently Used (LRU) and Second-Chance (Clock).

```
COMPILE: gcc proj4.c -o proj4

USAGE: ./proj4 [input_file] [LRU | CLOCK]
```

Example Input:
```
10 4 30
5
4
4
3
2
5
1
6
6
5
2
7
1
6
1
2
6
9
6
0
2
3
6
5
3
2
6
7
7
1
```
LRU Output:
```
Page 5 loaded into Frame 0
Page 4 loaded into Frame 1
Page 4 already in Frame 1
Page 3 loaded into Frame 2
Page 2 loaded into Frame 3
Page 5 already in Frame 0
Page 4 unloaded from Frame 1, Page 1 loaded into Frame 1
Page 3 unloaded from Frame 2, Page 6 loaded into Frame 2
Page 6 already in Frame 2
Page 5 already in Frame 0
Page 2 already in Frame 3
Page 1 unloaded from Frame 1, Page 7 loaded into Frame 1
Page 6 unloaded from Frame 2, Page 1 loaded into Frame 2
Page 5 unloaded from Frame 0, Page 6 loaded into Frame 0
Page 1 already in Frame 2
Page 2 already in Frame 3
Page 6 already in Frame 0
Page 7 unloaded from Frame 1, Page 9 loaded into Frame 1
Page 6 already in Frame 0
Page 1 unloaded from Frame 2, Page 0 loaded into Frame 2
Page 2 already in Frame 3
Page 9 unloaded from Frame 1, Page 3 loaded into Frame 1
Page 6 already in Frame 0
Page 0 unloaded from Frame 2, Page 5 loaded into Frame 2
Page 3 already in Frame 1
Page 2 already in Frame 3
Page 6 already in Frame 0
Page 5 unloaded from Frame 2, Page 7 loaded into Frame 2
Page 7 already in Frame 2
Page 3 unloaded from Frame 1, Page 1 loaded into Frame 1
15 page faults
```

CLOCK Output:
```
Page 5 loaded into Frame 0
Page 4 loaded into Frame 1
Page 4 already in Frame 1
Page 3 loaded into Frame 2
Page 2 loaded into Frame 3
Page 5 already in Frame 0
Page 3 unloaded from Frame 2, Page 1 loaded into Frame 2
Page 2 unloaded from Frame 3, Page 6 loaded into Frame 3
Page 6 already in Frame 3
Page 5 already in Frame 0
Page 4 unloaded from Frame 1, Page 2 loaded into Frame 1
Page 1 unloaded from Frame 2, Page 7 loaded into Frame 2
Page 5 unloaded from Frame 0, Page 1 loaded into Frame 0
Page 6 already in Frame 3
Page 1 already in Frame 0
Page 2 already in Frame 1
Page 6 already in Frame 3
Page 7 unloaded from Frame 2, Page 9 loaded into Frame 2
Page 6 already in Frame 3
Page 2 unloaded from Frame 1, Page 0 loaded into Frame 1
Page 9 unloaded from Frame 2, Page 2 loaded into Frame 2
Page 6 unloaded from Frame 3, Page 3 loaded into Frame 3
Page 1 unloaded from Frame 0, Page 6 loaded into Frame 0
Page 0 unloaded from Frame 1, Page 5 loaded into Frame 1
Page 3 already in Frame 3
Page 2 already in Frame 2
Page 6 already in Frame 0
Page 5 unloaded from Frame 1, Page 7 loaded into Frame 1
Page 7 already in Frame 1
Page 2 unloaded from Frame 2, Page 1 loaded into Frame 2
17 page faults
```
