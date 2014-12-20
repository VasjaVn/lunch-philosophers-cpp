#include "stdafx.h"
#include "Philosopher.h"

State  CPhilosopher::s_state[]     = { THINKING };
HANDLE CPhilosopher::s_Semaphore[] = { NULL };

/****************************************************************************************/

CPhilosopher::CPhilosopher( int               p_iNumber,
						    CRITICAL_SECTION& p_rcsMutex,
							HWND              p_hWnd ) : m_rcsMutex( p_rcsMutex ),
														 m_hWnd( p_hWnd )
{
	m_iNumber = p_iNumber;
	m_iLeft   = ( m_iNumber + COUNT_PHILOSOPHERS - 1) % COUNT_PHILOSOPHERS;
	m_iRight  = ( m_iNumber + 1) % COUNT_PHILOSOPHERS;

	m_timeThinking = 200;
	m_timeEating = 1000;

	CPhilosopher::s_Semaphore[m_iNumber] = CreateSemaphore( NULL, 0, 1, NULL );
}


/****************************************************************************************/

CPhilosopher::~CPhilosopher()
{
	CloseHandle( s_Semaphore[m_iNumber] );
}


/****************************************************************************************/

void CPhilosopher::takeForks()
{
	EnterCriticalSection(&m_rcsMutex);
	CPhilosopher::s_state[m_iNumber] = HUNGRY;
	testSelf();
	LeaveCriticalSection(&m_rcsMutex);
	WaitForSingleObject( s_Semaphore[m_iNumber], INFINITE );
}


/****************************************************************************************/

void CPhilosopher::putForks()
{
	EnterCriticalSection(&m_rcsMutex);
	CPhilosopher::s_state[m_iNumber] = THINKING;
	testNeighbor(m_iLeft);
	testNeighbor(m_iRight);
	LeaveCriticalSection(&m_rcsMutex);
}


/****************************************************************************************/

void CPhilosopher::think()
{
	Sleep( m_timeThinking );
}


/****************************************************************************************/

void CPhilosopher::eat()
{
	InvalidateRect( m_hWnd, NULL, FALSE );
	writeToConsole();
	Sleep( m_timeEating );
}


/****************************************************************************************/

void CPhilosopher::setTimeoutThinking( int p_iTimeout )
{
	m_timeThinking = p_iTimeout;
}


/****************************************************************************************/

void CPhilosopher::setTimeoutEating( int p_iTimeout )
{
	m_timeEating = p_iTimeout;
}


/****************************************************************************************/

void CPhilosopher::testSelf()
{
	if (s_state[m_iNumber] == HUNGRY && s_state[m_iLeft] != EATING && s_state[m_iRight] != EATING) {
		s_state[m_iNumber] = EATING;
		ReleaseSemaphore( s_Semaphore[m_iNumber], 1, NULL );
	}
}


/****************************************************************************************/

void CPhilosopher::testNeighbor( int p_iNumber )
{
	int iLeft   = ( p_iNumber + COUNT_PHILOSOPHERS - 1) % COUNT_PHILOSOPHERS;
	int iRight  = ( p_iNumber + 1) % COUNT_PHILOSOPHERS;

	if (s_state[p_iNumber] == HUNGRY && s_state[iLeft] != EATING && s_state[iRight] != EATING) {
		s_state[p_iNumber] = EATING;
		ReleaseSemaphore( s_Semaphore[p_iNumber], 1, NULL );
	}
}


/****************************************************************************************/

#define SIZE_BUFFER 100

void CPhilosopher::writeToConsole()
{
	TCHAR szBuffer[SIZE_BUFFER] = { 0 };

	TCHAR szOne[SIZE_BUFFER]   = { 0 };
	TCHAR szTwo[SIZE_BUFFER]   = { 0 };
	TCHAR szThree[SIZE_BUFFER] = { 0 };
	TCHAR szFour[SIZE_BUFFER]  = { 0 };
	TCHAR szFive[SIZE_BUFFER]  = { 0 };

	
	convertStateToString( CPhilosopher::s_state[0], szOne );
	convertStateToString( CPhilosopher::s_state[1], szTwo );
	convertStateToString( CPhilosopher::s_state[2], szThree );
	convertStateToString( CPhilosopher::s_state[3], szFour );
	convertStateToString( CPhilosopher::s_state[4], szFive );

	_stprintf_s( szBuffer, _T("%s\t%s\t%s\t%s\t%s\n"), szOne, szTwo, szThree, szFour, szFive );

	WriteConsole( g_hOut, szBuffer, _tcslen( szBuffer ), NULL, NULL );
}


/****************************************************************************************/

void CPhilosopher::convertStateToString( State p_state, TCHAR p_szBuffer[] )
{
	switch ( p_state ) {
		
		case THINKING:
			_tcscpy_s( p_szBuffer, SIZE_BUFFER, _T("THINKING") );
			break;

		case HUNGRY:
			_tcscpy_s( p_szBuffer, SIZE_BUFFER, _T("HUNGRY") );
			break;

		case EATING:
			_tcscpy_s( p_szBuffer, SIZE_BUFFER, _T("EATING") );
			break;

		default:
			_tcscpy_s( p_szBuffer, SIZE_BUFFER, _T("ERROR") );
	}
}
