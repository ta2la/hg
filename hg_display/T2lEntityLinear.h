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

#include "T2lEntityStyled.h"
#include "T2lPolyLine2.h"

namespace T2l
{

//=============================================================================
class EntityLinear : public EntityStyled {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityLinear( Style* style, bool styleOwner,
                    bool closed, StyleChange* styleChange );
    virtual ~EntityLinear() {}
//<NEIGHBOURS>
    PolyLine2& points() { return points_; }
//=============================================================================
//protected:
//<DATA>
    PolyLine2 points_;
//<INTERNALS>
    void drawBasic_(Canvas* canvas);
    bool check_(Canvas* canvas);
};

} // namespace T2l
