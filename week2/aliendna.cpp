//By Pedro Barbeira
/*
 * TimeComplexity   O(NlogN)
 * SpaceComplexity  O(n)
 */
#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
//JSHYNSHQSHDGNSHNSJAHSSA

struct Base{
public:
    uint8_t letter;
    uint16_t freq;
};

bool operator<(Base b1, Base b2){
    return b2.freq < b1.freq;
}

Base newBase(uint8_t c){
    Base b;
    b.letter = c;
    b.freq = 1;
    return b;
}

int aliendna(){
    std::vector<Base> res;
    uint8_t c = getchar();
    bool notFound = false;
    Base b = newBase(c);

    while(c != '\n') {
        if (res.empty()) res.push_back(b);
        else {
            for (int i = 0; i < res.size(); i++) {
                if (c == res[i].letter) {
                    res[i].freq++;
                    notFound = false;
                    break;
                } else notFound = true;
            }
        }
        if (notFound) res.push_back(newBase(c));
        c = getchar();
    }

    stable_sort(res.begin(), res.end());

    for(auto it:res) std::cout << it.letter << " " << it.freq << '\n';
}