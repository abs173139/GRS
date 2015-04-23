#include "GRSStdAfx.h"
#include "GRSLimitLoop.h"

#include "cmath"

void GRSLimitLoop::Release()
{
  m_mesh.remove_property(m_faceCOGPts);
  m_mesh.remove_property(m_edgeMidPts);

  m_mesh.remove_property(m_limitVertexPts);
  m_mesh.remove_property(m_limitEdgePts);
  m_mesh.remove_property(m_limitFacePts);
}

void GRSLimitLoop::Init()
{
  m_mesh.add_property(m_faceCOGPts);
  m_mesh.add_property(m_edgeMidPts);

  m_mesh.add_property(m_limitVertexPts);
  m_mesh.add_property(m_limitEdgePts);
  m_mesh.add_property(m_limitFacePts);

  ComputeLimitPoints();
}

void GRSLimitLoop::ComputeLoopCOGs()
{
  GRSFaceVertexIter fv_it;
  for ( fv_it = m_mesh.fv_iter(m_faceHandle); fv_it; ++fv_it )
    ComputeAdjFacesCOGs(fv_it.handle());
}

void GRSLimitLoop::ComputeLoopMidPts()
{
  GRSFaceVertexIter fv_it;
  for ( fv_it = m_mesh.fv_iter(m_faceHandle); fv_it; ++fv_it )
    ComputeAdjEdgesMidPts(fv_it.handle());
}

void GRSLimitLoop::ComputeOneEdgePoint( const GRSHalfedgeHandle& ihEdgeH )
{
  /*
    0) Sketch
  //////////////////
  //      |       //
  // [f3] e3 [f2] //
  //      |       //
  //-e0-- ## --e2-//
  //      |       //
  // [f0] e1 [f1] //
  //      |       //
  //////////////////
  */
  GRSPoint res(0.,0.,0.);
  GRSVertexHandle hVtx = GetHalfEdgeSourceVertex(ihEdgeH);
  
  // number of adjacent edges
  GRSScalar n = m_mesh.valence(hVtx);
  
  double sigma = 1./sqrt((4 + pow(cos(M_PI/(double)n), 2)));
  double lambda = (5. + cos(2.*M_PI/(double)n) + cos(M_PI/(double)n)*sqrt(18.+2.*cos(2.*M_PI/(double)n)))/16.;
  
  GRSScalar i(0);
  GRSHalfedgeHandle h = ihEdgeH;
  do {
    // take face shared by current half-edge and half-edge rotated CCW
    GRSFaceHandle hFace = m_mesh.face_handle(h);

    double alpha = (1 - sigma*cos(M_PI/(double)n))*cos(2.*M_PI*(double)i/(double)n);
    double beta = 2.*sigma*cos((2.*M_PI*(double)i+M_PI)/(double)n);

    res += alpha*m_mesh.property(m_edgeMidPts, m_mesh.edge_handle(h));
    res += beta*m_mesh.property(m_faceCOGPts, hFace);

    h = m_mesh.ccw_rotated_halfedge_handle(h);
    i++;

  } while ( h != ihEdgeH );

  res *= 2./(double)n;
  m_mesh.property(m_limitEdgePts, ihEdgeH) += 2.*res*lambda/3.;
  m_mesh.property(m_limitEdgePts, ihEdgeH) += m_mesh.property(m_limitVertexPts, hVtx);

  // we have all limit vertex points and edge points shared in mesh properties
}



void GRSLimitLoop::ComputeOneVertexPoint( const GRSVertexHandle& iVh )
{
  GRSScalar val = m_mesh.valence(iVh);
  GRSVertexOHalfedgeIter voh_it;
  GRSHalfedgeHandle hh;
  for ( voh_it = m_mesh.voh_iter(iVh); voh_it; ++voh_it )
  {
    hh = voh_it.handle();
    m_mesh.property(m_limitVertexPts, iVh) += GetEdgeMidpoint(hh);
    m_mesh.property(m_limitVertexPts, iVh) += GetFaceCOG(hh);
  }

  m_mesh.property(m_limitVertexPts, iVh) *= 4.;
  m_mesh.property(m_limitVertexPts, iVh) /= (val*(val + 5.));
  m_mesh.property(m_limitVertexPts, iVh) += m_mesh.point(iVh)*((val - 3.)/(val + 5.));
}

