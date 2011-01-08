///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Nov 18 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gui.h"

///////////////////////////////////////////////////////////////////////////

MainDialogBase::MainDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );
	
	wxBoxSizer* mainSizer;
	mainSizer = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer19->AddGrowableCol( 1 );
	fgSizer19->AddGrowableRow( 1 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mNotebook = new wxNotebook( this, wxID_ANY, wxPoint( -1,10 ), wxSize( 385,430 ), 0 );
	
	fgSizer19->Add( mNotebook, 1, wxALL|wxEXPAND, 5 );
	
	
	fgSizer19->Add( 0, 0, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	mLoadButton = new wxButton( this, wxID_ANY, _("Load"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer21->Add( mLoadButton, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	mSaveButton = new wxButton( this, wxID_ANY, _("Save"), wxPoint( -1,-1 ), wxSize( 80,-1 ), 0 );
	bSizer21->Add( mSaveButton, 0, wxTOP, 5 );
	
	
	bSizer21->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mExit = new wxButton( this, wxID_ANY, _("Exit"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer21->Add( mExit, 0, wxBOTTOM|wxTOP, 5 );
	
	mOKButton = new wxButton( this, wxID_ANY, _("TaskBar"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	mOKButton->SetDefault(); 
	bSizer21->Add( mOKButton, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	fgSizer19->Add( bSizer21, 1, wxEXPAND, 5 );
	
	mainSizer->Add( fgSizer19, 1, wxEXPAND, 5 );
	
	this->SetSizer( mainSizer );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialogBase::OnCloseDialog ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( MainDialogBase::OnInit ) );
	mNotebook->Connect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( MainDialogBase::OnNotebookPageChanged ), NULL, this );
	mLoadButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::mLoadButtonClick ), NULL, this );
	mSaveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::mSaveButtonClick ), NULL, this );
	mExit->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::mExitButtonClick ), NULL, this );
	mOKButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnOKClick ), NULL, this );
}

MainDialogBase::~MainDialogBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( MainDialogBase::OnCloseDialog ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( MainDialogBase::OnInit ) );
	mNotebook->Disconnect( wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxNotebookEventHandler( MainDialogBase::OnNotebookPageChanged ), NULL, this );
	mLoadButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::mLoadButtonClick ), NULL, this );
	mSaveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::mSaveButtonClick ), NULL, this );
	mExit->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::mExitButtonClick ), NULL, this );
	mOKButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( MainDialogBase::OnOKClick ), NULL, this );
	
}

