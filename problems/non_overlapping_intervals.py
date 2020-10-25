#
# Remove minimum intervals to have only non-overlapping intervals
#
# Greedy Approach:
# if we sort intervals based on start time, we shall not be  maximizing possible
# number of non-overlapping intervals. Say an initial large interval masks all other.
# The strategy therefore is to sort intervals based on end time. The interval which
# finishes first, shall become our first non-overlapping candidate.
#
# Similar to Activity Selection Problem. We reduce the problem to maximizing the set
# of non-overlapping intervals.
#
# My initial approach was to compute a rank for each interval and them remove based
# on the maximum rank, till there are no dependencies
#
import sys

def eraseOverlapIntervals(intervals):
	intervals = sorted(intervals, key = lambda x : x[1])
	count = 0
	prev_end = -sys.maxint - 1
	for r in intervals:
		if r[0] > prev_end:
			count += 1
			prev_end = r[1]
	return len(intervals) - count
