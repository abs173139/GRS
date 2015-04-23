#pragma once

#ifndef GRSLimitLoop_h
#define GRSLimitLoop_h

#include "GRSMesh.h"
#include "GRSMeshSSToNurbs.h"
#include "GRSRes.h"

class GRSLimitLoop
{
public:
  typedef OpenMesh::VPropHandleT<GRSPoint> GRSLimitVtxPts;
  typedef OpenMesh::HPropHandleT<GRSPoint> GRSLimitEdgePts;
  typedef OpenMesh::HPropHandleT<GRSPoint> GRSLimitFacePts;

  typedef OpenMesh::EPropHandleT<GRSPoint> GRSEdgeMidPts;
  typedef OpenMesh::FPropHandleT<GRSPoint> GRSFaceCOGs;

public:
  GRSLimitLoop(GRSPatchDefData& iData) : m_mesh(iData.m_mesh), m_faceHandle(iData.m_fHandle), 
    m_limitEdgePts(), m_limitVertexPts(), m_limitFacePts()
  {
    Init();
  }

  GRSLimitLoop(GRSFaceHandle& iVh, GRSMesh& iMesh) : m_mesh(iMesh), m_faceHandle(iVh), 
  m_limitEdgePts(), m_limitVertexPts(), m_limitFacePts()
  {
    Init();
  }

  ~GRSLimitLoop()
  {
    Release();
  }

  /*
    Limit points for constructing Gregory patch
  */
  void ComputeLimitPoints()
  {
    ComputeLoopCOGs();
    ComputeLoopMidPts();

    ComputeVtxPoints();
    ComputeEdgePoints();
    ComputeFacePoints();
  }

  GRSRes FillPoints(GRSPointVector& ovPts, GRSPointVector& oePts, GRSPointVector& ofPts);

private:

  inline void AddVtxPoint(const GRSHalfedgeHandle& iHeH, GRSPointVector& oVtxPts)
  {
    oVtxPts.push_back(m_mesh.property(m_limitVertexPts, GetHalfEdgeSourceVertex(iHeH)));
  }

  inline void AddEdgePoint(const GRSHalfedgeHandle& iHeH, GRSPointVector& oEdgePts)
  {
    oEdgePts.push_back(m_mesh.property(m_limitEdgePts, iHeH));
  }

  inline void AddFacePoint(const GRSHalfedgeHandle& iHeH, GRSPointVector& oFacePts)
  {
    oFacePts.push_back(m_mesh.property(m_limitFacePts, iHeH));
  }

  inline GRSPoint& GetEdgeMidpoint(const GRSHalfedgeHandle& iHeH) const
  {
    return m_mesh.property(m_edgeMidPts, m_mesh.edge_handle(iHeH));
  }

  inline GRSPoint& GetFaceCOG(const GRSHalfedgeHandle& iHeH) const
  {
    return m_mesh.property(m_faceCOGPts, m_mesh.face_handle(iHeH));
  }

  inline GRSVertexHandle GetHalfEdgeSourceVertex(const GRSHalfedgeHandle& iHeH) const
  {
    return m_mesh.to_vertex_handle(m_mesh.opposite_halfedge_handle(iHeH));
  }

  void Release();
  void Init();

  void ComputeEdgePoints();
  void ComputeFacePoints();
  void ComputeVtxPoints();

  void ComputeLoopCOGs();
  void ComputeLoopMidPts();

  void ComputeAdjFacesCOGs(const GRSVertexHandle& iVh);
  void ComputeAdjEdgesMidPts(const GRSVertexHandle& iVh);

  void ComputeOneEdgePoint(const GRSHalfedgeHandle& iheH);
  void ComputeFacePointCCW(const GRSHalfedgeHandle& iheH);
  void ComputeFacePointCW(const GRSHalfedgeHandle& iheH);
  void ComputeOneVertexPoint(const GRSVertexHandle& iVh);

private:
  GRSMesh& m_mesh;
  GRSFaceHandle& m_faceHandle;
  GRSLimitVtxPts m_limitVertexPts;
  GRSLimitEdgePts m_limitEdgePts;
  GRSLimitFacePts  m_limitFacePts;
  GRSEdgeMidPts m_edgeMidPts;
  GRSFaceCOGs m_faceCOGPts;
};


#endif // GRSLimitLoop_h
