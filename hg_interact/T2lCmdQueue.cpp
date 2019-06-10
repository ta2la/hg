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
#include "T2lCmdQueue.h"
#include "T2lCmd_pan.h"
#include "T2lCmd_zoomBox.h"
#include "T2lCmd_select.h"
#include "T2lCmd_void.h"
#include "T2lTentativeImplementation.h"
#include "TcCmdTransl.h"
#include <iostream>
#include <sstream>

using namespace T2l;
using namespace std;

CmdQueue* CmdQueue::queue_ = new CmdQueue();

//=============================================================================
CmdQueue::CmdQueue() :
    cmdStack_(*this),
    tentative_(new TentativeImplementation)
{
    add(new Cmd_void(), false);
}

//=============================================================================
bool CmdQueue::offerText ( const QString& text )
{
    if (text == "#") {
        consumeText_ = !consumeText_;
        TcCmdTransl::xcall("voidcmd", true);
        return true;
    }

    if (consumeText_ == false) return false;

    activeCommand()->enterText(text);
    //cout << "CONSUMING TEXT: " << text.toStdString() << endl;

    return true;
}

//=============================================================================
void CmdQueue::enterPointStright( const Point2F& pt, Display& view )
{
    activeCommand()->enterPoint(pt, view);
}

//=============================================================================
void CmdQueue::enterPoint( const Point2F& pt, Display& view )
{
    Point2F PT(pt);

    if (tentative_->entered_ == true) {
        PT = tentative_->consume();
    }

    stringstream cmd;
    cmd << "xy \"" << PT.x() << "\" \"" << PT.y() << "\"";

    TcCmdTransl::xcall(cmd.str().c_str(), true);
}

//=============================================================================
Cmd* CmdQueue::activeCommand()
{
    if ( cmdStack_.count() == 0 ) {
        Cmd_pan* cmd = new Cmd_pan();
    }

    return cmdStack_.get(cmdStack_.count()-1);
}

//=============================================================================
void CmdQueue::enterReset( Display& view )
{
    activeCommand()->enterReset(view);
    TcCmdTransl::xcall("voidcmd", true);
}

//=============================================================================
void CmdQueue::enterMove( const Point2F& pt, Display& view )
{
    activeCommand()->enterMove(pt, view);
}

//=============================================================================
void CmdQueue::enterTentative ( const Point2F& pt, Display& view )
{
    tentative_->enterTentative( pt, view );
}

//=============================================================================
void CmdQueue::add(Cmd* cmd, bool once)
{
    assert ( cmd != NULL );

    if ( once == false ) {
        for (int i = 0; i < cmdStack_.count(); i++) {
            Cmd* cmdi = cmdStack_.get(i);
            delete cmdi;
        }
    }

    cmdStack_.add(cmd);
    cmd->once_ = once;
}

//=============================================================================
