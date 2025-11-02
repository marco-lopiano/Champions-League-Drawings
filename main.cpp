#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <nlohmann/json.hpp>
#include <fstream>
#include <unordered_map>

using namespace std;
using json = nlohmann::json;

// HELPERS
vector<string> concatenateTeams(json data, vector<string>* pots) {
    vector<string> out;
    for (auto i : *pots){
        vector<string> temp = data[i].get<vector<string>>();
        out.insert( out.end(), temp.begin(), temp.end());
    }
    return out;
}

class Draw {
    public:
        string home;
        string away;
        bool valid;

        Draw(bool isValid = true) {
            home = "None";
            away = "None";
            valid = isValid;
        };

        bool isFull() {
            if (home == "None" && away == "None") {
                return true;
            } else {
                return false;
            }
        }

        bool isHomeFull() {
            if (home == "None") {
                return false;
            }
            return true;
        }

        bool isAwayFull() {
            if (away == "None") {
                return false;
            }
            return true;
        }

        bool isValid() {
            return valid;
        }
};

class TeamCalendar {
    public:
        string name;
        unordered_map<string, Draw> draws;
        bool valid;
        TeamCalendar() = default; // https://stackoverflow.com/questions/71047000/error-no-matching-function-for-call-to-nodenode-secondstdforward-ar

        TeamCalendar(string x, bool isValid = true) {
            name = x;
            valid = isValid;

        }
        
        Draw getPotByType(string potType) {
            Draw out(false);
            if ( draws.find(potType) != draws.end() ) {
                out = draws[potType];
            }
            return out;
        }

        void addPot(string potType, Draw draw) {
            if (getPotByType(potType).isValid() == false){
                draws[potType] = draw;
            }
        }
        bool isValid() {
            return valid;
        }

        void display(){
            cout << "display method to be implemented" << endl;
        }
};

class Calendar {
    public:
        string season;
        vector<string> teams;
        vector<string> pots;
        unordered_map<string, TeamCalendar> calendar;

        Calendar(string x, vector<string>y,  vector<string> z) {
            season = x;
            teams = y;
            pots = z;
        }

        TeamCalendar getTeamCalendar(string teamName) {
            TeamCalendar out("False", false);
            if ( calendar.find(teamName) != calendar.end() ) {
                out = calendar[teamName];
            }
            return out;
        }

        void addToCalendar(string teamName, TeamCalendar data_in) {
             if (getTeamCalendar(teamName).isValid() == false){
                calendar[teamName] = data_in;
            }
        }

        void runDrawings() {

            for (auto currentTeam : teams) {

                // adds team calendar to calendar if not already there
                TeamCalendar temp = TeamCalendar(currentTeam);
                addToCalendar(currentTeam, temp);
      
                cout << temp.isValid() << endl;

                // check if team is already in calendar

                // TeamCalendar currentTeamCalendar(currentTeam);

        //         Draw test = currentTeamCalendar.getPotByType("Pot1");

        //         cout << test.isValid() << endl;

        //         // cout << test << endl;

        //             for (auto p : pots){

        //                 Draw tempDraw;
                

        //                 // vector<string> potTeams = teams[p].get<vector<string>>();
        //                 // vector<string> potSelection = selectRandom( &potTeams, currentTeam );

        //                 // SinglePotDraw potDraw(potSelection, p);
        //                 // otherTest.teamDrawings.push_back(potDraw);

        //                 break;
        //             }

        //         //     diplayTeamDrawings( otherTest, sep);

                    break;
            }
        }
};

int main() {

    ifstream f("teams.json");
    json teams = json::parse(f);
  
    vector<string> pots = {"Pot1", "Pot2", "Pot3", "Pot4"}; // TODO: get these from json file too

    vector<string> allTeams = concatenateTeams( teams, &pots );

    // int sep = getMax(&allTeams);

    Calendar currentCalendar( "2024/25", allTeams, pots );
    currentCalendar.runDrawings();


    return 0;
}

