//====================================================================
//
// Copyright © 1995 - 2010 MapTel
// All Rights Reserved. 
// Use subject to License Agreement.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
// Purpose:
//   Prototype definitions for ArcPad extension DLL functions
//   and definitions of structures, flags and constants.
//
//====================================================================

#ifndef __APEX__
#define __APEX__

#pragma once
#include <windows.h>
#include <tchar.h>
#include <objidl.h>
#include "Shapes.h"
#include "Instrument.h"

//--------------------------------------------------------------------
//
// ArcPad Extension DLL Definitions
//
//--------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------

#define APEXDECL __declspec(dllexport)

//--------------------------------------------------------------------

DECLARE_HANDLE(HLAYER);
DECLARE_HANDLE(HFEATURE);
DECLARE_HANDLE(HGPS);
DECLARE_HANDLE(HAUX);
DECLARE_HANDLE(HRANGEFINDER);
DECLARE_HANDLE(HSYMBOL);

//--------------------------------------------------------------------

#define APEX_EXTENSION                          _T("dll")

//--------------------------------------------------------------------

#define APEX_NOT_IMPLEMENTED                    -1
#define APEX_FALSE                              0
#define APEX_TRUE                               1

//--------------------------------------------------------------------

#define APEX_PROP_FLAGS                         0           // G- Reserved
#define APEX_PROP_NAME                          1           // G- One line descriptive name of extension
#define APEX_PROP_CODENAME                      2           // G- 4 character (DWORD) name of extension
#define APEX_PROP_LCID                          3           // -S ArcPad's current locale
#define APEX_PROP_DEBUG                         4           // -S ArcPad's current debug flags
                                                
#define APEX_PROP_TOOL_COUNT                    10          // G- Return number of tools
//#define APEX_PROP_TOOL_TBNAME                 11          // G- Toolbar caption
//#define APEX_PROP_TOOL_TBCAPTION              12          // G- Toolbar caption
#define APEX_PROP_TOOL_TYPE                     20          // G- Return tool type
#define APEX_PROP_TOOL_NAME                     21          // G- Tool name
#define APEX_PROP_TOOL_ICON                     22          // G- Return icon index

#define APEX_PROP_APPKEY						100			// -S * Virtual key code assigned

#define APEX_PROP_GPS_ACTIVE                    200         // -S (DWORD)pInfo = CODENAME if activating, or NULL 
#define APEX_PROP_GPS_LASTPOSITION              201         // -S (SPOINTZ*)pInfo = Last known position

//--------------------------------------------------------------------

#define APEX_FLAG_NONE                          0x00000000

//--------------------------------------------------------------------

#define APEX_TYPE_UTILITY                       0x00000000
#define APEX_TYPE_LAYER_VECTOR                  0x00000001
#define APEX_TYPE_LAYER_RASTER                  0x00000002
#define APEX_TYPE_GPS                           0x00000010
#define APEX_TYPE_RANGEFINDER					0x00000020
#define APEX_TYPE_CAMERA						0x00000100
#define APEX_TYPE_PROJECTION					0x00001000		// Map projection type
#define APEX_TYPE_TRANSFORM						0x00002000		// Datum transformation method

//--------------------------------------------------------------------

#define APEX_TOOL_CMD_MASK                      0x000000FF
#define APEX_TOOL_CMD_GENERIC                   0x00000000
#define APEX_TOOL_CMD_FIND                      0x00000001
                                                
#define APEX_TOOL_GROUP_MASK                    0x0000FF00
#define APEX_TOOL_GROUP_GENERIC                 0x00000000
#define APEX_TOOL_GROUP_LAYER                   0x00000100
#define APEX_TOOL_GROUP_GPS                     0x00000200
                                                
#define APEX_TOOL_POS_MASK                      0x00FF0000
#define APEX_TOOL_POS_TOOLSMENU                 0x00000000
#define APEX_TOOL_POS_FINDMENU                  0x00010000
#define APEX_TOOL_POS_GPSMENU                   0x00020000
//#define APEX_TOOL_POS_TOOLBAR                 0x00800000
                                                
                                                // General tool (tools menu)
#define APEX_TOOL_TOOL                          (APEX_TOOL_CMD_GENERIC | APEX_TOOL_GROUP_GENERIC)
                                                // General layer tool (tools menu)
#define APEX_TOOL_LAYERTOOL                     (APEX_TOOL_CMD_GENERIC | APEX_TOOL_GROUP_LAYER)
                                                // Layer - Find tool
#define APEX_TOOL_FIND                          (APEX_TOOL_CMD_FIND | APEX_TOOL_GROUP_LAYER)
                                                // General tool (GPS menu)
#define APEX_TOOL_GPS                           (APEX_TOOL_CMD_GENERIC | APEX_TOOL_GROUP_GPS)

//--------------------------------------------------------------------
// * = Mandatory

#define APEX_LAYER_PROP_FLAGS                   0           // G- *
#define APEX_LAYER_PROP_EXTENT                  1           // G- * Extents of layer or feature (if hFeature != NULL)
#define APEX_LAYER_PROP_NAME                    2           // G- Descriptive name of layer
#define APEX_LAYER_PROP_COMMENTS                3           // G- Descriptive comments for layer
#define APEX_LAYER_PROP_PROJECTION              4           // G- Projection string
#define APEX_LAYER_PROP_FILEFILTER              5           // G- Filter string (See additional values for nIndex)
#define APEX_LAYER_PROP_QUICKDRAW               6           // G- Does the extension support QuickDraw capabilities

#define APEX_LAYER_PROP_FEATURE                 100         // G- Entire feature into memory
#define APEX_LAYER_PROP_FEATURE_SYMBOL          101         // G- Symbol number for a specified feature
#define APEX_LAYER_PROP_FEATURE_FLAGS           102         // G- Feature flags for layer
                                                
#define APEX_LAYER_PROP_FIELD_COUNT             200         // G- Number of attribute fields
#define APEX_LAYER_PROP_FIELD_NAME              201         // G- Name of field 
#define APEX_LAYER_PROP_FIELD_TYPE              202         // G- Field data type
#define APEX_LAYER_PROP_FIELD_LENGTH            203         // G- Field length
#define APEX_LAYER_PROP_FIELD_PRECISION         204         // G- Field precision ('N' fields only)
#define APEX_LAYER_PROP_FIELD_VALUE             205         // GS Field value
                                                
#define APEX_LAYER_PROP_SYMBOL_COUNT            300         // G- Number of symbols
#define APEX_LAYER_PROP_SYMBOL_LABEL            301         // G- Symbol legend label
#define APEX_LAYER_PROP_SYMBOL_VALUE            302         // G- Symbol value
#define APEX_LAYER_PROP_SYMBOL_STATE            303         // GS Symbol states (see flags)
                                                
#define APEX_LAYER_PROP_GEOMETRY                400         // GS Feature geometry (see SHAPE type for structure details)
#define APEX_LAYER_PROP_GEOMETRYSYMBOL          401			// GS
#define APEX_LAYER_PROP_TEXT                    402         // GS
#define APEX_LAYER_PROP_TEXTSYMBOL              403			// GS

                                                
//#define APEX_LAYER_PROP_EDIT_FLAGS            500         // G- Edit capability flags
#define APEX_LAYER_PROP_EDIT_STATE              501         // -S Set/unset layer editing state

