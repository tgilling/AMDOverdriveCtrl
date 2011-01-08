///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov 18 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gui__
#define __gui__

#include <wx/intl.h>

#include <wx/gdicmn.h>
#include <wx/notebook.h>
#include <wx/string.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statline.h>
#include <wx/gauge.h>
#include <wx/panel.h>
#include <wx/slider.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/hyperlink.h>
#include <wx/checkbox.h>
#include <wx/choice.h>
#include <wx/listctrl.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class MainDialogBase
///////////////////////////////////////////////////////////////////////////////
class MainDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* mNotebook;
		
		wxButton* mLoadButton;
		wxButton* mSaveButton;
		
		wxButton* mExit;
		wxButton* mOKButton;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnCloseDialog( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnInit( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnNotebookPageChanged( wxNotebookEvent& event ) { event.Skip(); }
		virtual void mLoadButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mSaveButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mExitButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnOKClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		MainDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("AMDOverdriveCtrl"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 395,485 ), long style = wxCLOSE_BOX|wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX ); 
		~MainDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CInfoPanelBase
///////////////////////////////////////////////////////////////////////////////
class CInfoPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxStaticText* m_staticText1;
		wxTextCtrl* mInfoCardID;
		wxStaticLine* m_staticline3;
		wxStaticText* m_staticText2;
		wxTextCtrl* mInfoTemperature;
		wxGauge* mInfoActivity;
		wxStaticLine* m_staticline4;
		wxStaticText* m_staticText3;
		wxStaticText* mDefaultGPUMHz;
		wxStaticText* mDefaultMemMHz;
		wxStaticText* mDefaultVolt;
		wxStaticText* mPCILanes;
		wxTextCtrl* mInfoCurrentGPU;
		wxTextCtrl* mInfoCurrentMemory;
		wxTextCtrl* mInfoCurrentVoltage;
		wxStaticLine* m_staticline5;
		wxStaticText* m_staticText6;
		wxStaticText* m_staticText7;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		
		wxTextCtrl* mInfoMinFanSpeed;
		wxTextCtrl* mInfoMaxFanSpeed;
		wxTextCtrl* mInfoCurrentFanSpeed;
		wxStaticLine* m_staticline6;
		wxStaticText* m_staticText10;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText12;
		wxStaticText* m_staticText13;
		wxStaticText* mInfoLevelLow;
		wxTextCtrl* mInfoOVGPULow;
		wxTextCtrl* mInfoOVMemLow;
		wxTextCtrl* mInfoOVVoltLow;
		wxStaticText* mInfoLevelMid;
		wxTextCtrl* mInfoOVGPUMid;
		wxTextCtrl* mInfoOVMemMid;
		wxTextCtrl* mInfoOVVoltMid;
		wxStaticText* mInfoLevelHigh;
		wxTextCtrl* mInfoOVGPUHigh;
		wxTextCtrl* mInfoOVMemHigh;
		wxTextCtrl* mInfoOVVoltHigh;
	
	public:
		
		CInfoPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxPoint( -1,15 ), const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CInfoPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CSettingsPanelBase
///////////////////////////////////////////////////////////////////////////////
class CSettingsPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxStaticText* m_staticText17;
		
		
		wxTextCtrl* mCurrentGPUFreq;
		
		
		wxTextCtrl* mMinGPUFreq;
		wxButton* mGPUFreqMinus;
		wxSlider* mGPUFreqSlider;
		wxButton* mGPUFreqPlus;
		wxTextCtrl* mMaxGPUFreq;
		wxStaticLine* m_staticline5;
		wxStaticText* m_staticText171;
		
		
		wxTextCtrl* mCurrentMemFreq;
		
		
		wxTextCtrl* mMinMemFreq;
		wxButton* mMemFreqMinus;
		wxSlider* mMemFreqSlider;
		wxButton* mMemFreqPlus;
		wxTextCtrl* mMaxMemFreq;
		wxStaticLine* m_staticline6;
		wxStaticText* m_staticText172;
		
		
		wxTextCtrl* mCurrentVoltage;
		
		
		wxTextCtrl* mMinVoltage;
		wxButton* mVoltageMinus;
		wxSlider* mVoltageSlider;
		wxButton* mVoltagePlus;
		wxTextCtrl* mMaxVoltage;
		
		// Virtual event handlers, overide them in your derived class
		virtual void mGPUFreqMinusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mGPUFreqSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void mGPUFreqPlusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mMemFreqMinusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mMemFreqSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void mMemFreqPlusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mVoltageMinusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mVoltageSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void mVoltagePlusClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CSettingsPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 370,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CSettingsPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CFanSpeedPanelBase
///////////////////////////////////////////////////////////////////////////////
class CFanSpeedPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxStaticText* m_staticText17;
		
		
		
		
		
		
		wxTextCtrl* mTargetFanSpeed;
		
		
		wxTextCtrl* mMinFanSpeed;
		wxButton* mFanSpeedMinus;
		wxSlider* mFanSpeedSlider;
		wxButton* mFanSpeedPlus;
		wxTextCtrl* mMaxFanSpeed;
		wxStaticText* mMinRPM;
		
		wxStaticText* mCurrentFanSpeed;
		
		wxStaticText* mMaxRPM;
		wxStaticLine* m_staticline8;
		wxStaticText* m_staticText26;
		wxPanel* mFanProfile;
		wxStaticLine* m_staticline9;
		
		
		wxButton* mButtonProfile;
		wxButton* mButtonDefault;
		wxButton* mButtonSet;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void mFanSpeedMinusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mFanSpeedSliderOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void mFanSpeedPlusClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void EnterPanel( wxMouseEvent& event ) { event.Skip(); }
		virtual void LeavePanel( wxMouseEvent& event ) { event.Skip(); }
		virtual void LeftDblClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void MouseMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void mButtonProfileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonDefaultClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonSetClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CFanSpeedPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CFanSpeedPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CAuthorPanelBase
///////////////////////////////////////////////////////////////////////////////
class CAuthorPanelBase : public wxPanel 
{
	private:
	
	protected:
		wxStaticBitmap* mBitmap;
		
		wxStaticText* mText1;
		wxHyperlinkCtrl* m_hyperlink1;
		wxStaticText* mText2;
		wxStaticText* mText3;
	
	public:
		
		CAuthorPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CAuthorPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CMonitorPanelBase
///////////////////////////////////////////////////////////////////////////////
class CMonitorPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxStaticText* m_staticText30;
		
		wxSlider* mTimerSlider;
		wxStaticText* mTimerInterval;
		wxSlider* mTempSlider;
		wxPanel* mTemperature;
		wxStaticText* m_staticText32;
		wxSlider* mFanSpeedSlider;
		wxPanel* mFanSpeed;
		wxStaticText* m_staticText321;
		
		wxPanel* mPerfLevel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void mTimerSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void mTemperatureSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void EnterPanel( wxMouseEvent& event ) { event.Skip(); }
		virtual void LeavePanel( wxMouseEvent& event ) { event.Skip(); }
		virtual void MouseMotion( wxMouseEvent& event ) { event.Skip(); }
		virtual void mFanSpeedSliderScroll( wxScrollEvent& event ) { event.Skip(); }
		
	
	public:
		
		CMonitorPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CMonitorPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CFanControlPanelBase
///////////////////////////////////////////////////////////////////////////////
class CFanControlPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxCheckBox* mEnable;
		wxStaticText* mCurrentTemperature;
		wxStaticText* mCurrentFanSpeed;
		wxChoice* mCurveType;
		wxButton* mButtonClear;
		wxStaticLine* m_staticline10;
		wxPanel* mCurve;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void mEnableOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void mCurveTypeOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonClearClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mCurveOnEnterWindow( wxMouseEvent& event ) { event.Skip(); }
		virtual void mCurveOnLeaveWindow( wxMouseEvent& event ) { event.Skip(); }
		virtual void mCurveOnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void mCurveOnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void mCurveOnMotion( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		CFanControlPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CFanControlPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CAppProfilePanelBase
///////////////////////////////////////////////////////////////////////////////
class CAppProfilePanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxCheckBox* mEnable;
		
		wxStaticText* m_staticText41;
		wxTextCtrl* mActiveProfileName;
		wxStaticLine* m_staticline16;
		wxStaticText* m_staticText36;
		
		wxTextCtrl* mDefaultProfileName;
		wxButton* mButtonChooseDefault;
		
		wxListCtrl* mProfileList;
		
		wxButton* mButtonDeleteProfile;
		wxButton* mButtonEditProfile;
		wxButton* mButtonAddProfile;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void mEnableOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonChooseDefaultClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLeftDClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void mButtonDeleteProfileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonEditProfileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonAddProfileClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CAppProfilePanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CAppProfilePanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CProfileAddDialogBase
///////////////////////////////////////////////////////////////////////////////
class CProfileAddDialogBase : public wxDialog 
{
	private:
	
	protected:
		
		wxStaticText* m_staticText38;
		
		wxTextCtrl* mAppName;
		wxStaticText* m_staticText39;
		
		wxTextCtrl* mProfileName;
		wxButton* mButtonChooseProfile;
		
		wxStdDialogButtonSizer* mDialogButtons;
		wxButton* mDialogButtonsOK;
		wxButton* mDialogButtonsCancel;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void mButtonChooseProfileClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void CancelButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OKButtonClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CProfileAddDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~CProfileAddDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class COvdrSettingsPanelBase
///////////////////////////////////////////////////////////////////////////////
class COvdrSettingsPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxNotebook* mOvdrNotebook;
		
		wxButton* mButtonReset;
		wxButton* mButtonSet;
		
		
		// Virtual event handlers, overide them in your derived class
		virtual void mButtonResetClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mButtonSetClick( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		COvdrSettingsPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~COvdrSettingsPanelBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class CColorTempPanelBase
///////////////////////////////////////////////////////////////////////////////
class CColorTempPanelBase : public wxPanel 
{
	private:
	
	protected:
		
		wxCheckBox* mEnable;
		
		wxStaticText* m_staticText40;
		wxTextCtrl* mLongitude;
		wxStaticText* m_staticText41;
		wxTextCtrl* mLatitude;
		
		wxStaticText* m_staticText42;
		wxTextCtrl* mColorTempDay;
		wxSlider* mColorTempDaySlider;
		wxButton* mButtonTestDayColor;
		wxButton* mButtonSetDayColor;
		wxStaticText* m_staticText421;
		wxTextCtrl* mColorTempNight;
		wxSlider* mColorTempNightSlider;
		wxButton* mButtonTestNightColor;
		wxButton* mButtonSetNightColor;
		wxStaticText* m_staticText422;
		wxTextCtrl* mTransition;
		wxSlider* mTransitionSlider;
		wxStaticLine* m_staticline11;
		wxPanel* mCurve;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		virtual void mEnableOnCheckBox( wxCommandEvent& event ) { event.Skip(); }
		virtual void mLongitudeOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void mLatitudeOnText( wxCommandEvent& event ) { event.Skip(); }
		virtual void mColorTempDaySliderOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void ButtonTestDayColorClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ButtonSetDayColorClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mColorTempNightSliderOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void ButtonTestNightColorClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void ButtonSetNightColorClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void mTransitionSliderOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void mCurveOnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void mCurveOnLeftUp( wxMouseEvent& event ) { event.Skip(); }
		virtual void mCurveOnMotion( wxMouseEvent& event ) { event.Skip(); }
		
	
	public:
		
		CColorTempPanelBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 385,-1 ), long style = wxTAB_TRAVERSAL ); 
		~CColorTempPanelBase();
	
};

#endif //__gui__
