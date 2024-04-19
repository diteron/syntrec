#pragma once

class SyntRecApp : public QApplication {
public:
    SyntRecApp(int& argc, char** argv);
    ~SyntRecApp();

private:
    void setSystemColorScheme();
};
