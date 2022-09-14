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

    // Transformations tools
    _tools["Transformations"] += new SelectTool();

    // Primitives tools
    _tools["Primitives"] += new RectTool();
    _tools["Primitives"] += new EllipseTool();
    _tools["Primitives"] += new PolygonTool();

    // Tools menu
    QMenu* tools_menu = new QMenu("Tools");
    menuBar()->addMenu(tools_menu);

    for(auto key : _tools.keys())
    {
        QMenu* menu = new QMenu(key);
        tools_menu->addMenu(menu);

        for(int i=0; i<_tools[key].size(); i++)
        {
            Tool* tool = _tools[key][i];
            QKeySequence hot_key(tool->getHotKey());
            QString name = tool->getName();
            menu->addAction(tr(name.toStdString().c_str()), [this, tool](){ this->canvas->setCurrentTool(tool); }, hot_key);
        }
    }
    /*
    // Transformations tools
    QMenu* tools_primitives = new QMenu("Primitives");
    tools_menu->addMenu(tools_primitives);

    // Ellipse primitive tool
    act = tools_primitives->addAction(tr("Ellipse"), 0, 0, QKeySequence("E"));
    connect(act, SIGNAL(triggered(bool)), this, SLOT(selectEllipseTool()));

    // Primitives tools
    QMenu* tools_primitives = new QMenu("Primitives");
    tools_menu->addMenu(tools_primitives);

    // Rect primitive tool
    QAction* act = tools_primitives->addAction(tr("Rect"), [this](){this->canvas->setCurrentTool()}, QKeySequence("R"));
    //connect(act, SIGNAL(triggered(bool)), this, SLOT(selectRectTool()));

    // Ellipse primitive tool
    act = tools_primitives->addAction(tr("Ellipse"), 0, 0, QKeySequence("E"));
    connect(act, SIGNAL(triggered(bool)), this, SLOT(selectEllipseTool()));

    // Ellipse primitive tool
    act = tools_primitives->addAction(tr("Polygon"), 0, 0, QKeySequence("P"));
    connect(act, SIGNAL(triggered(bool)), this, SLOT(selectPolygonTool()));
*/
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


