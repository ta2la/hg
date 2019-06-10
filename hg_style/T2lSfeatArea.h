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

#include "T2lColor.h"
#include "T2lSfeat.h"

namespace T2l
{

//=============================================================================
class SfeatArea : public Sfeat {
//=============================================================================
public:
//<CONSTRUCTION>
    SfeatArea( const Color& color = Color::BLACK, unsigned char alpha = 255 );
    virtual ~SfeatArea(void) {;}
//<METHODS>
    double alpha() const { return alpha_; }
//=============================================================================
//<OVERRIDES>
    virtual SfeatArea* getAsArea() { return NULL; }
protected:
//<DATA>
    double          alpha_;
};

} // namespace T2l
