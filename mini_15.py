class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def reverse_between(head, left, right):
    cur_node = head
    while cur_node != left:
        cur_node = cur_node.next
    stack = []
    
    cur_node = cur_node.next
    while cur_node != right:
        stack.append(cur_node)

    cur_node = left
    while stack:
        cur_node.next = stack.pop()
    cur_node.next = right
    return head
