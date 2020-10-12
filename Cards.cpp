#include "Cards.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <time.h>
#include <unordered_set>
#include <mutex>
using namespace std;

//Shuffle function
void Cards::shuffle()
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
//Distribute Card
vector<int> Cards::distribute()
{
    //Only return hands with the deck has more than 5 cards left
    if (count <= 46)
    {
        m.lock();
        vector<int> hand(deck.begin() + count, deck.begin() + count + 5);
        count += 6;
        m.unlock();
        return hand;
    }
    return {};
}
//Reset the deck and shuffle
void Cards::reset()
{
    count = 0;
    shuffle();
}

//Check Score
pair<int, string> Cards::checkScore(vector<int> hand)
{

    int size = hand.size();
    int total = 0;
    //Empty hand
    if (size == 0)
    {
        return make_pair(0, "EMPTY HAND");
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
            //Rare case of 2 or more royal flush the superior suit wins
            return make_pair(1000 + (hand[0] / 13), "ROYAL FLUSH !!");
        }
        //Straight flush
        for (int i = 1; i < size; ++i)
        {
            if ((hand[i] % 13) - 1 != (hand[i - 1] % 13))
            {
                //Normal Flush
                return make_pair(600, "FLUSH");
            }
            if (i == (size - 1))
            {
                //Rare case of 2 or more straight flush the superior suit wins
                return make_pair(900 + (hand[0] / 13), "STRAIGHT FLUSH");
            }
        }
    }

    //Four of a kind
    if (umap.size() == 2 && unique_suits.size() == 4)
    {
        return make_pair(800 + (hand.back() % 13), "FOUR OF A KIND");
    }

    if (unique_suits.size() >= 3)
    {
        //Full house
        if (umap.size() == 2 && ((umap[*unique_suits.begin()] == 3 || umap[*unique_suits.begin()] == 2)))
        {
            return make_pair(700 + (hand.back() % 13), "FULL HOUSE");
        }
        //Three of a kind
        else if (umap.size() == 3)
        {
            for (auto i = unique_suits.begin(); i != unique_suits.end(); ++i)
            {
                if (umap[*i] == 3)
                {
                    return make_pair(400 + (hand.back() % 13), "THREE OF A KIND");
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
                return make_pair(500 + (hand.back() % 13), "STRAIGHT");
            }
        }
    }
    //Two pair
    if (umap.size() == 3)
    {
        for (int i = 0; i < hand.size(); ++i)
        {
            if (umap[hand[i]] == 2)
            {
                total += hand[i];
            }
        }
        total += 300;

        //Highest pair wins
        return make_pair(total, "TWO PAIR");
    }
    //Pair
    if (umap.size() == 4)
    {
        //Highest pair wins
        for (int i = 0; i < hand.size(); ++i)
        {
            if (umap[hand[i]] == 2)
            {
                total = hand[i] + 200;
                break;
            }
        }
        return make_pair(total, "PAIR");
    }

    //High Card
    return make_pair(hand.back(), "HIGH CARD");
}

void Cards::show(vector<int> hand)
{
    m.lock();
    int size = hand.size();
    for (int i = 0; i < size; ++i)
    {
        int suits = hand[i] / 13;
        int num = hand[i] % 13;
        cout << cardType[suits] << "-" << cardRef[num] << " ";
    }
    cout << endl;
    m.unlock();
}