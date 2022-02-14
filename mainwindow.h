#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_textEdit_3_textChanged();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_checkBox_stateChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QString cipher(bool invert);
    bool keyCheck();
    int *decodeDirection();
    void showDirection();
    bool checkAllInString(QString inpStr, QString fromStr);
    QString generateRandomKey();
    void saveKey();
    void setDefaultKey();

};
#endif // MAINWINDOW_H
