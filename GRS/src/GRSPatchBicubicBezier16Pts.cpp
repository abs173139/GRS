#include "GRSStdAfx.h"
#include "GRSPatchBicubicBezier16Pts.h"
#include "GRSSurfNurbs.h"
#include "GRSMeshSSToNurbs.h"

GRSRes GRSPatchBicubicBezier16Pts::PutToNURBS( GRSSurfNurbs& oNurbs )
{
  if ( m_controlPoints.GetNSz()!= 4 && m_controlPoints.GetMSz() != 4 )
    return GRSRes_IncorrectInput;

  size_t uDeg = 4;
  size_t vDeg = 4;

  GRSDoubleGrid weights;
  weights.SetSize(uDeg, vDeg, 1.0);

  GRSDoubleVector knots; // same for U and V
  knots.resize(8, 0);

  double knotVal = 0;
  for ( size_t knotCount = 0; knotCount < 8; knotCount++ ) {
    knotVal = 0.125 * knotCount;
    knots[knotCount] = knotVal;
  }

  oNurbs.Set(uDeg, vDeg, m_controlPoints, weights, knots, knots);
  return GRSRes_Ok;
}

GRSRes GRSPatchBicubicBezier16Pts::DefinePatch(GRSPatchDefData& iData)
{
  GRSMesh mesh = iData.m_mesh;
  GRSFaceHandle fH = iData.m_fHandle;

  m_controlPoints.SetSize(4, 4, GRSPoint(0.,0.,0.));

  GRSPointVector pV;
  GRSFaceHalfedgeIter fhe_it;
  // [0] -> [4] -> [8] -> [12]
  for ( fhe_it = mesh.fh_iter(fH); fhe_it; ++fhe_it )
  {
    // fill first vertex in inner loop ( vertex labeled zero)
    // corresponding [12] -> [0]
    
    GRSVertexHandle vh = mesh.to_vertex_handle(fhe_it.handle());
    pV.push_back(mesh.point(vh));

    // moving around face
    // | 11 | 10| 9 | 7 |
    // -------------------
    // | 13 | 8 | 4 | 6 |
    // -------------------
    // | 14 |12 |*0*| 5 |
    // -------------------
    // | 15 |*1*|*2*|*3*|
    // -------------------

    GRSHalfedgeHandle h;
    GRSHalfedgeHandle hInit = mesh.opposite_halfedge_handle(fhe_it.handle());

    //fill three vertex in outer loop

    // [1]
    h = mesh.next_halfedge_handle(hInit);
    vh = mesh.to_vertex_handle(h);
    pV.push_back(mesh.point(vh));

    // [2]
    h = mesh.next_halfedge_handle(h);
    vh = mesh.to_vertex_handle(h);
    pV.push_back(mesh.point(vh));
    
    h = mesh.next_halfedge_handle(h);

    // [3]
    h = mesh.opposite_halfedge_handle(h);
    h = mesh.next_halfedge_handle(h);
    vh = mesh.to_vertex_handle(h);
    pV.push_back(mesh.point(vh));
  }

  this->FillPointsGridFromMeshData(pV);

  return GRSRes_Ok;
}

void GRSPatchBicubicBezier16Pts::FillPointsGridFromMeshData( GRSPointVector& iV )
{
  if ( iV.size() != 16 )
    return;

  m_controlPoints.SetSize(4, 4, GRSPoint(0., 0., 0.));

  m_controlPoints(0, 0) = iV[11];
  m_controlPoints(1, 0) = iV[10];
  m_controlPoints(2, 0) = iV[9];
  m_controlPoints(3, 0) = iV[7];

  m_controlPoints(0, 1) = iV[13];
  m_controlPoints(1, 1) = iV[8];
  m_controlPoints(2, 1) = iV[4];
  m_controlPoints(3, 1) = iV[6];

  m_controlPoints(0, 2) = iV[14];
  m_controlPoints(1, 2) = iV[12];
  m_controlPoints(2, 2) = iV[0];
  m_controlPoints(3, 2) = iV[5];

  m_controlPoints(0, 3) = iV[15];
  m_controlPoints(1, 3) = iV[1];
  m_controlPoints(2, 3) = iV[2];
  m_controlPoints(3, 3) = iV[3];
}

