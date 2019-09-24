#include "mywindow.h"
QString English(std::string str, unsigned index, unsigned shift);
QString Ukrainian(QString str, unsigned index, unsigned shift, std::vector<std::pair<QChar,int>> lower, std::vector<std::pair<QChar,int>> upper);
void visit(QString const& chars, size_t max_len, QString const& cur);

MyWindow::MyWindow(QWidget *parent) : QDialog(parent)
{
    label = new QLabel("Введіть текст");
    line = new QLineEdit;
    okey = new QPushButton("Okey");
    close = new QPushButton("Close");
    read = new QPushButton("Read");
    language = new QComboBox;
    cipher = new QComboBox;
    slider = new QSlider(Qt::Horizontal);
    spinbox = new QSpinBox;

    language->addItem("Англійська"); language->addItem("Українська");
    cipher->addItem("Зашифрувати"); cipher->addItem("Розшифрувати");

    slider->setMaximum(25);slider->setMinimum(4);
    spinbox->setMaximum(25); spinbox->setMinimum(4);

    okey->setEnabled(false);

    Lower = {{L'а', 0}, {L'б', 1},{L'в', 2},{L'г', 3},{L'ґ', 4},{L'д', 5},{L'е', 6},{L'є', 7},{L'ж', 8},{L'з', 9},{L'и', 10},
                {L'і', 11},{L'ї', 12},{L'й', 13},{L'к', 14},{L'л', 15},{L'м', 16},{L'н', 17},{L'о', 18},{L'п', 19},{L'р', 20},{L'с', 21},
                {L'т', 22},{L'у', 23},{L'ф', 24},{L'х', 25},{L'ц', 26},{L'ч', 27},{L'ш', 28},{L'щ', 29}, {L'ь', 30},{L'ю', 31},{L'я', 32}

    };
    Upper = {{L'А', 0}, {L'Б', 1},{L'В', 2},{L'Г', 3},{L'Ґ', 4},{L'Д', 5},{L'Е', 6},{L'Є', 7},{L'Ж', 8},{L'З', 9},{L'И', 10},
                {L'І', 11},{L'Ї', 12},{L'Й', 13},{L'К', 14},{L'Л', 15},{L'М', 16},{L'Н', 17},{L'О', 18},{L'П', 19},{L'Р', 20},{L'С', 21},
                {L'Т', 22},{L'У', 23},{L'Ф', 24},{L'Х', 25},{L'Ц', 26},{L'Ч', 27},{L'Ш', 28},{L'Щ', 29}, {L'Ь', 30},{L'Ю', 31},{L'Я', 32}

    };

    QHBoxLayout *leftup = new QHBoxLayout;
    leftup->addWidget(language);
    leftup->addWidget(cipher);

    QHBoxLayout *leftcenter = new QHBoxLayout;
    leftcenter->addWidget(label);
    leftcenter->addWidget(line);

    QHBoxLayout *leftdown = new QHBoxLayout;
    leftdown->addWidget(spinbox);
    leftdown->addWidget(slider);

    QVBoxLayout *left = new QVBoxLayout;
    left->addLayout(leftup);
    left->addLayout(leftcenter);
    left->addLayout(leftdown);

    QVBoxLayout *right = new QVBoxLayout;
    right->addWidget(okey);
    right->addWidget(read);
    right->addWidget(close);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addLayout(right);

    setLayout(main);

    connect(spinbox, SIGNAL(valueChanged(int)), slider, SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)), spinbox, SLOT(setValue(int)));
    connect(close, SIGNAL(clicked()),this, SLOT(close()));
    connect(line, SIGNAL(textChanged(QString)), this, SLOT(okEnable(QString)));
    connect(okey, SIGNAL(clicked()), this, SLOT(okPressed()));
    connect(read, SIGNAL(clicked()), this, SLOT(readPressed()));

}

void MyWindow::okEnable(QString str){
    okey->setEnabled(!str.isEmpty());
}

void MyWindow::okPressed(){
    if(language->currentIndex() == 0){
        QString qstring = English((line->text()).toStdString(), cipher->currentIndex(), spinbox->value());
        emit Sig(qstring);
    }
    if(language->currentIndex() == 1){
        QString qstring = Ukrainian(line->text(), cipher->currentIndex(), spinbox->value(), Lower, Upper);
        emit Sig(qstring);
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

QString English(std::string str, unsigned index, unsigned shift){
    constexpr unsigned abcSize = 26;
    QString qstring;
    if(shift > 25) shift = 25;

    if(index == 0){
        for(auto &i : str){
            if(i >= 'A' && i <= 'Z'){
                i += shift;
                if(i > 'Z')
                    i -= abcSize;
            }
            else if(i >= 'a' && i <= 'z'){
                const int ind = static_cast<int>(i) + shift;
                if(ind > 127)
                    i =  i - abcSize + shift;
                else{
                   i += shift;
                    if(i > 'z')
                        i -= abcSize;
                }
            }

        }
    }

    else if(index == 1){
        for(auto &i : str){
            if(i >= 'A' && i <= 'Z'){
                i -= shift;
                if(i < 'A')
                    i += abcSize;
            }
            else if(i >= 'a' && i <= 'z'){
                i -= shift;
                if(i < 'a')
                    i += abcSize;
            }
        }
    }
    qstring = QString::fromStdString(str);
    return qstring;
}

QString Ukrainian(QString str, unsigned index, unsigned shift, std::vector<std::pair<QChar,int>> lower, std::vector<std::pair<QChar,int>> upper){

    std::vector<size_t> vec;
    for(size_t i = 0; i != 33; ++i)
        vec.push_back(i);

    if(index == 0){
        std::rotate(vec.begin(), vec.begin()+shift, vec.end());
        for(auto &i : str){
            bool ind = false;
               for(size_t j = 0; j != lower.size(); ++j)
                    if(i == lower[j].first){
                        i = lower.at(vec.at(j)).first;
                        ind = true;
                        break;
                    }
                if(!ind)
                    for(size_t j = 0; j != upper.size(); ++j)
                        if(i == upper[j].first){
                            i = upper.at(vec.at(j)).first;
                            break;
                        }
        }
    }
    else if(index == 1){
        std::rotate(vec.begin(), vec.end()-shift, vec.end());
        for(auto &i : str){
            bool ind = false;
               for(size_t j = 0; j != lower.size(); ++j)
                    if(i == lower[j].first){
                        i = lower.at(vec.at(j)).first;
                        ind = true;
                        break;
                    }
                if(!ind)
                    for(size_t j = 0; j != upper.size(); ++j)
                        if(i == upper[j].first){
                            i = upper.at(vec.at(j)).first;
                            break;
                        }
        }
    }

    return str;
}



Interface::Interface(QWidget *parent) : QDialog(parent){
    text = new QTextEdit;
    write = new QPushButton("Write");
    brute = new QPushButton("Brute Force");

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(text);
    layout->addWidget(write);
    layout->addWidget(brute);
    setLayout(layout);

    connect(write, SIGNAL(clicked()), this, SLOT(writePressed()));
    connect(brute, SIGNAL(clicked()), this, SLOT(bruteForce()));
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

void Interface::bruteForce(){
    visit("abcd", 4, "");
}
void visit(QString const& chars, size_t max_len, QString const& cur) {
    if(cur.length() == max_len) {
      return;
    }
    else {
      for(auto c : chars) {
        QString next = cur + c;
        qDebug() << next << '\n';

        visit(chars, max_len, next);
      }
    }
}
