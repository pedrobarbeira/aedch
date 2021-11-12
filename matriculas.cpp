#include <iostream>
#include <vector>
#include <cmath>

static int Z_VAL = 22;                                                                                                      //fix for portuguese alphabet
static int X_VAL = 21;                                                                                                      //fix for portuguese alphabet
static int BIG_LETTER = 23;                                                                                                 //increment of 1 big letter i.e: BA-00-00 = 23 small letters
static int GEN_VAL = 5290000;                                                                                               //number of plates per generation:
// (23 (big letters) * 23 (small letters) * 10000 (numbers)
/**
 * An invaluable ally during implementation. Through this function it's possible
 * to quickly check the value of any pair of license plates. Decided to keep it
 * in the final code as a reward for all it's hard work during implementation.
 * May it serve as a reminder of the importance of the Work, no matter how small
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

//Simple helper functions
/**
 * Simple boolean test to check if the plate letters are according to
 * the Portuguese alphabet
 * @param c
 * @return true if valid, false otherwise
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
    if(m[2] == '-' && m[5] == '-') {                                                                                       //Plates must be of the form YY-YY-YY
        if (isalpha(m[0]) && isValid(m[0]) && isalpha(m[1]) && isValid(m[1]) &&                             //AA-00-00 is 1st generation
            isdigit(m[3]) && isdigit(m[4])) {
            if (isalpha(m[6]) && isValid(m[6]) && isalpha(m[7]) && isValid(m[7]))                           //AA-00-AA is 4th generation
                c = '4';
            else if (isdigit(m[6]) && isdigit(m[7]))
                c = '1';
        }
        else if (isalpha(m[6]) && isValid(m[6]) && isalpha(m[7]) && isValid(m[7]) &&                        //00-00-AAis 2nd generation
                 isdigit(m[0]) && isdigit(m[1]) && isdigit(m[3]) && isdigit(m[4]))
            c = '2';
        else if (isalpha(m[3]) && isValid(m[3]) && isalpha(m[4]) && isValid(m[4]) &&                        //00-AA-00 is 3rd generation
                 isdigit(m[0]) && isdigit(m[1]) && isdigit(m[6]) && isdigit(m[7]))
            c = '3';
        else c = '5';
    }
    else c = '5';                                                                                                           //An invalid plate has been entered. Triggers error response
}

/**
 * Normalizes the plate number to standardized XX-NN-NN. In the case when
 * the plate is of the XX-NN-XX format, normalizes to XX-XX-NN
 * @param m license plate
 * @param c generation
 */
//try to systematize this into a loop
void reorder(std::string& m, const char c){
    std::string temp1, temp2;
    switch(c){
        case '1':return;                                                                                                    //Already normalized
        case '2':                                                                                                           // Turns 00-00-AA into AA-00-00
            temp1 = m.substr(6, 2);
            temp2 = m.substr(0, 5);
            m = temp1 + "-" + temp2;
            return;
        case '3':                                                                                                           //Turns 00-AA-00 into AA-00-00
            temp1 = m.substr(3, 2);
            m = temp1 + "-" + m.substr(0, 2) + "-" + m.substr(6,2);
            return;
        case '4':                                                                                                           //Turns AA-00-AA into AA-AA-00
            temp1 = m.substr(6,2);
            temp2 = m.substr(3, 2);
            m = m.substr(0, 2) + "-" + temp1 + "-" + temp2;
            return;
        default: return;
    }
}

/**
 * Calculates the increment corresponding to the second letter of the plate
 * @param c the letter
 * @param p the power of 10 required
 * @param value the license plate numerical value
 */
long long int letterVal(char c , int p){
    long long value;
    if (c == 'Z') value = Z_VAL * (int)pow(10, p);
    else if (c == 'X') value = X_VAL * (int)pow(10, p);
    else if (c > 'J' && c < 'X') value = (c - 'A' - 1) * (int)pow(10, p);
    else value = (c - 'A') * (int)pow(10, p);
    return value;
}

//Mid-level abstractions
/**
 * Calculates the numerical value corresponding to a particular letter of the plate
 * @param c the letter
 * @param i the index of the letter
 * @param value the license plate numerical value
 * @param gen4 boolean to trigger gen4 plate handling
 */
