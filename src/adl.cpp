/*******************************************************************************

 * This program reads HW information from your ATI Radeon card and displays them
 * You can also change frequencies and voltages.

 * THIS PROGRAM MAY DAMAGE YOUR VIDEO CARD, IF YOU APPLY NONSENSIAL VALUES.
 * e.g. INCREASING THE VOLTAGES AND FREQUENCIES IN CONJUNCTION WITH LOWERING THE
 *      FAN SPEED IS NOT ADVISABLE!

 * Copyright(C) Thorsten Gilling (tgilling@web.de)

 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*******************************************************************************/

#include "adl.h"

#include <iostream>

#ifdef FAKE_ATI_CARD
#define GPA(x,y) x=NULL;
#else
#define GPA(x,y) x=(y)GetProcAddress(hDLL, #x); if(x == NULL) { cout << "API: " << #x << " is missing." << endl; /*return false;*/ }
#endif

using namespace std;

ADL* ADL::ms_instance = NULL;

ADL::ADL()
    : ADL_Main_Control_Create(NULL)
    , ADL_Main_Control_Refresh(NULL)
    , ADL_Main_Control_Destroy(NULL)
    , ADL_Graphics_Platform_Get(NULL)
    , ADL_Adapter_Active_Get(NULL)
    , ADL_Adapter_NumberOfAdapters_Get(NULL)
    , ADL_Adapter_AdapterInfo_Get(NULL)
    , ADL_Adapter_ASICFamilyType_Get(NULL)
    , ADL_Adapter_Speed_Caps(NULL)
    , ADL_Adapter_Speed_Get(NULL)
    , ADL_Adapter_Speed_Set(NULL)
    , ADL_Adapter_Accessibility_Get(NULL)
    , ADL_Adapter_VideoBiosInfo_Get(NULL)
    , ADL_Adapter_ID_Get(NULL)
    , ADL_Adapter_CrossdisplayAdapterRole_Caps(NULL)
    , ADL_Adapter_CrossdisplayInfo_Get(NULL)
    , ADL_Adapter_CrossdisplayInfo_Set(NULL)
    , ADL_Adapter_Crossfire_Caps(NULL)
    , ADL_Adapter_Crossfire_Get(NULL)
    , ADL_Adapter_Crossfire_Set(NULL)
    , ADL_Display_DisplayInfo_Get(NULL)
    , ADL_Display_NumberOfDisplays_Get(NULL)
    , ADL_Display_PreservedAspectRatio_Get(NULL)
    , ADL_Display_PreservedAspectRatio_Set(NULL)
    , ADL_Display_ImageExpansion_Get(NULL)
    , ADL_Display_ImageExpansion_Set(NULL)
    , ADL_Display_Position_Get(NULL)
    , ADL_Display_Position_Set(NULL)
    , ADL_Display_Size_Get(NULL)
    , ADL_Display_Size_Set(NULL)
    , ADL_Display_AdjustCaps_Get(NULL)
    , ADL_Display_Capabilities_Get(NULL)
    , ADL_Display_ConnectedDisplays_Get(NULL)
    , ADL_Display_DeviceConfig_Get(NULL)
    , ADL_Display_Property_Get(NULL)
    , ADL_Display_Property_Set(NULL)
    , ADL_Display_SwitchingCapability_Get(NULL)
    , ADL_Display_DitherState_Get(NULL)
    , ADL_Display_DitherState_Set(NULL)
    , ADL_Display_SupportedPixelFormat_Get(NULL)
    , ADL_Display_PixelFormat_Get(NULL)
    , ADL_Display_PixelFormat_Set(NULL)
    , ADL_Display_ODClockInfo_Get(NULL)
    , ADL_Display_ODClockConfig_Set(NULL)
    , ADL_Display_AdjustmentCoherent_Get(NULL)
    , ADL_Display_AdjustmentCoherent_Set(NULL)
    , ADL_Display_ReducedBlanking_Get(NULL)
    , ADL_Display_ReducedBlanking_Set(NULL)
    , ADL_Display_FormatsOverride_Get(NULL)
    , ADL_Display_FormatsOverride_Set(NULL)
    , ADL_Display_MVPUCaps_Get(NULL)
    , ADL_Display_MVPUStatus_Get(NULL)
    , ADL_Adapter_Active_Set(NULL)
    , ADL_Adapter_Active_SetPrefer(NULL)
    , ADL_Adapter_Primary_Get(NULL)
    , ADL_Adapter_Primary_Set(NULL)
    , ADL_Adapter_ModeSwitch(NULL)
    , ADL_Display_Modes_Get(NULL)
    , ADL_Display_Modes_Set(NULL)
    , ADL_Display_PossibleMode_Get(NULL)
    , ADL_Display_ForcibleDisplay_Get(NULL)
    , ADL_Display_ForcibleDisplay_Set(NULL)
    , ADL_Adapter_NumberOfActivatableSources_Get(NULL)
    , ADL_Adapter_Display_Caps(NULL)
    , ADL_Display_DisplayMapConfig_Get(NULL)
    , ADL_Display_DisplayMapConfig_Set(NULL)
    , ADL_Display_PossibleMapping_Get(NULL)
    , ADL_Display_DisplayMapConfig_Validate(NULL)
    , ADL_Display_DisplayMapConfig_PossibleAddAndRemove(NULL)
    , ADL_Display_SLSGrid_Caps(NULL)
    , ADL_Display_SLSMapIndexList_Get(NULL)
    , ADL_Display_SLSMapIndex_Get(NULL)
    , ADL_Display_SLSMapConfig_Get(NULL)
    , ADL_Display_SLSMapConfig_Create(NULL)
    , ADL_Display_SLSMapConfig_Delete(NULL)
    , ADL_Display_SLSMapConfig_SetState(NULL)
    , ADL_Display_SLSMapConfig_Rearrange(NULL)
    , ADL_Display_PossibleMode_WinXP_Get(NULL)
    , ADL_Display_BezelOffsetSteppingSize_Get(NULL)
    , ADL_Display_BezelOffset_Set(NULL)
    , ADL_Display_BezelSupported_Validate(NULL)
    , ADL_Display_ColorCaps_Get(NULL)
    , ADL_Display_Color_Set(NULL)
    , ADL_Display_Color_Get(NULL)
    , ADL_Display_ColorTemperatureSource_Get(NULL)
    , ADL_Display_ColorTemperatureSource_Set(NULL)
    , ADL_Display_ModeTimingOverride_Get(NULL)
    , ADL_Display_ModeTimingOverride_Set(NULL)
    , ADL_Display_ModeTimingOverrideList_Get(NULL)
    , ADL_Display_CustomizedModeListNum_Get(NULL)
    , ADL_Display_CustomizedModeList_Get(NULL)
    , ADL_Display_CustomizedMode_Add(NULL)
    , ADL_Display_CustomizedMode_Delete(NULL)
    , ADL_Display_CustomizedMode_Validate(NULL)
    , ADL_Display_Underscan_Set(NULL)
    , ADL_Display_Underscan_Get(NULL)
    , ADL_Display_Overscan_Set(NULL)
    , ADL_Display_Overscan_Get(NULL)
    , ADL_Display_ControllerOverlayAdjustmentCaps_Get(NULL)
    , ADL_Display_ControllerOverlayAdjustmentData_Get(NULL)
    , ADL_Display_ControllerOverlayAdjustmentData_Set(NULL)
    , ADL_Display_PowerXpressVersion_Get(NULL)
    , ADL_Display_PowerXpressActiveGPU_Get(NULL)
    , ADL_Display_PowerXpressActiveGPU_Set(NULL)
    , ADL_Display_PowerXpress_AutoSwitchConfig_Get(NULL)
    , ADL_Display_PowerXpress_AutoSwitchConfig_Set(NULL)
    , ADL_DFP_BaseAudioSupport_Get(NULL)
    , ADL_DFP_HDMISupport_Get(NULL)
    , ADL_DFP_MVPUAnalogSupport_Get(NULL)
    , ADL_DFP_PixelFormat_Caps(NULL)
    , ADL_DFP_PixelFormat_Get(NULL)
    , ADL_DFP_PixelFormat_Set(NULL)
    , ADL_DFP_GPUScalingEnable_Get(NULL)
    , ADL_DFP_GPUScalingEnable_Set(NULL)
    , ADL_DFP_AllowOnlyCETimings_Get(NULL)
    , ADL_DFP_AllowOnlyCETimings_Set(NULL)
    , ADL_Display_TVCaps_Get(NULL)
    , ADL_TV_Standard_Set(NULL)
    , ADL_TV_Standard_Get(NULL)
    , ADL_CV_DongleSettings_Get(NULL)
    , ADL_CV_DongleSettings_Set(NULL)
    , ADL_CV_DongleSettings_Reset(NULL)
    , ADL_Overdrive5_CurrentActivity_Get(NULL)
    , ADL_Overdrive5_ThermalDevices_Enum(NULL)
    , ADL_Overdrive5_Temperature_Get(NULL)
    , ADL_Overdrive5_FanSpeedInfo_Get(NULL)
    , ADL_Overdrive5_FanSpeed_Get(NULL)
    , ADL_Overdrive5_FanSpeed_Set(NULL)
    , ADL_Overdrive5_FanSpeedToDefault_Set(NULL)
    , ADL_Overdrive5_ODParameters_Get(NULL)
    , ADL_Overdrive5_ODPerformanceLevels_Get(NULL)
    , ADL_Overdrive5_ODPerformanceLevels_Set(NULL)
    , ADL_Display_WriteAndReadI2CRev_Get(NULL)
    , ADL_Display_WriteAndReadI2C(NULL)
    , ADL_Display_DDCBlockAccess_Get(NULL)
    , ADL_Display_DDCInfo_Get(NULL)
    , ADL_Display_EdidData_Get(NULL)
    , ADL_Workstation_Caps(NULL)
    , ADL_Workstation_Stereo_Get(NULL)
    , ADL_Workstation_Stereo_Set(NULL)
    , ADL_Workstation_AdapterNumOfGLSyncConnectors_Get(NULL)
    , ADL_Workstation_DisplayGenlockCapable_Get(NULL)
    , ADL_Workstation_GLSyncModuleDetect_Get(NULL)
    , ADL_Workstation_GLSyncModuleInfo_Get(NULL)
    , ADL_Workstation_GLSyncGenlockConfiguration_Get(NULL)
    , ADL_Workstation_GLSyncGenlockConfiguration_Set(NULL)
    , ADL_Workstation_GLSyncPortState_Get(NULL)
    , ADL_Workstation_GLSyncPortState_Set(NULL)
    , ADL_Workstation_DisplayGLSyncMode_Get(NULL)
    , ADL_Workstation_DisplayGLSyncMode_Set(NULL)
    , ADL_Workstation_GLSyncSupportedTopology_Get(NULL)
    , ADL_Workstation_LoadBalancing_Get(NULL)
    , ADL_Workstation_LoadBalancing_Set(NULL)
    , ADL_Workstation_LoadBalancing_Caps(NULL)
