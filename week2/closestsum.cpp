//By Pedro Barbeira
#include <iostream>
#include <vector>
#include <algorithm>

void calcSum(std::vector<int> v, std::vector<int>& sums){
    for(int i = 0; i < v.size()-1; i++){
        for (int j = i+1; j < v.size(); j++){
            sums.push_back(v[i] + v[j]);
        }
    }
}

void findPair(std::vector<int> sums, int target, std::vector<std::string>&res){
    if(target < sums[0]) {
        res.push_back(std::to_string(sums[0]));
        return;
    }
    else if (target>sums[sums.size() -1]){
        res.push_back(std::to_string(sums[sums.size()-1]));
        return;
    }

    int i = 0;
    int j = sums.size()-1;
    int mid, val;

    while(i < j){
        mid = (i+j)/2;
        val = sums[mid];
        if(target > val)
            i = mid + 1;
        else if(target < val)
            j = mid - 1;
        else {
            res.push_back(std::to_string(val));
            return;
        }
    }

    int iDiff = abs(target-sums[i]);
    int upDiff = abs(target-sums[i+1]);
    int lowDiff = abs(target-sums[i-1]);
    std::string load;

    if(iDiff == upDiff && sums[i] != sums[i+1]) {
        load = std::to_string(sums[i]) + " " + std::to_string(sums[i+1]);
        res.push_back(load);
    }
    else if (iDiff == lowDiff && sums[i] != sums[i-1]) {
        load = std::to_string(sums[i-1]) +  " " + std::to_string(sums[i]);
        res.push_back(load);
    }
    else if(iDiff > upDiff) res.push_back(std::to_string(sums[i+1]));
    else if(iDiff > lowDiff) res.push_back(std::to_string(sums[i-1]));
    else res.push_back(std::to_string(sums[i]));

}

int closestSum(){
    std::vector<int> sums;
    std::vector<int> v;
    std::vector<std::string> res;
    int n, q;

    std::cin >> n;
    while(n != 0){
        std::cin >> q;
        v.push_back(q);
        n--;
    }
    calcSum(v, sums);
    sort(sums.begin(), sums.end());

    std::cin >> q;
    while(q != 0){
        std::cin >> n;
        findPair(sums, n, res);
        q--;
    }

    for(auto it: res)
        std::cout << it << std::endl;

    return 0;

}