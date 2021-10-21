import re
s= "abc12abc34abc武汉理工xy1"
print(re.findall(r"\d+\.?\d*",s)) #['12', '34', '1']
print(re.findall(r"[\u4e00-\u9fa5]+",s)) #['武汉理工’]
