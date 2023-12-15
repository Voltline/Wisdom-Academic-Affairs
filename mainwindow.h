#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QtWinExtras/QtWin>
#include <QtConcurrent/QtConcurrent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void on_pushButton_clicked();
    void on_QuitButton_clicked();
    void on_MinButton_clicked();

private:
    Ui::MainWindow *ui;
    void update_test();
    QPoint mousePoint;
    bool mouse_press;
};
