#ifndef WELCOMEWINDOW_H
#define WELCOMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFileDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QApplication>

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
    void onLoginClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QPushButton *startButton;
    QPushButton *instructionsButton;
    QPushButton *keyBindingsButton;
    QPushButton *exitButton;
    QWidget *loginWidget;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QPushButton *loginButton;
};

#endif // WELCOMEWINDOW_H
