#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGuiApplication>
#include <QClipboard>
#include <QPixmap>
#include <QIcon>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("icon.png"));
    setWindowTitle("Clipboard saver");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pasteButton_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();

    QPixmap pixmap = clipboard->pixmap();
    clipboard->clear();
    if (!pixmap.isNull()) {

        ui->pasteArea->setPixmap(pixmap.scaled(ui->pasteArea->width(), ui->pasteArea->height(), Qt::KeepAspectRatio));
        QString savePath = QFileDialog::getSaveFileName(this, tr("Save File"), "/", tr("Images (*.jpg)"));
        pixmap.save(savePath, "jpg");
    }
    else {
        ui->pasteArea->setText("there is no picture in clipboard");
    }
}
