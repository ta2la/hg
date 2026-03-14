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
#include "T2lSfeat.h"

using namespace T2l;

//=============================================================================
Sfeat::Sfeat( const Color& color ) :
    color_(color)
{
}

//=============================================================================
bool Sfeat::isScaleIn(double scale)
{
    if ( scale_.isEmpty() )       return true;
    if ( scale_.isInside(scale) ) return true;
    return false;
}

//=============================================================================
