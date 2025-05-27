#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent) : QMainWindow(parent), timer(new QTimer(this))
{
    setWindowTitle("2048游戏");
    setMinimumSize(600, 700);

    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    //将刚刚创建的QWidget对象设置为GameWindow的中央部件。

    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    //mainLayout 被定义成局部变量，它的作用域仅限于构造函数内部。在构造函数执行完毕之后，这个布局对象的地址就不再被其他成员函数引用

    // 游戏信息面板
    QWidget *infoWidget = new QWidget(centralWidget);
    //infoWidget被用作一个容器，用于容纳游戏信息显示部件和操作按钮。
    QGridLayout *infoLayout = new QGridLayout(infoWidget);
    //QGridLayout是一种布局管理器，它能够将部件排列成网格状。在网格布局中，每个部件都可以被放置在指定的行和列位置，方便进行复杂的界面布局。

    QLabel *titleLabel = new QLabel("2048", infoWidget);
    titleLabel->setStyleSheet("font-size: 48px; font-weight: bold; color: #776e65;");
    infoLayout->addWidget(titleLabel, 0, 0, 2, 1);
    // font-size: 48px：设置标签文本的字体大小为 48 像素，使标题更加醒目。
    // font-weight: bold：设置标签文本的字体为粗体，增强标题的视觉效果。
    // color: #776e65：设置标签文本的颜色为十六进制颜色码

    scoreLabel = new QLabel("分数: 0", infoWidget);
    scoreLabel->setStyleSheet("font-size: 24px; color: #776e65;");
    infoLayout->addWidget(scoreLabel, 0, 1);

    stepsLabel = new QLabel("步数: 0", infoWidget);
    stepsLabel->setStyleSheet("font-size: 24px; color: #776e65;");
    infoLayout->addWidget(stepsLabel, 0, 2);

    timeLabel = new QLabel("时间: 00:00", infoWidget);
    timeLabel->setStyleSheet("font-size: 24px; color: #776e65;");
    infoLayout->addWidget(timeLabel, 0, 3);

    newGameButton = new QPushButton("新游戏", infoWidget);
    newGameButton->setStyleSheet("font-size: 18px; padding: 5px; background-color: #8f7a66; color: white; border-radius: 5px;");
    infoLayout->addWidget(newGameButton, 1, 1);

    saveButton = new QPushButton("保存游戏", infoWidget);
    saveButton->setStyleSheet("font-size: 18px; padding: 5px; background-color: #8f7a66; color: white; border-radius: 5px;");
    infoLayout->addWidget(saveButton, 1, 2);

    loadButton = new QPushButton("加载游戏", infoWidget);
    loadButton->setStyleSheet("font-size: 18px; padding: 5px; background-color: #8f7a66; color: white; border-radius: 5px;");
    infoLayout->addWidget(loadButton, 1, 3);

    mainLayout->addWidget(infoWidget);

    // 游戏棋盘
    QWidget *boardWidget = new QWidget(centralWidget);
    boardWidget->setStyleSheet("background-color: #bbada0; border-radius: 10px;");
    gameLayout = new QGridLayout(boardWidget);
    gameLayout->setSpacing(10);// 设置网格布局中各个部件之间的间距为 10 像素，使格子之间有一定的间隔。
    gameLayout->setContentsMargins(10, 10, 10, 10);//设置布局的内边距为 10 像素，即布局内容与布局边界之间的距离。

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            board[i][j] = new QLabel("", boardWidget);
            board[i][j]->setAlignment(Qt::AlignCenter);//设置每个 QLabel 的文本对齐方式为居中对齐，使文本在格子中居中显示。
            board[i][j]->setStyleSheet("background-color: #cdc1b4; border-radius: 5px;");
            board[i][j]->setFixedSize(120, 120);//设置每个 QLabel 的固定大小为 120x120 像素
            gameLayout->addWidget(board[i][j], i, j);//使用 addWidget 方法将每个 QLabel 添加到 gameLayout 中，i 和 j 分别指定了 QLabel 在网格布局中的行和列位置。
        }
    }

    mainLayout->addWidget(boardWidget, 1, Qt::AlignCenter);

    // 返回按钮
    backButton = new QPushButton("返回主菜单", centralWidget);
    backButton->setStyleSheet("font-size: 20px; padding: 10px; background-color: #8f7a66; color: white; border-radius: 5px;");
    mainLayout->addWidget(backButton, 0, Qt::AlignCenter);

    // 初始化游戏
    initGame();

    // 连接信号和槽
    connect(timer, &QTimer::timeout, this, &GameWindow::updateTime);
    connect(newGameButton, &QPushButton::clicked, this, &GameWindow::onNewGameClicked);
    connect(saveButton, &QPushButton::clicked, this, &GameWindow::onSaveGameClicked);
    connect(loadButton, &QPushButton::clicked, this, &GameWindow::onLoadGameClicked);
    connect(backButton, &QPushButton::clicked, this, &GameWindow::onBackClicked);
}

