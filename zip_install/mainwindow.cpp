#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Exit_triggered()
{
    close();
}

void MainWindow::on_Github_triggered()
{
    QDesktopServices::openUrl(QUrl("https://github.com/MrSteelRat", QUrl::TolerantMode));
}

void MainWindow::on_DownloadBtn_clicked()
{
    QString fileUrl = "https://www.7-zip.org/a/7z2301-x64.exe";
    QString fileName = "7z2301-x64.exe";

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl(fileUrl));

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::downloadProgress, this, &MainWindow::on_Install_bar_valueChanged);

    connect(reply, &QNetworkReply::finished, [this, reply, fileName]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
            }
        }
        reply->deleteLater();

        // Обнуляем значение прогресса по завершению загрузки
        ui->Install_bar->setValue(0);
    });
}

void MainWindow::on_Install_bar_valueChanged(int value, int valueTotal)
{
    int progress = static_cast<int>((value * 100) / valueTotal);

    ui->Install_bar->setValue(progress);
}

void MainWindow::on_InstallBtn_clicked()
{
    QString fileName = "7z2301-x64.exe";

    // Формируем путь к исполняемому файлу
    QString filePath = "C:\\" + fileName;

    // Создаем процесс для запуска программы с правами администратора
    QProcess *installProcess = new QProcess(this);

    // Указываем путь к исполняемому файлу
    installProcess->setProgram(filePath);

    // Соединяем сигнал finished() с соответствующим слотом для обновления ProgressBar
    connect(installProcess, &QProcess::finished, this, &MainWindow::on_Install_bar_valueChanged);

    // Запускаем процесс с правами администратора
    installProcess->startDetached();
}
