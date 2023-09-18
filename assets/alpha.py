from PIL import Image

file_name = input("Enter file name: ")
file_name = file_name + ".png"
print(file_name)

def converImage():
    img = Image.open(file_name)
    img = img.convert("RGBA")

    datas = img.getdata()

    newData = []

    for item in datas:
        if (item[0] > 240 and item[1] > 240 and item[2] > 240):
           newData.append((255, 255, 255, 0))
        elif (item[0] == 238 and item[1] == 238 and item[2] == 238):
            newData.append((255, 255, 255, 0))
        else:
            newData.append(item)
    
    img.putdata(newData)
    img.save("cha1.png", "PNG")
    print("Successful")

converImage()
