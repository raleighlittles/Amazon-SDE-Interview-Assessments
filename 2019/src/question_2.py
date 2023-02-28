def optimalUtilization(maxTravelDist: int, forwardRouteList: list, returnRouteList: list) -> list:
    """
    Sort both list of routes by their distance, in decreasing order.
    Then discard any route greater than or equal to the maximum travel distance.
    Then, pick the longest route in the forward direction. (Either direction would work here)
    Once you have the longest forward route, go down the list of returning routes (in sorted order),
    and make sure that the distance of the forward route you picked earlier plus the distance of
    the current returning route does not exceed the safe travel distance.
    If you find a pair whose sum does not exceed the safe travel distance, store that as the best
    route pair.
    Keep repeating this process as you go down the current list of returning routes. Once you've
    performed this process for all return routes for the given forward route you chose, move
    on to the next longest route. If the distance of the forward route plus the distance of the
    return route do not exceed the length of the best distance, then keep going (remember that the routes are sorted!)

    :param maxTravelDist:
    :param forwardRouteList:
    :param returnRouteList:
    :return:
    """
    optimal_route_pairs = []
    best_distance = 0

    sortedForwardRoutes = sorted(forwardRouteList, key=lambda k: k[1], reverse=True)
    sortedReturnRoutes = sorted(returnRouteList, key=lambda k: k[1], reverse=True)

    for forward_route in sortedForwardRoutes:
        fwd_route_id, fwd_route_length = forward_route

        if fwd_route_length >= maxTravelDist:
            # Skip this forward route if it is greater than or equal to the maximum distance
            # If this route is exactly equal to the maximum distance, then you wouldn't have
            # enough "fuel" to make the return leg of the journey.
            continue

        for return_route in sortedReturnRoutes:
            ret_route_id, ret_route_length = return_route

            # Have you found the best distance yet?
            if (best_distance == 0):
                # If not, check if this route could be your best distance.
                if (fwd_route_length + ret_route_length) <= maxTravelDist:
                    # If you haven't found a best distance yet, and the sum of these route lengths
                    # are within your safe travel distance, then this is your best route (for now).
                    best_distance = fwd_route_length + ret_route_length
                    optimal_route_pairs.append([fwd_route_id, ret_route_id])

                else:
                    # If this combination of forward route and return route are longer than the max
                    # travel distance, then go on to the next longest return route
                    continue


            else:
                # If you've seen a best distance so far, check if this route exceeds that distance
                if (fwd_route_length + ret_route_length) < best_distance:
                    # If this combined route length doesn't match your best distance, then it can't
                    # be in the optimal set; and further, since you've been iterating over the trips
                    # sorted by length first, by the time you reach here, you are done, there cannot be another optimal path.
                    break

                elif (fwd_route_length + ret_route_length == best_distance):
                    optimal_route_pairs.append([fwd_route_id, ret_route_id])

    return optimal_route_pairs
