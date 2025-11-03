
#include <iostream>
#include<vector>
#include<string>
using namespace std;


enum class OrderType {
    GoodTillCandle,
    FillOrKill
};

enum class Side {
    Buy,
    Sell
};

using Price = uint32_t;
using Quantity = int32_t;
using OrderId = uint64_t;


struct LevelInfo {
    Price price_;
    Quantity quantity_;
};
using LevelInfos = vector<LevelInfo>;


class OrderbookLevelInfos {
public:
    OrderbookLevelInfos(const LevelInfos& bids, const LevelInfos& asks)
        : bids_{ bids }, asks_{ asks }
    { }

    const LevelInfos& GetBids() const { return bids_; }
    const LevelInfos& GetAsks() const { return asks_; }

private:
    LevelInfos bids_;
    LevelInfos asks_;
};

class Order {
public:
    Order(OrderType orderType, OrderId orderId, Side side, Price price, Quantity quantity)
        : orderType_{ orderType }
        , orderId_{ orderId }
        , side_{ side }
        , price_{ price }
        , initialQuantity_{ quantity }
        , remainingQuantity_{quantity}
    { }

    OrderType GetOrderType() const { return orderType_; }
    OrderId GetOrderId() const { return orderId_; }
    Side GetSide() const { return side_; }
    Price GetPrice() const { return price_; }
    Quantity GetInitialQuantity() const { return initialQuantity_; }
    Quantity GetRemainingQuantity() const { return remainingQuantity_; }
    Quantity GetFilledQuantity() const { return GetInitialQuantity() - GetRemainingQuantity(); }
    
    void Fill(Quantity quantity)
    {
        if (quantity > GetRemainingQuantity()) {
            throw logic_error("Order (" + to_string(GetOrderId()) + ") can not be filled for more than it's remaining quantity");
        }

        remainingQuantity_ -= quantity;
    }

private:
    OrderType orderType_;
    OrderId orderId_;
    Side side_;
    Price price_;
    Quantity initialQuantity_, remainingQuantity_;
};

int main()
{
    cout << "Hello World!\n";
}
