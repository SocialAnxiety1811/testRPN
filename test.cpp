#include "test.h"

Test::Test(QWidget *parent, QString nameOfTest)
    : QWidget{parent},
    nameOfTest(nameOfTest)
{
    scrollArea->setWidget(mainTestWidget);
    QRect screenGeometry = QGuiApplication::screens().at(0)->geometry();

    this->showMaximized();
    this->setWindowFlags(Qt::Window);

    scrollArea->setWidgetResizable(true);
    scrollArea->setFixedSize(screenGeometry.width(), screenGeometry.height());

    mainTestWidget->setObjectName("mainTWObj");

    testLayout->setContentsMargins(0, 0, 0, 0);

    if (nameOfTest == "санитарка")
    {
        QLabel *nameOfTest = new QLabel(mainTestWidget);
        nameOfTest->setText("Тесты по соблюдению требований биологической безопасности и управлению биорисками \nдля санитарки вирусологической лаборатории");
        nameOfTest->setMaximumHeight(50);
        testLayout->addWidget(nameOfTest);
        nameOfTest->setObjectName("nameOfTestObj");
        maxQuestions = 15;

        nurseTest();
    }
    else if (nameOfTest == "фельдшер-лаборант")
    {
        QLabel *nameOfTest = new QLabel(mainTestWidget);
        nameOfTest->setText("Тесты по соблюдению требований биологической безопасностии управлению биорисками \nдля фельдшера-лаборанта вирусологической лаборатории");
        nameOfTest->setMaximumHeight(50);
        testLayout->addWidget(nameOfTest);
        nameOfTest->setObjectName("nameOfTestObj");
        maxQuestions = 30;

        paramedicTest();
    }
    else if (nameOfTest == "врач-вирусолог")
    {
        QLabel *nameOfTest = new QLabel(mainTestWidget);
        nameOfTest->setText("Тесты по соблюдению требований биологической безопасностии управлению биорисками \nдля врача-вирусолога вирусологической лаборатории");
        nameOfTest->setMaximumHeight(50);
        testLayout->addWidget(nameOfTest);
        nameOfTest->setObjectName("nameOfTestObj");
        maxQuestions = 40;

        doctorVirologistTest();
    }

    testLayout->setAlignment(Qt::AlignHCenter);

    submit->setText("Завершить попытку");
    submit->setObjectName("submitObj");
    testLayout->addWidget(submit);

    // testLayout->setSpacing(5);
    mainTestWidget->setLayout(testLayout);

    connect(submit, &QPushButton::clicked, this, &Test::submitTest);

    QFile style(":/style.css");
    style.open(QFile::ReadOnly);
    this->setStyleSheet(style.readAll());
}

double Test::submitTest()
{
    double result{0};
    for (auto& localQuestion: questionsVec)
    {
        if (localQuestion->isCorrect())
        {
            qDebug() << "true";
            result += 1;
        }
    }

    double testResult = (result * 100)/maxQuestions;
    personalPoints = testResult;

    QString fio {fioInput->toPlainText()};
    QString resultStr {QString::number(personalPoints)};
    QString todayDataStr{inputTodayData->toPlainText()};
    qDebug() << todayDataStr;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/arturogaj/testRPN/employees.db");

    if (!db.open()) {
        qDebug() << "Ошибка при открытии базы данных:" << db.lastError().text();
        return 1;
    }

    QString queryStr = QString("INSERT INTO employees (fio, post, result, data) VALUES ('%1', '%2', '%3', '%4')").arg(fio).arg(nameOfTest).arg(resultStr).arg(todayDataStr);

    QSqlQuery query;
    if (!query.exec(queryStr)) {
        qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    } else {
        qDebug() << "Данные успешно добавлены в таблицу.";
    }

    // Закрываем базу данных
    db.close();
    this->close();

    return 1;
}

void Test::nurseTest()
{
    fioLayout->addWidget(fioL);
    fioLayout->addWidget(fioInput);
    fioL->setText("Укажите ФИО");
    fioL->setStyleSheet("color: black;");
    fioW->setMaximumHeight(75);
    fioW->setLayout(fioLayout);
    testLayout->addWidget(fioW);
    fioW->setObjectName("q1WObj");

    QWidget *dataWidget = new QWidget(mainTestWidget);
    QVBoxLayout *dataLayout = new QVBoxLayout;
    dataWidget->setLayout(dataLayout);
    dataWidget->setObjectName("q1WObj");
    dataWidget->setMaximumHeight(75);
    testLayout->addWidget(dataWidget);
    inputTodayData = new QTextEdit(dataWidget);
    QLabel *dataInputInfo = new QLabel(dataWidget);
    dataInputInfo->setText("Введите дату прохождения теста");
    dataInputInfo->setStyleSheet("color: black;");
    inputTodayData->setMaximumHeight(25);
    dataLayout->addWidget(dataInputInfo);
    dataLayout->addWidget(inputTodayData);

    QWidget *q1Widget = new QWidget(mainTestWidget);
    q1Widget->setFixedHeight(150);
    q1Widget->setObjectName("q1WObj");
    QVBoxLayout *q1Layout = new QVBoxLayout(q1Widget);
    Question* q1 = new Question(q1Widget, 4, true, 2);
    q1->addQuestion("Какой раствор используется для генеральной уборки в «заразной» зоне вирусологической лаборатории?");
    q1->addAnswer("3% раствор хлорной извести");
    q1->addAnswer("3% раствор Хлорамина Б");
    q1->addAnswer("3% раствор перекиси водорода");
    q1->addAnswer("96 % спирт");
    q1Layout->setContentsMargins(0, 0, 0, 0);
    q1Layout->addWidget(q1);
    q1Widget->setLayout(q1Layout);
    testLayout->addWidget(q1Widget);

    QWidget *q2Widget = new QWidget(mainTestWidget);
    q2Widget->setFixedHeight(150);
    q2Widget->setObjectName("q1WObj");
    QVBoxLayout *q2Layout = new QVBoxLayout(q2Widget);
    Question *q2 = new Question (q2Widget, 4, true, 3);
    q2->addQuestion("Рабочий раствор хлорамина годен в течение:");
    q2->addAnswer("1 суток");
    q2->addAnswer("7 суток");
    q2->addAnswer("15 суток");
    q2->addAnswer("30 суток");
    q2Layout->setContentsMargins(0, 0, 0, 0);
    q2Layout->addWidget(q2);
    q2Widget->setLayout(q2Layout);
    testLayout->addWidget(q2Widget);

    QWidget *q3Widget = new QWidget(mainTestWidget);
    q3Widget->setFixedHeight(130);
    q3Widget->setObjectName("q1WObj");
    QVBoxLayout *q3Layout = new QVBoxLayout(q3Widget);
    Question *q3 = new Question (q3Widget, 3, true, 2);
    q3->addQuestion("Чему подлежит использованный уборочный инвентарь?");
    q3->addAnswer("Уничтожению");
    q3->addAnswer("Дезинфекции");
    q3->addAnswer("Длительному пребыванию в проветриваемом помещении");
    q3Layout->setContentsMargins(0, 0, 0, 0);
    q3Layout->addWidget(q3);
    q3Widget->setLayout(q3Layout);
    testLayout->addWidget(q3Widget);

    QWidget *q4Widget = new QWidget(mainTestWidget);
    q4Widget->setFixedHeight(180);
    q4Widget->setObjectName("q1WObj");
    QVBoxLayout *q4Layout = new QVBoxLayout(q4Widget);
    Question *q4 = new Question (q4Widget, 5, false, 1, 2);
    q4->addQuestion("Какие виды уборок применяют в вирусологической лаборатории?");
    q4->addAnswer("Генеральную");
    q4->addAnswer("Текущую");
    q4->addAnswer("Первичную");
    q4->addAnswer("Локальную");
    q4->addAnswer("Профилактическую");
    q4Layout->setContentsMargins(0, 0, 0, 0);
    q4Layout->addWidget(q4);
    q4Widget->setLayout(q4Layout);
    testLayout->addWidget(q4Widget);

    QWidget *q5Widget = new QWidget(mainTestWidget);
    q5Widget->setFixedHeight(130);
    q5Widget->setObjectName("q1WObj");
    QVBoxLayout *q5Layout = new QVBoxLayout(q5Widget);
    Question *q5 = new Question (q5Widget, 3, true, 1);
    q5->addQuestion("Как используют уборочный инвентарь в лаборатории, работающей с ПБА 3-4 групп патогенности?");
    q5->addAnswer("Раздельный для «чистой» и «заразной» зон");
    q5->addAnswer("Общий для «чистой» и «заразной» зон");
    q5->addAnswer("Общий для «чистой» и «заразной» зон при соблюдении этапности уборки «от чистого к грязному»");
    q5Layout->setContentsMargins(0, 0, 0, 0);
    q5Layout->addWidget(q5);
    q5Widget->setLayout(q5Layout);
    testLayout->addWidget(q5Widget);

    QWidget *q6Widget = new QWidget(mainTestWidget);
    q6Widget->setFixedHeight(130);
    q6Widget->setObjectName("q1WObj");
    QVBoxLayout *q6Layout = new QVBoxLayout(q6Widget);
    Question *q6 = new Question (q6Widget, 3, true, 2);
    q6->addQuestion("Минимальная высота обработки стен при генеральной уборке составляет:");
    q6->addAnswer("1,5 м");
    q6->addAnswer("2,0 м");
    q6->addAnswer("2,5 м");
    q6Layout->setContentsMargins(0, 0, 0, 0);
    q6Layout->addWidget(q6);
    q6Widget->setLayout(q6Layout);
    testLayout->addWidget(q6Widget);

    QWidget *q7Widget = new QWidget(mainTestWidget);
    q7Widget->setFixedHeight(130);
    q7Widget->setObjectName("q1WObj");
    QVBoxLayout *q7Layout = new QVBoxLayout(q7Widget);
    Question *q7 = new Question (q7Widget, 3, true, 1);
    q7->addQuestion("Очистку и дезинфекцию фильтрующей системы кондиционера, расположенногов«заразной»зоне проводят:");
    q7->addAnswer("1 раз в 3 месяца");
    q7->addAnswer("2 раза в год");
    q7->addAnswer("1 раз в год");
    q7Layout->setContentsMargins(0, 0, 0, 0);
    q7Layout->addWidget(q7);
    q7Widget->setLayout(q7Layout);
    testLayout->addWidget(q7Widget);

    QWidget *q8Widget = new QWidget(mainTestWidget);
    q8Widget->setFixedHeight(150);
    q8Widget->setObjectName("q1WObj");
    QVBoxLayout *q8Layout = new QVBoxLayout(q8Widget);
    Question *q8 = new Question (q8Widget, 4, true, 2);
    q8->addQuestion("К какому классу относят медицинские отходы, содержащие ПБА 3-4 группы?");
    q8->addAnswer("А");
    q8->addAnswer("Б");
    q8->addAnswer("В");
    q8->addAnswer("Г");
    q8Layout->setContentsMargins(0, 0, 0, 0);
    q8Layout->addWidget(q8);
    q8Widget->setLayout(q8Layout);
    testLayout->addWidget(q8Widget);

    QWidget *q9Widget = new QWidget(mainTestWidget);
    q9Widget->setFixedHeight(150);
    q9Widget->setObjectName("q1WObj");
    QVBoxLayout *q9Layout = new QVBoxLayout(q9Widget);
    Question *q9 = new Question (q9Widget, 4, true, 2);
    q9->addQuestion("В плановом порядке защитная одежда меняется:");
    q9->addAnswer("Ежедневно");
    q9->addAnswer("1 раз в неделю");
    q9->addAnswer("2 раза в месяц");
    q9->addAnswer("1 раз в месяц");
    q9Layout->setContentsMargins(0, 0, 0, 0);
    q9Layout->addWidget(q9);
    q9Widget->setLayout(q9Layout);
    testLayout->addWidget(q9Widget);

    QWidget *q10Widget = new QWidget(mainTestWidget);
    q10Widget->setFixedHeight(180);
    q10Widget->setObjectName("q1WObj");
    QVBoxLayout *q10Layout = new QVBoxLayout(q10Widget);
    Question *q10 = new Question (q10Widget, 5, true, 4);
    q10->addQuestion("Смешение отходов различных классов в общем пакете:");
    q10->addAnswer("Допустимо при дефиците одноразовых пакетов");
    q10->addAnswer("Допустимо при соответствующей маркировке пакетов");
    q10->addAnswer("Зависит от классов отходов");
    q10->addAnswer("Недопустимо");
    q10->addAnswer("Допустимо");
    q10Layout->setContentsMargins(0, 0, 0, 0);
    q10Layout->addWidget(q10);
    q10Widget->setLayout(q10Layout);
    testLayout->addWidget(q10Widget);

    QWidget *q11Widget = new QWidget(mainTestWidget);
    q11Widget->setFixedHeight(150);
    q11Widget->setObjectName("q1WObj");
    QVBoxLayout *q11Layout = new QVBoxLayout(q11Widget);
    Question *q11 = new Question (q11Widget, 4, true, 1);
    q11->addQuestion("Тара, которая допускается для сбора отходов класса Б:");
    q11->addAnswer("Одноразовые пакеты");
    q11->addAnswer("Плотные мешки из водоотталкивающей ткани");
    q11->addAnswer("Бумажные мешки/пакеты");
    q11->addAnswer("Твёрдая картонная тара");
    q11Layout->setContentsMargins(0, 0, 0, 0);
    q11Layout->addWidget(q11);
    q11Widget->setLayout(q11Layout);
    testLayout->addWidget(q11Widget);

    QWidget *q12Widget = new QWidget(mainTestWidget);
    q12Widget->setFixedHeight(180);
    q12Widget->setObjectName("q1WObj");
    QVBoxLayout *q12Layout = new QVBoxLayout(q12Widget);
    Question *q12 = new Question (q12Widget, 5, false, 2, 3, 4);
    q12->addQuestion("Какие помещения размещают в «заразной» зоне?");
    q12->addAnswer("Для стерилизации лабораторной посуды");
    q12->addAnswer("Для приёма и обработки материала");
    q12->addAnswer("Для проведения исследовани");
    q12->addAnswer("Для обеззараживания инфекционного материала");
    q12->addAnswer("Для работы с документами");
    q12Layout->setContentsMargins(0, 0, 0, 0);
    q12Layout->addWidget(q12);
    q12Widget->setLayout(q12Layout);
    testLayout->addWidget(q12Widget);

    QWidget *q13Widget = new QWidget(mainTestWidget);
    q13Widget->setFixedHeight(150);
    q13Widget->setObjectName("q1WObj");
    QVBoxLayout *q13Layout = new QVBoxLayout(q13Widget);
    Question *q13 = new Question (q13Widget, 4, true, 3);
    q13->addQuestion("Кратность обработки поверхности бактерицидных ламп:");
    q13->addAnswer("1 раз в месяц");
    q13->addAnswer("2 раза в месяц");
    q13->addAnswer("1 раз в неделю");
    q13->addAnswer("2 раза в неделю");
    q13Layout->setContentsMargins(0, 0, 0, 0);
    q13Layout->addWidget(q13);
    q13Widget->setLayout(q13Layout);
    testLayout->addWidget(q13Widget);

    QWidget *q14Widget = new QWidget(mainTestWidget);
    q14Widget->setFixedHeight(180);
    q14Widget->setObjectName("q1WObj");
    QVBoxLayout *q14Layout = new QVBoxLayout(q14Widget);
    Question *q14 = new Question (q14Widget, 5, true, 4);
    q14->addQuestion("Обработка поверхности бактерицидных ламп проводится:");
    q14->addAnswer("3 % раствором хлорамина Б");
    q14->addAnswer("3 % раствором перекиси водорода");
    q14->addAnswer("6 % раствором перекиси водорода");
    q14->addAnswer("70 % раствор спирта");
    q14->addAnswer("96 % раствор спирта");
    q14Layout->setContentsMargins(0, 0, 0, 0);
    q14Layout->addWidget(q14);
    q14Widget->setLayout(q14Layout);
    testLayout->addWidget(q14Widget);

    QWidget *q15Widget = new QWidget(mainTestWidget);
    q15Widget->setFixedHeight(130);
    q15Widget->setObjectName("q1WObj");
    QVBoxLayout *q15Layout = new QVBoxLayout(q15Widget);
    Question *q15 = new Question (q15Widget, 4, true, 2);
    q15->addQuestion("Сколько входов должна иметь вирусологическая лаборатория?");
    q15->addAnswer("1 – для сотрудников и доставки материала на исследование");
    q15->addAnswer("2 – один для сотрудников, другой для доставки материала на исследование");
    q15->addAnswer("3 – один для сотрудников, другой для доставки материала на исследование, третий для хозяйственных нужд");
    q15Layout->setContentsMargins(0, 0, 0, 0);
    q15Layout->addWidget(q15);
    q15Widget->setLayout(q15Layout);
    testLayout->addWidget(q15Widget);

    QWidget *q16Widget = new QWidget(mainTestWidget);
    q16Widget->setFixedHeight(150);
    q16Widget->setObjectName("q1WObj");
    QVBoxLayout *q16Layout = new QVBoxLayout(q16Widget);
    Question *q16 = new Question (q16Widget, 4, true, 1);
    q16->addQuestion("Какой минимальный запас дезинфицирующих средств в лаборатории, работающей с ПБА?");
    q16->addAnswer("1 неделя");
    q16->addAnswer("2 недели");
    q16->addAnswer("1 месяц");
    q16->addAnswer("1 квартал");
    q16Layout->setContentsMargins(0, 0, 0, 0);
    q16Layout->addWidget(q16);
    q16Widget->setLayout(q16Layout);
    testLayout->addWidget(q16Widget);

    QWidget *q17Widget = new QWidget(mainTestWidget);
    q17Widget->setFixedHeight(180);
    q17Widget->setObjectName("q1WObj");
    QVBoxLayout *q17Layout = new QVBoxLayout(q17Widget);
    Question *q17 = new Question (q17Widget, 5, true, 3);
    q17->addQuestion("Упаковку какого цвета используют для сбора отходов класса Б?");
    q17->addAnswer("Красную");
    q17->addAnswer("Синюю");
    q17->addAnswer("Жёлтую");
    q17->addAnswer("Зелёную");
    q17->addAnswer("Чёрную");
    q17Layout->setContentsMargins(0, 0, 0, 0);
    q17Layout->addWidget(q17);
    q17Widget->setLayout(q17Layout);
    testLayout->addWidget(q17Widget);

    QWidget *q18Widget = new QWidget(mainTestWidget);
    q18Widget->setFixedHeight(180);
    q18Widget->setObjectName("q1WObj");
    QVBoxLayout *q18Layout = new QVBoxLayout(q18Widget);
    Question *q18 = new Question (q18Widget, 5, true, 3);
    q18->addQuestion("С какой периодичностью проводится плановая генеральная уборка в отдельно взятом помещении «заразной» зоны?");
    q18->addAnswer("Ежедневно");
    q18->addAnswer("2 раза в неделю");
    q18->addAnswer("1 раз в неделю");
    q18->addAnswer("2 раза в месяц");
    q18->addAnswer("1 раз в месяц");
    q18Layout->setContentsMargins(0, 0, 0, 0);
    q18Layout->addWidget(q18);
    q18Widget->setLayout(q18Layout);
    testLayout->addWidget(q18Widget);

    QWidget *q19Widget = new QWidget(mainTestWidget);
    q19Widget->setFixedHeight(150);
    q19Widget->setObjectName("q1WObj");
    QVBoxLayout *q19Layout = new QVBoxLayout(q19Widget);
    Question *q19 = new Question (q19Widget, 4, true, 1);
    q19->addQuestion("На дверях «заразной» зоны в соответствии с СанПин 3.3686-21 обязательно разместить:");
    q19->addAnswer("Знак «Биологическая опасность»");
    q19->addAnswer("Знак «Биологическая безопасность»");
    q19->addAnswer("Надпись «Осторожно! «Заразная» зона!»");
    q19->addAnswer("Надпись «Посторонним вход запрещён!»");
    q19Layout->setContentsMargins(0, 0, 0, 0);
    q19Layout->addWidget(q19);
    q19Widget->setLayout(q19Layout);
    testLayout->addWidget(q19Widget);

    QWidget *q20Widget = new QWidget(mainTestWidget);
    q20Widget->setFixedHeight(150);
    q20Widget->setObjectName("q1WObj");
    QVBoxLayout *q20Layout = new QVBoxLayout(q20Widget);
    Question *q20 = new Question (q20Widget, 4, true, 4);
    q20->addQuestion("Сброс жидких отходов лаборатории, работающей с ПБА 3-4 группы, в общую канализацию:");
    q20->addAnswer("Не разрешён");
    q20->addAnswer("Разрешён");
    q20->addAnswer("Разрешён не более 15 л в сутки");
    q20->addAnswer("Разрешён после обеззараживания");
    q20Layout->setContentsMargins(0, 0, 0, 0);
    q20Layout->addWidget(q20);
    q20Widget->setLayout(q20Layout);
    testLayout->addWidget(q20Widget);

    QWidget *q21Widget = new QWidget(mainTestWidget);
    q21Widget->setFixedHeight(150);
    q21Widget->setObjectName("q1WObj");
    QVBoxLayout *q21Layout = new QVBoxLayout(q21Widget);
    Question *q21 = new Question (q21Widget, 4, true, 4);
    q21->addQuestion("В помещениях «заразной» зоны проводят обеззараживание:");
    q21->addAnswer("Поверхностей");
    q21->addAnswer("Стоков");
    q21->addAnswer("Воздуха");
    q21->addAnswer("Всё перечисленное");
    q21Layout->setContentsMargins(0, 0, 0, 0);
    q21Layout->addWidget(q21);
    q21Widget->setLayout(q21Layout);
    testLayout->addWidget(q21Widget);

    QWidget *q22Widget = new QWidget(mainTestWidget);
    q22Widget->setFixedHeight(150);
    q22Widget->setObjectName("q1WObj");
    QVBoxLayout *q22Layout = new QVBoxLayout(q22Widget);
    Question *q22 = new Question (q22Widget, 4, true, 4);
    q22->addQuestion("Время обеззараживания поверхностей 3 % раствором Хлорамина Б в помещениях «заразной» зоны вирусологической лаборатории:");
    q22->addAnswer("15 минут");
    q22->addAnswer("30 минут");
    q22->addAnswer("60 минут");
    q22->addAnswer("120 минут");
    q22Layout->setContentsMargins(0, 0, 0, 0);
    q22Layout->addWidget(q22);
    q22Widget->setLayout(q22Layout);
    testLayout->addWidget(q22Widget);

    QWidget *q23Widget = new QWidget(mainTestWidget);
    q23Widget->setFixedHeight(150);
    q23Widget->setObjectName("q1WObj");
    QVBoxLayout *q23Layout = new QVBoxLayout(q23Widget);
    Question *q23 = new Question (q23Widget, 4, false, 1, 4);
    q23->addQuestion("Время обеззараживания защитной одежды в 3 % растворе Хлорамина Б при работе с вируссодержащим материалом:");
    q23->addAnswer("Незагрязнённая – 30 минут");
    q23->addAnswer("Незагрязнённая – 60 минут");
    q23->addAnswer("Загрязнённая – 60 минут");
    q23->addAnswer("Загрязнённая – 120 минут");
    q23Layout->setContentsMargins(0, 0, 0, 0);
    q23Layout->addWidget(q23);
    q23Widget->setLayout(q23Layout);
    testLayout->addWidget(q23Widget);

    QWidget *q24Widget = new QWidget(mainTestWidget);
    q24Widget->setFixedHeight(190);
    q24Widget->setObjectName("q1WObj");
    QVBoxLayout *q24Layout = new QVBoxLayout(q24Widget);
    Question *q24 = new Question (q24Widget, 4, true, 4);
    q24->addQuestion("Время обеззараживания уборочного материала в 3 % растворе Хлорамина Б после уборки в «заразной» зоне вирусологической \nлаборатории:");
    q24->addAnswer("30 минут");
    q24->addAnswer("60 минут");
    q24->addAnswer("90 минут");
    q24->addAnswer("120 минут");
    q24Layout->setContentsMargins(0, 0, 0, 0);
    q24Layout->addWidget(q24);
    q24Widget->setLayout(q24Layout);
    testLayout->addWidget(q24Widget);

    QWidget *q25Widget = new QWidget(mainTestWidget);
    q25Widget->setFixedHeight(180);
    q25Widget->setObjectName("q1WObj");
    QVBoxLayout *q25Layout = new QVBoxLayout(q25Widget);
    Question *q25 = new Question (q25Widget, 5, false, 1, 5);
    q25->addQuestion("Какие помещения размещают в «чистой» зоне?");
    q25->addAnswer("Для стерилизации лабораторной посуды");
    q25->addAnswer("Для приёма и обработки материала");
    q25->addAnswer("Для проведения исследований");
    q25->addAnswer("Для обеззараживания инфекционного материала");
    q25->addAnswer("Для работы с документами");
    q25Layout->setContentsMargins(0, 0, 0, 0);
    q25Layout->addWidget(q25);
    q25Widget->setLayout(q25Layout);
    testLayout->addWidget(q25Widget);

    questionsVec = {q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25};
    questionWidgets = {q1Widget, q2Widget, q3Widget, q4Widget, q5Widget, q6Widget, q7Widget, q8Widget, q9Widget, q10Widget, q11Widget, q12Widget, q13Widget, q14Widget, q15Widget, q16Widget, q17Widget, q18Widget, q19Widget, q20Widget, q21Widget, q22Widget, q23Widget, q24Widget, q25Widget};
    beforeShuffledW = questionWidgets;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(questionWidgets.begin(), questionWidgets.end(), gen);
    std::vector<size_t> indices(questionWidgets.size());

    for (size_t i = 0; i < 10 && !questionWidgets.empty(); ++i)
    {
        QWidget* el = questionWidgets[i];
        el->hide();
        el->deleteLater();
    }

    int counter = 1;
    for (auto el : beforeShuffledW)
    {
        if (el && !el->isHidden())
        { // Проверка, чтобы избежать доступа к скрытым и удаленным виджетам
            Question* q = el->findChild<Question*>();
            QString iStr = QString::number(counter);
            q->getQuestion()->setText(iStr + " " + q->getQuestion()->text());
            ++counter;
        }
    }
}

