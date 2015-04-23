#include "GRSStdAfx.h"
#include "GRSPatchGregoryTriangle15Pts.h"

#include "GRSSurfNurbs.h"
#include "GRSLimitLoop.h"

GRSRes GRSPatchGregoryTriangle15Pts::PutToNURBS( GRSSurfNurbs& oNurbs )
{
  if ( m_aVtxPts.size() != 3 || m_aEdgePts.size() != 6 || m_aFacePts.size() != 6 )
    return GRSRes_IncorrectInput;

  GRSPointsGrid points;
  FillPoints(points);

  GRSDoubleGrid weights;
  FillWeights(weights);

  GRSDoubleVector knots;
  FillKnots(knots);

  oNurbs.Set(8, 8, points, weights, knots, knots);

  return GRSRes_Ok;
}

void GRSPatchGregoryTriangle15Pts::FillPoints( GRSPointsGrid& oaPoints )
{
  oaPoints.SetSize(8, 8);

  oaPoints(0, 0) = m_aVtxPts[2]; /* any point */

  oaPoints(0, 1) = m_aVtxPts[2];

  oaPoints(0, 2) = (3*m_aEdgePts[4])/5. + (2*m_aVtxPts[2])/5.;

  oaPoints(0, 3) = (3*m_aEdgePts[3])/10. + (3*m_aEdgePts[4])/5. + m_aVtxPts[2]/10.;

  oaPoints(0, 4) = (3*m_aEdgePts[3])/5. + (3*m_aEdgePts[4])/10. + m_aVtxPts[1]/10.;

  oaPoints(0, 5) = (3*m_aEdgePts[3])/5. + (2*m_aVtxPts[1])/5.;

  oaPoints(0, 6) = m_aVtxPts[1];

  oaPoints(0, 7) = m_aVtxPts[2]; /* any point */

  oaPoints(1, 0) = m_aVtxPts[2];

  oaPoints(1, 1) = (3*m_aEdgePts[4])/11. + (3*m_aEdgePts[5])/11. + (5*m_aVtxPts[2])/11.;

  oaPoints(1, 2) = (3*m_aEdgePts[3])/41. + (12*m_aEdgePts[4])/41. + (6*m_aEdgePts[5])/41. + (12*m_aFacePts[4])/41. + (8*m_aVtxPts[2])/41.;

  oaPoints(1, 3) = (4*m_aEdgePts[3])/25. + (6*m_aEdgePts[4])/25. + m_aEdgePts[5]/25. + (4*m_aFacePts[3])/25. + (8*m_aFacePts[4])/25. + m_aVtxPts[1]/75. + m_aVtxPts[2]/15.;

  oaPoints(1, 4) = m_aEdgePts[2]/25. + (6*m_aEdgePts[3])/25. + (4*m_aEdgePts[4])/25. + (8*m_aFacePts[3])/25. + (4*m_aFacePts[4])/25. + m_aVtxPts[1]/15. + m_aVtxPts[2]/75.;

  oaPoints(1, 5) = (6*m_aEdgePts[2])/41. + (12*m_aEdgePts[3])/41. + (3*m_aEdgePts[4])/41. + (12*m_aFacePts[3])/41. + (8*m_aVtxPts[1])/41.;

  oaPoints(1, 6) = (3*m_aEdgePts[2])/11. + (3*m_aEdgePts[3])/11. + (5*m_aVtxPts[1])/11.;

  oaPoints(1, 7) = m_aVtxPts[1];

  oaPoints(2, 0) = (3*m_aEdgePts[5])/5. + (2*m_aVtxPts[2])/5.;

  oaPoints(2, 1) = (3*m_aEdgePts[0])/41. + (3*m_aEdgePts[4])/41. + (15*m_aEdgePts[5])/41. + (12*m_aFacePts[5])/41. + (8*m_aVtxPts[2])/41.;

  oaPoints(2, 2) = m_aEdgePts[0]/15. + m_aEdgePts[3]/45. + (4*m_aEdgePts[4])/45. + m_aEdgePts[5]/5. + (4*m_aFacePts[0])/45. + (4*m_aFacePts[3])/45. + (4*m_aFacePts[4])/45. + (4*m_aFacePts[5])/15. + (4*m_aVtxPts[2])/45.;

  oaPoints(2, 3) = (9*m_aEdgePts[0])/235. + (3*m_aEdgePts[1])/235. + (6*m_aEdgePts[2])/235. + (12*m_aEdgePts[3])/235. + (18*m_aEdgePts[4])/235. + (21*m_aEdgePts[5])/235. + (24*m_aFacePts[0])/235. + (12*m_aFacePts[1])/235. + (12*m_aFacePts[2])/235. + (36*m_aFacePts[3])/235. + (36*m_aFacePts[4])/235. + (36*m_aFacePts[5])/235. + (2*m_aVtxPts[1])/235. + (8*m_aVtxPts[2])/235.;

  oaPoints(2, 4) = (3*m_aEdgePts[0])/235. + (9*m_aEdgePts[1])/235. + (21*m_aEdgePts[2])/235. + (18*m_aEdgePts[3])/235. + (12*m_aEdgePts[4])/235. + (6*m_aEdgePts[5])/235. + (12*m_aFacePts[0])/235. + (24*m_aFacePts[1])/235. + (36*m_aFacePts[2])/235. + (36*m_aFacePts[3])/235. + (36*m_aFacePts[4])/235. + (12*m_aFacePts[5])/235. + (8*m_aVtxPts[1])/235. + (2*m_aVtxPts[2])/235.;

  oaPoints(2, 5) = m_aEdgePts[1]/15. + m_aEdgePts[2]/5. + (4*m_aEdgePts[3])/45. + m_aEdgePts[4]/45. + (4*m_aFacePts[1])/45. + (4*m_aFacePts[2])/15. + (4*m_aFacePts[3])/45. + (4*m_aFacePts[4])/45. + (4*m_aVtxPts[1])/45.;

  oaPoints(2, 6) = (3*m_aEdgePts[1])/41. + (15*m_aEdgePts[2])/41. + (3*m_aEdgePts[3])/41. + (12*m_aFacePts[2])/41. + (8*m_aVtxPts[1])/41.;

  oaPoints(2, 7) = (3*m_aEdgePts[2])/5. + (2*m_aVtxPts[1])/5.;

  oaPoints(3, 0) = (3*m_aEdgePts[0])/10. + (3*m_aEdgePts[5])/5. + m_aVtxPts[2]/10.;

  oaPoints(3, 1) = (9*m_aEdgePts[0])/37. + (27*m_aEdgePts[5])/74. + (6*m_aFacePts[0])/37. + (6*m_aFacePts[5])/37. + m_aVtxPts[0]/74. + (2*m_aVtxPts[2])/37.;

  oaPoints(3, 2) = (21*m_aEdgePts[0])/115. + (3*m_aEdgePts[1])/115. + (3*m_aEdgePts[2])/230. + (24*m_aEdgePts[5])/115. + (24*m_aFacePts[0])/115. + (6*m_aFacePts[1])/115. + (6*m_aFacePts[2])/115. + (24*m_aFacePts[5])/115. + m_aVtxPts[0]/46. + (3*m_aVtxPts[2])/115.;

  oaPoints(3, 3) = (8*m_aEdgePts[0])/65. + (9*m_aEdgePts[1])/130. + (3*m_aEdgePts[2])/65. + (7*m_aEdgePts[5])/65. + (12*m_aFacePts[0])/65. + (8*m_aFacePts[1])/65. + (8*m_aFacePts[2])/65. + (12*m_aFacePts[5])/65. + m_aVtxPts[0]/39. + m_aVtxPts[1]/390. + (2*m_aVtxPts[2])/195.;

  oaPoints(3, 4) = (9*m_aEdgePts[0])/130. + (8*m_aEdgePts[1])/65. + (7*m_aEdgePts[2])/65. + (3*m_aEdgePts[5])/65. + (8*m_aFacePts[0])/65. + (12*m_aFacePts[1])/65. + (12*m_aFacePts[2])/65. + (8*m_aFacePts[5])/65. + m_aVtxPts[0]/39. + (2*m_aVtxPts[1])/195. + m_aVtxPts[2]/390.;

  oaPoints(3, 5) = (3*m_aEdgePts[0])/115. + (21*m_aEdgePts[1])/115. + (24*m_aEdgePts[2])/115. + (3*m_aEdgePts[5])/230. + (6*m_aFacePts[0])/115. + (24*m_aFacePts[1])/115. + (24*m_aFacePts[2])/115. + (6*m_aFacePts[5])/115. + m_aVtxPts[0]/46. + (3*m_aVtxPts[1])/115.;

  oaPoints(3, 6) = (9*m_aEdgePts[1])/37. + (27*m_aEdgePts[2])/74. + (6*m_aFacePts[1])/37. + (6*m_aFacePts[2])/37. + m_aVtxPts[0]/74. + (2*m_aVtxPts[1])/37.;

  oaPoints(3, 7) = (3*m_aEdgePts[1])/10. + (3*m_aEdgePts[2])/5. + m_aVtxPts[1]/10.;

  oaPoints(4, 0) = (3*m_aEdgePts[0])/5. + (3*m_aEdgePts[5])/10. + m_aVtxPts[0]/10.;

  oaPoints(4, 1) = (33*m_aEdgePts[0])/71. + (3*m_aEdgePts[1])/71. + (15*m_aEdgePts[5])/71. + (12*m_aFacePts[0])/71. + (8*m_aVtxPts[0])/71.;

  oaPoints(4, 2) = (15*m_aEdgePts[0])/43. + (21*m_aEdgePts[1])/215. + (3*m_aEdgePts[2])/215. + (6*m_aEdgePts[5])/43. + (48*m_aFacePts[0])/215. + (12*m_aFacePts[1])/215. + (26*m_aVtxPts[0])/215.;

  oaPoints(4, 3) = m_aEdgePts[0]/4. + m_aEdgePts[1]/6. + m_aEdgePts[2]/24. + m_aEdgePts[5]/12. + m_aFacePts[0]/5. + (2*m_aFacePts[1])/15. + m_aVtxPts[0]/8.;

  oaPoints(4, 4) = m_aEdgePts[0]/6. + m_aEdgePts[1]/4. + m_aEdgePts[2]/12. + m_aEdgePts[5]/24. + (2*m_aFacePts[0])/15. + m_aFacePts[1]/5. + m_aVtxPts[0]/8.;

  oaPoints(4, 5) = (21*m_aEdgePts[0])/215. + (15*m_aEdgePts[1])/43. + (6*m_aEdgePts[2])/43. + (3*m_aEdgePts[5])/215. + (12*m_aFacePts[0])/215. + (48*m_aFacePts[1])/215. + (26*m_aVtxPts[0])/215.;

  oaPoints(4, 6) = (3*m_aEdgePts[0])/71. + (33*m_aEdgePts[1])/71. + (15*m_aEdgePts[2])/71. + (12*m_aFacePts[1])/71. + (8*m_aVtxPts[0])/71.;

  oaPoints(4, 7) = (3*m_aEdgePts[1])/5. + (3*m_aEdgePts[2])/10. + m_aVtxPts[0]/10.;

  oaPoints(5, 0) = (3*m_aEdgePts[0])/5. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 1) = (18*m_aEdgePts[0])/35. + (3*m_aEdgePts[1])/35. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 2) = (3*m_aEdgePts[0])/7. + (6*m_aEdgePts[1])/35. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 3) = (12*m_aEdgePts[0])/35. + (9*m_aEdgePts[1])/35. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 4) = (9*m_aEdgePts[0])/35. + (12*m_aEdgePts[1])/35. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 5) = (6*m_aEdgePts[0])/35. + (3*m_aEdgePts[1])/7. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 6) = (3*m_aEdgePts[0])/35. + (18*m_aEdgePts[1])/35. + (2*m_aVtxPts[0])/5.;

  oaPoints(5, 7) = (3*m_aEdgePts[1])/5. + (2*m_aVtxPts[0])/5.;

  oaPoints(6, 0) = m_aVtxPts[0];

  oaPoints(6, 1) = m_aVtxPts[0];

  oaPoints(6, 2) = m_aVtxPts[0];

  oaPoints(6, 3) = m_aVtxPts[0];

  oaPoints(6, 4) = m_aVtxPts[0];

  oaPoints(6, 5) = m_aVtxPts[0];

  oaPoints(6, 6) = m_aVtxPts[0];

  oaPoints(6, 7) = m_aVtxPts[0];

  oaPoints(7, 0) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 1) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 2) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 3) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 4) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 5) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 6) = m_aVtxPts[0]; /* any point */

  oaPoints(7, 7) = m_aVtxPts[0]; /* any point */
}

