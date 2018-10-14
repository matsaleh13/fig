#include "gtest/gtest.h"

#include "fig_key.h"

#include <map>
#include <unordered_map>

template <typename TChar>
class FigKeyTypedFixture : public ::testing::Test {
public:
  const TChar* input_key_name();
  const TChar* test_key_name();
  const TChar* test_key_name_compare_less();

  typedef std::basic_string<TChar> StringType;
};

template <>
const char* FigKeyTypedFixture<char>::input_key_name() {
  return "Forty-Two";
}

template <>
const wchar_t* FigKeyTypedFixture<wchar_t>::input_key_name() {
  return L"Forty-Two";
}

template <>
const char* FigKeyTypedFixture<char>::test_key_name() {
  return "forty-two";
}

template <>
const wchar_t* FigKeyTypedFixture<wchar_t>::test_key_name() {
  return L"forty-two";
}

template <>
const char* FigKeyTypedFixture<char>::test_key_name_compare_less() {
  return "42";
}

template <>
const wchar_t* FigKeyTypedFixture<wchar_t>::test_key_name_compare_less() {
  return L"42";
}

using MyTypes = ::testing::Types<char, wchar_t>;
TYPED_TEST_CASE(FigKeyTypedFixture, MyTypes);

TYPED_TEST(FigKeyTypedFixture, create_key_from_const_char) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k(this->input_key_name());

  ASSERT_EQ(k.name(), StringType(this->test_key_name()));
}

TYPED_TEST(FigKeyTypedFixture, create_key_from_basic_string) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k(StringType(this->input_key_name()));

  ASSERT_EQ(k.name(), StringType(this->test_key_name()));
}

TYPED_TEST(FigKeyTypedFixture, key_compare_equals) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k(this->input_key_name());

  ASSERT_TRUE(k == KeyType(this->test_key_name()));
}

TYPED_TEST(FigKeyTypedFixture, key_compare_less) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k(this->input_key_name());

  ASSERT_TRUE(KeyType(this->test_key_name_compare_less()) < k);
}

TYPED_TEST(FigKeyTypedFixture, key_hash) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k(this->input_key_name());

  ASSERT_NE(std::hash<KeyType>()(k), 0);

  ASSERT_EQ(std::hash<KeyType>()(k),
            std::hash<StringType>()(this->test_key_name()));
}

TYPED_TEST(FigKeyTypedFixture, key_compare_less_in_map) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k1(this->input_key_name());
  KeyType k2(this->test_key_name_compare_less());

  // ordered map
  std::map<KeyType, int> m;
  m.insert(std::make_pair(k1, 1));
  m.insert(std::make_pair(k2, 2));  // should sort first

  ASSERT_EQ(m.begin()->first, k2);
}

TYPED_TEST(FigKeyTypedFixture, key_lookup_in_unordered_map) {
  using StringType = typename FigKeyTypedFixture::StringType;
  using KeyType = fig::core::FigKey<StringType>;

  KeyType k1(this->input_key_name());
  KeyType k2(this->test_key_name_compare_less());

  std::unordered_map<KeyType, int> m;
  m.insert(std::make_pair(k1, 1));
  m.insert(std::make_pair(k2, 2));  

  ASSERT_EQ(m.find(k1)->second, 1);
}


// TODO: Support other comparisons?
//
// TYPED_TEST(FigKeyTypedFixture, key_compare_not_equals) {
//   fig::core::FigKey<typename FigKeyTypedFixture::StringType> k(
//       this->input_key_name());

//   ASSERT_TRUE(k != fig::core::FigKey<typename
//   FigKeyTypedFixture::StringType>(
//                        this->test_key_name_compare_less()));
// }

// TYPED_TEST(FigKeyTypedFixture, key_compare_less_or_equal) {
//   fig::core::FigKey<typename FigKeyTypedFixture::StringType> k(
//       this->input_key_name());

//   ASSERT_TRUE(fig::core::FigKey<typename FigKeyTypedFixture::StringType>(
//                   this->test_key_name_compare_less()) <= k);
//   ASSERT_TRUE(fig::core::FigKey<typename FigKeyTypedFixture::StringType>(
//                   this->test_key_name()) <= k);
// }

// TYPED_TEST(FigKeyTypedFixture, key_compare_greater) {
//   fig::core::FigKey<typename FigKeyTypedFixture::StringType> k(
//       this->input_key_name());

//   ASSERT_TRUE(k > fig::core::FigKey<typename FigKeyTypedFixture::StringType>(
//                   this->test_key_name_compare_less()));
// }

// TYPED_TEST(FigKeyTypedFixture, key_compare_greater_or_equal) {
//   fig::core::FigKey<typename FigKeyTypedFixture::StringType> k(
//       this->input_key_name());

//   ASSERT_TRUE(k > fig::core::FigKey<typename FigKeyTypedFixture::StringType>(
//                   this->test_key_name_compare_less()));
// }