CInfoPanelBase::CInfoPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer6;
	fgSizer6 = new wxFlexGridSizer( 10, 1, 0, 0 );
	fgSizer6->SetFlexibleDirection( wxBOTH );
	fgSizer6->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer6->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 1, 2, 0, 0 );
	fgSizer1->AddGrowableCol( 1 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Card Model"), wxDefaultPosition, wxSize( 95,-1 ), 0 );
	m_staticText1->Wrap( -1 );
	m_staticText1->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer1->Add( m_staticText1, 0, wxALIGN_CENTER|wxALL, 5 );
	
	mInfoCardID = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer1->Add( mInfoCardID, 0, wxALL|wxEXPAND, 5 );
	
	fgSizer6->Add( fgSizer1, 1, wxEXPAND, 5 );
	
	m_staticline3 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer6->Add( m_staticline3, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer2->SetFlexibleDirection( wxBOTH );
	fgSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText2 = new wxStaticText( this, wxID_ANY, _("Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	m_staticText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText2->SetMinSize( wxSize( 95,-1 ) );
	
	fgSizer2->Add( m_staticText2, 0, wxALIGN_CENTER|wxALL, 5 );
	
	mInfoTemperature = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer2->Add( mInfoTemperature, 0, wxALL, 5 );
	
	mInfoActivity = new wxGauge( this, wxID_ANY, 100, wxDefaultPosition, wxSize( 167,12 ), wxGA_HORIZONTAL );
	fgSizer2->Add( mInfoActivity, 0, wxALIGN_CENTER|wxLEFT, 7 );
	
	fgSizer6->Add( fgSizer2, 1, wxEXPAND, 5 );
	
	m_staticline4 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer6->Add( m_staticline4, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Frequencies"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	m_staticText3->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText3->SetMinSize( wxSize( 95,-1 ) );
	
	fgSizer3->Add( m_staticText3, 0, wxALL, 5 );
	
	mDefaultGPUMHz = new wxStaticText( this, wxID_ANY, _("GPU"), wxDefaultPosition, wxDefaultSize, 0 );
	mDefaultGPUMHz->Wrap( -1 );
	mDefaultGPUMHz->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer3->Add( mDefaultGPUMHz, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mDefaultMemMHz = new wxStaticText( this, wxID_ANY, _("Mem"), wxDefaultPosition, wxDefaultSize, 0 );
	mDefaultMemMHz->Wrap( -1 );
	mDefaultMemMHz->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer3->Add( mDefaultMemMHz, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mDefaultVolt = new wxStaticText( this, wxID_ANY, _("Voltage"), wxDefaultPosition, wxDefaultSize, 0 );
	mDefaultVolt->Wrap( -1 );
	mDefaultVolt->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer3->Add( mDefaultVolt, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mPCILanes = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	mPCILanes->Wrap( -1 );
	fgSizer3->Add( mPCILanes, 0, wxALIGN_CENTER|wxALL, 5 );
	
	mInfoCurrentGPU = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer3->Add( mInfoCurrentGPU, 0, wxALL, 5 );
	
	mInfoCurrentMemory = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer3->Add( mInfoCurrentMemory, 0, wxALL, 5 );
	
	mInfoCurrentVoltage = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer3->Add( mInfoCurrentVoltage, 0, wxALL, 5 );
	
	fgSizer6->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer6->Add( m_staticline5, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 2, 4, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText6 = new wxStaticText( this, wxID_ANY, _("FanSpeed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	m_staticText6->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText6->SetMinSize( wxSize( 95,-1 ) );
	
	fgSizer4->Add( m_staticText6, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( this, wxID_ANY, _("Min"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	m_staticText7->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer4->Add( m_staticText7, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText8 = new wxStaticText( this, wxID_ANY, _("Max"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	m_staticText8->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer4->Add( m_staticText8, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText9 = new wxStaticText( this, wxID_ANY, _("Current"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	m_staticText9->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer4->Add( m_staticText9, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	
	fgSizer4->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mInfoMinFanSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer4->Add( mInfoMinFanSpeed, 0, wxALL, 5 );
	
	mInfoMaxFanSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer4->Add( mInfoMaxFanSpeed, 0, wxALL, 5 );
	
	mInfoCurrentFanSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer4->Add( mInfoCurrentFanSpeed, 0, wxALL, 5 );
	
	fgSizer6->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer6->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );
	
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 4, 4, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText10 = new wxStaticText( this, wxID_ANY, _("Overdrive"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	m_staticText10->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	m_staticText10->SetMinSize( wxSize( 95,-1 ) );
	
	fgSizer5->Add( m_staticText10, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( this, wxID_ANY, _("GPU"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	m_staticText11->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer5->Add( m_staticText11, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText12 = new wxStaticText( this, wxID_ANY, _("Memory"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText12->Wrap( -1 );
	m_staticText12->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer5->Add( m_staticText12, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	m_staticText13 = new wxStaticText( this, wxID_ANY, _("Voltage"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	m_staticText13->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	fgSizer5->Add( m_staticText13, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mInfoLevelLow = new wxStaticText( this, wxID_ANY, _("Low Level"), wxDefaultPosition, wxDefaultSize, 0 );
	mInfoLevelLow->Wrap( -1 );
	fgSizer5->Add( mInfoLevelLow, 0, wxALIGN_CENTER|wxALL, 5 );
	
	mInfoOVGPULow = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVGPULow, 0, wxALL, 5 );
	
	mInfoOVMemLow = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVMemLow, 0, wxALL, 5 );
	
	mInfoOVVoltLow = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVVoltLow, 0, wxALL, 5 );
	
	mInfoLevelMid = new wxStaticText( this, wxID_ANY, _("Mid Level"), wxDefaultPosition, wxDefaultSize, 0 );
	mInfoLevelMid->Wrap( -1 );
	fgSizer5->Add( mInfoLevelMid, 0, wxALIGN_CENTER|wxALL, 5 );
	
	mInfoOVGPUMid = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVGPUMid, 0, wxALL, 5 );
	
	mInfoOVMemMid = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVMemMid, 0, wxALL, 5 );
	
	mInfoOVVoltMid = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVVoltMid, 0, wxALL, 5 );
	
	mInfoLevelHigh = new wxStaticText( this, wxID_ANY, _("High Level"), wxDefaultPosition, wxDefaultSize, 0 );
	mInfoLevelHigh->Wrap( -1 );
	fgSizer5->Add( mInfoLevelHigh, 0, wxALIGN_CENTER|wxALL, 5 );
	
	mInfoOVGPUHigh = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVGPUHigh, 0, wxALL, 5 );
	
	mInfoOVMemHigh = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVMemHigh, 0, wxALL, 5 );
	
	mInfoOVVoltHigh = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_CENTRE|wxTE_READONLY );
	fgSizer5->Add( mInfoOVVoltHigh, 0, wxALL, 5 );
	
	fgSizer6->Add( fgSizer5, 1, wxEXPAND, 5 );
	
	bSizer2->Add( fgSizer6, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer2 );
	this->Layout();
}

CInfoPanelBase::~CInfoPanelBase()
{
}

CSettingsPanelBase::CSettingsPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer7;
	fgSizer7 = new wxFlexGridSizer( 1, 1, 0, 0 );
	fgSizer7->SetFlexibleDirection( wxBOTH );
	fgSizer7->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer7->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText17 = new wxStaticText( this, wxID_ANY, _("GPU (MHz)"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer14->Add( m_staticText17, 0, wxLEFT|wxTOP, 5 );
	
	fgSizer7->Add( bSizer14, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 2, 5, 0, 0 );
	fgSizer8->AddGrowableCol( 3 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCurrentGPUFreq = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer8->Add( mCurrentGPUFreq, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mMinGPUFreq = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer8->Add( mMinGPUFreq, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mGPUFreqMinus = new wxButton( this, wxID_ANY, _("-"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mGPUFreqMinus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer8->Add( mGPUFreqMinus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mGPUFreqSlider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 172,-1 ), wxSL_HORIZONTAL );
	fgSizer8->Add( mGPUFreqSlider, 0, wxALL|wxEXPAND, 5 );
	
	mGPUFreqPlus = new wxButton( this, wxID_ANY, _("+"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mGPUFreqPlus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer8->Add( mGPUFreqPlus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMaxGPUFreq = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer8->Add( mMaxGPUFreq, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer7->Add( fgSizer8, 1, wxEXPAND, 5 );
	
	m_staticline5 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer7->Add( m_staticline5, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer15;
	bSizer15 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText171 = new wxStaticText( this, wxID_ANY, _("Memory (MHz)"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText171->Wrap( -1 );
	m_staticText171->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer15->Add( m_staticText171, 0, wxLEFT|wxTOP, 5 );
	
	fgSizer7->Add( bSizer15, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer81;
	fgSizer81 = new wxFlexGridSizer( 2, 5, 0, 0 );
	fgSizer81->AddGrowableCol( 3 );
	fgSizer81->SetFlexibleDirection( wxBOTH );
	fgSizer81->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizer81->SetMinSize( wxSize( 380,-1 ) ); 
	
	fgSizer81->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer81->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCurrentMemFreq = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer81->Add( mCurrentMemFreq, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer81->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer81->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mMinMemFreq = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer81->Add( mMinMemFreq, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMemFreqMinus = new wxButton( this, wxID_ANY, _("-"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mMemFreqMinus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer81->Add( mMemFreqMinus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMemFreqSlider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 172,-1 ), wxSL_HORIZONTAL );
	fgSizer81->Add( mMemFreqSlider, 0, wxALL|wxEXPAND, 5 );
	
	mMemFreqPlus = new wxButton( this, wxID_ANY, _("+"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mMemFreqPlus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer81->Add( mMemFreqPlus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMaxMemFreq = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer81->Add( mMaxMemFreq, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer7->Add( fgSizer81, 1, wxEXPAND, 5 );
	
	m_staticline6 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer7->Add( m_staticline6, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText172 = new wxStaticText( this, wxID_ANY, _("Voltage (V)"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText172->Wrap( -1 );
	m_staticText172->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer16->Add( m_staticText172, 0, wxLEFT|wxTOP, 5 );
	
	fgSizer7->Add( bSizer16, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer82;
	fgSizer82 = new wxFlexGridSizer( 2, 5, 0, 0 );
	fgSizer82->AddGrowableCol( 3 );
	fgSizer82->SetFlexibleDirection( wxBOTH );
	fgSizer82->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizer82->SetMinSize( wxSize( 380,-1 ) ); 
	
	fgSizer82->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer82->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCurrentVoltage = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer82->Add( mCurrentVoltage, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer82->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer82->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mMinVoltage = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer82->Add( mMinVoltage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mVoltageMinus = new wxButton( this, wxID_ANY, _("-"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mVoltageMinus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer82->Add( mVoltageMinus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mVoltageSlider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 172,-1 ), wxSL_HORIZONTAL );
	fgSizer82->Add( mVoltageSlider, 0, wxALL|wxEXPAND, 5 );
	
	mVoltagePlus = new wxButton( this, wxID_ANY, _("+"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mVoltagePlus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer82->Add( mVoltagePlus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMaxVoltage = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer82->Add( mMaxVoltage, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer7->Add( fgSizer82, 1, wxEXPAND, 5 );
	
	bSizer3->Add( fgSizer7, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer3 );
	this->Layout();
	
	// Connect Events
	mGPUFreqMinus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mGPUFreqMinusClick ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqPlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mGPUFreqPlusClick ), NULL, this );
	mMemFreqMinus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mMemFreqMinusClick ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqPlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mMemFreqPlusClick ), NULL, this );
	mVoltageMinus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mVoltageMinusClick ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltagePlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mVoltagePlusClick ), NULL, this );
}

CSettingsPanelBase::~CSettingsPanelBase()
{
	// Disconnect Events
	mGPUFreqMinus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mGPUFreqMinusClick ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CSettingsPanelBase::mGPUFreqSliderScroll ), NULL, this );
	mGPUFreqPlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mGPUFreqPlusClick ), NULL, this );
	mMemFreqMinus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mMemFreqMinusClick ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CSettingsPanelBase::mMemFreqSliderScroll ), NULL, this );
	mMemFreqPlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mMemFreqPlusClick ), NULL, this );
	mVoltageMinus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mVoltageMinusClick ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltageSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CSettingsPanelBase::mVoltageSliderScroll ), NULL, this );
	mVoltagePlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CSettingsPanelBase::mVoltagePlusClick ), NULL, this );
	
}

CFanSpeedPanelBase::CFanSpeedPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 5, 1, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer12->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 4, 5, 0, 0 );
	fgSizer8->AddGrowableCol( 3 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	fgSizer8->SetMinSize( wxSize( 380,-1 ) ); 
	m_staticText17 = new wxStaticText( this, wxID_ANY, _("FAN"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	m_staticText17->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer8->Add( m_staticText17, 0, wxLEFT|wxTOP, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mTargetFanSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer8->Add( mTargetFanSpeed, 0, wxALIGN_CENTER_HORIZONTAL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mMinFanSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer8->Add( mMinFanSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mFanSpeedMinus = new wxButton( this, wxID_ANY, _("-"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mFanSpeedMinus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer8->Add( mFanSpeedMinus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mFanSpeedSlider = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxSize( 183,-1 ), wxSL_HORIZONTAL );
	fgSizer8->Add( mFanSpeedSlider, 0, wxALL|wxEXPAND, 5 );
	
	mFanSpeedPlus = new wxButton( this, wxID_ANY, _("+"), wxDefaultPosition, wxSize( 23,23 ), 0 );
	mFanSpeedPlus->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer8->Add( mFanSpeedPlus, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMaxFanSpeed = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 50,-1 ), wxTE_CENTRE|wxTE_READONLY );
	fgSizer8->Add( mMaxFanSpeed, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mMinRPM = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	mMinRPM->Wrap( -1 );
	fgSizer8->Add( mMinRPM, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mCurrentFanSpeed = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	mCurrentFanSpeed->Wrap( -1 );
	fgSizer8->Add( mCurrentFanSpeed, 0, wxALIGN_CENTER|wxALL, 5 );
	
	
	fgSizer8->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mMaxRPM = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	mMaxRPM->Wrap( -1 );
	fgSizer8->Add( mMaxRPM, 0, wxALIGN_CENTER|wxALL, 5 );
	
	fgSizer12->Add( fgSizer8, 1, wxEXPAND, 5 );
	
	m_staticline8 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer12->Add( m_staticline8, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxVERTICAL );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, _("FAN Profile"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	m_staticText26->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer8->Add( m_staticText26, 0, wxLEFT, 5 );
	
	fgSizer12->Add( bSizer8, 1, wxEXPAND, 5 );
	
	mFanProfile = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 370,170 ), wxTAB_TRAVERSAL );
	fgSizer12->Add( mFanProfile, 1, wxEXPAND | wxALL, 5 );
	
	m_staticline9 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer12->Add( m_staticline9, 0, wxEXPAND | wxALL, 5 );
	
	
	fgSizer12->Add( 0, 10, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mButtonProfile = new wxButton( this, wxID_ANY, _("Profile"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer5->Add( mButtonProfile, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mButtonDefault = new wxButton( this, wxID_ANY, _("Default"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer5->Add( mButtonDefault, 0, wxALL, 5 );
	
	mButtonSet = new wxButton( this, wxID_ANY, _("Set Value"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer5->Add( mButtonSet, 0, wxALL, 5 );
	
	
	bSizer5->Add( 0, 0, 1, wxEXPAND, 5 );
	
	fgSizer12->Add( bSizer5, 1, wxEXPAND, 5 );
	
	bSizer4->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer4 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( CFanSpeedPanelBase::OnPaint ) );
	mFanSpeedMinus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mFanSpeedMinusClick ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedPlus->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mFanSpeedPlusClick ), NULL, this );
	mFanProfile->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CFanSpeedPanelBase::EnterPanel ), NULL, this );
	mFanProfile->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CFanSpeedPanelBase::LeavePanel ), NULL, this );
	mFanProfile->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CFanSpeedPanelBase::LeftDblClick ), NULL, this );
	mFanProfile->Connect( wxEVT_MOTION, wxMouseEventHandler( CFanSpeedPanelBase::MouseMotion ), NULL, this );
	mButtonProfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mButtonProfileClick ), NULL, this );
	mButtonDefault->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mButtonDefaultClick ), NULL, this );
	mButtonSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mButtonSetClick ), NULL, this );
}

CFanSpeedPanelBase::~CFanSpeedPanelBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( CFanSpeedPanelBase::OnPaint ) );
	mFanSpeedMinus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mFanSpeedMinusClick ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CFanSpeedPanelBase::mFanSpeedSliderOnScroll ), NULL, this );
	mFanSpeedPlus->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mFanSpeedPlusClick ), NULL, this );
	mFanProfile->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CFanSpeedPanelBase::EnterPanel ), NULL, this );
	mFanProfile->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CFanSpeedPanelBase::LeavePanel ), NULL, this );
	mFanProfile->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CFanSpeedPanelBase::LeftDblClick ), NULL, this );
	mFanProfile->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CFanSpeedPanelBase::MouseMotion ), NULL, this );
	mButtonProfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mButtonProfileClick ), NULL, this );
	mButtonDefault->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mButtonDefaultClick ), NULL, this );
	mButtonSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanSpeedPanelBase::mButtonSetClick ), NULL, this );
	
}

CAuthorPanelBase::CAuthorPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );
	
	bSizer7->SetMinSize( wxSize( 385,-1 ) ); 
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 1, 3, 0, 0 );
	fgSizer17->AddGrowableCol( 3 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mBitmap = new wxStaticBitmap( this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize( 128,120 ), 0 );
	fgSizer17->Add( mBitmap, 0, wxLEFT, 5 );
	
	
	fgSizer17->Add( 20, 0, 1, wxEXPAND, 5 );
	
	mText1 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mText1->Wrap( -1 );
	mText1->SetFont( wxFont( 12, 70, 94, 92, false, wxEmptyString ) );
	
	fgSizer17->Add( mText1, 0, wxALIGN_CENTER_HORIZONTAL|wxEXPAND|wxLEFT|wxRIGHT, 5 );
	
	fgSizer18->Add( fgSizer17, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer20;
	bSizer20 = new wxBoxSizer( wxVERTICAL );
	
	bSizer20->SetMinSize( wxSize( 385,-1 ) ); 
	m_hyperlink1 = new wxHyperlinkCtrl( this, wxID_ANY, _("AMDOverdriveCtrl on SourceForge"), wxT("http://www.sourceforge.net/projects/amdovdrvctrl"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer20->Add( m_hyperlink1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mText2 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mText2->Wrap( -1 );
	mText2->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 93, 90, false, wxEmptyString ) );
	
	bSizer20->Add( mText2, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	mText3 = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTRE );
	mText3->Wrap( -1 );
	mText3->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 94, 92, false, wxEmptyString ) );
	
	bSizer20->Add( mText3, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 5 );
	
	fgSizer18->Add( bSizer20, 1, wxEXPAND, 5 );
	
	bSizer7->Add( fgSizer18, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer7 );
	this->Layout();
}

CAuthorPanelBase::~CAuthorPanelBase()
{
}

CMonitorPanelBase::CMonitorPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer15;
	fgSizer15 = new wxFlexGridSizer( 10, 1, 0, 0 );
	fgSizer15->SetFlexibleDirection( wxBOTH );
	fgSizer15->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer15->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText30 = new wxStaticText( this, wxID_ANY, _("Temperature"), wxPoint( -1,-1 ), wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	m_staticText30->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	bSizer13->Add( m_staticText30, 0, wxLEFT|wxTOP, 5 );
	
	
	bSizer13->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mTimerSlider = new wxSlider( this, wxID_ANY, 10, 1, 101, wxDefaultPosition, wxSize( 100,-1 ), wxSL_HORIZONTAL );
	bSizer13->Add( mTimerSlider, 0, wxRIGHT|wxTOP, 5 );
	
	mTimerInterval = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 30,-1 ), wxALIGN_RIGHT );
	mTimerInterval->Wrap( -1 );
	bSizer13->Add( mTimerInterval, 0, wxLEFT|wxRIGHT|wxTOP, 5 );
	
	fgSizer14->Add( bSizer13, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );
	
	mTempSlider = new wxSlider( this, wxID_ANY, 100, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer10->Add( mTempSlider, 0, wxALL|wxEXPAND, 5 );
	
	mTemperature = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 340,95 ), wxTAB_TRAVERSAL );
	bSizer10->Add( mTemperature, 1, wxALL|wxEXPAND, 5 );
	
	fgSizer14->Add( bSizer10, 1, wxEXPAND, 5 );
	
	fgSizer15->Add( fgSizer14, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText32 = new wxStaticText( this, wxID_ANY, _("FanSpeed"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	m_staticText32->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer16->Add( m_staticText32, 0, wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxHORIZONTAL );
	
	mFanSpeedSlider = new wxSlider( this, wxID_ANY, 100, 1, 100, wxDefaultPosition, wxDefaultSize, wxSL_INVERSE|wxSL_VERTICAL );
	bSizer11->Add( mFanSpeedSlider, 0, wxALL|wxEXPAND, 5 );
	
	mFanSpeed = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 340,95 ), wxTAB_TRAVERSAL );
	bSizer11->Add( mFanSpeed, 1, wxEXPAND | wxALL, 5 );
	
	fgSizer16->Add( bSizer11, 1, wxEXPAND, 5 );
	
	fgSizer15->Add( fgSizer16, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer161;
	fgSizer161 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer161->SetFlexibleDirection( wxBOTH );
	fgSizer161->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText321 = new wxStaticText( this, wxID_ANY, _("Overdrive Level"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText321->Wrap( -1 );
	m_staticText321->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer161->Add( m_staticText321, 0, wxLEFT|wxTOP, 5 );
	
	wxFlexGridSizer* fgSizer25;
	fgSizer25 = new wxFlexGridSizer( 2, 2, 0, 0 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer25->Add( 29, 0, 1, wxEXPAND, 5 );
	
	mPerfLevel = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 340,95 ), wxTAB_TRAVERSAL );
	fgSizer25->Add( mPerfLevel, 1, wxALL|wxEXPAND, 5 );
	
	fgSizer161->Add( fgSizer25, 1, wxEXPAND, 5 );
	
	fgSizer15->Add( fgSizer161, 1, wxEXPAND, 5 );
	
	bSizer9->Add( fgSizer15, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer9 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( CMonitorPanelBase::OnPaint ) );
	mTimerSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTemperature->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CMonitorPanelBase::EnterPanel ), NULL, this );
	mTemperature->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CMonitorPanelBase::LeavePanel ), NULL, this );
	mTemperature->Connect( wxEVT_MOTION, wxMouseEventHandler( CMonitorPanelBase::MouseMotion ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeed->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CMonitorPanelBase::EnterPanel ), NULL, this );
	mFanSpeed->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CMonitorPanelBase::LeavePanel ), NULL, this );
	mFanSpeed->Connect( wxEVT_MOTION, wxMouseEventHandler( CMonitorPanelBase::MouseMotion ), NULL, this );
	mPerfLevel->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CMonitorPanelBase::EnterPanel ), NULL, this );
	mPerfLevel->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CMonitorPanelBase::LeavePanel ), NULL, this );
	mPerfLevel->Connect( wxEVT_MOTION, wxMouseEventHandler( CMonitorPanelBase::MouseMotion ), NULL, this );
}

CMonitorPanelBase::~CMonitorPanelBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( CMonitorPanelBase::OnPaint ) );
	mTimerSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTimerSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CMonitorPanelBase::mTimerSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTempSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CMonitorPanelBase::mTemperatureSliderScroll ), NULL, this );
	mTemperature->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CMonitorPanelBase::EnterPanel ), NULL, this );
	mTemperature->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CMonitorPanelBase::LeavePanel ), NULL, this );
	mTemperature->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CMonitorPanelBase::MouseMotion ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeedSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CMonitorPanelBase::mFanSpeedSliderScroll ), NULL, this );
	mFanSpeed->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CMonitorPanelBase::EnterPanel ), NULL, this );
	mFanSpeed->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CMonitorPanelBase::LeavePanel ), NULL, this );
	mFanSpeed->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CMonitorPanelBase::MouseMotion ), NULL, this );
	mPerfLevel->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CMonitorPanelBase::EnterPanel ), NULL, this );
	mPerfLevel->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CMonitorPanelBase::LeavePanel ), NULL, this );
	mPerfLevel->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CMonitorPanelBase::MouseMotion ), NULL, this );
	
}

