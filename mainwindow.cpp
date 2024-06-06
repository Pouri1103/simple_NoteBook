#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newDocument);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::open);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::about);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
}
///////////////////////////////////////////////

MainWindow::~MainWindow()
{
    delete ui;
}

///////////////////////////////////////////////

void MainWindow::newDocument()
{
    QMessageBox::StandardButton btn;
    btn = QMessageBox::question(this,"delete text","Delete your text?", QMessageBox::Yes|QMessageBox::No);
    if (btn == QMessageBox::Yes)
    {
        ui->textEdit->clear();
        setWindowTitle("");
    }
}

void MainWindow::open()
{
    bool emptyOpen;
    if (ui->textEdit->toPlainText().length() == 0)
        emptyOpen = 1;
    else
    {
        QMessageBox::StandardButton btn;
        btn = QMessageBox::warning(this,"delete text","Delete your text?", QMessageBox::Yes|QMessageBox::No);
        if (btn == QMessageBox::Yes)
            emptyOpen=1;
        else
            emptyOpen=0;
    }
    if (emptyOpen)
    {
        QString fileAddress = QFileDialog::getOpenFileName(this,"Open the file");
        if (fileAddress != "")
        {
            QFile file(fileAddress);

            if (!file.open(QIODevice::ReadOnly | QFile::Text))
                QMessageBox::warning(this, "warning", "can't open file : " + file.errorString());

            setWindowTitle(fileAddress);

            QTextStream in(&file);
            QString text = in.readAll();
            ui->textEdit->setText(text);

            file.close();
        }
    }
}

void MainWindow::save()
{
    QString fileAddress = windowTitle();

    if (fileAddress == "NoteBook")
        fileAddress = QFileDialog::getSaveFileName(this,"Save","new text","text(*.txt)");

    QFile file(fileAddress);
    if(!file.open(QIODevice::WriteOnly | QFile::Text))
        QMessageBox::critical(this, "Error !", "can't save file : " + file.errorString());

    setWindowTitle(fileAddress);

    QTextStream out(&file);

    QString text = ui->textEdit->toPlainText();
    out << text;

    file.close();
}

void MainWindow::about()
{
    QMessageBox::information(this, "about me!", "This is a NotePad example !!!    \n       Made by Pouriya");
}

