#pragma once

#include <string>
#include <vector>

struct BriefItem {
  std::string ref;
  std::string desc;
};

std::vector<BriefItem> cutBriefItems(const std::string& htmlContent);

void removeUnrecognizedXmlPatterns(std::string& htmlContent);

std::string getBriefsFromTimeContent(const std::string& timeContent);

std::string serializeToJsonString(const std::vector<BriefItem>&);
