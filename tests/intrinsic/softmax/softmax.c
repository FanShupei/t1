#include <math.h>
#include <riscv_vector.h>
#include <stdlib.h>

#define PI (3.14159265358979f)

#define ARRAY_ZIZE 1024
float src_f32[ARRAY_ZIZE];
float actual[ARRAY_ZIZE];
float temp[ARRAY_ZIZE];

float test_data[] = {
    -5.000000000000000000,   -4.990224828934506363,    -4.980449657869012725,
    -4.970674486803519088,   -4.960899315738025450,    -4.951124144672531813,
    -4.941348973607038175,   -4.931573802541544538,    -4.921798631476050900,
    -4.912023460410557263,   -4.902248289345063625,    -4.892473118279569988,
    -4.882697947214076351,   -4.872922776148582713,    -4.863147605083089076,
    -4.853372434017595438,   -4.843597262952101801,    -4.833822091886608163,
    -4.824046920821114526,   -4.814271749755620888,    -4.804496578690127251,
    -4.794721407624633613,   -4.784946236559139976,    -4.775171065493646338,
    -4.765395894428152701,   -4.755620723362659064,    -4.745845552297165426,
    -4.736070381231671789,   -4.726295210166178151,    -4.716520039100684514,
    -4.706744868035190876,   -4.696969696969697239,    -4.687194525904203601,
    -4.677419354838709964,   -4.667644183773216326,    -4.657869012707722689,
    -4.648093841642229052,   -4.638318670576735414,    -4.628543499511241777,
    -4.618768328445748139,   -4.608993157380254502,    -4.599217986314760864,
    -4.589442815249267227,   -4.579667644183773589,    -4.569892473118279952,
    -4.560117302052786314,   -4.550342130987292677,    -4.540566959921799040,
    -4.530791788856305402,   -4.521016617790811765,    -4.511241446725318127,
    -4.501466275659824490,   -4.491691104594330852,    -4.481915933528837215,
    -4.472140762463343577,   -4.462365591397849940,    -4.452590420332356302,
    -4.442815249266862665,   -4.433040078201368139,    -4.423264907135874502,
    -4.413489736070380864,   -4.403714565004887227,    -4.393939393939393590,
    -4.384164222873899952,   -4.374389051808406315,    -4.364613880742912677,
    -4.354838709677419040,   -4.345063538611925402,    -4.335288367546431765,
    -4.325513196480938127,   -4.315738025415444490,    -4.305962854349950852,
    -4.296187683284457215,   -4.286412512218963577,    -4.276637341153469940,
    -4.266862170087976303,   -4.257086999022482665,    -4.247311827956989028,
    -4.237536656891495390,   -4.227761485826001753,    -4.217986314760508115,
    -4.208211143695014478,   -4.198435972629520840,    -4.188660801564027203,
    -4.178885630498533565,   -4.169110459433039928,    -4.159335288367546291,
    -4.149560117302052653,   -4.139784946236559016,    -4.130009775171065378,
    -4.120234604105571741,   -4.110459433040078103,    -4.100684261974584466,
    -4.090909090909090828,   -4.081133919843597191,    -4.071358748778103553,
    -4.061583577712609916,   -4.051808406647116279,    -4.042033235581622641,
    -4.032258064516129004,   -4.022482893450635366,    -4.012707722385141729,
    -4.002932551319648091,   -3.993157380254154454,    -3.983382209188660816,
    -3.973607038123167179,   -3.963831867057673541,    -3.954056695992179904,
    -3.944281524926686266,   -3.934506353861192629,    -3.924731182795698992,
    -3.914956011730205354,   -3.905180840664711717,    -3.895405669599218079,
    -3.885630498533724442,   -3.875855327468230804,    -3.866080156402737167,
    -3.856304985337243529,   -3.846529814271749892,    -3.836754643206256254,
    -3.826979472140762617,   -3.817204301075268980,    -3.807429130009775342,
    -3.797653958944281705,   -3.787878787878788067,    -3.778103616813294430,
    -3.768328445747800792,   -3.758553274682307155,    -3.748778103616813517,
    -3.739002932551319880,   -3.729227761485826242,    -3.719452590420332605,
    -3.709677419354838968,   -3.699902248289345330,    -3.690127077223851693,
    -3.680351906158358055,   -3.670576735092864418,    -3.660801564027370780,
    -3.651026392961877143,   -3.641251221896383505,    -3.631476050830889868,
    -3.621700879765395786,   -3.611925708699902149,    -3.602150537634408511,
    -3.592375366568914874,   -3.582600195503421237,    -3.572825024437927599,
    -3.563049853372433962,   -3.553274682306940324,    -3.543499511241446687,
    -3.533724340175953049,   -3.523949169110459412,    -3.514173998044965774,
    -3.504398826979472137,   -3.494623655913978499,    -3.484848484848484862,
    -3.475073313782991224,   -3.465298142717497587,    -3.455522971652003950,
    -3.445747800586510312,   -3.435972629521016675,    -3.426197458455523037,
    -3.416422287390029400,   -3.406647116324535762,    -3.396871945259042125,
    -3.387096774193548487,   -3.377321603128054850,    -3.367546432062560768,
    -3.357771260997067131,   -3.347996089931573493,    -3.338220918866079856,
    -3.328445747800586219,   -3.318670576735092581,    -3.308895405669598944,
    -3.299120234604105306,   -3.289345063538611669,    -3.279569892473118031,
    -3.269794721407624394,   -3.260019550342130756,    -3.250244379276637119,
    -3.240469208211143481,   -3.230694037145649844,    -3.220918866080156207,
    -3.211143695014662569,   -3.201368523949168932,    -3.191593352883675294,
    -3.181818181818181657,   -3.172043010752688019,    -3.162267839687194382,
    -3.152492668621700744,   -3.142717497556207107,    -3.132942326490713469,
    -3.123167155425219832,   -3.113391984359726194,    -3.103616813294232557,
    -3.093841642228738920,   -3.084066471163245282,    -3.074291300097751645,
    -3.064516129032258007,   -3.054740957966764370,    -3.044965786901270732,
    -3.035190615835777095,   -3.025415444770283457,    -3.015640273704789820,
    -3.005865102639296182,   -2.996089931573802545,    -2.986314760508308908,
    -2.976539589442815270,   -2.966764418377321633,    -2.956989247311827995,
    -2.947214076246334358,   -2.937438905180840720,    -2.927663734115347083,
    -2.917888563049853445,   -2.908113391984359808,    -2.898338220918866170,
    -2.888563049853372533,   -2.878787878787878896,    -2.869012707722385258,
    -2.859237536656891621,   -2.849462365591397983,    -2.839687194525904346,
    -2.829912023460410708,   -2.820136852394917071,    -2.810361681329423433,
    -2.800586510263929796,   -2.790811339198436158,    -2.781036168132942521,
    -2.771260997067448884,   -2.761485826001955246,    -2.751710654936461609,
    -2.741935483870967527,   -2.732160312805473890,    -2.722385141739980252,
    -2.712609970674486615,   -2.702834799608992977,    -2.693059628543499340,
    -2.683284457478005702,   -2.673509286412512065,    -2.663734115347018427,
    -2.653958944281524790,   -2.644183773216031152,    -2.634408602150537515,
    -2.624633431085043878,   -2.614858260019550240,    -2.605083088954056603,
    -2.595307917888562965,   -2.585532746823069328,    -2.575757575757575690,
    -2.565982404692082053,   -2.556207233626588415,    -2.546432062561094778,
    -2.536656891495601140,   -2.526881720430107503,    -2.517106549364613866,
    -2.507331378299120228,   -2.497556207233626591,    -2.487781036168132953,
    -2.478005865102639316,   -2.468230694037145678,    -2.458455522971652041,
    -2.448680351906158403,   -2.438905180840664766,    -2.429130009775171128,
    -2.419354838709677491,   -2.409579667644183854,    -2.399804496578690216,
    -2.390029325513196579,   -2.380254154447702941,    -2.370478983382209304,
    -2.360703812316715666,   -2.350928641251222029,    -2.341153470185728391,
    -2.331378299120234754,   -2.321603128054741116,    -2.311827956989247479,
    -2.302052785923753842,   -2.292277614858260204,    -2.282502443792766567,
    -2.272727272727272929,   -2.262952101661779292,    -2.253176930596285654,
    -2.243401759530791573,   -2.233626588465297935,    -2.223851417399804298,
    -2.214076246334310660,   -2.204301075268817023,    -2.194525904203323385,
    -2.184750733137829748,   -2.174975562072336110,    -2.165200391006842473,
    -2.155425219941348836,   -2.145650048875855198,    -2.135874877810361561,
    -2.126099706744867923,   -2.116324535679374286,    -2.106549364613880648,
    -2.096774193548387011,   -2.086999022482893373,    -2.077223851417399736,
    -2.067448680351906098,   -2.057673509286412461,    -2.047898338220918824,
    -2.038123167155425186,   -2.028347996089931549,    -2.018572825024437911,
    -2.008797653958944274,   -1.999022482893450636,    -1.989247311827956999,
    -1.979472140762463361,   -1.969696969696969724,    -1.959921798631476086,
    -1.950146627565982449,   -1.940371456500488812,    -1.930596285434995174,
    -1.920821114369501537,   -1.911045943304007899,    -1.901270772238514262,
    -1.891495601173020624,   -1.881720430107526987,    -1.871945259042033349,
    -1.862170087976539712,   -1.852394916911046074,    -1.842619745845552437,
    -1.832844574780058799,   -1.823069403714565162,    -1.813294232649071525,
    -1.803519061583577887,   -1.793743890518084250,    -1.783968719452590612,
    -1.774193548387096975,   -1.764418377321603337,    -1.754643206256109700,
    -1.744868035190615618,   -1.735092864125121981,    -1.725317693059628343,
    -1.715542521994134706,   -1.705767350928641068,    -1.695992179863147431,
    -1.686217008797653794,   -1.676441837732160156,    -1.666666666666666519,
    -1.656891495601172881,   -1.647116324535679244,    -1.637341153470185606,
    -1.627565982404691969,   -1.617790811339198331,    -1.608015640273704694,
    -1.598240469208211056,   -1.588465298142717419,    -1.578690127077223782,
    -1.568914956011730144,   -1.559139784946236507,    -1.549364613880742869,
    -1.539589442815249232,   -1.529814271749755594,    -1.520039100684261957,
    -1.510263929618768319,   -1.500488758553274682,    -1.490713587487781044,
    -1.480938416422287407,   -1.471163245356793770,    -1.461388074291300132,
    -1.451612903225806495,   -1.441837732160312857,    -1.432062561094819220,
    -1.422287390029325582,   -1.412512218963831945,    -1.402737047898338307,
    -1.392961876832844670,   -1.383186705767351032,    -1.373411534701857395,
    -1.363636363636363757,   -1.353861192570870120,    -1.344086021505376483,
    -1.334310850439882845,   -1.324535679374389208,    -1.314760508308895570,
    -1.304985337243401933,   -1.295210166177908295,    -1.285434995112414658,
    -1.275659824046921020,   -1.265884652981427383,    -1.256109481915933745,
    -1.246334310850439664,   -1.236559139784946026,    -1.226783968719452389,
    -1.217008797653958752,   -1.207233626588465114,    -1.197458455522971477,
    -1.187683284457477839,   -1.177908113391984202,    -1.168132942326490564,
    -1.158357771260996927,   -1.148582600195503289,    -1.138807429130009652,
    -1.129032258064516014,   -1.119257086999022377,    -1.109481915933528740,
    -1.099706744868035102,   -1.089931573802541465,    -1.080156402737047827,
    -1.070381231671554190,   -1.060606060606060552,    -1.050830889540566915,
    -1.041055718475073277,   -1.031280547409579640,    -1.021505376344086002,
    -1.011730205278592365,   -1.001955034213098727,    -0.9921798631476050900,
    -0.9824046920821114526,  -0.9726295210166178151,   -0.9628543499511241777,
    -0.9530791788856305402,  -0.9433040078201369028,   -0.9335288367546432653,
    -0.9237536656891496278,  -0.9139784946236559904,   -0.9042033235581623529,
    -0.8944281524926687155,  -0.8846529814271750780,   -0.8748778103616814406,
    -0.8651026392961878031,  -0.8553274682306941656,   -0.8455522971652005282,
    -0.8357771260997068907,  -0.8260019550342132533,   -0.8162267839687196158,
    -0.8064516129032259784,  -0.7966764418377323409,   -0.7869012707722387034,
    -0.7771260997067450660,  -0.7673509286412514285,   -0.7575757575757577911,
    -0.7478005865102641536,  -0.7380254154447705162,   -0.7282502443792768787,
    -0.7184750733137832412,  -0.7086999022482896038,   -0.6989247311827959663,
    -0.6891495601173023289,  -0.6793743890518086914,   -0.6695992179863150540,
    -0.6598240469208214165,  -0.6500488758553277790,   -0.6402737047898341416,
    -0.6304985337243405041,  -0.6207233626588468667,   -0.6109481915933532292,
    -0.6011730205278595918,  -0.5913978494623659543,   -0.5816226783968723169,
    -0.5718475073313786794,  -0.5620723362658850419,   -0.5522971652003914045,
    -0.5425219941348977670,  -0.5327468230694041296,   -0.5229716520039104921,
    -0.5131964809384168547,  -0.5034213098729232172,   -0.4936461388074286916,
    -0.4838709677419350541,  -0.4740957966764414167,   -0.4643206256109477792,
    -0.4545454545454541417,  -0.4447702834799605043,   -0.4349951124144668668,
    -0.4252199413489732294,  -0.4154447702834795919,   -0.4056695992179859545,
    -0.3958944281524923170,  -0.3861192570869986795,   -0.3763440860215050421,
    -0.3665689149560114046,  -0.3567937438905177672,   -0.3470185728250241297,
    -0.3372434017595304923,  -0.3274682306940368548,   -0.3176930596285432173,
    -0.3079178885630495799,  -0.2981427174975559424,   -0.2883675464320623050,
    -0.2785923753665686675,  -0.2688172043010750301,   -0.2590420332355813926,
    -0.2492668621700877551,  -0.2394916911045941177,   -0.2297165200391004802,
    -0.2199413489736068428,  -0.2101661779081132053,   -0.2003910068426195679,
    -0.1906158357771259304,  -0.1808406647116322929,   -0.1710654936461386555,
    -0.1612903225806450180,  -0.1515151515151513806,   -0.1417399804496577431,
    -0.1319648093841641057,  -0.1221896383186704682,   -0.1124144672531768308,
    -0.1026392961876831933,  -0.09286412512218955584,  -0.08308895405669591838,
    -0.07331378299120228093, -0.06353861192570864347,  -0.05376344086021500601,
    -0.04398826979472136856, -0.03421309872922773110,  -0.02443792766373409364,
    -0.01466275659824045619, -0.004887585532746818728, 0.004887585532746818728,
    0.01466275659824045619,  0.02443792766373409364,   0.03421309872922773110,
    0.04398826979472136856,  0.05376344086021500601,   0.06353861192570864347,
    0.07331378299120228093,  0.08308895405669591838,   0.09286412512218955584,
    0.1026392961876831933,   0.1124144672531768308,    0.1221896383186704682,
    0.1319648093841641057,   0.1417399804496577431,    0.1515151515151513806,
    0.1612903225806450180,   0.1710654936461386555,    0.1808406647116322929,
    0.1906158357771259304,   0.2003910068426195679,    0.2101661779081132053,
    0.2199413489736068428,   0.2297165200391004802,    0.2394916911045941177,
    0.2492668621700877551,   0.2590420332355813926,    0.2688172043010750301,
    0.2785923753665686675,   0.2883675464320623050,    0.2981427174975559424,
    0.3079178885630495799,   0.3176930596285432173,    0.3274682306940368548,
    0.3372434017595304923,   0.3470185728250241297,    0.3567937438905177672,
    0.3665689149560114046,   0.3763440860215050421,    0.3861192570869986795,
    0.3958944281524923170,   0.4056695992179859545,    0.4154447702834795919,
    0.4252199413489732294,   0.4349951124144668668,    0.4447702834799605043,
    0.4545454545454541417,   0.4643206256109477792,    0.4740957966764414167,
    0.4838709677419350541,   0.4936461388074286916,    0.5034213098729223290,
    0.5131964809384168547,   0.5229716520039104921,    0.5327468230694041296,
    0.5425219941348977670,   0.5522971652003914045,    0.5620723362658850419,
    0.5718475073313786794,   0.5816226783968723169,    0.5913978494623659543,
    0.6011730205278595918,   0.6109481915933532292,    0.6207233626588468667,
    0.6304985337243405041,   0.6402737047898341416,    0.6500488758553277790,
    0.6598240469208214165,   0.6695992179863150540,    0.6793743890518086914,
    0.6891495601173023289,   0.6989247311827959663,    0.7086999022482896038,
    0.7184750733137832412,   0.7282502443792768787,    0.7380254154447705162,
    0.7478005865102641536,   0.7575757575757577911,    0.7673509286412514285,
    0.7771260997067450660,   0.7869012707722387034,    0.7966764418377323409,
    0.8064516129032259784,   0.8162267839687196158,    0.8260019550342132533,
    0.8357771260997068907,   0.8455522971652005282,    0.8553274682306941656,
    0.8651026392961878031,   0.8748778103616814406,    0.8846529814271750780,
    0.8944281524926687155,   0.9042033235581623529,    0.9139784946236559904,
    0.9237536656891496278,   0.9335288367546432653,    0.9433040078201369028,
    0.9530791788856305402,   0.9628543499511241777,    0.9726295210166178151,
    0.9824046920821114526,   0.9921798631476050900,    1.001955034213098727,
    1.011730205278592365,    1.021505376344086002,     1.031280547409579640,
    1.041055718475073277,    1.050830889540566915,     1.060606060606060552,
    1.070381231671554190,    1.080156402737047827,     1.089931573802541465,
    1.099706744868035102,    1.109481915933528740,     1.119257086999022377,
    1.129032258064516014,    1.138807429130009652,     1.148582600195503289,
    1.158357771260996927,    1.168132942326490564,     1.177908113391984202,
    1.187683284457477839,    1.197458455522971477,     1.207233626588465114,
    1.217008797653958752,    1.226783968719452389,     1.236559139784946026,
    1.246334310850439664,    1.256109481915933301,     1.265884652981426939,
    1.275659824046920576,    1.285434995112414214,     1.295210166177907851,
    1.304985337243401489,    1.314760508308895126,     1.324535679374388764,
    1.334310850439882401,    1.344086021505376038,     1.353861192570869676,
    1.363636363636363313,    1.373411534701856951,     1.383186705767350588,
    1.392961876832844226,    1.402737047898337863,     1.412512218963831501,
    1.422287390029325138,    1.432062561094818776,     1.441837732160312413,
    1.451612903225806051,    1.461388074291299688,     1.471163245356793325,
    1.480938416422286963,    1.490713587487780600,     1.500488758553274238,
    1.510263929618768763,    1.520039100684262401,     1.529814271749756038,
    1.539589442815249676,    1.549364613880743313,     1.559139784946236951,
    1.568914956011730588,    1.578690127077224226,     1.588465298142717863,
    1.598240469208211501,    1.608015640273705138,     1.617790811339198775,
    1.627565982404692413,    1.637341153470186050,     1.647116324535679688,
    1.656891495601173325,    1.666666666666666963,     1.676441837732160600,
    1.686217008797654238,    1.695992179863147875,     1.705767350928641513,
    1.715542521994135150,    1.725317693059628787,     1.735092864125122425,
    1.744868035190616062,    1.754643206256109700,     1.764418377321603337,
    1.774193548387096975,    1.783968719452590612,     1.793743890518084250,
    1.803519061583577887,    1.813294232649071525,     1.823069403714565162,
    1.832844574780058799,    1.842619745845552437,     1.852394916911046074,
    1.862170087976539712,    1.871945259042033349,     1.881720430107526987,
    1.891495601173020624,    1.901270772238514262,     1.911045943304007899,
    1.920821114369501537,    1.930596285434995174,     1.940371456500488812,
    1.950146627565982449,    1.959921798631476086,     1.969696969696969724,
    1.979472140762463361,    1.989247311827956999,     1.999022482893450636,
    2.008797653958944274,    2.018572825024437911,     2.028347996089931549,
    2.038123167155425186,    2.047898338220918824,     2.057673509286412461,
    2.067448680351906098,    2.077223851417399736,     2.086999022482893373,
    2.096774193548387011,    2.106549364613880648,     2.116324535679374286,
    2.126099706744867923,    2.135874877810361561,     2.145650048875855198,
    2.155425219941348836,    2.165200391006842473,     2.174975562072336110,
    2.184750733137829748,    2.194525904203323385,     2.204301075268817023,
    2.214076246334310660,    2.223851417399804298,     2.233626588465297935,
    2.243401759530791573,    2.253176930596285210,     2.262952101661778848,
    2.272727272727272485,    2.282502443792766122,     2.292277614858259760,
    2.302052785923753397,    2.311827956989247035,     2.321603128054740672,
    2.331378299120234310,    2.341153470185727947,     2.350928641251221585,
    2.360703812316715222,    2.370478983382208860,     2.380254154447702497,
    2.390029325513196135,    2.399804496578689772,     2.409579667644183409,
    2.419354838709677047,    2.429130009775170684,     2.438905180840664322,
    2.448680351906157959,    2.458455522971651597,     2.468230694037145234,
    2.478005865102638872,    2.487781036168132509,     2.497556207233626147,
    2.507331378299120672,    2.517106549364614310,     2.526881720430107947,
    2.536656891495601585,    2.546432062561095222,     2.556207233626588859,
    2.565982404692082497,    2.575757575757576134,     2.585532746823069772,
    2.595307917888563409,    2.605083088954057047,     2.614858260019550684,
    2.624633431085044322,    2.634408602150537959,     2.644183773216031597,
    2.653958944281525234,    2.663734115347018871,     2.673509286412512509,
    2.683284457478006146,    2.693059628543499784,     2.702834799608993421,
    2.712609970674487059,    2.722385141739980696,     2.732160312805474334,
    2.741935483870967971,    2.751710654936461609,     2.761485826001955246,
    2.771260997067448884,    2.781036168132942521,     2.790811339198436158,
    2.800586510263929796,    2.810361681329423433,     2.820136852394917071,
    2.829912023460410708,    2.839687194525904346,     2.849462365591397983,
    2.859237536656891621,    2.869012707722385258,     2.878787878787878896,
    2.888563049853372533,    2.898338220918866170,     2.908113391984359808,
    2.917888563049853445,    2.927663734115347083,     2.937438905180840720,
    2.947214076246334358,    2.956989247311827995,     2.966764418377321633,
    2.976539589442815270,    2.986314760508308908,     2.996089931573802545,
    3.005865102639296182,    3.015640273704789820,     3.025415444770283457,
    3.035190615835777095,    3.044965786901270732,     3.054740957966764370,
    3.064516129032258007,    3.074291300097751645,     3.084066471163245282,
    3.093841642228738920,    3.103616813294232557,     3.113391984359726194,
    3.123167155425219832,    3.132942326490713469,     3.142717497556207107,
    3.152492668621700744,    3.162267839687194382,     3.172043010752688019,
    3.181818181818181657,    3.191593352883675294,     3.201368523949168932,
    3.211143695014662569,    3.220918866080156207,     3.230694037145649844,
    3.240469208211143481,    3.250244379276637119,     3.260019550342130756,
    3.269794721407624394,    3.279569892473118031,     3.289345063538611669,
    3.299120234604105306,    3.308895405669598944,     3.318670576735092581,
    3.328445747800586219,    3.338220918866079856,     3.347996089931573493,
    3.357771260997067131,    3.367546432062560768,     3.377321603128054406,
    3.387096774193548043,    3.396871945259041681,     3.406647116324535318,
    3.416422287390028956,    3.426197458455522593,     3.435972629521016231,
    3.445747800586509868,    3.455522971652003505,     3.465298142717497143,
    3.475073313782990780,    3.484848484848484418,     3.494623655913978055,
    3.504398826979471693,    3.514173998044965330,     3.523949169110458968,
    3.533724340175952605,    3.543499511241446243,     3.553274682306939880,
    3.563049853372433518,    3.572825024437927155,     3.582600195503420792,
    3.592375366568914430,    3.602150537634408067,     3.611925708699901705,
    3.621700879765395342,    3.631476050830888980,     3.641251221896382617,
    3.651026392961876255,    3.660801564027369892,     3.670576735092863530,
    3.680351906158357167,    3.690127077223850804,     3.699902248289344442,
    3.709677419354838079,    3.719452590420331717,     3.729227761485825354,
    3.739002932551318992,    3.748778103616812629,     3.758553274682306267,
    3.768328445747799904,    3.778103616813293542,     3.787878787878787179,
    3.797653958944280816,    3.807429130009774454,     3.817204301075268091,
    3.826979472140761729,    3.836754643206255366,     3.846529814271749004,
    3.856304985337242641,    3.866080156402736279,     3.875855327468229916,
    3.885630498533723554,    3.895405669599217191,     3.905180840664710828,
    3.914956011730204466,    3.924731182795698103,     3.934506353861191741,
    3.944281524926685378,    3.954056695992179016,     3.963831867057672653,
    3.973607038123166291,    3.983382209188659928,     3.993157380254153566,
    4.002932551319647203,    4.012707722385142617,     4.022482893450636254,
    4.032258064516129892,    4.042033235581623529,     4.051808406647117167,
    4.061583577712610804,    4.071358748778104442,     4.081133919843598079,
    4.090909090909091717,    4.100684261974585354,     4.110459433040078991,
    4.120234604105572629,    4.130009775171066266,     4.139784946236559904,
    4.149560117302053541,    4.159335288367547179,     4.169110459433040816,
    4.178885630498534454,    4.188660801564028091,     4.198435972629521729,
    4.208211143695015366,    4.217986314760509003,     4.227761485826002641,
    4.237536656891496278,    4.247311827956989916,     4.257086999022483553,
    4.266862170087977191,    4.276637341153470828,     4.286412512218964466,
    4.296187683284458103,    4.305962854349951741,     4.315738025415445378,
    4.325513196480939015,    4.335288367546432653,     4.345063538611926290,
    4.354838709677419928,    4.364613880742913565,     4.374389051808407203,
    4.384164222873900840,    4.393939393939394478,     4.403714565004888115,
    4.413489736070381753,    4.423264907135875390,     4.433040078201369028,
    4.442815249266862665,    4.452590420332356302,     4.462365591397849940,
    4.472140762463343577,    4.481915933528837215,     4.491691104594330852,
    4.501466275659824490,    4.511241446725318127,     4.521016617790811765,
    4.530791788856305402,    4.540566959921799040,     4.550342130987292677,
    4.560117302052786314,    4.569892473118279952,     4.579667644183773589,
    4.589442815249267227,    4.599217986314760864,     4.608993157380254502,
    4.618768328445748139,    4.628543499511241777,     4.638318670576735414,
    4.648093841642229052,    4.657869012707722689,     4.667644183773216326,
    4.677419354838709964,    4.687194525904203601,     4.696969696969697239,
    4.706744868035190876,    4.716520039100684514,     4.726295210166178151,
    4.736070381231671789,    4.745845552297165426,     4.755620723362659064,
    4.765395894428152701,    4.775171065493646338,     4.784946236559139976,
    4.794721407624633613,    4.804496578690127251,     4.814271749755620888,
    4.824046920821114526,    4.833822091886608163,     4.843597262952101801,
    4.853372434017595438,    4.863147605083089076,     4.872922776148582713,
    4.882697947214076351,    4.892473118279569988,     4.902248289345063625,
    4.912023460410557263,    4.921798631476050900,     4.931573802541544538,
    4.941348973607038175,    4.951124144672531813,     4.960899315738025450,
    4.970674486803519088,    4.980449657869012725,     4.990224828934506363,
    5.000000000000000000};

