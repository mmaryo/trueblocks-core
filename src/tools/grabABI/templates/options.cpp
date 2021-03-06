/*-------------------------------------------------------------------------
 * This source code is confidential proprietary information which is
 * copyright (c) 2018, 2019 TrueBlocks, LLC (http://trueblocks.io)
 * All Rights Reserved
 *
 * The LICENSE at the root of this repo details your rights (if any)
 *------------------------------------------------------------------------*/
/*
 * Parts of this file were generated with makeClass. Edit only those parts of the code
 * outside of the BEG_CODE/END_CODE sections
 */
#include "main.h"

//---------------------------------------------------------------------------------------------------
static const COption params[] = {
    // BEG_CODE_OPTIONS
    COption("parse", "p", "", OPT_SWITCH, "display parsed input data"),
    COption("logs", "g", "", OPT_SWITCH, "display smart contract lo(g)s or events"),
    COption("trace", "t", "", OPT_SWITCH, "display smart contract internal traces"),
    COption("accounting", "a", "", OPT_SWITCH, "display credits and debits per account and reconcile at each block"),
    COption("no_check", "n", "", OPT_SWITCH, "do not do balance check at each block"),
    COption("debug", "d", "", OPT_SWITCH, "enter debug mode (pause after each transaction)"),
    COption("single", "s", "", OPT_SWITCH, "if debugging is enable&#44; single step through transactions"),
    COption("export", "e", "", OPT_SWITCH, "export the transactions to export file"),
    COption("json", "j", "", OPT_SWITCH, "ignore export format and export as json"),
    COption("bals", "b", "", OPT_SWITCH, "if a balance does not reconcile&#44; export a message to a file"),
    COption("list", "l", "", OPT_SWITCH, "display list of monitored accounts"),
    COpt ion("kBlock", "k", "<blknum>", OPT_FLAG, "start processing at block :k"),
    COption("offset", "o", "<blknum>", OPT_FLAG, "offset to kBlock"),
    COption("", "", "", OPT_DESCRIPTION,
            "Index transactions for a given Ethereum address (or collection of addresses)."),
    // END_CODE_OPTIONS
};
static const size_t nParams = sizeof(params) / sizeof(COption);

