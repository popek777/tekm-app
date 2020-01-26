#include <iostream>
#include <string>

#include "AppUtils.h"
#include "HttpsUtils.h"

int main() {

  auto timeContent = https::get("time.com", "443", "/");
  auto briefItems = cutBriefItems(timeContent);

  std::cout << serializeToJsonString(briefItems) << std::endl;

  return 0;
}
