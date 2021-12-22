/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'gameengine.hh'
 */

#include "gameengine.hh"
#include <QTimer>

#include <iostream>
#include <QMessageBox>
#include <QString>

using namespace std;

GameEngine::GameEngine(GameBoard& gameBoard):
    QObject(0),
    CARD_NUM_(2), // just for testing
    PLAYER_NUM_(2), // just for testing
    numOfUncovereds_(0),
    totalUncoveredPairs_(0),
    turnIndex_(0),
    graphicalGameboard_(gameBoard)
{
    randomGenerator_.seed(time(NULL));

    connect(&graphicalGameboard_, SIGNAL(signalShowPoint(int)),
                                        this, SLOT(showPoints(int)));

    //initilizeGameBoard();
}

int GameEngine::smallerFactor(int product){
    int smallFactor = 1;
    for (int i = 2; i * i <= product; ++i){
        if (product % i == 0){
            smallFactor = i;
        }
    }
    return smallFactor;
}

void GameEngine::shuffleVector(vector<int> &numList){
    unsigned int n = numList.size();
    uniform_int_distribution<int> distribution(0, n - 1);
    for (unsigned int i = 0; i < n; ++i){
        unsigned newIndex = distribution(randomGenerator_);
        int temp = numList[i];
        numList[i] = numList[newIndex];
        numList[newIndex] = temp;
    }
}

shared_ptr<Card> GameEngine::cardAt(int row, int col) const{
    if (row >= 0 and row <= graphicalGameboard_.numOfRow_ and
        col >= 0 and col <= graphicalGameboard_.numOfCol_){
        return cards_.at(row).at(col);
    }
    return nullptr;
}

void GameEngine::initializeCardGrid(){
    int smallFactor = smallerFactor(CARD_NUM_); // number of rows
    int bigFactor = CARD_NUM_ / smallFactor; // number of columns
    graphicalGameboard_.numOfCol_ = bigFactor;
    graphicalGameboard_.numOfRow_ = smallFactor;
    int numOfPairs = CARD_NUM_ / 2;

    // create a vector containing all distinct index
    vector<int> indexList;
    for (unsigned int i = 0; i < MAX_NUM_PAIRS; ++i){
        indexList.push_back(i);
    }
    shuffleVector(indexList); // was shuffled
    // create a vector containing index will be picked for a card
    vector<int> pickedIndexList;
    for (int i = 0; i < numOfPairs; ++i){
        pickedIndexList.push_back(indexList[i]);
        pickedIndexList.push_back(indexList[i]);
    }
    shuffleVector(pickedIndexList);

    unsigned int k = 0; // the order of picking index
    for (int row = 0; row < smallFactor; row++){
        vector<shared_ptr<Card>> rowCardsVector;
        for (int col = 0; col < bigFactor; col++){
            int indexOfImage = pickedIndexList[k++];
            shared_ptr<Card> newCard = make_shared<Card>(row, col, indexOfImage);
            rowCardsVector.push_back(newCard);
            // Add to game board
            graphicalGameboard_.addCardWidget(row, col, newCard);
        }
        cards_.push_back(rowCardsVector);
    }
}

void GameEngine::initilizeGameBoard(){
    graphicalGameboard_.clear();
    std::cout << "x" << std::endl;
    // ================== DISPLAY TIMER AND TURN
    graphicalGameboard_.initializeClock();
    string playerInTurn = players_.at(turnIndex_)->getName();
    graphicalGameboard_.initializeTurnLabel(playerInTurn);

    // ================== DISPLAY CARD GRID
    initializeCardGrid();

    // ================== DISPLAY POINTS OF PLAYERS
    graphicalGameboard_.initializePlayerBox(players_);

    // ================== DISPLAY 'PAUSE' AND 'BACK' BUTTON
    graphicalGameboard_.initializePauseBt();
}

void GameEngine::initializePlayers(std::vector<string> &playersName)
{
    for (string name : playersName){
        players_.push_back(make_shared<Player>(name));
    }
}