//--------------------------------------------------------------------

// Constants for APEX_LAYER_PROP_FLAGS

#define APEX_LAYER_FLAG_NONE                    0x00000000
#define APEX_LAYER_FLAG_REPROJECT               0x00000001  // Reporojection of feature coordinates is supported
#define APEX_LAYER_FLAG_AUX                     0x00000002  // Layer requires use of the AUX port
#define APEX_LAYER_FLAG_DYNAMIC                 0x00000004  // Layer contents are dynamic (changing)
#define APEX_LAYER_FLAG_EDITABLE                0x00000008  // Editing of features is supported
                                                
// Constants for APEX_LAYER_PROP_FEATURE_FLAGS
                                                
#define APEX_LAYER_FEATURE_FLAG_NONE            0x00000000
#define APEX_LAYER_FEATURE_FLAG_POINT           0x00000001  // Point feature type supported
#define APEX_LAYER_FEATURE_FLAG_POLYLINE        0x00000002  // Polyline feature type supported
#define APEX_LAYER_FEATURE_FLAG_POLYGON         0x00000004  // Polygon feature type supported
#define APEX_LAYER_FEATURE_FLAG_Z               0x00010000  // Features support 'Z' value
#define APEX_LAYER_FEATURE_FLAG_MEASURE         0x00020000  // Features support measure value

#define APEX_LAYER_FEATURE_FLAG_GEOMETRYSYMBOL  0x00100000  // 
#define APEX_LAYER_FEATURE_FLAG_POINTTEXT       0x01000000  // Text On Point feature supported
#define APEX_LAYER_FEATURE_FLAG_POLYLINETEXT    0x02000000  // Text On Polyline feature supported
#define APEX_LAYER_FEATURE_FLAG_POLYGONTEXT     0x04000000  // Text On Polygon feature supported
#define APEX_LAYER_FEATURE_FLAG_TEXTSYMBOL		0x10000000  // 

// Constants APEX_LAYER_PROP_SYMBOL_STATE

#define APEX_SYMBOL_HIDDEN                      0x00000000
#define APEX_SYMBOL_VISIBLE                     0x00000001

// Constants for APEXAPI_LayerDialogFeature
                                                
#define APEX_LAYER_FEATURE_DIALOG_IDENTIFY      0x00000001  // Feature dialog is to be used for identify (read-only)
#define APEX_LAYER_FEATURE_DIALOG_EDIT          0x00000002  // Feature dialog is to be used for editing
#define APEX_LAYER_FEATURE_DIALOG_CREATE        0x00000004  // Feature dialog is to be used for creation of a new feature

// nIndex values for APEX_LAYER_FILEFILTER property

#define APEX_LAYER_FILEFILTER_FILTER			0			// File filter string eg "JPEG Files (*.jpg)|*.jpg;*.jpeg;*.jfif"
#define APEX_LAYER_FILEFILTER_DEFAULTEXT		1			// Default file extension eg "jpg"

//--------------------------------------------------------------------

#define APEX_FIELD_CHAR                         'C'
#define APEX_FIELD_NUMERIC                      'N'
#define APEX_FIELD_DATE                         'D'
#define APEX_FIELD_LOGICAL                      'L'

//--------------------------------------------------------------------

#define APEX_GPS_FLAG_NONE                      0x00000000
#define APEX_GPS_FLAG_INITPOSITION              0x00000001

#define APEX_GPS_CODENAME_NMEA                  0x41454D4E      // NMEA = 0x4E4D4541
#define APEX_GPS_CODENAME_TSIP                  0x50495354      // TSIP = 0x54534950
#define APEX_GPS_CODENAME_EARTHMATE             0x54524145      // EART = 0x45415254
#define APEX_GPS_CODENAME_PLGR                  0x52474C50      // PLGR = 0x504C4752
#define APEX_GPS_CODENAME_SIRF					0x46526953		// SiRF = 0x53695246

//--------------------------------------------------------------------

#define APEX_MAX_PROPERTYNAME                   64              // Maximum length of a property name
#define APEX_MAX_PROPERTYVALUE                  1024            // Maximum length of a property value

//--------------------------------------------------------------------

#define WM_ARCPAD                               (WM_APP + 0x100)
#define WM_ARCPAD_SCRIPT                        (WM_ARCPAD + 1)
#define WM_ARCPAD_GETFUNCTION                   (WM_ARCPAD + 2)
#define WM_ARCPAD_EXEVENT                       (WM_ARCPAD + 3)
#define WM_ARCPAD_GPSRXREADY                    (WM_ARCPAD + 4)
#define WM_ARCPAD_ISREADY						(WM_ARCPAD + 5)

//--------------------------------------------------------------------

#define COPYDATA_CMD_SCRIPT                     1
#define COPYDATA_CMD_GPSSEND                    2
#define COPYDATA_CMD_AUXSEND                    3
#define COPYDATA_CMD_RANGEFINDERSEND            4

//--------------------------------------------------------------------
// Function pointer
//--------------------------------------------------------------------

#define APEX_FN_PROJECT                         1                   // Project to current view coordinates
#define APEX_FN_UNPROJECT                       2                   // Unproject from view coordinates
#define APEX_FN_DCPROJECT                       3                   // Project to device coordinates
#define APEX_FN_DCUNPROJECT                     4                   // UnProject from device coordinates
#define APEX_FN_COLORPICKER                     5                   // Color picker dialog
#define APEX_FN_FONTPICKER                      6                   // Font picker dialog
#define APEX_FN_EVALUATE                        7                   // Evaluate a script expression
#define APEX_FN_PAINTLAYER						8					// Paint the layer's DC to the screen
#define APEX_FN_JPEGLOAD						9					// Load HBITMAP from JPEG image
#define APEX_FN_JPEGSAVE						10					// Save HBITMAP to JPEG image
#define APEX_FN_JPEGROTATE						11					// Rotate JPEG image
#define APEX_FN_IMAGEPROPSOPEN					12					// Open image properties
#define APEX_FN_IMAGEPROPSCLOSE					13					// Close image properties
#define APEX_FN_IMAGEPROPSGET					14					// Get image property
#define APEX_FN_IMAGEPROPSSET					15					// Set image property
#define APEX_FN_SYMBOLCREATE					16					// Create a symbol object
#define APEX_FN_SYMBOLDESTROY					17					// Destroy a symbol object
#define APEX_FN_SYMBOLGETXML					18					// Retrieve a symbol's XML definition
#define APEX_FN_SYMBOLDRAWSHAPE					19					// Draw a feature using a symbol
#define APEX_FN_SYMBOLDRAWMARKER				20
#define APEX_FN_SYMBOLDRAWPOLYLINE				21
#define APEX_FN_SYMBOLDRAWPOLYGON				22
#define APEX_FN_SYMBOLDRAWMARKERTEXT			23
#define APEX_FN_SYMBOLDRAWPOLYLINETEXT			24
#define APEX_FN_SYMBOLDRAWPOLYGONTEXT			25


