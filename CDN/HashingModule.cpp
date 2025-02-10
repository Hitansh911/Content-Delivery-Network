#include <iostream>
#include <string>
using namespace std;

#define MAX 5  // Define table size

// Hash function: returns the index for a content ID using modulo
int h(int key) {
    return key % MAX;
}

// Function to display the hash table (cache)
void Display_Table(string Table[]) {
    cout << "Index\tContent\n";
    for (int i = 0; i < MAX; i++) {
        if (Table[i] != "")
            cout << i << "\t" << Table[i] << endl;
        else
            cout << i << "\t" << "Empty" << endl;
    }
}

// Simulate fetching content from the origin server
void fetch_from_origin(int contentID) {
    cout << "Fetching content from the Origin Server for content ID: " << contentID << endl;
    cout << "Content for content ID " << contentID << " has been fetched from the Origin Server." << endl;
}

int main() {
    string Table[MAX];  // Simulating the cache using a hash table
    int contentID;

    // Initialize cache
    for (int i = 0; i < MAX; i++) {
        Table[i] = "";
    }

    // Pre-populate cache
    Table[h(1)] = "Video1";
    Table[h(2)] = "Image1";

    Display_Table(Table);

    // Simulate content requests
    while (true) {
        cout << "\nEnter content ID to request (or -1 to stop): ";
        cin >> contentID;

        if (contentID == -1) {
            break;  // Exit loop
        }

        int index = h(contentID);

        if (Table[index] != "") {
            cout << "Content found in cache: " << Table[index] << endl;
        } else {
            cout << "Content not found in cache." << endl;
            fetch_from_origin(contentID);
            cout << "Exiting due to content not found in cache." << endl;
            break;
        }

        Display_Table(Table);
    }

    return 0;
}
