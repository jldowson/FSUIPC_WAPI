#pragma once

#include <windows.h>
#include <string>
#include <map>
#include <utility>

#define CDA_NAME_TEMPLATE	"FSUIPC_VNAME"

using namespace std;

namespace CDAIdBankMSFS {
  class CDAIdBank {
	public:
		CDAIdBank(int id, HANDLE hSimConnect);
		~CDAIdBank();
		pair<string, int> getId(int size);
		pair<string, int> getId(int size, string);
		void returnId(int id);

	protected:

	private:
		int nextId;
		multimap<int, pair<string, int>> availableBank; // keyed on size
		map<int, pair<string, int>> outBank; // keyed on Id
		HANDLE  hSimConnect;
  };
} // End of namespace
