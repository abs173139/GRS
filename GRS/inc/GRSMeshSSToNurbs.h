#pragma once

#ifndef GRSMeshSSTNurbs_h
#define GRSMeshSSTNurbs_h

#include "GRSMesh.h"
#include "GRSSurfNurbs.h"

class GRSPatch;

struct GRSPatchDefData 
{
  GRSPatchDefData(GRSMesh& iMesh, GRSFaceHandle& ifHandle) : m_mesh(iMesh), m_fHandle(ifHandle) {}

  GRSMesh& m_mesh;
  GRSFaceHandle& m_fHandle;
};

class GRSMeshSSToNurbs
{
public:
  GRSMeshSSToNurbs(GRSMesh& iMesh) : m_mesh(iMesh) {}
  ~GRSMeshSSToNurbs();
  void Run();
  void RunTestingQuad();
  void RunTestingTri();
  void DetachResult(GRSSurfNurbsPtrList& oRes);

private:
  GRSPatch* GetNewPatchForFace(const GRSFaceHandle& iH) const;

  bool IsFaceWithExtraOrdVertex( const GRSFaceHandle& iH ) const;

  inline GRSScalar GetVertexValence( const GRSVertexHandle& iH ) const
  {
    return m_mesh.valence(iH);
  }

  inline GRSScalar GetFaceVertexCount( const GRSFaceHandle& iH ) const
  {
    return m_mesh.valence(iH);
  }

  inline bool IsVertexExtraOrd( const GRSVertexHandle& iH ) const
  {
    return GetVertexValence(iH) != 4;
  }

  void ClearNurbsList();

private:
  GRSMesh& m_mesh;
  GRSSurfNurbsPtrList m_resNurbsList;
};

#endif // GRSMeshSSToNurbs