typedef enum APEX_JXFORM
{
	APEX_JXFORM_NONE,				// No transformation 
	APEX_JXFORM_FLIP_HORZ,			// Horizontal flip 
	APEX_JXFORM_FLIP_VERT,			// Vertical flip 
	APEX_JXFORM_TRANSPOSE,			// Transpose across UL-to-LR axis 
	APEX_JXFORM_TRANSVERSE,			// Transpose across UR-to-LL axis 
	APEX_JXFORM_ROTATE_90,			// 90-degree clockwise rotation 
	APEX_JXFORM_ROTATE_180,			// 180-degree rotation 
	APEX_JXFORM_ROTATE_270			// 270-degree clockwise (or 90 ccw)
} APEX_JXFORM;

typedef int 		(CALLBACK *APEX_PFN_PROJECT)(HLAYER hLayer, const SPOINT *pPoints, int nPoints, SPOINT *pViewPoints);
typedef int 		(CALLBACK *APEX_PFN_UNPROJECT)(HLAYER hLayer, const SPOINT *pViewPoints, int nPoints, SPOINT *pPoints);
typedef int 		(CALLBACK *APEX_PFN_DCPROJECT)(HLAYER hLayer, const SPOINT *pPoints, int nPoints, POINT *pDCPoints);
typedef int 		(CALLBACK *APEX_PFN_DCUNPROJECT)(HLAYER hLayer, const POINT *pDCPoints, int nPoints, SPOINT *pPoints);
typedef COLORREF	(CALLBACK *APEX_PFN_COLORPICKER)(HWND hWnd, COLORREF rgb);
typedef int			(CALLBACK *APEX_PFN_FONTPICKER)(HWND hWnd, LOGFONT *pLogFont);
typedef HRESULT		(CALLBACK *APEX_PFN_EVALUATE)(LPCWSTR pExpression, VARIANT *pResult, HANDLE hContext);
typedef void		(CALLBACK *APEX_PFN_PAINTLAYER)(HLAYER hLayer, HDC hDC, int Progress);
typedef HBITMAP		(CALLBACK *APEX_PFN_JPEGLOAD)(LPCTSTR pFilename);
typedef int			(CALLBACK *APEX_PFN_JPEGSAVE)(LPCTSTR pFilename, HBITMAP hBitmap, DWORD Quality);
typedef int			(CALLBACK *APEX_PFN_JPEGROTATE)(LPCTSTR pFromFilename, LPCTSTR pToFilename, APEX_JXFORM JXForm);
typedef HANDLE		(CALLBACK *APEX_PFN_IMAGEPROPSOPEN)(LPCTSTR pFilename);
typedef void		(CALLBACK *APEX_PFN_IMAGEPROPSCLOSE)(HANDLE hImage);
typedef HRESULT		(CALLBACK *APEX_PFN_IMAGEPROPSGET)(HANDLE hImage, int nTag, VARIANT* pValue);
typedef HRESULT		(CALLBACK *APEX_PFN_IMAGEPROPSSET)(HANDLE hImage, int nTag, VARIANT* pValue);
typedef HSYMBOL		(CALLBACK *APEX_PFN_SYMBOLCREATE)(LPCTSTR pDefinitionXML);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDESTROY)(HSYMBOL hSymbol);
typedef int			(CALLBACK *APEX_PFN_SYMBOLGETXML)(HSYMBOL hSymbol, LPTSTR pDefinition);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWSHAPE)(HDC hDC, HSYMBOL hSymbol, HLAYER hLayer, LPSHAPE pShape, HSYMBOL hTextSymbol, LPCTSTR pText, double Scale);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWMARKER)(HDC hDC, HSYMBOL hSymbol, int x, int y, double Angle, double Scale, SIZE *pMarkerSize);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWPOLYLINE)(HDC hDC, HSYMBOL hSymbol, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWPOLYGON)(HDC hDC, HSYMBOL hSymbol, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWMARKERTEXT)(HDC hDC, HSYMBOL hSymbol, LPCTSTR pText, RECT *pRect, double Angle, double Scale);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWPOLYLINETEXT)(HDC hDC, HSYMBOL hSymbol, LPCTSTR pText, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale);
typedef HRESULT		(CALLBACK *APEX_PFN_SYMBOLDRAWPOLYGONTEXT)(HDC hDC, HSYMBOL hSymbol, LPCTSTR pText, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale);

//--------------------------------------------------------------------
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

typedef struct APEX_XFORM
{
    double          eM11;
    double          eM12;
    double          eM21;
    double          eM22;
    double          eDx;
    double          eDy;
} APEX_XFORM;

//--------------------------------------------------------------------
// Transformation helper macros

#define APEX_XFormX(T,X,Y)      ((X) * (T).eM11 + (Y) * (T).eM21 + (T).eDx)
#define APEX_XFormY(T,X,Y)      ((X) * (T).eM12 + (Y) * (T).eM22 + (T).eDy)

//--------------------------------------------------------------------
// Layer update

typedef struct APEX_LAYER_UPDATE
{
	HDC				hWindowDC;					// Screen	DC for progressive drawing
	HDC				hBitmapDC;					// Memory DC that has hBitmap is selected into	it
	HBITMAP			hBitmap;
	LPVOID			pBitmap;					//	Bitmap data	(DIBsection)
	HBITMAP			hTranparentMask;			
	LPVOID			pTransparentMask;			// Bitmap data (DIBsection)
	SRECT			MapExtent;					// Requested	extent in map coordinates, module returns actual extent	of data	in hBitmap
	RECT			BitmapExtent;				// Size	of Bitmap, module may update this to actual	size of	bitmap used
	SIZE			DisplaySize;				// Intended pixel resolution	to display to. This	is so the extension	can	choose an 
												// appropriate scale of	data if	it supports	some sort of hierarchy.. eg	MrSID, PNG?
} 
APEX_LAYER_UPDATE;

//--------------------------------------------------------------------

typedef struct APEX_LAYER_DRAW
{
    HDC             hDC;                        // Handle to rendering device context
    HDC             hWindowDC;                  // Handle to current view window device context
    SRECTZ          Extent;                     // Extents of rendering context in map coordinates
    double          MapScale;                   // Map scale of rendering context
    RECT            WindowExtent;               // Extent of window (Device units)
    APEX_XFORM      ToWindow;                   // Affine transform from map to window coordinates
    APEX_XFORM      ToMap;                      // Affine transform from window to map coordinates
	double			ReferenceScale;				// Reference scale for layer
	HDC				hLayerDC;					// Handle to layer temporary device context
	COLORREF		TransparentColor;			// Transparent color
	double			Transparency;				// Transparency : 1.0 = 0% = Transparent, 0.0 = 100% = Opaque
	BYTE			ColorTransform[3][256];		// RGB Transformation lookup tables
	WORD			ViewDrawMode;				// 0 = Normal, 1 = QuickDraw
	WORD			QuickDrawStyle;				// 0 = Invisible, 1 = Fast, 2 = Detail
	WORD			QuickDrawQuality;			// 0 = Normal, 1=1/2, 2=1/4, 3-1/16, 4=1/32
}
APEX_LAYER_DRAW;

//--------------------------------------------------------------------
// Drawing flags
//
//#define APEX_DRAW_NORMAL                  0x00000000
//#define APEX_DRAW_HILITE                  0x00000001

//--------------------------------------------------------------------
// Query flags