GameWindow::~GameWindow()
{
    delete timer;
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    bool moved = false;
    bool gameOver = false;

    switch (event->key()) {
    case Qt::Key_Left:
        moved = moveLeft();
        break;
    case Qt::Key_Right:
        moved = moveRight();
        break;
    case Qt::Key_Up:
        moved = moveUp();
        break;
    case Qt::Key_Down:
        moved = moveDown();
        break;
    case Qt::Key_W:
        moved = moveUp();
        break;
    case Qt::Key_S:
        moved = moveDown();
        break;
    case Qt::Key_A:
        moved = moveLeft();
        break;
    case Qt::Key_D:
        moved = moveRight();
        break;
    default:
        QMainWindow::keyPressEvent(event);
        return;
    }

    if (moved) {
        steps++;
        stepsLabel->setText("步数: " + QString::number(steps));
        generateNewNumber();
        updateBoard();
        checkGameOver();
    }
}

void GameWindow::updateTime()
{
    QTime currentTime = QTime::currentTime();
    int seconds = startTime.secsTo(currentTime);
    int minutes = seconds / 60;
    seconds = seconds % 60;
    elapsedTime = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
    //.arg(minutes, 2, 10, QChar('0')) 表示将 minutes 作为第一个参数替换 %1，并将其格式化为宽度为 2 的十进制字符串，不足两位时在前面补 0。
    timeLabel->setText("时间: " + elapsedTime);
}

void GameWindow::onNewGameClicked()
{
    initGame();
}

void GameWindow::onSaveGameClicked()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存游戏", "", "2048 Game Files (*.2048)");
    if (!filename.isEmpty()) {
        saveGame(filename);
    }
}

void GameWindow::onLoadGameClicked()
{
    QString filename = QFileDialog::getOpenFileName(this, "加载游戏", "", "2048 Game Files (*.2048)");
    if (!filename.isEmpty()) {
        loadGame(filename);
    }
}

void GameWindow::onBackClicked()
{
    timer->stop();
    emit backToMainMenu();
    this->close();
    parentWidget()->show();
}

void GameWindow::initGame()
{
    // 初始化游戏数据
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            gameBoard[i][j] = 0;
        }
    }

    score = 0;
    steps = 0;
    scoreLabel->setText("分数: " + QString::number(score));
    stepsLabel->setText("步数: " + QString::number(steps));

    // 初始化计时器
    if (!timer) {
        timer = new QTimer(this);
    } else {
        timer->stop();
    }
    startTime = QTime::currentTime();
    timer->start(1000);
    updateTime();

    // 生成两个初始数字
    generateNewNumber();
    generateNewNumber();
    updateBoard();
}

