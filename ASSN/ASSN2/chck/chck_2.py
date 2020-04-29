#
# POSTECH CSED233 ASSN2 AUTO CHECKER
# Python 3.7+
#
# by beta@plus, gwon minjae.
# special thx to whysw@plus, yang seungwon.
#
# github.com/beta-lux
#

import random
import subprocess
import os

SIZE_TREE_MAX = 15
NUM_TEST_MAX = 100000
NUM_PRINT_PROCESS = 100
NUM_RANGE_TEST_HEAP = 50
FILE_EXECUTABLE = "pa2"
FILE_OUTPUT = "result.csv"

info = lambda x: print(f"[+] {x}")
erro = lambda x: print(f"[-] {x}")
blan = lambda x: print(f"    {x}")


class Node:
    def __init__(self, value: str):
        self.left: Node = None
        self.right: Node = None
        self.value: str = value


class Tree:
    root: Node

    def find_idx(self, tree_str: str, start: int, end: int) -> int:
        if start > end:
            return -1

        result: str = ""

        for idx in range(start, end + 1):
            data = tree_str[idx]
            if data == "(":
                result += data
            elif data == ")":
                if result[-1] == "(":
                    result = result[:-1]
                    if len(result) == 0:
                        return idx

        return -1

    def _build_tree(self, tree_str: str, start: int, end: int) -> type(Node):
        if start > end:
            return None

        node = Node(tree_str[start])
        idx = -1

        if start + 1 <= end and tree_str[start + 1] == "(":
            idx = self.find_idx(tree_str, start + 1, end)

        if idx != -1:
            node.left = self._build_tree(tree_str, start + 2, idx - 1)
            node.right = self._build_tree(tree_str, idx + 2, end - 1)

        return node

    def build_tree(self, tree_str: str):
        self.root = self._build_tree(tree_str, 0, len(tree_str) - 1)

    def pre_order(self):
        result_list = []
        self._pre_order(self.root, result_list)
        return result_list

    def _pre_order(self, node: type(Node), result_list):
        if node is None:
            return
        result_list.append(node.value)
        self._pre_order(node.left, result_list)
        self._pre_order(node.right, result_list)

    def post_order(self):
        result_list = []
        self._post_order(self.root, result_list)
        return result_list

    def _post_order(self, node, result_list):
        if node is None:
            return
        self._post_order(node.left, result_list)
        self._post_order(node.right, result_list)
        result_list.append(node.value)

    def in_order(self):
        result_list = []
        self._in_order(self.root, result_list)
        return result_list

    def _in_order(self, node, result_list):
        if node is None:
            return
        self._in_order(node.left, result_list)
        result_list.append(node.value)
        self._in_order(node.right, result_list)

    def height(self) -> int:
        return self._height(self.root)

    def _height(self, node):
        if node is None:
            return -1
        else:
            return ((self._height(node.left)) if (self._height(node.left) > self._height(node.right)) else (
                self._height(node.right))) + 1

    def is_complete(self):
        h = self.height()
        return self._is_complete(self.root, h, 0, False, True)[0]

    def _is_complete(self, node, height: int, depth: int, is_done: bool, complete: bool) -> (bool, bool):
        if not complete:
            return complete, is_done

        if node is None:
            return (height == depth) or (height == (depth - 1)), is_done
        else:
            if depth == height - 1:
                if is_done:
                    complete = (node.left is None) and (node.right is None)
                else:
                    is_done = (node.left is None) or (node.right is None)
                    complete = not ((node.left is None) and (node.right is not None))
            elif depth != height:
                complete = (node.left is not None) and (node.right is not None)

            (complete, is_done) = self._is_complete(node.left, height, depth + 1, is_done, complete)
            (complete, is_done) = self._is_complete(node.right, height, depth + 1, is_done, complete)
            return complete, is_done


class MinHeap:
    heap_size: int = 0
    heap_arr = [None] * 100

    def print(self):
        res = ""
        for i in range(self.heap_size):
            res += (str(self.heap_arr[i]) + " ")
        return res.strip()

    def parent_idx(self, idx: int) -> int:
        return int((idx - 1) / 2)

    def lc_idx(self, idx: int)->int:
        return (idx*2)+1

    def rc_idx(self, idx: int)->int:
        return (idx*2)+2

    def insert_key(self, k: int):
        self.heap_arr[self.heap_size] = k
        p = self.parent_idx(self.heap_size)
        idx = self.heap_size
        self.heap_size += 1
        while True:
            if idx == 0:
                break
            if self.heap_arr[p] > self.heap_arr[idx]:
                self.heap_arr[p], self.heap_arr[idx] = self.heap_arr[idx], self.heap_arr[p]
            else:
                break
            idx = p
            p = self.parent_idx(idx)

    def delete_min(self):
        if self.heap_size == 0:
            return
        self.heap_size -= 1
        self.heap_arr[0], self.heap_arr[self.heap_size] = self.heap_arr[self.heap_size], None
        self._prop(0)

    def _prop(self, i):
        if i > self.heap_size:
            return

        lc = self.lc_idx(i)
        rc = self.rc_idx(i)
        mi = 0

        if lc >= self.heap_size:
            return
        elif rc >= self.heap_size:
            mi = lc
        else:
            mi = lc if self.heap_arr[lc] < self.heap_arr[rc] else rc

        if self.heap_arr[mi] < self.heap_arr[i]:
            self.heap_arr[mi], self.heap_arr[i] = self.heap_arr[i], self.heap_arr[mi]
            self._prop(mi)



