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

#include <stack>

#include "VrmlNamespace.h"
#include "VrmlNodeType.h"
#include "VrmlNodeVisitor.h"
#include "VrmlNode.h"
#include "Route.h"
#include "System.h"
#include "VrmlNodeAnchor.h"
#include "VrmlNodeAppearance.h"
#include "VrmlNodeAudioClip.h"
#include "VrmlNodeBackground.h"
#include "VrmlNodeBillboard.h"
#include "VrmlNodeBox.h"
#include "VrmlNodeCollision.h"
#include "VrmlNodeColor.h"
#include "VrmlNodeColorInt.h"
#include "VrmlNodeCone.h"
#include "VrmlNodeCoordinate.h"
#include "VrmlNodeCoordinateInt.h"
#include "VrmlNodeCylinder.h"
#include "VrmlNodeCylinderSensor.h"
#include "VrmlNodeDirLight.h"
#include "VrmlNodeElevationGrid.h"
#include "VrmlNodeExtrusion.h"
#include "VrmlNodeFog.h"
#include "VrmlNodeFontStyle.h"
#include "VrmlNodeGroup.h"
#include "VrmlNodeIFaceSet.h"
#include "VrmlNodeILineSet.h"
#include "VrmlNodeImageTexture.h"
#include "VrmlNodeInline.h"
#include "VrmlNodeLOD.h"
#include "VrmlNodeMaterial.h"
#include "VrmlNodeMovieTexture.h"
#include "VrmlNodeNavigationInfo.h"
#include "VrmlNodeNormal.h"
#include "VrmlNodeNormalInt.h"
#include "VrmlNodeOrientationInt.h"
#include "VrmlNodePixelTexture.h"
#include "VrmlNodePlaneSensor.h"
#include "VrmlNodePointLight.h"
#include "VrmlNodePointSet.h"
#include "VrmlNodePositionInt.h"
#include "VrmlNodeProto.h"
#include "VrmlNodeProximitySensor.h"
#include "VrmlNodeScalarInt.h"
#include "VrmlNodeScript.h"
#include "VrmlNodeShape.h"
#include "VrmlNodeSound.h"
#include "VrmlNodeSphere.h"
#include "VrmlNodeSphereSensor.h"
#include "VrmlNodeSpotLight.h"
#include "VrmlNodeSwitch.h"
#include "VrmlNodeText.h"
#include "VrmlNodeTextureCoordinate.h"
#include "VrmlNodeTextureTransform.h"
#include "VrmlNodeTimeSensor.h"
#include "VrmlNodeTouchSensor.h"
#include "VrmlNodeTransform.h"
#include "VrmlNodeViewpoint.h"
#include "VrmlNodeVisibilitySensor.h"
#include "VrmlNodeWorldInfo.h"

#include <string.h>

# ifndef NDEBUG
#   include <typeinfo>
# endif

// This should at least be a sorted vector...
std::list< VrmlNodeType* > VrmlNamespace::builtInList;

// Ref count of namespaces so builtins can be freed
int VrmlNamespace::s_nNamespaces;

VrmlNamespace::VrmlNamespace( VrmlNamespace *parent ) :
  d_parent(parent)
{
  ++s_nNamespaces;

  // Initialize typeList with built in nodes
  if (builtInList.size() == 0) defineBuiltIns();
}

VrmlNamespace::~VrmlNamespace()
{
  // Free nameList
  std::list<VrmlNode*>::iterator n;
  for (n = d_nameList.begin(); n != d_nameList.end(); ++n)
    (*n)->dereference();
  
  // Free typeList
  std::list<VrmlNodeType*>::iterator i;
  for (i = d_typeList.begin(); i != d_typeList.end(); ++i)
    (*i)->dereference();

  // Free builtins
  if ( --s_nNamespaces == 0 )
    {
      for (i = builtInList.begin(); i != builtInList.end(); ++i)
	(*i)->dereference();
      builtInList.clear();
    }
}


//
//  Built in nodes.
//  This code replaces the reading of the "standardNodes.wrl" file
//  of empty PROTOs so I don't need to carry that file around.
//

