/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * MainMenu window which is shown firstly when the program starts
 * It has two buttons 'start'-> bring the pre-informaiton form where
 * player can type the amount of cards and players. 'quit' button ->
 * exit the program
 *
 */
#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include "gameboard.hh"
#include "gameengine.hh"
#include "infoform.hh"
#include "gameboardwindow.hh"

#include <QMainWindow>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(GameBoard &gameBoard, GameEngine &eng, QWidget *parent = nullptr);
    ~MainWindow();

signals:
    // start the game board
    void startGameBoardWindow();

private slots:
    // show the InfoForm when a player clicked startButton
    void on_startButton_clicked();

    // emitted when signal 'backMainMenu' activated in gameEngine
    // bring player to main menu - hide game board
    void goMainMenu();

private:
    Ui::MainWindow* ui_;
    InfoForm* form_;
    // QGraphicsView view_;
    GameBoardWindow* boardWindow_;

};
#endif // MAINWINDOW_HH
