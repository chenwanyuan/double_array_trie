import os
#lib_path = "{}/{}".format(os.path.split(os.path.abspath(__file__))[0],"_dat.so")
#print(lib_path)
if not os.path.isfile("{}/{}".format(os.path.split(os.path.abspath(__file__))[0],"_dat.so")):
    os.system("cd {} && bash my.make && cd -".format(os.path.split(os.path.abspath(__file__))[0]))