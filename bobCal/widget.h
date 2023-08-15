#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void updateButtonStatus(); // 버튼 상태 업데이트 함수
    void changeMoney(int diff); // 금액 변경 함수

private slots:
    void on_pb_10_clicked(); // 10원 버튼 클릭 시 호출되는 함수

    void on_pb_50_clicked(); // 50원 버튼 클릭 시 호출되는 함수

    void on_pb_100_clicked(); // 100원 버튼 클릭 시 호출되는 함수

    void on_pb_500_clicked(); // 500원 버튼 클릭 시 호출되는 함수

    void on_pbCoffee_clicked(); // 커피 버튼 클릭 시 호출되는 함수

    void on_pbTea_clicked(); // 차 버튼 클릭 시 호출되는 함수

    void on_pbMilk_clicked(); // 우유 버튼 클릭 시 호출되는 함수

    void on_pbReset_clicked(); // 잔돈 반환 버튼 클릭 시 호출되는 함수

private:
    Ui::Widget *ui;
    int money {0}; // 사용자의 금액 변수
};
#endif // WIDGET_H
