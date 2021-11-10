#include <iostream>
#include <vector>
#include <cmath>

static int Z_VAL = 22;          //fix for portuguese alphabet
static int X_VAL = 21;          //fix for portuguese alphabet
static int BIG_LETTER = 23;     //increment of 1 big letter i.e: BA-00-00 = 23 small letters
static int GEN_VAL = 5290000;   //number of plates per generation:
// (23 (big letters) * 23 (small letters) * 10000 (numbers)

/**
 * An invaluable ally during implementation. Through this function it's possible
 * to quickly check the value of any pair of license plates. Decided to keep it
 * in the final code as a reward for all it's hard work during implementation.
 * May it serve a reminder of the importance of the Work, no matter how small
 * or simple it may appear to the uninitiated.
 */
/*void driverTest(){
    std::string m1 = "12-SV-45";    //704456
    std::string m2 = "67-PT-89";

    char c1, c2;

    parse(m1,m2,c1,c2);

    long long int i1 = calcVal(m1, c1);
    long long int i2= calcVal(m2, c2);

    std::cout << i1-i2 << std::endl;
}*/

/**
 * Simple boolean test to check if the plate letters are according to
 * the Portuguese alphabet
 * @param c
 * @return
 */
bool isValid(char c){
    return c != 'K' && c != 'W' && c != 'Y';
}

/**
 * Determines which generation the plate belongs to. Triggers an error response
 * in main if an invalid plate is entered.
 * @param m the plate number
 * @param c the generation to be determined
 */
void generation(std::string m, char& c){
    //Plates must be of the form YY-YY-YY
    if(m[2] == '-' && m[5] == '-') {
        //AA-00-00 is 1st generation
        if (isalpha(m[0]) && isValid(m[0]) && isalpha(m[1]) && isValid(m[1]) &&
            isdigit(m[3]) && isdigit(m[4])) {
            //AA-00-AA is 4th generation
            if (isalpha(m[6]) && isValid(m[6]) && isalpha(m[7]) && isValid(m[7]))
                c = '4';
            else if (isdigit(m[6]) && isdigit(m[7]))
                c = '1';
        }
            //00-00-AAis 2nd generation
        else if (isalpha(m[6]) && isValid(m[6]) && isalpha(m[7]) && isValid(m[7]) &&
                 isdigit(m[0]) && isdigit(m[1]) && isdigit(m[3]) && isdigit(m[4]))
            c = '2';
            //00-AA-00 is 3rd generation
        else if (isalpha(m[3]) && isValid(m[3]) && isalpha(m[4]) && isValid(m[4]) &&
                 isdigit(m[0]) && isdigit(m[1]) && isdigit(m[6]) && isdigit(m[7]))
            c = '3';
        else c = '5';
    }
        //An invalid plate has been entered. Triggers error response
    else c = '5';
}

/**
 * Generalized swap function
 * @tparam T the generalized parameter
 * @param a to be swapped for b
 * @param b to be swapped for a
 */
template<typename T>
void swap(T& a, T& b){
    T temp;
    temp = a;
    a = b;
    b = temp;
}

/**
 * Swaps license plates and their respective generations
 * @param m1 license plate
 * @param m2 license plate
 * @param c1 m1 generation
 * @param c2 m2 generation
 */
void swapM(std::string& m1, std::string& m2, char& c1, char& c2){
    swap(m1, m2);
    swap(c1, c2);
}

/**
 * Determines which plate has the higher number and puts it in m1. Updates
 * generation accordingly
 * @param m1 license plate
 * @param m2 license plate
 * @param c1 m1 generation
 * @param c2 m2 generation
 */
void order(std::string& m1, std::string& m2, char&c1, char& c2) {
    //Compares generations first to save time and resources
    if (c2 > c1) {
        swapM(m1, m2, c1, c2);
        return;
    } else if (c1 == c2) {
        //If they are of the same generation, proceeds to a chain comparison of
        //each element of the plate
        if (m1[0] < m2[0]) swapM(m1, m2, c1, c2);
        else if (m1[0] == m2[0]) {
            if (m1[1] < m2[1]) swapM(m1, m2, c1, c2);
            else if (m1[1] == m2[1]) {
                if (m1[3] < m2[3]) swapM(m1, m2, c1, c2);
                else if (m1[3] == m2[3]) {
                    if (m1[4] < m2[4]) swapM(m1, m2, c1, c2);
                    else if (m1[4] == m2[4]) {
                        if (m1[6] < m2[6]) swapM(m1, m2, c1, c2);
                        else if (m1[6] == m2[6]) {
                            if (m1[7] < m2[7]) swapM(m1, m2, c1, c2);
                        }
                    }
                }
            }
        }
    }
}

