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

#include "T2lIdentify.h"
#include "T2lPolyLine2.h"

namespace T2l//CHECKEND
{

class Area2;

//=============================================================================
class IdentifyLine : public Identify {
//=============================================================================
public:
//<CONSTRUCTION>
    IdentifyLine(const Canvas& canvas);
    virtual ~IdentifyLine() {}
//<METHODS>
    Point2FCol& points() { return polyline_.points(); }
//=============================================================================
//<OVERRIDES>
    virtual bool byPoint(const Point2F& pt);
    virtual bool byBox(const Box2F& box);
    virtual void display(EntityList& list);
protected:
//<DATA>
    PolyLine2 polyline_;
//<INTERNALS>
    void exactArea_(Area2& area);
};

} // namespace T2l
