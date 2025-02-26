#include <gtest/gtest.h>
#include <format-string-check.h>

TEST(FormatTest, EmptyString) {
    auto empty = format<"">();
    EXPECT_TRUE(empty.empty());
}

TEST(FormatTest, SinglePlaceholder) {
    EXPECT_EQ(format<"{}">(123), "123");
    EXPECT_EQ(format<"Befor {}">(123), "Befor 123");
    EXPECT_EQ(format<"{} After">(123), "123 After");
    EXPECT_EQ(format<"Befor {} After">(123), "Befor 123 After");
}

TEST(FormatTest, TwoPlaceholders) {
    EXPECT_EQ(format<"{} {}">(123, "aa"), "123 aa");

    EXPECT_EQ(format<"{} middle {}">(123, "aa"), "123 middle aa");
    EXPECT_EQ(format<"Befor {} middle {}">(123, "aa"), "Befor 123 middle aa");

    EXPECT_EQ(format<"Befor {} middle {} after">(123, "aa"), "Befor 123 middle aa after");
}
