/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * The game board class
 * Showing, updating graphical items in the gameboard such as grid of cards, digital clock
 * label of player in turn, combobox and deck for player's points and 'pause' button
 */
#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "card.hh"
#include "carditem.hh"
#include "player.hh"

#include <QGraphicsScene>
#include <QPushButton>
#include <QComboBox>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include <vector>
#include <string>

using namespace std;

class GameBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    GameBoard(QObject* parent = nullptr);
    virtual ~GameBoard();
    // add new card widget in the given coordinate
    void addCardWidget(int row, int col, shared_ptr<Card> card);

    // remove card widget in the given coordinate
    void removeCardWidget(int row, int col);

    // flip card
    bool flipCard(int row, int col) const;

    // Initializing a digital clock
    void initializeClock();

    // Initializing label displaying the playerTurn
    void initializeTurnLabel(string& playerName);

    // Initializing Pause and BackToMainMenu button
    void initializePauseBt();

    // Initializing player combobox showing points
    // corresponding to each player
    void initializePlayerBox(vector<shared_ptr<Player>>& playerList);

    // set player's name in turn
    void setPlayerTurn(string& playerName);

    // set point to be displayed
    void setPointDisplayed(int points);

    // get the player's name which is chosen in the combobox
    string getPlayerNameBox();

    // pause-continue the digital clock of the game board
    void switchClock(bool on = false);

    // move card to player's dock from starting row-col coordinate
    void moveCardDock(CardItem* card, int numOfCards);

    // hide the card achieved by player from the grid
    void hideCard(int row, int col);

    // hide all cards from the pre-selected-player's dock
    void hideDockCard();

    // find card with given row and col
    CardItem* findCard(int row, int col) const;

    int numOfRow_;
    int numOfCol_;

signals:
    // When user clicked on the card
    void mouseClick(int x, int y);

    // emit signal for GameEngine showing point of a player
    // is chosen in combobox
    void signalShowPoint(int index);

private slots:
    // run the digital clock, emiited when signal timeout
    void showTime();

    // show the point of player when a player's name is
    // chosen in the combobox
    void showPoint(int index);

    // pause game
    void pauseGame();

protected:
    // Handler for mouse click events
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;

private:
    const int TIME_INTERVAL_ = 1000; // 1 second
    // margin between cards
    const int MARGIN_ = 20;
    const int CARD_WIDTH_ = 40;
    const int CARD_HEIGHT_ = 70;

    // Timer digital clock
    QLabel* digitalClockLabel_;
    QTimer* timer_;
    QTime* time_;
    const int CLOCK_WIDTH_ = 80;
    const int CLOCK_HEIGHT_ = 20;

    // Text displaying turn of players
    QLabel* playerTurnLabel_;
    const int TURN_LABEL_WIDTH_ = 200;
    const int TURN_LABEL_HEIGHT_ = 20;

    // comboBox showing player names corresponding to their points
    QComboBox* playerBox_;
    QLabel* playerPoint_;

    // Pause button
    QPushButton* pauseButton_;

    // Timer for moving cards
    QTimer* cardTimer_;

    // convert index of column and row to x,y_coordinate
    QPoint gridToPoint(int row, int col) const;

    // convert index of column and row to x,y_coordinate
    // at the center of the grid square
    QPoint gridToPointCenter(int row, int col) const;

    // convert x,y_coordinate to index of row and column
    void pointToGrid(QPoint& point, int& row, int& col);

};

#endif // GAMEBOARD_HH
