#pragma once

#ifndef GRSMesh_h
#define GRSMesh_h

#include "GRSRes.h"
#include "GRSString.h"
#include "GRSInternalTypes.h"

class GRSPatch;
class GRSSurfNurbs;

/*
  Mesh specification
*/
struct GRSTraits : public OpenMesh::DefaultTraits
{
  // use double valued coordinates
  typedef OpenMesh::Vec3d Point;
  typedef OpenMesh::Vec3d Normal;
  typedef size_t Scalar;

  FaceTraits
  {
  public:
    FaceT() : m_nurbs(0) { }

    const GRSSurfNurbs* GetNURBS() const { return m_nurbs; }
    GRSSurfNurbs* GetNURBS() { return m_nurbs; }
    void SetNURBS( GRSSurfNurbs* ipNurbs ) { m_nurbs = ipNurbs; }

  private:
    GRSSurfNurbs* m_nurbs;
  };
};

typedef OpenMesh::PolyMesh_ArrayKernelT<GRSTraits> GRSMesh;
typedef GRSMesh::VertexIter GRSVertexIter;
typedef GRSMesh::FaceIter GRSFaceIter;
typedef GRSMesh::EdgeIter GRSEdgeIter;
typedef GRSMesh::HalfedgeIter GRSHalfedgeIter;
typedef GRSMesh::ConstVertexIter GRSConstVertexIter;
typedef GRSMesh::VertexVertexIter GRSVertexVertexIter;
typedef GRSMesh::VertexFaceIter GRSVertexFaceIter;
typedef GRSMesh::ConstVertexVertexIter GRSConstVertexVertexIter;
typedef GRSMesh::FaceHandle GRSFaceHandle;
typedef GRSMesh::EdgeHandle GRSEdgeHandle;
typedef GRSMesh::HalfedgeHandle GRSHalfedgeHandle;
typedef GRSMesh::VertexHandle GRSVertexHandle;
typedef GRSMesh::Scalar GRSScalar;
typedef GRSMesh::ConstFaceVertexIter GRSCFaceVertexIter;
typedef GRSMesh::FaceFaceIter GRSFaceFaceIter;
typedef GRSMesh::FaceHalfedgeIter GRSFaceHalfedgeIter;
typedef GRSMesh::FaceVertexIter GRSFaceVertexIter;
//iterate over all outgoing half-edges
typedef GRSMesh::VertexOHalfedgeIter GRSVertexOHalfedgeIter;
//iterate over all outgoing half-edges
typedef GRSMesh::VertexIHalfedgeIter GRSVertexIHalfedgeIter;


namespace GRSMeshUtils {

  bool ReadMeshC_STL(GRSMesh& iMesh, const char* iFileName );
  bool ReadMeshW_STL(GRSMesh& iMesh, const GRSString& iFileName);
  bool WriteMeshC_STL(GRSMesh& iMesh, const char* iFileName);
  bool WriteMeshW_STL(GRSMesh& iMesh, const GRSString& iFileName);

  bool ReadMeshW_OBJ(GRSMesh& iMesh, const GRSString& iFileName);
  bool ReadMeshC_OBJ(GRSMesh& iMesh, const GRSStringC& iFileName);

  void ComputeFaceNormals( GRSMesh& iMesh );
  void ReleaseFaceNormals( GRSMesh& iMesh );

  void ReplaceVertices(GRSMesh& iMesh, GRSPointVector& oCoGVec);
}

#endif // GRSMesh_h
