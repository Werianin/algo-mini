class Node:
    def __init__(self, data):
        self.data = data
        self.next = None

class LinkedList:
    def __init__(self):
        self.head = None

    def insert_at_end(self, data):
        new_node = Node(data)
        if self.head is None:
            self.head = new_node
            return
        cur_node = self.head
        while cur_node.next:
            cur_node = cur_node.next
        cur_node.next = new_node

    def get_index(self, node):
        ind = 0
        new_node = self.head
        while new_node != node:
            node = node.next
            ind += 1
        return ind



def finding_cycle(head):
    slow = fast = head
    while True:
        for _ in range(2):
            if fast.next is None:
                print('no cycle')
                return
            fast = fast.next
        slow = slow.next
        if slow is fast:
            break
    fast = head
    while fast != slow:
        fast = fast.next.next
        slow = slow.next
    ind = LinkedList.get_index(slow)
    print(f'tail connects to node index {ind}')
