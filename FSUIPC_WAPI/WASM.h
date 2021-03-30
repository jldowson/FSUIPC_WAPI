#pragma once
/*
 * Main WASM Interface. This is the file that is shared
 * between the WASM module and the Client.
 */
#define MAX_VAR_NAME_SIZE		56 // Max size of a CDA is 8k. So Max no lvars per CDK is
 //   8192/(this valuw) = 146
#define MAX_CDA_NAME_SIZE		64 
#define MAX_NO_LVAR_CDAS		7 // Allows for 1022 lvars (7*(8k/56)): 8 is max and allows for 1024 lvars, the max allowd for the value area (8k/8)
#define MAX_NO_HVAR_CDAS		4 // We can have more of these if needed
#define CONFIG_CDA_NAME			"FSUIPC_config"
#define LVARVALUE_CDA_NAME		"FSUIPC_SetLvar"
#define CCODE_CDA_NAME			"FSUIPC_CalcCode"
#define MAX_CALC_CODE_SIZE		256 // Up to 8k

// Define the default value where our events start. From this:
//    0 = Get Config Data (provided but shouldn't be needed)
//   +1 = Set LVAR (short values): parameter contains LVAR ID in low word and encoded value in hi word
//   +2 = Set HVAR: parameter contains ID of CDA that holds the lvar in the low word, and the hvar index number in the hi word
//   +3 = Request to Update LVARS: ignored if WASM is updating internally.
//   +4 = Request to List LVARS (generates aircraft LVAR file)
//   +5 = Reload Control: scans for lvars and re-reads hvar files and drops and re-creates all CDAs accordingly
// Note that it should be possible to change this value (via an ini parameter)
// in both the WASM module and any clients. They must, of course, match.
#define EVENT_START_NO			0x1FFF0

#pragma pack(push, 1)
namespace WASM {
	typedef struct _CDASETLVAR
	{
		int id;
		double lvarValue;
	} CDASETLVAR;

	typedef struct _CDACALCCODE
	{
		char calcCode[MAX_CALC_CODE_SIZE];
	} CDACALCCODE;

	typedef struct _CDAName
	{
		char name[MAX_VAR_NAME_SIZE];
	} CDAName;

	typedef struct _CDAValue
	{
		double value;
	} CDAValue;

	typedef enum {
		LVARF, HVARF, VALUEF
	} CDAType;

	typedef struct _CONFIG_CDA
	{
		char CDA_Names[MAX_NO_LVAR_CDAS + MAX_NO_HVAR_CDAS + 1][MAX_CDA_NAME_SIZE];
		int CDA_Size[MAX_NO_LVAR_CDAS + MAX_NO_HVAR_CDAS + 1];
		CDAType CDA_Type[MAX_NO_LVAR_CDAS + MAX_NO_HVAR_CDAS + 1];
	} CONFIG_CDA;
}
#pragma pack(pop)
