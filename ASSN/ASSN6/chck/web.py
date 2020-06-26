# just for web!
# https://csacademy.com/app/graph_editor/


def site_to_cmd(target: str):
    res = ""
    t = target.split("\n")
    for i in t:
        res += f"('{i[0]}','{i[2]}'),"
    return f"[{res[:-1]}]"


def cmd_to_site(target: str):
    target = target.replace(" ", "")
    target = target.replace("[", "").replace("]", "")
    target = target.replace("','", " ")
    target = target.replace("'),", "\n")
    target = target.replace("('", "")

    return target


def gen(target: str):
    target = target.replace("\n", '","')
    return target


aa = """[('A-B', 4), ('A-H', 8), ('B-H', 11), ('B-C', 8), ('C-D', 7), ('D-F', 14), ('D-E', 9), ('E-F', 10), ('H-G', 1), ('G-F', 2), ('C-F', 4), ('C-I', 2), ('H-I', 7), ('I-G', 6), ('MST', 'A')]"""

aa = aa.replace(" ", "")
tmp = cmd_to_site(aa) if aa[0] == "[" else site_to_cmd(aa)
print(tmp)