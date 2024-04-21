# simpleGraphs

HW6 will ask you to read and modify part of these codes.

* `graphClass.h` has the graph implementation for directed graphs. (Note: you could use this for undirected graphs as well by adding edges both ways)
* `graphTest.cpp` has starter code for creating new graphs and testing graph algorithms with string graphs.

Compile graphTest using the following line:
    
    clang++ -std=c++11 graphTest.cpp -o graphTest

After compiling graphTest, you can run with command line options.

#### default:

    ./graphTest
* This creates an example graph (shown below) with three nodes and no cycles

[Example Graph](./imgs/exampleGraph.png raw=true)

#### cycle:

    ./graphTest cycle
* This creates an example graph with five nodes and two cycles

[Example Cycle](./imgs/exampleCycle.png)

#### input
    
    ./graphTest input <n>
* This prompts the user to input n nodes
* It further prompts the user to input the number of edges
and space delimited pairs of nodes to define each edge

##### Example:
    

    ./graphTest input 3
    Enter 3 nodes
    >> A B C
    Enter number of edges
    >> 5
    A B
    A C
    B C
    B A
    C B
