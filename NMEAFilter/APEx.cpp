//====================================================================
//
// Copyright © 2002-2005 MapTel
// All Rights Reserved. 
// Use subject to License Agreement.
//
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//
// Purpose:
//
//	Support library for ArcPad extensions
//
//====================================================================

#define _CRT_SECURE_NO_WARNINGS

#define STRICT
#include "APEx.h"
#include <math.h>
#include <float.h>

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

#ifndef UNDER_CE
#pragma comment(lib, "version.lib")
#endif

#pragma comment(lib, "OLEAUT32.LIB")

//--------------------------------------------------------------------
// 
//--------------------------------------------------------------------

#define SQRD(X)		((X)*(X))

static const double PI	= 3.14159265358979323846264;

//--------------------------------------------------------------------
// 
//--------------------------------------------------------------------

APEX_PFN_PROJECT					CAPEx::m_pfnProject = NULL;
APEX_PFN_UNPROJECT					CAPEx::m_pfnUnProject = NULL;
APEX_PFN_DCPROJECT					CAPEx::m_pfnDCProject = NULL;
APEX_PFN_DCUNPROJECT				CAPEx::m_pfnDCUnProject = NULL;
APEX_PFN_COLORPICKER				CAPEx::m_pfnColorPicker = NULL;
APEX_PFN_FONTPICKER					CAPEx::m_pfnFontPicker = NULL;
APEX_PFN_EVALUATE					CAPEx::m_pfnEvaluate = NULL;
APEX_PFN_PAINTLAYER					CAPEx::m_pfnPaintLayer = NULL;
APEX_PFN_JPEGLOAD					CAPEx::m_pfnJPEGLoad = NULL;
APEX_PFN_JPEGSAVE					CAPEx::m_pfnJPEGSave = NULL;
APEX_PFN_JPEGROTATE					CAPEx::m_pfnJPEGRotate = NULL;
APEX_PFN_IMAGEPROPSOPEN				CAPEx::m_pfnImagePropsOpen = NULL;
APEX_PFN_IMAGEPROPSCLOSE			CAPEx::m_pfnImagePropsClose = NULL;
APEX_PFN_IMAGEPROPSGET				CAPEx::m_pfnImagePropsGet = NULL;
APEX_PFN_IMAGEPROPSSET				CAPEx::m_pfnImagePropsSet = NULL;
APEX_PFN_SYMBOLCREATE				CAPEx::m_pfnSymbolCreate = NULL;
APEX_PFN_SYMBOLDESTROY				CAPEx::m_pfnSymbolDestroy = NULL;
APEX_PFN_SYMBOLGETXML				CAPEx::m_pfnSymbolGetXML = NULL;
APEX_PFN_SYMBOLDRAWSHAPE			CAPEx::m_pfnSymbolDrawShape = NULL;
APEX_PFN_SYMBOLDRAWMARKER			CAPEx::m_pfnSymbolDrawMarker = NULL;
APEX_PFN_SYMBOLDRAWPOLYLINE			CAPEx::m_pfnSymbolDrawPolyline = NULL;
APEX_PFN_SYMBOLDRAWPOLYGON			CAPEx::m_pfnSymbolDrawPolygon = NULL;
APEX_PFN_SYMBOLDRAWMARKERTEXT		CAPEx::m_pfnSymbolDrawMarkerText = NULL;
APEX_PFN_SYMBOLDRAWPOLYLINETEXT		CAPEx::m_pfnSymbolDrawPolylineText = NULL;
APEX_PFN_SYMBOLDRAWPOLYGONTEXT		CAPEx::m_pfnSymbolDrawPolygonText = NULL;

//--------------------------------------------------------------------
// Return a string or string length only
//--------------------------------------------------------------------

LRESULT CAPEx::ReturnString(LPVOID pInfo, LPCTSTR String)
{
	if (pInfo != NULL) _tcscpy((LPTSTR)pInfo, String);
	return _tcslen(String);
}

//--------------------------------------------------------------------
// Check if user wishes to stop current operation (i.e. LayerDraw)
//
// Returns true if user clicks mouse or pushes ESC key.
//--------------------------------------------------------------------

bool CAPEx::UserBreak()
{
	MSG Msg;

	/*
	if (PeekMessage(&Msg, NULL, WM_LBUTTONDOWN, WM_MOUSELAST+1, PM_NOREMOVE)) 
	{
		return true;
	}
	*/

	if (PeekMessage(&Msg, NULL, WM_KEYUP, WM_KEYUP, PM_NOREMOVE)) 
	{
		if (Msg.wParam == VK_ESCAPE) return true;
	}

	return false;
}

