#pragma once

#ifndef GRSGridTemplate_h
#define GRSGridTemplate_h

#include <vector>

template <class T>
class GRSGridTemplate
{
public:
  GRSGridTemplate() : m_m(0), m_n(0) {}

  GRSGridTemplate(size_t iM, size_t iN) : m_m(iM), m_n(iN) { SetSize(m_m, m_n); }

  void SetSize(size_t iM, size_t iN)
  {
    m_m = iM;
    m_n = iN;

    m_data.clear();    
    m_data.resize(iM * iN);
  }

  void SetSize(size_t iM, size_t iN, const T& iVal)
  {
    m_m = iM;
    m_n = iN;

    m_data.clear();    
    m_data.resize(iM * iN, iVal);
  }

  size_t GetNSz() const { return m_n; }
  size_t GetMSz() const { return m_m; }

  const T& operator () ( size_t iMIdx, size_t iNIdx ) const
  {
    return m_data.at(GetIdx(iMIdx, iNIdx));
  }

  T& operator () ( size_t iMIdx, size_t iNIdx )
  {
    return m_data[GetIdx(iMIdx, iNIdx)];
  }
  
private:

  /*
  *            N
  *       * * * * * *            N            N              N             N
  *    M  * * * * * *    ->  * * * * * *   * * * * * *   * * * * * *   * * * * * *
  *       * * * * * *      
  *       * * * * * * 
  *
  */
  size_t GetIdx(size_t iMIdx, size_t iNIdx) const
  {
    if ( iMIdx > m_m || iNIdx > m_n )
      return -1;

    return iMIdx * m_m + iNIdx;
  }

private:
  size_t m_m;
  size_t m_n;
  std::vector<T> m_data;
};


#endif // GRSGridTemplate_h

