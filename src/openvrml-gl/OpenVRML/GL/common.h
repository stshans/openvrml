//
// OpenVRML
//
// Copyright (C) 2001  Braden McDaniel
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

# ifndef OPENVRML_GL_COMMON_H
#   define OPENVRML_GL_COMMON_H

#   if defined(_WIN32)
#     if defined(DLL_EXPORT)
#       define OPENVRML_GL_SCOPE __declspec(dllexport)
#     elif defined(OPENVRML_DLL_IMPORT)
#       define OPENVRML_GL_SCOPE __declspec(dllimport)
#     endif
#   endif
#   if !defined(OPENVRML_GL_SCOPE)
#     define OPENVRML_GL_SCOPE
#   endif

# endif
