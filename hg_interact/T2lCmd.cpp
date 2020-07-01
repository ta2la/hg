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
#include "T2lCmd.h"
#include "T2lCmdStack.h"
#include "T2lCmdQueue.h"
#include "T2lDisplay.h"

#include <assert.h>

using namespace T2l;

//=============================================================================
Cmd::Cmd(const QString& name) :
    name_(name)
{
}

//=============================================================================
Cmd::~Cmd()
{
    assert(queue() != NULL);
    CmdStack& stack = queue()->cmdStack();
    if ( stack.count() == 1 ) return;
    stack.remove(stack.count()-1);
}

//=============================================================================
CmdQueue* Cmd::queue()
{
    CmdStack* stack = dynamic_cast<CmdStack*>(parent_);
    assert(stack);
    return &stack->parent();
}

//=============================================================================
void Cmd::enterMove ( const Point2F& pt, Display& view )
{
    view.entityPack()->dynamicRefresh();
}

//=============================================================================
