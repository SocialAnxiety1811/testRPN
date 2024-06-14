#ifndef TEST_H
#define TEST_H

#include <QWidget>
#include <QtWidgets>
#include "question.h"
#include <QLabel>
#include <QTextEdit>
#include <QScrollArea>
#include <QGridLayout>
#include <QVector>
#include <QComboBox>
#include <random>
#include <algorithm>

#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlError>
#include <QSqlQuery>

#include <QFile>

class Test : public QWidget
{
    Q_OBJECT
public:
    explicit Test(QWidget *parent = nullptr, QString nameOfTest = "");

    void nurseTest();
    void paramedicTest();
    void doctorVirologistTest();

private:
    QString nameOfTest;
    double maxQuestions;

    QGridLayout *insideThisLayout = new QGridLayout(this);

    QVBoxLayout* scrollLayout = new QVBoxLayout(this);
    QScrollArea* scrollArea = new QScrollArea(this);
    QWidget* mainTestWidget = new QWidget(this);

    QVBoxLayout *testLayout = new QVBoxLayout();
    QWidget *fioW = new QWidget(mainTestWidget);
    QVBoxLayout *fioLayout = new QVBoxLayout();
    QLabel* fioL = new QLabel();
    QTextEdit *fioInput = new QTextEdit();
    QVector<Question> questions;

    QPushButton *submit = new QPushButton(mainTestWidget);
    QVector<Question*> questionsVec;
    std::vector<QWidget*> questionWidgets;
    std::vector<QWidget*> beforeShuffledW;

    double personalPoints{};
    QSqlQueryModel *model = new QSqlQueryModel();
    QTextEdit *inputTodayData;

public slots:
    double submitTest();

signals:
};

#endif // TEST_H
