#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDesktopServices>
#include <QUrl>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QFile>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QProcess process;

private slots:
    void on_Exit_triggered();

    void on_Github_triggered();

    void on_DownloadBtn_clicked();

    void on_Install_bar_valueChanged(int value, int valueTotal);

    void on_InstallBtn_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
