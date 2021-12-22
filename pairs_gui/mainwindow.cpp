/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'mainwindow.hh'
 */

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(GameBoard &gameBoard, GameEngine &eng, QWidget *parent)
    : QMainWindow(parent),
    ui_(new Ui::MainWindow),
    form_(new InfoForm),
    boardWindow_(new GameBoardWindow(gameBoard, eng))
{
    // setActiveScene(scene);

    ui_->setupUi(this);

    connect(form_, SIGNAL(sendNumOfCards(unsigned int)), &(boardWindow_->eng_),
            SLOT(receiveNumOfCards(unsigned int)));
    connect(form_, SIGNAL(sendNumOfPlayers(unsigned int)), &(boardWindow_->eng_),
            SLOT(receiveNumOfPlayers(unsigned int)));
    connect(form_, SIGNAL(sendPlayersName(std::vector<std::string>)), &(boardWindow_->eng_),
            SLOT(receivePlayersName(std::vector<std::string>)));
    connect(form_, SIGNAL(showGameBoard()), boardWindow_, SLOT(startGame()));
    connect(&(boardWindow_->eng_), SIGNAL(backMainMenu()), this, SLOT(goMainMenu()));
    connect(ui_->quitButton, SIGNAL(clicked()), this, SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui_;
}


void MainWindow::on_startButton_clicked()
{
    form_->show();
    this->hide();
}

void MainWindow::goMainMenu()
{
    form_->reset();
    boardWindow_->hide();
    this->show();
}


