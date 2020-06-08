#! /usr/bin/python3.7

import random
import subprocess
import os
import glob
import sys
from itertools import permutations, combinations
from string import ascii_uppercase

# DEFINE
NODE_N: int = 10
BINARY_FOLDER = "src"
MAX_LIST_LEN: int = 20
MAX_HASH_N: int = 10
MAX_EPOCH: int = 1000
MAX_HASH_M: int = 10
MAX_HASH_B: int = 30
MAX_HASH_LEN: int = 30
RESULT_FILENAME = "submit.txt"
LOG_FILENAME = "result.tsv"
words = ["the","of","to","and","a","in","is","it","you","that","he","was","for","on","are","with","as","I","his","they","be","at","one","have","this","from","or","had","by","not","word","but","what","some","we","can","out","other","were","all","there","when","up","use","your","how","said","an","each","she","which","do","their","time","if","will","way","about","many","then","them","write","would","like","so","these","her","long","make","thing","see","him","two","has","look","more","day","could","go","come","did","number","sound","no","most","people","my","over","know","water","than","call","first","who","may","down","side","been","now","find","any","new","work","part","take","get","place","made","live","where","after","back","little","only","round","man","year","came","show","every","good","me","give","our","under","name","very","through","just","form","sentence","great","think","say","help","low","line","differ","turn","cause","much","mean","before","move","right","boy","old","too","same","tell","does","set","three","want","air","well","also","play","small","end","put","home","read","hand","port","large","spell","add","even","land","here","must","big","high","such","follow","act","why","ask","men","change","went","light","kind","off","need","house","picture","try","us","again","animal","point","mother","world","near","build","self","earth","father","head","stand","own","page","should","country","found","answer","school","grow","study","still","learn","plant","cover","food","sun","four","between","state","keep","eye","never","last","let","thought","city","tree","cross","farm","hard","start","might","story","saw","far","sea","draw","left","late","run","don't","while","press","close","night","real","life","few","north","open","seem","together","next","white","children","begin","got","walk","example","ease","paper","group","always","music","those","both","mark","often","letter","until","mile","river","car","feet","care","second","book","carry","took","science","eat","room","friend","began","idea","fish","mountain","stop","once","base","hear","horse","cut","sure","watch","color","face","wood","main","enough","plain","girl","usual","young","ready","above","ever","red","list","though","feel","talk","bird","soon","body","dog","family","direct","pose","leave","song","measure","door","product","black","short","numeral","class","wind","question","happen","complete","ship","area","half","rock","order","fire","south","problem","piece","told","knew","pass","since","top","whole","king","space","heard","best","hour","better","true","during","hundred","five","remember","step","early","hold","west","ground","interest","reach","fast","verb","sing","listen","six","table","travel","less","morning","ten","simple","several","vowel","toward","war","lay","against","pattern","slow","center","love","person","money","serve","appear","road","map","rain","rule","govern","pull","cold","notice","voice","unit","power","town","fine","certain","fly","fall","lead","cry","dark","machine","note","wait","plan","figure","star","box","noun","field","rest","correct","able","pound","done","beauty","drive","stood","contain","front","teach","week","final","gave","green","oh","quick","develop","ocean","warm","free","minute","strong","special","mind","behind","clear","tail","produce","fact","street","inch","multiply","nothing","course","stay","wheel","full","force","blue","object","decide","surface","deep","moon","island","foot","system","busy","test","record","boat","common","gold","possible","plane","stead","dry","wonder","laugh","thousand","ago","ran","check","game","shape","equate","hot","miss","brought","heat","snow","tire","bring","yes","distant","fill","east","paint","language","among","grand","ball","yet","wave","drop","heart","am","present","heavy","dance","engine","position","arm","wide","sail","material","size","vary","settle","speak","weight","general","ice","matter","circle","pair","include","divide","syllable","felt","perhaps","pick","sudden","count","square","reason","length","represent","art","subject","region","energy","hunt","probable","bed","brother","egg","ride","cell","believe","fraction","forest","sit","race","window","store","summer","train","sleep","prove","lone","leg","exercise","wall","catch","mount","wish","sky","board","joy","winter","sat","written","wild","instrument","kept","glass","grass","cow","job","edge","sign","visit","past","soft","fun","bright","gas","weather","month","million","bear","finish","happy","hope","flower","clothe","strange","gone","jump","baby","eight","village","meet","root","buy","raise","solve","metal","whether","push","seven","paragraph","third","shall","held","hair","describe","cook","floor","either","result","burn","hill","safe","cat","century","consider","type","law","bit","coast","copy","phrase","silent","tall","sand","soil","roll","temperature","finger","industry","value","fight","lie","beat","excite","natural","view","sense","ear","else","quite","broke","case","middle","kill","son","lake","moment","scale","loud","spring","observe","child","straight","consonant","nation","dictionary","milk","speed","method","organ","pay","age","section","dress","cloud","surprise","quiet","stone","tiny","climb","cool","design","poor","lot","experiment","bottom","key","iron","single","stick","flat","twenty","skin","smile","crease","hole","trade","melody","trip","office","receive","row","mouth","exact","symbol","die","least","trouble","shout","except","wrote","seed","tone","join","suggest","clean","break","lady","yard","rise","bad","blow","oil","blood","touch","grew","cent","mix","team","wire","cost","lost","brown","wear","garden","equal","sent","choose","fell","fit","flow","fair","bank","collect","save","control","decimal","gentle","woman","captain","practice","separate","difficult","doctor","please","protect","noon","whose","locate","ring","character","insect","caught","period","indicate","radio","spoke","atom","human","history","effect","electric","expect","crop","modern","element","hit","student","corner","party","supply","bone","rail","imagine","provide","agree","thus","capital","won't","chair","danger","fruit","rich","thick","soldier","process","operate","guess","necessary","sharp","wing","create","neighbor","wash","bat","rather","crowd","corn","compare","poem","string","bell","depend","meat","rub","tube","famous","dollar","stream","fear","sight","thin","triangle","planet","hurry","chief","colony","clock","mine","tie","enter","major","fresh","search","send","yellow","gun","allow","print","dead","spot","desert","suit","current","lift","rose","continue","block","chart","hat","sell","success","company","subtract","event","particular","deal","swim","term","opposite","wife","shoe","shoulder","spread","arrange","camp","invent","cotton","born","determine","quart","nine","truck","noise","level","chance","gather","shop","stretch","throw","shine","property","column","molecule","select","wrong","gray","repeat","require","broad","prepare","salt","nose","plural","anger","claim","continent","oxygen","sugar","death","pretty","skill","women","season","solution","magnet","silver","thank","branch","match","suffix","especially","fig","afraid","huge","sister","steel","discuss","forward","similar","guide","experience","score","apple","bought","led","pitch","coat","mass","card","band","rope","slip","win","dream","evening","condition","feed","tool","total","basic","smell","valley","nor","double","seat","arrive","master","track","parent","shore","division","sheet","substance","favor","connect","post","spend","chord","fat","glad","original","share","station","dad","bread","charge","proper","bar","offer","segment","slave","duck","instant","market","degree","populate","chick","dear","enemy","reply","drink","occur","support","speech","nature","range","steam","motion","path","liquid","log","meant","quotient","teeth","shell","neck"]


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


