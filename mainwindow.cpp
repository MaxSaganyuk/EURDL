#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDir"
#include "QTextStream"
#include "QDebug"

QString alph = "abcdefghijklmnopqrstuvwxyz";
QString digits = "0123456789";

QString standart_key = "hn1r!j4i9da27gpzyolexcfk0bs3t$w586~qvum@";
QLabel *error_labels[4];


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    error_labels[0] = ui->label_5;
    error_labels[1] = ui->label_6;
    error_labels[2] = ui->label_7;
    error_labels[3] = ui->label_10;
    for(int i = 0; i < 4; ++i) error_labels[i]->setVisible(false);

    QFile file(QDir::currentPath() + "\\key.txt");
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream stream(&file);
        QString protoKey;

        stream >> protoKey;

        file.close();

        if(protoKey.length() == 40) ui->textEdit_3->setText(protoKey);
        if(!keyCheck()) ui->textEdit_3->setText(standart_key);
    }
    else ui->textEdit_3->setText(standart_key);

}

int *MainWindow::decodeDirection(){
    int *directions = new int[4];

    if(ui->checkBox->isChecked()){
        for(int i = 0; i < 4; ++i) directions[i] = i;
    }
    else{
        QString key = ui->textEdit_3->toPlainText();

        int count = 0;
        for(int i = 0; i < key.length(); ++i){
            if(alph.indexOf(key[i]) == -1 && digits.indexOf(key[i]) == -1){
                directions[count++] = i % 4;
                //printf("%i\n", i);
            }
        }
    }

    return directions;
}

void MainWindow::showDirection(){
    int *direction = decodeDirection();
    QString directions_str = "URDL";
    QString res = "";

    for(int i = 0; i < 4; ++i){
        res += directions_str[direction[i]];
    }

    ui->label_9->setText(res);
}

QString MainWindow::generateRandomKey(){
    QString newKey = standart_key;

    int currentRand1;
    int currentRand2;

    QChar currentChar1;
    QChar currentChar2;

    for(int i = 0; i < standart_key.length(); ++i){
        currentRand1 = qrand() % 40;
        currentRand2 = qrand() % 40;

        currentChar1 = newKey[currentRand1];
        currentChar2 = newKey[currentRand2];

        newKey[currentRand2] = currentChar1;
        newKey[currentRand1] = currentChar2;
    }

    return newKey;
}

QString MainWindow::cipher(bool invert){
    enum Direction{
        UP,
        RIGHT,
        DOWN,
        LEFT
    };

    QString key = ui->textEdit_3->toPlainText();
    QString grid[4][10];

    for(int i = 0; i < 4; ++i){
        for(int j = 0; j < 10; ++j) grid[i][j] = key[10 * i + j];
    }

    QString text;
    if(invert) text = ui->textEdit_2->toPlainText();
    else text = ui->textEdit->toPlainText();

    text = text.toLower();

    int *direction = decodeDirection();
    if(invert){
        for(int i = 0; i < 4; ++i){
            direction[i] = (direction[i] + 2) % 4;
        }
    }

    QString res = "";

    int i = 0;
    int j = 0;
    int currentIndex;
    int directionIndex = 0;

    //printf("%i\n", text.length());
    for(int count = 0; count < text.length(); ++count){
        if(key.indexOf(text[count]) == -1){
            res += text[count];
            continue;
        }

        currentIndex = key.indexOf(text[count]);
        //printf("%i\n", key.indexOf(text[count]));
        i = currentIndex / 10;
        j = currentIndex % 10;

        switch (direction[directionIndex]) {
            case UP:
                --i;
                if(i < 0) i = 3;
                break;
            case RIGHT:
                ++j;
                if(j > 9) j = 0;
                break;
            case DOWN:
                ++i;
                if(i > 3) i = 0;
                break;
            case LEFT:
                --j;
                if(j < 0) j = 9;
                break;
        }

        ++directionIndex;
        res += grid[i][j];
        if(directionIndex == 4) directionIndex = 0;
    }

    return res;

}

bool MainWindow::checkAllInString(QString inpStr, QString fromStr){
    bool res;

    int currentIndexOf;
    bool *fromStr_bool = new bool[fromStr.length()];

    for(int i = 0; i < fromStr.length(); ++i) fromStr_bool[i] = false;
    int fromStr_count = 0;

    for(int i = 0; i < inpStr.length(); ++i){
        currentIndexOf = fromStr.indexOf(inpStr[i]);
        if(currentIndexOf != -1 && !fromStr_bool[currentIndexOf]){
            fromStr_bool[currentIndexOf] = true;
            ++fromStr_count;
        }
    }

    if(fromStr_count != fromStr.length()) res = true;
    else res = false;

    return res;
}

bool MainWindow::keyCheck(){
    QString inpKey = ui->textEdit_3->toPlainText();

    ui->label_9->setText("");

    bool allFlagsFalse = true;
    bool flags[4];
    for(int i = 0; i < 4; ++i) flags[i] = false;

    if(inpKey.length() != 40){
        flags[0] = true;
    }
    flags[1] = checkAllInString(inpKey, alph);
    flags[2] = checkAllInString(inpKey, digits);

    QString uniqueChars = "";
    for(int i = 0; i < inpKey.length(); ++i){
        if(alph.indexOf(inpKey[i]) == -1 && digits.indexOf(inpKey[i]) == -1 && uniqueChars.indexOf(inpKey[i]) == -1){
            uniqueChars += inpKey[i];
        }
    }
    if(uniqueChars.length() != 4) flags[3] = true;

    for(int i = 0; i < 4; ++i){
        if(flags[i]){
            error_labels[i]->setVisible(true);
            allFlagsFalse = false;
        }
        else{
            error_labels[i]->setVisible(false);
        }
    }

    if(allFlagsFalse) showDirection();

    return allFlagsFalse;
}

void MainWindow::saveKey(){
    QFile file(QDir::currentPath() + "\\key.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream stream(&file);

        stream << ui->textEdit_3->toPlainText();

        file.close();
    }

}

void MainWindow::setDefaultKey(){

    ui->textEdit_3->setText(standart_key);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_textEdit_3_textChanged(){
    keyCheck();
}

void MainWindow::on_pushButton_3_clicked(){
    ui->textEdit_3->setText(generateRandomKey());
}

void MainWindow::on_pushButton_clicked()
{
    if(keyCheck()) ui->textEdit_2->setText(cipher(false));
}

void MainWindow::on_pushButton_2_clicked()
{
    if(keyCheck()) ui->textEdit->setText(cipher(true));
}

void MainWindow::on_pushButton_4_clicked()
{
    if(keyCheck()) saveKey();
}

void MainWindow::on_pushButton_5_clicked()
{
    setDefaultKey();
}

void MainWindow::on_checkBox_stateChanged(int arg1){
    keyCheck();
}
