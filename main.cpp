#include "mainscreen.h"
#include <QApplication>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <map>
#include "import/PCA/lib/PathGenerate.h"
#include "import/PCA/lib/ImageData.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainScreen w;
    w.show();

    return a.exec();
}
