import Image
import csv
import time

symbols = ["a", "i", "u", "e", "o", "ka","ki","ku","ke","ko", "sa","shi","su","se","so", "ta","chi","tsu","te","to", "na","ni","nu","ne","no", "ha","hi","fu","he","ho", "ma","mi","mu","me","mo", "ya","yu","yo" , "ra","ri","ru","re","ro", "wa","wo" , "n", "ga","gi","gu","ge","go", "za","ji","zu","ze","zo", "da","di","du","de","do", "ba","bi","bu","be","bo", "pa","pi","pu","pe","po", "kya","kyu","kyo", "sha","shu","sho", "cha","chu","cho", "nya","nyu","nyo", "hya","hyu","hyo" , "mya","myu","myo" , "rya","ryu","ryo" , "gya","gyu","gyo" , "ja","ju","jo" , "bya","byu","byo" , "pya","pyu","pyo"]

def addToCSV(path,symbol,csv_writer):
	j=0
	while j<500:
		im = Image.open(symbol + path + str(j) + '.jpg')
		pix = im.load()
		pixels = list(im.getdata())
		x=0
		width, height = im.size
		row = []
		while x<width:
			y=0
			while y<height:
				row.append(255-pixels[x*50+y][0])
				y=y+1
			x=x+1
		csv_writer.writerow(row)
		j=j+1

with open('testJ.csv', 'wb') as csv_file:
	csv_writer = csv.writer(csv_file)
	for symbol in symbols:
		addToCSV('/transform',symbol,csv_writer)
		addToCSV('/noise',symbol,csv_writer)
		print symbol
