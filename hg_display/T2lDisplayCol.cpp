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
#include "T2lDisplayCol.h"
#include "assert.h"

using namespace T2l;

//=============================================================================
DisplayCol::DisplayCol()
{
}

//=============================================================================
DisplayCol& DisplayCol::instance()
{   static DisplayCol* col = NULL;
    if (col == NULL) col = new DisplayCol();
    return *col;
}

//=============================================================================
Display* DisplayCol::active()
{
    if (count() == 0) {
        assert(0);
        return NULL;
    }

    for ( int i = 0; i < count(); i++ ) {
        if ( active_ != get(i)) continue;
        return active_;
    }

    active_ = get(0);
    return active_;
}

//=============================================================================
