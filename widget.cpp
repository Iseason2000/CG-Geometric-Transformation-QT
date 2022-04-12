#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle(QString::fromLocal8Bit("多边形变换"));
    //默认显示开始
    this->painter        = new PolygonPainter(ui->label);
    this->currentPolygon = new Polygon({QPoint(200, 200), QPoint(300, 200), QPoint(300, 300), QPoint(200, 300)});
    currentPolygon->move(50, -20);
    currentPolygon->rotate(currentPolygon->getCenterPoint(), 2.0);
    currentPolygon->scale(currentPolygon->getCenterPoint(), 2, 2);
    painter->drawPolygon(currentPolygon->getTransformPoints());
    isFinish = true;
    changetransformFrame();
    //默认显示结束
}

Widget::~Widget()
{
    delete ui;
}

void Widget::mousePressEvent(QMouseEvent* event)
{
    if (!isPainting)  //只有按下按钮才能画
        return;
    int x = event->x() - 75;  //坐标修正到lable
    int y = event->y() - 20;
    if (x < 0 || y < 0)
        return;
    if (x > MAXWIDTH || y > MAXHEIGHT)
        return;
    painter->addPoint(QPoint(x, y));
    if (painter->getPointsCount() >= 3)
        ui->finshButton->setDisabled(false);
    else
        ui->finshButton->setDisabled(true);
}

void Widget::changetransformFrame()
{
    if (!isFinish)
        ui->transformFrame->setDisabled(true);
    else
        ui->transformFrame->setEnabled(true);
}

void Widget::on_finshButton_clicked()
{
    if (!isPainting)
        return;
    painter->final();
    isPainting = false;
    isFinish   = true;
    changetransformFrame();
    this->currentPolygon = new Polygon();
    currentPolygon->addPoints(painter->getPoints());
    ui->drawButton->setDisabled(true);
}

void Widget::on_resetButton_clicked()
{
    this->painter->reset();
    isFinish = false;
    ui->finshButton->setDisabled(true);
    changetransformFrame();
    if (this->currentPolygon) {
        delete this->currentPolygon;
        this->currentPolygon = nullptr;
    }
    ui->drawButton->setDisabled(false);
}

void Widget::on_drawButton_clicked()
{
    isPainting = true;
}

void Widget::on_moveButton_clicked()
{
    int x = ui->spinBox_moveX->text().toInt();
    int y = -ui->spinBox_moveY->text().toInt();
    currentPolygon->move(x, y);
    painter->reset();
    painter->drawPolygon(currentPolygon->getTransformPoints());
}

void Widget::on_scaleButton_clicked()
{
    QPoint center;
    if (ui->checkBox_scale_mid->isChecked()) {
        center = currentPolygon->getCenterPoint();
    } else {
        center.setX(ui->spinBox_scale_centerX->text().toInt() + 250);
        center.setY(ui->spinBox_scale_centerY->text().toInt() + 250);
    }
    float fx = ui->doubleSpinBox_scaleX->text().toFloat();
    float fy = ui->doubleSpinBox_scaleY->text().toFloat();
    currentPolygon->scale(center, fx, fy);
    painter->reset();
    painter->drawPolygon(currentPolygon->getTransformPoints());
}

void Widget::on_rotateButton_clicked()
{
    QPoint center;
    if (ui->checkBox_spin_mid->isChecked()) {
        center = currentPolygon->getCenterPoint();
    } else {
        center.setX(ui->spinBox_rotate_centerX->text().toInt() + 250);
        center.setY(ui->spinBox_rotate_centerY->text().toInt() + 250);
    }
    float angle = ui->doubleSpinBox_rotate->text().toFloat() * 3.1415926;
    currentPolygon->rotate(center, angle);
    painter->reset();
    painter->drawPolygon(currentPolygon->getTransformPoints());
}

void Widget::on_checkBox_scale_mid_stateChanged(int arg1)
{
    if (arg1 == 2) {
        ui->spinBox_scale_centerX->setDisabled(true);
        ui->spinBox_scale_centerY->setDisabled(true);
    } else {
        ui->spinBox_scale_centerX->setDisabled(false);
        ui->spinBox_scale_centerY->setDisabled(false);
    }
}

void Widget::on_checkBox_spin_mid_stateChanged(int arg1)
{
    if (arg1 == 2) {
        ui->spinBox_rotate_centerX->setDisabled(true);
        ui->spinBox_rotate_centerY->setDisabled(true);
    } else {
        ui->spinBox_rotate_centerX->setDisabled(false);
        ui->spinBox_rotate_centerY->setDisabled(false);
    }
}