void GameEngine::flipAndCheckCards(int row, int col){
    if (continueFlip_){
        // Two cards have the same positions
        if (numOfUncovereds_ > 0 and row == twoUncoveredCards[0]->getXCoordinate()
                and col == twoUncoveredCards[0]->getYCoordinate()){

            return;
        }
        if (not graphicalGameboard_.flipCard(row, col)){
            // if the card is already removed
            return;
        }
        twoUncoveredCards[numOfUncovereds_ ++]= cardAt(row, col);
        if (numOfUncovereds_  == 2){

            numOfUncovereds_ = 0; // reset to 0
            shared_ptr<Card> card1 = twoUncoveredCards[0];
            shared_ptr<Card> card2 = twoUncoveredCards[1];

            // Two cards are identical
            if (card1->getIndex() == card2->getIndex()){
                shared_ptr<Player> inTurnPlayer = players_.at(turnIndex_);
                // plus 1 point for 2 identical cards
                inTurnPlayer->plusPoint();
                totalUncoveredPairs_ ++;

                // add card to obtained list of player
                inTurnPlayer->addPlayerCard(graphicalGameboard_.findCard(
                                                card2->getXCoordinate(),
                                                card2->getYCoordinate()));

                // remove one card
                graphicalGameboard_.removeCardWidget(
                            card1->getXCoordinate(), card1->getYCoordinate());
                // hide one card
                graphicalGameboard_.hideCard(card2->getXCoordinate(),
                                             card2->getYCoordinate());

                // update points on the screen
                if (inTurnPlayer->getName() == graphicalGameboard_.getPlayerNameBox()){
                    showPoints(turnIndex_);
                }
            }
            else{
                continueFlip_ = false;                
                updateTurn();
                QTimer::singleShot(DELAY_TIME_, this, SLOT(rehideCards()));
            }
        }
    }

    // check if all total cards are uncovered or not
    // if true then ask player want to replay or quit game
    if  (totalUncoveredPairs_ == CARD_NUM_ / 2){
        // The game should end
        vector<shared_ptr<Player>> maxPlayers = greatestPlayers();
        int doReplay = wantReplay(maxPlayers);
        if (doReplay == QMessageBox::Yes){
            // replay, the same players, same number of cards
            // only the order and figure of cards are changed
            reset();
            initilizeGameBoard();
        }
        else{
            // emit back to main menu
            reset();
            players_.clear();
            emit backMainMenu();
        }
    }
}

void GameEngine::updateTurn(){
    // change turn
    turnIndex_ = (turnIndex_ + 1) % players_.size();
    // name of the player in turn at this moment
    string newTurn = players_.at(turnIndex_)->getName();
    graphicalGameboard_.setPlayerTurn(newTurn);
}

void GameEngine::rehideCards(){
    shared_ptr<Card> card1 = twoUncoveredCards[0];
    shared_ptr<Card> card2 = twoUncoveredCards[1];
    graphicalGameboard_.flipCard(card1->getXCoordinate(), card1->getYCoordinate());
    graphicalGameboard_.flipCard(card2->getXCoordinate(), card2->getYCoordinate());
    continueFlip_ = true;
}

void GameEngine::showPoints(int index){
    shared_ptr<Player> selectedPlayer = players_.at(index);
    int point = selectedPlayer->getPoint();
    graphicalGameboard_.setPointDisplayed(point);

    graphicalGameboard_.hideDockCard();

    // Show which cards a player have achieved
    int n = selectedPlayer->cardsObtained_.size();
    for (int i = 0; i < n; ++i){
        CardItem* card = selectedPlayer->cardsObtained_.at(i);
        graphicalGameboard_.moveCardDock(card, i);
    }


}

void GameEngine::receiveNumOfCards(unsigned int num)
{
    CARD_NUM_ = num;
}

void GameEngine::receiveNumOfPlayers(unsigned int num)
{
    PLAYER_NUM_ = num;
}

void GameEngine::receivePlayersName(std::vector<string> playersName)
{
    initializePlayers(playersName);
}

vector<shared_ptr<Player>> GameEngine::greatestPlayers(){
    int maxPoint = 0;
    vector<shared_ptr<Player>> maxPlayers;
    for (shared_ptr<Player> p : players_){
        if (p->getPoint() > maxPoint){
            maxPoint = p->getPoint();
        }
    }
    for (shared_ptr<Player> p : players_){
        if (p->getPoint() == maxPoint){
            maxPlayers.push_back(p);
        }
    }
    return maxPlayers;
}

int GameEngine::wantReplay(vector<shared_ptr<Player>> greatestPlayers){
    graphicalGameboard_.switchClock(); // pause the clock
    string namePlayers = "";
    for (shared_ptr<Player> p : greatestPlayers){
        namePlayers += " " + p->getName();
    }
    string result = "won";
    if (greatestPlayers.size() > 1){
        result = "tied";
    }
    string announcement = "The player(s)" + namePlayers + " " + result
            + " with " + to_string(greatestPlayers.at(0)->getPoint())
            + " point(s)" + "\nDo you want to replay ?";
    return QMessageBox::question(0, "Congratulation!!!",
                                 QString::fromStdString(announcement),
                                 QMessageBox::Yes, QMessageBox::No);
}

void GameEngine::resetPlayer()
{
    for (auto p : players_){
        p->cardsObtained_.clear();
        p->resetPoint();
    }
}

void GameEngine::reset(){
    totalUncoveredPairs_ = 0; // reset to 0
    cards_.clear();
    turnIndex_ = 0;
    resetPlayer();
}
