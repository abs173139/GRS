#pragma once

#ifndef GRSSurfNurbs_h
#define GRSSurfNurbs_h

#include "GRSPoint.h"
#include "GRSInternalTypes.h"

#include <list>
class GRSSurfNurbs;
typedef std::list<GRSSurfNurbs*> GRSSurfNurbsPtrList;

class GRSSurfNurbs {
public:

  GRSSurfNurbs() : m_degU(0), m_degV(0) {}

  GRSSurfNurbs( size_t iUDeg, 
                size_t iVDeg,
                const GRSPointsGrid& iaPts,
                const GRSDoubleGrid& iaWeights,
                const GRSDoubleVector& iaUKnots, 
                const GRSDoubleVector& iaVKnots ) 
                : m_degU (iUDeg)
                , m_degV (iVDeg)
                , m_controlPoints ( iaPts )
                , m_weights ( iaWeights )
                , m_knotsU ( iaUKnots )
                , m_knotsV ( iaVKnots )
  {
  }

  void Set( size_t iUDeg, 
            size_t iVDeg,
            const GRSPointsGrid& iaPts,
            const GRSDoubleGrid& iaWeights,
            const GRSDoubleVector& iaUKnots, 
            const GRSDoubleVector& iaVKnots ) 
  {
    m_degU = iUDeg;
    m_degV = iVDeg;
    m_controlPoints = iaPts;
    m_weights = iaWeights;
    m_knotsU = iaUKnots;
    m_knotsV = iaVKnots;
  }

  size_t GetDegU() const { return m_degU; }
  size_t GetDegV() const { return m_degV; }

  const GRSPointsGrid& GetPoints() const { return m_controlPoints; }
  const GRSDoubleGrid& GetWeights() const { return m_weights; }
  const GRSDoubleVector& GetKnotsU() const { return m_knotsU; }
  const GRSDoubleVector& GetKnotsV() const { return m_knotsV; }


private:
  size_t m_degU;
  size_t m_degV;

  GRSPointsGrid m_controlPoints;
  GRSDoubleGrid m_weights;
  GRSDoubleVector m_knotsU;
  GRSDoubleVector m_knotsV;  
};


#endif // GRSSurfNurbs_h

