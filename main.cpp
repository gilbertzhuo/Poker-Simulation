#include <iostream>
#include <vector>
#include "Cards.h"
#include <thread>
using namespace std;

struct user
{
    //Name of the user
    string name;
    //Cards on hand
    vector<int> hand;
    //Card Ranking
    string state;
    int score = 0;
};

void thread_task(Cards &c, user &a);
void player_stats(vector<user> &players);
void winner(vector<user> &champion);

int main()
{
    //Initialize a deck
    int num = 0;
    Cards card;
    while (num == 0)
    {
        user a = {"Gilbert Zhuo"}, b = {"player_b"}, c = {"player_c"}, d = {"player_d"};
        //Initializing 4 player as thread
        thread player_a(thread_task, ref(card), ref(a));
        thread player_b(thread_task, ref(card), ref(b));
        thread player_c(thread_task, ref(card), ref(c));
        thread player_d(thread_task, ref(card), ref(d));
        //Joining thread to main
        player_a.join();
        player_b.join();
        player_c.join();
        player_d.join();
        //Store the user data into vector
        vector<user> players = {a, b, c, d};
        //Output the names and the cards
        player_stats(players);
        //Find out the winner
        winner(players);
        //Swap a new deck
        card.reset();
        cout << "Do you wish to continue?\nINPUT 0 to continue :>" << endl;
        cin >> num;
        //Exit Loop for input other than 0
        if (cin.fail())
        {
            break;
        }
    }

    return 0;
}

void thread_task(Cards &c, user &a)
{
    //5 cards to the player
    a.hand = c.distribute();
    //Checks the score of the card
    a.score = c.checkScore(a.hand).first;
    //Check Card ranking
    a.state = c.checkScore(a.hand).second;
}
void player_stats(vector<user> &players)
{
    int size = players.size();
    for (int i = 0; i < size; ++i)
    {

        cout << "------------------\n"
             << players[i].name << "\n"
             << players[i].score << "\n"
             << players[i].state << endl;
    }
}
void winner(vector<user> &champion)
{
    int max_score = 0;
    int max_i = 0;
    int size = champion.size();
    for (int i = 0; i < size; ++i)
    {
        if (max_score < champion[i].score)
        {
            max_score = champion[i].score;
            max_i = i;
        }
    }
    cout << "************\n"
         << "***WINNER***\n"
         << "************" << endl
         << champion[max_i].name << "\nCard Ranking: " << champion[max_i].state << "\nScore: " << champion[max_i].score << "\n"
         << endl;
}