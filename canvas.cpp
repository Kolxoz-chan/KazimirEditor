#include "canvas.h"

Canvas::Canvas()
{
    _current_tool = new EllipseTool();
}

void Canvas::setCurrentTool(Tool* tool)
{
    _current_tool = tool;
}

void Canvas::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(_current_tool)
    {
        _current_tool->onMousePress(this, mouseEvent);
    }
}

void Canvas::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(_current_tool)
    {
        _current_tool->onMouseMove(this, mouseEvent);
    }
}

void Canvas::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(_current_tool)
    {
        _current_tool->onMouseRelease(this, mouseEvent);
    }
}

void Canvas::keyPressEvent(QKeyEvent *keyEvent)
{
    if(_current_tool)
    {
        _current_tool->onKeyPress(this, keyEvent);
    }
}

void Canvas::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if(_current_tool)
    {
        _current_tool->onKeyRelease(this, keyEvent);
    }
}
