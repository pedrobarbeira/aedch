#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

static int Z_VAL = 22;  //fix for portuguese alphabet
static int X_VAL = 21;  //fix for portuguese alphabet
static int L_VAL = 10;
static int BIG_LETTER = 23; //increment of 1 big letter i.e: BA-00-00 = #23000
static int GEN_VAL = 23*BIG_LETTER*pow(10, 4);   //number of plates per generation (23 big letters)

void generation(std::string m, char& c){
    if(isalpha(m[0])){
        if(isalpha(m[6]))
            c = '4';
        else c = '1';
    }
    else if (isalpha(m[3]))
        c = '3';
    else c = '2';
}

template<typename T>
void swap(T& a, T& b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}

void swapM(std::string& m1, std::string& m2, char& c1, char& c2){
    swap(m1, m2);
    swap(c1, c2);
}

void order(std::string& m1, std::string& m2, char&c1, char& c2){
    if (c2 > c1){
        swapM(m1,m2,c1,c2);
        return;
    }
    else if(c1 == c2) {
        switch (c1) {
            case '1':
                if (m1.substr(0, 2) < m2.substr(0, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(3, 2) < m2.substr(3, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(6, 2) < m2.substr(6, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else return;
            case '2':
                if (m1.substr(6, 2) < m2.substr(6, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(0, 2) < m2.substr(0, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(3, 2) < m2.substr(3, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else return;
            case '3':
                if (m1.substr(3, 2) < m2.substr(3, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(0, 2) < m2.substr(0, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(6, 2) < m2.substr(6, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else return;
            case '4':
                if (m1.substr(0, 2) < m2.substr(0, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(6, 2) < m2.substr(6, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else if (m1.substr(3, 2) < m2.substr(3, 2)) {
                    swapM(m1, m2, c1, c2);
                    return;
                } else return;
        }
    }
    else return;
}

void reorder(std::string& m, const char c){
    std::string temp1, temp2;
    switch(c){
        case '1':return;
        case '2':
            temp1 = m.substr(6, 2);
            temp2 = m.substr(0, 5);
            m = temp1 + "-" + temp2;
            return;
        case '3':
            temp1 = m.substr(3, 2);
            temp2 = temp1+ "-" + m.substr(0, 2) + "-" + m.substr(6,2);
            m = temp2;
            return;
        case '4':
            return;
    }
}

void parse(std::string& m1, std::string& m2, char& c1, char& c2){
    generation(m1, c1);
    generation(m2, c2);

    reorder(m1,c1);
    reorder(m2, c2);

    order(m1,m2,c1,c2);

}

void letterCalc(char c, int i, long long int& value){
    int p;
    if(i == 0 || i == 6){
        //Attributes power value
        if(i == 0) p = 4;
        else p = 2;
        //Calculates value of each first letter
        if(c == 'Z') value += Z_VAL * BIG_LETTER * pow(10, p);
        else if(c == 'X') value += X_VAL * BIG_LETTER * pow(10, p);
        else if(c > 'J' && c < 'X') value += (c - 'A') * BIG_LETTER* pow(10, p);
        else value += (c - 'A') * BIG_LETTER* pow(10, p);
        return;
    }
    else {
        //Attributes power value;
        if (i == 1) p = 4;
        else if (i == 7) p = 2;
        //Calculates value for each second letter
        if(c == 'Z') value += Z_VAL * pow(10, p);
        else if(c == 'X') value += X_VAL * pow(10, p);
        else if(c > 'J' && c < 'X') value += (c - 'A' -1) * pow(10, p);
        else value += (c - 'A') * pow(10, p);
        return;
    }
    return;
}

long long int calcVal(const std::string m, const char c){
    long long int value = (int(c) -1) * GEN_VAL;
    if(c == '4'){
        letterCalc(m[0], 0, value);
        letterCalc(m[1], 0, value);
        letterCalc(m[6], 6, value);
        letterCalc(m[7], 7, value);
        value += (m[3] - '0') * 10 + (m[4] - '0');
    }
    else{
        //Process first value with special cases
        letterCalc(m[0], 0, value);
        //Process second value with special cases
        letterCalc(m[1], 1, value);
        //Process remaining values
        value += (m[3] -'0') * pow(10, 3) + (m[4]-'0') * pow(10, 2) +
                (m[6]-'0') * 10 + (m[7]-'0');
    }
    return value;
}

void driverTest(){
    std::string m1 = "AA-00-AA";
    std::string m2 = "00-AA-00";
    char c1, c2;

    parse(m1,m2,c1,c2); //turning g3 m1 into XXNNNN -> add '-';

    long long int i1 = calcVal(m1, c1); //returning weird value;
    long long int i2= calcVal(m2, c2);

    std::cout << i1-i2 << std::endl;
}

int main() {
    int n;
    long long int i1, i2;
    std::string m1, m2; //matriculas
    char g1, g2; //geraçoes

    std::vector<std::vector<std::string>> matriculas;
    std::vector<std::string>load;

    std::cin >> n;

    for(int i = 0; i < n; i++){
        std::cin >> m1 >> m2;
        load.push_back(m1);
        load.push_back(m2);
        matriculas.push_back(load);
        load.clear();
    }

    for(auto it = matriculas.begin();
            it != matriculas.end(); it++){
        m1 = (*it)[0];
        m2 = (*it)[1];
        parse(m1,m2, g1, g2);
        i1=calcVal(m1, g1);
        i2=calcVal(m2, g2);
        std::cout << i1 - i2 << std:: endl;
    }

    return 0;
}
