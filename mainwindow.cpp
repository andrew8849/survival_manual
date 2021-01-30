#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Swof's Suvival Munual");
    this->setWindowFlags(Qt::CustomizeWindowHint);


    MainWindow::LOAD_ITEM_IMG();
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    setCursor(Qt::ClosedHandCursor);
    x_coordinate = event->x();
    y_coordinate = event->y();

}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {

    QCursor curso = cursor();

    mainwindow_left_pos = QPoint(event->globalX()-x_coordinate, event->globalY());
    mainwindow_right_pos = QPoint(ui->centralwidget->size().width(), 0) + mainwindow_left_pos;
    mainwindow_top_pos = QPoint(event->globalX(), event->globalY()-y_coordinate);
    mainwindow_bottom_pos = QPoint(event->globalX(), event->globalY() + ui->centralwidget->size().height()-y_coordinate);



    rDesktop = QGuiApplication::screenAt(mainwindow_right_pos);
    lDesktop = QGuiApplication::screenAt(mainwindow_left_pos);
    tDesktop = QGuiApplication::screenAt(mainwindow_top_pos);
    bDesktop = QGuiApplication::screenAt(mainwindow_bottom_pos);



    if(curso == Qt::ClosedHandCursor){
        int x = event->globalX()-x_coordinate;
        int y = event->globalY()-y_coordinate;

        if(lDesktop != nullptr && rDesktop != nullptr){
            if(lDesktop->availableGeometry().right()-20 < mainwindow_left_pos.x() || mainwindow_left_pos.x() < lDesktop->availableGeometry().left()+20){
                x = rDesktop->availableGeometry().left();
                qDebug() << "left";
            }
            else if(rDesktop->availableGeometry().right()-20 < mainwindow_right_pos.x() || mainwindow_right_pos.x() < rDesktop->availableGeometry().left()+20){
                x = lDesktop->availableGeometry().right()-ui->centralwidget->size().width();
                qDebug() << "right";
            }
        }
        if(tDesktop != nullptr && bDesktop != nullptr){
            if(tDesktop->availableGeometry().top()+20 > mainwindow_top_pos.y() || mainwindow_top_pos.y() > tDesktop->availableGeometry().bottom()-20){
                y = bDesktop->availableGeometry().top();
                qDebug() << "top";
            }
            else if(bDesktop->availableGeometry().bottom()-20 < mainwindow_bottom_pos.y() || mainwindow_bottom_pos.y() < bDesktop->availableGeometry().top()+20){
                y = tDesktop->availableGeometry().bottom()-ui->centralwidget->size().height();
                qDebug() << "bottom";
            }
        }
        move(x,y);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    setCursor(Qt::ArrowCursor);

}

MainWindow::~MainWindow()
{
    qDebug()<<"END";
    delete ui;
}

void MainWindow::LOAD_ITEM_IMG(){

    QListWidgetItem *tmp;
    QString item_name;

    for(int i = 0; i< TOOL_AMOUNT; i++){
        item_name = game_item.Item[i].Consol + ".png";
        tmp = new QListWidgetItem(QIcon(":/ITEM/" + item_name),game_item.Item[i].NAME,ui->list_item);
        tmp->setData(Qt::UserRole,i);
        ui->list_item->addItem(tmp);
    }

}

void MainWindow::on_list_item_itemClicked(QListWidgetItem *item)
{
    int height = 1;
    ui->label_name->setText(item->text());
    int h = ui->label_img->height();
    ui->label_img->setPixmap(item->icon().pixmap(QSize(h,h)).scaled(h,h,Qt::KeepAspectRatio));

    ui->list_explanation->clear();
    ui->list_material->clear();

    QListWidgetItem *tmp = new QListWidgetItem("콘솔명 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Consol);
    ui->list_explanation->addItem(tmp);
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Damage != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("데미지 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Damage);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Armor != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("방어력 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Armor);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Durability != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("내구도 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Durability);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Kinds != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("분류 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Kinds);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].hunger != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("배고픔 : " + game_item.Item[item->data(Qt::UserRole).toInt()].hunger);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Sanity != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("정신력 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Sanity);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Health != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("체력 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Health);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].Rot != NULL){
        QListWidgetItem *tmp = new QListWidgetItem("부패일 : " + game_item.Item[item->data(Qt::UserRole).toInt()].Rot);
        ui->list_explanation->addItem(tmp);
        height++;
    }
    if(game_item.Item[item->data(Qt::UserRole).toInt()].How != NULL){
        QStringList list = game_item.Item[item->data(Qt::UserRole).toInt()].How.split(",");
        for(int i =0; i<list.count();i++){
            QString item_name = list[i].split("x")[0];
            for(int j=0;j<TOOL_AMOUNT;j++){
                if(game_item.Item[j].NAME==item_name){
                    new QListWidgetItem(QIcon(":/ITEM/" + game_item.Item[j].Consol + ".png"),game_item.Item[j].NAME+" x"+list[i].split("x")[1],ui->list_material);
                }
            }
        }
    }
    else{
        QListWidgetItem *tmp = new QListWidgetItem("디스 이즈 a 파밍템");
        ui->list_material->addItem(tmp);
    }
    ui->text_etc->setText(game_item.Item[item->data(Qt::UserRole).toInt()].Etc);
    ui->verticalLayout_2->setStretch(2,height);


}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{
    for(int row=0;row<ui->list_item->count();row++ ){
        ui->list_item->item(row)->setHidden(true);
    }
    QList<QListWidgetItem *> tmp;
    tmp = ui->list_item->findItems(arg1,Qt::MatchContains);
    for(int amount=0;amount<tmp.count();amount++){
        tmp[amount]->setHidden(false);
    }
    Checked_button();
}