#define APEX_QUERY_NEAREST                  0x00000001
#define APEX_QUERY_SEQUENTIAL               0x00000002

//--------------------------------------------------------------------

#define APEX_FEATURE_NULL                   ((HFEATURE)0)           // Same as NULL : ie No feature

//--------------------------------------------------------------------
// Helper macros
//--------------------------------------------------------------------

// Test if pathname is a directory

#define APEX_IsDirectory(P)                 ((GetFileAttributes(P) & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY)

// Send message to ArcPad to return a function pointer

#define APEX_GetFunction(H, FN)             (APEX_PFN_##FN)SendMessage(H, WM_ARCPAD_GETFUNCTION, APEX_FN_##FN, 0)

// Test is a non-zero flag value is set

#define APEX_IsFlagSet(V, F)                (((V) & (F)) == (F))

//--------------------------------------------------------------------
// Projection/Transformation
//--------------------------------------------------------------------

// Projection paramaters

#define APEX_PRJ_PARM_X0      0 	// False easting                                    
#define APEX_PRJ_PARM_Y0      1 	// False northing                                   

#define APEX_PRJ_PARM_LAM0    2 	// Central meridian, Longitude of origin            
#define APEX_PRJ_PARM_LON0    2 	// = APEX_PRJ_PARM_LAM0                             
#define APEX_PRJ_PARM_PHI0    6 	// Central parallel, Latitude of origin             
#define APEX_PRJ_PARM_LAT0    6 	// = APEX_PRJ_PARM_PHI0                             

#define APEX_PRJ_PARM_PHI1    3 	// Standard parallel 1, Latitude of 1st point       
#define APEX_PRJ_PARM_LAT1    3 	// = APEX_PRJ_PARM_PHI1                             
#define APEX_PRJ_PARM_LAM1    8 	// Longitude of 1st point                           
#define APEX_PRJ_PARM_LON1    8 	// = APEX_PRJ_PARM_LAM1                             

#define APEX_PRJ_PARM_PHI2    4 	// Standard parallel 2, Latitude of 2nd point       
#define APEX_PRJ_PARM_LAT2    4 	// = APEX_PRJ_PARM_PHI2                             
#define APEX_PRJ_PARM_LAM2    9 	// Longitude of 2nd point                           
#define APEX_PRJ_PARM_LON2    9 	// = APEX_PRJ_PARM_LAM2                             

#define APEX_PRJ_PARM_LAMC   10 	// Longitude of Center                              
#define APEX_PRJ_PARM_LONC   10 	//  == APEX_PRJ_PARM_LAMC                           
#define APEX_PRJ_PARM_PHIC   11 	// Latitude of Center                               
#define APEX_PRJ_PARM_LATC   11 	//  == APEX_PRJ_PARM_PHIC                           

#define APEX_PRJ_PARM_K0      5 	// Scale factor                                     
#define APEX_PRJ_PARM_ALPHA   7 	// Azimuth                                          
#define APEX_PRJ_PARM_HEIGHT 15 	// Height                                           

#define APEX_PRJ_PARM_XS     12 	// X Scale                                          
#define APEX_PRJ_PARM_YS     13 	// Y Scale                                          
#define APEX_PRJ_PARM_XYR    14 	// XY Plane Rotation                                

#define APEX_PRJ_PARM_OPTION 15 	// Option                                           

// Transform method parameters

#define APEX_PRJ_PARM_DX 	 0 		// X-axis translation                               
#define APEX_PRJ_PARM_DY 	 1 		// Y-axis translation                               
#define APEX_PRJ_PARM_DZ 	 2 		// Z-axis translation                               
#define APEX_PRJ_PARM_RX 	 3 		// X-axis rotation                                  
#define APEX_PRJ_PARM_RY 	 4 		// Y-axis rotation                                  
#define APEX_PRJ_PARM_RZ 	 5 		// Z-axis rotation                                  
#define APEX_PRJ_PARM_DS 	 6 		// Scale difference                                 
#define APEX_PRJ_PARM_XCR	 7 		// X coord of Rotation Origin                       
#define APEX_PRJ_PARM_YCR	 8 		// Y coord of Rotation Origin                       
#define APEX_PRJ_PARM_ZCR	 9 		// Z coord of Rotation Origin                       
#define APEX_PRJ_PARM_ND 	15 		// Name of Dataset for Grid based Geog transforms   

//--------------------------------------------------------------------

#define APEX_PRJ_NAME_MAX	64		// Maximum name size
#define APEX_PRJ_PARAM_MAX	64		// Maximum number of parameters

// Spheroid data

typedef struct APEX_PRJ_SPHEROID
{
	DWORD		Code;
	CHAR		Name[APEX_PRJ_NAME_MAX];
	double		Axis;
	double		Flattening;
} APEX_PRJ_SPHEROID;

typedef APEX_PRJ_SPHEROID *APEX_PRJ_PSPHEROID;
typedef APEX_PRJ_SPHEROID const *APEX_PRJ_PCSPHEROID;

//--------------------------------------------------------------------
// Extension Common Routines
//--------------------------------------------------------------------

#define APEXAPI_APExInitialize              APEXDECL LRESULT    APExInitialize(HWND hWnd)
#define APEXAPI_APExTerminate               APEXDECL LRESULT    APExTerminate(void)
#define APEXAPI_APExDialogAbout             APEXDECL LRESULT    APExDialogAbout(HWND hWnd)
#define APEXAPI_APExDialogProperties        APEXDECL LRESULT    APExDialogProperties(HWND hWnd)
#define APEXAPI_APExEscape                  APEXDECL HRESULT    APExEscape(HANDLE hObject, VARIANT *pParam1, VARIANT *pParam2, VARIANT *pParam3, VARIANT *pResult)

#define APEXAPI_APExGetProperty             APEXDECL LRESULT    APExGetProperty(DWORD nProp, LONG nIndex, LPVOID pInfo)
#define APEXAPI_APExSetProperty             APEXDECL LRESULT    APExSetProperty(DWORD nProp, LONG nIndex, LPVOID pInfo)

#define APEXAPI_APExTool                    APEXDECL LRESULT    APExTool(DWORD nTool, HWND hWnd, HANDLE hObject, HANDLE hSubObject, LPCSRECTZ pExtent)

#define APEXAPI_APExPreTranslateMessage     APEXDECL BOOL       APExPreTranslateMessage(MSG *pMsg)

#define APEXAPI_APExPreTranslateNMEA        APEXDECL LRESULT    APExPreTranslateNMEA(LPSTR pSentence, int nFields, LPCSTR pFields[], INSTRUMENT *pInstrument);

#define APEXAPI_APExGetObjectProperty       APEXDECL HRESULT    APExGetObjectProperty(HANDLE hObject, BSTR Name, long Index, VARIANT *pResult)
#define APEXAPI_APExSetObjectProperty       APEXDECL HRESULT    APExSetObjectProperty(HANDLE hObject, BSTR Name, long Index, VARIANT Value)

//--------------------------------------------------------------------
// Layer Extension Specific Routines
//--------------------------------------------------------------------

#define APEXAPI_LayerIsValidPath            APEXDECL LRESULT    LayerIsValidPath(LPCTSTR pFileName)

