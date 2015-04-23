#pragma once

#ifndef GRSPatch_h
#define GRSPatch_h

#include "GRSRes.h"

class GRSSurfNurbs;
struct GRSPatchDefData;

class GRSPatch 
{
public:
  virtual ~GRSPatch() {}

  virtual GRSRes PutToNURBS( GRSSurfNurbs& oNurbs ) = 0;
  virtual GRSRes DefinePatch( GRSPatchDefData& iData ) = 0;
};

#endif // GRSPatch_h

