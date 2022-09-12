#include "shape.h"

template<class T>
Shape<T>::Shape(Type type)
{
    _type = type;
}

template<class T>
void Shape<T>::setPosition(QPointF pos)
{
    _item->setPos(pos);
}

template<class T>
void Shape<T>::setScale(QSizeF scale)
{
    _item->setScale(scale);
}

template<class T>
void Shape<T>::setRotation(qreal rotation)
{
    _item->setRotation(rotation);
}

template<class T>
T* Shape<T>::getItem()
{
    return _item;
}

// Rect shape
RectShape::RectShape(QPointF pos, QSizeF size) : Shape(Type::Rect)
{
    _item = new QGraphicsRectItem(QRectF(pos, size));
}

void RectShape::setRect(QRectF rect)
{
    _item->setRect(rect);
}
