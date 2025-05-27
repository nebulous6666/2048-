#include <QApplication>
#include "loginwindow.h"
#include "welcomewindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 先显示登录窗口
    LoginWindow loginWindow;
    loginWindow.show();

    // 创建欢迎窗口（但先不显示）
    WelcomeWindow welcomeWindow;

    // 登录成功后显示欢迎窗口
    QObject::connect(&loginWindow, &LoginWindow::loginSuccess, &welcomeWindow, [&](const QString &username) {
        welcomeWindow.show();
    });

    return a.exec();
}
