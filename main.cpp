#include <windows.h>
#include <olenls.h>
#include <ctl3d.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <map>

#include "resources.h"

#define BST_UNCHECKED       0x0000
#define BST_CHECKED         0x0001

#define ID_BUTTON1          501
#define ID_BUTTON2          502
#define ID_CHECKBOX         503
#define ID_LISTBOX          504
#define ID_BUTTON3          505
#define ID_EDITBOX          506
#define ID_LISTBOX2         507
#define ID_BUTTON4          508
#define ID_COMBOBOX         509
#define ID_EDITBOX2         510
#define ID_BUTTON5          511
#define ID_BUTTON6          512
#define ID_STATIC           513
#define ID_STATIC2          514
#define ID_BUTTON7          515
#define ID_BUTTON8          516
#define ID_BUTTON9          517
#define ID_BUTTON10         518

LPSTR ClassName2 = "Klasa Okienka 2";

char buffer[65536];

typedef struct secondWindow {
    HWND hwnd;
    HWND hButton, hButton2;
    unsigned long int id;
} SECONDWINDOW;

typedef std::map<HWND,SECONDWINDOW*> WINDOWMEMORY;

HBRUSH g_hBrush = CreateSolidBrush(GetSysColor(COLOR_WINDOW));

WINDOWMEMORY winMem;

//HHOOK hMyHook=NULL;
// FARPROC proc=NULL;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
// BOOL _export FAR PASCAL DlgProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc2(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
// LRESULT CALLBACK ReturnProc(int, WPARAM, LPARAM);

HWND createSecondWindow(HWND hwnd, WINDOWMEMORY &winMem, unsigned long int id) {
    SECONDWINDOW *secWin=new SECONDWINDOW;

    HINSTANCE hInstance=(HINSTANCE)GetWindowWord(hwnd,GWW_HINSTANCE);

    secWin->hwnd = CreateWindow(ClassName2, "Oto okienko 2", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
                                NULL, NULL, hInstance, NULL);

    if(secWin->hwnd==NULL) {
        delete secWin;
        return NULL;
    }
    else {
        winMem[secWin->hwnd]=secWin;
        secWin->id=id;
        
        secWin->hButton =CreateWindow("BUTTON", "Test", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 5, 150, 30,
                                        secWin->hwnd, (HMENU)ID_BUTTON5, hInstance, NULL);

        secWin->hButton2=CreateWindow("BUTTON", "Test 2", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 35, 150, 30,
                                        secWin->hwnd, (HMENU)ID_BUTTON6, hInstance, NULL);

        ShowWindow(secWin->hwnd,SW_SHOW);
        UpdateWindow(secWin->hwnd);

        return secWin->hwnd;
    }
}

void deleteWindow(WINDOWMEMORY &winMem, HWND hwnd) {
    delete winMem[hwnd];
    winMem.erase(hwnd);
    return;
}

void ShowInteger(long int integer) {
    char test[20];
    ltoa(integer,test,10);
    MessageBox(0,test,"ShowInteger",MB_OK);
    return;
}

