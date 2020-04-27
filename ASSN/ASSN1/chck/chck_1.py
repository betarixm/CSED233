#
# POSTECH CSED233 ASSN1 AUTO CHECKER
# Python 3.7+
#
# By beta@plus, minjae gwon.
# github.com/beta-lux
#

import random
import subprocess
import os

NUM_COMMAND_MAX = 10
NUM_TEST_MAX = 10000
NUM_PRINT_PROCESS = 100
FILE_EXECUTABLE = "pa1"
FILE_OUTPUT = "new_result.csv"

info = lambda x: print(f"[+] {x}")
erro = lambda x: print(f"[-] {x}")
blan = lambda x: print(f"    {x}")


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


class Task:
    set = []
    task_num = 0

    def run(self, cmd_str):
        return []

    def make(self):
        cmd = self.set[random.randint(0, len(self.set) - 1)]
        num = "NULL" if (("dequeue" in cmd) or ("pop" in cmd)) else (
            random.randint(0, 5) if ("insert_at" in cmd) else (random.randint(-20, 20)))
        return f"('{cmd}',{num})"

    def make_cases(self, size):
        case = f'{self.task_num} "['
        for _ in range(size):
            case = f"{case}{self.make()},"

        case = case[:-1] + ']"'

        return case

    def simulate(self, cmd_str):
        num_task, cmd_list = parser(cmd_str)
        result_list = self.run(cmd_list)
        result = "error" if result_list is None else ("empty" if len(result_list) == 0 else make_str(result_list))
        return result


class Task3(Task):
    set = ["append", "insert_at"]
    task_num = 3

    def run(self, cmd_list):
        result_list = []
        for cmd in cmd_list:
            if 'append' in cmd[0]:
                result_list.append(cmd[1])
            if 'insert_at' in cmd[0]:
                if len(result_list) < cmd[1]:
                    return None
                else:
                    result_list.insert(cmd[1], 0)
        return result_list


class Task4(Task):
    set = ["push"]
    task_num = 4

    def run(self, cmd_list):
        result_list = []
        for cmd in cmd_list:
            if 'push' in cmd[0]:
                result_list.insert(0, cmd[1])
        return result_list


class Task5(Task):
    set = ["push", "pop"]
    task_num = 5

    def run(self, cmd_list):
        result_list = []
        for cmd in cmd_list:
            if 'push' in cmd[0]:
                result_list.insert(0, cmd[1])
            if 'pop' in cmd[0]:
                if len(result_list) == 0:
                    return None
                else:
                    result_list = result_list[1:]

        return result_list


class Task6(Task):
    set = ["enqueue", "dequeue"]
    task_num = 6

    def run(self, cmd_list):
        result_list = []
        for cmd in cmd_list:
            if 'enqueue' in cmd[0]:
                result_list.append(cmd[1])
            if 'dequeue' in cmd[0]:
                if len(result_list) == 0:
                    return None
                else:
                    result_list = result_list[1:]
        return result_list


f = open_file(FILE_OUTPUT)

tasks = [Task3(), Task4(), Task5(), Task6()]

t = lambda x: tasks[x - 3]


def simulate(task_num, size, res_file):
    test_case = t(task_num).make_cases(size)
    py_res = t(task_num).simulate(test_case)
    my_res = get(FILE_EXECUTABLE, test_case)
    res_file.write(f"{test_case}\t{py_res}\t{my_res}\n")
    is_success = py_res == my_res

    return is_success, test_case, py_res, my_res


num_fail = 0

for i in range(NUM_TEST_MAX):
    if i % NUM_PRINT_PROCESS == 0:
        info(f"Processing... {i/NUM_TEST_MAX*100}%")
    task_num = random.randint(3, 6)
    size = random.randint(1, NUM_COMMAND_MAX)
    s, c, p, m = simulate(task_num, size, f)

    if not s:
        num_fail += 1
        erro("Different!")
        blan(f"Case: {c}")
        blan(f"Pypy: {p}")
        blan(f"Mymy: {m}")
        print()


info(f"Done! Success: {str((NUM_TEST_MAX - num_fail)/NUM_TEST_MAX * 100)}%")

