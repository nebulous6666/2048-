#include "loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("2048游戏 - 登录");
    setMinimumSize(400, 300);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
centralWidget->setStyleSheet("background-color: #f5f5dc;");
    mainLayout = new QVBoxLayout(centralWidget);

    // 登录界面
    loginWidget = new QWidget(centralWidget);
    QVBoxLayout *loginLayout = new QVBoxLayout(loginWidget);

    QLabel *loginTitleLabel = new QLabel("用户登录", loginWidget);
    loginTitleLabel->setAlignment(Qt::AlignCenter);
    loginTitleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #776e65;");
    loginLayout->addWidget(loginTitleLabel);

    loginLayout->addSpacing(20);

    loginUsernameEdit = new QLineEdit(loginWidget);
    loginUsernameEdit->setPlaceholderText("用户名");
    loginUsernameEdit->setStyleSheet("font-size: 16px; padding: 8px; border-radius: 5px;");
    loginLayout->addWidget(loginUsernameEdit);

    loginPasswordEdit = new QLineEdit(loginWidget);
    loginPasswordEdit->setPlaceholderText("密码");
    loginPasswordEdit->setEchoMode(QLineEdit::Password);
    loginPasswordEdit->setStyleSheet("font-size: 16px; padding: 8px; border-radius: 5px;");
    loginLayout->addWidget(loginPasswordEdit);

    loginLayout->addSpacing(10);

    loginButton = new QPushButton("登录", loginWidget);
    loginButton->setStyleSheet("font-size: 18px; padding: 10px; background-color: #8f7a66; color: white; border-radius: 5px;");
    loginLayout->addWidget(loginButton);

    loginLayout->addSpacing(20);

    switchToRegisterButton = new QPushButton("没有账号？注册新用户", loginWidget);
    switchToRegisterButton->setStyleSheet("font-size: 14px; color: #776e65; border: none;");
    switchToRegisterButton->setFlat(true);
    loginLayout->addWidget(switchToRegisterButton);

    mainLayout->addWidget(loginWidget);

    // 注册界面（默认隐藏）
    registerWidget = new QWidget(centralWidget);
    QVBoxLayout *registerLayout = new QVBoxLayout(registerWidget);

    QLabel *registerTitleLabel = new QLabel("注册新用户", registerWidget);
    registerTitleLabel->setAlignment(Qt::AlignCenter);
    registerTitleLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #776e65;");
    registerLayout->addWidget(registerTitleLabel);

    registerLayout->addSpacing(20);

    registerUsernameEdit = new QLineEdit(registerWidget);
    registerUsernameEdit->setPlaceholderText("用户名");
    registerUsernameEdit->setStyleSheet("font-size: 16px; padding: 8px; border-radius: 5px;");
    registerLayout->addWidget(registerUsernameEdit);

    registerPasswordEdit = new QLineEdit(registerWidget);
    registerPasswordEdit->setPlaceholderText("密码");
    registerPasswordEdit->setEchoMode(QLineEdit::Password);
    registerPasswordEdit->setStyleSheet("font-size: 16px; padding: 8px; border-radius: 5px;");
    registerLayout->addWidget(registerPasswordEdit);

    registerConfirmPasswordEdit = new QLineEdit(registerWidget);
    registerConfirmPasswordEdit->setPlaceholderText("确认密码");
    registerConfirmPasswordEdit->setEchoMode(QLineEdit::Password);
    registerConfirmPasswordEdit->setStyleSheet("font-size: 16px; padding: 8px; border-radius: 5px;");
    registerLayout->addWidget(registerConfirmPasswordEdit);

    registerLayout->addSpacing(10);

    registerButton = new QPushButton("注册", registerWidget);
    registerButton->setStyleSheet("font-size: 18px; padding: 10px; background-color: #edcf72; color: #f9f6f2; border-radius: 5px;");
    registerLayout->addWidget(registerButton);

    registerLayout->addSpacing(20);

    switchToLoginButton = new QPushButton("已有账号？返回登录", registerWidget);
    switchToLoginButton->setStyleSheet("font-size: 14px; color: #776e65; border: none;");
    switchToLoginButton->setFlat(true);
    registerLayout->addWidget(switchToLoginButton);

    mainLayout->addWidget(registerWidget);

    // 初始显示登录界面，隐藏注册界面
    loginWidget->show();
    registerWidget->hide();

    // 连接信号和槽
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &LoginWindow::onRegisterButtonClicked);
    connect(switchToRegisterButton, &QPushButton::clicked, this, &LoginWindow::onSwitchToRegisterClicked);
    connect(switchToLoginButton, &QPushButton::clicked, this, &LoginWindow::onSwitchToLoginClicked);
}

LoginWindow::~LoginWindow()
{
}

void LoginWindow::onSwitchToRegisterClicked()
{
    loginWidget->hide();
    registerWidget->show();
}
void LoginWindow::onLoginButtonClicked()
{
    QString username = loginUsernameEdit->text().trimmed();
    QString password = loginPasswordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录失败", "请输入用户名和密码！");
        return;
    }

    if (verifyUser(username, password)) {
        emit loginSuccess(username);
        this->close();
    } else {
        QMessageBox::warning(this, "登录失败", "用户名或密码错误！");
    }
}

void LoginWindow::onRegisterButtonClicked()
{
    QString username = registerUsernameEdit->text().trimmed();
    QString password = registerPasswordEdit->text();
    QString confirmPassword = registerConfirmPasswordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "注册失败", "用户名和密码不能为空！");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "注册失败", "两次输入的密码不一致！");
        return;
    }

    if (createUser(username, password)) {
        QMessageBox::information(this, "注册成功", "账号创建成功，请登录！");
        onSwitchToLoginClicked();
    } else {
        QMessageBox::warning(this, "注册失败", "用户名已存在！");
    }
}


void LoginWindow::onSwitchToLoginClicked()
{
    registerWidget->hide();
    loginWidget->show();
}

bool LoginWindow::verifyUser(const QString &username, const QString &password)
{
    QFile file("E:/qt project/C++/project11/text/123.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false; // 文件不存在或无法打开，视为无用户
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 2 && parts[0] == username && parts[1] == password) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

bool LoginWindow::createUser(const QString &username, const QString &password)
{
    // 先检查用户是否已存在
    if (verifyUser(username, password)) {
        return false;
    }

    // 追加新用户到文件
    QFile file("E:/qt project/C++/project11/text/123.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        QMessageBox::critical(this, "错误", "无法创建账号文件！");
        return false;
    }

    QTextStream out(&file);
    out << username << " " << password << "\n";
    file.close();

    return true;
}
