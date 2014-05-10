/********************************************************************************
** Form generated from reading UI file 'mainscreen.ui'
**
** Created: Sat May 10 00:33:00 2014
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
    QGroupBox *method;
    QRadioButton *pca;
    QRadioButton *lda;
    QPushButton *OK;
    QLabel *label;
    QCheckBox *use_ELT;
    QGroupBox *groupBox;
    QRadioButton *profile_face;
    QRadioButton *fronta_face;
    QGroupBox *groupBox_2;
    QLineEdit *path;
    QPushButton *brow;

    void setupUi(QDialog *MainScreen)
    {
        if (MainScreen->objectName().isEmpty())
            MainScreen->setObjectName(QString::fromUtf8("MainScreen"));
        MainScreen->resize(498, 369);
        method = new QGroupBox(MainScreen);
        method->setObjectName(QString::fromUtf8("method"));
        method->setEnabled(true);
        method->setGeometry(QRect(20, 20, 441, 61));
        pca = new QRadioButton(method);
        pca->setObjectName(QString::fromUtf8("pca"));
        pca->setGeometry(QRect(60, 30, 91, 22));
        pca->setChecked(true);
        lda = new QRadioButton(method);
        lda->setObjectName(QString::fromUtf8("lda"));
        lda->setGeometry(QRect(220, 30, 116, 22));
        lda->setChecked(false);
        OK = new QPushButton(MainScreen);
        OK->setObjectName(QString::fromUtf8("OK"));
        OK->setGeometry(QRect(380, 330, 98, 27));
        label = new QLabel(MainScreen);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 90, 171, 31));
        use_ELT = new QCheckBox(MainScreen);
        use_ELT->setObjectName(QString::fromUtf8("use_ELT"));
        use_ELT->setGeometry(QRect(240, 90, 97, 31));
        groupBox = new QGroupBox(MainScreen);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 150, 441, 80));
        profile_face = new QRadioButton(groupBox);
        profile_face->setObjectName(QString::fromUtf8("profile_face"));
        profile_face->setGeometry(QRect(70, 30, 116, 22));
        profile_face->setChecked(true);
        fronta_face = new QRadioButton(groupBox);
        fronta_face->setObjectName(QString::fromUtf8("fronta_face"));
        fronta_face->setGeometry(QRect(220, 30, 116, 22));
        groupBox_2 = new QGroupBox(MainScreen);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 240, 421, 71));
        path = new QLineEdit(groupBox_2);
        path->setObjectName(QString::fromUtf8("path"));
        path->setGeometry(QRect(10, 20, 291, 31));
        brow = new QPushButton(groupBox_2);
        brow->setObjectName(QString::fromUtf8("brow"));
        brow->setGeometry(QRect(320, 20, 98, 31));

        retranslateUi(MainScreen);

        QMetaObject::connectSlotsByName(MainScreen);
    } // setupUi

    void retranslateUi(QDialog *MainScreen)
    {
        MainScreen->setWindowTitle(QApplication::translate("MainScreen", "MainScreen", 0, QApplication::UnicodeUTF8));
        method->setTitle(QApplication::translate("MainScreen", "Recognition Method", 0, QApplication::UnicodeUTF8));
        pca->setText(QApplication::translate("MainScreen", "PCA", 0, QApplication::UnicodeUTF8));
        lda->setText(QApplication::translate("MainScreen", "LDA", 0, QApplication::UnicodeUTF8));
        OK->setText(QApplication::translate("MainScreen", "OK", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainScreen", "Enhanced Local Texture ", 0, QApplication::UnicodeUTF8));
        use_ELT->setText(QApplication::translate("MainScreen", "Use", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainScreen", "Data train", 0, QApplication::UnicodeUTF8));
        profile_face->setText(QApplication::translate("MainScreen", "Profile face", 0, QApplication::UnicodeUTF8));
        fronta_face->setText(QApplication::translate("MainScreen", "Frontal face", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainScreen", "Image Test", 0, QApplication::UnicodeUTF8));
        brow->setText(QApplication::translate("MainScreen", "Select", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainScreen: public Ui_MainScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINSCREEN_H
