#include "shape.h"

Shape::Shape(Type type)
{
    _type = type;
}

void Shape::setPosition(QPointF pos)
{
    _item->setPos(pos);
}

void Shape::setRotation(qreal rotation)
{
    _item->setRotation(rotation);
}

QGraphicsItem* Shape::getItem()
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
    dynamic_cast<QGraphicsRectItem*>(_item)->setRect(rect);
}
