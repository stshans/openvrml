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

#ifndef SCRIPTOBJECT_H
#define SCRIPTOBJECT_H

#include <stddef.h>
#include "common.h"

class VrmlField;
class VrmlNodeScript;

class OPENVRML_SCOPE ScriptObject {
public:
    virtual ~ScriptObject() = 0;
    virtual void activate(double timeStamp, const char * fname,
                          size_t argc, const VrmlField * const argv[]) = 0;

protected:
    ScriptObject(VrmlNodeScript & scriptNode);

    VrmlNodeScript & scriptNode;

private:
    // non-copyable
    ScriptObject(const ScriptObject &);
    ScriptObject & operator=(const ScriptObject &);
};

#endif
