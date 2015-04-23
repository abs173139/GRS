#include "GRSStdAfx.h"
#include "GRSStringUtils.h"
#include "Windows.h"

static const size_t BUF_SZ = 1024;
static char charBuf[BUF_SZ];
static wchar_t wcharBuf[BUF_SZ];

GRSString GRSStringUtils::CutAfterLastSlashOrBackslash(const GRSString& iStr)
{
  size_t posLastSlashOrBackSl = iStr.find_last_of(L"\\/", iStr.length() - 2);
  return iStr.substr(0, posLastSlashOrBackSl + 1);
}

GRSString GRSStringUtils::GetApplDir()
{
  wchar_t fullPath[BUF_SZ];
  GetModuleFileName(0, fullPath, BUF_SZ);
  GRSString s = fullPath;
  return CutAfterLastSlashOrBackslash(s);
}

GRSString GRSStringUtils::GetProjectRootDir()
{
  GRSString fullPath = GetApplDir();
  return CutAfterLastSlashOrBackslash(fullPath);
}

GRSString GRSStringUtils::GetInputTestPath( const GRSString& iTest )
{
  GRSString modelsPath = GetProjectRootDir();
  modelsPath += L"\\GRSModels\\";
  modelsPath += iTest;
  return modelsPath;
}

GRSString GRSStringUtils::GetOutputTestPath( const GRSString& iTest )
{
  GRSString outpTestName = GetTempDir();
  outpTestName += L"\\";
  outpTestName += iTest;
  return outpTestName;
}

GRSString GRSStringUtils::GetTempDir()
{
  GRSString tmpDir = GetProjectRootDir();
  tmpDir += L"\\GRSTemp";
  return tmpDir;
}

int GRSStringUtils::WtoC(const GRSString& iWStr, GRSStringC& oCStr)
{
  int rc = WideCharToMultiByte( CP_UTF8, 0, iWStr.c_str(), -1, charBuf, BUF_SZ, 0, 0 );

  if ( rc == 0 ) { // number of bytes written
    return 1;
  }

  oCStr = charBuf;
  return 0;
}

int GRSStringUtils::CtoW(const GRSStringC& iCStr, GRSString& oWStr)
{
  int rc = MultiByteToWideChar( CP_UTF8, 0, iCStr.c_str(), -1, wcharBuf, BUF_SZ );

  if ( rc == 0 ) { // number of bytes written
    return 1;
  }

  oWStr = wcharBuf;
  return 0;
}