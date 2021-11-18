//Created by Pedro Barbeira up201303693
/*  TimeComplexity O(n)
 *  SpaceCpomplexity O(n)
 *  Improved version of the Week1 Challenge 4 algorithm.
 *  Upon further reflection, I realized the implementation could be
 * greatly optimized by working with numbers instead of vectors.
 *  This submission has the goal of testing the solution against the
 * grading tool before implementing the method to bypass the machine's
 * number limitation.
 */
#include<iostream>
#include<vector>
#include<cmath>
#include<fstream>

/**
 * Counts a number's digits and calculates their sum
 * @param value the number
 * @param i number of digits
 * @return the sum
 * Time Complexity: O(n)
 * Space Complexity: O(n);
 */
uint16_t digitSum(uint64_t value, short& i){
    uint16_t sum;
    i = sum = 0;
    while(value != 0){
        sum += value % 10;
        value /= 10;
        i++;
    }
    return sum;
}

/**
 * Finds smaller number > value which sum = k
 * @param value the number
 * @param sum the sum
 * @param k target value
 * @param i number of digits
 * Time Complexity: O(n)
 * Space Comlexity: O(1)
 */
void findNum(uint64_t& value, uint16_t sum, uint16_t k, short i){ //pass i as i--
    uint16_t d = k - sum, x = 0;
    if(sum < k) i= 1;
    for(uint16_t currDigit; d; d=k-sum){
        currDigit = uint64_t(value/pow(10, i-1)) % 10;
        if(sum > k){
            if(x < k){
                x += currDigit;     //adds digit to pSum
                i--;                                        //i points to next digit
            }
            else{
                value += pow(10, i+1);  //increments digit before pSum > k
                uint64_t extract = value % (long long int)pow(10, i+1);        //extracts portion to zero
                value -= extract;
                sum = digitSum(value, i);
                i = 1;                                                  //points i to the first digit
            }
        }
        else{
            x = std::min(d, uint16_t(9-currDigit));
            value += x * pow(10, i-1);
            sum += x;
            i++;
        }
    }
}

int main(){
    uint64_t value;
    uint16_t target, n;
    std::vector<uint64_t> res;
    short i;

    std::cin >> n;

    while(n != 0) {
        std::cin >> value >> target;

        uint16_t sum = digitSum(value, i);
        if (sum == target) {
            value++;
            sum = digitSum(value, i);
        }
        findNum(value, sum, target, i);

        res.push_back(value);
        n--;
    }
    for(auto it : res) std::cout << it << std::endl;
    return 0;
}