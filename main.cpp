#include <windows.h>
#include <ctl3d.h>
#include <stdlib.h>
#include <string.h>
#include "stddef.h"

#include "resources.h"

#define BST_UNCHECKED       0x0000
#define BST_CHECKED         0x0001

#define ID_PRZYCISK1    501
#define ID_PRZYCISK2    502
#define ID_CHECKBOX     503
#define ID_LISTBOX      504
#define ID_PRZYCISK3    505
#define ID_EDITBOX      506
#define ID_LISTBOX2     507
#define ID_PRZYCISK4    508
#define ID_COMBOBOX     509
#define ID_EDITBOX2     510

HWND hText, hText2;
HWND hListBox, hListBox2;
HWND hStatic2;
HWND hCombo;

// HBRUSH g_hBrush = CreateSolidBrush(RGB(255,255,0));

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL _export FAR PASCAL DlgProc(HWND, UINT, WPARAM, LPARAM);

void ShowInteger(long int integer)
{
    char test[20];
    ltoa(integer,test,10);
    MessageBox(0,test,"ShowInteger",MB_OK);
    return;
}

long int inline MakeDialogBox(HWND hwnd, unsigned int type, void *x)
{
    HANDLE instHandle=(HINSTANCE)GetWindowWord(hwnd,GWW_HINSTANCE);
    FARPROC proc=MakeProcInstance((FARPROC)x, instHandle);
    return DialogBox(instHandle, MAKEINTRESOURCE(type), hwnd, (DLGPROC)proc);
}

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
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;

    if(!RegisterClass(&wc))
    {
        MessageBox(NULL,"Nie uda³o siê utworzyæ okna.","B³¹d",MB_ICONSTOP | MB_OK);
        return 1;
    }

    HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(200));

    HWND hwnd;

    hwnd = CreateWindow(NazwaKlasy, "Oto okienko", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
                        NULL, hMenu, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL,"Nie uda³o siê wyœwietliæ okna.","B³¹d",MB_ICONSTOP | MB_OK);
        return 1;
    }

    HWND hPrzycisk, hPrzycisk2, hPrzycisk3, hPrzycisk4;
    HWND hCheckBox;
    HWND hStatic;
    
    hPrzycisk = CreateWindow("BUTTON", "Wyœwietl tekst", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 5, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK1, hInstance, NULL);

    hPrzycisk2 =CreateWindow("BUTTON", "Wyœwietl stan", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 35, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK2, hInstance, NULL);

    hPrzycisk3 =CreateWindow("BUTTON", "Wyœwietl wybrany", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 65, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK3, hInstance, NULL);

    hPrzycisk4 =CreateWindow("BUTTON", "Testowy", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 95, 150, 30,
                             hwnd, (HMENU)ID_PRZYCISK4, hInstance, NULL);

    hText = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
                         5, 5, 150, 150, hwnd, (HMENU)ID_EDITBOX, hInstance, NULL);

    hCheckBox = CreateWindow("BUTTON", "Opcja", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, 5, 165, 150, 30,
                             hwnd, (HMENU)ID_CHECKBOX, hInstance, NULL);

    hStatic = CreateWindow("STATIC", "Test", WS_CHILD | WS_VISIBLE | SS_LEFT, 5, 195, 150, 205, hwnd, NULL, hInstance, NULL);

    hListBox = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_AUTOVSCROLL | LBS_NOTIFY,
                            320, 5, 150, 150, hwnd, (HMENU)ID_LISTBOX, hInstance, NULL);

    hListBox2 =CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_AUTOVSCROLL | LBS_NOTIFY,
                            320, 155, 150, 150, hwnd, (HMENU)ID_LISTBOX2, hInstance, NULL);

    hStatic2 =CreateWindow("STATIC", "0", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 5, 150, 205, hwnd, NULL, hInstance, NULL);

    hText2 =CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_PASSWORD | ES_AUTOHSCROLL,
                         320, 310, 150, 24, hwnd, (HMENU)ID_EDITBOX2, hInstance, NULL);

    hCombo =CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                         320, 344, 150, 124, hwnd, (HMENU)ID_COMBOBOX, hInstance, NULL);

    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Test 1");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Test 2");

    SendMessage(hText2, EM_SETPASSWORDCHAR, 0x95, 0);

    if(Ctl3dRegister(hInstance) && Ctl3dEnabled())
    {
        //unsigned int ctlRegs=(CTL3D_ALL) & ~(CTL3D_BUTTONS);
        unsigned int ctlRegs=CTL3D_ALL;
        Ctl3dSubclassDlg(hwnd,ctlRegs);

        HDC hDC=GetWindowDC(hPrzycisk);
        SetBkMode(hDC, TRANSPARENT);
        
        /*
        Ctl3dSubclassCtl(hPrzycisk);
        Ctl3dSubclassCtl(hPrzycisk2);
        Ctl3dSubclassCtl(hPrzycisk3);
        
        Ctl3dSubclassCtl(hText);
        Ctl3dSubclassCtl(hCheckBox);
        Ctl3dSubclassCtl(hListBox);
        Ctl3dSubclassCtl(hListBox2);
        Ctl3dSubclassCtl(hText2);
        */
        //Ctl3dAutoSubclass(hInstance);
    }
    else
    {
        MessageBox(hwnd,"Zarejestrowanie CTL3D nie powiod³o siê!","Ostrze¿enie",MB_ICONEXCLAMATION);
    }

    SetWindowText(hStatic, "Test 2");

    for(unsigned long int x=0; x<65536; ++x)
    {
        char test[10];
        ltoa(x,test,10);
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) test);
    }

    SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM) "xD");

    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    HACCEL hAccel=LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATORS));
    if(!hAccel)
    {
        MessageBox(0,"Nie uda³o siê za³adowaæ akceleratorów!","B³¹d",0);
    }

    MSG Komunikat;

    while(GetMessage(&Komunikat, NULL, 0, 0 ))
    {
        if(!TranslateAccelerator(hwnd, hAccel, &Komunikat))
        {
            TranslateMessage(&Komunikat);
            DispatchMessage(&Komunikat);
        }
    }
    
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CTLCOLOR:
            switch(HIWORD(lParam))
            {
                /*
                case CTLCOLOR_STATIC:
                    HWND hCtl = (HWND)LOWORD(lParam);
                    HDC hDC = (HDC)wParam;
                    if(hCtl == hStatic2)
                    {
                        SetBkMode(hDC, TRANSPARENT);
                        return (LRESULT) g_hBrush;
                    }
                    
                    break;
                */
                case CTLCOLOR_BTN:
                    SetBkMode((HDC)wParam, TRANSPARENT);
                    break;
            }
            break;
        case WM_COMMAND:
            switch(wParam)
            {
                case ID_ACC_TAB:
                    /*
                    char testClass[5];
                    GetClassName(GetFocus(),testClass,5);
                    if(strcasecmp(testClass,"EDIT")==0)
                    */
                    if(GetFocus()==hText)
                    {
                        SendMessage(GetFocus(), WM_CHAR, VK_TAB, 0);
                    }
                    else
                    {
                        SetFocus(GetNextDlgTabItem(hwnd,GetFocus(),false));
                    }
                    break;
                case ID_PLIK_ZAKONCZ:
                    DestroyWindow(hwnd);
                    //PostQuitMessage(0);
                    break;
                case ID_POMOC_O:
                    MakeDialogBox(hwnd,IDD_DIALOG1,DlgProc);
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
                        // ShowInteger(index);
                    }
                    if(HIWORD(lParam)==LBN_SELCHANGE)
                    {
                        long int index=SendMessage(hListBox, LB_GETCURSEL, 0, 0);
                        char test[10];
                        ltoa(index,test,10);
                        SetWindowText(hStatic2,test);
                        // MessageBox(hwnd,test,"Wartoœæ",MB_OK);
                    }
                    break;
                case ID_PRZYCISK4:
                /*
                    HANDLE instHandle=(HINSTANCE)GetWindowWord(hwnd,GWW_HINSTANCE);
                    FARPROC proc=MakeProcInstance((FARPROC)DlgProc, instHandle);
                    int ret=DialogBox(instHandle, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, (DLGPROC)proc);
                    ShowInteger(ret);
                */
                    ShowInteger(MakeDialogBox(hwnd,IDD_DIALOG1,DlgProc));
                    break;
            }
            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            if(Ctl3dEnabled() && (!Ctl3dUnregister(GetWindowWord(hwnd,GWW_HINSTANCE))))
            {
                MessageBox(0,"Wyrejestrowanie aplikacji z CTL3D nie powiod³o siê!","Ostrze¿enie",MB_ICONEXCLAMATION);
            }
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return 0;
}

BOOL _export FAR PASCAL DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_INITDIALOG:
            break;
        case WM_COMMAND:
            switch(wParam)
            {
                case IDOK:
                    EndDialog(hwnd,IDOK);
                    break;
                case IDCANCEL:
                    EndDialog(hwnd,IDCANCEL);
                    break;
            }
            break;
        default:
            return FALSE;
    }
    return TRUE;
}
