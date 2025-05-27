#include "loginwindow.h"
#include <QVBoxLayout>
#include <QWidget>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("登录");
    setMinimumSize(300, 200);

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);

    usernameEdit = new QLineEdit(central);
    usernameEdit->setPlaceholderText("用户名");
    layout->addWidget(usernameEdit);

    passwordEdit = new QLineEdit(central);
    passwordEdit->setPlaceholderText("密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordEdit);

    loginButton = new QPushButton("登录", central);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}

LoginWindow::~LoginWindow() {}

void LoginWindow::onLoginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (!username.isEmpty() && !password.isEmpty()) {
        emit loginSuccess(username);
        this->close();
    } else {
        QMessageBox::warning(this, "登录失败", "请输入用户名和密码！");
    }
}