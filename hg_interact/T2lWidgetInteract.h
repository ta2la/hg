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
#pragma once

#include "T2lWidget.h"
#include <QTime>

namespace T2l//CHECKEND
{

//=============================================================================
class WidgetInteract : public Widget {
//=============================================================================
public:
//<CONSTRUCTION>
    WidgetInteract( const Point2F& origin = Point2F(0, 0), double scale =1.0/1000.0 );
    virtual ~WidgetInteract();
//<METHODS>
    void zoom( const QPoint& zoomCenterInDisplay, double factorX, double factorY );
//=============================================================================
//<OVERRIDES>
    virtual void wheelEvent(QWheelEvent* event);
    virtual void mousePressEvent( QMouseEvent* e);
    virtual void mouseReleaseEvent( QMouseEvent* e);
    virtual void mouseMoveEvent( QMouseEvent* e);
    virtual void leaveEvent(QEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);
//<QT>
    Q_OBJECT
//protected:
//<DATA>
    bool        pressed_;
    QPoint      pressedPoint_;
    QTime       zoomEventTime_;
    bool        draggingMode_;
//<INTERNALS>
    Point2F mapPixelInDisplayMetric_(Point2F point);
//<FRIENDS>
};

} // namespace T2l
