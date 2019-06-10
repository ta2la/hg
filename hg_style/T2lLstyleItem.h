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
#include "T2lItemCol.h"

namespace T2l
{

//=============================================================================
class LstyleItem : public Item {
//=============================================================================
public:
    LstyleItem( double size, bool isSpace );
    virtual ~LstyleItem(void) {;}
//<METHODS>
    double size(void) const { return size_; }
    bool   isSpace(void) const { return isSpace_; }
//=============================================================================
//<OVERRIDES>
protected:
//<DATA>
    double size_;
    bool   isSpace_;
};

typedef ItemCol<LstyleItem> LineStyleItemCol;

} // namespace T2l
