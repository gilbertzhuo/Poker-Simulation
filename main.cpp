#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <time.h>
using namespace std;

class Cards
{
private:
    int count = 0;
    const string cardType[4] = {"CLUBS", "DIAMONDS", "HEARTS", "SPADES"};
    const string cardRef[13] = {"ACE", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    //Initialise a deck
    vector<int> deck = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12,
                        13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,
                        26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38,
                        39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51};
    //Shuffle function
    void shuffle()
    {
        //Using time as seed
        srand(time(NULL));
        //Fisher–Yates shuffle Algorithm O(N)
        for (int i = 51; i > 0; i--)
        {
            int j = rand() % (i + 1);
            swap(deck[i], deck[j]);
        }
    }

public:
    //Distribute Card
    vector<int> distribute()
    {
        //Only return hands with the deck has more than 5 cards left
        if (count <= 46)
        {
            vector<int> hand(deck.begin() + count, deck.begin() + count + 5);
            count += 6;
            return hand;
        }
        return {};
    }
    //Reset the deck and shuffle
    void reset()
    {
        count = 0;
        shuffle();
    }
    void show(vector<int> hands)
    {
        int size = hands.size();
        for (int i = 0; i < size; ++i)
        {
            int suits = hands[i] / 13;
            int num = hands[i] % 13;
            cout << cardType[suits] << " " << cardRef[num] << endl;
        }
    }

    //Check Win
    int checkWin(vector<int> hand)
    {
        sort(hand.begin(), hand.end());

        //Royal flush

        //Straight flush

        //Four of a kind

        //Full house

        //Flush

        //Straight

        //Three of a kind

        //Two pair

        //Pair

        //High Card
        return 0;
    }
    Cards()
    {
        shuffle();
    }
};

int main()
{
    Cards c;
    vector<int> hands;
    hands = c.distribute();
    c.show(hands);

    return 0;
}