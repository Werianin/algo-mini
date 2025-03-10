import heapq

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __lt__(self, another):
        return self.val < another.val

def merge_sorted_lists(lists):
    heap = []

    for i in range(len(lists)):
        if lists[i]:
            heapq.heappush(heap, (lists[i].val, i, lists[i]))

    start = ListNode(0)
    cur = start

    while heap:
        val, idx, node = heapq.heappop(heap)
        cur.next = node
        cur = cur.next

        if node.next:
            heapq.heappush(heap, (node.next.value, idx, node.next))

    return start.next
