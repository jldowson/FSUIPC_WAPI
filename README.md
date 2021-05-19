# FSUIPC_WAPI
API for connection to the FSUIPC WASM Module

FSUIPC_WAPI is a client-side API library for communication with the FSUIPC WASM module.
This allows for the retrieval/listing of lbars/hvars, for the setting of lvars and the activation of hvars.

The WASMIF class is the main interface. To use, first instantiate a WASMIF object:<br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMIF* WASMIFPtr = WASMIF::getInstance(hWnd);</code><br>

Then start the service:<br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMIFPtr->start();</code><br>

You can then get/set/list lvars and list/activate hvars using the provided member functions, e,g.<br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMPtr->getLvarValues(map<string, double> lvars);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMPtr->getHvarList(unordered_map<int, string> hvars);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>double value = WASMPtr->getLvar(const char* lvarName);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMPtr->setHvar(int id);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMPtr->executeCalclatorCode(const char* ccode);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>WASMPtr->setLvar(int id, double value);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;etc<br>

You can register for a callback function to be called when the lvars/hvars have been loaded and are available using the following function:<br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>void registerUpdateCallback(void (*callbackFunction)(void));</code><br>

You can also register for a callback to be received when lvars have been updated, and flag individual lvars to be added to this callback, using the following functions:<br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>void registerLvarUpdateCallback(void (*callbackFunction)(int id[], double newValue[]));</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>void registerLvarUpdateCallback(void (*callbackFunction)(const char* lvarName[], double newValue[]));</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>void flagLvarForUpdateCallback(int lvarId);</code><br>
&nbsp;&nbsp;&nbsp;&nbsp;<code>void flagLvarForUpdateCallback(const char* lvarName);</code><br>

Note that the registration and flagging of lvars for callback should be performed in the callback function registered for lvars loaded /CDAs updated.
Once callback will be received per CDA (if data held in that CDA that has been flagged has changed), and the aeeat parameters for the callback (id or name and value) will contain a terminating element of -1 (for id based callbask) or NULL (for lvar name based callback).
Note also that if you register for both callbacks by id and callbacks by name, both callback functions s will be called.
  
A demo test client using this API is available here: https://github.com/jldowson/WASMClient

For any problems, questions or requests, please use the FSUIPC7 support forum:
&nbsp;&nbsp;&nbsp;&nbsp;https://forum.simflight.com/forum/183-fsuipc7-msfs/
 
John Dowson
19th May 2021