#ifdef LINUX
    , ADL_Adapter_MemoryInfo_Get(NULL)
    , ADL_DesktopConfig_Get(NULL)
    , ADL_DesktopConfig_Set(NULL)
    , ADL_NumberOfDisplayEnable_Get(NULL)
    , ADL_DisplayEnable_Set(NULL)
    , ADL_Display_IdentifyDisplay(NULL)
    , ADL_Display_LUTColor_Set(NULL)
    , ADL_Display_LUTColor_Get(NULL)
    , ADL_Adapter_XScreenInfo_Get(NULL)
    , ADL_Display_XrandrDisplayName_Get(NULL)
#endif
    , mNrOfAdapters(0)
    , mpAdapterInfo(NULL)
    , mpODPerformanceLevels(NULL)
    , hDLL(NULL)
    , mFeatures(0)
{
}

ADL::~ADL()
{
    if (mpODPerformanceLevels != NULL)
    {
	free (mpODPerformanceLevels);
	mpODPerformanceLevels = NULL;
    }
}

ADL* ADL::Instance()
{
    if(ms_instance == NULL)
    {
        ms_instance = new ADL();
        if (ms_instance)
        {
            if (!ms_instance->Init())
            {
                cout << "Error: Could not Init library." << endl;
            }
        }
    }
    return ms_instance;
}

