#include "GRSStdAfx.h"
#include "GRSPatchGregoryQuad20Pts.h"

#include "GRSSurfNurbs.h"
#include "GRSLimitLoop.h"

GRSRes GRSPatchGregoryQuad20Pts::PutToNURBS( GRSSurfNurbs& oNurbs )
{
  if ( m_aVtxPts.size() != 4 || m_aEdgePts.size() != 8 || m_aFacePts.size() != 8 )
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

void GRSPatchGregoryQuad20Pts::FillPoints( GRSPointsGrid& oaPoints )
{
  oaPoints.SetSize(8,8);

  oaPoints(0, 0) = m_aVtxPts[1]; /* any point */

  oaPoints(0, 1) = m_aVtxPts[1];

  oaPoints(0, 2) = (6*m_aEdgePts[3])/11. + (5*m_aVtxPts[1])/11.;

  oaPoints(0, 3) = (15*m_aEdgePts[3])/23. + (6*m_aEdgePts[4])/23. + (2*m_aVtxPts[1])/23.;

  oaPoints(0, 4) = (6*m_aEdgePts[3])/23. + (15*m_aEdgePts[4])/23. + (2*m_aVtxPts[2])/23.;

  oaPoints(0, 5) = (6*m_aEdgePts[4])/11. + (5*m_aVtxPts[2])/11.;

  oaPoints(0, 6) = m_aVtxPts[2];

  oaPoints(0, 7) = m_aVtxPts[2]; /* any point */

  oaPoints(1, 0) = m_aVtxPts[1];

  oaPoints(1, 1) = (3*m_aEdgePts[2])/13. + (3*m_aEdgePts[3])/13. + (7*m_aVtxPts[1])/13.;

  oaPoints(1, 2) = (15*m_aEdgePts[2])/109. + (42*m_aEdgePts[3])/109. + (6*m_aEdgePts[4])/109. + (18*m_aFacePts[2])/109. + (28*m_aVtxPts[1])/109.;

  oaPoints(1, 3) = (6*m_aEdgePts[2])/211. + (84*m_aEdgePts[3])/211. + (42*m_aEdgePts[4])/211. + (45*m_aFacePts[2])/211. + (9*m_aFacePts[4])/211. + (9*m_aFacePts[5])/211. + (14*m_aVtxPts[1])/211. + (2*m_aVtxPts[2])/211.;

  oaPoints(1, 4) = (42*m_aEdgePts[3])/211. + (84*m_aEdgePts[4])/211. + (6*m_aEdgePts[5])/211. + (18*m_aFacePts[2])/211. + (27*m_aFacePts[4])/211. + (18*m_aFacePts[5])/211. + (2*m_aVtxPts[1])/211. + (14*m_aVtxPts[2])/211.;

  oaPoints(1, 5) = (6*m_aEdgePts[3])/109. + (42*m_aEdgePts[4])/109. + (15*m_aEdgePts[5])/109. + (18*m_aFacePts[4])/109. + (28*m_aVtxPts[2])/109.;

  oaPoints(1, 6) = (3*m_aEdgePts[4])/13. + (3*m_aEdgePts[5])/13. + (7*m_aVtxPts[2])/13.;

  oaPoints(1, 7) = m_aVtxPts[2];

  oaPoints(2, 0) = (6*m_aEdgePts[2])/11. + (5*m_aVtxPts[1])/11.;

  oaPoints(2, 1) = (6*m_aEdgePts[1])/109. + (42*m_aEdgePts[2])/109. + (15*m_aEdgePts[3])/109. + (18*m_aFacePts[2])/109. + (28*m_aVtxPts[1])/109.;

  oaPoints(2, 2) = (15*m_aEdgePts[1])/412. + (21*m_aEdgePts[2])/103. + (21*m_aEdgePts[3])/103. + (15*m_aEdgePts[4])/412. + (9*m_aFacePts[1])/206. + (27*m_aFacePts[2])/103. + (9*m_aFacePts[3])/206. + (9*m_aFacePts[4])/412. + (9*m_aFacePts[5])/412. + (13*m_aVtxPts[1])/103.;

  oaPoints(2, 3) = m_aEdgePts[1]/128. + (7*m_aEdgePts[2])/128. + (13*m_aEdgePts[3])/64. + (7*m_aEdgePts[4])/64. + m_aEdgePts[5]/128. + (15*m_aFacePts[1])/256. + (63*m_aFacePts[2])/256. + (21*m_aFacePts[3])/256. + (21*m_aFacePts[4])/256. + (21*m_aFacePts[5])/256. + (3*m_aFacePts[7])/128. + (7*m_aVtxPts[1])/192. + (5*m_aVtxPts[2])/768.;

  oaPoints(2, 4) = m_aEdgePts[2]/128. + (7*m_aEdgePts[3])/64. + (13*m_aEdgePts[4])/64. + (7*m_aEdgePts[5])/128. + m_aEdgePts[6]/128. + (3*m_aFacePts[1])/128. + (21*m_aFacePts[2])/256. + (21*m_aFacePts[3])/256. + (3*m_aFacePts[4])/16. + (9*m_aFacePts[5])/64. + (3*m_aFacePts[6])/128. + (9*m_aFacePts[7])/256. + (5*m_aVtxPts[1])/768. + (7*m_aVtxPts[2])/192.;

  oaPoints(2, 5) = (15*m_aEdgePts[3])/412. + (21*m_aEdgePts[4])/103. + (21*m_aEdgePts[5])/103. + (15*m_aEdgePts[6])/412. + (9*m_aFacePts[3])/206. + (27*m_aFacePts[4])/103. + (9*m_aFacePts[5])/206. + (9*m_aFacePts[6])/412. + (9*m_aFacePts[7])/412. + (13*m_aVtxPts[2])/103.;

  oaPoints(2, 6) = (15*m_aEdgePts[4])/109. + (42*m_aEdgePts[5])/109. + (6*m_aEdgePts[6])/109. + (18*m_aFacePts[4])/109. + (28*m_aVtxPts[2])/109.;

  oaPoints(2, 7) = (6*m_aEdgePts[5])/11. + (5*m_aVtxPts[2])/11.;

  oaPoints(3, 0) = (6*m_aEdgePts[1])/23. + (15*m_aEdgePts[2])/23. + (2*m_aVtxPts[1])/23.;

  oaPoints(3, 1) = (42*m_aEdgePts[1])/211. + (84*m_aEdgePts[2])/211. + (6*m_aEdgePts[3])/211. + (18*m_aFacePts[0])/211. + (27*m_aFacePts[2])/211. + (18*m_aFacePts[3])/211. + (2*m_aVtxPts[0])/211. + (14*m_aVtxPts[1])/211.;

  oaPoints(3, 2) = m_aEdgePts[0]/128. + (7*m_aEdgePts[1])/64. + (13*m_aEdgePts[2])/64. + (7*m_aEdgePts[3])/128. + m_aEdgePts[4]/128. + (21*m_aFacePts[0])/256. + (21*m_aFacePts[1])/256. + (3*m_aFacePts[2])/16. + (9*m_aFacePts[3])/64. + (3*m_aFacePts[4])/128. + (9*m_aFacePts[5])/256. + (3*m_aFacePts[7])/128. + (5*m_aVtxPts[0])/768. + (7*m_aVtxPts[1])/192.;

  oaPoints(3, 3) = m_aEdgePts[0]/94. + (7*m_aEdgePts[1])/235. + (14*m_aEdgePts[2])/235. + (14*m_aEdgePts[3])/235. + (7*m_aEdgePts[4])/235. + m_aEdgePts[5]/94. + m_aEdgePts[6]/235. + m_aEdgePts[7]/235. + (21*m_aFacePts[0])/470. + (63*m_aFacePts[1])/470. + (39*m_aFacePts[2])/235. + (39*m_aFacePts[3])/235. + (18*m_aFacePts[4])/235. + (24*m_aFacePts[5])/235. + (3*m_aFacePts[6])/235. + (18*m_aFacePts[7])/235. + m_aVtxPts[0]/705. + (7*m_aVtxPts[1])/705. + m_aVtxPts[2]/705.;

  oaPoints(3, 4) = m_aEdgePts[0]/235. + m_aEdgePts[1]/235. + m_aEdgePts[2]/94. + (7*m_aEdgePts[3])/235. + (14*m_aEdgePts[4])/235. + (14*m_aEdgePts[5])/235. + (7*m_aEdgePts[6])/235. + m_aEdgePts[7]/94. + (3*m_aFacePts[0])/235. + (18*m_aFacePts[1])/235. + (21*m_aFacePts[2])/470. + (63*m_aFacePts[3])/470. + (39*m_aFacePts[4])/235. + (39*m_aFacePts[5])/235. + (18*m_aFacePts[6])/235. + (24*m_aFacePts[7])/235. + m_aVtxPts[1]/705. + (7*m_aVtxPts[2])/705. + m_aVtxPts[3]/705.;

  oaPoints(3, 5) = m_aEdgePts[3]/128. + (7*m_aEdgePts[4])/128. + (13*m_aEdgePts[5])/64. + (7*m_aEdgePts[6])/64. + m_aEdgePts[7]/128. + (3*m_aFacePts[1])/128. + (15*m_aFacePts[3])/256. + (63*m_aFacePts[4])/256. + (21*m_aFacePts[5])/256. + (21*m_aFacePts[6])/256. + (21*m_aFacePts[7])/256. + (7*m_aVtxPts[2])/192. + (5*m_aVtxPts[3])/768.;

  oaPoints(3, 6) = (6*m_aEdgePts[4])/211. + (84*m_aEdgePts[5])/211. + (42*m_aEdgePts[6])/211. + (45*m_aFacePts[4])/211. + (9*m_aFacePts[6])/211. + (9*m_aFacePts[7])/211. + (14*m_aVtxPts[2])/211. + (2*m_aVtxPts[3])/211.;

  oaPoints(3, 7) = (15*m_aEdgePts[5])/23. + (6*m_aEdgePts[6])/23. + (2*m_aVtxPts[2])/23.;

  oaPoints(4, 0) = (15*m_aEdgePts[1])/23. + (6*m_aEdgePts[2])/23. + (2*m_aVtxPts[0])/23.;

  oaPoints(4, 1) = (6*m_aEdgePts[0])/211. + (84*m_aEdgePts[1])/211. + (42*m_aEdgePts[2])/211. + (45*m_aFacePts[0])/211. + (9*m_aFacePts[2])/211. + (9*m_aFacePts[3])/211. + (14*m_aVtxPts[0])/211. + (2*m_aVtxPts[1])/211.;

  oaPoints(4, 2) = (7*m_aEdgePts[0])/128. + (13*m_aEdgePts[1])/64. + (7*m_aEdgePts[2])/64. + m_aEdgePts[3]/128. + m_aEdgePts[7]/128. + (63*m_aFacePts[0])/256. + (21*m_aFacePts[1])/256. + (21*m_aFacePts[2])/256. + (21*m_aFacePts[3])/256. + (3*m_aFacePts[5])/128. + (15*m_aFacePts[7])/256. + (7*m_aVtxPts[0])/192. + (5*m_aVtxPts[1])/768.;

  oaPoints(4, 3) = (14*m_aEdgePts[0])/235. + (14*m_aEdgePts[1])/235. + (7*m_aEdgePts[2])/235. + m_aEdgePts[3]/94. + m_aEdgePts[4]/235. + m_aEdgePts[5]/235. + m_aEdgePts[6]/94. + (7*m_aEdgePts[7])/235. + (39*m_aFacePts[0])/235. + (39*m_aFacePts[1])/235. + (18*m_aFacePts[2])/235. + (24*m_aFacePts[3])/235. + (3*m_aFacePts[4])/235. + (18*m_aFacePts[5])/235. + (21*m_aFacePts[6])/470. + (63*m_aFacePts[7])/470. + (7*m_aVtxPts[0])/705. + m_aVtxPts[1]/705. + m_aVtxPts[3]/705.;

  oaPoints(4, 4) = (7*m_aEdgePts[0])/235. + m_aEdgePts[1]/94. + m_aEdgePts[2]/235. + m_aEdgePts[3]/235. + m_aEdgePts[4]/94. + (7*m_aEdgePts[5])/235. + (14*m_aEdgePts[6])/235. + (14*m_aEdgePts[7])/235. + (18*m_aFacePts[0])/235. + (24*m_aFacePts[1])/235. + (3*m_aFacePts[2])/235. + (18*m_aFacePts[3])/235. + (21*m_aFacePts[4])/470. + (63*m_aFacePts[5])/470. + (39*m_aFacePts[6])/235. + (39*m_aFacePts[7])/235. + m_aVtxPts[0]/705. + m_aVtxPts[2]/705. + (7*m_aVtxPts[3])/705.;

  oaPoints(4, 5) = m_aEdgePts[0]/128. + m_aEdgePts[4]/128. + (7*m_aEdgePts[5])/64. + (13*m_aEdgePts[6])/64. + (7*m_aEdgePts[7])/128. + (3*m_aFacePts[0])/128. + (9*m_aFacePts[1])/256. + (3*m_aFacePts[3])/128. + (21*m_aFacePts[4])/256. + (21*m_aFacePts[5])/256. + (3*m_aFacePts[6])/16. + (9*m_aFacePts[7])/64. + (5*m_aVtxPts[2])/768. + (7*m_aVtxPts[3])/192.;

  oaPoints(4, 6) = (42*m_aEdgePts[5])/211. + (84*m_aEdgePts[6])/211. + (6*m_aEdgePts[7])/211. + (18*m_aFacePts[4])/211. + (27*m_aFacePts[6])/211. + (18*m_aFacePts[7])/211. + (2*m_aVtxPts[2])/211. + (14*m_aVtxPts[3])/211.;

  oaPoints(4, 7) = (6*m_aEdgePts[5])/23. + (15*m_aEdgePts[6])/23. + (2*m_aVtxPts[3])/23.;

  oaPoints(5, 0) = (6*m_aEdgePts[1])/11. + (5*m_aVtxPts[0])/11.;

  oaPoints(5, 1) = (15*m_aEdgePts[0])/109. + (42*m_aEdgePts[1])/109. + (6*m_aEdgePts[2])/109. + (18*m_aFacePts[0])/109. + (28*m_aVtxPts[0])/109.;

  oaPoints(5, 2) = (21*m_aEdgePts[0])/103. + (21*m_aEdgePts[1])/103. + (15*m_aEdgePts[2])/412. + (15*m_aEdgePts[7])/412. + (27*m_aFacePts[0])/103. + (9*m_aFacePts[1])/206. + (9*m_aFacePts[2])/412. + (9*m_aFacePts[3])/412. + (9*m_aFacePts[7])/206. + (13*m_aVtxPts[0])/103.;

  oaPoints(5, 3) = (13*m_aEdgePts[0])/64. + (7*m_aEdgePts[1])/128. + m_aEdgePts[2]/128. + m_aEdgePts[6]/128. + (7*m_aEdgePts[7])/64. + (3*m_aFacePts[0])/16. + (9*m_aFacePts[1])/64. + (3*m_aFacePts[2])/128. + (9*m_aFacePts[3])/256. + (3*m_aFacePts[5])/128. + (21*m_aFacePts[6])/256. + (21*m_aFacePts[7])/256. + (7*m_aVtxPts[0])/192. + (5*m_aVtxPts[3])/768.;

  oaPoints(5, 4) = (7*m_aEdgePts[0])/64. + m_aEdgePts[1]/128. + m_aEdgePts[5]/128. + (7*m_aEdgePts[6])/128. + (13*m_aEdgePts[7])/64. + (21*m_aFacePts[0])/256. + (21*m_aFacePts[1])/256. + (3*m_aFacePts[3])/128. + (15*m_aFacePts[5])/256. + (63*m_aFacePts[6])/256. + (21*m_aFacePts[7])/256. + (5*m_aVtxPts[0])/768. + (7*m_aVtxPts[3])/192.;

  oaPoints(5, 5) = (15*m_aEdgePts[0])/412. + (15*m_aEdgePts[5])/412. + (21*m_aEdgePts[6])/103. + (21*m_aEdgePts[7])/103. + (9*m_aFacePts[0])/412. + (9*m_aFacePts[1])/412. + (9*m_aFacePts[5])/206. + (27*m_aFacePts[6])/103. + (9*m_aFacePts[7])/206. + (13*m_aVtxPts[3])/103.;

  oaPoints(5, 6) = (6*m_aEdgePts[5])/109. + (42*m_aEdgePts[6])/109. + (15*m_aEdgePts[7])/109. + (18*m_aFacePts[6])/109. + (28*m_aVtxPts[3])/109.;

  oaPoints(5, 7) = (6*m_aEdgePts[6])/11. + (5*m_aVtxPts[3])/11.;

  oaPoints(6, 0) = m_aVtxPts[0];

  oaPoints(6, 1) = (3*m_aEdgePts[0])/13. + (3*m_aEdgePts[1])/13. + (7*m_aVtxPts[0])/13.;

  oaPoints(6, 2) = (42*m_aEdgePts[0])/109. + (15*m_aEdgePts[1])/109. + (6*m_aEdgePts[7])/109. + (18*m_aFacePts[0])/109. + (28*m_aVtxPts[0])/109.;

  oaPoints(6, 3) = (84*m_aEdgePts[0])/211. + (6*m_aEdgePts[1])/211. + (42*m_aEdgePts[7])/211. + (27*m_aFacePts[0])/211. + (18*m_aFacePts[1])/211. + (18*m_aFacePts[6])/211. + (14*m_aVtxPts[0])/211. + (2*m_aVtxPts[3])/211.;

  oaPoints(6, 4) = (42*m_aEdgePts[0])/211. + (6*m_aEdgePts[6])/211. + (84*m_aEdgePts[7])/211. + (9*m_aFacePts[0])/211. + (9*m_aFacePts[1])/211. + (45*m_aFacePts[6])/211. + (2*m_aVtxPts[0])/211. + (14*m_aVtxPts[3])/211.;

  oaPoints(6, 5) = (6*m_aEdgePts[0])/109. + (15*m_aEdgePts[6])/109. + (42*m_aEdgePts[7])/109. + (18*m_aFacePts[6])/109. + (28*m_aVtxPts[3])/109.;

  oaPoints(6, 6) = (3*m_aEdgePts[6])/13. + (3*m_aEdgePts[7])/13. + (7*m_aVtxPts[3])/13.;

  oaPoints(6, 7) = m_aVtxPts[3];

  oaPoints(7, 0) = m_aVtxPts[3]; /* any point */

  oaPoints(7, 1) = m_aVtxPts[0];

  oaPoints(7, 2) = (6*m_aEdgePts[0])/11. + (5*m_aVtxPts[0])/11.;

  oaPoints(7, 3) = (15*m_aEdgePts[0])/23. + (6*m_aEdgePts[7])/23. + (2*m_aVtxPts[0])/23.;

  oaPoints(7, 4) = (6*m_aEdgePts[0])/23. + (15*m_aEdgePts[7])/23. + (2*m_aVtxPts[3])/23.;

  oaPoints(7, 5) = (6*m_aEdgePts[7])/11. + (5*m_aVtxPts[3])/11.;

  oaPoints(7, 6) = m_aVtxPts[3];

  oaPoints(7, 7) = m_aVtxPts[3]; /* any point */
}

void GRSPatchGregoryQuad20Pts::FillWeights( GRSDoubleGrid& oaWeights )
{
  oaWeights.SetSize(8, 8);

  oaWeights(0, 0) = oaWeights(0, 7) = oaWeights(7, 0) = oaWeights(7, 7) = 0.;

  oaWeights(0, 1) = oaWeights(1, 7) = oaWeights(6, 0) = oaWeights(6, 7) = oaWeights(7, 1) = oaWeights(7, 6) = oaWeights(0, 6) = 2/7.;

  oaWeights(3, 6) = oaWeights(0, 2) = oaWeights(2, 0) = oaWeights(0, 5) = oaWeights(5, 0) = oaWeights(5, 7) = oaWeights(7, 5) = oaWeights(7, 2) = oaWeights(2, 7) = 11/21.;

  oaWeights(0, 3) = oaWeights(0, 4) = oaWeights(3, 0) = oaWeights(3, 7) = oaWeights(4, 0) = oaWeights(4, 7) = oaWeights(7, 3) = oaWeights(7, 4) = 23/35.;

  oaWeights(1, 1) = oaWeights(6, 1) = oaWeights(6, 6) = oaWeights(1, 6) = 26/49.;

  oaWeights(1, 2) = oaWeights(1, 5) = oaWeights(2, 1) = 109/147.;

  oaWeights(1, 3) = oaWeights(1, 4) = oaWeights(3, 1) = oaWeights(3, 6) = oaWeights(4, 6) = oaWeights(6, 3) = oaWeights(6, 4) = oaWeights(4, 1) = 211/245.;

  oaWeights(2, 2) = oaWeights(2, 5) = oaWeights(5, 2) = oaWeights(5, 5) = 412/441.;

  oaWeights(5, 1) = oaWeights(5, 6) = oaWeights(2, 6) = oaWeights(2, 6) = oaWeights(6, 5) = 109/147.;

  oaWeights(3, 2) = oaWeights(3, 5) = oaWeights(5, 3) = oaWeights(5, 4) = oaWeights(2, 3) = oaWeights(2, 4) = oaWeights(4, 5) = oaWeights(4, 2) = 256/245.;

  oaWeights(3, 3) = oaWeights(3, 4) = oaWeights(4, 3) = oaWeights(4, 4) = 282/245.;
}

void GRSPatchGregoryQuad20Pts::FillKnots( GRSDoubleVector& oaKnots )
{
  oaKnots.resize(16, 0);

  for ( size_t i = 8; i < 16; i++ ) // last 8 elements are equal to 1
    oaKnots[i] = 1.0;
}

GRSRes GRSPatchGregoryQuad20Pts::DefinePatch( GRSPatchDefData& iData )
{
  GRSLimitLoop* pLimLoop = new GRSLimitLoop(iData);

  GRSRes res = pLimLoop->FillPoints(m_aVtxPts, m_aEdgePts, m_aFacePts);
  
  PrintPatch();
  
  delete pLimLoop;

  return res;
}

void GRSPatchGregoryQuad20Pts::PrintPatch()
{
  GRSPointVector::iterator itV, itE, itF;
  
  std::cout << "Vertex points:" << std::endl;
  for ( itV = m_aVtxPts.begin(); itV != m_aVtxPts.end(); ++itV )
    std::cout << "v[" << std::distance(m_aVtxPts.begin(), itV) << "] = " << *itV << std::endl;
  
  std::cout << "Edge points:" << std::endl;
  for ( itE = m_aEdgePts.begin(); itE != m_aEdgePts.end(); ++itE )
    std::cout << "e[" << std::distance(m_aEdgePts.begin(), itE) << "] = " << *itE << std::endl;

  std::cout << "Face points:" << std::endl;
  for ( itF = m_aFacePts.begin(); itF != m_aFacePts.end(); ++itF )
    std::cout << "f[" << std::distance(m_aFacePts.begin(), itF) << "] = " << *itF << std::endl;
}

void GRSPatchGregoryQuad20Pts::TestFillPatch20Pts(GRSPatchGregoryQuad20Pts& oPatch)
{
  GRSPointVector vPts;
  GRSPointVector ePts;
  GRSPointVector fPts;

  vPts.push_back(GRSPoint(0, 0, 0));
  vPts.push_back(GRSPoint(0, 3, 0));
  vPts.push_back(GRSPoint(3, 3, 0));
  vPts.push_back(GRSPoint(3, 0, 0));

  ePts.push_back(GRSPoint(1, 0, 0));
  ePts.push_back(GRSPoint(0, 1, 0));
  ePts.push_back(GRSPoint(0, 2, 0));
  ePts.push_back(GRSPoint(1, 3, 0));
  ePts.push_back(GRSPoint(2, 3, 0));
  ePts.push_back(GRSPoint(3, 2, 0));
  ePts.push_back(GRSPoint(3, 1, 0));
  ePts.push_back(GRSPoint(2, 0, 0));

  fPts.push_back(GRSPoint(1, 0.8, 3));
  fPts.push_back(GRSPoint(0.9, 1, 4));
  fPts.push_back(GRSPoint(1.01, 1.9, 1.));
  fPts.push_back(GRSPoint(1, 2, 0.9));
  fPts.push_back(GRSPoint(2, 1.9, 3.5));
  fPts.push_back(GRSPoint(1.9, 2, 3.8));
  fPts.push_back(GRSPoint(2, 1.01, 2.5));
  fPts.push_back(GRSPoint(1.8, 1, 2.6));

  oPatch.SetVertexPoints(vPts);
  oPatch.SetEdgePoints(ePts);
  oPatch.SetFacePoints(fPts);
}


