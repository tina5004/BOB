#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox> //message 객체 선언


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // 음료를 뽑을 수 있는 금액이 채워지지 않았다면 음료 버튼 비활성화
    ui->pbCoffee->setEnabled(false);
    ui->pbTea->setEnabled(false);
    ui->pbMilk->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::updateButtonStatus()
{
    ui->pbCoffee->setEnabled(money >= 100);
    ui->pbTea->setEnabled(money >= 150);
    ui->pbMilk->setEnabled(money >= 200);
}

void Widget::changeMoney(int diff)
{
    money += diff;
    ui->lcdNumber->display(money);
    updateButtonStatus();
}

void Widget::on_pb_10_clicked()
{
    changeMoney(10);
}


void Widget::on_pb_50_clicked()
{
    changeMoney(50);
}


void Widget::on_pb_100_clicked()
{
    changeMoney(100);
}


void Widget::on_pb_500_clicked()
{
    changeMoney(500);
}


void Widget::on_pbCoffee_clicked()
{
    changeMoney(-100);
}


void Widget::on_pbTea_clicked()
{
    changeMoney(-150);
}


void Widget::on_pbMilk_clicked()
{
    changeMoney(-200);
}


void Widget::on_pbReset_clicked()
{
    QMessageBox mb;
    // 잔돈 계산 및 출력
    mb.information(this, "잔돈 반환", QString("[잔돈]\n500원 : %1개,\n100원 : %2개,\n50원 : %3개,\n10원 : %4개")
                   .arg(money / 500).arg((money % 500) / 100).arg(((money % 500) % 100) / 50).arg(((money % 500) % 100) % 50));
    // 잔돈 초기화 및 버튼 상태 업데이트
    money = 0;
    ui->lcdNumber->display(money);
    updateButtonStatus();
}

