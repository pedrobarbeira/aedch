#include <iostream>
#include <vector>

using namespace std;

int narranj1() {
    int cases, n, m, k, sum;
    vector<vector<int>> v;

    cin >> cases;

    for(int i = 0; i < cases; i++) {
        cin >> n >> k;
        vector<int> arr;
        arr.push_back(n);
        arr.push_back(k);
        v.push_back(arr);
    }
    for(vector<vector<int>>::iterator it= v.begin(); it != v.end(); it++){
        do{
            sum = 0;
            (*it)[0]++;
            m = (*it)[0];
            while(m != 0) {
                sum += m % 10;
                m /= 10;
            }
        }while(sum != (*it)[1]);
        cout << (*it)[0] << endl;
    }
    return 0;
}

