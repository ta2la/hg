//
// Copyright (C) 2024 Petr Talla. [petr.talla@gmail.com]
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

namespace T2l {

class PgraphItemText;
class PgraphItemBox;

//===================================================================
class PgraphItem : public Item  {
//===================================================================
public:
    PgraphItem(void);
    virtual ~PgraphItem(void) = default;
//===================================================================
    virtual PgraphItemText* getAsText() { return nullptr; }
    virtual PgraphItemBox*  getAsBox() { return nullptr; }

    virtual PgraphItem* clone() = 0;

    int cursorPos_ = {-1};

    friend class PgraphCursor;
};

} //namespace T2l