void ADL::Release()
{
    if(ms_instance)
    {
	ms_instance->ADL_Main_Control_Destroy ();

    #if defined (LINUX)
	dlclose(ms_instance->hDLL);
    #else
	FreeLibrary(ms_instance->hDLL);
    #endif

        delete ms_instance;
    }
    ms_instance = NULL;
}

#ifdef LINUX
void* ADL::GetProcAddress(void* pLibrary, const char* name)
{
    return dlsym(pLibrary, name);
}
#endif

// Memory allocation function
void* __stdcall ADL::sADL_Main_Memory_Alloc (int iSize)
{
    void* lpBuffer = malloc ( iSize );
    return lpBuffer;
}

void* __stdcall ADL::ADL_Main_Memory_Alloc (int iSize)
{
    return sADL_Main_Memory_Alloc(iSize);
}

// Optional Memory de-allocation function
void __stdcall ADL::ADL_Main_Memory_Free (void** lpBuffer)
{
    if ( NULL != *lpBuffer )
    {
        free ( *lpBuffer );
        *lpBuffer = NULL;
    }
}

bool ADL::Init()
{
#ifndef FAKE_ATI_CARD
#if defined (LINUX)
    hDLL = dlopen( "libatiadlxx.so", RTLD_LAZY|RTLD_GLOBAL);
#else
    hDLL = LoadLibrary("atiadlxx.dll");
    if (hDLL == NULL)
        // A 32 bit calling application on 64 bit OS will fail to LoadLIbrary.
        // Try to load the 32 bit library (atiadlxy.dll) instead
        hDLL = LoadLibrary("atiadlxy.dll");
#endif

    if (NULL == hDLL)
    {
        return false;
    }
#else
    mNrOfAdapters = 1;
#endif

    GPA(ADL_Main_Control_Create, ADL_MAIN_CONTROL_CREATE)
    GPA(ADL_Main_Control_Destroy, ADL_MAIN_CONTROL_DESTROY)
    GPA(ADL_Adapter_NumberOfAdapters_Get, ADL_ADAPTER_NUMBEROFADAPTERS_GET)
    GPA(ADL_Adapter_AdapterInfo_Get, ADL_ADAPTER_ADAPTERINFO_GET)
    GPA(ADL_Display_DisplayInfo_Get, ADL_DISPLAY_DISPLAYINFO_GET)
    GPA(ADL_Display_ColorCaps_Get, ADL_DISPLAY_COLORCAPS_GET)
    GPA(ADL_Display_Color_Get, ADL_DISPLAY_COLOR_GET)
    GPA(ADL_Display_Color_Set, ADL_DISPLAY_COLOR_SET)

    GPA(ADL_Main_Control_Create, ADL_MAIN_CONTROL_CREATE)
    GPA(ADL_Main_Control_Refresh, ADL_MAIN_CONTROL_REFRESH)
    GPA(ADL_Main_Control_Destroy, ADL_MAIN_CONTROL_DESTROY)
    GPA(ADL_Graphics_Platform_Get, ADL_GRAPHICS_PLATFORM_GET)

    GPA(ADL_Adapter_Active_Get, ADL_ADAPTER_ACTIVE_GET)
    GPA(ADL_Adapter_NumberOfAdapters_Get, ADL_ADAPTER_NUMBEROFADAPTERS_GET)
    GPA(ADL_Adapter_AdapterInfo_Get, ADL_ADAPTER_ADAPTERINFO_GET)
    GPA(ADL_Adapter_ASICFamilyType_Get, ADL_ADAPTER_ASICFAMILYTYPE_GET)
    GPA(ADL_Adapter_Speed_Caps,	ADL_ADAPTER_SPEED_CAPS)
    GPA(ADL_Adapter_Speed_Get, ADL_ADAPTER_SPEED_GET)
    GPA(ADL_Adapter_Speed_Set, ADL_ADAPTER_SPEED_SET)
    GPA(ADL_Adapter_Accessibility_Get, ADL_ADAPTER_ACCESSIBILITY_GET)
    GPA(ADL_Adapter_VideoBiosInfo_Get, ADL_ADAPTER_VIDEOBIOSINFO_GET)
    GPA(ADL_Adapter_ID_Get, ADL_ADAPTER_ID_GET)

    GPA(ADL_Adapter_CrossdisplayAdapterRole_Caps, ADL_ADAPTER_CROSSDISPLAYADAPTERROLE_CAPS)
    GPA(ADL_Adapter_CrossdisplayInfo_Get, ADL_ADAPTER_CROSSDISPLAYINFO_GET)
    GPA(ADL_Adapter_CrossdisplayInfo_Set, ADL_ADAPTER_CROSSDISPLAYINFO_SET)

    GPA(ADL_Adapter_Crossfire_Caps, ADL_ADAPTER_CROSSFIRE_CAPS)
    GPA(ADL_Adapter_Crossfire_Get, ADL_ADAPTER_CROSSFIRE_GET)
    GPA(ADL_Adapter_Crossfire_Set, ADL_ADAPTER_CROSSFIRE_SET)

    GPA(ADL_Display_DisplayInfo_Get, ADL_DISPLAY_DISPLAYINFO_GET)
    GPA(ADL_Display_NumberOfDisplays_Get, ADL_DISPLAY_NUMBEROFDISPLAYS_GET)
    GPA(ADL_Display_PreservedAspectRatio_Get, ADL_DISPLAY_PRESERVEDASPECTRATIO_GET)
    GPA(ADL_Display_PreservedAspectRatio_Set, ADL_DISPLAY_PRESERVEDASPECTRATIO_SET)
    GPA(ADL_Display_ImageExpansion_Get, ADL_DISPLAY_IMAGEEXPANSION_GET)
    GPA(ADL_Display_ImageExpansion_Set, ADL_DISPLAY_IMAGEEXPANSION_SET)
    GPA(ADL_Display_Position_Get, ADL_DISPLAY_POSITION_GET)
    GPA(ADL_Display_Position_Set, ADL_DISPLAY_POSITION_SET)
    GPA(ADL_Display_Size_Get, ADL_DISPLAY_SIZE_GET)
    GPA(ADL_Display_Size_Set, ADL_DISPLAY_SIZE_SET)
    GPA(ADL_Display_AdjustCaps_Get, ADL_DISPLAY_ADJUSTCAPS_GET)
    GPA(ADL_Display_Capabilities_Get, ADL_DISPLAY_CAPABILITIES_GET)
    GPA(ADL_Display_ConnectedDisplays_Get, ADL_DISPLAY_CONNECTEDDISPLAYS_GET)
    GPA(ADL_Display_DeviceConfig_Get, ADL_DISPLAY_DEVICECONFIG_GET)
    GPA(ADL_Display_Property_Get, ADL_DISPLAY_PROPERTY_GET)
    GPA(ADL_Display_Property_Set, ADL_DISPLAY_PROPERTY_SET)
    GPA(ADL_Display_SwitchingCapability_Get, ADL_DISPLAY_SWITCHINGCAPABILITY_GET)
    GPA(ADL_Display_DitherState_Get, ADL_DISPLAY_DITHERSTATE_GET)
    GPA(ADL_Display_DitherState_Set, ADL_DISPLAY_DITHERSTATE_SET)
    GPA(ADL_Display_SupportedPixelFormat_Get, ADL_DISPLAY_SUPPORTEDPIXELFORMAT_GET)
    GPA(ADL_Display_PixelFormat_Get, ADL_DISPLAY_PIXELFORMAT_GET)
    GPA(ADL_Display_PixelFormat_Set, ADL_DISPLAY_PIXELFORMAT_SET)
    GPA(ADL_Display_ODClockInfo_Get, ADL_DISPLAY_ODCLOCKINFO_GET)
    GPA(ADL_Display_ODClockConfig_Set, ADL_DISPLAY_ODCLOCKCONFIG_SET)
    GPA(ADL_Display_AdjustmentCoherent_Get, ADL_DISPLAY_ADJUSTMENTCOHERENT_GET)
    GPA(ADL_Display_AdjustmentCoherent_Set, ADL_DISPLAY_ADJUSTMENTCOHERENT_SET)
    GPA(ADL_Display_ReducedBlanking_Get, ADL_DISPLAY_REDUCEDBLANKING_GET)
    GPA(ADL_Display_ReducedBlanking_Set, ADL_DISPLAY_REDUCEDBLANKING_SET)
    GPA(ADL_Display_FormatsOverride_Get, ADL_DISPLAY_FORMATSOVERRIDE_GET)
    GPA(ADL_Display_FormatsOverride_Set, ADL_DISPLAY_FORMATSOVERRIDE_SET)
    GPA(ADL_Display_MVPUCaps_Get, ADL_DISPLAY_MVPUCAPS_GET)
    GPA(ADL_Display_MVPUStatus_Get, ADL_DISPLAY_MVPUSTATUS_GET)

    GPA(ADL_Adapter_Active_Set, ADL_ADAPTER_ACTIVE_SET)
    GPA(ADL_Adapter_Active_SetPrefer, ADL_ADAPTER_ACTIVE_SETPREFER)
    GPA(ADL_Adapter_Primary_Get, ADL_ADAPTER_PRIMARY_GET)
    GPA(ADL_Adapter_Primary_Set, ADL_ADAPTER_PRIMARY_SET)
    GPA(ADL_Adapter_ModeSwitch, ADL_ADAPTER_MODESWITCH)
    GPA(ADL_Display_Modes_Get, ADL_DISPLAY_MODES_GET)
    GPA(ADL_Display_Modes_Set, ADL_DISPLAY_MODES_SET)
    GPA(ADL_Display_PossibleMode_Get, ADL_DISPLAY_POSSIBLEMODE_GET)
    GPA(ADL_Display_ForcibleDisplay_Get, ADL_DISPLAY_FORCIBLEDISPLAY_GET)
    GPA(ADL_Display_ForcibleDisplay_Set, ADL_DISPLAY_FORCIBLEDISPLAY_SET)
    GPA(ADL_Adapter_NumberOfActivatableSources_Get, ADL_ADAPTER_NUMBEROFACTIVATABLESOURCES_GET)
    GPA(ADL_Adapter_Display_Caps, ADL_ADAPTER_DISPLAY_CAPS)
    GPA(ADL_Display_DisplayMapConfig_Get, ADL_DISPLAY_DISPLAYMAPCONFIG_GET)
    GPA(ADL_Display_DisplayMapConfig_Set, ADL_DISPLAY_DISPLAYMAPCONFIG_SET)
    GPA(ADL_Display_PossibleMapping_Get, ADL_DISPLAY_POSSIBLEMAPPING_GET)
    GPA(ADL_Display_DisplayMapConfig_Validate, ADL_DISPLAY_DISPLAYMAPCONFIG_VALIDATE)
    GPA(ADL_Display_DisplayMapConfig_PossibleAddAndRemove, ADL_DISPLAY_DISPLAYMAPCONFIG_POSSIBLEADDANDREMOVE)
    GPA(ADL_Display_SLSGrid_Caps, ADL_DISPLAY_SLSGRID_CAPS)
    GPA(ADL_Display_SLSMapIndexList_Get, ADL_DISPLAY_SLSMAPINDEXLIST_GET)
    GPA(ADL_Display_SLSMapIndex_Get, ADL_DISPLAY_SLSMAPINDEX_GET)
    GPA(ADL_Display_SLSMapConfig_Get, ADL_DISPLAY_SLSMAPCONFIG_GET)
    GPA(ADL_Display_SLSMapConfig_Create, ADL_DISPLAY_SLSMAPCONFIG_CREATE)
    GPA(ADL_Display_SLSMapConfig_Delete, ADL_DISPLAY_SLSMAPCONFIG_DELETE)
    GPA(ADL_Display_SLSMapConfig_SetState, ADL_DISPLAY_SLSMAPCONFIG_SETSTATE)
    GPA(ADL_Display_SLSMapConfig_Rearrange, ADL_DISPLAY_SLSMAPCONFIG_REARRANGE)
    #ifndef LINUX
	//ADL_Display_PossibleMode_WinXP_Get= NULL;
	GPA(ADL_Display_PossibleMode_WinXP_Get, ADL_DISPLAY_POSSIBLEMODE_WINXP_GET)
    #else
	ADL_Display_PossibleMode_WinXP_Get = NULL;
    #endif
    GPA(ADL_Display_BezelOffsetSteppingSize_Get, ADL_DISPLAY_BEZELOFFSETSTEPPINGSIZE_GET)
    GPA(ADL_Display_BezelOffset_Set, ADL_DISPLAY_BEZELOFFSET_SET)
    GPA(ADL_Display_BezelSupported_Validate, ADL_DISPLAY_BEZELSUPPORTED_VALIDATE)

    GPA(ADL_Display_ColorCaps_Get, ADL_DISPLAY_COLORCAPS_GET)
    GPA(ADL_Display_Color_Set, ADL_DISPLAY_COLOR_SET)
    GPA(ADL_Display_Color_Get, ADL_DISPLAY_COLOR_GET)
    GPA(ADL_Display_ColorTemperatureSource_Get, ADL_DISPLAY_COLORTEMPERATURESOURCE_GET)
    GPA(ADL_Display_ColorTemperatureSource_Set, ADL_DISPLAY_COLORTEMPERATURESOURCE_SET)

    GPA(ADL_Display_ModeTimingOverride_Get, ADL_DISPLAY_MODETIMINGOVERRIDE_GET)
    GPA(ADL_Display_ModeTimingOverride_Set, ADL_DISPLAY_MODETIMINGOVERRIDE_SET)
    GPA(ADL_Display_ModeTimingOverrideList_Get, ADL_DISPLAY_MODETIMINGOVERRIDELIST_GET)

    GPA(ADL_Display_CustomizedModeListNum_Get, ADL_DISPLAY_CUSTOMIZEDMODELISTNUM_GET)
    GPA(ADL_Display_CustomizedModeList_Get, ADL_DISPLAY_CUSTOMIZEDMODELIST_GET)
    GPA(ADL_Display_CustomizedMode_Add, ADL_DISPLAY_CUSTOMIZEDMODE_ADD)
    GPA(ADL_Display_CustomizedMode_Delete, ADL_DISPLAY_CUSTOMIZEDMODE_DELETE)
    GPA(ADL_Display_CustomizedMode_Validate, ADL_DISPLAY_CUSTOMIZEDMODE_VALIDATE)

    GPA(ADL_Display_Underscan_Set, ADL_DISPLAY_UNDERSCAN_SET)
    GPA(ADL_Display_Underscan_Get, ADL_DISPLAY_UNDERSCAN_GET)
    GPA(ADL_Display_Overscan_Set, ADL_DISPLAY_OVERSCAN_SET)
    GPA(ADL_Display_Overscan_Get, ADL_DISPLAY_OVERSCAN_GET)

    GPA(ADL_Display_ControllerOverlayAdjustmentCaps_Get, ADL_DISPLAY_CONTROLLEROVERLAYADJUSTMENTCAPS_GET)
    GPA(ADL_Display_ControllerOverlayAdjustmentData_Get, ADL_DISPLAY_CONTROLLEROVERLAYADJUSTMENTDATA_GET)
    GPA(ADL_Display_ControllerOverlayAdjustmentData_Set, ADL_DISPLAY_CONTROLLEROVERLAYADJUSTMENTDATA_SET)

    GPA(ADL_Display_PowerXpressVersion_Get, ADL_DISPLAY_POWERXPRESSVERSION_GET)
    GPA(ADL_Display_PowerXpressActiveGPU_Get, ADL_DISPLAY_POWERXPRESSACTIVEGPU_GET)
    GPA(ADL_Display_PowerXpressActiveGPU_Set, ADL_DISPLAY_POWERXPRESSACTIVEGPU_SET)
    GPA(ADL_Display_PowerXpress_AutoSwitchConfig_Get, ADL_DISPLAY_POWERXPRESS_AUTOSWITCHCONFIG_GET)
    GPA(ADL_Display_PowerXpress_AutoSwitchConfig_Set, ADL_DISPLAY_POWERXPRESS_AUTOSWITCHCONFIG_SET)

    GPA(ADL_DFP_BaseAudioSupport_Get, ADL_DFP_BASEAUDIOSUPPORT_GET)
    GPA(ADL_DFP_HDMISupport_Get, ADL_DFP_HDMISUPPORT_GET)
    GPA(ADL_DFP_MVPUAnalogSupport_Get, ADL_DFP_MVPUANALOGSUPPORT_GET)
    GPA(ADL_DFP_PixelFormat_Caps, ADL_DFP_PIXELFORMAT_CAPS)
    GPA(ADL_DFP_PixelFormat_Get, ADL_DFP_PIXELFORMAT_GET)
    GPA(ADL_DFP_PixelFormat_Set, ADL_DFP_PIXELFORMAT_SET)
    GPA(ADL_DFP_GPUScalingEnable_Get, ADL_DFP_GPUSCALINGENABLE_GET)
    GPA(ADL_DFP_GPUScalingEnable_Set, ADL_DFP_GPUSCALINGENABLE_SET)
    GPA(ADL_DFP_AllowOnlyCETimings_Get, ADL_DFP_ALLOWONLYCETIMINGS_GET)
    GPA(ADL_DFP_AllowOnlyCETimings_Set, ADL_DFP_ALLOWONLYCETIMINGS_SET)

    GPA(ADL_Display_TVCaps_Get, ADL_DISPLAY_TVCAPS_GET)
    GPA(ADL_TV_Standard_Set, ADL_TV_STANDARD_SET)
    GPA(ADL_TV_Standard_Get, ADL_TV_STANDARD_GET)

    GPA(ADL_CV_DongleSettings_Get, ADL_CV_DONGLESETTINGS_GET)
    GPA(ADL_CV_DongleSettings_Set, ADL_CV_DONGLESETTINGS_SET)
    GPA(ADL_CV_DongleSettings_Reset, ADL_CV_DONGLESETTINGS_RESET)

    GPA(ADL_Overdrive5_CurrentActivity_Get, ADL_OVERDRIVE5_CURRENTACTIVITY_GET)
    GPA(ADL_Overdrive5_ThermalDevices_Enum, ADL_OVERDRIVE5_THERMALDEVICES_ENUM)
    GPA(ADL_Overdrive5_Temperature_Get, ADL_OVERDRIVE5_TEMPERATURE_GET)
    GPA(ADL_Overdrive5_FanSpeedInfo_Get, ADL_OVERDRIVE5_FANSPEEDINFO_GET)
    GPA(ADL_Overdrive5_FanSpeed_Get, ADL_OVERDRIVE5_FANSPEED_GET)
    GPA(ADL_Overdrive5_FanSpeed_Set, ADL_OVERDRIVE5_FANSPEED_SET)
    GPA(ADL_Overdrive5_FanSpeedToDefault_Set, ADL_OVERDRIVE5_FANSPEEDTODEFAULT_SET)
    GPA(ADL_Overdrive5_ODParameters_Get, ADL_OVERDRIVE5_ODPARAMETERS_GET)
    GPA(ADL_Overdrive5_ODPerformanceLevels_Get, ADL_OVERDRIVE5_ODPERFORMANCELEVELS_GET)
    GPA(ADL_Overdrive5_ODPerformanceLevels_Set, ADL_OVERDRIVE5_ODPERFORMANCELEVELS_SET)

    GPA(ADL_Display_WriteAndReadI2CRev_Get, ADL_DISPLAY_WRITEANDREADI2CREV_GET)
    GPA(ADL_Display_WriteAndReadI2C, ADL_DISPLAY_WRITEANDREADI2C)
    GPA(ADL_Display_DDCBlockAccess_Get, ADL_DISPLAY_DDCBLOCKACCESS_GET)
    GPA(ADL_Display_DDCInfo_Get, ADL_DISPLAY_DDCINFO_GET)
    GPA(ADL_Display_EdidData_Get, ADL_DISPLAY_EDIDDATA_GET)

    GPA(ADL_Workstation_Caps, ADL_WORKSTATION_CAPS)
    GPA(ADL_Workstation_Stereo_Get, ADL_WORKSTATION_STEREO_GET)
    GPA(ADL_Workstation_Stereo_Set, ADL_WORKSTATION_STEREO_SET)
    GPA(ADL_Workstation_AdapterNumOfGLSyncConnectors_Get, ADL_WORKSTATION_ADAPTERNUMOFGLSYNCCONNECTORS_GET)
    GPA(ADL_Workstation_DisplayGenlockCapable_Get, ADL_WORKSTATION_DISPLAYGENLOCKCAPABLE_GET)
    GPA(ADL_Workstation_GLSyncModuleDetect_Get, ADL_WORKSTATION_GLSYNCMODULEDETECT_GET)
    GPA(ADL_Workstation_GLSyncModuleInfo_Get, ADL_WORKSTATION_GLSYNCMODULEINFO_GET)
    GPA(ADL_Workstation_GLSyncGenlockConfiguration_Get, ADL_WORKSTATION_GLSYNCGENLOCKCONFIGURATION_GET)
    GPA(ADL_Workstation_GLSyncGenlockConfiguration_Set, ADL_WORKSTATION_GLSYNCGENLOCKCONFIGURATION_SET)
    GPA(ADL_Workstation_GLSyncPortState_Get, ADL_WORKSTATION_GLSYNCPORTSTATE_GET)
    GPA(ADL_Workstation_GLSyncPortState_Set, ADL_WORKSTATION_GLSYNCPORTSTATE_SET)
    GPA(ADL_Workstation_DisplayGLSyncMode_Get, ADL_WORKSTATION_DISPLAYGLSYNCMODE_GET)
    GPA(ADL_Workstation_DisplayGLSyncMode_Set, ADL_WORKSTATION_DISPLAYGLSYNCMODE_SET)
    GPA(ADL_Workstation_GLSyncSupportedTopology_Get, ADL_WORKSTATION_GLSYNCSUPPORTEDTOPOLOGY_GET)
    GPA(ADL_Workstation_LoadBalancing_Get, ADL_WORKSTATION_LOADBALANCING_GET)
    GPA(ADL_Workstation_LoadBalancing_Set, ADL_WORKSTATION_LOADBALANCING_SET)
    GPA(ADL_Workstation_LoadBalancing_Caps, ADL_WORKSTATION_LOADBALANCING_CAPS)

#ifdef LINUX
    GPA(ADL_Adapter_MemoryInfo_Get, ADL_ADAPTER_MEMORYINFO_GET)
    GPA(ADL_DesktopConfig_Get, ADL_DESKTOPCONFIG_GET)
    GPA(ADL_DesktopConfig_Set, ADL_DESKTOPCONFIG_SET)
    GPA(ADL_NumberOfDisplayEnable_Get, ADL_NUMBEROFDISPLAYENABLE_GET)
    GPA(ADL_DisplayEnable_Set, ADL_DISPLAYENABLE_SET)
    GPA(ADL_Display_IdentifyDisplay, ADL_DISPLAY_IDENTIFYDISPLAY)
    GPA(ADL_Display_LUTColor_Set, ADL_DISPLAY_LUTCOLOR_SET)
    GPA(ADL_Display_LUTColor_Get, ADL_DISPLAY_LUTCOLOR_GET)
    GPA(ADL_Adapter_XScreenInfo_Get, ADL_ADAPTER_XSCREENINFO_GET)
    GPA(ADL_Display_XrandrDisplayName_Get, ADL_DISPLAY_XRANDRDISPLAYNAME_GET)
#endif

#ifndef FAKE_ATI_CARD
    // Initialize ADL. The second parameter is 1, which means:
    // retrieve adapter information only for adapters that are physically present and enabled in the system
    if (ADL_OK != ADL_Main_Control_Create (sADL_Main_Memory_Alloc, 1))
    {
        return false;
    }

    if (ADL_Adapter_NumberOfAdapters_Get(&mNrOfAdapters) == ADL_OK)
    {
	if (mNrOfAdapters > 0)
	{
	    mpAdapterInfo = (LPAdapterInfo) malloc (sizeof(AdapterInfo) * mNrOfAdapters);
	    if (mpAdapterInfo != NULL)
	    {
		memset (mpAdapterInfo, '\0', sizeof(AdapterInfo) * mNrOfAdapters);
	        if (ADL_Adapter_AdapterInfo_Get (mpAdapterInfo, sizeof (AdapterInfo) * mNrOfAdapters) != ADL_OK)
		{
		    cout << "ERROR: no adapter info available!" << endl;
		}
		if (UpdateData() == 0)
		{
		    cout << "ERROR: failed to read card values!" << endl;
		}
	    }
	    else
	    {
		return false;
	    }
	}
	else
	{
	    return false;
	}
	return true;
    }
    else
    {
	return false;
    }
#else
    return true;
#endif
}

