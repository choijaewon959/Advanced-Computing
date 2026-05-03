//
// Created by Mohammed RHAZI on 02/05/2026.
//
#include <cassert>
#include "OrderBook.h"

void testAddOrder(){
    OrderBook book;
    book.addOrder("ORD001", 50.10, 100, true);

    assert(book.orderLookup.count("ORD001") == 1);
}