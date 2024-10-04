#include "mainmenugame.h"
#include "ui_mainmenugame.h"

MainMenuGame::MainMenuGame(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainMenuGame)
{
    ui->setupUi(this);
}

MainMenuGame::~MainMenuGame()
{
    delete ui;
}

void MainMenuGame::on_Exit_Btn_clicked()
{
    close();
}

