#include <cassert>
#include <iostream>
#include <string>
#include <unordered_map>

#include "lfw-core/utils/string_parser/match_all.hpp"
#include "lfw-core/utils/string_parser/match_block.hpp"
#include "lfw-core/utils/string_parser/match_colon_value.hpp"
#include "lfw-core/utils/string_parser/match_hash_end.hpp"
#include "lfw-core/utils/string_parser/take_blocks.hpp"
#include "lfw-core/utils/string_parser/take_sections.hpp"
#include "lfw-core/base/Fields.h"

using namespace string_parser;

// ========================================================================
static void test_match_all()
{
  auto results = match_all("aa bb cc aa dd", std::regex(R"(aa)"));
  assert(results.size() == 2);
  assert(results[0] == "aa");
  assert(results[1] == "aa");
}

static void test_match_all_callback()
{
  int count = 0;
  match_all("x1 x2 x3", std::regex(R"(x\d)"),
            [&](const std::smatch &)
            { ++count; });
  assert(count == 3);
}

static void test_match_block()
{
  auto blocks = match_block("<tag>hello</tag> <tag>world</tag>", "<tag>", "</tag>");
  assert(blocks.size() == 2);
  assert(blocks[0] == "hello");
  assert(blocks[1] == "world");
}

static void test_match_block_once()
{
  auto result = match_block_once("<name>Arthur</name>", "<name>", "</name>");
  assert(result.has_value());
  assert(result.value() == "Arthur");

  auto none = match_block_once("no tags here", "<x>", "</x>");
  assert(!none.has_value());
}

static void test_match_colon_value()
{
  auto pairs = match_colon_value("  hp: 100  mp: 50  ");
  assert(pairs.size() == 2);
  assert(pairs[0].first == "hp" && pairs[0].second == "100");
  assert(pairs[1].first == "mp" && pairs[1].second == "50");
}

static void test_match_colon_value_callback()
{
  int count = 0;
  match_colon_value("a: 1 b: 2", [&](const std::string &k, const std::string &v)
                    { ++count; });
  assert(count == 2);
}

static void test_match_hash_end()
{
  auto result = match_hash_end("some text #comment\n");
  assert(result.has_value());
  assert(result.value() == "comment");

  auto none = match_hash_end("no hash here");
  assert(!none.has_value());
}

static void test_take_blocks()
{
  auto [blocks, remains] = take_blocks("pre<tag>A</tag>mid<tag>B</tag>post", "<tag>", "</tag>");
  assert(blocks.size() == 2);
  assert(blocks[0] == "A");
  assert(blocks[1] == "B");
  assert(remains == "premidpost");
}

static void test_take_blocks_no_match()
{
  auto [blocks, remains] = take_blocks("plain text", "[", "]");
  assert(blocks.empty());
  assert(remains == "plain text");
}

static void test_take_sections()
{
  auto [sections, remains] = take_sections<>(R"(
    header
    <section>
      name: Hero
      hp:   100
      mp:   50
    </section>
    footer
    <section>
      name: Boss
      hp:   500
    </section>
    tail
  )",
                                             "<section>", "</section>");

  assert(sections.size() == 2);

  assert(sections[0]["name"] == "Hero");
  assert(sections[0]["hp"] == "100");
  assert(sections[0]["mp"] == "50");

  assert(sections[1]["name"] == "Boss");
  assert(sections[1]["hp"] == "500");
}

struct Hero
{
  std::string name;
  int hp = 0;
  int mp = 0;
};

static const auto &hero_fields_ref()
{
  static const auto fs = fields<Hero>(
      field("name", FieldKind::Str, &Hero::name, "名称"),
      field("hp", FieldKind::Int, &Hero::hp, "生命"),
      field("mp", FieldKind::Int, &Hero::mp, "魔法"));
  return fs;
}

static void test_take_sections_struct()
{
  auto [sections, remains] = take_sections<Hero>(
      R"(
    <hero>
      name: Arthur
      hp:   200
      mp:   80
    </hero>
    <hero>
      name: Lancelot
      hp:   150
    </hero>
  )",
      "<hero>", "</hero>",
      hero_fields_ref());

  assert(sections.size() == 2);
  assert(sections[0].name == "Arthur");
  assert(sections[0].hp == 200);
  assert(sections[0].mp == 80);

  assert(sections[1].name == "Lancelot");
  assert(sections[1].hp == 150);
  assert(sections[1].mp == 0); // not present
}

// ========================================================================
void run_string_parser_tests()
{
  std::cout << "  --- string_parser ---\n";

  test_match_all();
  test_match_all_callback();
  test_match_block();
  test_match_block_once();
  test_match_colon_value();
  test_match_colon_value_callback();
  test_match_hash_end();
  test_take_blocks();
  test_take_blocks_no_match();
  test_take_sections();
  test_take_sections_struct();

  std::cout << "  PASS: string_parser (11 subtests)\n";
}
