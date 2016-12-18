import urllib2
import os

basic_str = 'http://www.japanesewordswriting.com/wp-content/uploads/2010/09/katakana-'
symbols = {"a", "i", "u", "e", "o", "ka","ki","ku","ke","ko", "sa","shi","su","se","so", "ta","chi","tsu","te","to", "na","ni","nu","ne","no", "ha","hi","fu","he","ho", "ma","mi","mu","me","mo", "ya","yu","yo" , "ra","ri","ru","re","ro", "wa","wo" , "n", "ga","gi","gu","ge","go", "za","ji","zu","ze","zo", "da","di","du","de","do", "ba","bi","bu","be","bo", "pa","pi","pu","pe","po", "kya","kyu","kyo", "sha","shu","sho", "cha","chu","cho", "nya","nyu","nyo", "hya","hyu","hyo" , "mya","myu","myo" , "rya","ryu","ryo" , "gya","gyu","gyo" , "ja","ju","jo" , "bya","byu","byo" , "pya","pyu","pyo" }
ext = '.png'
for symbol in symbols:
	req = urllib2.Request(basic_str + symbol + ext)
	req.add_header('User-Agent', 'Mozilla/5.0 (X11; Ubuntu; Linux x86_64; rv:50.0) Gecko/20100101 Firefox/50.0')
	req.add_header('Host', 'www.japanesewordswriting.com')
	req.add_header('Referer', 'http://www.japanesewordswriting.com/ki-for-hiragana-and-katakana-67/')
	resource = urllib2.urlopen(req)
	os.makedirs("./" + symbol)
	out = open("./" + symbol + "/" + symbol + ext, 'wb')
	out.write(resource.read())
out.close()
