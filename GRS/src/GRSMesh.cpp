#include "GRSStdAfx.h"
#include "GRSMesh.h"
#include "GRSString.h"
#include "GRSStringUtils.h"

using namespace OpenMesh::IO;

bool GRSMeshUtils::ReadMeshC_STL( GRSMesh& iMesh, const char* iFileName )
{
  _STLReader_ rd;
  return rd.read(iFileName, ImporterT<GRSMesh>(iMesh), Options());
}

bool GRSMeshUtils::ReadMeshW_STL( GRSMesh& iMesh, const GRSString& iFileName )
{
  GRSStringC fileName;
  GRSStringUtils::WtoC(iFileName, fileName);
  return ReadMeshC_STL(iMesh, fileName.c_str());
}

bool GRSMeshUtils::WriteMeshC_STL( GRSMesh& iMesh, const char* iFileName )
{
  // for the correct output .stl file normals must be computed
  ComputeFaceNormals(iMesh);

  _STLWriter_ wr;
  bool res = wr.write(iFileName, ExporterT<GRSMesh>(iMesh), Options());

  ReleaseFaceNormals(iMesh);
  
  return res;
}

bool GRSMeshUtils::WriteMeshW_STL( GRSMesh& iMesh, const GRSString& iFileName )
{
  GRSStringC fileName;
  GRSStringUtils::WtoC(iFileName, fileName);
  return WriteMeshC_STL(iMesh, fileName.c_str());
}

void GRSMeshUtils::ReleaseFaceNormals( GRSMesh& iMesh )
{
  iMesh.release_face_normals();
};

void GRSMeshUtils::ComputeFaceNormals( GRSMesh& iMesh )
{
  if ( !iMesh.has_face_normals() )
    iMesh.request_face_normals();
  
  GRSFaceIter fit;
  for ( fit = iMesh.faces_begin(); fit != iMesh.faces_end(); ++fit )
    iMesh.set_normal(fit, iMesh.calc_face_normal(fit));
}

void GRSMeshUtils::ReplaceVertices( GRSMesh& ioMesh, GRSPointVector& iCoGVec )
{
  GRSVertexIter itV;
  GRSPointVector::iterator itVcog;
  for ( itV = ioMesh.vertices_begin(), itVcog = iCoGVec.begin(); itV != ioMesh.vertices_end(); ++itV, ++itVcog )
  {
    if ( !ioMesh.is_boundary(itV) )
      ioMesh.set_point(itV, *itVcog);
  }
}

bool GRSMeshUtils::ReadMeshW_OBJ(GRSMesh& iMesh, const GRSString& iFileName)
{
  GRSStringC fileName;
  GRSStringUtils::WtoC(iFileName, fileName);
  return ReadMeshC_OBJ(iMesh, fileName);
}

bool GRSMeshUtils::ReadMeshC_OBJ(GRSMesh& iMesh, const GRSStringC& iFileName)
{
  _OBJReader_ rd;
  return rd.read(iFileName, ImporterT<GRSMesh>(iMesh), Options());
}

