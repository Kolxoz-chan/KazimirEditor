#ifndef TOOL_H
#define TOOL_H

#include <QtCore>
#include <QtWidgets>

#include "shape.h"

class Tool
{
private:
    QString _name, _description;

public:
    Tool(QString _name, QString _description);

    virtual void onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event){};
    virtual void onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event){};
    virtual void onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event){};
    virtual void onKeyPress(QGraphicsScene* canvas, QKeyEvent *keyEvent){};
    virtual void onKeyRelease(QGraphicsScene* canvas, QKeyEvent *keyEvent){};
};

class RectTool : public Tool
{
private:
    QGraphicsRectItem* _rect_item = nullptr;
    QPointF begin;

public:
    RectTool();

    void onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
    void onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
    void onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
};

class EllipseTool : public Tool
{
private:
    QGraphicsEllipseItem* _rect_item = nullptr;
    QPointF begin;

public:
    EllipseTool();

    void onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
    void onMouseRelease(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
    void onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
};

class PolygonTool : public Tool
{
private:
    QGraphicsPathItem* _polygon_item = nullptr;
    QPainterPath _path;

public:
    PolygonTool();

    void onMousePress(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
    void onMouseMove(QGraphicsScene* canvas, QGraphicsSceneMouseEvent* event) override;
    void onKeyRelease(QGraphicsScene* canvas, QKeyEvent *keyEvent) override;
};

#endif // TOOL_H
