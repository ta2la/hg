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
#include "T2lSfeatLine.h"

using namespace T2l;

//=============================================================================
SfeatLine::SfeatLine( const Color& color, double width,
           T2l::Lstyle* lstyle, double offset ) :
    Sfeat(color),
    width_(width),
    offset_(offset),
    lstyle_(lstyle),
    extBeg_(0.0),
    extEnd_(0.0)
{
}

//=============================================================================
