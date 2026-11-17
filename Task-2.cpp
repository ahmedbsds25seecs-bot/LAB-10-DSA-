#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

const int LIMIT = 1000;
//Backtracking function
void findSequences(int current, int target, int budget,
                   vector<string>& operations, stack<string>& opStack) {

    //Target state reached
    if (current == target) {
        stack<string> temp = opStack;
        vector<string> result;

        while (!temp.empty()) {
            result.push_back(temp.top());
            temp.pop();
        }
        cout << "Sequence: ";
        for (int i = result.size() - 1; i >= 0; i--)
            cout << result[i] << " ";

        cout << endl;
        return;
    }
    //Maximum operation budget reached
    if (budget == 0) return;

    //Try each allowed operation
    for (int i = 0; i < operations.size(); i++) {

        int next = current;
        string op = operations[i];

        //Apply the selected operation
        if (op == "+3") next = current + 3;
        else if (op == "*2") next = current * 2;
        else if (op == "-5") next = current - 5;
        else if (op == "/2") {
            if (current % 2 != 0) continue;
            next = current / 2;
        }
        //Check system boundaries
        if (next < 0 || next > LIMIT) continue;
        //Push operation before recursion
        opStack.push(op);

        findSequences(next, target, budget - 1, operations, opStack);
        //Pop operation to undo the choice
        opStack.pop();
    }
}
int main() {

    int initial, target, budget;
    cout << "Enter initial state: ";
    cin >> initial;

    cout << "Enter target state: ";
    cin >> target;

    cout << "Enter maximum operation budget: ";
    cin >> budget;

    vector<string> operations = {"+3", "*2", "-5", "/2"};
    stack<string> opStack;
    cout << "\nValid operation sequences:\n";
    findSequences(initial, target, budget, operations, opStack);

    return 0;
}
