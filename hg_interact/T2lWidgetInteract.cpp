//
// Copyright (C) 2015 Petr Talla. [petr.talla@gmail.com]
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//		      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
#include "T2lWidgetInteract.h"
#include "T2lWidgetInteractCol.h"
#include "T2lCmdQueue.h"
#include "T2lGObject.h"
#include "T2lVector2.h"
#include "T2lEntityPack.h"
#include "T2lCmd_pan.h"
#include "T2lDisplayCol.h"
#include "T2lModifier3d.h"

#include <QPixmap>
#include <QMouseEvent>

#include <iostream>

using namespace T2l;
using namespace std;//CHECKEND

//=============================================================================
WidgetInteract::WidgetInteract(const Point2F& origin, double scale ) :
    Widget(origin, scale ),
    draggingMode_(false),
    zoomEventTime_(QTime::currentTime()),
    pressed_(false)
{
    setAttribute(Qt::WA_NoSystemBackground, true);
    //setAttribute(Qt::WA_NoBackground);
    setAutoFillBackground(false);
    setCursor(Qt::ArrowCursor);
}

//=============================================================================
WidgetInteract::~WidgetInteract()
{
    bool contained = false;
    for( int i = 0; i < WidgetInteractCol::instance().count(); i++) {
        if ( WidgetInteractCol::instance().get(i) != this ) continue;
        contained = true;
        break;
    }
    if ( contained == false ) return;
    WidgetInteractCol::instance().remove(this);
}

//=============================================================================
void WidgetInteract::keyPressEvent(QKeyEvent *event)
{
    QString text = event->text();

    if (event->key() == Qt::Key_Backspace)   text = "__BACKSPACE__";
    else if (event->key() == Qt::Key_Insert) text = "__INSERT__";
    else if (event->key() == Qt::Key_Left)   text = "__LEFT__";
    else if (event->key() == Qt::Key_Right)  text = "__RIGHT__";
    else if (event->key() == Qt::Key_Return) {
        text = "__ENTER__";
    }
    else if (event->key() == Qt::Key_Enter) {
        text = "__ENTER__";
    }

    CmdQueue::queue().offerText(text);
    CmdQueue::queue().enterMove(mapPixelInDisplayMetric_(lastMove_), *this);
}

//=============================================================================
void WidgetInteract::mousePressEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) return;

    pressed_ = true;
    pressedPoint_ = e->pos();
}

//=============================================================================
void WidgetInteract::mouseReleaseEvent( QMouseEvent* event)
{
    setCursor(Qt::ArrowCursor);

    if ( event->button() == Qt::LeftButton )  {
        Point2F pt2 = mapPixelInDisplayMetric_(Point2F(event->pos().x(), event->pos().y()));
        Point3F pt(pt2.x(), pt2.y(), Modifier3d::instance().z());

        DisplayCol::instance().activeSet(this);
        CmdQueue::queue().enterPoint(pt, *this);

        pressed_      = false;
        draggingMode_ = false;
    }
    else if ( event->button() == Qt::RightButton) {
        CmdQueue::queue().enterReset(*this);
    }
    else if (event->button() == Qt::MiddleButton) {
        Point2F pt = mapPixelInDisplayMetric_(Point2F(event->pos().x(), event->pos().y()));
        CmdQueue::queue().enterTentative(pt, *this);
    }
}

//=============================================================================
void WidgetInteract::mouseMoveEvent(QMouseEvent* event)
{
    DisplayCol::instance().activeSet(this);

    CmdQueue& q = CmdQueue::queue();

    Vector2I delta( event->pos().x() - pressedPoint_.x(),
                    event->pos().y() - pressedPoint_.y() );


    if ( pressed_  && !draggingMode_ && (delta.getLengthSq() > 50) ) {
        setCursor(Qt::ClosedHandCursor);
        q.add(new Cmd_pan(), true);
        Point2F center(pressedPoint_.x(), pressedPoint_.y());
        Point2F pt2 = mapPixelInDisplayMetric_(center);
        q.enterPoint(Point3F(pt2.x(), pt2.y(), Modifier3d::instance().z()), *this);
        draggingMode_ = true;
    }

    lastMove_= Point2F(event->pos().x(), event->pos().y());
    q.enterMove(mapPixelInDisplayMetric_(lastMove_), *this);
}

//=============================================================================
void WidgetInteract::wheelEvent( QWheelEvent* event )
{
    double delta = event->angleDelta().y();
    double zoomFactor = ( delta < 0) ? 0.8 : 1.2;
    zoom( event->position().toPoint(), zoomFactor);
}

//=============================================================================
void WidgetInteract::leaveEvent(QEvent*)
{
    EntityPack* pack = entityPack();
    if (pack == nullptr) return;
    pack->cleanDynamic();
    pack->dynamicRefresh();
}

//=============================================================================
void WidgetInteract::zoom( const QPoint& zoomCenterInDisplay, double factor )
{
    if ( zoomEventTime_.msecsTo(QTime::currentTime()) < 100 ) return;
    zoomEventTime_ = QTime::currentTime();

    const Point2F centerBefore = mapPixelInMetric_(Point2F(zoomCenterInDisplay.x(), zoomCenterInDisplay.y()));

    scaleSet(scale()*factor);
    //scaleSet(scale(Scale2::Y)*factorY, Scale2::Y);

    const Point2F centerAfter = mapPixelInMetric_(Point2F(zoomCenterInDisplay.x(), zoomCenterInDisplay.y()));
    Point2F originNew = origin();
    originNew.add(Vector2F(centerAfter, centerBefore));
    originSet(originNew);

    refresh();
}

//=============================================================================
Point2F WidgetInteract::mapPixelInDisplayMetric_(Point2F pt)
{
    double x = pt.x()-edge_[EDGE_LEFT];
    double y = pt.y()+edge_[EDGE_BOTTOM];

    return mapPixelInMetric_(Point2F(x, y));
}

//=============================================================================
