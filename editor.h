#ifndef EDITOR_H
#define EDITOR_H

#include "canvas.h"

class Editor : public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsView* canvas_widget;
    Canvas* canvas;
    QToolBar* tool_bar;

private slots:
    void selectRectTool();
    void selectEllipseTool();
    void selectPolygonTool();

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

};
#endif // EDITOR_H
