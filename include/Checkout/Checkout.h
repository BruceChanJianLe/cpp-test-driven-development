#ifndef CHECKOUT_H_
#define CHECKOUT_H_

#include <string>
#include <map>


class Checkout
{
    public:
        Checkout();
        virtual ~Checkout();

        void addItemPrice(std::string item, int price);
        void addItem(std::string item);
        int calculateTotal();
        void addDiscount(std::string item, int number, int discountPrice);

    protected:
        struct Discount
        {
            int number_of_item;
            int discount_price;
        };
        
        std::map<std::string, int> prices;
        std::map<std::string, Discount> discounts;
        std::map<std::string, int> items;
        int total;

        void calculateItem(std::string item, int ItemCnt);
        void calculateDiscount(std::string item, int itemCnt, Discount discount);
};
#endif // CHECKOUT_H_