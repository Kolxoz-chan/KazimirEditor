#ifndef EDITOR_H
#define EDITOR_H

#include "canvas.h"
#include "tool.h"

class Editor : public QMainWindow
{
    Q_OBJECT

private:
    QGraphicsView* canvas_widget;
    Canvas* canvas;
    QToolBar* tool_bar;
    QMap<QString, QVector<Tool*>> _tools;

private slots:
    void selectRectTool();
    void selectEllipseTool();
    void selectPolygonTool();

public:
    Editor(QWidget *parent = nullptr);
    ~Editor();

};
#endif // EDITOR_H
