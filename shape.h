#ifndef SHAPE_H
#define SHAPE_H

#include <QtCore>
#include <QtWidgets>

class Shape
{
public:
    enum class Type
    {
        Rect,
        Ellipse,
        Polygon
    };

protected:
    QGraphicsItem* _item;
    Type _type;

public:
    Shape(Type type);

    void setPosition(QPointF pos);
    void setRotation(qreal rotation);

    QGraphicsItem* getItem();
};

// Rect shape
class RectShape : public Shape
{
public:
    RectShape(QPointF pos = QPointF(0, 0), QSizeF size = QSizeF(100, 100));

    void setRect(QRectF rect);
};

#endif // SHAPE_H