void GameWindow::generateNewNumber()
{
    // 查找所有空白位置
    QVector<QPair<int, int>> emptyPositions;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoard[i][j] == 0) {
                emptyPositions.append(qMakePair(i, j));
            }
        }
    }

    if (!emptyPositions.isEmpty()) {
        // 随机选择一个空白位置
        int randomIndex = QRandomGenerator::global()->bounded(emptyPositions.size());
        int row = emptyPositions[randomIndex].first;
        int col = emptyPositions[randomIndex].second;

        // 90%概率生成2，10%概率生成4
        gameBoard[row][col] = (QRandomGenerator::global()->bounded(10) < 9) ? 2 : 4;
    }
}

bool GameWindow::canMove()
{
    // 检查是否有空白位置
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoard[i][j] == 0) {
                return true;
            }
        }
    }

    // 检查是否有相邻相同的数字
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] == gameBoard[i][j+1]) {
                return true;
            }
        }
    }

    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[i][j] == gameBoard[i+1][j]) {
                return true;
            }
        }
    }

    return false;
}

bool GameWindow::moveLeft()
{
    bool moved = false;

    // 先合并
    mergeLeft();

    // 再移动
    for (int i = 0; i < 4; i++) {
        for (int j = 1; j < 4; j++) {
            if (gameBoard[i][j] != 0) {
                int k = j;
                while (k > 0 && gameBoard[i][k-1] == 0) {
                    gameBoard[i][k-1] = gameBoard[i][k];
                    gameBoard[i][k] = 0;
                    k--;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool GameWindow::moveRight()
{
    bool moved = false;

    // 先合并
    mergeRight();

    // 再移动
    for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
            if (gameBoard[i][j] != 0) {
                int k = j;
                while (k < 3 && gameBoard[i][k+1] == 0) {
                    gameBoard[i][k+1] = gameBoard[i][k];
                    gameBoard[i][k] = 0;
                    k++;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool GameWindow::moveUp()
{
    bool moved = false;

    // 先合并
    mergeUp();

    // 再移动
    for (int j = 0; j < 4; j++) {
        for (int i = 1; i < 4; i++) {
            if (gameBoard[i][j] != 0) {
                int k = i;
                while (k > 0 && gameBoard[k-1][j] == 0) {
                    gameBoard[k-1][j] = gameBoard[k][j];
                    gameBoard[k][j] = 0;
                    k--;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

bool GameWindow::moveDown()
{
    bool moved = false;

    // 先合并
    mergeDown();

    // 再移动
    for (int j = 0; j < 4; j++) {
        for (int i = 2; i >= 0; i--) {
            if (gameBoard[i][j] != 0) {
                int k = i;
                while (k < 3 && gameBoard[k+1][j] == 0) {
                    gameBoard[k+1][j] = gameBoard[k][j];
                    gameBoard[k][j] = 0;
                    k++;
                    moved = true;
                }
            }
        }
    }

    return moved;
}

void GameWindow::mergeLeft()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 3; j++) {
            if (gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard[i][j+1]) {
                gameBoard[i][j] *= 2;
                score += gameBoard[i][j];
                gameBoard[i][j+1] = 0;
                scoreLabel->setText("分数: " + QString::number(score));
            }
        }
    }
}

void GameWindow::mergeRight()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 3; j > 0; j--) {
            if (gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard[i][j-1]) {
                gameBoard[i][j] *= 2;
                score += gameBoard[i][j];
                gameBoard[i][j-1] = 0;
                scoreLabel->setText("分数: " + QString::number(score));
            }
        }
    }
}

void GameWindow::mergeUp()
{
    for (int j = 0; j < 4; j++) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard[i+1][j]) {
                gameBoard[i][j] *= 2;
                score += gameBoard[i][j];
                gameBoard[i+1][j] = 0;
                scoreLabel->setText("分数: " + QString::number(score));
            }
        }
    }
}

void GameWindow::mergeDown()
{
    for (int j = 0; j < 4; j++) {
        for (int i = 3; i > 0; i--) {
            if (gameBoard[i][j] != 0 && gameBoard[i][j] == gameBoard[i-1][j]) {
                gameBoard[i][j] *= 2;
                score += gameBoard[i][j];
                gameBoard[i-1][j] = 0;
                scoreLabel->setText("分数: " + QString::number(score));
            }
        }
    }
}

void GameWindow::updateBoard()
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoard[i][j] == 0) {
                board[i][j]->setText("");
                board[i][j]->setStyleSheet("background-color: #cdc1b4; border-radius: 5px;");
            } else {
                board[i][j]->setText(QString::number(gameBoard[i][j]));
                QString color = getColorForNumber(gameBoard[i][j]);
                board[i][j]->setStyleSheet(QString("background-color: %1; color: %2; font-size: 28px; font-weight: bold; border-radius: 5px;")
                                               .arg(color)
                                               .arg(gameBoard[i][j] <= 4 ? "#776e65" : "#f9f6f2"));
            }
        }
    }
}

