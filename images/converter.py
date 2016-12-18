import Image

symbols = {"a", "i", "u", "e", "o", "ka","ki","ku","ke","ko", "sa","shi","su","se","so", "ta","chi","tsu","te","to", "na","ni","nu","ne","no", "ha","hi","fu","he","ho", "ma","mi","mu","me","mo", "ya","yu","yo" , "ra","ri","ru","re","ro", "wa","wo" , "n", "ga","gi","gu","ge","go", "za","ji","zu","ze","zo", "da","di","du","de","do", "ba","bi","bu","be","bo", "pa","pi","pu","pe","po", "kya","kyu","kyo", "sha","shu","sho", "cha","chu","cho", "nya","nyu","nyo", "hya","hyu","hyo" , "mya","myu","myo" , "rya","ryu","ryo" , "gya","gyu","gyo" , "ja","ju","jo" , "bya","byu","byo" , "pya","pyu","pyo" }
ext = '.png'
ext1 = '.jpg'
for symbol in symbols:
	str = symbol + '/' + symbol
	im = Image.open(str + ext)
	im.load()
	background = Image.new("RGB", im.size, (255, 255, 255))
	background.paste(im, mask=im.split()[3])
	background.save(str + ext1, 'JPEG', quality=100)


