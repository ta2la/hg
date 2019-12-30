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
#include "T2lBox2.h"
#include <QPixmap>
#include <QImage>

namespace T2l
{

//=============================================================================
class EntityImage : public Entity {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    EntityImage(const Box2F& bound, QPixmap* pixmap = NULL, bool owner = false);
    EntityImage(const Box2F& bound, QImage* image);
    virtual ~EntityImage(void);
//<METHODS>
    void pixmapSet(const QPixmap* pixmap, bool owner);
//=============================================================================
//<OVERRIDES>
    virtual void draw(Canvas* canvas);
protected:
//<DATA>
    const QImage*  image_;

    const QPixmap* pixmap_;
    bool           owner_;
//<INTERNAL>
    void destroy_();
};

} // namespace T2l