void GameWindow::checkGameOver()
{
    // 检查是否获胜
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (gameBoard[i][j] >= 2048) {
                timer->stop();
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "恭喜", "你赢了！再玩一局？",
                                              QMessageBox::Yes | QMessageBox::No);
                if (reply == QMessageBox::Yes) {
                    initGame();
                } else {
                    this->close();
                    parentWidget()->show();
                }
                return;
            }
        }
    }

    // 检查是否游戏结束
    if (!canMove()) {
        timer->stop();
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "游戏结束", QString("你的分数: %1\n再玩一局？").arg(score),
                                      QMessageBox::Yes | QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            initGame();
        } else {
            this->close();
            parentWidget()->show();
        }
    }
}

void GameWindow::saveGame(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        // 保存分数和步数
        out << score << "\n";
        out << steps << "\n";
        out << elapsedTime << "\n";

        // 保存游戏棋盘
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                out << gameBoard[i][j] << " ";
            }
            out << "\n";
        }

        file.close();
        QMessageBox::information(this, "保存成功", "游戏已成功保存！");
    } else {
        QMessageBox::warning(this, "保存失败", "无法保存游戏文件！");
    }
}

void GameWindow::loadGame(const QString &filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);

        // 读取分数和步数
        score = in.readLine().toInt();
        steps = in.readLine().toInt();//in.readLine().toInt() 从文件中读取一行文本，并将其转换为整数，分别赋值给 score 和 steps。
        elapsedTime = in.readLine();

        // 更新显示
        scoreLabel->setText("分数: " + QString::number(score));
        stepsLabel->setText("步数: " + QString::number(steps));
        timeLabel->setText("时间: " + elapsedTime);

        // 解析时间字符串并设置计时器
        QStringList timeParts = elapsedTime.split(":");
        if (timeParts.size() == 2) {
            int minutes = timeParts[0].toInt();
            int seconds = timeParts[1].toInt();
            startTime = QTime::currentTime().addSecs(-(minutes * 60 + seconds));
            if (timer->isActive()) {
                timer->stop();
            }
            timer->start(1000);
        }

        // 读取游戏棋盘
        for (int i = 0; i < 4; i++) {
            QString line = in.readLine();
            QStringList parts = line.split(" ");
            for (int j = 0; j < 4 && j < parts.size(); j++) {
                gameBoard[i][j] = parts[j].toInt();
            }
        }

        file.close();
        updateBoard();
        QMessageBox::information(this, "加载成功", "游戏已成功加载！");
    } else {
        QMessageBox::warning(this, "加载失败", "无法打开游戏文件！");
    }
}

QString GameWindow::getColorForNumber(int number)
{
    switch (number) {
    case 2: return "#eee4da";
    case 4: return "#ede0c8";
    case 8: return "#f2b179";
    case 16: return "#f59563";
    case 32: return "#f67c5f";
    case 64: return "#f65e3b";
    case 128: return "#edcf72";
    case 256: return "#edcc61";
    case 512: return "#edc850";
    case 1024: return "#edc53f";
    case 2048: return "#edc22e";
    default: return "#3c3a32";
    }
}