CFanControlPanelBase::CFanControlPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 4, 1, 0, 0 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer20->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer21;
	bSizer21 = new wxBoxSizer( wxHORIZONTAL );
	
	mEnable = new wxCheckBox( this, wxID_ANY, _("Enable"), wxDefaultPosition, wxSize( 90,-1 ), 0 );
	bSizer21->Add( mEnable, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	wxBoxSizer* bSizer211;
	bSizer211 = new wxBoxSizer( wxVERTICAL );
	
	mCurrentTemperature = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	mCurrentTemperature->Wrap( -1 );
	bSizer211->Add( mCurrentTemperature, 0, wxALL, 5 );
	
	mCurrentFanSpeed = new wxStaticText( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	mCurrentFanSpeed->Wrap( -1 );
	bSizer211->Add( mCurrentFanSpeed, 0, wxALL, 5 );
	
	bSizer21->Add( bSizer211, 1, wxEXPAND, 5 );
	
	wxArrayString mCurveTypeChoices;
	mCurveType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxSize( 90,-1 ), mCurveTypeChoices, 0 );
	mCurveType->SetSelection( 0 );
	bSizer21->Add( mCurveType, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mButtonClear = new wxButton( this, wxID_ANY, _("Reset"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer21->Add( mButtonClear, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer20->Add( bSizer21, 1, wxEXPAND, 5 );
	
	m_staticline10 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer20->Add( m_staticline10, 0, wxEXPAND | wxALL, 5 );
	
	mCurve = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 368,310 ), wxTAB_TRAVERSAL );
	fgSizer20->Add( mCurve, 1, wxEXPAND | wxALL, 5 );
	
	bSizer19->Add( fgSizer20, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer19 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( CFanControlPanelBase::OnPaint ) );
	mEnable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CFanControlPanelBase::mEnableOnCheckBox ), NULL, this );
	mCurveType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CFanControlPanelBase::mCurveTypeOnChoice ), NULL, this );
	mButtonClear->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanControlPanelBase::mButtonClearClick ), NULL, this );
	mCurve->Connect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CFanControlPanelBase::mCurveOnEnterWindow ), NULL, this );
	mCurve->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CFanControlPanelBase::mCurveOnLeaveWindow ), NULL, this );
	mCurve->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CFanControlPanelBase::mCurveOnLeftDown ), NULL, this );
	mCurve->Connect( wxEVT_LEFT_UP, wxMouseEventHandler( CFanControlPanelBase::mCurveOnLeftUp ), NULL, this );
	mCurve->Connect( wxEVT_MOTION, wxMouseEventHandler( CFanControlPanelBase::mCurveOnMotion ), NULL, this );
}