void reduce(float *a, float *result_sum, int len) {
  int count = 0;
  uint32_t vblkCnt = len;
  // set vlmax and initialize variables
  size_t vlmax = __riscv_vsetvlmax_e32m1();

  size_t l = __riscv_vsetvl_e32m8(vblkCnt);
  vfloat32m1_t vec_zero = __riscv_vfmv_v_f_f32m1(0, l);

  vfloat32m8_t vx, vy;
  vy = __riscv_vfmv_v_f_f32m8(0, __riscv_vsetvl_e32m8(vblkCnt));
  for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
    vx = __riscv_vle32_v_f32m8(a, l);
    a += l;
    vy = __riscv_vfadd_vv_f32m8(vy, vx, l);
  }
  vblkCnt = len;
  vfloat32m1_t vec_sum;
  vec_sum = __riscv_vfredusum_vs_f32m8_f32m1(vy, vec_zero,
                                             __riscv_vsetvl_e32m8(vblkCnt));
  float sum = __riscv_vfmv_f_s_f32m1_f32(vec_sum);

  *result_sum = sum;
}

void rvfdiv_f32(float *src, float *dest, float divded, int len) {
  uint32_t vblkCnt = len; /* Loop counter */
  size_t l;
  vfloat32m8_t vx, vy;
  for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
    vx = __riscv_vle32_v_f32m8(src, l);
    src += l;
    vy = __riscv_vfdiv_vf_f32m8(vx, divded, l);
    __riscv_vse32_v_f32m8(dest, vy, l);
    dest += l;
  }
}

