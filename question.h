#ifndef QUESTION_H
#define QUESTION_H

#include <QWidget>
#include <QVector>
#include <QVBoxLayout>
#include <QCheckBox>
#include <QLabel>
#include <QDebug>
#include <QFile>

enum checkStates {
    nothingChecked,
    anotherChecked,
    theSameChecked
};

enum numberOfResponses {
    one,
    two,
    three,
    four
};

class Question : public QWidget
{
    Q_OBJECT
public:
    explicit Question(QWidget *parent = nullptr, int p_numberOfAnswers = 3, bool p_isOneCorrect = false, int p_c1 = 0, int p_c2 = 0, int p_c3 = 0, int p_c4 = 0);

    void addQuestion(QString question);
    void addAnswer(QString answer);
    bool isCorrect();
    QLabel *label;
    QLabel* getQuestion();

    checkStates currentCheckState(QCheckBox *senderCheckBox);

private:
    QVBoxLayout *vLayout = new QVBoxLayout(this);
    int numberOfAnswers;
    bool isOneCorrect;

    int c1;
    int c2;
    int c3;
    int c4;

    QVector<QCheckBox*> answers;
    QVector<bool> correctV;

private slots:
    void checkboxClicked();
};

#endif // QUESTION_H
