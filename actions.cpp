#include "actions.h"
#include <windows.h>

HWND lHwnd;

bool checkWindow() {
	lHwnd = FindWindow(NULL, L"League of Legends (TM) Client"); // Change me
	return lHwnd != NULL;
}

void detectMonitorSize(int *w, int *h) {
	RECT rc;
	GetWindowRect(GetDesktopWindow(), &rc);
	*w = rc.right - rc.left;
	*h = rc.bottom - rc.top;
}

void setPosition(int x, int y, int w, int h) {
	SetWindowPos(lHwnd, NULL, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
}

void getPosition(int *x, int *y, int *w, int *h) {
	RECT rc;
	GetWindowRect(lHwnd, &rc);
	*x = rc.left;
	*y = rc.top;
	*w = rc.right - rc.left;
	*h = rc.bottom - rc.top;
}
