#pragma once

#include <QMainWindow>
#include <QMouseEvent>
#include <QStandardItemModel>
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
    void updateClassTableView(const QString& dept = "");
    void on_QuitButton_clicked();
    void on_MinButton_clicked();
    void on_testbutton_clicked();
    void on_testbutton_2_clicked();
    void on_comboBox_activated(const QString &arg1 = "");

    void on_testbutton_3_clicked();

    void on_aboutButton_clicked();

private:
    Ui::MainWindow *ui;
    QStandardItemModel showClassTableModel;
    void update_test();
    QPoint mousePoint;
    bool mouse_press;
};
