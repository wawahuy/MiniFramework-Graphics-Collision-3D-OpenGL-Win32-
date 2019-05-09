/* Project udp hole punching
 * Use Network, Window, System of YUH LIB
 * Áp dụng ký thuật PWNAT
 *
 */

//#define UDPHOLE
#ifdef UDPHOLE

#define YUH_FREE_CONSOLE
#include <System/YuhSystem.h>
#include <Window/YuhWindow.h>
#include <Network/YuhNetwork.h>
#include <Graphics/YuhGraphics.h>
#include <CommCtrl.h>
#include <map>
#pragma comment (lib, "comctl32.lib")

using namespace yuh;
using namespace yuh::window;
using namespace yuh::net;

#define MAX_BUFFER_WIN32 5000
#define PORT_TCP L"8111"
#define PORT_UDP L"12345"
#define IP_SERVER L"127.0.0.1"
#define RUN_WITH_DEFAULT false

long globalID = 0;

struct Client {
	TCPSocketPtr tcp;
	AddressInfo  udp;
	long id;
	long callid;
	bool flagcall;
};

struct ClientSend {
	AddressInfo addr;
	long id;
};

typedef map<long, Client> ListClient;
typedef pair<long, Client> ChildClient;


bool is_number(const std::string &s) {
	return !s.empty() && std::all_of(s.begin(), s.end(), ::isdigit);
}

wstring StringToWString(const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());
	return wsTmp;
}

//GetText
std::wstring GetText(HWND hwnd) {
	wchar_t buffer[MAX_BUFFER_WIN32];
	GetWindowTextW(hwnd, buffer, MAX_BUFFER_WIN32);
	return wstring(buffer);
}


//Create Window Ip Address
HWND CreateIPAddress(HWND parent, Vec2i pos, Vec2ui size) {
	HWND hwndIp = CreateWindowW(WC_IPADDRESSW, L"", WS_CHILD | WS_VISIBLE | WS_BORDER, pos.x, pos.y, size.x, size.y, parent, NULL, NULL, NULL);
	ShowWindow(hwndIp, SW_SHOW);
	return hwndIp;
}


//Create Button
HWND CreateButton(HWND parent, WCHAR *name, Vec2i pos, Vec2ui size, long idButton) {
	HWND hwndBt = CreateWindowW(L"BUTTON", name, WS_CHILD | WS_VISIBLE | WS_BORDER, pos.x, pos.y, size.x, size.y, parent, (HMENU)idButton, NULL, NULL);
	ShowWindow(hwndBt, SW_SHOW);
	return hwndBt;
}


