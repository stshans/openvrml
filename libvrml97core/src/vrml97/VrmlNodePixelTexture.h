//
//  Vrml 97 library
//  Copyright (C) 1998 Chris Morley
//
//  VrmlNodePixelTexture.h

#ifndef VRMLNODEPIXELTEXTURE_H
#define VRMLNODEPIXELTEXTURE_H

#include "VrmlNodeTexture.h"
#include "VrmlSFImage.h"
#include "VrmlSFBool.h"
#include "Viewer.h"

class VrmlNodePixelTexture : public VrmlNodeTexture {

public:

  // Define the fields of PixelTexture nodes
  static VrmlNodeType *defineType(VrmlNodeType *t = 0);
  virtual VrmlNodeType & nodeType() const;

  VrmlNodePixelTexture(VrmlScene *);
  virtual ~VrmlNodePixelTexture();

  virtual VrmlNode *cloneMe() const;

  virtual ostream& printFields(ostream& os, int indent);

  virtual void render(Viewer *);

  virtual const VrmlField *getField(const char *fieldName) const;
  virtual void setField(const char *fieldName, const VrmlField &fieldValue);

  virtual int nComponents();
  virtual int width();
  virtual int height();
  virtual int nFrames();
  virtual unsigned char* pixels();

  virtual VrmlNodePixelTexture*	toPixelTexture() const;

  virtual bool getRepeatS(){ return d_repeatS.get(); }
  virtual bool getRepeatT(){ return d_repeatT.get(); } 

private:

  VrmlSFImage d_image;
  VrmlSFBool d_repeatS;
  VrmlSFBool d_repeatT;

  Viewer::TextureObject d_texObject;
};

#endif
