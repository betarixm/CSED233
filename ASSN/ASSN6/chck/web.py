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


aa = """[('0', '1'), ('1', '0'), ('1', '2'), ('1', '3'), ('2', '1'), ('2', '5'), ('2', '6'), ('2', '7'), ('3', '1'), ('3', '4'), ('3', '5'), ('3', '6'), ('4', '3'), ('4', '5'), ('4', '8'), ('5', '2'), ('5', '3'), ('5', '4'), ('6', '2'), ('6', '3'), ('7', '2'), ('8', '4')]"""

aa = aa.replace(" ", "")
tmp = cmd_to_site(aa) if aa[0] == "[" else site_to_cmd(aa)
print(tmp)