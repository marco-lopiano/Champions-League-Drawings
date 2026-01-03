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
    string region;
    double rating;
    string placementPot;
};

struct Match {
    double temperature;
    Team* home;
    Team* away;
};

class Calendar {
    public:
        json teamsData;
        vector<Team> teams;
        vector<Match> matches;

        Calendar(json x) {
            teamsData = x;
            initialize(teamsData);
        };

        void initialize(const json& teamsData) {
            for (auto& [key, value] : teamsData.items()) {
                for (auto& entry : value) {
                    Team t;
                    t.name = entry[0].get<std::string>();
                    t.rating = entry[1].get<double>();
                    t.placementPot = key;
                    teams.push_back(t);
                }
            }
        };

        void listTeams() {
            for (Team t : teams) {
                cout << t.name << " - " << t.placementPot << " - " << t.rating << endl;
            }
        };

        Team* getTeamByName(string name) {
            for (auto& entry : teams){
                if (entry.name == name) {
                    return &entry;
                }
            }
            return nullptr;
        };

        int countMatches (Team* team, string potType, string location) {
            int counter = 0;
            vector<string> pots = {"Pot1", "Pot2", "Pot3", "Pot4"};

            for (auto& m : matches) {
                if (location == "home") {
                    if (team->name == m.home->name && team->placementPot == potType) {
                        counter ++;
                    }
                }
            }

            return counter;
        }
        
        // TODO: add cases?
        bool isMatchPossible (Team* tH, Team* tA) {
            if (!tH || !tA) {
                cerr << "Team not found\n";
                return false;
            }

            if (tH->name == tA->name) {
                cerr << "Team cannot be againts itself\n";
                return false;
            }

            int homeTeamCountH = countMatches(tH, "Pot1", "home");
            if (homeTeamCountH >= 2) {
                return false;
            }

            // if ( tA->placementPot != potType && tB->placementPot != potType ) {
            //     cerr << "At least one Team needs to belong to the pot type\n";
            //     return false;
            // }
            return true;
        }

        void addMatch(string teamHome, string teamAway) {
            auto tH = getTeamByName(teamHome);
            auto tA = getTeamByName(teamAway);

            bool check = isMatchPossible(tH, tA);

            if ( check == true) {
                Match m;
                m.home = tH;
                m.away = tA;
                m.temperature = tH->rating + tA->rating;
                matches.push_back(m);
            }
        }

        void listMatches(){
            for (const auto& m : matches) {
                cout << "***" << endl;
                cout << "Home: " << m.home->name << " (" << m.home->placementPot << ")" << " vs " << "Away: " << m.away->name << " (" << m.away->placementPot << ")" << " " << m.temperature << endl;
            }
        };
};


int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);

    Calendar myCal(teams);

    myCal.addMatch("Internazionale", "Real Madrid");
    myCal.addMatch("Internazionale", "Barcelona");
    myCal.addMatch("Bayern Munich", "Internazionale");


    myCal.addMatch("Internazionale", "Atletico Madrid");



    myCal.listMatches();

    return 0;
}

