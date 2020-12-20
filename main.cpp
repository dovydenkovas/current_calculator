#include <QApplication>
// import main window
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("images/logo.png"));
    MainWindow win;
    win.show();
    return QApplication::exec();
}

