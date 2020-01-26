#pragma once

#include <string>
#include <vector>

struct BriefItem {
  std::string ref;
  std::string desc;
};

std::vector<BriefItem> cutBriefItems(const std::string& timeHtmlContent);

std::string serializeToJsonString(const std::vector<BriefItem>&);
