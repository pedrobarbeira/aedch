#include <iostream>
#include <vector>

short MAX_DIGIT = 9;

/**
 * Prints the elements of a value vector
 * @param v the value vector
 * @param o the target ostream
 */
void printVal(std::vector<short>& v, std::ostream& o){
    short max = v.size();
    for(int i = 0; i < max; i++)
        o << v[i];
    o << std::endl;
}

/**
 * Calculates the sum of the digits of a string
 * @param s the string
 * @param res the sum of the digits
 */
short vSum(const std::vector<short>& v){
    short res = 0, max = v.size();
    for(int i = 0; i < max; i++)
        res += v[i];
    return res;
}

/**
 * Gives the value vector n+1 extra slots
 * @param v the value vector
 * @param slots the extra slots
 */
void extend(std::vector<short>&v, short n = 0){
    std::vector<short> newV;
    newV.push_back(1);
    for(int i = 0; i < v.size() + n; i++)
        newV.push_back(0);
    v = newV;
}

/**
 * Increments 1 to the vector of digits
 * @param v the vector
 */
void increment(std::vector<short>&v, short index){
    for(int i = index; i >= 0; i--){
        if(v[i] == 9){
            if(i == 0) extend(v);
            else v[i] = 0;
        }
        else {
            v[i]++;
            return;
        }
    }
}

/**
 * Fixes the value, making sure it's ready to go through the findNum() function
 * @param v the value vector
 * @param target the target
 */
void fixNum(std::vector<short>& v, short target) {
    short partialSum = 0;
    bool zero = false;
    if (v[0] >= target) extend(v);
    else {
        partialSum += v[0];
        for (int i = 1; i < v.size(); i++) {
            if(!zero) {
                partialSum += v[i];
                if (partialSum >= target) {
                    increment(v, short(i - 1));
                    i--;
                    zero = true;
                }
            }
            else v[i] = 0;
        }
    }
}

/**
 * Case when the original sum is over target
 * @param v the value vector
 * @param target the target
 * @param sum the sum
 */
void overTarget(std::vector<short>&v, short target, short sum){
    short diff, i = short(v.size()-1);
    sum = vSum(v);
    diff = short(target-sum);
    while(diff!=0){

        if(diff >= MAX_DIGIT){
            v[i] = MAX_DIGIT;
            diff -= MAX_DIGIT;
            i--;
        }
        else {
            v[i] = diff;
            return;
        }
    }
}

/**
 * Case for where the original sum is under  target
 * @param v the value vector
 * @param target the target
 * @param sum the difference between sum and target
 */
void underTarget(std::vector<short>&v, short target, short diff){
    int last = v.size() -1;
    short lastDiff;
    while(diff != 0){
        lastDiff = MAX_DIGIT - v[last];
        if(v[last] == 9) last--;
        else {
            if (diff <= lastDiff) {
                v[last] += diff;
                last--;
                return;
            } else {
                diff -= lastDiff;
                v[last] = 9;
            }
        }
    }
}

/**
 * Adjusts the vector size and ensures everything is set and ready to go
 * @param v the value
 * @param target the target value
 */
void getVal(std::vector<short>& v, short target){
    short slots;
    if (target > MAX_DIGIT * v.size()) {                                                                                      //Ensures the number has enough digits to reach target
        slots = (short)(target / 9);
        extend(v, short(slots - v.size()));
    }

    short sum = vSum(v);
    if(sum >= target) {
        fixNum(v, target);
        overTarget(v, target, sum);
    }
    else underTarget(v, target, short(target-sum));

}

/**
 * Reads input, storing the first value in a string, digit by digit, and the second
 * in a int variable n. Checks for valid input
 * @param s the string
 * @param n the int variable
 * @return 0 upon success
 */
int stov(std::vector<short>& values, std::string s){
    bool test=true;
    for(int i = 0; i < s.length(); i++){
        if(isdigit(s[i])) values.push_back((s[i]-'0'));
        else{
            if(s[i] != ' ') test = false;
            break;
        }
    }
    if (!test) return 1;

    return 0;
}


/**
 * Receives a list of numbers (n) and their respective targets. Calculates the
 * closest number above n which the sum of all it's digits equals target
 * @return 0 upon success
 */
int arranjadoes() {
    short n, target;
    std::vector<std::vector<short>> res;
    std::vector<short> value;
    std::string s;

    std::cin >> n;

    while (n > 0) {

        std::cin >> s >> target;

        if(stov(value, s)!= 0) std::cout << "Invalid Input!\n";
        else {
            getVal(value, target);
            res.push_back(value);
            value.clear();
        }
        n--;
    }
    for(int i = 0; i < res.size(); i++)
        printVal(res[i], std::cout);

    return 0;
}