void letterCalc(char c, int i, long long int& value, bool gen4) {
    int p, n;
    if(gen4) p = 2;                                                                                                         //Ajusts the power of 10 required for letterVal()
    else p = 4;
    switch(i){                                                                                                              //Adjusts the power of 23 required
        case 0:
            if(gen4) n = 3;
            else n = 1;
            break;
        case 1:
            if(gen4) n = 2;
            else n = 0;
            break;
        case 3: n = 1; break;
        case 4: n = 0; break;
        default: return;
    }
    value += (int)pow(BIG_LETTER, n) * letterVal(c, p);
}

/**
 * Turns a license plate key into a numerical value
 * @param m the license plate
 * @param c the generation
 * @return the corresponding numerical value
 */
long long int calcVal(std::string& m, const char c){
    long long int value = (int(c) -1) * GEN_VAL;                                                                            //Calculates the numerical equivalent of the generation

    bool gen4 = false;
    int n = 2;
    if(c == '4'){                                                                                                           //Triggers gen4 special case
        gen4= true;
        n = 5;
    }
    for(int i = 0; i < n; i++){                                                                                             //Calculates letter values
        if (i != 2)                                                                                                         //If it's gen4, skips over m[2] (a -)
            letterCalc(m[i], i, value, gen4);
    }
    if(!gen4) value += stoi(m.substr(3, 2)) * (int)pow(10, 2);                                          //Adds first pair of numbers

    value += stoi(m.substr(6,2));                                                                              //Adds last pair of numbers
    return value;
}

//Interface
/**
 * Parses the license plates and generations, ordering and normalizing them
 * @param m1 license plate
 * @param m2 license plate
 * @param c1 m1 generation
 * @param c2 m2 generation
 */
void parse(std::string& m1, std::string& m2, char& c1, char& c2){
    generation(m1, c1);                                                                                                 //Determines the generation of each plate
    generation(m2, c2);

    if(c1 == '5' || c2 == '5') return;                                                                                      //Terminates if there were invalid plates

    reorder(m1,c1);                                                                                                     //Normalizes the plate number to XX-NN-NN format
    reorder(m2, c2);
}

//Main
/**
 * Prints results vector
 * @param res results vector
 */
void print(const std::vector<int>&res){
    for(auto it = res.begin(); it < res.end(); it++)
        std::cout << (*it) << std::endl;
}

/**
 * The purpose of this function is to calculate the distance between two
 * license plates. The purpose is achieved by turning the license plate
 * into an integer type value, corresponding to it's position in a
 * hypothetical continuum.
 * I.E: AA-00-00 would be 0, AA-23-00 would be 2300, 00-00-AA would be 5290000
 * @return 0 upon success
 */
int matriculas() {
    long long int i1, i2;                                                                                                   //Variable declarations
    std::string m1, m2;
    char g1, g2;
    std::vector<int> res;
    int n;

    std::cin >> n;                                                                                                          //Reads number of pairs from stdin;

    for(int i = 0; i < n; i++) {                                                                                            //Reads plate numbers from stdin
        std::cin >> m1 >> m2;

        if (m1.length() != 8) g1 = '5';                                                                                     //Plates are of the form YY-YY-YY, therefore must have 8 characters
        else if (m2.length() != 8) g2 = '5';
        else if (m1.length() != 8 && m2.length() != 8) {
            g1 = '5';
            g2 = '5';
        }
        else parse(m1, m2, g1, g2);                                                                         //Calls parser to normalize/order the plates and retrieve their generations

        if (g1 == '5' && g2 == '5') std::cout << "Ivalid Plates: " << m1 << " " << m2 << std::endl;                         //Alerts the user if any invalid plates were entered.
        else if (g1 == '5') std::cout << "Invalid Plate: " << m1 << std::endl;
        else if (g2 == '5') std::cout << "Ivalid Plate: " << m2 << std::endl;
        else {
            i1 = calcVal(m1, g1);                                                                                       //Calculates the numerical equivalent of each plate
            i2 = calcVal(m2, g2);
            res.push_back(abs(i1-i2));                                                                                           //Outputs the distance between a pair of plates
        }
    }

    print(res);                                                                                                             //Prints results

    return 0;
}