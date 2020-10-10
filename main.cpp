#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
#include <time.h>
#include <unordered_set>
#include <thread>
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
            m.lock();
            vector<int> hand(deck.begin() + count, deck.begin() + count + 5);
            count += 6;
            m.unlock();
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
        m.lock();
        int size = hand.size();
        for (int i = 0; i < size; ++i)
        {
            int suits = hand[i] / 13;
            int num = hand[i] % 13;
            cout << cardType[suits] << " " << cardRef[num] << " ";
        }
        cout << endl;
        m.unlock();
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
            //Highest pair wins
            return 300;
        }
        //Pair
        if (umap.size() == 4)
        {
            cout << "PAIR" << endl;
            //Highest pair wins
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
    string name;
    vector<int> hand;
    int score = 0;
};

void thread_task(Cards &c, user &a)
{
    a.hand = c.distribute();
}

int main()
{
    //Initialize a deck
    Cards card;
    user a = {"Gilbert"};
    user b = {"player_b"};
    user c = {"player_c"};
    user d = {"player_d"};
    thread player_a(thread_task, ref(card), ref(a));
    thread player_b(thread_task, ref(card), ref(b));
    thread player_c(thread_task, ref(card), ref(c));
    thread player_d(thread_task, ref(card), ref(d));
    player_a.join();
    player_b.join();
    player_c.join();
    player_d.join();
    cout << a.name << endl;
    card.show(a.hand);
    cout << card.checkScore(a.hand) << endl;
    cout << b.name << endl;
    card.show(b.hand);
    cout << card.checkScore(b.hand) << endl;
    cout << c.name << endl;
    card.show(c.hand);
    cout << card.checkScore(c.hand) << endl;
    cout << d.name << endl;
    card.show(d.hand);
    cout << card.checkScore(d.hand) << endl;
    return 0;
}