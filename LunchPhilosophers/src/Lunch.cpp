#include "stdafx.h"
#include "Lunch.h"


CLunch* CLunch::s_pInstance = NULL;

/*********************************************************************************************************/

CLunch* CLunch::getInstance() {
	if ( s_pInstance == NULL ) {
		s_pInstance = new CLunch();
	}
	return s_pInstance;
}

/*********************************************************************************************************/

CLunch::CLunch() 
{
	InitializeCriticalSection( &m_csMutex );
}


/*********************************************************************************************************/

CLunch::~CLunch() 
{
	CLunch::s_pInstance = NULL;
	DeleteCriticalSection( &m_csMutex );
}


/*********************************************************************************************************/

void CLunch::setHWND( HWND p_hWnd )
{
	m_hWnd = p_hWnd;
}


/*********************************************************************************************************/

void CLunch::start()
{
	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {

		CPhilosopher* pPhilosopher = new CPhilosopher( i , m_csMutex, m_hWnd );
		pPhilosopher->setTimeoutThinking( g_tmData[i].tmThink );
		pPhilosopher->setTimeoutEating( g_tmData[i].tmEat );

		m_pThreadData[i] = new ThreadData();
		m_pThreadData[i]->hSemExit = CreateSemaphore( NULL, 0, 1, NULL );
		m_pThreadData[i]->pPhilosopher = pPhilosopher;

		m_hThreads[i] = CreateThread( NULL, 0, CLunch::threadProc, m_pThreadData[i], 0, NULL );
	}
}


/*********************************************************************************************************/

void CLunch::stop()
{	
	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {			
		ReleaseSemaphore( m_pThreadData[i]->hSemExit, 1, NULL );
	}

	/*
	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {			
		TerminateThread( m_hThreads[i], 0 );
	}*/

	WaitForMultipleObjects( COUNT_PHILOSOPHERS, m_hThreads, TRUE, INFINITE );

	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {

		if ( m_pThreadData[i] != NULL ) {
			
			CPhilosopher* pPhilosopher = m_pThreadData[i]->pPhilosopher;
			HANDLE hSemExit            = m_pThreadData[i]->hSemExit;

			if ( pPhilosopher != NULL ) {
				delete pPhilosopher;
				pPhilosopher = NULL;
			} 
			
			CloseHandle( hSemExit );

			delete m_pThreadData[i];
			m_pThreadData[i] = NULL;
		}
	}
}


/*********************************************************************************************************/

void CLunch::pause()
{
	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {
		SuspendThread( m_hThreads[i] );
	}
}


/*********************************************************************************************************/

void CLunch::resume()
{
	for ( int i = 0; i < COUNT_PHILOSOPHERS; i++ ) {
		ResumeThread( m_hThreads[i] );
	}
}


/*********************************************************************************************************/

#define TIMEOUT_WAIT_FOR_SEM 1

DWORD WINAPI CLunch::threadProc(LPVOID lpParameter)
{
	ThreadData* pThreadStruct = (ThreadData*)lpParameter;

	CPhilosopher* pPhilosopher = pThreadStruct->pPhilosopher;
	HANDLE hSemExit            = pThreadStruct->hSemExit;
	
	while ( true ) {

		DWORD dw = WaitForSingleObject( hSemExit, TIMEOUT_WAIT_FOR_SEM );

		switch ( dw ) {
		
			case WAIT_OBJECT_0:
				return 0;

			case WAIT_TIMEOUT:
				break;

			case WAIT_FAILED:
				break;
		}

		pPhilosopher->think();
		pPhilosopher->takeForks();
		pPhilosopher->eat();
		pPhilosopher->putForks();
	}
	return 0;
}
