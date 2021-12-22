/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'gameboardwindow.hh'
 */

#include "gameboardwindow.hh"
#include "ui_gameboardwindow.h"

#include <QLayout>

GameBoardWindow::GameBoardWindow(GameBoard &board, GameEngine &eng, QWidget *parent) :
    QWidget(parent),
    eng_(eng),
    ui_(new Ui::GameBoardWindow),
    view_(this),
    board_(board)
{
    ui_->setupUi(this);

    connect(&board_, SIGNAL(mouseClick(int, int)), &eng_,
                     SLOT(flipAndCheckCards(int, int)));

}

GameBoardWindow::~GameBoardWindow()
{
    delete ui_;
}

void GameBoardWindow::startGame()
{
    eng_.initilizeGameBoard();
    setActiveScene();
    this->show();
}

void GameBoardWindow::setActiveScene()
{
    view_.setScene(&board_);
    view_.show();
    view_.setAlignment(Qt::AlignCenter);
    setFixedSize(view_.size());
}
