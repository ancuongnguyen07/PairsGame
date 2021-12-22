/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'card.hh'
 */

#include "card.hh"

Card::Card(int xCoordinate, int yCoordinate, int indexOfImage):
    xCoordinate_(xCoordinate),
    yCoordinate_(yCoordinate),
    index_(indexOfImage)
{

}

int Card::getXCoordinate() const{
    return xCoordinate_;
}

int Card::getYCoordinate() const{
    return yCoordinate_;
}

int Card::getIndex() const{
    return index_;
}