CFanControlPanelBase::~CFanControlPanelBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( CFanControlPanelBase::OnPaint ) );
	mEnable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CFanControlPanelBase::mEnableOnCheckBox ), NULL, this );
	mCurveType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( CFanControlPanelBase::mCurveTypeOnChoice ), NULL, this );
	mButtonClear->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CFanControlPanelBase::mButtonClearClick ), NULL, this );
	mCurve->Disconnect( wxEVT_ENTER_WINDOW, wxMouseEventHandler( CFanControlPanelBase::mCurveOnEnterWindow ), NULL, this );
	mCurve->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( CFanControlPanelBase::mCurveOnLeaveWindow ), NULL, this );
	mCurve->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CFanControlPanelBase::mCurveOnLeftDown ), NULL, this );
	mCurve->Disconnect( wxEVT_LEFT_UP, wxMouseEventHandler( CFanControlPanelBase::mCurveOnLeftUp ), NULL, this );
	mCurve->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CFanControlPanelBase::mCurveOnMotion ), NULL, this );
	
}

CAppProfilePanelBase::CAppProfilePanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxBoxSizer* bSizer22;
	bSizer22 = new wxBoxSizer( wxVERTICAL );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 5, 1, 0, 0 );
	fgSizer22->AddGrowableCol( 1 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer22->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer30;
	bSizer30 = new wxBoxSizer( wxHORIZONTAL );
	
	mEnable = new wxCheckBox( this, wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer30->Add( mEnable, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer30->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, _("Active profile:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer30->Add( m_staticText41, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mActiveProfileName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 170,-1 ), wxTE_CENTRE|wxTE_READONLY );
	bSizer30->Add( mActiveProfileName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer22->Add( bSizer30, 1, wxEXPAND, 5 );
	
	m_staticline16 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer22->Add( m_staticline16, 0, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer23;
	bSizer23 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText36 = new wxStaticText( this, wxID_ANY, _("Default profile"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	bSizer23->Add( m_staticText36, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer23->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mDefaultProfileName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 230,-1 ), wxTE_CENTRE|wxTE_READONLY );
	bSizer23->Add( mDefaultProfileName, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mButtonChooseDefault = new wxButton( this, wxID_ANY, _("..."), wxDefaultPosition, wxSize( 24,24 ), 0 );
	bSizer23->Add( mButtonChooseDefault, 0, wxALIGN_CENTER_VERTICAL|wxBOTTOM|wxLEFT|wxTOP, 5 );
	
	fgSizer22->Add( bSizer23, 1, wxALL|wxEXPAND, 5 );
	
	
	fgSizer22->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	mProfileList = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 370,233 ), wxLC_REPORT );
	fgSizer21->Add( mProfileList, 0, wxALL, 5 );
	
	wxBoxSizer* bSizer24;
	bSizer24 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mButtonDeleteProfile = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer24->Add( mButtonDeleteProfile, 0, wxALL, 5 );
	
	mButtonEditProfile = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer24->Add( mButtonEditProfile, 0, wxALL, 5 );
	
	mButtonAddProfile = new wxButton( this, wxID_ANY, _("Add"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer24->Add( mButtonAddProfile, 0, wxALL, 5 );
	
	
	bSizer24->Add( 0, 0, 1, wxEXPAND, 5 );
	
	fgSizer21->Add( bSizer24, 1, wxEXPAND, 5 );
	
	fgSizer22->Add( fgSizer21, 1, wxEXPAND, 5 );
	
	bSizer22->Add( fgSizer22, 1, wxEXPAND, 5 );
	
	this->SetSizer( bSizer22 );
	this->Layout();
	
	// Connect Events
	mEnable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mEnableOnCheckBox ), NULL, this );
	mButtonChooseDefault->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonChooseDefaultClick ), NULL, this );
	mProfileList->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CAppProfilePanelBase::OnLeftDClick ), NULL, this );
	mButtonDeleteProfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonDeleteProfileClick ), NULL, this );
	mButtonEditProfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonEditProfileClick ), NULL, this );
	mButtonAddProfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonAddProfileClick ), NULL, this );
}

