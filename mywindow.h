#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include <QFile>
#include <QRandomGenerator>
#include <string>
#include <vector>
#include <bitset>
#include <algorithm>

class MyWindow : public QDialog
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = nullptr);
private:
    QLabel *label;
    QLabel *label2;
    QLineEdit *line;
    size_t lineSize;
    QLineEdit *gamma;
    QPushButton *okey;
    QPushButton *read;
    QPushButton *random;
    QComboBox *language;

    std::vector<std::pair<char, size_t>> alphabet;

private:
    void gamuv(const QString &text, const QString &gamma, QString &newText);
private slots:
    void okEnable(QString);
    void okEnable2(QString);
    void okPressed();
    void readPressed();
    void randomPressed();
signals:
    void Sig(QString);

};

class Interface : public QDialog{
    Q_OBJECT
public:
    Interface(QWidget *parent = nullptr);
private:
    QTextEdit *text;
    QPushButton *write;
public slots:
    void Message(QString);
    void writePressed();

};

void gamuv(const QString &, const QString &, QString &);
QString stringSize(QString, const QString &);
#endif // MYWINDOW_H