extern const char* defTransFmt;
extern const char* defTraceFmt;
extern string_q cleanFmt2(const string_q& str);
//---------------------------------------------------------------------------------------------------
bool COptions::parseArguments(string_q& command) {
    if (!standardOptions(command))
        return false;

    // BEG_CODE_LOCAL_INIT
    // END_CODE_LOCAL_INIT

    Init();
    explode(arguments, command, ' ');
    for (auto arg : arguments) {
        if (false) {
            // do nothing -- make auto code generation easier
            // BEG_CODE_AUTO
            // END_CODE_AUTO

        } else if (contains(arg, "-k:") || contains(arg, "--kBlock:")) {
            arg = substitute(substitute(arg, "-k:", ""), "--kBlock:", "");
            if (!isNumeral(arg)) {
                cerr << substitute(usageStr("You must specify a block number (" + arg + ")"), "\n", "\r\n");
                return false;
            }
            kBlock = str_2_Uint(arg);

        } else if (contains(arg, "-o:") || contains(arg, "--offset:")) {
            arg = substitute(substitute(arg, "-o:", ""), "--offset:", "");
            if (!isNumeral(arg)) {
                cerr << substitute(usageStr("You must specify a number for offset (" + arg + ")"), "\n", "\r\n");
                return false;
            }
            offset = str_2_Uint(arg);

        } else if (arg == "--single" || arg == "--single_step") {
            single_on = true;

        } else if (arg == "-n" || arg == "--no_check") {
            no_check = true;

        } else if (arg == "-a" || arg == "--accounting") {
            accounting_on = true;

        } else if (arg == "-g" || arg == "--logs") {
            logs_on = true;

        } else if (arg == "-t" || arg == "--trace") {
            trace_on = true;

        } else if (arg == "-p" || arg == "--parse") {
            parse_on = true;

        } else if (arg == "-b" || arg == "--bals") {
            report_bals = true;

        } else if (arg == "-d" || arg == "--debug") {
            debugger_on = true;

        } else if (arg == "-e" || arg == "--export") {
            export_on = true;

        } else if (arg == "-j" || arg == "--json") {
            colorsOff();
            json_on = true;

        } else if (arg == "-l" || arg == "--list") {
            colorsOff();
            CToml toml("./con fig.toml");
            COptions visitor;
            if (!visitor.loadW atches(toml))
                return false;

            if (visitor.w atches.size() > 2)
                cout << "[";

            for (uint32_t i = 0; i < visitor.w atches.size() - 1; i++) {
                cout << " { ";
                cout << "\"address\": \"" << visitor.w atches[i].color << visitor.w atches[i].address << cOff << "\", ";
                cout << "\"firstBlock\": " << bRed << visitor.w atches[i].firstBlock << cOff << ", ";
                cout << "\"name\": \"" << visitor.w atches[i].color << visitor.w atches[i].name << cOff << "\"";
                cout << " }" << (i < visitor.w atches.size() - 2 ? ",\r\n " : " \r\n");
            }

            if (visitor.w atches.size() > 2)
                cout << "]";

            e xit(0);

        } else if (startsWith(arg, '-')) {  // do not collapse
            if (!builtInCmd(arg)) {
                return usage("Invalid option: " + arg);
            }
        }
    }

    kBlock = max((blknum_t)0, kBlock - offset);

    if (debugger_on && !accounting_on)
        return usage("If you want to use the debugger, you must use the --accounting option as well.");

    if (!fileExists("./con fig.toml"))
        return usage("The con fig.toml file was not found. Are you in the right folder? Quitting...\n");

    CToml toml("./con fig.toml");
    if (!loadW atches(toml))
        return false;
    theWidth = toml.getConfigInt("display", "width", theWidth);

    accounting_on = toml.getConfigBool("display", "accounting", false) || accounting_on;
    logs_on = toml.getConfigBool("display", "logs", false) || logs_on;
    trace_on = toml.getConfigBool("display", "trace", false) || trace_on;
    parse_on = toml.getConfigBool("display", "parse", false) || parse_on;
    debugger_on = toml.getConfigBool("display", "debug", false) || debugger_on;
    single_on = toml.getConfigBool("display", "single", false) || single_on;
    no_check = toml.getConfigBool("display", "no_check", false) || no_check;
    autocorrect_on = toml.getConfigBool("display", "autocorrect", false) || autocorrect_on;
    json_on = toml.getConfigBool("formats", "as_json", false) || json_on;

    // If we're not told to use Json, then we use format strings. No format string == export as json
    if (!json_on) {
        transFmt = cleanFmt2(toml.getConfigStr("formats", "trans_fmt", defTransFmt));
        traceFmt = cleanFmt2(toml.getConfigStr("formats", "trace_fmt", defTraceFmt));
    } else {
        debugger_on = accounting_on = trace_on = logs_on = false;
    }

    replaceAll(transFmt, "{ISERROR}", cRed + "ERROR:{b:ISERROR}");
    replaceAll(traceFmt, "{ISERROR}", cRed + "ERROR:{b:ISERROR}");

    return true;
}

//---------------------------------------------------------------------------------------------------
void COptions::Init(void) {
    registerOptions(nParams, params);

    // BEG_CODE_INIT
    // END_CODE_INIT

    no_check = false;
    single_on = false;
    accounting_on = false;
    logs_on = false;
    trace_on = false;
    debugger_on = false;
    export_on = false;
    parse_on = false;
    autocorrect_on = false;
    report_bals = false;
    json_on = false;
    kBlock = 0;
    offset = 0;
    minArgs = 0;
    theWidth = 23;
}

//---------------------------------------------------------------------------------------------------
COptions::COptions(void)
    : transStats(),
      blockStats(),
      setSorts(GETRUNTIME_CLASS(CBlock), GETRUNTIME_CLASS(CTransaction), GETRUNTIME_CLASS(CReceipt));
#ifdef DEBUGGER_ON
tBuffer(),
#endif
    transFmt(""), traceFmt(""), esc_hit(false) {
    Init();
    barLen(80);
    // BEG_CODE_NOTES
    // END_CODE_NOTES

    // BEG_ERROR_MSG
    // END_ERROR_MSG
}

//--------------------------------------------------------------------------------
COptions::~COptions(void) {
}

//-----------------------------------------------------------------------
string_q cleanFmt2(const string_q& str) {
    return (substitute(
        substitute(substitute(substitute(substitute((str), "\\n\\\n", "\\n"), "\n", ""), "\\n", "\n"), "\\t", "\t"),
        "\\r", "\r"));
}

//-----------------------------------------------------------------------
// const char* defTransFmt = "{ \"date\": \"[{DATE}]\", \"from\": \"[{FROM}]\", \"to\": \"[{TO}]\", \"value\":
// \"[{VALUE}]\" }";
const char* defTransFmt =
    "+=+ \"date\": \"[{DATE}]\", \"from\": \"[{FROM}]\", \"to\": \"[{TO}]\", \"value\": \"[{VALUE}]\" =+=";
const char* defTraceFmt = "{ \"[{DATESH}]\", \"[{TIME}]\", \"[{FROM}]\", \"[{TO}]\", \"[{VALUE}]\" }";