void GRSLimitLoop::ComputeAdjFacesCOGs( const GRSVertexHandle& iVh )
{
  GRSVertexFaceIter vf_it;
  for (vf_it = m_mesh.vf_iter(iVh); vf_it; ++vf_it)
  {
    m_mesh.property(m_faceCOGPts, vf_it).vectorize(0.0);
    GRSScalar val = m_mesh.valence(vf_it.handle());

    GRSFaceVertexIter fv_it;
    for ( fv_it = m_mesh.fv_iter(vf_it); fv_it; ++fv_it )
      m_mesh.property(m_faceCOGPts, vf_it) += m_mesh.point(fv_it);
    
    m_mesh.property(m_faceCOGPts, vf_it) /= val;
  }
}

void GRSLimitLoop::ComputeAdjEdgesMidPts( const GRSVertexHandle& iVh )
{
  GRSVertexOHalfedgeIter voh_it;
  for ( voh_it = m_mesh.voh_iter(iVh); voh_it; ++voh_it )
  {
    GRSHalfedgeHandle heh = voh_it.handle();
    GRSHalfedgeHandle opHeh = m_mesh.opposite_halfedge_handle(heh);
    GRSEdgeHandle eh = m_mesh.edge_handle(voh_it);
    m_mesh.property(m_edgeMidPts, eh).vectorize(0.0);
    m_mesh.property(m_edgeMidPts, eh) += m_mesh.point(m_mesh.to_vertex_handle(heh));
    m_mesh.property(m_edgeMidPts, eh) += m_mesh.point(m_mesh.to_vertex_handle(opHeh));
    m_mesh.property(m_edgeMidPts, eh) /= 2.;
  }
}

void GRSLimitLoop::ComputeFacePointCCW( const GRSHalfedgeHandle& ihEdgeH )
{
    /*
       half-edge
      V0------>V1
      1) c1 - c0
      2) m2 - m0
  //////////////////      
  // ------------- //     
  //| [f3] | [f2] |//     
  //|      |      |//     
  //|--m0--V0--m2-|//     
  //|      |      |//  
  //| [c0] m1 [c1]|//    
  //|      |      |//      
  // ------V1----- //     
  //////////////////      
  */

  GRSVertexHandle v0 = GetHalfEdgeSourceVertex(ihEdgeH);
  GRSVertexHandle v1 = m_mesh.to_vertex_handle(ihEdgeH);

  GRSScalar n0 = m_mesh.valence(v0);
  GRSScalar n1 = m_mesh.valence(v1);
  
  double c0 = cos(2.*M_PI/n0);
  double c1 = cos(2.*M_PI/n1);

  GRSHalfedgeHandle hNext = m_mesh.ccw_rotated_halfedge_handle(ihEdgeH);
  GRSHalfedgeHandle hPrev = m_mesh.cw_rotated_halfedge_handle(ihEdgeH);

  GRSPoint r = (GetEdgeMidpoint(hNext) - GetEdgeMidpoint(hPrev))/3.;
  r += 2.*(GetFaceCOG(ihEdgeH) - GetFaceCOG(hPrev))/3.;

  double d = m_mesh.valence(m_faceHandle);

  m_mesh.property(m_limitFacePts, ihEdgeH) += c1*m_mesh.property(m_limitVertexPts, v0);
  m_mesh.property(m_limitFacePts, ihEdgeH) += ((double)d - 2.*c0 - c1)*m_mesh.property(m_limitEdgePts, ihEdgeH);
  m_mesh.property(m_limitFacePts, ihEdgeH) += 2.*c0*m_mesh.property(m_limitEdgePts, m_mesh.opposite_halfedge_handle(ihEdgeH));
  m_mesh.property(m_limitFacePts, ihEdgeH) += r;
  m_mesh.property(m_limitFacePts, ihEdgeH) /= (double)d;

  // we have all limit elements to construct Gregory patch
}

