import random
import subprocess
import os
import glob
import sys

# DEFINE
BINARY_FOLDER = "src"
MAX_LIST_LEN: int = 10
MAX_HASH_N: int = 5
MAX_EPOCH: int = 1000000
RESULT_FILENAME = "submit.txt"
LOG_FILENAME = "result.tsv"

# Just for print.
erro = lambda x: print(f"[-] {x}")
info = lambda x: print(f"[+] {x}")
blan = lambda x: print(f"    {x}")


# Methods to Make task-string.
def gen_block(isInsert: bool, num: int) -> str:
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


def gen_tree():
    s = f"[{gen_rnd_list(random.randint(1, MAX_LIST_LEN))[:-1]}]"
    return s


def gen_tree_insert():
    return f"[{gen_list(True, random.randint(1, MAX_LIST_LEN))[:-1]}]"


def gen_key(n: int) -> int:
    l = range(2**n)
    return random.choice(l)


def gen_r(n: int) -> int:
    l = range(0, n+1, 2)
    return random.choice(l)


def gen_hash_function_str():
    n = random.randint(1, MAX_HASH_N)
    r = gen_r(n)
    key = gen_key(n)

    return f"[('n', {str(n)}), ('r', {str(r)}), ('key', {str(key)})]"


def gen_rnd_table_block_str(key: int):
    is_insert = random.choice([True, True, False])
    return gen_table_block_str(key, is_insert)


def gen_table_block_str(key: int, is_insert: bool):
    r = "insert" if is_insert else "delete"
    return f"('{str(r)}', {str(key)})"


def gen_hash_table_str():
    n = random.randint(1, MAX_HASH_N)
    r = gen_r(n)
    size = random.randint(1, 2**r)

    res = f"('n', {n}), ('r', {r}),"
    
    insert_list = []
    
    for _ in range(size):
        is_insert = True if len(insert_list) is 0 else random.choice([True, True, False])

        if is_insert:
            while True:
                k = gen_key(n)
                if k not in insert_list:
                    insert_list.append(k)
                    break
        else:
            k = random.choice(insert_list)
            insert_list.remove(k)

        res += f"{gen_table_block_str(k, is_insert)},"

    return f"[{res[:-1]}]"


# Set task-string
def epoch():
    task_num = int(random.choice(sys.argv[1:]))  # Number to Check.
    binary_list = glob.glob(f"./{BINARY_FOLDER}/*")
    result_list = []
    task_str = ""

    if task_num == 3:
        task_str = gen_tree_insert()
    elif task_num == 4:
        task_str = gen_tree()
    elif task_num == 5:
        task_str = gen_hash_function_str()
    elif task_num == 6:
        task_str = gen_hash_table_str()

    # print(task_str)
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
    subprocess.run(cmd, stdout=subprocess.DEVNULL)

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
    if i % (MAX_EPOCH // 1000) == 0:
        info(f"Tested {i / MAX_EPOCH * 100}%...")
    epoch()

info("Tested 100%!")
