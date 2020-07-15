#include <iostream>
#include <gtest/gtest.h>
#include "Checkout.h"


class CheckoutTests : public ::testing::Test
{
    public:
        ;
    protected:
        Checkout co;
};


// Comment out duplicated TEST_F
// TEST_F(CheckoutTests, CanAddItemPrice)
// {
//     co.addItemPrice("a", 1);
// }


// TEST_F(CheckoutTests, CanAddItem)
// {
//     co.addItem("a");
// }


TEST_F(CheckoutTests, CanCalculateTotal)
{
    co.addItemPrice("a", 1);
    co.addItem("a");
    int total = co.calculateTotal();
    ASSERT_EQ(1, total);
}


TEST_F(CheckoutTests, CanGetTotalForMultipleItems)
{
    co.addItemPrice("a", 1);
    co.addItemPrice("b", 2);
    co.addItem("a");
    co.addItem("b");
    auto total = co.calculateTotal();
    ASSERT_EQ(3, total);
}


TEST_F(CheckoutTests, CanAddDiscount)
{
    co.addDiscount("a", 3, 2);
}


TEST_F(CheckoutTests, CanCalculateTotalWithDiscount)
{
    co.addItemPrice("a", 1);
    co.addDiscount("a", 3, 2);
    co.addItem("a");
    co.addItem("a");
    co.addItem("a");
    auto total = co.calculateTotal();
    ASSERT_EQ(2, total);
}

TEST_F(CheckoutTests, ItemWithNoPriceThrowException)
{
    ASSERT_THROW(co.addItem("a"), std::invalid_argument);
}