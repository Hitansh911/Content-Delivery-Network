#include <iostream>
#include <string>
using namespace std;

#define MAX 5  // Define smaller table size

// Hash function: returns the index for a content ID using modulo
int h(int key) {
    return key % MAX;  // Using smaller MAX size for simplicity
}

// Function to display the table (simulating the cache lookup)
void Display_Table(string Table[]) {
    cout << "Index\tContent\n";
    for (int i = 0; i < MAX; i++) {
        if (Table[i] != "")
            cout << i << "\t" << Table[i] << endl;
        else
            cout << i << "\t" << "Empty" << endl;
    }
}

// Simulate fetching content from the origin server (if not cached)
void fetch_from_origin(int contentID) {
    cout << "Content not found in cache. Fetching from origin server for content ID: " << contentID << endl;
    cout << "Content for content ID " << contentID << " has been fetched from the origin server." << endl;
}

int main() {
    string Table[MAX];  // This will simulate the cache (hash table)
    int contentID;
    string contentName;

    // Initialize the table with empty strings (indicating empty slots)
    for (int i = 0; i < MAX; i++) {
        Table[i] = "";
    }

    // Pre-populate the cache with some sample content (simulating cached content)
    Table[h(1)] = "Video1";
    Table[h(2)] = "Image1";

    Display_Table(Table);  // Display the initial cache state

    // Simulating content requests from users
    while (true) {
        cout << "\nEnter content ID to request (or -1 to stop): ";
        cin >> contentID;

        if (contentID == -1) {
            break;  // Exit loop if user enters -1
        }

        int index = h(contentID);  // Calculate index using the hash function

        // Check if the content is in the cache
        if (Table[index] != "") {
            cout << "Content found in cache: " << Table[index] << endl;  // Serve content from cache
        } else {
            cout << "Content not found in cache." << endl;
            fetch_from_origin(contentID);  // Fetch content from the origin server

            // Immediately exit the program if the content is not found in the cache
            cout << "Exiting due to content not found in cache." << endl;
            break;
        }

        Display_Table(Table);  // Display the cache state after the request
    }

    return 0;
}


/* 2 and 3 module
#include <iostream>
#include <climits>
#include <string>
using namespace std;

#define MAX 5  // Number of servers

int h(int key) {
    return key % MAX;  // Simple hash function for content ID
}

// Display the local cache table
void Display_Table(string Table[]) {
    cout << "Index\tContent\n";
    for (int i = 0; i < MAX; i++) {
        if (Table[i] != "")
            cout << i << "\t" << Table[i] << endl;
        else
            cout << i << "\t" << "Empty" << endl;
    }
}

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

// Graph class to represent the server network
class Graph {
private:
    int nov;          // Number of vertices (servers)
    int g[MAX][MAX];  // Latency matrix

public:
    Graph(int vertices);             // Constructor
    void displayGraph();             // Display the graph
    void findNearestServers(int, int[]);  // Find nearest servers for a given server
};

// Constructor to initialize graph
Graph::Graph(int vertices) {
    nov = vertices;

    // Initialize graph with predefined latencies
    for (int i = 0; i < nov; i++) {
        for (int j = 0; j < nov; j++) {
            if (i == j)
                g[i][j] = 0;
            else
                g[i][j] = INT_MAX;  // No direct connection initially
        }
    }

    // Predefined graph connections
    g[0][1] = 10; g[1][0] = 10;
    g[0][2] = 20; g[2][0] = 20;
    g[1][2] = 5;  g[2][1] = 5;
    g[2][3] = 15; g[3][2] = 15;
    g[3][4] = 30; g[4][3] = 30;
}

// Display the graph
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

// Find nearest servers to the start server
void Graph::findNearestServers(int startServer, int nearestServers[]) {
    int dist[MAX];       // Store shortest distances
    bool visited[MAX];   // Track visited servers

    // Initialize distances and visited status
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

        visited[u] = true;  // Mark the chosen server as visited

        // Update distances for adjacent servers
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

    // Local cache for Server 1
    string Table[MAX];
    for (int i = 0; i < MAX; i++) Table[i] = "";

    // Prepopulate Server 1's cache
    Table[h(1)] = "Video1";
    Table[h(2)] = "Image1";

    // Simulated content availability on other servers
    string serverContent[MAX][MAX] = {
        {"", "", "", "", ""},
        {"Video1", "Image1", "", "", ""},
        {"", "", "Content3", "Content4", ""},
        {"", "", "", "", ""},
        {"", "", "", "", ""}
    };

    Display_Table(Table);

    while (true) {
        int contentID;
        cout << "\nEnter content ID to request (or -1 to stop): ";
        cin >> contentID;

        if (contentID == -1) break;

        int index = h(contentID);
        if (Table[index] != "") {
            cout << "Content found in cache: " << Table[index] << endl;
        } else {
            cout << "Content not found in cache." << endl;
            int startServer = 1;
            int nearestServers[MAX];
            g.findNearestServers(startServer, nearestServers);

            bool fetched = false;
            for (int i = 0; i < MAX && !fetched; i++) {
                int serverID = nearestServers[i];
                if (serverID != startServer && serverContent[serverID][contentID] != "") {
                    fetch_from_server(serverID, contentID);
                    Table[index] = serverContent[serverID][contentID];
                    fetched = true;
                }
            }

            if (!fetched) {
                // Fetch from the Origin Server if no servers have the content
                fetch_from_server(-1, contentID);
                Table[index] = "Content from Origin Server";
            }

            Display_Table(Table);
        }
    }

    return 0;
}
*/