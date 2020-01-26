#include <iostream>
#include <string>

#include "AppUtils.h"
#include "HttpsUtils.h"

int main() {
  auto timeContent = https::get("time.com", "443", "/");
  //removeUnrecognizedXmlPatterns(timeContent);
  auto briefItems = cutBriefItems(timeContent);

  std::cout << serializeToJsonString(briefItems) << std::endl;

  //std::cout << timeContent << std::endl;
  //std::cout << getBriefsFromTimeContent(timeContent) << std::endl;

  return 0;
}
