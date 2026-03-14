//
// Copyright (C) 2025 Petr Talla. [petr.talla@gmail.com]
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

namespace T2l
{
class EntityPack;

//=============================================================================
class DisplayBase : public Item {
//=============================================================================
public:
//<CONSTRUCTION>
    DisplayBase() {};
    virtual ~DisplayBase() = default;
//<NEIGHBOURS>
    void entityPackSet(EntityPack* pack) { entityPack_ = pack; };
    EntityPack* entityPack() { return entityPack_; }
//<DATA>
//<METHODS>
    virtual bool isQml() { return false; }
    virtual void updateDynamic() = 0;
    virtual void updateBmp() = 0;
//=============================================================================
//<OVERRIDES>
//protected:
    EntityPack* entityPack_ = nullptr;
//<INTERNALS>
//<FRIENDS>
};

} // namespace T2l
