#include "gtest/gtest.h"

#include "fig_key.h"

template <typename TChar>
class FigKeyFixture : public ::testing::TestWithParam<const TChar*> {
};

TEST_P(FigKeyFixture, create_key_from_const_char) {
  auto key_value = "forty-two";
  
  fig::core::FigKey<TypeParam> k(key_value);

  ASSERT_EQ(k.name(), TypeParam(key_value));
}

TEST_P(FigKeyFixture, create_key_from_string) {
  auto key_value = TypeParam("forty-two");
  
  fig::core::FigKey<TypeParam> k(key_value);

  ASSERT_EQ(k.name(), TypeParam(key_value));
}


