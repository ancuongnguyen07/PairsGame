
/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'gameboard.hh'
 */

#include "gameboard.hh"
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include <math.h>

using namespace std;

GameBoard::GameBoard(QObject* parent):
    QGraphicsScene(parent),
    numOfRow_(0),
    numOfCol_(0)
{
    setSceneRect(0, 0, MAX_NUM_PAIRS * (CARD_WIDTH_ + MARGIN_),
                 MAX_NUM_PAIRS * (CARD_HEIGHT_ + MARGIN_));

    // Initializing in order not to re-initialize every time
    // a player replay
    timer_ = new QTimer(parent);
    time_ = new QTime(0,0,0);

    // After 1 second the timer_ emit signal timeout()
    connect(timer_, SIGNAL(timeout()), this, SLOT(showTime()));
}

GameBoard::~GameBoard()
{
    delete timer_;
    delete time_;
}

void GameBoard::addCardWidget(int row, int col, shared_ptr<Card> card){
    CardItem* Card = new CardItem(card, CARD_WIDTH_, CARD_HEIGHT_, 0);

    addItem(Card);
    Card->setPos(gridToPoint(row, col));   
}

void GameBoard::removeCardWidget(int row, int col){
    QPoint scenePos = gridToPointCenter(row, col);

    // Find the widget at the given point and remove it
    QGraphicsItem* toBeRemovedItem = itemAt(scenePos, QTransform());

    if (toBeRemovedItem != 0){
        removeItem(toBeRemovedItem);
        delete toBeRemovedItem;
    }
}

QPoint GameBoard::gridToPoint(int row, int col) const{
    int xCoor = MARGIN_ * col + (col + 1) * CARD_WIDTH_;
    int yCoor = MARGIN_ * row + (row + 1) * CARD_HEIGHT_;
    return QPoint(xCoor, yCoor);
}

QPoint GameBoard::gridToPointCenter(int row, int col) const{
    int xCoor = MARGIN_ * col + (col + 1) * CARD_WIDTH_ + CARD_WIDTH_ / 2;
    int yCoor = MARGIN_ * row + (row + 1) * CARD_HEIGHT_ + CARD_HEIGHT_ / 2;
    return QPoint(xCoor, yCoor);
}

void GameBoard::pointToGrid(QPoint &point, int &row, int &col){
    col = (point.x() - CARD_WIDTH_) / (MARGIN_ + CARD_WIDTH_);
    row = (point.y() - CARD_HEIGHT_) / (MARGIN_ + CARD_HEIGHT_);
}

CardItem *GameBoard::findCard(int row, int col) const
{
    QPoint cardPos = gridToPointCenter(row, col);
    // Card Widget at given coordinate
    return dynamic_cast<CardItem*>(itemAt(cardPos, QTransform()));
}


void GameBoard::mousePressEvent(QGraphicsSceneMouseEvent *event){
    QGraphicsScene::mousePressEvent(event);

    QPoint clickPos = event->scenePos().toPoint();
    if (clickPos.x() >= CARD_WIDTH_ and clickPos.x() <= MARGIN_ * numOfCol_ +
            (numOfCol_ + 1) * CARD_WIDTH_ and
            clickPos.y() >= CARD_HEIGHT_ and clickPos.y() <= MARGIN_ * numOfRow_ +
            (numOfRow_ + 1) * CARD_HEIGHT_){

        int x;
        int y;
        pointToGrid(clickPos, x, y);

        emit mouseClick(x, y);
    }
}

bool GameBoard::flipCard(int row, int col) const{
    CardItem* toBeFlippedCard = findCard(row, col);
    if (toBeFlippedCard == nullptr){
        return false;
    }

    toBeFlippedCard->flipCard();
    toBeFlippedCard->updateImage();
    return true;
}

void GameBoard::initializeClock(){
    timer_->start(TIME_INTERVAL_);
    digitalClockLabel_ = new QLabel();

    timer_->start();

    digitalClockLabel_->setFixedSize(CLOCK_WIDTH_, CLOCK_HEIGHT_);
    digitalClockLabel_->setStyleSheet("QLabel { background-color : green; "
                                      "color : white;}");
    digitalClockLabel_->setText(time_->toString("mm : ss"));
    digitalClockLabel_->move(100, digitalClockLabel_->height() + MARGIN_);
    digitalClockLabel_->setAlignment(Qt::AlignCenter);
    addWidget(digitalClockLabel_);
}

