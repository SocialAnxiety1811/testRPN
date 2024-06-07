#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>
#include <QSpacerItem>
#include <memory>

#include <QFile>

#include "test.h"

// QT_BEGIN_NAMESPACE
// namespace Ui {
// class MainWindow;
// }
// QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget *centralWidget = new QWidget(this);

    QGridLayout *mainLayout = new QGridLayout(centralWidget);

    QComboBox *testSelection = new QComboBox();
    QPushButton *letsStart = new QPushButton("Начать тестирование");

    QWidget *passwordWidget = new QWidget();
    QPushButton *adminButton = new QPushButton("Войти");
    QTextEdit *writePassword = new QTextEdit();

    std::unique_ptr <Test> test_ptr;
    double personalPoints{};

    QSqlQueryModel *model = new QSqlQueryModel();

private slots:
    void openTest();
    void admit();

};
#endif // MAINWINDOW_H
