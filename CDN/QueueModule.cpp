#include<iostream>
#include<string>

using namespace std;

#define MAX 5 // Number of servers
int front = 0, rear = -1, size = 5;
int contentQueue[10]; // Queue to store content requests (content IDs)

string cache[MAX]; // Local cache to store content at different indices

// Hash function to map content IDs to cache index
int h(int contentID) {
    return contentID % MAX;
}

// Function to simulate fetching content from servers or origin
void fetchContent(int contentID, int cacheIndex);

// Function to enqueue content request (user input)
void enqueue() {
    cout << "You are in Enqueue Operation" << endl;
    if (rear == size - 1) {
        cout << "Queue is Overflow!!!" << endl;
    } else {
        int contentID;
        cout << "Enter content ID to request: ";
        cin >> contentID;
        rear++;
        contentQueue[rear] = contentID;
    }
}

// Function to dequeue content request and process it
void dequeue() {
    cout << "You are in Dequeue operation!" << endl;
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
}

// Function to display the current state of the cache
void displayCache() {
    cout << "Cache Content:" << endl;
    for (int i = 0; i < MAX; i++) {
        if (cache[i] != "") {
            cout << "Index " << i << ": " << cache[i] << endl;
        } else {
            cout << "Index " << i << ": Empty" << endl;
        }
    }
}

int main() {
    int choice;
    
    // Initialize the cache to be empty
    for (int i = 0; i < MAX; i++) {
        cache[i] = "";
    }

    do {
        cout << "\nEnter Your Choice (1 - Enqueue, 2 - Dequeue, 3 - Display Cache, 4 - Exit): ";
        cin >> choice;

        switch (choice) {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            displayCache();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
