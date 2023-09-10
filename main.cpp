#include <windows.h>
#include <stdlib.h>

#include "menuitems.h"

#define BST_UNCHECKED       0x0000
#define BST_CHECKED         0x0001

#define ID_PRZYCISK1    501
#define ID_PRZYCISK2    502
#define ID_CHECKBOX     503
#define ID_LISTBOX      504
#define ID_PRZYCISK3    505
#define ID_EDITBOX      506
#define ID_LISTBOX2     507

HWND hText;
HWND hListBox, hListBox2;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // MessageBox(NULL,"Fender!","Test",MB_ICONINFORMATION | MB_OK);

    WNDCLASS wc;
    LPSTR NazwaKlasy = "Klasa Okienka";

    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;

    if(!RegisterClass(&wc))
    {
        MessageBox(NULL,"Nie uda³o siê utworzyæ okna.","B³¹d",MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(200));

    HWND hwnd;

    hwnd = CreateWindow(NazwaKlasy, "Oto okienko", WS_OVERLAPPEDWINDOW, 20, 20, 640, 480,
                        NULL, hMenu, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL,"Nie uda³o siê wyœwietliæ okna.","B³¹d",MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    HWND hPrzycisk, hPrzycisk2, hPrzycisk3;
    HWND hCheckBox;
    HWND hStatic;
    
    hPrzycisk = CreateWindow("BUTTON", "Wyœwietl tekst", WS_CHILD | WS_VISIBLE, 160, 5, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

    hPrzycisk2 =CreateWindow("BUTTON", "Wyœwietl stan", WS_CHILD | WS_VISIBLE, 160, 35, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);

    hPrzycisk3 =CreateWindow("BUTTON", "Wyœwietl wybrany", WS_CHILD | WS_VISIBLE, 160, 65, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK3, hInstance, NULL);

    hText = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_MULTILINE | ES_AUTOVSCROLL,
                         5, 5, 150, 150, hwnd, (HMENU)ID_EDITBOX, hInstance, NULL);

    hCheckBox = CreateWindow("BUTTON", "Opcja", WS_CHILD | WS_VISIBLE | BS_CHECKBOX, 5, 165, 150, 30,
                             hwnd, (HMENU)ID_CHECKBOX, hInstance, NULL);

    hStatic = CreateWindow("STATIC", "Test", WS_CHILD | WS_VISIBLE | SS_LEFT, 5, 195, 150, 205, hwnd, NULL, hInstance, NULL);

    hListBox = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_AUTOVSCROLL | LBS_NOTIFY,
                            320, 5, 150, 150, hwnd, (HMENU)ID_LISTBOX, hInstance, NULL);

    hListBox2 =CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | ES_AUTOVSCROLL | LBS_NOTIFY,
                            320, 155, 150, 150, hwnd, (HMENU)ID_LISTBOX2, hInstance, NULL);

    SetWindowText(hStatic, "Test 2");

    for(unsigned long int x=0; x<65537; ++x)
    {
        char test[10];
        ltoa(x,test,10);
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) test);
    }

    SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM) "xD");

    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    MSG Komunikat;

    while(GetMessage(&Komunikat, NULL, 0, 0 ))
    {
        TranslateMessage(&Komunikat);
        DispatchMessage(&Komunikat);
    }
    
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_COMMAND:
            switch(wParam)
            {
                case ID_PLIK_ZAKONCZ:
                    PostQuitMessage(0);
                    break;
                case ID_PRZYCISK1:
                    // Odczyt danych z pola tekstowego
                    DWORD dlugosc = GetWindowTextLength(hText);
                    LPSTR Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc+1);
                    GetWindowText(hText,Bufor,dlugosc+1);
                    MessageBox(hwnd,Bufor,"Pobrany tekst",MB_OK);
                    GlobalFree((unsigned)Bufor);
                    break;
                case ID_PRZYCISK2:
                    if(IsDlgButtonChecked(hwnd, ID_CHECKBOX))
                    {
                        MessageBox(hwnd,"Zaznaczony!","Stan",MB_ICONINFORMATION);
                    }
                    else
                    {
                        MessageBox(hwnd,"Niezaznaczony!","Stan",MB_ICONINFORMATION);
                    }
                    break;
                case ID_CHECKBOX:
                    if(IsDlgButtonChecked(hwnd, ID_CHECKBOX))
                    {
                        CheckDlgButton(hwnd, ID_CHECKBOX, BST_UNCHECKED); // = 0
                    }
                    else
                    {
                        CheckDlgButton(hwnd, ID_CHECKBOX, BST_CHECKED); // = 1
                    }
                    break;
                case ID_PRZYCISK3:
                    long int index=SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                    char test[10];
                    ltoa(index,test,10);
                    MessageBox(hwnd,test,"Wartoœæ",MB_OK);
                    break;
                case ID_LISTBOX:
                    if(HIWORD(lParam)==LBN_DBLCLK)
                    {
                        long int index=SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                        char test[10];
                        ltoa(index,test,10);
                        MessageBox(hwnd,test,"Wartoœæ",MB_OK);
                    }
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return 0;
}
