#include <iostream>
#include <climits>
#include <string>
using namespace std;

#define MAX 5  // Number of servers

// Simulate fetching content from a server
void fetch_from_server(int serverID, int contentID) {
    if (serverID == -1) {
        cout << "Fetching content from Origin Server for content ID: " << contentID << endl;
        cout << "Content for content ID " << contentID << " has been fetched from the Origin Server." << endl;
    } else {
        cout << "Fetching content from Server " << serverID << " for content ID: " << contentID << endl;
        cout << "Content for content ID " << contentID << " has been fetched from Server " << serverID << "." << endl;
    }
}

class Graph {
private:
    int nov;          // Number of vertices (servers)
    int g[MAX][MAX];  // Latency matrix

public:
    Graph(int vertices);
    void displayGraph();
    void findNearestServers(int, int[]);
};

// Constructor to initialize the graph
Graph::Graph(int vertices) {
    nov = vertices;

    // Initialize graph with predefined latencies
    for (int i = 0; i < nov; i++) {
        for (int j = 0; j < nov; j++) {
            if (i == j)
                g[i][j] = 0;
            else
                g[i][j] = INT_MAX;
        }
    }

    // Predefined connections
    g[0][1] = 10; g[1][0] = 10;
    g[0][2] = 20; g[2][0] = 20;
    g[1][2] = 5;  g[2][1] = 5;
    g[2][3] = 15; g[3][2] = 15;
    g[3][4] = 30; g[4][3] = 30;
}

// Display the graph (latency matrix)
void Graph::displayGraph() {
    cout << "Graph (Latency Matrix):\n";
    for (int i = 0; i < nov; i++) {
        for (int j = 0; j < nov; j++) {
            if (g[i][j] == INT_MAX)
                cout << "INF\t";
            else
                cout << g[i][j] << "\t";
        }
        cout << endl;
    }
}

// Find the nearest servers
void Graph::findNearestServers(int startServer, int nearestServers[]) {
    int dist[MAX];       // Store shortest distances
    bool visited[MAX];   // Track visited servers

    // Initialize distances
    for (int i = 0; i < nov; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
    }
    dist[startServer] = 0;

    for (int count = 0; count < nov - 1; count++) {
        int minDist = INT_MAX, u = -1;

        // Find the nearest unvisited server
        for (int v = 0; v < nov; v++) {
            if (!visited[v] && dist[v] < minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        visited[u] = true;

        for (int v = 0; v < nov; v++) {
            if (!visited[v] && g[u][v] != INT_MAX && dist[u] != INT_MAX && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
            }
        }
    }

    // Sort servers by distance
    for (int i = 0; i < nov; i++) nearestServers[i] = i;
    for (int i = 0; i < nov - 1; i++) {
        for (int j = i + 1; j < nov; j++) {
            if (dist[nearestServers[i]] > dist[nearestServers[j]]) {
                swap(nearestServers[i], nearestServers[j]);
            }
        }
    }
}

int main() {
    Graph g(5);
    g.displayGraph();

    int startServer = 1;
    int nearestServers[MAX];
    g.findNearestServers(startServer, nearestServers);

    cout << "\nNearest servers to Server " << startServer << ":\n";
    for (int i = 0; i < MAX; i++) {
        cout << "Server " << nearestServers[i] << endl;
    }

    return 0;
}