//--------------------------------------------------------------------
// Check if a point falls in the specified rectangle
//
// Note these routines are 2D only and do not check the 'Z' values
//--------------------------------------------------------------------

bool CAPEx::PointInRect(LPCSPOINT pPoint, LPCSRECT pRect)
{
	return  pPoint->x >= pRect->xMin &&
			pPoint->x <= pRect->xMax &&
			pPoint->y >= pRect->yMin &&
			pPoint->y <= pRect->yMax;
}

bool CAPEx::PointInRect(LPCSPOINT pPoint, LPCSRECTZ pRectZ)
{
	return  pPoint->x >= pRectZ->xMin &&
			pPoint->x <= pRectZ->xMax &&
			pPoint->y >= pRectZ->yMin &&
			pPoint->y <= pRectZ->yMax;
}

//--------------------------------------------------------------------
// Check if Rects Overlap
//--------------------------------------------------------------------

bool CAPEx::RectOnRect(LPCSRECT pRect1, LPCSRECT pRect2)
{
	return !(pRect1->xMin > pRect2->xMax ||
			 pRect1->xMax < pRect2->xMin ||
			 pRect1->yMin > pRect2->yMax ||
			 pRect1->yMax < pRect2->yMin);
}

//--------------------------------------------------------------------
// Check if Rect1 is within Rect2
//--------------------------------------------------------------------

bool CAPEx::RectInRect(LPCSRECT pRect1, LPCSRECT pRect2)
{
	return	pRect1->xMin >= pRect2->xMin &&
			pRect1->xMin <= pRect2->xMax &&
			pRect1->xMax >= pRect2->xMin &&
			pRect1->xMax <= pRect2->xMax &&
			pRect1->yMin >= pRect2->yMin &&
			pRect1->yMin <= pRect2->yMax &&
			pRect1->yMax >= pRect2->yMin &&
			pRect1->yMax <= pRect2->yMax;
}

//--------------------------------------------------------------------
// Normalizes a rectangle so both the height and width are positive.
//--------------------------------------------------------------------

void CAPEx::NormalizeRect(LPSRECT pRect)
{
	if (pRect->xMin > pRect->xMax)
	{
		double t = pRect->xMin;
		pRect->xMin = pRect->xMax;
		pRect->xMax = t;
	}

	if (pRect->yMin > pRect->yMax)
	{
		double t = pRect->yMin;
		pRect->yMin = pRect->yMax;
		pRect->yMax = t;
	}
}

//--------------------------------------------------------------------
// Routines to check if a shape type or shape structure is of a 
// particular shape category.
//--------------------------------------------------------------------

bool CAPEx::IsPoint(long ShapeType)
{
	return	ShapeType == SHAPE_TYPE_POINT ||
			ShapeType == SHAPE_TYPE_POINTM ||
			ShapeType == SHAPE_TYPE_POINTZ;
}

bool CAPEx::IsPoint(LPCSHAPE pShape)
{
	return IsPoint(pShape->ShapeType);
}

//--------------------------------------------------------------------

bool CAPEx::IsPolyline(long ShapeType)
{
	return	ShapeType == SHAPE_TYPE_POLYLINE ||
			ShapeType == SHAPE_TYPE_POLYLINEM ||
			ShapeType == SHAPE_TYPE_POLYLINEZ;
}

bool CAPEx::IsPolyline(LPCSHAPE pShape)
{
	return IsPolyline(pShape->ShapeType);
}

//--------------------------------------------------------------------

bool CAPEx::IsPolygon(long ShapeType)
{
	return	ShapeType == SHAPE_TYPE_POLYGON ||
			ShapeType == SHAPE_TYPE_POLYGONM ||
			ShapeType == SHAPE_TYPE_POLYGONZ;
}

bool CAPEx::IsPolygon(LPCSHAPE pShape)
{
	return IsPolygon(pShape->ShapeType);
}

//--------------------------------------------------------------------

bool CAPEx::IsMultiPoint(long ShapeType)
{
	return	ShapeType == SHAPE_TYPE_MULTIPOINT ||
			ShapeType == SHAPE_TYPE_MULTIPOINTM ||
			ShapeType == SHAPE_TYPE_MULTIPOINTZ;
}

bool CAPEx::IsMultiPoint(LPCSHAPE pShape)
{
	return IsMultiPoint(pShape->ShapeType);
}