/**
 * Normalizes the plate number to standardized XX-NN-NN. In the case when
 * the plate is of the XX-NN-XX format, normalizes to XX-XX-NN
 * @param m license plate
 * @param c generation
 */
void reorder(std::string& m, const char c){
    std::string temp1, temp2;
    switch(c){
        //Already normalized
        case '1':return;
            // Turns 00-00-AA into AA-00-00
        case '2':
            temp1 = m.substr(6, 2); //AA
            temp2 = m.substr(0, 5); //00-00
            m = temp1 + "-" + temp2; //AA-00-00
            return;
            //Turns 00-AA-00 into AA-00-00
        case '3':
            temp1 = m.substr(3, 2); //AA
            m = temp1 + "-" + m.substr(0, 2) + "-" + m.substr(6,2); //AA-00-00
            return;
            //Turns AA-00-AA into AA-AA-00
        case '4':
            temp1 = m.substr(6,2); //00
            temp2 = m.substr(3, 2); //AA
            m = m.substr(0, 2) + "-" + temp1 + "-" + temp2; //AA-AA-00
            return;
        default: return;
    }
}

/**
 * Calculates the increment corresponding to the first letter of the plate. All
 * the somethingLetter() functions handle the special case of the Portuguese
 * alphabet, which doesn't include the letters 'K', 'W' and 'Y'.
 * @param c the letter
 * @param p the power of 10 required
 * @param value the license plate numerical value
 */
void bigLetter(char c, int p, long long int& value){
    if (c == 'Z') value += Z_VAL * BIG_LETTER * (int)pow(10, p);
    else if (c == 'X') value += X_VAL * BIG_LETTER * (int)pow(10, p);
    else if (c > 'J' && c < 'X') value += (c - 'A' - 1) * BIG_LETTER * (int)pow(10, p);
    else value += (c - 'A') * BIG_LETTER * (int)pow(10, p);
}

/**
 * Calculates the increment corresponding to the second letter of the plate
 * @param c the letter
 * @param p the power of 10 required
 * @param value the license plate numerical value
 */
void smallLetter(char c , int p, long long int& value){
    if (c == 'Z') value += Z_VAL * (int)pow(10, p);
    else if (c == 'X') value += X_VAL * (int)pow(10, p);
    else if (c > 'J' && c < 'X') value += (c - 'A' - 1) * (int)pow(10, p);
    else value += (c - 'A') * (int)pow(10, p);
}

/**
 * Special case of the above functions for generation 4 license plates (XX-NN-XX).
 * Handles the first two letters. This is a special case, since the increments of the
 * first 2 letters require the use of powers of 23.
 * @param c the letter
 * @param index either 0, for the first, or 1, for the second
 * @param value the license plate numerical value
 */
void gen4Letter(char c, int index, long long int& value){
    if(index == 0){
        if (c == 'Z') value += Z_VAL * (int)pow(BIG_LETTER, 3) * (int)pow(10, 2);
        else if (c == 'X') value += X_VAL * (int)pow(BIG_LETTER, 3) * (int)pow(10, 2);
        else if (c > 'J' && c < 'X') value += (c - 'A' - 1) * (int)pow(BIG_LETTER, 3) * (int)pow(10, 2);
        else value += (c - 'A') * (int)pow(BIG_LETTER, 3) * (int)pow(10, 2);
    }
    else if (index == 1){
        if (c == 'Z') value += Z_VAL * (int)pow(BIG_LETTER, 2) * (int)pow(10, 2);
        else if (c == 'X') value += X_VAL * (int)pow(BIG_LETTER, 2) * (int)pow(10, 2);
        else if (c > 'J' && c < 'X') value += (c - 'A' - 1) * (int)pow(BIG_LETTER, 2) * (int)pow(10, 2);
        else value += (c - 'A') * (int)pow(BIG_LETTER, 2) * (int)pow(10, 2);

    }
    else return;
}

/**
 * Calculates the numerical value corresponding to a particular letter of the plate
 * @param c the letter
 * @param i the index of the letter
 * @param value the license plate numerical value
 * @param gen4 boolean to handle gen4 plates
 */
