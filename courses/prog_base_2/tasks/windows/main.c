#include <windows.h>
#include <CommCtrl.h>

enum {
    STATIC_ID,
    STATIC_ID_NAME,
    STATIC_ID_SURNAME,
    STATIC_ID_BIRTHDATE,
    STATIC_ID_YEAR,
    STATIC_ID_SCORE,
    ID_ST,
    ID_TIMER,
};

typedef struct musician_s
{
    char name [30];
    char surname [30];
    char birthdate [10];
    int year;
    double score;
} musician_t;

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HINSTANCE hInst);

int WINAPI WinMain(
                   HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow
                  )
{
    const char g_szClassName[] = "myWindowClass";
    HINSTANCE hInst = hInstance;
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "The musicians",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500, 400,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, HINSTANCE hInst) {
    static HWND hMusicians, hNForm, hName, hSNForm, hSurname, hBForm, hBirthdate, hYForm, hYear, hSForm, hScore, hIForm, hTForm, hIndex, hTimer;
    musician_t mus[3] =
    {
        {"Viktor", "Coj", "1962-06-21", 1990, 5.0},
        {"Freddie", "Mercury", "1946-09-05", 1991, 5.0},
        {"Michael", "Jackson", "1958-08-29", 2009, 4.9}
    };
    static int time = 0;
    switch(msg)
    {
        case WM_CREATE:
            {
                hMusicians = CreateWindowEx(0,
                              WC_BUTTON,
                              "Musicians",
                              WS_CHILD | WS_VISIBLE  | BS_GROUPBOX | WS_GROUP,
                              15, 15, 200, 320,
                              hwnd, NULL, hInst, NULL);
                hNForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Name:",
                                WS_CHILD | WS_VISIBLE,
                                20, 25, 70, 15,
                                hMusicians, NULL, hInst, NULL);

                hSNForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Surname:",
                                WS_CHILD | WS_VISIBLE,
                                20, 75, 70, 15,
                                hMusicians, NULL, hInst, NULL);

                hBForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Birthdate:",
                                WS_CHILD | WS_VISIBLE,
                                20, 125, 70, 15,
                                hMusicians, NULL, hInst, NULL);

                hYForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Year of death:",
                                WS_CHILD | WS_VISIBLE,
                                20, 175, 120, 15,
                                hMusicians, NULL, hInst, NULL);

                hSForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Score:",
                                WS_CHILD | WS_VISIBLE,
                                20, 225, 70, 15,
                                hMusicians, NULL, hInst, NULL);

                hIForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Index:",
                                WS_CHILD | WS_VISIBLE,
                                20, 275, 70, 15,
                                hMusicians, NULL, hInst, NULL);

                hTForm = CreateWindowEx(0,
                                WC_STATIC,
                                "Time:",
                                WS_CHILD | WS_VISIBLE,
                                270, 235, 40, 15,
                                hwnd, NULL, hInst, NULL);

                hName = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                20, 45, 120, 15,
                                hMusicians, 1, hInst, NULL);

                hSurname = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                20, 95, 120, 15,
                                hMusicians, 2, hInst, NULL);

                hBirthdate = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                20, 145, 120, 15,
                                hMusicians, 3, hInst, NULL);

                hYear = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                20, 195, 120, 15,
                                hMusicians, 4, hInst, NULL);

                hScore = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                20, 245, 120, 15,
                                hMusicians, 5, hInst, NULL);

                hIndex = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                20, 295, 120, 15,
                                hMusicians, 0, hInst, NULL);

                hTimer = CreateWindowEx(0,
                                WC_STATIC,
                                "",
                                WS_CHILD | WS_VISIBLE,
                                320, 235, 30, 15,
                                hwnd, 0, hInst, NULL);

                CreateWindowW(L"Button", L"Timer",
                                WS_VISIBLE | WS_CHILD | BS_CHECKBOX | BS_AUTOCHECKBOX,
                                270, 270, 60, 15,
                                hwnd, 6, NULL, NULL);

                CheckDlgButton(hwnd, 6, BST_CHECKED);
                int setter = SetTimer(hwnd, 7, 1000, NULL);
                if(setter == 0)
                      MessageBox(hwnd, "Problem with Timer!", "Error!", MB_OK | MB_ICONEXCLAMATION);
                break;
    }
    case WM_TIMER:
    {
        if (IsDlgButtonChecked(hwnd, 6))
        {
            char year[4] = "";
            char score[3] = "";
            char index[1] = "";
            char timeL[5] = "";
            SetWindowText(hName, mus[time%3].name);
            SetWindowText(hSurname, mus[time%3].surname);
            SetWindowText(hBirthdate, mus[time%3].birthdate);
            sprintf(year, "%i", mus[time%3].year);
            SetWindowText(hYear, TEXT(year));
            sprintf(score, "%.1f", mus[time%3].score);
            SetWindowText(hScore, TEXT(score));
            sprintf(index, "%i", time%3);
            SetWindowText(hIndex, TEXT(index));
            time++;
            sprintf(timeL, "%i", time);
            SetWindowText(hTimer, TEXT(timeL));
        }
        break;
    }
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