//--------------------------------------------------------------------

bool CAPEx::IsPoly(long ShapeType)
{
	return	ShapeType == SHAPE_TYPE_POLYLINE ||
			ShapeType == SHAPE_TYPE_POLYLINEM ||
			ShapeType == SHAPE_TYPE_POLYLINEZ ||
			ShapeType == SHAPE_TYPE_POLYGON ||
			ShapeType == SHAPE_TYPE_POLYGONM ||
			ShapeType == SHAPE_TYPE_POLYGONZ;
}

bool CAPEx::IsPoly(LPCSHAPE pShape)
{
	return IsPoly(pShape->ShapeType);
}

//--------------------------------------------------------------------
// Conversion routines between radian and decimal degrees
//--------------------------------------------------------------------

double ToRadians(double Degrees)
{ 
	return (Degrees * PI) / 180.0; 
}

double ToDegrees(double Radians) 
{ 
	return (Radians * 180.0) / PI; 
}

//--------------------------------------------------------------------
// Distance between two points
//--------------------------------------------------------------------

double CAPEx::Distance(LPCSPOINT pA, LPCSPOINT pB)
{
	return sqrt(SQRD(pA->x - pB->x) + SQRD(pA->y - pB->y));
}

//--------------------------------------------------------------------
// NaN (Not-a-Number) helper routines
//--------------------------------------------------------------------

bool CAPEx::IsNaN(double d)
{
	return _isnan(d) || (d <= SHAPE_NAN_THRESHOLD);
}

bool CAPEx::IsNaN(const double &d)
{
	return _isnan(d) || (d <= SHAPE_NAN_THRESHOLD);
}

void CAPEx::SetNaN(double *pd)
{
	*pd = SHAPE_NAN;
}

void CAPEx::SetNaN(double &d)
{
	d = SHAPE_NAN;
}

//--------------------------------------------------------------------
// Calculate the memory required to hold a shape
//--------------------------------------------------------------------

int CAPEx::CalculateShapeSize(long ShapeType, int nParts, int nPoints)
{
	switch (ShapeType)
	{
	// Point

	case SHAPE_TYPE_POINT :
		return sizeof(long) + sizeof(SPOINT);

	case SHAPE_TYPE_POINTM :
		return sizeof(long) + sizeof(SPOINTM);

	case SHAPE_TYPE_POINTZ :
		return sizeof(long) + sizeof(SPOINTZ);

	// Poly

	case SHAPE_TYPE_POLYLINE :
	case SHAPE_TYPE_POLYGON :
		return sizeof(long) +						// ShapeType
				sizeof(SRECT) +						// Extent
				sizeof(long) * (2 + nParts) +		// NumParts + NumPoints + Part Points Index
				sizeof(SPOINT) * nPoints;			// Points Array

	case SHAPE_TYPE_POLYLINEM :
	case SHAPE_TYPE_POLYGONM :
		return sizeof(long) +						// ShapeType
				sizeof(SRECT) +						// Extent
				sizeof(long) * (2 + nParts) +		// NumParts + NumPoints + Part Points Index
				sizeof(SPOINT) * nPoints +			// Points Array
				sizeof(double) * (2 + nPoints);		// M Range + Array

	case SHAPE_TYPE_POLYLINEZ :
	case SHAPE_TYPE_POLYGONZ :
		return sizeof(long) +						// ShapeType
				sizeof(SRECT) +						// Extent
				sizeof(long) * (2 + nParts) +		// NumParts + NumPoints + Part Points Index
				sizeof(SPOINT) * nPoints +			// Points Array
				sizeof(double) * (2 + nPoints) +	// Z Range + Array
				sizeof(double) * (2 + nPoints);		// M Range + Array

	// Multipoint

	case SHAPE_TYPE_MULTIPOINT :
		return sizeof(long) +						// ShapeType
				sizeof(SRECT) +						// Extent
				sizeof(long) +						// nPoints
				sizeof(SPOINT) * nPoints;

	case SHAPE_TYPE_MULTIPOINTM :
		return sizeof(long) +						// ShapeType
				sizeof(SRECT) +						// Extent
				sizeof(long) +						// nPoints
				sizeof(SPOINT) * nPoints +			// Points Array
				sizeof(double) * (2 + nPoints);		// M Range + Array

	case SHAPE_TYPE_MULTIPOINTZ :
		return sizeof(long) +						// ShapeType
				sizeof(SRECT) +						// Extent
				sizeof(long) +						// nPoints
				sizeof(SPOINT) * nPoints +			// Points Array
				sizeof(double) * (2 + nPoints) +	// Z Range + Array
				sizeof(double) * (2 + nPoints);		// M Range + Array
	}

	return 0;
}

