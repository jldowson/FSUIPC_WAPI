#include "CDAIdBank.h"
#include "SimConnect.h"
#include "Logger.h"

using namespace std;
using namespace CDAIdBankMSFS;
using namespace CPlusPlusLogging;

CDAIdBank::CDAIdBank(int id, HANDLE hSimConnect) {
	nextId = id;
	this->hSimConnect = hSimConnect;
}

CDAIdBank::~CDAIdBank() {

}


pair<string, int> CDAIdBank::getId(int size) {
	pair<string, int> returnVal;
	std::map<int, pair<string, int>>::iterator it;

	// First, check if we have one available
	it = availableBank.find(size);
	if (it != availableBank.end()) {
		returnVal = make_pair(it->second.first, it->second.second);
		availableBank.erase(it);
		pair<int, pair<string, int>> out = make_pair(returnVal.second, make_pair(returnVal.first, size));
		outBank.insert(out);
	}
	else {
		// Create new CDA
		string newName = string(CDA_NAME_TEMPLATE + to_string(nextId));
		returnVal = getId(size, newName);
	}

	return returnVal;
}


pair<string, int> CDAIdBank::getId(int size, string name) {
	char szLogBuffer[512];
	pair<string, int> returnVal;
	std::map<int, pair<string, int>>::iterator it;
	DWORD dwLastID;

	// First, check if we have one available
	it = availableBank.find(size);
	if (it != availableBank.end()) {
		returnVal = make_pair(it->second.first, it->second.second);
		availableBank.erase(it);
		pair<int, pair<string, int>> out = make_pair(returnVal.second, make_pair(returnVal.first, size));
		outBank.insert(out);
	}
	else {
		// Create new CDA
		string newName = string(name);
		returnVal = make_pair(newName, nextId);
		pair<int, pair<string, int>> out = make_pair(nextId, make_pair(newName, size));
		outBank.insert(out);

		// Set-up CDA
		if (!SUCCEEDED(SimConnect_MapClientDataNameToID(hSimConnect, newName.c_str(), nextId))) {
			sprintf_s(szLogBuffer, sizeof(szLogBuffer), "Error mapping CDA name %s to ID %d", newName.c_str(), nextId);
			LOG_ERROR(szLogBuffer);
		}
		else {
			SimConnect_GetLastSentPacketID(hSimConnect, &dwLastID);
			sprintf_s(szLogBuffer, sizeof(szLogBuffer), "CDA name %s mapped to ID %d [requestId=%lu]", newName.c_str(), nextId, dwLastID);
			LOG_DEBUG(szLogBuffer);
		}

		// Finally, Create the client data if it doesn't already exist
		if (!SUCCEEDED(SimConnect_CreateClientData(hSimConnect, nextId, size, SIMCONNECT_CREATE_CLIENT_DATA_FLAG_READ_ONLY))) {
			sprintf_s(szLogBuffer, sizeof(szLogBuffer), "Error creating client data area with id=%d and size=%d", nextId, size);
			LOG_ERROR(szLogBuffer);
		}
		else {
			SimConnect_GetLastSentPacketID(hSimConnect, &dwLastID);
			sprintf_s(szLogBuffer, sizeof(szLogBuffer), "Client data area created with id=%d (size=%d) [requestID=%lu]", nextId, size, dwLastID);
			LOG_DEBUG(szLogBuffer);
		}
		nextId++;
	}

	return returnVal;

}


void CDAIdBank::returnId(int id) {
	std::map<int, pair<string, int>>::iterator it;
	// First, check if we have one available
	it = outBank.find(id);
	if (it != outBank.end()) {
		pair<string, int> p = outBank.at(id);
		pair<int, pair<string, int>> returnedItem = make_pair(p.second, make_pair(p.first, id));
		outBank.erase(it);
		availableBank.insert(returnedItem);
	}

}
