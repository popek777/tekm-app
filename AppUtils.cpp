#include "AppUtils.h"

#include <boost/algorithm/string.hpp>

#include <fifo_map.hpp>
#include <nlohmann/json.hpp>

// NOTE:
// this is very poor solution (parsing content string 'by hand') however boost
// property tree , nor tooska libraries did not cope with parsing time.com html content
// so I decided to manually parse 'brief items' from html content
std::vector<BriefItem> cutBriefItems(const std::string& timeHtmlContent) {
  std::size_t pos{0};

  auto findNext = [&](const char* tag) {
    pos = timeHtmlContent.find(tag, pos);
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
    item.ref = timeHtmlContent.substr(refStartPos, pos - refStartPos);

    constexpr std::size_t descOffset = 2;
    pos += descOffset;
    auto descStartPos = pos;
    findNext("</a>");
    item.desc = timeHtmlContent.substr(descStartPos, pos - descStartPos);
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

