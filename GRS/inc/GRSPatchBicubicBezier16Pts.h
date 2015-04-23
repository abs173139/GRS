#pragma once

#ifndef GRSPatchBicubicBezier16Pts_h
#define GRSPatchBicubicBezier16Pts_h

#include "GRSPatch.h"
#include "GRSInternalTypes.h"

class GRSPatchBicubicBezier16Pts : public GRSPatch 
{
public:
  void FillPointsGridFromMeshData( GRSPointVector& iV );
  virtual ~GRSPatchBicubicBezier16Pts() {}

  virtual GRSRes PutToNURBS(GRSSurfNurbs& oNurbs);
  virtual GRSRes DefinePatch(GRSPatchDefData& iData);

private:
  GRSPointsGrid m_controlPoints;
};

#endif // GRSPatchBicubicBezier16Pts_h
