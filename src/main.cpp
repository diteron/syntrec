#include "pch.h"

#include "ui/syntrec_app.h"
#include "ui/main_window.h"

int main(int argc, char** argv)
{
    SyntRecApp app(argc, argv);
    
    const int width = 1220, height = 650;
    MainWindow mainWnd(width, height);
    mainWnd.setFixedSize(width, height);
    mainWnd.show();
    
    int result = app.exec();
    return result;
}
