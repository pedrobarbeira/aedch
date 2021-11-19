#include <iostream>
#include <vector>

int findDays(std::vector<int> v, int max){
    int days = 1, sum = 0;
    for(int i = 0; i < v.size(); i++){
        sum += v[i];
        if(sum > max){
            days++;
            sum = v[i];
        }
    }
    return days;
}

int maxDistance(std::vector<int> v, int d){
    int lo = 0, high = 0, mid, answer;
    for(int i = 0; i < v.size(); i++){
        lo = std::max(lo, v[i]);
        high += v[i];
    }

    while(lo < high) {
        mid = (lo + high) / 2;
        int days = findDays(v, mid);

        if(days <= d) high = mid;
        else lo = mid+1;
    }
    return high;
}

int main(){
    int n, d, p, k;
    std::vector<int> distances;
    std::vector<int> days;

    std::cin >> n;
    while(n > 0){
        std::cin >> d;
        distances.push_back(d);
        n--;
    }

    std::cin >> p;
    while(p > 0){
        std::cin >> k;
        days.push_back(k);
        p--;
    }

    for(auto day: days)
        std::cout << maxDistance(distances, day) << '\n';

    return 0;
}