#include <algorithm>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>
#include <optional>

using namespace std;
using json = nlohmann::json;

struct Team {
    string name;
    string region;
    double rating;
    int startingPot;
    array<array<int, 2>, 4> pots = {{
        { -1, -1 },
        { -1, -1 },
        { -1, -1 },
        { -1, -1 }
    }};

};

class Calendar {
    public:
        json teamsData;
        vector<Team> teams;
        vector<string> pots = {"Pot1", "Pot2", "Pot3", "Pot4"};

        Calendar(json x) {
            teamsData = x;
            initialize(teamsData);
        };

        optional<int> getPotIndex(string potstring) {
            auto it = find(pots.begin(), pots.end(), potstring);

            if (it != pots.end()) {
                int index = it - pots.begin();
                return index;
            }
            return nullopt;
        };

        void initialize(const json& teamsData) {
            for (auto& [key, value] : teamsData.items()) {
                for (auto& entry : value) {

                    auto _potindex = getPotIndex(key);
                    if (_potindex) {
                        Team t;
                        t.name = entry[0].get<std::string>();
                        t.rating = entry[1].get<double>();
                        t.startingPot = *_potindex;
                        teams.push_back(t);
                    }
                }
            }
        };

        void listTeamsData() {
            for (Team t : teams) {
                cout << t.name << " - " << pots[t.startingPot] << " - " << t.rating << endl;
            }
        };

        // TODO: add color to team based on pot
        // TODO: add color to pot matches based on difficulty
        void printCalendar() {
            constexpr int teamNameWidth = 20;

            cout << "┌" << string(teamNameWidth + 4 * 7, '-') << "┐" << "\n";

            cout << "|" << setw(teamNameWidth) << left << "Team Name";

            for (int p = 0; p < 4; ++p) {
                cout << "| POT" << (p + 1) << " ";
            }
            cout << "|" << "\n";

            cout << "|" << setw(teamNameWidth) << left << " ";

            for (int p = 0; p < 4; ++p) {
                cout << "| H  A ";
            }
            cout << "|" << "\n";

            cout << "|" << string(teamNameWidth + 4 * 7, '-') << "|" << "\n";

            for (const Team& t : teams) {
                cout << "|" << setw(teamNameWidth) << left << t.name << "|";
                
                constexpr int potWidth = 3;
                for (int p = 0; p < 4; ++p) {
                    cout << setw(potWidth) << t.pots[p][0] << setw(potWidth) << right << t.pots[p][1] << "|";
                }
                cout << "\n";
            }
            cout << "└" << string(teamNameWidth + 4 * 7, '-') << "┘" << "\n";
        };
};


int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);

    Calendar myCal(teams);

    // manual match making for testing purposes
    myCal.teams[0].pots[myCal.teams[1].startingPot][0] = 1;
    myCal.teams[1].pots[myCal.teams[0].startingPot][1] = 0;

    myCal.teams[0].pots[myCal.teams[14].startingPot][0] = 14;
    myCal.teams[14].pots[myCal.teams[0].startingPot][1] = 0;

    myCal.printCalendar();


    return 0;
}

