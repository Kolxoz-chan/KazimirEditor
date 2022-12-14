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
    _tools["Transformations"] += new MoveTool();
    _tools["Transformations"] += new RotateTool();

    // Primitives tools
    _tools["Primitives"] += new RectTool();
    _tools["Primitives"] += new EllipseTool();
    _tools["Primitives"] += new PolygonTool();

    // Edit menu
    QMenu* edit_menu = new QMenu("Edit");
    menuBar()->addMenu(edit_menu);

    edit_menu->addAction(tr("Delete"), [this](){this->canvas->removeSelectedItems();}, QKeySequence("Delete"));

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
}

Editor::~Editor()
{

}


