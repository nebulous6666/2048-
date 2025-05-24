#include "keybindingswindow.h"

KeyBindingsWindow::KeyBindingsWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("2048游戏 - 按键说明");
    setMinimumSize(600, 400);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("按键说明", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #776e65;");
    mainLayout->addWidget(titleLabel);

    // 添加间距
    QLabel *spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(20);
    mainLayout->addWidget(spacer);

    keyBindingsLabel = new QLabel(
        "2048游戏支持以下按键操作：\n\n"
        "方向键：\n"
        "↑ (上箭头) - 向上移动方块\n"
        "↓ (下箭头) - 向下移动方块\n"
        "← (左箭头) - 向左移动方块\n"
        "→ (右箭头) - 向右移动方块\n\n"
        "WASD键：\n"
        "W - 向上移动方块\n"
        "S - 向下移动方块\n"
        "A - 向左移动方块\n"
        "D - 向右移动方块\n\n"
        "游戏控制：\n"
        "N - 开始新游戏\n"
        "S - 保存当前游戏\n"
        "L - 加载已保存的游戏\n"
        "ESC - 返回主菜单",
        centralWidget
        );
    keyBindingsLabel->setAlignment(Qt::AlignLeft);
    keyBindingsLabel->setStyleSheet("font-size: 18px; color: #776e65;");
    keyBindingsLabel->setWordWrap(true);
    keyBindingsLabel->setContentsMargins(20, 0, 20, 0);
    mainLayout->addWidget(keyBindingsLabel);

    // 添加间距
    spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(30);
    mainLayout->addWidget(spacer);

    backButton = new QPushButton("返回", centralWidget);
    backButton->setStyleSheet("font-size: 20px; padding: 10px; background-color: #8f7a66; color: white; border-radius: 5px;");
    backButton->setFixedSize(150, 50);
    mainLayout->addWidget(backButton, 0, Qt::AlignCenter);

    connect(backButton, &QPushButton::clicked, this, &KeyBindingsWindow::onBackClicked);
}

KeyBindingsWindow::~KeyBindingsWindow()
{
}

void KeyBindingsWindow::onBackClicked()
{
    this->close();
}
