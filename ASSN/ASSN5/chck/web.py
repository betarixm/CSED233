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


asdf = "[('A','B'),('B','C'),('C','D'),('D','A'),('A','C'),('C','A')]"

print(cmd_to_site(asdf))