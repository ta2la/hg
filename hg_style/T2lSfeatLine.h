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
#include "T2lLstyle.h"

namespace T2l
{
//=============================================================================
class SfeatLine : public Sfeat {
//=============================================================================
public:
//<CONSTRUCTION>
    SfeatLine( const Color& color = Color::BLACK, double width = 0.25,
               T2l::Lstyle* lstyle = NULL, double offset = 0.0 );
    virtual ~SfeatLine(void) {;}
//<METHODS>
    double offset()       { return offset_; }
    double width()        { return width_; }
    T2l::Lstyle* lstyle() { return lstyle_; }
    double extBeg()       { return extBeg_; }
    double extEnd()       { return extEnd_; }
//=============================================================================
//<OVERRIDES>
    virtual SfeatLine*  getAsLine()      { return this; }
protected:
//<DATA>
    double     width_;
    double     offset_;
    Lstyle*    lstyle_;
    double     extBeg_;
    double     extEnd_;
};

} // namespace T2l
