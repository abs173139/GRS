#pragma once

#ifndef GRSPatchGregory_h
#define GRSPatchGregory_h

#include "GRSPatch.h"
#include "GRSInternalTypes.h"

class GRSPatchGregory : public GRSPatch 
{
public:
  virtual ~GRSPatchGregory() {}

private:
  virtual void FillPoints( GRSPointsGrid& oaPoints ) = 0;
  virtual void FillWeights( GRSDoubleGrid& oaWeights ) = 0;
  virtual void FillKnots( GRSDoubleVector& oaKnots ) = 0;
};

#endif // GRSPatchGregory_h

