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

#include "T2lItem.h"
#include "T2lPoint2.h"
#include "T2lPoint2Col.h"
#include "T2lPoint3.h"
#include "T2lVector3.h"

#include <QString>

namespace T2l
{
class CmdQueue;
class Display;
class DisplayBase;

//=============================================================================
class Cmd : public Item {
//=============================================================================
public:
//<CONSTRUCTION>
    Cmd(const QString& name = "nullptr");
    virtual ~Cmd();
//<NEIGHBOURS>
    CmdQueue* queue();
//<METHODS>
    const   QString&  name()      const     { return name_; }
    virtual QString   hint(void)  const { return "no hint"; }
    virtual QString   dialog()    const { return ""; }
    virtual QString   dialogTml() const { return ""; }
    
    virtual void enterPoint( const Point2F& /*pt*/, Display& /*view*/ ) {}
    virtual void enterPoint( const Point3F& /*pt*/, Display& /*view*/ ) {}
    virtual void enterMove ( const Point2F& /*pt*/, Display& /*view*/ );
    virtual void enterReset( Display& /*view*/ ) {}
    virtual void enterText( const QString& /*text*/) {}

    virtual void enterRay(const Point3F& eye, const Vector3F dir, DisplayBase* display) {}
    virtual void moveRay(const Point3F& eye, const Vector3F dir, DisplayBase* display) {}

    virtual Point2F recalculateOrtho_( const Point2F& pt );
//=============================================================================
//<OVERRIDES>
//protected:
    QString    name_;
    bool       once_;
    Point2FCol cmdpts_;
//<DATA>
//<INTERNALS>
//<FRIENDS>
    friend class Queue;
};

} // namespace T2l