void
VrmlNamespace::addBuiltIn( VrmlNodeType *type)
{
  builtInList.push_front( type->reference() );
}




void VrmlNamespace::defineBuiltIns()
{
  addBuiltIn( VrmlNodeAnchor::defineType() );
  addBuiltIn( VrmlNodeAppearance::defineType() );
  addBuiltIn( VrmlNodeAudioClip::defineType() );
  addBuiltIn( VrmlNodeBackground::defineType() );
  addBuiltIn( VrmlNodeBillboard::defineType() );
  addBuiltIn( VrmlNodeBox::defineType() );
  addBuiltIn( VrmlNodeCollision::defineType() );
  addBuiltIn( VrmlNodeColor::defineType() );
  addBuiltIn( VrmlNodeColorInt::defineType() );
  addBuiltIn( VrmlNodeCone::defineType() );
  addBuiltIn( VrmlNodeCoordinate::defineType() );
  addBuiltIn( VrmlNodeCoordinateInt::defineType() );
  addBuiltIn( VrmlNodeCylinder::defineType() );
  addBuiltIn( VrmlNodeCylinderSensor::defineType() );
  addBuiltIn( VrmlNodeDirLight::defineType() );
  addBuiltIn( VrmlNodeElevationGrid::defineType() );
  addBuiltIn( VrmlNodeExtrusion::defineType() );
  addBuiltIn( VrmlNodeFog::defineType() );
  addBuiltIn( VrmlNodeFontStyle::defineType() );
  addBuiltIn( VrmlNodeGroup::defineType() );
  addBuiltIn( VrmlNodeIFaceSet::defineType() );
  addBuiltIn( VrmlNodeILineSet::defineType() );
  addBuiltIn( VrmlNodeImageTexture::defineType() );
  addBuiltIn( VrmlNodeInline::defineType() );
  addBuiltIn( VrmlNodeLOD::defineType() );
  addBuiltIn( VrmlNodeMaterial::defineType() );
  addBuiltIn( VrmlNodeMovieTexture::defineType() );
  addBuiltIn( VrmlNodeNavigationInfo::defineType() );
  addBuiltIn( VrmlNodeNormal::defineType() );
  addBuiltIn( VrmlNodeNormalInt::defineType() );
  addBuiltIn( VrmlNodeOrientationInt::defineType() );
  addBuiltIn( VrmlNodePixelTexture::defineType() );
  addBuiltIn( VrmlNodePlaneSensor::defineType() );
  addBuiltIn( VrmlNodePointLight::defineType() );
  addBuiltIn( VrmlNodePointSet::defineType() );
  addBuiltIn( VrmlNodePositionInt::defineType() );
  addBuiltIn( VrmlNodeProximitySensor::defineType() );
  addBuiltIn( VrmlNodeScalarInt::defineType() );
  addBuiltIn( VrmlNodeScript::defineType() );
  addBuiltIn( VrmlNodeShape::defineType() );
  addBuiltIn( VrmlNodeSound::defineType() );
  addBuiltIn( VrmlNodeSphere::defineType() );
  addBuiltIn( VrmlNodeSphereSensor::defineType() );
  addBuiltIn( VrmlNodeSpotLight::defineType() );
  addBuiltIn( VrmlNodeSwitch::defineType() );
  addBuiltIn( VrmlNodeText::defineType() );
  addBuiltIn( VrmlNodeTextureCoordinate::defineType() );
  addBuiltIn( VrmlNodeTextureTransform::defineType() );
  addBuiltIn( VrmlNodeTimeSensor::defineType() );
  addBuiltIn( VrmlNodeTouchSensor::defineType() );
  addBuiltIn( VrmlNodeTransform::defineType() );
  addBuiltIn( VrmlNodeViewpoint::defineType() );
  addBuiltIn( VrmlNodeVisibilitySensor::defineType() );
  addBuiltIn( VrmlNodeWorldInfo::defineType() );
}


// A safer version for reading PROTOs from files.

void
VrmlNamespace::addNodeType( VrmlNodeType *type )
{
  if ( findType( type->getName() ) != NULL)
    theSystem->warn("PROTO %s already defined\n",
		    type->getName() );
  else
    d_typeList.push_front( type->reference() );
}


