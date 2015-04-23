#include "GRSStdAfx.h"
#include "GRSSSToNURBS.h"
#include "GRSStringUtils.h"
#include "GRSMesh.h"
#include "GRSMeshSSToNurbs.h"
#include "GRSUtils.h"

GRSSSToNURBS::~GRSSSToNURBS()
{
  GRSUtils::ClearContainerCallDelete(m_resNurbs);
}

bool GRSSSToNURBS::Run(int argc, _TCHAR* argv[])
{
  if ( argc < 2 )
    return false;

  m_modelType = DefineModelType(argv[1]);

  if ( m_modelType == mtUNDEF )
    return false;
  
  m_modelPath = GetModelFullPath(argv[1]);
  m_modelNameNoExt = GetModelNameNoExt(m_modelPath);

  if ( argc == 3 ) {
    m_outModelPathNoExt = argv[2]; // directory
    m_outModelPathNoExt += L"\\";
    m_outModelPathNoExt += m_modelNameNoExt;
    m_outModelPathNoExt += L".";

  } else {
    m_outModelPathNoExt = m_modelPath.substr(0, m_modelPath.length() - 3);
  }

  GRSMesh mesh;

  if ( m_modelType == mtOBJ ) {
    if ( !GRSMeshUtils::ReadMeshW_OBJ(mesh, m_modelPath) )
      return false;
  }

  if ( m_modelType == mtSTL ) {
    if ( !GRSMeshUtils::ReadMeshW_STL(mesh, m_modelPath) )
      return false;
  }

  GRSMeshSSToNurbs ss2n(mesh);

  ss2n.Run();
  ss2n.DetachResult(m_resNurbs);
  
  return true;
}

GRSString GRSSSToNURBS::GetModelFullPath(const GRSString& iInputModelName)
{
  size_t pp = iInputModelName.find_last_of(L"\\/");

  if ( pp != GRSString::npos )
    return iInputModelName;

  return GRSStringUtils::GetApplDir() + iInputModelName;
}

GRSString GRSSSToNURBS::GetModelNameNoExt(const GRSString& iModelPath)
{
  size_t p_sl = iModelPath.find_last_of(L"\\/");

  if ( p_sl == GRSString::npos )
    return iModelPath;

  size_t p_dot = iModelPath.find_last_of(L".");
  GRSString s = iModelPath.substr(p_sl + 1, p_dot - p_sl - 1);
  return s;
}

GRSSSToNURBS::ModelType GRSSSToNURBS::DefineModelType(const GRSString& iModelPath)
{
  size_t len = iModelPath.length();
  size_t posDot = iModelPath.rfind(L"."[0]);

  if ( len - posDot != 4 )
    return mtUNDEF;

  GRSString ext = iModelPath.substr(posDot + 1);

  GRSString obj_ext = L"obj";
  GRSString obj_ext2 = L"ODJ";

  GRSString stl_ext = L"stl";
  GRSString stl_ext2 = L"STL";

  if ( ( ext.compare(obj_ext) == 0 ) || ( ext.compare(obj_ext2) == 0 ) ) {
    return mtOBJ;
  }

  if ( ( ext.compare(stl_ext) == 0 ) || ( ext.compare(stl_ext2) == 0 ) ) {
    return mtSTL;
  }  
  
  return mtUNDEF;
}

