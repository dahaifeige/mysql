#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSqlError err = initDb();
    if (err.type() != QSqlError::NoError) {
        QMessageBox::critical(this, "Unable to initialize Database",
                              "Error initializing database: " + err.text());        return;
    }
    QSqlQuery query("SELECT name FROM student");
    while (query.next()) {
        QString name = query.value(0).toString();
        qDebug() << "name:" << name;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

QSqlError MainWindow::initDb()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    // db.setHostName("wangfei");
    db.setDatabaseName("db_test");
    db.setUserName("root");
    db.setPassword("fei5296290");
    if (!db.open()) {
        return db.lastError();
    }
    return QSqlError();
}
