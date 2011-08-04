/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef ARROW_H
#define ARROW_H

#include <QGraphicsLineItem>
#include <QtXml>

#include <QGraphicsLineItem>
#include <QtXml>
#include "diagramtextitem.h"
#include "lineitem.h"
#include "diagramitem.h"

class lineItem;

QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsPathItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE

class Arrow : public QGraphicsPathItem
{
public:
    enum { Type = UserType + 32 };

    Arrow(DiagramTextItem *startItem, DiagramTextItem *endItem,
      QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);

    int type() const
        { return Type; }
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void setColor(const QColor &color)
        { myColor=color; }
    DiagramTextItem *startItem() const
        { return myStartItem; }
    DiagramTextItem *endItem() const
        { return myEndItem; }

    void removeLine(lineItem *line);
    void removeLines();
    bool addLine(lineItem *line);
    QList<QPointF> getCorners()
        { return myCorners;}

    void createCorner(QPointF cornerPos, lineItem *inLine);
    void createCorner(QPointF cornerPos, int index);
    void moveCorner(QPointF cornerPos, lineItem *inLine);

    void setVisibleCorners(bool visible);
    void setSelectedLines(bool sel);

    void snapToGrid(QGraphicsSceneMouseEvent *event);

    QDomDocument toXmlFormat();

    QPointF startOffset() const
        { return myStartItem->offset();}

    QPointF endOffset() const
        { return myEndItem->offset();}

    DiagramItem  *startOwner() const
        { return myStartItem->ownerItem();}
    DiagramItem  *endOwner() const
        { return myEndItem->ownerItem();}

    QDomElement toXml(QDomDocument &,QHash<int , DiagramItem *>) const;

    QGraphicsScene *myOwnerScene;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);

private:
    DiagramTextItem *myStartItem;
    DiagramTextItem *myEndItem;
    QColor myColor;
    QPolygonF arrowHeadEnd;
    QPolygonF arrowHeadStart;
    QList<lineItem *> myLines;
    QList<lineItem *> myCLines;
    QList<QPointF> myCorners;    
    qreal arrowSize;    
    bool moving;
    QPointF previousPos;
    bool positionChanged;
};

#endif