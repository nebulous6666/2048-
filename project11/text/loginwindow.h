#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

signals:
    void loginSuccess(const QString &username);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void onSwitchToRegisterClicked();
    void onSwitchToLoginClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;

    // 登录界面组件
    QWidget *loginWidget;
    QLineEdit *loginUsernameEdit;
    QLineEdit *loginPasswordEdit;
    QPushButton *loginButton;
    QPushButton *switchToRegisterButton;

    // 注册界面组件
    QWidget *registerWidget;
    QLineEdit *registerUsernameEdit;
    QLineEdit *registerPasswordEdit;
    QLineEdit *registerConfirmPasswordEdit;
    QPushButton *registerButton;
    QPushButton *switchToLoginButton;

    // 文件操作
    bool verifyUser(const QString &username, const QString &password);
    bool createUser(const QString &username, const QString &password);
};

#endif // LOGINWINDOW_H
