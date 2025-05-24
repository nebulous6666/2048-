#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QKeyEvent>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRandomGenerator>
#include<QFileDialog>

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateTime();
    void onNewGameClicked();
    void onSaveGameClicked();
    void onLoadGameClicked();
    void onBackClicked();

private:
    void initGame();
    void generateNewNumber();
    bool canMove();
    bool moveLeft();
    bool moveRight();
    bool moveUp();
    bool moveDown();
    void mergeLeft();
    void mergeRight();
    void mergeUp();
    void mergeDown();
    void updateBoard();
    void checkGameOver();
    void saveGame(const QString &filename);
    void loadGame(const QString &filename);
    QString getColorForNumber(int number);

    QWidget *centralWidget;
    QGridLayout *gameLayout;
    QLabel *board[4][4];
    QLabel *scoreLabel;
    QLabel *stepsLabel;
    QLabel *timeLabel;
    QPushButton *newGameButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QPushButton *backButton;

    int gameBoard[4][4];
    int score;
    int steps;
    QTimer *timer;
    QTime startTime;
    QString elapsedTime;

signals:
    void backToMainMenu();
};

#endif // GAMEWINDOW_H
