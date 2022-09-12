#ifndef SHAPE_H
#define SHAPE_H

#include <QtCore>
#include <QtWidgets>



template<class T>
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
    T* _item;
    Type _type;

public:
    Shape(Type type);

    void setPosition(QPointF pos);
    void setScale(QSizeF size);
    void setRotation(qreal rotation);

    T* getItem();
};

// Rect shape
class RectShape : public Shape<QGraphicsRectItem>
{
public:
    RectShape(QPointF pos = QPointF(0, 0), QSizeF size = QSizeF(100, 100));

    void setRect(QRectF rect);
};

#endif // SHAPE_H