void GRSPatchGregoryTriangle15Pts::FillWeights( GRSDoubleGrid& oaWeights )
{
  oaWeights.SetSize(8,8);

  oaWeights(0, 2) = oaWeights(0, 5) = oaWeights(2, 0) = oaWeights(2, 7) = oaWeights(5, 0) = oaWeights(5, 1) = oaWeights(5, 2) = oaWeights(5, 3) = oaWeights(5, 4) = oaWeights(5, 5) = oaWeights(5, 6) = oaWeights(5, 5) = 5/21.;

  oaWeights(0, 1) = oaWeights(0, 6) = oaWeights(1, 0) = oaWeights(1, 7) = oaWeights(6, 0) = oaWeights(6, 1) = oaWeights(6, 2) = oaWeights(6, 3) = oaWeights(6, 4) = oaWeights(6, 5) = oaWeights(6, 6) = oaWeights(6, 7) = 1/7.;

  oaWeights(0, 0) = oaWeights(0, 7) = oaWeights(7, 0) = oaWeights(7, 1) = oaWeights(7, 2) = oaWeights(7, 3) = oaWeights(7, 4) = oaWeights(7, 5) = oaWeights(7, 6) = oaWeights(7, 7) = 0.;

  oaWeights(0, 3) = oaWeights(0, 4) = oaWeights(3, 0) = oaWeights(3, 7) = oaWeights(4, 0) = oaWeights(4, 7) = 2/7.;

  oaWeights(1, 1) = oaWeights(1, 6) = 11/49.;

  oaWeights(1, 3) = oaWeights(1, 4) = oaWeights(2, 5) = oaWeights(2, 2) = 15/49.;

  oaWeights(2, 1) = oaWeights(2, 6) = oaWeights(1, 2) = oaWeights(1, 5) = oaWeights(2, 3) = oaWeights(2, 4) = 47/147.;

  oaWeights(3, 1) = oaWeights(3, 6) = 74/245.;

  oaWeights(3, 2) = oaWeights(3, 5) = 46/147.;

  oaWeights(3, 3) = oaWeights(3, 4) = 78/245.;

  oaWeights(4, 1) = oaWeights(4, 6) = 71/245.;

  oaWeights(4, 2) = oaWeights(4, 5) = 43/147.;

  oaWeights(4, 3) = oaWeights(4, 4) = 72/245.;
}

