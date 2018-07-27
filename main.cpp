/// UnBeatables - LARA
//g++ -ggdb `pkg-config --cflags opencv` -o `basename main.cpp .cpp` main.cpp `pkg-config --libs opencv`./

#include "controller.hpp"

using namespace std;


int main(int argc, char* argv[])
{

    cout << "parse created..." << endl;

    Controller controller(argc, argv);

    return 0;
}
