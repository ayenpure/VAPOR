#ifndef _Proj4API_h_
#define	_Proj4API_h_

#include <vapor/MyBase.h>

namespace VAPoR {

//  
//! \class Proj4API
//! \brief Wrapper for proj4 C API
//! 
//! \author John Clyne
//! 
//! This class provides a convience wrapper for the proj4 Cartographic
//! Projections Library http://trac.osgeo.org/proj/
//!
class VDF_API Proj4API : public Wasp::MyBase {

public:

	Proj4API();
	~Proj4API();

	//! Initialize the class 
	//!
	//! Initializes the class with source and destination proj4
	//! transformation strings. 
	//!
	//! \param[in] srcdef The source proj4 transformation definition. If
	//! empty, the string "+proj=latlong" is used.
	//! \param[in] dstdef The destintation proj4 transformation definition. If
	//! empty, the string "+proj=latlong" is used.
	//!
	//! \retval status Retruns a negative int on failure 
	//!
	//! \sa pj_init_plus()
	//
	int Initialize(string srcdef, string dstdef);

	//! Transform coordinates 
	//!
	//! Transforms coordinates based on defintions of the source
	//! and destination proj4 transformation definitions passed to 
	//! Initialize(). Transformations are performed between 
	//! Geographic coordinates (latitude and longitude) and Cartographic 
	//! coordinates (Cartesian) as specified by the transformation
	//! definitions. Cartographic coordinates are referred to as the
	//! Projection Coordinate System (PCS). Default units for the PCS
	//! are meters on the ground. Geographic coordinates are always
	//! in degrees.
	//! 
	//!
	//! \note As with the proj4 C library the transformations are 
	//! performed in place, modifiying the input values
	//!
	//! \param[in,out] x array of longitudes or PCS X values
	//! \param[in,out] y array of latitudes or PCS Y values
	//! \param[in] n num elements in x, y, and z
	//! \param[in] offset Offset between adjacent values in the input and
	//! output arrays.
	//!
	//! \retval status Retruns a negative int on failure 
	//!
	//! \sa Initialize(), pj_transform()
	//!
	int Transform(double *x, double *y, size_t n, int offset=1) const;
	int Transform(double *x, double *y, double *z, size_t n, int offset=1) const;
	int Transform(float *x, float *y, size_t n, int offset=1) const;
	int Transform(float *x, float *y, float *z, size_t n, int offset=1) const;

	//! Return true of source projection definition is lat-long
	//!
	//! This method returns true iff the source projection definition
	//! is geographic (i.e. +proj=latlong). If true, subsequent transforms
	//! expect input values to be in geographic coordinates (i.e. degrees)
	//! False is returned otherwise
	//!
	//! \sa Initialize(), pj_is_latlong()
	//
	bool IsLatLonSrc() const;

	//! Return true of destination projection definition is lat-long
	//!
	//! This method returns true iff the destination projection definition
	//! is geographic (i.e. +proj=latlong). If true, subsequent transforms
	//! will return output values in geographic coordinates (i.e. degrees)
	//! False is returned otherwise
	//!
	//! \sa Initialize(), pj_is_latlong()
	//
	bool IsLatLonDst() const;

	bool IsGeocentSrc() const;
	bool IsGeocentDst() const;

	//! Return the current source projection definition string
	string GetSrcStr() const;

	//! Return the current destination projection definition string
	string GetDstStr() const;

	int Transform(
		string srcdef, string dstdef,
		double *x, double *y, double *z, size_t n, int offset
	) const; 
	int Transform(
		string srcdef, string dstdef,
		float *x, float *y, float *z, size_t n, int offset
	) const; 

	//! Return the error string generated by the proj4 C API for the
	//! most recent error
	//!
	//! \sa pj_strerrno()

	string ProjErr() const;

	//! Clamp the input values to bounds permitted by the source
	//! projection. If the source projection is not recognized the
	//! method is a no-op
	//
	void Clamp(double *x, double *y, size_t n, int offset) const;


	//! Return true if the destination projection is cylindrical
	//!
	//! Returns true if the destination projection string is either
	//! cylindrical "eqc", or mercator "merc"
	//
	bool IsCylindrical() const;

private:
 void* _pjSrc;
 void* _pjDst;

 int _Initialize(
	string srcdef, string dstdef, void **pjSrc, void **pjDst
 ) const; 

 int _Transform(
	void *pjSrc, void *pjDst,
	double *x, double *y, double *z, size_t n, int offset
 ) const;

 int _Transform(
	void *pjSrc, void *pjDst,
	float *x, float *y, float *z, size_t n, int offset
 ) const;
	
};
};

#endif
