#include "welcomewindow.h"
#include "welcomewindow.h"
#include "gamewindow.h"
#include "instructionswindow.h"
#include "keybindingswindow.h"

WelcomeWindow::WelcomeWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("2048游戏 - 欢迎界面");
    setMinimumSize(800, 600);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("2048游戏", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 48px; font-weight: bold; color: #776e65;");
    mainLayout->addWidget(titleLabel);

    // 添加间距
    QLabel *spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(50);
    mainLayout->addWidget(spacer);

    // 登录界面
    loginWidget = new QWidget(centralWidget);
    QVBoxLayout *loginLayout = new QVBoxLayout(loginWidget);

    usernameEdit = new QLineEdit(loginWidget);
    usernameEdit->setPlaceholderText("用户名");
    usernameEdit->setStyleSheet("font-size: 18px; padding: 10px; border-radius: 5px;");
    loginLayout->addWidget(usernameEdit);

    passwordEdit = new QLineEdit(loginWidget);
    passwordEdit->setPlaceholderText("密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setStyleSheet("font-size: 18px; padding: 10px; border-radius: 5px;");
    loginLayout->addWidget(passwordEdit);

    loginButton = new QPushButton("登录", loginWidget);
    loginButton->setStyleSheet("font-size: 20px; padding: 10px; background-color: #8f7a66; color: white; border-radius: 5px;");
    loginButton->setFixedSize(150, 50);
    loginLayout->addWidget(loginButton, 0, Qt::AlignCenter);

    loginLayout->addSpacing(20);
    mainLayout->addWidget(loginWidget, 0, Qt::AlignCenter);

    // 添加间距
    spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(30);
    mainLayout->addWidget(spacer);

    // 游戏菜单
    QWidget *menuWidget = new QWidget(centralWidget);
    QVBoxLayout *menuLayout = new QVBoxLayout(menuWidget);

    startButton = new QPushButton("开始游戏", menuWidget);
    startButton->setStyleSheet("font-size: 24px; padding: 15px; background-color: #edcf72; color: #f9f6f2; border-radius: 10px;");
    startButton->setFixedSize(250, 60);
    menuLayout->addWidget(startButton, 0, Qt::AlignCenter);

    instructionsButton = new QPushButton("游戏说明", menuWidget);
    instructionsButton->setStyleSheet("font-size: 24px; padding: 15px; background-color: #edcc61; color: #f9f6f2; border-radius: 10px;");
    instructionsButton->setFixedSize(250, 60);
    menuLayout->addWidget(instructionsButton, 0, Qt::AlignCenter);

    keyBindingsButton = new QPushButton("按键说明", menuWidget);
    keyBindingsButton->setStyleSheet("font-size: 24px; padding: 15px; background-color: #edc850; color: #f9f6f2; border-radius: 10px;");
    keyBindingsButton->setFixedSize(250, 60);
    menuLayout->addWidget(keyBindingsButton, 0, Qt::AlignCenter);

    exitButton = new QPushButton("退出游戏", menuWidget);
    exitButton->setStyleSheet("font-size: 24px; padding: 15px; background-color: #edc53f; color: #f9f6f2; border-radius: 10px;");
    exitButton->setFixedSize(250, 60);
    menuLayout->addWidget(exitButton, 0, Qt::AlignCenter);

    menuLayout->addSpacing(20);
    mainLayout->addWidget(menuWidget, 0, Qt::AlignCenter);

    // 初始禁用菜单按钮
    startButton->setEnabled(false);
    instructionsButton->setEnabled(false);
    keyBindingsButton->setEnabled(false);
    exitButton->setEnabled(false);

    // 连接信号和槽
    connect(startButton, &QPushButton::clicked, this, &WelcomeWindow::onStartGameClicked);
    connect(instructionsButton, &QPushButton::clicked, this, &WelcomeWindow::onInstructionsClicked);
    connect(keyBindingsButton, &QPushButton::clicked, this, &WelcomeWindow::onKeyBindingsClicked);
    connect(exitButton, &QPushButton::clicked, this, &WelcomeWindow::onExitClicked);
    connect(loginButton, &QPushButton::clicked, this, &WelcomeWindow::onLoginClicked);
}

WelcomeWindow::~WelcomeWindow()
{
}

void WelcomeWindow::onLoginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // 简单的登录验证（实际应用中应使用更安全的方法）
    if (!username.isEmpty() && !password.isEmpty()) {
        QMessageBox::information(this, "登录成功", "欢迎回来，" + username + "！");
        startButton->setEnabled(true);
        instructionsButton->setEnabled(true);
        keyBindingsButton->setEnabled(true);
        exitButton->setEnabled(true);
        loginWidget->setVisible(false);
    } else {
        QMessageBox::warning(this, "登录失败", "请输入用户名和密码！");
    }
}

void WelcomeWindow::onStartGameClicked()
{
    GameWindow *gameWindow = new GameWindow(this);
    gameWindow->show();
    this->hide();
}

void WelcomeWindow::onInstructionsClicked()
{
    InstructionsWindow *instructionsWindow = new InstructionsWindow(this);
    instructionsWindow->show();
}

void WelcomeWindow::onKeyBindingsClicked()
{
    KeyBindingsWindow *keyBindingsWindow = new KeyBindingsWindow(this);
    keyBindingsWindow->show();
}

void WelcomeWindow::onExitClicked()
{
    QApplication::quit();
}
