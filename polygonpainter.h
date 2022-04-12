#ifndef POLYGONPAINTER_H
#define POLYGONPAINTER_H
#include <QImage>
#include <QLabel>
#include <QMainWindow>
#include <QRgb>
#include <vector>
#define MAXHEIGHT 500  //画布高度
#define MAXWIDTH 500   //画布宽度
using namespace std;
class PolygonPainter
{
public:
    PolygonPainter(QLabel* lable);
    void           addPoint(QPoint point);              //添加点
    void           drawPolygon(vector<QPoint> points);  //绘制多边形
    int            getPointsCount();                    //获取点数n
    vector<QPoint> getPoints();
    //划线加点方法
    void initFistPoint(int x, int y);                                                     //初始化第一个点
    void next(int x, int y);                                                              //添加下一个点
    void drawLineDDA(float m, float x, float y, int x0, int y0, int x1, int y1, QRgb c);  // dda划线
    void drawLine(int x1, int y1, int x2, int y2, QRgb c);                                //画出2点之间的线
    void final();                                                                         //结束画点
    void reset();                                                                         //重置
    void update();                                                                        //更新画板

private:
    vector<QPoint> points;
    QLabel*        lable;
    int            n  = 0;
    int            t  = 0;
    int            xp = 0;
    int            yp = 0;
    int            xa[MAXWIDTH];
    int            ya[MAXHEIGHT];
    int            lastx = 0, lasty = 0;
    QImage         k;                                      //画板
    QImage         temp;                                   //储存画板模板
    QRgb           lineColor       = qRgb(255, 94, 144);   //多边形线条颜色
    QRgb           defautLineColor = qRgb(120, 120, 120);  //坐标系颜色
};

#endif  // POLYGONPAINTER_H
