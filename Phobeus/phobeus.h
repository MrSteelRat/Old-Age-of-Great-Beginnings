#ifndef PHOBEUS_H
#define PHOBEUS_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QUrl>
#include <QDesktopServices>

QT_BEGIN_NAMESPACE
namespace Ui { class Phobeus; }
QT_END_NAMESPACE

class Phobeus : public QMainWindow

{
    Q_OBJECT

public:
    Phobeus(QWidget *parent = nullptr);
    ~Phobeus();

private slots:
    void on_actionOpen_triggered();

    void on_actionInfo_triggered();

    void on_actionExit_triggered();

private:
    Ui::Phobeus *ui;
    QLabel* imageLabel;
};

#endif // PHOBEUS_H