CAppProfilePanelBase::~CAppProfilePanelBase()
{
	// Disconnect Events
	mEnable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mEnableOnCheckBox ), NULL, this );
	mButtonChooseDefault->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonChooseDefaultClick ), NULL, this );
	mProfileList->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CAppProfilePanelBase::OnLeftDClick ), NULL, this );
	mButtonDeleteProfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonDeleteProfileClick ), NULL, this );
	mButtonEditProfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonEditProfileClick ), NULL, this );
	mButtonAddProfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CAppProfilePanelBase::mButtonAddProfileClick ), NULL, this );
	
}

CProfileAddDialogBase::CProfileAddDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 5, 1, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer24->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer27;
	bSizer27 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText38 = new wxStaticText( this, wxID_ANY, _("Application"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	bSizer27->Add( m_staticText38, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer27->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mAppName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 240,-1 ), wxTE_CENTRE );
	bSizer27->Add( mAppName, 0, wxALL, 5 );
	
	fgSizer24->Add( bSizer27, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	m_staticText39 = new wxStaticText( this, wxID_ANY, _("Profile"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText39->Wrap( -1 );
	bSizer29->Add( m_staticText39, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mProfileName = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 206,-1 ), wxTE_CENTRE|wxTE_READONLY );
	bSizer29->Add( mProfileName, 0, wxALL, 5 );
	
	mButtonChooseProfile = new wxButton( this, wxID_ANY, _("..."), wxDefaultPosition, wxSize( 24,24 ), 0 );
	bSizer29->Add( mButtonChooseProfile, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer24->Add( bSizer29, 1, wxEXPAND, 5 );
	
	
	fgSizer24->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxVERTICAL );
	
	mDialogButtons = new wxStdDialogButtonSizer();
	mDialogButtonsOK = new wxButton( this, wxID_OK );
	mDialogButtons->AddButton( mDialogButtonsOK );
	mDialogButtonsCancel = new wxButton( this, wxID_CANCEL );
	mDialogButtons->AddButton( mDialogButtonsCancel );
	mDialogButtons->Realize();
	bSizer28->Add( mDialogButtons, 1, wxALL|wxEXPAND, 5 );
	
	fgSizer24->Add( bSizer28, 1, wxEXPAND, 5 );
	
	
	fgSizer24->Add( 0, 5, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer24 );
	this->Layout();
	fgSizer24->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	mButtonChooseProfile->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProfileAddDialogBase::mButtonChooseProfileClick ), NULL, this );
	mDialogButtonsCancel->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProfileAddDialogBase::CancelButtonClick ), NULL, this );
	mDialogButtonsOK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProfileAddDialogBase::OKButtonClick ), NULL, this );
}

