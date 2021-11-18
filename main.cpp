#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>

struct Sequence{
    Sequence* parent = NULL;
    std::string sequence;
    uint16_t includes = 0;
    std::vector<Sequence*> derivations;
};

bool bestKey(Sequence* s1, Sequence* s2){
    if(s1->includes == s2->includes)
        return s1->sequence.length() < s2->sequence.length();
    else return s1->includes > s2->includes;
}

void cleanUp(std::vector<Sequence*>& in, std::string s1){
    for(std::vector<Sequence*>::iterator it = in.begin(); it != in.end(); it++)
        if((*it)->sequence.length() <= s1.length()) {
            if (s1.find((*it)->sequence) != UINT32_MAX && s1 != (*it)->sequence) {
                in.erase(it);
                it--;
            }
        }
}

std::string concatenate(std::string s1, std::string s2){
    std::string ret = s1 + s2,
            t1, t2;
    int i = std::min(s1.length(), s2.length()) - 1;
    while(i > 0){
        t1 = s1.substr(s1.length()-i, i);
        t2 = s2.substr(0, i);
        if(t1 == t2) {
            ret = s1.substr(0, s1.length()) + s2.substr(i);
            break;
        }
        else {
            t1 = s1.substr(0, i);
            t2 = s2.substr(s2.length()-i, i);
            if( t1 == t2) {
                ret = s2.substr(0, s2.length()) + s1.substr(i, s1.length());
                break;
            }
            else i--;
        }
    }
    return ret;
}

void potentialKeys(std::vector<std::string> inp, std::vector<std::string>& potential, int size){
    std::string s1, s2;
    for(int i = 0; i < inp.size(); i++){
        for(int j = inp.size()-1; j > i; j--){
            s1 = concatenate(inp[i], inp[j]);
            if(s1.length() <= size) potential.push_back(s1);
            s2 = concatenate(inp[j], inp[i]);
            if(s2.length() <= size) potential.push_back(s2);
        }
    }
}

int countSub(std::vector<Sequence*> in, std::string key){
    int i = 0;
    for(auto it : in){
        if(key.find(it->sequence) != UINT32_MAX) i++;
    }
    return i;
}

/**
 * Exhaustively combines strings and stores them in parent's derivation vector
 * @param in the vector of strings
 * @param parent the string to be combined with
 * @param size the string size restriction
 */
void matchmaker(std::vector<Sequence*>in, Sequence* parent, int size){
    std::string s;
    for(auto it: in){
        if(it->sequence != parent->sequence){
            s = concatenate(it->sequence, parent->sequence);
            if(s.length() < size){
                Sequence* newSeq = new Sequence;
                newSeq->sequence = s;
                newSeq->parent = parent;
                parent->derivations.push_back(newSeq);              //Stores them in parent's derivations vector
            }
        }
    }
}

//original method receives no parent and calls matchmaker
/**
 * Checks the derivations vector of the parent against the atomic inputs to
 * determinate suitable candidate keys
 * @param in the atomic inputs vector
 * @param keys holds candidate keys
 * @param size the restriction max string length
 * @return the key, if it happens to find one; empty string otherwise
 */
std::string forgeKeys(Sequence* parent, std::vector<Sequence*> in, std::vector<Sequence*>& keys, int size) {
    std::vector<Sequence *>::iterator it = in.begin();
    //Counts how many atomic substrings fit in each possible key
    for (std::vector<Sequence *>::iterator d = (*it)->derivations.begin(); d != (*it)->derivations.end(); d++) {
        (*d)->includes = countSub(in, (*d)->sequence);
        if ((*d)->includes <= 2) {          //Eliminates redundant keys
            (*it)->derivations.erase(d);
            d--;
        } else if ((*d)->includes == in.size()) return (*d)->sequence;
    }
    sort((*it)->derivations.begin(), (*it)->derivations.end(), bestKey);        //Sorts remaining keys

    for (auto d: (*it)->derivations)                    //Cleans up the key vector
        cleanUp((*it)->derivations, d->sequence);

    keys.insert(keys.end(), (*it)->derivations.begin(), (*it)->derivations.end());
    it++;
    return "";
}

std::string shortestSuperString(std::vector<Sequence*> in, int size) {
    std::vector<Sequence *> keys;
    std::string res = "";
    int j = 0;
    sort(in.begin(), in.end(), bestKey);
    //Cleans up values that are substrings of other values
    for (int i = 0; i < in.size(); i++)
        cleanUp(in, in[i]->sequence);
    int i = 0; //counts increments on main sequence
    //Might have to insert this into a larger while that cicles through all atomic inputs
    //Calculates all permutations of all values and removes redundancy

    matchmaker(in, (*in.begin()), size);
    res = forgeKeys((*in.begin()),in, keys, size);                //has non-redundant keys forged from it[0]
    std::vector<Sequence*>::iterator k = keys.begin();

    while (res.empty() || k != keys.end()) {
        //At this point i have a vector with the best possible candidate keys
        //I want to apply the same method to them:
        //  combine each key with each atomic input
        //  eliminate redundancy
        //      need a counter to account for powers of 2 - try to apply this to brute force method, since this was the problem that kept it from converging
        //  repeat the process to exhaustion
        //Eventually we'll either reach a key that workd, or an empty derivations vector -> all keys will have length > size
        //Iterate to next key in line - either next in parent's derivation vector, or next in original vector
    }
    std::cout << "res: " << res << std::endl;
}

int main() {
    std::vector<Sequence*> input;
    std::ifstream infile;
    std::string in;
    int q, size;

    infile.open("C:\\Coding\\Cpp\\AEDCH\\week2\\dnafiles\\inp3.txt");
    infile >> q >> size;

    while(q != 0){
        infile >> in;
        Sequence* newSeq = new Sequence;
        (*newSeq).sequence = in;
        input.push_back(newSeq);
        q--;
    }

    shortestSuperString(input, size);


    return 0;
}
