#pragma once
#include <windows.h>
#include <stdio.h>
#include <map>
#include <unordered_map>
#include <vector>
#include "SimConnect.h"
#include "WASM.h"
#include "ClientDataArea.h"
#include "CDAIdBank.h"

using namespace ClientDataAreaMSFS;
using namespace CDAIdBankMSFS;

using namespace std;

enum WASM_EVENT_ID {
	EVENT_SET_LVAR=1,		// map to StartEventNo + 1
	EVENT_SET_HVAR,			// map to StartEventNo + 2
	EVENT_UPDATE_CDAS,		// map to StartEventNo + 3
	EVENT_LIST_LVARS,		// map to StartEventNo + 4
	EVENT_RELOAD,			// map to StartEventNo + 5
	EVENT_CONFIG_RECEIVED=9,
	EVENT_VALUES_RECEIVED=10, // Allow for MAX_NO_VALUE_CDAS (2)
	EVENT_LVARS_RECEIVED=12, // Allow for MAX_NO_LVAR_CDAS (12)
	EVENT_HVARS_RECEIVED=30, // Allow for MAX_NO_HVAR_CDAS (4)
};

enum LOGLEVEL
{
	DISABLE_LOG = 1,
	LOG_LEVEL_INFO = 2,
	LOG_LEVEL_BUFFER = 3,
	LOG_LEVEL_DEBUG = 4,
	LOG_LEVEL_TRACE = 5,
	ENABLE_LOG = 6,
};

class WASMIF
{
	public:
		static class WASMIF* GetInstance(HWND hWnd, int startEventNo = EVENT_START_NO, void (*loggerFunction)(const char* logString) = nullptr);
		static class WASMIF* GetInstance(HWND hWnd, void (*loggerFunction)(const char* logString));
		bool start();
		void end();
		void createAircraftLvarFile();
		void reload();
		void setLvarUpdateFrequency(int freq);
		void setSimConfigConnection(int connection);
		int getLvarUpdateFrequency();
		void setLogLevel(LOGLEVEL logLevel);
		double getLvar(int lvarID);
		double getLvar(const char * lvarName);
		void setLvar(unsigned short id, double value);
		void setLvar(unsigned short id, short value);
		void setLvar(unsigned short id, const char *value);
		void setLvar(unsigned short id, unsigned short value);
		void setHvar(int id);
		void logLvars(); // Just print to log for now
		void getLvarValues(map<string, double >& returnMap);
		void logHvars(); // Just print to log for now
		void getLvarList(unordered_map<int, string >& returnMap);
		void getHvarList(unordered_map<int, string >& returnMap);
		void executeCalclatorCode(const char *code);
		int getLvarIdFromName(const char* lvarName);
		void getLvarNameFromId(int id, char* name);
		bool createLvar(const char* lvarName, DWORD value);

	public:
		static void CALLBACK MyDispatchProc(SIMCONNECT_RECV* pData, DWORD cbData, void* pContext);
		static VOID CALLBACK StaticConfigTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
		static VOID CALLBACK StaticRequestDataTimer(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

	protected:
		WASMIF();
		~WASMIF();
	private:
		static DWORD WINAPI StaticSimConnectThreadStart(void* Param);
		void DispatchProc(SIMCONNECT_RECV* pData, DWORD cbData);
		VOID CALLBACK ConfigTimer(HWND hWnd, UINT uMsg, DWORD dwTime);
		VOID CALLBACK RequestDataTimer(HWND hWnd, UINT uMsg, DWORD dwTime);
		volatile  HANDLE hThread = NULL;
		DWORD WINAPI SimConnectStart();
		void SimConnectEnd();
		const char* getEventString(int eventNo);
		void setLvar(DWORD param);

	private:
		static WASMIF* m_Instance;
		HANDLE  hSimConnect;
		HWND hWnd;
		int quit, noLvarCDAs, noHvarCDAs, startEventNo, lvarUpdateFrequency;
		UINT_PTR configTimer;
		UINT_PTR requestTimer;
		BOOL configReceived;
		ClientDataArea* lvar_cdas[MAX_NO_LVAR_CDAS];
		ClientDataArea* hvar_cdas[MAX_NO_HVAR_CDAS];
		ClientDataArea* value_cda[MAX_NO_VALUE_CDAS];
		static int nextDefinitionID;
		vector<string> lvarNames;
		vector<double> lvarValues;
		vector<string> hvarNames;
		CDAIdBank* cdaIdBank;
		int simConnection;
		CRITICAL_SECTION        lvarMutex;
};

