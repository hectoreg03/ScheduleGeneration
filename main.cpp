#include <windows.h>
#include <commctrl.h>
#include <string>
#include <vector>
#include<iostream>

/* Global variables for the input fields */
HWND hEditTeams, hEditSports;
std::vector<HWND> hEditCourts;      // Vector to hold the court input fields
std::vector<HWND> hStaticLabels;    // Vector to hold the labels for the courts
HWND hButtonClear, hButtonGenerate; // Handles for the buttons
int buttonYPosition = 100;           // Initial Y position of the buttons

/* Function prototypes */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void ClearFields();
void CreateCourtInputs(HWND hwnd, int sportsCount);
void GenerateSchedules(HWND hwnd);
void UpdateButtonPosition(int sportsCount);
void ClearPreviousCourtInputs();

/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    switch (Message) {
        case WM_DESTROY: {
            PostQuitMessage(0);
            break;
        }
        case WM_CREATE: {
            // Create labels and input fields
            CreateWindow("STATIC", "Cantidad de Equipos:", WS_VISIBLE | WS_CHILD, 20, 20, 150, 20, hwnd, NULL, NULL, NULL);
            hEditTeams = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 20, 100, 20, hwnd, NULL, NULL, NULL);
            
            CreateWindow("STATIC", "Cantidad de Deportes:", WS_VISIBLE | WS_CHILD, 20, 60, 150, 20, hwnd, NULL, NULL, NULL);
            hEditSports = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 60, 100, 20, hwnd, NULL, NULL, NULL);
            
            // Create buttons
            hButtonClear = CreateWindow("BUTTON", "Borrar", WS_VISIBLE | WS_CHILD, 20, buttonYPosition, 100, 30, hwnd, (HMENU)2, NULL, NULL);
            hButtonGenerate = CreateWindow("BUTTON", "Generar Horarios", WS_VISIBLE | WS_CHILD, 130, buttonYPosition, 130, 30, hwnd, (HMENU)3, NULL, NULL);
            break;
        }
        case WM_COMMAND: {
            switch (LOWORD(wParam)) {
                case 2: // Botón "Borrar"
                    ClearFields();
                    break;
                case 3: // Botón "Generar Horarios"
                    GenerateSchedules(hwnd);
                    break;
            }
            
            // Handling sports input update
            if (HIWORD(wParam) == EN_UPDATE && (HWND)lParam == hEditSports) {
                char buffer[256];
                GetWindowText(hEditSports, buffer, 256);
                int sports = atoi(buffer);

                // Clear previous court inputs and labels
                ClearPreviousCourtInputs();

                // Create new court inputs based on the sports count
                if (sports > 0) {
                    CreateCourtInputs(hwnd, sports);
                    UpdateButtonPosition(sports); // Update the button positions
                }
            }
            break;
        }
        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

/* Function to create court input fields */
void CreateCourtInputs(HWND hwnd, int sportsCount) {
    for (int i = 0; i < sportsCount; ++i) {
        char label[256];
        sprintf(label, "Canchas para Deporte %i:", i + 1);
        std::cout<<label<<std::endl;
        // Create and store the label
        HWND hLabel = CreateWindow("STATIC", label, WS_VISIBLE | WS_CHILD, 20, 100 + i * 40, 150, 20, hwnd, NULL, NULL, NULL);
        hStaticLabels.push_back(hLabel); // Store the handle for the label
        
        // Create and store the edit field
        HWND hEdit = CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER, 200, 100 + i * 40, 100, 20, hwnd, NULL, NULL, NULL);
        hEditCourts.push_back(hEdit);    // Store the handle for the edit field
    }
}

/* Function to clear the text fields */
void ClearFields() {
    SetWindowText(hEditTeams, "");
    SetWindowText(hEditSports, "");

    // Destroy court input fields and labels
    ClearPreviousCourtInputs();

    // Reset button positions to default
    UpdateButtonPosition(0);
}

/* Function to clear previous court input fields and labels */
void ClearPreviousCourtInputs() {
    // Destroy previous court input fields
    for (HWND hEdit : hEditCourts) {
        DestroyWindow(hEdit);
    }
    hEditCourts.clear(); // Clear the vector holding the input fields
    
    // Destroy previous labels
    for (HWND hLabel : hStaticLabels) {
        DestroyWindow(hLabel);
    }
    hStaticLabels.clear(); // Clear the vector holding the labels
}

/* Function to generate schedules */
void GenerateSchedules(HWND hwnd) {
    // Logic to generate schedules goes here
    // For now, just display a message box
    MessageBox(hwnd, "Generando horarios...", "Información", MB_OK);
    
}

/* Function to update button positions */
void UpdateButtonPosition(int sportsCount) {
    buttonYPosition = 100 + sportsCount * 40 + 20; // Calculate new Y position based on the number of sports
    
    // Move buttons below the new fields
    SetWindowPos(hButtonClear, NULL, 20, buttonYPosition, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    SetWindowPos(hButtonGenerate, NULL, 130, buttonYPosition, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc; /* A properties struct of our window */
    HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
    MSG msg; /* A temporary location for all messages */

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc; /* This is where we will send messages to */
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "Caption", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, /* x */
        CW_USEDEFAULT, /* y */
        640, /* width */
        480, /* height */
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}
