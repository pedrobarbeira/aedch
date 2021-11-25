#include <iostream>
#include <stack>
#include <vector>

class InvalidExp{
    std::string err;
public:
    InvalidExp(){
        err = "Expressao Incorrecta\n";
    }
    std::string getErr(){
        return err;
    }
};

bool isoperator(std::string c){
    return c == "*" || c == "/" || c == "+" || c == "-";
}

bool validNum(std::string s) {
    for (int i = 0; i < s.size(); i++)
        if (!isdigit(s[i])) return false;
    return true;
}

int getIndex(std::string s) {
    int index = 0;
    for (int i = 0; i < s.size(); i++) {
        if (!isblank(s[i])) index++;
        else break;
    }
    return index;
}

void rpnCalc(std::string line) {
    int i, x, y;
    std::stack<int> calc;
    std::string in;

    while (!line.empty()) {
        if (line.size() > 1) {
            i = getIndex(line);
            in = line.substr(0, i);             //takes out first number
            line = line.substr(++i);                 //truncates line
        } else {
            in = line;
            line = "";
        }
        if (isoperator(in)) {
            if (calc.empty()) throw InvalidExp();
            y = calc.top();
            calc.pop();
            if (calc.empty()) throw InvalidExp();
            x = calc.top();
            calc.pop();
            switch (in[0]) {
                case '+': x += y;break;
                case '-': x -= y;break;
                case '*':x *= y;break;
                case '/':x /= y; break;
            }
            calc.push(x);
        } else if (validNum(in)) {
            calc.push(stoi(in));
        } else throw InvalidExp();
    }
    if(calc.size() != 1) throw InvalidExp();
    std::cout << calc.top() << '\n';
    calc.pop();
}

int rpn(){
    int n;
    std::string line;
    std::vector<std::string> input;

    std::cin >> n;
    std::cin.ignore();

    while(n > 0) {
        std::getline(std::cin, line);
        input.push_back(line);
        n--;
    }

    for(auto in : input){
        try {
            rpnCalc(in);
        }
        catch (InvalidExp e) {
            std::cout << e.getErr();
        }
    }

    return 0;
}