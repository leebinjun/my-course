#include "keyevent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    ThreadDlg w1;
//    w1.show();


    KeyEvent w;
    w.show();


    return a.exec();
}
