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
#include "T2lEntityCol.h"
#include "T2lEntity.h"
#include <assert.h>

using namespace T2l;

//=============================================================================
EntityCol::EntityCol()
{
}

//=============================================================================
EntityCol::~EntityCol()
{
    for ( int i = 0; i < items_.count(); i++ ) {
        items_.get(i)->parent_ = NULL;
    }

    clean();
}

//=============================================================================
void EntityCol::add(Entity* item)
{
    assert( item->parent_ == NULL );
    item->parent_ = this;
    items_.add(item);
}

//=============================================================================
void EntityCol::clean()
{
    for( int i = 0; i < items_.count(); i++ ) delete items_.get(i);
    items_.clean();
}

//=============================================================================
void EntityCol::remove_(Entity* entity)
{
    items_.remove(entity);
    entity->parent_ = NULL;
}

//=============================================================================
