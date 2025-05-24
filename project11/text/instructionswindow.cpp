#include "instructionswindow.h"

InstructionsWindow::InstructionsWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("2048游戏 - 游戏说明");
    setMinimumSize(600, 400);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    titleLabel = new QLabel("游戏说明", centralWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #776e65;");
    mainLayout->addWidget(titleLabel);

    // 添加间距
    QLabel *spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(20);
    mainLayout->addWidget(spacer);

    instructionsLabel = new QLabel(
        "2048是一款数字益智游戏，目标是通过合并相同数字的方块，创建出数值为2048的方块。\n\n"
        "游戏规则：\n"
        "1. 使用方向键（上、下、左、右）或WASD键移动所有方块。\n"
        "2. 当两个相同数字的方块相撞时，它们会合并成一个它们的和。\n"
        "3. 每次移动后，会在空白位置随机生成一个新的2或4。\n"
        "4. 当无法进行任何移动时，游戏结束。\n\n"
        "游戏提示：\n"
        "1. 尽量保持一个方向的增长，例如将大数放在角落。\n"
        "2. 优先合并较大的数字。\n"
        "3. 注意留出空白位置以保持游戏的灵活性。\n\n"
        "祝你好运！",
        centralWidget
        );
    instructionsLabel->setAlignment(Qt::AlignLeft);
    instructionsLabel->setStyleSheet("font-size: 18px; color: #776e65;");
    instructionsLabel->setWordWrap(true);
    instructionsLabel->setContentsMargins(20, 0, 20, 0);
    mainLayout->addWidget(instructionsLabel);

    // 添加间距
    spacer = new QLabel("", centralWidget);
    spacer->setFixedHeight(30);
    mainLayout->addWidget(spacer);

    backButton = new QPushButton("返回", centralWidget);
    backButton->setStyleSheet("font-size: 20px; padding: 10px; background-color: #8f7a66; color: white; border-radius: 5px;");
    backButton->setFixedSize(150, 50);
    mainLayout->addWidget(backButton, 0, Qt::AlignCenter);

    connect(backButton, &QPushButton::clicked, this, &InstructionsWindow::onBackClicked);
}

InstructionsWindow::~InstructionsWindow()
{
}

void InstructionsWindow::onBackClicked()
{
    this->close();
}
