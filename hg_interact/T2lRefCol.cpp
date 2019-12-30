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
#include "T2lRefCol.h"
#include "T2lGObjectPool.h"
#include "T2lFilter.h"
#include "T2lGObject.h"
#include "assert.h"

using namespace T2l;//CHECKEND

//=============================================================================
RefCol::RefCol(Filter* filter) :
    filter_(filter),
    dirty_(false)
{
}

//=============================================================================
RefCol::~RefCol()
{
    QList<RefCol*>& registry = GObjectPool::instance().registryRefCol_;

    for ( int i = 0; i < registry.count(); i++) {
        if ( registry.at(i) != this ) continue;
        registry.removeAt(i);
    }

    for (int i = 0; i < items_.count(); i++) {
        Ref* ref = items_.get(i);
        ref->parent_ = NULL;
        delete ref;
    }

    delete filter_;
}

//=============================================================================
void RefCol::remove_(Ref* ref)
{
    items_.remove(ref);
    dirty_ = true;
}

//=============================================================================
void RefCol::initialize()
{
    assert (filter_ != NULL);

    GObjectPool& pool = GObjectPool::instance();
    for ( auto it = pool.registryUuid_.begin();
          it != pool.registryUuid_.end(); it++) {
        this->add(it.value());
    }

    dirty_ = true;
}

//=============================================================================
bool RefCol::add(GObject* object)
{
    bool result = pass_(object);
    if (result) addForce_(object);
    return result;
}

//=============================================================================
bool RefCol::pass_(GObject* object)
{
    assert(object);
    if (filter_ == NULL) return true;
    return filter_->pass(object);
}


//=============================================================================
bool RefCol::addForce_(GObject* object)
{
    Ref* ref = new Ref(object);
    items_.add(ref);
    ref->parent_ = this;
    dirty_ = true;
    return true;
}

//=============================================================================
void RefCol::synchronizeContainment_(GObject* object)
{
    QList<Ref*>& refs = object->refs_;

    if (filter_->pass(object)) {
        for ( int i = 0; i < refs.count(); i++ ) {
            if ( refs.at(i)->parent_ == this) return;
        }

        addForce_(object);
    }
    else {
        for ( int i = 0; i < refs.count(); i++ ) {
            Ref* refi = refs.at(i);
            if (refi->parent_ != this) continue;
            delete refi;
        }
    }
}

//=============================================================================
