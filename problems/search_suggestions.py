import copy
import unittest

'''
m:1 l:1 r:2 prod :v
v found 1 2
['kfnyprlqjosvbkvfvanh', 'kfnyprlqjosvbkvfvanh']
a
m:1 l:1 r:2 prod :a
a found 0 2
['kfnwqytfhroyewirkaof', 'kfnyprlqjosvbkvfvanh', 'kfnyprlqjosvbkvfvanh']
n
'''

def binSearchMod(products, searchWord, l, r, p):
        print searchWord[p]
        if l < 0 or r < 0:
            return -1, -1

        found = False
        while l <= r and not found:
            m = l + (r - l)/2
            print 'm:{} l:{} r:{} prod :{}'.format(m, l, r, searchWord[p])
            if p >= len(products[m]):
                l = m + 1
            elif searchWord[p] == products[m][p]:
                found = True
            elif searchWord[p] > products[m][p]:
                l = m + 1
            else:
                r = m - 1
        
        if found:
            for i in range(m, -1, -1):
                if len(products[i]) > p and searchWord[0 : p + 1] == products[i][0 : p + 1]:
                    l = i
                else:
                    break

            for i in range(m, len(products), 1):
                if len(products[i]) > p and searchWord[0 : p + 1] == products[i][0 : p + 1]:
                    r = i
                else:
                    break

            print searchWord[p], 'found', l, r
            return l, r
        else:
            return -1, -1
        
def suggestedProducts(products, searchWord):
        """
        :type products: List[str]
        :type searchWord: str
        :rtype: List[List[str]]
        """
        o = []
        n = len(searchWord)
        l = 0
        r = len(products) - 1
        products.sort()
        #print 'l :{} r:{}'.format(l, r)
        for i in range(n):
            l, r = binSearchMod(products, searchWord, l, r, i)
            if l < 0:
                o.append([])
            else:
                e = min(r - l + 1, 3)
                o.append(products[l : l + e])   
                print o[-1]
        return o

class Tests(unittest.TestCase):

    #@unittest.skip('skip test01')
    def test_01(self):
        products = ["mobile","mouse","moneypot","monitor","mousepad"]
        searchWord = "mouse"
        result = suggestedProducts(products, searchWord)
        expect = [
                    [ 'mobile', 'moneypot', 'monitor' ],
                    [ 'mobile', 'moneypot', 'monitor' ],
                    [ 'mouse',  'mousepad' ],
                    [ 'mouse', 'mousepad' ],
                    [ 'mouse', 'mousepad' ]
                 ]
        self.assertEqual(result, expect)
 
    @unittest.skip('skip test01')
    def test_02(self):
        products = ["california","calgary", "canyonlands", "colorado"]
        searchWord = "caltech"
        result = suggestedProducts(products, searchWord)
        #for i in result:
        #    print i
        expect = [
                    [ 'calgary', 'california', 'canyonlands' ],
                    [ 'calgary', 'california', 'canyonlands' ],
                    [ 'calgary', 'california' ],
                    [],
                    [],
                    [],
                    []
                 ]
        self.assertEqual(result, expect)
 
    @unittest.skip('skip test03')
    def test_03(self):
        products = ["california", "calgary", "canyonlands", "colorado"]
        searchWord = "xal"
        result = suggestedProducts(products, searchWord)
        expect = [
                    [],
                    [],
                    []
                 ]
        self.assertEqual(result, expect)

    @unittest.skip('skip test04')
    def test_04(self):
        products = [ "xat", "calgary", "canyonlands", "colorado"]
        searchWord = "xal"
        result = suggestedProducts(products, searchWord)
        #for i in result:
        #    print i
        expect = [
                    [ "xat" ],
                    [ "xat" ],
                    []
                 ]
        self.assertEqual(result, expect)

    @unittest.skip('skip test04')
    def test_04(self):
        products = [ "xat", "calgary", "canyonlands", "colorado"]
        searchWord = "xalasasdasdadafcasdfadfasdadd"
        result = suggestedProducts(products, searchWord)
        #for i in result:
        #    print i
        expect = [ [] ] * len(searchWord)
        expect[0] = [ "xat" ]
        expect[1] = [ "xat" ]
        self.assertEqual(result, expect)

    @unittest.skip('skip test05')
    def test_05(self):
        products = [ "xat", "calgary", "canyonlands", "colorado"]
        searchWord = "xalasasdasdadafcasdfadfasdadd"
        result = suggestedProducts(products, searchWord)
        #for i in result:
        #    print i
        expect = [ [] ] * len(searchWord)
        expect[0] = [ "xat" ]
        expect[1] = [ "xat" ]
        self.assertEqual(result, expect)

