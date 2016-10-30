//#pragma once

#ifndef CPARSER_H
#define CPARSER_H

#include <string>
#include <iostream>
#include <map>
#include <set>

using namespace std;

/*	Aufbau der verschiedenen Nachrichtentypen:
COMMAND:
"CMD:\t	'the command which should be obeyed'\n"
MESSAGE:
"MSG:\t	'message which should be displayed'\n"
INFORMATION:
"INFO:\t	TAG\t	'information about tag's issue'\n"
information can consist of:
- one or two values, depending on the used TAG
values are splitted by a tab ('\t')
ERROR:
"ERR:\t	TAG\t	'details about the error\n"
REQUEST:
"REQ:\t	TAG\n"

*/
enum ENUM_MSG_TYPE { UNKNOWN, COMMAND, MESSAGE, INFORMATION, ERROR, REQUEST, NUMBER_OF_ELEMENTS };

const string MSG_TYPE_STRINGS[NUMBER_OF_ELEMENTS] =
{ "unknown", "command", "message", "information", "error", "request" };

const string INDICATOR[NUMBER_OF_ELEMENTS] =
{ "unknown", "CMD:", "MSG:", "INFO:", "ERR:", "REQ:" };

const set<string> TAGS = { "T", "H", "TH", "NoTag" };

/*	struct that will be returned after parsing
*/
struct parsed_msg {
	ENUM_MSG_TYPE m_msgType = UNKNOWN;
	string m_tag = "";
	string m_msg = "";
	double m_value1 = -273.15;
	double m_value2 = -273.15;
};


class CParser
{
public:
	CParser();
	virtual ~CParser();

	parsed_msg parseMSG(const string msgToParse);

	// prints any parsed_msg
	void printParsedMsg(const parsed_msg pm);

private:
	// Members
	parsed_msg m_parsed_msg;

	map<ENUM_MSG_TYPE, string> m_map_enum_string;
	map<string, ENUM_MSG_TYPE> m_map_enum_Indicator;

	string m_msgToParse;
	string m_restMsg;
	unsigned int m_msgLength;

	// Methods
	int parseMsgLength(const string msg);
	bool msgHasOnlyEndingNewLine(const string msg);
	void printMsgToParse();
	void removeNewLine();
	ENUM_MSG_TYPE parseTypeOfMsg();
	void parseRestOfMsg();
	void parseTag();
	void parseMsg();
	void parseValues();
	void look4correctTag(string probableTag);
	bool checkEndOfMsg();

	void printMaps();
};

#endif