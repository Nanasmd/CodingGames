#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

/*int main()
{
    // amount of hexagonal cells in this map
    int number_of_cells;
    scanf("%d", &number_of_cells);
    for (int i = 0; i < number_of_cells; i++) {
        // 0 for empty, 1 for eggs, 2 for crystal
        int type;
        // the initial amount of eggs/crystals on this cell
        int initial_resources;
        // the index of the neighbouring cell for each direction
        int neigh_0;
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        scanf("%d%d%d%d%d%d%d%d", &type, &initial_resources, &neigh_0, &neigh_1, &neigh_2, &neigh_3, &neigh_4, &neigh_5);
    }
    int number_of_bases;
    scanf("%d", &number_of_bases);
    for (int i = 0; i < number_of_bases; i++) {
        int my_base_index;
        scanf("%d", &my_base_index);
    }
    for (int i = 0; i < number_of_bases; i++) {
        int opp_base_index;
        scanf("%d", &opp_base_index);
    }

    // game loop
    while (1) {
        for (int i = 0; i < number_of_cells; i++) {
            // the current amount of eggs/crystals on this cell
            int resources;
            // the amount of your ants on this cell
            int my_ants;
            // the amount of opponent ants on this cell
            int opp_ants;
            scanf("%d%d%d", &resources, &my_ants, &opp_ants);
        }

        // Write an action using printf(). DON'T FORGET THE TRAILING \n
        // To debug: fprintf(stderr, "Debug messages...\n");


        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
        printf("WAIT\n");
    }

    return 0;
}*/

#define MAX_CELLS 1000

// the Cell structure
typedef struct {
    int type;
    int initial_resources;
    int neigh[6];
} Cell;

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        exit(0);
    }
    newNode->data = v;
    newNode->next = NULL;
    return newNode;
}

// BFS to find the shortest distance from source cell to the base
int bfs(int source, int base, Cell cells[], int numberOfCells) {
    Node* queue[MAX_CELLS];
    int front = 0;
    int rear = -1;
    int dist[MAX_CELLS];
    for (int i = 0; i < numberOfCells; i++) {
        dist[i] = -1;
    }

    queue[++rear] = createNode(source);
    dist[source] = 0;

    while (front <= rear) {
        Node* temp = queue[front++];
        for (int i = 0; i < 6; i++) {
            int u = cells[temp->data].neigh[i];
            if (u != -1 && dist[u] == -1) {
                dist[u] = dist[temp->data] + 1;
                queue[++rear] = createNode(u);
            }
        }
    }
    return dist[base];
}

int main() {
    int numberOfCells;
    scanf("%d", &numberOfCells);
    Cell cells[MAX_CELLS];
    for (int i = 0; i < numberOfCells; i++) {
        scanf("%d %d", &cells[i].type, &cells[i].initial_resources);
        for (int j = 0; j < 6; j++) {
            scanf("%d", &cells[i].neigh[j]);
        }
    }

    int numberOfBases;
    scanf("%d", &numberOfBases);
    int myBaseIndex;
    scanf("%d", &myBaseIndex);
    int oppBaseIndex;
    scanf("%d", &oppBaseIndex);

    while (1) {
        int resources, myAnts, oppAnts;
        int bestCell = -1, bestDist = 1000000000, minOpponentAnts = 1000000000;
        for (int i = 0; i < numberOfCells; i++) {
            scanf("%d %d %d", &resources, &myAnts, &oppAnts);
            if (cells[i].type == 2 && resources > 0) {
                int dist = bfs(i, myBaseIndex, cells, numberOfCells);
                int opponentAnts = 0;
                for (int j = 0; j < 6; j++) {
                    int neigh = cells[i].neigh[j];
                    if (neigh != -1) {
                        opponentAnts += oppAnts;
                    }
                }
                if (dist < bestDist || (dist == bestDist && opponentAnts < minOpponentAnts)) {
                    bestCell = i;
                    bestDist = dist;
                    minOpponentAnts = opponentAnts;
                }
            }
        }

        if (bestCell != -1) {
            printf("LINE %d %d 1\n", myBaseIndex, bestCell);
        } else {
            printf("WAIT\n");
        }
    }

    return 0;
}
