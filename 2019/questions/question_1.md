# About 

Amazon is planning to release a new order prioritization algorithm to optimize fulfilling Prime deliverise on time. All orders (Prime or otherwise) are given an alphanumeric ID code. However, Prime orders are given additional metadata that consists of a space delimited string of positive integers. Each order is therefore defined as their alphanumeric ID code, followed by a space, followed by their space delimited metadata.

You have been tasked with sorting a list of all orders in the order queue to assist in prioritization of fulfillment. They should be sorted according to the following order.

1. The prime orders should be returned first, sorted by lexigraphic sort of the alphabetic metadata.
2. Only in the case of ties, the identifier should be used as a backup sort.
3. The remaining non-Prime orders must come after, in the original order they were given in the input.

Write a function or method to sort the orders according to this pattern.

# Input 

The input to the function/method consists of two arguments;
*num_orders* is an integer representing the number of orders.
*order_list*, a list of strings representing all of the orders.

# Output

Return a list of strings representing the correctly prioritized orders.

# Note 

The order identifier consists of only lower case English characters and numbers.