void GRSLimitLoop::ComputeFacePointCW( const GRSHalfedgeHandle& ihEdgeH )
{
  GRSVertexHandle v0 = GetHalfEdgeSourceVertex(ihEdgeH);
  GRSVertexHandle v1 = m_mesh.to_vertex_handle(ihEdgeH);

  GRSScalar n0 = m_mesh.valence(v0);
  GRSScalar n1 = m_mesh.valence(v1);
  
  double c0 = cos(2.*M_PI/n0);
  double c1 = cos(2.*M_PI/n1);

  GRSHalfedgeHandle hNext = m_mesh.cw_rotated_halfedge_handle(ihEdgeH);
  GRSHalfedgeHandle hPrev = m_mesh.ccw_rotated_halfedge_handle(ihEdgeH);

  GRSPoint r = (GetEdgeMidpoint(hNext) - GetEdgeMidpoint(hPrev))/3.;
  r += 2.*(GetFaceCOG(hNext) - GetFaceCOG(ihEdgeH))/3.;

  double d = m_mesh.valence(m_faceHandle);

  m_mesh.property(m_limitFacePts, ihEdgeH) += c1*m_mesh.property(m_limitVertexPts, v0);
  m_mesh.property(m_limitFacePts, ihEdgeH) += ((double)d - 2.*c0 - c1)*m_mesh.property(m_limitEdgePts, ihEdgeH);
  m_mesh.property(m_limitFacePts, ihEdgeH) += 2.*c0*m_mesh.property(m_limitEdgePts, m_mesh.opposite_halfedge_handle(ihEdgeH));
  m_mesh.property(m_limitFacePts, ihEdgeH) += r;
  m_mesh.property(m_limitFacePts, ihEdgeH) /= (double)d;
}

void GRSLimitLoop::ComputeVtxPoints()
{
  GRSFaceVertexIter fv_it;
  for ( fv_it = m_mesh.fv_iter(m_faceHandle); fv_it; ++fv_it )
  {
    m_mesh.property(m_limitVertexPts, fv_it).vectorize(0.0);
    ComputeOneVertexPoint(fv_it.handle());
  }
}

void GRSLimitLoop::ComputeEdgePoints()
{
  GRSFaceHalfedgeIter fhe_it;
  for ( fhe_it = m_mesh.fh_iter(m_faceHandle); fhe_it; ++fhe_it )
  {
    // if we fix oriented basis on the plane and begin
    // to combine center of coordinates with each 
    // polygon's boundary vertex 
    // without changing orientation when we obtain two 
    // transversal vector fields

    GRSHalfedgeHandle heH = fhe_it.handle();
    m_mesh.property(m_limitEdgePts, heH).vectorize(0.0);
    ComputeOneEdgePoint(heH);

    GRSHalfedgeHandle opHeH = m_mesh.opposite_halfedge_handle(heH);
    m_mesh.property(m_limitEdgePts, opHeH).vectorize(0.0);
    ComputeOneEdgePoint(opHeH);
  }
}

void GRSLimitLoop::ComputeFacePoints()
{
  GRSFaceHalfedgeIter fhe_it;
  for ( fhe_it = m_mesh.fh_iter(m_faceHandle); fhe_it; ++fhe_it )
  {
    GRSHalfedgeHandle heH = fhe_it.handle();
    m_mesh.property(m_limitFacePts, heH).vectorize(0.0);
    ComputeFacePointCCW(heH);

    GRSHalfedgeHandle opHeH = m_mesh.opposite_halfedge_handle(heH);
    m_mesh.property(m_limitFacePts, opHeH).vectorize(0.0);
    ComputeFacePointCW(opHeH);
  }
}

GRSRes GRSLimitLoop::FillPoints( GRSPointVector& oVtxPts, GRSPointVector& oEdgePts, GRSPointVector& oFacePts )
{
  // http://wiki.ledas.ru/w/Gregory_patches
  // http://wiki.ledas.ru/w/File:Quad_enum.jpg
  // http://wiki.ledas.ru/images/a/ae/Triang_enum.jpg

  oVtxPts.clear(); oEdgePts.clear(); oFacePts.clear();

  GRSHalfedgeHandle hHInit = m_mesh.halfedge_handle(m_faceHandle);

  AddVtxPoint(hHInit, oVtxPts);

  AddEdgePoint(hHInit, oEdgePts);
  AddFacePoint(hHInit, oFacePts);

  GRSHalfedgeHandle hH = m_mesh.prev_halfedge_handle(hHInit);
  while ( hH != hHInit )
  {
    GRSHalfedgeHandle hHOp = m_mesh.opposite_halfedge_handle(hH);
    
    AddEdgePoint(hHOp, oEdgePts);
    AddFacePoint(hHOp, oFacePts);
    
    AddVtxPoint(hH, oVtxPts);
    AddEdgePoint(hH, oEdgePts);
    AddFacePoint(hH, oFacePts);

    hH = m_mesh.prev_halfedge_handle(hH);
  }
  
  hHInit = m_mesh.opposite_halfedge_handle(hHInit);

  AddEdgePoint(hHInit, oEdgePts);
  AddFacePoint(hHInit, oFacePts);
  
  return GRSRes_Ok;
}
