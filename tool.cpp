#include "tool.h"

Tool::Tool(QString name, QString description)
{
    _name = name;
    _description = description;
}

// RectTool --------------------------------------------- //
RectTool::RectTool() : Tool("Rect tool", "")
{

}

void RectTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    begin = event->scenePos();
    QSizeF size = QSizeF(1, 1);
    QRectF rect = QRectF(begin, size);
    _rect_item = canvas->addRect(rect);
}

void RectTool::onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    _rect_item = nullptr;
}

void RectTool::onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    if(_rect_item)
    {
        QRectF rect = _rect_item->rect();
        QPointF delta = event->scenePos() - begin;
        rect.setSize(QSizeF(delta.x(), delta.y()));

        _rect_item->setRect(rect);
        canvas->update();
    }
}

// RectTool --------------------------------------------- //
EllipseTool::EllipseTool() : Tool("Ellipse tool", "")
{

}

void EllipseTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    begin = event->scenePos();
    QSizeF size = QSizeF(1, 1);
    QRectF rect = QRectF(begin, size);
    _rect_item = canvas->addEllipse(rect);
}

void EllipseTool::onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    _rect_item = nullptr;
}

void EllipseTool::onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    if(_rect_item)
    {
        QRectF rect = _rect_item->rect();
        QPointF delta = event->scenePos() - begin;
        rect.setSize(QSizeF(delta.x(), delta.y()));

        _rect_item->setRect(rect);
        canvas->update();
    }
}

// PolygonTool
PolygonTool::PolygonTool() : Tool("Polygon", "")
{

}

void PolygonTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    QPointF pos = event->scenePos();
    if(_polygon_item)
    {
        _path.lineTo(pos + QPointF(1, 1));
        _polygon_item->setPath(_path);
    }
    else
    {
        _path = QPainterPath(pos);
        _path.lineTo(pos + QPointF(1, 1));
        _polygon_item = canvas->addPath(_path);
    }
}

void PolygonTool::onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    if(_polygon_item)
    {
        QPointF pos = event->scenePos();
        int index = _path.elementCount()-1;
        auto elem = _path.elementAt(index);

        if(elem.isLineTo())
        {
            _path.setElementPositionAt(index, pos.x(), pos.y());
        }
        _polygon_item->setPath(_path);
    }
}

void PolygonTool::onKeyRelease(QGraphicsScene* canvas, QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Enter || keyEvent->key() == Qt::Key_Return)
    {
        int index = _path.elementCount()-2;
        auto elem = _path.elementAt(index);

        _path.setElementPositionAt(index+1, elem.x, elem.y);
        _polygon_item->setPath(_path);
        _polygon_item = nullptr;
    }
}