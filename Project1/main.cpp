#include <Windows.h>
#include <tchar.h>
#include <ctime>
#include <list>
#include "resource.h"
using namespace std;

HWND hCombo, hList, hEdit;

BOOL CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPTSTR lpszCmdLine, int nCmdShow)
{
    // создаём главное окно приложения на основе модального диалога
    return  DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
}

BOOL CALLBACK DlgProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
    switch (message)
    {
    case WM_INITDIALOG:
        hCombo = GetDlgItem(hWnd, IDC_COMBO1);
        hList = GetDlgItem(hWnd, IDC_LIST1);
        hEdit = GetDlgItem(hWnd, IDC_EDIT1);
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Сумма чисел")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Произведение чисел")));
        SendMessage(hCombo, CB_ADDSTRING, 0, LPARAM(TEXT("Среднее арифметическое")));
        return TRUE;

    case WM_COMMAND:
        if (wp == IDC_BUTTON1)
        {
            // Очистим ListBox
            SendMessage(hList, LB_RESETCONTENT, 0, 0);
            // Очистим Edit
            SetWindowText(hEdit, TEXT(""));
            // Получим индекс выбранного элемента ComboBox
            int index = SendMessage(hCombo, CB_GETCURSEL, 0, 0);

            //заполняем ListBox случайными числами от -10 до 10
            TCHAR str[50];
            int min_row = 10, max_row = 20;
            int min_num = -10, max_num = 10;
            srand(time(0));
            int n = min_row + rand() % (max_row - min_row + 1);  //количество чисел
            list<int> num;  //список чисел

            while(num.size() <= n)
            {
                //рандомное число от -10 до 10 (исключая 0)                
                do {
                    num.push_back(min_num + rand() % (max_num - min_num + 1));
                } while (num.back() == 0);

                _stprintf_s(str, TEXT("%i"), num.back());
                SendMessage(hList, LB_ADDSTRING, 0, LPARAM(str));
            }

            double a = 0;
            switch (index)
            {
            case 0:   //произведение
                a++;
                for (auto i = num.begin(); i != num.end(); i++)
                {
                    a *= *i;
                }                
                break;
            case 1:   //среднее знач
                for (auto i = num.begin(); i != num.end(); i++)
                {
                    a += *i;
                }
                a /= n;
                break;
            case 2:  //сумма
                for (auto i = num.begin(); i != num.end(); i++)
                {
                    a += *i;
                }
                break;
            }
            //вывести результат в Edit
            _stprintf_s(str, TEXT("%.1f"), a);
            SetWindowText(hEdit, str);
        }
        return TRUE;
    case WM_CLOSE:
        EndDialog(hWnd, 0); // закрываем модальный диалог
        return TRUE;
    }
    return FALSE;
}