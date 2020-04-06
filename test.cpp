#include <iostream>

int main(){
    using namespace std;
    int target = 1231234;
    int len = 0;
    while(target) {
        target = int(target/10);
        len++;
    }
    cout << len << endl;
}