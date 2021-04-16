/*----------------------------------------------------------------------------
 *      CL3000 LED Screen Controller
 *----------------------------------------------------------------------------
 *      Name:    MiniLED.cpp
 *      Purpose: CL3000 API functions.
 *----------------------------------------------------------------------------
 *      Copyright (c) 2010 Lytec Inc. All rights reserved.
 *---------------------------------------------------------------------------*/
#include "stdafx.h"
#include "MiniLED.h"

_MC_ComInitial        MC_ComInitial;
_MC_NetInitial        MC_NetInitial;
_MC_Close             MC_Close;
_MC_Reset             MC_Reset;
_MC_SetLEDNum         MC_SetLEDNum;
_MC_SetRemoteIP       MC_SetRemoteIP;
_MC_ControlPlay       MC_ControlPlay;
_MC_SetBright         MC_SetBright;
_MC_SetPowerMode      MC_SetPowerMode;
_MC_SetAutoPower      MC_SetAutoPower;
_MC_SendBrightTable   MC_SendBrightTable;
_MC_SetDispParams     MC_SetDispParams;
_MC_SetClock          MC_SetClock;
_MC_GetClock          MC_GetClock;
_MC_GetRunTimeInfo    MC_GetRunTimeInfo;
_MC_ChangeGroup       MC_ChangeGroup;

_MC_SendProgList      MC_SendProgList;
_MC_SendXMPXPic       MC_SendXMPXPic;
_MC_GetXMPXPic        MC_GetXMPXPic;
_MC_SendText          MC_SendText;
_MC_SendRTView        MC_SendRTView;
_MC_GetRTViewPkt      MC_GetRTViewPkt;
_MC_SendFontInfo      MC_SendFontInfo;
_MC_SendFontLibPkt    MC_SendFontLibPkt;
_MC_ShowString        MC_ShowString;
_MC_TxtToXMPXFile     MC_TxtToXMPXFile;
_MC_ShowXMPXPic       MC_ShowXMPXPic;

_MC_InitForPackage    MC_InitForPackage;
_MC_GetPackage        MC_GetPackage;
_MC_CheckAnswer       MC_CheckAnswer;

HINSTANCE             hMC_DLL;

