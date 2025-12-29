#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;

struct Team {
    string name;
    double rating;

    string pot1_h;
    string pot1_a;

    string pot2_h;
    string pot2_a;

    string pot3_h;
    string pot3_a;

    string pot4_h;
    string pot4_a;
};

vector<Team> loadPot(const json& potJson) {
    vector<Team> pot;

    for (auto& entry : potJson) {
        Team t;
        t.name = entry[0].get<std::string>();
        t.rating = entry[1].get<double>();
        pot.push_back(t);
    }
    return pot;
}

void display_teams(json teams){
    for (auto& [key, value] : teams.items()) {
        cout << "***** ";
        cout << key;
        cout << " *****" << endl;

        vector<Team> pot = loadPot(value);

        for (auto& t : pot){
            cout << t.name << endl;
            cout << "--- rating: " << t.rating << endl;
            cout << "--- Pot 1 home: " << t.pot1_h << endl;
            cout << "--- Pot 1 away: " << t.pot1_a << endl;

            cout << "--- Pot 2 home: " << t.pot2_h << endl;
            cout << "--- Pot 2 away: " << t.pot2_a << endl;

            cout << "--- Pot 3 home: " << t.pot3_h << endl;
            cout << "--- Pot 3 away: " << t.pot3_a << endl;

            cout << "--- Pot 4 home: " << t.pot4_h << endl;
            cout << "--- Pot 4 away: " << t.pot4_a << endl;
        }
    }
}   

int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);

    display_teams(teams);

    return 0;
}