void letterCalc(char c, int i, long long int& value, bool gen4){
    if(gen4){
        switch(i){
            case 0:
                gen4Letter(c, 0, value);
                break;
            case 1:
                gen4Letter(c, 1, value);
                break;
            case 3:
                bigLetter(c, 2, value);
                break;
            case 4:
                smallLetter(c, 2, value);
            default: return;
        }

    }
    else {
        if (i == 0) {
            bigLetter(c, 4, value);
            return;
        } else {
            smallLetter(c, 4, value);

        }
    }
}

/**
 * Turns a license plate key into a numerical value
 * @param m the license plate
 * @param c the generation
 * @return the corresponding numerical value
 */
long long int calcVal(std::string& m, const char c){
    //Calculates the numerical equivalent of the generation
    long long int value = (int(c) -1) * GEN_VAL;

    //Handles the generation 4 plate special case
    if(c == '4'){
        letterCalc(m[0], 0, value, true);
        letterCalc(m[1], 1, value, true);
        letterCalc(m[3], 3, value, true);
        letterCalc(m[4], 4, value, true);
        value += (m[6] - '0') * 10 + (m[7] - '0');
    }
        //Handles standard cases
    else{
        //Process first value with special cases
        letterCalc(m[0], 0, value, false);
        //Process second value with special cases
        letterCalc(m[1], 1, value, false);
        //Process remaining values
        value += (m[3] -'0') * (int)pow(10, 3) + (m[4]-'0') * (int)pow(10, 2) +
                 (m[6]-'0') * 10 + (m[7]-'0');
    }
    return value;
}


/**
 * Parses the license plates and generations, ordering and normalizing them
 * @param m1 license plate
 * @param m2 license plate
 * @param c1 m1 generation
 * @param c2 m2 generation
 */
void parse(std::string& m1, std::string& m2, char& c1, char& c2){
    //Determines the generation of each plate
    generation(m1, c1);
    generation(m2, c2);

    //Terminates if there were invalid plates
    if(c1 == '5' || c2 == '5') return;

    //Normalizes the plate number to XX-NN-NN format
    reorder(m1,c1);
    reorder(m2, c2);

    //Determines which plate has a larger numerical equivalent
    order(m1,m2,c1,c2);

}

/**
 * Reads the console input and puts it into a string matrix
 * @param matriculas the string matrix
 */
void readInput(std::vector<std::vector<std::string>>& matriculas){
    int n;
    std::string m1, m2;
    std::vector<std::string>load;

    //Reads number of pairs from stdin
    std::cin >> n;

    //Reads and stores each pair in a n*2 string matrix
    for(int i = 0; i < n; i++){
        std::cin >> m1 >> m2;
        load.push_back(m1);
        load.push_back(m2);
        matriculas.push_back(load);
        load.clear();
    }
}

/**
 * The purpose of this function is to calculate the distance between two
 * license plates. The purpose is achieved by turning the license plate
 * into an integer type value, corresponding to it's position in a
 * hypothetical continuum.
 * I.E: AA-00-00 would be 0, AA-23-00 would be 2300, 00-00-AA would be 5290000
 * @return 0 upon success
 */
int main() {
    std::string m = "AA-00-00";
    char g;
    generation(m, g);

    long long int i1, i2;
    std::string m1, m2; //matriculas
    char g1, g2; //gerações

    std::vector<std::vector<std::string>> matriculas;

    //Read the list of license plates
    readInput(matriculas);

    //Iterates through the matrix and calculates distances
    for(auto it  = matriculas.begin(); it < matriculas.end(); it++) {
        m1 = (*it)[0];
        m2 = (*it)[1];

        //Plates are of the form YY-YY-YY, therefore must have 8 characters
        if (m1.length() != 8) g1 = '5';
        else if (m2.length() != 8) g2 = '5';
        else if (m1.length() != 8 && m2.length() != 8) {
            g1 = '5';
            g2 = '5';
        }
        else //Calls parser to normalize/order the plates and retrieve their generations
            parse(m1, m2, g1, g2);
        //Alerts the user if any invalid plates were entered.
        if (g1 == '5' && g2 == '5') std::cout << "Ivalid Plates: " << m1 << " " << m2 << std::endl;
        else if (g1 == '5') std::cout << "Invalid Plate: " << m1 << std::endl;
        else if (g2 == '5') std::cout << "Ivalid Plate: " << m2 << std::endl;
        else {
            //Calculates the numerical equivalent of each plate
            i1 = calcVal(m1, g1);
            i2 = calcVal(m2, g2);

            //Outputs the distance between a pair of plates
            std::cout << i1 - i2 << std::endl;
        }
    }

    return 0;
}