void Test::paramedicTest()
{
    fioLayout->addWidget(fioL);
    fioLayout->addWidget(fioInput);
    fioL->setText("Укажите ФИО");
    fioL->setStyleSheet("color: black;");
    fioW->setMaximumHeight(75);
    fioW->setLayout(fioLayout);
    testLayout->addWidget(fioW);
    fioW->setObjectName("q1WObj");

    QWidget *dataWidget = new QWidget(mainTestWidget);
    QVBoxLayout *dataLayout = new QVBoxLayout;
    dataWidget->setLayout(dataLayout);
    dataWidget->setObjectName("q1WObj");
    dataWidget->setMaximumHeight(75);
    testLayout->addWidget(dataWidget);
    inputTodayData = new QTextEdit(dataWidget);
    QLabel *dataInputInfo = new QLabel(dataWidget);
    dataInputInfo->setText("Введите дату прохождения теста");
    dataInputInfo->setStyleSheet("color: black;");
    inputTodayData->setMaximumHeight(25);
    dataLayout->addWidget(dataInputInfo);
    dataLayout->addWidget(inputTodayData);

    QWidget *q1Widget = new QWidget(mainTestWidget);
    q1Widget->setFixedHeight(170);
    q1Widget->setObjectName("q1WObj");
    QVBoxLayout *q1Layout = new QVBoxLayout(q1Widget);
    Question* q1 = new Question(q1Widget, 3, true, 3);
    q1->addQuestion("Какой нормативный документ на сегодняшний день определяет санитарно-эпидемиологические требования к обеспечению \nбезопасности при работе с ПБА?");
    q1->addAnswer("СП 1.2.731-99«Безопасность работы с микроорганизмами III - IV групп патогенности и гельминтами»");
    q1->addAnswer("СП 1.3.2322-08 «Безопасность работы с микроорганизмами III - IV групп патогенности (опасности) и возбудителями паразитарных \nболезней»");
    q1->addAnswer("СанПиН 3.3686-21 «Санитарно-эпидемиологические требования по профилактике инфекционных болезней»");
    q1Layout->setContentsMargins(0, 0, 0, 0);
    q1Layout->addWidget(q1);
    q1Widget->setLayout(q1Layout);
    testLayout->addWidget(q1Widget);

    QWidget *q2Widget = new QWidget(mainTestWidget);
    q2Widget->setFixedHeight(170);
    q2Widget->setObjectName("q1WObj");
    QVBoxLayout *q2Layout = new QVBoxLayout(q2Widget);
    Question *q2 = new Question (q2Widget, 3, true, 2);
    q2->addQuestion("С какой целью разработаны Санитарные правила и нормы СанПиН 3.3686-21 «Санитарно-эпидемиологические требования по \nпрофилактике инфекционных болезней»?");
    q2->addAnswer("С целью обеспечения безопасности сотрудников лаборатории");
    q2->addAnswer("С целью предупреждения возникновения и распространения инфекционных болезней среди населения");
    q2->addAnswer("С целью обеспечения безопасности всех сотрудников учреждения");
    q2Layout->setContentsMargins(0, 0, 0, 0);
    q2Layout->addWidget(q2);
    q2Widget->setLayout(q2Layout);
    testLayout->addWidget(q2Widget);

    QWidget *q3Widget = new QWidget(mainTestWidget);
    q3Widget->setFixedHeight(200);
    q3Widget->setObjectName("q1WObj");
    QVBoxLayout *q3Layout = new QVBoxLayout(q3Widget);
    Question *q3 = new Question (q3Widget, 4, false, 1, 3, 4);
    q3->addQuestion("Санитарные правила СанПиН 3.3686-21 устанавливают обязательные требования:");
    q3->addAnswer("К комплексу организационных, профилактических, санитарно-противоэпидемических, лабораторно-диагностических мероприятий, \nнаправленных на обеспечение раннего выявления, предупреждения возникновения и распространения инфекционных болезней среди населения ");
    q3->addAnswer("К осуществлению сбора, обеззараживания, обезвреживания, временного хранения и удаления медицинских отходов");
    q3->addAnswer("К порядку учета, хранения, передачи и транспортирования ПБА, а также объектов и материалов, содержащих или подозрительных на \nсодержание ПБА");
    q3->addAnswer("К организационным, санитарно-противоэпидемическим (профилактическим), инженерно-техническим мероприятиям, направленным на \nобеспечение личной и общественной безопасности, защиту окружающей среды при работе с микроорганизмами, вирусами, белковоподобными инфекционными частицами (прионами), ядами биологического происхождения (токсинами) и иными биологическими агентами, в том числе созданными в результате генетических манипуляций, применения технологий синтетической биологии и другой направленной деятельности, способных вызывать патологический процесс в организме человека или животного, а также биологические материалы, в которых могут содержаться перечисленные ПБА");
    q3Layout->setContentsMargins(0, 0, 0, 0);
    q3Layout->addWidget(q3);
    q3Widget->setLayout(q3Layout);
    testLayout->addWidget(q3Widget);

    QWidget *q4Widget = new QWidget(mainTestWidget);
    q4Widget->setFixedHeight(150);
    q4Widget->setObjectName("q1WObj");
    QVBoxLayout *q4Layout = new QVBoxLayout(q4Widget);
    Question *q4 = new Question (q4Widget, 5, true, 2);
    q4->addQuestion("Сколько групп патогенности существует в действующей классификации?");
    q4->addAnswer("2");
    q4->addAnswer("4");
    q4->addAnswer("6");
    q4->addAnswer("8");
    q4Layout->setContentsMargins(0, 0, 0, 0);
    q4Layout->addWidget(q4);
    q4Widget->setLayout(q4Layout);
    testLayout->addWidget(q4Widget);

    QWidget *q5Widget = new QWidget(mainTestWidget);
    q5Widget->setFixedHeight(200);
    q5Widget->setObjectName("q1WObj");
    QVBoxLayout *q5Layout = new QVBoxLayout(q5Widget);
    Question *q5 = new Question (q5Widget, 5, false, 2, 3, 4);
    q5->addQuestion("Какие помещения размещают в «заразной» зоне?");
    q5->addAnswer("Для стерилизации лабораторной посуды ");
    q5->addAnswer("Для приёма и обработки материала");
    q5->addAnswer("Для проведения исследований");
    q5->addAnswer("Для обеззараживания инфекционного материала");
    q5->addAnswer("Для работы с документами");
    q5Layout->setContentsMargins(0, 0, 0, 0);
    q5Layout->addWidget(q5);
    q5Widget->setLayout(q5Layout);
    testLayout->addWidget(q5Widget);

    QWidget *q6Widget = new QWidget(mainTestWidget);
    q6Widget->setFixedHeight(150);
    q6Widget->setObjectName("q1WObj");
    QVBoxLayout *q6Layout = new QVBoxLayout(q6Widget);
    Question *q6 = new Question (q6Widget, 4, false, 1, 2);
    q6->addQuestion("Методы обеззараживания инфекционного материала");
    q6->addAnswer("Химический");
    q6->addAnswer("Физический");
    q6->addAnswer("Биологический");
    q6->addAnswer("Измельчение");
    q6Layout->setContentsMargins(0, 0, 0, 0);
    q6Layout->addWidget(q6);
    q6Widget->setLayout(q6Layout);
    testLayout->addWidget(q6Widget);

    QWidget *q7Widget = new QWidget(mainTestWidget);
    q7Widget->setFixedHeight(150);
    q7Widget->setObjectName("q1WObj");
    QVBoxLayout *q7Layout = new QVBoxLayout(q7Widget);
    Question *q7 = new Question (q7Widget, 4, false, 1, 2, 4);
    q7->addQuestion("Что относят к физическим методам обеззараживания инфекционного материала?");
    q7->addAnswer("Обработка водяным насыщенным паром под давлением");
    q7->addAnswer("Ультрафиолетовое излучение");
    q7->addAnswer("Обработка 70 % спиртом");
    q7->addAnswer("Сжигание");
    q7Layout->setContentsMargins(0, 0, 0, 0);
    q7Layout->addWidget(q7);
    q7Widget->setLayout(q7Layout);
    testLayout->addWidget(q7Widget);

    QWidget *q8Widget = new QWidget(mainTestWidget);
    q8Widget->setFixedHeight(150);
    q8Widget->setObjectName("q1WObj");
    QVBoxLayout *q8Layout = new QVBoxLayout(q8Widget);
    Question *q8 = new Question (q8Widget, 4, false, 1, 2, 3);
    q8->addQuestion("Методы контроля работы паровых и воздушных стерилизаторов, используемых для обеззараживания ПБА:");
    q8->addAnswer("Химический");
    q8->addAnswer("Физический");
    q8->addAnswer("Биологический");
    q8->addAnswer("Учёт показаний манометра");
    q8Layout->setContentsMargins(0, 0, 0, 0);
    q8Layout->addWidget(q8);
    q8Widget->setLayout(q8Layout);
    testLayout->addWidget(q8Widget);

    QWidget *q9Widget = new QWidget(mainTestWidget);
    q9Widget->setFixedHeight(150);
    q9Widget->setObjectName("q1WObj");
    QVBoxLayout *q9Layout = new QVBoxLayout(q9Widget);
    Question *q9 = new Question (q9Widget, 4, true, 3);
    q9->addQuestion("Кратность планового биологического контроля паровых и воздушных стерилиза-торов, используемых для обеззараживания ПБА:");
    q9->addAnswer("2 раза в месяц");
    q9->addAnswer("2 раза в квартал");
    q9->addAnswer("2 раза в год");
    q9->addAnswer("1 раз в год");
    q9Layout->setContentsMargins(0, 0, 0, 0);
    q9Layout->addWidget(q9);
    q9Widget->setLayout(q9Layout);
    testLayout->addWidget(q9Widget);

    QWidget *q10Widget = new QWidget(mainTestWidget);
    q10Widget->setFixedHeight(180);
    q10Widget->setObjectName("q1WObj");
    QVBoxLayout *q10Layout = new QVBoxLayout(q10Widget);
    Question *q10 = new Question (q10Widget, 4, true, 3);
    q10->addQuestion("Кратность обработки поверхности бактерицидных ламп:");
    q10->addAnswer("1 раз в месяц");
    q10->addAnswer("2 раза в месяц");
    q10->addAnswer("1 раз в неделю");
    q10->addAnswer("2 раза в неделю");
    q10Layout->setContentsMargins(0, 0, 0, 0);
    q10Layout->addWidget(q10);
    q10Widget->setLayout(q10Layout);
    testLayout->addWidget(q10Widget);

    QWidget *q11Widget = new QWidget(mainTestWidget);
    q11Widget->setFixedHeight(200);
    q11Widget->setObjectName("q1WObj");
    QVBoxLayout *q11Layout = new QVBoxLayout(q11Widget);
    Question *q11 = new Question (q11Widget, 4, true, 1);
    q11->addQuestion("Какой режим паровой стерилизации необходимо использовать для обеззараживания вируссодержащей жидкости, взвеси зараженной \nкультуры клеток?");
    q11->addAnswer("Водяной насыщенный пар под давлением 2,0 кгс/см2, (132 +/- 2) °C, 60 минут");
    q11->addAnswer("Водяной насыщенный пар под давлением 2,0 кгс/см2, (132 +/- 2) °C, 45 минут");
    q11->addAnswer("Водяной насыщенный пар под давлением 1,1 кгс/см2, (120 +/- 2) °C, 45 минут");
    q11->addAnswer("Водяной насыщенный пар под давлением 1,1 кгс/см2, (120 +/- 2) °C, 20 минут");
    q11Layout->setContentsMargins(0, 0, 0, 0);
    q11Layout->addWidget(q11);
    q11Widget->setLayout(q11Layout);
    testLayout->addWidget(q11Widget);

    QWidget *q12Widget = new QWidget(mainTestWidget);
    q12Widget->setFixedHeight(150);
    q12Widget->setObjectName("q1WObj");
    QVBoxLayout *q12Layout = new QVBoxLayout(q12Widget);
    Question *q12 = new Question (q12Widget, 3, false, 2, 3);
    q12->addQuestion("Внеплановую проверку эксплуатационных характеристик боксов микробиологической безопасности проводят при:");
    q12->addAnswer("Замене инженерно-технического персонала");
    q12->addAnswer("Монтаже и вводе в эксплуатацию");
    q12->addAnswer("После перемещения и/или ремонта");
    q12Layout->setContentsMargins(0, 0, 0, 0);
    q12Layout->addWidget(q12);
    q12Widget->setLayout(q12Layout);
    testLayout->addWidget(q12Widget);

    QWidget *q13Widget = new QWidget(mainTestWidget);
    q13Widget->setFixedHeight(150);
    q13Widget->setObjectName("q1WObj");
    QVBoxLayout *q13Layout = new QVBoxLayout(q13Widget);
    Question *q13 = new Question (q13Widget, 3, false, 1, 2);
    q13->addQuestion("Виды аварий при работе с патогенными биологическими агентами:");
    q13->addAnswer("Авария, связанная с нарушением целостности кожных покровов");
    q13->addAnswer("Авария, связанная с нарушением целостности средств индивидуальной защиты");
    q13->addAnswer("Авария, связанная с нарушением методики выполнения исследований");
    q13Layout->setContentsMargins(0, 0, 0, 0);
    q13Layout->addWidget(q13);
    q13Widget->setLayout(q13Layout);
    testLayout->addWidget(q13Widget);

    QWidget *q14Widget = new QWidget(mainTestWidget);
    q14Widget->setFixedHeight(180);
    q14Widget->setObjectName("q1WObj");
    QVBoxLayout *q14Layout = new QVBoxLayout(q14Widget);
    Question *q14 = new Question (q14Widget, 4, true, 2);
    q14->addQuestion("В состав аварийной аптечки входит:");
    q14->addAnswer("Спирт этиловый 70%, йод, антибиотики, перевязочные средства");
    q14->addAnswer("Спирт этиловый 70%, йод, нашатырный спирт, жгут кровоостанавливающий, перевязочные средства");
    q14->addAnswer("Спирт этиловый 70%, йод, нашатырный спирт, жгут кровоостанавливающий, жаропонижающие препараты ");
    q14->addAnswer("Спирт этиловый 70%, йод, нашатырный спирт, жгут кровоостанавливающий, антигистаминные средства ");
    q14Layout->setContentsMargins(0, 0, 0, 0);
    q14Layout->addWidget(q14);
    q14Widget->setLayout(q14Layout);
    testLayout->addWidget(q14Widget);

    QWidget *q15Widget = new QWidget(mainTestWidget);
    q15Widget->setFixedHeight(150);
    q15Widget->setObjectName("q1WObj");
    QVBoxLayout *q15Layout = new QVBoxLayout(q15Widget);
    Question *q15 = new Question (q15Widget, 4, true, 4);
    q15->addQuestion("При приёме на работу, связанную с использованием ПБА 3-4 групп, персонал проходит:");
    q15->addAnswer("Вводный инструктаж по биологической безопасности");
    q15->addAnswer("Предварительный медицинский осмотр с целью выявления медицинских противопоказаний к вакцинопрофилактике ");
    q15->addAnswer("Оценку уровня специфического иммунитета для определения необходимости их иммунизации от управляемых инфекций");
    q15->addAnswer("Всё перечисленное");
    q15Layout->setContentsMargins(0, 0, 0, 0);
    q15Layout->addWidget(q15);
    q15Widget->setLayout(q15Layout);
    testLayout->addWidget(q15Widget);

    QWidget *q16Widget = new QWidget(mainTestWidget);
    q16Widget->setFixedHeight(150);
    q16Widget->setObjectName("q1WObj");
    QVBoxLayout *q16Layout = new QVBoxLayout(q16Widget);
    Question *q16 = new Question (q16Widget, 3, true, 2);
    q16->addQuestion("Сколько входов должна иметь вирусологическая лаборатория?");
    q16->addAnswer("1 – для сотрудников и доставки материала на исследование");
    q16->addAnswer("2 – один для сотрудников, другой для доставки материала на исследование");
    q16->addAnswer("3 – один для сотрудников, другой для доставки материала на исследование, третий для хозяйственных нужд");
    q16Layout->setContentsMargins(0, 0, 0, 0);
    q16Layout->addWidget(q16);
    q16Widget->setLayout(q16Layout);
    testLayout->addWidget(q16Widget);

    QWidget *q17Widget = new QWidget(mainTestWidget);
    q17Widget->setFixedHeight(150);
    q17Widget->setObjectName("q1WObj");
    QVBoxLayout *q17Layout = new QVBoxLayout(q17Widget);
    Question *q17 = new Question (q17Widget, 3, true, 3);
    q17->addQuestion("Аварийная сигнализация в помещениях «заразной» зоны предусмотрена на случай:");
    q17->addAnswer("Пожара");
    q17->addAnswer("Вызова сотрудника при большом объёме работ");
    q17->addAnswer("Аварийных ситуаций при работе с ПБА");
    q17Layout->setContentsMargins(0, 0, 0, 0);
    q17Layout->addWidget(q17);
    q17Widget->setLayout(q17Layout);
    testLayout->addWidget(q17Widget);

    QWidget *q18Widget = new QWidget(mainTestWidget);
    q18Widget->setFixedHeight(160);
    q18Widget->setObjectName("q1WObj");
    QVBoxLayout *q18Layout = new QVBoxLayout(q18Widget);
    Question *q18 = new Question (q18Widget, 4, true, 3);
    q18->addQuestion("Время непрерывной работы с ПБА:");
    q18->addAnswer("1 час");
    q18->addAnswer("2 часа");
    q18->addAnswer("4 часа");
    q18->addAnswer("6 часов");
    q18Layout->setContentsMargins(0, 0, 0, 0);
    q18Layout->addWidget(q18);
    q18Widget->setLayout(q18Layout);
    testLayout->addWidget(q18Widget);

    QWidget *q19Widget = new QWidget(mainTestWidget);
    q19Widget->setFixedHeight(150);
    q19Widget->setObjectName("q1WObj");
    QVBoxLayout *q19Layout = new QVBoxLayout(q19Widget);
    Question *q19 = new Question (q19Widget, 4, true, 1);
    q19->addQuestion("Какой минимальный запас дезинфицирующих средств в лаборатории, работающей с ПБА?");
    q19->addAnswer("1 неделя");
    q19->addAnswer("2 недели");
    q19->addAnswer("1 месяц");
    q19->addAnswer("1 квартал");
    q19Layout->setContentsMargins(0, 0, 0, 0);
    q19Layout->addWidget(q19);
    q19Widget->setLayout(q19Layout);
    testLayout->addWidget(q19Widget);

    QWidget *q20Widget = new QWidget(mainTestWidget);
    q20Widget->setFixedHeight(170);
    q20Widget->setObjectName("q1WObj");
    QVBoxLayout *q20Layout = new QVBoxLayout(q20Widget);
    Question *q20 = new Question (q20Widget, 5, true, 3);
    q20->addQuestion("Упаковку какого цвета используют для сбора отходов класса Б?");
    q20->addAnswer("Красную");
    q20->addAnswer("Синюю");
    q20->addAnswer("Жёлтую");
    q20->addAnswer("Зелёную");
    q20->addAnswer("Чёрную");
    q20Layout->setContentsMargins(0, 0, 0, 0);
    q20Layout->addWidget(q20);
    q20Widget->setLayout(q20Layout);
    testLayout->addWidget(q20Widget);

    QWidget *q21Widget = new QWidget(mainTestWidget);
    q21Widget->setFixedHeight(150);
    q21Widget->setObjectName("q1WObj");
    QVBoxLayout *q21Layout = new QVBoxLayout(q21Widget);
    Question *q21 = new Question (q21Widget, 4, true, 2);
    q21->addQuestion("Что предусматривает химический контроль режима стерилизации?");
    q21->addAnswer("Контроль работы манометров стерилизатора");
    q21->addAnswer("Использование индикаторов");
    q21->addAnswer("Использование биотестов");
    q21->addAnswer("Контроль влажности обработанных изделий");
    q21Layout->setContentsMargins(0, 0, 0, 0);
    q21Layout->addWidget(q21);
    q21Widget->setLayout(q21Layout);
    testLayout->addWidget(q21Widget);

    QWidget *q22Widget = new QWidget(mainTestWidget);
    q22Widget->setFixedHeight(150);
    q22Widget->setObjectName("q1WObj");
    QVBoxLayout *q22Layout = new QVBoxLayout(q22Widget);
    Question *q22 = new Question (q22Widget, 4, true, 3);
    q22->addQuestion("Рабочий раствор хлорамина годен в течение:");
    q22->addAnswer("1 суток");
    q22->addAnswer("7 суток");
    q22->addAnswer("15 суток");
    q22->addAnswer("30 суток");
    q22Layout->setContentsMargins(0, 0, 0, 0);
    q22Layout->addWidget(q22);
    q22Widget->setLayout(q22Layout);
    testLayout->addWidget(q22Widget);

    QWidget *q23Widget = new QWidget(mainTestWidget);
    q23Widget->setFixedHeight(150);
    q23Widget->setObjectName("q1WObj");
    QVBoxLayout *q23Layout = new QVBoxLayout(q23Widget);
    Question *q23 = new Question (q23Widget, 3, true, 1);
    q23->addQuestion("Очистку и дезинфекцию фильтрующей системы кондиционера, расположенного в «заразной» зоне проводят:");
    q23->addAnswer("1 раз в 3 месяца");
    q23->addAnswer("2 раза в год");
    q23->addAnswer("1 раз в год");
    q23Layout->setContentsMargins(0, 0, 0, 0);
    q23Layout->addWidget(q23);
    q23Widget->setLayout(q23Layout);
    testLayout->addWidget(q23Widget);

    QWidget *q24Widget = new QWidget(mainTestWidget);
    q24Widget->setFixedHeight(150);
    q24Widget->setObjectName("q1WObj");
    QVBoxLayout *q24Layout = new QVBoxLayout(q24Widget);
    Question *q24 = new Question (q24Widget, 4, true, 2);
    q24->addQuestion("К какому классу относят медицинские отходы, содержащие ПБА 3-4 группы?");
    q24->addAnswer("А");
    q24->addAnswer("Б");
    q24->addAnswer("В");
    q24->addAnswer("Г");
    q24Layout->setContentsMargins(0, 0, 0, 0);
    q24Layout->addWidget(q24);
    q24Widget->setLayout(q24Layout);
    testLayout->addWidget(q24Widget);

    QWidget *q25Widget = new QWidget(mainTestWidget);
    q25Widget->setFixedHeight(180);
    q25Widget->setObjectName("q1WObj");
    QVBoxLayout *q25Layout = new QVBoxLayout(q25Widget);
    Question *q25 = new Question (q25Widget, 4, true, 2);
    q25->addQuestion("Заполнение мягкой упаковки медицинских отходов класса Б возможно:");
    q25->addAnswer("Не более чем на 1/2");
    q25->addAnswer("Не более чем на 3/4");
    q25->addAnswer("Не менее чем на 90 %");
    q25->addAnswer("Полностью");
    q25Layout->setContentsMargins(0, 0, 0, 0);
    q25Layout->addWidget(q25);
    q25Widget->setLayout(q25Layout);
    testLayout->addWidget(q25Widget);

    QWidget *q26Widget = new QWidget(mainTestWidget);
    q26Widget->setFixedHeight(180);
    q26Widget->setObjectName("q1WObj");
    QVBoxLayout *q26Layout = new QVBoxLayout(q26Widget);
    Question *q26 = new Question (q26Widget, 3, false, 2, 3);
    q26->addQuestion("К лаборатории, работающей с ПБА предъявляют следующие требования:");
    q26->addAnswer("Забор материала осуществляется в пределах помещений лаборатории");
    q26->addAnswer("Лаборатория должна размещаться в изолированной части здания или в отдельно стоящем здании");
    q26->addAnswer("Лаборатория должна быть строго зонирована");
    q26Layout->setContentsMargins(0, 0, 0, 0);
    q26Layout->addWidget(q26);
    q26Widget->setLayout(q26Layout);
    testLayout->addWidget(q26Widget);

    QWidget *q27Widget = new QWidget(mainTestWidget);
    q27Widget->setFixedHeight(180);
    q27Widget->setObjectName("q1WObj");
    QVBoxLayout *q27Layout = new QVBoxLayout(q27Widget);
    Question *q27 = new Question (q27Widget, 5, true, 3);
    q27->addQuestion("К медицинским отходам класса Б относят:");
    q27->addAnswer("Вакцины, непригодные к использованию");
    q27->addAnswer("Использованные средства личной гигиены");
    q27->addAnswer("Материалы и инструменты, контаминированные ПБА 3-4 группы патогенности");
    q27->addAnswer("Ртутьсодержащие отходы");
    q27->addAnswer("Пищевые отходы, образовавшиеся в лаборатории");
    q27Layout->setContentsMargins(0, 0, 0, 0);
    q27Layout->addWidget(q27);
    q27Widget->setLayout(q27Layout);
    testLayout->addWidget(q27Widget);

    QWidget *q28Widget = new QWidget(mainTestWidget);
    q28Widget->setFixedHeight(180);
    q28Widget->setObjectName("q1WObj");
    QVBoxLayout *q28Layout = new QVBoxLayout(q28Widget);
    Question *q28 = new Question (q28Widget, 4, true, 2);
    q28->addQuestion("В плановом порядке защитная одежда меняется:");
    q28->addAnswer("Ежедневно");
    q28->addAnswer("1 раз в неделю");
    q28->addAnswer("2 раза в месяц");
    q28->addAnswer("1 раз в месяц");
    q28Layout->setContentsMargins(0, 0, 0, 0);
    q28Layout->addWidget(q28);
    q28Widget->setLayout(q28Layout);
    testLayout->addWidget(q28Widget);

    QWidget *q29Widget = new QWidget(mainTestWidget);
    q29Widget->setFixedHeight(180);
    q29Widget->setObjectName("q1WObj");
    QVBoxLayout *q29Layout = new QVBoxLayout(q29Widget);
    Question *q29 = new Question (q29Widget, 5, false, 3, 4);
    q29->addQuestion("При нарушении целостности кожных покровов поврежденное место обрабатывают:");
    q29->addAnswer("3 % раствором перекиси водорода");
    q29->addAnswer("6 % раствором перекиси водорода");
    q29->addAnswer("5 % спиртовым раствором йода");
    q29->addAnswer("70 % спиртом");
    q29->addAnswer("96 % спиртом");
    q29Layout->setContentsMargins(0, 0, 0, 0);
    q29Layout->addWidget(q29);
    q29Widget->setLayout(q29Layout);
    testLayout->addWidget(q29Widget);

    QWidget *q30Widget = new QWidget(mainTestWidget);
    q30Widget->setFixedHeight(180);
    q30Widget->setObjectName("q1WObj");
    QVBoxLayout *q30Layout = new QVBoxLayout(q30Widget);
    Question *q30 = new Question (q30Widget, 5, true, 4);
    q30->addQuestion("При возможном попадании ПБА на кожные покровы это место обрабатывают:");
    q30->addAnswer("3 % раствором перекиси водорода");
    q30->addAnswer("6 % раствором перекиси водорода");
    q30->addAnswer("5 % спиртовым раствором йода");
    q30->addAnswer("70 % спиртом");
    q30->addAnswer("96 % спиртом");
    q30Layout->setContentsMargins(0, 0, 0, 0);
    q30Layout->addWidget(q30);
    q30Widget->setLayout(q30Layout);
    testLayout->addWidget(q30Widget);

    QWidget *q31Widget = new QWidget(mainTestWidget);
    q31Widget->setFixedHeight(180);
    q31Widget->setObjectName("q1WObj");
    QVBoxLayout *q31Layout = new QVBoxLayout(q31Widget);
    Question *q31 = new Question (q31Widget, 4, false, 1, 4);
    q31->addQuestion("При обращении с медицинскими отходами запрещается:");
    q31->addAnswer("Заполнять пакет с медицинскими отходами полностью");
    q31->addAnswer("Обеззараживать медицинские отходы");
    q31->addAnswer("Осуществлять любые манипуляции с медицинскими отходами в перчатках");
    q31->addAnswer("Утрамбовывать медицинские отходы");
    q31Layout->setContentsMargins(0, 0, 0, 0);
    q31Layout->addWidget(q31);
    q31Widget->setLayout(q31Layout);
    testLayout->addWidget(q31Widget);

    QWidget *q32Widget = new QWidget(mainTestWidget);
    q32Widget->setFixedHeight(180);
    q32Widget->setObjectName("q1WObj");
    QVBoxLayout *q32Layout = new QVBoxLayout(q32Widget);
    Question *q32 = new Question (q32Widget, 5, true, 4);
    q32->addQuestion("Смешение отходов различных классов в общем пакете:");
    q32->addAnswer("Допустимо при дефиците одноразовых пакетов");
    q32->addAnswer("Допустимо при соответствующей маркировке пакетов");
    q32->addAnswer("Зависит от классов отходов");
    q32->addAnswer("Недопустимо");
    q32->addAnswer("Допустимо");
    q32Layout->setContentsMargins(0, 0, 0, 0);
    q32Layout->addWidget(q32);
    q32Widget->setLayout(q32Layout);
    testLayout->addWidget(q32Widget);

    QWidget *q33Widget = new QWidget(mainTestWidget);
    q33Widget->setFixedHeight(180);
    q33Widget->setObjectName("q1WObj");
    QVBoxLayout *q33Layout = new QVBoxLayout(q33Widget);
    Question *q33 = new Question (q33Widget, 4, true, 1);
    q33->addQuestion("Тара, которая допускается для сбора отходов класса Б:");
    q33->addAnswer("Одноразовые пакеты");
    q33->addAnswer("Плотные мешки из водоотталкивающей ткани");
    q33->addAnswer("Бумажные мешки/пакеты");
    q33->addAnswer("Твёрдая картонная тара");
    q33Layout->setContentsMargins(0, 0, 0, 0);
    q33Layout->addWidget(q33);
    q33Widget->setLayout(q33Layout);
    testLayout->addWidget(q33Widget);

    QWidget *q34Widget = new QWidget(mainTestWidget);
    q34Widget->setFixedHeight(180);
    q34Widget->setObjectName("q1WObj");
    QVBoxLayout *q34Layout = new QVBoxLayout(q34Widget);
    Question *q34 = new Question (q34Widget, 4, false, 1, 2, 3);
    q34->addQuestion("При разлитии биологической жидкости необходимо:");
    q34->addAnswer("Абсорбировать пролитые жидкости");
    q34->addAnswer("Поверхность обработать дезинфицирующим средством");
    q34->addAnswer("Материалы, используемые для обеззараживания, поместить в отходы класса Б");
    q34->addAnswer("Через 2 часа обеззараженные материалы (осколки и др.) поместить в отходы класса А");
    q34Layout->setContentsMargins(0, 0, 0, 0);
    q34Layout->addWidget(q34);
    q34Widget->setLayout(q34Layout);
    testLayout->addWidget(q34Widget);

    QWidget *q35Widget = new QWidget(mainTestWidget);
    q35Widget->setFixedHeight(180);
    q35Widget->setObjectName("q1WObj");
    QVBoxLayout *q35Layout = new QVBoxLayout(q35Widget);
    Question *q35 = new Question (q35Widget, 4, true, 2);
    q35->addQuestion("Обязательный инструктаж по соблюдению требований биологической безопасности проходят:");
    q35->addAnswer("При приеме на работу");
    q35->addAnswer("При приеме на работу и затем ежегодно");
    q35->addAnswer("При приеме на работу и затем один раз в два года");
    q35->addAnswer("По желанию сотрудника");
    q35Layout->setContentsMargins(0, 0, 0, 0);
    q35Layout->addWidget(q35);
    q35Widget->setLayout(q35Layout);
    testLayout->addWidget(q35Widget);

    QWidget *q36Widget = new QWidget(mainTestWidget);
    q36Widget->setFixedHeight(180);
    q36Widget->setObjectName("q1WObj");
    QVBoxLayout *q36Layout = new QVBoxLayout(q36Widget);
    Question *q36 = new Question (q36Widget, 4, true, 3);
    q36->addQuestion("Обезвреживанием медицинских отходов называется:");
    q36->addAnswer("Изменение внешнего вида отходов, исключающее возможность их повторного использования");
    q36->addAnswer("Использование отходов в качестве вторичных ресурсов после соответствующей переработки");
    q36->addAnswer("Обработка отходов с применением технологий, ведущих к утрате всех опасных свойств");
    q36->addAnswer("Захоронение в местах, установленных действующим законодательством");
    q36Layout->setContentsMargins(0, 0, 0, 0);
    q36Layout->addWidget(q36);
    q36Widget->setLayout(q36Layout);
    testLayout->addWidget(q36Widget);

    QWidget *q37Widget = new QWidget(mainTestWidget);
    q37Widget->setFixedHeight(180);
    q37Widget->setObjectName("q1WObj");
    QVBoxLayout *q37Layout = new QVBoxLayout(q37Widget);
    Question *q37 = new Question (q37Widget, 3, true, 2);
    q37->addQuestion("Персонал лаборатории, работающей с ПБА 3-4 группы при работе с медицинскими отходами подвергается риску:");
    q37->addAnswer("Получения физической травмы");
    q37->addAnswer("Инфекционного заражения");
    q37->addAnswer("Токсического поражения");
    q37Layout->setContentsMargins(0, 0, 0, 0);
    q37Layout->addWidget(q37);
    q37Widget->setLayout(q37Layout);
    testLayout->addWidget(q37Widget);

    QWidget *q38Widget = new QWidget(mainTestWidget);
    q38Widget->setFixedHeight(180);
    q38Widget->setObjectName("q1WObj");
    QVBoxLayout *q38Layout = new QVBoxLayout(q38Widget);
    Question *q38 = new Question (q38Widget, 4, true, 4);
    q38->addQuestion("Химический метод дезинфекции предполагает применение:");
    q38->addAnswer("Паров моющих средств");
    q38->addAnswer("Водяного насыщенного пара");
    q38->addAnswer("Дистиллированной воды");
    q38->addAnswer("Растворов химических средств");
    q38Layout->setContentsMargins(0, 0, 0, 0);
    q38Layout->addWidget(q38);
    q38Widget->setLayout(q38Layout);
    testLayout->addWidget(q38Widget);

    QWidget *q39Widget = new QWidget(mainTestWidget);
    q39Widget->setFixedHeight(180);
    q39Widget->setObjectName("q1WObj");
    QVBoxLayout *q39Layout = new QVBoxLayout(q39Widget);
    Question *q39 = new Question (q39Widget, 4, false, 1, 4);
    q39->addQuestion("Время обеззараживания защитной одежды в 3 % растворе Хлорамина Б при работе с вируссодержащим материалом:");
    q39->addAnswer("Незагрязнённая –  30 минут");
    q39->addAnswer("Незагрязнённая –  60 минут");
    q39->addAnswer("Загрязнённая   –  60 минут");
    q39->addAnswer("Загрязнённая   – 120 минут");
    q39Layout->setContentsMargins(0, 0, 0, 0);
    q39Layout->addWidget(q39);
    q39Widget->setLayout(q39Layout);
    testLayout->addWidget(q39Widget);

    QWidget *q40Widget = new QWidget(mainTestWidget);
    q40Widget->setFixedHeight(180);
    q40Widget->setObjectName("q1WObj");
    QVBoxLayout *q40Layout = new QVBoxLayout(q40Widget);
    Question *q40 = new Question (q40Widget, 4, true, 4);
    q40->addQuestion("В помещениях «заразной» зоны проводят обеззараживание:");
    q40->addAnswer("Поверхностей");
    q40->addAnswer("Стоков");
    q40->addAnswer("Воздуха");
    q40->addAnswer("Всё перечисленное");
    q40Layout->setContentsMargins(0, 0, 0, 0);
    q40Layout->addWidget(q40);
    q40Widget->setLayout(q40Layout);
    testLayout->addWidget(q40Widget);

    QWidget *q41Widget = new QWidget(mainTestWidget);
    q41Widget->setFixedHeight(180);
    q41Widget->setObjectName("q1WObj");
    QVBoxLayout *q41Layout = new QVBoxLayout(q41Widget);
    Question *q41 = new Question (q41Widget, 3, true, 1);
    q41->addQuestion("Что такое биориск?");
    q41->addAnswer("Сочетание вероятности возникновения вредного воздействия и степени вредного воздействия в тех случаях, когда источником \nтакого воздействия является биологический агент");
    q41->addAnswer("Процесс высвобождения опасных биологических агентов на рабочем месте");
    q41->addAnswer("Опасность, происходящая от живых объектов");
    q41Layout->setContentsMargins(0, 0, 0, 0);
    q41Layout->addWidget(q41);
    q41Widget->setLayout(q41Layout);
    testLayout->addWidget(q41Widget);

    QWidget *q42Widget = new QWidget(mainTestWidget);
    q42Widget->setFixedHeight(180);
    q42Widget->setObjectName("q1WObj");
    QVBoxLayout *q42Layout = new QVBoxLayout(q42Widget);
    Question *q42 = new Question (q42Widget, 5, true, 5);
    q42->addQuestion("Какую информацию необходимо оценить для оценки биорисков?");
    q42->addAnswer("Работа с какими ПБА осуществляется в лаборатории и каковы их патогенные характеристики");
    q42->addAnswer("Какие виды лабораторных работ будут проводиться");
    q42->addAnswer("Какой тип оборудования будет использоваться");
    q42->addAnswer("Какие существуют человеческие факторы");
    q42->addAnswer("Всё перечисленное");
    q42Layout->setContentsMargins(0, 0, 0, 0);
    q42Layout->addWidget(q42);
    q42Widget->setLayout(q42Layout);
    testLayout->addWidget(q42Widget);

    QWidget *q43Widget = new QWidget(mainTestWidget);
    q43Widget->setFixedHeight(180);
    q43Widget->setObjectName("q1WObj");
    QVBoxLayout *q43Layout = new QVBoxLayout(q43Widget);
    Question *q43 = new Question (q43Widget, 4, false, 1, 3);
    q43->addQuestion("Ключевые аспекты системы оценки риска:");
    q43->addAnswer("Анализ биориска");
    q43->addAnswer("Учёт биориска");
    q43->addAnswer("Разработка стратегии по контролю биориска");
    q43->addAnswer("Наблюдение за биориском");
    q43Layout->setContentsMargins(0, 0, 0, 0);
    q43Layout->addWidget(q43);
    q43Widget->setLayout(q43Layout);
    testLayout->addWidget(q43Widget);

    QWidget *q44Widget = new QWidget(mainTestWidget);
    q44Widget->setFixedHeight(180);
    q44Widget->setObjectName("q1WObj");
    QVBoxLayout *q44Layout = new QVBoxLayout(q44Widget);
    Question *q44 = new Question (q44Widget, 3, true, 2);
    q44->addQuestion("Какова частота планового проведения оценки биорисков?");
    q44->addAnswer("1 раз в месяц");
    q44->addAnswer("1 раз в год");
    q44->addAnswer("1 раз в 5 лет");
    q44Layout->setContentsMargins(0, 0, 0, 0);
    q44Layout->addWidget(q44);
    q44Widget->setLayout(q44Layout);
    testLayout->addWidget(q44Widget);

    QWidget *q45Widget = new QWidget(mainTestWidget);
    q45Widget->setFixedHeight(180);
    q45Widget->setObjectName("q1WObj");
    QVBoxLayout *q45Layout = new QVBoxLayout(q45Widget);
    Question *q45 = new Question (q45Widget, 4, true, 4);
    q45->addQuestion("Что необходимо оценить с целью анализа вероятности возникновения риска по причине человеческих факторов?");
    q45->addAnswer("Структуру и штатную численность персонала");
    q45->addAnswer("Образование, квалификацию, опыту работы, профессиональную подготовку, технические знания и навыки");
    q45->addAnswer("Качество выполнения работ, исследований и соответствии их требованиям нормативной документации");
    q45->addAnswer("Всё перечисленное");
    q45Layout->setContentsMargins(0, 0, 0, 0);
    q45Layout->addWidget(q45);
    q45Widget->setLayout(q45Layout);
    testLayout->addWidget(q45Widget);

    QWidget *q46Widget = new QWidget(mainTestWidget);
    q46Widget->setFixedHeight(180);
    q46Widget->setObjectName("q1WObj");
    QVBoxLayout *q46Layout = new QVBoxLayout(q46Widget);
    Question *q46 = new Question (q46Widget, 4, false, 2, 4);
    q46->addQuestion("Кто осуществляет оценку биориска?");
    q46->addAnswer("Представитель отдела юридического обеспечения");
    q46->addAnswer("Комиссия по соблюдению требований биологической безопасности");
    q46->addAnswer("Руководитель лаборатории");
    q46->addAnswer("Представитель хозяйственного отдела");
    q46Layout->setContentsMargins(0, 0, 0, 0);
    q46Layout->addWidget(q46);
    q46Widget->setLayout(q46Layout);
    testLayout->addWidget(q46Widget);

    QWidget *q47Widget = new QWidget(mainTestWidget);
    q47Widget->setFixedHeight(180);
    q47Widget->setObjectName("q1WObj");
    QVBoxLayout *q47Layout = new QVBoxLayout(q47Widget);
    Question *q47 = new Question (q47Widget, 4, false, 1, 3);
    q47->addQuestion("Факторы, влияющие на высокую вероятность возникновения инцидента:");
    q47->addAnswer("Лабораторные мероприятия, связанные с аэрозолизацией");
    q47->addAnswer("Низкая инфекционная доза ПБА");
    q47->addAnswer("Лабораторная деятельность, связанная с использованием колющих предметов");
    q47->addAnswer("Высокий уровень компетентности персонала, выполняющего работы");
    q47Layout->setContentsMargins(0, 0, 0, 0);
    q47Layout->addWidget(q47);
    q47Widget->setLayout(q47Layout);
    testLayout->addWidget(q47Widget);

    QWidget *q48Widget = new QWidget(mainTestWidget);
    q48Widget->setFixedHeight(100);
    q48Widget->setObjectName("q1WObj");
    QVBoxLayout *q48Layout = new QVBoxLayout(q48Widget);
    Question *q48 = new Question (q48Widget, 2, true, 1);
    q48->addQuestion("Является ли фактором, влияющим на высокую вероятность возникновения инцидента, большой объём проводимых исследований?");
    q48->addAnswer("Да");
    q48->addAnswer("Нет");
    q48Layout->setContentsMargins(0, 0, 0, 0);
    q48Layout->addWidget(q48);
    q48Widget->setLayout(q48Layout);
    testLayout->addWidget(q48Widget);

    QWidget *q49Widget = new QWidget(mainTestWidget);
    q49Widget->setFixedHeight(180);
    q49Widget->setObjectName("q1WObj");
    QVBoxLayout *q49Layout = new QVBoxLayout(q49Widget);
    Question *q49 = new Question (q49Widget, 4, false, 1, 3);
    q49->addQuestion("Какие лабораторные мероприятия, связанные с аэрозолизацией осуществляются в вирусологической лаборатории?");
    q49->addAnswer("Заражение клеточных культур инфекционным (в том числе пассажным) материалом");
    q49->addAnswer("Микроскопия заражённых клеточных культур");
    q49->addAnswer("Пипетирование (титрование) вируссодержащего материала");
    q49->addAnswer("Обеззараживание инфекционного материала");
    q49Layout->setContentsMargins(0, 0, 0, 0);
    q49Layout->addWidget(q49);
    q49Widget->setLayout(q49Layout);
    testLayout->addWidget(q49Widget);

    QWidget *q50Widget = new QWidget(mainTestWidget);
    q50Widget->setFixedHeight(180);
    q50Widget->setObjectName("q1WObj");
    QVBoxLayout *q50Layout = new QVBoxLayout(q50Widget);
    Question *q50 = new Question (q50Widget, 5, true, 5);
    q50->addQuestion("Стратегии для снижения и контроля рисков:");
    q50->addAnswer("Ликвидация ПБА");
    q50->addAnswer("Снижение и замена ПБА");
    q50->addAnswer("Защита персонала/окружающей среды");
    q50->addAnswer("Соблюдение требований биологической безопасности");
    q50->addAnswer("Всё перечисленное");
    q50Layout->setContentsMargins(0, 0, 0, 0);
    q50Layout->addWidget(q50);
    q50Widget->setLayout(q50Layout);
    testLayout->addWidget(q50Widget);

    questionsVec = {q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, q26, q27, q28, q29, q30, q31, q32, q33, q34, q35, q36, q37, q38, q39, q40, q41, q42, q43, q44, q45, q46, q47, q48, q49, q50};
    questionWidgets = {q1Widget, q2Widget, q3Widget, q4Widget, q5Widget, q6Widget, q7Widget, q8Widget, q9Widget, q10Widget, q11Widget, q12Widget, q13Widget, q14Widget, q15Widget, q16Widget, q17Widget, q18Widget, q19Widget, q20Widget, q21Widget, q22Widget, q23Widget, q24Widget, q25Widget, q26Widget, q27Widget, q28Widget, q29Widget, q30Widget, q31Widget, q32Widget, q33Widget, q34Widget, q35Widget, q36Widget, q37Widget, q38Widget, q39Widget, q40Widget, q41Widget, q42Widget, q43Widget, q44Widget, q45Widget, q46Widget, q47Widget, q48Widget, q49Widget, q50Widget};
    beforeShuffledW = questionWidgets;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(questionWidgets.begin(), questionWidgets.end(), gen);
    std::vector<size_t> indices(questionWidgets.size());

    for (size_t i = 0; i < 20 && !questionWidgets.empty(); ++i)
    {
        QWidget* el = questionWidgets[i];
        el->hide();
        el->deleteLater();
    }

    int counter = 1;
    for (auto el : beforeShuffledW)
    {
        if (el && !el->isHidden())
        { // Проверка, чтобы избежать доступа к скрытым и удаленным виджетам
            Question* q = el->findChild<Question*>();
            QString iStr = QString::number(counter);
            q->getQuestion()->setText(iStr + " " + q->getQuestion()->text());
            ++counter;
        }
    }
}

