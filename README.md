# FSUIPC_WAPI
API for connection to the FSUIPC WASM Module

FSUIPC_WAPI is a client-side API library for communication with the FSUIPC WASM module.
This allows for the retrieval/listing of lbars/hvars, for the setting of lvars and the activation of hvars.

The WASMIF class is the main interface. To use, first instantiate a WASMIF object:<br>
<code>        WASMIF* WASMIFPtr = WASMIF::getInstance(hWnd);</code><br>

Then start the service:<br>
<code>        WASMIFPtr->start();</code><br>

You can then get/set/list lvars and list/activate hvars using the provided member functions, e,g.<br>
<code>        WASMPtr->getLvarValues(map<string, double> lvars);</code><br>
<code>        WASMPtr->getHvarList(unordered_map<int, string> hvars);</code><br>
<code>        double value = WASMPtr->getLvar(const char* lvarName);</code><br>
<code>        WASMPtr->setHvar(int id);</code><br>
<code>        WASMPtr->executeCalclatorCode(const char* ccode);</code><br>
<code>        WASMPtr->setLvar(int id, double value);</code><br>
              etc<br>
  
A demo test vlient using this API is available here: https://github.com/jldowson/WASMClient

Note: to build from source, the MSFS SDK is referenced from C:\MSFS-SDK. You can change the build properties to point to your MSFS SDK installation, or create a symbolic link (or junction) to link that location to yout actial installation location.
