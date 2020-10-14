std::string JSON_API GetPinYin(std::string jsonStr) { return "xxxx"; }

int GetPinYinLen(int len) { return 7; }

#include <windows.h>

std::wstring CharToWchar(const char* c, size_t m_encode = CP_ACP) {
  std::wstring str;
  int len = MultiByteToWideChar(m_encode, 0, c, strlen(c), NULL, 0);
  wchar_t* m_wchar = new wchar_t[len + 1];
  MultiByteToWideChar(m_encode, 0, c, strlen(c), m_wchar, len);
  m_wchar[len] = '\0';
  str = m_wchar;
  delete m_wchar;
  return str;
}

std::string WcharToChar(const wchar_t* wp, size_t m_encode = CP_ACP) {
  std::string str;
  int len =
      WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), NULL, 0, NULL, NULL);
  char* m_char = new char[len + 1];
  WideCharToMultiByte(m_encode, 0, wp, wcslen(wp), m_char, len, NULL, NULL);
  m_char[len] = '\0';
  str = m_char;
  delete m_char;
  return str;
}

class Json::StreamWriterBuilder;

std::string JsonToString(const Json::Value& root) {
  static Json::Value def = []() {
    Json::Value def;
    Json::StreamWriterBuilder::setDefaults(&def);
    def["emitUTF8"] = true;
    return def;
  }();

  std::ostringstream stream;
  Json::StreamWriterBuilder stream_builder;
  stream_builder.settings_ = def; // Config emitUTF8
  std::unique_ptr<Json::StreamWriter> writer(stream_builder.newStreamWriter());
  writer->write(root, &stream);
  return stream.str();
}

int JSON_API GetPinYinXPtr(char* jsonStr, int jsonLen, char* pinYin,
                           int pinYinLen) {
  if (jsonStr == NULL) {
    return 77;
  }
  std::string jsonMsg = WcharToChar((wchar_t*)jsonStr);

  if (pinYin) {
    int wPinYinLen = pinYinLen * 2;
    memset(pinYin, 0, wPinYinLen);
    Json::Reader reader;
    Json::Value jsonVal, jsonCtx, jsonPinYinGroup, jsonPinYin;
    Json::Value def;
    def["emitUTF8"] = true;

    reader.parse(jsonMsg, jsonVal);
    std::cout << "jsonVal:" << jsonVal.toStyledString() << std::endl;
    jsonCtx = jsonVal[0];
    std::cout << "jsonCtx:" << jsonCtx.toStyledString() << std::endl;
    jsonPinYinGroup = jsonCtx[1];
    std::cout << "jsonPinYinGroup:" << jsonPinYinGroup.toStyledString()
              << std::endl;
    jsonPinYin = jsonPinYinGroup[3];
    std::string strPinYin = JsonToString(jsonPinYin);  // jsonPinYin.toStyledString();
    std::cout << strPinYin << std::endl;
    memcpy(pinYin, (void*)strPinYin.c_str(), pinYinLen);
    std::wstring pinYinMsg = CharToWchar(strPinYin.c_str());
    memcpy(pinYin, (void*)pinYinMsg.c_str(), wPinYinLen);
    return 99;
  }
  return 88;
}
