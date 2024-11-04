#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>

/*
COMPILER COMMAND:
g++ -o main -std=c++17 -Wall -Wextra -I /opt/homebrew/Cellar/nlohmann-json/3.11.3/include -pedantic main.cpp
*/

using namespace std;
using json = nlohmann::json;

vector<string> selectRandom(vector<string>* array, string avoid){
    vector<string> out;
    // barely understanding what's going on here, will need to come back to this
    // gets 3 random items from vector
    sample(
        (*array).begin(),
        (*array).end(),
        back_inserter(out), // seems unnecessary, here for the time being as it is working
        3,
        mt19937{random_device{}()}
    );

    // If element is found found, erase it otherwise remove latest element 
    // to make sure we have only 2 entries
    auto it = std::find(out.begin(), out.end(), avoid);

    if (it != out.end()) {
        out.erase(it);
    } else {
        out.pop_back();
    }

    return out;
}

int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);
    unordered_map<string, vector<string>> drawings;

    vector<string> pots = {"Pot1", "Pot2", "Pot3", "Pot4"}; // TODO: get these from json file too
    
    string currentTeam = "Internazionale";
    vector<string> currentTeams = teams["Pot1"].get<vector<string>>();

    vector<string> test = selectRandom( &currentTeams, currentTeam);

    drawings[currentTeam] = {test};


    for (auto  i : drawings) {
        for (auto j : i.second) {
            cout << j << endl;
        }
    }



    // cout << test << endl;
    // cout << static_cast<int16_t>(res) << endl;

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

