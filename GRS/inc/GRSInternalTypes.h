#pragma once

#ifndef GRSInternalTypes_h
#define GRSInternalTypes_h

#include "GRSPoint.h"
#include "GRSGridTemplate.h"

#include <vector>

typedef GRSGridTemplate<double>   GRSDoubleGrid;
typedef GRSGridTemplate<GRSPoint>   GRSPointsGrid;

typedef std::vector<double> GRSDoubleVector;
typedef std::vector<GRSPoint> GRSPointVector;
typedef std::vector<GRSPoint>::iterator GRSPointVectorIterator;

#endif // GRSInternalTypes_h