def open_file(file_name):
    is_header = False
    if os.path.exists(file_name):
        rf = open(file_name, "r")
        if rf.readable():
            is_header = ("Task" in rf.readline())

        rf.close()

    af = open(file_name, "a")
    if not is_header:
        af.write("Task\tPython Result\tMy Result\n")
    return af


def parser(cmd_str):
    res = []
    task_num = cmd_str[0]
    cmd_str = cmd_str[4:-2]
    cmd = cmd_str.split("('")[1:]
    for i in cmd:
        t = i.split("'")
        tmp = t[1][1:].split(")")[0]
        res.append([t[0], "NULL" if "NULL" in tmp else int(tmp)])
    return task_num, res


def make_str(res_list):
    result = ""
    for i in res_list:
        result = result + str(i) + " "

    return result[:-1]


def get(exe, cmd_str):
    if os.path.exists("./submit.txt"):
        os.remove("./submit.txt")
    subprocess.call(f"./{exe} {cmd_str}", shell=True)
    f = open("submit.txt")
    return f.read().split("\n")[1]


def rnd_num_str(able: bool = True):
    l = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9"]
    if able:
        l.append("")
    return random.choice(l)


def gen_node_str(v, l, r):
    return f"{v}({l})({r})"


def gen_tree_str(n):
    tree_str = gen_node_str(rnd_num_str(False), rnd_num_str(), rnd_num_str())
    for _ in range(n):
        l = [tree_str, rnd_num_str()]
        random.shuffle(l)
        tree_str = gen_node_str(rnd_num_str(False), l[0], l[1])
    return tree_str


def gen_rnd_tree_str(n):
    a = random.randint(0, n)
    b = n - a
    return gen_node_str(rnd_num_str(False), gen_tree_str(a), gen_tree_str(b))


def gen_rnd_tree(n):
    t = Tree()
    t.build_tree(gen_rnd_tree_str(n))
    return t


def parse_tree_cmd(cmd: str)->str:
    return cmd.split('"')[1].split('"')[0]


def gen_block_str(ins: str, num: int) -> str:
    return f"('{ins}',{'NULL' if 'delMin' in ins else str(num)})"


def rnd_block_str() -> str:
    return gen_block_str(random.choice(["insert", "delMin"]), random.randint(0, NUM_RANGE_TEST_HEAP))


def gen_heap_str(n: int) -> str:
    res = ""
    for _ in range(n):
        res += (rnd_block_str() + ",")

    return f"[{res[:-1]}]"


def parse_heap_cmd(cmd_str: str) -> list:
    res = []
    cmd_str = cmd_str[4:-2]
    cmd = cmd_str.split("('")[1:]
    for i in cmd:
        t = i.split("'")
        tmp = t[1][1:].split(")")[0]
        res.append([t[0], "NULL" if "NULL" in tmp else int(tmp)])
    return res

class Task:
    set = []
    task_num = 0

    def run(self, cmd_str) -> str:
        return ""

    def make_cmd(self, g):
        return f'{self.task_num} "{g}"'


class Task2(Task):
    set = ["preorder", "inorder", "postorder"]
    task_num = 2

    def make_cmd(self, g):
        return f'{self.task_num} "{g}" "{random.choice(self.set)}"'

    def run(self, cmd: str):
        t = Tree()
        t.build_tree(parse_tree_cmd(cmd))

        res = ""
        if "inorder" in cmd:
            l = t.in_order()
        elif "postorder" in cmd:
            l = t.post_order()
        elif "preorder" in cmd:
            l = t.pre_order()
        else:
            return ""

        for _ in l:
            res += (str(_) + " ")

        return res[:-1]


class Task3(Task):
    task_num = 3

    def run(self, cmd: str):
        t = Tree()
        t.build_tree(parse_tree_cmd(cmd))

        return str(t.height())


class Task4(Task):
    task_num = 4

    def run(self, cmd: str):
        t = Tree()
        t.build_tree(parse_tree_cmd(cmd))

        return "1" if t.is_complete() else "0"


class Task6(Task):
    task_num = 6

    def run(self, cmd: str):
        l = parse_heap_cmd(cmd)
        h = MinHeap()
        for c in l:
            if 'delMin' in c[0]:
                h.delete_min()
            if 'insert' in c[0]:
                h.insert_key(c[1])

        return h.print()


f = open_file(FILE_OUTPUT)

tasks = [Task2(), Task3(), Task4(), None, Task6()]

t = lambda x: tasks[x - 2]


def simulate(task_num, size, res_file):
    if task_num == 6:
        cmd = t(task_num).make_cmd(gen_heap_str(size))
    else:
        cmd = t(task_num).make_cmd(gen_rnd_tree_str(size))
    py_res = t(task_num).run(cmd)
    my_res = get(FILE_EXECUTABLE, cmd).strip()
    res_file.write(f"{cmd}\t{py_res}\t{my_res}\n")
    is_success = py_res == my_res

    return is_success, cmd, py_res, my_res

num_fail = 0

for i in range(NUM_TEST_MAX):
    if i % NUM_PRINT_PROCESS == 0:
        info(f"Processing... {i/NUM_TEST_MAX*100}%")
    task_num = random.choice([2, 3, 4, 6])
    size = random.randint(1, SIZE_TREE_MAX)
    s, c, p, m = simulate(task_num, size, f)

    if not s:
        num_fail += 1
        erro("Different!")
        blan(f"Case: {c}")
        blan(f"Pypy: {p}")
        blan(f"Mymy: {m}")
        print()


info(f"Done! Success: {str((NUM_TEST_MAX - num_fail)/NUM_TEST_MAX * 100)}%")


