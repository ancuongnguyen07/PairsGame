/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * The game engine class
 * Control and is responsible for all game-flow of the program
 * Checking the game ends or not, add point for players, checking invalid mouseclick
 * Deciding which window should hide or show
 *
 */
#ifndef GAMEENGINE_HH
#define GAMEENGINE_HH

#include "gameboard.hh"
#include "card.hh"
#include "carditem.hh"
#include "player.hh"

#include <QObject>
#include <vector>
#include <random>
#include <map>
#include <QGraphicsScene>

using namespace std;

class GameEngine : public QObject
{
    Q_OBJECT

public:
    GameEngine(GameBoard& gameBoard);
    virtual ~GameEngine() {};

    // Initilizing a board for showing game status
    void initilizeGameBoard();

    // initialize a list of player objects
    void initializePlayers(std::vector<std::string> &playersName);

signals:
    // emitted when a player click back to main menu
    void backMainMenu();

private slots:
    // Flip card when a player clicked on it
    // and check if two cards are identical or not
    // if they are identical
    void flipAndCheckCards(int row, int col);

    // re-hide the cards
    void rehideCards();

    // show point with chosen player's name
    void showPoints(int index);

public slots:
    // receive number of cards from InfoForm
    void receiveNumOfCards(unsigned int num);

    // receive number of players from InfoForm
    void receiveNumOfPlayers(unsigned int num);

    // receive a vector of players'name
    void receivePlayersName(std::vector<std::string> playersName);
private:
    // Random number generator
    default_random_engine randomGenerator_;

    // delay time for re-hiding the cards
    unsigned int DELAY_TIME_ = 2000;

    // number of cards
    unsigned int CARD_NUM_;

    // number of players
    unsigned int PLAYER_NUM_;

    // number of uncovered cards at the same time
    unsigned int numOfUncovereds_;

    // total number of discovered cards
    unsigned int totalUncoveredPairs_;

    // flag for continuing fliping cards
    bool continueFlip_ = true;

    // A board of cards
    vector<vector<shared_ptr<Card>>> cards_;

    // vector containing player objects
    vector<shared_ptr<Player>> players_;

    // map containing players in order as in leaderboard


    // the number indicate the pos of player in the
    // vector 'players_'
    unsigned int turnIndex_;


    // array of QPoints containing two cards are uncovered
    shared_ptr<Card> twoUncoveredCards[2];

    // Drawing area to show the game status
    GameBoard& graphicalGameboard_;

    // Initializing a grid of cards
    void initializeCardGrid();

    // Calculate two factors which their product is the number of cards
    // Reference from the template of 'pairs' exercise in week 4
    int smallerFactor(int product);

    // shuffle elements in a vector of int
    void shuffleVector(vector<int>& numList);    

    // return the cardPt at row x and col y
    shared_ptr<Card> cardAt(int row, int col) const;

    // update turn
    void updateTurn();

    // find the player with highest point
    vector<shared_ptr<Player>> greatestPlayers();

    // announce the result of the game and ask
    // if the player want to replay or not
    int wantReplay(vector<shared_ptr<Player>> greatestPlayers);

    // reset cardItem obtained of all players to restart the game
    void resetPlayer();

    // reset gamePlay: cards, cards obtained by players, uncoveredCards
    void reset();

};

#endif // GAMEENGINE_HH
