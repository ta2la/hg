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

#include "T2lRef.h"

namespace T2l//CHECKEND
{

class Filter;

//=============================================================================
class RefCol {
//=============================================================================
public:
//<CONSTRUCTION>
    RefCol(Filter* filter);
    virtual ~RefCol();
//<NEIGHBOURS>
    Filter* filter() { return filter_; }
//<ITEMS>
    virtual bool add(GObject* object);
    int count() const { return items_.count(); }
    Ref* get(int index) { return items_.get(index); }
//<METHODS>
    virtual void initialize();
    virtual void refreshDisplay() {}
    void dirtySet() { dirty_ = true; }
//=============================================================================
//<OVERRIDES>
//protected:
//<DATA>
    List<T2l::Ref> items_;
    Filter*        filter_;
    bool           dirty_;
//<INTERNALS>
    void         synchronizeContainment_(GObject* object);
    virtual bool pass_(GObject*);
    virtual bool addForce_(GObject*);
    void         modifiedSolve_(Ref* /*ref*/) {}
    virtual void remove_(Ref* ref);
//<FRIENDS>
};

} // namespace T2l
