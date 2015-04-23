#include "GRSStdAfx.h"
#include "GRSMeshSSToNurbs.h"
#include "GRSPatchGregoryQuad20Pts.h"
#include "GRSPatchGregoryTriangle15Pts.h"
#include "GRSPatchBicubicBezier16Pts.h"

#include "GRSUtils.h"

GRSMeshSSToNurbs::~GRSMeshSSToNurbs()
{
  ClearNurbsList();
}

void GRSMeshSSToNurbs::RunTestingQuad()
{
  ClearNurbsList();

  GRSPatchGregoryQuad20Pts quad;
  GRSPatchGregoryQuad20Pts::TestFillPatch20Pts(quad);
  GRSSurfNurbs* pNQuad = new GRSSurfNurbs;
  quad.PutToNURBS(*pNQuad);
  m_resNurbsList.push_back(pNQuad);
}

void GRSMeshSSToNurbs::RunTestingTri()
{
  ClearNurbsList();

  GRSPatchGregoryTriangle15Pts tri;
  GRSPatchGregoryTriangle15Pts::TestFillPatch15Pts(tri);
  GRSSurfNurbs* pNTri = new GRSSurfNurbs;
  tri.PutToNURBS(*pNTri);
  m_resNurbsList.push_back(pNTri);  
}

void GRSMeshSSToNurbs::Run()
{
  ClearNurbsList();

  GRSFaceIter fit = m_mesh.faces_begin();
  GRSFaceHandle fH;

  for ( ; fit != m_mesh.faces_end(); ++fit )
  {
    fH = fit.handle();

    GRSPatch* pPatch = GetNewPatchForFace(fH);

    if ( !pPatch )
      continue;

    GRSPatchDefData data(m_mesh, fH);
    pPatch->DefinePatch(data);

    GRSSurfNurbs* pN = new GRSSurfNurbs;

    //m_mesh.data(fH).SetNURBS(pN);
    GRSRes rc = pPatch->PutToNURBS(*pN);

    if ( rc != GRSRes_Ok ) {
      delete pN;
      continue;
    }

    m_resNurbsList.push_back(pN);
    
    delete pPatch;

  }
}

void GRSMeshSSToNurbs::DetachResult(GRSSurfNurbsPtrList& oRes)
{
  oRes = m_resNurbsList;
  m_resNurbsList.clear();
}

void GRSMeshSSToNurbs::ClearNurbsList()
{
  GRSUtils::ClearContainerCallDelete(m_resNurbsList);
}

GRSPatch* GRSMeshSSToNurbs::GetNewPatchForFace(const GRSFaceHandle& iH) const
{
  bool hasExtrV = IsFaceWithExtraOrdVertex(iH);
  GRSScalar count = GetFaceVertexCount(iH);

  if ( count == 3 ) {

    return new GRSPatchGregoryTriangle15Pts;    
  }
  
  if ( hasExtrV && ( count == 4 ) ) {

    return new GRSPatchGregoryQuad20Pts;    
  }

  if ( !hasExtrV && ( count == 4)) {

    return new GRSPatchBicubicBezier16Pts;    
  }

  return 0;
}

bool GRSMeshSSToNurbs::IsFaceWithExtraOrdVertex( const GRSFaceHandle& iH ) const
{
  GRSFaceVertexIter fv_it;
  for( fv_it = m_mesh.fv_iter(iH); fv_it; ++fv_it )
    if ( IsVertexExtraOrd(fv_it.handle()) )
      return true;

  return false;
}
