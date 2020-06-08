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


aa = """[('B', 'E'),('E', 'A'),('E', 'D'),('B', 'A'),('B', 'C'),('B', 'D'),('D', 'A'),('E', 'B'),('D', 'E'),('D', 'C'),('A', 'E'),('A', 'B'),('C', 'E'),('E', 'C'),('C', 'B')]"""

print(cmd_to_site(aa))