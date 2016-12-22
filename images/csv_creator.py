import Image

symbols = {"a", "i", "u", "e", "o", "ka","ki","ku","ke","ko", "sa","shi","su","se","so", "ta","chi","tsu","te","to", "na","ni","nu","ne","no", "ha","hi","fu","he","ho", "ma","mi","mu","me","mo", "ya","yu","yo" , "ra","ri","ru","re","ro", "wa","wo" , "n", "ga","gi","gu","ge","go", "za","ji","zu","ze","zo", "da","di","du","de","do", "ba","bi","bu","be","bo", "pa","pi","pu","pe","po", "kya","kyu","kyo", "sha","shu","sho", "cha","chu","cho", "nya","nyu","nyo", "hya","hyu","hyo" , "mya","myu","myo" , "rya","ryu","ryo" , "gya","gyu","gyo" , "ja","ju","jo" , "bya","byu","byo" , "pya","pyu","pyo" }

for symbol in symbols:
	i=0
	while i<10:
		im = Image.open(symbol + '/transform' + str(i) + '.jpg')
		pix = im.load()
		x=0
		width, height = im.size
		while x<width:
			y=0
			while y<height:
				y=y+1
			x=x+1
		i=i+1
