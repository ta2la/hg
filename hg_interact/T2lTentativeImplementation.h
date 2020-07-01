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
#include "T2lEntityList.h"

namespace T2l//CHECKEND
{

class Display;

//=============================================================================
class TentativeImplementation {
//=============================================================================
public:
//<CONSTRUCTION>
    TentativeImplementation();
    virtual ~TentativeImplementation() {}
//<METHODS>
    virtual void enterTentative( const Point2F& pt, Display& view );
    virtual void afterConsumation() {};
    Point2F      consume();
//=============================================================================
//<OVERRIDES>
//protected:
//<DATA>
    EntityList entities_;
    Point2F    position_;
    bool       entered_;
//<INTERNALS>
    void enterTentative_( const Point2F& pt, Display& view );
//<FRIENDS>
    friend class CmdQueue;
};

} // namespace T2l
