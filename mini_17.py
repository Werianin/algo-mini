import heapq

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def merge_sorted_lists(lists):
    heap = []

    for l in lists:
        if l:
            heapq.heappush(heap, (l.val, l))

    start = ListNode(0)
    cur = start

    while heap:
        val, l = heapq.heappop(heap)
        cur.next = node
        cur = cur.next

        if node.next:
            heapq.heappush(heap, (l.next.val, l.next))

    return start.next
