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

#include "T2lRefCol.h"
#include "TcObject.h"
#include "T2lEntityPack.h"

namespace T2l//CHECKEND
{

//=============================================================================
class Scene : public RefCol, public TcObject {
//=============================================================================
public:
//<CONSTRUCTION>
    Scene(Filter* filter);
    virtual ~Scene();
//<METHODS>
    EntityPack& entities() { return entities_; }
//=============================================================================
//<OVERRIDES>
    virtual void initialize();
    virtual bool add(GObject* object);
    virtual void refreshDisplay();
//protected:
//<DATA>
    EntityPack entities_;
//<INTERNALS>
//<FRIENDS>
};

} // namespace T2l
