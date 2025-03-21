class MinStack:

    def __init__(self):
        self.stack = []

    def push(self, val: int) -> None:
        min_val = val
        if self.stack and self.stack[-1][1] < min_val:
            min_val = self.stack[-1][1]
        self.stack.append((val, min_val))

    def pop(self) -> None:
        return self.stack.pop()[0]

    def top(self) -> int:
        return self.stack[-1][0]

    def getMin(self) -> int:
        return self.stack[-1][1]
