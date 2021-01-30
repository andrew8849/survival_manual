#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QPixmap>
#include <QIcon>
#include <QProxyStyle>
#include <QStyleOptionTab>
#include <QList>
#include <QClipboard>
#include <windows.h>
#include <QMouseEvent>
#include <QScreen>
#include <QApplication>
#include <QGuiApplication>
#include <QSizeGrip>

#include "item.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_list_item_itemClicked(QListWidgetItem *item);

    void on_lineEdit_textEdited(const QString &arg1);

    void on_pushButton_1_clicked(bool checked);

    void on_pushButton_2_clicked(bool checked);

    void on_pushButton_3_clicked(bool checked);

    void on_pushButton_4_clicked(bool checked);

    void on_list_explanation_itemDoubleClicked(QListWidgetItem *item);

    void on_pushButton_5_clicked(bool checked);

    void on_pushButton_6_clicked(bool checked);

    void on_pushButton_7_clicked(bool checked);

    void on_pushButton_8_clicked(bool checked);

    void on_button_x_clicked();

    void on_button_minimize_clicked();

    void on_button_maximize_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    void LOAD_ITEM_IMG();
    ITEM game_item = ITEM();
    void Checked_button();

    int x_coordinate;
    int y_coordinate;
    QPoint mainwindow_left_pos;
    QPoint mainwindow_right_pos;
    QPoint mainwindow_top_pos;
    QPoint mainwindow_bottom_pos;

    QScreen *lDesktop;
    QScreen *rDesktop;
    QScreen *tDesktop;
    QScreen *bDesktop;

    bool ispressed;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);


};


#endif // MAINWINDOW_H