void exp_f32_v(float *src, float *dest, int32_t len) {
  uint32_t vblkCnt = len; /* Loop counter */
  size_t l;
  vfloat32m8_t vx, vy, vz;
  vint32m8_t vx_int;

  for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
    vx = __riscv_vle32_v_f32m8(src, l);
    src += l;
    vx = __riscv_vfmul_vf_f32m8(vx, 1.4426950408889634f, l); // log2(e)
    vx_int = __riscv_vfcvt_rtz_x_f_v_i32m8(vx, l);
    vx = __riscv_vfsub_vv_f32m8(vx, __riscv_vfcvt_f_x_v_f32m8(vx_int, l), l);

    vx_int = __riscv_vadd_vx_i32m8(vx_int, 127, l);
    vx_int = __riscv_vmul_vx_i32m8(vx_int, (1 << 23), l);
    vy = __riscv_vreinterpret_v_i32m8_f32m8(vx_int);

    vx = __riscv_vfmul_vf_f32m8(vx, 0.693147180559945f, l); // ln2
    vz = __riscv_vfmul_vf_f32m8(vx, 1.0 / 5040, l);         // 1/7!
    vz = __riscv_vfmul_vv_f32m8(vx, __riscv_vfadd_vf_f32m8(vz, 1 / 720, l),
                                l); // 1/6!
    vz = __riscv_vfmul_vv_f32m8(vx, __riscv_vfadd_vf_f32m8(vz, 1.0 / 120, l),
                                l); // 1/5!
    vz = __riscv_vfmul_vv_f32m8(vx, __riscv_vfadd_vf_f32m8(vz, 1.0 / 24, l),
                                l); // 1/4!
    vz = __riscv_vfmul_vv_f32m8(vx, __riscv_vfadd_vf_f32m8(vz, 1.0 / 6, l),
                                l); // 1/3!
    vz = __riscv_vfmul_vv_f32m8(vx, __riscv_vfadd_vf_f32m8(vz, 1.0 / 2, l),
                                l); // 1/2!
    vz = __riscv_vfmul_vv_f32m8(vx, __riscv_vfadd_vf_f32m8(vz, 1.0, l),
                                l); // 1/1!
    vz = __riscv_vfadd_vf_f32m8(vz, 1, l);

    vy = __riscv_vfmul_vv_f32m8(vy, vz, l);
    __riscv_vse32_v_f32m8(dest, vy, l);
    dest += l;
  }
}