void GameBoard::showTime(){
    *time_ = time_->addSecs(1);
    digitalClockLabel_->setText(time_->toString("mm : ss"));
}

void GameBoard::initializeTurnLabel(string& playerName){
    playerTurnLabel_ = new QLabel();
    QPoint clockPos = digitalClockLabel_->pos();
    playerTurnLabel_->move(clockPos.x() + MARGIN_ + digitalClockLabel_->width(),
                           clockPos.y());
    playerTurnLabel_->setFixedSize(TURN_LABEL_WIDTH_, TURN_LABEL_HEIGHT_);
    playerTurnLabel_->setAlignment(Qt::AlignCenter);
    setPlayerTurn(playerName);
    addWidget(playerTurnLabel_);
}

void GameBoard::setPlayerTurn(string &playerName){

    playerTurnLabel_->setText(QString::fromStdString(playerName));
    playerTurnLabel_->setAlignment(Qt::AlignCenter);
}

void GameBoard::initializePlayerBox(vector<shared_ptr<Player>> &playerList){
    playerBox_ = new QComboBox();
    playerPoint_ = new QLabel();

    connect(playerBox_, SIGNAL(currentIndexChanged(int)), this, SLOT(showPoint(int)));

    for (shared_ptr<Player>& p : playerList){
        playerBox_->addItem(QString::fromStdString(p->getName()));
    }
    playerBox_->move(MARGIN_ + CARD_WIDTH_ / 2,
                     (numOfRow_ + 1) * (CARD_HEIGHT_ + MARGIN_));
    playerBox_->setEditable(false);
    addWidget(playerBox_);

    // POINTS OF PLAYER
    playerPoint_->setText(0);
    QPoint playerBoxPos = playerBox_->pos();
    playerPoint_->move(playerBoxPos.x() + playerBox_->width() + MARGIN_,
                       playerBoxPos.y() + playerBox_->heightMM() / 2);
    playerPoint_->setText(QString::number(0));
    addWidget(playerPoint_);
}

void GameBoard::showPoint(int index){
    emit signalShowPoint(index);
}

void GameBoard::pauseGame()
{
    timer_->stop();
    QMessageBox::information(0, "Attention!!!", "Game is paused",
                                           QMessageBox::Ok);
    timer_->start(TIME_INTERVAL_);
}

void GameBoard::initializePauseBt(){
    pauseButton_ = new QPushButton();
    pauseButton_->setText("Pause");
    QPoint playerBoxPos = playerBox_->pos();
    pauseButton_->move(playerBoxPos.x(), playerBox_->y() + MARGIN_
                       + (pauseButton_->heightMM() + CARD_HEIGHT_) / 2);
    addWidget(pauseButton_);

    connect(pauseButton_, SIGNAL(clicked()), this, SLOT(pauseGame()));
}

void GameBoard::setPointDisplayed(int points){
    playerPoint_->setText(QString::number(points));
}

string GameBoard::getPlayerNameBox(){
    return playerBox_->currentText().toStdString();
}

void GameBoard::switchClock(bool on)
{
    if (on){
        timer_->start(1000);
        return;
    }
    timer_->stop();
}

void GameBoard::moveCardDock(CardItem *card, int numOfCards)
{
    int newY = playerBox_->pos().y() + MARGIN_ + playerBox_->heightMM() / 2;
    int newX = playerBox_->pos().x() + numOfCards * (CARD_WIDTH_ + MARGIN_);
    card->setPos(newX, newY);
    card->setOpenCard();
    card->updateImage();
    card->show();
}

void GameBoard::hideCard(int row, int col)
{
    CardItem* toBeHidenCard = findCard(row, col);
    if (toBeHidenCard == nullptr){
        return;
    }
    toBeHidenCard->hide();
}

void GameBoard::hideDockCard()
{
    for (int i = 0 ; i <= (numOfRow_ * numOfRow_) / 2; ++i){
        int newY = playerBox_->pos().y() + MARGIN_ + playerBox_->heightMM();
        int newX = playerBox_->pos().x() + i * (CARD_WIDTH_ + MARGIN_);
        QGraphicsItem* toBeHiden = itemAt(newX + CARD_WIDTH_ / 2,
                                     newY + CARD_HEIGHT_ /  2,
                                          QTransform());
        if (toBeHiden != nullptr){
            toBeHiden->hide();
        }
    }
}

