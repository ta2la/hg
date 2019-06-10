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

#include "TcObject.h"
#include "T2lPoint2.h"
#include "T2lBox2.h"
#include "T2lRef.h"

#include <QString>
#include <QList>

namespace T2l//CHECKEND
{

class EntityList;
class Canvas;
class StyleChange;
class GObjectPool;

//=============================================================================
class GObject : public TcObject {
//=============================================================================
public:
//<STATE>
    enum EIdentified { IDENTIFIED_NOTIMPLEMENTED, IDENTIFIED_YES, IDENTIFIED_NO };
//<CONSTRUCTION>
    GObject();
    virtual ~GObject();
//<DATA>
    const QString& uuid() const { return uuid_; }
    bool isSelected() const { return selected_; }
    void isSelectedSet(bool arg);
//<METHODS>
    virtual void display(EntityList& /*list*/, RefCol* /*scene*/) = 0;
    virtual EIdentified identifiedByPoint( const Canvas& /*canvas*/, const Point2F& /*pt*/) {return IDENTIFIED_NOTIMPLEMENTED; }
    virtual EIdentified identifiedByBox( const Canvas& /*canvas*/, const Box2F& /*box*/)  {return IDENTIFIED_NOTIMPLEMENTED; }

    static StyleChange* styleChange();
//=============================================================================
//<OVERRIDES>
//protected:
//<DATA>
    QString uuid_;

    QList<Ref*> refs_;
    bool selected_;
//<INTERNALS>
    virtual void modifiedSet_();
    void modifiedSolve_();
//<FRIENDS>
    friend class GObjectPool;
    friend class Cmd_object_movePoints;
    friend class Cmd_over_file_manipulate;
    friend class Cmd_actual_image_set;
};

} // namespace T2l
