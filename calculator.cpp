#include <windows.h>
#include <string>
#include <sstream>

const char g_szClassName[] = "myWindowClass";
HWND hEdit1, hEdit2, hStatic;

void ShowResult(double result) {
    std::ostringstream oss;
    oss << result;
    MessageBox(NULL, oss.str().c_str(), "Result", MB_OK | MB_ICONINFORMATION);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE:
            hStatic = CreateWindow("STATIC", "Please input two numbers", WS_VISIBLE | WS_CHILD | SS_CENTER,
                                   20, 10, 200, 25, hwnd, NULL, NULL, NULL);
            hEdit1 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  50, 40, 150, 25, hwnd, NULL, NULL, NULL);
            hEdit2 = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER,
                                  50, 70, 150, 25, hwnd, NULL, NULL, NULL);
            CreateWindow("BUTTON", "+", WS_VISIBLE | WS_CHILD,
                         50, 110, 40, 40, hwnd, (HMENU)1, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_VISIBLE | WS_CHILD,
                         95, 110, 40, 40, hwnd, (HMENU)2, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_VISIBLE | WS_CHILD,
                         140, 110, 40, 40, hwnd, (HMENU)3, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_VISIBLE | WS_CHILD,
                         185, 110, 40, 40, hwnd, (HMENU)4, NULL, NULL);
            break;
        case WM_COMMAND:
            if (LOWORD(wParam) >= 1 && LOWORD(wParam) <= 4) {
                char buffer1[32], buffer2[32];
                GetWindowText(hEdit1, buffer1, 32);
                GetWindowText(hEdit2, buffer2, 32);
                double num1 = atof(buffer1);
                double num2 = atof(buffer2);
                double result = 0;
                switch (LOWORD(wParam)) {
                    case 1: result = num1 + num2; break;
                    case 2: result = num1 - num2; break;
                    case 3: result = num1 * num2; break;
                    case 4: result = (num2 != 0) ? num1 / num2 : 0; break;
                }
                ShowResult(result);
            }
            break;
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 127)); // สีพื้นหลังชมพูสด
    wc.lpszClassName = g_szClassName;
    
    if (!RegisterClassEx(&wc)) {
        MessageBox(nullptr, "Window Registration Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    HWND hwnd = CreateWindowEx(
        0, g_szClassName, "My Calculator", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT, 250, 200, nullptr, nullptr, hInstance, nullptr);
    
    if (!hwnd) {
        MessageBox(nullptr, "Window Creation Failed!", "Error", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}