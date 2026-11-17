#include <iostream>
#include <vector>
using namespace std;

class Node {
public:
    int serviceID;
    int cost;
    Node* left;
    Node* right;

    Node(int id, int c) {
        serviceID = id;
        cost = c;
        left = NULL;
        right = NULL;
    }
};
//Insert node into BST according to monthly cost
Node* insert(Node* root, int id, int cost) {

    if (root == NULL)
        return new Node(id, cost);

    if (cost < root->cost)
        root->left = insert(root->left, id, cost);
    else
        root->right = insert(root->right, id, cost);

    return root;
}
//Part A: Find all downward paths
void findDownwardPaths(Node* root, int target,
                       vector<Node*>& path) {

    if (root == NULL) return;

    //Add current node to path
    path.push_back(root);

    //Check all paths ending at current node
    int sum = 0;

    for (int i = path.size() - 1; i >= 0; i--) {
        sum += path[i]->cost;

        if (sum == target) {
            cout << "Path: ";

            for (int j = i; j < path.size(); j++)
                cout << path[j]->serviceID << " ";

            cout << endl;
        }
    }
    //Explore left and right subtrees
    findDownwardPaths(root->left, target, path);
    findDownwardPaths(root->right, target, path);

    //Backtrack: Remove current node
    path.pop_back();
}
//In-order traversal to get sorted BST nodes
void getSortedNodes(Node* root, vector<Node*>& nodes) {

    if (root == NULL) return;

    getSortedNodes(root->left, nodes);
    nodes.push_back(root);
    getSortedNodes(root->right, nodes);
}
//Print a valid subset
void printSubset(vector<Node*>& subset) {

    cout << "Subset: ";

    for (int i = 0; i < subset.size(); i++)
        cout << subset[i]->serviceID << " ";

    cout << endl;
}
//Part B: Find all subsets with target cost
void findTargetSubsets(vector<Node*>& nodes, int index,
                       int currentSum, int target,
                       vector<Node*>& subset) {

    //Target sum reached
    if (currentSum == target) {
        printSubset(subset);
        return;
    }
    if (index == nodes.size()) return;

    //Pruning using BST sorted order
    if (currentSum + nodes[index]->cost > target)
        return;
    //Include current node
    subset.push_back(nodes[index]);

    findTargetSubsets(nodes, index + 1,
                      currentSum + nodes[index]->cost,
                      target, subset);

    //Backtrack: Remove current node
    subset.pop_back();
    //Exclude current node
    findTargetSubsets(nodes, index + 1,
                      currentSum, target, subset);
}
int main() {
    Node* root = NULL;

    int n;
    cout << "Enter number of microservices: ";
    cin >> n;
    //Create BST
    for (int i = 0; i < n; i++) {

        int id, cost;

        cout << "Enter service ID and monthly cost: ";
        cin >> id >> cost;

        root = insert(root, id, cost);
    }
    int target;
    cout << "Enter target budget: ";
    cin >> target;

    //Part A
    cout << "\nPart A: Downward Paths\n";
    vector<Node*> path;
    findDownwardPaths(root, target, path);

    //Part B
    cout << "\nPart B: Target Subsets\n";

    vector<Node*> nodes;
    vector<Node*> subset;

    getSortedNodes(root, nodes);
    findTargetSubsets(nodes, 0, 0, target, subset);

    return 0;
}
