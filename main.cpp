
#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    int msgboxID = MessageBoxW(
        NULL,
        (LPCWSTR)L"Ressources not available !\nDo you want to try again !", 
        (LPCWSTR)L"Account Details", MB_ICONWARNING | MB_OKCANCEL | MB_DEFBUTTON1);
    
    // switch (msgboxID)
    // {
    // case IDCONTINUE:
    //     break;

    // case IDTRYAGAIN:
    //     break;

    // case IDCANCEL:
    //     break;
    // }

    return msgboxID;
}

