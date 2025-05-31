#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>//QMainWindow 是 Qt 中用于创建主窗口的基类，WelcomeWindow 类将继承自它。
#include <QString>//#include <QString>：包含 QString 类的头文件，QString 是 Qt 中用于处理字符串的类。
#include <QVBoxLayout>//QVBoxLayout 是 Qt 中的垂直布局管理器，用于将子部件垂直排列。
#include <QLabel>//QLabel 是 Qt 中用于显示文本或图像的标签类。
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
