//====================================================================
//
// Copyright © 1995 - 2007 MapTel
// All Rights Reserved. 
// Use subject to License Agreement.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Purpose:
//   Definitions of shape structures. 
//
//====================================================================

#ifndef __SHAPETYPE__
#define __SHAPETYPE__
#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// Shape type codes
//--------------------------------------------------------------------

/*
#define SHAPE_TYPE_NULL         0
#define SHAPE_TYPE_POINT        1
#define SHAPE_TYPE_POLYLINE     3
#define SHAPE_TYPE_POLYGON      5
#define SHAPE_TYPE_MULTIPOINT   8
#define SHAPE_TYPE_POINTZ       11
#define SHAPE_TYPE_POLYLINEZ    13
#define SHAPE_TYPE_POLYGONZ     15
#define SHAPE_TYPE_MULTIPOINTZ  18
#define SHAPE_TYPE_POINTM       21
#define SHAPE_TYPE_POLYLINEM    23
#define SHAPE_TYPE_POLYGONM     25
#define SHAPE_TYPE_MULTIPOINTM  28
#define SHAPE_TYPE_MULTIPATCH   31
*/

typedef enum tagSHAPETYPE
{
	SHAPE_TYPE_UNKNOWN		= -1,
    SHAPE_TYPE_NULL         = 0,
    SHAPE_TYPE_POINT        = 1,
    SHAPE_TYPE_POLYLINE     = 3,
    SHAPE_TYPE_POLYGON      = 5,
    SHAPE_TYPE_MULTIPOINT   = 8,
    SHAPE_TYPE_POINTZ       = 11,
    SHAPE_TYPE_POLYLINEZ    = 13,
    SHAPE_TYPE_POLYGONZ     = 15,
    SHAPE_TYPE_MULTIPOINTZ  = 18,
    SHAPE_TYPE_POINTM       = 21,
    SHAPE_TYPE_POLYLINEM    = 23,
    SHAPE_TYPE_POLYGONM     = 25,
    SHAPE_TYPE_MULTIPOINTM  = 28,
    SHAPE_TYPE_MULTIPATCH   = 31,
}
SHAPETYPE;

/* Will become this

...Z becomes .. ZM
new ...Z types added

typedef enum SHAPETYPE
{
	SHAPE_TYPE_UNKNOWN		= -1,
    SHAPE_TYPE_NULL         = 0,
    SHAPE_TYPE_POINT        = 1,
    SHAPE_TYPE_POLYLINE     = 3,
    SHAPE_TYPE_POLYGON      = 5,
    SHAPE_TYPE_MULTIPOINT   = 8,
    SHAPE_TYPE_POINTZ       = 9,
    SHAPE_TYPE_POLYLINEZ    = 10,
    SHAPE_TYPE_POINTZM      = 11,
    SHAPE_TYPE_POLYLINEZM   = 13,
    SHAPE_TYPE_POLYGONZM    = 15,
    SHAPE_TYPE_MULTIPOINTZM = 18,
    SHAPE_TYPE_POLYGONZ     = 19,
    SHAPE_TYPE_POINTM       = 21,
    SHAPE_TYPE_POLYLINEM    = 23,
    SHAPE_TYPE_POLYGONM     = 25,
    SHAPE_TYPE_MULTIPOINTM  = 28,
    SHAPE_TYPE_MULTIPATCH   = 31,
}
SHAPETYPE;
*/

//--------------------------------------------------------------------
// Shape classifications
//--------------------------------------------------------------------

typedef enum SHAPECLASS
{
	SHAPE_CLASS_UNKNOWN		= -1,
    SHAPE_CLASS_POINT        = 0,
    SHAPE_CLASS_POLYLINE     = 1,
    SHAPE_CLASS_POLYGON      = 2,
    SHAPE_CLASS_MULTIPOINT   = 3,
}
SHAPECLASS;

//--------------------------------------------------------------------
// Not a number constants. 
//--------------------------------------------------------------------

#define SHAPE_NAN               -1.7976931348623158e+308        // -DBL_MAX
#define SHAPE_NAN_THRESHOLD     -10e38                          // NaN threhsold value

//--------------------------------------------------------------------
// Point, Measured Point and 3D Point structures.
//--------------------------------------------------------------------

typedef struct SPOINT
{
    double      x;                  // X coordinate
    double      y;                  // Y coordinate
}
SPOINT, *LPSPOINT;

typedef const SPOINT *LPCSPOINT;


typedef struct SPOINTM
{
    double      x;                  // X coordinate
    double      y;                  // Y coordinate
    double      m;                  // Measure value
}
SPOINTM, *LPSPOINTM;

