/*
 * Card class
 *
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * This card class is mainly used for checking if two cards are identical or not
 * Saving row-col coordinate - coordinate in the 2-dimensional matrix
 * (different from the x-y coordinate in the gameboard)
 *
 */
#ifndef CARD_HH
#define CARD_HH

class Card
{
public:
    Card(int xCoordinate, int yCoordinate, int indexOfImage);

    int getXCoordinate() const;
    int getYCoordinate() const;
    int getIndex() const;

private:
    int xCoordinate_;
    int yCoordinate_;

    // index of image in enum 'IMAGE_ITEM'
    int index_;

    // card item pt
};

#endif // CARD_HH
