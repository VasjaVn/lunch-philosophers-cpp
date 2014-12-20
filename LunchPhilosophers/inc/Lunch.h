#ifndef __LUNCH_H__
#define __LUNCH_H__

#include "Philosopher.h"
#include "TimeoutData.h"

extern TimeoutData g_tmData[COUNT_PHILOSOPHERS];

typedef struct _ThreadData {
	HANDLE        hSemExit;
	CPhilosopher* pPhilosopher;

} ThreadData;


class CLunch {

	public:
		~CLunch();

		void setHWND( HWND p_hWnd );

		void start();
		void stop();
		void pause();
		void resume();


	public:
		static CLunch* getInstance();

	private:
		CLunch();

	private:
		static DWORD WINAPI threadProc(LPVOID lpParameter);
	
    private:
		ThreadData*      m_pThreadData[COUNT_PHILOSOPHERS];
	    CRITICAL_SECTION m_csMutex;
		HANDLE           m_hThreads[COUNT_PHILOSOPHERS];
		HWND             m_hWnd;

	private:
		static CLunch*   s_pInstance;

};

#endif // __LUNCH_H__