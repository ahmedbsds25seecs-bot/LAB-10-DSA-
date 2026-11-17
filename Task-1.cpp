
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

//Node of the singly linked list
class Node {
public:
    int id;
    int weight;
    Node* next;

    Node(int i, int w) {
        id = i;
        weight = w;
        next = NULL;
    }
};
//Truck information
class Truck {
public:
    int capacity;

    Truck(int c) {
        capacity = c;
    }
};
//Calculate total weight of remaining containers
int getRemainingWeight(Node* current) {
    int total = 0;

    while (current != NULL) {
        total += current->weight;
        current = current->next;
    }

    return total;
}
//Calculate total capacity of remaining trucks
int getTotalCapacity(queue<Truck> trucks) {
    int total = 0;

    while (!trucks.empty()) {
        total += trucks.front().capacity;
        trucks.pop();
    }

    return total;
}
//Backtracking function
bool assignContainers(Node* current, queue<Truck> trucks,
                      vector<vector<int>>& loads) {

    //All containers have been assigned
    if (current == NULL) {
        return true;
    }
    //No trucks are left
    if (trucks.empty()) {
        return false;
    }
    //Pruning: Check if remaining containers can fit
    //in the total capacity of remaining trucks
    int remainingWeight = getRemainingWeight(current);
    int availableCapacity = getTotalCapacity(trucks);

    if (remainingWeight > availableCapacity) 
        return false;
    
    //Get the current truck
    Truck currentTruck = trucks.front();
    trucks.pop();

    int currentWeight = 0;
    vector<int> currentLoad;
    Node* temp = current;
    //Try assigning consecutive containers to this truck
    while (temp != NULL) {
        currentWeight += temp->weight;

        //Pruning: Truck cannot carry this container
        if (currentWeight > currentTruck.capacity) {
            break;
        }
        currentLoad.push_back(temp->id);
        //Store this truck's current load
        loads.push_back(currentLoad);
        //Try assigning the remaining containers
        if (assignContainers(temp->next, trucks, loads)) {
            return true;
        }
        //Backtrack: Remove the previous assignment
        loads.pop_back();

        temp = temp->next;
    }
    return false;
}
int main() {

    Node* head = NULL;
    Node* tail = NULL;

    int n;
    cout << "Enter number of containers: ";
    cin >> n;
    //Create the linked list
    for (int i = 0; i < n; i++) {

        int id, weight;

        cout << "Enter container ID and weight: ";
        cin >> id >> weight;
        Node* newNode = new Node(id, weight);

        if (head == NULL) {
            head = newNode;
            tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
    queue<Truck> trucks;
    int t;
    cout << "Enter number of trucks: ";
    cin >> t;
    //Insert trucks into the queue
    for (int i = 0; i < t; i++) {
        int capacity;

        cout << "Enter truck " << i + 1 << " capacity: ";
        cin >> capacity;

        trucks.push(Truck(capacity));
    }
    vector<vector<int>> loads;
    //Call the backtracking function
    if (assignContainers(head, trucks, loads)) {
        cout << "\nAll containers successfully assigned!\n";

        for (int i = 0; i < loads.size(); i++) {

            cout << "Truck " << i + 1 << ": ";

            for (int j = 0; j < loads[i].size(); j++) 
                cout << loads[i][j] << " ";
            
            cout << endl;
        }
    }
    else {
        cout << "\nInsufficient truck capacity." << endl;
    }
    return 0;
}
