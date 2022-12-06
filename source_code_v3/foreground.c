/**
*** INTEL CONFIDENTIAL
***
*** Copyright (March 2011) (March 2011) Intel Corporation All Rights Reserved.
*** The source code contained or described herein and all documents related to the
*** source code ("Material") are owned by Intel Corporation or its suppliers or
*** licensors. Title to the Material remains with Intel Corporation or its
*** suppliers and licensors. The Material contains trade secrets and proprietary
*** and confidential information of Intel or its suppliers and licensors.
*** The Material is protected by worldwide copyright and trade secret laws
*** and treaty provisions. No part of the Material may be used, copied,
*** reproduced, modified, published, uploaded, posted, transmitted, distributed,
*** or disclosed in any way without Intel's prior express written permission.
***
*** No license under any patent, copyright, trade secret or other intellectual
*** property right is granted to or conferred upon you by disclosure or delivery
*** of the Materials, either expressly, by implication, inducement, estoppel or
*** otherwise. Any license under such intellectual property rights must be
*** express and approved by Intel in writing.
**/

//-----------------------------------------------------------------------------
// Headers inclusions.
//-----------------------------------------------------------------------------
#include <assert.h>
#include <process.h> // for _beginthreadex
#include <windows.h>
#include <tchar.h>
#include <Psapi.h> // GetProcessImageFileName
#include <stdio.h>
#include <string.h> // to split the PII path
#include "foreground.h"

//-----------------------------------------------------------------------------
// Custom event-listener thread data.
//-----------------------------------------------------------------------------
#ifdef __PL_WINDOWS__
DWORD thread_id = 0;
HANDLE thread_handle = NULL;
char window_name[STRING_BUFFERS_SIZE] = { '\0' };
char image_name[MAX_PATH] = { '\0' };
char class_name[STRING_BUFFERS_SIZE] = { '\0' };
#endif // __PL_WINDOWS__

