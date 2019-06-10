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
#include "T2lEntity.h"
#include "T2lEntityColI.h"

using namespace T2l;

//=============================================================================
Entity:: Entity(StyleChange* styleChange) :
    styleChange_(styleChange),
    parent_(NULL),
    layer_(0)
{
}

//=============================================================================
Entity::~Entity()
{
    destroy_not_delete_();
    for ( Area2* clip : clips_ ) delete clip;
}

//=============================================================================
void Entity::destroy_not_delete_()
{
    if ( parent_ != NULL ) parent_->remove_(this);
}

//=============================================================================
void Entity::addClip(T2l::Area2* clip)
{
    Entity::clips_.push_back(clip);
}

//=============================================================================
