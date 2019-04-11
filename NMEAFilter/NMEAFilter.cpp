#include "stdafx.h"
#include "APEx.h"
#include "resource.h"

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

HWND                  g_hWnd           = NULL;
APEX_PFN_EVALUATE     g_fnEvaluate     = NULL;

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

const TCHAR APExName[]    = TEXT("ArcPad NMEA Filter");
const DWORD APExCodeName  = *(DWORD *) "@~NM";

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

extern "C" APEXDECL LRESULT APExInitialize(HWND hWnd)
{
    g_hWnd = hWnd;
    g_fnEvaluate = APEX_GetFunction(hWnd, EVALUATE);
    return APEX_TYPE_UTILITY;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

extern "C" APEXDECL LRESULT APExTerminate(void)
{
    return APEX_TRUE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

extern "C" APEXDECL LRESULT APExPreTranslateNMEA(LPSTR pSentence, int nFields, LPCSTR pFields[], INSTRUMENT *pInstrument)
{
	char Filters[1024] = "!$BD;$";
	char* FiltersEnv = getenv("NMEAFILTERS");
	char* DebugEnv = getenv("NMEAFILTERS_DEBUG");
	int debugMode = (DebugEnv != NULL && strcmp(DebugEnv, "YES") == 0) ? 1 : 0;

	static DWORD lastShownAccept = 0;
	static DWORD lastShownReject = 0;

	char* pFilter = (FiltersEnv != NULL && *FiltersEnv != '\0') ? FiltersEnv : Filters;
	while (pFilter && *pFilter != '0')
	{
		char* pFilterEnd = strchr(pFilter, ';');
		if (*pFilter == '!')
		{
			pFilter++;
			int n = pFilterEnd ? (pFilterEnd - pFilter) : strlen(pFilter);
			if (strncmp(pSentence, pFilter, n) == 0)
			{
				if (debugMode > 0)
				{
					if (GetTickCount() > lastShownReject + 10000)
					{
						MessageBoxA(g_hWnd, pSentence, "Reject", MB_OK);
						lastShownReject = GetTickCount();
					}
				}
				return APEX_TRUE;
			}
		}
		else
		{
			int n = pFilterEnd ? (pFilterEnd - pFilter) : strlen(pFilter);
			if (strncmp(pSentence, pFilter, n) == 0)
			{
				if (debugMode > 0)
				{
					if (GetTickCount() > lastShownAccept + 10000)
					{
						MessageBoxA(g_hWnd, pSentence, pFilter, MB_OK);
						lastShownAccept = GetTickCount();
					}
				}
				return APEX_FALSE;
			}
		}
		pFilter = pFilterEnd ? pFilterEnd + 1 : NULL;
	}

	return APEX_FALSE;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------

extern "C" APEXDECL LRESULT APExGetProperty(DWORD nProp, LONG nIndex, LPVOID pInfo)
{
    switch (nProp)
    {
    case APEX_PROP_FLAGS :
        return APEX_FLAG_NONE;

    case APEX_PROP_NAME :
        if (pInfo != NULL)
        {
            _tcscpy((LPTSTR) pInfo, APExName);
        }
        return _tcslen(APExName);

    case APEX_PROP_CODENAME :
        memcpy(pInfo, &APExCodeName, 4);
        return APEX_TRUE;

    case APEX_PROP_TOOL_ICON :
        return IDI_NMEA_FILTER;
    }

    return APEX_NOT_IMPLEMENTED;
}

//----------------------------------------------------------------------
//
//----------------------------------------------------------------------
