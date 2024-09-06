#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "json.hpp" // super ugly
#include <fstream> 

// compiling with: g++ -o main -std=c++17 -Wall -Wextra -pedantic main.cpp

using namespace std;
using json = nlohmann::json;

string selectRandom(vector<string>* array){
    vector<string> out;
    sample(
        (*array).begin(),
        (*array).end(),
        back_inserter(out), // seems unnecessary, here for the time being as it is working
        1,
        mt19937{random_device{}()}
    );
    return out[0];
}

int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);
    vector<string> pots = { "Pot1", "Pot2", "Pot3", "Pot4" };

    for (auto i : pots){

        cout << "Evaluating: " << i << endl;

        vector<string> myArray = teams[i].get<vector<string>>();
        string t = selectRandom( &myArray );
        cout << "---" << t << endl;
    }
    return 0;
}