long int inline MakeDialogBox(HWND hwnd, unsigned int type, void* procedure) {
    long int result;
    HANDLE instHandle=(HINSTANCE)GetWindowWord(hwnd,GWW_HINSTANCE);
    FARPROC proc=MakeProcInstance((FARPROC)procedure, instHandle);
    result=DialogBox(instHandle, MAKEINTRESOURCE(type), hwnd, (DLGPROC)proc);
    FreeProcInstance(proc);
    return result;
}
/*
HHOOK inline MakeSetWindowsHook(HWND hwnd, FARPROC &proc, int hookType, void* procedure) {
    HANDLE instHandle=(HINSTANCE)GetWindowWord(hwnd,GWW_HINSTANCE);
    proc=MakeProcInstance((FARPROC)procedure, instHandle);
    return (HHOOK)(int)SetWindowsHook(hookType, (HOOKPROC)proc);
}
*/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // MessageBox(NULL,"Fender!","Test",MB_ICONINFORMATION | MB_OK);

    WNDCLASS wc = { 0 };
    LPSTR ClassName = "Klasa Okienka";

    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    // wc.hIcon = LoadIcon(NULL, IDI_HAND); // some funny joke ;-)
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hbrBackground = g_hBrush;
    wc.lpszMenuName = /*NULL*/ MAKEINTRESOURCE(IDR_MENU1);
    wc.lpszClassName = ClassName;

    if(!RegisterClass(&wc)) {
        MessageBox(NULL,"Nie uda³o siê utworzyæ klasy okna.","B³¹d",MB_ICONSTOP | MB_OK);
        return 1;
    }

    //HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));

    // FIRST WINDOW

    HWND hwnd;

    hwnd = CreateWindow(ClassName, "Oto okienko", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
                        NULL, /*hMenu*/NULL, hInstance, NULL);

    if(hwnd == NULL) {
        MessageBox(NULL,"Nie uda³o siê wyœwietliæ okna.","B³¹d",MB_ICONSTOP | MB_OK);
        return 1;
    }

    HWND hButton, hButton2, hButton3, hButton4, hButton9, hButton10, hButton11, hButton12;
    HWND hCheckBox;
    HWND hStatic, hStatic2;
    HWND hText, hText2;
    HWND hListBox, hListBox2;
    HWND hCombo;

    hButton = CreateWindow("BUTTON", "Wyœwietl tekst", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 5, 150, 30,
                             hwnd, (HMENU)ID_BUTTON1, hInstance, NULL);

    hButton2 =CreateWindow("BUTTON", "Wyœwietl stan", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 35, 150, 30,
                             hwnd, (HMENU)ID_BUTTON2, hInstance, NULL);

    hButton3 =CreateWindow("BUTTON", "Wyœwietl wybrany", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 65, 150, 30,
                             hwnd, (HMENU)ID_BUTTON3, hInstance, NULL);

    hButton4 =CreateWindow("BUTTON", "Testowy", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 95, 150, 30,
                             hwnd, (HMENU)ID_BUTTON4, hInstance, NULL);

    hButton9 =CreateWindow("BUTTON", "Utwórz okno", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 125, 150, 30,
                             hwnd, (HMENU)ID_BUTTON7, hInstance, NULL);

    hButton10=CreateWindow("BUTTON", "Test 2", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 155, 150, 30,
                             hwnd, (HMENU)ID_BUTTON8, hInstance, NULL);

    hButton11=CreateWindow("BUTTON", "Test 3", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 185, 150, 30,
                             hwnd, (HMENU)ID_BUTTON9, hInstance, NULL);

    hButton12=CreateWindow("BUTTON", "Test 4", WS_CHILD | WS_VISIBLE | WS_TABSTOP, 160, 215, 150, 30,
                             hwnd, (HMENU)ID_BUTTON10, hInstance, NULL);

    hText = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_MULTILINE | ES_AUTOVSCROLL | ES_WANTRETURN,
                         5, 5, 150, 150, hwnd, (HMENU)ID_EDITBOX, hInstance, NULL);

    hCheckBox = CreateWindow("BUTTON", "Opcja", WS_CHILD | WS_VISIBLE | WS_TABSTOP | BS_CHECKBOX, 5, 165, 150, 30,
                             hwnd, (HMENU)ID_CHECKBOX, hInstance, NULL);

    hStatic = CreateWindow("STATIC", "Test", WS_CHILD | WS_VISIBLE | SS_LEFT, 5, 195, 150, 16, hwnd, (HMENU)ID_STATIC, hInstance, NULL);

    hListBox = CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_AUTOVSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
                            320, 5, 150, 150, hwnd, (HMENU)ID_LISTBOX, hInstance, NULL);

    SetWindowPos(hListBox,NULL,320,5,150,150,SWP_NOZORDER);

    hListBox2 =CreateWindow("LISTBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_TABSTOP | ES_AUTOVSCROLL | LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
                            320, 155, 150, 150, hwnd, (HMENU)ID_LISTBOX2, hInstance, NULL);

    SetWindowPos(hListBox2,NULL,320,155,150,150,SWP_NOZORDER);

    hStatic2 =CreateWindow("STATIC", "0", WS_CHILD | WS_VISIBLE | SS_LEFT, 480, 5, 150, 16, hwnd, (HMENU)ID_STATIC2, hInstance, NULL);

    hText2 =CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | ES_PASSWORD | ES_AUTOHSCROLL,
                         320, 310, 150, 24, hwnd, (HMENU)ID_EDITBOX2, hInstance, NULL);

    hCombo =CreateWindow("COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP | CBS_DROPDOWNLIST | CBS_HASSTRINGS,
                         320, 344, 150, 124, hwnd, (HMENU)ID_COMBOBOX, hInstance, NULL);

    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Test 1");
    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) "Test 2");

    std::string testString="Eksperyment";

    SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)testString.c_str());

    SendMessage(hText2, EM_SETPASSWORDCHAR, 0x95, 0);

    if(Ctl3dRegister(hInstance) && Ctl3dEnabled()) {
        //unsigned int ctlRegs=(CTL3D_ALL) & ~(CTL3D_BUTTONS);
        unsigned int ctlRegs=CTL3D_ALL;
        Ctl3dSubclassDlg(hwnd,ctlRegs);
        
        /*
        Ctl3dSubclassCtl(hButton);
        Ctl3dSubclassCtl(hButton2);
        Ctl3dSubclassCtl(hButton3);
        
        Ctl3dSubclassCtl(hText);
        Ctl3dSubclassCtl(hCheckBox);
        Ctl3dSubclassCtl(hListBox);
        Ctl3dSubclassCtl(hListBox2);
        Ctl3dSubclassCtl(hText2);
        */
        //Ctl3dAutoSubclass(hInstance);
    }
    else {
        MessageBox(hwnd,"Zarejestrowanie CTL3D nie powiod³o siê!","Ostrze¿enie",MB_ICONEXCLAMATION);
    }

    SetWindowText(hStatic, "Test 2");

    for(unsigned long int x=0; x<65536; ++x) {
        char test[10];
        ltoa(x,test,10);
        SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM) test);
    }

    SendMessage(hListBox2, LB_ADDSTRING, 0, (LPARAM) "xD");

    // hMyHook=MakeSetWindowsHook(hwnd,proc,WH_KEYBOARD,ReturnProc);

    ShowWindow(hwnd,nCmdShow);
    UpdateWindow(hwnd);

    // FIRST WINDOW ^^^

    HACCEL hAccel=LoadAccelerators(hInstance, MAKEINTRESOURCE(IDR_ACCELERATORS));
    if(!hAccel) {
        MessageBox(0,"Nie uda³o siê za³adowaæ akceleratorów!","B³¹d",0);
    }

    WNDCLASS wc2 = { 0 };

    wc2.style = 0;
    wc2.lpfnWndProc = WndProc2;
    wc2.cbClsExtra = 0;
    wc2.cbWndExtra = 0;
    wc2.hInstance = hInstance;
    // wc2.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    wc2.hIcon = LoadIcon(NULL, IDI_EXCLAMATION); // some funny joke ;-)
    wc2.hCursor = LoadCursor(NULL, IDC_ARROW);
    // wc2.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc2.hbrBackground = g_hBrush;
    wc2.lpszMenuName = NULL;
    wc2.lpszClassName = ClassName2;

    if(!RegisterClass(&wc2)) {
        MessageBox(NULL,"Nie uda³o siê utworzyæ klasy okna.","B³¹d",MB_ICONSTOP | MB_OK);
        return 1;
    }

    MSG Message;

    while(GetMessage(&Message, NULL, 0, 0 )) {
        HWND temp=GetParent(Message.hwnd);
        if(temp==NULL) {
            temp=Message.hwnd;
        }
        if(!TranslateAccelerator(temp, hAccel, &Message)) {
            TranslateMessage(&Message);
            DispatchMessage(&Message);
        }
    }
    
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CTLCOLOR:
            switch(HIWORD(lParam)) {
                /*
                case CTLCOLOR_STATIC:
                    HWND hCtl = (HWND)LOWORD(lParam);
                    HDC hDC = (HDC)wParam;
                    if(hCtl == hStatic2) {
                        SetBkMode(hDC, TRANSPARENT);
                        return (LRESULT) g_hBrush;
                    }
                    
                    break;
                */
                case CTLCOLOR_STATIC:
                    SetBkMode((HDC)wParam, TRANSPARENT);
                    return g_hBrush;
                    // break;
                case CTLCOLOR_BTN:
                    SetBkMode((HDC)wParam, TRANSPARENT);
                    break;
            }
            break;
        case WM_COMMAND:
            switch(wParam) {
                case ID_ACC_TAB:
                    /*
                    char testClass[5];
                    GetClassName(GetFocus(),testClass,5);
                    if(strcasecmp(testClass,"EDIT")==0)
                    */
                    //MessageBox(0,"","",0);
                    if(GetFocus()==GetDlgItem(hwnd,ID_EDITBOX)) {
                        SendMessage(GetFocus(), WM_CHAR, VK_TAB, 0);
                    }
                    else {
                        SetFocus(GetNextDlgTabItem(hwnd,GetFocus(),false));
                    }
                    break;
                case ID_ACC_ALTF4:
                    SendMessage(hwnd, WM_CLOSE, 0, 0);
                    break;
                case ID_ACC_F1:
                    MakeDialogBox(hwnd,IDD_DIALOG1,DlgProc);
                    break;
                case ID_FILE_EXIT:
                    DestroyWindow(hwnd);
                    break;
                case ID_HELP_ABOUT:
                    MakeDialogBox(hwnd,IDD_DIALOG1,DlgProc);
                    break;
                case ID_BUTTON1:
                    // Reading data from edit box
                    DWORD length = GetWindowTextLength(GetDlgItem(hwnd,ID_EDITBOX));
                    LPSTR addBuffer = (LPSTR)GlobalAlloc(GPTR, length+1);
                    //GetWindowText(hText,addBuffer,length+1);
                    GetWindowText(GetDlgItem(hwnd,ID_EDITBOX),addBuffer,length+1);
                    MessageBox(hwnd,addBuffer,"Pobrany tekst",MB_OK);
                    GlobalFree((unsigned)addBuffer);
                    break;
                case ID_BUTTON2:
                    if(IsDlgButtonChecked(hwnd, ID_CHECKBOX)) {
                        MessageBox(hwnd,"Zaznaczony!","Stan",MB_ICONINFORMATION);
                    }
                    else {
                        MessageBox(hwnd,"Niezaznaczony!","Stan",MB_ICONINFORMATION);
                    }
                    break;
                case ID_CHECKBOX:
                    if(IsDlgButtonChecked(hwnd, ID_CHECKBOX)) {
                        CheckDlgButton(hwnd, ID_CHECKBOX, BST_UNCHECKED); // = 0
                    }
                    else {
                        CheckDlgButton(hwnd, ID_CHECKBOX, BST_CHECKED); // = 1
                    }
                    break;
                case ID_BUTTON3:
                    long int index=SendMessage(GetDlgItem(hwnd,ID_LISTBOX), LB_GETCURSEL, 0, 0);
                    char test[10];
                    ltoa(index,test,10);
                    MessageBox(hwnd,test,"Wartoœæ",MB_OK);
                    break;
                case ID_LISTBOX:
                    if(HIWORD(lParam)==LBN_DBLCLK) {
                        long int index=SendMessage(GetDlgItem(hwnd,ID_LISTBOX), LB_GETCURSEL, 0, 0);
                        char test[10];
                        ltoa(index,test,10);
                        MessageBox(hwnd,test,"Wartoœæ",MB_OK);
                        // ShowInteger(index);
                    }
                    if(HIWORD(lParam)==LBN_SELCHANGE) {
                        long int index=SendMessage(GetDlgItem(hwnd,ID_LISTBOX), LB_GETCURSEL, 0, 0);
                        char test[10];
                        ltoa(index,test,10);
                        SetWindowText(GetDlgItem(hwnd,ID_STATIC2),test);
                        // MessageBox(hwnd,test,"Wartoœæ",MB_OK);
                    }
                    break;
                case ID_BUTTON4:
                    ShowInteger(MakeDialogBox(hwnd,IDD_DIALOG1,DlgProc));
                    break;
                case ID_BUTTON7:
                    createSecondWindow(hwnd,winMem,0);
                    break;
                case ID_BUTTON8:
                    HINSTANCE hInstance = GetWindowWord(hwnd,GWW_HINSTANCE);
                    HGLOBAL hMem = LoadResource(hInstance,FindResource(hInstance,MAKEINTRESOURCE(IDR_RCDATA1),RT_RCDATA));
                    /*
                        // may be like that:
                        void *lpData = LockResource(hMem);
                        WORD *test2 = (WORD*)lpData;
                    */
                    WORD *test2 = (WORD*)LockResource(hMem);
                    char test3[256];
                    unsigned int x=0;
                    while(test2[x]) {
                        test3[x]=(char)test2[x];
                        ++x;
                    }
                    test3[x]=0;
                    MessageBox(hwnd,(const char*)test3,"Test 2",MB_OK);
                    UnlockResource(hMem);
                    FreeResource(hMem);
                    break;
                case ID_BUTTON9:
                    char test4[256];
                    if(GetLocaleInfoA(LOCALE_USER_DEFAULT,LOCALE_IDEFAULTANSICODEPAGE,test4,256)) {
                        MessageBox(hwnd,(const char*)test4,"Test 3",MB_OK);
                    }
                    if(GetLocaleInfoA(LOCALE_USER_DEFAULT,LOCALE_SABBREVLANGNAME,test4,256)) {
                        MessageBox(hwnd,(const char*)test4,"Test 3",MB_OK);
                    }
                    break;
                case ID_BUTTON10:
                    char test5[256];
                    HINSTANCE hInstance2=GetWindowWord(hwnd,GWW_HINSTANCE);
                    if(LoadString(hInstance2,IDS_STRING1,test5,256)) {
                        MessageBox(hwnd,(const char*)test5,"Test 4",MB_OK);
                    }
                    if(LoadString(hInstance2,IDS_STRING2,test5,256)) {
                        MessageBox(hwnd,(const char*)test5,"Test 4",MB_OK);
                    }
                    if(LoadString(hInstance2,IDS_STRING3,test5,256)) {
                        MessageBox(hwnd,(const char*)test5,"Test 4",MB_OK);
                    }
                    break;
            }
            break;
            
        case WM_SIZE:
            unsigned long int width= LOWORD(lParam);
            unsigned long int height=HIWORD(lParam);
            
            SetWindowPos(GetDlgItem(hwnd,ID_LISTBOX),NULL,0,0,width-482,height-276,SWP_NOMOVE | SWP_NOZORDER);
            
            break;
            
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            if(Ctl3dEnabled() && (!Ctl3dUnregister(GetWindowWord(hwnd,GWW_HINSTANCE)))) {
                MessageBox(0,"Wyrejestrowanie aplikacji z CTL3D nie powiod³o siê!","Ostrze¿enie",MB_ICONEXCLAMATION);
            }
            /*
            if(hMyHook!=NULL) {
                MessageBox(0,"Hook","",0);
                if(UnhookWindowsHook(WH_KEYBOARD, proc)) {
                    MessageBox(0,"Unhook OK :)","",0);
                }
            }
            if(proc!=NULL) {
                MessageBox(0,"Proc","",0);
                FreeProcInstance(proc);
            }
            */
            DeleteObject(g_hBrush);
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return 0;
}