//--------------------------------------------------------------------
// Send command and data to ArcPad
//--------------------------------------------------------------------

void CAPEx::SendData(HWND hWnd, DWORD Cmd, LPVOID pData, DWORD nData)
{
	COPYDATASTRUCT	CDS;
	CDS.dwData = Cmd;
	CDS.cbData = nData,
	CDS.lpData = pData;

	::SendMessage(hWnd, WM_COPYDATA, NULL, (LPARAM)&CDS);
}

//--------------------------------------------------------------------
// Send a script to ArcPad
//--------------------------------------------------------------------

void CAPEx::SendScript(HWND hWnd, LPCWSTR pScript)
{
	SendData(hWnd, COPYDATA_CMD_SCRIPT, (LPVOID)pScript, (DWORD)(wcslen(pScript) + 1) * sizeof(WCHAR));
}

//--------------------------------------------------------------------
// Send a string to the GPS port
//--------------------------------------------------------------------

void CAPEx::SendGPS(HWND hWnd, LPCSTR pText)
{
	SendData(hWnd, COPYDATA_CMD_GPSSEND, (LPVOID)pText, (DWORD)strlen(pText));
}

//--------------------------------------------------------------------
// Send binary data to the GPS port
//--------------------------------------------------------------------

void CAPEx::SendGPS(HWND hWnd, LPVOID pData, int nData)
{
	SendData(hWnd, COPYDATA_CMD_GPSSEND, pData, nData);
}

//--------------------------------------------------------------------
// Send a string to the AUX port
//--------------------------------------------------------------------

void CAPEx::SendAUX(HWND hWnd, LPCSTR pText)
{
	SendData(hWnd, COPYDATA_CMD_AUXSEND, (LPVOID)pText, (DWORD)strlen(pText));
}

//--------------------------------------------------------------------
// Send binary data to the AUX port
//--------------------------------------------------------------------

void CAPEx::SendAUX(HWND hWnd, LPVOID pData, int nData)
{
	SendData(hWnd, COPYDATA_CMD_AUXSEND, pData, nData);
}

//--------------------------------------------------------------------
// Send a string to the Rangefinder port
//--------------------------------------------------------------------

void CAPEx::SendRangefinder(HWND hWnd, LPCSTR pText)
{
	SendData(hWnd, COPYDATA_CMD_RANGEFINDERSEND, (LPVOID)pText, (DWORD)strlen(pText));
}

//--------------------------------------------------------------------
// Send binary data to the Rangefinder port
//--------------------------------------------------------------------

void CAPEx::SendRangefinder(HWND hWnd, LPVOID pData, int nData)
{
	SendData(hWnd, COPYDATA_CMD_RANGEFINDERSEND, pData, nData);
}

//--------------------------------------------------------------------
// Retrieve all callback function pointers
//--------------------------------------------------------------------

