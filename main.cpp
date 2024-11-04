#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>

/*
COMPILER COMMAND:
g++ -o main -std=c++17 -Wall -Wextra -I /opt/homebrew/Cellar/nlohmann-json/3.11.3/include -pedantic main.cpp
*/

using namespace std;
using json = nlohmann::json;

class SinglePotDraw {
    public:
        string potType;
        string home;
        string away;
        SinglePotDraw(vector<string> x, string y) {
            home = x[0];
            away = x[1];
            potType = y;
        }
};

class PerTeamCollectionOfDrawings {
    public:
        string team;
        vector<SinglePotDraw> teamDrawings;
        PerTeamCollectionOfDrawings(string name) {
            team = name;
        } 
};

vector<string> selectRandom(vector<string>* array, string avoid){
    vector<string> out;
    // gets 3 random teams from vector
    sample(
        (*array).begin(),
        (*array).end(),
        back_inserter(out), // seems unnecessary, here for the time being as it is working
        3,
        mt19937{random_device{}()}
    );

    // If element is found found, erase it otherwise remove latest element 
    // to make sure we have only 2 entries
    auto foundSelf = std::find(out.begin(), out.end(), avoid);

    if (foundSelf != out.end()) {
        out.erase(foundSelf);
    } else {
        out.pop_back();
    }

    return out;
}

void diplayTeamDrawings (PerTeamCollectionOfDrawings dataIn, int separator) {
    cout << dataIn.team << endl;
    cout << right << "    H:   "
        << setw(separator) << right << dataIn.teamDrawings[0].home << " | "
        << setw(separator) << right << dataIn.teamDrawings[1].home << " | "
        << setw(separator) << right << dataIn.teamDrawings[2].home << " | "
        << setw(separator) << right << dataIn.teamDrawings[3].home << " | "
        << endl;

    cout << right << "    A:   "
        << setw(separator) << right << dataIn.teamDrawings[0].away << " | "
        << setw(separator) << right << dataIn.teamDrawings[1].away << " | "
        << setw(separator) << right << dataIn.teamDrawings[2].away << " | "
        << setw(separator) << right << dataIn.teamDrawings[3].away << " | "
        << endl;
}
 
vector<string> concatenateTeams(json data, vector<string>* pots) {
    vector<string> out;
    for (auto i : *pots){
        vector<string> temp = data[i].get<vector<string>>();
        out.insert( out.end(), temp.begin(), temp.end());
    }
    return out;
}

int getMax (vector<string> *array) {
    int myMax = 0;

    for (auto i : *array) {
        int current = i.size();

        if (current > myMax) {
            myMax = current;
        }
    }
    return myMax;
}

int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);
  
    vector<string> pots = {"Pot1", "Pot2", "Pot3", "Pot4"}; // TODO: get these from json file too

    vector<string> allTeams = concatenateTeams( teams, &pots );

    int sep = getMax(&allTeams);

    for (auto currentTeam : allTeams) {

        PerTeamCollectionOfDrawings otherTest(currentTeam);

        for (auto p : pots){
            vector<string> potTeams = teams[p].get<vector<string>>();
            vector<string> potSelection = selectRandom( &potTeams, currentTeam );

            SinglePotDraw potDraw(potSelection, p);
            otherTest.teamDrawings.push_back(potDraw);
        }
        diplayTeamDrawings( otherTest, sep);
    }
    return 0;
}

