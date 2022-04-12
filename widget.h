#ifndef WIDGET_H
#define WIDGET_H

#include <QMouseEvent>
#include <QWidget>
#include "polygon.h"
#include "polygonpainter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

protected:
    void mousePressEvent(QMouseEvent* e);  //鼠标点击事件,用于获取点

private:
    Ui::Widget*     ui;
    Polygon*        currentPolygon = nullptr;  //当前多边形
    PolygonPainter* painter;                   //当前多边形绘制器
    bool            isFinish   = false;        // 是否完成多边形绘制？
    bool            isPainting = false;        //是否正在绘制多边形
    void            changetransformFrame();    //由isFinish设置变换模块能否使用
private slots:
    //交互按钮逻辑
    void on_finshButton_clicked();                      //完成 按钮
    void on_resetButton_clicked();                      //重置 按钮
    void on_drawButton_clicked();                       //绘制 按钮
    void on_moveButton_clicked();                       //移动按钮
    void on_checkBox_scale_mid_stateChanged(int arg1);  //缩放 中心 可选按钮
    void on_checkBox_spin_mid_stateChanged(int arg1);   //旋转 中心 可选按钮
    void on_scaleButton_clicked();                      //缩放 按钮
    void on_rotateButton_clicked();                     //旋转 按钮
};
#endif  // WIDGET_H
