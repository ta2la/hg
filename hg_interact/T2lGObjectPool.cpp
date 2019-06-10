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
#include "T2lGObjectPool.h"
#include "TcObject.h"
#include "T2lRefColSelection.h"
#include "T2lGObject.h"
#include <assert.h>

using namespace T2l;//CHECKEND

//=============================================================================
GObjectPool::GObjectPool() :
    updateLock_(0)
{
    registryRefCol_.append(new RefColSelection());
}

//=============================================================================
void GObjectPool::addRefCol(RefCol* refCol)
{
    registryRefCol_.append(refCol);
    refCol->initialize();
}

//=============================================================================
void GObjectPool::handleLockDecrement_()
{
    if (--updateLock_ > 0) return;
    assert (updateLock_ >= 0);

    for( int i = 0; i < registryChanged_.count(); i++ ) {
        GObject* object = registryChanged_.get(i);
        if (object->state_ == TcObject::STATE_NEW) {
            for ( int ref = 0; ref < registryRefCol_.count(); ref++ ) {
                registryRefCol_.at(ref)->add(object);
            }
        }
        else {
            for(int ref = 0; ref < registryRefCol_.count(); ref++) {
                registryRefCol_.at(ref)->synchronizeContainment_(object);
            }
        }

        object->modifiedSolve_();
        object->state_ = TcObject::STATE_UPTODATE;
    }

    registryChanged_.clean();

    for ( int i = 0; i < registryRefCol_.count(); i++) {
        if (registryRefCol_.at(i)->dirty_) {
            registryRefCol_.at(i)->refreshDisplay();
            registryRefCol_.at(i)->dirty_ = false;
        }
    }
}

//=============================================================================
RefColSelection& GObjectPool::selected()
{
    RefColSelection* result = dynamic_cast<RefColSelection*>(registryRefCol_.at(0));
    assert(result);
    return *result;
}

//=============================================================================
GObjectPool& GObjectPool::instance()
{
    static GObjectPool* pool = NULL;
    if ( pool == NULL ) pool = new GObjectPool();
    return *pool;
}

//=============================================================================
