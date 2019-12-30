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

#include "T2lEntity.h"
#include "T2lStyle.h"

namespace T2l
{

//=============================================================================
class EntityStyled : public Entity {
//=============================================================================
public:
//<CONSTRUCTION>
    EntityStyled( Style* style = NULL, bool owner = false, StyleChange* styleChange = NULL );
    virtual ~EntityStyled(void);
//<METHODS>
    const Style* style() const { return style_; }
    void styleSet(Style* style, bool owner) { style_ = style; owner_ = owner; }
//=============================================================================
    T2l::Style* style_;
    bool        owner_;
};

} // namespace T2l
