#include "AppUtils.h"

#include <iostream>
#include <istream>
#include <ostream>

#include <boost/algorithm/string.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <fifo_map.hpp>
#include <nlohmann/json.hpp>

namespace pt = boost::property_tree;

void removeUnrecognizedXmlPatterns(std::string& htmlContent) {
  std::size_t pos{0};
  while (std::string::npos != (pos = htmlContent.find("<script async", pos))) {
    constexpr std::size_t closingCharOffset = 13;
    if (htmlContent[pos + closingCharOffset ] == '>') {
      constexpr std::size_t spaceOffset = 7;
      // replace '<script async>' with '<script>      '
      htmlContent.replace(pos + spaceOffset, 6, ">      ");
    } else {
      constexpr std::size_t asyncWordOffset = 8;
      constexpr std::size_t asyncWordLen{5};
      // replace '<script async name="val"...' with <script       name="val"...
      htmlContent.replace(pos + asyncWordOffset, asyncWordLen, asyncWordLen,
                          ' ');
    }
  }

  pos = 0;
  while (std::string::npos != (pos = htmlContent.find("async src=", pos))) {
    constexpr std::size_t asyncWordLen{5};
    // replace 'async src=...' with '      src=...'
    htmlContent.replace(pos, asyncWordLen, asyncWordLen, ' ');
  }
}

std::vector<BriefItem> cutBriefItems(const std::string& timeContent) {
  std::size_t pos{0};

  auto findNext = [&](const char* tag) {
    pos = timeContent.find(tag, pos);
    if (std::string::npos == pos)
      throw std::runtime_error("tag '" + std::string(tag) + "' was not found");
  };

  findNext(">The Brief</div>");

  std::vector<BriefItem> briefItems(6, BriefItem{});

  for (auto& item : briefItems) {
    findNext("<div class=\"column-tout  \">");
    findNext("<div class='column-tout-info '>");
    findNext("<a href=\"");

    constexpr std::size_t refOffset = 9;
    pos += refOffset;
    auto refStartPos = pos;
    findNext("\">");
    item.ref = timeContent.substr(refStartPos, pos - refStartPos);

    constexpr std::size_t descOffset = 2;
    pos += descOffset;
    auto descStartPos = pos;
    findNext("</a>");
    item.desc = timeContent.substr(descStartPos, pos - descStartPos);
    boost::trim(item.desc);
  }

  return briefItems;
}

namespace {
  using namespace nlohmann;

  // by defaul json keeps key values in std::map which means while they are
  // dumped into string first item which appears is link rather then title.
  // To avoid this issue json library suggest to use fifo_map:
  //
  // https://github.com/nlohmann/json#notes
  template <class K, class V, class dummy_compare, class A>
  using my_workaround_fifo_map =
      fifo_map<K, V, nlohmann::fifo_map_compare<K>, A>;
  using my_json = basic_json<my_workaround_fifo_map>;

}  // namespace

std::string serializeToJsonString(const std::vector<BriefItem>& briefItems) {
  my_json news = my_json::array();
  for(const auto& item: briefItems) {
    my_json itemView;
    itemView["title"] = item.desc;
    itemView["link"] = "https://time.com/" + item.ref;
    news.push_back(itemView);
  }
  my_json root;
  root["news"] = news;

  return root.dump(2);
}

std::string getBriefsFromTimeContent(const std::string& timeContent) {
  std::istringstream is{timeContent};

  pt::ptree tree;
  pt::xml_parser::read_xml(is, tree);

  std::ostringstream os;
  pt::json_parser::write_json(os, tree);

  return os.str();
}
