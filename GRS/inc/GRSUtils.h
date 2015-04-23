#pragma once

#ifndef GRSUtils_h
#define GRSUtils_h

namespace GRSUtils
{
  template<class T_Cont>
  void ClearContainerCallDelete(T_Cont& iCont)
  {
    for ( T_Cont::iterator it = iCont.begin(); it != iCont.end(); ++it ) {
      delete *it;
    }

    iCont.clear();
  }

}

#endif // GRSUtils_h

