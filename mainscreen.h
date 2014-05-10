#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QDialog>
#include <QtGui>
#include <iostream>
namespace Ui {
class MainScreen;
}

class MainScreen : public QDialog
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();
public slots:
    void radioSelect();
    void quit();
    void openFile();
    void startRecognition();
private:
    Ui::MainScreen *ui;
    QTextEdit *textEdit;
    QPushButton *quitButton;
};

#endif // MAINSCREEN_H
