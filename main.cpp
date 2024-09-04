#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using namespace std;


string selectRandom(vector<string>* array){
    vector<string> out;
    sample(
        (*array).begin(),
        (*array).end(),
        back_inserter(out),
        1,
        mt19937{random_device{}()}
    );
    return out[0];
}


int main() {

    vector<string> myArray{ "Blue", "Red", "Orange" };

    string t = selectRandom( &myArray );
    cout << t << endl;
    return 0;
}

