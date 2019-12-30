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

#include "T2lDisplay.h"
#include <QWidget>
//#include <QOpenGLWidget>

namespace T2l
{

class DisplayDynamic;

//=============================================================================
class Widget : public Display, public QWidget {
//=============================================================================
public:
//<CONSTRUCTION>
    Widget(const Point2F& origin, double scale );
    virtual ~Widget();
//=============================================================================
//<OVERRIDES>
    virtual void updateDynamic();
    virtual Size2F size() const;
protected:
    virtual void paintEvent(QPaintEvent* event);
    virtual void resizeEvent(QResizeEvent* event);
    virtual void leaveEvent(QEvent* event);
    virtual void refresh_();
    virtual void closeEvent(QCloseEvent *event);
//<DATA>
    DisplayDynamic* displayDynamic_;
    int updateId_;
//<INTERNALS>
    Point2F mapPixelInMetric_(const Point2F);
    virtual bool isBitmapFresh_();
    void cleanDrawing_(QPainter& painter);
    void cleanDrawing_box_(QPainter& painter, const Box2I& box);
    virtual int widthPx_() { return width()-edge_[EDGE_LEFT]-edge_[EDGE_RIGHT]; }
    virtual int heightPx_() { return height()-edge_[EDGE_TOP]-edge_[EDGE_BOTTOM]; }
};

} // namespace T2l
