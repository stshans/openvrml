//
// OpenVRML
//
// Copyright (C) 1998  Chris Morley
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
// 

#ifndef VRMLNODECHILD_H
#define VRMLNODECHILD_H

#include "VrmlNode.h"
class VrmlNodeScene;

class VrmlNodeChild : public VrmlNode {

public:

  // Define the fields of all built in child nodes
  static VrmlNodeType *defineType(VrmlNodeType *t);

  virtual const VrmlNodeChild * toChild() const;
  virtual VrmlNodeChild * toChild();

protected:
  VrmlNodeChild(VrmlScene *);
  VrmlNodeChild(const VrmlNodeChild & node);

};

#endif // VRMLNODECHILD_H