const VrmlNodeType *
VrmlNamespace::findType( const char *name )
{
  // Look through the PROTO stack:
  const VrmlNodeType *nt = findPROTO(name);
  if (nt) return nt;

  // Look in parent scope for the type
  if (d_parent)
    return d_parent->findType( name );

  // Look through the built ins
  std::list<VrmlNodeType*>::iterator i;
  for (i = builtInList.begin(); i != builtInList.end(); ++i)
    {
      nt = *i;
      if (nt != NULL && strcmp(nt->getName(),name) == 0)
	return nt;
    }

  return NULL;
}

const VrmlNodeType *    // LarryD
VrmlNamespace::findPROTO(const char *name)
{
  // Look through the PROTO list ONLY:
  std::list<VrmlNodeType*>::iterator i;
  for (i = d_typeList.begin(); i != d_typeList.end(); ++i)
    {
      const VrmlNodeType *nt = *i;
      if (nt != NULL && strcmp(nt->getName(),name) == 0)
	return nt;
    }
  return NULL;
}


const VrmlNodeType *
VrmlNamespace::firstType()
{
  // Top of the PROTO stack (should make sure it has an implementation...)
  if (d_typeList.size() > 0)
    return d_typeList.front()->reference();
  return NULL;
}

void
VrmlNamespace::addNodeName( VrmlNode *namedNode )
{
  // We could remove any existing node with this name, but
  // since we are just pushing this one onto the front of
  // the list, the other name won't be found. If we do
  // something smart with this list (like sorting), this
  // will need to change.
  d_nameList.push_front( namedNode->reference() );
}

void
VrmlNamespace::removeNodeName( VrmlNode *namedNode )
{
  d_nameList.remove( namedNode );
  namedNode->dereference();
}


VrmlNode * VrmlNamespace::findNode( const char *name ) const
{
    for (std::list<VrmlNode*>::const_iterator n = d_nameList.begin();
         n != d_nameList.end(); ++n) {
        if (strcmp((*n)->name(), name) == 0) {
            return *n;
        }
    }
    
    return 0;
}

