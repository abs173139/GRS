#pragma once

#ifndef GRSPatchGregoryTriangle15Pts_h
#define GRSPatchGregoryTriangle15Pts_h

#include "GRSPatchGregoryTriangle.h"
#include "GRSInternalTypes.h"

class GRSPatchGregoryTriangle15Pts :public GRSPatchGregoryTriangle
{
public:
  virtual GRSRes PutToNURBS(GRSSurfNurbs& oNurbs);
  virtual GRSRes DefinePatch(GRSPatchDefData& iData);
  virtual ~GRSPatchGregoryTriangle15Pts() {}
  
  void SetVertexPoints(const GRSPointVector& iaPts) { m_aVtxPts = iaPts; }
  void SetEdgePoints(const GRSPointVector& iaPts) { m_aEdgePts = iaPts; }
  void SetFacePoints(const GRSPointVector& iaPts) { m_aFacePts = iaPts; }

  static void TestFillPatch15Pts(GRSPatchGregoryTriangle15Pts& oPatch);

private:
  virtual void FillPoints(GRSPointsGrid& oaPoints);
  virtual void FillWeights(GRSDoubleGrid& oaWeights);
  virtual void FillKnots(GRSDoubleVector& oaKnots);

private:
  GRSPointVector m_aVtxPts;
  GRSPointVector m_aFacePts;
  GRSPointVector m_aEdgePts;
};

#endif // GRSPatchGregoryTriangle15Pts_h