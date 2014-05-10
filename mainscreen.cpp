#include "mainscreen.h"
#include "ui_mainscreen.h"



MainScreen::MainScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
    connect(ui->brow, SIGNAL(clicked()), this, SLOT(openFile()));


    connect(ui->OK, SIGNAL(clicked()), this, SLOT(startRecognition()));
}

MainScreen::~MainScreen()
{
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

void MainScreen::startRecognition(){
    bool use_elt = false;
    int data_train = 0, method = 0;
    //Method:
    if(ui->pca->isChecked()){
        method = 0;
    }else {
        method = 1;
    }
    
    if(ui->use_ELT->isChecked()){
        use_elt = true;
    }else {
        use_elt = false;
    }
    
    if(ui->fronta_face->isChecked()){
        data_train = 1;
    }else if(ui->profile_face->isChecked()){
        data_train = 0;
    }
    
    QString string_path = ui->path->text();
    if(string_path.toStdString().length() > 0 ){
        std::cout << "image path: " << string_path.toStdString() << std::endl;
    }else {
        std::cout << "image path error" << std::endl;
    }
    
    std::cout << "result: " << " method: " << method << " data: " << data_train;
    
}
