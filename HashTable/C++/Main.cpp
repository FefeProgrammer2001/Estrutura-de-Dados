#include "HashTable.hpp"
#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Digite a capacidade da tabela hash: ";
    cin >> n;

    HashTable<double> hash(n);

    cout << "Insira os valores:" << endl;
    for(int i = 0; i < n; i++) {
        double valor;
        cout << "Valor " << (i+1) << ": ";
        cin >> valor;
        hash.insert(valor);
    }

    hash.printTable();
    hash.printCollisionQueue();
    return 0;
}
