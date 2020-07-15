#include "Checkout.h"


Checkout::Checkout()
: total(0)
{
    // @todo
}


Checkout::~Checkout()
{
    // @todo
}


void Checkout::addItemPrice(std::string item, int price)
{
    prices[item] = price;
}


void Checkout::addItem(std::string item)
{
    // Determine if the item exist
    auto priceIter = prices.find(item);
    if(priceIter == prices.end())
    {
        throw std::invalid_argument("Invalid item. No price found!");
    }

    // Add number of Item if exist
    items[item]++;
}


int Checkout::calculateTotal()
{
    // Set total to 0
    total = 0;

    // Loop through the items "map"
    for(std::map<std::string, int>::iterator itemIter = items.begin(); itemIter != items.end(); itemIter++)
    {
        std::string item = itemIter->first;
        int itemCnt = itemIter->second;

        calculateItem(item, itemCnt);
    }
    return total;
}


void Checkout::calculateItem(std::string item, int itemCnt)
{
    auto discountIter = discounts.find(item);
    if(discountIter != discounts.end())
    {
        auto discount = discountIter->second;
        calculateDiscount(item, itemCnt, discount);
    }
    else
    {
        total += itemCnt * prices[item];
    }
    
}


void Checkout::calculateDiscount(std::string item, int itemCnt, Discount discount)
{
    if(itemCnt >= discount.number_of_item)
    {
        int nbrOfDiscounts = itemCnt / discount.number_of_item;
        total += nbrOfDiscounts * discount.discount_price;
        int remainingItems = itemCnt % discount.number_of_item;
        total += remainingItems * prices[item];
    }
    else
    {
        total += itemCnt * prices[item];
    }
}


void Checkout::addDiscount(std::string item, int number, int discountPrice)
{
    Discount discount;
    discount.number_of_item = number;
    discount.discount_price = discountPrice;
    discounts[item] = discount;
}