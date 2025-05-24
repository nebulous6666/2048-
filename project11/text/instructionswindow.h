#ifndef INSTRUCTIONSWINDOW_H
#define INSTRUCTIONSWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class InstructionsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit InstructionsWindow(QWidget *parent = nullptr);
    ~InstructionsWindow();

private slots:
    void onBackClicked();

private:
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QLabel *titleLabel;
    QLabel *instructionsLabel;
    QPushButton *backButton;
};

#endif // INSTRUCTIONSWINDOW_H
