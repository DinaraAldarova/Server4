#pragma once
#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <fstream>
#include < Windows.h >

using namespace std;

enum class s { error, working };
enum class n { server, off, on };

struct info
{
	int ID;
	n status;
	char buff[4096] = "";
	HANDLE stream; //��� ���� ������ � ��������, ��������� �����/������
	SOCKET sock;
	HANDLE mailslot;
	//��� � ���� ������������ ����?
	string mpath;
};
class ServerInterLayer
{
#pragma region ��������
private:
	s status = s::error;
	SOCKET client_socket;//��������� ����� �����
	u_short port = 665;
	list <string> log = { "11111", "2222", "333", "44", "5" };
	vector <string> files = { "f1", "f2", "f3", "f4", "f5" };
	vector <string> users = { "u1", "u2", "u3", "u4", "u5" };
	HANDLE hMutex_Log;
	HANDLE hMutex_Users;
	HANDLE hMutex_Files;

public:
	HOSTENT * hst;
	string IPv4;
	vector <info> client_info = {};
	//�������� �� false, ������� true � �������� ��������� ����� ������
	bool isOutDated_Users = true;
	bool isOutDated_Files = true;
	//����������� ������ ��� ������ � client_info
	CRITICAL_SECTION cs_info;
	CRITICAL_SECTION cs_files;
	CRITICAL_SECTION cs_users;
#pragma endregion

#pragma region Get- � set-������
private:


public:
	int new_ID();
	ServerInterLayer();
	s getStatus();
	void setStatus(s new_status);
	vector<string> getFiles();
	void setFile(string new_file);
	vector<string> getUsers();
	void setUser(string new_user);
	void setClient_info(info new_client_info);
	SOCKET getClient_socket();
	SOCKET setClient_socket(SOCKET new_client_socket);
	u_short getPort();
	void pushLog(string message);
	string popLog();
	bool Log_isEmpty();

#pragma endregion

#pragma region ������ ������ �������
private:
	//DWORD WINAPI initialize(LPVOID param);
	//DWORD WINAPI WorkWithClient(LPVOID client_socket);
	void quit_client(int ID);

public:
	void init();
	int Exit();

#pragma endregion
};