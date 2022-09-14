#ifndef CANVAS_H
#define CANVAS_H

#include <QtWidgets>
#include <QtDebug>
#include "tool.h"

class Canvas : public QGraphicsScene
{
private:
    Tool* _current_tool = nullptr;

    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);

    void keyPressEvent(QKeyEvent *keyEvent);
    void keyReleaseEvent(QKeyEvent *keyEvent);

public:
    Canvas();

    void setCurrentTool(Tool* tool);

    void removeSelectedItems();
};

#endif // CANVAS_H
