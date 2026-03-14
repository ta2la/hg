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

#include "T2lEntityColI.h"
#include "T2lList.h"

namespace T2l
{

//=============================================================================
class EntityCol : public EntityColI {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityCol();
    virtual ~EntityCol();
    
    void clean();
//<ITEMS>
    int count() { return items_.count(); }
    Entity* get(int i) { return items_.get(i); }
    void add(Entity* item);
//=============================================================================
//<OVERRIDES>
    virtual void remove_(Entity* entity);
protected:
    List<Entity> items_;
};

} // namespace T2l