bool ADL::IsATICardAndCatalystPresent() const
{
    return (mNrOfAdapters > 0);
}

int ADL::UpdateData()
{
    int result = 0;

    if (mNrOfAdapters > 0)
    {
    #ifdef FAKE_ATI_CARD
	mFanSpeedInfo.iMinRPM = 500;
	mFanSpeedInfo.iMaxRPM = 4000;
	mFanSpeedInfo.iMaxPercent = 85;
	mFanSpeedInfo.iMinPercent = 12;

	mODActivity.iMaximumBusLanes = 16;
	mODActivity.iCurrentBusLanes = 16;
	mODActivity.iCurrentBusSpeed = 5000;

	static int cnt = 0;

	++cnt;

	if (cnt < 20)
	{
	    mODActivity.iEngineClock = 75000;
	    mODActivity.iMemoryClock = 95000;
	    mODActivity.iCurrentPerformanceLevel = 2;
	    mCurrentFanSpeed.iFanSpeed = 1734 + (rand() % 2) * 3 - (rand() % 3) * 5;
	    mTemperature.iTemperature = 46500 + (rand() % 2) * 500;
	}
	else if (cnt < 40)
	{
	    mODActivity.iEngineClock = 65000;
	    mODActivity.iMemoryClock = 75000;
	    mODActivity.iCurrentPerformanceLevel = 1;
	    mCurrentFanSpeed.iFanSpeed = 1534 + (rand() % 2) * 3 - (rand() % 3) * 5;
	    mTemperature.iTemperature = 43500 + (rand() % 2) * 500;
	}
	else if (cnt < 60)
	{
	    mODActivity.iEngineClock = 25000;
	    mODActivity.iMemoryClock = 35000;
	    mODActivity.iCurrentPerformanceLevel = 0;
	    mCurrentFanSpeed.iFanSpeed = 1234 + (rand() % 2) * 3 - (rand() % 3) * 5;
	    mTemperature.iTemperature = 40500 + (rand() % 2) * 500;
	}
	else
	{
	    cnt = 0;
	}

	mODActivity.iVddc = 1023;
	mODActivity.iActivityPercent = 50 + (rand() % 2) * 25 - (rand() % 3) * 25;

	mODClockInfo.sEngineClock.iDefaultClock = 75000;
	mODClockInfo.sMemoryClock.iDefaultClock = 90000;

	int perf_level_size = sizeof(ADLODPerformanceLevels) + sizeof(ADLODPerformanceLevel) * (3 - 1);
	mpODPerformanceLevels = (ADLODPerformanceLevels*)malloc(perf_level_size);
	mpODPerformanceLevels->iSize = perf_level_size;
	mpODPerformanceLevels->aLevels[0].iEngineClock = 20000;
	mpODPerformanceLevels->aLevels[0].iMemoryClock = 30000;
	mpODPerformanceLevels->aLevels[0].iVddc = 1023;
	mpODPerformanceLevels->aLevels[1].iEngineClock = 30000;
	mpODPerformanceLevels->aLevels[1].iMemoryClock = 40000;
	mpODPerformanceLevels->aLevels[1].iVddc = 1263;
	mpODPerformanceLevels->aLevels[2].iEngineClock = 40000;
	mpODPerformanceLevels->aLevels[2].iMemoryClock = 50000;
	mpODPerformanceLevels->aLevels[2].iVddc = 1263;

	mNrOfAdapters = 1;
	mpAdapterInfo = (LPAdapterInfo) malloc (sizeof(AdapterInfo) * mNrOfAdapters);
	if (mpAdapterInfo != NULL)
	{
	    memset (mpAdapterInfo, 0, sizeof(AdapterInfo) * mNrOfAdapters);
	    strncpy(mpAdapterInfo->strAdapterName, "Fake AMD/ATI Card", ADL_MAX_PATH-1);
	}

	mODParameters.sEngineClock.iMax = 85000;
	mODParameters.sEngineClock.iMin = 11000;
	mODParameters.sEngineClock.iStep =  500;

	mODParameters.sMemoryClock.iMax = 110000;
	mODParameters.sMemoryClock.iMin =  10000;
	mODParameters.sMemoryClock.iStep =  1000;

	mODParameters.sVddc.iMax = 1263;
	mODParameters.sVddc.iMin = 1023;
	mODParameters.sVddc.iStep =  80;

	mODParameters.iNumberOfPerformanceLevels = 3;

	result = 0;
//	result = ERR_GET_CURRENT_FANSPEED_FAILED;
//	mCurrentFanSpeed.iFanSpeed = 0;
//	mFanSpeedInfo.iMinRPM = 0;
//	mFanSpeedInfo.iMaxRPM = 0;
//	mFanSpeedInfo.iMaxPercent = 0;
//	mFanSpeedInfo.iMinPercent = 0;

//	result = ERR_GET_TEMPERATURE_FAILED;
//	mTemperature.iTemperature = 0;

//	result = ERR_GET_OD_PERF_LEVELS_FAILED | ERR_GET_ACTIVITY_FAILED;
//	mODParameters.sEngineClock.iMax = 0;
//	mODParameters.sEngineClock.iMin = 0;
//	mODParameters.sEngineClock.iStep = 0;
//
//	mODParameters.sMemoryClock.iMax = 0;
//	mODParameters.sMemoryClock.iMin = 0;
//	mODParameters.sMemoryClock.iStep = 0;
//
//	mODParameters.sVddc.iMax = 0;
//	mODParameters.sVddc.iMin = 0;
//	mODParameters.sVddc.iStep = 0;

    #else

	mTemperature.iSize = sizeof(ADLTemperature);
	if (SAVE_CALL(ADL_Overdrive5_Temperature_Get)(0, 0, &mTemperature) != ADL_OK)
	{
	    mTemperature.iTemperature = 0;
	    result |= ERR_GET_TEMPERATURE_FAILED;
	}

	mFanSpeedInfo.iSize = sizeof(ADLFanSpeedInfo);
	if (SAVE_CALL(ADL_Overdrive5_FanSpeedInfo_Get)(0, 0, &mFanSpeedInfo) != ADL_OK)
	{
	    mFanSpeedInfo.iMinRPM = 0;
	    mFanSpeedInfo.iMaxRPM = 0;
	    mFanSpeedInfo.iMinPercent = 0;
	    mFanSpeedInfo.iMaxPercent = 0;
	    result |= ERR_GET_FANSPEED_INFO_FAILED;
	}

	mCurrentFanSpeed.iSize = sizeof(ADLFanSpeedValue);
	mCurrentFanSpeed.iFlags = ADL_DL_FANCTRL_SPEED_TYPE_RPM;
	if (SAVE_CALL(ADL_Overdrive5_FanSpeed_Get)(0, 0, &mCurrentFanSpeed) != ADL_OK)
	{
	    mCurrentFanSpeed.iFanSpeed = 0;
	    result |= ERR_GET_CURRENT_FANSPEED_FAILED;
	}

	mODParameters.iSize = sizeof(ADLODParameters);
	if (SAVE_CALL(ADL_Overdrive5_ODParameters_Get)(0, &mODParameters) == ADL_OK)
	{
	    if (mpODPerformanceLevels == NULL)
	    {
		int perf_level_size = sizeof(ADLODPerformanceLevels) + sizeof(ADLODPerformanceLevel) * (mODParameters.iNumberOfPerformanceLevels - 1);
		mpODPerformanceLevels = (ADLODPerformanceLevels*)malloc(perf_level_size);
		mpODPerformanceLevels->iSize = perf_level_size;
	    }

	    if (SAVE_CALL(ADL_Overdrive5_ODPerformanceLevels_Get)(0, 0, mpODPerformanceLevels) != ADL_OK)
	    {
		free(mpODPerformanceLevels);
		mpODPerformanceLevels = NULL;
		result |= ERR_GET_OD_PERF_LEVELS_FAILED;
	    }
	}
	else
	{
	    result |= ERR_GET_OD_PARAMETERS_FAILED;
	}

	mODActivity.iSize = sizeof(ADLPMActivity);
	if (SAVE_CALL(ADL_Overdrive5_CurrentActivity_Get)(0, &mODActivity) != ADL_OK)
	{
	    mODActivity.iEngineClock = 0;
	    mODActivity.iMemoryClock = 0;
	    mODActivity.iVddc = 0;
	    mODActivity.iCurrentPerformanceLevel = 0;
	    mODActivity.iActivityPercent = 0;
	    result |= ERR_GET_ACTIVITY_FAILED;
	}

	mODClockInfo.iSize = sizeof(ADLAdapterODClockInfo);
	if (SAVE_CALL(ADL_Display_ODClockInfo_Get)(0, &mODClockInfo) != ADL_OK)
	{
	    mODClockInfo.sEngineClock.iCurrentClock = 0;
	    mODClockInfo.sEngineClock.iDefaultClock = 0;
	    mODClockInfo.sMemoryClock.iCurrentClock = 0;
	    mODClockInfo.sMemoryClock.iDefaultClock = 0;
	    result |= ERR_GET_DEFAULTCLOCKINFO_FAILED;
	}
    #endif
    }

    mFeatures = ~result;

    return mFeatures;
}