void process_max(float *src, float *dest, int32_t len) {

  uint32_t vblkCnt = len; /* Loop counter */
  size_t l = __riscv_vsetvl_e32m8(vblkCnt);
  vfloat32m1_t vec_zero = __riscv_vfmv_v_f_f32m1(0, l);

  vfloat32m8_t vx, vy;
  float max_value;
  float *src_addr = src;
  vy = __riscv_vfmv_v_f_f32m8(0, __riscv_vsetvl_e32m8(vblkCnt));
  for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
    vx = __riscv_vle32_v_f32m8(src_addr, l);
    src_addr += l;
    vy = __riscv_vfmax_vv_f32m8(vx, vy, l);
  }

  vblkCnt = len;

  vfloat32m1_t vec_max;
  vec_max = __riscv_vfredmax_vs_f32m8_f32m1(vy, vec_zero,
                                            __riscv_vsetvl_e32m8(vblkCnt));
  max_value = __riscv_vfmv_f_s_f32m1_f32(vec_max);

  for (; (l = __riscv_vsetvl_e32m8(vblkCnt)) > 0; vblkCnt -= l) {
    vx = __riscv_vle32_v_f32m8(src, l);
    src += l;
    vy = __riscv_vfsub_vf_f32m8(vx, max_value, l);
    __riscv_vse32_v_f32m8(dest, vy, l);
    dest += l;
  }
}

void softmax(void) {
  float sum;

  process_max(src_f32, temp, ARRAY_ZIZE);

  exp_f32_v(temp, temp, ARRAY_ZIZE);

  reduce(temp, &sum, ARRAY_ZIZE);

  rvfdiv_f32(temp, actual, sum, ARRAY_ZIZE);
}

int test(void) {
  int i;
  int ret = 0;

  for (i = 0; i < ARRAY_ZIZE; i++) {
    src_f32[i] = test_data[i];
  }

  softmax();

  return ret;
}

