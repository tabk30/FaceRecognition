/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created: Tue Jun 10 17:40:49 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINSCREEN_H
#define UI_MAINSCREEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_MainScreen
{
public:
    QGroupBox *Input;
    QGroupBox *groupBox_2;
    QLineEdit *path;
    QPushButton *brow;
    QPushButton *OK;
    QGroupBox *ReSult;
    QLabel *Face_Detect;
    QGroupBox *Face_recognjtion;
    QLabel *FaceRecognition;
    QLabel *FR_Result;
    QGroupBox *groupBox_4;
    QTextBrowser *ResultLB;

    void setupUi(QDialog *MainScreen)
    {
        if (MainScreen->objectName().isEmpty())
            MainScreen->setObjectName(QString::fromUtf8("MainScreen"));
        MainScreen->resize(1301, 686);
        Input = new QGroupBox(MainScreen);
        Input->setObjectName(QString::fromUtf8("Input"));
        Input->setGeometry(QRect(30, 10, 951, 141));
        Input->setFlat(false);
        Input->setCheckable(false);
        groupBox_2 = new QGroupBox(Input);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 30, 931, 91));
        path = new QLineEdit(groupBox_2);
        path->setObjectName(QString::fromUtf8("path"));
        path->setGeometry(QRect(20, 40, 601, 31));
        brow = new QPushButton(groupBox_2);
        brow->setObjectName(QString::fromUtf8("brow"));
        brow->setGeometry(QRect(650, 40, 101, 31));
        OK = new QPushButton(groupBox_2);
        OK->setObjectName(QString::fromUtf8("OK"));
        OK->setGeometry(QRect(790, 40, 101, 31));
        ReSult = new QGroupBox(MainScreen);
        ReSult->setObjectName(QString::fromUtf8("ReSult"));
        ReSult->setGeometry(QRect(10, 150, 621, 531));
        Face_Detect = new QLabel(ReSult);
        Face_Detect->setObjectName(QString::fromUtf8("Face_Detect"));
        Face_Detect->setGeometry(QRect(10, 30, 591, 481));
        Face_recognjtion = new QGroupBox(MainScreen);
        Face_recognjtion->setObjectName(QString::fromUtf8("Face_recognjtion"));
        Face_recognjtion->setGeometry(QRect(650, 150, 621, 531));
        FaceRecognition = new QLabel(Face_recognjtion);
        FaceRecognition->setObjectName(QString::fromUtf8("FaceRecognition"));
        FaceRecognition->setGeometry(QRect(10, 30, 591, 481));
        FR_Result = new QLabel(Face_recognjtion);
        FR_Result->setObjectName(QString::fromUtf8("FR_Result"));
        FR_Result->setGeometry(QRect(80, 80, 251, 151));
        FR_Result->setMidLineWidth(1);
        groupBox_4 = new QGroupBox(MainScreen);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(990, 10, 281, 141));
        ResultLB = new QTextBrowser(groupBox_4);
        ResultLB->setObjectName(QString::fromUtf8("ResultLB"));
        ResultLB->setGeometry(QRect(0, 20, 281, 121));

        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QDialog *MainScreen)
    {
        MainScreen->setWindowTitle(QApplication::translate("MainScreen", "MainScreen", 0, QApplication::UnicodeUTF8));
        Input->setTitle(QApplication::translate("MainScreen", "Ipput", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainScreen", "Image Test", 0, QApplication::UnicodeUTF8));
        brow->setText(QApplication::translate("MainScreen", "Select", 0, QApplication::UnicodeUTF8));
        OK->setText(QApplication::translate("MainScreen", "OK", 0, QApplication::UnicodeUTF8));
        ReSult->setTitle(QApplication::translate("MainScreen", "Face Detection", 0, QApplication::UnicodeUTF8));
        Face_Detect->setText(QString());
        Face_recognjtion->setTitle(QApplication::translate("MainScreen", "Face Recognition", 0, QApplication::UnicodeUTF8));
        FaceRecognition->setText(QString());
        FR_Result->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainScreen", "List label assign for image", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
