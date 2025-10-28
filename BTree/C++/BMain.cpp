#include "BTree.hpp"
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter the N value: ";
    cin >> n;
    BTree tree(n);

    int num_elements;
    cout << "Enter the number of elements: ";
    cin >> num_elements;
    cout << "Enter the BTree values:\n";
    for(int i = 0; i < num_elements; i++) {
        int value;
        cout << "Node " << (i + 1) << ": ";
        cin >> value;
        tree.insert(value);
    }
    cout << endl;

    tree.print();
    return 0;
}