const VrmlMFNode VrmlNamespace::cloneNodes(const VrmlMFNode & mfnode) {
    
    class NodeCloneVisitor : public VrmlNodeVisitor {
    public:
        NodeCloneVisitor(VrmlNamespace & ns): ns(ns) {}
        
        virtual ~NodeCloneVisitor() {}
        
        const VrmlMFNode clone(const VrmlMFNode & mfnode) {
            VrmlMFNode clonedNodes(this->visitChildren(mfnode));
            assert(this->rootNodeStack.size() == 0);
            
            for (size_t i = 0; i < mfnode.getLength(); ++i) {
                mfnode[i]->resetVisitedFlag();
            }
            
            return clonedNodes;
        }
        
        virtual void visit(VrmlNodeAnchor & node) {
            VrmlNodeAnchor * const clonedNode = new VrmlNodeAnchor(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setChildren(this->visitChildren(node.getChildren()));
        }
        
        virtual void visit(VrmlNodeAppearance & node) {
            VrmlNodeAppearance * const clonedNode =
                    new VrmlNodeAppearance(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getMaterial().get()) {
                this->visitNode(*node.getMaterial().get());
                assert(dynamic_cast<VrmlNodeMaterial *>
                        (this->rootNodeStack.top()));
                clonedNode->setMaterial(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getTexture().get()) {
                this->visitNode(*node.getTexture().get());
                assert(dynamic_cast<VrmlNodeTexture *>
                        (this->rootNodeStack.top()));
                clonedNode->setTexture(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getTextureTransform().get()) {
                this->visitNode(*node.getTextureTransform().get());
                assert(dynamic_cast<VrmlNodeTextureTransform *>
                        (this->rootNodeStack.top()));
                clonedNode->setTextureTransform(
                        VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeAudioClip & node) {
            this->rootNodeStack.push(new VrmlNodeAudioClip(node));
        }
        
        virtual void visit(VrmlNodeBackground & node) {
            this->rootNodeStack.push(new VrmlNodeBackground(node));
        }
        
        virtual void visit(VrmlNodeBillboard & node) {
            VrmlNodeBillboard * const clonedNode = new VrmlNodeBillboard(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setChildren(this->visitChildren(node.getChildren()));
        }
        
        virtual void visit(VrmlNodeBox & node) {
            this->rootNodeStack.push(new VrmlNodeBox(node));
        }
        
        virtual void visit(VrmlNodeCollision & node) {
            VrmlNodeCollision * const clonedNode = new VrmlNodeCollision(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setChildren(this->visitChildren(node.getChildren()));
            if (node.getProxy().get()) {
                this->visitNode(*node.getProxy().get());
                assert(dynamic_cast<VrmlNodeChild *>
                        (this->rootNodeStack.top()));
                clonedNode->setProxy(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeColor & node) {
            this->rootNodeStack.push(new VrmlNodeColor(node));
        }
        
        virtual void visit(VrmlNodeColorInt & node) {
            this->rootNodeStack.push(new VrmlNodeColorInt(node));
        }
        
        virtual void visit(VrmlNodeCone & node) {
            this->rootNodeStack.push(new VrmlNodeCone(node));
        }
        
        virtual void visit(VrmlNodeCoordinate & node) {
            this->rootNodeStack.push(new VrmlNodeCoordinate(node));
        }
        
        virtual void visit(VrmlNodeCoordinateInt & node) {
            this->rootNodeStack.push(new VrmlNodeCoordinateInt(node));
        }
        
        virtual void visit(VrmlNodeCylinder & node) {
            this->rootNodeStack.push(new VrmlNodeCylinder(node));
        }
        
        virtual void visit(VrmlNodeCylinderSensor & node) {
            this->rootNodeStack.push(new VrmlNodeCylinderSensor(node));
        }
        
        virtual void visit(VrmlNodeDirLight & node) {
            this->rootNodeStack.push(new VrmlNodeDirLight(node));
        }
        
        virtual void visit(VrmlNodeElevationGrid & node) {
            VrmlNodeElevationGrid * const clonedNode =
                    new VrmlNodeElevationGrid(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getColor().get()) {
                this->visitNode(*node.getColor().get());
                assert(dynamic_cast<VrmlNodeColor *>
                        (this->rootNodeStack.top()));
                clonedNode->setColor(VrmlSFNode(VrmlSFNode(this->rootNodeStack.top())));
                this->rootNodeStack.pop();
            }
            
            if (node.getNormal().get()) {
                this->visitNode(*node.getNormal().get());
                assert(dynamic_cast<VrmlNodeNormal *>
                        (this->rootNodeStack.top()));
                clonedNode->setNormal(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getTexCoord().get()) {
                this->visitNode(*node.getTexCoord().get());
                assert(dynamic_cast<VrmlNodeTextureCoordinate *>
                        (this->rootNodeStack.top()));
                clonedNode->setTexCoord(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeExtrusion & node) {
            this->rootNodeStack.push(new VrmlNodeExtrusion(node));
        }
        
        virtual void visit(VrmlNodeFog & node) {
            this->rootNodeStack.push(new VrmlNodeFog(node));
        }
        
        virtual void visit(VrmlNodeFontStyle & node) {
            this->rootNodeStack.push(new VrmlNodeFontStyle(node));
        }
        
        virtual void visit(VrmlNodeGroup & node) {
            VrmlNodeGroup * const clonedNode = new VrmlNodeGroup(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setChildren(this->visitChildren(node.getChildren()));
        }
        
        virtual void visit(VrmlNodeIFaceSet & node) {
            VrmlNodeIFaceSet * const clonedNode = new VrmlNodeIFaceSet(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getColor().get()) {
                this->visitNode(*node.getColor().get());
                assert(dynamic_cast<VrmlNodeColor *>
                        (this->rootNodeStack.top()));
                clonedNode->setColor(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getCoord().get()) {
                this->visitNode(*node.getCoord().get());
                assert(dynamic_cast<VrmlNodeCoordinate *>
                        (this->rootNodeStack.top()));
                clonedNode->setCoord(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getNormal().get()) {
                this->visitNode(*node.getNormal().get());
                assert(dynamic_cast<VrmlNodeNormal *>
                        (this->rootNodeStack.top()));
                clonedNode->setNormal(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getTexCoord().get()) {
                this->visitNode(*node.getTexCoord().get());
                assert(dynamic_cast<VrmlNodeTextureCoordinate *>
                        (this->rootNodeStack.top()));
                clonedNode->setTexCoord(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeILineSet & node) {
            VrmlNodeILineSet * const clonedNode = new VrmlNodeILineSet(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getColor().get()) {
                this->visitNode(*node.getColor().get());
                assert(dynamic_cast<VrmlNodeColor *>
                        (this->rootNodeStack.top()));
                clonedNode->setColor(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getCoord().get()) {
                this->visitNode(*node.getCoord().get());
                assert(dynamic_cast<VrmlNodeCoordinate *>
                        (this->rootNodeStack.top()));
                clonedNode->setCoord(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeImageTexture & node) {
            this->rootNodeStack.push(new VrmlNodeImageTexture(node));
        }
        
        virtual void visit(VrmlNodeInline & node) {
            this->rootNodeStack.push(new VrmlNodeInline(node));
        }
        
        virtual void visit(VrmlNodeLOD & node) {
            VrmlNodeLOD * const clonedNode = new VrmlNodeLOD(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setLevel(this->visitChildren(node.getLevel()));
        }
        
        virtual void visit(VrmlNodeMaterial & node) {
            this->rootNodeStack.push(new VrmlNodeMaterial(node));
        }
        
        virtual void visit(VrmlNodeMovieTexture & node) {
            this->rootNodeStack.push(new VrmlNodeMovieTexture(node));
        }
        
        virtual void visit(VrmlNodeNavigationInfo & node) {
            this->rootNodeStack.push(new VrmlNodeNavigationInfo(node));
        }
        
        virtual void visit(VrmlNodeNormal & node) {
            this->rootNodeStack.push(new VrmlNodeNormal(node));
        }
        
        virtual void visit(VrmlNodeNormalInt & node) {
            this->rootNodeStack.push(new VrmlNodeNormalInt(node));
        }
        
        virtual void visit(VrmlNodeOrientationInt & node) {
            this->rootNodeStack.push(new VrmlNodeOrientationInt(node));
        }
        
        virtual void visit(VrmlNodePixelTexture & node) {
            this->rootNodeStack.push(new VrmlNodePixelTexture(node));
        }
        
        virtual void visit(VrmlNodePlaneSensor & node) {
            this->rootNodeStack.push(new VrmlNodePlaneSensor(node));
        }
        
        virtual void visit(VrmlNodePointLight & node) {
            this->rootNodeStack.push(new VrmlNodePointLight(node));
        }
        
        virtual void visit(VrmlNodePointSet & node) {
            VrmlNodePointSet * const clonedNode = new VrmlNodePointSet(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getColor().get()) {
                this->visitNode(*node.getColor().get());
                assert(dynamic_cast<VrmlNodeColor *>
                        (this->rootNodeStack.top()));
                clonedNode->setColor(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getCoord().get()) {
                this->visitNode(*node.getCoord().get());
                assert(dynamic_cast<VrmlNodeCoordinate *>
                        (this->rootNodeStack.top()));
                clonedNode->setCoord(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodePositionInt & node) {
            this->rootNodeStack.push(new VrmlNodePositionInt(node));
        }
        
        virtual void visit(VrmlNodeProto & node) {
            VrmlNodeProto * const clonedNode = new VrmlNodeProto(node);
            clonedNode->addToScene(node.scene(), clonedNode->nodeType().url());
            this->rootNodeStack.push(clonedNode);
        }
        
        virtual void visit(VrmlNodeProximitySensor & node) {
            this->rootNodeStack.push(new VrmlNodeProximitySensor(node));
        }
        
        virtual void visit(VrmlNodeScalarInt & node) {
            this->rootNodeStack.push(new VrmlNodeScalarInt(node));
        }
        
        virtual void visit(VrmlNodeScript & node) {
            VrmlNodeScript * const clonedNode = new VrmlNodeScript(node);
            this->rootNodeStack.push(clonedNode);
            for (VrmlNodeScript::FieldList::const_iterator 
                    i = node.fields().begin(), j = clonedNode->fields().begin();
                    i != node.fields().end(); ++i, ++j) {
                assert((*i)->value);
                if ((*i)->type == VrmlField::SFNODE) {
                    assert(dynamic_cast<VrmlSFNode *>((*i)->value));
                    if (static_cast<VrmlSFNode *>((*i)->value)->get()) {
                        visitNode(*static_cast<VrmlSFNode *>((*i)->value)->get());
                        static_cast<VrmlSFNode *>((*j)->value)
                                ->set(this->rootNodeStack.top());
                        this->rootNodeStack.pop();
                    }
                } else if ((*i)->type == VrmlField::MFNODE) {
                    assert(dynamic_cast<VrmlMFNode *>((*i)->value));
                    static_cast<VrmlMFNode &>(*(*j)->value) =
                        visitChildren(static_cast<VrmlMFNode &>(*(*i)->value));
                }
            }
        }
        
        virtual void visit(VrmlNodeShape & node) {
            VrmlNodeShape * const clonedNode = new VrmlNodeShape(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getAppearance().get()) {
                this->visitNode(*node.getAppearance().get());
                assert(dynamic_cast<VrmlNodeAppearance *>
                        (this->rootNodeStack.top()));
                clonedNode->setAppearance(
                        VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
            
            if (node.getGeometry().get()) {
                this->visitNode(*node.getGeometry().get());
                assert(dynamic_cast<VrmlNodeGeometry *>
                        (this->rootNodeStack.top()));
                clonedNode->setGeometry(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeSound & node) {
            VrmlNodeSound * const clonedNode = new VrmlNodeSound(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getSource().get()) {
                this->visitNode(*node.getSource().get());
                assert(dynamic_cast<VrmlNodeAudioClip *>
                        (this->rootNodeStack.top()));
                clonedNode->setSource(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeSphere & node) {
            this->rootNodeStack.push(new VrmlNodeSphere(node));
        }
        
        virtual void visit(VrmlNodeSphereSensor & node) {
            this->rootNodeStack.push(new VrmlNodeSphereSensor(node));
        }
        
        virtual void visit(VrmlNodeSpotLight & node) {
            this->rootNodeStack.push(new VrmlNodeSpotLight(node));
        }
        
        virtual void visit(VrmlNodeSwitch & node) {
            VrmlNodeSwitch * const clonedNode = new VrmlNodeSwitch(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setChoice(this->visitChildren(node.getChoice()));
        }
        
        virtual void visit(VrmlNodeText & node) {
            VrmlNodeText * const clonedNode = new VrmlNodeText(node);
            this->rootNodeStack.push(clonedNode);
            
            if (node.getFontStyle().get()) {
                this->visitNode(*node.getFontStyle().get());
                assert(dynamic_cast<VrmlNodeFontStyle *>
                        (this->rootNodeStack.top()));
                clonedNode->setFontStyle(VrmlSFNode(this->rootNodeStack.top()));
                this->rootNodeStack.pop();
            }
        }
        
        virtual void visit(VrmlNodeTextureCoordinate & node) {
            this->rootNodeStack.push(new VrmlNodeTextureCoordinate(node));
        }
        
        virtual void visit(VrmlNodeTextureTransform & node) {
            this->rootNodeStack.push(new VrmlNodeTextureTransform(node));
        }
        
        virtual void visit(VrmlNodeTimeSensor & node) {
            this->rootNodeStack.push(new VrmlNodeTimeSensor(node));
        }
        
        virtual void visit(VrmlNodeTouchSensor & node) {
            this->rootNodeStack.push(new VrmlNodeTouchSensor(node));
        }
        
        virtual void visit(VrmlNodeTransform & node) {
            VrmlNodeTransform * const clonedNode = new VrmlNodeTransform(node);
            this->rootNodeStack.push(clonedNode);
            clonedNode->setChildren(this->visitChildren(node.getChildren()));
        }
        
        virtual void visit(VrmlNodeViewpoint & node) {
            this->rootNodeStack.push(new VrmlNodeViewpoint(node));
        }
        
        virtual void visit(VrmlNodeVisibilitySensor & node) {
            this->rootNodeStack.push(new VrmlNodeVisibilitySensor(node));
        }
        
        virtual void visit(VrmlNodeWorldInfo & node) {
            this->rootNodeStack.push(new VrmlNodeWorldInfo(node));
        }
        
    private:
        //
        // Not copyable.
        //
        NodeCloneVisitor(const NodeCloneVisitor &);
        NodeCloneVisitor & operator=(const NodeCloneVisitor &);
        
        const VrmlMFNode visitChildren(const VrmlMFNode & children) {
            VrmlMFNode clonedChildren(children.getLength());
            for (size_t i = 0; i < clonedChildren.getLength(); ++i) {
                if (children[i]) {
                    this->visitNode(*children[i]);
                    assert(this->rootNodeStack.top());
                    clonedChildren[i] = this->rootNodeStack.top()->reference();
                    this->rootNodeStack.pop();
                }
            }
            return clonedChildren;
        }
        
        void visitNode(VrmlNode & node) {
            if (node.accept(*this)) {
                assert(this->rootNodeStack.size() > 0);
                assert(typeid(node) == typeid(*this->rootNodeStack.top()));
                const char * const name = this->rootNodeStack.top()->name();
                if (*this->rootNodeStack.top()->name()) {
                    this->ns.addNodeName(this->rootNodeStack.top());
                }
            } else {
                assert(this->ns.findNode(node.name()));
                this->rootNodeStack.push(this->ns.findNode(node.name()));
            }
        }
        
        VrmlNamespace & ns;
        std::stack<VrmlNode *> rootNodeStack;
    };
    
    class NodeRouteCopyVisitor : public VrmlNodeVisitor {
    public:
        NodeRouteCopyVisitor(VrmlNamespace & ns): ns(ns) {}
        
        virtual ~NodeRouteCopyVisitor() {}
        
        void copyRoutes(const VrmlMFNode & mfnode) {
            this->visitChildren(mfnode);
            
            for (size_t i = 0; i < mfnode.getLength(); ++i) {
                mfnode[i]->resetVisitedFlag();
            }
        }
        
        virtual void visit(VrmlNodeAnchor & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getChildren());
        }
        
        virtual void visit(VrmlNodeAppearance & node) {
            this->copyRoutesFromNode(node);
            if (node.getMaterial().get()) {
                node.getMaterial().get()->accept(*this);
            }
            if (node.getTexture().get()) {
                node.getTexture().get()->accept(*this);
            }
            if (node.getTextureTransform().get()) {
                node.getTextureTransform().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeAudioClip & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeBackground & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeBillboard & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getChildren());
        }
        
        virtual void visit(VrmlNodeBox & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeCollision & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getChildren());
        }
        
        virtual void visit(VrmlNodeColor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeColorInt & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeCone & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeCoordinate & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeCoordinateInt & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeCylinder & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeCylinderSensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeDirLight & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeElevationGrid & node) {
            this->copyRoutesFromNode(node);
            if (node.getColor().get()) {
                node.getColor().get()->accept(*this);
            }
            if (node.getNormal().get()) {
                node.getNormal().get()->accept(*this);
            }
            if (node.getTexCoord().get()) {
                node.getTexCoord().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeExtrusion & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeFog & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeFontStyle & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeGroup & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getChildren());
        }
        
        virtual void visit(VrmlNodeIFaceSet & node) {
            this->copyRoutesFromNode(node);
            if (node.getColor().get()) {
                node.getColor().get()->accept(*this);
            }
            if (node.getCoord().get()) {
                node.getCoord().get()->accept(*this);
            }
            if (node.getNormal().get()) {
                node.getNormal().get()->accept(*this);
            }
            if (node.getTexCoord().get()) {
                node.getTexCoord().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeILineSet & node) {
            this->copyRoutesFromNode(node);
            if (node.getColor().get()) {
                node.getColor().get()->accept(*this);
            }
            if (node.getCoord().get()) {
                node.getCoord().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeImageTexture & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeInline & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeLOD & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getLevel());
        }
        
        virtual void visit(VrmlNodeMaterial & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeMovieTexture & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeNavigationInfo & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeNormal & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeNormalInt & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeOrientationInt & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodePixelTexture & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodePlaneSensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodePointLight & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodePointSet & node) {
            this->copyRoutesFromNode(node);
            if (node.getColor().get()) {
                node.getColor().get()->accept(*this);
            }
            if (node.getCoord().get()) {
                node.getCoord().get()->accept(*this);
            }
       }
        
        virtual void visit(VrmlNodePositionInt & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeProto & node) {
            this->copyRoutesFromNode(node);
            //
            // What about the fields of a PROTO'd node?
            //
        }
        
        virtual void visit(VrmlNodeProximitySensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeScalarInt & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeScript & node) {
            this->copyRoutesFromNode(node);
            for (VrmlNodeScript::FieldList::const_iterator
                    i = node.fields().begin(); i != node.fields().end(); ++i) {
                assert((*i)->value);
                if ((*i)->type == VrmlField::SFNODE) {
                    assert(dynamic_cast<VrmlSFNode *>((*i)->value));
                    if (static_cast<VrmlSFNode *>((*i)->value)->get()) {
                        static_cast<VrmlSFNode *>((*i)->value)->get()
                                ->accept(*this);
                    }
                } else if ((*i)->type == VrmlField::MFNODE) {
                    assert(dynamic_cast<VrmlMFNode *>((*i)->value));
                    this->visitChildren(static_cast<VrmlMFNode &>(*(*i)->value));
                }
            }
        }
        
        virtual void visit(VrmlNodeShape & node) {
            this->copyRoutesFromNode(node);
            if (node.getAppearance().get()) {
                node.getAppearance().get()->accept(*this);
            }
            if (node.getGeometry().get()) {
                node.getGeometry().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeSound & node) {
            this->copyRoutesFromNode(node);
            if (node.getSource().get()) {
                node.getSource().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeSphere & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeSphereSensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeSpotLight & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeSwitch & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getChoice());
        }
        
        virtual void visit(VrmlNodeText & node) {
            this->copyRoutesFromNode(node);
            if (node.getFontStyle().get()) {
                node.getFontStyle().get()->accept(*this);
            }
        }
        
        virtual void visit(VrmlNodeTextureCoordinate & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeTextureTransform & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeTimeSensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeTouchSensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeTransform & node) {
            this->copyRoutesFromNode(node);
            this->visitChildren(node.getChildren());
        }
        
        virtual void visit(VrmlNodeViewpoint & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeVisibilitySensor & node) {
            this->copyRoutesFromNode(node);
        }
        
        virtual void visit(VrmlNodeWorldInfo & node) {
            this->copyRoutesFromNode(node);
        }
        
    private:
        //
        // Not copyable.
        //
        NodeRouteCopyVisitor(const NodeRouteCopyVisitor &);
        NodeRouteCopyVisitor & operator=(const NodeRouteCopyVisitor &);
        
        void copyRoutesFromNode(VrmlNode & node) {
            const char * fromName = 0;
            if (*(fromName = node.name())) {
                VrmlNode * const fromNode = this->ns.findNode(fromName);
                assert(fromNode);
                for (Route * route = node.getRoutes(); route;
                        route = route->next()) {
                    const char * toName = route->toNode()->name();
                    assert(this->ns.findNode(toName));
                    fromNode->addRoute(route->fromEventOut(),
                            this->ns.findNode(toName), route->toEventIn());
                }
            }
        }
        
        void visitChildren(const VrmlMFNode & children) {
            for (size_t i = 0; i < children.getLength(); ++i) {
                if (children[i]) {
                    children[i]->accept(*this);
                }
            }
        }
        
        VrmlNamespace & ns;
    };
    
    VrmlMFNode clonedNodes(NodeCloneVisitor(*this).clone(mfnode));
    NodeRouteCopyVisitor(*this).copyRoutes(mfnode);
    
    return clonedNodes;
}
