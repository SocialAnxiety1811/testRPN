#include "question.h"

Question::Question(QWidget *parent, int p_numberOfAnswers, bool p_isOneCorrect, int p_c1, int p_c2, int p_c3, int p_c4)
    : QWidget(parent)
{
    numberOfAnswers = p_numberOfAnswers;
    c1 = p_c1;
    c2 = p_c2;
    c3 = p_c3;
    c4 = p_c4;
    isOneCorrect = p_isOneCorrect;

    this->setLayout(vLayout);
    // vLayout->setContentsMargins(0, 0, 0, 5);
    // vLayout->setSpacing(5);
    this->show();

    QFile style(":/style.css");
    style.open(QFile::ReadOnly);
    this->setStyleSheet(style.readAll());
}

void Question::addQuestion(QString p_question)
{
    QWidget *question = new QWidget(this);
    question->setMaximumHeight(40);
    label = new QLabel(p_question, question);
    label->setObjectName("questionObj");
    vLayout->addWidget(question);
}

QLabel* Question::getQuestion()
{
    return label;
}


int checkCurrent = 1;
void Question::addAnswer(QString p_answer)
{
    QCheckBox *answer = new QCheckBox(p_answer, this);
    answer->setObjectName("answerObj");
    answer->setText(p_answer);
    answer->setMaximumHeight(30);
    answer->setObjectName(QStringLiteral("answer%1").arg(checkCurrent-1));
    checkCurrent+=1;
    vLayout->addWidget(answer);
    answer->setObjectName("questionObj");
    answers.append(answer);

    if (isOneCorrect)
    {
        answer->setStyleSheet(
            "QCheckBox::indicator {"
            "    width: 10px;"
            "    height: 10px;"
            "    border-radius: 6px;" // Закругляем углы
            "    background-color: lightgray;"
            "    border: 1px solid gray;"
            "}"
            "QCheckBox::indicator:checked {"
            "    background-color: lightgreen;" // Цвет, когда чекбокс отмечен
            "}"
        );

        connect(answer, &QCheckBox::clicked, this, &Question::checkboxClicked);
    }
    else {
        answer->setStyleSheet(
            "QCheckBox::indicator {"
            "    width: 10px;"
            "    height: 10px;"
            "    border-radius: 7px;" // Закругляем углы
            "    background-color: lightgray;"
            "    border: 1px solid gray;"
            "}"
            "QCheckBox::indicator:checked {"
            "    background-color: lightgreen;" // Цвет, когда чекбокс отмечен
            "}"
            );
    }
}

checkStates Question::currentCheckState(QCheckBox *senderCheckBox)
{
    for (const auto& answer: answers)
    {
        if (answer->isChecked() && answer != senderCheckBox) return anotherChecked;
        if (answer->isChecked() && answer == senderCheckBox) return theSameChecked;
    }
    return nothingChecked;
}

void Question::checkboxClicked()
{
    QCheckBox* clickedCheck = qobject_cast<QCheckBox*>(sender());
    QString clickedCheckObj {clickedCheck->objectName()};

    checkStates currentState {currentCheckState(clickedCheck)};

    switch (currentState)
    {
    case theSameChecked:
    {
        clickedCheck->setChecked(false);
    }
    case anotherChecked:
    {
        for (auto& answer: answers)
        {
            if (answer != clickedCheck) answer->setChecked(false);
        }
    }
    case nothingChecked:
    {
        clickedCheck->setChecked(true);
    }
    }
}

bool Question::isCorrect()
{
    numberOfResponses state = [this]() {
        if (isOneCorrect)
        {
            return one;
        }
        else if (c1 != 0 && c2 != 0 && c3 == 0)
        {
            return two;
        }
        else if (c3 != 0 && c4 == 0)
        {
            return three;
        }
        else if (c4 != 0)
        {
            return four;
        }
    }();

    switch (state) {
    case one:
    {
        for (size_t i{0}; i < answers.size(); ++i)
        {
            QCheckBox* correctAnswer = answers[i];
            if (correctAnswer->isChecked() && (i == c1 - 1)) return true;
        }
    }
    case two:
    {
        int bothCorrect{0};
        for (size_t i{0}; i < answers.size(); ++i)
        {
            QCheckBox* correctAnswer = answers[i];
            if ( (i == c1 - 1) || (i == c2 - 1) )
            {
                if (correctAnswer->isChecked()) ++bothCorrect;
                // qDebug() << bothCorrect;
            }
        }
        if (bothCorrect == 2) return true;
    }
    case three:
    {
        int threeCorrect{0};
        for (size_t i{0}; i < answers.size(); ++i)
        {
            QCheckBox* correctAnswer = answers[i];
            if ( (i == c1 - 1) || (i == c2 - 1) || (i == c3 - 1) )
            {
                if (correctAnswer->isChecked()) ++threeCorrect;
            }
        }
        if (threeCorrect == 3) return true;
    }
    case four:
    {
        int fourCorrect{};
        for (size_t i{0}; i < answers.size(); ++i)
        {
            QCheckBox* correctAnswer = answers[i];

            if ( (i == c1 - 1) || (i == c2 - 1) || (i == c3 - 1) || (i == c4 - 1) )
            {
                if (correctAnswer->isChecked()) ++fourCorrect;
            }
        }
        if (fourCorrect == 4) return true;
    }
    }
}
