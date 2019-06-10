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

#include "T2lComponent.h"
#include "T2lBox2.h"
#include "T2lRectangle2.h"

#include <QPixmap>
#include <QImage>

namespace T2l
{
//=============================================================================
class ComponentPixmap : public T2l::Component {
//=============================================================================
public:
//<ENUMS>
//<CONSTRUCTION>
    ComponentPixmap( const QPixmap* pixmap, const Box2F& pixmapBox);
    ComponentPixmap( const QImage*  image,  const Rectangle2& imageRect);
    virtual ~ComponentPixmap(void) {}
//<METHODS>
    const QPixmap*    pixmap() const { return pixmap_; }
    const T2l::Box2F& pixmapBox() const {return pixmapBound_; }

    const QImage*     image() const {return image_; }
    T2l::Rectangle2   imageRect() const { return imageRect_; }
//=============================================================================
//<OVERRIDES>
    virtual ECategory category() { return COMPONENT_IMAGE; }
protected:
//<DATA>
    const QPixmap*   pixmap_;
    T2l::Box2F       pixmapBound_;

    const QImage*    image_;
    T2l::Rectangle2  imageRect_;
//<FRIENDS>
    friend class CanvasPainter;
};

} // namespace T2l
