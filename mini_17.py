import heapq

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __lt__(self, another):
        return self.val < another.val

def merge_sorted_lists(lists):
    heap = []

    for node in lists:
        if node:
            heapq.heappush(heap, (node.val, node))

    start = ListNode(0)
    cur = start

    while heap:
        val, node = heapq.heappop(heap)
        cur.next = node
        cur = cur.next

        if node.next:
            heapq.heappush(heap, (node.next.val, node.next))

    return start.next
