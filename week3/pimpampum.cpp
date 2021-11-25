#include <iostream>
#include <list>

int getWordNum(std::string sentence){
    int i = 1;
    for(int j = 0; j < sentence.size(); j++)
        if(isblank(sentence[j])) i++;
    return i;
}

void runSim(){
    int nPlayers, words;
    std::string sentence, p;
    std::list<std::string> players;

    std::cin.ignore();
    getline(std::cin, sentence);
    std::cin >> nPlayers;

    while(nPlayers > 0) {
        std::cin >> p;
        players.push_back(p);
        nPlayers--;
    }

    words = getWordNum(sentence);

    while(players.size() > 1){
        int i = 1;
        while(i < words){
            players.push_back((players.front()));
            players.pop_front();
            i++;
        }
        players.pop_front();
    }

    if(players.front() == "Carlos") std::cout << "O Carlos nao se livrou\n";
    else std::cout << "O Carlos livrou-se (coitado do " << players.front() << "!)\n";

}

int pimpampum(){
    int runs;

    std::cin >> runs;

    while(runs > 0){
        runSim();
        runs--;
    }

    return 0;
}