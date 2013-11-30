//// wavein.h
//
//#define RECORD_BUFFER_SIZE   327680L
//#define DATABLOCK_SIZE          32768L
//#define MAX_BUFFERS                 2  // double buffer
//#define MSG_LEN                   128
//
//enum Status
//{
//  StatusOkay,
//  StatusError,
//  StatusDone,
//} ;
//
//// global variables
////.................
//
//extern enum Status eStatus;
//
//extern char msg[MSG_LEN+1];
//
//extern HWAVEIN  hwi;
//extern LPWAVEHDR  whin[MAX_BUFFERS];
//extern CFile *AudioFile;
//
//// Storage buffer
////.............................
//
//extern VOID*    pRecordBuffer;
//extern DWORD    nRecordBufferPos;  // position in Record buffer
//extern DWORD    nRecordBufferLen;  // total data in Record buffer
//
//BOOL TestOpenInputDevice(HWND hWnd);
//
//VOID StartRecordTest  (HWND hWnd);
//VOID StopRecordTest   (HWND hWnd);
//VOID LoadDataBlock(WAVEHDR* lpwh);
//
//VOID AllocBuffers();
//VOID CleanUpBuffers();
//
//
//WaveIn.cpp
//
//#include <stdafx.h>
//#include "WaveIn.h"
//
//
//// global variables
////.................
//enum Status eStatus;
//
//char msg[MSG_LEN+1];
//
//HWAVEIN  hwi;
//LPWAVEHDR  whin[MAX_BUFFERS];
//
//
//// Storage buffer
////.............................
//
//VOID*    pRecordBuffer;
//DWORD    nRecordBufferPos = 0L;  // position in Record buffer
//DWORD    nRecordBufferLen = 0L;  // total data in Record buffer
//CFile *AudioFile;
//
//
//
///*****************************************************************************
//*  TestOpenInputDevice
//*
//*
//*
//******************************************************************************/
//
//BOOL TestOpenInputDevice(HWND hWnd)
//{
//   WAVEINCAPS   wic;
//	WAVEFORMATEX wfx;
//	UINT         nDevId;
//	MMRESULT     rc;
//	UINT         nMaxDevices = waveInGetNumDevs();
//
//	hwi = NULL;
//	nRecordBufferPos = 0L;  // position in Record buffer
//   nRecordBufferLen = 0L;  // total data in Record buffer
//   eStatus = StatusOkay;     // reset status
//
//	for (nDevId = 0; nDevId < nMaxDevices; nDevId++)
//	{
//	   rc = waveInGetDevCaps(nDevId, &wic, sizeof(wic));
//	   if (rc == MMSYSERR_NOERROR)
//	   {
//          // attempt 44.1 kHz stereo if device is capable
//
//          if (wic.dwFormats & WAVE_FORMAT_4S16)
//          {
//              wfx.nChannels      = 2;      // stereo
//              wfx.nSamplesPerSec = 44100;  // 44.1 kHz (44.1 * 1000)
//          }
//          else
//          {
//              wfx.nChannels      = wic.wChannels;  // use DevCaps # channels
//              wfx.nSamplesPerSec = 22050;  // 22.05 kHz (22.05 * 1000)
//          }
//
//	       wfx.wFormatTag      = WAVE_FORMAT_PCM;
//       	 wfx.wBitsPerSample  = 8;
//      	 wfx.nBlockAlign     = wfx.nChannels * wfx.wBitsPerSample / 8;
//      	 wfx.nAvgBytesPerSec = wfx.nSamplesPerSec * wfx.nBlockAlign;
//      	 wfx.cbSize          = 0;
//
//          // open waveform input device
//          //...........................
//
//	       rc = waveInOpen(&hwi, nDevId, &wfx, (DWORD)(VOID*)waveInProc, (DWORD)hWnd,
//	                       CALLBACK_FUNCTION);
//
//	       if (rc == MMSYSERR_NOERROR)
//	           break;
//	       else
//	       {
//	           waveInGetErrorText(rc, msg, MSG_LEN),
//	           MessageBox(hWnd, msg, NULL, MB_OK);
//	           return(FALSE);
//	       }
//	   }
//	}
//
//   // device not found, error condition
//   //..................................
//
//	if (hwi == NULL)
//	{
//       eStatus = StatusError;
//	    return(FALSE);
//   }
//
//
//   return(TRUE);
//}
//
//
///*****************************************************************************
//*  StartRecordTest
//*
//*
//*
//******************************************************************************/
//
//VOID StartRecordTest(HWND hWnd)
//{
//	MMRESULT rc;
//   int      i;
//   MMTIME   mmtime;
//
//	// prepare buffer blocks and add to input queue
//	//.............................................
//	for (i = 0; i < MAX_BUFFERS; i++)
//	{
//	   rc = waveInPrepareHeader(hwi, whin[i], sizeof(WAVEHDR));
//
//	   // add buffers to the input queue
//
//	   if (rc == MMSYSERR_NOERROR)
//	   {
//	       rc = waveInAddBuffer(hwi, whin[i], sizeof(WAVEHDR));
//		   //MessageBox(hWnd, "Added buffer", "After prep", MB_OK);
//	   }
//
//	   if (rc != MMSYSERR_NOERROR)
//	   {
//	       waveInGetErrorText(rc, msg, MSG_LEN),
//	       MessageBox(hWnd, msg, "Error in Preparartion of Wave Headers", MB_OK);
//          StopRecordTest(hWnd);  // free allocated memory
//	       return;
//	   }
//	}
//
//	// start recording
//	//................
//
//	rc = waveInStart(hwi);
//
//	// test waveInGetPosition() function
//
//   mmtime.wType = TIME_SAMPLES;
//
//   rc = waveInGetPosition(hwi, &mmtime, sizeof(MMTIME));
//
//   if (rc != MMSYSERR_NOERROR)
//	{
//	    waveInGetErrorText(rc, msg, MSG_LEN),
//	    MessageBox(hWnd, msg,"Error in GetPosition of WaveIn", MB_OK);
//	}
//
//}
//
///*****************************************************************************
//*  StopRecordTest
//*
//*
//*
//******************************************************************************/
//
//VOID StopRecordTest(HWND hWnd)
//{
//	//MMRESULT rc;
//	int i;
//	//int nReply;
//	//BOOL testopen;
//
//	// stop recording
//	//...............
//
//	//waveInReset Stops the device and sets all the pending buffers to zero.
//	waveInReset(hwi);
//
//	// Unprepare headers
//	//..................
//
//	for (i = 0; i < MAX_BUFFERS; i++)
//		waveInUnprepareHeader(hwi, whin[i], sizeof(WAVEHDR));
//
//	waveInClose(hwi);
//	AudioFile->Close();
//	MessageBox(hWnd, "Finished Recording and Saved WAV file", "Done", MB_OK);
//
//	// I do not know if cleanup is really necessary since the buffers were dynamically allocated.
//	// I think the memory is freed once the process is destroyed.
//
////CleanUpBuffers();
//
//
//}
//
//
//
///*****************************************************************************
//*  LoadDataBlock
//*
//*
//*
//******************************************************************************/
//
//VOID LoadDataBlock(WAVEHDR* lpwh)
//{
//   DWORD nLen;
//
//   if (nRecordBufferPos < nRecordBufferLen)
//   {
//       nLen = nRecordBufferLen - nRecordBufferPos;
//
//       if (nLen > DATABLOCK_SIZE)
//           nLen = DATABLOCK_SIZE;
//
//       memcpy(lpwh->lpData, ((char*)pRecordBuffer+nRecordBufferPos), nLen);
//       lpwh->dwBufferLength = nLen;
//       nRecordBufferPos  += nLen;
//   }
//   else
//       eStatus = StatusDone;
//}
//
//
//
///*****************************************************************************
//*  AllocBuffers
//*
//*
//*
//******************************************************************************/
//
//VOID AllocBuffers()
//{
//	int i;
//
//	// allocate two WAVEHDR buffer blocks
//	//...................................
//
//
//
//	for (i = 0; i < MAX_BUFFERS; i++)
//	{
//		whin[i] = new WAVEHDR;
//		if (whin[i])
//		{
//			whin[i]->lpData = new char[DATABLOCK_SIZE];
//			whin[i]->dwBufferLength = DATABLOCK_SIZE;
//			whin[i]->dwFlags = 0;
//		}
//	}
//
//	// allocate Record buffer - enough space to hold
//	// ten data buffer blocks of waveform sound data
//	//................................................
//
//	pRecordBuffer = new BYTE[RECORD_BUFFER_SIZE];
//}
//
///*****************************************************************************
//*  CleanUpBuffers
//*
//*
//*
//******************************************************************************/
//
//VOID CleanUpBuffers()
//{
//	/*
//	int i;
//
//	// free the WAVEHDR buffer blocks
//	//...............................
//
//	for (i = 0; i < MAX_BUFFERS; i++)
//	{
//		if (whin[i] != NULL)
//		{
//			delete whin[i]->lpData;
//			delete whin[i];
//			whin[i] = NULL;
//		}
//	}
//
//	// free Record buffer
//	//.....................
//
//	delete pRecordBuffer;
//	*/
//}
//
//
//// 3. These files alone do not explain the whole picture.  The process of audio capture has to be understood at the level of the individual components and then brought together as a whole.  The functions and variables defined above are global and will be called by the dialog box that will provide the mechanisms for refreshing the double buffering mechanism.
//// 4. To make things easy this is the point where a couple of controls should be added to the dialog.  These controls will be used to start the recording process and to terminate it.  You do not have to create controls, but I find that interactive examples are the most useful examples in Windows.  After adding the controls and function handlers you should have in the *.h  file of your dialog class something that looks something like this:
//
//// Implementation
//protected:
//	HICON m_hIcon;
//
//	// Generated message map functions
//	//{{AFX_MSG(CWaveInDlg)
//	virtual BOOL OnInitDialog();
//	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
//	afx_msg void OnPaint();
//	afx_msg HCURSOR OnQueryDragIcon();
//	afx_msg void OnStart();
//	afx_msg void OnStop();
//	afx_msg void OnInblock(WPARAM wParam, LPARAM lParam); //add manually to the file
//	DECLARE_EVENTSINK_MAP()
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//};
//
//// 5. Notice the function OnInblock(WPARAM wParam, LPARAM lParam).  This function must be added manually.  The definition of the file must be added to the *.cpp of your dialog (note that this function is a member of the derived dialog class.)  This function will be called when the WM_DATA message is passed to the dialog.  To handle the message passed back the following line must be added to the message map defined in your *.cpp file for the dialog:
//
//BEGIN_MESSAGE_MAP(CWaveInDlg, CDialog)
//	//{{AFX_MSG_MAP(CWaveInDlg)
//	ON_WM_SYSCOMMAND()
//	ON_WM_PAINT()
//	ON_WM_QUERYDRAGICON()
//	ON_BN_CLICKED(IDC_START, OnStart)
//	ON_BN_CLICKED(IDC_STOP, OnStop)
//	ON_MESSAGE(WIM_DATA, OnInblock) //Add this line
//	//}}AFX_MSG_MAP
//END_MESSAGE_MAP()
//
//
//// 6. The wave device knows where to post the message because the HWND handle of the dialog box is passed to TestOpenInputDevice(HWND hWnd).  The API function waveInOpen  takes the HWND as an argument when a callback window is specified as the callback mechanism.  The dialog functions are defined below:
//
//void CWaveInDlg::OnStart()
//{
//	// TODO: Add your control notification handler code here
//	AudioFile = new CFile("C:\\RawAudio\\data.raw", CFile::modeCreate | CFile::modeWrite);
//	int i;
//
//	for (i = 0; i < MAX_BUFFERS; i++)
//		whin[i] = NULL;
//
//	eStatus = StatusOkay;
//	AllocBuffers();
//
//	if ( TestOpenInputDevice(this->m_hWnd) )
//        StartRecordTest(this->m_hWnd);
//	else
//		CleanUpBuffers();
//
//}
//
//void CWaveInDlg::OnStop()
//{
//	// TODO: Add your control notification handler code here
//
//	eStatus = StatusDone;
//	StopRecordTest(this->m_hWnd);
//}
//
//
//void CWaveInDlg::OnInblock(WPARAM wParam, LPARAM lParam)
//{
//	// Received data buffer block with recorded data,
//	// Copy to Record buffer for use later
//	//...............................................
//
//	MMRESULT  rc;
//	MMTIME    mmtime;
//	LPWAVEHDR lpwh = (LPWAVEHDR)lParam;
//
//	//The following if block test if the buffer used for file I/O is full.
////If full then write the buffer to disk and then zero it out.
////If not totally full then add the received buffer to the file I/O buffer.
////After that is done send the buffer back to the device.
//
//	if (eStatus == StatusOkay)
//	{
//		if ((nRecordBufferPos + (lpwh->dwBytesRecorded)) >= RECORD_BUFFER_SIZE)
//		{
//			AudioFile->WriteHuge((BYTE*)pRecordBuffer, nRecordBufferLen);
//			//MessageBox(msg, "Got a input buffer back 1", MB_OK);
//			nRecordBufferPos = 0L;
//			nRecordBufferLen = 0L;
//		}
//
//		// copy data buffer block to Record buffer
//		//..........................................
//
//		memcpy( ((BYTE*)pRecordBuffer+nRecordBufferPos), lpwh->lpData, lpwh->dwBytesRecorded);
//		//MessageBox(msg, "Got a input buffer back", MB_OK);
//		nRecordBufferPos += lpwh->dwBytesRecorded;
//		nRecordBufferLen += lpwh->dwBytesRecorded;
//
//		mmtime.wType = TIME_BYTES;
//		waveInGetPosition(hwi, &mmtime, sizeof(MMTIME));
//		//wsprintf(msg, "%s - Recorded %ld bytes", lpszTitle, mmtime.u.cb);
//		//SetWindowText( msg);
//
//		// reuse data buffer block
//		//........................
//
//		rc = waveInPrepareHeader(hwi, lpwh, sizeof(WAVEHDR));
//
//		if (rc == MMSYSERR_NOERROR)
//			rc = waveInAddBuffer(hwi, lpwh, sizeof(WAVEHDR));
//
//		if (rc != MMSYSERR_NOERROR)
//		{
//			waveInGetErrorText(rc, msg, MSG_LEN),
//				MessageBox(msg, "Could not prepare buffer for refresh", MB_OK);
//			eStatus = StatusError;    // signal to shut down the process
//		}
//	}
//}
//
//
//// 7. This should be enough information to create a module in Visual C++  to capture audio without any gaps, pops, or other irregularities.  In fact this example could be adapted to also work in other development environments such as Delphi.   The only system specific code is the message map. Happy Recording :).
////
////
//// Travell Perkins
//// MIT Media Lab
//// tperkins@media.mit.edu
