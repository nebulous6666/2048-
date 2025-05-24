#ifndef KEYBINDINGSWINDOW_H
#define KEYBINDINGSWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class KeyBindingsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit KeyBindingsWindow(QWidget *parent = nullptr);
    ~KeyBindingsWindow();

private slots:
    void onBackClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *keyBindingsLabel;
    QPushButton *backButton;
};

#endif // KEYBINDINGSWINDOW_H
