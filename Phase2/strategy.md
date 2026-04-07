The client introduces a momentum trading strategy based on the last 3 observed prices. 
For each price sent by the server, the client stores the value in a queue of length 3.
The client then checks for momentum (if prices form an increasing or decreasing sequence).
If that is the case client sends an order to the server using priceId. 

To simulate processing latency, the client models a randomized delay before sending an order. If no momentum is registered, the client ignores the price and waits for the next one.

