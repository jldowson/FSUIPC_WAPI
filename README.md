# FSUIPC_WAPI
API for connection to the FSUIPC WASM Module

FSUIPC_WAPI is a clinet-side API library for communication with the FSUIPC WASM module.
This allows for the retrieval/listing of lbars/hvars, for the setting of lvars and the activation of hbars.

The WASMIF class is the main interface. To use, first instantiate a WASMIF object:
        WASMIF* WASMIFPtr = WASMIF::getInstance(hWnd);
Then start the service:
        WASMIFPtr->start()
You can then get/set/list lvars and list/activate hvars using the provided member functions, e,g.
        WASMPtr->getLvarValues(map<string, double> lvars);
        WASMPtr->getHvarList(unordered_map<int, string> hvars);
        double value = WASMPtr->getLvar(const char* lvarName);
        WASMPtr->setHvar(int id);
        WASMPtr->executeCalclatorCode(const char* ccode);
        WASMPtr->setLvar(int id, double value);
        etc

A demo test vlient using this API is available here: https://github.com/jldowson/WASMClient

Note: to build from source, the MSFS SDK is referenced from C:\MSFS-SDK. You can change the build properties to point to your MSFS SDK installation, or create a symbolic link (or junction) to link that location to yout actial installation location.
