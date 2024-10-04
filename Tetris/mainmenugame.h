#ifndef MAINMENUGAME_H
#define MAINMENUGAME_H

#include <QDialog>

namespace Ui {
class MainMenuGame;
}

class MainMenuGame : public QDialog
{
    Q_OBJECT

public:
    explicit MainMenuGame(QWidget *parent = nullptr);
    ~MainMenuGame();

private slots:
    void on_Exit_Btn_clicked();

private:
    Ui::MainMenuGame *ui;
};

#endif // MAINMENUGAME_H
