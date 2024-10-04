
#include "phobeus.h"
#include "./ui_phobeus.h"


Phobeus::Phobeus(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Phobeus)
{
    ui->setupUi(this);

    // создаем экземпляр QLabel для отображения изображения
    imageLabel = new QLabel(this);
    imageLabel->setBackgroundRole(QPalette::Base);
    imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    imageLabel->setScaledContents(true);


    // добавляем QLabel в centralwidget
    setCentralWidget(imageLabel);
}

Phobeus::~Phobeus()
{
    delete ui;
}



void Phobeus::on_actionOpen_triggered()
{
    //Open filedialog for change file
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "/home", tr("*.png *.xpm *.jpg"));

    QImage image(fileName);
    if(image.isNull()){
        QMessageBox::warning(this, tr("Image Viewer"),
                             tr("Cannot load %1.").arg(QDir::toNativeSeparators(fileName)));
        return;
    }
    // отображаем изображение на QLabel
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->adjustSize();
}


void Phobeus::on_actionInfo_triggered()
{
     QDesktopServices::openUrl(QUrl("https://github.com/MrSteelRat/Phobeus", QUrl::TolerantMode));
}


void Phobeus::on_actionExit_triggered()
{
     close();
}

