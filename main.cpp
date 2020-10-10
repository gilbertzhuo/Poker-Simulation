#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <time.h>
#include <unordered_set>
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
    void show(vector<int> hand)
    {
        int size = hand.size();
        for (int i = 0; i < size; ++i)
        {
            int suits = hand[i] / 13;
            int num = hand[i] % 13;
            cout << cardType[suits] << " " << cardRef[num] << endl;
        }
    }

    //Check Score
    int checkScore(vector<int> hand)
    {
        int size = hand.size();
        //Empty hand
        if (size == 0)
        {
            return 0;
        }
        sort(hand.begin(), hand.end());

        // int suits = hand[0] / 13;
        // int num = hand[0] % 13;
        //Unique hands
        unordered_set<int> unique_suits;
        for (int i = 0; i < hand.size(); ++i)
        {
            unique_suits.insert(hand[i] / 13);
        }
        unordered_map<int, int> umap;
        //Store card frequency into dictionary
        for (int i = 0; i < size; ++i)
        {
            umap[hand[i] % 13]++;
        }

        if (unique_suits.size() == 1)
        {
            //Royal flush
            //(Was thinking of using dictionary but felt unnecessary since sorted)
            if (hand[0] % 13 == 0 && hand[1] % 13 == 9 && hand[2] % 13 == 10 && hand[3] % 13 == 11 && hand[4] % 13 == 12)
            {
                cout << "ROYAL FLUSH !!" << endl;
                //Rare case of 2 or more royal flush the superior suit wins
                return 1000 + (hand[0] / 13);
            }
            //Straight flush
            for (int i = 1; i < size; ++i)
            {
                if ((hand[i] % 13) - 1 != (hand[i - 1] % 13))
                {
                    //Normal Flush
                    cout << "FLUSH" << endl;
                    return 600;
                }
                if (i == (size - 1))
                {
                    cout << "STRAIGHT FLUSH" << endl;
                    //Rare case of 2 or more straight flush the superior suit wins
                    return 900 + (hand[0] / 13);
                }
            }
        }

        //Four of a kind
        if (umap.size() == 2 && unique_suits.size() == 4)
        {
            cout << "FOUR OF A KIND" << endl;
            return 800;
        }

        if (unique_suits.size() >= 3)
        {
            //Full house
            if (umap.size() == 2 && ((umap[*unique_suits.begin()] == 3 || umap[*unique_suits.begin()] == 2)))
            {
                cout << "FULL HOUSE" << endl;
                return 700;
            }
            //Three of a kind
            else if (umap.size() == 3)
            {
                for (auto i = unique_suits.begin(); i != unique_suits.end(); ++i)
                {
                    if (umap[*i] == 3)
                    {
                        cout << "THREE OF A KIND" << endl;
                        return 400;
                    }
                }
            }
        }

        //Straight
        //ALL UNIQUE
        if (umap.size() == 5)
        {
            for (int i = 1; i < size; ++i)
            {
                if ((hand[i] % 13) - 1 != (hand[i - 1] % 13))
                {
                    break;
                }
                if (i == (size - 1))
                {
                    cout << "STRAIGHT" << endl;
                    return 500;
                }
            }
        }
        //Two pair
        if (umap.size() == 3)
        {
            cout << "TWO PAIR" << endl;
            return 300;
        }
        //Pair
        if (umap.size() == 4)
        {
            cout << "PAIR" << endl;
            return 200;
        }

        //High Card
        cout << "HIGH CARD" << endl;
        return hand.back();
    }
    Cards()
    {
        shuffle();
    }
};
struct user
{
    vector<int> hands;
    int score = 0;
};
int main()
{
    Cards c;
    // user a;
    // a.hands = c.distribute();
    // c.show(a.hands);
    vector<int> ccc = {4, 17, 6, 16, 2};
    cout << c.checkScore(ccc);

    return 0;
}