from collections import deque

class TreeNode:
    def __init__(self, key):
        self.val = key
        self.left = None
        self.right = None

class BinarySearchTree:
    def __init__(self):
        self.root = None

    # ==========================================
    # 1. INSERTION
    # ==========================================
    def insert(self, key):
        """Inserts a new key into the BST."""
        if self.root is None:
            self.root = TreeNode(key)
        else:
            self._insert_recursive(self.root, key)

    def _insert_recursive(self, node, key):
        if key < node.val:
            if node.left is None:
                node.left = TreeNode(key)
            else:
                self._insert_recursive(node.left, key)
        elif key > node.val:
            if node.right is None:
                node.right = TreeNode(key)
            else:
                self._insert_recursive(node.right, key)
        # Note: If key == node.val, we do nothing (assuming no duplicates allowed)

    # ==========================================
    # 2. SEARCHING
    # ==========================================
    def search(self, key):
        """Returns True if the key exists in the tree, False otherwise."""
        return self._search_recursive(self.root, key)

    def _search_recursive(self, node, key):
        if node is None:
            return False
        if node.val == key:
            return True
        if key < node.val:
            return self._search_recursive(node.left, key)
        return self._search_recursive(node.right, key)

    # ==========================================
    # 3. MIN / MAX / HEIGHT
    # ==========================================
    def get_min(self, node=None):
        """Finds the minimum value in the tree (leftmost node)."""
        current = node if node else self.root
        if current is None:
            return None
        while current.left is not None:
            current = current.left
        return current.val

    def get_max(self, node=None):
        """Finds the maximum value in the tree (rightmost node)."""
        current = node if node else self.root
        if current is None:
            return None
        while current.right is not None:
            current = current.right
        return current.val

    def get_height(self):
        """Returns the height of the tree (number of edges on longest path)."""
        return self._height_recursive(self.root)

    def _height_recursive(self, node):
        if node is None:
            return -1 # Return 0 if you count nodes instead of edges
        left_height = self._height_recursive(node.left)
        right_height = self._height_recursive(node.right)
        return 1 + max(left_height, right_height)

    # ==========================================
    # 4. DELETION
    # ==========================================
    def delete(self, key):
        """Deletes a key from the BST and rebalances."""
        self.root = self._delete_recursive(self.root, key)

    def _delete_recursive(self, node, key):
        if node is None:
            return node

        # Step 1: Find the node to delete
        if key < node.val:
            node.left = self._delete_recursive(node.left, key)
        elif key > node.val:
            node.right = self._delete_recursive(node.right, key)
        else:
            # Step 2: Node found. Handle the 3 cases of deletion:
            
            # Case A: Node has only one child or no child
            if node.left is None:
                return node.right
            elif node.right is None:
                return node.left

            # Case B: Node has two children
            # Find the inorder successor (smallest in the right subtree)
            temp_val = self.get_min(node.right)
            # Copy the successor's content to this node
            node.val = temp_val
            # Delete the successor
            node.right = self._delete_recursive(node.right, temp_val)

        return node

    # ==========================================
    # 5. TRAVERSALS
    # ==========================================
    def inorder(self):
        """Left -> Root -> Right (Returns elements in sorted ascending order)"""
        result = []
        self._inorder_recursive(self.root, result)
        return result

    def _inorder_recursive(self, node, result):
        if node:
            self._inorder_recursive(node.left, result)
            result.append(node.val)
            self._inorder_recursive(node.right, result)

    def preorder(self):
        """Root -> Left -> Right (Useful for copying a tree)"""
        result = []
        self._preorder_recursive(self.root, result)
        return result

    def _preorder_recursive(self, node, result):
        if node:
            result.append(node.val)
            self._preorder_recursive(node.left, result)
            self._preorder_recursive(node.right, result)

    def postorder(self):
        """Left -> Right -> Root (Useful for deleting a tree)"""
        result = []
        self._postorder_recursive(self.root, result)
        return result

    def _postorder_recursive(self, node, result):
        if node:
            self._postorder_recursive(node.left, result)
            self._postorder_recursive(node.right, result)
            result.append(node.val)

    def level_order(self):
        """Breadth-First Search (BFS) - Level by level top-down"""
        if self.root is None:
            return []
        
        result = []
        queue = deque([self.root])
        
        while queue:
            node = queue.popleft()
            result.append(node.val)
            if node.left:
                queue.append(node.left)
            if node.right:
                queue.append(node.right)
                
        return result

# ==========================================
# EXAMPLE USAGE
# ==========================================
if __name__ == "__main__":
    bst = BinarySearchTree()
    
    # Insert elements
    elements = [50, 30, 20, 40, 70, 60, 80]
    for el in elements:
        bst.insert(el)

    print("Inorder Traversal (Sorted):", bst.inorder())
    print("Level-order Traversal (BFS):", bst.level_order())
    
    print("\nTree Min:", bst.get_min())
    print("Tree Max:", bst.get_max())
    print("Tree Height:", bst.get_height())
    
    print("\nSearching for 40:", bst.search(40))
    print("Searching for 99:", bst.search(99))
    
    print("\nDeleting 20 (Leaf Node)...")
    bst.delete(20)
    print("Inorder after deletion:", bst.inorder())
    
    print("\nDeleting 50 (Root Node with 2 children)...")
    bst.delete(50)
    print("Inorder after deletion:", bst.inorder())
    print("New Root is:", bst.root.val)
