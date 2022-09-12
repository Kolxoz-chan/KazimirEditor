#include "editor.h"
#include "time.h"

Editor::Editor(QWidget *parent) : QMainWindow(parent)
{
    // Window settings
    resize(1280, 720);
    setMouseTracking(true);
    //showMaximized();

    // Canvas
    canvas_widget = new QGraphicsView(this);
    setCentralWidget(canvas_widget);

    canvas = new Canvas();
    canvas->setSceneRect(0, 0, 1280, 720);
    canvas_widget->setScene(canvas);
    canvas_widget->setMouseTracking(true);

    // ToolBar
    tool_bar = new QToolBar();
    addToolBar(Qt::ToolBarArea::LeftToolBarArea, tool_bar);

    // Tools menu
    QMenu* tools_menu = new QMenu("Tools");
    QAction* tools = menuBar()->addMenu(tools_menu);

    // Primitives tools
    QMenu* tools_primitives = new QMenu("Primitives");
    tools_menu->addMenu(tools_primitives);

    // Rect primitive tool
    QAction* act = tools_primitives->addAction(tr("Rect"), 0, 0, QKeySequence("R"));
    connect(act, SIGNAL(triggered(bool)), this, SLOT(selectRectTool()));

    // Ellipse primitive tool
    act = tools_primitives->addAction(tr("Ellipse"), 0, 0, QKeySequence("E"));
    connect(act, SIGNAL(triggered(bool)), this, SLOT(selectEllipseTool()));

    // Ellipse primitive tool
    act = tools_primitives->addAction(tr("Polygon"), 0, 0, QKeySequence("P"));
    connect(act, SIGNAL(triggered(bool)), this, SLOT(selectPolygonTool()));

}

void Editor::selectRectTool()
{
    canvas->setCurrentTool(new RectTool);
}

void Editor::selectEllipseTool()
{
    canvas->setCurrentTool(new EllipseTool);
}

void Editor::selectPolygonTool()
{
    canvas->setCurrentTool(new PolygonTool);
}

Editor::~Editor()
{

}


