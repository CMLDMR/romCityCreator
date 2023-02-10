#ifndef WIDGET_GRAPHICSVIEW_H
#define WIDGET_GRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QPolygon>


class QGraphicsLineItem;

namespace Widget {

class GraphicsScene;





enum class ElementItem{
    null = 0,
    tree
};


class Polygon
{
public:
    Polygon(){}


    QList<QPointF> pointList() const;

    void append( const QPointF &point){
        mPList.append(point);
    }

    void clear(){
        mPList.clear();
    }

private:
    QList<QPointF> mPList;
};






class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget* parent = nullptr );

    void setCurrentDrawingElement(const ElementItem &itemType);


private:
    GraphicsScene* mScene;
    ElementItem mCurrentElementType;

    Polygon mPolygon;

    QList<Polygon> mPolygonList;



    void renderScene();

    QGraphicsLineItem* mDrawingLineItem;
    QLineF mLineF;




    // QWidget interface
protected:
    virtual void mouseMoveEvent(QMouseEvent *event) override;


    virtual void mouseReleaseEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
};



class GraphicsScene : public QGraphicsScene
{
public:
    GraphicsScene(QObject* parent = nullptr );
};

} // namespace Widget

#endif // WIDGET_GRAPHICSVIEW_H