LRESULT CALLBACK WndProc2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_COMMAND:
            switch(wParam) {
                case ID_ACC_TAB:
                    SetFocus(GetNextDlgTabItem(hwnd,GetFocus(),false));
                    break;
                case ID_BUTTON5:
                    //ShowInteger(hwnd);
                    SetWindowText(GetDlgItem(hwnd,ID_BUTTON5),"Pyk 1");
                    break;
                case ID_BUTTON6:
                    //ShowInteger(hwnd);
                    SetWindowText(GetDlgItem(hwnd,ID_BUTTON6),"Pyk 2");
                    break;
            }
            break;
        case WM_DESTROY:
            deleteWindow(winMem,hwnd);
            break;
        default:
            return DefWindowProc(hwnd,msg,wParam,lParam);
    }
    return 0;
}

// BOOL _export FAR PASCAL DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
BOOL CALLBACK DlgProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        case WM_INITDIALOG:
            if(Ctl3dEnabled()) {
                unsigned int ctlRegs=CTL3D_ALL;
                Ctl3dSubclassDlg(hwnd,ctlRegs);
            }
            break;
        case WM_CTLCOLOR:
            switch(HIWORD(lParam)) {
                case CTLCOLOR_BTN:
                    SetBkMode((HDC)wParam, TRANSPARENT);
                    break;
            }
            break;
        case WM_COMMAND:
            switch(wParam) {
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
/*
LRESULT CALLBACK ReturnProc(int code, WPARAM wParam, LPARAM lParam) {
    if(code<0) {
        return CallNextHookEx(0,code,wParam,lParam);
    }
    else {
        if(wParam == VK_RETURN) {
            MessageBox(0,"Enter!","",0);
        }
    }
    return CallNextHookEx(0,code,wParam,lParam);
}
*/
