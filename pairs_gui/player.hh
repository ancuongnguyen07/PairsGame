/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * A Player Class which has name (string) and points (int) as private attribute
 * it is used to control the name, the points and which cards are achieved by this object
 *
 */
#ifndef PLAYER_HH
#define PLAYER_HH

#include "carditem.hh"

#include <string>
#include <vector>

using namespace std;

class Player
{
public:
    Player(string name);

    int getPoint() const;
    string getName() const;

    // increase 1 point when a player found a pair
    void plusPoint();

    // add card into obtained list
    void addPlayerCard(CardItem* obtainedCard);

    // return number of cards obtained
    int getNumOfCards() const;

    // vector of card items obtained by the player
    vector<CardItem*> cardsObtained_;

    // reset point
    void resetPoint();
private:
    string name_;
    int points_;

};

#endif // PLAYER_HH
