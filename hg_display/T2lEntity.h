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

#include "TcObject.h"
#include "T2lBox2.h"
#include "T2lArea2.h"

namespace T2l
{

class Canvas;
class CanvasI;
class StyleChange;
class EntityColI;

//=============================================================================
class Entity : public TcObject {
//=============================================================================
public:
//<ENUMS>
    enum EZorder { ZORDER_TOP, ZORDER_NORMAL, ZORDER_BOTTOM };
//<CONSTRUCTION>
    Entity( StyleChange* styleChange = NULL );
    virtual ~Entity(void);
//<METHODS>
    virtual void draw(Canvas* canvas) = 0;

    const Box2F&       bound() const { return bound_; }
    const StyleChange* styleChange()    { return styleChange_; }
    void               styleChangeSet(StyleChange* styleChange) { styleChange_ = styleChange; }

    void               addClip(T2l::Area2* clip);

    int                layer() { return layer_; }
    void               layerSet(int layer) { layer_ = layer; }
    static int         layerMax() { return 10e6; }
//=============================================================================
    Box2F                  bound_;
    StyleChange*           styleChange_;
    EntityColI*            parent_;
    std::list<T2l::Area2*> clips_;
    int                    layer_;
//<INTERNALS>
    void destroy_not_delete_();
//<FRIENDS>
    friend class Ref;
};

} // namespace T2l
