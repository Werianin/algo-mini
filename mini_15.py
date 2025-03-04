class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def reverse_between(head, left, right):
    cur_node = head
    for _ in range(left):
        cur_node = cur_node.next

    prev = cur_node
    cur_node = cur_node.next

    for _ in range(right - left):
        temp = cur_node.next
        prev = cur_node
        cur_node.next = left.next
        left.next = cur_node
        prev.next = temp
        cur_node = temp
