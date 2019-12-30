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
#include "T2lScene.h"
#include "T2lDisplay.h"

using namespace T2l;//CHECKEND

//=============================================================================
Scene::Scene(Filter* filter) :
    RefCol(filter),
    entities_(this)
{
}

//=============================================================================
Scene::~Scene()
{
    fabs(0);
}

//=============================================================================
bool Scene::add(GObject* object)
{
    if( pass_(object) == false) return false;
    Ref* ref = new Ref(object);
    items_.add(ref);
    ref->parent_ = this;
    dirtySet();
    return true;
}

//=============================================================================
void Scene::refreshDisplay()
{
    entities_.refresh();
}

//=============================================================================
void Scene::initialize()
{
    RefCol::initialize();
    for ( int i = 0; i < items_.count(); i++ ) items_.get(i)->repaint();
}

//=============================================================================
