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
#include "T2lBox2.h"

namespace T2l//CHECKEND
{

//=============================================================================
class IdentifyBox : public Identify {
//=============================================================================
public:
//<CONSTRUCTION>
    IdentifyBox(const Canvas& canvas, const Box2F& box);
    virtual ~IdentifyBox() {}
//<METHODS>
    void display(EntityList& list);
//=============================================================================
//<OVERRIDES>
    virtual bool byPoint(const Point2F& pt);
protected:
//<DATA>
    Box2F box_;
//<INTERNALS>
   Box2F boxCalc_();
};

} // namespace T2l
