/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'player.hh'
 */

#include "player.hh"

Player::Player(string name): name_(name), points_(0)
{

}

int Player::getPoint() const
{
    return points_;
}

string Player::getName() const{
    return name_;
}

void Player::plusPoint(){
    points_ ++;
}

void Player::addPlayerCard(CardItem *obtainedCard)
{
    cardsObtained_.push_back(obtainedCard);
}

int Player::getNumOfCards() const
{
    return cardsObtained_.size();
}

void Player::resetPoint()
{
    points_ = 0;
}



