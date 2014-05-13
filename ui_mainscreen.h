/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created: Wed May 14 05:07:37 2014
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
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>

QT_BEGIN_NAMESPACE

class Ui_MainScreen
{
public:
    QGroupBox *Input;
    QGroupBox *method;
    QRadioButton *pca;
    QRadioButton *lda;
    QGroupBox *groupBox;
    QRadioButton *profile_face;
    QRadioButton *fronta_face;
    QGroupBox *groupBox_3;
    QCheckBox *use_ELT;
    QGroupBox *groupBox_2;
    QLineEdit *path;
    QPushButton *brow;
    QPushButton *OK;
    QGroupBox *ReSult;
    QLabel *Face_Detect;
    QGroupBox *Face_recognjtion;
    QLabel *FaceRecognition;
    QGroupBox *groupBox_4;
    QLabel *FR_Result;

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
        method = new QGroupBox(Input);
        method->setObjectName(QString::fromUtf8("method"));
        method->setEnabled(true);
        method->setGeometry(QRect(10, 30, 211, 101));
        pca = new QRadioButton(method);
        pca->setObjectName(QString::fromUtf8("pca"));
        pca->setGeometry(QRect(10, 30, 91, 22));
        pca->setChecked(true);
        lda = new QRadioButton(method);
        lda->setObjectName(QString::fromUtf8("lda"));
        lda->setGeometry(QRect(10, 60, 116, 22));
        lda->setChecked(false);
        groupBox = new QGroupBox(Input);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(370, 30, 241, 91));
        profile_face = new QRadioButton(groupBox);
        profile_face->setObjectName(QString::fromUtf8("profile_face"));
        profile_face->setGeometry(QRect(10, 30, 116, 22));
        profile_face->setChecked(true);
        fronta_face = new QRadioButton(groupBox);
        fronta_face->setObjectName(QString::fromUtf8("fronta_face"));
        fronta_face->setGeometry(QRect(10, 60, 116, 22));
        groupBox_3 = new QGroupBox(Input);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(180, 30, 171, 81));
        use_ELT = new QCheckBox(groupBox_3);
        use_ELT->setObjectName(QString::fromUtf8("use_ELT"));
        use_ELT->setGeometry(QRect(40, 20, 97, 31));
        groupBox_2 = new QGroupBox(Input);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(520, 30, 421, 91));
        path = new QLineEdit(groupBox_2);
        path->setObjectName(QString::fromUtf8("path"));
        path->setGeometry(QRect(20, 40, 291, 31));
        brow = new QPushButton(groupBox_2);
        brow->setObjectName(QString::fromUtf8("brow"));
        brow->setGeometry(QRect(320, 40, 101, 31));
        OK = new QPushButton(Input);
        OK->setObjectName(QString::fromUtf8("OK"));
        OK->setGeometry(QRect(840, 110, 101, 31));
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
        groupBox_4 = new QGroupBox(MainScreen);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(990, 10, 281, 181));
        FR_Result = new QLabel(groupBox_4);
        FR_Result->setObjectName(QString::fromUtf8("FR_Result"));
        FR_Result->setGeometry(QRect(20, 30, 251, 151));
        FR_Result->setMidLineWidth(1);

        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QDialog *MainScreen)
    {
        MainScreen->setWindowTitle(QApplication::translate("MainScreen", "MainScreen", 0, QApplication::UnicodeUTF8));
        Input->setTitle(QApplication::translate("MainScreen", "Ipput", 0, QApplication::UnicodeUTF8));
        method->setTitle(QApplication::translate("MainScreen", "Recognition Method", 0, QApplication::UnicodeUTF8));
        pca->setText(QApplication::translate("MainScreen", "PCA", 0, QApplication::UnicodeUTF8));
        lda->setText(QApplication::translate("MainScreen", "LDA", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainScreen", "Data train", 0, QApplication::UnicodeUTF8));
        profile_face->setText(QApplication::translate("MainScreen", "Profile face", 0, QApplication::UnicodeUTF8));
        fronta_face->setText(QApplication::translate("MainScreen", "Frontal face", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainScreen", "Enhanced Local Texture ", 0, QApplication::UnicodeUTF8));
        use_ELT->setText(QApplication::translate("MainScreen", "Use", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainScreen", "Image Test", 0, QApplication::UnicodeUTF8));
        brow->setText(QApplication::translate("MainScreen", "Select", 0, QApplication::UnicodeUTF8));
        OK->setText(QApplication::translate("MainScreen", "OK", 0, QApplication::UnicodeUTF8));
        ReSult->setTitle(QApplication::translate("MainScreen", "Face Detection", 0, QApplication::UnicodeUTF8));
        Face_Detect->setText(QString());
        Face_recognjtion->setTitle(QApplication::translate("MainScreen", "Face Recognition", 0, QApplication::UnicodeUTF8));
        FaceRecognition->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainScreen", "List label assign for image", 0, QApplication::UnicodeUTF8));
        FR_Result->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
