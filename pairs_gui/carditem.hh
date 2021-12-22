/*
 * Card widget class
 *
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * The card widget is showed in the gameboard
 *
 */

#ifndef CARDITEM_HH
#define CARDITEM_HH

#include "card.hh"

#include <QGraphicsPixmapItem>
#include <memory>
#include <vector>
#include <string>

using namespace  std;

const int MAX_NUM_PAIRS = 10;

class CardItem : public QGraphicsPixmapItem
{
public:
    CardItem(shared_ptr<Card> card, int width, int height,
             QGraphicsItem* parent);

    // update figure of the front of the card when its status is changed
    void updateImage();

    // change the status of the card flipped-unflipped
    void flipCard();

    bool isFlipped() const;

    // make the status of the card is flipped
    void setOpenCard();
    
private:
    const int WIDTH_;
    const int HEIGHT_;

    bool isFlipped_;
    
    shared_ptr<Card> cardPt_;

};

#endif // CARDITEM_HH
