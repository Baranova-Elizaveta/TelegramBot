#include <QCoreApplication>
#include <QDebug>
#include "include/qttelegrambot.h"
#include <tgbot/tgbot.h>
#include <QUrlQuery>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QtSql>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>

#define TOKEN "5991791468:AAGR5AM0fb1Dtwcv4TrKz5OFXVW-emuinGc"

Telegram::Bot *bot;


struct ExchangeRate {
    QString name;
    QString level;
    QString author;
    QString genre;
};

void books(Telegram::Message message)
{
    QString  king = "Дракула — Dracula\n"
                    "Подходит для начального уровня A1-A2\n";
    QFile kingphoto("drac.jpg");
    if (kingphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &kingphoto, king);

    QString  addams = "Мистер Бин в городе — Mr. Bean In Town\n"
                      "Подходит для начального уровня A1-A2\n";
    QFile addamsphoto("mr.jpeg");
    if (addamsphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &addamsphoto, addams);

    QString  simpsons = "Портрет Дориана Грея — The Picture of Dorian Gray\n"
                        "Подходит для продвинутого уровня B1-B2\n";
    QFile simpsonsphoto("gray.jpg");
    if (simpsonsphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &simpsonsphoto, simpsons);

    QString  ghost = "Форрест Гамп — Forrest Gump\n"
                        "Подходит для продвинутого уровня B1-B2\n";
    QFile ghostphoto("for.jpg");
    if (ghostphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &ghostphoto, ghost);

    QString  fargo = "1984 \n"
                        "Подходит для продвинутого уровня C1-C2\n";
    QFile fargophoto("1984.jpg");
    if (fargophoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &fargophoto, fargo);
}

void films(Telegram::Message message)
{
    QString  king = "The Lion King /Король лев\n"
                    "Подходит для начального уровня A1-A2\n";
    QFile kingphoto("King.jpg");
    if (kingphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &kingphoto, king);

    QString  addams = "Addams Family Values / Ценности семейки Аддамс\n"
                      "Подходит для начального уровня A1-A2\n";
    QFile addamsphoto("Addams.jpg");
    if (addamsphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &addamsphoto, addams);

    QString  simpsons = "The Simpsons / Симпсоны\n"
                        "Подходит для продвинутого уровня B1-B2\n";
    QFile simpsonsphoto("simpsons.jpg");
    if (simpsonsphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &simpsonsphoto, simpsons);

    QString  ghost = "The Ghost Writer / Призрак\n"
                        "Подходит для продвинутого уровня B1-B2\n";
    QFile ghostphoto("ghost.jpg");
    if (ghostphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &ghostphoto, ghost);

    QString  fargo = "Fargo / Фарго\n"
                        "Подходит для продвинутого уровня C1-C2\n";
    QFile fargophoto("fargo.jpg");
    if (fargophoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &fargophoto, fargo);

    QString  west = "Westworld / Мир Дикого Запада\n"
                        "Подходит для продвинутого уровня C1-C2\n";
    QFile westphoto("west.jpg");
    if (westphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &westphoto, west);
}

void alphabet(Telegram::Message message)
{
    QString  alphabet = "Алфавит\n"
                      "Alphabet\n";
    QFile alphabetphoto("alphabet.jpg");
    if (alphabetphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &alphabetphoto, alphabet);
}

void verbs(Telegram::Message message)
{
    QString  verb = "Таблица неправильных глаголов\n";
                          QFile verbsphoto("verbs.png");
    if (verbsphoto.open(QIODevice::ReadOnly)) bot->sendPhoto(QString::number(message.chat.id), &verbsphoto, verb);
}


