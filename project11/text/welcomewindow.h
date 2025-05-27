#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
class WelcomeWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WelcomeWindow(QWidget *parent = nullptr);
    ~WelcomeWindow();

private slots:
    void onStartGameClicked();
    void onInstructionsClicked();
    void onKeyBindingsClicked();
    void onExitClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;

    // 菜单按钮
    QPushButton *startButton;
    QPushButton *instructionsButton;
    QPushButton *keyBindingsButton;
    QPushButton *exitButton;
};

#endif // WELCOMEWINDOW_H
