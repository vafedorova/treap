#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <sstream>

using namespace std;

// Добавить элемент x после i-го элемента списка. Если i = 0, то элемент добавляется в начало массива.
void add_elem(vector<int> &a, int i, int x) { 
    a.push_back(0);
    for (int j = a.size() - 1; j > i; j--) {
        a[j] = a[j - 1];
    }
    a[i] = x;
}


int main() {
    int n;
    cin >> n;
    vector<int> a;
    ostringstream os;
    a.reserve(n);
    for (int k = 0; k < n; k++) {
        char c;
        int i, j, x;
        cin >> c >> i >> j;
        if (c == '?') {
            assert(i >= 1 and i <= a.size());
            assert(j >= 1 and j <= a.size());
            os << min(a[i - 1], a[j - 1]) << "\n";
        }
        else if (c == '+') {
            x = j;
            add_elem(a, i, x); // добавить элемент x после i-го элемента списка
           //for (int i = 0; i < a.size(); ++i) {
           //    cout << a[i] << " ";
           //}
           //cout << endl;
        }
        else {
            assert(false);
        }
    }
    cout << os.str();
}