#define APEXAPI_LayerOpen                   APEXDECL HLAYER     LayerOpen(LPCTSTR pFileName, HWND hWnd)
#define APEXAPI_LayerClose                  APEXDECL LRESULT    LayerClose(HLAYER hLayer)
#define APEXAPI_LayerCreate                 APEXDECL LRESULT    LayerCreate(LPTSTR pFileName, HWND hWnd)

// Layer property routines

#define APEXAPI_LayerGetProperty            APEXDECL LRESULT    LayerGetProperty(HLAYER hLayer, DWORD nProp, HFEATURE hFeature, LONG nIndex, LPVOID pInfo)
#define APEXAPI_LayerSetProperty            APEXDECL LRESULT    LayerSetProperty(HLAYER hLayer, DWORD nProp, HFEATURE hFeature, LONG nIndex, LPVOID pInfo)

#define APEXAPI_LayerLoadProperty           APEXDECL LRESULT    LayerLoadProperty(HLAYER hLayer, LPCTSTR pName, LPCTSTR pValue)
#define APEXAPI_LayerSaveProperty           APEXDECL LRESULT    LayerSaveProperty(HLAYER hLayer, LONG nIndex, LPTSTR pName, LPTSTR pValue)

#define APEXAPI_LayerCreateFeature          APEXDECL HFEATURE   LayerCreateFeature(HLAYER hLayer, LPCSHAPE pShape, LPVOID Reserved)
#define APEXAPI_LayerDeleteFeature          APEXDECL LRESULT    LayerDeleteFeature(HLAYER hLayer, HFEATURE hFeature)

// Drawing routines

#define APEXAPI_LayerDraw                   APEXDECL LRESULT    LayerDraw(HLAYER hLayer, APEX_LAYER_DRAW *pDraw)
#define APEXAPI_LayerDrawSymbol             APEXDECL LRESULT    LayerDrawSymbol(HLAYER hLayer, DWORD nSymbol, HDC hDC, const RECT *pRect, DWORD Flags)
#define APEXAPI_LayerDrawFeature            APEXDECL LRESULT    LayerDrawFeature(HLAYER hLayer, HFEATURE hFeature, HDC hDC, DWORD Flags)

// Layer dialog routines

#define APEXAPI_LayerDialogProperties       APEXDECL LRESULT    LayerDialogProperties(HLAYER hLayer, HWND hWnd)
#define APEXAPI_LayerDialogIdentify         APEXDECL HFEATURE   LayerDialogIdentify(HLAYER hLayer, HWND hWnd, LPCSRECTZ pRect)
#define APEXAPI_LayerDialogHyperlink        APEXDECL HFEATURE   LayerDialogHyperlink(HLAYER hLayer, HWND hWnd, LPCSRECTZ pRect, LONG nIndex)
#define APEXAPI_LayerDialogSymbol           APEXDECL LRESULT    LayerDialogSymbol(HLAYER hLayer, HWND hWnd, DWORD nSymbol)
#define APEXAPI_LayerDialogFeature          APEXDECL LRESULT    LayerDialogFeature(HLAYER hLayer, HWND hWnd, HFEATURE hFeature, DWORD Flags)

#define APEXAPI_LayerHyperlink              APEXDECL LRESULT    LayerHyperlink(HLAYER hLayer, HWND hWnd, HFEATURE hFeature, LONG nIndex)

// Layer searching

#define APEXAPI_LayerQuery                  APEXDECL HFEATURE   LayerQuery(HLAYER hLayer, HFEATURE hFeature, LPCSRECTZ pRect, DWORD Flags)


#define APEXAPI_GPSOpen                     APEXDECL HGPS       GPSOpen(HANDLE hPort, HWND hWnd, DWORD Flags, LPCSPOINTZ pLastPosition, LPCTSTR pInitString)
#define APEXAPI_GPSOpenEx                   APEXDECL HGPS       GPSOpenEx(LPCTSTR pPortDev, LPDCB pDCB, HWND hWnd, DWORD Flags, LPCSPOINTZ pLastPosition, LPCTSTR pInitString)
#define APEXAPI_GPSClose                    APEXDECL LRESULT    GPSClose(HGPS hGPS)
#define APEXAPI_GPSRxHandler                APEXDECL LRESULT    GPSRxHandler(HGPS hGPS, LPBYTE pRxBuffer, LPDWORD pRxCount, LPBYTE pDataBuffer, LPDWORD pDataCount)
#define APEXAPI_GPSParse                    APEXDECL LRESULT    GPSParse(HGPS hGPS, LPBYTE pDataBuffer, INSTRUMENT *pGPS)
#define APEXAPI_GPSPoll                     APEXDECL LRESULT    GPSPoll(HGPS hGPS, DWORD SequenceNum)
#define APEXAPI_GPSWrite                    APEXDECL LRESULT    GPSWrite(HGPS hGPS, LPVOID pData, DWORD nData)

#define APEXAPI_AUXOpen                     APEXDECL HAUX       AUXOpen(HANDLE hPort, HWND hWnd, DWORD Flags, LPVOID pReserved1, LPVOID pReserved2)
#define APEXAPI_AUXClose                    APEXDECL LRESULT    AUXClose(HAUX hAUX)
#define APEXAPI_AUXRxHandler                APEXDECL LRESULT    AUXRxHandler(HAUX hAUX, LPBYTE pRxBuffer, LPDWORD pRxCount, LPBYTE pDataBuffer, LPDWORD pDataCount)
#define APEXAPI_AUXParse                    APEXDECL LRESULT    AUXParse(HAUX hAUX, LPBYTE pDataBuffer, LPVOID pReserved)

//--------------------------------------------------------------------
// Rangefinder Extension Specific Routines
//--------------------------------------------------------------------

#define APEXAPI_RangefinderOpen             APEXDECL HRANGEFINDER   RangefinderOpen(HANDLE hPort, HWND hWnd, DWORD Flags)
#define APEXAPI_RangefinderClose            APEXDECL LRESULT		RangefinderClose(HRANGEFINDER hRF)
#define APEXAPI_RangefinderParse            APEXDECL LRESULT		RangefinderParse(HRANGEFINDER hRF, LPBYTE pDataBuffer, INSTRUMENT *pRangeFinder)
#define APEXAPI_RangefinderParseNMEA		APEXDECL LRESULT     	RangefinderParseNMEA(HRANGEFINDER hRF, LPSTR pSentence, int nFields, LPCSTR pFields[], INSTRUMENT *pRangefinder);
#define APEXAPI_RangefinderWrite            APEXDECL LRESULT		RangefinderWrite(HRANGEFINDER hRF, LPVOID pData, DWORD nData)


//--------------------------------------------------------------------
// Camera Extension Specific Routines
//--------------------------------------------------------------------

#define APEXAPI_CameraCaptureStill			 APEXDECL LRESULT		CameraCaptureStill(HWND hWnd, LPTSTR pFileName, int nQuality, LPVOID pReserved)

//--------------------------------------------------------------------
// Projection Extension Specific Routines
//--------------------------------------------------------------------

