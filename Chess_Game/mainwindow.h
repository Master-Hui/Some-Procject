#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


 const int MARGIN = 10,COL=25,ROW=33,BLOCK_SIZE=22;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    int refresh_ms;

public:
    virtual void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *ev );
    void Chess_area_init();//棋盘区域初始化。
    void Chess_Lay_init(int a);//棋子初始摆放。
    virtual void timerEvent(QTimerEvent *event);//页面刷新。

private:
    int paint_timer=100;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
