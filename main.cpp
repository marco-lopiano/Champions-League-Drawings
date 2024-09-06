#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include "json.hpp" // super ugly
#include <fstream> 

// compiling with: g++ -o main -std=c++17 -Wall -Wextra -pedantic main.cpp

using namespace std;
using json = nlohmann::json;

int validityCheck(string current,  string drawed){
    if ( current == drawed ){
        return 0;
    } else {
        return 1;
    }
}

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

vector<string> runDrawings(vector<string>* array){
    vector<string> out;

    return out;
}

int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);
    vector<string> pots = {"Pot1", "Pot2", "Pot3", "Pot4"};

    vector<string> currentTeam = teams["Pot1"].get<vector<string>>();
    string test = selectRandom( &currentTeam );

    int res = validityCheck( "Internazionale", test );

    cout << test << endl;
    cout << static_cast<int16_t>(res) << endl;

    // for (auto p : pots){

    //     vector<string> currentTeam = teams[p].get<vector<string>>();
    //     for (auto t : currentTeam){
    //         cout << t << endl;
    //     }

    //     string t = selectRandom( &currentTeam );
    //     cout << "---" << t << endl;
    // }
    return 0;
}

