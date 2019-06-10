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
#include "T2lEntityPack.h"
#include "T2lDisplay.h"
#include "T2lEntity.h"
#include "T2lDisplayBmp.h"

#include <iostream>

using namespace T2l;

//=============================================================================
EntityPack::EntityPack(Scene* scene) :
    scene_(scene)
{
}

//=============================================================================
EntityPack::~EntityPack()
{
    entitiesD_.clean();
}

//=============================================================================
void EntityPack::add(Entity* entity)
{
    entities_.add(entity);
}

//=============================================================================
void EntityPack::addDynamic(Entity* entity)
{
    entitiesD_.add(entity);
}

//=============================================================================
void EntityPack::clean()
{
    entities_.clean();
}

//=============================================================================
void EntityPack::cleanDynamic()
{
    entitiesD_.clean();
}

//=============================================================================
void EntityPack::refresh(void)
{
    for (int i = 0; i < displays_.count(); i++) {
        displays_.get(i)->bitmap_->bmpUpdate();
    }
}

//=============================================================================
void EntityPack::draw(T2l::Canvas& canvas)
{
    std::cout << "-----------------------------------------" << std::endl;

    int BOUND = Entity::layerMax()+1;

    int currentLayer_ = 0;
    int nextLayer_    = BOUND;

    for (int i(0); i < entities_.count(); i++ ) {
        int layeri = entities_.get(i)->layer();
        if ( layeri > nextLayer_ ) continue ;
        nextLayer_ = layeri;
    }

    while ( nextLayer_ < BOUND ) {
        currentLayer_ = nextLayer_;
        nextLayer_    = BOUND;

        for (int i(0); i < entities_.count(); i++ ) {
            int layeri = entities_.get(i)->layer();
            if ( layeri > currentLayer_) {
                if ( layeri > nextLayer_ ) continue;
                nextLayer_ = layeri;
            }
            else if (layeri == currentLayer_) {
                entities_.get(i)->draw(&canvas);
            }
        }
    }
}

//=============================================================================
void EntityPack::dynamicRefresh(void)
{
    for (int i = 0; i < displays_.count(); i++) {
        displays_.get(i)->updateDynamic();
    }
}

//=============================================================================
void EntityPack::drawDynamic(T2l::Canvas& canvas)
{
    for (int i(0); i < entitiesD_.count(); i++ ) {
        entitiesD_.get(i)->draw(&canvas);
    }
}

//=============================================================================
void EntityPack::addDisplay(Display* display)
{
    displays_.add(display); display->entityPack_ = this;
}

//=============================================================================