CProfileAddDialogBase::~CProfileAddDialogBase()
{
	// Disconnect Events
	mButtonChooseProfile->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProfileAddDialogBase::mButtonChooseProfileClick ), NULL, this );
	mDialogButtonsCancel->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProfileAddDialogBase::CancelButtonClick ), NULL, this );
	mDialogButtonsOK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CProfileAddDialogBase::OKButtonClick ), NULL, this );
	
}

COvdrSettingsPanelBase::COvdrSettingsPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer24->Add( 0, 5, 1, wxEXPAND, 5 );
	
	mOvdrNotebook = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxSize( 370,334 ), 0 );
	
	fgSizer24->Add( mOvdrNotebook, 1, wxEXPAND | wxALL, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	
	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );
	
	mButtonReset = new wxButton( this, wxID_ANY, _("Reset"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer29->Add( mButtonReset, 0, wxALL, 5 );
	
	mButtonSet = new wxButton( this, wxID_ANY, _("Set"), wxDefaultPosition, wxSize( 80,-1 ), 0 );
	bSizer29->Add( mButtonSet, 0, wxALL, 5 );
	
	
	bSizer29->Add( 0, 0, 1, wxEXPAND, 5 );
	
	fgSizer24->Add( bSizer29, 1, wxEXPAND, 5 );
	
	this->SetSizer( fgSizer24 );
	this->Layout();
	
	// Connect Events
	mButtonReset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( COvdrSettingsPanelBase::mButtonResetClick ), NULL, this );
	mButtonSet->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( COvdrSettingsPanelBase::mButtonSetClick ), NULL, this );
}

