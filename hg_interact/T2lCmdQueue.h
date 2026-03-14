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

//#include "T2lWidgetInteract.h"
#include "T2lCmdStack.h"
#include "T2lQueue.h"
#include "T2lPoint3.h"

namespace T2l
{

class Cmd;
class TentativeImplementation;

//=============================================================================
class CmdQueue : public Queue {
//=============================================================================
public:
//<CONSTRUCTION>
    CmdQueue();
    virtual ~CmdQueue() {}
    static CmdQueue& queue() { return *queue_; }
//<METHODS>
    CmdStack& cmdStack() { return cmdStack_; }
    void add(Cmd* cmd, bool once);
    Cmd* activeCommand();
    void setTentaiveImplementation(TentativeImplementation* ti) { tentative_ = ti; }
    Point3F lastPoint() const { return lastPoint_; }
    Point2F originalPoint2() { return Point2F(originalPoint_.x(), originalPoint_.y()); }
//=============================================================================
    void enterPointStright ( const Point3F& pt, Display& view );
    void enterPoint        ( const Point3F& pt, Display& view );
    void enterReset        ( Display& view );
    void enterMove         ( const Point2F& pt, Display& view );
    void enterTentative    ( const Point2F& pt, Display& view );

    double  grid() { return grid_; }
    Point2F gridCalc( const Point2F& pt);
    void    gridSet(double grid) { grid_ = grid; }

//<OVERRIDES>
    virtual bool offerText ( const QString& text );
//protected:
//<DATA>
    CmdStack                 cmdStack_;
    Point3F                  lastPoint_;
    static CmdQueue*         queue_;

    double                   grid_;

    TentativeImplementation* tentative_;

    Point3F                  originalPoint_;
};

} // namespace T2l