/*-----------------------------------------------------------------------------
Function: modeler_init_inputs
Purpose : return the inputs count.
In      : pointer to an unsigned integer.
Out     : modified unsigned integer.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_API ESRV_STATUS modeler_init_inputs(
	unsigned int* p,
	int* pfd,
	int* pfe,
	char* po,
	size_t so
) {
	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert inputs not null
		assert(p != NULL);
	assert(pfd != NULL);
	assert(pfe != NULL);

	// Signal pure event-driven
	SIGNAL_PURE_EVENT_DRIVEN_MODE;

	// Set the input count
	SET_INPUTS_COUNT(INPUTS_COUNT);

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(NULL)

}

/*-----------------------------------------------------------------------------
Function: modeler_open_inputs
Purpose : open inputs.
In      : pointer to PINTEL_MODELER_INPUT_TABLE data structure.
Out     : modified PINTEL_MODELER_INPUT_TABLE data structure.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_API ESRV_STATUS modeler_open_inputs(PINTEL_MODELER_INPUT_TABLE p) {

	// Generic variable used in the for-loop
	unsigned int i = 0;

	// Input descriptions
	static char* descriptions[INPUTS_COUNT] = {
		INPUT_DESCRIPTION_STRINGS
	};
	static INTEL_MODELER_INPUT_TYPES types[INPUTS_COUNT] = {
		INPUT_TYPES
	};

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(p != NULL);

	// Begin the thread
#ifdef __PL_WINDOWS__
	thread_handle = (HANDLE)_beginthreadex(
		NULL,
		0,
		foreground_window_event_listener_thread,
		(void*)p,
		0,
		(unsigned int*)&thread_id
	);
	if (thread_handle == NULL) {
		goto modeler_open_inputs_error;
	}
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	iret = pthread_create(
		&thread_handle,
		NULL,
		foreground_window_event_listener_thread,
		(void*)p
	);
	if (iret != 0) {
		goto modeler_open_inputs_error;
	}
	thread_handle_initialized = 1;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	// Set inputs
	SET_INPUTS_NAME(INPUT_NAME_STRING);
	for (i = 0; i < INPUTS_COUNT; i++) {
		SET_INPUT_DESCRIPTION(
			i,
			descriptions[i]
		);
		SET_INPUT_TYPE(
			i,
			types[i]
		);
	} // for i (each input)

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

		modeler_open_inputs_error:

	return(ESRV_FAILURE);

}

/*-----------------------------------------------------------------------------
Function: modeler_close_inputs
Purpose : close inputs.
In      : pointer to PINTEL_MODELER_INPUT_TABLE data structure.
Out     : modified PINTEL_MODELER_INPUT_TABLE data structure.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_API ESRV_STATUS modeler_close_inputs(PINTEL_MODELER_INPUT_TABLE p) {

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(p != NULL);

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

	// Wait for the thread's end.
	if (thread_handle_initialized == 1) {
		iret = pthread_join(
			thread_handle,
			NULL
		);
		if (iret != 0) {
			goto modeler_close_inputs_error;
		}
	}
	thread_handle_initialized = 0;
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)

		modeler_close_inputs_error:

	return(ESRV_FAILURE);

#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

}

/*-----------------------------------------------------------------------------
Function: modeler_read_inputs
Purpose : collect all inputs.
In      : pointer to PINTEL_MODELER_INPUT_TABLE data structure.
Out     : modified PINTEL_MODELER_INPUT_TABLE data structure.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_STATUS modeler_read_inputs(PINTEL_MODELER_INPUT_TABLE p) {

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(p != NULL);

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

}

/*-----------------------------------------------------------------------------
Function: modeler_listen_inputs
Purpose : listen for all inputs.
In      : pointer to PINTEL_MODELER_INPUT_TABLE data structure.
Out     : modified PINTEL_MODELER_INPUT_TABLE data structure.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_STATUS modeler_listen_inputs(PINTEL_MODELER_INPUT_TABLE p) {

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(p != NULL);

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

}

/*-----------------------------------------------------------------------------
Function: modeler_process_dctl
Purpose : process DCTL commands on DCTL interrupt notification.
In      : pointer to PINTEL_MODELER_INPUT_TABLE data structure.
Out     : modified PINTEL_MODELER_INPUT_TABLE data structure.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_STATUS modeler_process_dctl(PINTEL_MODELER_INPUT_TABLE p) {

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(p != NULL);

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

}

/*-----------------------------------------------------------------------------
Function: modeler_process_lctl
Purpose : process LCTL commands on LCTL interrupt notification.
In      : pointer to PINTEL_MODELER_INPUT_TABLE data structure.
Out     : modified PINTEL_MODELER_INPUT_TABLE data structure.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_STATUS modeler_process_lctl(PINTEL_MODELER_INPUT_TABLE p) {

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(p != NULL);

	return(ESRV_SUCCESS);

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

}

//-----------------------------------------------------------------------------

/*-----------------------------------------------------------------------------
Function: foreground_window_event_listener_thread
Purpose : implement the pure event listener thread.
In      : pointers to the input table (passed as void *).
Out     : modified input variables and time events list data.
Return  : status.
-----------------------------------------------------------------------------*/
ESRV_API unsigned int __stdcall foreground_window_event_listener_thread(void* px) {

	// Necessary variables.
	DWORD dwret = 0;
	DWORD pid = 0;
	DWORD tid = 0;
	DWORD prev_pid = 0;

	HWND foreground_handle = NULL;
	HANDLE process_handle = NULL;

	BOOL bret = FALSE;
	BOOL is_hung = FALSE;
	BOOL is_immersive = FALSE;

	size_t stret = 0;

	unsigned long long int root_id = 0;

	TCHAR window_name_tchar[STRING_BUFFERS_SIZE] = { _T('\0') };
	TCHAR image_name_tchar[MAX_PATH] = { _T('\0') };
	TCHAR class_name_tchar[STRING_BUFFERS_SIZE] = { _T('\0') };

	char* token = NULL;
	char* prev_token = NULL;

	RECT rectangle;
	unsigned long long x_upper_left = 0;
	unsigned long long x_lower_right = 0;
	unsigned long long y_upper_left = 0;
	unsigned long long y_lower_right = 0;

	// Watchdog variables
	WATCHDOG_VARIABLES

		PINTEL_MODELER_INPUT_TABLE p = NULL;

	// Exception handling begins
	INPUT_BEGIN_EXCEPTIONS_HANDLING

		// Assert input not null
		assert(px != NULL);
	// Casting p
	p = (PINTEL_MODELER_INPUT_TABLE)px;

	INPUT_DIAGNOSTIC_NAME_THIS_THREAD(
		p,
		"foreground_window_event_listener_thread"
	);

	// Register with watchdog
	INPUT_REGISTER_EVENT_LOCKED_THREAD_WITH_WATCHDOG(
		p,
		"foreground_window_event_listener_thread",
		thread_handle,
		thread_id,
		STOP_SIGNAL,
		foreground_window_event_listener_thread_exit
	);

	// While-loop. Stop when STOP_REQUEST is 0
	while (STOP_REQUEST == 0) {

		// Wait for the stop signal
		dwret = WaitForSingleObject(
			STOP_SIGNAL,
			INPUT_PAUSE_IN_MS
		);

		// switch
		switch (dwret) {
		case WAIT_OBJECT_0:
			// Stop signal received --> leave
			goto foreground_window_event_listener_thread_exit;
			break;
		case WAIT_TIMEOUT:
			break; // Time out. Make measurement
		default:
			goto foreground_window_event_listener_thread_exit; // error condition
		}

		// Retrieve the foreground window
		foreground_handle = GetForegroundWindow();

		// Null foreground window handle in cases 
		// such as a window losing its activation
		if (foreground_handle == NULL) {
			continue;
		}

		// Get the root id
		root_id = (unsigned long long int)foreground_handle;

		// Get and set the thread identifier (tid) 
		// and the process identifier (pid)
		tid = GetWindowThreadProcessId(
			root_id,
			&pid
		);

		// Ensure that we don't log the same foreground every time
		if (pid == prev_pid) {
			continue;
		}
		else {
			prev_pid = pid;
		}

		// Set pid, tid, root_id
		SET_INPUT_ULL_VALUE(
			PROCESS_ID,
			pid
		);

		SET_INPUT_ULL_VALUE(
			THREAD_ID,
			tid
		);
		SET_INPUT_ULL_VALUE(
			ROOT_ID,
			root_id
		);

		// Get window name (window's title bar)
		(void)InternalGetWindowText(
			foreground_handle,
			window_name_tchar,
			sizeof(window_name_tchar) / sizeof(TCHAR)
		);
		(void)wcstombs_s(
			&stret,
			window_name,
			sizeof(window_name),
			window_name_tchar,
			_TRUNCATE
		);

		// Remove PII path by the separator "//"
		token = strtok(window_name, PATH_SEPARATOR_CHAR);
		prev_token = NULL;
		while (token != NULL) {
			prev_token = token;
			token = strtok(NULL, PATH_SEPARATOR_CHAR);
		}

		// Set the window name after removing PII
		SET_INPUT_STRING_ADDRESS(
			WINDOW_NAME,
			prev_token
		);

		// Get class name
		(void)GetClassNameW(
			foreground_handle,
			class_name_tchar,
			sizeof(class_name_tchar) / sizeof(TCHAR)
		);
		(void)wcstombs_s(
			&stret,
			class_name,
			sizeof(class_name),
			class_name_tchar,
			_TRUNCATE
		);
		// Adjust the class name (remove unnecessary parts)
		token = strtok(class_name, CLASS_NAME_SEPARATOR_CHAR);

		// Set the class name
		SET_INPUT_STRING_ADDRESS(
			CLASS_NAME,
			token
		);

		// Find the corners of the window rectangle
		(void)GetWindowRect(
			foreground_handle,
			&rectangle
		);

		x_upper_left = rectangle.left;
		x_lower_right = rectangle.right;
		y_upper_left = rectangle.top;
		y_lower_right = rectangle.bottom;

		// Set all the values of the window rectangle's corners
		SET_INPUT_ULL_VALUE(
			X_UPPER_LEFT,
			x_upper_left
		);

		SET_INPUT_ULL_VALUE(
			Y_UPPER_LEFT,
			y_upper_left
		);

		SET_INPUT_ULL_VALUE(
			X_LOWER_RIGHT,
			x_lower_right
		);

		SET_INPUT_ULL_VALUE(
			Y_LOWER_RIGHT,
			y_lower_right
		);

		// Check if the window is hung 
		// (return TRUE if the window stops responding; FALSE otherwise)
		is_hung = IsHungAppWindow(foreground_handle);

		SET_INPUT_ULL_VALUE(
			IS_HUNG,
			is_hung
		);

		// Check if the process belongs to a Windows Store app
		is_immersive = IsImmersiveProcess(foreground_handle);
		SET_INPUT_ULL_VALUE(
			IS_IMMERSIVE,
			is_immersive
		);

		// Try opening a process and Get the process image
		process_handle = OpenProcess(
			PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
			FALSE,
			pid
		);
		if (process_handle != NULL) {
			is_immersive = IsImmersiveProcess(process_handle);
			dwret = GetProcessImageFileName(
				process_handle,
				image_name_tchar,
				sizeof(image_name_tchar)
			);
			bret = CloseHandle(process_handle);
			process_handle = NULL;
		}
		else {
			(void)_tcsncpy(
				image_name_tchar,
				_T("Unable To Open Process"),
				sizeof(image_name_tchar) / sizeof(TCHAR)
			);
		}

		(void)wcstombs_s(
			&stret,
			image_name,
			sizeof(image_name),
			image_name_tchar,
			_TRUNCATE
		);
		// Remove PII and get the image name
		token = strtok(image_name, PATH_SEPARATOR_CHAR);
		prev_token = NULL;
		while (token != NULL) {
			prev_token = token;
			token = strtok(NULL, PATH_SEPARATOR_CHAR);
		}
		token = prev_token;
		while (token != NULL) {
			prev_token = token;
			token = strtok(NULL, NAME_SEPARATOR_CHAR);
		}
		// Set image name after removing PII
		SET_INPUT_STRING_ADDRESS(
			IMAGE_NAME,
			prev_token
		);
		SET_INPUT_ULL_VALUE(
			IS_IMMERSIVE,
			is_immersive
		);

		//---------------------------------------------------------------------
		// Trigger logging.
		//---------------------------------------------------------------------
		LOG_INPUT_VALUES;

	} // while

foreground_window_event_listener_thread_exit:

#ifdef __PL_WINDOWS__

	// Unregister the thread with watchdog
	INPUT_UNREGISTER_THREAD_WITH_WATCHDOG(
		p,
		thread_handle,
		thread_id
	);
#endif // __PL_WINDOWS__

#ifdef __PL_WINDOWS__
	return(ESRV_SUCCESS);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	return((void*)ESRV_SUCCESS);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

	// Exception handling ends
	INPUT_END_EXCEPTIONS_HANDLING(p)

		foreground_window_event_listener_thread_error:

#ifdef __PL_WINDOWS__
	return(ESRV_FAILURE);
#endif // __PL_WINDOWS__

#if defined (__PL_LINUX__) || (__PL_SOLARIS__) || (__PL_MACOSX__)
	return((void*)ESRV_FAILURE);
#endif // __PL_LINUX__ || __PL_SOLARIS__ || __PL_MACOSX__

}
