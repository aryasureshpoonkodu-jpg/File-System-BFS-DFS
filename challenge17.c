#include <stdio.h>
#include <string.h>

#define MAX 20

int graph[MAX][MAX];
int visited[MAX];
int n;

char files[MAX][30];

void BFS(int start, char target[]) {
    int queue[MAX], front = 0, rear = 0;
    int found = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    queue[rear++] = start;
    visited[start] = 1;

    printf("\nBFS Traversal: ");

    while (front < rear) {
        int current = queue[front++];

        printf("%s ", files[current]);

        if (strcmp(files[current], target) == 0)
            found = 1;

        for (int i = 0; i < n; i++) {
            if (graph[current][i] && !visited[i]) {
                queue[rear++] = i;
                visited[i] = 1;
            }
        }
    }

    if (found)
        printf("\nFile '%s' found using BFS.\n", target);
    else
        printf("\nFile '%s' not found using BFS.\n", target);
}

void DFSUtil(int current, char target[], int *found) {
    visited[current] = 1;

    printf("%s ", files[current]);

    if (strcmp(files[current], target) == 0)
        *found = 1;

    for (int i = 0; i < n; i++) {
        if (graph[current][i] && !visited[i]) {
            DFSUtil(i, target, found);
        }
    }
}

void DFS(int start, char target[]) {
    int found = 0;

    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nDFS Traversal: ");

    DFSUtil(start, target, &found);

    if (found)
        printf("\nFile '%s' found using DFS.\n", target);
    else
        printf("\nFile '%s' not found using DFS.\n", target);
}

int main() {
    int edges, u, v, start;
    char target[30];

    printf("Enter number of files/directories: ");
    scanf("%d", &n);

    if (n < 1 || n > MAX) {
        printf("Invalid number of files/directories.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter name of file/directory %d: ", i);
        scanf("%29s", files[i]);
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            graph[i][j] = 0;

    printf("Enter number of connections: ");
    scanf("%d", &edges);

    if (edges < 0 || edges > n * (n - 1) / 2) {
        printf("Invalid number of connections.\n");
        return 1;
    }

    printf("Enter connections using node indices (u v):\n");

    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);

        if (u < 0 || u >= n || v < 0 || v >= n || u == v) {
            printf("Invalid connection.\n");
            return 1;
        }

        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    printf("Enter starting node index: ");
    scanf("%d", &start);

    if (start < 0 || start >= n) {
        printf("Invalid starting node.\n");
        return 1;
    }

    printf("Enter file name to search: ");
    scanf("%29s", target);

    BFS(start, target);
    DFS(start, target);

    return 0;
}
