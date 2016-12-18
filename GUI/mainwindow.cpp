#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QFileDialog>
#include <QMessageBox>

QString fn;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(openFile()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(recognize()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile() {
    QPixmap pm;
    fn = QFileDialog::getOpenFileName(this, trUtf8("Open..."), "/home/user/ClionProjects/", tr("Image Files (*.png *.jpg *.bmp)"));
    if (fn != "") {
        if (!pm.load(fn)) {
            QMessageBox::critical(this, trUtf8("Error"), trUtf8("Impossible to load image."));
        }
        else {
            ui->label->setPixmap(pm);
            ui->label->setScaledContents(true);
        }
    }
}

void MainWindow::recognize() {
    //call ESOINN.recognize(fn)
    ui->textEdit->setText("japanese symbol");
}
