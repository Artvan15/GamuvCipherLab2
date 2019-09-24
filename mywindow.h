#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QtWidgets>
#include <QFile>
#include <string>
#include <algorithm>
#include <vector>
#include <locale>
#include <iostream>

class MyWindow : public QDialog
{
    Q_OBJECT
public:
    MyWindow(QWidget *parent = nullptr);
private:
    QLabel *label;
    QLineEdit *line;
    QPushButton *okey;
    QPushButton *read;
    QPushButton *close;
    QComboBox *language;
    QComboBox *cipher;
    QSpinBox *spinbox;
    QSlider *slider;
    std::vector<std::pair<QChar,int>> Lower;
    std::vector<std::pair<QChar,int>> Upper;

friend QString Ukrainian(QString, unsigned index, unsigned shift);
private slots:
    void okEnable(QString);
    void okPressed();
    void readPressed();
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
    QPushButton *brute;
public slots:
    void Message(QString);
    void writePressed();
    void bruteForce();

};

#endif // MYWINDOW_H
