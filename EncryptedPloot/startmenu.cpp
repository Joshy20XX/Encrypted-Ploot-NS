#include "startmenu.h"
#include "./ui_startmenu.h"
#include <QFileDialog>
#include <QFile>
#include <QCoreApplication>

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_pushButton_clicked()
{
    //Open the file dialog
    QString ploot_file = QFileDialog::getOpenFileName(
        this,
        "Open Ploot",
        "",
        "Ploot (*.ploot)"
        );
    //If the ploot file isn't empty, start encrypting
    if (!ploot_file.isEmpty()) {
        QFile file(ploot_file);

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString currentLine = in.readLine();
                qDebug() << currentLine;
            }
        }
        file.close();
    }
}


void StartMenu::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}


void StartMenu::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void StartMenu::on_actionOpen_triggered()
{
    StartMenu::on_pushButton_clicked();
}

