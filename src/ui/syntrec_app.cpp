#include <pch.h>

#include "syntrec_app.h"

SyntRecApp::SyntRecApp(int& argc, char** argv) : QApplication(argc, argv)
{

#ifdef Q_OS_WIN
    setSystemColorScheme();
#endif

}

SyntRecApp::~SyntRecApp()
{}

void SyntRecApp::setSystemColorScheme()
{
    Qt::ColorScheme systemColorScheme = qApp->styleHints()->colorScheme();
    if (systemColorScheme == Qt::ColorScheme::Dark) {
        setStyle(QStyleFactory::create("fusion"));
    }
}