#define APEXAPI_ProjectionForward			APEXDECL LRESULT			ProjectionForward(APEX_PRJ_PCSPHEROID pSpheroid, const double Parameters[APEX_PRJ_PARAM_MAX], int nCoords, SPOINTZ* pCoords)
#define APEXAPI_ProjectionInverse			APEXDECL LRESULT			ProjectionInverse(APEX_PRJ_PCSPHEROID pSpheroid, const double Parameters[APEX_PRJ_PARAM_MAX], int nCoords, SPOINTZ* pCoords)

//--------------------------------------------------------------------
// Datum Transform Extension Specific Routines
//--------------------------------------------------------------------

#define APEXAPI_TransformForward			APEXDECL LRESULT			TransformForward(const APEX_PRJ_SPHEROID Spheroid[2], const double Parameters[APEX_PRJ_PARAM_MAX], LPCTSTR pDataset, int nCoords, SPOINTZ* pCoords)
#define APEXAPI_TransformInverse			APEXDECL LRESULT			TransformInverse(const APEX_PRJ_SPHEROID Spheroid[2], const double Parameters[APEX_PRJ_PARAM_MAX], LPCTSTR pDataset, int nCoords, SPOINTZ* pCoords)

//--------------------------------------------------------------------
// Declare prototypes
//--------------------------------------------------------------------

/*
APEXAPI_APExInitialize;
APEXAPI_APExTerminate;
APEXAPI_APExDialogAbout;
APEXAPI_APExDialogProperties;
APEXAPI_APExEscape;
APEXAPI_APExGetProperty;
APEXAPI_APExSetProperty;
APEXAPI_APExTool;
APEXAPI_APExPreTranslateMessage;
APEXAPI_APExGetObjectProperty;
APEXAPI_APExSetObjectProperty;

APEXAPI_LayerIsValidPath;
APEXAPI_LayerOpen;
APEXAPI_LayerClose;
APEXAPI_LayerCreate;
APEXAPI_LayerGetProperty;
APEXAPI_LayerSetProperty;
APEXAPI_LayerLoadProperty;
APEXAPI_LayerSaveProperty;
APEXAPI_LayerDraw;
APEXAPI_LayerDrawSymbol;
APEXAPI_LayerDrawFeature;
APEXAPI_LayerDialogProperties;
APEXAPI_LayerDialogIdentify;
APEXAPI_LayerDialogHyperlink;
APEXAPI_LayerDialogSymbol;
APEXAPI_LayerDialogFeature;
APEXAPI_LayerHyperlink;
APEXAPI_LayerQuery;

APEXAPI_GPSOpen;
APEXAPI_GPSOpenEx;
APEXAPI_GPSClose;
APEXAPI_GPSRxHandler;
APEXAPI_GPSParse;
APEXAPI_GPSPoll;
APEXAPI_GPSWrite;

APEXAPI_AUXOpen;
APEXAPI_AUXClose;
APEXAPI_AUXRxHandler;
APEXAPI_AUXParse;

APEXAPI_CameraCaptureStill;
*/

#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------
// C++ helper class for building extensions
//
// The CAPEx class declares the APEx DLL entry points in a C++ class.
//
//--------------------------------------------------------------------

#ifdef __cplusplus

class CAPEx
{
public :
    static APEXDECL LRESULT     	APExInitialize(HWND hWnd);
    static APEXDECL LRESULT     	APExTerminate(void);
    static APEXDECL LRESULT     	APExDialogAbout(HWND hWnd);
    static APEXDECL LRESULT     	APExDialogProperties(HWND hWnd);
    static APEXDECL HRESULT     	APExEscape(HANDLE hObject, VARIANT *pParam1, VARIANT *pParam2, VARIANT *pParam3, VARIANT *pResult);
    static APEXDECL LRESULT     	APExGetProperty(DWORD nProp, LONG nIndex, LPVOID pInfo);
    static APEXDECL LRESULT     	APExSetProperty(DWORD nProp, LONG nIndex, LPVOID pInfo);
    static APEXDECL LRESULT     	APExTool(DWORD nTool, HWND hWnd, HANDLE hObject, HANDLE hSubObject, LPCSRECTZ pExtent);
    static APEXDECL BOOL        	APExPreTranslateMessage(MSG *pMsg);
    static APEXDECL LRESULT     	APExPreTranslateNMEA(LPSTR pSentence, int nFields, LPCSTR pFields[], INSTRUMENT *pInstrument);
    static APEXDECL HRESULT     	APExGetObjectProperty(HANDLE hObject, BSTR Name, long Index, VARIANT *pResult);
    static APEXDECL HRESULT     	APExSetObjectProperty(HANDLE hObject, BSTR Name, long Index, VARIANT Value);

	static APEXDECL	LRESULT			APExNotify(int nNotifyCode, LPVOID pNotifyInfo);
                                	
    static APEXDECL LRESULT     	LayerIsValidPath(LPCTSTR pFileName);
    static APEXDECL HLAYER      	LayerOpen(LPCTSTR pFileName, HWND hWnd);
    static APEXDECL LRESULT     	LayerClose(HLAYER hLayer);
    static APEXDECL LRESULT     	LayerCreate(LPTSTR pFileName, HWND hWnd);
    static APEXDECL LRESULT     	LayerGetProperty(HLAYER hLayer, DWORD nProp, HFEATURE hFeature, LONG nIndex, LPVOID pInfo);
    static APEXDECL LRESULT     	LayerSetProperty(HLAYER hLayer, DWORD nProp, HFEATURE hFeature, LONG nIndex, LPVOID pInfo);
    static APEXDECL LRESULT     	LayerLoadProperty(HLAYER hLayer, LPCTSTR pName, LPCTSTR pValue);
    static APEXDECL LRESULT     	LayerSaveProperty(HLAYER hLayer, LONG nIndex, LPTSTR pName, LPTSTR pValue);
    static APEXDECL HFEATURE    	LayerCreateFeature(HLAYER hLayer, LPCSHAPE pShape, LPVOID Reserved);
    static APEXDECL LRESULT     	LayerDeleteFeature(HLAYER hLayer, HFEATURE hFeature);
    static APEXDECL LRESULT     	LayerDraw(HLAYER hLayer, APEX_LAYER_DRAW *pDraw);
    static APEXDECL LRESULT     	LayerDrawSymbol(HLAYER hLayer, DWORD nSymbol, HDC hDC, const RECT *pRect, DWORD Flags);
    static APEXDECL LRESULT     	LayerDrawFeature(HLAYER hLayer, HFEATURE hFeature, HDC hDC, DWORD Flags);
    static APEXDECL LRESULT     	LayerDialogProperties(HLAYER hLayer, HWND hWnd);
    static APEXDECL HFEATURE    	LayerDialogIdentify(HLAYER hLayer, HWND hWnd, LPCSRECTZ pRect);
    static APEXDECL HFEATURE    	LayerDialogHyperlink(HLAYER hLayer, HWND hWnd, LPCSRECTZ pRect, LONG nIndex);
    static APEXDECL LRESULT     	LayerDialogSymbol(HLAYER hLayer, HWND hWnd, DWORD nSymbol);
    static APEXDECL LRESULT     	LayerDialogFeature(HLAYER hLayer, HWND hWnd, HFEATURE hFeature, DWORD Flags);
    static APEXDECL LRESULT     	LayerHyperlink(HLAYER hLayer, HWND hWnd, HFEATURE hFeature, LONG nIndex);
    static APEXDECL HFEATURE    	LayerQuery(HLAYER hLayer, HFEATURE hFeature, LPCSRECTZ pRect, DWORD Flags);