typedef const SPOINTM *LPCSPOINTM;

typedef struct SPOINTZ
{
    double      x;                  // X coordinate
    double      y;                  // Y coordinate
    double      z;                  // Z coordinate
    double      m;                  // Measure value
}
SPOINTZ, *LPSPOINTZ;

typedef const SPOINTZ *LPCSPOINTZ;

//--------------------------------------------------------------------
// Rectangle, Measured Rectangle and 3D Rectangle structures.
//--------------------------------------------------------------------

typedef struct SRECT
{
    double      xMin;
    double      yMin;
    double      xMax;
    double      yMax;
}
SRECT, *LPSRECT;

typedef const SRECT *LPCSRECT;

typedef struct SRECTM
{
    double      xMin;
    double      yMin;
    double      xMax;
    double      yMax;
    double      mMin;
    double      mMax;
}
SRECTM, *LPSRECTM;

typedef const SRECTM *LPCSRECTM;


typedef struct SRECTZ
{
    double      xMin;
    double      yMin;
    double      xMax;
    double      yMax;
    double      zMin;
    double      zMax;
    double      mMin;
    double      mMax;
}
SRECTZ, *LPSRECTZ;

typedef const SRECTZ *LPCSRECTZ;

//--------------------------------------------------------------------
// 2 byte packing
//--------------------------------------------------------------------

#pragma pack(push, 2)
#pragma warning(push)
#pragma warning(disable:4200)   // Allow zero length arrays

//--------------------------------------------------------------------
// Shape Multi Point structure
//--------------------------------------------------------------------

typedef struct SMULTIPOINT
{
    SRECT       Extent;
    long        NumPoints;
    SPOINT      Points[];
}
SMULTIPOINT, *LPSMULTIPOINT;

typedef const SMULTIPOINT *LPCSMULTIPOINT;

//--------------------------------------------------------------------
// Shape structure for lines and polys.
//--------------------------------------------------------------------

typedef struct SPOLY
{
    SRECT       Extent;
    long        NumParts;
    long        NumPoints;
    long        Parts[1];                       // NumParts 
    SPOINT      Points[];                       // NumPoints
}
SPOLY, *LPSPOLY;

typedef const SPOLY *LPCSPOLY;

//--------------------------------------------------------------------
// Generic Shape structure which is union of all shapes.
//--------------------------------------------------------------------

typedef struct SHAPE
{
    long                    ShapeType;
    union
    {
        SPOINT              Point;
        SPOINTM             PointM;
        SPOINTZ             PointZ;
        SPOLY               Poly;               // Single part Polyline/polygon header
        SMULTIPOINT         MultiPoint;         // Multipoint header
    };
}
SHAPE, *LPSHAPE;

typedef const SHAPE *LPCSHAPE;

//--------------------------------------------------------------------
// 
//  For any coordinates (x, y) , the transformed coordinates  (x', y') 
//  can be determined by the following algorithm: 
//
//  x' = x * eM11 + y * eM21 + eDx
//  y' = x * eM12 + y * eM22 + eDy 
//
//  where the transformation matrix is represented by the following: 
//
//      | eM11 eM12 0 | 
//      | eM21 eM22 0 | 
//      | eDx  eDy  1 | 
//
//--------------------------------------------------------------------

typedef struct SXFORM
{
	double	eM11;
	double	eM12;
	double	eM21;
	double	eM22;
	double	eDx;
	double	eDy;
}
SXFORM, *PSXFORM, *LPSXFORM;

#pragma pack(pop)
#pragma warning(pop)

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

#define SXFORM_AffineX(T,X,Y)		((X) * (T).eM11 + (Y) * (T).eM21 + (T).eDx)
#define SXFORM_AffineY(T,X,Y)		((X) * (T).eM12 + (Y) * (T).eM22 + (T).eDy)

#define SXFORM_ScaleX(T,X)			((X) * (T).eM11 + (T).eDx)
#define SXFORM_ScaleY(T,Y)			((Y) * (T).eM22 + (T).eDy)

//--------------------------------------------------------------------
// 
//--------------------------------------------------------------------

#pragma pack(push, 2)
#pragma warning(push)

typedef ULONGLONG SHAPEID;					// Type for ID values

typedef struct SPOINTID
{
	union
	{
		SPOINT		Point;					// 2D point
		SPOINTM		PointM;					// 2D point + measure
		SPOINTZ		PointZ;					// 3D point + measure
	};
	SHAPEID		ID;						// Identifier
} SPOINTID, *LPSPOINTID;

typedef const SPOINTID *LPCSPOINTID;

#pragma pack(pop)
#pragma warning(pop)

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif

