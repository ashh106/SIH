// Task 2.
// Spanning Tree
// Implement an algorithm to find a spanning tree of a given graph using Depth-First Search (DFS).
// Create a class Graph that represents an undirected graph using an adjacency list.
// The class should support adding edges and display the adjacency list.
// Write a function findSpanningTree() that takes a starting node and returns a spanning tree of the graph.
// Use Depth-First Search (DFS) to find the spanning tree.
// Use an adjacency list to represent the graph.
// Create a graph and add the following edges:
// c++
// graph.addEdge(0, 1);
// graph.addEdge(0, 2);
// graph.addEdge(1, 2);
// graph.addEdge(1, 3);
// graph.addEdge(2, 4);
// graph.addEdge(3, 4);

#include <stdio.h>
#include <stdlib.h>

// Define the adjacency list node structure
struct AdjListNode {
    int dest;
    struct AdjListNode* next;
};

// Define the adjacency list structure
struct AdjList {
    struct AdjListNode *head;
};

// Define the graph structure
struct Graph {
    int V;
    struct AdjList* array;
};

// Function to create a new adjacency list node
struct AdjListNode* newAdjListNode(int dest) {
    struct AdjListNode* newNode = (struct AdjListNode*) malloc(sizeof(struct AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

// Function to create a graph of V vertices
struct Graph* createGraph(int V) {
    struct Graph* graph = (struct Graph*) malloc(sizeof(struct Graph));
    graph->V = V;

    // Create an array of adjacency lists. Size of array will be V
    graph->array = (struct AdjList*) malloc(V * sizeof(struct AdjList));

    // Initialize each adjacency list as empty by making head as NULL
    for (int i = 0; i < V; ++i)
        graph->array[i].head = NULL;

    return graph;
}

// Function to add an edge to an undirected graph
void addEdge(struct Graph* graph, int src, int dest) {
    // Add an edge from src to dest. A new node is added to the adjacency list of src. The node is added at the beginning
    struct AdjListNode* newNode = newAdjListNode(dest);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;

    // Since graph is undirected, add an edge from dest to src also
    newNode = newAdjListNode(src);
    newNode->next = graph->array[dest].head;
    graph->array[dest].head = newNode;
}

// Utility function for DFS traversal
void DFSUtil(struct Graph* graph, int v, int visited[], struct Graph* spanningTree) {
    // Mark the current node as visited
    visited[v] = 1;

    // Recur for all the vertices adjacent to this vertex
    struct AdjListNode* temp = graph->array[v].head;
    while (temp) {
        int connectedVertex = temp->dest;

        // If an adjacent vertex has not been visited, then add the edge and recur
        if (!visited[connectedVertex]) {
            addEdge(spanningTree, v, connectedVertex);
            DFSUtil(graph, connectedVertex, visited, spanningTree);
        }
        temp = temp->next;
    }
}

// Function to find the spanning tree using DFS
struct Graph* findSpanningTree(struct Graph* graph, int startVertex) {
    // Create a visited array and mark all vertices as not visited
    int* visited = (int*) malloc(graph->V * sizeof(int));
    for (int i = 0; i < graph->V; ++i)
        visited[i] = 0;

    // Create a new graph to store the spanning tree
    struct Graph* spanningTree = createGraph(graph->V);

    // Call the recursive helper function to store the spanning tree
    DFSUtil(graph, startVertex, visited, spanningTree);

    return spanningTree;
}

// Function to print the adjacency list representation of graph
void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->V; ++v) {
        struct AdjListNode* temp = graph->array[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v);
        while (temp) {
            printf("-> %d", temp->dest);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main() {
    // Create a graph given in the above diagram
    int V = 5;
    struct Graph* graph = createGraph(V);
    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);

    // Print the adjacency list representation of the above graph
    printf("Original graph:\n");
    printGraph(graph);

    // Find and print the spanning tree
    struct Graph* spanningTree = findSpanningTree(graph, 0);
    printf("\nSpanning tree:\n");
    printGraph(spanningTree);

    return 0;
}
