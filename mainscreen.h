#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QDialog>
#include <QtGui>
#include <iostream>
#include "import/PCA/lib/PathGenerate.h"
#include "import/PCA/lib/ImageData.h"
#include "import/PCA/lib/NearestList.hpp"
#include "import/PCA/lib/Statistic.hpp"
#include "import/PCA/lib/FaceRecogniontPCA.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public QDialog
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = 0);
    ~MainScreen();
    QImage Mat2QImage(cv::Mat const& src);
public slots:
    void radioSelect();
    void quit();
    void openFile();
    void startRecognition();
private:
    Ui::MainScreen *ui;
    QTextEdit *textEdit;
    QPushButton *quitButton;
    FaceRecogniontPCA * pca_recogntition;
};

#endif // MAINSCREEN_H
