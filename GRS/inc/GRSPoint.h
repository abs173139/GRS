#pragma once

#ifndef GRSPoint_h
#define GRSPoint_h

typedef OpenMesh::Vec3d GRSPoint;

inline GRSPoint operator*(double iVal, const GRSPoint& iPoint) 
{
  return OpenMesh::VectorT<double,3>(iPoint) *= iVal;
}


#endif // GRSPoint_h
