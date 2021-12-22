/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Description:
 * The pre-information form where player can type the amount of cards and players
 * It has the 'start' button where the player begin the game after filling
 * information validly
 *
 */
#ifndef INFOFORM_HH
#define INFOFORM_HH

#include <QWidget>
#include <vector>
#include <string>

namespace Ui {
class InfoForm;
}

class InfoForm : public QWidget
{
    Q_OBJECT

public:
    explicit InfoForm(QWidget *parent = nullptr);
    ~InfoForm();

    // reset form
    void reset();

signals:
    // send the number of cards to game engine
    void sendNumOfCards(unsigned int num);

    // send the number of players to game engine
    void sendNumOfPlayers(unsigned int num);

    // send a vector of players' name
    void sendPlayersName(std::vector<std::string>);

    // show game board
    void showGameBoard();

private slots:
    // when a player clicked startButton, this slot also
    // emit signals to transfer data to gameEngine
    void on_startButton_clicked();

    // add the number of objects in combobox corresponding
    // to the number chosen by a player
    void on_numOfPlayersSpinBox_valueChanged(int numOfPlayers);

    // replace the original name like 'Player 1', 'Player 2', ...
    // by the name typed by the player
    void addNewNameInfo();

    // hide the label for announcing the failure of adding name
    void hideAddingNameLb();

private:
    Ui::InfoForm *ui_;
    const int MINIMUM_PLAYERS = 2;

    // get players' name from combobox
    std::vector<std::string> getPlayerNames();

    // show announcement/info through label
    void showInfo(const std::string &text, bool error = false);

    const int DELAY_TIME = 1000; // delay time for showing announcement
};

#endif // INFOFORM_HH
