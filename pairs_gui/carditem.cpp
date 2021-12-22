
/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'carditem.hh'
 */

#include "carditem.hh"

#include <QPixmap>
#include <iostream>

const vector<string> IMAGE_NAMES= {"apple", "bananas", "orange",
                                  "eggplant", "grapes", "cherries",
                                  "pear", "tomato", "strawberry",
                                  "watermelon"};


const string BACK_IMAGE = "back";
const string PREFIX_ = ":/Resources/";
const string SUFFIX_ = ".png";

CardItem::CardItem(shared_ptr<Card> card, int width, int height,
                   QGraphicsItem* parent):
    QGraphicsPixmapItem(parent),
    WIDTH_(width),
    HEIGHT_(height),
    isFlipped_(true),
    cardPt_(card)
{

    updateImage();
}

void CardItem::updateImage(){
    int indexOfImage = cardPt_->getIndex();

    // load the image and scale to the correct size
    string nameOfImage = IMAGE_NAMES[indexOfImage];
    if (isFlipped_){
        nameOfImage = BACK_IMAGE;
    }
    QPixmap map(QString::fromStdString(PREFIX_ +
                                       nameOfImage + SUFFIX_));
    setPixmap(map.scaled(WIDTH_, HEIGHT_));
}

void CardItem::flipCard(){
    isFlipped_ = not isFlipped_;
}

bool CardItem::isFlipped() const{
    return isFlipped_;
}

void CardItem::setOpenCard()
{
    isFlipped_ = false;
}
