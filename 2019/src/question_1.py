def sortOrders(num_orders: int, order_list: list) -> list:
    # Like the question says, prime orders should come first, and then within the prime orders
    # sort over the metadata, which is everything after the identifier.
    prime_orders: list = sorted(filter(is_prime_order, order_list), key=lambda k: (k.split()[1:], k.split()[0]))

    # Non-Prime orders
    non_prime_orders: list = list(filter(lambda v: not is_prime_order(v), order_list))

    return prime_orders + non_prime_orders


def is_prime_order(order_info: str) -> bool:
    return order_info.split()[1].isalpha()