void CAPEx::GetFunctions(HWND hWnd)
{
	m_pfnProject			= APEX_GetFunction(hWnd, PROJECT);
	m_pfnUnProject			= APEX_GetFunction(hWnd, UNPROJECT);
	m_pfnDCProject			= APEX_GetFunction(hWnd, DCPROJECT);
	m_pfnDCUnProject		= APEX_GetFunction(hWnd, DCUNPROJECT);
	m_pfnColorPicker		= APEX_GetFunction(hWnd, COLORPICKER);	
	m_pfnFontPicker			= APEX_GetFunction(hWnd, FONTPICKER);
	m_pfnEvaluate			= APEX_GetFunction(hWnd, EVALUATE);	
	m_pfnPaintLayer			= APEX_GetFunction(hWnd, PAINTLAYER);	
	m_pfnJPEGLoad			= APEX_GetFunction(hWnd, JPEGLOAD);	
	m_pfnJPEGSave			= APEX_GetFunction(hWnd, JPEGSAVE);
	m_pfnJPEGRotate			= APEX_GetFunction(hWnd, JPEGROTATE);
	m_pfnImagePropsOpen		= APEX_GetFunction(hWnd, IMAGEPROPSOPEN);
	m_pfnImagePropsClose	= APEX_GetFunction(hWnd, IMAGEPROPSCLOSE);
	m_pfnImagePropsGet		= APEX_GetFunction(hWnd, IMAGEPROPSGET);
	m_pfnImagePropsSet		= APEX_GetFunction(hWnd, IMAGEPROPSSET);
	m_pfnSymbolCreate		= APEX_GetFunction(hWnd, SYMBOLCREATE);
	m_pfnSymbolDestroy		= APEX_GetFunction(hWnd, SYMBOLDESTROY);
	m_pfnSymbolGetXML		= APEX_GetFunction(hWnd, SYMBOLGETXML);
	m_pfnSymbolDrawShape	= APEX_GetFunction(hWnd, SYMBOLDRAWSHAPE);
	m_pfnSymbolDrawMarker	= APEX_GetFunction(hWnd, SYMBOLDRAWMARKER);
	m_pfnSymbolDrawPolyline	= APEX_GetFunction(hWnd, SYMBOLDRAWPOLYLINE);
	m_pfnSymbolDrawPolygon	= APEX_GetFunction(hWnd, SYMBOLDRAWPOLYGON);
	m_pfnSymbolDrawMarkerText	= APEX_GetFunction(hWnd, SYMBOLDRAWMARKERTEXT);
	m_pfnSymbolDrawPolylineText	= APEX_GetFunction(hWnd, SYMBOLDRAWPOLYLINETEXT);
	m_pfnSymbolDrawPolygonText	= APEX_GetFunction(hWnd, SYMBOLDRAWPOLYGONTEXT);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

HRESULT CAPEx::ImagePropsSet(HANDLE hImage, int nTag, LPCTSTR pValue)
{
	VARIANT	Var;
	Var.vt = VT_BSTR;
	Var.bstrVal = SysAllocString(pValue);

	HRESULT hResult =  ImagePropsSet(hImage, nTag, &Var);

	VariantClear(&Var);

	return hResult;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

HRESULT CAPEx::ImagePropsSet(HANDLE hImage, int nTag, long Value)
{
	VARIANT	Var;
	Var.vt = VT_I4;
	Var.lVal = Value;

	return ImagePropsSet(hImage, nTag, &Var);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

HRESULT CAPEx::ImagePropsSet(HANDLE hImage, int nTag, double Value)
{
	VARIANT	Var;
	Var.vt = VT_R8;
	Var.dblVal = Value;

	return ImagePropsSet(hImage, nTag, &Var);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

HRESULT CAPEx::ImagePropsSet(HANDLE hImage, int nTag, LPSYSTEMTIME pValue)
{
	SYSTEMTIME	T;
	if (pValue == NULL)
	{
		pValue = &T;
		GetLocalTime(&T);
	}

	VARIANT	Var;
	Var.vt = VT_DATE;
	SystemTimeToVariantTime(pValue, &Var.date);

	return ImagePropsSet(hImage, nTag, &Var);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

HRESULT CAPEx::ImagePropsDelete(HANDLE hImage, int nTag)
{
	VARIANT	Var;
	VariantInit(&Var);

	return ImagePropsSet(hImage, nTag, &Var);
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

typedef struct VS_VERSIONINFO 
{ 
	WORD				wLength; 
	WORD				wValueLength; 
	WORD				wType; 
	WCHAR				szKey[sizeof("VS_VERSION_INFO")]; 
	WORD				Padding1[1]; // Ensures 32bit alignment
	VS_FIXEDFILEINFO	Value; 
	//WORD				Padding2[]; 
	//WORD				Children[]; 
}
VS_VERSIONINFO;

//--------------------------------------------------------------------

HRESULT CAPEx::GetVersion(HINSTANCE hInstance, VS_FIXEDFILEINFO& Version)
{
	TCHAR		FileName[MAX_PATH];

	::GetModuleFileName(hInstance, FileName, MAX_PATH);

	DWORD	VersionHandle = 0;
	DWORD VersionInfoSize = ::GetFileVersionInfoSize(FileName, &VersionHandle);
	if (VersionInfoSize == 0)
	{
		return E_FAIL;
	}

	VS_VERSIONINFO* VersionInfo = (VS_VERSIONINFO*)new BYTE [VersionInfoSize];

	BOOL Result = GetFileVersionInfo(FileName, VersionHandle, VersionInfoSize, VersionInfo);
	if (Result)
	{
		Version = VersionInfo->Value;
	}

	delete [] (LPBYTE)VersionInfo;

	return Result ? S_OK : E_FAIL;
}

//--------------------------------------------------------------------
//
//--------------------------------------------------------------------

