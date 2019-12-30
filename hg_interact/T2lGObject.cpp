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
#include "T2lGObject.h"
#include "T2lGObjectPool.h"
#include "T2lStyleChange.h"
#include <string>

using namespace T2l;
using namespace std;//CHECKEND

//=============================================================================
GObject::GObject() :
    uuid_(to_string(id()).c_str()),
    selected_(false)
{
    GObjectPool::instance().registryChanged_.add(this);
    GObjectPool::instance().registryUuid_.insert(uuid_, this);
}

//=============================================================================
GObject::~GObject()
{
    for(int i = 0; i < refs_.count(); i++) {
        refs_.at(i)->object_ = NULL;
        delete refs_.at(i);
    }

    GObjectPool::instance().registryUuid_.remove(uuid_);
    GObjectPool::instance().registryChanged_.remove(this);
}

//=============================================================================
void GObject::isSelectedSet(bool arg)
{
    if ( selected_ == arg) return;

    selected_ = arg;
    modifiedSet_();
}

//=============================================================================
void GObject::modifiedSet_()
{
    if( state_ = STATE_NEW ) return; //TODO mistake
    if( state_ = STATE_UPTODATE ) GObjectPool::instance().registryChanged_.add(this);
    state_ = STATE_CHANGED;
}

//=============================================================================
void GObject::modifiedSolve_(void)
{
    for (int i = 0; i < refs_.count(); i++) {
        refs_.at(i)->modifiedSolve_();
    }
}

//=============================================================================
StyleChange* GObject::styleChange()
{
    static StyleChange result(Color::MAGENTA, 0.25);
    return &result;
}


//=============================================================================
