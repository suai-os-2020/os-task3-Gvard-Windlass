#include "lab3.h"
#include <windows.h>
#include <iostream>

#define NUMBER_OF_THREADS 14

DWORD ThreadID;
// thread identifiers
HANDLE hThread[NUMBER_OF_THREADS];
// critical section lock
HANDLE hLock;
// semaphores
HANDLE hSemG, hSemK, hSemM, hSemN, hSemInterval, hSemContinue;

unsigned int lab3_thread_graph_id()
{
    return 20;
}

const char *lab3_unsynchronized_threads()
{
    return "bcf";
}

const char *lab3_sequential_threads()
{
    return "gkmn";
}

DWORD WINAPI thread_a(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 1
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "a" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_b(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 2
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "b" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_c(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 2
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 3
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "c" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_f(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 2
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 3
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 4
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "f" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_d(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 3
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "d" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_e(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 3
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "e" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 4
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "e" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 5
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "e" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_g(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 3
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 4
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 5
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 6 (sequential)
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hSemG, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemK, 1, NULL);
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 7
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "g" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_h(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 4
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "h" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_r(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 4
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "r" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 5
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "r" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_i(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 5
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "i" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_m(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 5
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "m" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 6
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hSemM, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "m" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemN, 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_n(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 5
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "n" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 6
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hSemN, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "n" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemG, 1, NULL);
    }

    ReleaseSemaphore(hSemInterval, 1, NULL);
    WaitForSingleObject(hSemContinue, INFINITE);

    // interval 7
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "n" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

DWORD WINAPI thread_k(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 6
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hSemK, INFINITE);
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "k" << std::flush;
        ReleaseMutex(hLock);
        computation();
        ReleaseSemaphore(hSemM, 1, NULL);
    }
    return 0;
}

DWORD WINAPI thread_p(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    // interval 7
    for (int i=0; i<3; i++)
    {
        WaitForSingleObject(hLock, INFINITE);
        std::cout << "p" << std::flush;
        ReleaseMutex(hLock);
        computation();
    }
    return 0;
}

int mutex_init()
{
    hLock = CreateMutex(NULL, FALSE, NULL);
    if (hLock == NULL)
    {
        std::cerr << "Mutex init failed" << std::endl;
        return 1;
    }
    return 0;
}

void semaphore_init()
{
    hSemG = CreateSemaphore(NULL, 1, 1, NULL);
    hSemK = CreateSemaphore(NULL, 0, 1, NULL);
    hSemM = CreateSemaphore(NULL, 0, 1, NULL);
    hSemN = CreateSemaphore(NULL, 0, 1, NULL);
    hSemInterval = CreateSemaphore(NULL, 0, 3, NULL);
    hSemContinue = CreateSemaphore(NULL, 0, 3, NULL);
}

int graph_flow()
{
    //***************************************interval 1*************************************//
    // start thread A
    hThread[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &ThreadID);
    if (hThread[0] == NULL)
    {
        std::cerr << "Can't create thread A. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // wait thread A to finish
    WaitForSingleObject(hThread[0], INFINITE);


    //***************************************interval 2*************************************//

    // start threads B, C, F
    hThread[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &ThreadID);
    if (hThread[1] == NULL)
    {
        std::cerr << "Can't create thread B. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &ThreadID);
    if (hThread[2] == NULL)
    {
        std::cerr << "Can't create thread C. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &ThreadID);
    if (hThread[5] == NULL)
    {
        std::cerr << "Can't create thread F. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // wait thread B to finish
    WaitForSingleObject(hThread[1], INFINITE);
    // wait C, F
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);


    //***************************************interval 3*************************************//
    // start D, E, G
    hThread[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &ThreadID);
    if (hThread[3] == NULL)
    {
        std::cerr << "Can't create thread D. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &ThreadID);
    if (hThread[4] == NULL)
    {
        std::cerr << "Can't create thread E. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &ThreadID);
    if (hThread[6] == NULL)
    {
        std::cerr << "Can't create thread G. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // continue C, F
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);

    // wait C, D to finish
    WaitForSingleObject(hThread[2], INFINITE);
    WaitForSingleObject(hThread[3], INFINITE);
    // wait E, F, G
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);


    //***************************************interval 4*************************************//
    // start H, R
    hThread[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &ThreadID);
    if (hThread[7] == NULL)
    {
        std::cerr << "Can't create thread H. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[13] = CreateThread(NULL, 0, thread_r, NULL, 0, &ThreadID);
    if (hThread[13] == NULL)
    {
        std::cerr << "Can't create thread R. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // continue E, F, G
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);

    // wait F, H to finish
    WaitForSingleObject(hThread[5], INFINITE);
    WaitForSingleObject(hThread[7], INFINITE);
    // wait E, G, R
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);


    //***************************************interval 5*************************************//
    // start I, M, N
    hThread[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &ThreadID);
    if (hThread[8] == NULL)
    {
        std::cerr << "Can't create thread I. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[10] = CreateThread(NULL, 0, thread_m, NULL, 0, &ThreadID);
    if (hThread[10] == NULL)
    {
        std::cerr << "Can't create thread M. Error: " << GetLastError() << std::endl;
        return 1;
    }
    hThread[11] = CreateThread(NULL, 0, thread_n, NULL, 0, &ThreadID);
    if (hThread[11] == NULL)
    {
        std::cerr << "Can't create thread N. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // continue E, G, R
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);

    // wait E, I, R to finish
    WaitForSingleObject(hThread[4], INFINITE);
    WaitForSingleObject(hThread[8], INFINITE);
    WaitForSingleObject(hThread[13], INFINITE);

    // wait G, M, N
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);


    //***************************************interval 6*************************************//
    // start K
    hThread[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &ThreadID);
    if (hThread[9] == NULL)
    {
        std::cerr << "Can't create thread K. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // continue G, M, N
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);

    // wait K, M to finish
    WaitForSingleObject(hThread[9], INFINITE);
    WaitForSingleObject(hThread[10], INFINITE);
    // wit G, N
    WaitForSingleObject(hSemInterval, INFINITE);
    WaitForSingleObject(hSemInterval, INFINITE);


    //***************************************interval 7*************************************//
    // start p
    hThread[12] = CreateThread(NULL, 0, thread_p, NULL, 0, &ThreadID);
    if (hThread[12] == NULL)
    {
        std::cerr << "Can't create thread P. Error: " << GetLastError() << std::endl;
        return 1;
    }

    // continue G, N
    ReleaseSemaphore(hSemContinue, 1, NULL);
    ReleaseSemaphore(hSemContinue, 1, NULL);

    // wait G, N, P to finish
    WaitForSingleObject(hThread[6], INFINITE);
    WaitForSingleObject(hThread[11], INFINITE);
    WaitForSingleObject(hThread[12], INFINITE);

    return 0;
}

void free_resources()
{
    for (int i = 0; i < NUMBER_OF_THREADS; ++i)
        CloseHandle(hThread[i]);

    CloseHandle(hLock);

    CloseHandle(hSemG);
    CloseHandle(hSemK);
    CloseHandle(hSemM);
    CloseHandle(hSemN);
    CloseHandle(hSemInterval);
    CloseHandle(hSemContinue);
}

int lab3_init()
{
    mutex_init();
    semaphore_init();
    graph_flow();
    free_resources();
    
    return 0;
}