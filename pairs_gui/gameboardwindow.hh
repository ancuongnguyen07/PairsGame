/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * The game board window class
 * As a container of GameBoard class (gameboard.hh)
 */
#ifndef GAMEBOARDWINDOW_HH
#define GAMEBOARDWINDOW_HH

#include "gameboard.hh"
#include "gameengine.hh"

#include <QWidget>
#include <QGraphicsView>

namespace Ui {
class GameBoardWindow;
}

class GameBoardWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameBoardWindow(GameBoard &gameBoard, GameEngine &eng, QWidget *parent = nullptr);
    ~GameBoardWindow();

    GameEngine& eng_;

public slots:
    // show the gameBoard when a player finished fill
    // pre-information and clicked startButton
    void startGame();

private:
    Ui::GameBoardWindow *ui_;
    QGraphicsView view_;
    GameBoard& board_;

    void setActiveScene(); // decide which scene should be showed or hiden
};

#endif // GAMEBOARDWINDOW_HH
