#ifndef __PHILOSOPHER_H__
#define __PHILOSOPHER_H__

#include "Shared.h"

enum State { THINKING, HUNGRY, EATING };

extern HANDLE g_hOut;

class CPhilosopher {

	public:
		CPhilosopher( int p_iNumber, CRITICAL_SECTION& p_rcsMutex, HWND p_hWnd );
		~CPhilosopher();

		void takeForks();
		void putForks();
		void think();
		void eat();

		void setTimeoutThinking( int p_iTimeout );
		void setTimeoutEating( int p_iTimeout );

	private:
		void testSelf();
		void testNeighbor( int p_iNumber );

		void writeToConsole();
		void convertStateToString( State p_state, TCHAR p_szStr[] );

	public:
		static State s_state[COUNT_PHILOSOPHERS];
	private:
		static HANDLE s_Semaphore[COUNT_PHILOSOPHERS];
	
	private:
		HWND m_hWnd;

		int m_iNumber;
		int m_iLeft;
		int m_iRight;

		CRITICAL_SECTION& m_rcsMutex;

		int m_timeThinking;
		int m_timeEating;

};

#endif // __PHILOSOPHER_H__