void GRSPatchGregoryTriangle15Pts::FillKnots( GRSDoubleVector& oaKnots )
{
  oaKnots.resize(16, 0);

  for ( size_t i = 8; i < 16; i++ ) // last 8 elements are equal to 1
    oaKnots[i] = 1.0;
}

GRSRes GRSPatchGregoryTriangle15Pts::DefinePatch( GRSPatchDefData& iData )
{
  GRSLimitLoop* pLimLoop = new GRSLimitLoop(iData);
  
  GRSRes res = pLimLoop->FillPoints(m_aVtxPts, m_aEdgePts, m_aFacePts);
  
  delete pLimLoop;
  
  return res;
}

// static
void GRSPatchGregoryTriangle15Pts::TestFillPatch15Pts(GRSPatchGregoryTriangle15Pts& oPatch)
{
  GRSPointVector vPts;
  GRSPointVector ePts;
  GRSPointVector fPts;

  vPts.push_back(GRSPoint(-1.5, 0, 0));
  vPts.push_back(GRSPoint(0, 1.5, 0));
  vPts.push_back(GRSPoint(1.5, 0, 0));


  ePts.push_back(GRSPoint(-1., 0, 0));
  ePts.push_back(GRSPoint(-1.2, 0.3, 0));
  ePts.push_back(GRSPoint(-1., 0.5, 1));
  ePts.push_back(GRSPoint(1., 0.5, 1.4));
  ePts.push_back(GRSPoint(1.2, 0.3, 1.2));
  ePts.push_back(GRSPoint(1., 0., 1.));

  fPts.push_back(GRSPoint(-0.2, 0.2, 1.4));
  fPts.push_back(GRSPoint(-0.2, 0.5, 1.));
  fPts.push_back(GRSPoint(-0.2, 0.7, 1.));
  fPts.push_back(GRSPoint(0.2, 0.7, 1.));
  fPts.push_back(GRSPoint(0.2, 0.5, 2.));
  fPts.push_back(GRSPoint(0.2, 0.2, 1.7));

  oPatch.SetVertexPoints(vPts);
  oPatch.SetEdgePoints(ePts);
  oPatch.SetFacePoints(fPts);
}
