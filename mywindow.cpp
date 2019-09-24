#include "mywindow.h"


MyWindow::MyWindow(QWidget *parent) : QDialog(parent), lineSize(0)
{
    label = new QLabel("Текст");
    label2 = new QLabel("Гамма");
    line = new QLineEdit;
    gamma = new QLineEdit;
    okey = new QPushButton("Okey");
    random = new QPushButton("Random");
    read = new QPushButton("Read");
    language = new QComboBox;


    language->addItem("Англійська"); language->addItem("Українська");


    okey->setEnabled(false);



    QHBoxLayout *leftup = new QHBoxLayout;
    leftup->addWidget(language);

    QHBoxLayout *leftcenter = new QHBoxLayout;
    leftcenter->addWidget(label);
    leftcenter->addWidget(line);

    QHBoxLayout *leftdown = new QHBoxLayout;
    leftdown->addWidget(label2);
    leftdown->addWidget(gamma);



    QVBoxLayout *left = new QVBoxLayout;
    left->addLayout(leftup);
    left->addLayout(leftcenter);
    left->addLayout(leftdown);


    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(okey);
    right->addWidget(read);
    right->addWidget(random);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);

    setLayout(main);

    connect(random, SIGNAL(clicked()),this, SLOT(randomPressed()));
    connect(line, SIGNAL(textChanged(QString)), this, SLOT(okEnable(QString)));
    connect(gamma, SIGNAL(textChanged(QString)), this, SLOT(okEnable2(QString)));
    connect(okey, SIGNAL(clicked()), this, SLOT(okPressed()));
    connect(read, SIGNAL(clicked()), this, SLOT(readPressed()));

}

void MyWindow::okEnable(QString str){
    okey->setEnabled(!str.isEmpty() && !gamma->text().isEmpty());
    lineSize = str.size();
}
void MyWindow::okEnable2(QString str){
    okey->setEnabled(!str.isEmpty() && !line->text().isEmpty());
}

void MyWindow::randomPressed(){
    const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
    QString temp;
    int v;
    for(size_t i = 0; i != lineSize; ++i){
        v = QRandomGenerator::global()->bounded(0,possibleCharacters.size());
        temp.append(possibleCharacters.at(v));
    }

    gamma->setText(temp);
    label->update();

}

void MyWindow::okPressed(){
    if(line->text().size() > gamma->text().size())
        gamma->setText(stringSize(gamma->text(), line->text()));
    else if(line->text().size() < gamma->text().size()){
        QString subString = gamma->text().left(line->text().size());
        gamma->setText(subString);
    }

    QString cipher;
    gamuv(line->text(), gamma->text(), cipher);
    emit Sig(cipher);
}

QString stringSize(QString gamma, const QString &text){
    size_t gamSize = gamma.size();
    size_t dist = text.size() - gamSize;
    QString::const_iterator it = gamma.cbegin();
    for(size_t i = 0; i != dist; ++i, ++it){
        if(i == gamSize)
            it = gamma.cbegin();
        gamma.append(*it);
    }
    return gamma;
}

void gamuv(const QString &text, const QString &gamma, QString &newText){
    std::vector<std::bitset<8>> vecG;
    std::vector<std::bitset<8>> vecT;

    for(QString::const_iterator itG = gamma.cbegin(), itT = text.cbegin(); itG != gamma.end(); ++itG, ++itT){
        vecG.push_back(itG->toLatin1());
        vecT.push_back(itT->toLatin1());
    }

    for(auto itG = vecG.begin(), itT = vecT.begin(); itG != vecG.end(); ++itG, ++itT){
        *itG ^= *itT;
        newText.append(static_cast<char>(itG->to_ulong()));
    }

}

void MyWindow::readPressed(){
    QFile read("I:/VANIA GAMES/Qt/filein.txt");
    if(read.open(QIODevice::ReadOnly)){
        QByteArray block = read.readAll();
        line->setText(block);
        read.close();
    }
}




Interface::Interface(QWidget *parent) : QDialog(parent){
    text = new QTextEdit;
    write = new QPushButton("Write");


    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(text);
    layout->addWidget(write);

    setLayout(layout);

    connect(write, SIGNAL(clicked()), this, SLOT(writePressed()));

}
void Interface::Message(QString str){
    text->setText(str);
    text->setReadOnly(true);
    this->show();
}

void Interface::writePressed(){
    QMessageBox *msg = new QMessageBox;
    QFile write("I:/VANIA GAMES/Qt/fileout.txt");
    if(write.open(QIODevice::WriteOnly)){
        write.write(text->toPlainText().toUtf8());
        msg->setText("Successful write");
        msg->show();
        write.close();
    }
}

