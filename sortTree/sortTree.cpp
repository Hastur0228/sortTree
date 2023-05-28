#include <iostream>
#include "sortTree.h"
using namespace std;
template<class KEY, class OTHER>
void display(SET<KEY, OTHER>* p) {
    if (p != NULL) cout << "(" << p->key << ", " << p->other << ")" << endl;
    else cout << "Not found." << endl;
}
int main() {
    SET<int, char*> a[] = { {10,(char*)"aaa"}, {8,(char*)"bbb"}, {21,(char*)"ccc"}, {87,(char*)"ddd"},
                           {56,(char*)"eee"}, {4,(char*)"fff"}, {11,(char*)"ggg"}, {3,(char*)"hhh"},
                           {22,(char*)"iii"}, {7,(char*)"jjj"} };
    sortTree<int, char*> sortTree;
    for (int i = 0; i < 10; ++i) {
        sortTree.insert(a[i]);
    }
    for (int i = 0; i < 10; ++i) {
        cout << "find: " << a[i].key << " = ";
        display(sortTree.find(a[i].key));
    }
    sortTree.midOrder();
    return 0;
}