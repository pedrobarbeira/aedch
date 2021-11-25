#include <iostream>
#include <list>

struct Plane{
    char type;
    std::string id;
    uint32_t time;
};

void airport(){
    int takeoff, land, t;
    std::string id;
    std::list<Plane*> planes;

    std::cin >> takeoff >> land;

    while(takeoff > 0){
        Plane* p = new Plane;
        (*p).type = 'T';
        std::cin >> id >> t;
        (*p).id = id;
        (*p).time = t;
        planes.push_back(p);
    }

}

int main(){
    int n;

    std::cin >> n;

    while(n > 0){
        airport();
        n--;
    }

    return 0;

}