def gen_undirected_str():
    target = ascii_uppercase[:NODE_N]
    com = list(combinations(target, 2))
    length = random.randint(1, len(com))
    output = ""
    for _ in range(length):
        t = random.choice(com)
        output +=  "('{}', '{}'),".format(t[0], t[1])
        com.remove(t)
    return "["+output[:-1]+"]"


def gen_directed_str():
    target = ascii_uppercase[:NODE_N]
    com = list(permutations(target, 2))
    length = random.randint(1, len(com))
    output = ""
    for _ in range(length):
        t = random.choice(com)
        if(t[0]!=t[1]):
            output +=  "('{}', '{}'),".format(t[0], t[1])
        com.remove(t)
    return "["+output[:-1]+"]"


def gen_hash_block(isInsert: bool, target: str):
    return f"('{'insert' if isInsert else 'search'}', '{target}')"


def gen_hash_str():
    M = random.randint(1, MAX_HASH_M)
    b = random.randint(1, MAX_HASH_B)
    word_list = []
    res = f"('M', {M}), ('b', {b}),"
    for _ in range(random.randint(1, MAX_HASH_LEN)):
        is_insert = random.choice([True, True, False])
        if is_insert:
            tmp = random.choice(words)
            res += f"{gen_hash_block(is_insert, tmp)},"
            word_list.append(tmp)
        else:
            is_exist = random.choice([True, True, False])
            tmp = (random.choice(word_list)) if (len(word_list) > 0 and is_exist) else (random.choice(words))
            res += f"{gen_hash_block(is_insert, tmp)},"

    return f"[{res[:-1]}]"

# Set task-string
def epoch():
    task_num = int(random.choice(sys.argv[1:]))  # Number to Check.
    binary_list = glob.glob(f"./{BINARY_FOLDER}/*")
    result_list = []
    task_str = ""

    if task_num == 2:
        task_str = gen_undirected_str()
    elif task_num == 3:
        task_str = gen_directed_str()
    elif task_num == 4 or task_str == 5:
        task_str = gen_hash_str()
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
            header = "task_num\task_str\t"
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

