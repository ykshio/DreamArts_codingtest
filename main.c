#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NODES 100

typedef struct {
    int start;
    int end;
    double distance;
} Edge;

Edge edges[MAX_NODES];
int numEdges = 0;
double maxDistance = 0.0;
int maxPath[MAX_NODES];
int currentPath[MAX_NODES];
int visited[MAX_NODES];
int pathIndex = 0;

void findLongestPath(int node, double currentDistance) {
    visited[node] = 1;
    currentPath[pathIndex++] = node;

    if (currentDistance > maxDistance) {
        maxDistance = currentDistance;
        for (int i = 0; i < pathIndex; i++) {
            maxPath[i] = currentPath[i];
        }
        // Null-terminate the path to avoid leftover nodes
        maxPath[pathIndex] = 0;
    }

    for (int i = 0; i < numEdges; i++) {
        if (edges[i].start == node && !visited[edges[i].end]) {
            findLongestPath(edges[i].end, currentDistance + edges[i].distance);
        }
    }

    visited[node] = 0;
    pathIndex--;
}

int main() {
    printf("Enter all edges in the format (start, end, distance) separated by newlines (end with an empty line):\n");

    char line[256];
    while (fgets(line, sizeof(line), stdin) && line[0] != '\n') {
        sscanf(line, "%d, %d, %lf", &edges[numEdges].start, &edges[numEdges].end, &edges[numEdges].distance);
        numEdges++;
    }

    int maxNode = 0;
    for (int i = 0; i < numEdges; i++) {
        if (edges[i].start > maxNode) maxNode = edges[i].start;
        if (edges[i].end > maxNode) maxNode = edges[i].end;
    }

    // Try finding the longest path from every possible starting node
    for (int i = 1; i <= maxNode; i++) {
        findLongestPath(i, 0.0);
    }

    for (int i = 0; i < MAX_NODES && maxPath[i] != 0; i++) {
        printf("%d\r\n", maxPath[i]);
    }

    return 0;
}

