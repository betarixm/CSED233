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


aa = """A B
B A
B C
C B
C D
D C
D A
A D
B F
F B
F G
G F
G C
C G"""

print(site_to_cmd(aa))