#include <iostream>
#include <climits>
#include <string>

using namespace std;

#define MAX 5 
int front = 0, rear = -1, size = 5;
int contentQueue[10]; 

string cache[MAX]; // Local cache to store content at different indices

// Latency matrix to store the latency between servers
int g[MAX][MAX] = {
    {0, 10, 20, INT_MAX, INT_MAX},  
    {10, 0, 5, 15, INT_MAX},        
    {20, 5, 0, 15, 30},             
    {INT_MAX, 15, 15, 0, 30},       
    {INT_MAX, INT_MAX, 30, 30, 0}   
};

int h(int contentID) {
    return contentID % MAX;
}

// Function to simulate fetching content from servers or origin
void fetchContent(int contentID, int cacheIndex);

// Enqueue and Dequeue operations
void enqueueAndDequeue() {
    cout << "You are in Enqueue & Dequeue Operation" << endl;
    
    int contentID;
    cout << "Enter content ID to request: ";
    cin >> contentID;

    // Enqueue operation (automatically add content ID to the queue)
    if (rear == size - 1) {
        cout << "Queue is Overflow!!!" << endl;
    } else {
        rear++;
        contentQueue[rear] = contentID;
        cout << "Content ID " << contentID << " enqueued." << endl;
    }

    // Dequeue operation (automatically after enqueue)
    if (front > rear) {
        cout << "Queue is Empty" << endl;
    } else {
        int dequeuedContentID = contentQueue[front];
        front++;
        cout << "Processing Content ID: " << dequeuedContentID << endl;

        // Check cache using hash function
        int index = h(dequeuedContentID);
        if (cache[index] != "") {
            cout << "Content found in cache: " << cache[index] << endl;
        } else {
            cout << "Content not found in cache. Checking server network..." << endl;
            // If not found in cache, check the server network (simulated)
            fetchContent(dequeuedContentID, index);
        }
    }
}

// Function to simulate fetching content from servers or origin
void fetchContent(int contentID, int cacheIndex) {
    // Here, let's simulate the fetching process.
    cout << "Fetching content from the nearest server or origin for content ID: " << contentID << endl;
    
    // Cache the content after fetching from a server or origin
    cache[cacheIndex] = "Content_" + to_string(contentID); // Simulate storing content in cache
    cout << "Content fetched and cached: " << cache[cacheIndex] << endl;

    // Display the latency to fetch content from the nearest server
    cout << "Latency between the requesting server and the nearest server for content ID " << contentID << ": ";
    cout << g[0][1] << " ms" << endl;  // Example of displaying the latency between server 0 and server 1
}

// Display the cache table (local cache)
void Display_Table(string Table[]) {
    cout << "Index\tContent\n";
    for (int i = 0; i < MAX; i++) {
        if (Table[i] != "")
            cout << i << "\t" << Table[i] << endl;
        else
            cout << i << "\t" << "Empty" << endl;
    }
}

int main() {
    // Initialize cache with predefined values (Video1 at index 1, Image1 at index 2)
    for (int i = 0; i < MAX; i++) {
        cache[i] = "";
    }
    cache[1] = "Content of Website";
    
    // Add a real blog link to cache[2]
    cache[2] = "Blog Post: The Life of a Cat\nFor an in-depth look at the fascinating world of cats, check out this blog: https://www.cats.org.uk/blog";

    // Continuous loop to take user input and process it
    while (true) {
        enqueueAndDequeue();  // Automatically enqueue and process content ID

        // Option to display the current cache state after each operation
        char displayCacheChoice;
        cout << "Would you like to display the cache content? (y/n): ";
        cin >> displayCacheChoice;

        if (displayCacheChoice == 'y' || displayCacheChoice == 'Y') {
            Display_Table(cache);
        }

        // Option to exit the loop
        char exitChoice;
        cout << "Do you want to continue? (y/n): ";
        cin >> exitChoice;
        if (exitChoice == 'n' || exitChoice == 'N') {
            break;
        }
    }

    return 0;
}
