from PIL import Image
import sys


filename = sys.argv[1]

img = Image.open(filename).convert("1")

w, h = img.size

if h % 8 != 0:
    raise Exception("Height must be a multiple of 8")


data = []


for yblock in range(0, h, 8):
    for x in range(w):

        byte = 0

        for bit in range(8):

            pixel = img.getpixel((x, yblock + bit))

            if pixel == 0:
                byte |= (1 << bit)

        data.append(byte)


print(f"const uint8_t bitmap[] PROGMEM =")
print("{")

for i,b in enumerate(data):
    print(f"0x{b:02X},", end=" ")

    if (i+1)%12 == 0:
        print()

print("\n};")

print()
print(f"WIDTH={w}")
print(f"HEIGHT={h}")