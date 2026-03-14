//
// Copyright (C) 2023 Petr Talla. [petr.talla@gmail.com]
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

#include "T2lVector2.h"

namespace T2l
{

//=============================================================================
class Modifier3d
//=============================================================================
{
public:
//<CONSTRUCTION>
   Modifier3d();
   static Modifier3d& instance() { static Modifier3d i; return i; }
//<METHODS>
   double z() { return z_; }
   void zSet(double z) { z_ = z;}

   Vector2F& shift3d() { return shift3d_; }
   void shift3dSet(const Vector2F& shift3d) { shift3d_ = shift3d; }
//=============================================================================
protected:
//<DATA>
   double    z_;
   Vector2F  shift3d_;
};

}

//=============================================================================
