#include "tool.h"

Tool::Tool(QString name, QString hot_key)
{
    _name = name;
    _hot_key = hot_key;
}

QString Tool::getName()
{
    return _name;
}

QString Tool::getHotKey()
{
    return _hot_key;
}

SelectTool::SelectTool() : Tool("Select", "S")
{

}

void SelectTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    begin = event->scenePos();
}

void SelectTool::onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    QPointF pos = event->scenePos();
    QRectF rect = QRectF(begin.x(), begin.y(), pos.x() - begin.x()+1, pos.y() - begin.y()+1);
    QPainterPath path;
    path.addRect(rect);
    canvas->setSelectionArea(path);
}

void SelectTool::onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{

}

MoveTool::MoveTool() : Tool("Move", "G")
{

}

void MoveTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    begin = event->scenePos();
    isPressed = true;

    QRectF rect = QRectF(begin.x(), begin.y(), 1, 1);
    QPainterPath path;
    path.addRect(rect);
    canvas->setSelectionArea(path);
};

void MoveTool::onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    isPressed = false;
};

void MoveTool::onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    if(isPressed)
    {
        QPointF pos = event->scenePos();
        QPointF delta = pos - begin;

        auto items = canvas->selectedItems();
        for(auto obj : items)
        {
            obj->moveBy(delta.x(), delta.y());
        }
        begin = pos;
    }
};

// RotateTool --------------------------------------------- //
RotateTool::RotateTool() : Tool("Rotate", "T")
{

}

void RotateTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    isPressed = true;
    QRectF bounding_rect;
    auto items = canvas->selectedItems();
    for(int i=0; i<items.size(); i++)
    {
        bounding_rect |= items[i]->boundingRect();
    }
    begin = bounding_rect.center();
};

void RotateTool::onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    isPressed = false;
};

void RotateTool::onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    QPointF pos = event->scenePos();
    if(isPressed)
    {
        QPointF delta = pos-begin;
        delta /= (delta.x() + delta.y());
        qDebug() << atan2(delta.y(), delta.x()) * 180 / M_PI;
    }
};

// RectTool --------------------------------------------- //
RectTool::RectTool() : Tool("Rect", "R")
{

}

void RectTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    begin = event->scenePos();
    QSizeF size = QSizeF(1, 1);
    QRectF rect = QRectF(begin, size);
    _rect_item = canvas->addRect(rect);
    _rect_item->setFlag(QGraphicsItem::ItemIsSelectable);
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
EllipseTool::EllipseTool() : Tool("Ellipse", "E")
{

}

void EllipseTool::onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event)
{
    begin = event->scenePos();
    QSizeF size = QSizeF(1, 1);
    QRectF rect = QRectF(begin, size);
    _rect_item = canvas->addEllipse(rect);
    _rect_item->setFlag(QGraphicsItem::ItemIsSelectable);
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
PolygonTool::PolygonTool() : Tool("Polygon", "P")
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
        _polygon_item->setFlag(QGraphicsItem::ItemIsSelectable);
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