if __name__ == "__main__":
    unittest.main()
    products = ["oqjrtcokaagakchrwrdbrlpnqivwcpzwuxbdkpkhndevouwyrtmbokxolhbvrencthmyplqixnhnokbhtbstmslfbinsypubqjckiqujvmknxuomdwqkfudgiqmpzkvnshrmnoeonzyfaipdcfdwhekrazfkdlfluyvoevahsyhvqjfcizxjhucbpqdjgmqqalqnvfyrtfkyrxlavfbagxkdloetaiedqbrmtzxwwrpyewrcbntsnrdzurzlfokcxolkltouozdobqvtoldjuincumspqpujynxxetbflfnkrscxgrvennmczurjvnoalxcfcrnddfckavedjrvewmawxazviumzpudgolofsxllhgsdrnvjbipcsqsdoosfdkhavhicsfbyavwyxziefmycknhzqujqkbqhacuaebwqpkfnkovxchczohhirczixikuoktkaamchcghynclonujiyzkcghjjjtzckjxmpssfqjirnfvrddvoqvdeteegupzevydcywjsoybsflpgpzkcoztcayffscwxkofwibguysdjtmddgevjhbxrfiqliqyiczdunhosdctrvlagcugpsskpvlsdhcbpdtdwjbhchymlptjrmzmezwljxemgzecptluxbwtgoyvqwrvxkartgrebdegyqdibemnficwpgsywlzczvwujmykkyhkkxhvrtmjxcyidawfxjcagsgutndplixpepddiosflfoujxndtgxsbzarlwacjtydorlrtukbyibaktiphojmrcbwjppnuwwihuerqswjpmyblrdslnwpdnzovpslsrfbzhjywbimwdiqhxmdssjovufgbqqykozfjbylihfwanzjdtgeoimwowocykeskvivwuybdrowolstbrbenioagkgwednhymqisdvjuycjvtrurzqssxrisozysizxeoyelhglnppsjzggjunmyabzptlfktzphlmhvpoqlnrwgxauepumssyecjpwfozhxhvodsasomhtgbasijrpphbijnxcyrajypogighdxacjxqyxagfuenwrdajqsuzrjtrqjebjnbmdzbqdgmbuqofbyegnxvgsegbaqxsdjjffdxiqgqtlgclqtmjqfmbrsccnoidkugbwscamrqfqmpbfuvvoxrodoccusixfehzetsbiflonazsmacvwilarpgpwjkexykqkmklqcuhdrhhgrzofbsjvzwdaghqxajgwqmuhyyervscyiyggbqyhpvotnmaubapigegatgtqeazgcytubsuhjzipbyxnkyqveeetgecxwinwdjuawpzdieizlzqplzajafeernecfkpiilnuqdjnipjybqishinomemdxfwabhemxecuyailbogehxwwtzvaueonxkjmdvojpjjxaftvnbbsfcjjyzwartrbmxgktbhrqeynwoziddoh","kfnyprlqjosvbkvfvanhqsxpfezfafuzxchbwsdagvgtmtwdjsgnodkahyfkpyfmrbrcineichemlomrgaydmjnzbqxhzpciwkwbcsrpeafwkitjibviipnhvcqntjuwnccylnqdwxmirvnggcdwfbldnhxsjjhfqcxlggcpldamlyttzibadxzcpwecjjxekeoucanprljnsgvhpxjydazzlxofypaxcnwhhkhrtwbecouqvoxnzsitdzyrxokhdtynjgygqarnhyaqsdrgdqdmpfwdhlayltvrjalfxxctwgqtmuwgdwzxyuiictaul","kfnwqytfhroyewirkaofdwdjtzyaeamrqkbdzganjfqfykfwizgtxjhrbvnmbwyfivwrbbjralxuptonwhlvztgefnggltqekduxdhznowjsayyaieacjvewhfookivjuwmwmhlobrgummkvjwclbipmkwrpbwqlbthbokenmcaupqbtuglgqtpuognhfachuscdsztjbuffgdzajlzhmnmksdnyrhahnnhilwnqohxyjsiatzshinquevymllusyqzkjwovmgtwwfztpbcpvyjdkqcdkscpimchxdjdrxvropgbgrrccfqnatlqjlojfczeggnanpuqtebjcyezdqpxsfkegxqfeplcmfxyqmlruapeywuftbbosmpegfpcepukcsvpgmfundbvbzazwqnefmbnnxntixtormwfbnuwheahzddwksodogedymeujvxacdbguthxhlcmmblfwjrnurpfuawoghyakqkccxcgxzdraasdivjgvtjrulhgktdxjuzpdyewckrpmjrttusqubhwntpchscprcdddsbyxrqrnplgazwjvojrtxogqdvqarcspvkfljlswpktqxlndidtnhzryohyyujfncunynxkblsdpjlaifdzsjxpuapwjzwzeahrnfkgtaehwjqsligfjnmsivinygzoeaejagsvzkyicbsyfxhqaotexdsvtxuexnmqsjhmojexevbgozlkbmuuexgpklnsetscrceuvtfhrxwvloiucqbzpxwtodopesljmisfxqmxhjlehpyaodfwqbnfvjtplauiyiyrddbjdpkvznmvpbzxgemfhgpwligjwznbztyaenziwooceebfwppfpgmzczoenqtmqcjdgvdlhjpwwlqcyjmaqnjicyrocrvxxrnrhpsqvrndurviilufvwbsswtjlmefydjechqrgeqjucsjyaaudocxgpvtbfekgynmnywltxvqddtjdaunvfqjclrjsohfenjxqjpvcklfdjoaavgoukzqjijycwqipkzpcvaqzqwgwnolrqudrcqqymlhelskpvrlobsjxlgsunkdlvqdgpnnrhcgdxasbdmrcrauswiticdiwkhdvpkduqgqpujcyjkrksmhjswvqccpxfacszfdsdvoxjnlphqawjlxryprgoexjqxryuxadviwdebxjyzolpqerfkxhklgpeffahclnfyfnwudwnjjqbcazsuzekwfsprbiwztqsxtxpiemfucwgcamdowvoymuwkstyqggmtknzezacoklmiaanvsttqknedeoayakomzzzntfmyfaunsnvimvkboqcfprizsofhauflvmetrwfoigjcxjavspnaqwpagfwslxolbjgglknrcacqntfcizfkmcrdbdidvojdritvnvgnsvrhjcutojfvjaspzdodnisyuirklwcxjitakdpxaclthbxgooxmqslftctxopfencxtzktckpkpkhlkboueylshbztlvkbtkpjdcxakldxmnjnqjyscgvydlmnpfnaxaicylivtesvtoqimovynmntiijxnwinlirbmiubpwlmwdscynsywgswsklxaxjwoculminicuphgtepjxmlhaolzzxuqqawjmvlniknniwexrelrvxagbtcqnzhdmiqfkyvwnsfuzskzlcvcyluzjtesuvzdknipreueyqgzvgbeqtmcnzwtfdgmihuzwtsdxahawfiwnpzzwpnzawfzyobyriuxbnlojvkfycwprgngluhgyirhutknuvdyebwrmaarbelkhzoqpilrneitzzuysmlpczdepdngeuwcpylcysafnmzulcrzlkaskbiexjikebbrwlbcpgvmiumsafuzqcuxnpwtjgqmlmnbeauljmyrxykugovjfazsrkzsyonecfejokeiwtxvdjawbkgvlqegxcoxwhldzoblzvhydopqpatwxllccdnlmxjypjiimtczqhubuloozyiwjmcsooqvufuamaopwxsexaaohazzctezrqahkdsnkqspkjqcvocnqirwzxocbxibrwrlrhzcuxlfqsgwoqyagkmcrdedasvrzjgugbrvvbsjtmjfbdxhchbkfomefrfrwdiyhhskrqstnnwrclsphqfrbwjvlitjmwtlmx","kfnyprlqjosvbkvfvanhqsxpfezfafuzxchbwsdagvgtmtwdjsgnodkahyfkpyfmrbrcineichemlomrgaydmjnzbqxhzpciwkwbcsrpeafwkitjibviipnhvcqntjuwnccylnqdwxmirvnggcdwfbldnhxsjjhfqcxlggcpldamlyttzibadxzcpwecjjxekeoucanprljnsgvhpxjydazzlxofypaxcnwhhkhrtwbecouqvoxnzsitdzyuoyzfkyseiohccpdtnjhqlrkgpcifvatradjfurxmwfssmbpbvxeoialjeyxujpgqdunhrthidhizzqddvuqzmoenmjzunulkrjyxfugrpvkwoiwyxwgrweakhbswllbyziranhxkleggegegdailjgyteaghdqnjqdjfhyrapqmckvxgxmasnweej"]
    products.sort()
    pp = []
    for i in products:
        print i[0:10]
        pp.append(i[0:20])
    #searchWord = "kfnyprlqj"
    searchWord = "kfnyprlqjosvbkvfvanhqsxpfezfafuzxchbwsdagvgtmtwdjsgnodkahyfkp"
    print searchWord
    result = suggestedProducts(pp, searchWord)
    for i in result:
        print i