COvdrSettingsPanelBase::~COvdrSettingsPanelBase()
{
	// Disconnect Events
	mButtonReset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( COvdrSettingsPanelBase::mButtonResetClick ), NULL, this );
	mButtonSet->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( COvdrSettingsPanelBase::mButtonSetClick ), NULL, this );
	
}

CColorTempPanelBase::CColorTempPanelBase( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style ) : wxPanel( parent, id, pos, size, style )
{
	wxFlexGridSizer* fgSizer26;
	fgSizer26 = new wxFlexGridSizer( 7, 1, 0, 0 );
	fgSizer26->SetFlexibleDirection( wxBOTH );
	fgSizer26->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	
	fgSizer26->Add( 0, 5, 1, wxEXPAND, 5 );
	
	wxBoxSizer* bSizer28;
	bSizer28 = new wxBoxSizer( wxHORIZONTAL );
	
	bSizer28->SetMinSize( wxSize( 380,-1 ) ); 
	mEnable = new wxCheckBox( this, wxID_ANY, _("enable"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer28->Add( mEnable, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer28->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText40 = new wxStaticText( this, wxID_ANY, _("Long."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText40->Wrap( -1 );
	bSizer28->Add( m_staticText40, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mLongitude = new wxTextCtrl( this, wxID_ANY, _("-13,5"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
	bSizer28->Add( mLongitude, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	m_staticText41 = new wxStaticText( this, wxID_ANY, _("Lat."), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText41->Wrap( -1 );
	bSizer28->Add( m_staticText41, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mLatitude = new wxTextCtrl( this, wxID_ANY, _("52,5"), wxDefaultPosition, wxDefaultSize, wxTE_CENTRE );
	bSizer28->Add( mLatitude, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	
	bSizer28->Add( 0, 0, 1, wxEXPAND, 5 );
	
	fgSizer26->Add( bSizer28, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer27;
	fgSizer27 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer27->SetFlexibleDirection( wxBOTH );
	fgSizer27->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText42 = new wxStaticText( this, wxID_ANY, _("Color temperature day"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText42->Wrap( -1 );
	m_staticText42->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer27->Add( m_staticText42, 0, wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bSizer29;
	bSizer29 = new wxBoxSizer( wxHORIZONTAL );
	
	mColorTempDay = new wxTextCtrl( this, wxID_ANY, _("6500"), wxDefaultPosition, wxSize( 80,-1 ), wxTE_CENTRE|wxTE_READONLY );
	bSizer29->Add( mColorTempDay, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mColorTempDaySlider = new wxSlider( this, wxID_ANY, 1300, 600, 1400, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	mColorTempDaySlider->SetMinSize( wxSize( 280,-1 ) );
	
	bSizer29->Add( mColorTempDaySlider, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer27->Add( bSizer29, 1, wxEXPAND, 5 );
	
	fgSizer26->Add( fgSizer27, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer271;
	fgSizer271 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer271->SetFlexibleDirection( wxBOTH );
	fgSizer271->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText421 = new wxStaticText( this, wxID_ANY, _("Color temperature night"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText421->Wrap( -1 );
	m_staticText421->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer271->Add( m_staticText421, 0, wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bSizer291;
	bSizer291 = new wxBoxSizer( wxHORIZONTAL );
	
	mColorTempNight = new wxTextCtrl( this, wxID_ANY, _("3400"), wxDefaultPosition, wxSize( 80,-1 ), wxTE_CENTRE|wxTE_READONLY );
	bSizer291->Add( mColorTempNight, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mColorTempNightSlider = new wxSlider( this, wxID_ANY, 680, 600, 1400, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	mColorTempNightSlider->SetMinSize( wxSize( 280,-1 ) );
	
	bSizer291->Add( mColorTempNightSlider, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer271->Add( bSizer291, 1, wxEXPAND, 5 );
	
	fgSizer26->Add( fgSizer271, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer272;
	fgSizer272 = new wxFlexGridSizer( 2, 1, 0, 0 );
	fgSizer272->SetFlexibleDirection( wxBOTH );
	fgSizer272->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText422 = new wxStaticText( this, wxID_ANY, _("Transition duration"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText422->Wrap( -1 );
	m_staticText422->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), 70, 90, 92, false, wxEmptyString ) );
	
	fgSizer272->Add( m_staticText422, 0, wxLEFT|wxTOP, 5 );
	
	wxBoxSizer* bSizer292;
	bSizer292 = new wxBoxSizer( wxHORIZONTAL );
	
	mTransition = new wxTextCtrl( this, wxID_ANY, _("30min"), wxDefaultPosition, wxSize( 80,-1 ), wxTE_CENTRE|wxTE_READONLY );
	bSizer292->Add( mTransition, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	mTransitionSlider = new wxSlider( this, wxID_ANY, 30, 0, 60, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	mTransitionSlider->SetMinSize( wxSize( 280,-1 ) );
	
	bSizer292->Add( mTransitionSlider, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );
	
	fgSizer272->Add( bSizer292, 1, wxEXPAND, 5 );
	
	fgSizer26->Add( fgSizer272, 1, wxEXPAND, 5 );
	
	m_staticline11 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	fgSizer26->Add( m_staticline11, 0, wxEXPAND | wxALL, 5 );
	
	mCurve = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 370,160 ), wxTAB_TRAVERSAL );
	fgSizer26->Add( mCurve, 1, wxEXPAND | wxALL, 5 );
	
	this->SetSizer( fgSizer26 );
	this->Layout();
	
	// Connect Events
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( CColorTempPanelBase::OnPaint ) );
	mEnable->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CColorTempPanelBase::mEnableOnCheckBox ), NULL, this );
	mLongitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CColorTempPanelBase::mLongitudeOnText ), NULL, this );
	mLatitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CColorTempPanelBase::mLatitudeOnText ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mCurve->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CColorTempPanelBase::mCurveOnLeftDown ), NULL, this );
	mCurve->Connect( wxEVT_MOTION, wxMouseEventHandler( CColorTempPanelBase::mCurveOnMotion ), NULL, this );
}

CColorTempPanelBase::~CColorTempPanelBase()
{
	// Disconnect Events
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( CColorTempPanelBase::OnPaint ) );
	mEnable->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( CColorTempPanelBase::mEnableOnCheckBox ), NULL, this );
	mLongitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CColorTempPanelBase::mLongitudeOnText ), NULL, this );
	mLatitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( CColorTempPanelBase::mLatitudeOnText ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempDaySlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CColorTempPanelBase::mColorTempDaySliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mColorTempNightSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CColorTempPanelBase::mColorTempNightSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mTransitionSlider->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( CColorTempPanelBase::mTransitionSliderOnScroll ), NULL, this );
	mCurve->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CColorTempPanelBase::mCurveOnLeftDown ), NULL, this );
	mCurve->Disconnect( wxEVT_MOTION, wxMouseEventHandler( CColorTempPanelBase::mCurveOnMotion ), NULL, this );
	
}