void Test::doctorVirologistTest()
{
    fioLayout->addWidget(fioL);
    fioLayout->addWidget(fioInput);
    fioL->setText("Укажите ФИО");
    fioW->setMaximumHeight(75);
    fioW->setLayout(fioLayout);
    testLayout->addWidget(fioW);
    fioW->setObjectName("q1WObj");

    QWidget *dataWidget = new QWidget(mainTestWidget);
    QVBoxLayout *dataLayout = new QVBoxLayout;
    dataWidget->setLayout(dataLayout);
    dataWidget->setObjectName("q1WObj");
    dataWidget->setMaximumHeight(75);
    testLayout->addWidget(dataWidget);
    inputTodayData = new QTextEdit(dataWidget);
    QLabel *dataInputInfo = new QLabel(dataWidget);
    dataInputInfo->setText("Введите дату прохождения теста");
    dataInputInfo->setStyleSheet("color: black;");
    inputTodayData->setMaximumHeight(25);
    dataLayout->addWidget(dataInputInfo);
    dataLayout->addWidget(inputTodayData);

    QWidget *q1Widget = new QWidget(mainTestWidget);
    q1Widget->setFixedHeight(210);
    q1Widget->setObjectName("q1WObj");
    QVBoxLayout *q1Layout = new QVBoxLayout(q1Widget);
    Question* q1 = new Question(q1Widget, 3, true, 3);
    q1->addQuestion("Какой нормативный документ на сегодняшний день определяет санитарно-эпидемиологические требования к обеспечению \nбезопасности при работе с ПБА?");
    q1->addAnswer("СП 1.2.731-99«Безопасность работы с микроорганизмами III - IV групп патогенности и гельминтами»");
    q1->addAnswer("СП 1.3.2322-08 «Безопасность работы с микроорганизмами III - IV групп патогенности (опасности) и возбудителями \nпаразитарных болезней»");
    q1->addAnswer("СанПиН 3.3686-21 «Санитарно-эпидемиологические требования по профилактике инфекционных болезней»");
    q1Layout->setContentsMargins(0, 0, 0, 0);
    q1Layout->addWidget(q1);
    q1Widget->setLayout(q1Layout);
    testLayout->addWidget(q1Widget);

    QWidget *q2Widget = new QWidget(mainTestWidget);
    q2Widget->setFixedHeight(200);
    q2Widget->setObjectName("q1WObj");
    QVBoxLayout *q2Layout = new QVBoxLayout(q2Widget);
    Question *q2 = new Question (q2Widget, 3, true, 2);
    q2->addQuestion("С какой целью разработаны Санитарные правила и нормы СанПиН 3.3686-21 «Санитарно-эпидемиологические требования по \nпрофилактике инфекционных болезней»?");
    q2->addAnswer("С целью обеспечения безопасности сотрудников лаборатории");
    q2->addAnswer("С целью предупреждения возникновения и распространения инфекционных болезней среди населения");
    q2->addAnswer("С целью обеспечения безопасности всех сотрудников учреждения");
    q2Layout->setContentsMargins(0, 0, 0, 0);
    q2Layout->addWidget(q2);
    q2Widget->setLayout(q2Layout);
    testLayout->addWidget(q2Widget);

    QWidget *q3Widget = new QWidget(mainTestWidget);
    q3Widget->setFixedHeight(400);
    q3Widget->setObjectName("q1WObj");
    QVBoxLayout *q3Layout = new QVBoxLayout(q3Widget);
    Question *q3 = new Question (q3Widget, 4, false, 1, 3, 4);
    q3->addQuestion("Санитарные правила СанПиН 3.3686-21 устанавливают обязательные требования:");
    q3->addAnswer("К комплексу организационных, профилактических, санитарно-противоэпидемических, лабораторно-диагностических мероприятий, \nнаправленных на обеспечение раннего выявления, предупреждения возникновения и распространения инфекционных \nболезней среди населения ");
    q3->addAnswer("К осуществлению сбора, обеззараживания, обезвреживания, временного хранения и удаления медицинских отходов");
    q3->addAnswer("К порядку учета, хранения, передачи и транспортирования ПБА, а также объектов и материалов, содержащих или подозрительных \nна содержание ПБА");
    q3->addAnswer("<html>К организационным, санитарно-противоэпидемическим (профилактическим), инженерно-техническим мероприятиям, направленным на <br>обеспечение личной и общественной безопасности, защиту окружающей среды при работе с микроорганизмами, вирусами, <br>белковоподобными инфекционными частицами (прионами), ядами биологического происхождения (токсинами) и иными <br>биологическими агентами, в том числе созданными в результате генетических манипуляций, применения технологий <br>синтетической биологии и другой направленной деятельности, способных вызывать патологический процесс в <br>организме человека или животного, а также биологические материалы, в которых могут содержаться перечисленные ПБА</html>");
    q3Layout->setContentsMargins(0, 0, 0, 0);
    q3Layout->addWidget(q3);
    q3Widget->setLayout(q3Layout);
    testLayout->addWidget(q3Widget);

    QWidget *q4Widget = new QWidget(mainTestWidget);
    q4Widget->setFixedHeight(180);
    q4Widget->setObjectName("q1WObj");
    QVBoxLayout *q4Layout = new QVBoxLayout(q4Widget);
    Question *q4 = new Question (q4Widget, 4, true, 4);
    q4->addQuestion("При приёме на работу, связанную с использованием ПБА 3-4 групп, персонал проходит:");
    q4->addAnswer("Вводный инструктаж по биологической безопасности");
    q4->addAnswer("Предварительный медицинский осмотр с целью выявления медицинских противопоказаний к вакцинопрофилактике");
    q4->addAnswer("Оценку уровня специфического иммунитета для определения необходимости их иммунизации от управляемых инфекций");
    q4->addAnswer("Всё перечисленное");
    q4Layout->setContentsMargins(0, 0, 0, 0);
    q4Layout->addWidget(q4);
    q4Widget->setLayout(q4Layout);
    testLayout->addWidget(q4Widget);

    QWidget *q5Widget = new QWidget(mainTestWidget);
    q5Widget->setFixedHeight(150);
    q5Widget->setObjectName("q1WObj");
    QVBoxLayout *q5Layout = new QVBoxLayout(q5Widget);
    Question *q5 = new Question (q5Widget, 4, true, 2);
    q5->addQuestion("Обязательный инструктаж по соблюдению требований биологической безопасности проходят:");
    q5->addAnswer("При приеме на работу");
    q5->addAnswer("При приеме на работу и затем ежегодно");
    q5->addAnswer("При приеме на работу и затем один раз в два года");
    q5->addAnswer("По желанию сотрудника");
    q5Layout->setContentsMargins(0, 0, 0, 0);
    q5Layout->addWidget(q5);
    q5Widget->setLayout(q5Layout);
    testLayout->addWidget(q5Widget);

    QWidget *q6Widget = new QWidget(mainTestWidget);
    q6Widget->setFixedHeight(150);
    q6Widget->setObjectName("q1WObj");
    QVBoxLayout *q6Layout = new QVBoxLayout(q6Widget);
    Question *q6 = new Question (q6Widget, 4, false, 1, 2);
    q6->addQuestion("Методы обеззараживания инфекционного материала");
    q6->addAnswer("Химический");
    q6->addAnswer("Физический");
    q6->addAnswer("Биологический");
    q6->addAnswer("Измельчение");
    q6Layout->setContentsMargins(0, 0, 0, 0);
    q6Layout->addWidget(q6);
    q6Widget->setLayout(q6Layout);
    testLayout->addWidget(q6Widget);

    QWidget *q7Widget = new QWidget(mainTestWidget);
    q7Widget->setFixedHeight(150);
    q7Widget->setObjectName("q1WObj");
    QVBoxLayout *q7Layout = new QVBoxLayout(q7Widget);
    Question *q7 = new Question (q7Widget, 4, false, 1, 2, 4);
    q7->addQuestion("Что относят к физическим методам обеззараживания инфекционного материала?");
    q7->addAnswer("Обработка водяным насыщенным паром под давлением");
    q7->addAnswer("Ультрафиолетовое излучение");
    q7->addAnswer("Обработка 70 % спиртом");
    q7->addAnswer("Сжигание");
    q7Layout->setContentsMargins(0, 0, 0, 0);
    q7Layout->addWidget(q7);
    q7Widget->setLayout(q7Layout);
    testLayout->addWidget(q7Widget);

    QWidget *q8Widget = new QWidget(mainTestWidget);
    q8Widget->setFixedHeight(150);
    q8Widget->setObjectName("q1WObj");
    QVBoxLayout *q8Layout = new QVBoxLayout(q8Widget);
    Question *q8 = new Question (q8Widget, 4, false, 1, 2, 3);
    q8->addQuestion("Методы контроля работы паровых и воздушных стерилизаторов, используемых для обеззараживания ПБА:");
    q8->addAnswer("Химический");
    q8->addAnswer("Физический");
    q8->addAnswer("Биологический");
    q8->addAnswer("Учёт показаний манометра");
    q8Layout->setContentsMargins(0, 0, 0, 0);
    q8Layout->addWidget(q8);
    q8Widget->setLayout(q8Layout);
    testLayout->addWidget(q8Widget);

    QWidget *q9Widget = new QWidget(mainTestWidget);
    q9Widget->setFixedHeight(150);
    q9Widget->setObjectName("q1WObj");
    QVBoxLayout *q9Layout = new QVBoxLayout(q9Widget);
    Question *q9 = new Question (q9Widget, 4, true, 3);
    q9->addQuestion("Кратность планового биологического контроля паровых и воздушных стерилиза-торов, используемых для обеззараживания ПБА:");
    q9->addAnswer("2 раза в месяц");
    q9->addAnswer("2 раза в квартал");
    q9->addAnswer("2 раза в год");
    q9->addAnswer("1 раз в год");
    q9Layout->setContentsMargins(0, 0, 0, 0);
    q9Layout->addWidget(q9);
    q9Widget->setLayout(q9Layout);
    testLayout->addWidget(q9Widget);

    QWidget *q10Widget = new QWidget(mainTestWidget);
    q10Widget->setFixedHeight(200);
    q10Widget->setObjectName("q1WObj");
    QVBoxLayout *q10Layout = new QVBoxLayout(q10Widget);
    Question *q10 = new Question (q10Widget, 4, true, 1);
    q10->addQuestion("Какой режим паровой стерилизации необходимо использовать для обеззараживания вируссодержащей жидкости, взвеси \nзараженной культуры клеток?");
    q10->addAnswer("Водяной насыщенный пар под давлением 2,0 кгс/см2, (132 +/- 2) °C, 60 минут");
    q10->addAnswer("Водяной насыщенный пар под давлением 2,0 кгс/см2, (132 +/- 2) °C, 45 минут");
    q10->addAnswer("Водяной насыщенный пар под давлением 1,1 кгс/см2, (120 +/- 2) °C, 45 минут");
    q10->addAnswer("Водяной насыщенный пар под давлением 1,1 кгс/см2, (120 +/- 2) °C, 20 минут");
    q10Layout->setContentsMargins(0, 0, 0, 0);
    q10Layout->addWidget(q10);
    q10Widget->setLayout(q10Layout);
    testLayout->addWidget(q10Widget);

    QWidget *q11Widget = new QWidget(mainTestWidget);
    q11Widget->setFixedHeight(150);
    q11Widget->setObjectName("q1WObj");
    QVBoxLayout *q11Layout = new QVBoxLayout(q11Widget);
    Question *q11 = new Question (q11Widget, 3, false, 2, 3);
    q11->addQuestion("Внеплановую проверку эксплуатационных характеристик боксов микробиологической безопасности проводят при:");
    q11->addAnswer("Замене инженерно-технического персонала");
    q11->addAnswer("Монтаже и вводе в эксплуатацию");
    q11->addAnswer("После перемещения и/или ремонта");    q11Layout->setContentsMargins(0, 0, 0, 0);
    q11Layout->addWidget(q11);
    q11Widget->setLayout(q11Layout);
    testLayout->addWidget(q11Widget);

    QWidget *q12Widget = new QWidget(mainTestWidget);
    q12Widget->setFixedHeight(180);
    q12Widget->setObjectName("q1WObj");
    QVBoxLayout *q12Layout = new QVBoxLayout(q12Widget);
    Question *q12 = new Question (q12Widget, 3, false, 1, 2);
    q12->addQuestion("Виды аварий при работе с патогенными биологическими агентами:");
    q12->addAnswer("Авария, связанная с нарушением целостности кожных покровов");
    q12->addAnswer("Авария, связанная с нарушением целостности средств индивидуальной защиты");
    q12->addAnswer("Авария, связанная с нарушением методики выполнения исследований");
    q12Layout->setContentsMargins(0, 0, 0, 0);
    q12Layout->addWidget(q12);
    q12Widget->setLayout(q12Layout);
    testLayout->addWidget(q12Widget);

    QWidget *q13Widget = new QWidget(mainTestWidget);
    q13Widget->setFixedHeight(170);
    q13Widget->setObjectName("q1WObj");
    QVBoxLayout *q13Layout = new QVBoxLayout(q13Widget);
    Question *q13 = new Question (q13Widget, 3, false, 1, 2, 4);
    q13->addQuestion("По сигналу «авария» сотрудник, принявший сигнал, сообщает руководителю подразделения:");
    q13->addAnswer("Характер аварии");
    q13->addAnswer("Произошло ли попадание инфекционного материала на кожные покровы");
    q13->addAnswer("Информацию о запасе СИЗ в лаборатории");
    q13->addAnswer("Количество пострадавших");
    q13->addAnswer("Информацию об исправности аварийной сигнализации");
    q13Layout->setContentsMargins(0, 0, 0, 0);
    q13Layout->addWidget(q13);
    q13Widget->setLayout(q13Layout);
    testLayout->addWidget(q13Widget);

    QWidget *q14Widget = new QWidget(mainTestWidget);
    q14Widget->setFixedHeight(180);
    q14Widget->setObjectName("q1WObj");
    QVBoxLayout *q14Layout = new QVBoxLayout(q14Widget);
    Question *q14 = new Question (q14Widget, 4, true, 2);
    q14->addQuestion("В состав аварийной аптечки входит:");
    q14->addAnswer("Спирт этиловый 70%, йод, антибиотики, перевязочные средства");
    q14->addAnswer("Спирт этиловый 70%, йод, нашатырный спирт, жгут кровоостанавливающий, перевязочные средства");
    q14->addAnswer("Спирт этиловый 70%, йод, нашатырный спирт, жгут кровоостанавливающий, жаропонижающие препараты ");
    q14->addAnswer("Спирт этиловый 70%, йод, нашатырный спирт, жгут кровоостанавливающий, антигистаминные средства ");
    q14Layout->setContentsMargins(0, 0, 0, 0);
    q14Layout->addWidget(q14);
    q14Widget->setLayout(q14Layout);
    testLayout->addWidget(q14Widget);

    QWidget *q15Widget = new QWidget(mainTestWidget);
    q15Widget->setFixedHeight(150);
    q15Widget->setObjectName("q1WObj");
    QVBoxLayout *q15Layout = new QVBoxLayout(q15Widget);
    Question *q15 = new Question (q15Widget, 4, true, 3);
    q15->addQuestion("Аварийная сигнализация в помещениях «заразной» зоны предусмотрена на случай:");
    q15->addAnswer("Пожара");
    q15->addAnswer("Вызова сотрудника при большом объёме работ");
    q15->addAnswer("Аварийных ситуаций при работе с ПБА");
    q15Layout->setContentsMargins(0, 0, 0, 0);
    q15Layout->addWidget(q15);
    q15Widget->setLayout(q15Layout);
    testLayout->addWidget(q15Widget);

    QWidget *q16Widget = new QWidget(mainTestWidget);
    q16Widget->setFixedHeight(150);
    q16Widget->setObjectName("q1WObj");
    QVBoxLayout *q16Layout = new QVBoxLayout(q16Widget);
    Question *q16 = new Question (q16Widget, 4, false, 1, 2, 3);
    q16->addQuestion("Пути уменьшения количества аварий при работе с ПБА:");
    q16->addAnswer("Регулярные инструктажи по технике безопасности и биобезопасности");
    q16->addAnswer("Воспитание чувства личной ответственности");
    q16->addAnswer("Проведение учений по действиям во время аварийных ситуаций");
    q16->addAnswer("Узкая специализация труда («отточенные» навыки)");
    q16Layout->setContentsMargins(0, 0, 0, 0);
    q16Layout->addWidget(q16);
    q16Widget->setLayout(q16Layout);
    testLayout->addWidget(q16Widget);

    QWidget *q17Widget = new QWidget(mainTestWidget);
    q17Widget->setFixedHeight(180);
    q17Widget->setObjectName("q1WObj");
    QVBoxLayout *q17Layout = new QVBoxLayout(q17Widget);
    Question *q17 = new Question (q17Widget, 4, false, 1, 2, 4);
    q17->addQuestion("Организационные мероприятия по биологической и физической защите включают:");
    q17->addAnswer("Организация охраны помещений для работ и хранения ПБА");
    q17->addAnswer("Организация запирающихся хранилищ");
    q17->addAnswer("Соблюдение методик при работе с ПБА");
    q17->addAnswer("Контроль доступа в отношении ПБА");
    q17Layout->setContentsMargins(0, 0, 0, 0);
    q17Layout->addWidget(q17);
    q17Widget->setLayout(q17Layout);
    testLayout->addWidget(q17Widget);

    QWidget *q18Widget = new QWidget(mainTestWidget);
    q18Widget->setFixedHeight(150);
    q18Widget->setObjectName("q1WObj");
    QVBoxLayout *q18Layout = new QVBoxLayout(q18Widget);
    Question *q18 = new Question (q18Widget, 4, true, 3);
    q18->addQuestion("Время непрерывной работы с ПБА:");
    q18->addAnswer("1 час");
    q18->addAnswer("2 часа");
    q18->addAnswer("4 часа");
    q18->addAnswer("6 часов");
    q18Layout->setContentsMargins(0, 0, 0, 0);
    q18Layout->addWidget(q18);
    q18Widget->setLayout(q18Layout);
    testLayout->addWidget(q18Widget);

    QWidget *q19Widget = new QWidget(mainTestWidget);
    q19Widget->setFixedHeight(150);
    q19Widget->setObjectName("q1WObj");
    QVBoxLayout *q19Layout = new QVBoxLayout(q19Widget);
    Question *q19 = new Question (q19Widget, 4, true, 1);
    q19->addQuestion("Какой минимальный запас дезинфицирующих средств в лаборатории, работающей с ПБА?");
    q19->addAnswer("1 неделя");
    q19->addAnswer("2 недели");
    q19->addAnswer("1 месяц");
    q19->addAnswer("1 квартал");
    q19Layout->setContentsMargins(0, 0, 0, 0);
    q19Layout->addWidget(q19);
    q19Widget->setLayout(q19Layout);
    testLayout->addWidget(q19Widget);

    QWidget *q20Widget = new QWidget(mainTestWidget);
    q20Widget->setFixedHeight(150);
    q20Widget->setObjectName("q1WObj");
    QVBoxLayout *q20Layout = new QVBoxLayout(q20Widget);
    Question *q20 = new Question (q20Widget, 4, true, 2);
    q20->addQuestion("В плановом порядке защитная одежда меняется:");
    q20->addAnswer("Ежедневно");
    q20->addAnswer("1 раз в неделю");
    q20->addAnswer("2 раза в месяц");
    q20->addAnswer("1 раз в месяц");
    q20Layout->setContentsMargins(0, 0, 0, 0);
    q20Layout->addWidget(q20);
    q20Widget->setLayout(q20Layout);
    testLayout->addWidget(q20Widget);

    QWidget *q21Widget = new QWidget(mainTestWidget);
    q21Widget->setFixedHeight(150);
    q21Widget->setObjectName("q1WObj");
    QVBoxLayout *q21Layout = new QVBoxLayout(q21Widget);
    Question *q21 = new Question (q21Widget, 4, true, 2);
    q21->addQuestion("Что предусматривает химический контроль режима стерилизации?");
    q21->addAnswer("Контроль работы манометров стерилизатора");
    q21->addAnswer("Использование индикаторов");
    q21->addAnswer("Использование биотестов");
    q21->addAnswer("Контроль влажности обработанных изделий");
    q21Layout->setContentsMargins(0, 0, 0, 0);
    q21Layout->addWidget(q21);
    q21Widget->setLayout(q21Layout);
    testLayout->addWidget(q21Widget);

    QWidget *q22Widget = new QWidget(mainTestWidget);
    q22Widget->setFixedHeight(150);
    q22Widget->setObjectName("q1WObj");
    QVBoxLayout *q22Layout = new QVBoxLayout(q22Widget);
    Question *q22 = new Question (q22Widget, 4, true, 3);
    q22->addQuestion("Рабочий раствор хлорамина годен в течение:");
    q22->addAnswer("1 суток");
    q22->addAnswer("7 суток");
    q22->addAnswer("15 суток");
    q22->addAnswer("30 суток");
    q22Layout->setContentsMargins(0, 0, 0, 0);
    q22Layout->addWidget(q22);
    q22Widget->setLayout(q22Layout);
    testLayout->addWidget(q22Widget);

    QWidget *q23Widget = new QWidget(mainTestWidget);
    q23Widget->setFixedHeight(150);
    q23Widget->setObjectName("q1WObj");
    QVBoxLayout *q23Layout = new QVBoxLayout(q23Widget);
    Question *q23 = new Question (q23Widget, 3, true, 1);
    q23->addQuestion("Очистку и дезинфекцию фильтрующей системы кондиционера, расположенного в «заразной» зоне проводят:");
    q23->addAnswer("1 раз в 3 месяца");
    q23->addAnswer("2 раза в год");
    q23->addAnswer("1 раз в год");
    q23Layout->setContentsMargins(0, 0, 0, 0);
    q23Layout->addWidget(q23);
    q23Widget->setLayout(q23Layout);
    testLayout->addWidget(q23Widget);

    QWidget *q24Widget = new QWidget(mainTestWidget);
    q24Widget->setFixedHeight(150);
    q24Widget->setObjectName("q1WObj");
    QVBoxLayout *q24Layout = new QVBoxLayout(q24Widget);
    Question *q24 = new Question (q24Widget, 4, true, 2);
    q24->addQuestion("К какому классу относят медицинские отходы, содержащие ПБА 3-4 группы?");
    q24->addAnswer("А");
    q24->addAnswer("Б");
    q24->addAnswer("В");
    q24->addAnswer("Г");
    q24Layout->setContentsMargins(0, 0, 0, 0);
    q24Layout->addWidget(q24);
    q24Widget->setLayout(q24Layout);
    testLayout->addWidget(q24Widget);

    QWidget *q25Widget = new QWidget(mainTestWidget);
    q25Widget->setFixedHeight(180);
    q25Widget->setObjectName("q1WObj");
    QVBoxLayout *q25Layout = new QVBoxLayout(q25Widget);
    Question *q25 = new Question (q25Widget, 4, true, 2);
    q25->addQuestion("Заполнение мягкой упаковки медицинских отходов класса Б возможно:");
    q25->addAnswer("Не более чем на 1/2");
    q25->addAnswer("Не более чем на 3/4");
    q25->addAnswer("Не менее чем на 90 %");
    q25->addAnswer("Полностью");
    q25Layout->setContentsMargins(0, 0, 0, 0);
    q25Layout->addWidget(q25);
    q25Widget->setLayout(q25Layout);
    testLayout->addWidget(q25Widget);

    QWidget *q26Widget = new QWidget(mainTestWidget);
    q26Widget->setFixedHeight(180);
    q26Widget->setObjectName("q1WObj");
    QVBoxLayout *q26Layout = new QVBoxLayout(q26Widget);
    Question *q26 = new Question (q26Widget, 3, true, 3);
    q26->addQuestion("К медицинским отходам класса Б относят:");
    q26->addAnswer("Вакцины, непригодные к использованию");
    q26->addAnswer("Использованные средства личной гигиены");
    q26->addAnswer("Материалы и инструменты, контаминированные ПБА 3-4 группы патогенности");
    q26->addAnswer("Ртутьсодержащие отходы");
    q26->addAnswer("Пищевые отходы, образовавшиеся в лаборатории");
    q26Layout->setContentsMargins(0, 0, 0, 0);
    q26Layout->addWidget(q26);
    q26Widget->setLayout(q26Layout);
    testLayout->addWidget(q26Widget);

    QWidget *q27Widget = new QWidget(mainTestWidget);
    q27Widget->setFixedHeight(150);
    q27Widget->setObjectName("q1WObj");
    QVBoxLayout *q27Layout = new QVBoxLayout(q27Widget);
    Question *q27 = new Question (q27Widget, 3, false, 2, 3);
    q27->addQuestion("К лаборатории, работающей с ПБА предъявляют следующие требования:");
    q27->addAnswer("Забор материала осуществляется в пределах помещений лаборатории");
    q27->addAnswer("Лаборатория должна размещаться в изолированной части здания или в отдельно стоящем здании");
    q27->addAnswer("Лаборатория должна быть строго зонирована");
    q27Layout->setContentsMargins(0, 0, 0, 0);
    q27Layout->addWidget(q27);
    q27Widget->setLayout(q27Layout);
    testLayout->addWidget(q27Widget);

    QWidget *q28Widget = new QWidget(mainTestWidget);
    q28Widget->setFixedHeight(180);
    q28Widget->setObjectName("q1WObj");
    QVBoxLayout *q28Layout = new QVBoxLayout(q28Widget);
    Question *q28 = new Question (q28Widget, 5, false, 3, 4);
    q28->addQuestion("При нарушении целостности кожных покровов поврежденное место обрабатывают:");
    q28->addAnswer("3 % раствором перекиси водорода");
    q28->addAnswer("6 % раствором перекиси водорода");
    q28->addAnswer("5 % спиртовым раствором йода");
    q28->addAnswer("70 % спиртом");
    q28->addAnswer("96 % спиртом");
    q28Layout->setContentsMargins(0, 0, 0, 0);
    q28Layout->addWidget(q28);
    q28Widget->setLayout(q28Layout);
    testLayout->addWidget(q28Widget);

    QWidget *q29Widget = new QWidget(mainTestWidget);
    q29Widget->setFixedHeight(180);
    q29Widget->setObjectName("q1WObj");
    QVBoxLayout *q29Layout = new QVBoxLayout(q29Widget);
    Question *q29 = new Question (q29Widget, 5, true, 4);
    q29->addQuestion("При возможном попадании ПБА на кожные покровы это место обрабатывают:");
    q29->addAnswer("3 % раствором перекиси водорода");
    q29->addAnswer("6 % раствором перекиси водорода");
    q29->addAnswer("5 % спиртовым раствором йода");
    q29->addAnswer("70 % спиртом");
    q29->addAnswer("96 % спиртом");
    q29Layout->setContentsMargins(0, 0, 0, 0);
    q29Layout->addWidget(q29);
    q29Widget->setLayout(q29Layout);
    testLayout->addWidget(q29Widget);

    QWidget *q30Widget = new QWidget(mainTestWidget);
    q30Widget->setFixedHeight(180);
    q30Widget->setObjectName("q1WObj");
    QVBoxLayout *q30Layout = new QVBoxLayout(q30Widget);
    Question *q30 = new Question (q30Widget, 4, true, 3);
    q30->addQuestion("При возможном попадании ПБА на слизистую глаз проводят обработку:");
    q30->addAnswer("Альбуцидом");
    q30->addAnswer("Искусственной слезой");
    q30->addAnswer("Водой");
    q30->addAnswer("Антиаллергическими средствами");
    q30Layout->setContentsMargins(0, 0, 0, 0);
    q30Layout->addWidget(q30);
    q30Widget->setLayout(q30Layout);
    testLayout->addWidget(q30Widget);

    QWidget *q31Widget = new QWidget(mainTestWidget);
    q31Widget->setFixedHeight(180);
    q31Widget->setObjectName("q1WObj");
    QVBoxLayout *q31Layout = new QVBoxLayout(q31Widget);
    Question *q31 = new Question (q31Widget, 4, false, 1, 4);
    q31->addQuestion("При обращении с медицинскими отходами запрещается:");
    q31->addAnswer("Заполнять пакет с медицинскими отходами полностью");
    q31->addAnswer("Обеззараживать медицинские отходы");
    q31->addAnswer("Осуществлять любые манипуляции с медицинскими отходами в перчатках");
    q31->addAnswer("Утрамбовывать медицинские отходы");
    q31Layout->setContentsMargins(0, 0, 0, 0);
    q31Layout->addWidget(q31);
    q31Widget->setLayout(q31Layout);
    testLayout->addWidget(q31Widget);

    QWidget *q32Widget = new QWidget(mainTestWidget);
    q32Widget->setFixedHeight(180);
    q32Widget->setObjectName("q1WObj");
    QVBoxLayout *q32Layout = new QVBoxLayout(q32Widget);
    Question *q32 = new Question (q32Widget, 4, true, 3);
    q32->addQuestion("Обезвреживанием медицинских отходов называется:");
    q32->addAnswer("Изменение внешнего вида отходов, исключающее возможность их повторного использования");
    q32->addAnswer("Использование отходов в качестве вторичных ресурсов после соответствующей переработки");
    q32->addAnswer("Обработка отходов с применением технологий, ведущих к утрате всех опасных свойств");
    q32->addAnswer("Захоронение в местах, установленных действующим законодательством");
    q32Layout->setContentsMargins(0, 0, 0, 0);
    q32Layout->addWidget(q32);
    q32Widget->setLayout(q32Layout);
    testLayout->addWidget(q32Widget);

    QWidget *q33Widget = new QWidget(mainTestWidget);
    q33Widget->setFixedHeight(180);
    q33Widget->setObjectName("q1WObj");
    QVBoxLayout *q33Layout = new QVBoxLayout(q33Widget);
    Question *q33 = new Question (q33Widget, 3, true, 2);
    q33->addQuestion("Персонал лаборатории, работающей с ПБА 3-4 группы при работе с медицинскими отходами подвергается риску:");
    q33->addAnswer("Получения физической травмы");
    q33->addAnswer("Инфекционного заражения");
    q33->addAnswer("Токсического поражения");
    q33Layout->setContentsMargins(0, 0, 0, 0);
    q33Layout->addWidget(q33);
    q33Widget->setLayout(q33Layout);
    testLayout->addWidget(q33Widget);

    QWidget *q34Widget = new QWidget(mainTestWidget);
    q34Widget->setFixedHeight(180);
    q34Widget->setObjectName("q1WObj");
    QVBoxLayout *q34Layout = new QVBoxLayout(q34Widget);
    Question *q34 = new Question (q34Widget, 4, false, 1, 2, 3);
    q34->addQuestion("При разлитии биологической жидкости необходимо:");
    q34->addAnswer("Абсорбировать пролитые жидкости");
    q34->addAnswer("Поверхность обработать дезинфицирующим средством");
    q34->addAnswer("Материалы, используемые для обеззараживания, поместить в отходы класса Б");
    q34->addAnswer("Через 2 часа обеззараженные материалы (осколки и др.) поместить в отходы класса А");
    q34Layout->setContentsMargins(0, 0, 0, 0);
    q34Layout->addWidget(q34);
    q34Widget->setLayout(q34Layout);
    testLayout->addWidget(q34Widget);

    QWidget *q35Widget = new QWidget(mainTestWidget);
    q35Widget->setFixedHeight(180);
    q35Widget->setObjectName("q1WObj");
    QVBoxLayout *q35Layout = new QVBoxLayout(q35Widget);
    Question *q35 = new Question (q35Widget, 4, true, 4);
    q35->addQuestion("Химический метод дезинфекции предполагает применение:");
    q35->addAnswer("Паров моющих средств");
    q35->addAnswer("Водяного насыщенного пара");
    q35->addAnswer("Дистиллированной воды");
    q35->addAnswer("Растворов химических средств");
    q35Layout->setContentsMargins(0, 0, 0, 0);
    q35Layout->addWidget(q35);
    q35Widget->setLayout(q35Layout);
    testLayout->addWidget(q35Widget);

    QWidget *q36Widget = new QWidget(mainTestWidget);
    q36Widget->setFixedHeight(200);
    q36Widget->setObjectName("q1WObj");
    QVBoxLayout *q36Layout = new QVBoxLayout(q36Widget);
    Question *q36 = new Question (q36Widget, 3, true, 1);
    q36->addQuestion("Что такое биориск?");
    q36->addAnswer("Сочетание вероятности возникновения вредного воздействия и степени вредного воздействия в тех случаях, когда источником \nтакого воздействия является биологический агент");
    q36->addAnswer("Процесс высвобождения опасных биологических агентов на рабочем месте");
    q36->addAnswer("Опасность, происходящая от живых объектов");
    q36Layout->setContentsMargins(0, 0, 0, 0);
    q36Layout->addWidget(q36);
    q36Widget->setLayout(q36Layout);
    testLayout->addWidget(q36Widget);

    QWidget *q37Widget = new QWidget(mainTestWidget);
    q37Widget->setFixedHeight(180);
    q37Widget->setObjectName("q1WObj");
    QVBoxLayout *q37Layout = new QVBoxLayout(q37Widget);
    Question *q37 = new Question (q37Widget, 5, true, 5);
    q37->addQuestion("Какую информацию необходимо оценить для оценки биорисков?");
    q37->addAnswer("Работа с какими ПБА осуществляется в лаборатории и каковы их патогенные характеристики");
    q37->addAnswer("Какие виды лабораторных работ будут проводиться");
    q37->addAnswer("Какой тип оборудования будет использоваться");
    q37->addAnswer("Какие существуют человеческие факторы");
    q37->addAnswer("Всё перечисленное");
    q37Layout->setContentsMargins(0, 0, 0, 0);
    q37Layout->addWidget(q37);
    q37Widget->setLayout(q37Layout);
    testLayout->addWidget(q37Widget);

    QWidget *q38Widget = new QWidget(mainTestWidget);
    q38Widget->setFixedHeight(180);
    q38Widget->setObjectName("q1WObj");
    QVBoxLayout *q38Layout = new QVBoxLayout(q38Widget);
    Question *q38 = new Question (q38Widget, 4, true, 2);
    q38->addQuestion("Плановая оценка биорисков осуществляется:");
    q38->addAnswer("Не реже 1 раза в квартал");
    q38->addAnswer("Не реже 1 раза в год");
    q38->addAnswer("Не реже 1 раза в 5 лет");
    q38->addAnswer("Только при возникновении внештатной ситуации");
    q38Layout->setContentsMargins(0, 0, 0, 0);
    q38Layout->addWidget(q38);
    q38Widget->setLayout(q38Layout);
    testLayout->addWidget(q38Widget);

    QWidget *q39Widget = new QWidget(mainTestWidget);
    q39Widget->setFixedHeight(180);
    q39Widget->setObjectName("q1WObj");
    QVBoxLayout *q39Layout = new QVBoxLayout(q39Widget);
    Question *q39 = new Question (q39Widget, 5, true, 5);
    q39->addQuestion("В каких случаях необходимо проведение внеплановой оценки биориска или её пересмотра?");
    q39->addAnswer("Внедрение нового метода исследования");
    q39->addAnswer("Строительство новых/модификация существующих лабораторий");
    q39->addAnswer("Изменения в составе персонала");
    q39->addAnswer("Возникновение непредвиденных событий, которые могут иметь отношение к управлению биорисками");
    q39->addAnswer("Всё перечисленное");
    q39Layout->setContentsMargins(0, 0, 0, 0);
    q39Layout->addWidget(q39);
    q39Widget->setLayout(q39Layout);
    testLayout->addWidget(q39Widget);

    QWidget *q40Widget = new QWidget(mainTestWidget);
    q40Widget->setFixedHeight(180);
    q40Widget->setObjectName("q1WObj");
    QVBoxLayout *q40Layout = new QVBoxLayout(q40Widget);
    Question *q40 = new Question (q40Widget, 4, false, 1, 3);
    q40->addQuestion("Ключевые аспекты системы оценки риска:");
    q40->addAnswer("Анализ биориска");
    q40->addAnswer("Учёт биориска");
    q40->addAnswer("Разработка стратегии по контролю биориска");
    q40->addAnswer("Наблюдение за биориском");
    q40Layout->setContentsMargins(0, 0, 0, 0);
    q40Layout->addWidget(q40);
    q40Widget->setLayout(q40Layout);
    testLayout->addWidget(q40Widget);

    QWidget *q41Widget = new QWidget(mainTestWidget);
    q41Widget->setFixedHeight(180);
    q41Widget->setObjectName("q1WObj");
    QVBoxLayout *q41Layout = new QVBoxLayout(q41Widget);
    Question *q41 = new Question (q41Widget, 4, false, 2, 3);
    q41->addQuestion("Кто осуществляет оценку биориска?");
    q41->addAnswer("Представитель отдела юридического обеспечения");
    q41->addAnswer("Комиссия по соблюдению требований биологической безопасности");
    q41->addAnswer("Руководитель лаборатории");
    q41->addAnswer("Представитель хозяйственного отдела");
    q41Layout->setContentsMargins(0, 0, 0, 0);
    q41Layout->addWidget(q41);
    q41Widget->setLayout(q41Layout);
    testLayout->addWidget(q41Widget);

    QWidget *q42Widget = new QWidget(mainTestWidget);
    q42Widget->setFixedHeight(180);
    q42Widget->setObjectName("q1WObj");
    QVBoxLayout *q42Layout = new QVBoxLayout(q42Widget);
    Question *q42 = new Question (q42Widget, 3, true, 1);
    q42->addQuestion("Цель этапа анализа биориска заключается в следующем:");
    q42->addAnswer("Определить вероятность воздействия и/или высвобождения биологического агента и тяжесть последствий такого события");
    q42->addAnswer("Предотвратить воздействие и/или высвобождение биологического агента");
    q42->addAnswer("Свести к минимуму вероятность воздействия и/или высвобождения биологического агента");
    q42Layout->setContentsMargins(0, 0, 0, 0);
    q42Layout->addWidget(q42);
    q42Widget->setLayout(q42Layout);
    testLayout->addWidget(q42Widget);

    QWidget *q43Widget = new QWidget(mainTestWidget);
    q43Widget->setFixedHeight(200);
    q43Widget->setObjectName("q1WObj");
    QVBoxLayout *q43Layout = new QVBoxLayout(q43Widget);
    Question *q43 = new Question (q43Widget, 7, true, 7);
    q43->addQuestion("Анализ биорисков со стороны руководства должен включать:");
    q43->addAnswer("Анализ результатов аудита");
    q43->addAnswer("Анализ действий, предпринятых на основе предыдущего анализа со стороны руководства");
    q43->addAnswer("Анализ мер контроля рисков и корректирующих действий");
    q43->addAnswer("Анализ данных об изменениях, которые могут повлиять на систему управления биорисками");
    q43->addAnswer("Результаты оценки биорисков");
    q43->addAnswer("Результаты расследования причин аварий и инцидентов");
    q43->addAnswer("Всё перечисленное");
    q43Layout->setContentsMargins(0, 0, 0, 0);
    q43Layout->addWidget(q43);
    q43Widget->setLayout(q43Layout);
    testLayout->addWidget(q43Widget);

    QWidget *q44Widget = new QWidget(mainTestWidget);
    q44Widget->setFixedHeight(180);
    q44Widget->setObjectName("q1WObj");
    QVBoxLayout *q44Layout = new QVBoxLayout(q44Widget);
    Question *q44 = new Question (q44Widget, 4, true, 4);
    q44->addQuestion("Что необходимо оценить с целью анализа вероятности возникновения риска по причине человеческих факторов?");
    q44->addAnswer("Структуру и штатную численность персонала");
    q44->addAnswer("Образование, квалификацию, опыту работы, профессиональную подготовку, технические знания и навыки");
    q44->addAnswer("Качество выполнения работ, исследований и соответствии их требованиям нормативной документации");
    q44->addAnswer("Всё перечисленное");
    q44Layout->setContentsMargins(0, 0, 0, 0);
    q44Layout->addWidget(q44);
    q44Widget->setLayout(q44Layout);
    testLayout->addWidget(q44Widget);

    QWidget *q45Widget = new QWidget(mainTestWidget);
    q45Widget->setFixedHeight(180);
    q45Widget->setObjectName("q1WObj");
    QVBoxLayout *q45Layout = new QVBoxLayout(q45Widget);
    Question *q45 = new Question (q45Widget, 4, false, 1, 3);
    q45->addQuestion("Факторы, влияющие на высокую вероятность возникновения инцидента:");
    q45->addAnswer("Лабораторные мероприятия, связанные с аэрозолизацией");
    q45->addAnswer("Низкая инфекционная доза ПБА");
    q45->addAnswer("Лабораторная деятельность, связанная с использованием колющих предметов");
    q45->addAnswer("Высокий уровень компетентности персонала, выполняющего работы");
    q45Layout->setContentsMargins(0, 0, 0, 0);
    q45Layout->addWidget(q45);
    q45Widget->setLayout(q45Layout);
    testLayout->addWidget(q45Widget);

    QWidget *q46Widget = new QWidget(mainTestWidget);
    q46Widget->setFixedHeight(180);
    q46Widget->setObjectName("q1WObj");
    QVBoxLayout *q46Layout = new QVBoxLayout(q46Widget);
    Question *q46 = new Question (q46Widget, 4, false, 1, 4);
    q46->addQuestion("Факторы, влияющие на последствия инцидента в случае его возникновения:");
    q46->addAnswer("Низкая инфекционная доза ПБА");
    q46->addAnswer("Высокая инфекционная доза ПБА");
    q46->addAnswer("Лёгкое течение заболевания");
    q46->addAnswer("Тяжёлое течение заболевания");
    q46Layout->setContentsMargins(0, 0, 0, 0);
    q46Layout->addWidget(q46);
    q46Widget->setLayout(q46Layout);
    testLayout->addWidget(q46Widget);

    QWidget *q47Widget = new QWidget(mainTestWidget);
    q47Widget->setFixedHeight(200);
    q47Widget->setObjectName("q1WObj");
    QVBoxLayout *q47Layout = new QVBoxLayout(q47Widget);
    Question *q47 = new Question (q47Widget, 4, true, 2);
    q47->addQuestion("Какой путь передачи инфекции является фактором, связанными как с высокой вероятностью возникновения инцидента, \nтак и с серьезными последствиями его возникновения:");
    q47->addAnswer("Фекально-оральный");
    q47->addAnswer("Воздушно-капельный");
    q47->addAnswer("Контактный");
    q47->addAnswer("Трансмиссивный");
    q47Layout->setContentsMargins(0, 0, 0, 0);
    q47Layout->addWidget(q47);
    q47Widget->setLayout(q47Layout);
    testLayout->addWidget(q47Widget);

    QWidget *q48Widget = new QWidget(mainTestWidget);
    q48Widget->setFixedHeight(100);
    q48Widget->setObjectName("q1WObj");
    QVBoxLayout *q48Layout = new QVBoxLayout(q48Widget);
    Question *q48 = new Question (q48Widget, 2, true, 1);
    q48->addQuestion("Является ли фактором, влияющим на высокую вероятность возникновения инцидента, большой объём проводимых исследований?");
    q48->addAnswer("Да");
    q48->addAnswer("Нет");
    q48Layout->setContentsMargins(0, 0, 0, 0);
    q48Layout->addWidget(q48);
    q48Widget->setLayout(q48Layout);
    testLayout->addWidget(q48Widget);

    QWidget *q49Widget = new QWidget(mainTestWidget);
    q49Widget->setFixedHeight(180);
    q49Widget->setObjectName("q1WObj");
    QVBoxLayout *q49Layout = new QVBoxLayout(q49Widget);
    Question *q49 = new Question (q49Widget, 4, true, 4);
    q49->addQuestion("При проведении оценки рисков необходимо учитывать:");
    q49->addAnswer("Наличие новых видов деятельности и методов исследования");
    q49->addAnswer("Модификацию структуры лаборатории, установку оборудования и т.п.");
    q49->addAnswer("Смену инженерно-технического персонала");
    q49->addAnswer("Всё перечисленное");
    q49Layout->setContentsMargins(0, 0, 0, 0);
    q49Layout->addWidget(q49);
    q49Widget->setLayout(q49Layout);
    testLayout->addWidget(q49Widget);

    QWidget *q50Widget = new QWidget(mainTestWidget);
    q50Widget->setFixedHeight(180);
    q50Widget->setObjectName("q1WObj");
    QVBoxLayout *q50Layout = new QVBoxLayout(q50Widget);
    Question *q50 = new Question (q50Widget, 5, false, 1, 3, 4, 5);
    q50->addQuestion("Продукция и услуги, которые могут оказывать влияние на управление биорисками:");
    q50->addAnswer("Лабораторное оборудование");
    q50->addAnswer("Канцелярские принадлежности");
    q50->addAnswer("Услуги по утилизации медицинских отходов");
    q50->addAnswer("Услуги по техническому обслуживанию оборудования и объекта");
    q50->addAnswer("Услуги службы безопасности");
    q50Layout->setContentsMargins(0, 0, 0, 0);
    q50Layout->addWidget(q50);
    q50Widget->setLayout(q50Layout);
    testLayout->addWidget(q50Widget);

    QWidget *q51Widget = new QWidget(mainTestWidget);
    q51Widget->setFixedHeight(220);
    q51Widget->setObjectName("q1WObj");
    QVBoxLayout *q51Layout = new QVBoxLayout(q51Widget);
    Question *q51 = new Question (q51Widget, 8, true, 8);
    q51->addQuestion("Объекты, подверженные риску контаминации ПБА:");
    q51->addAnswer("Персонал");
    q51->addAnswer("Защитная одежда и СИЗ");
    q51->addAnswer("Стеклянная посуда");
    q51->addAnswer("Оборудование");
    q51->addAnswer("Списанное оборудование");
    q51->addAnswer("Отходы");
    q51->addAnswer("Сточные воды лаборатории/организации");
    q51->addAnswer("Всё перечисленное");
    q51Layout->setContentsMargins(0, 0, 0, 0);
    q51Layout->addWidget(q51);
    q51Widget->setLayout(q51Layout);
    testLayout->addWidget(q51Widget);

    QWidget *q52Widget = new QWidget(mainTestWidget);
    q52Widget->setFixedHeight(220);
    q52Widget->setObjectName("q1WObj");
    QVBoxLayout *q52Layout = new QVBoxLayout(q52Widget);
    Question *q52 = new Question (q52Widget, 7, false, 1, 7);
    q52->addQuestion("К рискам выхода ПБА из «заразной» зоны относят:");
    q52->addAnswer("Кража ПБА или связанного с ним оборудования");
    q52->addAnswer("Саботаж, включая необоснованное «экспериментирование»");
    q52->addAnswer("Взлом и проникновение (в том числе вандализм)");
    q52->addAnswer("Чрезвычайные ситуации, обусловленные стихийными бедствиями и экстремальными погодными условиями (землетрясение, цунами, наводнение, ураган и др.)");
    q52->addAnswer("Чрезвычайные ситуации, обусловленные социальными факторами (террористический акт, общественные беспорядки и др.)");
    q52->addAnswer("Отказ инженерных коммуникаций");
    q52->addAnswer("Всё перечисленное");
    q52Layout->setContentsMargins(0, 0, 0, 0);
    q52Layout->addWidget(q52);
    q52Widget->setLayout(q52Layout);
    testLayout->addWidget(q52Widget);

    QWidget *q53Widget = new QWidget(mainTestWidget);
    q53Widget->setFixedHeight(180);
    q53Widget->setObjectName("q1WObj");
    QVBoxLayout *q53Layout = new QVBoxLayout(q53Widget);
    Question *q53 = new Question (q53Widget, 4, false, 1, 3);
    q53->addQuestion("Какие лабораторные мероприятия, связанные с аэрозолизацией осуществляются в вирусологической лаборатории?");
    q53->addAnswer("Заражение клеточных культур инфекционным (в том числе пассажным) материалом");
    q53->addAnswer("Микроскопия заражённых клеточных культур");
    q53->addAnswer("Пипетирование (титрование) вируссодержащего материала");
    q53->addAnswer("Обеззараживание инфекционного материала");
    q53Layout->setContentsMargins(0, 0, 0, 0);
    q53Layout->addWidget(q53);
    q53Widget->setLayout(q53Layout);
    testLayout->addWidget(q53Widget);

    QWidget *q54Widget = new QWidget(mainTestWidget);
    q54Widget->setFixedHeight(180);
    q54Widget->setObjectName("q1WObj");
    QVBoxLayout *q54Layout = new QVBoxLayout(q54Widget);
    Question *q54 = new Question (q54Widget, 5, true, 5);
    q54->addQuestion("Какие меры по контролю риска аэрозолизации во время пипетирования необходимо применять при работе с ПБА 3-4 группы?");
    q54->addAnswer("Использовать боксы биологической безопасности 2 класса");
    q54->addAnswer("Применять не пипетки с грушами, а автоматические дозаторы");
    q54->addAnswer("Использовать наконечники для дозаторов с фильтрами");
    q54->addAnswer("Вносить жидкость по стенке сосуда");
    q54->addAnswer("Всё перечисленное");
    q54Layout->setContentsMargins(0, 0, 0, 0);
    q54Layout->addWidget(q54);
    q54Widget->setLayout(q54Layout);
    testLayout->addWidget(q54Widget);

    QWidget *q55Widget = new QWidget(mainTestWidget);
    q55Widget->setFixedHeight(200);
    q55Widget->setObjectName("q1WObj");
    QVBoxLayout *q55Layout = new QVBoxLayout(q55Widget);
    Question *q55 = new Question (q55Widget, 5, false, 1, 2, 3, 4);
    q55->addQuestion("Какие меры по контролю риска образования аэрозолей при центрифугировании необходимо применять при работе с ПБА 3-4 \nгруппы?");
    q55->addAnswer("Всегда уравновешивать центрифужные флаконы/пробирки");
    q55->addAnswer("Перед использованием проверять целостность центрифужных флаконов/пробирок");
    q55->addAnswer("Плотно закрывать центрифужные флаконы/пробирки");
    q55->addAnswer("Регулярно дезинфицировать ротор центрифуги");
    q55->addAnswer("При аварии на центрифуге сразу открыть крышку, чтобы оценить характер и масштаб аварии");
    q55Layout->setContentsMargins(0, 0, 0, 0);
    q55Layout->addWidget(q55);
    q55Widget->setLayout(q55Layout);
    testLayout->addWidget(q55Widget);

    QWidget *q56Widget = new QWidget(mainTestWidget);
    q56Widget->setFixedHeight(180);
    q56Widget->setObjectName("q1WObj");
    QVBoxLayout *q56Layout = new QVBoxLayout(q56Widget);
    Question *q56 = new Question (q56Widget, 5, true, 5);
    q56->addQuestion("Стратегии для снижения и контроля рисков:");
    q56->addAnswer("Ликвидация ПБА");
    q56->addAnswer("Снижение и замена ПБА");
    q56->addAnswer("Защита персонала/окружающей среды");
    q56->addAnswer("Соблюдение требований биологической безопасности");
    q56->addAnswer("Всё перечисленное");
    q56Layout->setContentsMargins(0, 0, 0, 0);
    q56Layout->addWidget(q56);
    q56Widget->setLayout(q56Layout);
    testLayout->addWidget(q56Widget);

    QWidget *q57Widget = new QWidget(mainTestWidget);
    q57Widget->setFixedHeight(180);
    q57Widget->setObjectName("q1WObj");
    QVBoxLayout *q57Layout = new QVBoxLayout(q57Widget);
    Question *q57 = new Question (q57Widget, 3, true, 1);
    q57->addQuestion("Что предпринимают после разработки стратегии по контролю биориска?");
    q57->addAnswer("Выбор и реализацию мер по контролю биориска");
    q57->addAnswer("Повторный анализ биориска");
    q57->addAnswer("Ликвидацию ПБА");
    q57Layout->setContentsMargins(0, 0, 0, 0);
    q57Layout->addWidget(q57);
    q57Widget->setLayout(q57Layout);
    testLayout->addWidget(q57Widget);

    QWidget *q58Widget = new QWidget(mainTestWidget);
    q58Widget->setFixedHeight(200);
    q58Widget->setObjectName("q1WObj");
    QVBoxLayout *q58Layout = new QVBoxLayout(q58Widget);
    Question *q58 = new Question (q58Widget, 3, true, 3);
    q58->addQuestion("Что такое меры по контролю биориска?");
    q58->addAnswer("Определение стратегии, которая должна использоваться для контроля риска");
    q58->addAnswer("Анализ факторов, влияющих на высокую вероятность возникновения инцидента");
    q58->addAnswer("Использование совокупности инструментов, включающих коммуникацию, оценку, обучение, физический и операционный контроль, \nдля снижения риска инцидента/события до приемлемого уровня");
    q58Layout->setContentsMargins(0, 0, 0, 0);
    q58Layout->addWidget(q58);
    q58Widget->setLayout(q58Layout);
    testLayout->addWidget(q58Widget);

    QWidget *q59Widget = new QWidget(mainTestWidget);
    q59Widget->setFixedHeight(130);
    q59Widget->setObjectName("q1WObj");
    QVBoxLayout *q59Layout = new QVBoxLayout(q59Widget);
    Question *q59 = new Question (q59Widget, 2, true, 1);
    q59->addQuestion("Является ли документированный учёт ПБА мерой по контролю риска утраты ПБА?");
    q59->addAnswer("Да");
    q59->addAnswer("Нет");
    q59Layout->setContentsMargins(0, 0, 0, 0);
    q59Layout->addWidget(q59);
    q59Widget->setLayout(q59Layout);
    testLayout->addWidget(q59Widget);

    QWidget *q60Widget = new QWidget(mainTestWidget);
    q60Widget->setFixedHeight(220);
    q60Widget->setObjectName("q1WObj");
    QVBoxLayout *q60Layout = new QVBoxLayout(q60Widget);
    Question *q60 = new Question (q60Widget, 7, true, 7);
    q60->addQuestion("Меры по контролю риска, связанного с поведением человека:");
    q60->addAnswer("Оценка надежности и безопасности поведения сотрудника");
    q60->addAnswer("Обмен информацией и обратная связь с сотрудником");
    q60->addAnswer("Урегулирование и разрешение конфликтных ситуаций");
    q60->addAnswer("Остановка работы при выявлении небезопасных условий работы персонала");
    q60->addAnswer("Предотвращение «осуждения» и защиту персонала, информирующего об авариях, инцидентах, небезопасных условиях работы или \nнебезопасном поведении персонала");
    q60->addAnswer("Уважительное отношение к неприкосновенности частной жизни и достоинству человека");
    q60->addAnswer("Всё перечисленное");
    q60Layout->setContentsMargins(0, 0, 0, 0);
    q60Layout->addWidget(q60);
    q60Widget->setLayout(q60Layout);
    testLayout->addWidget(q60Widget);

    questionsVec = {q1, q2, q3, q4, q5, q6, q7, q8, q9, q10, q11, q12, q13, q14, q15, q16, q17, q18, q19, q20, q21, q22, q23, q24, q25, q26, q27, q28, q29, q30, q31, q32, q33, q34, q35, q36, q37, q38, q39, q40, q41, q42, q43, q44, q45, q46, q47, q48, q49, q50, q51, q52, q53, q54, q55, q56, q57, q58, q59, q60};
    questionWidgets = {q1Widget, q2Widget, q3Widget, q4Widget, q5Widget, q6Widget, q7Widget, q8Widget, q9Widget, q10Widget, q11Widget, q12Widget, q13Widget, q14Widget, q15Widget, q16Widget, q17Widget, q18Widget, q19Widget, q20Widget, q21Widget, q22Widget, q23Widget, q24Widget, q25Widget, q26Widget, q27Widget, q28Widget, q29Widget, q30Widget, q31Widget, q32Widget, q33Widget, q34Widget, q35Widget, q36Widget, q37Widget, q38Widget, q39Widget, q40Widget, q41Widget, q42Widget, q43Widget, q44Widget, q45Widget, q46Widget, q47Widget, q48Widget, q49Widget, q50Widget, q51Widget, q52Widget, q53Widget, q54Widget, q55Widget, q56Widget, q57Widget, q58Widget, q59Widget, q60Widget};
    beforeShuffledW = questionWidgets;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(questionWidgets.begin(), questionWidgets.end(), gen);
    std::vector<size_t> indices(questionWidgets.size());

    for (size_t i = 0; i < 20 && !questionWidgets.empty(); ++i)
    {
        QWidget* el = questionWidgets[i];
        el->hide();
        el->deleteLater();
    }

    int counter = 1;
    for (auto el : beforeShuffledW)
    {
        if (el && !el->isHidden())
        { // Проверка, чтобы избежать доступа к скрытым и удаленным виджетам
            Question* q = el->findChild<Question*>();
            QString iStr = QString::number(counter);
            q->getQuestion()->setText(iStr + " " + q->getQuestion()->text());
            ++counter;
        }
    }
}
