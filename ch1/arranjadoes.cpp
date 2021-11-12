#include <iostream>
#include <vector>

short MAX_DIGIT = 9;

/**
 * Prints the elements of a value vector
 * @param v the value vector
 * @param o the target ostream
 */
void printVal(std::vector<short>& v, std::ostream& o){                                                                  //Used ostream to easily be able
    short max = v.size();                                                                                               //to print into a file and check
    for(int i = 0; i < max; i++)                                                                                        //answers
        o << v[i];
    o << std::endl;
}

/**
 * Calculates the sum of the digits of a string
 * @param s the string
 * @param res the sum of the digits
 */
short vSum(const std::vector<short>& v){
    short res = 0;
    for(int i = 0; i < v.size(); i++)
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
        if(v[i] == 9){                                                                                                  //Case where the digit is exhausted
            if(i == 0) extend(v);
            else v[i] = 0;
        }
        else {
            v[i]++;                                                                                                     //Base case
            return;
        }
    }
}



/**
 * Case where the original sum is over target
 * @param v the value vector
 * @param target the target
 * @param sum the sum
 */
void overTarget(std::vector<short>&v, short target, short sum){
    short diff, i = short(v.size()-1);                                                                                  //In this case we're sure that the number will
    sum = vSum(v);
    diff = short(target-sum);
    while(diff!=0){
        if(diff >= MAX_DIGIT){                                                                                          //If diff >= 9, iteratively sets v[i] to 9 and
            v[i] = MAX_DIGIT;                                                                                           //subtracts 9 from diff.
            diff -= MAX_DIGIT;
            i--;
        }
        else {
            v[i] = diff;                                                                                                //Else just sets v[i] = diff
            return;
        }
    }
}

/**
 * Case where the original sum is under  target
 * @param v the value vector
 * @param target the target
 * @param sum the difference between sum and target
 */
void underTarget(std::vector<short>&v, short target, short diff){
    int i = v.size() -1;
    short lastDiff;
    while(diff != 0){
        lastDiff = MAX_DIGIT - v[i];                                                                                    //See's how many increments can fit in v[i]
        if(lastDiff == 0) i--;                                                                                          //v[i] is exhausted, proced to next iteration
        else {
            if (diff <= lastDiff) {                                                                                     //We can add diff to v[i]
                v[i] += diff;
                return;
            } else {
                diff -= lastDiff;                                                                                       //Sets v[i] to 9 and updates diff accordingly
                v[i] = 9;
            }
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
    if (v[0] >= target) extend(v);                                                                                  //If the first digit > target, extends vector
    else {
        partialSum += v[0];                                                                                             //Calculates partial sum untill partialSum > target
        for (int i = 1; i < v.size(); i++) {
            if(!zero) {
                partialSum += v[i];
                if (partialSum >= target) {                                                                             //Increments the "preceding digit" and adjusts iterator
                    increment(v, short(i - 1));                                                               //i.e 1[7]2 -> 2[7]2
                    i--;
                    zero = true;                                                                                        //Triggers flag to set remaining digits to zero
                }                                                                                                       //i.e 2[7]2 -> 200[]
            }
            else v[i] = 0;
        }
    }
}

/**
 * Acts as interface between main and worhorse functions. Adjusts the vector
 * size and ensures everything is set and ready to go
 * @param v the value
 * @param target the target value
 */
void getVal(std::vector<short>& v, short target){
    short slots;
    if (target > MAX_DIGIT * v.size()) {                                                                                //Ensures the number has enough digits to reach target
        slots = (short)(target / 9);
        extend(v, short(slots - v.size()));
    }

    short sum = vSum(v);
    if(sum >= target) {                                                                                                 //If sum > target, adjusts value to the form X..X0..0
        fixNum(v, target);                                                                                          //with sum < target
        overTarget(v, target, sum);
    }
    else underTarget(v, target, short(target-sum));                                                             //Else calls underTarget

}

/**
 * Reads input, extracting each digit as a character and storing it in
 * a short int vector. Checks if input is valid
 * @param value the vector
 * @return 0 upon success
 */
int readInput(std::vector<short>& value){
    char c;
    while(true){
        c = getchar();                                                                                                  //Extracts a char from stdin. If it's a digit
        if (!isdigit(c)){                                                                                               //stores it in vector. If it's a whitespace
            if(c != '\n'){                                                                                              //returns. If neither, exists with error code 1
                if (isblank(c)) break;
                else return 1;
            }
        }
        else value.push_back(c - '0');
    }
    return 0;
}

/**
 * Receives a list of numbers (n) and their respective targets. Calculates the
 * closest number above n which the sum of all it's digits equals target
 * @return 0 upon success
 */
int main() {
    short n, target;
    std::vector<std::vector<short>> res;
    std::vector<short> value;

    std::cin >> n;

    while (n > 0) {

        if(readInput(value) != 0) std::cout << "Invalid Input!\n";                                                   //Reads input and checks for errors

        std::cin >> target;

        if(target > 100) std::cout << "Invalid Input!\n";                                                               //Ensures target is within problem constraints
        else {
            getVal(value, target);                                                                              //Calculates value and stores it in answer vector
            res.push_back(value);
            value.clear();
        }
        n--;
    }
    for(int i = 0; i < res.size(); i++)                                                                                 //Prints out answer vector to stdout
        printVal(res[i], std::cout);

    return 0;
}