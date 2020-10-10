#include <iostream>
#include <vector>
#include <mutex>
using namespace std;
class Cards
{
private:
    mutex m;
    int count = 0;
    const string cardType[4] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    const string cardRef[13] = {"ACE", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    //Initialise a deck
    vector<int> deck = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};
    //Shuffle function
    void shuffle();

public:
    //Distribute Card
    vector<int> distribute();
    //Reset the deck and shuffle
    void reset();
    //Turns numeric numbers into  cardType and number
    // void show(vector<int> hand);
    //Check Score
    pair<int, string> checkScore(vector<int> hand);
    Cards()
    {
        shuffle();
    };
};