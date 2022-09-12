#ifndef CANVAS_H
#define CANVAS_H

#include <QtWidgets>
#include <QtDebug>
#include "tool.h"

class Canvas : public QGraphicsScene
{
private:
    Tool* _current_tool = nullptr;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

public:
    Canvas();

    void setCurrentTool(Tool* tool);
};

#endif // CANVAS_H