import random
import subprocess
import os
import glob

BINARY_FOLDER = "src"
MAX_LIST_LEN: int = 20
MAX_EPOCH: int = 1000
RESULT_FILENAME = "submit.txt"
LOG_FILENAME = "result.tsv"

erro = lambda x: print(f"[-] {x}")
info = lambda x: print(f"[+] {x}")
blan = lambda x: print(f"    {x}")


def gen_block(isInsert:bool, num: int) -> str:
    s = "insert" if isInsert else "delete"
    return f"('{s}',{str(num)})"


def gen_rnd_block(isInsert: bool) -> str:
    return gen_block(isInsert, random.randint(-9, 9))


def gen_list(isInsert: bool, num: int) -> str:
    s = ""
    for i in range(num):
        s += f"{gen_rnd_block(isInsert)},"

    return s


def gen_rnd_list(num: int) -> str:
    s = ""
    for i in range(num):
        rnd_delete = random.choice([True, True, False])
        s += f"{gen_rnd_block(rnd_delete)},"

    return s


def gen_sort(task_num: int):
    type_sort = ["bubbleSort", "insertionSort", "mergeSort"]
    s = f"[{gen_list(True, random.randint(1, MAX_LIST_LEN))}('{type_sort[task_num - 2]}',NULL)]"
    return s


def gen_bst():
    s = f"[{gen_rnd_list(random.randint(1, MAX_LIST_LEN))[:-1]}]"
    return s


def gen_bst_insert():
    return f"[{gen_list(True, random.randint(1, MAX_LIST_LEN))[:-1]}]"


def epoch():
    task_num = random.choice([1, 2, 3, 4, 6])
    binary_list = glob.glob(f"./{BINARY_FOLDER}/*")
    result_list = []

    if task_num == 6:
        task_str = gen_bst()
    elif task_num == 5:
        task_str = gen_bst_insert()
    elif task_num == 1:
        task_str = ""
    else:
        task_str = gen_sort(task_num)

    for b in binary_list:
        result_list.append(get_result(b, task_num, task_str))

    if len(list(set(result_list))) != 1:
        erro("Different!")
        print(task_num, task_str)
        for i in range(len(binary_list)):
            info(binary_list[i])
            print(result_list[i])
            print()

    log(task_num, task_str, binary_list, result_list)


def get_result(binary, task_num, task_str):
    if os.path.isfile(RESULT_FILENAME):
        os.remove(RESULT_FILENAME)
    cmd = [binary, str(task_num), task_str]
    subprocess.run(cmd)

    with open(RESULT_FILENAME, "r") as f:
        s = f.read()

    return s


def log(task_num, task_str, binary_list, result_list):
    make_log_header(binary_list)
    row = f"{task_num}\t{task_str}\t"
    for r in result_list:
        tmp = r.replace("\n", ' [n] ')
        row += f"{tmp}\t"

    with open(LOG_FILENAME, 'a') as f:
        f.write(row[:-1] + "\n")


def make_log_header(binary_list):
    is_header_exist = False

    if os.path.isfile(LOG_FILENAME):
        with open(LOG_FILENAME, 'r') as f:
            if "task" in f.readline():
                is_header_exist = True

    if not is_header_exist:
        with open(LOG_FILENAME, 'w') as f:
            header = "task_num\ttask_str\t"
            for b in binary_list:
                header += f"{b}\t"
            f.write(header[:-1] + "\n")


def get_binary_list():
    l = []
    for filename in glob.glob(f"./{BINARY_FOLDER}/*"):
        l.append(f"./{BINARY_FOLDER}/{filename}")
    return l


for i in range(MAX_EPOCH):
    if i % 10 == 0:
        info(f"Tested {i / MAX_EPOCH * 100}%...")
    epoch()
