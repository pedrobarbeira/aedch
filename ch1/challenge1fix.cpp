#include <iostream>

using namespace std;

int meaningOfLife(){
    int input, count = 0, length;
    cin >> length;
    for(int i = 0; i < length; i++){
        std::cin >> input;
        if(input == 42)
            count++;}
    cout << count;
    return 0;
}