#ifndef POLYGON_H
#define POLYGON_H
#include <QPoint>
#include <vector>
#include "math.h"
using namespace std;

class Polygon
{
private:
    vector<QPoint> points;  //储存点集
    float**        matrix;  //复合矩阵

public:
    Polygon();
    Polygon(initializer_list<QPoint> points);
    ~Polygon();

    void           addPoint(QPoint point);            //添加点
    void           addPoints(vector<QPoint> points);  //添加点
    QPoint         getCenterPoint();                  //计算中心点(经过变换)
    int            getSize();                         //获取点数
    vector<QPoint> getTransformPoints();              //获取变换后的点集

    //变换方法
    void move(int x, int y);                      //平移
    void rotate(QPoint center, float angle);      //绕点旋转
    void scale(QPoint center, float x, float y);  //缩放

    //矩阵相关
    float** getNewMatrix();                  //创建新的3*3单位矩阵
    void    freeMatrix(float** matrix);      //释放矩阵内存
    void    multiplyMatrix(float** matrix);  //变换矩阵乘以复合矩阵
    void    resetMatrix();
};

#endif  // POLYGON_H
