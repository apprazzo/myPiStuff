#include "Parser.h"

using namespace std;

ENUM_MSG_TYPE operator++(ENUM_MSG_TYPE& f, int) { // int denotes postfix++
	if (f == NUMBER_OF_ELEMENTS) return f = NUMBER_OF_ELEMENTS; // rollover
	int temp = f;
	return f = static_cast<ENUM_MSG_TYPE> (++temp);
}

CParser::CParser() {
	m_msgToParse = "";
	m_msgLength = m_msgToParse.length();
	for (ENUM_MSG_TYPE i = UNKNOWN; i < NUMBER_OF_ELEMENTS; i++) {
		m_map_enum_string[i] = MSG_TYPE_STRINGS[i];
		m_map_enum_Indicator[INDICATOR[i]] = i;
	}
	//printMaps();
}

CParser::~CParser() {
}

parsed_msg CParser::parseMSG(const string msgToParse) {
	m_msgToParse = msgToParse;
	m_msgLength = parseMsgLength(m_msgToParse);
	removeNewLine();

	m_parsed_msg.m_msgType = parseTypeOfMsg();
	parseRestOfMsg();

	return m_parsed_msg;
}

int CParser::parseMsgLength(const string msg) {
	if (msg.empty()) {
		throw invalid_argument("message is empty");
	}
	else
		return msg.length();
}

bool CParser::msgHasOnlyEndingNewLine(const string msg) {
	if (msg.find("\n") == string::npos) {
		throw invalid_argument("message does not have a new line (\\n)");
	}
	else {
		int first = msg.find_first_of("\n");
		int last = msg.find_last_of("\n");
		if (first == last) {
			if (first == m_msgLength - 1) {
				return true;
			}
			else {
				throw invalid_argument("new line (\\n) does not finish the message");
			}
		}
		else {
			throw invalid_argument("message does have multiple new lines (\\n)");
		}
	}
}

void CParser::removeNewLine() {
	if (msgHasOnlyEndingNewLine(m_msgToParse)) {
		m_msgToParse.erase(m_msgToParse.end() - 1);
	}
	else {
		throw invalid_argument("new line (\\n) could not be removed");
	}
}

void CParser::printMsgToParse() {
	cout << "message to parse: " << m_msgToParse << endl;
}

ENUM_MSG_TYPE CParser::parseTypeOfMsg() {
	string parsedMsgType = "";
	size_t posColon = string::npos;
	posColon = m_msgToParse.find_first_of("\t");

	if (posColon != string::npos) {
		parsedMsgType = m_msgToParse.substr(0, posColon);
		m_restMsg = m_msgToParse.substr(posColon + 1);

		map<string, ENUM_MSG_TYPE>::iterator it = m_map_enum_Indicator.find(parsedMsgType);
		if (it != m_map_enum_Indicator.end()) {
			return it->second;
		}
		else {
			throw invalid_argument("unknown type of message");
		}
	}
	else {
		throw invalid_argument("Indicator separating Tab (\\t) is missing");
	}
}

void CParser::parseRestOfMsg() {
	switch (m_parsed_msg.m_msgType) {
	case COMMAND:
	case MESSAGE:
		m_parsed_msg.m_msg = m_restMsg;
		m_restMsg = "";
		checkEndOfMsg();
		break;
	case INFORMATION:
		parseTag();
		parseValues();
		checkEndOfMsg();
		break;
	case ERROR:
		parseTag();
		parseMsg();
		checkEndOfMsg();
		break;
	case REQUEST:
		parseTag();
		checkEndOfMsg();
		break;
	default:
		throw invalid_argument("parsing rest of message failed");
		break;
	
	}
}


