class Node:

    def __init__(self, data):
        self.data = data
        self.next = None

    def __str__(self):
        return str(self.data)

class Queue:

    def __init__(self):
        self.head = None
        self.tail = None

    def put(self, node):
        if self.head is None:
            self.head = node
            self.tail = node
            return

        self.tail.next = node
        self.tail = node

    def get(self):
        if self.head is None:
            return None

        if self.head.next is None:
            temp = self.head
            self.head = None
            self.tail = None
            return temp

        temp = self.head
        self.head = self.head.next
        return temp

    def update(self):
        current = self.head

        while current is not None:
            current.data.update()
            current = current.next

    def draw(self):
        current = self.head

        while current is not None:
            current.data.draw()
            current = current.next

    def __str__(self):
        result = ""
        current = self.head

        while current is not None:
            result += str(current)
            current = current.next

        return result + '\n'