void Vivod(Telegram::Message message)
{
    QFile file("test.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["books"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> books;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();
            rate.level = val.toObject()["level"].toString();
            rate.author = val.toObject()["author"].toString();
            rate.genre = val.toObject()["genre"].toString();

            // Добавляем новый объект в вектор
           books.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Название книги: "+books[j].name+"\n";
                str += "Уровень английского: "+ books[j].level+"\n";
                str += "Автор: "+ books[j].author+ "\n";
                str += "Жанр: "+ books[j].genre+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}



/*void showIrregularVerbsTable(Telegram::Message message)
{
    QFile file("verbs.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["irregular"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> irregular;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();

            // Добавляем новый объект в вектор
           irregular.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Таблица: \n"+irregular[j].name+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}*/

void ToBe(Telegram::Message message)
{
    QFile file("be.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["be"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> be;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();

            // Добавляем новый объект в вектор
           be.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Правило: \n"+be[j].name+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}

void ToHave(Telegram::Message message)
{
    QFile file("have.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["have"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> have;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();

            // Добавляем новый объект в вектор
           have.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Правило: \n"+have[j].name+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}

void Active(Telegram::Message message)
{
    QFile file("active.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["have"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> have;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();

            // Добавляем новый объект в вектор
           have.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Правило: \n"+have[j].name+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}

void Passive(Telegram::Message message)
{
    QFile file("passive.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["have"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> have;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();

            // Добавляем новый объект в вектор
           have.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Правило: \n"+have[j].name+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}

void ModelVerbs(Telegram::Message message)
{
    QFile file("model.json");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream stream(&file);
        QByteArray response;
        QString str1 = stream.readAll().toUtf8();
        response.append(str1.toUtf8());
        qDebug() << response;
        // Преобразование ответа ///////////////////////////////////////////////////////////
        QJsonDocument doc = QJsonDocument::fromJson(response);
        QJsonObject obj = doc.object();
        QJsonArray arr = obj["model"].toArray();
        int i=0;
        // Создаем вектор, в котором будем хранить объекты структуры ExchangeRate
        std::vector<ExchangeRate> model;
        // Проходимся по всем объектам массива
        for (const auto& val : arr) {
            // Создаем новый объект структуры ExchangeRate
            ExchangeRate rate;
            i++;
            // Получаем значения полей из JSON-объекта
            rate.name = val.toObject()["name"].toString();

            // Добавляем новый объект в вектор
           model.push_back(rate);
        }QString str;
        for(int j=0; j<i; j++){
                str += "Правило: \n"+model[j].name+"\n";
                str += "\n";
        }
        bot->sendMessage(QString::number(message.chat.id), str);
    }
}



void translate(const QString& text, const QString& from, const QString& to, const qint32 &id)
{
    QNetworkAccessManager* networkManager = new QNetworkAccessManager();
    QUrl url("https://translate.googleapis.com/translate_a/single");
    QUrlQuery urlQuery;
    urlQuery.addQueryItem("client", "gtx");
    urlQuery.addQueryItem("sl", from);
    urlQuery.addQueryItem("tl", to);
    urlQuery.addQueryItem("dt", "t");
    urlQuery.addQueryItem("q", text);
    url.setQuery(urlQuery);
    QNetworkRequest request;
    request.setUrl(url);
    QNetworkReply* reply = networkManager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [reply, id, networkManager]() {
        QByteArray response = reply->readAll();

        QJsonDocument jsonDocument = QJsonDocument::fromJson(response);
        QString translatedText = jsonDocument.array()[0].toArray().at(0).toArray().at(0).toString();
        translatedText = translatedText.mid(37);

        bot->sendMessage(id, "Перевод: " + translatedText);
        reply->deleteLater();
        networkManager->deleteLater(); // очистка менеджера после завершения запроса
    });
}

void showPastSimpleRules(const qint32& id)
{
    QString rules = "The Past Simple is used to describe actions or states that occurred at a specific time in the past.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + Verb (Past Simple) + Object\n";
    rules += "Negative: Subject + did not (didn't) + Verb (base form) + Object\n";
    rules += "Question: Did + Subject + Verb (base form) + Object?\n";
    QString rule = "The Past Simple используется для описания действий или состояний, которые произошли в конкретное время в прошлом.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + Глагол (Past Simple) + Дополнение\n";
    rule += "Отрицательное: Подлежащее + did not (didn't) + Глагол (базовая форма) + Дополнение\n";
    rule += "Вопросительное: Did + Подлежащее + Глагол (базовая форма) + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}
void showPresentSimpleRules(const qint32& id)
{
QString rules = "The Present Simple is used to describe habits, routines, general truths, and events that happen regularly.\n\n";
rules += "Structure:\n";
rules += "Positive: Subject + Verb (base form) + Object\n";
rules += "Negative: Subject + do/does not (doesn't) + Verb (base form) + Object\n";
rules += "Question: Do/Does + Subject + Verb (base form) + Object?\n";
QString rule = "The Present Simple используется для описания привычек, рутин, общих истин и событий, которые происходят регулярно.\n\n";
rule += "Структура:\n";
rule += "Утвердительное: Подлежащее + Глагол (базовая форма) + Дополнение\n";
rule += "Отрицательное: Подлежащее + do/does not (doesn't) + Глагол (базовая форма) + Дополнение\n";
rule += "Вопросительное: Do/Does + Подлежащее + Глагол (базовая форма) + Дополнение?\n";
bot->sendMessage(id, rules);
bot->sendMessage(id, rule);
}

void showPresentContinuousRules(const qint32& id)
{
QString rules = "The Present Continuous is used to describe actions happening now, temporary actions, and future arrangements.\n\n";
rules += "Structure:\n";
rules += "Positive: Subject + am/is/are + Verb (-ing form) + Object\n";
rules += "Negative: Subject + am/is/are not (isn't/aren't) + Verb (-ing form) + Object\n";
rules += "Question: Am/Is/Are + Subject + Verb (-ing form) + Object?\n";
QString rule = "The Present Continuous используется для описания действий, происходящих в данный момент, временных действий и будущих планов.\n\n";
rule += "Структура:\n";
rule += "Утвердительное: Подлежащее + am/is/are + Глагол (-ing форма) + Дополнение\n";
rule += "Отрицательное: Подлежащее + am/is/are not (isn't/aren't) + Глагол (-ing форма) + Дополнение\n";
rule += "Вопросительное: Am/Is/Are + Подлежащее + Глагол (-ing форма) + Дополнение?\n";
bot->sendMessage(id, rules);
bot->sendMessage(id, rule);
}
void showPastContinuousRules(const qint32& id)
{
    QString rules = "The Past Continuous is used to describe actions or events that were in progress at a specific time in the past.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + was/were + Verb (-ing form) + Object\n";
    rules += "Negative: Subject + was/were not + Verb (-ing form) + Object\n";
    rules += "Question: Was/Were + Subject + Verb (-ing form) + Object?\n";
    QString rule = "The Past Continuous используется для описания действий или событий, которые происходили в определенное время в прошлом.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + was/were + Глагол (-ing форма) + Дополнение\n";
    rule += "Отрицательное: Подлежащее + was/were not + Глагол (-ing форма) + Дополнение\n";
    rule += "Вопросительное: Was/Were + Подлежащее + Глагол (-ing форма) + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}

void showPastPerfectRules(const qint32& id)
{
    QString rules = "The Past Perfect is used to describe an action that happened before another action in the past.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + had + past participle of Verb + Object\n";
    rules += "Negative: Subject + had not + past participle of Verb + Object\n";
    rules += "Question: Had + Subject + past participle of Verb + Object?\n";
    QString rule = "The Past Perfect используется для описания действия, которое произошло перед другим действием в прошлом.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + had + причастие прошедшего времени Глагола + Дополнение\n";
    rule += "Отрицательное: Подлежащее + had not + причастие прошедшего времени Глагола + Дополнение\n";
    rule += "Вопросительное: Had + Подлежащее + причастие прошедшего времени Глагола + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}
void showPastPerfectContinuousRules(const qint32& id)
{
    QString rules = "The Past Perfect Continuous is used to describe an action that started in the past and continued up until another time in the past. It emphasizes the duration of the action.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + had + been + Verb (ing form) + Object\n";
    rules += "Negative: Subject + had not (hadn't) + been + Verb (ing form) + Object\n";
    rules += "Question: Had + Subject + been + Verb (ing form) + Object?\n";
    QString rule = "The Past Perfect Continuous используется для описания действия, которое началось в прошлом и продолжалось до какого-то момента в прошлом. Он акцентирует на продолжительности действия.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + had + been + Глагол (в форме -ing) + Дополнение\n";
    rule += "Отрицательное: Подлежащее + had not (hadn't) + been + Глагол (в форме -ing) + Дополнение\n";
    rule += "Вопросительное: Had + Подлежащее + been + Глагол (в форме -ing) + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}
void showFutureSimpleRules(const qint32& id)
{
    QString rules = "The Future Simple is used to describe actions that will take place in the future.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + will + Verb (base form) + Object\n";
    rules += "Negative: Subject + will not (won't) + Verb (base form) + Object\n";
    rules += "Question: Will + Subject + Verb (base form) + Object?\n";
    QString rule = "The Future Simple используется для описания действий, которые произойдут в будущем.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + will + Глагол (базовая форма) + Дополнение\n";
    rule += "Отрицательное: Подлежащее + will not (won't) + Глагол (базовая форма) + Дополнение\n";
    rule += "Вопросительное: Will + Подлежащее + Глагол (базовая форма) + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}
void showFutureContinuousRules(const qint32& id)
{
    QString rules = "The Future Continuous is used to describe actions that will be in progress at a specific time in the future.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + will be + Verb (present participle) + Object\n";
    rules += "Negative: Subject + will not (won't) be + Verb (present participle) + Object\n";
    rules += "Question: Will + Subject + be + Verb (present participle) + Object?\n";
    QString rule = "Future Continuous используется для описания действий, которые будут находиться в процессе выполнения в конкретное время в будущем.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + will be + Глагол (настоящее причастие) + Дополнение\n";
    rule += "Отрицательное: Подлежащее + will not (won't) be + Глагол (настоящее причастие) + Дополнение\n";
    rule += "Вопросительное: Will + Подлежащее + be + Глагол (настоящее причастие) + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}

void showFuturePerfectRules(const qint32& id)
{
    QString rules = "The Future Perfect is used to describe an action that will be completed before a specific time in the future.\n\n";
    rules += "Structure:\n";
    rules += "Positive: Subject + will have + Verb (past participle) + Object\n";
    rules += "Negative: Subject + will not (won't) have + Verb (past participle) + Object\n";
    rules += "Question: Will + Subject + have + Verb (past participle) + Object?\n";
    QString rule = "Future Perfect используется для описания действия, которое будет завершено к конкретному времени в будущем.\n\n";
    rule += "Структура:\n";
    rule += "Утвердительное: Подлежащее + will have + Глагол (прошедшее причастие) + Дополнение\n";
    rule += "Отрицательное: Подлежащее + will not (won't) have + Глагол (прошедшее причастие) + Дополнение\n";
    rule += "Вопросительное: Will + Подлежащее + have + Глагол (прошедшее причастие) + Дополнение?\n";
    bot->sendMessage(id, rules);
    bot->sendMessage(id, rule);
}


void newMessage(Telegram::Message message)
{


    qDebug() << "new message:" << message;

       if (bot && message.type == Telegram::Message::TextType) {
           if (message.string == "/start") {
               Telegram::KeyboardMarkup keyboard = {{"help"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id, "Добро пожаловать в меню бота для изучения английского языка! Нажмите на кнопку help, чтобы увидеть список команд.\n "
                                                 "В дальнейшем при вводе слова help будет доступ к списку команд",0,0,0,linemarkup);
           } else if (message.string == "help") {//общий саисок команд (неправильне глаголы, грамматика, грамматика времен, фильмы, книги,сайты для изучения, кнопка с переводом)
               Telegram::InlineKeyboardButtons inlinebut = {{Telegram::InlineKeyboardButton("Перевести текст","","","","/translate")}};
               Telegram::InlineKeyboardMarkup inlinemarkup(inlinebut);//
               bot->sendMessage(message.from.id, "Список основных команд:\n /start - начало работы\n "//
                                                 "help - список команд\n "//
                                                 "about - описание бота\n"//
                                                 "grammar - грамматика в английском языке\n "//
                                                 "grammar_of_tenses - список времен в английском языке\n"//
                                                 "films - подборка фильмов по уровням\n "//
                                                 "books - подборка книг по уровням\n "//
                                                 "sites - подборка сайтов"//
                                                 ,0,0,0,inlinemarkup);
               Telegram::KeyboardMarkup keyboard = {{"/start","about","help","📕grammar"},{"📕grammar_of_tenses","🎥films","📚books","💻sites"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id,"Выбери с чего ты хочешь начать:)",0,0,0,linemarkup);
           }   else if(message.string == "sites"){
               bot->sendMessage(message.from.id,"http://tubequizard.com/ - сайт для прокачки восприятия речи на слух. Выбираешь"
                                "фильтрацию по уровню, типу, категории видео. Смотришь/слушаешь видео по фразам,"
                                "вписываешь пропущенное слово. Нажимая на фразу, можно переслушивать нужный"
                                "отрывок. Реальные акценты, ток-шоу, отрывки из фильмов. Кнопкой check можно"
                                "себя проверить.\n\n"
                                "https://www.newsinlevels.com/ - здесь актуальные новости на английском по разным уровням сложности\n\n"
                                "https://www.englishgrammar.org/ - сайт, посвященный английской грамматике\n\n"
                                "https://quizlet.com/ru - создавай свои карточки и в игровой форме изучай слова и выражения. Можно пользоваться готовыми карточками - просто набери в поиске нужную тему.\n\n"
                                "https://www.youtube.com/watch?v=IV30jAw7dxA - как подготовиться к интервью на английском");
           }
           else if (message.string == "grammar") {
               Telegram::KeyboardMarkup keyboard = {{"Beginner","Elementary","Pre-intermidiate"},{"Intermidiate","Upper-intermidiate","Advanced"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id, "Выбери необходимы тебе уровень для изучения:)\n "
                                                 ,0,0,0,linemarkup);
           }else if(message.string == "Beginner"){
               Telegram::KeyboardMarkup keyboard = {{"alphabet","to_be","to_have"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id,"Ты выбрал начальный уровень! Поздравляю ты только начинаешь свой путь в изучении английского языка. Я буду рад тебе помочь)\n"
                                                "Выбери с чего ты хочешь начать:",0,0,0,linemarkup);
           }
           else if(message.string == "Elementary"){
                          Telegram::KeyboardMarkup keyboard = {{"model_verbs","irregular_verbs_table"}};
                          Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
                          bot->sendMessage(message.from.id,"Ты выбрал начальный-продвинутый уровень! Я буду рад тебе помочь)\n"
                                                           "Выбери с чего ты хочешь начать:",0,0,0,linemarkup);
                      }
           else if(message.string == "Pre-intermidiate"){
               Telegram::KeyboardMarkup keyboard = {{"active_voice","passive_voice"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id,"Ты выбрал начальный-продвинутый уровень! Я буду рад тебе помочь)\n"
                                                "Выбери с чего ты хочешь начать:",0,0,0,linemarkup);
           }
           else if(message.string == "Intermidiate"){
               Telegram::KeyboardMarkup keyboard = {{"active_voice","passive_voice"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id,"Ты выбрал начальный-продвинутый уровень! Я буду рад тебе помочь)\n"
                                                "Выбери с чего ты хочешь начать:",0,0,0,linemarkup);
           }
           else if(message.string == "Upper-intermidiate"){
               Telegram::KeyboardMarkup keyboard = {{"After/Before","Since"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id,"Ты выбрал начальный-продвинутый уровень! Я буду рад тебе помочь)\n"
                                                "Выбери с чего ты хочешь начать:",0,0,0,linemarkup);
           }
           else if(message.string == "Advanced"){
               Telegram::KeyboardMarkup keyboard = {{"dare","used to"}};
               Telegram::ReplyKeyboardMarkup linemarkup(keyboard,true);
               bot->sendMessage(message.from.id,"Ты выбрал начальный-продвинутый уровень! Я буду рад тебе помочь)\n"
                                                "Выбери с чего ты хочешь начать:",0,0,0,linemarkup);
           }
           else if (message.string == "grammar_of_tenses") {
               Telegram::KeyboardMarkup keyboard = {{"pastSimple","presentSimple","futureSimplepastContinuous"}, {"presentContinuous","pastContinuous","futureContinuous"},{"presentPerfect","pastPerfect","futurePerfect"},{"pastPerfectContinuous","presentPerfectContinuous","futurePerfectContinuous"}};
               Telegram::ReplyKeyboardMarkup markup(keyboard,true);
               bot->sendMessage(message.from.id, "Времена в английском языке:\n выберете нужное вам время",0,0,0,markup);
           }else if (message.string == "about") {
               bot->sendMessage(message.from.id, "Hello!!!\n "
                                                 "Если ты пришел ко мне, значит ты знаешь чего хочешь:)\n"
                                                 "Ладно, перейдем к делу. Этот бот создан для упрощения изучения английского языка."
                                                 "В него собрано множество правил, переводчик, рекомендации книг по уровням и т.д.\n");
           }else if(message.string.contains("/translate")){
               translate(message.string,"en","ru",message.from.id);
           }else if (message.string == "irregular_verbs_table") {
               verbs(message);
           }else if (message.string.contains("pastSimple")){
               showPastSimpleRules(message.from.id);
           }else if (message.string.contains("presentSimple")){
               showPresentSimpleRules(message.from.id);
           }else if (message.string.contains("presentContinuous")){
               showPresentContinuousRules(message.from.id);
           }else if (message.string.contains("pastContinuous")){
                showPastContinuousRules(message.from.id);
           }else if (message.string.contains("pastPerfect")){
                showPastPerfectRules(message.from.id);
           }else if (message.string.contains("pastPerfectContinuous")){
                showPastPerfectContinuousRules(message.from.id);
           }else if (message.string.contains("futureSimple")){
                showFutureSimpleRules(message.from.id);
           }else if (message.string.contains("futureContinuous")){
               showFutureContinuousRules(message.from.id);
          }else if (message.string.contains("futurePerfect")){
               showFuturePerfectRules(message.from.id);
          }else if (message.string == "to_be"){
                         ToBe(message);
           }else if (message.string == "to_have"){
                          ToHave(message);
           }else if (message.string == "active_voice"){
               Active(message);
}else if (message.string == "passive_voice"){
               Passive(message);
}
           else if (message.string == "model_verbs"){
                          ModelVerbs(message);
           }
           else if (message.string == "alphabet"){
               alphabet(message);
           }
           else if (message.string == "films"){
               films(message);
           }
           else if (message.string == "books"){
               books(message);
           }
       }
          else {
               bot->sendMessage(message.from.id, "Неизвестная команда. Введите /help, чтобы увидеть список команд.");
           }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    bot = new Telegram::Bot(TOKEN, true, 500, 4);
    QObject::connect(bot, &Telegram::Bot::message, &newMessage);
    qDebug() << "Started Telegram Bot";

    return a.exec();
}
