#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QPixmap>
#include <QIcon>

#define SAVE_PATH "C:\\Users\\79884\\Downloads\\"
#define FILE_NAME "screenshot"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("Launch.png"));
    setWindowTitle("ClipboardSaver");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pasteButton_clicked()
{
    ui->pasteArea->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    const int maxHeight = 304;
    const int maxWidth = 616;
    static int nameIndex = 0;
    QClipboard *clipboard = QGuiApplication::clipboard();
    QString savePath = SAVE_PATH;
    QString fileName = FILE_NAME;

    QPixmap pixmap = clipboard->pixmap();
    clipboard->clear();
    if (!pixmap.isNull()) {
        nameIndex++;
        int height = pixmap.height();
        int width = pixmap.width();

        QPixmap rescaledPixmap;
        if (height > width) {
            rescaledPixmap = pixmap.scaledToHeight(maxHeight);
        }
        else {
            rescaledPixmap = pixmap.scaledToWidth(maxWidth);
        }
        ui->pasteArea->setPixmap(rescaledPixmap);

        pixmap.save(savePath + fileName + QString::number(nameIndex) + ".jpg", "jpg", -1);
    }
    else {
        ui->pasteArea->setText("there is no picture in clipboard");
    }
}
