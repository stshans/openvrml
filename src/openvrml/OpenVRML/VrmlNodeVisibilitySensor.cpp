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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "VrmlNodeVisibilitySensor.h"
#include "VrmlNodeType.h"
#include "VrmlNodeVisitor.h"
#include "VrmlNodeNavigationInfo.h"
#include "MathUtils.h"
#include "System.h"
#include "Viewer.h"
#include "VrmlScene.h"

// VisibilitySensor factory. 

static VrmlNode *creator( VrmlScene *scene ) 
{
  return new VrmlNodeVisibilitySensor(scene);
}


// Define the built in VrmlNodeType:: "VisibilitySensor" fields

VrmlNodeType *VrmlNodeVisibilitySensor::defineType(VrmlNodeType *t)
{
  static VrmlNodeType *st = 0;

  if (! t)
    {
      if (st) return st;		// Only define the type once.
      t = st = new VrmlNodeType("VisibilitySensor", creator);
      t->reference();
    }

  VrmlNodeChild::defineType(t);	// Parent class
  t->addExposedField("center", VrmlField::SFVEC3F);
  t->addExposedField("enabled", VrmlField::SFBOOL);
  t->addExposedField("size", VrmlField::SFVEC3F);
  t->addEventOut("enterTime", VrmlField::SFTIME);
  t->addEventOut("exitTime", VrmlField::SFTIME);
  t->addEventOut("isActive", VrmlField::SFBOOL);

  return t;
}

VrmlNodeType & VrmlNodeVisibilitySensor::nodeType() const
{
    return *defineType(0);
}


VrmlNodeVisibilitySensor::VrmlNodeVisibilitySensor( VrmlScene *scene ) :
  VrmlNodeChild(scene),
  d_center(0.0, 0.0, 0.0),
  d_enabled(true),
  d_size(0.0, 0.0, 0.0),
  d_isActive(false),
  d_enterTime(0.0),
  d_exitTime(0.0)
{
  setModified();
}

VrmlNodeVisibilitySensor::~VrmlNodeVisibilitySensor()
{
}

bool VrmlNodeVisibilitySensor::accept(VrmlNodeVisitor & visitor) {
    if (!this->visited) {
        this->visited = true;
        visitor.visit(*this);
        return true;
    }
    
    return false;
}

ostream& VrmlNodeVisibilitySensor::printFields(ostream& os, int indent)
{
  if (! FPZERO(d_center.getX()) ||
      ! FPZERO(d_center.getY()) ||
      ! FPZERO(d_center.getZ()) )
    PRINT_FIELD(center);
  if (! d_enabled.get())
    PRINT_FIELD(enabled);
  if (! FPZERO(d_size.getX()) ||
      ! FPZERO(d_size.getY()) ||
      ! FPZERO(d_size.getZ()) )
    PRINT_FIELD(size);
      
  return os;
}

//
// Generate visibility events.
//
// This is in a render() method since the it needs to be computed
// with respect to the accumulated transformations above it in the
// scene graph. Move to update() when xforms are accumulated in Groups...
//

void VrmlNodeVisibilitySensor::render(Viewer *viewer, VrmlRenderContext rc)
{

  if (d_enabled.get())
    {
      VrmlSFTime timeNow( theSystem->time() );
      float xyz[2][3];

      // hack: enclose box in a sphere...
      xyz[0][0] = d_center.getX();
      xyz[0][1] = d_center.getY();
      xyz[0][2] = d_center.getZ();
      xyz[1][0] = d_center.getX() + d_size.getX();
      xyz[1][1] = d_center.getY() + d_size.getY();
      xyz[1][2] = d_center.getZ() + d_size.getZ();
      viewer->transformPoints( 2, &xyz[0][0] );
      float dx = xyz[1][0]-xyz[0][0];
      float dy = xyz[1][1]-xyz[0][1];
      float dz = xyz[1][2]-xyz[0][2];
      float r  = dx*dx + dy*dy + dz*dz;
      if (! FPZERO(r) ) r = sqrt( r );

      // Was the sphere visible last time through? How does this work
      // for USE'd nodes? I need a way for each USE to store whether
      // it was active.
      bool wasIn = d_isActive.get();

      // Is the sphere visible? ...
      bool inside = xyz[0][2] < 0.0; // && z > - scene->visLimit()
      if (inside)
	{
	  VrmlNodeNavigationInfo *ni = d_scene->bindableNavigationInfoTop();
	  if (ni &&
	      ! FPZERO(ni->visibilityLimit()) &&
	      xyz[0][2] < - ni->visibilityLimit())
	    inside = false;
	}

      // This bit assumes 90degree fieldOfView to get rid of trig calls...
      if (inside)
	inside = ( fabs(xyz[0][0]) < -0.5 * xyz[0][2] + r &&
		   fabs(xyz[0][1]) < -0.5 * xyz[0][2] + r );

      // Just became visible
      if (inside && ! wasIn)
	{
	  theSystem->debug("VS enter %g, %g, %g\n",
			xyz[0][0], xyz[0][1], xyz[0][2]);

	  d_isActive.set(true);
	  eventOut(timeNow.get(), "isActive", d_isActive);

	  d_enterTime = timeNow;
	  eventOut(timeNow.get(), "enterTime", d_enterTime);
	}

      // Check if viewer has left the box
      else if (wasIn && ! inside)
	{
	  theSystem->debug("VS exit %g, %g, %g\n",
			xyz[0][0], xyz[0][1], xyz[0][2]);

	  d_isActive.set(false);
	  eventOut(timeNow.get(), "isActive", d_isActive );

	  d_exitTime = timeNow;
	  eventOut(timeNow.get(), "exitTime", d_exitTime);
	}
    }

  else
    clearModified();
}

// Get the value of a field or eventOut.

const VrmlField *VrmlNodeVisibilitySensor::getField(const char *fieldName) const
{
  // exposedFields
  if ( strcmp( fieldName, "center" ) == 0 )
    return &d_center;
  else if ( strcmp( fieldName, "enabled" ) == 0 )
    return &d_enabled;
  else if ( strcmp( fieldName, "size" ) == 0 )
    return &d_size;

  // eventOuts
  else if ( strcmp( fieldName, "isActive" ) == 0 )
    return &d_isActive;  
  else if ( strcmp( fieldName, "enterTime" ) == 0 )
    return &d_enterTime;  
  else if ( strcmp( fieldName, "exitTime" ) == 0 )
    return &d_exitTime;  

  return VrmlNodeChild::getField( fieldName );
}


// Set the value of one of the node fields.

void VrmlNodeVisibilitySensor::setField(const char *fieldName,
					const VrmlField &fieldValue)
{
  if TRY_FIELD(center, SFVec3f)
  else if TRY_FIELD(enabled, SFBool)
  else if TRY_FIELD(size, SFVec3f)
  else
    VrmlNodeChild::setField(fieldName, fieldValue);
}

