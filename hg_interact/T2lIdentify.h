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

#include "T2lPoint2.h"
#include "T2lBox2.h"

namespace T2l//CHECKEND
{

class EntityList;
class Canvas;
class Entity;
class Sfeat;

//=============================================================================
class Identify {
//=============================================================================
public:
//<CONSTRUCTION>
    Identify(const Canvas& canvas, double enlargement = 2.5);
    virtual ~Identify() {}
//<METHODS>
    double enlargement() { return enlargement_; }
    void enlargementSet(double enlargement);

    virtual bool byPoint(const Point2F& pt) = 0;
    virtual bool byBox(const Box2F& box) = 0;
    virtual void display(EntityList& /*list*/) {}
//=============================================================================

    double   enlargement_;
    const Canvas& canvas_;
};

} // namespace T2l