	//static APEXDECL LRESULT			LayerGetScanline(HLAYER hLayer, LONG nX1, LONG nX2, LONG nY, LRESULT (*ResponseCallBack)(HLAYER hLayer, RAS_RESPONSE *pResponse));
    //static APEXDECL LRESULT	    	LayerGetSubImage(HLAYER hLayer, LPCRECT pExtent, double nDesiredPixelScale, LRESULT (*ResponseCallBack)(HLAYER, RAS_RESPONSE *));

    static APEXDECL HGPS        	GPSOpen(HANDLE hPort, HWND hWnd, DWORD Flags, LPCSPOINTZ pLastPosition, LPCTSTR pInitString);
    static APEXDECL HGPS        	GPSOpenEx(LPCTSTR pPortDev, LPDCB pDCB, HWND hWnd, DWORD Flags, LPCSPOINTZ pLastPosition, LPCTSTR pInitString);
    static APEXDECL LRESULT     	GPSClose(HGPS hGPS);
    static APEXDECL LRESULT     	GPSRxHandler(HGPS hGPS, LPBYTE pRxBuffer, LPDWORD pRxCount, LPBYTE pDataBuffer, LPDWORD pDataCount);
    static APEXDECL LRESULT     	GPSParse(HGPS hGPS, LPBYTE pDataBuffer, INSTRUMENT *pGPS);
    static APEXDECL LRESULT     	GPSPoll(HGPS hGPS, DWORD SequenceNum);
    static APEXDECL LRESULT     	GPSWrite(HGPS hGPS, LPVOID pData, DWORD nData);
                                	
    static APEXDECL HAUX        	AUXOpen(HANDLE hPort, HWND hWnd, DWORD Flags, LPVOID pReserved1, LPVOID pReserved2);
    static APEXDECL LRESULT     	AUXClose(HAUX hAUX);
    static APEXDECL LRESULT     	AUXRxHandler(HAUX hAUX, LPBYTE pRxBuffer, LPDWORD pRxCount, LPBYTE pDataBuffer, LPDWORD pDataCount);
    static APEXDECL LRESULT     	AUXParse(HAUX hAUX, LPBYTE pDataBuffer, LPVOID pReserved);

	static APEXDECL HRANGEFINDER	RangefinderOpen(HANDLE hPort, HWND hWnd, DWORD Flags);
	static APEXDECL LRESULT			RangefinderClose(HRANGEFINDER hRF);
	static APEXDECL LRESULT			RangefinderParse(HRANGEFINDER hRF, LPBYTE pDataBuffer, INSTRUMENT *pRangeFinder);
    static APEXDECL LRESULT     	RangefinderParseNMEA(HRANGEFINDER hRF, LPSTR pSentence, int nFields, LPCSTR pFields[], INSTRUMENT *pRangefinder);
	static APEXDECL LRESULT			RangefinderWrite(HRANGEFINDER hRF, LPVOID pData, DWORD nData);

    static APEXDECL LRESULT     	CameraCaptureStill(HWND hWnd, LPTSTR pFileName, int nQuality, LPVOID pReserved);

	static APEXDECL LRESULT			ProjectionForward(APEX_PRJ_PCSPHEROID pSpheroid, const double Parameters[APEX_PRJ_PARAM_MAX], int nCoords, SPOINTZ* pCoords);
	static APEXDECL LRESULT			ProjectionInverse(APEX_PRJ_PCSPHEROID pSpheroid, const double Parameters[APEX_PRJ_PARAM_MAX], int nCoords, SPOINTZ* pCoords);

	static APEXDECL LRESULT			TransformForward(const APEX_PRJ_SPHEROID Spheroid[2], const double Parameters[APEX_PRJ_PARAM_MAX], LPCTSTR pDataset, int nCoords, SPOINTZ* pCoords);
	static APEXDECL LRESULT			TransformInverse(const APEX_PRJ_SPHEROID Spheroid[2], const double Parameters[APEX_PRJ_PARAM_MAX], LPCTSTR pDataset, int nCoords, SPOINTZ* pCoords);

    // Helper functions

    static LRESULT ReturnString(LPVOID pInfo, LPCTSTR String);

    static bool UserBreak();

    static bool PointInRect(LPCSPOINT pPoint, LPCSRECT pRect);
    static bool PointInRect(LPCSPOINT pPoint, LPCSRECTZ pRectZ);
    static bool RectOnRect(LPCSRECT pRect1, LPCSRECT pRect2);
    static bool RectInRect(LPCSRECT pRect1, LPCSRECT pRect2);
    static void NormalizeRect(LPSRECT pRect);

    static bool IsPoint(long ShapeType);
    static bool IsPoint(LPCSHAPE pShape);
    static bool IsPolyline(long ShapeType);
    static bool IsPolyline(LPCSHAPE pShape);
    static bool IsPolygon(long ShapeType);
    static bool IsPolygon(LPCSHAPE pShape);
    static bool IsMultiPoint(long ShapeType);
    static bool IsMultiPoint(LPCSHAPE pShape);
    static bool IsPoly(long ShapeType);
    static bool IsPoly(LPCSHAPE pShape);

    static double ToRadians(double Degrees);
    static double ToDegrees(double Radians) ;
    static double Distance(LPCSPOINT pA, LPCSPOINT pB);

    static bool IsNaN(double d);
    static bool IsNaN(const double &d);
    static void SetNaN(double *pd);
    static void SetNaN(double &d);


    static int CalculateShapeSize(long ShapeType, int nParts, int nPoints);

    static void SendData(HWND hWnd, DWORD Cmd, LPVOID pData, DWORD nData);
    static void SendScript(HWND hWnd, LPCWSTR pScript);
    static void SendGPS(HWND hWnd, LPCSTR pText);
    static void SendGPS(HWND hWnd, LPVOID pData, int nData);
    static void SendAUX(HWND hWnd, LPCSTR pText);
    static void SendAUX(HWND hWnd, LPVOID pData, int nData);
    static void SendRangefinder(HWND hWnd, LPCSTR pText);
    static void SendRangefinder(HWND hWnd, LPVOID pData, int nData);

protected:
	static void GetFunctions(HWND hWnd);