/******************************************************************************
* Function Name  : LoadMiniLEDdll
* Description    : Load MiniLED dll.
* Input          : None
* Output         : None
* Return         : TRUE if load sucessfully, else FALSE.
*******************************************************************************/
BOOL LoadMiniLEDdll( void )
{
  hMC_DLL = ::LoadLibrary("MiniLED.dll");

  // 获取可调用的函数的指针
  // Get pointer of functions in the DLL
  if (hMC_DLL!=NULL)
  {
    MC_ComInitial     = (_MC_ComInitial    )::GetProcAddress(hMC_DLL, "MC_ComInitial"    );
    MC_NetInitial     = (_MC_NetInitial    )::GetProcAddress(hMC_DLL, "MC_NetInitial"    );
    MC_Close          = (_MC_Close         )::GetProcAddress(hMC_DLL, "MC_Close"         );
    MC_Reset          = (_MC_Reset         )::GetProcAddress(hMC_DLL, "MC_Reset"         );
    MC_SetLEDNum      = (_MC_SetLEDNum     )::GetProcAddress(hMC_DLL, "MC_SetLEDNum"     );
    MC_SetRemoteIP    = (_MC_SetRemoteIP   )::GetProcAddress(hMC_DLL, "MC_SetRemoteIP"   );
    MC_ControlPlay    = (_MC_ControlPlay   )::GetProcAddress(hMC_DLL, "MC_ControlPlay"   );
    MC_SetBright      = (_MC_SetBright     )::GetProcAddress(hMC_DLL, "MC_SetBright"     );
    MC_SetPowerMode   = (_MC_SetPowerMode  )::GetProcAddress(hMC_DLL, "MC_SetPowerMode"  );
    MC_SetAutoPower   = (_MC_SetAutoPower  )::GetProcAddress(hMC_DLL, "MC_SetAutoPower"  );
    MC_SendBrightTable= (_MC_SendBrightTable)::GetProcAddress(hMC_DLL, "MC_SendBrightTable");
    MC_SetDispParams  = (_MC_SetDispParams )::GetProcAddress(hMC_DLL, "MC_SetDispParams" );
    MC_SetClock       = (_MC_SetClock      )::GetProcAddress(hMC_DLL, "MC_SetClock"      );
    MC_GetClock       = (_MC_GetClock      )::GetProcAddress(hMC_DLL, "MC_GetClock"      );
    MC_GetRunTimeInfo = (_MC_GetRunTimeInfo)::GetProcAddress(hMC_DLL, "MC_GetRunTimeInfo");
    MC_ChangeGroup    = (_MC_ChangeGroup   )::GetProcAddress(hMC_DLL, "MC_ChangeGroup"   );

    MC_SendProgList   = (_MC_SendProgList  )::GetProcAddress(hMC_DLL, "MC_SendProgList"  );
    MC_SendXMPXPic    = (_MC_SendXMPXPic   )::GetProcAddress(hMC_DLL, "MC_SendXMPXPic"   );
    MC_GetXMPXPic     = (_MC_GetXMPXPic    )::GetProcAddress(hMC_DLL, "MC_GetXMPXPic"    );
    MC_SendText       = (_MC_SendText      )::GetProcAddress(hMC_DLL, "MC_SendText"      );
    MC_SendRTView     = (_MC_SendRTView    )::GetProcAddress(hMC_DLL, "MC_SendRTView"    );
    MC_GetRTViewPkt   = (_MC_GetRTViewPkt  )::GetProcAddress(hMC_DLL, "MC_GetRTViewPkt"  );
    MC_SendFontInfo   = (_MC_SendFontInfo  )::GetProcAddress(hMC_DLL, "MC_SendFontInfo"  );
    MC_SendFontLibPkt = (_MC_SendFontLibPkt)::GetProcAddress(hMC_DLL, "MC_SendFontLibPkt");
    MC_ShowString     = (_MC_ShowString    )::GetProcAddress(hMC_DLL, "MC_ShowString"    );
    MC_TxtToXMPXFile  = (_MC_TxtToXMPXFile )::GetProcAddress(hMC_DLL, "MC_TxtToXMPXFile" );
    MC_ShowXMPXPic    = (_MC_ShowXMPXPic   )::GetProcAddress(hMC_DLL, "MC_ShowXMPXPic"   );

    MC_InitForPackage = (_MC_InitForPackage)::GetProcAddress(hMC_DLL, "MC_InitForPackage");
    MC_GetPackage     = (_MC_GetPackage    )::GetProcAddress(hMC_DLL, "MC_GetPackage"    );
    MC_CheckAnswer    = (_MC_CheckAnswer   )::GetProcAddress(hMC_DLL, "MC_CheckAnswer"   );
  }

  // 判断函数指针获取成功否
  // Check these pointer
  if ((!hMC_DLL          ) ||
      (!MC_ComInitial    ) ||
      (!MC_NetInitial    ) ||
      (!MC_Close         ) ||
      (!MC_Reset         ) ||
      (!MC_SetLEDNum     ) ||
      (!MC_SetRemoteIP   ) ||
      (!MC_ControlPlay   ) ||
      (!MC_SetBright     ) ||
      (!MC_SetPowerMode  ) ||
      (!MC_SetAutoPower  ) ||
      (!MC_SendBrightTable)||
      (!MC_SetDispParams ) ||
      (!MC_SetClock      ) ||
      (!MC_GetClock      ) ||
      (!MC_GetRunTimeInfo) ||
      (!MC_ChangeGroup   ) ||

      (!MC_SendProgList  ) ||
      (!MC_SendXMPXPic   ) ||
      (!MC_GetXMPXPic    ) ||
      (!MC_SendText      ) ||
      (!MC_SendRTView    ) ||
      (!MC_GetRTViewPkt  ) ||
      (!MC_SendFontInfo  ) ||
      (!MC_SendFontLibPkt) ||
      (!MC_ShowString    ) ||
      (!MC_TxtToXMPXFile ) ||
      (!MC_ShowXMPXPic   ) ||

      (!MC_InitForPackage) ||
      (!MC_GetPackage    ) ||
      (!MC_CheckAnswer   )
     )
  {
    FreeLibrary(hMC_DLL);
    hMC_DLL = NULL;
    return FALSE;
  }

  return TRUE;
}

/******************************************************************************
* Function Name  : FreeMiniLEDdll
* Description    : Release MiniLED dll.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void FreeMiniLEDdll( void )
{
  if (hMC_DLL != NULL) ::FreeLibrary(hMC_DLL);
}