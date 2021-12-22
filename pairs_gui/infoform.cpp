/*
 * Author : An Cuong Nguyen
 * Email: cuong.nguyen@tuni.fi
 * Student Number: 050358715
 *
 * Implementation of 'infoform.hh'
 */

#include "infoform.hh"
#include "ui_infoform.h"

#include <QMessageBox>
#include <QLineEdit>
#include <QTimer>
#include <QString>
#include <iostream>

InfoForm::InfoForm(QWidget *parent) :
    QWidget(parent),
    ui_(new Ui::InfoForm)
{
    ui_->setupUi(this);
    ui_->infoLabel->hide();
    ui_->playersNameBox->setMaxCount(MINIMUM_PLAYERS);
    connect(ui_->playersNameBox->lineEdit(), SIGNAL(editingFinished()),
            this, SLOT(addNewNameInfo()));
}

InfoForm::~InfoForm()
{
    delete ui_;
}

void InfoForm::reset()
{
    ui_->playersNameBox->clear();
    ui_->numOfCardsSpinBox->clear();
    ui_->numOfPlayersSpinBox->clear();
}


void InfoForm::on_startButton_clicked()
{
    if (ui_->playersNameBox->count() != ui_->playersNameBox->maxCount()){
        std::cout << ui_->playersNameBox->count() << std::endl << ui_->playersNameBox->maxCount();
        showInfo("All players have to be named", true);
        QTimer::singleShot(DELAY_TIME * 2, this, SLOT(hideAddingNameLb()));
        return;
    }
    emit sendNumOfCards((unsigned int) 2 * ui_->numOfCardsSpinBox->value());
    emit sendNumOfPlayers((unsigned int) ui_->numOfPlayersSpinBox->value());
    emit sendPlayersName(getPlayerNames());
    emit showGameBoard();
    this->hide();
}

void InfoForm::on_numOfPlayersSpinBox_valueChanged(int numOfPlayers)
{
    int currentMax = ui_->playersNameBox->maxCount();
    if (numOfPlayers < currentMax){
        ui_->playersNameBox->clear();
    }
    ui_->playersNameBox->setMaxCount(numOfPlayers);
}


void InfoForm::addNewNameInfo(){
    std::string currentName = ui_->playersNameBox->currentText().toStdString();

    if (currentName.empty()){
        return;
    }
    showInfo("The name is added successfully");
    QTimer::singleShot(DELAY_TIME, this, SLOT(hideAddingNameLb()));
}

std::vector<std::string> InfoForm::getPlayerNames(){
    std::vector<std::string> playerNamesList;
    QComboBox *namesBox = ui_->playersNameBox;
    for (int i = 0; i < namesBox->count(); ++i){
        playerNamesList.push_back(namesBox->itemText(i).toStdString());
    }
    return playerNamesList;
}

void InfoForm::hideAddingNameLb(){
    ui_->infoLabel->hide();
}

void InfoForm::showInfo(const std::string &text, bool error){
    if (error){
        ui_->infoLabel->setStyleSheet("QLabel {color : red;}");
    }
    else{
        ui_->infoLabel->setStyleSheet("QLabel {color : green;}");
    }
    ui_->infoLabel->setText(QString::fromStdString(text));
    ui_->infoLabel->show();
}


