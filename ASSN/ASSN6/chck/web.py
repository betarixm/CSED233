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


aa = """[('A-B',4),('B-C',9),('C-E',-2),('E-C',8),('B-Z',1),('A-Z',4),('Z-C',3),('B-F',6),('A-R',7),('R-B',-4),('B-R',8),('R-F',7),('F-E',6),('E-F',5),('E-D',6),('A', 'Z')]
"""

aa = aa.replace(" ", "")
tmp = cmd_to_site(aa) if aa[0] == "[" else site_to_cmd(aa)
print(tmp)