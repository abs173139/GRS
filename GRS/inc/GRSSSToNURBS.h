#pragma once

#ifndef GRSSSToNURBS_h
#define GRSSSToNURBS_h

#include "GRSString.h"
#include "GRSSurfNurbs.h"

class GRSSSToNURBS 
{
public:
  enum ModelType {
    mtUNDEF = 0,
    mtOBJ = 1,
    mtSTL = 2
  };

  GRSSSToNURBS() : m_modelType(mtUNDEF) {}
  ~GRSSSToNURBS();

  bool Run(int argc, _TCHAR* argv[]);

  const GRSSurfNurbsPtrList& GetRes() const { return m_resNurbs; }

  /*
  * Without extension
  */
  const GRSString& GetOutModelPathNoExt() const { return m_outModelPathNoExt; }
  
private:
  ModelType DefineModelType(const GRSString& iModelPath);
  GRSString GetModelFullPath(const GRSString& iInputModelName);

  GRSString GetModelNameNoExt(const GRSString& iModelPath);

private:
  GRSString m_modelPath;
  GRSString m_modelNameNoExt;
  ModelType m_modelType;
  GRSSurfNurbsPtrList m_resNurbs;

  GRSString m_outModelPathNoExt;
};

#endif // GRSSSToNURBS_h

