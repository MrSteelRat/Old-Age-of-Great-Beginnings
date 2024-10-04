#include "gamescreen.h"
#include "ui_gamescreen.h"

GameScreen::GameScreen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::GameScreen)
{
    ui->setupUi(this);
}

GameScreen::~GameScreen()
{
    delete ui;
}

void GameScreen::on_Rotate_Right_Btn_clicked()
{

}

