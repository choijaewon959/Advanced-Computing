//
// Created by Mohammed RHAZI on 02/05/2026.
//
#include <cassert>
#include "OrderBook.h"

void testAddOrder() {
    OrderBook book;
    book.addOrder("ORD001", 50.10, 100, true);

    assert(book.orderLookup.count("ORD001") == 1);
    assert(book.orderLookup["ORD001"].quantity == 100);
    assert(book.orderLookup["ORD001"].price == 50.10);
}
void testDeleteOrder() {
    OrderBook book;
    book.addOrder("ORD002", 50.10, 100, true);
    book.deleteOrder("ORD002");

    assert(book.orderLookup.count("ORD002") == 0);
}
void testModifyOrder() {
    OrderBook book;
    book.addOrder("ORD003", 50.10, 100, true);
    book.modifyOrder("ORD003", 50.40, 95);

    assert(book.orderLookup.count("ORD003") == 1);
    assert(book.orderLookup["ORD003"].quantity == 95);
    assert(book.orderLookup["ORD003"].price == 50.40);
}
int main() {
    testAddOrder();
    testDeleteOrder();
    testModifyOrder();
}