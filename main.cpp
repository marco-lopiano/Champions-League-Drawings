#include <algorithm>
#include <iostream>
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
    double rating;

    string belongsTo;
    string region;
};

struct Match {
    string pot;
    Team* home;
    Team* away;
    double temperature;
};

class Calendar {
    public:
        json teams;
        vector<Team> Teams;
        vector<Match> Matches;

        Calendar(json x) {
            teams = x;
            initialize(teams);
        };

        void initialize(const json& teams) {
            for (auto& [key, value] : teams.items()) {
                for (auto& entry : value) {
                    Team t;
                    t.name = entry[0].get<std::string>();
                    t.rating = entry[1].get<double>();
                    t.belongsTo = key;
                    Teams.push_back(t);
                }
            }
        };

        void traverseAllMatches(){
            for (const auto& m : Matches) {
                cout << "***" << endl;
                cout << m.pot << endl;
                cout << m.home->name << " vs " << m.away->name << " " << m.temperature << endl;
            }
        };

        Team* getTeamByName(string name) {
            for (auto& entry : Teams){
                if (entry.name == name) {
                    return &entry;
                }
            }
            return nullptr;
        };

        void addMatch(string teamA, string teamB, string potType) {
            auto tA = getTeamByName(teamA);
            auto tB = getTeamByName(teamB);


            if (!tA || !tB) {
                cerr << "Team not found\n";
                return;
            }

            if (tA->name == tB->name) {
                cerr << "Team cannot be againts itself\n";
                return;
            }

            if ( tA->belongsTo != potType && tB->belongsTo != potType ) {
                cerr << "At least one Team needs to belong to the pot type\n";
                return;
            }

            Match m;
            m.pot = potType;
            m.home = tA;
            m.away = tB;
            m.temperature = tA->rating + tB->rating;
            Matches.push_back(m);
        }
};


int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);

    Calendar myCal(teams);

    // myCal.traverse();

    myCal.addMatch("Juventus", "Real Madrid", "Pot1");
    myCal.addMatch("Barcelona", "Barcelona", "Pot1");
    myCal.addMatch("Barcelona", "Internazionale", "Pot1");



    myCal.traverseAllMatches();

    // auto t = myCal.getTeamByName("Real Madrid");
    // if (t) {
    //     cout << (*t).name << "\n";
    // }


    return 0;
}

