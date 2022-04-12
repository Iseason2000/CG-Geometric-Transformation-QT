#include "polygon.h"
#include <QDebug>
#include <iostream>
Polygon::Polygon()
{
    this->matrix = getNewMatrix();
}

Polygon::Polygon(initializer_list<QPoint> points)
//可变参数传值 使用方法：Polygon({point1,point2,point3})
{
    for (auto point = points.begin(); point != points.end(); point++) {
        this->points.push_back(*point);
    }
    this->matrix = getNewMatrix();
}

Polygon::~Polygon()
{
    freeMatrix(matrix);
    points.clear();
    points.shrink_to_fit();
}

void Polygon::addPoint(QPoint point)
{
    this->points.push_back(point);
}

void Polygon::addPoints(vector<QPoint> points)
{
    for (auto point = points.begin(); point != points.end(); point++) {
        this->points.push_back(*point);
    }
}

QPoint Polygon::getCenterPoint()
{
    vector<QPoint> points = getTransformPoints();  //获取计算变换之后的点
    int            xSum = 0, ySum = 0;
    int            size = points.size();  //在使用前应该检测是否为0
    for (auto point = points.begin(); point != points.end(); point++) {
        xSum += point->x();
        ySum += point->y();
    }
    return QPoint(int(xSum / size), int(ySum / size));
}

int Polygon::getSize()
{
    return this->points.size();
}

vector<QPoint> Polygon::getTransformPoints()
{
    vector<QPoint> newPoints = this->points;  //拷贝，不会改变原点
    for (auto point = newPoints.begin(); point != newPoints.end(); point++) {
        int x = point->x();
        int y = point->y();
        point->setX(int(matrix[0][0] * x + matrix[0][1] * y + matrix[0][2]));
        point->setY(int(matrix[1][0] * x + matrix[1][1] * y + matrix[1][2]));
    }
    return newPoints;
}

void Polygon::move(int x, int y)
{
    float** moveMatrix = getNewMatrix();
    moveMatrix[0][2]   = x;
    moveMatrix[1][2]   = y;
    multiplyMatrix(moveMatrix);
    freeMatrix(moveMatrix);
}

void Polygon::rotate(QPoint center, float angle)
{
    float** rotateMatrix = getNewMatrix();
    rotateMatrix[0][0]   = cos(angle);
    rotateMatrix[0][1]   = -sin(angle);
    rotateMatrix[0][2]   = center.x() * (1 - cos(angle)) + center.y() * sin(angle);
    rotateMatrix[1][0]   = sin(angle);
    rotateMatrix[1][1]   = cos(angle);
    rotateMatrix[1][2]   = center.y() * (1 - cos(angle)) - center.x() * sin(angle);
    multiplyMatrix(rotateMatrix);
    freeMatrix(rotateMatrix);
}

void Polygon::scale(QPoint center, float x, float y)
{
    float** scaleMatrix = getNewMatrix();
    scaleMatrix[0][0]   = x;
    scaleMatrix[0][2]   = (1 - x) * center.x();
    scaleMatrix[1][1]   = y;
    scaleMatrix[1][2]   = (1 - y) * center.y();
    multiplyMatrix(scaleMatrix);
    freeMatrix(scaleMatrix);
}

void Polygon::multiplyMatrix(float** matrix)
{
    float** sourceMatrix = this->matrix;
    float** newMatrix    = new float*[3];
    for (int row = 0; row < 3; row++) {  //创建空矩阵用于存储结果
        newMatrix[row]  = new float[3];
        *newMatrix[row] = 0.0;
        for (int col = 0; col < 3; col++) {
            newMatrix[row][col] = 0.0;
        }
    }
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            newMatrix[row][col] += sourceMatrix[0][col] * matrix[row][0];
            newMatrix[row][col] += sourceMatrix[1][col] * matrix[row][1];
            newMatrix[row][col] += sourceMatrix[2][col] * matrix[row][2];
        }
    }
    freeMatrix(this->matrix);  //释放旧结果
    this->matrix = newMatrix;
}

void Polygon::resetMatrix()
{
    if (this->matrix)  //如果存在
        freeMatrix(this->matrix);
    this->matrix = getNewMatrix();
}

float** Polygon::getNewMatrix()
{
    float** matrix = new float*[3];
    for (int row = 0; row < 3; row++) {
        matrix[row] = new float[3];
        for (int col = 0; col < 3; col++)
            matrix[row][col] = float(row == col);
    }
    //值等于float  matrix[3][3] = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    return matrix;
}

void Polygon::freeMatrix(float** matrix)
{
    delete[] matrix[2];
    delete[] matrix[1];
    delete[] matrix[0];
    delete[] matrix;
}