//Create Edit
HWND CreateEdit(HWND parent, long style, Vec2i pos, Vec2ui size) {
	HWND hwnd = CreateWindowW(L"Edit", L"",  WS_VISIBLE | style, pos.x, pos.y, size.x, size.y, parent, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}

void AppendEdit(HWND hwnd, wchar_t * str) {
	HWND ac = GetActiveWindow();

	int ndx = GetWindowTextLength(hwnd);
	
	if (ndx > 20000) {
		wstring str = GetText(hwnd);
		SetWindowText(hwnd, str.substr(str.length()/3, str.length()-str.length()/3).c_str());
		ndx = GetWindowTextLength(hwnd);
	}

	//SetFocus(hwnd);
	SendMessage(hwnd, EM_SETSEL, (WPARAM)ndx, (LPARAM)ndx);
	SendMessage(hwnd, EM_REPLACESEL, 0, (LPARAM)((LPSTR)str));

	SetActiveWindow(ac);
}


//Create Text
HWND CreateText(HWND parent, WCHAR *name, Vec2i pos, Vec2ui size) {
	HWND hwnd = CreateWindowW(L"Static", name, WS_CHILD | WS_VISIBLE, pos.x, pos.y, size.x, size.y, parent, NULL, NULL, NULL);
	ShowWindow(hwnd, SW_SHOW);
	return hwnd;
}


//Check Clisk button with hwnd
bool IsClickedButton(MSG msg, HWND hwnd) {
	return	msg.message			==	WM_COMMAND &&
			HIWORD(msg.wParam)	==	BN_CLICKED &&
			(HWND)msg.lParam	==	hwnd;
}


//Check Click button with ID
bool IsClickedButton(MSG msg, long idButton) {
	return msg.message == WM_COMMAND && LOWORD(msg.wParam) == idButton;
}

/* Server
 * 
 */
void Server() {
	//Init YUH Listen all event
	Event::isGetEventW32API = true;

	//Init ComCtl
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_INTERNET_CLASSES;
	InitCommonControlsEx(&icex);

	//============
	int traversal = 0;
	bool init = RUN_WITH_DEFAULT;
	bool runServer = false;
	TCPSocketPtr tcpServer;
	UDPSocketPtr udpServer;
	ListClient listClient;
	//============

	//Create Widow
	WindowPtr window = Window::create(L"Test Hole UDP Server", Vec2ui(700, 500));
	window->setFrameMax(60);

	//Create Window Child Deltail
	WindowPtr windeltail = Window::create(L"Thông tin Server", Vec2ui(200, 200), window, WS_OVERLAPPED | WS_VISIBLE | WS_DISABLED);
	windeltail->setParent(window);
	windeltail->setPosition(Vec2i(10, 80));
	HWND textStatus = CreateText(windeltail->getHandle(), L"Trạng thái: Đóng", Vec2i(10, 10), Vec2ui(195, 45));
	HWND textTCPcon = CreateText(windeltail->getHandle(), L"Số lượng online: 0", Vec2i(10, 65), Vec2ui(195, 45));
	HWND textUDPcon = CreateText(windeltail->getHandle(), L"Số lượng P2P: 0", Vec2i(10, 120), Vec2ui(195, 45));

	//Create Window LOG
	HWND hwndLog = CreateEdit(window->getHandle(), WS_CHILD |  WS_VSCROLL | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_READONLY, Vec2i(230, 80), Vec2ui(430, 350));


	//Window Chang Port
	CreateText(window->getHandle(), L"Port UDP:", Vec2i(10, 10), Vec2ui(70, 25));
	CreateText(window->getHandle(), L"Port TCP:", Vec2i(120, 10), Vec2ui(80, 25));
	HWND hwndPortUDP = CreateEdit(window->getHandle(), WS_CHILD | ES_NUMBER | WS_BORDER | ES_CENTER, Vec2i(10, 30), Vec2ui(80, 25));
	HWND hwndPortTCP = CreateEdit(window->getHandle(), WS_CHILD | ES_NUMBER | WS_BORDER | ES_CENTER, Vec2i(120, 30), Vec2ui(80, 25));
	SetWindowText(hwndPortUDP, PORT_UDP);
	SetWindowText(hwndPortTCP, PORT_TCP);
	HWND hwndBtIP = CreateButton(window->getHandle(), L"Khởi tạo", Vec2i(220, 30), Vec2ui(80, 25), 0);

	auto updateClient = [&]() -> void {
		Packet packet;
		
		//List to byte
		std::vector<ClientSend> data;
		data.resize(listClient.size());
		
		for (auto temp = listClient.begin(); temp != listClient.end(); temp++) {
			data.push_back(ClientSend{ temp->second.tcp->getAddress(), temp->first});
		}

		if (listClient.size() > 0) {
			packet.append((char*)&data[0], sizeof(data[0])*data.size());
		}


		//Send all client list new
		for (auto temp = listClient.begin(); temp != listClient.end(); temp++) {
			if (!temp->second.tcp->isClose()) {
				temp->second.tcp->send(packet);
			}
		}

		//Update UI
		wstring text = runServer ? L"Mở" : L"Đóng";
		SetWindowText(textStatus, (L"Trạng thái: " + text).c_str());
		SetWindowText(textTCPcon, (L"Số lượng online: " + to_wstring(listClient.size())).c_str());
		SetWindowText(textUDPcon, (L"Số lượng P2P: " + to_wstring(traversal)).c_str());

	};


	while (window->isOpen()) {

		//Event YUH
		Event evt;
		while (window->pollEvent(evt));

		//EVENT on Win32API
		MSG msg;
		while (Event::pollEvent(msg)) {
			//Close
			if (msg.message == WM_CLOSE && msg.hwnd == window->getHandle()) window->close();

			//Clicked connect
			if (IsClickedButton(msg, hwndBtIP) || init) {
				init = false;
				SetWindowText(hwndBtIP, !( runServer = !runServer )? L"Khởi tạo" : L"Ngừng");

				//Establish
				if (runServer) {
					SetWindowLongPtr(hwndPortTCP, GWL_STYLE, GetWindowLongPtr(hwndPortTCP, GWL_STYLE) | WS_DISABLED);
					SetWindowLongPtr(hwndPortUDP, GWL_STYLE, GetWindowLongPtr(hwndPortUDP, GWL_STYLE) | WS_DISABLED);

					//Get Port
					int portUDP = stoi(GetText(hwndPortUDP));
					int portTCP = stoi(GetText(hwndPortTCP));

					//Init Socket
					tcpServer = TCPSocket::create();
					tcpServer->listen(portTCP);
					tcpServer->setBlocking(false);

					udpServer = UDPSocket::create();
					udpServer->bind(portUDP);
					udpServer->setBlocking(false);

					listClient.clear();
				}
				else {
					SetWindowLongPtr(hwndPortTCP, GWL_STYLE, GetWindowLongPtr(hwndPortTCP, GWL_STYLE) & ~WS_DISABLED);
					SetWindowLongPtr(hwndPortUDP, GWL_STYLE, GetWindowLongPtr(hwndPortUDP, GWL_STYLE) & ~WS_DISABLED);
					tcpServer->close();
					udpServer->close();
				}

				updateClient();
			}


		}

		//Network
		if (runServer) {
			if (tcpServer->isClose() || udpServer->isClose()) {
				AppendEdit(hwndLog, L"Error Socket!\r\n");
			}

			Packet packet;
			AddressInfo addr;

			//UDP Server Recv
			if (udpServer->recvfrom(packet, addr) == Socket::SK_OK) {
				string sid = packet.getString();
				if (is_number(sid)){
					long id = stol(sid);
					if (listClient.find(id) != listClient.end()) {
						listClient[id].udp = addr;
					}
				}
			}

			//TCP Server Accept
			Client client;
			if (tcpServer->accept(client.tcp)) {
				client.id = globalID++;
				listClient.insert(ChildClient(client.id, client));
				
				//Send ID to user
				client.tcp->send(Packet("ID___" + to_string(client.id)));
				Sleep(10);

				//GUI
				updateClient();

				//Log
				AppendEdit(hwndLog, (wchar_t*)(L"[TCP] Accept ID: "+ to_wstring(client.id) + L" - " + StringToWString(client.tcp->getAddress().getString()) + L"\r\n").c_str());
			}

			//TCP Server Recv
			for (auto temp = listClient.begin(); temp != listClient.end(); ) {
				auto get = temp++;
				TCPSocketPtr client = get->second.tcp;

				if (!client->isClose()) {

					//Recv
					Socket::Status status = client->recv(packet);

					switch (status) {
					case Socket::SK_OK:
					{
						AppendEdit(hwndLog, (wchar_t*)(L"[TCP] Recv By ID " + to_wstring(get->first) + L": " + StringToWString(packet.getString()) + L"\r\n").c_str());
						
						string str = packet.getString();
						Packet packetSend;

						//Close connect
						if (str == "close") { client->close(); break; }
						
						/*													false id
						 *	Client A -> TCP Send CALL_[ID] -> Server Check --------> Back Send Clien A , ERROR CALL
						 *										   |
						 *			       Ghi vao callID cua A	   | true ID, send HCAL_[A]
						 *										   |
						 *										Client [ID]
						 *										   |
						 *										   | NO Accept ----> ACKN_[A]  ----> Server ----> Send A
						 *										   |								(xóa callid)
						 *										 [ID] Accept
						 *										   |
						 *										   | Send ACKY_[A]		(lưu callid trên X)
						 *										   |		
						 *										  Server  (kiểm tra callid của A có phải là [ID] không, nếu sai thì không lưu callid)
						 *										   |______-----> Send FUDP, khi nhận được cả 2 udp socket tiến hành gửi cho nhau dữ liệu
						 */


						//Flag
						string sFlag = str.substr(0, 5);

						if (sFlag.size() < 5) break;


						//Get ID
						string sid = str.substr(5, str.size() - 5);
						if (!is_number(sid)) break;
						long id = stol(sid);

						//Send Error
						if (listClient.find(id) == listClient.end()) {
							packetSend.append(L"ERRORKhông tim được ID!");
							client->send(packetSend);
							break;
						}

						//CLient A request client B Chat
						if (sFlag == "CALL_") {
							get->second.flagcall = true;
							get->second.callid = id;
							//Send request client B
							packetSend.append("HCAL_" + to_string(get->first));
							listClient[id].tcp->send(packetSend);
						}

						//Client B request Dont Accep client A
						else if (sFlag == "ACKN_") {
							packetSend.append("ACKN_");
							listClient[id].flagcall = false;
							listClient[id].tcp->send(packetSend);
						}

						//Client B request Accept client A
						else if (sFlag == "ACKY_") {
							//Check
							if (listClient[id].callid != get->second.id || listClient[id].flagcall == false) break;
							get->second.flagcall = true;
							get->second.callid = id;

							//Send flag 
							packetSend.append("FUDP_");
							
							listClient[id].tcp->send(packetSend);
							listClient[id].udp = AddressInfo();

							get->second.tcp->send(packetSend);
							get->second.udp = AddressInfo();
						}

						else if (sFlag == "OUT__") {
							if (id == get->second.callid) {
								listClient[id].tcp->send(Packet("OUT__"));
							}
						}

						break;
					}

					case Socket::SK_ERROR:
						break;

					case Socket::SK_DISCONNECTED:

						//Send End Connect UDP
						if (get->second.flagcall) {
							Packet sen;
							sen.append(L"ERRORClient đã mất kết nối");
							listClient[get->second.callid].flagcall = false;
							listClient[get->second.callid].tcp->send(sen);
						}

						client->close();
						break;
					}
				}
				else {
					//Close Socket
					listClient.erase(get->first);
					updateClient();
					AppendEdit(hwndLog, (wchar_t*)(L"[TCP] Close: " + StringToWString(client->getAddress().getString()) + L"\r\n").c_str());
				}
			}


			//TCP Server send UDP Client
			for (auto temp = listClient.begin(); temp != listClient.end(); temp++) {
				Client A = temp->second;
				if (!A.flagcall ||A.udp == NULL) continue;
			
				Client B = listClient[A.callid];
				if (!B.flagcall || B.udp == NULL) continue;

				traversal++;

				Packet pk;
				ClientSend cl;

				//A
				cl.id = A.id;
				cl.addr = A.udp;
				pk.append((char*)&cl, sizeof(cl));
				B.tcp->send(pk);

				//B
				pk.clear();
				cl.id = B.id;
				cl.addr = B.udp;
				pk.append((char*)&cl, sizeof(cl));
				A.tcp->send(pk);

				temp->second.flagcall = false;
				listClient[A.callid].flagcall = false;
			}
		}


		//Limit Frame
		window->display();
	}
}

/*
 *
 */
void SClient(){
	//Init YUH Listen all event
	Event::isGetEventW32API = true;

	//Init ComCtl
	INITCOMMONCONTROLSEX icex;
	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_INTERNET_CLASSES;
	InitCommonControlsEx(&icex);

	//
	TCPSocketPtr tcp;
	UDPSocketPtr udp;
	AddressInfo  udpInfo;
	bool runClient = false;
	bool init = RUN_WITH_DEFAULT;
	int ID;
	bool bConnectClient = false;
	ClientSend csConnectClient;

	Timer timer;
	bool bSetUpConnect = false;
	int countSendAuto = 0;
	int countRecvAuto = 0;
	//

	//Window
	WindowPtr window = Window::create(L"Client YUH", Vec2ui(600, 150));
	window->setStyle(window->getStyle() ^ WS_THICKFRAME);
	window->setFrameMax(60);
	
	CreateText(window->getHandle(), L"Port UDP:", Vec2i(220, 10), Vec2ui(70, 25));
	CreateText(window->getHandle(), L"Port TCP:", Vec2i(320, 10), Vec2ui(80, 25));
	CreateText(window->getHandle(), L"IP Server:", Vec2i(10, 10), Vec2ui(80, 25));
	HWND hwndPortUDP = CreateEdit(window->getHandle(), WS_CHILD | ES_NUMBER | WS_BORDER | ES_CENTER, Vec2i(220, 35), Vec2ui(80, 25));
	HWND hwndPortTCP = CreateEdit(window->getHandle(), WS_CHILD | ES_NUMBER | WS_BORDER | ES_CENTER, Vec2i(320, 35), Vec2ui(80, 25));
	HWND hwndIp = CreateIPAddress(window->getHandle(), Vec2i(10, 35), Vec2ui(200, 25));
	SetWindowText(hwndPortUDP, PORT_UDP);
	SetWindowText(hwndPortTCP, PORT_TCP);
	SetWindowText(hwndIp, IP_SERVER);
	HWND hwndBtIP = CreateButton(window->getHandle(), L"Kết nối", Vec2i(420, 35), Vec2ui(80, 25), 0);

	//Client Window
	WindowPtr windowClient = Window::create(L"", Vec2ui(300, 400));
	windowClient->setStyle(windowClient->getStyle() ^ WS_THICKFRAME);
	ShowWindow(windowClient->getHandle(), SW_HIDE);
	HWND textID = CreateText(windowClient->getHandle(), L"ID Của bạn: __", Vec2i(20, 20), Vec2ui(100, 25));

	WindowPtr winTCCall = Window::create(L"Kết Nối P2P ID", Vec2ui(140, 130), WS_VISIBLE | WS_CAPTION);
	winTCCall->setParent(windowClient);
	winTCCall->setPosition(Vec2i(18, 60));
	HWND hwndIDCall = CreateEdit(winTCCall->getHandle(), WS_CHILD | ES_NUMBER | WS_BORDER | ES_CENTER, Vec2i(10, 10), Vec2ui(100, 25));
	HWND hwndBtCall = CreateButton(winTCCall->getHandle(), L"Băt Tay", Vec2i(10, 45), Vec2ui(100, 25), 0);

	//Client Waitting flag ASKY_ OR ASKN_, FUDP_,...
	WindowPtr windowWait = Window::create(L"", Vec2ui(400, 200), WS_OVERLAPPED | WS_VISIBLE);
	HWND hwndTextWait = CreateText(windowWait->getHandle(), L"", Vec2i(10, 30), Vec2ui(380, 40));
	HWND hwndBtOutWait = CreateButton(windowWait->getHandle(), L"Thoát", Vec2i(150, 100), Vec2ui(100, 25), 0);
	SetWindowLongPtr(hwndTextWait, GWL_STYLE, SS_CENTER | WS_VISIBLE | WS_CHILD);
	ShowWindow(windowWait->getHandle(), SW_HIDE);

	//Client Connect
	WindowPtr windowConnect = Window::create(L"", Vec2ui(500, 500));
	windowConnect->setStyle(windowConnect->getStyle() ^ WS_THICKFRAME);
	ShowWindow(windowConnect->getHandle(), SW_HIDE);
	HWND hwndEdChat = CreateEdit(windowConnect->getHandle(), WS_VISIBLE | WS_CHILD | WS_BORDER |ES_AUTOHSCROLL |ES_AUTOVSCROLL | WS_VSCROLL, Vec2i(10, 420), Vec2ui(400, 30));
	HWND hwndEdChatBox = CreateEdit(windowConnect->getHandle(), WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | WS_VSCROLL | ES_MULTILINE | ES_READONLY, Vec2i(10, 10), Vec2ui(480, 400));
	HWND hwndBtChat = CreateButton(windowConnect->getHandle(), L"Chat", Vec2i(420, 420), Vec2ui(60, 30), 0);


	//P2P , send flag CALL_[id]
	bool WaitFlag = false;
	string WaitFlagStr = "";

	auto showWindowClient = [&]()-> void {
		//Enable window client
		windowClient->setStyle(windowClient->getStyle() & ~WS_DISABLED);

		//Hide window wait
		ShowWindow(windowWait->getHandle(), SW_HIDE);

		countSendAuto = 0;
		countRecvAuto = 0;
	};


	auto fCallID = [&](int id) -> void {
		//Disable window client
		SetWindowLongPtr(windowClient->getHandle(), GWL_STYLE, GetWindowLongPtr(windowClient->getHandle(), GWL_STYLE) | WS_DISABLED);

		//Send call
		WaitFlag = true;
		WaitFlagStr = "CALL_";
		tcp->send(Packet("CALL_" + to_string(id)));

		//Show window waiting
		ShowWindow(windowWait->getHandle(), SW_SHOW);
		windowWait->setTitile(L"Kết nối đến ID: " + to_wstring(id));
		windowWait->setPosition(windowClient->getPosition());
		SetWindowText(hwndTextWait, L"Thiết lập bắt tay qua server flag \"CALL_\"...");
	};


	auto fConnectClient = [&]() {
		WaitFlag = false;

		Sleep(1000);
		ShowWindow(windowWait->getHandle(), SW_HIDE);
		ShowWindow(windowClient->getHandle(), SW_HIDE);
		ShowWindow(windowConnect->getHandle(), SW_SHOW);
		windowConnect->setTitile(L"Connect UDP: " + StringToWString(csConnectClient.addr.getString()));
		windowConnect->setPosition(windowClient->getPosition());

		SetWindowText(hwndEdChat, L"");
		SetWindowText(hwndEdChatBox, L"");
	};

	while (window->isOpen()) {
		Event evt;
		while (window->pollEvent(evt));

		MSG msg;
		while (Event::pollEvent(msg)) {
			//Close
			if (msg.message == WM_CLOSE && msg.hwnd == window->getHandle()) window->close();

			//Disconnect
			if (msg.hwnd == windowClient->getHandle() && msg.message == WM_CLOSE) {
				tcp->send(Packet("close"));
				Sleep(100);

				tcp->close();
				udp->close();
				
				ShowWindow(windowClient->getHandle(), SW_HIDE);
				ShowWindow(window->getHandle(), SW_SHOW);
				
				runClient = false;
			}

			//Out connect client
			if (msg.message == WM_CLOSE && msg.hwnd == windowConnect->getHandle()) {
				ShowWindow(windowConnect->getHandle(), SW_HIDE);
				ShowWindow(windowClient->getHandle(), SW_SHOW);
				showWindowClient();
				tcp->send(Packet("OUT__" + to_string(csConnectClient.id)));
				bConnectClient = false;
				WaitFlagStr = "";
			}

			//Chat
			if (IsClickedButton(msg, hwndBtChat) && bConnectClient && GetText(hwndEdChat).length() > 0) {
				Packet pkk;
				pkk.append(GetText(hwndEdChat));
				udp->sendto(pkk, csConnectClient.addr);
				SetWindowText(hwndEdChat, L"");
			}


			//Call
			if (IsClickedButton(msg, hwndBtCall) && GetText(hwndIDCall).size() > 0) {
				fCallID(stoi(GetText(hwndIDCall)));
			}

			//Exit Waiting
			if (IsClickedButton(msg, hwndBtOutWait) && WaitFlag) {
				
				//Send Disable flag to server
				if (WaitFlagStr == "CALL_") {

				}

				//Disable
				WaitFlag = false;
				showWindowClient();

			}

			//click
			if (IsClickedButton(msg, hwndBtIP) || !init) {
				init = true;

				if (!runClient) {
					int portTCP = stoi(GetText(hwndPortTCP));
					int portUDP = stoi(GetText(hwndPortUDP));
					wstring wIP = GetText(hwndIp);
					string   IP = string(wIP.begin(), wIP.end());

					tcp = TCPSocket::create();
					udp = UDPSocket::create();
					udpInfo = AddressInfo(IP, portUDP);

					if (!tcp->connect(AddressInfo(IP, portTCP))) {
						MessageBox(window->getHandle(), L"Không thể kết nối đến server!\r\n", 0, 0);
						break;
					}

					udp->setBlocking(false);
					tcp->setBlocking(false);

					//Show Window client
					ShowWindow(window->getHandle(), SW_HIDE);
					ShowWindow(windowClient->getHandle(), SW_SHOW);
					SetWindowText(windowClient->getHandle(), (L"Kết nối: " + wIP + L"    TCP: " + std::to_wstring(portTCP) + L"   UDP: " + std::to_wstring(portUDP)).c_str());

					runClient = true;
				}
			}

		}

		//Srv
		if (runClient) {

			/*
			 * Kết nối qua UDP
			 * P2P
			 *
			 */
			if (bConnectClient) {
				Packet pudp;
				AddressInfo adr;

				if (udp->recvfrom(pudp, adr) == Socket::SK_OK) {
					if (pudp.getString() == "Auto" && !bSetUpConnect) {
						if (++countRecvAuto >= 20) {
							bSetUpConnect = true;
						}
					}
					else {
						string sadr = adr.getString();
						AppendEdit(hwndEdChatBox, (wchar_t*)(L"[" + wstring(sadr.begin(), sadr.end()) + L"]: " + pudp.getWString()).c_str());
						AppendEdit(hwndEdChatBox, L"\r\n");
					}
				}

				if (!bSetUpConnect && timer.elapsed() > 3000) {
					countSendAuto = 0;
					timer.reset();
				}

				if (!bSetUpConnect || countSendAuto < 100) {
					udp->sendto(Packet("Auto"), csConnectClient.addr);
					countSendAuto++;

					wstring title = windowConnect->getTitle();
					int pos;
					if ((pos = title.find('#')) != wstring::npos) {
						title.erase(pos, title.size() - pos);
					}
					windowConnect->setTitile(title + L"# " + to_wstring(countRecvAuto) + L"/" + to_wstring(countSendAuto));
				}

			}


			Packet packetRecv;
			Socket::Status status = tcp->recv(packetRecv);

			switch (status) {
			case Socket::SK_OK:
			{
				//check mess calling
				if (WaitFlag && WaitFlagStr == "FUDP_" && !bConnectClient) {
					ClientSend *clientUDP = (ClientSend*)packetRecv.getData();

					string sadd = clientUDP->addr.getString();

					SetWindowText(hwndTextWait, (L"Lấy kết nối thành công vơi ID " + to_wstring(clientUDP->id) + L". UDP Connect: " + wstring(sadd.begin(), sadd.end()) + L"     UDP Hole").c_str());

					bSetUpConnect = false;
					bConnectClient = true;
					csConnectClient.addr = clientUDP->addr;
					csConnectClient.id = clientUDP->id;
					fConnectClient();
					break;
				}

				//Chek mess sys
				string str = packetRecv.getString();

				wstring wstr = packetRecv.getWString();

				if (str.size() < 5) break;

				string flag = str.substr(0, 5);

				string data = str.substr(5, str.size() - 5);

				if (flag == "ID___") {
					ID = stoi(data);
					SetWindowText(textID, (L"ID Của bạn: "+wstring(data.begin(), data.end())).c_str());
				}

				else if(flag == "ERROR") {
					if (WaitFlag) {
						showWindowClient();
						WaitFlag = false;
					}
					wstr.erase(0, 5);
					MessageBox(windowClient->getHandle(), wstr.c_str(), 0, 0);
				}

				else if (flag == "HCAL_") {
					int select = MessageBox(windowWait->getHandle(), (L"Bạn có muốn kết nối với ID "+wstring(data.begin(), data.end())).c_str(), L"Yêu cầu kết nối", MB_YESNO | MB_ICONQUESTION);
					if (select == IDYES) {
						WaitFlag = true;
						ShowWindow(windowWait->getHandle(), SW_SHOW);
						windowWait->setTitile(L"Kết nối đến ID: " + wstring(data.begin(), data.end()));
						windowWait->setPosition(windowClient->getPosition());
						tcp->send(Packet("ACKY_" + data));
					}
					else {
						tcp->send(Packet("ACKN_"));
					}
				}

				else if (WaitFlag && flag == "ACKN_") {
					showWindowClient();
					WaitFlag = false;
					MessageBox(windowWait->getHandle(), (L"ID" + wstring(data.begin(), data.end()) + L" không chấp nhận yêu cầu kết nối của bạn").c_str(), 0, 0);
				}

				else if (WaitFlag && flag == "FUDP_") {
					SetWindowText(hwndTextWait, L"B Đã chấp nhận kết nối. Thiết lập bắt tay qua UDP flag \"FUDP_\"...");
					WaitFlagStr = "FUDP_";
					udp->sendto(Packet(to_string(ID)), udpInfo);
				}

				else if (flag == "OUT__" && bConnectClient) {
					ShowWindow(windowConnect->getHandle(), SW_HIDE);
					ShowWindow(windowClient->getHandle(), SW_SHOW);
					showWindowClient();
					MessageBox(windowClient->getHandle(), L"Ngắt kết nối!", 0, MB_ICONQUESTION);
					bConnectClient = false;
					WaitFlagStr = "";
				}

				break;
			}

			case Socket::SK_DISCONNECTED:
				PostMessage(windowClient->getHandle(), WM_CLOSE, 0, 0);
				break;
			}

		}

		window->display();
	}

}


/* Main
 *
 */
void main() {
		int get = MessageBoxW(0, L"Chọn Yes mở SERVER!\r\nChọn No mở Client!\r\nCancle để thoát!", L"YUH Thử UDP Traversal!", MB_YESNOCANCEL | MB_ICONQUESTION);
		if (get == IDYES) Server();
		else if (get == IDNO) SClient();
}

#endif