void CParser::parseTag()
{
	string probableTag = "";
	size_t posColon = string::npos;
	posColon = m_restMsg.find_first_of("\t");

	try
	{
		if (m_parsed_msg.m_msgType == REQUEST) {
			if (posColon != string::npos) {
				throw invalid_argument("additional tab (\\t) found on your request");
			}
			probableTag = m_restMsg;
			m_restMsg = "";

			look4correctTag(probableTag);
		}

		else if (posColon != string::npos) {
			probableTag = m_restMsg.substr(0, posColon);
			m_restMsg = m_restMsg.substr(posColon + 1);

			look4correctTag(probableTag);
		}
		else {
			throw invalid_argument("Tag separating Tab (\\t) is missing");
		}
	}
	catch (const std::invalid_argument e) {
		throw e;
	}
	catch (const std::exception e) {
		throw e;
	}
}

void CParser::parseMsg()
{
	size_t posColon = string::npos;
	posColon = m_restMsg.find_first_of("\t");
	if (posColon = string::npos) {
		m_parsed_msg.m_msg = m_restMsg;
		m_restMsg = "";
	}
	else {
		throw invalid_argument("Invalid additional Tab (\\t) in message");
	}
}

void CParser::parseValues()
{
	try {
		if (!m_parsed_msg.m_tag.compare("TH")) {
			size_t posColon = string::npos;
			posColon = m_restMsg.find_first_of("\t");

			if (posColon == string::npos) {
				throw invalid_argument("insufficient number of arguments");
			}
			else {
				m_parsed_msg.m_value1 = stod(m_restMsg.substr(0, posColon));
				m_restMsg = m_restMsg.substr(posColon + 1);

				posColon = m_restMsg.find_first_of("\t");
				if (posColon == string::npos) {
					m_parsed_msg.m_value2 = stod(m_restMsg.substr(0, posColon));
					m_restMsg = "";
				}
				else {
					throw invalid_argument("too many arguments");
				}
			}
		}
		else {
			m_parsed_msg.m_value1 = stod(m_restMsg);
			m_restMsg = "";
		}
	}
	catch (invalid_argument e) {
		string exMsg = e.what();
		if ((!exMsg.compare("insufficient number of arguments")) 
			|| (!exMsg.compare("too many arguments"))) {
			throw e;
		}
		else {
			exMsg = m_restMsg;
			exMsg.append(" is not of kind double");
			throw invalid_argument(exMsg);
		}
	}
	// TODO: TEST
	catch (out_of_range e) {
		string exMsg = m_restMsg;
		exMsg.append(" is out of range of double");
		throw out_of_range(exMsg);
	}
	catch (exception e) {
		throw e;
	}
}

void CParser::look4correctTag(string probableTag)
{
	set<string>::iterator it;
	for (it = TAGS.begin(); it != TAGS.end(); ++it) {
		if (!probableTag.compare(*it)) {
			m_parsed_msg.m_tag = probableTag;
			return;
		}
	}
	m_parsed_msg.m_tag = "NoTag";
	string throwmsg = "invalid Tag: ";
	throwmsg.append(probableTag);
	throw invalid_argument(throwmsg);
}

bool CParser::checkEndOfMsg()
{
	if (m_restMsg.empty()) {
		return true;
	} else {
		throw invalid_argument("excpected end of message not found");
	}
}

void CParser::printMaps() {
	cout << "map Enum String" << endl;
	for (map<ENUM_MSG_TYPE, string>::iterator it = m_map_enum_string.begin();
		it != m_map_enum_string.end(); ++it) {
		cout << it->first << " - " << it->second << endl;
	}

	cout << "map Enum Indicator" << endl;
	for (map<string, ENUM_MSG_TYPE>::iterator it = m_map_enum_Indicator.begin();
		it != m_map_enum_Indicator.end(); ++it) {
		cout << it->first << " - " << it->second << endl;
	}
}

void CParser::printParsedMsg(const parsed_msg pm) {
	cout << "message is of type: " << MSG_TYPE_STRINGS[pm.m_msgType] << endl;
	cout << "tag = " << pm.m_tag << endl;
	cout << "message = " << pm.m_msg << endl;
	cout << "value 1 = " << to_string(pm.m_value1) << endl;
	cout << "value 2 = " << to_string(pm.m_value2) << endl;
}
