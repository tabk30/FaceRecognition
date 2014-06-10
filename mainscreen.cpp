#include "mainscreen.h"
#include "ui_mainscreen.h"

MainScreen::MainScreen(QWidget *parent) :
QDialog(parent),
ui(new Ui::MainScreen) {
    ui->setupUi(this);
    connect(ui->brow, SIGNAL(clicked()), this, SLOT(openFile()));


    connect(ui->OK, SIGNAL(clicked()), this, SLOT(startRecognition()));

    this->pca_recogntition = new FaceRecogniontPCA();
}

MainScreen::~MainScreen() {
    delete ui;
}

void MainScreen::radioSelect() {
}

void MainScreen::quit() {
    //    std::cout << "Test click event" << std::endl;
}

void MainScreen::openFile() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "",
            tr("Image Files (*.png *.jpg *.jpeg *.pgm);"));

    if (fileName != "") {
        //std::cout << "Test click event: " <<  fileName.toStdString() << std::endl;
        ui->path->setText(fileName);
    }
}

void MainScreen::startRecognition() {

    QString string_path = ui->path->text();
    if (string_path.toStdString().length() > 0) {
        vector<string> _result_fr = this->pca_recogntition->recognition(string_path.toStdString());

        Mat face_detect = Mat(this->pca_recogntition->face_detect);
        QImage q_face_detect = this->Mat2QImage(face_detect);

        this->ui->Face_Detect->setPixmap(QPixmap::fromImage(q_face_detect));
        this->ui->Face_Detect->show();

        Mat face_recognition = Mat(this->pca_recogntition->face_recognition);
        QImage q_face_recognition = this->Mat2QImage(face_recognition);

        this->ui->FaceRecognition->setPixmap(QPixmap::fromImage(q_face_recognition));
        this->ui->FaceRecognition->show();

        //set result:
        string _result_display = "<ol>";
        for (unsigned int i = 0; i < _result_fr.size(); i++) {
            _result_display.append("<li>");
            _result_display.append(_result_fr.at(i));
            _result_display.append("</li>");
        }
        _result_display.append("<ol>");
        QString richText(_result_display.c_str());

        this->ui->ResultLB->setText(richText);
        this->ui->ResultLB->show();
    }
}

QImage MainScreen::Mat2QImage(cv::Mat const& inMat) {
    switch (inMat.type()) {
            // 8-bit, 4 channel
        case CV_8UC4:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB32);

            return image;
        }

            // 8-bit, 3 channel
        case CV_8UC3:
        {
            QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_RGB888);

            return image.rgbSwapped();
        }

            // 8-bit, 1 channel
        case CV_8UC1:
        {
            static QVector<QRgb> sColorTable;

            // only create our color table once
            if (sColorTable.isEmpty()) {
                for (int i = 0; i < 256; ++i)
                    sColorTable.push_back(qRgb(i, i, i));
            }

            QImage image(inMat.data, inMat.cols, inMat.rows, inMat.step, QImage::Format_Indexed8);

            image.setColorTable(sColorTable);

            return image;
        }

        default:
            qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << inMat.type();
            break;
    }

    return QImage();
}
