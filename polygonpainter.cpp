#include "polygonpainter.h"

PolygonPainter::PolygonPainter(QLabel* lable)
{
    QImage l(MAXWIDTH, MAXHEIGHT, QImage::Format_ARGB32);
    k = l;
    drawLine(250, 0, 250, 499, defautLineColor);
    drawLine(0, 250, 499, 250, defautLineColor);
    temp        = k;  //储存带坐标系的模板
    this->lable = lable;
    update();
}

void PolygonPainter::addPoint(QPoint point)
{
    int x = point.x();
    int y = point.y();
    if (n == 0)
        initFistPoint(x, y);
    else
        next(x, y);
}

void PolygonPainter::drawPolygon(vector<QPoint> points)
{
    int count = 1;
    int size  = points.size();
    for (auto point = points.begin(); point != points.end(); point++) {
        if (count == 1) {
            initFistPoint(point->x(), point->y());
        }
        next(point->x(), point->y());
        if (count == size) {
            final();
        }
        count++;
    }
}

int PolygonPainter::getPointsCount()
{
    return this->n;
}

vector<QPoint> PolygonPainter::getPoints()
{
    return points;
}

void PolygonPainter::initFistPoint(int x, int y)
{
    lastx = x;
    lasty = y;
    n     = 1;
    xp    = x;
    yp    = y;
    points.push_back(QPoint(x, y));
}

void PolygonPainter::next(int x, int y)
{
    int x0 = lastx, y0 = lasty;
    xa[n - 1] = x0;
    ya[n - 1] = y0;
    lastx     = x;
    lasty     = y;
    drawLine(x0, y0, x, y, lineColor);
    update();
    n++;
    points.push_back(QPoint(x, y));
}

void PolygonPainter::drawLineDDA(float m, float x, float y, int x0, int y0, int x1, int y1, QRgb c)
{
    if (x0 <= x1 && y0 <= y1) {
        if (m <= 1 && m >= -1) {
            while (x < x1) {
                y = y + m;
                x = x + 1;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        } else {
            while (y < y1) {
                y = y + 1;
                x = x + 1 / m;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        }
    } else if (x1 <= x0 && y1 <= y0) {
        if (m <= 1 && m >= -1) {
            while (x > x1) {
                y = y - m;
                x = x - 1;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        } else {
            while (y > y1) {
                y = y - 1;
                x = x - 1 / m;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        }
    } else if (x0 <= x1 && y1 <= y0) {
        if (m <= 1 && m >= -1) {
            while (x < x1) {
                y = y + m;
                x = x + 1;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        } else {
            while (y > y1) {
                y = y - 1;
                x = x - (1 / m);
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        }
    } else if (x1 <= x0 && y0 <= y1) {
        if (m <= 1 && m >= -1) {
            while (x > x1) {
                y = y - m;
                x = x - 1;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        } else {
            while (y < y1) {
                y = y + 1;
                x = x + 1 / m;
                if (x > 0 && x < MAXWIDTH && y > 0 && y < MAXHEIGHT)
                    k.setPixel(x, y, c);
            }
        }
    }
}

void PolygonPainter::drawLine(int x1, int y1, int x2, int y2, QRgb c)
{
    float m, fx, fy;
    m  = y2 - y1;
    m  = m / (x2 - x1);
    fx = x1;
    fy = y1;
    drawLineDDA(m, fx, fy, x1, y1, x2, y2, c);
}

void PolygonPainter::final()
{
    drawLine(lastx, lasty, xa[0], ya[0], lineColor);
    update();
}

void PolygonPainter::reset()
{
    n     = 0;
    t     = 0;
    xp    = 0;
    yp    = 0;
    lastx = 0;
    lasty = 0;
    memset(xa, 0, sizeof(xa));
    memset(ya, 0, sizeof(ya));
    points.clear();
    points.shrink_to_fit();
    k = temp;
    update();
}

void PolygonPainter::update()
{
    lable->setPixmap(QPixmap::fromImage(k));
}
