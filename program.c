#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100
#define MAX_SIZE 100

// Structure to represent an edge
typedef struct {
    int source;
    int destination;
} Edge;

// Structure to represent a graph
typedef struct {
    Edge edges[MAX_NODES];
    int numEdges;
    int numNodes;
} Graph;

// Function to initialize a graph
void initializeGraph(Graph* graph, int numNodes) {
    graph->numEdges = 0;
    graph->numNodes = numNodes;
}

// Function to add an edge to the graph
// Function to add an edge to the graph (for duplex connections)
void addEdge(Graph* graph, int source, int destination) {
    Edge edge1;
    edge1.source = source;
    edge1.destination = destination;

    Edge edge2;
    edge2.source = destination;
    edge2.destination = source;

    graph->edges[graph->numEdges] = edge1;
    graph->edges[graph->numEdges + 1] = edge2;
    graph->numEdges += 2;
}


// Function to perform depth-first search
void dfs(Graph* graph, int currentNode, int* visited, int* sequence, int* sequenceIndex) {
    visited[currentNode] = 1;
    sequence[(*sequenceIndex)++] = currentNode;

    int i;
    for (i = 0; i < graph->numEdges; i++) {
        Edge edge = graph->edges[i];
        if (edge.source == currentNode && !visited[edge.destination]) {
            dfs(graph, edge.destination, visited, sequence, sequenceIndex);
        }
    }
}

// Function to find the connection sequence
void findConnectionSequence(Graph* graph, int startNode, int* sequence) {
    int visited[MAX_NODES] = {0};
    int sequenceIndex = 0;

    dfs(graph, startNode, visited, sequence, &sequenceIndex);
    sequence[sequenceIndex] = startNode; // Add the starting node at the end
}

int findMaxFrequency(int arr[], int size) {
    int i, j;
    int frequency[MAX_SIZE] = {0}; // Initialize frequency array with 0
    int maxFrequency = 0;

    for (i = 0; i < size; i++) {
        int element = arr[i];
        int count = 0;

        for (j = 0; j < size; j++) {
            if (arr[j] == element) {
                count++;
            }
        }

        frequency[element] = count;

        if (count > maxFrequency) {
            maxFrequency = count;
        }
    }

    return maxFrequency;
}

int main() {
    // Example graph
    Graph graph;
    int numNodes = 3;
    int output =0;
    int arr[numNodes+1];
    initializeGraph(&graph, numNodes);
    int maxFrequency;
    // Adding edges
    addEdge(&graph, 0, 1);
    addEdge(&graph, 1, 2);
    addEdge(&graph, 0, 3);
    int startNode = 0;

    // Finding the connection sequence
    int sequence[MAX_NODES];
    findConnectionSequence(&graph, startNode, sequence);

    // Printing the connection sequence
    printf("Connection Sequence: ");
    int i;
    for (i = 0; i < graph.numNodes + 1; i++) {
         arr[i]=sequence[i];
        printf("%d ", sequence[i]);
    }
    printf("\n"); 
    int size = sizeof(arr) / sizeof(arr[0]);
    maxFrequency = findMaxFrequency(arr, size);
    printf("No of connections to be changed: %d\n", maxFrequency-1);
    return 0;
}
