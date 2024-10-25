import os

for i in os.listdir("./render"):
    if(i.startswith("Output")):
        pass
    else:
        os.remove(os.path.join("./render",i))