#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // FrontEnd
    this->setCentralWidget(centralWidget);

    testSelection->addItem("врач-вирусолог");
    testSelection->addItem("санитарка");
    testSelection->addItem("фельдшер-лаборант");

    mainLayout->addWidget(testSelection, 2, 2, 1, 10);
    mainLayout->addWidget(letsStart, 4, 2, 2, 10);
    mainLayout->addWidget(passwordWidget, 6, 2, 1, 10);
    this->setLayout(mainLayout);

    QGridLayout *passwordLayout = new QGridLayout();
    passwordLayout->addWidget(adminButton, 0, 0, 1, 2);
    passwordLayout->addWidget(writePassword, 0, 2, 1, 8);
    passwordWidget->setLayout(passwordLayout);

    //connects
    connect(letsStart, &QPushButton::clicked, this, &MainWindow::openTest);
    connect (adminButton, &QPushButton::clicked, this, &MainWindow::admit);

    QFile style(":/style.css");
    style.open(QFile::ReadOnly);
    this->setStyleSheet(style.readAll());
}

MainWindow::~MainWindow()
{
}

void MainWindow::openTest()
{
    QString nameOfTest = testSelection->currentText();
    test_ptr = std::make_unique<Test>(nullptr, nameOfTest);
    test_ptr.get()->show();
}

void MainWindow::admit()
{
    QString p {"rpn123"};

    QString pathToDatabase = "/Users/arturogaj/testRPN/employees.db";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(pathToDatabase);

    if (!db.open())
    {
        qDebug() << "Ошибка открытия базы данных";
    }
    else
    {
        qDebug() << "База данных успешно открыта!";

        QStringList lst = db.tables();
        foreach (QString str, lst) {
            qDebug() << "Тablе:" << str;
        }
    }


    QString queryStr = "SELECT fio, post, result, data FROM employees";
    model->setQuery(queryStr, db);
    if (model->lastError().isValid()) {
        qDebug() << "Ошибка выполнения запроса:" << model->lastError().text();
        return;
    }

    QTableView *viewTable = new QTableView;
    viewTable->setModel(model);

    QString text = writePassword->toPlainText();
    if (text == p) viewTable->show();
}