	static inline int 		Project(HLAYER hLayer, const SPOINT *pPoints, int nPoints, SPOINT *pViewPoints) { return m_pfnProject(hLayer, pPoints, nPoints, pViewPoints); };
	static inline int 		UnProject(HLAYER hLayer, const SPOINT *pViewPoints, int nPoints, SPOINT *pPoints) { return m_pfnUnProject(hLayer, pViewPoints, nPoints, pPoints); };
	static inline int 		DCProject(HLAYER hLayer, const SPOINT *pPoints, int nPoints, POINT *pDCPoints) { return m_pfnDCProject(hLayer, pPoints, nPoints, pDCPoints); };
	static inline int 		DCUnProject(HLAYER hLayer, const POINT *pDCPoints, int nPoints, SPOINT *pPoints) { return m_pfnDCUnProject(hLayer, pDCPoints, nPoints, pPoints); };
	static inline COLORREF	ColorPicker(HWND hWnd, COLORREF rgb) { return m_pfnColorPicker(hWnd, rgb); };
	static inline int		FontPicker(HWND hWnd, LOGFONT *pLogFont) { return m_pfnFontPicker(hWnd, pLogFont); };
	static inline HRESULT	Evaluate(LPCWSTR pExpression, VARIANT *pResult, HANDLE hContext) { return m_pfnEvaluate(pExpression, pResult, hContext); };
	static inline void		PaintLayer(HLAYER hLayer, HDC hDC, int Progress) { m_pfnPaintLayer(hLayer, hDC, Progress); };
	static inline HBITMAP	JPEGLoad(LPCTSTR pFilename) { return m_pfnJPEGLoad(pFilename); };
	static inline bool		JPEGSave(LPCTSTR pFilename, HBITMAP hBitmap, int nQuality) { return m_pfnJPEGSave(pFilename, hBitmap, nQuality) != 0; };
	static inline bool		JPEGRotate(LPCTSTR pFromFilename, LPCTSTR pToFilename, APEX_JXFORM JXForm) { return m_pfnJPEGRotate(pFromFilename, pToFilename, JXForm) != 0; };
	static inline HANDLE	ImagePropsOpen(LPCTSTR pFilename) { return m_pfnImagePropsOpen(pFilename); };
	static inline void		ImagePropsClose(HANDLE hImage) { m_pfnImagePropsClose(hImage); };
	static inline HRESULT 	ImagePropsGet(HANDLE hImage, int nTag, VARIANT* pValue) { return m_pfnImagePropsGet(hImage, nTag, pValue); };
	static inline HRESULT 	ImagePropsSet(HANDLE hImage, int nTag, VARIANT* pValue) { return m_pfnImagePropsSet(hImage, nTag, pValue); };
	static HRESULT 			ImagePropsSet(HANDLE hImage, int nTag, LPCTSTR pValue);
	static HRESULT 			ImagePropsSet(HANDLE hImage, int nTag, long Value);
	static HRESULT 			ImagePropsSet(HANDLE hImage, int nTag, double Value);
	static HRESULT 			ImagePropsSet(HANDLE hImage, int nTag, LPSYSTEMTIME pValue);
	static HRESULT 			ImagePropsDelete(HANDLE hImage, int nTag);
	static HSYMBOL			SymbolCreate(LPCTSTR pDefinitionXML) { return m_pfnSymbolCreate(pDefinitionXML); };
	static HRESULT			SymbolDestroy(HSYMBOL hSymbol) { return m_pfnSymbolDestroy(hSymbol); };
	static int				SymbolGetXML(HSYMBOL hSymbol, LPTSTR pDefinition) { return m_pfnSymbolGetXML(hSymbol, pDefinition); };
	static HRESULT			SymbolDrawShape(HDC hDC, HSYMBOL hSymbol, HLAYER hLayer, LPSHAPE pShape, HSYMBOL hTextSymbol, LPCTSTR pText, double Scale) { return m_pfnSymbolDrawShape(hDC, hSymbol, hLayer, pShape, hTextSymbol, pText, Scale); };
	static HRESULT			SymbolDrawMarker(HDC hDC, HSYMBOL hSymbol, int x, int y, double Angle, double Scale, SIZE *pMarkerSize) { return m_pfnSymbolDrawMarker(hDC, hSymbol, x, y, Angle, Scale, pMarkerSize); }
	static HRESULT			SymbolDrawPolyline(HDC hDC, HSYMBOL hSymbol, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale) { return m_pfnSymbolDrawPolyline(hDC, hSymbol, pPoints, nPoints, pParts, nParts, Scale); }
	static HRESULT			SymbolDrawPolygon(HDC hDC, HSYMBOL hSymbol, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale) { return m_pfnSymbolDrawPolygon(hDC, hSymbol, pPoints, nPoints, pParts, nParts, Scale); }
	static HRESULT			SymbolDrawMarkerText(HDC hDC, HSYMBOL hSymbol, LPCTSTR pText, RECT *pRect, double Angle, double Scale) { return m_pfnSymbolDrawMarkerText(hDC, hSymbol, pText, pRect, Angle, Scale); }
	static HRESULT CALLBACK SymbolDrawPolylineText(HDC hDC, HSYMBOL hSymbol, LPCTSTR pText, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale) { return m_pfnSymbolDrawPolylineText(hDC, hSymbol, pText, pPoints, nPoints, pParts, nParts, Scale); }
	static HRESULT CALLBACK SymbolDrawPolygonText(HDC hDC, HSYMBOL hSymbol, LPCTSTR pText, LPPOINT pPoints, int nPoints, LPLONG pParts, int nParts, double Scale) { return m_pfnSymbolDrawPolygonText(hDC, hSymbol, pText, pPoints, nPoints, pParts, nParts, Scale); }

	// Version information

	static HRESULT			GetVersion(HINSTANCE hInstance, VS_FIXEDFILEINFO& Version);

protected:
	static APEX_PFN_PROJECT				m_pfnProject;
	static APEX_PFN_UNPROJECT			m_pfnUnProject;
	static APEX_PFN_DCPROJECT			m_pfnDCProject;
	static APEX_PFN_DCUNPROJECT			m_pfnDCUnProject;
	static APEX_PFN_COLORPICKER			m_pfnColorPicker;
	static APEX_PFN_FONTPICKER			m_pfnFontPicker;
	static APEX_PFN_EVALUATE			m_pfnEvaluate;
	static APEX_PFN_PAINTLAYER			m_pfnPaintLayer;
	static APEX_PFN_JPEGLOAD			m_pfnJPEGLoad;
	static APEX_PFN_JPEGSAVE			m_pfnJPEGSave;
	static APEX_PFN_JPEGROTATE			m_pfnJPEGRotate;
	static APEX_PFN_IMAGEPROPSOPEN		m_pfnImagePropsOpen;
	static APEX_PFN_IMAGEPROPSCLOSE		m_pfnImagePropsClose;
	static APEX_PFN_IMAGEPROPSGET		m_pfnImagePropsGet;
	static APEX_PFN_IMAGEPROPSSET		m_pfnImagePropsSet;
	static APEX_PFN_SYMBOLCREATE		m_pfnSymbolCreate;
	static APEX_PFN_SYMBOLDESTROY		m_pfnSymbolDestroy;
	static APEX_PFN_SYMBOLGETXML		m_pfnSymbolGetXML;
	static APEX_PFN_SYMBOLDRAWSHAPE		m_pfnSymbolDrawShape;
	static APEX_PFN_SYMBOLDRAWMARKER	m_pfnSymbolDrawMarker;
	static APEX_PFN_SYMBOLDRAWPOLYLINE	m_pfnSymbolDrawPolyline;
	static APEX_PFN_SYMBOLDRAWPOLYGON	m_pfnSymbolDrawPolygon;
	static APEX_PFN_SYMBOLDRAWMARKERTEXT	m_pfnSymbolDrawMarkerText;
	static APEX_PFN_SYMBOLDRAWPOLYLINETEXT	m_pfnSymbolDrawPolylineText;
	static APEX_PFN_SYMBOLDRAWPOLYGONTEXT	m_pfnSymbolDrawPolygonText;

};
#endif
#endif

