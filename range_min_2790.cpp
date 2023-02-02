#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;

// Добавить элемент x после i-го элемента списка. Если i = 0, то элемент добавляется в начало массива.
void add_elem(vector<int> &a, int i, int x) { 
    vector<int> copy_of_a = a;
    copy_of_a.push_back(0);
    copy_of_a[i] = x;
    for (int j = i; j < a.size(); j++) {
        copy_of_a[j + 1] = a[j];
    }
    a = copy_of_a;
}


int main() {
    int n;
    cin >> n;
    vector<int> a;
    vector<int> b;
    a.reserve(n);
    for (int k = 0; k < n; k++) {
        char c;
        int i, j, x;
        cin >> c >> i >> j;
        if (c == '?') {
            b.push_back(min(a[i - 1], a[j - 1]));
        }
        else if (c == '+') {
            x = j;
            add_elem(a, i, x); // добавить элемент x после i-го элемента списка
        }
        else {
            assert(false);
        }
    }
    if (b.size() != 0) {
        for (int i = 0; i < b.size(); i++) {
            cout << b[i] << endl;
        }
    }
}