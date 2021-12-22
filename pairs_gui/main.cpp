/*
 * Flipping card game
 *
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * The detailed instructions how to play and what the program does in the file
 * 'intructions.txt'.
 * This file is used to intialize fundamental components of the program
 * and then statrt the main window
 */

#include "mainwindow.hh"

#include <QApplication>
#include <QGraphicsScene>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameBoard board;
    GameEngine eng(board);
    MainWindow w(board, eng);

    w.show();
    return a.exec();
}
