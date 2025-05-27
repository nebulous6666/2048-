#include "welcomewindow.h"
#include "welcomewindow.h"
#include "gamewindow.h"
#include "instructionswindow.h"
#include "keybindingswindow.h"
#include <QFile>
#include <QTextStream>
WelcomeWindow::WelcomeWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("2048游戏 - 欢迎界面");//setWindowTitle：设置窗口的标题为 "2048 游戏 - 游戏说明"。
    setMinimumSize(800, 600);//setMinimumSize：设置窗口的最小尺寸为 600x400 像素。

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    //mainLayout 被定义成成员变量，这意味着在整个 WelcomeWindow 类的生命周期里都能访问该布局。

    mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("2048游戏", centralWidget); // 创建一个 QLabel 对象作为标题标签，显示 "游戏说明"。
    titleLabel->setAlignment(Qt::AlignCenter); // 设置标题标签的文本对齐方式为居中对齐。
    titleLabel->setStyleSheet("font-size: 48px; font-weight: bold; color: #776e65;");//     使用样式表设置标题标签的字体大小、字体粗细和颜色。
    mainLayout->addWidget(titleLabel);//         将标题标签添加到垂直布局中。

    // 添加间距
    QLabel *spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(10);
    mainLayout->addWidget(spacer);

    // 登录界面
    loginWidget = new QWidget(centralWidget);
    QVBoxLayout *loginLayout = new QVBoxLayout(loginWidget);

    usernameEdit = new QLineEdit(loginWidget);//这行代码创建了一个 QLineEdit 对象 usernameEdit，它是一个单行文本输入框，用于用户输入用户名。
    usernameEdit->setPlaceholderText("用户名");
    usernameEdit->setStyleSheet("font-size: 18px; padding: 10px; border-radius: 5px;");
    //font-size: 18px：将文本框内文本的字体大小设置为 18 像素。
    // padding: 10px：为文本框内的文本添加 10 像素的内边距，使文本不会紧贴文本框的边界。
    //border-radius: 5px：将文本框的边框设置为圆角，圆角半径为 5 像素，使文本框的外观更加美观。
    loginLayout->addWidget(usernameEdit);

    passwordEdit = new QLineEdit(loginWidget);
    passwordEdit->setPlaceholderText("密码");
    passwordEdit->setEchoMode(QLineEdit::Password);
    //用户输入的字符将不会以明文形式显示，
    passwordEdit->setStyleSheet("font-size: 18px; padding: 10px; border-radius: 5px;");
    loginLayout->addWidget(passwordEdit);

    loginButton = new QPushButton("登录", loginWidget);
    loginButton->setStyleSheet("font-size: 20px; padding: 10px; background-color: #8f7a66; color: white; border-radius: 5px;");
    loginButton->setFixedSize(150, 50);
    loginLayout->addWidget(loginButton, 0, Qt::AlignCenter);

    loginLayout->addSpacing(20);//这行代码在 loginLayout 布局中添加一个 20 像素的间距。
    mainLayout->addWidget(loginWidget, 0, Qt::AlignCenter);
    //这行代码将 loginWidget 添加到 mainLayout 布局中。mainLayout 是 WelcomeWindow 的主布局管理器，这里设置为 0 表示该部件不会随着布局的伸缩而改变大小。

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

// void WelcomeWindow::onLoginClicked()
// {
//     QString username = usernameEdit->text();
//     QString password = passwordEdit->text();

//     // 简单的登录验证（实际应用中应使用更安全的方法）
//     if (!username.isEmpty() && !password.isEmpty()) {
//         QMessageBox::information(this, "登录成功", "欢迎回来，" + username + "！");
//         startButton->setEnabled(true);
//         instructionsButton->setEnabled(true);
//         keyBindingsButton->setEnabled(true);
//         exitButton->setEnabled(true);
//         loginWidget->setVisible(false);
//     } else {
//         QMessageBox::warning(this, "登录失败", "请输入用户名和密码！");
//     }
// }




void WelcomeWindow::onLoginClicked()
{
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    // 打开存储账号密码的txt文件
    QFile file("E:/qt project/C++/project11/text/123.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "错误", "无法打开账号密码文件！");
        return;
    }

    QTextStream in(&file);
    bool loginSuccess = false;
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(" ");
        if (parts.size() == 2) {
            QString storedUsername = parts[0];
            QString storedPassword = parts[1];
            if (storedUsername == username && storedPassword == password) {
                loginSuccess = true;
                break;
            }
        }
    }
    file.close();

    if (loginSuccess) {
        QMessageBox::information(this, "登录成功", "欢迎回来，" + username + "！");
        startButton->setEnabled(true);
        instructionsButton->setEnabled(true);
        keyBindingsButton->setEnabled(true);
        exitButton->setEnabled(true);
        loginWidget->setVisible(false);
    } else {
        QMessageBox::warning(this, "登录失败", "请输入正确的用户名和密码！");
    }
}


void WelcomeWindow::onInstructionsClicked()
{
    InstructionsWindow *instructionsWindow = new InstructionsWindow(this);
    instructionsWindow->show();
}

void WelcomeWindow::onStartGameClicked()
{
    GameWindow *gameWindow = new GameWindow(this);
    gameWindow->show();
    gameWindow->setFocus();
    //1. 焦点问题
    //如果GameWindow窗口没有获取到焦点，那么它将无法接收键盘事件。在GameWindow显示时，需要确保它获得焦点。
    this->hide();
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
