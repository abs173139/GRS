#pragma once

#ifndef GRSPatchGregoryQuad20Pts_h
#define GRSPatchGregoryQuad20Pts_h

#include "GRSPatchGregoryQuad.h"
#include "GRSInternalTypes.h"

class GRSPatchGregoryQuad20Pts :public GRSPatchGregoryQuad
{
public:
  virtual ~GRSPatchGregoryQuad20Pts() {}
  virtual GRSRes DefinePatch(GRSPatchDefData& iData);
  virtual GRSRes PutToNURBS(GRSSurfNurbs& oNurbs);

  void SetVertexPoints(const GRSPointVector& iaPts) { m_aVtxPts = iaPts; }
  void SetEdgePoints(const GRSPointVector& iaPts) { m_aEdgePts = iaPts; }
  void SetFacePoints(const GRSPointVector& iaPts) { m_aFacePts = iaPts; }
  void PrintPatch();

  static void TestFillPatch20Pts(GRSPatchGregoryQuad20Pts& oPatch);

private:
  virtual void FillPoints(GRSPointsGrid& oaPoints);
  virtual void FillWeights(GRSDoubleGrid& oaWeights);
  virtual void FillKnots(GRSDoubleVector& oaKnots);

private:
  GRSPointVector m_aVtxPts;
  GRSPointVector m_aFacePts;
  GRSPointVector m_aEdgePts;
};

#endif // GRSPatchGregoryQuad20Pts_h

