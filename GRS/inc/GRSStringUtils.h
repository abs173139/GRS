#pragma once

#ifndef GRSStringUtils_h
#define GRSStringUtils_h

#include "GRSString.h"

namespace GRSStringUtils {

  GRSString GetApplDir();
  GRSString GetProjectRootDir();
  GRSString GetInputTestPath(const GRSString& iTest);
  GRSString GetOutputTestPath(const GRSString& iTest);
  GRSString GetTempDir();

  // all after last slash or backslash is cutted
  GRSString CutAfterLastSlashOrBackslash(const GRSString& iStr);

  int WtoC(const GRSString& iWStr, GRSStringC& oCStr);
  int CtoW(const GRSStringC& iCStr, GRSString& oWStr);

  
}

#endif // GRSStringUtils_h