void MainWindow::on_list_explanation_itemDoubleClicked(QListWidgetItem *item)
{
    QString str = item->text();
    QList<QString> list = str.split(": ");
    if(list[0] == "콘솔명 "){

        QApplication::clipboard()->setText("c_give("""+list[1]+""",10)");
    }

}

void MainWindow::Checked_button()
{
    ui->pushButton_1->setChecked(false);
    ui->pushButton_2->setChecked(false);
    ui->pushButton_3->setChecked(false);
    ui->pushButton_4->setChecked(false);
    ui->pushButton_5->setChecked(false);
    ui->pushButton_6->setChecked(false);
    ui->pushButton_7->setChecked(false);
    ui->pushButton_8->setChecked(false);
    ui->pushButton_9->setChecked(false);
    ui->pushButton_10->setChecked(false);
    ui->pushButton_11->setChecked(false);
    ui->pushButton_12->setChecked(false);
    ui->pushButton_13->setChecked(false);
    ui->pushButton_14->setChecked(false);
}

void MainWindow::on_pushButton_1_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_1->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="도구"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_2_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_2->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="조명"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }

}

void MainWindow::on_pushButton_3_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_3->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="생존"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}
void MainWindow::on_pushButton_4_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_4->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="음식"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}


void MainWindow::on_pushButton_5_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_5->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="과학"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_6_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_6->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="전투"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_7_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_7->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="구조물"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}

void MainWindow::on_pushButton_8_clicked(bool checked)
{
    if(checked == true){
        Checked_button();
        ui->pushButton_8->setChecked(true);
    }
    else{
        QList<QListWidgetItem *> tmp = ui->list_item->findItems("",Qt::MatchContains);
        for(int amount=0;amount<tmp.count();amount++){
            tmp[amount]->setHidden(false);
        }
        return;
    }
    for(int row=0;row<TOOL_AMOUNT;row++ ){
        QString item_name = ui->list_item->item(row)->text();
        ui->list_item->item(row)->setHidden(true);
        for(int i=0;i<TOOL_AMOUNT;i++){
            if(game_item.Item[i].NAME==item_name){
                if(game_item.Item[i].Tabs=="가공"){
                    ui->list_item->item(row)->setHidden(false);
                }
            }
        }
    }
}



void MainWindow::on_button_x_clicked()
{

    qDebug() << this->rect().topLeft();
   QWidget::close();
}



void MainWindow::on_button_minimize_clicked()
{
    QWidget::showMinimized();

}

void MainWindow::on_button_maximize_clicked(bool checked)
{
    if(checked == true){
        QWidget::showMaximized();
    }
    else{
        QWidget::showNormal();
    }
}
